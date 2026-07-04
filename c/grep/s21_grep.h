#ifndef S21_GREP_H
#define S21_GREP_H

#include <regex.h>
#include <stdio.h>

struct flags {
  int e;
  int i;
  int v;
  int c;
  int l;
  int n;
};

int flag_switch(char* input, struct flags* flags, int* expecting_pattern,
                int* cflags);
int parser(int* expecting_pattern, int* file_start, char* pattern,
           char* input[], int* argc, struct flags* flags, int* cflags);
int match(FILE* fptr, regex_t* regex, struct flags* flags, char* filename,
          int* files_cnt);

#endif