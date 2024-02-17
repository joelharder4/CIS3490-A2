/* CIS*3490 Assignment 2
 * File:       P21.c
 * Name:       Joel Harder
 * Student ID: 1191485
 * Date:       Feb 14, 2023
*/

#include <stdio.h>
#include <time.h>
#include <math.h>

#define N_NUMBERS 30000
#define PI 3.14159
#define BUFFSIZE 256

typedef struct coords {
    double x;
    double y;
} Coord;



void bruteForceHull(Coord*, int);
void getFileName(char* buffer);
void readFile(char*, Coord*);
int appendCoord(Coord*, Coord, int);
void printShortestPath(Coord*, int, Coord, Coord);



int main() {
    Coord array[N_NUMBERS];
    char* fileName = malloc(sizeof(char) * BUFFSIZE);

    getFileName(fileName);
    readFile(fileName, array);
    bruteForceHull( array, N_NUMBERS-1 );

    return 0;
}



/// @brief if a coordinate is not already in the array, it will be appended to the end
/// @param arr the array to append the Coord to
/// @param point the new point to be added
/// @param pos the length of the array
/// @return 1 if successfully added, 0 if it is already in the array
int appendCoord(Coord* arr, Coord point, int pos) {
    for (int i = 0; i < pos; i++) {
        if (arr[i].x == point.x && arr[i].y == point.y) {
            //printf("duplicate extreme point found\n");
            return 0;
        }
    }

    arr[pos] = point;
    printf("extreme point found. x = %lf  y = %lf\n", point.x, point.y);
    return 1;
}




/// @brief finds and prints the shortest path from s1 to s2 by traversing the array
/// @param arr the ordered array to trace the path through
/// @param len the length of arr
/// @param s1 the point to start from
/// @param s2 the point to end at
void printShortestPath(Coord* arr, int len, Coord s1, Coord s2) {
    int index1, index2;
    double clock = 0;
    double counterclock = 0;
    Coord pathcl[len];
    Coord pathccl[len];

    if (s1.x == s2.x && s1.y == s2.y) {
        printf("s1 and s2 are the same\n");
        return;
    }

    // find indexes of s1 and s2 in the sorted array
    for (int i = 0; i < len; i++) {
        if (arr[i].x == s1.x && arr[i].y == s1.y) {
            index1 = i;
        }
        if (arr[i].x == s2.x && arr[i].y == s2.y) {
            index2 = i;
        }
    }

    // check distance clockwise
    int cur = index1;
    int next;
    int i = 0;

    if (cur == len-1) {
        next = 0;
    } else {
        next = cur + 1;
    }

    while (cur != index2) {
        clock += sqrt( pow(arr[next].x - arr[cur].x, 2.0) + pow(arr[next].y - arr[cur].y, 2.0) );
        // printf("distance for path x = %lf  -->  x = %lf   is %lf\n", (arr[cur]).x, (arr[next]).x, sqrt( pow(arr[next].x - arr[cur].x, 2.0) + pow(arr[next].y - arr[cur].y, 2.0)));
        (pathcl[i]).x = (arr[cur]).x;
        (pathcl[i]).y = (arr[cur]).y;

        cur = next;
        if (next == len-1) {
            next = 0;
        } else {
            next++;
        }
        i++;
    }

    int j = 0;
    cur = index1;
    if (cur == 0) {
        next = len-1;
    } else {
        next = cur - 1;
    }

    // check distance counterclockwise
    while (cur != index2) {
        counterclock += sqrt( pow(arr[next].x - arr[cur].x, 2.0) + pow(arr[next].y - arr[cur].y, 2.0) );
        (pathccl[j]).x = (arr[cur]).x;
        (pathccl[j]).y = (arr[cur]).y;


        cur = next;
        if (next == 0) {
            next = len-1;
        } else {
            next--;
        }
        j++;
    }

    // printf("\ns1:  x = %lf    y = %lf\n", s1.x, s1.y);
    // printf("s2:  x = %lf    y = %lf\n", s2.x, s2.y);

    printf("\nThe fastest path from s1 to s2 is:\n"); 
    if (clock < counterclock) { // clockwise is faster
        for (int k = 0; k < i; k++) {
            printf("%d: x = %.3lf, y = %.3lf  -->  ", k+1, pathcl[k].x, pathcl[k].y);

            if (k < i-1) {
                printf("x = %.3lf, y = %.3lf\n", pathcl[k+1].x, pathcl[k+1].y);
            } else {
                printf("x = %.3lf, y = %.3lf\n", s2.x, s2.y);
            }
            
        }
        printf("The length of the path is %.2lf units\n", clock);
    } else { // counterclockwise is faster
        for (int k = 0; k < j; k++) {
            printf("%d: x = %.3lf, y = %.3lf  -->  ", k+1, pathccl[k].x, pathccl[k].y);

            if (k < j-1) {
                printf("x = %.3lf, y = %.3lf\n", pathccl[k+1].x, pathccl[k+1].y);
            } else {
                printf("x = %.3lf, y = %.3lf\n", s2.x, s2.y);
            }
        }
        printf("The length of the path is %.2lf units\n", counterclock);
    }
}



