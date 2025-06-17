#ifndef MICROEX_H
#define MICROEX_H

#define NSYMS 100
#define TYPE_INT 0
#define TYPE_FLOAT 1
#define MAX_TEMP_SIZE 100

struct symtab {
    char *name;
    int type;
    int check_is_array;
    int array_size;
    union {
        int int_val;
        float float_val;
    } val;
    int check_is_declared;
};

extern struct symtab symtab[NSYMS];
struct symtab *symlook(char *s);

typedef struct {
    char *place; // location of expression result -> register name or operand
    int type; // Type int or float
} expression_attribute;

typedef struct {
    char*name; // Name of the temp variable
    int type;  // Type int or float
} temp_information;

#endif

