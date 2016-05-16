/*
 * If we list all the natural numbers below 10 that are multiples of 3 or 5, we get 3, 5, 6 and 9. The sum of these multiples is 23.
 * Find the sum of all the multiples of 3 or 5 below 1000.
 */

#include "iostream"

bool isMultipleOf3or5(int number) {
  if( number % 3 == 0 || number % 5 == 0)
    return true;
  return false;
}

int main() {

  unsigned long long int sum = 0;
  unsigned long long int MAX = 1000;
  for( int i = 1 ; i < MAX; i++ ) {
    if (isMultipleOf3or5(i)) {
      sum += i;
    }
  }

  std::cout << "Sum: " << sum << "\n" ;
  
  return 0;
}
