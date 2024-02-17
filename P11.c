/* CIS*3490 Assignment 2
 * File:       P11.c
 * Name:       Joel Harder
 * Student ID: 1191485
 * Date:       Feb 14, 2023
*/

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

#define N_NUMBERS 50000
#define BUFFSIZE 256

int bruteInversions(int[]);
void getFileName(char* buffer);
void readFile(char*, int*);


int main() {
    char* fileName = malloc(sizeof(char) * BUFFSIZE);
    int array[N_NUMBERS] = {0};
    int inversions;

    getFileName(fileName);
    readFile(fileName, array);

    struct timespec ts;
    timespec_get(&ts, TIME_UTC);
    long start = ts.tv_sec;

    inversions = bruteInversions(array);
    printf("there are %d inversions\n", inversions);

    timespec_get(&ts, TIME_UTC);
    long end = ts.tv_sec;
    printf("this took %ld seconds\n", end - start);

    free(fileName);
    return 0;
}



/// @brief calculates the number of inversions in an array
/// @param arr the array to count inversions from
/// @return an integer of how many inversions are in the array
int bruteInversions(int arr[N_NUMBERS]) {
    int count = 0;

    for (int j = 1; j < N_NUMBERS; j++) {
        for (int i = 0; i < j; i++) {
            if (arr[i] > arr[j]) {
                count++;
            }
        }
    }

    return count;
}



/// @brief reads integers from a file into an array
/// @param fileName the name of the file to read from
/// @param array the array to read the numbers into
void readFile(char *fileName, int* array) {
    FILE* fp = fopen(fileName, "r");
    int i = 0;

    while ( !feof(fp) ) {
        fscanf(fp, "%d %d %d %d %d\n", &(array[i]), &(array[i+1]), &(array[i+2]), &(array[i+3]), &(array[i+4]));
        //printf("%d\n", array[i]);
        i += 5;
    }

    fclose(fp);
}





/// @brief prompts for a filename and reads it into a string
/// @param buffer the string to read the fileName into
void getFileName(char* buffer) {    
    printf("Enter the file name below and press enter\n");
    
    int length = read(STDIN_FILENO, buffer, BUFFSIZE);
    printf("\n");

    //printf("your input: %s\n", buffer); // debug

    // if the buffer did not run out of room
    if (length < BUFFSIZE && length > 0) {
        buffer[strlen(buffer) - 1] = '\0';
    } else {
        fprintf(stderr, "File name is invalid. Please try again.\n\n");
        getFileName(buffer);
    }
}
