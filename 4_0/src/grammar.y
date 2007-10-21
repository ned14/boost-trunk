%include {
/*
Copyright 2007 Redshift Software, Inc.
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or http://www.boost.org/LICENSE_1_0.txt)
*/
}

%name jamParse
%start_symbol run
%token_prefix JAM_

// Ops by increasing precedence.
%left OR_OR OR.
%left AND_AND AND.
%left EQ NEQ IN.
%left LT LE GT GE.
%left NOT.

// Just a sequence of rules to run.
run                 ::= .
run                 ::= rules.

// Zero or more rules.
block               ::= null.
block               ::= rules.

// One or more rules.
rules               ::= rule.
rules               ::= rule rules.
rules               ::= LOCAL list assign_list_opt EOM block.

null                ::= .

assign_list_opt     ::= EQ list.
assign_list_opt     ::= null.

arglist_opt         ::= LPAREN lol RPAREN.
arglist_opt         ::= .

local_opt           ::= LOCAL.
local_opt           ::= .

// Any one of Jam's rules.
rule                ::= LBRACE block RBRACE.
rule                ::= INCLUDE list EOM.
rule                ::= ARG lol EOM.
rule                ::= arg assign list EOM.
rule                ::= arg ON list assign list EOM.
rule                ::= RETURN list EOM.
rule                ::= FOR local_opt ARG IN list LBRACE block RBRACE.
rule                ::= SWITCH list LBRACE cases RBRACE.
rule                ::= IF expr LBRACE block RBRACE.
rule                ::= MODULE list LBRACE block RBRACE.
rule                ::= CLASS lol LBRACE block RBRACE.
rule                ::= WHILE expr LBRACE block RBRACE.
rule                ::= IF expr LBRACE block RBRACE ELSE rule.
rule                ::= local_opt RULE ARG arglist_opt rule.
rule                ::= OM arg rule.
rule                ::= ACTIONS eflags ARG bindlist LBRACE STRING RBRACE.

// "-=", "+=", "?=", "default ="
assign              ::= EQ.
assign              ::= PLUS_EQ.
assign              ::= OPT_EQ.
assign              ::= DEFAULT EQ.

// An expression for if.
expr                ::= arg.
expr                ::= expr EQ expr.
expr                ::= expr NEQ expr.
expr                ::= expr LT expr.
expr                ::= expr LE expr.
expr                ::= expr GT expr.
expr                ::= expr GE expr.
expr                ::= expr AND expr.
expr                ::= expr AND_AND expr.
expr                ::= expr OR expr.
expr                ::= expr OR_OR expr.
expr                ::= expr IN expr.
expr                ::= NOT expr.
expr                ::= LPAREN expr RPAREN.

// Action elements inside a switch.
cases               ::= .
cases               ::= case cases.

// Single action element inside a switch.
case                ::= CASE ARG COLON block.

// Lists of lists.
lol                 ::= list.
lol                 ::= list COLON lol.

// Zero or more args in a list.
list                ::= .
list                ::= list arg.

//
arg                 ::= ARG.
arg                 ::= LBRACKET func RBRACKET.

// Function call evaluation (inside [])
func                ::= arg lol.
func                ::= ON arg arg lol.
func                ::= ON arg RETURN list.

// Zero or more modifiers to 'executes'
eflags              ::= .
eflags              ::= eflags eflag.

// Action execution flag.
eflag               ::= UPDATED.
eflag               ::= TOGETHER.
eflag               ::= IGNORE.
eflag               ::= QUITELY.
eflag               ::= PIECEMEAL.
eflag               ::= EXISTING.

// List of variables to bind for an action.
bindlist            ::= .
bindlist            ::= BIND list.
