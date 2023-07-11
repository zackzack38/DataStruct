/*
*  Author: Zachary Levinson
*  Date: 11/20/21
*  Purpose: Read from a csv and find the top 10 cars with highest city mpg and write the results into a new csv
*  file. Now uses qsort.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LEN 6000
#define MAX_FIE 150
struct car{
  char id[MAX_FIE + 1];
  char classification[MAX_FIE + 1];
  char EType[MAX_FIE + 1];
  char Trans[MAX_FIE + 1];
  int MPG_City;
  char FType[MAX_FIE + 1];
  int MPG_High;
};
struct car cars[MAX_LEN];
int compare_cars(const void *p, const void *q); //Used with qsort to sort the list
void read_line(char *str, int n); //Take in input from console, not sure how to do scanf
int main(int argc, char *argv[])
{
  char fileName[100 + 1];
  char fileNameOut[] = "TOP10_city_mpg.csv";
  printf("Enter the file name: ");
  read_line(fileName, MAX_FIE);
  
  FILE* pFile = fopen(fileName, "r"); //Reading in file
  if(pFile == NULL)
  {
    printf("Error opening the input file.\n");
    return 1;
  }
  
  FILE* oFile = fopen(fileNameOut, "w"); //Writing out file
  if(oFile == NULL)
  {
    printf("Error opening the output file.\n");
    return 1;
  }

  int i = 0; //i - increments the array, by the end is the length of the whole.
  while (!feof(pFile) && !ferror(pFile))
  {
    if(fscanf(pFile, "%[^,], %[^,], %[^,], %[^,], %d, %[^,], %d\n", cars[i].id, cars[i].classification, cars[i].EType, cars[i].Trans, &cars[i].MPG_City, cars[i].FType, &cars[i].MPG_High) == 7)
    {
      i++;
    }
    else
    {
      printf("An input was not read correctly at %d\n", i);
      i++;
    }
  }//fileName has been read through and saved to the struct
  
  qsort(cars, i, sizeof(struct car), compare_cars);//replaced for project 10 sort_city_mpg(cars, i); //Sorts the array of cars
  
  for(i = 0; i < 10; i++)
  {
    fprintf(oFile, "%s,%s,%s,%s,%d,%s,%d\n", cars[i].id, cars[i].classification, cars[i].EType, cars[i].Trans, cars[i].MPG_City, cars[i].FType, cars[i].MPG_High);
  }
  
  fclose(pFile);
  fclose(oFile);
  return 0;
}

//Compares pointers to two elements in the list, returns [1 if p is less than q], [0 if p is equal to q], [-1 if p is greater than q]
int compare_cars(const void *p, const void *q)
{
  if(((struct car *)p)->MPG_City < ((struct car *)q)->MPG_City)
  {
    return 1;
  }
  else if(((struct car *)p)->MPG_City == ((struct car *)q)->MPG_City)
  {
    return 0;
  }
  else
  {
    return -1;
  }
}

/*
* Name: read_line
* Purpose: Read user input using getchar and saves it to the string that str is pointing to.
*/
void read_line(char *str, int n) //read_line modified as length of input is not important from return type int to type void
{
  int ch, i = 0;
  while ((ch = getchar()) != '\n')
  {
    if(i < n)
    {
      *str++ = ch;
      i++;
    }
  }
  *str = '\0';
}