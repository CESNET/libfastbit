#include "fileWrapper.h"
#include <map>
#include <fcntl.h>
#include <util.h>
#include <cstring>

//#define WRAPPER_DEBUG 1
#define BUFFER_SIZE 100

std::map<FILE *, gzFile> descriptors;

FILE* fileOpen(const char *path, const char *mode) {
	/* Open as ordinary file */
	FILE *f =  fopen(path, mode);
	if (!f) return f;

	return f;
	/* no data files pass through here */

	if (strchr(mode, '+') == NULL) {
#ifdef WRAPPER_DEBUG
		printf("Using gz\n");
#endif
		/* Add gz wrapper */
		int ft = dup(fileno(f));
		FILE *fd = fdopen(ft, mode);
		gzFile gzf = gzdopen(fileno(fd), "r");
		if (!gzf) {
			fclose(fd);
			return NULL;
		}

		/* Test whether the file is gzipped */
		if (!gzdirect(gzf)) {
			/* remember the descriptor relation */
			descriptors[fd] = gzf;
			/* We do not need both descriptors now */
			fclose(f);
			f = fd;
		} else {
#ifdef WRAPPER_DEBUG
			printf("file is not gzipped\n");
#endif
			gzclose(gzf);

			/* gzdirect moves the file offset, reset it */
			fseek(f, 0, SEEK_SET);
		}
	}
#ifdef WRAPPER_DEBUG
	else {
		printf("fileOpen: Opening file for reading AND writing! Not using compression\n");
	}

	printf("fileOpen: [%i] %s\n", fileno(f), path);
#endif

//	/* Add gz wrapper */
//	gzFile gzf = gzdopen(fileno(f), mode);
//	if (!gzf) {
//		fclose(f);
//		return NULL;
//	}
//
//	/* remember the descriptor relation */
//	descriptors[f] = gzf;

//#ifdef WRAPPER_DEBUG
//	printf("fileOpen: [%i] %s\n", fileno(f), path);
//#endif

	return f;
}

int fileClose(FILE *fp) {
#ifdef WRAPPER_DEBUG
	printf("fileClose: [%i]\n", fileno(fp));
#endif

	/* No such descriptor */
	if ( descriptors.find(fp) == descriptors.end() ) {
	  return fclose(fp);
	}

	gzFile gzf = descriptors.at(fp);
	descriptors.erase(fp);

	return gzclose(gzf);
}

size_t fileRead(void *ptr, size_t size, size_t nmemb, FILE *stream) {
#ifdef WRAPPER_DEBUG
	printf("fileRead: [%i]\n", fileno(stream));
#endif

	/* No such descriptor */
	if ( descriptors.find(stream) == descriptors.end() ) {
	  return fread(ptr, size, nmemb, stream);
	}

	return gzread(descriptors.at(stream), ptr, size * nmemb);
}

size_t fileWrite(const void *ptr, size_t size, size_t nmemb, FILE *stream) {
#ifdef WRAPPER_DEBUG
	if (stream != stderr)
		printf("fileWrite: [%i]\n", fileno(stream));
#endif

	/* No such descriptor */
	if ( descriptors.find(stream) == descriptors.end() ) {
		return fwrite(ptr, size, nmemb, stream);
	}

	return gzwrite(descriptors.at(stream), ptr, size * nmemb);
}

int fileSeek(FILE *stream, long offset, int whence) {
#ifdef WRAPPER_DEBUG
	printf("fileSeek: [%i]\n", fileno(stream));
#endif

	/* No such descriptor */
	if ( descriptors.find(stream) == descriptors.end() ) {
		return fseek(stream, offset, whence);
	}

	return gzseek(descriptors.at(stream), offset, whence);
}

long fileTell(FILE *stream) {
#ifdef WRAPPER_DEBUG
	printf("fileTell: [%i]\n", fileno(stream));
#endif

	/* No such descriptor */
	if ( descriptors.find(stream) == descriptors.end() ) {
		return ftell(stream);
	}

	gztell(descriptors.at(stream));
}

void fileRewind(FILE *stream) {
#ifdef WRAPPER_DEBUG
	printf("fileRewind: [%i]\n", fileno(stream));
#endif

	/* No such descriptor */
	if ( descriptors.find(stream) == descriptors.end() ) {
		return rewind(stream);
	}

	gzrewind(descriptors.at(stream));
}


typedef struct {
	gzFile fd;
	char *buf;
	size_t pos;
	size_t len;
} fileWrapper_t;

std::map<int, fileWrapper_t> unixDescriptors;

