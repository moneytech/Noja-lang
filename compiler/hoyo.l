
%{
    #include "hoyo.tab.c"
%}

%option yylineno

%%


[ \t\n]             {}
\'(\\.|[^\\'])*\'            { yylval.value_string = duplicate_segment(yytext+1, yyleng-2); return STRING; }

[0-9]+\.[0-9]+  { yylval.value_f64 = strtod(yytext, 0); return FLOAT; }

[0-9]+          { yylval.value_i64 = strtoll(yytext, 0, 10); return INT; }

xor             return XOR;
and             return AND;
or              return OR;
not             return NOT;

for             return FOR;
while           return WHILE;
do              return DO;
if              return IF;
else            return ELSE;
return          return RETURN;
break           return BREAK;
continue        return CONTINUE;
print           return PRINT;
fn              return FUNCTION;
true            return TRUE;
false           return FALSE;
#breakpoint     return BREAKPOINT;
import          return IMPORT;
from            return FROM;
as              return AS;
class           return CLASS;

[a-zA-Z_]+[0-9]*  { yylval.label = duplicate_segment(yytext, yyleng); return LABEL; }

\+               return ADD;
\-               return SUB;
\*               return MUL;
\\               return DIV;
\:               return DDOTS;
=                return ASSIGN;
\(               return BRK_OP;
\)               return BRK_CL;
\,               return COMMA;
\{               return BRK_C_OP;
\}               return BRK_C_CL;
\[               return BRK_S_OP;
\]               return BRK_S_CL;
\<               return LSS;
\>               return GRT;
\>\=              return GEQ;
\<\=              return LEQ;
\!\=               return NQL;
\=\=               return EQL;
\.               return DOT;
\$               return DOLLA;
\;                return SEMICOLON;
%%