/// @brief prompt the user for inputs to get s1 and s2
/// @param s1 the point that the shortest path will start
/// @param s2 the point that the shortest path will end
void getPoints(Coord* s1, Coord* s2) {
    printf("enter the x value for s1: ");
    scanf("%lf", &(s1->x));

    printf("enter the y value for s1: ");
    scanf("%lf", &(s1->y));

    printf("enter the x value for s2: ");
    scanf("%lf", &(s2->x));

    printf("enter the y value for s2: ");
    scanf("%lf", &(s2->y));
}



/// @brief sorts a given array of points around an arbitruary point in clockwise order
/// @param arr an array of points to be sorted
/// @param len the length of arr
void sortClockwise(Coord* arr, int len) {
    Coord sorted[len];
    Coord pivot = arr[0];
    double angles[len];
    double min = 180;
    double prevMin = -180;
    int index = 0;

    for (int i = 0; i < len; i++) {
        //printf("angles[%d] = %lf    x = %lf     y = %lf\n", i, angles[i], arr[i].x, arr[i].y);
        angles[i] = atan2(arr[i].y - pivot.y, arr[i].x - pivot.x) * 180 / PI;
    }

    sorted[0] = arr[0];

    for (int i = 0; i < len; i++) {
        for (int j = 0; j < len; j++) {
            if (angles[j] < min && angles[j] > prevMin) {
                //printf("angles[%d] = %lf    min = %lf      prevMin = %lf\n", j, angles[j], min, prevMin);
                min = angles[j];
                index = j;
            }
        }

        sorted[i] = arr[index];
        prevMin = min;
        min = 180;
    }

    printf("\nhere is all of the extreme points:\n");
    for(int i = 0; i < len; i++) {
        printf("%d: x = %lf   y = %lf\n", i, sorted[i].x, sorted[i].y);
    }

    Coord s1;
    Coord s2;
    getPoints(&s1, &s2);
    printShortestPath(sorted, len, s1, s2);
}




/// @brief uses brute force to find all extreme points in a convex hull
/// @param arr the array of all points in the data set
/// @param len the length of arr
void bruteForceHull(Coord* arr, int len) {

    struct timespec ts;
    timespec_get(&ts, TIME_UTC);
    long start = ts.tv_sec;

    double dist1, dist2, dist3;
    double distFromLine;
    int below, above, skipi;
    Coord extreme[len];
    int count = 0;

    for (int i = 0; i < len; i++) {
        skipi = 0;
        for (int j = 0; j < len; j++) {
            if (j == i) {
                continue;
            }
            below = 0; // treat as boolean
            above = 0; // treat as boolean
            for (int k = 0; k < len; k++) {
                if (k == i || k == j) {
                    continue;
                }
                // calculate the distance that point k is from line i->j
                distFromLine = ((arr[k].x - arr[i].x) * (arr[j].y - arr[i].y)) - ((arr[k].y - arr[i].y) * (arr[j].x - arr[i].x));
                if (distFromLine < 0) {
                    below = 1;
                } else if (distFromLine > 0) {
                    above = 1;
                } else { // if distFromLine == 0
                    // this means the point lies exactly on the line
                    dist1 = sqrt( pow(arr[k].x - arr[i].x, 2.0) + pow(arr[k].y - arr[i].y, 2.0) );
                    dist2 = sqrt( pow(arr[j].x - arr[i].x, 2.0) + pow(arr[j].y - arr[i].y, 2.0) );
                    dist3 = sqrt( pow(arr[j].x - arr[k].x, 2.0) + pow(arr[j].y - arr[k].y, 2.0) );

                    if (dist1 < dist2 && dist3 < dist2) {
                        continue;
                    } else{
                        skipi = 1;
                        break;
                    }
                }

                // the line arr[i]->arr[j] is not part of convex hull
                if (below == 1 && above == 1) {
                    break;
                }
            }
            if ((below == 0 || above == 0) && skipi == 0 ) {
                count += appendCoord(extreme, arr[i], count);
            }
        }
    }

    printf("\nThere are %d extreme points\n", count);

    timespec_get(&ts, TIME_UTC);
    long end = ts.tv_sec;
    printf("this took %ld seconds\n", (end - start));

    sortClockwise(extreme, count);

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



/// @brief reads points from a file into an array
/// @param fileName the name of the file to read from
/// @param array the array to read the points into
void readFile(char *fileName, Coord* array) {
    FILE* fp = fopen(fileName, "r");
    int i = 0;

    while ( !feof(fp) ) {
        fscanf(fp, "%lf %lf \n", &(array[i].x), &(array[i].y));
        //printf("%lf %lf\n", array[i].x, array[i].y); // debug
        i++;
    }

    fclose(fp);
}