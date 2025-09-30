#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MEMORY_SIZE 30000

int memoryPointer = 0;
int *memoryBlock;

void fillMemoryBlock(int *memoryBlock);
char *readFromFile(const char *fileName);
char *readFromTerminal();
void run(const char *source);
void runSubString(const char *source, int startIndex);

int main(int argc, char *argv[]){
  
  memoryBlock = malloc(sizeof(int) * MEMORY_SIZE);

  //fill it with 0's
  fillMemoryBlock(memoryBlock);

  if(argc == 1){
    //use the command line for input
    char *source = readFromTerminal();
    run(source);
    free(source);
  }
  else if(argc == 2){
    //a file has been given
    char *source= readFromFile(argv[1]);
    run(source);
    free(source);
  }
  else{
    printf("Usage ./a.out 'file.txt' || ./a.out\n");
    free(memoryBlock);
    exit(1);
  }

  free(memoryBlock); 
  return 0;
}

char *readFromTerminal(){
  char *buffer = malloc(sizeof(char) * 1000);
  printf("Enter your code: \n");
  scanf(" %s", buffer);
  return buffer;
}

char *readFromFile(const char *fileName){
  FILE *file;
  file = fopen(fileName, "r");

  if(file == NULL){
    printf("Cannot find file\n");
    exit(1);
  }
  fseek(file, 0, SEEK_END); //move pointer to end of file
  int fileSize = ftell(file);// get the pointer location(index)
  rewind(file); //move pointer back to the start
  
  char *buffer = malloc(sizeof(char) * fileSize + 1); //leave room for Null termintor
  fread(buffer, 1, fileSize, file);
  buffer[fileSize] = '\0'; //add the null teminator

  fclose(file);
  return buffer;
}

void runSubString(const char *source, int startIndex){
  //TODO: figure this out
}

void run(const char *source){
  int length = strlen(source);
  if(length <= 0){
    printf("Nothing to run\n");
    exit(1);
  }
  int index = 0;
  while(source[index] != '\0'){
    switch(source[index]){
      case '>':
        memoryPointer++;
        break;
      case '<':
        memoryPointer--;
        break;
      case '+':
        memoryBlock[memoryPointer]++;
        break;
      case '-':
        memoryBlock[memoryPointer]--;
        break;
      case '[':
        runSubString(source, index);
        break;
      case ',':
        char input;
        scanf(" %c", &input);
        memoryBlock[memoryPointer] = (int)input;
        break;
      case '.':
        printf("%c", memoryBlock[memoryPointer]);
        break;
      default:
        break;
    }
    //printf("%d, ", indexInSource);
    index++;
  }

}

void fillMemoryBlock(int *memoryBlock){
  for(int i = 0; i < MEMORY_SIZE; i++){
    memoryBlock[i] = 0;
  }
}

