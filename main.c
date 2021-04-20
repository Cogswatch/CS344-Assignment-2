// More includes than I could ever need
// Courtesy of Exploration: Directories
#include <fcntl.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

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
  
    scanf(" %d", &input[0]);

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

        scanf(" %d", &input[1]);

        if (input[1] == 1)
        {
          // The program finds the largest file with the extension csv in the current directory whose name starts with the prefix movies_ and automatically process it.
          // In case of tie, pick any of the files with the extension csv starting with movies_ that have the largest size.

          // Courtesy of Exploration: Directories
          DIR* currDir = opendir(".");  // Open the current directory
          struct dirent *aDir;          // Directory Struct
          time_t lastModifTime;         // Time Since Last Modification
          off_t largestSize = 0;        // Largest file read
          struct stat dirStat;          // Meta Data Struct
          int i = 0;                    // Record First Safety
          char entryName[256];          // Name Holder

          // Go through all the entries
          while((aDir = readdir(currDir)) != NULL){

            // Check for prefix = "movies"
            if(strncmp("movies", aDir->d_name, strlen("movies")) == 0){
              
              // Get meta-data for the current entry
              stat(aDir->d_name, &dirStat);  

              // CVS verification idea modified from https://stackoverflow.com/questions/4849986/how-can-i-check-the-file-extensions-in-c

              char *end = strrchr(aDir->d_name,'.');// = aDir->d_name + strlen(aDir->d_name);

              if(i == 0 || end != NULL ) {
                //ends with csv
                if(i == 0 || strcmp(end,".csv") == 0) {
                  // Compare File Sizes
                  if(i == 0 || dirStat.st_size > largestSize){
                      largestSize = dirStat.st_size;
                      memset(entryName, '\0', sizeof(entryName));
                      strcpy(entryName, aDir->d_name);
                    }
                }
              }

              i++;
            }
          }

          // Close the directory
          closedir(currDir);
          printf("Now processing the chosen file named %s\n", entryName);
          
        } else if (input[1] == 2)
        {
          // The program finds the smallest file with the extension csv in the current directory whose name starts with the prefix movies_ and automatically process it.
          // In case of tie, pick any of the files with the extension csv starting with movies_ that have the smallest size.
          // Courtesy of Exploration: Directories
          DIR* currDir = opendir(".");  // Open the current directory
          struct dirent *aDir;          // Directory Struct
          time_t lastModifTime;         // Time Since Last Modification
          off_t largestSize = 0;        // Largest file read
          struct stat dirStat;          // Meta Data Struct
          int i = 0;                    // Record First Safety
          char entryName[256];          // Name Holder

          // Go through all the entries
          while((aDir = readdir(currDir)) != NULL){

            // Check for prefix = "movies"
            if(strncmp("movies", aDir->d_name, strlen("movies")) == 0){
              
              // Get meta-data for the current entry
              stat(aDir->d_name, &dirStat);  

              // CVS verification idea modified from https://stackoverflow.com/questions/4849986/how-can-i-check-the-file-extensions-in-c

              char *end = strrchr(aDir->d_name,'.');// = aDir->d_name + strlen(aDir->d_name);

              if(i == 0 || end != NULL ) {
                //ends with csv
                if(i == 0 || strcmp(end,".csv") == 0) {
                  // Compare File Sizes
                  if(i == 0 || dirStat.st_size < largestSize){
                      largestSize = dirStat.st_size;
                      memset(entryName, '\0', sizeof(entryName));
                      strcpy(entryName, aDir->d_name);
                    }
                }
              }

              i++;
            }
          }

          // Close the directory
          closedir(currDir);
          printf("Now processing the chosen file named %s\n", entryName);
          
        } else if (input[1] == 3)
        {
          // The program asks the user to enter the name of a file.
          // The program checks if this file exists in the current directory. If the file is not found, the program should write an error message and again give the user the 3 choices about picking a file, i.e., don't go back to the main menu, but stay at the menu for picking a file.
          // For this option, there is no requirement that the file name must start with a particular prefix or that it must have a particular extension.

          char entryName[256];          // Name Holder
          int file_descriptor;          // File existance status

          printf("Enter the complete file name: ");
          scanf(" %s", entryName);

          // Largely from Exploration: Files

          file_descriptor = open(entryName, O_RDWR , 0600);
          if (file_descriptor == -1){
            printf("open() failed on \"%s\"\n", entryName);
            perror("Error");
          }
	
	        printf("file_descriptor = %d\n", file_descriptor);

          close(file_descriptor);

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




