/*
 * Keep track of the elapsed time for kind sorting algorithms on randomly
 * chosen vector.Display a table of the observed running times for a predefined
 * set of sizes.
 */
#include <iostream>
#include "console.h"
#include "gwindow.h" // for GWindow
#include "simpio.h"  // for getLine
#include "vector.h"  // for Vector
#include <ctime>// for clock
#include "random.h"// for randomInteger
#include "iomanip"
using namespace std;

//global constants
const int INPUT_SIZES[] = {1000, 10000, 100000};
const int SIZES = sizeof INPUT_SIZES / sizeof INPUT_SIZES[0];

//function prototypes
void insertionSort(Vector<int> &vec);
void initRandomVec(Vector<int> &vec, int size);
void quickSort(Vector<int> &vec, int start, int end);
int partition(Vector<int> &vec, int start, int end);
int main() {
    //record a list of observed running time with a set of specifed size
    Vector<double> elapsedTime;


    for(int i=0; i<SIZES; i++) {
        Vector<int> vec;
        //initialize a vector
        initRandomVec(vec, INPUT_SIZES[i]);

        //sort the vector
        double start = double(clock()) / CLOCKS_PER_SEC;// CPU clock cycles / (clock cycle / second) = seconds

        quickSort(vec, 0, vec.size()-1);
        double end = double(clock()) / CLOCKS_PER_SEC;
        double elapsed = end - start;//compute the elapsed time
        elapsedTime.add(elapsed);
    }

    //display a table of observed running time
    cout << "    N    " << "|  Time (msec)  " << endl;
    for(int i=0; i<SIZES; i++) {
        cout << right << setw(7) << INPUT_SIZES[i] << "  |"
             << setw(10) << elapsedTime[i] << endl;
    }


    return 0;
}
void insertionSort(Vector<int> &vec) {

    for(int j=1; j<vec.size(); j++) {
        int key = vec[j];

        int i=j-1;
        while(i>=0 && key < vec[i]) {
            vec[i+1] = vec[i];
            i--;
        }

        vec[i+1] = key;
    }
}

/**
 * Get a random vector with a specified size.
 */
void initRandomVec(Vector<int> &vec, int size) {
    //get a list of random elements
    for(int i=0; i<size; i++) {
        vec.add(randomInteger(0, 9999));
    }
}

void quickSort(Vector<int> &vec, int start, int end) {
    if(start >= end) return;
    else {
        int boundary = partition(vec, start, end);
        quickSort(vec, start, boundary - 1);
        quickSort(vec, boundary + 1, end);
    }
}

int partition(Vector<int> &vec, int start, int end) {
    int pivot = vec[start];
    int lh = start + 1;
    int rh = end;

    while(true) {//doesn't conincidence
        while(lh<rh && vec[rh] > pivot) rh--;
        while(lh<rh && vec[rh] <= pivot) lh++;
        if(lh == rh) break;
        //swap the elements
        int tmp = vec[rh];
        vec[rh] = vec[lh];
        vec[lh] = tmp;
    }
    if(pivot<=vec[lh]) return start;
    //homing the pivot
    vec[start] = vec[lh];
    vec[lh] = pivot;
    return lh;
}
