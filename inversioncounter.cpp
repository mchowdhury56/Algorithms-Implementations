/*******************************************************************************
 * Name        : inversioncounter.cpp
 * Author      : Marjan Chowdhury
 * Description : Counts the number of inversions in an array 
 *               using two different implementations.
 ******************************************************************************/
#include <iostream>
#include <algorithm>
#include <sstream>
#include <vector>
#include <cstdio>
#include <cctype>
#include <cstring>

using namespace std;

// Function prototype.
static long mergesort(int array[], int scratch[], int low, int high);

/**
 * Counts the number of inversions in an array in theta(n^2) time.
 */
long count_inversions_slow(int array[], int length) {
    
    long count = 0;
    for(int current = 0; current < length; ++current){
        for(int next = current + 1; next < length; ++next){
            if(array[current] > array[next]){
                ++count;
            }
        } 
    }
    return count;

}

/**
 * Counts the number of inversions in an array in theta(n lg n) time.
 */
long count_inversions_fast(int array[], int length) {
    int *scratch = new int[length];
    long inversions = mergesort(array, scratch, 0, length -1);
    delete[] scratch;
    return inversions;
}

static long mergesort(int array[], int scratch[], int low, int high) {
    long count = 0;
    
    if(low < high){
        int mid = low + (high - low) / 2;
        count += mergesort(array, scratch, low, mid);
        count += mergesort(array, scratch, mid + 1, high);
        int l = low;
        int h = mid+1;
        for(int i = low; i <= high; ++i ){
            if(l <= mid && (h > high || array[l] <= array[h]) ){
                scratch[i] = array[l];
                ++l; 
            }else{
                scratch[i] = array[h];
                ++h;
                count += mid +1 -l;
            }
        }
        for(int j = low; j <= high; ++j){
            array[j] = scratch[j];
        }
    }
    
    return count;
}

int[] mergesort(int array[], int scratch[], int low, int high){
    if (low < high){
        int mid = low + (high - low) / 2;
        mergesort(array, scratch, low, mid);
        mergesort(array, scratch, mid + 1, high);
        int l = low;
        int h = mid + 1;
        for (int i = low; i <= high; ++i){
            if (l <= mid && (h > high || array[l] <= array[h])){
                scratch[i] = array[l];
                ++l;
            }else{
                scratch[i] = array[h];
                ++h;
            }
        }
        for (int j = low; j <= high; ++j){
            array[j] = scratch[j];
        }
    }
    return array;
}

int main(int argc, char *argv[]) {

    bool slow = false;
    if (argc > 1){
        istringstream input;
        input.str(argv[1]);
        string arg2;
        if (argc >= 3){
            cerr << "Usage: ./inversioncounter [slow]" << endl;
            return 1;
        }
        else if (!(input >> arg2) || (argc == 2 && arg2 != "slow")){
            cerr << "Error: Unrecognized option '" << arg2 << "'." << endl;
            return 1;
        }
        slow = true;
    }

    cout << "Enter sequence of integers, each followed by a space: " << flush;

    istringstream iss;
    int value, index = 0;
    vector<int> values;
    string str;
    str.reserve(11);
    char c;
    while (true) {
        c = getchar();
        const bool eoln = c == '\r' || c == '\n';
        if (isspace(c) || eoln) {
            if (str.length() > 0) {
                iss.str(str);
                if (iss >> value) {
                    values.push_back(value);
                } else {
                    cerr << "Error: Non-integer value '" << str
                         << "' received at index " << index << "." << endl;
                    return 1;
                }
                iss.clear();
                ++index;
            }
            if (eoln) {
                break;
            }
            str.clear();
        } else {
            str += c;
        }
    }
    
    if(values.empty()){
        cerr << "Error: Sequence of integers not received." << endl;
        return 1;
    }

    long result;
    if (slow){
        result = count_inversions_slow(&values[0], values.size());
    }
    else{
        result = count_inversions_fast(&values[0], values.size());
    }
    cout << "Number of inversions: " << result << endl;

    return 0;
}