int unixOpen(const char *pathname, int flags, mode_t mode) {
#ifdef WRAPPER_DEBUG
	fprintf(stderr, "unixOpen: %s\n", pathname);
#endif


	/* Open as ordinary file */
	int f = open(pathname, flags, mode);
	if (f < 0) return f;

	if (flags != OPEN_READWRITE) {
#ifdef WRAPPER_DEBUG
		fprintf(stderr, "Using gz\n");
#endif
		/* Translate open flags to gzdopen mode */
		char gzmode[3] = {'\0'};

		switch (flags) {
			case OPEN_APPENDONLY:
#ifdef WRAPPER_DEBUG
				fprintf(stderr, "OPEN_APPENDONLY\n");
#endif
				gzmode[0] = 'a';
				break;
			case OPEN_READONLY:
#ifdef WRAPPER_DEBUG
				fprintf(stderr, "OPEN_READONLY\n");
#endif
				gzmode[0] = 'r';
				break;
			case OPEN_WRITEADD:
#ifdef WRAPPER_DEBUG
				fprintf(stderr, "OPEN_WRITEADD\n");
#endif
				gzmode[0] = 'w';
				break;
			case OPEN_WRITENEW:
#ifdef WRAPPER_DEBUG
				fprintf(stderr, "OPEN_WRITENEW\n");
#endif
				gzmode[0] = 'w';
				break;
			default: /* open for reading */
#ifdef WRAPPER_DEBUG
				fprintf(stderr, "default\n");
#endif
				gzmode[0] = 'r';
				break;
		}

		/* Add gz wrapper */
		int fd = dup(f);
#ifdef WRAPPER_DEBUG
		fprintf(stderr, "Using mode '%s' for [%i,%i]\n", gzmode, f, fd);
#endif
		fileWrapper_t fw;
		fw.buf = NULL;
		fw.pos = 0;

		fw.fd = gzdopen(fd, gzmode);
		if (!fw.fd) {
			close(fd);
			return -1;
		}

		/* Test whether the file is gzipped */
		if (!gzdirect(fw.fd)) {
			/* We do not need both descriptors now */
			close(f);
			f = fd;

			/* writing to new file is complicated, we need to buffer all data in order to allow seeking */
			if (flags == OPEN_WRITENEW) {
				fw.buf = (char *) malloc(BUFFER_SIZE);
				if (!fw.buf) {
					perror("Cannot allocate memory for file buffer");
					exit(-1);
				}
				fw.len = BUFFER_SIZE;
			}

			/* save the descriptor */
			unixDescriptors[fd] = fw;
		} else {
#ifdef WRAPPER_DEBUG
			fprintf(stderr, "file is not gzipped\n");
#endif
			gzclose(fw.fd);

			/* gzdirect moves the file offset, reset it */
			lseek(f, 0, SEEK_SET);
		}
	}
#ifdef WRAPPER_DEBUG
	else {
		fprintf(stderr, "unixOpen: Opening file for reading AND writing! Not using compression\n");
	}

	fprintf(stderr, "unixOpen: [%i] %s\n", f, pathname);
#endif
	return f;
}

int unixOpen(const char *pathname, int flags) {
	return unixOpen(pathname, flags, 0);
}

ssize_t unixRead(int fd, void *buf, size_t count) {
#ifdef WRAPPER_DEBUG
	fprintf(stderr, "unixRead: [%i]\n", fd);
#endif

	/* No such descriptor */
	if ( unixDescriptors.find(fd) == unixDescriptors.end() ) {
		return read(fd, buf, count);
	}

#ifdef WRAPPER_DEBUG
	fprintf(stderr, "Using gz\n");
#endif

	return gzread(unixDescriptors.at(fd).fd, buf, count);
}

ssize_t unixWrite(int fd, const void *buf, size_t count) {
#ifdef WRAPPER_DEBUG
	fprintf(stderr, "unixWrite: [%i]\n", fd);
#endif

	/* No such descriptor */
	if (unixDescriptors.find(fd) == unixDescriptors.end() ) {
		return write(fd, buf, count);
	}

#ifdef WRAPPER_DEBUG
	fprintf(stderr, "Using gz\n");
#endif
	fileWrapper_t &fw = unixDescriptors[fd]; /* Reference to fileWrapper */
	int i = -1;

	if (fw.buf == NULL) {
		/* Standard write */
		i = gzwrite(fw.fd, buf, count);

	} else {
		/* Write to buffer */
		/* Check size first */
		if ((fw.pos + count) > fw.len) {
			fw.len = fw.len*2 + count; /* TODO use better heuristics */
			fw.buf = (char *) realloc(fw.buf, fw.len);
			if (!fw.buf) {
				perror("Cannot allocate memory for file buffer");
				exit(-1);
			}
		}

		/* Copy to buffer */
		memcpy(fw.buf + fw.pos, buf, count);
		fw.pos += count;

		/* set return value */
		i = count;
	}

#ifdef WRAPPER_DEBUG
		fprintf(stderr, "Written %i bytes of %i\n", i, count);
#endif

	return i;
}

