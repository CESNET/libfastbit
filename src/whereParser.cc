/* A Bison parser, made by GNU Bison 2.7.12-4996.  */

/* Skeleton implementation for Bison LALR(1) parsers in C++
   
      Copyright (C) 2002-2013 Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.
   
   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */
/* "%code top" blocks.  */
/* Line 276 of lalr1.cc  */
#line 6 "whereParser.yy"

/** \file Defines the parser for the where clause accepted by FastBit IBIS.
    The definitions are processed through bison.
*/

#include <iostream>


/* Line 276 of lalr1.cc  */
#line 45 "whereParser.cc"

// Take the name prefix into account.
#define yylex   ibislex

/* First part of user declarations.  */

/* Line 283 of lalr1.cc  */
#line 53 "whereParser.cc"


#include "whereParser.hh"

/* User implementation prologue.  */
/* Line 289 of lalr1.cc  */
#line 98 "whereParser.yy"

#include "whereLexer.h"

#undef yylex
#define yylex driver.lexer->lex

/* Line 289 of lalr1.cc  */
#line 68 "whereParser.cc"


# ifndef YY_NULL
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULL nullptr
#  else
#   define YY_NULL 0
#  endif
# endif

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* FIXME: INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

# ifndef YYLLOC_DEFAULT
#  define YYLLOC_DEFAULT(Current, Rhs, N)                               \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).begin  = YYRHSLOC (Rhs, 1).begin;                   \
          (Current).end    = YYRHSLOC (Rhs, N).end;                     \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).begin = (Current).end = YYRHSLOC (Rhs, 0).end;      \
        }                                                               \
    while (/*CONSTCOND*/ false)
# endif


/* Suppress unused-variable warnings by "using" E.  */
#define YYUSE(e) ((void) (e))

/* Enable debugging if requested.  */
#if YYDEBUG

/* A pseudo ostream that takes yydebug_ into account.  */
# define YYCDEBUG if (yydebug_) (*yycdebug_)

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)	\
do {							\
  if (yydebug_)						\
    {							\
      *yycdebug_ << Title << ' ';			\
      yy_symbol_print_ ((Type), (Value), (Location));	\
      *yycdebug_ << std::endl;				\
    }							\
} while (false)

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug_)				\
    yy_reduce_print_ (Rule);		\
} while (false)

# define YY_STACK_PRINT()		\
do {					\
  if (yydebug_)				\
    yystack_print_ ();			\
} while (false)

#else /* !YYDEBUG */

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Type, Value, Location) YYUSE(Type)
# define YY_REDUCE_PRINT(Rule)        static_cast<void>(0)
# define YY_STACK_PRINT()             static_cast<void>(0)

#endif /* !YYDEBUG */

#define yyerrok		(yyerrstatus_ = 0)
#define yyclearin	(yychar = yyempty_)

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)


namespace ibis {
/* Line 357 of lalr1.cc  */
#line 163 "whereParser.cc"

  /* Return YYSTR after stripping away unnecessary quotes and
     backslashes, so that it's suitable for yyerror.  The heuristic is
     that double-quoting is unnecessary unless the string contains an
     apostrophe, a comma, or backslash (other than backslash-backslash).
     YYSTR is taken from yytname.  */
  std::string
  whereParser::yytnamerr_ (const char *yystr)
  {
    if (*yystr == '"')
      {
        std::string yyr = "";
        char const *yyp = yystr;

        for (;;)
          switch (*++yyp)
            {
            case '\'':
            case ',':
              goto do_not_strip_quotes;

            case '\\':
              if (*++yyp != '\\')
                goto do_not_strip_quotes;
              /* Fall through.  */
            default:
              yyr += *yyp;
              break;

            case '"':
              return yyr;
            }
      do_not_strip_quotes: ;
      }

    return yystr;
  }


  /// Build a parser object.
  whereParser::whereParser (class ibis::whereClause& driver_yyarg)
    :
#if YYDEBUG
      yydebug_ (false),
      yycdebug_ (&std::cerr),
#endif
      driver (driver_yyarg)
  {
  }

  whereParser::~whereParser ()
  {
  }

#if YYDEBUG
  /*--------------------------------.
  | Print this symbol on YYOUTPUT.  |
  `--------------------------------*/

  inline void
  whereParser::yy_symbol_value_print_ (int yytype,
			   const semantic_type* yyvaluep, const location_type* yylocationp)
  {
    YYUSE (yylocationp);
    YYUSE (yyvaluep);
    std::ostream& yyo = debug_stream ();
    std::ostream& yyoutput = yyo;
    YYUSE (yyoutput);
    YYUSE (yytype);
  }


  void
  whereParser::yy_symbol_print_ (int yytype,
			   const semantic_type* yyvaluep, const location_type* yylocationp)
  {
    *yycdebug_ << (yytype < yyntokens_ ? "token" : "nterm")
	       << ' ' << yytname_[yytype] << " ("
	       << *yylocationp << ": ";
    yy_symbol_value_print_ (yytype, yyvaluep, yylocationp);
    *yycdebug_ << ')';
  }
#endif

  void
  whereParser::yydestruct_ (const char* yymsg,
			   int yytype, semantic_type* yyvaluep, location_type* yylocationp)
  {
    YYUSE (yylocationp);
    YYUSE (yymsg);
    YYUSE (yyvaluep);

    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

    switch (yytype)
    {
      case 31: /* "signed integer sequence" */
/* Line 452 of lalr1.cc  */
#line 95 "whereParser.yy"
        { delete ((*yyvaluep).stringVal); };
/* Line 452 of lalr1.cc  */
#line 266 "whereParser.cc"
        break;
      case 32: /* "unsigned integer sequence" */
/* Line 452 of lalr1.cc  */
#line 95 "whereParser.yy"
        { delete ((*yyvaluep).stringVal); };
/* Line 452 of lalr1.cc  */
#line 273 "whereParser.cc"
        break;
      case 33: /* "name string" */
/* Line 452 of lalr1.cc  */
#line 95 "whereParser.yy"
        { delete ((*yyvaluep).stringVal); };
/* Line 452 of lalr1.cc  */
#line 280 "whereParser.cc"
        break;
      case 34: /* "number sequence" */
/* Line 452 of lalr1.cc  */
#line 95 "whereParser.yy"
        { delete ((*yyvaluep).stringVal); };
/* Line 452 of lalr1.cc  */
#line 287 "whereParser.cc"
        break;
      case 35: /* "string sequence" */
/* Line 452 of lalr1.cc  */
#line 95 "whereParser.yy"
        { delete ((*yyvaluep).stringVal); };
/* Line 452 of lalr1.cc  */
#line 294 "whereParser.cc"
        break;
      case 36: /* "string literal" */
/* Line 452 of lalr1.cc  */
#line 95 "whereParser.yy"
        { delete ((*yyvaluep).stringVal); };
/* Line 452 of lalr1.cc  */
#line 301 "whereParser.cc"
        break;
      case 43: /* qexpr */
/* Line 452 of lalr1.cc  */
#line 96 "whereParser.yy"
        { delete ((*yyvaluep).whereNode); };
/* Line 452 of lalr1.cc  */
#line 308 "whereParser.cc"
        break;
      case 44: /* simpleRange */
/* Line 452 of lalr1.cc  */
#line 96 "whereParser.yy"
        { delete ((*yyvaluep).whereNode); };
/* Line 452 of lalr1.cc  */
#line 315 "whereParser.cc"
        break;
      case 45: /* compRange2 */
/* Line 452 of lalr1.cc  */
#line 96 "whereParser.yy"
        { delete ((*yyvaluep).whereNode); };
/* Line 452 of lalr1.cc  */
#line 322 "whereParser.cc"
        break;
      case 46: /* compRange3 */
/* Line 452 of lalr1.cc  */
#line 96 "whereParser.yy"
        { delete ((*yyvaluep).whereNode); };
/* Line 452 of lalr1.cc  */
#line 329 "whereParser.cc"
        break;
      case 47: /* mathExpr */
/* Line 452 of lalr1.cc  */
#line 96 "whereParser.yy"
        { delete ((*yyvaluep).whereNode); };
/* Line 452 of lalr1.cc  */
#line 336 "whereParser.cc"
        break;

      default:
        break;
    }
  }

