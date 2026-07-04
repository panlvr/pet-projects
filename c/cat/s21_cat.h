#ifndef S21_CAT
#define S21_CAT

#include <stdio.h>

struct flags {
  int b;
  int e;
  int n;
  int s;
  int t;
  int v;
  int E;
  int T;
};

int char_flags(char* input, struct flags* flags);
int string_flags(char* input, struct flags* flags);
int parse_flags(char* input, struct flags* flags, int* flag);
void input(char* file, struct flags* flags, int* is_new_line, int* line_number,
           int* empty_line_seen);
void process_file(struct flags* flags, FILE* fptr, int* is_new_line,
                  int* line_number, int* empty_line_seen);
void is_allowed(struct flags* flags, int* ch, int* empty_line_seen,
                int* allowed);
void numbering(struct flags* flags, int* ch, int* line_number);
void flag_v(int* ch);
void flag_e(int* ch);
void flag_t(int* ch);

#endif