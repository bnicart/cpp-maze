/*
 * 
 * The prime factors of 13195 are 5, 7, 13 and 29.
 *
 * What is the largest prime factor of the number 600851475143 ?
 */

#include "iostream"

bool isPrime(unsigned long n) {

  if ( n <= 3) { return n > 1; }
  else if ( n % 2 == 0 || n % 3 == 0 ) { return false; }
  else { 
    for (unsigned short i = 5 ; i*i <= n ; i += 6 ) {
      if ( n % i == 0 || n % (i+2) == 0 ) { return false; }
    }
    return true;
  }

}

int main() {

  unsigned long long int number = 0, factor = 0;
  number = 600851475143;

  for( factor = 2 ; factor < number ; factor++ ) {
    if( number % factor == 0 && isPrime(factor)) {
      std::cout << factor << ",";
    }
  }

  return 0;
}
