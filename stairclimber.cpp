/*******************************************************************************
 * Name        : stairclimber.cpp
 * Author      : Marjan Chowdhury
 * Description : Lists the number of ways to climb n stairs using brute force.
 ******************************************************************************/
#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iomanip>
#include <cmath>

using namespace std;

vector< vector<int> > get_ways(int num_stairs) {
    // TODO: Return a vector of vectors of ints representing
    // the different combinations of ways to climb num_stairs
    // stairs, moving up either 1, 2, or 3 stairs at a time.
    vector< vector<int> > ways;
    if(num_stairs <= 0 ){
        vector<int> empty;
        ways.push_back(empty);
    }else{
        for(int i = 1; i < 4; i++){
            if(num_stairs >= i ){
                vector< vector<int> > result = get_ways(num_stairs - i);
                for(auto pointer = result.begin(); pointer != result.end(); pointer++){
                    pointer -> insert(pointer -> begin(),i);
                }
                ways.insert(ways.end(), result.begin(), result.end());
            }  
        }
    }
    return ways;




}
int num_digits(int num) {
    // TODO: write code to determine how many digits are in an integer
    // Hint: No strings are needed. Keep dividing by 10.
    int count = 1;
    while(num >= 10){
        count++;
        num = floor(num/10);
    }
    return count;
}
void display_ways(const vector< vector<int> > &ways) {
    // TODO: Display the ways to climb stairs by iterating over
    // the vector of vectors and printing each combination.
    const int size = ways.size();
    cout << endl;
    int max_width = num_digits(size);

    for(unsigned int i = 0; i < ways.size(); i++){
        cout << setw(max_width) << i+1 << ". [";
        for(unsigned int j = 0; j < ways[i].size(); j++){
            if(j == ways[i].size() - 1){
                cout << ways.at(i).at(j) << "]" <<endl;
            }else{
                cout << ways.at(i).at(j) <<", ";
            }
        }
    }
}


int main(int argc, char * const argv[]) {
    int m;
    istringstream iss;
    if(argc != 2){
        cout << "Usage: " << argv[0] << " <number of stairs>" << endl;
        return 1;
    }
    iss.str(argv[1]);
    if ( !(iss >> m) ) {
        cerr << "Error: Number of stairs must be a positive integer."
             << endl;
        return 1;
    }
    if(m <= 0 ){
        cout << "Error: Number of stairs must be a positive integer." << endl;
        return 1;
    }

    vector< vector<int> > ways = get_ways(m);
    if(ways.size() == 1){
        cout << ways.size() << " way to climb " << m << " stair.";
    }else{
        cout << ways.size() << " ways to climb " << m << " stairs.";
    }
    display_ways(ways);
    return 0;
}
