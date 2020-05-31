/*******************************************************************************
 * Name        : unique.cpp
 * Author      : Marjan Chowdhury
 * Description : Determining uniqueness of chars with int as bit vector.
 ******************************************************************************/
#include <iostream>
#include <cctype>

using namespace std;

bool is_all_lowercase(const string &s) {
    // TODO: returns true if all characters in string are lowercase
    // letters in the English alphabet; false otherwise.
    for(char c: s){
        if(isupper(c) || !isalpha(c)){
            return false;
        }
    }
    return true;
}

bool all_unique_letters(const string &s) {
    // TODO: returns true if all letters in string are unique, that is
    // no duplicates are found; false otherwise.
    // You may use only a single int for storage and work with bitwise
    // and bitshifting operators.
    // No credit will be given for other solutions.
    unsigned int x = 0;
    for(char c: s){
        int difference = c-'a';
        if(((1<< difference) & x )> 0){
            return false;
        }
        x |= (1<< difference);
    }
    return true;
}

int main(int argc, char * const argv[]) {
    // TODO: reads and parses command line arguments.
    // Calls other functions to produce correct output.
    if(argc != 2){
        cout << "Usage: " << argv[0] << " <string>" << endl;
        return 1;
    }

    if(!is_all_lowercase(argv[1])){
        cout << "Error: String must contain only lowercase letters." << endl;
        return 1;
    }

    if(!all_unique_letters(argv[1])){
        cout << "Duplicate letters found." << endl;
        return 0;
    }

    cout<< "All letters are unique." << endl;
    return 0;

}
