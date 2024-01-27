# COP4520-Assignment-1
Using 8 threads to quickly and efficiently find all the primes and the sum of all primes up to 100 million.

## How to run
```command
g++ assignment1.cpp -o assignment1 -std=c++20
./assignment1
```
- Since I submitted the executable file for my C++ source code you don't need to run the first command, however, I thought i'd inlcude it anyway. The second command runs executeable file.

### Code Summary
I began my approach by creating a vector to hold 8 threads which, to generate my threads I created a loop to run to 8, assigning each thread to start from that index in the loop and end at 100,000,000. For my findPrimes function I had each thread start a loop starting from the start parameter and running until it is less than or equal to the end parameter, in which each thread will lock and increment the sum and total prime variables then unlock, if the number is prime, ensuring mutual exclusion. In order to maintain an equivalent run time amongst threads, I have each thread increment from 8, that way each thread is executing within at most 8 digits from other threads. This is crucial to satisfy the condition that each thread must have equivalent execution times. Since a thread running primes from 1-1000 will take significantly less time to run than finding primes from 10,000,000 to 11,000,000, my method ensures these numbers will execute numbers somewhat equivalent in size, therefore making each threads runtime somewhat equivalent.