  void
  whereParser::yypop_ (unsigned int n)
  {
    yystate_stack_.pop (n);
    yysemantic_stack_.pop (n);
    yylocation_stack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
  whereParser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  whereParser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  whereParser::debug_level_type
  whereParser::debug_level () const
  {
    return yydebug_;
  }

  void
  whereParser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif

  inline bool
  whereParser::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  inline bool
  whereParser::yy_table_value_is_error_ (int yyvalue)
  {
    return yyvalue == yytable_ninf_;
  }

  int
  whereParser::parse ()
  {
    /// Lookahead and lookahead in internal form.
    int yychar = yyempty_;
    int yytoken = 0;

    // State.
    int yyn;
    int yylen = 0;
    int yystate = 0;

    // Error handling.
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// Semantic value of the lookahead.
    static semantic_type yyval_default;
    semantic_type yylval = yyval_default;
    /// Location of the lookahead.
    location_type yylloc;
    /// The locations where the error started and ended.
    location_type yyerror_range[3];

    /// $$.
    semantic_type yyval;
    /// @$.
    location_type yyloc;

    int yyresult;

    // FIXME: This shoud be completely indented.  It is not yet to
    // avoid gratuitous conflicts when merging into the master branch.
    try
      {
    YYCDEBUG << "Starting parse" << std::endl;


/* User initialization code.  */
/* Line 539 of lalr1.cc  */
#line 29 "whereParser.yy"
{ // initialize location object
    yylloc.begin.filename = yylloc.end.filename = &(driver.clause_);
}
/* Line 539 of lalr1.cc  */
#line 436 "whereParser.cc"

    /* Initialize the stacks.  The initial state will be pushed in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystate_stack_.clear ();
    yysemantic_stack_.clear ();
    yylocation_stack_.clear ();
    yysemantic_stack_.push (yylval);
    yylocation_stack_.push (yylloc);

    /* New state.  */
  yynewstate:
    yystate_stack_.push (yystate);
    YYCDEBUG << "Entering state " << yystate << std::endl;

    /* Accept?  */
    if (yystate == yyfinal_)
      goto yyacceptlab;

    goto yybackup;

    /* Backup.  */
  yybackup:

    /* Try to take a decision without lookahead.  */
    yyn = yypact_[yystate];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    /* Read a lookahead token.  */
    if (yychar == yyempty_)
      {
        YYCDEBUG << "Reading a token: ";
        yychar = yylex (&yylval, &yylloc);
      }

    /* Convert token to internal form.  */
    if (yychar <= yyeof_)
      {
	yychar = yytoken = yyeof_;
	YYCDEBUG << "Now at end of input." << std::endl;
      }
    else
      {
	yytoken = yytranslate_ (yychar);
	YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
      }

    /* If the proper action on seeing token YYTOKEN is to reduce or to
       detect an error, take that action.  */
    yyn += yytoken;
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yytoken)
      goto yydefault;

    /* Reduce or error.  */
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
	if (yy_table_value_is_error_ (yyn))
	  goto yyerrlab;
	yyn = -yyn;
	goto yyreduce;
      }

    /* Shift the lookahead token.  */
    YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

    /* Discard the token being shifted.  */
    yychar = yyempty_;

    yysemantic_stack_.push (yylval);
    yylocation_stack_.push (yylloc);

    /* Count tokens shifted since error; after three, turn off error
       status.  */
    if (yyerrstatus_)
      --yyerrstatus_;

    yystate = yyn;
    goto yynewstate;

  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[yystate];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;

  /*-----------------------------.
  | yyreduce -- Do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    /* If YYLEN is nonzero, implement the default value of the action:
       `$$ = $1'.  Otherwise, use the top of the stack.

       Otherwise, the following line sets YYVAL to garbage.
       This behavior is undocumented and Bison
       users should not rely upon it.  */
    if (yylen)
      yyval = yysemantic_stack_[yylen - 1];
    else
      yyval = yysemantic_stack_[0];

    // Compute the default @$.
    {
      slice<location_type, location_stack_type> slice (yylocation_stack_, yylen);
      YYLLOC_DEFAULT (yyloc, slice, yylen);
    }

    // Perform the reduction.
    YY_REDUCE_PRINT (yyn);
    switch (yyn)
      {
          case 2:
/* Line 664 of lalr1.cc  */
#line 107 "whereParser.yy"
    {
#if defined(DEBUG) && DEBUG + 0 > 1
    LOGGER(ibis::gVerbose >= 0)
	<< __FILE__ << ":" << __LINE__ << " parsing -- " << *(yysemantic_stack_[(3) - (1)].whereNode)
	<< " || " << *(yysemantic_stack_[(3) - (3)].whereNode);
#endif
    (yyval.whereNode) = new ibis::qExpr(ibis::qExpr::LOGICAL_OR);
    (yyval.whereNode)->setRight((yysemantic_stack_[(3) - (3)].whereNode));
    (yyval.whereNode)->setLeft((yysemantic_stack_[(3) - (1)].whereNode));
}
    break;

  case 3:
/* Line 664 of lalr1.cc  */
#line 117 "whereParser.yy"
    {
#if defined(DEBUG) && DEBUG + 0 > 1
    LOGGER(ibis::gVerbose >= 0)
	<< __FILE__ << ":" << __LINE__ << " parsing -- " << *(yysemantic_stack_[(3) - (1)].whereNode)
	<< " ^ " << *(yysemantic_stack_[(3) - (3)].whereNode);
#endif
    (yyval.whereNode) = new ibis::qExpr(ibis::qExpr::LOGICAL_XOR);
    (yyval.whereNode)->setRight((yysemantic_stack_[(3) - (3)].whereNode));
    (yyval.whereNode)->setLeft((yysemantic_stack_[(3) - (1)].whereNode));
}
    break;

  case 4:
/* Line 664 of lalr1.cc  */
#line 127 "whereParser.yy"
    {
#if defined(DEBUG) && DEBUG + 0 > 1
    LOGGER(ibis::gVerbose >= 0)
	<< __FILE__ << ":" << __LINE__ << " parsing -- " << *(yysemantic_stack_[(3) - (1)].whereNode)
	<< " && " << *(yysemantic_stack_[(3) - (3)].whereNode);
#endif
    (yyval.whereNode) = new ibis::qExpr(ibis::qExpr::LOGICAL_AND);
    (yyval.whereNode)->setRight((yysemantic_stack_[(3) - (3)].whereNode));
    (yyval.whereNode)->setLeft((yysemantic_stack_[(3) - (1)].whereNode));
}
    break;

  case 5:
/* Line 664 of lalr1.cc  */
#line 137 "whereParser.yy"
    {
#if defined(DEBUG) && DEBUG + 0 > 1
    LOGGER(ibis::gVerbose >= 0)
	<< __FILE__ << ":" << __LINE__ << " parsing -- " << *(yysemantic_stack_[(3) - (1)].whereNode)
	<< " &~ " << *(yysemantic_stack_[(3) - (3)].whereNode);
#endif
    (yyval.whereNode) = new ibis::qExpr(ibis::qExpr::LOGICAL_MINUS);
    (yyval.whereNode)->setRight((yysemantic_stack_[(3) - (3)].whereNode));
    (yyval.whereNode)->setLeft((yysemantic_stack_[(3) - (1)].whereNode));
}
    break;

  case 6:
/* Line 664 of lalr1.cc  */
#line 147 "whereParser.yy"
    {
#if defined(DEBUG) && DEBUG + 0 > 1
    LOGGER(ibis::gVerbose >= 0)
	<< __FILE__ << ":" << __LINE__ << " parsing -- ! " << *(yysemantic_stack_[(2) - (2)].whereNode);
#endif
    (yyval.whereNode) = new ibis::qExpr(ibis::qExpr::LOGICAL_NOT);
    (yyval.whereNode)->setLeft((yysemantic_stack_[(2) - (2)].whereNode));
}
    break;

  case 7:
/* Line 664 of lalr1.cc  */
#line 155 "whereParser.yy"
    {
    (yyval.whereNode) = (yysemantic_stack_[(3) - (2)].whereNode);
}
    break;

  case 11:
/* Line 664 of lalr1.cc  */
#line 164 "whereParser.yy"
    {
#if defined(DEBUG) && DEBUG + 0 > 1
    LOGGER(ibis::gVerbose >= 0)
	<< __FILE__ << ":" << __LINE__ << " parsing -- " << *(yysemantic_stack_[(3) - (1)].stringVal) << " IN ("
	<< *(yysemantic_stack_[(3) - (3)].stringVal) << ")";
#endif
    (yyval.whereNode) = new ibis::qDiscreteRange((yysemantic_stack_[(3) - (1)].stringVal)->c_str(), (yysemantic_stack_[(3) - (3)].stringVal)->c_str());
    delete (yysemantic_stack_[(3) - (3)].stringVal);
    delete (yysemantic_stack_[(3) - (1)].stringVal);
}
    break;

  case 12:
/* Line 664 of lalr1.cc  */
#line 174 "whereParser.yy"
    {
#if defined(DEBUG) && DEBUG + 0 > 1
    LOGGER(ibis::gVerbose >= 0)
	<< __FILE__ << ":" << __LINE__ << " parsing -- " << *(yysemantic_stack_[(7) - (1)].stringVal) << " IN ("
	<< (yysemantic_stack_[(7) - (4)].doubleVal) << ", " << (yysemantic_stack_[(7) - (6)].doubleVal) << ")";
#endif
    std::vector<double> vals(2);
    vals[0] = (yysemantic_stack_[(7) - (4)].doubleVal);
    vals[1] = (yysemantic_stack_[(7) - (6)].doubleVal);
    (yyval.whereNode) = new ibis::qDiscreteRange((yysemantic_stack_[(7) - (1)].stringVal)->c_str(), vals);
    delete (yysemantic_stack_[(7) - (1)].stringVal);
}
    break;

  case 13:
/* Line 664 of lalr1.cc  */
#line 186 "whereParser.yy"
    {
#if defined(DEBUG) && DEBUG + 0 > 1
    LOGGER(ibis::gVerbose >= 0)
	<< __FILE__ << ":" << __LINE__ << " parsing -- " << *(yysemantic_stack_[(5) - (1)].stringVal) << " IN ("
	<< (yysemantic_stack_[(5) - (4)].doubleVal) << ")";
#endif
    (yyval.whereNode) = new ibis::qContinuousRange((yysemantic_stack_[(5) - (1)].stringVal)->c_str(), ibis::qExpr::OP_EQ, (yysemantic_stack_[(5) - (4)].doubleVal));
    delete (yysemantic_stack_[(5) - (1)].stringVal);
}
    break;

  case 14:
/* Line 664 of lalr1.cc  */
#line 195 "whereParser.yy"
    {
#if defined(DEBUG) && DEBUG + 0 > 1
    LOGGER(ibis::gVerbose >= 0)
	<< __FILE__ << ":" << __LINE__ << " parsing -- " << *(yysemantic_stack_[(3) - (1)].stringVal) << " NOT NULL";
#endif
    (yyval.whereNode) = new ibis::qContinuousRange((yysemantic_stack_[(3) - (1)].stringVal)->c_str(), ibis::qExpr::OP_UNDEFINED, 0U);
}
    break;

  case 15:
/* Line 664 of lalr1.cc  */
#line 202 "whereParser.yy"
    {
#if defined(DEBUG) && DEBUG + 0 > 1
    LOGGER(ibis::gVerbose >= 0)
	<< __FILE__ << ":" << __LINE__ << " parsing -- " << *(yysemantic_stack_[(4) - (1)].stringVal) << " NOT IN ("
	<< *(yysemantic_stack_[(4) - (4)].stringVal) << ")";
#endif
    (yyval.whereNode) = new ibis::qExpr(ibis::qExpr::LOGICAL_NOT);
    (yyval.whereNode)->setLeft(new ibis::qDiscreteRange((yysemantic_stack_[(4) - (1)].stringVal)->c_str(), (yysemantic_stack_[(4) - (4)].stringVal)->c_str()));
    delete (yysemantic_stack_[(4) - (4)].stringVal);
    delete (yysemantic_stack_[(4) - (1)].stringVal);
}
    break;

  case 16:
/* Line 664 of lalr1.cc  */
#line 213 "whereParser.yy"
    {
#if defined(DEBUG) && DEBUG + 0 > 1
    LOGGER(ibis::gVerbose >= 0)
	<< __FILE__ << ":" << __LINE__ << " parsing -- " << *(yysemantic_stack_[(8) - (1)].stringVal) << " NOT IN ("
	<< (yysemantic_stack_[(8) - (5)].doubleVal) << ", " << (yysemantic_stack_[(8) - (7)].doubleVal) << ")";
#endif
    std::vector<double> vals(2);
    vals[0] = (yysemantic_stack_[(8) - (5)].doubleVal);
    vals[1] = (yysemantic_stack_[(8) - (7)].doubleVal);
    (yyval.whereNode) = new ibis::qExpr(ibis::qExpr::LOGICAL_NOT);
    (yyval.whereNode)->setLeft(new ibis::qDiscreteRange((yysemantic_stack_[(8) - (1)].stringVal)->c_str(), vals));
    delete (yysemantic_stack_[(8) - (1)].stringVal);
}
    break;

  case 17:
/* Line 664 of lalr1.cc  */
#line 226 "whereParser.yy"
    {
#if defined(DEBUG) && DEBUG + 0 > 1
    LOGGER(ibis::gVerbose >= 0)
	<< __FILE__ << ":" << __LINE__ << " parsing -- " << *(yysemantic_stack_[(6) - (1)].stringVal) << " NOT IN ("
	<< (yysemantic_stack_[(6) - (5)].doubleVal) << ")";
#endif
    (yyval.whereNode) = new ibis::qExpr(ibis::qExpr::LOGICAL_NOT);
    (yyval.whereNode)->setLeft(new ibis::qContinuousRange((yysemantic_stack_[(6) - (1)].stringVal)->c_str(), ibis::qExpr::OP_EQ, (yysemantic_stack_[(6) - (5)].doubleVal)));
    delete (yysemantic_stack_[(6) - (1)].stringVal);
}
    break;

  case 18:
/* Line 664 of lalr1.cc  */
#line 236 "whereParser.yy"
    {
#if defined(DEBUG) && DEBUG + 0 > 1
    LOGGER(ibis::gVerbose >= 0)
	<< __FILE__ << ":" << __LINE__ << " parsing -- " << *(yysemantic_stack_[(3) - (1)].stringVal) << " IN ("
	<< *(yysemantic_stack_[(3) - (3)].stringVal) << ")";
#endif
    (yyval.whereNode) = new ibis::qAnyString((yysemantic_stack_[(3) - (1)].stringVal)->c_str(), (yysemantic_stack_[(3) - (3)].stringVal)->c_str());
    delete (yysemantic_stack_[(3) - (3)].stringVal);
    delete (yysemantic_stack_[(3) - (1)].stringVal);
}
    break;

  case 19:
/* Line 664 of lalr1.cc  */
#line 246 "whereParser.yy"
    {
#if defined(DEBUG) && DEBUG + 0 > 1
    LOGGER(ibis::gVerbose >= 0)
	<< __FILE__ << ":" << __LINE__ << " parsing -- " << *(yysemantic_stack_[(7) - (1)].stringVal) << " IN ("
	<< *(yysemantic_stack_[(7) - (4)].stringVal) << ", " << *(yysemantic_stack_[(7) - (6)].stringVal) << ")";
#endif
    std::string val;
    val = '"'; /* add quote to keep strings intact */
    val += *(yysemantic_stack_[(7) - (4)].stringVal);
    val += "\", \"";
    val += *(yysemantic_stack_[(7) - (6)].stringVal);
    val += '"';
    (yyval.whereNode) = new ibis::qAnyString((yysemantic_stack_[(7) - (1)].stringVal)->c_str(), val.c_str());
    delete (yysemantic_stack_[(7) - (6)].stringVal);
    delete (yysemantic_stack_[(7) - (4)].stringVal);
    delete (yysemantic_stack_[(7) - (1)].stringVal);
}
    break;

  case 20:
/* Line 664 of lalr1.cc  */
#line 263 "whereParser.yy"
    {
#if defined(DEBUG) && DEBUG + 0 > 1
    LOGGER(ibis::gVerbose >= 0)
	<< __FILE__ << ":" << __LINE__ << " parsing -- " << *(yysemantic_stack_[(7) - (1)].stringVal) << " IN ("
	<< *(yysemantic_stack_[(7) - (4)].stringVal) << ", " << *(yysemantic_stack_[(7) - (6)].stringVal) << ")";
#endif
    std::string val;
    val = '"'; /* add quote to keep strings intact */
    val += *(yysemantic_stack_[(7) - (4)].stringVal);
    val += "\", \"";
    val += *(yysemantic_stack_[(7) - (6)].stringVal);
    val += '"';
    (yyval.whereNode) = new ibis::qAnyString((yysemantic_stack_[(7) - (1)].stringVal)->c_str(), val.c_str());
    delete (yysemantic_stack_[(7) - (6)].stringVal);
    delete (yysemantic_stack_[(7) - (4)].stringVal);
    delete (yysemantic_stack_[(7) - (1)].stringVal);
}
    break;

  case 21:
/* Line 664 of lalr1.cc  */
#line 280 "whereParser.yy"
    {
#if defined(DEBUG) && DEBUG + 0 > 1
    LOGGER(ibis::gVerbose >= 0)
	<< __FILE__ << ":" << __LINE__ << " parsing -- " << *(yysemantic_stack_[(7) - (1)].stringVal) << " IN ("
	<< *(yysemantic_stack_[(7) - (4)].stringVal) << ", " << *(yysemantic_stack_[(7) - (6)].stringVal) << ")";
#endif
    std::string val;
    val = '"'; /* add quote to keep strings intact */
    val += *(yysemantic_stack_[(7) - (4)].stringVal);
    val += "\", \"";
    val += *(yysemantic_stack_[(7) - (6)].stringVal);
    val += '"';
    (yyval.whereNode) = new ibis::qAnyString((yysemantic_stack_[(7) - (1)].stringVal)->c_str(), val.c_str());
    delete (yysemantic_stack_[(7) - (6)].stringVal);
    delete (yysemantic_stack_[(7) - (4)].stringVal);
    delete (yysemantic_stack_[(7) - (1)].stringVal);
}
    break;

  case 22:
/* Line 664 of lalr1.cc  */
#line 297 "whereParser.yy"
    {
#if defined(DEBUG) && DEBUG + 0 > 1
    LOGGER(ibis::gVerbose >= 0)
	<< __FILE__ << ":" << __LINE__ << " parsing -- " << *(yysemantic_stack_[(7) - (1)].stringVal) << " IN ("
	<< *(yysemantic_stack_[(7) - (4)].stringVal) << ", " << *(yysemantic_stack_[(7) - (6)].stringVal) << ")";
#endif
    std::string val;
    val = '"'; /* add quote to keep strings intact */
    val += *(yysemantic_stack_[(7) - (4)].stringVal);
    val += "\", \"";
    val += *(yysemantic_stack_[(7) - (6)].stringVal);
    val += '"';
    (yyval.whereNode) = new ibis::qAnyString((yysemantic_stack_[(7) - (1)].stringVal)->c_str(), val.c_str());
    delete (yysemantic_stack_[(7) - (6)].stringVal);
    delete (yysemantic_stack_[(7) - (4)].stringVal);
    delete (yysemantic_stack_[(7) - (1)].stringVal);
}
    break;

  case 23:
/* Line 664 of lalr1.cc  */
#line 314 "whereParser.yy"
    {
#if defined(DEBUG) && DEBUG + 0 > 1
    LOGGER(ibis::gVerbose >= 0)
	<< __FILE__ << ":" << __LINE__ << " parsing -- " << *(yysemantic_stack_[(5) - (1)].stringVal) << " IN ("
	<< *(yysemantic_stack_[(5) - (4)].stringVal) << ")";
#endif
    std::string val;
    val = '"'; /* add quote to keep strings intact */
    val += *(yysemantic_stack_[(5) - (4)].stringVal);
    val += '"';
    (yyval.whereNode) = new ibis::qAnyString((yysemantic_stack_[(5) - (1)].stringVal)->c_str(), val.c_str());
    delete (yysemantic_stack_[(5) - (4)].stringVal);
    delete (yysemantic_stack_[(5) - (1)].stringVal);
}
    break;

  case 24:
/* Line 664 of lalr1.cc  */
#line 328 "whereParser.yy"
    {
#if defined(DEBUG) && DEBUG + 0 > 1
    LOGGER(ibis::gVerbose >= 0)
	<< __FILE__ << ":" << __LINE__ << " parsing -- " << *(yysemantic_stack_[(5) - (1)].stringVal) << " IN ("
	<< *(yysemantic_stack_[(5) - (4)].stringVal) << ")";
#endif
    std::string val;
    val = '"'; /* add quote to keep strings intact */
    val += *(yysemantic_stack_[(5) - (4)].stringVal);
    val += '"';
    (yyval.whereNode) = new ibis::qAnyString((yysemantic_stack_[(5) - (1)].stringVal)->c_str(), val.c_str());
    delete (yysemantic_stack_[(5) - (4)].stringVal);
    delete (yysemantic_stack_[(5) - (1)].stringVal);
}
    break;

  case 25:
/* Line 664 of lalr1.cc  */
#line 342 "whereParser.yy"
    {
#if defined(DEBUG) && DEBUG + 0 > 1
    LOGGER(ibis::gVerbose >= 0)
	<< __FILE__ << ":" << __LINE__ << " parsing -- " << *(yysemantic_stack_[(3) - (1)].stringVal) << " LIKE "
	<< *(yysemantic_stack_[(3) - (3)].stringVal);
#endif
    (yyval.whereNode) = new ibis::qLike((yysemantic_stack_[(3) - (1)].stringVal)->c_str(), (yysemantic_stack_[(3) - (3)].stringVal)->c_str());
    delete (yysemantic_stack_[(3) - (3)].stringVal);
    delete (yysemantic_stack_[(3) - (1)].stringVal);
}
    break;

  case 26:
/* Line 664 of lalr1.cc  */
#line 352 "whereParser.yy"
    {
#if defined(DEBUG) && DEBUG + 0 > 1
    LOGGER(ibis::gVerbose >= 0)
	<< __FILE__ << ":" << __LINE__ << " parsing -- " << *(yysemantic_stack_[(3) - (1)].stringVal) << " LIKE "
	<< *(yysemantic_stack_[(3) - (3)].stringVal);
#endif
    (yyval.whereNode) = new ibis::qLike((yysemantic_stack_[(3) - (1)].stringVal)->c_str(), (yysemantic_stack_[(3) - (3)].stringVal)->c_str());
    delete (yysemantic_stack_[(3) - (3)].stringVal);
    delete (yysemantic_stack_[(3) - (1)].stringVal);
}
    break;

  case 27:
/* Line 664 of lalr1.cc  */
#line 362 "whereParser.yy"
    {
#if defined(DEBUG) && DEBUG + 0 > 1
    LOGGER(ibis::gVerbose >= 0)
	<< __FILE__ << ":" << __LINE__ << " parsing -- " << *(yysemantic_stack_[(4) - (1)].stringVal) << " NOT IN ("
	<< *(yysemantic_stack_[(4) - (4)].stringVal) << ")";
#endif
    (yyval.whereNode) = new ibis::qExpr(ibis::qExpr::LOGICAL_NOT);
    (yyval.whereNode)->setLeft(new ibis::qAnyString((yysemantic_stack_[(4) - (1)].stringVal)->c_str(), (yysemantic_stack_[(4) - (4)].stringVal)->c_str()));
    delete (yysemantic_stack_[(4) - (4)].stringVal);
    delete (yysemantic_stack_[(4) - (1)].stringVal);
}
    break;

  case 28:
/* Line 664 of lalr1.cc  */
#line 373 "whereParser.yy"
    {
#if defined(DEBUG) && DEBUG + 0 > 1
    LOGGER(ibis::gVerbose >= 0)
	<< __FILE__ << ":" << __LINE__ << " parsing -- " << *(yysemantic_stack_[(8) - (1)].stringVal) << " NOT IN ("
	<< *(yysemantic_stack_[(8) - (5)].stringVal) << ", " << *(yysemantic_stack_[(8) - (7)].stringVal) << ")";
#endif
    std::string val;
    val = '"'; /* add quote to keep strings intact */
    val += *(yysemantic_stack_[(8) - (5)].stringVal);
    val += "\", \"";
    val += *(yysemantic_stack_[(8) - (7)].stringVal);
    val += '"';
    (yyval.whereNode) = new ibis::qExpr(ibis::qExpr::LOGICAL_NOT);
    (yyval.whereNode)->setLeft(new ibis::qAnyString((yysemantic_stack_[(8) - (1)].stringVal)->c_str(), val.c_str()));
    delete (yysemantic_stack_[(8) - (7)].stringVal);
    delete (yysemantic_stack_[(8) - (5)].stringVal);
    delete (yysemantic_stack_[(8) - (1)].stringVal);
}
    break;

  case 29:
/* Line 664 of lalr1.cc  */
#line 391 "whereParser.yy"
    {
#if defined(DEBUG) && DEBUG + 0 > 1
    LOGGER(ibis::gVerbose >= 0)
	<< __FILE__ << ":" << __LINE__ << " parsing -- " << *(yysemantic_stack_[(8) - (1)].stringVal) << " NOT IN ("
	<< *(yysemantic_stack_[(8) - (5)].stringVal) << ", " << *(yysemantic_stack_[(8) - (7)].stringVal) << ")";
#endif
    std::string val;
    val = '"'; /* add quote to keep strings intact */
    val += *(yysemantic_stack_[(8) - (5)].stringVal);
    val += "\", \"";
    val += *(yysemantic_stack_[(8) - (7)].stringVal);
    val += '"';
    (yyval.whereNode) = new ibis::qExpr(ibis::qExpr::LOGICAL_NOT);
    (yyval.whereNode)->setLeft(new ibis::qAnyString((yysemantic_stack_[(8) - (1)].stringVal)->c_str(), val.c_str()));
    delete (yysemantic_stack_[(8) - (7)].stringVal);
    delete (yysemantic_stack_[(8) - (5)].stringVal);
    delete (yysemantic_stack_[(8) - (1)].stringVal);
}
    break;

  case 30:
/* Line 664 of lalr1.cc  */
#line 409 "whereParser.yy"
    {
#if defined(DEBUG) && DEBUG + 0 > 1
    LOGGER(ibis::gVerbose >= 0)
	<< __FILE__ << ":" << __LINE__ << " parsing -- " << *(yysemantic_stack_[(8) - (1)].stringVal) << " NOT IN ("
	<< *(yysemantic_stack_[(8) - (5)].stringVal) << ", " << *(yysemantic_stack_[(8) - (7)].stringVal) << ")";
#endif
    std::string val;
    val = '"'; /* add quote to keep strings intact */
    val += *(yysemantic_stack_[(8) - (5)].stringVal);
    val += "\", \"";
    val += *(yysemantic_stack_[(8) - (7)].stringVal);
    val += '"';
    (yyval.whereNode) = new ibis::qExpr(ibis::qExpr::LOGICAL_NOT);
    (yyval.whereNode)->setLeft(new ibis::qAnyString((yysemantic_stack_[(8) - (1)].stringVal)->c_str(), val.c_str()));
    delete (yysemantic_stack_[(8) - (7)].stringVal);
    delete (yysemantic_stack_[(8) - (5)].stringVal);
    delete (yysemantic_stack_[(8) - (1)].stringVal);
}
    break;

  case 31:
/* Line 664 of lalr1.cc  */
#line 427 "whereParser.yy"
    {
#if defined(DEBUG) && DEBUG + 0 > 1
    LOGGER(ibis::gVerbose >= 0)
	<< __FILE__ << ":" << __LINE__ << " parsing -- " << *(yysemantic_stack_[(8) - (1)].stringVal) << " NOT IN ("
	<< *(yysemantic_stack_[(8) - (5)].stringVal) << ", " << *(yysemantic_stack_[(8) - (7)].stringVal) << ")";
#endif
    std::string val;
    val = '"'; /* add quote to keep strings intact */
    val += *(yysemantic_stack_[(8) - (5)].stringVal);
    val += "\", \"";
    val += *(yysemantic_stack_[(8) - (7)].stringVal);
    val += '"';
    (yyval.whereNode) = new ibis::qExpr(ibis::qExpr::LOGICAL_NOT);
    (yyval.whereNode)->setLeft(new ibis::qAnyString((yysemantic_stack_[(8) - (1)].stringVal)->c_str(), val.c_str()));
    delete (yysemantic_stack_[(8) - (7)].stringVal);
    delete (yysemantic_stack_[(8) - (5)].stringVal);
    delete (yysemantic_stack_[(8) - (1)].stringVal);
}
    break;

  case 32:
/* Line 664 of lalr1.cc  */
#line 445 "whereParser.yy"
    {
#if defined(DEBUG) && DEBUG + 0 > 1
    LOGGER(ibis::gVerbose >= 0)
	<< __FILE__ << ":" << __LINE__ << " parsing -- " << *(yysemantic_stack_[(6) - (1)].stringVal) << " NOT IN ("
	<< *(yysemantic_stack_[(6) - (5)].stringVal) << ")";
#endif
    std::string val;
    val = '"'; /* add quote to keep strings intact */
    val += *(yysemantic_stack_[(6) - (5)].stringVal);
    val += '"';
    (yyval.whereNode) = new ibis::qExpr(ibis::qExpr::LOGICAL_NOT);
    (yyval.whereNode)->setLeft(new ibis::qAnyString((yysemantic_stack_[(6) - (1)].stringVal)->c_str(), val.c_str()));
    delete (yysemantic_stack_[(6) - (5)].stringVal);
    delete (yysemantic_stack_[(6) - (1)].stringVal);
}
    break;

  case 33:
/* Line 664 of lalr1.cc  */
#line 460 "whereParser.yy"
    {
#if defined(DEBUG) && DEBUG + 0 > 1
    LOGGER(ibis::gVerbose >= 0)
	<< __FILE__ << ":" << __LINE__ << " parsing -- " << *(yysemantic_stack_[(6) - (1)].stringVal) << " NOT IN ("
	<< *(yysemantic_stack_[(6) - (5)].stringVal) << ")";
#endif
    std::string val;
    val = '"'; /* add quote to keep strings intact */
    val += *(yysemantic_stack_[(6) - (5)].stringVal);
    val += '"';
    (yyval.whereNode) = new ibis::qExpr(ibis::qExpr::LOGICAL_NOT);
    (yyval.whereNode)->setLeft(new ibis::qAnyString((yysemantic_stack_[(6) - (1)].stringVal)->c_str(), val.c_str()));
    delete (yysemantic_stack_[(6) - (5)].stringVal);
    delete (yysemantic_stack_[(6) - (1)].stringVal);
}
    break;

  case 34:
/* Line 664 of lalr1.cc  */
#line 475 "whereParser.yy"
    {
#if defined(DEBUG) && DEBUG + 0 > 1
    LOGGER(ibis::gVerbose >= 0)
	<< __FILE__ << ":" << __LINE__ << " parsing -- " << *(yysemantic_stack_[(3) - (1)].stringVal) << " in ("
	<< *(yysemantic_stack_[(3) - (3)].stringVal) << ")";
#endif
    (yyval.whereNode) = new ibis::qIntHod((yysemantic_stack_[(3) - (1)].stringVal)->c_str(), (yysemantic_stack_[(3) - (3)].stringVal)->c_str());
    delete (yysemantic_stack_[(3) - (3)].stringVal);
    delete (yysemantic_stack_[(3) - (1)].stringVal);
}
    break;

  case 35:
/* Line 664 of lalr1.cc  */
#line 485 "whereParser.yy"
    {
#if defined(DEBUG) && DEBUG + 0 > 1
    LOGGER(ibis::gVerbose >= 0)
	<< __FILE__ << ":" << __LINE__ << " parsing -- " << *(yysemantic_stack_[(4) - (1)].stringVal) << " not in ("
	<< *(yysemantic_stack_[(4) - (4)].stringVal) << ")";
#endif
    (yyval.whereNode) = new ibis::qExpr(ibis::qExpr::LOGICAL_NOT);
    (yyval.whereNode)->setLeft(new ibis::qIntHod((yysemantic_stack_[(4) - (1)].stringVal)->c_str(), (yysemantic_stack_[(4) - (4)].stringVal)->c_str()));
    delete (yysemantic_stack_[(4) - (4)].stringVal);
    delete (yysemantic_stack_[(4) - (1)].stringVal);
}
    break;

  case 36:
/* Line 664 of lalr1.cc  */
#line 496 "whereParser.yy"
    {
#if defined(DEBUG) && DEBUG + 0 > 1
    LOGGER(ibis::gVerbose >= 0)
	<< __FILE__ << ":" << __LINE__ << " parsing -- " << *(yysemantic_stack_[(3) - (1)].stringVal) << " in ("
	<< *(yysemantic_stack_[(3) - (3)].stringVal) << ")";
#endif
    (yyval.whereNode) = new ibis::qUIntHod((yysemantic_stack_[(3) - (1)].stringVal)->c_str(), (yysemantic_stack_[(3) - (3)].stringVal)->c_str());
    delete (yysemantic_stack_[(3) - (3)].stringVal);
    delete (yysemantic_stack_[(3) - (1)].stringVal);
}
    break;

  case 37:
/* Line 664 of lalr1.cc  */
#line 506 "whereParser.yy"
    {
#if defined(DEBUG) && DEBUG + 0 > 1
    LOGGER(ibis::gVerbose >= 0)
	<< __FILE__ << ":" << __LINE__ << " parsing -- " << *(yysemantic_stack_[(4) - (1)].stringVal) << " not in ("
	<< *(yysemantic_stack_[(4) - (4)].stringVal) << ")";
#endif
    (yyval.whereNode) = new ibis::qExpr(ibis::qExpr::LOGICAL_NOT);
    (yyval.whereNode)->setLeft(new ibis::qUIntHod((yysemantic_stack_[(4) - (1)].stringVal)->c_str(), (yysemantic_stack_[(4) - (4)].stringVal)->c_str()));
    delete (yysemantic_stack_[(4) - (4)].stringVal);
    delete (yysemantic_stack_[(4) - (1)].stringVal);
}
    break;

  case 38:
/* Line 664 of lalr1.cc  */
#line 517 "whereParser.yy"
    {
#if defined(DEBUG) && DEBUG + 0 > 1
    LOGGER(ibis::gVerbose >= 0)
	<< __FILE__ << ":" << __LINE__ << " parsing -- " << *(yysemantic_stack_[(3) - (1)].stringVal)
	<< " CONTAINS " << *(yysemantic_stack_[(3) - (3)].stringVal);
#endif
    (yyval.whereNode) = new ibis::qKeyword((yysemantic_stack_[(3) - (1)].stringVal)->c_str(), (yysemantic_stack_[(3) - (3)].stringVal)->c_str());
    delete (yysemantic_stack_[(3) - (1)].stringVal);
    delete (yysemantic_stack_[(3) - (3)].stringVal);
}
    break;

  case 39:
/* Line 664 of lalr1.cc  */
#line 527 "whereParser.yy"
    {
#if defined(DEBUG) && DEBUG + 0 > 1
    LOGGER(ibis::gVerbose >= 0)
	<< __FILE__ << ":" << __LINE__ << " parsing -- " << (yysemantic_stack_[(3) - (1)].stringVal)
	<< " CONTAINS " << *(yysemantic_stack_[(3) - (3)].stringVal);
#endif
    (yyval.whereNode) = new ibis::qKeyword((yysemantic_stack_[(3) - (1)].stringVal)->c_str(), (yysemantic_stack_[(3) - (3)].stringVal)->c_str());
    delete (yysemantic_stack_[(3) - (3)].stringVal);
    delete (yysemantic_stack_[(3) - (1)].stringVal);
}
    break;

  case 40:
/* Line 664 of lalr1.cc  */
#line 537 "whereParser.yy"
    {
#if defined(DEBUG) && DEBUG + 0 > 1
    LOGGER(ibis::gVerbose >= 0)
	<< __FILE__ << ":" << __LINE__ << " parsing -- " << *(yysemantic_stack_[(5) - (1)].stringVal)
	<< " CONTAINS " << *(yysemantic_stack_[(5) - (4)].stringVal);
#endif
    (yyval.whereNode) = new ibis::qKeyword((yysemantic_stack_[(5) - (1)].stringVal)->c_str(), (yysemantic_stack_[(5) - (4)].stringVal)->c_str());
    delete (yysemantic_stack_[(5) - (1)].stringVal);
    delete (yysemantic_stack_[(5) - (4)].stringVal);
}
    break;

  case 41:
/* Line 664 of lalr1.cc  */
#line 547 "whereParser.yy"
    {
#if defined(DEBUG) && DEBUG + 0 > 1
    LOGGER(ibis::gVerbose >= 0)
	<< __FILE__ << ":" << __LINE__ << " parsing -- " << (yysemantic_stack_[(5) - (1)].stringVal)
	<< " CONTAINS " << *(yysemantic_stack_[(5) - (4)].stringVal);
#endif
    (yyval.whereNode) = new ibis::qKeyword((yysemantic_stack_[(5) - (1)].stringVal)->c_str(), (yysemantic_stack_[(5) - (4)].stringVal)->c_str());
    delete (yysemantic_stack_[(5) - (4)].stringVal);
    delete (yysemantic_stack_[(5) - (1)].stringVal);
}
    break;

  case 42:
/* Line 664 of lalr1.cc  */
#line 557 "whereParser.yy"
    {
#if defined(DEBUG) && DEBUG + 0 > 1
    LOGGER(ibis::gVerbose >= 0)
	<< __FILE__ << ":" << __LINE__ << " parsing -- " << (yysemantic_stack_[(7) - (1)].stringVal)
	<< " CONTAINS (" << *(yysemantic_stack_[(7) - (4)].stringVal) << ", " << *(yysemantic_stack_[(7) - (6)].stringVal) << ')';
#endif
    (yyval.whereNode) = new ibis::qAllWords((yysemantic_stack_[(7) - (1)].stringVal)->c_str(), (yysemantic_stack_[(7) - (4)].stringVal)->c_str(), (yysemantic_stack_[(7) - (6)].stringVal)->c_str());
    delete (yysemantic_stack_[(7) - (6)].stringVal);
    delete (yysemantic_stack_[(7) - (4)].stringVal);
    delete (yysemantic_stack_[(7) - (1)].stringVal);
}
    break;

  case 43:
/* Line 664 of lalr1.cc  */
#line 568 "whereParser.yy"
    {
#if defined(DEBUG) && DEBUG + 0 > 1
    LOGGER(ibis::gVerbose >= 0)
	<< __FILE__ << ":" << __LINE__ << " parsing -- " << (yysemantic_stack_[(7) - (1)].stringVal)
	<< " CONTAINS (" << *(yysemantic_stack_[(7) - (4)].stringVal) << ", " << *(yysemantic_stack_[(7) - (6)].stringVal) << ')';
#endif
    (yyval.whereNode) = new ibis::qAllWords((yysemantic_stack_[(7) - (1)].stringVal)->c_str(), (yysemantic_stack_[(7) - (4)].stringVal)->c_str(), (yysemantic_stack_[(7) - (6)].stringVal)->c_str());
    delete (yysemantic_stack_[(7) - (6)].stringVal);
    delete (yysemantic_stack_[(7) - (4)].stringVal);
    delete (yysemantic_stack_[(7) - (1)].stringVal);
}
    break;

  case 44:
/* Line 664 of lalr1.cc  */
#line 579 "whereParser.yy"
    {
#if defined(DEBUG) && DEBUG + 0 > 1
    LOGGER(ibis::gVerbose >= 0)
	<< __FILE__ << ":" << __LINE__ << " parsing -- " << (yysemantic_stack_[(7) - (1)].stringVal)
	<< " CONTAINS (" << *(yysemantic_stack_[(7) - (4)].stringVal) << ", " << *(yysemantic_stack_[(7) - (6)].stringVal) << ')';
#endif
    (yyval.whereNode) = new ibis::qAllWords((yysemantic_stack_[(7) - (1)].stringVal)->c_str(), (yysemantic_stack_[(7) - (4)].stringVal)->c_str(), (yysemantic_stack_[(7) - (6)].stringVal)->c_str());
    delete (yysemantic_stack_[(7) - (6)].stringVal);
    delete (yysemantic_stack_[(7) - (4)].stringVal);
    delete (yysemantic_stack_[(7) - (1)].stringVal);
}
    break;

  case 45:
/* Line 664 of lalr1.cc  */
#line 590 "whereParser.yy"
    {
#if defined(DEBUG) && DEBUG + 0 > 1
    LOGGER(ibis::gVerbose >= 0)
	<< __FILE__ << ":" << __LINE__ << " parsing -- " << (yysemantic_stack_[(7) - (1)].stringVal)
	<< " CONTAINS (" << *(yysemantic_stack_[(7) - (4)].stringVal) << ", " << *(yysemantic_stack_[(7) - (6)].stringVal) << ')';
#endif
    (yyval.whereNode) = new ibis::qAllWords((yysemantic_stack_[(7) - (1)].stringVal)->c_str(), (yysemantic_stack_[(7) - (4)].stringVal)->c_str(), (yysemantic_stack_[(7) - (6)].stringVal)->c_str());
    delete (yysemantic_stack_[(7) - (6)].stringVal);
    delete (yysemantic_stack_[(7) - (4)].stringVal);
    delete (yysemantic_stack_[(7) - (1)].stringVal);
}
    break;

  case 46:
/* Line 664 of lalr1.cc  */
#line 601 "whereParser.yy"
    {
#if defined(DEBUG) && DEBUG + 0 > 1
    LOGGER(ibis::gVerbose >= 0)
	<< __FILE__ << ":" << __LINE__ << " parsing -- " << (yysemantic_stack_[(3) - (1)].stringVal)
	<< " CONTAINS (" << *(yysemantic_stack_[(3) - (3)].stringVal) << ')';
#endif
    (yyval.whereNode) = new ibis::qAllWords((yysemantic_stack_[(3) - (1)].stringVal)->c_str(), (yysemantic_stack_[(3) - (3)].stringVal)->c_str());
    delete (yysemantic_stack_[(3) - (3)].stringVal);
    delete (yysemantic_stack_[(3) - (1)].stringVal);
}
    break;

  case 47:
/* Line 664 of lalr1.cc  */
#line 611 "whereParser.yy"
    {
#if defined(DEBUG) && DEBUG + 0 > 1
    LOGGER(ibis::gVerbose >= 0)
	<< __FILE__ << ":" << __LINE__ << " parsing -- ANY(" << *(yysemantic_stack_[(6) - (3)].stringVal) << ") = "
	<< (yysemantic_stack_[(6) - (6)].doubleVal) << ")";
#endif
    (yyval.whereNode) = new ibis::qAnyAny((yysemantic_stack_[(6) - (3)].stringVal)->c_str(), (yysemantic_stack_[(6) - (6)].doubleVal));
    delete (yysemantic_stack_[(6) - (3)].stringVal);
}
    break;

  case 48:
/* Line 664 of lalr1.cc  */
#line 620 "whereParser.yy"
    {
#if defined(DEBUG) && DEBUG + 0 > 1
    LOGGER(ibis::gVerbose >= 0)
	<< __FILE__ << ":" << __LINE__ << " parsing -- ANY(" << *(yysemantic_stack_[(6) - (3)].stringVal) << ") = "
	<< *(yysemantic_stack_[(6) - (6)].stringVal) << ")";
#endif
    (yyval.whereNode) = new ibis::qAnyAny((yysemantic_stack_[(6) - (3)].stringVal)->c_str(), (yysemantic_stack_[(6) - (6)].stringVal)->c_str());
    delete (yysemantic_stack_[(6) - (6)].stringVal);
    delete (yysemantic_stack_[(6) - (3)].stringVal);
}
    break;

  case 49:
/* Line 664 of lalr1.cc  */
#line 630 "whereParser.yy"
    {
#if defined(DEBUG) && DEBUG + 0 > 1
    LOGGER(ibis::gVerbose >= 0)
	<< __FILE__ << ":" << __LINE__ << " parsing -- " << *(yysemantic_stack_[(3) - (1)].stringVal) << " = " << *(yysemantic_stack_[(3) - (3)].int64Val);
#endif
    (yyval.whereNode) = new ibis::qIntHod((yysemantic_stack_[(3) - (1)].stringVal)->c_str(), (yysemantic_stack_[(3) - (3)].int64Val));
    delete (yysemantic_stack_[(3) - (1)].stringVal);
}
    break;

  case 50:
/* Line 664 of lalr1.cc  */
#line 638 "whereParser.yy"
    {
#if defined(DEBUG) && DEBUG + 0 > 1
    LOGGER(ibis::gVerbose >= 0)
	<< __FILE__ << ":" << __LINE__ << " parsing -- " << *(yysemantic_stack_[(3) - (1)].stringVal) << " != " << *(yysemantic_stack_[(3) - (3)].int64Val);
#endif
    (yyval.whereNode) = new ibis::qExpr(ibis::qExpr::LOGICAL_NOT);
    (yyval.whereNode)->setLeft(new ibis::qIntHod((yysemantic_stack_[(3) - (1)].stringVal)->c_str(), (yysemantic_stack_[(3) - (3)].int64Val)));
    delete (yysemantic_stack_[(3) - (1)].stringVal);
}
    break;

  case 51:
/* Line 664 of lalr1.cc  */
#line 647 "whereParser.yy"
    {
#if defined(DEBUG) && DEBUG + 0 > 1
    LOGGER(ibis::gVerbose >= 0)
	<< __FILE__ << ":" << __LINE__ << " parsing -- " << *(yysemantic_stack_[(3) - (1)].stringVal) << " = " << *(yysemantic_stack_[(3) - (3)].uint64Val);
#endif
    (yyval.whereNode) = new ibis::qUIntHod((yysemantic_stack_[(3) - (1)].stringVal)->c_str(), (yysemantic_stack_[(3) - (3)].uint64Val));
    delete (yysemantic_stack_[(3) - (1)].stringVal);
}
    break;

  case 52:
/* Line 664 of lalr1.cc  */
#line 655 "whereParser.yy"
    {
#if defined(DEBUG) && DEBUG + 0 > 1
    LOGGER(ibis::gVerbose >= 0)
	<< __FILE__ << ":" << __LINE__ << " parsing -- " << *(yysemantic_stack_[(3) - (1)].stringVal) << " != " << *(yysemantic_stack_[(3) - (3)].uint64Val);
#endif
    (yyval.whereNode) = new ibis::qExpr(ibis::qExpr::LOGICAL_NOT);
    (yyval.whereNode)->setLeft(new ibis::qUIntHod((yysemantic_stack_[(3) - (1)].stringVal)->c_str(), (yysemantic_stack_[(3) - (3)].uint64Val)));
    delete (yysemantic_stack_[(3) - (1)].stringVal);
}
    break;

  case 53:
/* Line 664 of lalr1.cc  */
#line 664 "whereParser.yy"
    {
#if defined(DEBUG) && DEBUG + 0 > 1
    LOGGER(ibis::gVerbose >= 0)
	<< __FILE__ << ":" << __LINE__ << " parsing -- " << *(yysemantic_stack_[(3) - (3)].stringVal) << " = "
	<< *(yysemantic_stack_[(3) - (1)].stringVal);
#endif
    (yyval.whereNode) = new ibis::qString((yysemantic_stack_[(3) - (3)].stringVal)->c_str(), (yysemantic_stack_[(3) - (1)].stringVal)->c_str());
    delete (yysemantic_stack_[(3) - (3)].stringVal);
    delete (yysemantic_stack_[(3) - (1)].stringVal);
}
    break;

  case 54:
/* Line 664 of lalr1.cc  */
#line 674 "whereParser.yy"
    {
#if defined(DEBUG) && DEBUG + 0 > 1
    LOGGER(ibis::gVerbose >= 0)
	<< __FILE__ << ":" << __LINE__ << " parsing -- " << *(yysemantic_stack_[(3) - (3)].stringVal) << " = "
	<< *(yysemantic_stack_[(3) - (1)].stringVal);
#endif
    (yyval.whereNode) = new ibis::qExpr(ibis::qExpr::LOGICAL_NOT);
    (yyval.whereNode)->setLeft(new ibis::qString((yysemantic_stack_[(3) - (3)].stringVal)->c_str(), (yysemantic_stack_[(3) - (1)].stringVal)->c_str()));
    delete (yysemantic_stack_[(3) - (3)].stringVal);
    delete (yysemantic_stack_[(3) - (1)].stringVal);
}
    break;

  case 55:
/* Line 664 of lalr1.cc  */
#line 685 "whereParser.yy"
    {
#if defined(DEBUG) && DEBUG + 0 > 1
    LOGGER(ibis::gVerbose >= 0)
	<< __FILE__ << ":" << __LINE__ << " parsing -- " << *(yysemantic_stack_[(3) - (1)].stringVal) << " = "
	<< *(yysemantic_stack_[(3) - (3)].stringVal);
#endif
    (yyval.whereNode) = new ibis::qString((yysemantic_stack_[(3) - (1)].stringVal)->c_str(), (yysemantic_stack_[(3) - (3)].stringVal)->c_str());
    delete (yysemantic_stack_[(3) - (3)].stringVal);
    delete (yysemantic_stack_[(3) - (1)].stringVal);
}
    break;

  case 56:
/* Line 664 of lalr1.cc  */
#line 695 "whereParser.yy"
    {
#if defined(DEBUG) && DEBUG + 0 > 1
    LOGGER(ibis::gVerbose >= 0)
	<< __FILE__ << ":" << __LINE__ << " parsing -- " << *(yysemantic_stack_[(3) - (1)].stringVal) << " != "
	<< *(yysemantic_stack_[(3) - (3)].stringVal);
#endif
    (yyval.whereNode) = new ibis::qExpr(ibis::qExpr::LOGICAL_NOT);
    (yyval.whereNode)->setLeft(new ibis::qString((yysemantic_stack_[(3) - (1)].stringVal)->c_str(), (yysemantic_stack_[(3) - (3)].stringVal)->c_str()));
    delete (yysemantic_stack_[(3) - (3)].stringVal);
    delete (yysemantic_stack_[(3) - (1)].stringVal);
}
    break;

  case 57:
/* Line 664 of lalr1.cc  */
#line 706 "whereParser.yy"
    {
    ibis::math::term *me2 = static_cast<ibis::math::term*>((yysemantic_stack_[(3) - (3)].whereNode));
#if defined(DEBUG) && DEBUG + 0 > 1
    LOGGER(ibis::gVerbose >= 0)
	<< __FILE__ << ":" << __LINE__ << " parsing -- " << *(yysemantic_stack_[(3) - (1)].stringVal) << " = "
	<< *me2;
#endif
    if (me2->termType() == ibis::math::NUMBER) {
	(yyval.whereNode) = new ibis::qContinuousRange((yysemantic_stack_[(3) - (1)].stringVal)->c_str(), ibis::qExpr::OP_EQ, me2->eval());
	delete (yysemantic_stack_[(3) - (3)].whereNode);
    }
    else {
	ibis::math::variable *me1 = new ibis::math::variable((yysemantic_stack_[(3) - (1)].stringVal)->c_str());
	(yyval.whereNode) = new ibis::compRange(me1, ibis::qExpr::OP_EQ, me2);
    }
    delete (yysemantic_stack_[(3) - (1)].stringVal);
}
    break;

  case 58:
/* Line 664 of lalr1.cc  */
#line 723 "whereParser.yy"
    {
    ibis::math::term *me2 = static_cast<ibis::math::term*>((yysemantic_stack_[(3) - (3)].whereNode));
#if defined(DEBUG) && DEBUG + 0 > 1
    LOGGER(ibis::gVerbose >= 0)
	<< __FILE__ << ":" << __LINE__ << " parsing -- " << *(yysemantic_stack_[(3) - (1)].stringVal) << " = "
	<< *me2;
#endif
    ibis::qExpr*tmp = 0;
    if (me2->termType() == ibis::math::NUMBER) {
	tmp = new ibis::qContinuousRange((yysemantic_stack_[(3) - (1)].stringVal)->c_str(), ibis::qExpr::OP_EQ, me2->eval());
	delete (yysemantic_stack_[(3) - (3)].whereNode);
    }
    else {
	ibis::math::variable *me1 = new ibis::math::variable((yysemantic_stack_[(3) - (1)].stringVal)->c_str());
	tmp = new ibis::compRange(me1, ibis::qExpr::OP_EQ, me2);
    }
    delete (yysemantic_stack_[(3) - (1)].stringVal);
    (yyval.whereNode) = new ibis::qExpr(ibis::qExpr::LOGICAL_NOT);
    (yyval.whereNode)->setLeft(tmp);
}
    break;

  case 59:
/* Line 664 of lalr1.cc  */
#line 746 "whereParser.yy"
    {
    ibis::math::term *me2 = static_cast<ibis::math::term*>((yysemantic_stack_[(3) - (3)].whereNode));
    ibis::math::term *me1 = static_cast<ibis::math::term*>((yysemantic_stack_[(3) - (1)].whereNode));
#if defined(DEBUG) && DEBUG + 0 > 1
    LOGGER(ibis::gVerbose >= 0)
	<< __FILE__ << ":" << __LINE__ << " parsing -- " << *me1 << " = "
	<< *me2;
#endif
    (yyval.whereNode) = new ibis::compRange(me1, ibis::qExpr::OP_EQ, me2);
}
    break;

  case 60:
/* Line 664 of lalr1.cc  */
#line 756 "whereParser.yy"
    {
    ibis::math::term *me2 = static_cast<ibis::math::term*>((yysemantic_stack_[(3) - (3)].whereNode));
    ibis::math::term *me1 = static_cast<ibis::math::term*>((yysemantic_stack_[(3) - (1)].whereNode));
#if defined(DEBUG) && DEBUG + 0 > 1
    LOGGER(ibis::gVerbose >= 0)
	<< __FILE__ << ":" << __LINE__ << " parsing -- " << *me1 << " != "
	<< *me2;
#endif
    (yyval.whereNode) = new ibis::qExpr(ibis::qExpr::LOGICAL_NOT);
    (yyval.whereNode)->setLeft(new ibis::compRange(me1, ibis::qExpr::OP_EQ, me2));
}
    break;

  case 61:
/* Line 664 of lalr1.cc  */
#line 767 "whereParser.yy"
    {
    ibis::math::term *me2 = static_cast<ibis::math::term*>((yysemantic_stack_[(3) - (3)].whereNode));
    ibis::math::term *me1 = static_cast<ibis::math::term*>((yysemantic_stack_[(3) - (1)].whereNode));
#if defined(DEBUG) && DEBUG + 0 > 1
    LOGGER(ibis::gVerbose >= 0)
	<< __FILE__ << ":" << __LINE__ << " parsing -- " << *me1 << " < "
	<< *me2;
#endif
    (yyval.whereNode) = new ibis::compRange(me1, ibis::qExpr::OP_LT, me2);
}
    break;

  case 62:
/* Line 664 of lalr1.cc  */
#line 777 "whereParser.yy"
    {
    ibis::math::term *me2 = static_cast<ibis::math::term*>((yysemantic_stack_[(3) - (3)].whereNode));
    ibis::math::term *me1 = static_cast<ibis::math::term*>((yysemantic_stack_[(3) - (1)].whereNode));
#if defined(DEBUG) && DEBUG + 0 > 1
    LOGGER(ibis::gVerbose >= 0)
	<< __FILE__ << ":" << __LINE__ << " parsing -- " << *me1 << " <= "
	<< *me2;
#endif
    (yyval.whereNode) = new ibis::compRange(me1, ibis::qExpr::OP_LE, me2);
}
    break;

  case 63:
/* Line 664 of lalr1.cc  */
#line 787 "whereParser.yy"
    {
    ibis::math::term *me2 = static_cast<ibis::math::term*>((yysemantic_stack_[(3) - (3)].whereNode));
    ibis::math::term *me1 = static_cast<ibis::math::term*>((yysemantic_stack_[(3) - (1)].whereNode));
#if defined(DEBUG) && DEBUG + 0 > 1
    LOGGER(ibis::gVerbose >= 0)
	<< __FILE__ << ":" << __LINE__ << " parsing -- " << *me1 << " > "
	<< *me2;
#endif
    (yyval.whereNode) = new ibis::compRange(me1, ibis::qExpr::OP_GT, me2);
}
    break;

  case 64:
/* Line 664 of lalr1.cc  */
#line 797 "whereParser.yy"
    {
    ibis::math::term *me2 = static_cast<ibis::math::term*>((yysemantic_stack_[(3) - (3)].whereNode));
    ibis::math::term *me1 = static_cast<ibis::math::term*>((yysemantic_stack_[(3) - (1)].whereNode));
#if defined(DEBUG) && DEBUG + 0 > 1
    LOGGER(ibis::gVerbose >= 0)
	<< __FILE__ << ":" << __LINE__ << " parsing -- " << *me1 << " >= "
	<< *me2;
#endif
    (yyval.whereNode) = new ibis::compRange(me1, ibis::qExpr::OP_GE, me2);
}
    break;

  case 65:
/* Line 664 of lalr1.cc  */
#line 859 "whereParser.yy"
    {
    ibis::math::term *me3 = static_cast<ibis::math::term*>((yysemantic_stack_[(5) - (5)].whereNode));
    ibis::math::term *me2 = static_cast<ibis::math::term*>((yysemantic_stack_[(5) - (3)].whereNode));
    ibis::math::term *me1 = static_cast<ibis::math::term*>((yysemantic_stack_[(5) - (1)].whereNode));
#if defined(DEBUG) && DEBUG + 0 > 1
    LOGGER(ibis::gVerbose >= 0)
	<< __FILE__ << ":" << __LINE__ << " parsing -- " << *me1 << " < "
	<< *me2 << " < " << *me3;
#endif
    (yyval.whereNode) = new ibis::compRange(me1, ibis::qExpr::OP_LT, me2,
			     ibis::qExpr::OP_LT, me3);
}
    break;

  case 66:
/* Line 664 of lalr1.cc  */
#line 871 "whereParser.yy"
    {
    ibis::math::term *me3 = static_cast<ibis::math::term*>((yysemantic_stack_[(5) - (5)].whereNode));
    ibis::math::term *me2 = static_cast<ibis::math::term*>((yysemantic_stack_[(5) - (3)].whereNode));
    ibis::math::term *me1 = static_cast<ibis::math::term*>((yysemantic_stack_[(5) - (1)].whereNode));
#if defined(DEBUG) && DEBUG + 0 > 1
    LOGGER(ibis::gVerbose >= 0)
	<< __FILE__ << ":" << __LINE__ << " parsing -- " << *me1 << " < "
	<< *me2 << " <= " << *me3;
#endif
    (yyval.whereNode) = new ibis::compRange(me1, ibis::qExpr::OP_LT, me2,
			     ibis::qExpr::OP_LE, me3);
}
    break;

  case 67:
/* Line 664 of lalr1.cc  */
#line 883 "whereParser.yy"
    {
    ibis::math::term *me3 = static_cast<ibis::math::term*>((yysemantic_stack_[(5) - (5)].whereNode));
    ibis::math::term *me2 = static_cast<ibis::math::term*>((yysemantic_stack_[(5) - (3)].whereNode));
    ibis::math::term *me1 = static_cast<ibis::math::term*>((yysemantic_stack_[(5) - (1)].whereNode));
#if defined(DEBUG) && DEBUG + 0 > 1
    LOGGER(ibis::gVerbose >= 0)
	<< __FILE__ << ":" << __LINE__ << " parsing -- " << *me1 << " <= "
	<< *me2 << " < " << *me3;
#endif
    (yyval.whereNode) = new ibis::compRange(me1, ibis::qExpr::OP_LE, me2,
			     ibis::qExpr::OP_LT, me3);
}
    break;

  case 68:
/* Line 664 of lalr1.cc  */
#line 895 "whereParser.yy"
    {
    ibis::math::term *me3 = static_cast<ibis::math::term*>((yysemantic_stack_[(5) - (5)].whereNode));
    ibis::math::term *me2 = static_cast<ibis::math::term*>((yysemantic_stack_[(5) - (3)].whereNode));
    ibis::math::term *me1 = static_cast<ibis::math::term*>((yysemantic_stack_[(5) - (1)].whereNode));
#if defined(DEBUG) && DEBUG + 0 > 1
    LOGGER(ibis::gVerbose >= 0)
	<< __FILE__ << ":" << __LINE__ << " parsing -- " << *me1 << " <= "
	<< *me2 << " <= " << *me3;
#endif
    (yyval.whereNode) = new ibis::compRange(me1, ibis::qExpr::OP_LE, me2,
			     ibis::qExpr::OP_LE, me3);
}
    break;

  case 69:
/* Line 664 of lalr1.cc  */
#line 907 "whereParser.yy"
    {
    ibis::math::term *me3 = static_cast<ibis::math::term*>((yysemantic_stack_[(5) - (5)].whereNode));
    ibis::math::term *me2 = static_cast<ibis::math::term*>((yysemantic_stack_[(5) - (3)].whereNode));
    ibis::math::term *me1 = static_cast<ibis::math::term*>((yysemantic_stack_[(5) - (1)].whereNode));
#if defined(DEBUG) && DEBUG + 0 > 1
    LOGGER(ibis::gVerbose >= 0)
	<< __FILE__ << ":" << __LINE__ << " parsing -- " << *me1 << " > "
	<< *me2 << " > " << *me3;
#endif
    (yyval.whereNode) = new ibis::compRange(me3, ibis::qExpr::OP_LT, me2,
			     ibis::qExpr::OP_LT, me1);
}
    break;

  case 70:
/* Line 664 of lalr1.cc  */
#line 919 "whereParser.yy"
    {
    ibis::math::term *me3 = static_cast<ibis::math::term*>((yysemantic_stack_[(5) - (5)].whereNode));
    ibis::math::term *me2 = static_cast<ibis::math::term*>((yysemantic_stack_[(5) - (3)].whereNode));
    ibis::math::term *me1 = static_cast<ibis::math::term*>((yysemantic_stack_[(5) - (1)].whereNode));
#if defined(DEBUG) && DEBUG + 0 > 1
    LOGGER(ibis::gVerbose >= 0)
	<< __FILE__ << ":" << __LINE__ << " parsing -- " << *me1 << " > "
	<< *me2 << " >= " << *me3;
#endif
    (yyval.whereNode) = new ibis::compRange(me3, ibis::qExpr::OP_LE, me2,
			     ibis::qExpr::OP_LT, me1);
}
    break;

  case 71:
/* Line 664 of lalr1.cc  */
#line 931 "whereParser.yy"
    {
    ibis::math::term *me3 = static_cast<ibis::math::term*>((yysemantic_stack_[(5) - (5)].whereNode));
    ibis::math::term *me2 = static_cast<ibis::math::term*>((yysemantic_stack_[(5) - (3)].whereNode));
    ibis::math::term *me1 = static_cast<ibis::math::term*>((yysemantic_stack_[(5) - (1)].whereNode));
#if defined(DEBUG) && DEBUG + 0 > 1
    LOGGER(ibis::gVerbose >= 0)
	<< __FILE__ << ":" << __LINE__ << " parsing -- " << *me1 << " >= "
	<< *me2 << " > " << *me3;
#endif
    (yyval.whereNode) = new ibis::compRange(me3, ibis::qExpr::OP_LT, me2,
			     ibis::qExpr::OP_LE, me1);
}
    break;

  case 72:
/* Line 664 of lalr1.cc  */
#line 943 "whereParser.yy"
    {
    ibis::math::term *me3 = static_cast<ibis::math::term*>((yysemantic_stack_[(5) - (5)].whereNode));
    ibis::math::term *me2 = static_cast<ibis::math::term*>((yysemantic_stack_[(5) - (3)].whereNode));
    ibis::math::term *me1 = static_cast<ibis::math::term*>((yysemantic_stack_[(5) - (1)].whereNode));
#if defined(DEBUG) && DEBUG + 0 > 1
    LOGGER(ibis::gVerbose >= 0)
	<< __FILE__ << ":" << __LINE__ << " parsing -- " << *me1 << " >= "
	<< *me2 << " >= " << *me3;
#endif
    (yyval.whereNode) = new ibis::compRange(me3, ibis::qExpr::OP_LE, me2,
			     ibis::qExpr::OP_LE, me1);
}
    break;

  case 73:
/* Line 664 of lalr1.cc  */
#line 955 "whereParser.yy"
    {
    ibis::math::term *me3 = static_cast<ibis::math::term*>((yysemantic_stack_[(5) - (5)].whereNode));
    ibis::math::term *me2 = static_cast<ibis::math::term*>((yysemantic_stack_[(5) - (3)].whereNode));
    ibis::math::term *me1 = static_cast<ibis::math::term*>((yysemantic_stack_[(5) - (1)].whereNode));
#if defined(DEBUG) && DEBUG + 0 > 1
    LOGGER(ibis::gVerbose >= 0)
	<< __FILE__ << ":" << __LINE__ << " parsing -- " << *me1 << " BETWEEN "
	<< *me2 << " AND " << *me3;
#endif
    (yyval.whereNode) = new ibis::compRange(me2, ibis::qExpr::OP_LE, me1,
			     ibis::qExpr::OP_LE, me3);
}
    break;

  case 74:
/* Line 664 of lalr1.cc  */
#line 970 "whereParser.yy"
    {
#if defined(DEBUG) && DEBUG + 0 > 1
    LOGGER(ibis::gVerbose >= 0)
	<< __FILE__ << ":" << __LINE__ << " parsing -- " << *(yysemantic_stack_[(3) - (1)].whereNode)
	<< " + " << *(yysemantic_stack_[(3) - (3)].whereNode);
#endif
    ibis::math::bediener *opr =
	new ibis::math::bediener(ibis::math::PLUS);
    opr->setRight((yysemantic_stack_[(3) - (3)].whereNode));
    opr->setLeft((yysemantic_stack_[(3) - (1)].whereNode));
    (yyval.whereNode) = static_cast<ibis::qExpr*>(opr);
}
    break;

  case 75:
/* Line 664 of lalr1.cc  */
#line 982 "whereParser.yy"
    {
#if defined(DEBUG) && DEBUG + 0 > 1
    LOGGER(ibis::gVerbose >= 0)
	<< __FILE__ << ":" << __LINE__ << " parsing -- " << *(yysemantic_stack_[(3) - (1)].whereNode)
	<< " - " << *(yysemantic_stack_[(3) - (3)].whereNode);
#endif
    ibis::math::bediener *opr =
	new ibis::math::bediener(ibis::math::MINUS);
    opr->setRight((yysemantic_stack_[(3) - (3)].whereNode));
    opr->setLeft((yysemantic_stack_[(3) - (1)].whereNode));
    (yyval.whereNode) = static_cast<ibis::qExpr*>(opr);
}
    break;

  case 76:
/* Line 664 of lalr1.cc  */
#line 994 "whereParser.yy"
    {
#if defined(DEBUG) && DEBUG + 0 > 1
    LOGGER(ibis::gVerbose >= 0)
	<< __FILE__ << ":" << __LINE__ << " parsing -- " << *(yysemantic_stack_[(3) - (1)].whereNode)
	<< " * " << *(yysemantic_stack_[(3) - (3)].whereNode);
#endif
    ibis::math::bediener *opr =
	new ibis::math::bediener(ibis::math::MULTIPLY);
    opr->setRight((yysemantic_stack_[(3) - (3)].whereNode));
    opr->setLeft((yysemantic_stack_[(3) - (1)].whereNode));
    (yyval.whereNode) = static_cast<ibis::qExpr*>(opr);
}
    break;

  case 77:
/* Line 664 of lalr1.cc  */
#line 1006 "whereParser.yy"
    {
#if defined(DEBUG) && DEBUG + 0 > 1
    LOGGER(ibis::gVerbose >= 0)
	<< __FILE__ << ":" << __LINE__ << " parsing -- " << *(yysemantic_stack_[(3) - (1)].whereNode)
	<< " / " << *(yysemantic_stack_[(3) - (3)].whereNode);
#endif
    ibis::math::bediener *opr =
	new ibis::math::bediener(ibis::math::DIVIDE);
    opr->setRight((yysemantic_stack_[(3) - (3)].whereNode));
    opr->setLeft((yysemantic_stack_[(3) - (1)].whereNode));
    (yyval.whereNode) = static_cast<ibis::qExpr*>(opr);
}
    break;

  case 78:
/* Line 664 of lalr1.cc  */
#line 1018 "whereParser.yy"
    {
#if defined(DEBUG) && DEBUG + 0 > 1
    LOGGER(ibis::gVerbose >= 0)
	<< __FILE__ << ":" << __LINE__ << " parsing -- " << *(yysemantic_stack_[(3) - (1)].whereNode)
	<< " % " << *(yysemantic_stack_[(3) - (3)].whereNode);
#endif
    ibis::math::bediener *opr =
	new ibis::math::bediener(ibis::math::REMAINDER);
    opr->setRight((yysemantic_stack_[(3) - (3)].whereNode));
    opr->setLeft((yysemantic_stack_[(3) - (1)].whereNode));
    (yyval.whereNode) = static_cast<ibis::qExpr*>(opr);
}
    break;

  case 79:
/* Line 664 of lalr1.cc  */
#line 1030 "whereParser.yy"
    {
#if defined(DEBUG) && DEBUG + 0 > 1
    LOGGER(ibis::gVerbose >= 0)
	<< __FILE__ << ":" << __LINE__ << " parsing -- " << *(yysemantic_stack_[(3) - (1)].whereNode)
	<< " ^ " << *(yysemantic_stack_[(3) - (3)].whereNode);
#endif
    ibis::math::bediener *opr =
	new ibis::math::bediener(ibis::math::POWER);
    opr->setRight((yysemantic_stack_[(3) - (3)].whereNode));
    opr->setLeft((yysemantic_stack_[(3) - (1)].whereNode));
    (yyval.whereNode) = static_cast<ibis::qExpr*>(opr);
}
    break;

  case 80:
/* Line 664 of lalr1.cc  */
#line 1042 "whereParser.yy"
    {
#if defined(DEBUG) && DEBUG + 0 > 1
    LOGGER(ibis::gVerbose >= 0)
	<< __FILE__ << ":" << __LINE__ << " parsing -- " << *(yysemantic_stack_[(3) - (1)].whereNode)
	<< " & " << *(yysemantic_stack_[(3) - (3)].whereNode);
#endif
    ibis::math::bediener *opr =
	new ibis::math::bediener(ibis::math::BITAND);
    opr->setRight((yysemantic_stack_[(3) - (3)].whereNode));
    opr->setLeft((yysemantic_stack_[(3) - (1)].whereNode));
    (yyval.whereNode) = static_cast<ibis::qExpr*>(opr);
}
    break;

  case 81:
/* Line 664 of lalr1.cc  */
#line 1054 "whereParser.yy"
    {
#if defined(DEBUG) && DEBUG + 0 > 1
    LOGGER(ibis::gVerbose >= 0)
	<< __FILE__ << ":" << __LINE__ << " parsing -- " << *(yysemantic_stack_[(3) - (1)].whereNode)
	<< " | " << *(yysemantic_stack_[(3) - (3)].whereNode);
#endif
    ibis::math::bediener *opr =
	new ibis::math::bediener(ibis::math::BITOR);
    opr->setRight((yysemantic_stack_[(3) - (3)].whereNode));
    opr->setLeft((yysemantic_stack_[(3) - (1)].whereNode));
    (yyval.whereNode) = static_cast<ibis::qExpr*>(opr);
}
    break;

  case 82:
/* Line 664 of lalr1.cc  */
#line 1066 "whereParser.yy"
    {
#if defined(DEBUG) && DEBUG + 0 > 1
    LOGGER(ibis::gVerbose >= 0)
	<< __FILE__ << ":" << __LINE__ << " parsing -- " << *(yysemantic_stack_[(4) - (1)].stringVal) << "("
	<< *(yysemantic_stack_[(4) - (3)].whereNode) << ")";
#endif
    ibis::math::stdFunction1 *fun =
	new ibis::math::stdFunction1((yysemantic_stack_[(4) - (1)].stringVal)->c_str());
    delete (yysemantic_stack_[(4) - (1)].stringVal);
    fun->setLeft((yysemantic_stack_[(4) - (3)].whereNode));
    (yyval.whereNode) = static_cast<ibis::qExpr*>(fun);
}
    break;

  case 83:
/* Line 664 of lalr1.cc  */
#line 1078 "whereParser.yy"
    {
#if defined(DEBUG) && DEBUG + 0 > 1
    LOGGER(ibis::gVerbose >= 0)
	<< __FILE__ << ":" << __LINE__ << " parsing -- " << *(yysemantic_stack_[(6) - (1)].stringVal) << "("
	<< *(yysemantic_stack_[(6) - (3)].whereNode) << ", " << *(yysemantic_stack_[(6) - (5)].whereNode) << ")";
#endif
    ibis::math::stdFunction2 *fun =
	new ibis::math::stdFunction2((yysemantic_stack_[(6) - (1)].stringVal)->c_str());
    fun->setRight((yysemantic_stack_[(6) - (5)].whereNode));
    fun->setLeft((yysemantic_stack_[(6) - (3)].whereNode));
    (yyval.whereNode) = static_cast<ibis::qExpr*>(fun);
    delete (yysemantic_stack_[(6) - (1)].stringVal);
}
    break;

  case 84:
/* Line 664 of lalr1.cc  */
#line 1091 "whereParser.yy"
    {
#if defined(DEBUG) && DEBUG + 0 > 1
    LOGGER(ibis::gVerbose >= 0)
	<< __FILE__ << ":" << __LINE__ << " parsing -- - " << *(yysemantic_stack_[(2) - (2)].whereNode);
#endif
    ibis::math::bediener *opr =
	new ibis::math::bediener(ibis::math::NEGATE);
    opr->setRight((yysemantic_stack_[(2) - (2)].whereNode));
    (yyval.whereNode) = static_cast<ibis::qExpr*>(opr);
}
    break;

  case 85:
/* Line 664 of lalr1.cc  */
#line 1101 "whereParser.yy"
    {
    (yyval.whereNode) = (yysemantic_stack_[(2) - (2)].whereNode);
}
    break;

  case 86:
/* Line 664 of lalr1.cc  */
#line 1104 "whereParser.yy"
    {
    (yyval.whereNode) = (yysemantic_stack_[(3) - (2)].whereNode);
}
    break;

  case 87:
/* Line 664 of lalr1.cc  */
#line 1107 "whereParser.yy"
    {
#if defined(DEBUG) && DEBUG + 0 > 1
    LOGGER(ibis::gVerbose >= 0)
	<< __FILE__ << ":" << __LINE__ << " got a variable name " << *(yysemantic_stack_[(1) - (1)].stringVal);
#endif
    ibis::math::variable *var =
	new ibis::math::variable((yysemantic_stack_[(1) - (1)].stringVal)->c_str());
    (yyval.whereNode) = static_cast<ibis::qExpr*>(var);
    delete (yysemantic_stack_[(1) - (1)].stringVal);
}
    break;

  case 88:
/* Line 664 of lalr1.cc  */
#line 1117 "whereParser.yy"
    {
#if defined(DEBUG) && DEBUG + 0 > 1
    LOGGER(ibis::gVerbose >= 0)
	<< __FILE__ << ":" << __LINE__ << " got a number " << (yysemantic_stack_[(1) - (1)].doubleVal);
#endif
    ibis::math::number *num = new ibis::math::number((yysemantic_stack_[(1) - (1)].doubleVal));
    (yyval.whereNode) = static_cast<ibis::qExpr*>(num);
}
    break;

  case 89:
/* Line 664 of lalr1.cc  */
#line 1127 "whereParser.yy"
    { /* pass qexpr to the driver */
    driver.expr_ = (yysemantic_stack_[(2) - (1)].whereNode);
}
    break;

  case 90:
/* Line 664 of lalr1.cc  */
#line 1130 "whereParser.yy"
    { /* pass qexpr to the driver */
    driver.expr_ = (yysemantic_stack_[(2) - (1)].whereNode);
}
    break;


/* Line 664 of lalr1.cc  */
#line 1946 "whereParser.cc"
      default:
        break;
      }

    /* User semantic actions sometimes alter yychar, and that requires
       that yytoken be updated with the new translation.  We take the
       approach of translating immediately before every use of yytoken.
       One alternative is translating here after every semantic action,
       but that translation would be missed if the semantic action
       invokes YYABORT, YYACCEPT, or YYERROR immediately after altering
       yychar.  In the case of YYABORT or YYACCEPT, an incorrect
       destructor might then be invoked immediately.  In the case of
       YYERROR, subsequent parser actions might lead to an incorrect
       destructor call or verbose syntax error message before the
       lookahead is translated.  */
    YY_SYMBOL_PRINT ("-> $$ =", yyr1_[yyn], &yyval, &yyloc);

    yypop_ (yylen);
    yylen = 0;
    YY_STACK_PRINT ();

    yysemantic_stack_.push (yyval);
    yylocation_stack_.push (yyloc);

    /* Shift the result of the reduction.  */
    yyn = yyr1_[yyn];
    yystate = yypgoto_[yyn - yyntokens_] + yystate_stack_[0];
    if (0 <= yystate && yystate <= yylast_
	&& yycheck_[yystate] == yystate_stack_[0])
      yystate = yytable_[yystate];
    else
      yystate = yydefgoto_[yyn - yyntokens_];
    goto yynewstate;

  /*------------------------------------.
  | yyerrlab -- here on detecting error |
  `------------------------------------*/
  yyerrlab:
    /* Make sure we have latest lookahead translation.  See comments at
       user semantic actions for why this is necessary.  */
    yytoken = yytranslate_ (yychar);

    /* If not already recovering from an error, report this error.  */
    if (!yyerrstatus_)
      {
	++yynerrs_;
	if (yychar == yyempty_)
	  yytoken = yyempty_;
	error (yylloc, yysyntax_error_ (yystate, yytoken));
      }

    yyerror_range[1] = yylloc;
    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */
        if (yychar <= yyeof_)
          {
            /* Return failure if at end of input.  */
            if (yychar == yyeof_)
              YYABORT;
          }
        else
          {
            yydestruct_ ("Error: discarding", yytoken, &yylval, &yylloc);
            yychar = yyempty_;
          }
      }

