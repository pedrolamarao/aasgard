grammar GdbMi;

@header {
package aasgard.gdb;
}

// rule

output : outOfBand* resultRecord? GDB NL ;
outOfBand : asyncRecord | streamOutput ;

resultRecord : CIRCUMFLEX record NL ;

asyncRecord : execAsyncRecord | notifyAsyncRecord ;
execAsyncRecord : ASTERISK record NL ;
statusAsyncRecord : PLUS record NL ;
notifyAsyncRecord : EQUALS record NL ;

streamOutput : consoleStreamOutput | targetStreamOutput | logStreamOutput ;
consoleStreamOutput : TILDE constant NL ;
targetStreamOutput : AT constant NL ;
logStreamOutput : AND constant NL ;

record : classs ( COMMA result )* ;
classs : STRING ;
result : variable EQUALS value ;

variable : STRING ;
value : constant | tuple | list ;

constant : QSTRING ;
tuple : LBRACE ( result ( COMMA result )* )? RBRACE ;
list : ( LBRACKET ( value ( COMMA value )* )? RBRACKET ) ;

// actually, below, but ambigous
// list : ( LBRACKET ( value ( COMMA value )* )? RBRACKET ) | ( LBRACKET ( result ( COMMA result )* )? RBRACKET ) ;

// lexeme — symbols

ASTERISK : '*' ;
AND : '&' ;
AT : '@' ;
CIRCUMFLEX : '^' ;
COMMA : ',' ;
EQUALS : '=' ;
LBRACE : '{' ;
LBRACKET : '[' ;
PLUS : '+' ;
RBRACE : '}' ;
RBRACKET : ']' ;
NL : '\r'? '\n' ;
TILDE : '~' ;

// lexeme — sequences

GDB : '(gdb)' ;
QSTRING : '"' ( ~["] | ( '\\"' ) )+ '"' ;
STRING : [\-a-z]+ ;
