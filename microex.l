%{
#include "microex.h"
#include "y.tab.h"

int line_count = 1;
int col_count = 1;
int token_line = 1;
int token_col = 1;

#define RETURN_TOK(tok) do { token_line = line_count; token_col = col_count; col_count = col_count + yyleng; return tok; } while(0)
%}

%%
"%%".*("\n")? {
    if (yytext[yyleng - 1] == '\n') {
        line_count = line_count + 1;
        col_count = 1;
    } 
    else {
        col_count = col_count + yyleng;
    }
}

[Pp][Rr][Oo][Gg][Rr][Aa][Mm]   { RETURN_TOK(PROGRAM); }
[Bb][Ee][Gg][Ii][Nn]           { RETURN_TOK(Begin); }
[Ee][Nn][Dd]                   { RETURN_TOK(END); }
[Dd][Ee][Cc][Ll][Aa][Rr][Ee]   { RETURN_TOK(DECLARE); }
[Aa][Ss]                       { RETURN_TOK(AS); }
[Ii][Nn][Tt][Ee][Gg][Ee][Rr]   { RETURN_TOK(INTEGER); }
[Ff][Ll][Oo][Aa][Tt]           { RETURN_TOK(FLOAT); }
[Ii][Ff]                       { RETURN_TOK(IF); }
[Tt][Hh][Ee][Nn]               { RETURN_TOK(THEN); }
[Ee][Ll][Ss][Ee]               { RETURN_TOK(ELSE); }
[Ee][Nn][Dd][Ii][Ff]           { RETURN_TOK(ENDIF); }
[Ff][Oo][Rr]                   { RETURN_TOK(FOR); }
[Tt][Oo]                       { RETURN_TOK(TO); }
[Dd][Oo][Ww][Nn][Tt][Oo]       { RETURN_TOK(DOWNTO); }
[Ee][Nn][Dd][Ff][Oo][Rr]       { RETURN_TOK(ENDFOR); }
[Ww][Hh][Ii][Ll][Ee]           { RETURN_TOK(WHILE); }
[Ee][Nn][Dd][Ww][Hh][Ii][Ll][Ee] { RETURN_TOK(ENDWHILE); }

[0-9]+\.[0-9]+  { yylval.float_val = atof(yytext); RETURN_TOK(FLOAT_NUMBER); }
[0-9]+          { yylval.int_val = atoi(yytext); RETURN_TOK(INT_NUMBER); }

","     { RETURN_TOK(','); }
";"     { RETURN_TOK(';'); }
"["     { RETURN_TOK('['); }
"]"     { RETURN_TOK(']'); }
"("     { RETURN_TOK('('); }
")"     { RETURN_TOK(')'); }
"+"     { RETURN_TOK('+'); }
"-"     { RETURN_TOK('-'); }
"*"     { RETURN_TOK('*'); }
"/"     { RETURN_TOK('/'); }
":="    { RETURN_TOK(ASSIGN); }
">="    { RETURN_TOK(GEQ); }
"<="    { RETURN_TOK(LEQ); }
"=="    { RETURN_TOK(EQ); }
"!="    { RETURN_TOK(NEQ); }
">"     { RETURN_TOK(GT); }
"<"     { RETURN_TOK(LT); }

[ \t\r]+ { col_count = col_count + yyleng; }
\n+ { line_count = line_count + yyleng; col_count = 1; }

[A-Za-z][A-Za-z0-9]* { yylval.symp = symlook(yytext); RETURN_TOK(NAME); }

. {
    fprintf(stderr,
            "[Lexical error] line %d, column %d, unexpected character '%c'\n",
            line_count, col_count, *yytext);
    col_count = col_count + 1;
    exit(1);
}

%%