    /* Else will try to reuse lookahead token after shifting the error
       token.  */
    goto yyerrlab1;


  /*---------------------------------------------------.
  | yyerrorlab -- error raised explicitly by YYERROR.  |
  `---------------------------------------------------*/
  yyerrorlab:

    /* Pacify compilers like GCC when the user code never invokes
       YYERROR and the label yyerrorlab therefore never appears in user
       code.  */
    if (false)
      goto yyerrorlab;

    yyerror_range[1] = yylocation_stack_[yylen - 1];
    /* Do not reclaim the symbols of the rule which action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    yystate = yystate_stack_[0];
    goto yyerrlab1;

  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;	/* Each real token shifted decrements this.  */

    for (;;)
      {
	yyn = yypact_[yystate];
	if (!yy_pact_value_is_default_ (yyn))
	{
	  yyn += yyterror_;
	  if (0 <= yyn && yyn <= yylast_ && yycheck_[yyn] == yyterror_)
	    {
	      yyn = yytable_[yyn];
	      if (0 < yyn)
		break;
	    }
	}

	/* Pop the current state because it cannot handle the error token.  */
	if (yystate_stack_.height () == 1)
	  YYABORT;

	yyerror_range[1] = yylocation_stack_[0];
	yydestruct_ ("Error: popping",
		     yystos_[yystate],
		     &yysemantic_stack_[0], &yylocation_stack_[0]);
	yypop_ ();
	yystate = yystate_stack_[0];
	YY_STACK_PRINT ();
      }

