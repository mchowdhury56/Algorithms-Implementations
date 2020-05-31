/*******************************************************************************
 * Name        : sieve.cpp
 * Author      : Marjan Chowdhury
 * Description : Sieve of Eratosthenes
 ******************************************************************************/
#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>

using namespace std;

class PrimesSieve {
public:
    PrimesSieve(int limit);

    ~PrimesSieve() {
        delete [] is_prime_;
    }

    int num_primes() const {
        return num_primes_;
    }

    void display_primes() const;

    int get_max_prime();

private:
    // Instance variables
    bool * const is_prime_;
    const int limit_;
    int num_primes_, max_prime_;

    // Method declarations
    int count_num_primes() const;
    void sieve();
    static int num_digits(int num);
};

PrimesSieve::PrimesSieve(int limit) :
      is_prime_{new bool[limit + 1]}, limit_{limit} {
        is_prime_[0]=false;
        is_prime_[1]=false;
        for(int i= 2; i <= limit_; i++){
            is_prime_[i]=true;
        }
        sieve();
        max_prime_ = get_max_prime();
}

void PrimesSieve::display_primes() const {
    // TODO: write code to display the primes in the format specified in the
    // requirements document.
    cout << endl;
    cout << "Number of primes found: " << num_primes_ << endl;
    cout << "Primes up to " <<limit_<< ":";
    const int max_prime_width = num_digits(max_prime_); 
    const int primes_per_row = 80 / (max_prime_width +1);
    // in the case that we only need to output one line, spacing does not need to
    // be constant and we can just print once space per item
    // else, have constant spacing such that the largest numbers have one space between them.
    if (num_primes_ <= primes_per_row){ // the case that we print one line
        cout << endl << "2";
        for (int this_prime = 3; this_prime < limit_; this_prime++){
            while (!is_prime_[this_prime] && this_prime <= limit_){
                this_prime++;
            }
            if (is_prime_[this_prime]){
                cout << " " << this_prime++;
            }
        }
    } else { // the case we print more than one line
        int primes_printed = 0;
        for (int i = 2; i <= limit_; i++){
            if(is_prime_[i]){
                if (primes_printed++ % primes_per_row == 0){
                    cout << endl;
                } else {
                    cout << " ";
                }
                cout << setw(max_prime_width) << i;
            }
        }
    }
}

int PrimesSieve::count_num_primes() const {
    // TODO: write code to count the number of primes found
    int count = 0;
    for(int i =0; i<= limit_ ; i++){
        if(is_prime_[i]){
            count++;
        }
    }
    return count;
}

void PrimesSieve::sieve() {
    // TODO: write sieve algorithm
    for(int i = 2; i <= sqrt(limit_); i++ ){
        if(is_prime_[i]){
            for(int j = i*i; j <= limit_; j += i){
                is_prime_[j] = false;
            }
        }
    }
    num_primes_ = count_num_primes();
    

}

int PrimesSieve::get_max_prime() {
    // Assigns the max prime number to the max_prime_ variable
    int max_prime = 0;
    for(int i = 0; i<= limit_ ; i++){
        if(is_prime_[i]){
            max_prime = i;
        }
    }
    return max_prime;

}

int PrimesSieve::num_digits(int num) {
    // TODO: write code to determine how many digits are in an integer
    // Hint: No strings are needed. Keep dividing by 10.
    int count = 1;
    while(num >= 10){
        count++;
        num = floor(num/10);
    }
    return count;
}

int main() {
    cout << "**************************** " <<  "Sieve of Eratosthenes" <<
            " ****************************" << endl;
    cout << "Search for primes up to: ";
    string limit_str;
    cin >> limit_str;
    int limit;

    // Use stringstream for conversion. Don't forget to #include <sstream>
    istringstream iss(limit_str);
    // Check for error.
    if ( !(iss >> limit) ) {
        cerr << "Error: Input is not an integer." << endl;
        return 1;
    }
    if (limit < 2) {
        cerr << "Error: Input must be an integer >= 2." << endl;
        return 1;
    }
    // TODO: write code that uses your class to produce the desired output.
    PrimesSieve sieve(limit);
    sieve.display_primes();
    return 0;
}
