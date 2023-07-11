/**************************************************************************************************/
// Test File for PP0
// Requires the Catch2 header file
// How to compile: g++ -std=c++17 -Wall -I$(CATCH_SINGLE_INCLUDE) (All cpp files)
// Example if Catch 2 is in the same directory as project: 
//    Example: g++ -std=c++17 -Wall example_code.cpp PP0Test.cpp
// To see what tests were successful and failed, run your executable with the -s flag
//    Example: a.out -s
// A successful test should output: All tests passed (5 assertions in 1 test case)
/**************************************************************************************************/

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "example_code.hpp"

TEST_CASE( "Factorials are computed") {
  REQUIRE( factorial(0) == 1 );
  REQUIRE( factorial(1) == 1 );
  REQUIRE( factorial(2) ==  2 );
  REQUIRE( factorial(3) == 6 );
  REQUIRE( factorial(10) == 3628800 );
}