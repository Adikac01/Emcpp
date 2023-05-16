#include <iostream>
#define SQR(a) a*a
int main(){
   int a = 2;
   int b = 3;
   int c = SQR((b+a));
   std::cout << c;
   return c;
}