#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <functional>
#include <cassert>
#include <numeric>
#include <cmath>
#include <type_traits>

using namespace std;


bool absLess(int a, int b) { 
    return abs(a) < abs(b); 
}
struct Nearest{
   int c;
   bool operator(int a, int b) {
     return abs(a-c) < abs(b-c);
   }  
};

std::vector<int> v = {2,34,2,13, -2, 32, -24}; 
// function pointer
std::sort(v.begin(), v.end(), absLess);  

// class with operator()
std::sort(v.begin(), v.end(), Nearest{4});

// lambda expression
std::sort(v.begin(), v.end(),
   [](int a, int b){ return a > b; }    
);

