# CSV TO "SCSV" CONVERTER

The other day I needed to open a csv with Microsoft Excel and to my surprise, I found out that Excel's csv file work by separating each value with a ';' instead of a ','

Instead of manually change the original file, or tinkering with Excel's options, I decided to program a converter that substitutes every ',' in a file with a ';' and saves the modified file as "converted.csv"




## How to use it

When you launch the program from terminal you can specify **two** parameters:
  1. input file name - **obligatory**
  2. output file name - *optional*

Example: `./converte my_file.csv my_output.cvs`

Here's how the program handles the console parameters:
  1. **No parameters** : The "Unable to read input file" error will be displayed and the program will stop
  2. **Only the first parameter** : The input file is converted and saved ina new file called "converted.csv" that will be located in the program folder
  3. **Both parameters**
      1. If the output file is specified without the .csv extension the program will add it; that means that if you don't have a destination file you can just add the name you want for the output file and the program will create it for you
      2. If the output file specified has the .csv extension the program will try to find it and use it as the destination file, if it doesn't exist it will create it.
