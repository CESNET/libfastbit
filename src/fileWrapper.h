/*
 * fileWrapper.h
 *
 *  Created on: Jan 30, 2014
 *      Author: velan
 */

#ifndef FILEWRAPPER_H_
#define FILEWRAPPER_H_

#include<stdio.h>
#include<zlib.h>

FILE* fileOpen(const char *path, const char *mode);
int fileClose(FILE *fp);
size_t fileRead(void *ptr, size_t size, size_t nmemb, FILE *stream);
size_t fileWrite(const void *ptr, size_t size, size_t nmemb, FILE *stream);
int fileSeek(FILE *stream, long offset, int whence);
long fileTell(FILE *stream);
void fileRewind(FILE *stream);

int unixOpen(const char *pathname, int flags, mode_t mode);
int unixOpen(const char *pathname, int flags);
ssize_t unixRead(int fd, void *buf, size_t count);
ssize_t unixWrite(int fd, const void *buf, size_t count);
int unixClose(int fd);
off_t unixLseek(int fd, off_t offset, int whence);
int unixStat(const char *path, struct stat *buf);


#endif /* FILEWRAPPER_H_ */
