// CSV TO CSV CONVERTER - by Giocrom
// version (alpha) 2.5

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Librares/errors.h"
#include "Librares/output.h"

void fieldCheck(FILE *input, FILE *output,
                char current, char new, char c, int counter);


int main(int argc, char *argv[]){

  //argv[1] = InputFileName (i.e. "times.csv")
  //argv[2] = OutputFileName  (optional)
  //argv[3] = CurrentEncoding (i.e. ",")
  //argv[4] = WantedEncoding (i.e. ";")

  if (argc == 1) {
    printf("Usage: csvconverter ");
    printf("input_file.csv output_file current_separator new_separator\n");
    return 0;
  }

  // ERROR handling
  FILE *fp_in = errorHandling(argc, argv[1]);
  if(fp_in == NULL){
    return -1;
  }

  // Output File handling
  FILE *fp_out = outputHandling(argc, argv[2]);
  if(fp_out == NULL){
    fclose(fp_in);
    return -1;
  }

  char c;   // Currently analyzed char
  while((c = fgetc(fp_in)) != EOF){
    if (c == argv[argc - 2][0]) {
      fprintf(fp_out, "%c", argv[argc - 1][0]);
    } else if (c == '"') {
      fprintf(fp_out, "\"");
      fieldCheck(fp_in, fp_out, argv[argc - 2][0], argv[argc - 1][0], c, 1);
    } else {
      fprintf(fp_out, "%c", c);
    }
  }

  fclose(fp_in);
  fclose(fp_out);

  printf("\nConversion Completed!\n");

  return 0;
}


// The fieldCheck function skips the convertion of fields enclosed by ""
void fieldCheck(FILE *input, FILE *output,
                char current, char new, char c, int counter){
  while ((c = fgetc(input)) != EOF && c != current) {
    if (c == '"'){counter++;}
    fprintf(output, "%c", c);
  }

  if (c == EOF) {
    return;
  }

  if ((counter % 2) == 1) {
    fprintf(output, "%c", current);
    fieldCheck(input, output, current, new, c, counter);
  } else {
    fprintf(output, "%c", new);
    return;
  }
}
