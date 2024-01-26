//John Dufresne
//Assignment 1: Find primes from 1 to 10^8, spawn upon 8 threads

#include <iostream>
#include <fstream>
#include <format>
#include <vector> 
#include <thread> 
#include <mutex> // Locks
#include <chrono> // time in seconds
#include <algorithm> //sort

using namespace std;

const int MAX = 100000000; // 10^8
const int NUM_THREADS = 8;
mutex mu; //object for lock
int totalPrimeCount = 0; //holds count for number of primes
long long totalPrimeSum = 0; //holds count for sum of primes

// Returns true if number is prime, false if not
bool isPrime(int num) {
    if (num <= 1) return false;
    else{
        for (int i = 2; i * i <= num; i++) {
            if (num % i == 0) return false;
        }
        return true;
    }
}

void findPrimes(int start, int end) {
    int primeCount = 0;
    long long primeSum = 0;
    for (int i = start; i <= end; i+=8) {
        if (isPrime(i)) {
            primeCount++;
            primeSum += i;
        }
    }
    mu.lock(); //Issue lock so no other thread can access our total variables
    totalPrimeCount += primeCount;
    totalPrimeSum += primeSum;
    mu.unlock(); //Unlock
}

int main() {
    //Vector holding our 8 threads
    vector<thread> threads;
    
    //start timer
    auto start_timer = chrono::high_resolution_clock::now(); 

    for(int i = 1; i <= NUM_THREADS; ++i){
        threads.push_back(thread(findPrimes, i, MAX));
    }

    //Join threads 
    for (auto& th : threads) {
        th.join();
    }

    //End timer, find total, and convert to seconds
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end - start_timer;

    //Write results to output.txt
    ofstream outFile("output.txt");
    outFile << format("<{} seconds> <{} primes> <{}>", duration.count(), totalPrimeCount, totalPrimeSum);

    return 0;
}
