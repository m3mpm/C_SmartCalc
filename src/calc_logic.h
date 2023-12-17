#ifndef SRC_C_SMART_CALC_H_
#define SRC_C_SMART_CALC_H_

#include <ctype.h>
#include <math.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SUCCESS 1
#define FAILURE 0
#define EPS 1e-7

/* priority:
'( , ) = 0;
'+ , -' = 1;
'* , /' = 2;
'm' - mod = 2
'c' - cos = 5;
's' - sin = 5;
't' - tan = 5;
'o' - acos = 5;
'i' - asin = 5;
'a' - atan = 5;
'q' - sqrt = 5;
'n' - ln = 5;
'g' - log = 5;
'^' - pow = 6
'u' - unary minus = 7;
 */

typedef struct stack_operators {
  char arr_char[512];
  int priority;
  unsigned int pos;
} Stack_op;

typedef struct stack_numbers {
  double arr_num[256];
  unsigned int pos;
} Stack_num;

/*---main fuction--*/
int get_result(char *str, double input_x, double *result);

/*--- check input string functions ---*/
int check_input_str(char *str);                  // error 2-12
int check_length_str(const char *str);           // error #2
int check_correct_chars(const char *str);        // error #3
int check_number_brackets(const char *str);      // error #4
int check_functions_names(const char *str);      // error #5
int check_name(const char *str);                 // error #22
int check_brackets(const char *str);             // error #6
int check_dots(const char *str);                 // error #7
int check_x(const char *str);                    // error #8
int check_operator_plus_minus(const char *str);  // error #9
int check_operator_mde(const char *str);         // error #10
int check_mod(const char *str);                  // error #11
int check_functions(const char *str);            // error #12 #13 - 21
int check_acos(const char *str);                 // error #0
int check_asin(const char *str);                 // error #0
int check_atan(const char *str);                 // error #0
int check_cos(const char *str);                  // error #0
int check_sin(const char *str);                  // error #0
int check_tan(const char *str);                  // error #0
int check_sqrt(const char *str);                 // error #0
int check_log(const char *str);                  // error #0
int check_ln(const char *str);                   // error #0

/*--- search x---*/
int is_find_x(const char *str);

/*--- rebuild string before back polish notanion ---*/
void rebuild_string(char *dst, char *src);
void rename_functions(char *dst, char *src);
void rebuild_signs(char *dst, char *src);
void rebuild_unary_plus_minus(char *dst, char *src);
void add_zero_to_number(char *dst, char *src);
void add_multi_to_function(char *dst, char *src);

/*--- back polish notation functions ---*/
void create_polish(Stack_op *pst_polish, Stack_op *pst_op, char *pstr);
int get_priority(char ch);

/*--- stack functions ---*/
// operations stack
void init_stack_op(Stack_op *st);
void push_stack_op(Stack_op *st, char value);
char pop_stack_op(Stack_op *st);
char peek_stack_op(Stack_op *st);
int is_empty_stack_op(Stack_op *st);
// value stack
void init_stack_num(Stack_num *st);
void push_stack_num(Stack_num *st, double value);
double pop_stack_num(Stack_num *st);
int is_empty_stack_num(Stack_num *st);

/*--- back polish notation processing function ---*/
/*
error = 40 - /
error = 41 - mod
error = 42 - acos
error = 43 - asin
error = 44 - sqrt
error = 45 - log
error = 46 - ln
*/

int make_calculation(char *str, double x, double *result);  // error = FAILURE 0

#endif  //  SRC_C_SMART_CALC_H_