    yyerror_range[2] = yylloc;
    // Using YYLLOC is tempting, but would change the location of
    // the lookahead.  YYLOC is available though.
    YYLLOC_DEFAULT (yyloc, yyerror_range, 2);
    yysemantic_stack_.push (yylval);
    yylocation_stack_.push (yyloc);

    /* Shift the error token.  */
    YY_SYMBOL_PRINT ("Shifting", yystos_[yyn],
		     &yysemantic_stack_[0], &yylocation_stack_[0]);

    yystate = yyn;
    goto yynewstate;

    /* Accept.  */
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;

    /* Abort.  */
  yyabortlab:
    yyresult = 1;
    goto yyreturn;

  yyreturn:
    if (yychar != yyempty_)
      {
        /* Make sure we have latest lookahead translation.  See comments
           at user semantic actions for why this is necessary.  */
        yytoken = yytranslate_ (yychar);
        yydestruct_ ("Cleanup: discarding lookahead", yytoken, &yylval,
                     &yylloc);
      }

    /* Do not reclaim the symbols of the rule which action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    while (1 < yystate_stack_.height ())
      {
        yydestruct_ ("Cleanup: popping",
                     yystos_[yystate_stack_[0]],
                     &yysemantic_stack_[0],
                     &yylocation_stack_[0]);
        yypop_ ();
      }

    return yyresult;
    }
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack"
                 << std::endl;
        // Do not try to display the values of the reclaimed symbols,
        // as their printer might throw an exception.
        if (yychar != yyempty_)
          {
            /* Make sure we have latest lookahead translation.  See
               comments at user semantic actions for why this is
               necessary.  */
            yytoken = yytranslate_ (yychar);
            yydestruct_ (YY_NULL, yytoken, &yylval, &yylloc);
          }

        while (1 < yystate_stack_.height ())
          {
            yydestruct_ (YY_NULL,
                         yystos_[yystate_stack_[0]],
                         &yysemantic_stack_[0],
                         &yylocation_stack_[0]);
            yypop_ ();
          }
        throw;
      }
  }

  // Generate an error message.
  std::string
  whereParser::yysyntax_error_ (int yystate, int yytoken)
  {
    std::string yyres;
    // Number of reported tokens (one for the "unexpected", one per
    // "expected").
    size_t yycount = 0;
    // Its maximum.
    enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
    // Arguments of yyformat.
    char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];

    /* There are many possibilities here to consider:
       - If this state is a consistent state with a default action, then
         the only way this function was invoked is if the default action
         is an error action.  In that case, don't check for expected
         tokens because there are none.
       - The only way there can be no lookahead present (in yytoken) is
         if this state is a consistent state with a default action.
         Thus, detecting the absence of a lookahead is sufficient to
         determine that there is no unexpected or expected token to
         report.  In that case, just report a simple "syntax error".
       - Don't assume there isn't a lookahead just because this state is
         a consistent state with a default action.  There might have
         been a previous inconsistent state, consistent state with a
         non-default action, or user semantic action that manipulated
         yychar.
       - Of course, the expected token list depends on states to have
         correct lookahead information, and it depends on the parser not
         to perform extra reductions after fetching a lookahead from the
         scanner and before detecting a syntax error.  Thus, state
         merging (from LALR or IELR) and default reductions corrupt the
         expected token list.  However, the list is correct for
         canonical LR with one exception: it will still contain any
         token that will not be accepted due to an error action in a
         later state.
    */
    if (yytoken != yyempty_)
      {
        yyarg[yycount++] = yytname_[yytoken];
        int yyn = yypact_[yystate];
        if (!yy_pact_value_is_default_ (yyn))
          {
            /* Start YYX at -YYN if negative to avoid negative indexes in
               YYCHECK.  In other words, skip the first -YYN actions for
               this state because they are default actions.  */
            int yyxbegin = yyn < 0 ? -yyn : 0;
            /* Stay within bounds of both yycheck and yytname.  */
            int yychecklim = yylast_ - yyn + 1;
            int yyxend = yychecklim < yyntokens_ ? yychecklim : yyntokens_;
            for (int yyx = yyxbegin; yyx < yyxend; ++yyx)
              if (yycheck_[yyx + yyn] == yyx && yyx != yyterror_
                  && !yy_table_value_is_error_ (yytable_[yyx + yyn]))
                {
                  if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                    {
                      yycount = 1;
                      break;
                    }
                  else
                    yyarg[yycount++] = yytname_[yyx];
                }
          }
      }

    char const* yyformat = YY_NULL;
    switch (yycount)
      {
#define YYCASE_(N, S)                         \
        case N:                               \
          yyformat = S;                       \
        break
        YYCASE_(0, YY_("syntax error"));
        YYCASE_(1, YY_("syntax error, unexpected %s"));
        YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
        YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
        YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
        YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
      }

    // Argument number.
    size_t yyi = 0;
    for (char const* yyp = yyformat; *yyp; ++yyp)
      if (yyp[0] == '%' && yyp[1] == 's' && yyi < yycount)
        {
          yyres += yytnamerr_ (yyarg[yyi++]);
          ++yyp;
        }
      else
        yyres += *yyp;
    return yyres;
  }


  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
  const signed char whereParser::yypact_ninf_ = -35;
  const short int
  whereParser::yypact_[] =
  {
        67,    67,   -34,   -20,   -20,   -35,    13,     2,    67,    14,
     -35,   -35,   -35,   115,    16,   -35,   -12,    27,   -20,   -35,
     -35,    50,   222,   234,    71,    64,   129,   -20,    19,    37,
      -5,    53,   -35,    67,    67,    67,    67,   -35,   -20,   -20,
     -20,   -20,   -20,   -20,   -20,   -20,   -20,   -20,   -20,   -20,
     -20,   -20,   -20,   -35,    15,   187,   -35,   197,   -35,   -35,
     -35,   253,   -35,   -35,   -35,   253,   -35,   -35,   -35,   232,
     -35,   -35,   -35,   -35,    36,   -35,   -35,   166,   -35,   -35,
     -35,   -35,   -35,   -35,   235,    21,   124,   155,   147,   177,
     253,   253,   216,   260,   133,   264,   264,    54,    54,    54,
      54,    47,   -35,   -35,   -35,   -35,    58,    87,    93,   156,
     184,   214,   -35,   -20,   -20,   -20,   -20,   -20,   -20,   -20,
     -20,   -20,   -20,    57,    59,   266,   268,   270,   -35,   233,
     -35,   259,   -35,    78,   -35,   261,   -35,   263,   195,   253,
     253,   253,   253,   253,   253,   253,   253,   253,   -35,   -35,
     -35,    98,   -35,   265,   -35,   267,    62,    95,   104,   114,
     125,   127,   145,   186,   191,   -35,   194,   209,   220,   254,
     272,   -35,   -35,   -35,   -35,   -35,   -35,   -35,   -35,   -35,
     -35,   -35,   -35,   -35,   -35
  };

  /* YYDEFACT[S] -- default reduction number in state S.  Performed when
     YYTABLE doesn't specify something else to do.  Zero means the
     default is an error.  */
  const unsigned char
  whereParser::yydefact_[] =
  {
         0,     0,     0,     0,     0,    88,    87,     0,     0,     0,
       8,     9,    10,     0,     0,     6,     0,    87,     0,    85,
      84,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    89,     0,     0,     0,     0,    90,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     1,     0,     0,    14,     0,    49,    51,
      55,    57,    50,    52,    56,    58,    38,    46,    39,     0,
      34,    36,    11,    18,     0,    25,    26,     0,    53,    54,
       7,    86,     4,     5,     2,     3,    62,    64,    61,    63,
      59,    60,     0,    81,    80,    74,    75,    76,    77,    78,
      79,     0,    35,    37,    15,    27,     0,     0,     0,     0,
       0,     0,    82,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    40,     0,
      41,     0,    13,     0,    23,     0,    24,     0,     0,    68,
      67,    72,    71,    66,    65,    70,    69,    73,    47,    48,
      17,     0,    32,     0,    33,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    83,     0,     0,     0,     0,
       0,    45,    44,    43,    42,    12,    19,    21,    20,    22,
      16,    28,    30,    29,    31
  };

  /* YYPGOTO[NTERM-NUM].  */
  const signed char
  whereParser::yypgoto_[] =
  {
       -35,    49,   -35,   -35,   -35,    -3,   -35
  };

  /* YYDEFGOTO[NTERM-NUM].  */
  const signed char
  whereParser::yydefgoto_[] =
  {
        -1,     9,    10,    11,    12,    13,    14
  };

  /* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule which
     number is the opposite.  If YYTABLE_NINF_, syntax error.  */
  const signed char whereParser::yytable_ninf_ = -1;
  const unsigned char
  whereParser::yytable_[] =
  {
        19,    20,     3,     4,    16,    31,    33,    34,    35,    36,
       5,    28,    29,    17,    32,    55,    53,    21,    18,    61,
      65,    54,    22,    23,    77,    33,    34,    35,    36,    24,
      25,    26,    33,    34,    80,    86,    87,    88,    89,    90,
      91,    92,    93,    94,    95,    96,    97,    98,    99,   100,
      15,    27,    78,    56,   101,    37,   123,    30,    38,    39,
      40,    41,    42,    43,   124,    27,   109,    57,    44,   110,
      79,     1,   111,    45,    46,    47,    48,    49,    50,    51,
      52,    52,    82,    83,    84,    85,     2,   148,   125,     3,
       4,   126,    81,   149,   127,    70,    71,     5,    72,    73,
       6,   171,    74,     7,    66,     8,    67,    68,   160,    69,
     138,   139,   140,   141,   142,   143,   144,   145,   146,   147,
      38,    39,    40,    41,    42,    43,   128,   129,   166,   114,
      44,   115,   130,   131,   172,    45,    46,    47,    48,    49,
      50,    51,    52,   173,    45,    46,    47,    48,    49,    50,
      51,    52,   118,   174,   119,    47,    48,    49,    50,    51,
      52,   116,    75,   117,   175,    76,   176,    45,    46,    47,
      48,    49,    50,    51,    52,    45,    46,    47,    48,    49,
      50,    51,    52,   120,   177,   121,    45,    46,    47,    48,
      49,    50,    51,    52,     0,   132,   133,    45,    46,    47,
      48,    49,    50,    51,    52,   112,   113,    45,    46,    47,
      48,    49,    50,    51,    52,    45,    46,    47,    48,    49,
      50,    51,    52,   134,   135,   178,    81,   122,   102,   103,
     179,   104,   105,   180,   165,   106,    45,    46,    47,    48,
      49,    50,    51,    52,     3,     4,    33,    34,   181,    36,
      58,    59,     5,   136,   137,    17,     3,     4,    60,   182,
      18,     0,    62,    63,     5,   107,   156,    17,   108,   157,
      64,     0,    18,    45,    46,    47,    48,    49,    50,    51,
      52,    46,    47,    48,    49,    50,    51,    52,    49,    50,
      51,    52,   158,   183,   161,   159,   163,   162,   167,   164,
     169,   168,     0,   170,     0,   150,   151,   152,   153,   154,
     155,   184
  };

  /* YYCHECK.  */
  const signed char
  whereParser::yycheck_[] =
  {
         3,     4,    22,    23,    38,     8,    11,    12,    13,    14,
      30,     9,    10,    33,     0,    18,     0,     4,    38,    22,
      23,    33,     9,    10,    27,    11,    12,    13,    14,    16,
      17,    18,    11,    12,    39,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    52,
       1,    38,    33,     3,    39,    41,     9,     8,     5,     6,
       7,     8,     9,    10,    17,    38,    30,    17,    15,    33,
      33,     4,    36,    20,    21,    22,    23,    24,    25,    26,
      27,    27,    33,    34,    35,    36,    19,    30,    30,    22,
      23,    33,    39,    34,    36,    31,    32,    30,    34,    35,
      33,    39,    38,    36,    33,    38,    35,    36,    30,    38,
     113,   114,   115,   116,   117,   118,   119,   120,   121,   122,
       5,     6,     7,     8,     9,    10,    39,    40,    30,     5,
      15,     7,    39,    40,    39,    20,    21,    22,    23,    24,
      25,    26,    27,    39,    20,    21,    22,    23,    24,    25,
      26,    27,     5,    39,     7,    22,    23,    24,    25,    26,
      27,     6,    33,     8,    39,    36,    39,    20,    21,    22,
      23,    24,    25,    26,    27,    20,    21,    22,    23,    24,
      25,    26,    27,     6,    39,     8,    20,    21,    22,    23,
      24,    25,    26,    27,    -1,    39,    40,    20,    21,    22,
      23,    24,    25,    26,    27,    39,    40,    20,    21,    22,
      23,    24,    25,    26,    27,    20,    21,    22,    23,    24,
      25,    26,    27,    39,    40,    39,    39,    11,    31,    32,
      39,    34,    35,    39,    39,    38,    20,    21,    22,    23,
      24,    25,    26,    27,    22,    23,    11,    12,    39,    14,
      28,    29,    30,    39,    40,    33,    22,    23,    36,    39,
      38,    -1,    28,    29,    30,    33,    33,    33,    36,    36,
      36,    -1,    38,    20,    21,    22,    23,    24,    25,    26,
      27,    21,    22,    23,    24,    25,    26,    27,    24,    25,
      26,    27,    33,    39,    33,    36,    33,    36,    33,    36,
      33,    36,    -1,    36,    -1,    39,    40,    39,    40,    39,
      40,    39
  };

  /* STOS_[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
  const unsigned char
  whereParser::yystos_[] =
  {
         0,     4,    19,    22,    23,    30,    33,    36,    38,    43,
      44,    45,    46,    47,    48,    43,    38,    33,    38,    47,
      47,     4,     9,    10,    16,    17,    18,    38,     9,    10,
      43,    47,     0,    11,    12,    13,    14,    41,     5,     6,
       7,     8,     9,    10,    15,    20,    21,    22,    23,    24,
      25,    26,    27,     0,    33,    47,     3,    17,    28,    29,
      36,    47,    28,    29,    36,    47,    33,    35,    36,    38,
      31,    32,    34,    35,    38,    33,    36,    47,    33,    33,
      39,    39,    43,    43,    43,    43,    47,    47,    47,    47,
      47,    47,    47,    47,    47,    47,    47,    47,    47,    47,
      47,    39,    31,    32,    34,    35,    38,    33,    36,    30,
      33,    36,    39,    40,     5,     7,     6,     8,     5,     7,
       6,     8,    11,     9,    17,    30,    33,    36,    39,    40,
      39,    40,    39,    40,    39,    40,    39,    40,    47,    47,
      47,    47,    47,    47,    47,    47,    47,    47,    30,    34,
      39,    40,    39,    40,    39,    40,    33,    36,    33,    36,
      30,    33,    36,    33,    36,    39,    30,    33,    36,    33,
      36,    39,    39,    39,    39,    39,    39,    39,    39,    39,
      39,    39,    39,    39,    39
  };

#if YYDEBUG
  /* TOKEN_NUMBER_[YYLEX-NUM] -- Internal symbol number corresponding
     to YYLEX-NUM.  */
  const unsigned short int
  whereParser::yytoken_number_[] =
  {
         0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,    40,    41,
      44,    59
  };
