// CSV TO CSV CONVERTER - by Giocrom
// version (alpha) 2.0

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_FILE_NAME_LEN 31

int checkOutputName(char *output);
void fieldCheck(FILE *input, FILE *output, char current, char new);

int main(int argc, char *argv[]){

  //argv[1] = InputFileName (i.e. "times.csv")
  //argv[2] = OutputFileName  (optional)
  //argv[3] = CurrentEncoding (i.e. ",")
  //argv[4] = WantedEncoding (i.e. ";")

  // ERROR handling
  FILE *fp_in;
  if ((fp_in = fopen(argv[1], "r")) == NULL) {
    printf("ERROR: failed to open file\n");
    return -1;
  }

  if (argc < 4) {
    printf("ERROR: too few parameters\n");
    return -1;
  }

  if (argc > 5) {
    printf("ERROR: too many parameters\n");
    return -1;
  }

  // Output File handling
  FILE *fp_out;
  if (argc == 5) {   // if argc == 5 then an Output File was specified
    // file's name check
    if(checkOutputName(argv[2])){
      printf("ERROR: invalid output file name\n");
      return -1;
    }
    // Check if the file's name has the .csv extention
    char extention[5] = {'.','c','s','v','\0'};
    int flag = 1, j = 0;
    for (int i = (strlen(argv[2]) - 4); i < strlen(argv[2]); i++){
      if(argv[2][i] != extention[j]){ flag = 0; }
      j++;
    }
    if(flag){
      fp_out = fopen(argv[2], "w");
    } else {
      printf("\nThe .csv extention will be added to \"%s\"\n", argv[2]);
      int len = (strlen(argv[2]) + strlen(extention) + 1);
      char new_out[len];
      strcpy(new_out, argv[2]);
      int j = 0;
      for (int i = strlen(argv[2]); i < len; i++) {
        new_out[i] = extention[j];
        j++;
      }
      printf("\nOUTPUT FILE: \"%s\"\n", new_out);
      fp_out = fopen(new_out, "w");
    }
  } else {
    fp_out = fopen("converted.csv", "w");
    printf("\nOUTPUT FILE: \"converted.csv\"\n");
  }

  char c;   // Currently analyzed char
  while((fscanf(fp_in, "%c", &c)) != EOF){
    if (c == '"') {
      fprintf(fp_out, "\"");
      fieldCheck(fp_in, fp_out, argv[argc - 2][0], argv[argc - 1][0]);
    } else if (c == argv[argc - 2][0]) {
        fprintf(fp_out, "%c", argv[argc - 1][0]);
    } else {
      fprintf(fp_out, "%c", c);
    }
  }


  fclose(fp_in);
  fclose(fp_out);

  printf("\nConversion Completed!\n");

  return 0;
}

// The checkOutputName function checks if the output file's name is legal
int checkOutputName(char *output){

  // Check if the file's name is too long
  if (strlen(output) > MAX_FILE_NAME_LEN) {return 1;}

  // Check if the file's name starts or ends with a blank space
  if ((output[0] || output[strlen(output) - 1]) == ' ') {
    return 1;
  }

  // Check if the file's name contains crl chars or punctuation chars
  int flag = 0;
  for (int i = 0; i < strlen(output); i++) {
    if(ispunct((unsigned char)output[i])){flag = 1;}
    if(iscntrl((unsigned char)output[i])){flag = 1;}
    if (output[i] == '_' || output[i] == '.') {
      flag = 0;
    }
  }
  return flag;
}

// The fieldCheck function skips the convertion of fields enclosed by ""
void fieldCheck(FILE *input, FILE *output, char current, char new){
  char c;
  while ((fscanf(input, "%c", &c)) != EOF && c != current) {
    fprintf(output, "%c", c);
  }
  if (c == current){ fprintf(output, "%c", new); }
  return;
}
