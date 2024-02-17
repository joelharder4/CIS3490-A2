/* CIS*3490 Assignment 2
 * File:       P22.c
 * Name:       Joel Harder
 * Student ID: 1191485
 * Date:       Feb 14, 2023
*/

#include <stdio.h>
#include <time.h>
#include <math.h>

#define N_NUMBERS 30000
#define PI 3.14159

typedef struct coords {
    double x;
    double y;
} Coord;


void readFile(char *fileName, Coord* array);
void findHull(Coord* arr, int len, Coord p1, Coord p2, Coord* extremes, int* nExtremes);
void quickHull(Coord* arr, int len);


int main() {
    Coord array[N_NUMBERS];

    readFile("data_A2_Q2.txt", array);

    quickHull( array, N_NUMBERS-1);

    return 0;
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
        //printf("distance for path x = %lf  -->  x = %lf   is %lf\n", (arr[cur]).x, (arr[next]).x, sqrt( pow(arr[next].x - arr[cur].x, 2.0) + pow(arr[next].y - arr[cur].y, 2.0)));
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

    printf("\nhere are all of the extreme points:\n");
    for(int i = 0; i < len; i++) {
        printf("%d: x = %lf   y = %lf\n", i, sorted[i].x, sorted[i].y);
    }

    Coord s1;
    Coord s2;
    getPoints(&s1, &s2);
    printShortestPath(sorted, len, s1, s2);
}









/// @brief recursively finds the farthest point on the left hand side, makes 2 new lines and repeats
/// @param arr the array of all points to look at
/// @param len the length of arr
/// @param p1 the point where the line segment starts
/// @param p2 the point where the line segment ends
/// @param extremes an array of all of the extreme points found so far
/// @param nExtremes the number of extreme points (length of extremes)
void findHull(Coord* arr, int len, Coord p1, Coord p2, Coord* extremes, int* nExtremes) {

    if (len == 0) {
        return;
    }

    Coord S1[len];
    Coord S2[len];
    Coord farthest = arr[0];
    double dist, side1, side2;
    double farthestDist = -9999;
    double x1, x2, x3;
    double y1, y2, y3;
    int count1 = 0;
    int count2 = 0;


    // find the farthest point
    for (int i = 0; i < len; i++) {
        x1 = p1.x;
        x2 = p2.x;
        x3 = arr[i].x;
        y1 = p1.y;
        y2 = p2.y;
        y3 = arr[i].y;

        // x1y2 + x3y1 + x2y3 − x3y2 − x2y1 − x1y3
        dist = (x1*y2) + (x3*y1) + (x2*y3) - (x3*y2) - (x2*y1) - (x1*y3);
        
        if (dist > farthestDist) {
            //printf("dist: %lf\n", dist);
            farthestDist = dist;
            farthest = arr[i];
        }
    }

    // Add point C to convex hull at the location between p1 and p2
    printf("found extreme point (%.2lf, %.2lf)\n", farthest.x, farthest.y);
    extremes[(*nExtremes)] = farthest;
    (*nExtremes)++;

    // populate array S1 with all points to the left of line p1->farthest
    // and array S2 with all points to the left of line farthest->p2
    for (int i = 0; i < len; i++) {
        side1 = ((arr[i].x - p1.x) * (farthest.y - p1.y)) - ((arr[i].y - p1.y) * (farthest.x - p1.x));
        side2 = ((arr[i].x - farthest.x) * (p2.y - farthest.y)) - ((arr[i].y - farthest.y) * (p2.x - farthest.x));

        // if it is on the left side
        if ( side1 < 0 ) {
            S1[count1] = arr[i];
            count1++;
        }

        if (side2 < 0) {
            S2[count2] = arr[i];
            count2++;
        }

        // printf ("%d %d\n", side1 < 0, side2 < 0);
    }

    // printf("count1: %d  (%.2lf, %.2lf)  (%.2lf, %.2lf)\n", count1, p1.x, p1.y, farthest.x, farthest.y);
    findHull(S1, count1, p1, farthest, extremes, nExtremes);

    //printf("count2: %d  (%.2lf, %.2lf)  (%.2lf, %.2lf)\n\n", count2, farthest.x, farthest.y, p2.x, p2.y);
    findHull(S2, count2, farthest, p2, extremes, nExtremes);
}






/// @brief finds the extreme points in a convex hull using divide and conquer
/// @param arr the array of all coordinates in the data set
/// @param len the length of arr
void quickHull(Coord* arr, int len) {

    struct timespec ts;
    timespec_get(&ts, TIME_UTC);
    long start = ts.tv_nsec;
    
    Coord left[len];
    Coord right[len];
    Coord extremes[len];
    int nExtremes = 0;
    int countL = 0;
    int countR = 0;
    double dist;

    Coord min, max;
    min.x = 9999;
    min.y = 0;
    max.x = 0;
    max.y = 0;

    // find left and right most points (min & max)
    for (int i = 0; i < len; i++) {
        if (arr[i].x > max.x) {
            max = arr[i];
        }
        if (arr[i].x < min.x) {
            min = arr[i];
        }
    }

    // split the array into top and bottom
    for (int i = 0; i < len; i++) {
        dist = ((arr[i].x - min.x) * (max.y - min.y)) - ((arr[i].y - min.y) * (max.x - min.x));

        // if it is on the left side
        if ( dist < 0 ) {
            left[countL] = arr[i];
            countL++;
        } else if (dist > 0) { // if it is on the right side
            right[countR] = arr[i];
            countR++;
        }
    }

    //printf("upper: %d   lower: %d\n", countL, countR);
    
    extremes[0] = max;
    extremes[1] = min;
    nExtremes = 2;

    findHull(left, countL, min, max, extremes, &nExtremes);
    findHull(right, countR, max, min, extremes, &nExtremes);

    printf("\nThere are %d extreme points\n", nExtremes);

    timespec_get(&ts, TIME_UTC);
    long end = ts.tv_nsec;
    double t = (end - start);
    printf("this took %.5lf seconds\n", t/1000000000.0);

    sortClockwise(extremes, nExtremes);
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