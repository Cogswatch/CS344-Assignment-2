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

void processFile(char*);

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
          processFile(entryName);
          
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
          processFile(entryName);
          
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
            printf("The file %s was not found. Try again\n", entryName);
            input[1] = 0;
          } else {

            processFile(entryName);

          }

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

struct movie *processMovieFile(char *filePath);
struct movie *createMovie(char *currLine);

struct movie
{
    char *title;          // Movie Title
    int   year;           // Year of release
    char *languages[5];// Languages
    double ranking;       // Rating, either int or double
    struct movie *next;   // Linked List Itterator
};

void processFile(char* fileName) {
  printf("Now processing the chosen file named %s\n", fileName);

  char dirName[256];
  sprintf(dirName, "bradychr.movies.%ld", (random()%100000));

  mkdir(dirName, 0750);

  int file_descriptor;
  char filePath[256];

  // Extract movies from provided file
  struct movie *MoviesList = processMovieFile(fileName);

  // Start by finding lowest year
  struct movie *searchHead = MoviesList;
  struct movie *searchHead2 = MoviesList;

  // Lookup table for year filtering. Stupid. Dirty. 
  // But more importantly...
  // It does the job :(
    
  int foundYears[3000];
  for(int i = 0; i < 3000; i++) {
    foundYears[i] = 0;
  }

  // O(n^2) yuck

  // Begin Search Loop
  while(searchHead != NULL) {
    // no entry found yet
    if (foundYears[searchHead->year] == 0) {
      foundYears[searchHead->year] = 1;
      
      searchHead2 = MoviesList;

      while (searchHead2 != NULL)
      {
        if(searchHead->year == searchHead2->year) {

          // FOUND MATCH

          sprintf(filePath, "./%s/%d.txt", dirName, searchHead2->year);

          file_descriptor = open(filePath, O_RDWR | O_CREAT | O_APPEND, 0640);

          char contents[256];

          sprintf(contents, "%s\n", searchHead2->title);

          write(file_descriptor, contents, strlen(contents));

          close(file_descriptor);

          printf("%d %s\n", searchHead2->year, searchHead2->title);
        }

        searchHead2 = searchHead2->next;
      }

    }
    
    searchHead = searchHead->next;
  }

};

struct movie *processMovieFile(char *filePath)
{
    // Open the specified file for reading only
    FILE *movieFile = fopen(filePath, "r");

    char *currLine = NULL;
    size_t len = 0;
    ssize_t nread;
    char *token;

    // The head of the linked list
    struct movie *head = NULL;
    // The tail of the linked list
    struct movie *tail = NULL;

    int legendGuard = 0;

    // Read the file line by line
    while ((nread = getline(&currLine, &len, movieFile)) != -1)
    {
        legendGuard++;
        if (legendGuard == 1)
        {
          continue;
        }
        

        // Get a new student node corresponding to the current line
        struct movie *newNode = createMovie(currLine);

        // Is this the first node in the linked list?
        if (head == NULL)
        {
            // This is the first node in the linked link
            // Set the head and the tail to this node
            head = newNode;
            tail = newNode;
        }
        else
        {
            // This is not the first node.
            // Add this node to the list and advance the tail
            tail->next = newNode;
            tail = newNode;
        }
    }
    free(currLine);
    fclose(movieFile);
    return head;
}

/* Parse the current line which is space delimited and create a
*  student struct with the data in this line
*/
struct movie *createMovie(char *currLine)
{
    struct movie *currMovie = malloc(sizeof(struct movie));

    // For use with strtok_r
    char *saveptr;
    char *saveptr2;

    // The first token is the title
    char *token = strtok_r(currLine, ",", &saveptr);
    currMovie->title = calloc(strlen(token) + 1, sizeof(char));
    strcpy(currMovie->title, token);

    // The next token is the year
    token = strtok_r(NULL, ",", &saveptr);
    currMovie->year = atoi(token);

    // === The next token(s) is the languages

    // Outer loop, extract sub array
    token = strtok_r(NULL, ",", &saveptr);

    // remove brackets (this one sucked)
    char *token2 = strtok_r(token, "[", &saveptr2);
    token2 = strtok_r(token2, "]", &saveptr2);
    
    // Reset delemeter to semicolon
    token2 = strtok_r(token2, ";", &saveptr2);

    int i = 0; 
    while(token2 != NULL) {
      
      currMovie->languages[i] = calloc(strlen(token2) + 1, sizeof(char));
      strcpy(currMovie->languages[i], token2);

      i++;
      token2 = strtok_r(NULL, ";", &saveptr2);
    }

    

    // The last token is the rating value
    token = strtok_r(NULL, "\n", &saveptr);
    currMovie->ranking = strtod(token, NULL);

    // Set the next node to NULL in the newly created student entry
    currMovie->next = NULL;

    return currMovie;
}