#endif

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
  const unsigned char
  whereParser::yyr1_[] =
  {
         0,    42,    43,    43,    43,    43,    43,    43,    43,    43,
      43,    44,    44,    44,    44,    44,    44,    44,    44,    44,
      44,    44,    44,    44,    44,    44,    44,    44,    44,    44,
      44,    44,    44,    44,    44,    44,    44,    44,    44,    44,
      44,    44,    44,    44,    44,    44,    44,    44,    44,    44,
      44,    44,    44,    44,    44,    44,    44,    44,    44,    45,
      45,    45,    45,    45,    45,    46,    46,    46,    46,    46,
      46,    46,    46,    46,    47,    47,    47,    47,    47,    47,
      47,    47,    47,    47,    47,    47,    47,    47,    47,    48,
      48
  };

  /* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
  const unsigned char
  whereParser::yyr2_[] =
  {
         0,     2,     3,     3,     3,     3,     2,     3,     1,     1,
       1,     3,     7,     5,     3,     4,     8,     6,     3,     7,
       7,     7,     7,     5,     5,     3,     3,     4,     8,     8,
       8,     8,     6,     6,     3,     4,     3,     4,     3,     3,
       5,     5,     7,     7,     7,     7,     3,     6,     6,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     5,     5,     5,     5,     5,
       5,     5,     5,     5,     3,     3,     3,     3,     3,     3,
       3,     3,     4,     6,     2,     2,     3,     1,     1,     2,
       2
  };


  /* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
     First, the terminals, then, starting at \a yyntokens_, nonterminals.  */
  const char*
  const whereParser::yytname_[] =
  {
    "\"end of input\"", "error", "$undefined", "\"null\"", "\"not\"",
  "\"<=\"", "\">=\"", "\"<\"", "\">\"", "\"==\"", "\"!=\"", "\"and\"",
  "\"&!\"", "\"or\"", "\"xor\"", "\"between\"", "\"contains\"", "\"in\"",
  "\"like\"", "\"any\"", "\"|\"", "\"&\"", "\"+\"", "\"-\"", "\"*\"",
  "\"/\"", "\"%\"", "\"**\"", "\"integer value\"",
  "\"unsigned integer value\"", "\"floating-point number\"",
  "\"signed integer sequence\"", "\"unsigned integer sequence\"",
  "\"name string\"", "\"number sequence\"", "\"string sequence\"",
  "\"string literal\"", "CONSTAINSOP", "'('", "')'", "','", "';'",
  "$accept", "qexpr", "simpleRange", "compRange2", "compRange3",
  "mathExpr", "START", YY_NULL
  };

