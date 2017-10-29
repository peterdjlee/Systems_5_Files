#include "randfile.h"

int rand_num() {
  int random;
  int file = open("/dev/random", O_RDONLY);
  if (file < 0) {
    exit(0);
  }
  read(file, &random, sizeof(random));
  close(file);
  return random;
}

int main() {
  int arr_one[10], i;

  // fd = open("foo", O_CREAT | O_WRONLY, 0777);

  printf("Creating random numbers...\n");
  for (i = 0; i < 10; i++) {
    int num = rand_num();
    arr_one[i] = num;
    printf("arr_one[%d]: %d\n", i, num);
  }

  int file = open("file", O_CREAT | O_WRONLY, 0644);
  printf("\nWriting to the file...\n");
  write(file, arr_one, sizeof(arr_one));
  close(file);

  int arr_two[10];
  printf("\nReading from the file...\n");
  file = open("file", O_RDONLY, 0644);
  read(file, arr_two, sizeof(arr_two));
  close(file);

  printf("\nVerifying if numbers match...\n");
  for (i = 0; i < 10; i++) {
    if(arr_one[i] == arr_two[i]) {
      printf("arr_two[%d]: %d\n", i, arr_two[i]);
    } else {
      printf("ERROR");
    }
  }

  // printing out error if any
  // printf("errno: %d\n", errno);
  // printf("string error: %s\n", strerror(errno)); //bash does this!!

}
