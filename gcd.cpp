/*******************************************************************************
 * Name    : gcd.cpp
 * Author  : Marjan Chowdhury
 * Description : Computes the GCD of two command-line arguments.
 ******************************************************************************/
#include <iostream>
#include <sstream>
#include <algorithm>

using namespace std;

int gcd_iterative(int m, int n){
    if (m < 0){
        m = abs(m);
    }
    if (n < 0){
        n = abs(n);
    }
    if (n==0){
        return (m);
    }
    while(m != n){
        if(m > n){
            m -= n;
        }else{
            n -= m;
        }
    }
    return (m);
}
int gcd_recursive(int m, int n){
    if (m < 0){
        m = abs(m);
    }
    if (n < 0){
        n = abs(n);
    }if (n==0){
        return (m);
    }
    if (m%n == 0){
        return (n);
    }
    return gcd_recursive(n, m%n);

}

int main(int argc, char* const argv[]) {
    int m, n;
    istringstream iss;

    if (argc != 3) {
        cerr << "Usage: " << argv[0] << " <integer m> <integer n>"
             << endl;
        return 1;
    }
    iss.str(argv[1]);
    if ( !(iss >> m) ) {
        cerr << "Error: The first argument is not a valid integer."
             << endl;
        return 1;
    }
    iss.clear(); // clear the error code
    iss.str(argv[2]);
    if ( !(iss >> n) ) {
        cerr << "Error: The second argument is not a valid integer."
             << endl;
        return 1;
    }

    cout << "Iterative: gcd(" << m << ", "<< n <<") = "   << gcd_iterative(m,n) << endl;
    cout << "Recursive: gcd(" << m << ", "<< n <<") = "   << gcd_recursive(m,n) << endl;
    return 0;
}
