/* CIS*3490 Assignment 2
 * File:       P12.c
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
#include <math.h>

#define N_NUMBERS 50000
#define BUFFSIZE 256

int fastInversions(int[N_NUMBERS], int, int);
void getFileName(char* buffer);
void readFile(char*, int*);
void copyArray(int* src, int* dest, int start, int end);





/// @brief merges the left and right sub-arrays of arr
/// @param arr the entire array of all integers that is being sorted
/// @param left the index of the left-most element to merge
/// @param mid the index of the middle element to merge
/// @param right the index of the right-most element to merge
/// @return an integer of the number of inversions that took place in the merge
int merge(int arr[], int left, int mid, int right) {
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;
    int inversions = 0;

    int arrL[n1], arrR[n2];
 
    for (i = 0; i < n1; i++) {
        arrL[i] = arr[left + i];
    }
        
    for (j = 0; j < n2; j++) {
        arrR[j] = arr[mid + j + 1];
    }
    
    i = 0;
    j = 0;
    k = left;

    while (i < n1 && j < n2) {
        if (arrL[i] <= arrR[j]) {
            arr[k] = arrL[i];
            i++;
        }
        else {
            arr[k] = arrR[j];
            inversions += (n1 - i);
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = arrL[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = arrR[j];
        j++;
        k++;
    }

    return inversions;
}
 
/// @brief sorts the given array using divide and conquer and counts inversions
/// @param arr the entire array to be sorted
/// @param left the left-most index of the current split
/// @param right the right-most index of the current split
/// @return an integer of the number of inversions in the array
int mergeSort(int arr[], int left, int right) {   
    int mid;
    int inversions = 0;
    if (left < right) {
        mid = left + (right - left) / 2;

        inversions += mergeSort(arr, left, mid);
        inversions += mergeSort(arr, mid + 1, right);
 
        inversions += merge(arr, left, mid, right);
    }
    return inversions;
}






int main() {
    char* fileName = malloc(sizeof(char) * BUFFSIZE);
    int array[N_NUMBERS] = {0};
    int inversions = 0;

    //fileName = "data_A2_Q1.txt";
    getFileName(fileName);
    
    struct timespec ts;
    timespec_get(&ts, TIME_UTC);
    long start = ts.tv_nsec;

    readFile(fileName, array);

    inversions = mergeSort(array, 0, N_NUMBERS-1);
    printf("there are %d inversions\n", inversions);

    timespec_get(&ts, TIME_UTC);
    long end = ts.tv_nsec;
    double t = (end - start);
    printf("this took %.5lf seconds\n", t/1000000000);

    free(fileName);
    return 0;
}




/// @brief reads integers from a file into an array
/// @param fileName the name of the file to read from
/// @param array the array to read the numbers into
void readFile(char *fileName, int* array) {
    FILE* fp = fopen(fileName, "r");
    int i = 0;

    while ( !feof(fp) ) {
        fscanf(fp, "%d %d %d %d %d\n", &(array[i]), &(array[i+1]), &(array[i+2]), &(array[i+3]), &(array[i+4]));
        //printf("%d\n", array[i]); // debug
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

    // if the buffer did not run out of room
    if (length < BUFFSIZE && length > 0) {
        buffer[strlen(buffer) - 1] = '\0';
    } else {
        fprintf(stderr, "File name is invalid. Please try again.\n\n");
        getFileName(buffer);
    }
}