#if YYDEBUG
  /* YYRHS -- A `-1'-separated list of the rules' RHS.  */
  const whereParser::rhs_number_type
  whereParser::yyrhs_[] =
  {
        48,     0,    -1,    43,    13,    43,    -1,    43,    14,    43,
      -1,    43,    11,    43,    -1,    43,    12,    43,    -1,     4,
      43,    -1,    38,    43,    39,    -1,    44,    -1,    45,    -1,
      46,    -1,    33,    17,    34,    -1,    33,    17,    38,    30,
      40,    30,    39,    -1,    33,    17,    38,    30,    39,    -1,
      33,     4,     3,    -1,    33,     4,    17,    34,    -1,    33,
       4,    17,    38,    30,    40,    30,    39,    -1,    33,     4,
      17,    38,    30,    39,    -1,    33,    17,    35,    -1,    33,
      17,    38,    33,    40,    33,    39,    -1,    33,    17,    38,
      36,    40,    33,    39,    -1,    33,    17,    38,    33,    40,
      36,    39,    -1,    33,    17,    38,    36,    40,    36,    39,
      -1,    33,    17,    38,    33,    39,    -1,    33,    17,    38,
      36,    39,    -1,    33,    18,    33,    -1,    33,    18,    36,
      -1,    33,     4,    17,    35,    -1,    33,     4,    17,    38,
      33,    40,    33,    39,    -1,    33,     4,    17,    38,    36,
      40,    33,    39,    -1,    33,     4,    17,    38,    33,    40,
      36,    39,    -1,    33,     4,    17,    38,    36,    40,    36,
      39,    -1,    33,     4,    17,    38,    33,    39,    -1,    33,
       4,    17,    38,    36,    39,    -1,    33,    17,    31,    -1,
      33,     4,    17,    31,    -1,    33,    17,    32,    -1,    33,
       4,    17,    32,    -1,    33,    16,    33,    -1,    33,    16,
      36,    -1,    33,    16,    38,    33,    39,    -1,    33,    16,
      38,    36,    39,    -1,    33,    16,    38,    36,    40,    36,
      39,    -1,    33,    16,    38,    36,    40,    33,    39,    -1,
      33,    16,    38,    33,    40,    36,    39,    -1,    33,    16,
      38,    33,    40,    33,    39,    -1,    33,    16,    35,    -1,
      19,    38,    33,    39,     9,    30,    -1,    19,    38,    33,
      39,    17,    34,    -1,    33,     9,    28,    -1,    33,    10,
      28,    -1,    33,     9,    29,    -1,    33,    10,    29,    -1,
      36,     9,    33,    -1,    36,    10,    33,    -1,    33,     9,
      36,    -1,    33,    10,    36,    -1,    33,     9,    47,    -1,
      33,    10,    47,    -1,    47,     9,    47,    -1,    47,    10,
      47,    -1,    47,     7,    47,    -1,    47,     5,    47,    -1,
      47,     8,    47,    -1,    47,     6,    47,    -1,    47,     7,
      47,     7,    47,    -1,    47,     7,    47,     5,    47,    -1,
      47,     5,    47,     7,    47,    -1,    47,     5,    47,     5,
      47,    -1,    47,     8,    47,     8,    47,    -1,    47,     8,
      47,     6,    47,    -1,    47,     6,    47,     8,    47,    -1,
      47,     6,    47,     6,    47,    -1,    47,    15,    47,    11,
      47,    -1,    47,    22,    47,    -1,    47,    23,    47,    -1,
      47,    24,    47,    -1,    47,    25,    47,    -1,    47,    26,
      47,    -1,    47,    27,    47,    -1,    47,    21,    47,    -1,
      47,    20,    47,    -1,    33,    38,    47,    39,    -1,    33,
      38,    47,    40,    47,    39,    -1,    23,    47,    -1,    22,
      47,    -1,    38,    47,    39,    -1,    33,    -1,    30,    -1,
      43,     0,    -1,    43,    41,    -1
  };

  /* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
     YYRHS.  */
  const unsigned short int
  whereParser::yyprhs_[] =
  {
         0,     0,     3,     7,    11,    15,    19,    22,    26,    28,
      30,    32,    36,    44,    50,    54,    59,    68,    75,    79,
      87,    95,   103,   111,   117,   123,   127,   131,   136,   145,
     154,   163,   172,   179,   186,   190,   195,   199,   204,   208,
     212,   218,   224,   232,   240,   248,   256,   260,   267,   274,
     278,   282,   286,   290,   294,   298,   302,   306,   310,   314,
     318,   322,   326,   330,   334,   338,   344,   350,   356,   362,
     368,   374,   380,   386,   392,   396,   400,   404,   408,   412,
     416,   420,   424,   429,   436,   439,   442,   446,   448,   450,
     453
  };

  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
  const unsigned short int
  whereParser::yyrline_[] =
  {
         0,   107,   107,   117,   127,   137,   147,   155,   158,   159,
     160,   164,   174,   186,   195,   202,   213,   226,   236,   246,
     263,   280,   297,   314,   328,   342,   352,   362,   373,   391,
     409,   427,   445,   460,   475,   485,   496,   506,   517,   527,
     537,   547,   557,   568,   579,   590,   601,   611,   620,   630,
     638,   647,   655,   664,   674,   685,   695,   706,   723,   746,
     756,   767,   777,   787,   797,   859,   871,   883,   895,   907,
     919,   931,   943,   955,   970,   982,   994,  1006,  1018,  1030,
    1042,  1054,  1066,  1078,  1091,  1101,  1104,  1107,  1117,  1127,
    1130
  };

  // Print the state stack on the debug stream.
  void
  whereParser::yystack_print_ ()
  {
    *yycdebug_ << "Stack now";
    for (state_stack_type::const_iterator i = yystate_stack_.begin ();
	 i != yystate_stack_.end (); ++i)
      *yycdebug_ << ' ' << *i;
    *yycdebug_ << std::endl;
  }

  // Report on the debug stream that the rule \a yyrule is going to be reduced.
  void
  whereParser::yy_reduce_print_ (int yyrule)
  {
    unsigned int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    /* Print the symbols being reduced, and their result.  */
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
	       << " (line " << yylno << "):" << std::endl;
    /* The symbols being reduced.  */
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
		       yyrhs_[yyprhs_[yyrule] + yyi],
		       &(yysemantic_stack_[(yynrhs) - (yyi + 1)]),
		       &(yylocation_stack_[(yynrhs) - (yyi + 1)]));
  }
