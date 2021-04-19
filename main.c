#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {

  // Input with initial values
  int input[2] = {0,0};

  // Exit condition check
  while (input[0] != 2)
  {
    printf("\n");
    printf("1. Select file to process\n");
    printf("2. Exit the program\n");
    printf("\n");
    printf("Enter a choice 1 or 2: ");
  
    scanf("%d", &input[0]);

    if(input[0] == 1) {
      //Reset Outer Option
      input[0] = 0;

      //Inner Menu and options
      while((input[1] != 1) && (input[1] != 2) && (input[1] != 3)) 
      {
        printf("\n");
        printf("Which file you want to process?\n");
        printf("Enter 1 to pick the largest file\n");
        printf("Enter 2 to pick the smallest file\n");
        printf("Enter 3 to specify the name of a file\n");
        printf("\n");
        printf("Enter a choice from 1 to 3: ");

        scanf("%d", &input[1]);

        if (input[1] == 1)
        {
          // The program finds the largest file with the extension csv in the current directory whose name starts with the prefix movies_ and automatically process it.
          // In case of tie, pick any of the files with the extension csv starting with movies_ that have the largest size.
          
        } else if (input[1] == 2)
        {
          // The program finds the smallest file with the extension csv in the current directory whose name starts with the prefix movies_ and automatically process it.
          // In case of tie, pick any of the files with the extension csv starting with movies_ that have the smallest size.

        } else if (input[1] == 3)
        {
          // The program asks the user to enter the name of a file.
          // The program checks if this file exists in the current directory. If the file is not found, the program should write an error message and again give the user the 3 choices about picking a file, i.e., don't go back to the main menu, but stay at the menu for picking a file.
          // For this option, there is no requirement that the file name must start with a particular prefix or that it must have a particular extension.

        } else {
          printf("Invalid Input\n");
        }

      }

      // Reset Inner Option
      input[1] = 0;

    } else if (input[0] != 2)
    {
      printf("Invalid Input\n");
    }
    
  
  }

  return 0;
}




