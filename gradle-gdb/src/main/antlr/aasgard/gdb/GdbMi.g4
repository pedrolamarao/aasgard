grammar GdbMi;

@header {
package aasgard.gdb;
}

// rule

output : ( outOfBand | resultRecord )* gdb ;

// documentation states below but gdb 9.1 behaves otherwise
// output : outOfBand* resultRecord? gdb ;

outOfBand : asyncRecord | streamOutput ;

asyncRecord : execAsyncRecord
    | statusAsyncRecord
    | notifyAsyncRecord
    ;
    
streamOutput : consoleStreamOutput
    | targetStreamOutput
    | logStreamOutput
    ;

resultRecord : CIRCUMFLEX record NL ;
execAsyncRecord : ASTERISK record NL ;
statusAsyncRecord : PLUS record NL ;
notifyAsyncRecord : EQUALS record NL ;
consoleStreamOutput : TILDE constant NL ;
targetStreamOutput : AT constant NL ;
logStreamOutput : AND constant NL ;
gdb : GDB NL ;

record : classs ( COMMA result )* ;
classs : STRING ;
result : variable EQUALS value ;

variable : STRING ;
value : constant | tuple | list ;

constant : QSTRING ;
tuple : LBRACE ( result ( COMMA result )* )? RBRACE ;
list : ( LBRACKET ( value ( COMMA value )* )? RBRACKET ) ;

// documentation states below but ambiguous so ignore
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

GDB : '(gdb) ' ;
QSTRING : '"' ( ~["] | ( '\\"' ) )+ '"' ;
STRING : [\-a-z]+ ;