#endif // YYDEBUG

  /* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
  whereParser::token_number_type
  whereParser::yytranslate_ (int t)
  {
    static
    const token_number_type
    translate_table[] =
    {
           0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      38,    39,     2,     2,    40,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    41,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37
    };
    if ((unsigned int) t <= yyuser_token_number_max_)
      return translate_table[t];
    else
      return yyundef_token_;
  }

  const int whereParser::yyeof_ = 0;
  const int whereParser::yylast_ = 311;
  const int whereParser::yynnts_ = 7;
  const int whereParser::yyempty_ = -2;
  const int whereParser::yyfinal_ = 53;
  const int whereParser::yyterror_ = 1;
  const int whereParser::yyerrcode_ = 256;
  const int whereParser::yyntokens_ = 42;

  const unsigned int whereParser::yyuser_token_number_max_ = 292;
  const whereParser::token_number_type whereParser::yyundef_token_ = 2;


} // ibis
/* Line 1135 of lalr1.cc  */
#line 2657 "whereParser.cc"
/* Line 1136 of lalr1.cc  */
#line 1135 "whereParser.yy"

void ibis::whereParser::error(const ibis::whereParser::location_type& l,
			      const std::string& m) {
    LOGGER(ibis::gVerbose >= 0)
	<< "Warning -- ibis::whereParser encountered " << m
	<< " at location " << l;
}