int unixClose(int fd) {
#ifdef WRAPPER_DEBUG
	fprintf(stderr, "unixClose: [%i]\n", fd);
#endif

	/* No such descriptor */
	if ( unixDescriptors.find(fd) == unixDescriptors.end() ) {
	  return close(fd);
	}

#ifdef WRAPPER_DEBUG
	fprintf(stderr, "Using gz\n");
#endif
	fileWrapper_t fw = unixDescriptors.at(fd); /* Copy element */
	unixDescriptors.erase(fd);

	/* Check the buffer */
	if (fw.buf != NULL) {
		gzwrite(fw.fd, fw.buf, fw.pos);
		free(fw.buf);
	}

	int i = gzclose(fw.fd);
	if (i != Z_OK) fprintf(stderr, "unixClose: %s\n", gzerror(fw.fd, &i));
	return i;
}

off_t unixLseek(int fd, off_t offset, int whence) {
#ifdef WRAPPER_DEBUG
	fprintf(stderr, "unixLseek: (offset: %i) (whence: %i) [%i]\n", offset, whence, fd);
#endif

	/* No such descriptor */
	if ( unixDescriptors.find(fd) == unixDescriptors.end() ) {
		return lseek(fd, offset, whence);
	}

#ifdef WRAPPER_DEBUG
	fprintf(stderr, "Using gz\n");
#endif
	fileWrapper_t &fw = unixDescriptors[fd]; /* Reference to fileWrapper */

	/* Check whether we work with a buffer */
	if (fw.buf != NULL) {
		switch (whence) {
		case SEEK_SET:
				if (offset < 0) return -1;

				if (fw.len < offset) {
					/* skip after the buffer. realloc */
					fw.len = offset + BUFFER_SIZE;
					fw.buf = (char *) realloc(fw.buf, fw.len);
					if (!fw.buf) {
						perror("Cannot allocate memory for file buffer");
						exit(-1);
					}
				}
				/* move the position */
				fw.pos = offset;

			break;
		case SEEK_CUR:
			if (fw.pos + offset < 0) return -1;

			if (fw.pos + offset > fw.len) {
				/* skip after the buffer. realloc */
				fw.len = fw.pos + offset + BUFFER_SIZE;
				fw.buf = (char *) realloc(fw.buf, fw.len);
				if (!fw.buf) {
					perror("Cannot allocate memory for file buffer");
					exit(-1);
				}
			}
			/* move the position */
			fw.pos += offset;

			break;
		case SEEK_END:
			if (fw.len + offset < 0) return -1;

			if (offset > 0) {
				/* skip after the buffer. realloc */
				fw.len += offset + BUFFER_SIZE;
				fw.buf = (char *) realloc(fw.buf, fw.len);
				if (!fw.buf) {
					perror("Cannot allocate memory for file buffer");
					exit(-1);
				}
			}
			/* move the position */
			fw.pos = fw.len + offset;

			break;
		}

		/* return current position */
		return (fw.pos);
	}

	return gzseek(unixDescriptors.at(fd).fd, offset, whence);
}

int unixStat(const char *path, struct stat *buf) {
	int ret, direct;

#ifdef WRAPPER_DEBUG
	fprintf(stderr, "unixStat: %s\n", path);
#endif

	/* Call stat */
	ret = stat(path, buf);

	/* End on error */
	if (ret < 0) {
		return ret;
	}

	/* Check whether the file is compressed */
	gzFile gzf = gzopen(path, "r");
	direct = gzdirect(gzf);
	gzclose(gzf);

	/* Do nothing more for uncompressed file */
	if (direct) return ret;

#ifdef WRAPPER_DEBUG
	fprintf(stderr, "unixStat: getting compressed file size\n");
#endif

	/* Get uncompressed file length */
	uint32_t length = 0;
	int f = open(path, O_RDONLY);
	lseek(f, -4, SEEK_END);
	read(f, &length, 4);
	close(f);

	/* Update the length return in stat */
	buf->st_size = length;

	return ret;
}

