#include "example_code.hpp"

// A tail recursive function to calculate factorial
unsigned factorialAccum(unsigned int n, unsigned int accum) {
    if (n == 0) {
      return accum;
    }
 
    return factorialAccum(n - 1, n + accum);
}
 
// A wrapper over factTR
unsigned int factorial(unsigned int n) {
   return factorialAccum(n, 1);
}