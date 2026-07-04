#include "s21_grep.h"

#include <regex.h>
#include <string.h>

int main(int argc, char* argv[]) {
  struct flags flags = {0};
  // command flag pattern file
  char pattern[4096] = "";
  regex_t regex;
  int file_start = 0;
  int expecting_pattern = 0;
  int cflags = REG_EXTENDED | REG_NEWLINE;
  if (parser(&expecting_pattern, &file_start, pattern, argv, &argc, &flags,
             &cflags) != 0) {
    return 1;
  }
  if (pattern[0] == '\0') {
    printf("Please provide a pattern");
    return 2;
  }
  if (file_start == 0) {
    printf("Please provide at least one file");
    return 3;
  }
  int files_cnt = (argc - file_start);
  int comp_res = regcomp(&regex, pattern, cflags);
  if (comp_res != 0) {
    printf("Couldn't compile");
    return 4;
  }
  for (int i = file_start; i < argc; i++) {
    FILE* fptr = fopen(argv[i], "r");
    if (fptr != NULL) {
      match(fptr, &regex, &flags, argv[i], &files_cnt);
    } else {
      printf("Couldn't open file");
      return 5;
    }
  }
  regfree(&regex);
  return 0;
}

int flag_switch(char* input, struct flags* flags, int* expecting_pattern,
                int* cflags) {
  int len = strlen(input);
  int invalid_flag = 0;
  for (int i = 1; i < len; i++) {
    int recognized = 0;
    if (input[i] == 'e') {
      flags->e = 1;
      recognized = 1;
      *expecting_pattern = 1;
    }
    if (input[i] == 'i') {
      flags->i = 1;
      recognized = 1;
      (*cflags) |= REG_ICASE;
    }
    if (input[i] == 'v') {
      flags->v = 1;
      recognized = 1;
    }
    if (input[i] == 'c') {
      flags->c = 1;
      recognized = 1;
    }
    if (input[i] == 'l') {
      flags->l = 1;
      recognized = 1;
    }
    if (input[i] == 'n') {
      flags->n = 1;
      recognized = 1;
    }
    if (!recognized) {
      invalid_flag = 1;
    }
  }
  return invalid_flag;
}

int parser(int* expecting_pattern, int* file_start, char* pattern,
           char* input[], int* argc, struct flags* flags, int* cflags) {
  int pattern_seen = 0;
  int success = 0;
  for (int i = 1; i < *argc; i++) {
    if (*expecting_pattern) {
      if (pattern_seen == 0) {
        strcpy(pattern, input[i]);
      } else {
        strcat(pattern, "|");
        strcat(pattern, input[i]);
      }
      pattern_seen++;
      *expecting_pattern = 0;
    } else if (input[i][0] == '-') {
      // parse flags
      int result = flag_switch(input[i], flags, expecting_pattern, cflags);
      if (result == 1) {
        printf("Flag doesn't exist, please enter valid flag");
        success = 1;
      }
    } else if (pattern_seen == 0) {
      strcpy(pattern, input[i]);
      pattern_seen = 1;
      *expecting_pattern = 0;
    } else if (*file_start == 0) {
      *file_start = i;
    }
  }
  return success;
}

int match(FILE* fptr, regex_t* regex, struct flags* flags, char* filename,
          int* files_cnt) {
  int matching_lines = 0;
  int line_number = 1;
  char line[4096];
  while (fgets(line, sizeof(line), fptr) != NULL) {
    int did_match = regexec(regex, line, 0, NULL, 0) == 0;
    if (flags->v) {
      did_match = !did_match;
    }
    if (did_match) {
      matching_lines++;
    }
    if (did_match && flags->l) {
      printf("%s\n", filename);
      fclose(fptr);
      return 0;
    } else if (did_match && flags->n && !flags->c) {
      if (*files_cnt > 1) {
        printf("%s:%i:%s", filename, line_number, line);
        if (line[strlen(line) - 1] != '\n') printf("\n");
      } else {
        printf("%i:%s", line_number, line);
        if (line[strlen(line) - 1] != '\n') printf("\n");
      }
    } else if (did_match && !flags->c) {
      if (*files_cnt > 1) {
        printf("%s:%s", filename, line);
        if (line[strlen(line) - 1] != '\n') printf("\n");
      } else {
        printf("%s", line);
        if (line[strlen(line) - 1] != '\n') printf("\n");
      }
    }
    line_number++;
  }
  if (flags->c) {
    if (*files_cnt > 1) {
      printf("%s:%i\n", filename, matching_lines);
    } else {
      printf("%i\n", matching_lines);
    }
  }
  fclose(fptr);
  return 0;
}