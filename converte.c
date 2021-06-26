/****************************************************************************************************************************************************************************
   I found myself in the situation to need a csv file to be modified as such every value was separated by a ';' instead of a ','
   Being really lazy I decided to write a "converter" instead of doing in it by hand
   It's a really simple program but I actually ahd a lot of fun creating it, so here it is.
****************************************************************************************************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]){
  char c;
  char ext[5] = {'.', 'c','s','v','\0'};  // ".csv" extention
  FILE *fp_in;
  FILE *fp_out;
  
  // Check if the input file exists
  if ((fp_in = fopen(argv[1], "r")) == NULL) {
    printf("ERROR: failed to open file\n");
    return 1;
  }
  
  // When you call the program you can specify the output file as the second parameter
  // The prgram checks if you specofied an output file or not, if you don't it creates a "converted.csv"
  if (argc > 2) {
    if(strstr(argv[2], ext) != NULL){   // Check if the spefified output has the '.csv' extention
      fp_out = fopen(argv[2], "w");
    } else {
      printf("\nThe .csv  extention will be added to \"%s\"\n", argv[2]);
      int len = (strlen(argv[2]) + strlen(ext) + 1);    // length of the file name + extention + one for the '\0' terminator
      char new_out[len];
      strcpy(new_out, argv[2]);
      int j = 0;
      for (int i = strlen(argv[2]); i < len; i++) {     // create a string with the new output file name
        new_out[i] = ext[j];
        j++;
      }
      printf("\nOUTPUT FILE: \"%s\"\n", new_out);
      fp_out = fopen(new_out, "w");
    }
  } else {    // if the output file is not specified
    fp_out = fopen("converted.csv", "w");
  }

  // Converting every ';' in ','
  while((fscanf(fp_in, "%c", &c)) != EOF){
    if (c == ',') {
      fprintf(fp_out, "%s", ";");
    } else {
      fprintf(fp_out, "%c", c);
    }
  }

  fclose(fp_in);
  fclose(fp_out);

  printf("\nConversion Completed!\n");

  return 0;
}
