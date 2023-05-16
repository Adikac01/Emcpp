#include <iostream>

class InitPolicy {
public:
   template<typename T>
   static void init(T v[], size_t N){
      for(size_t i = 0; i < N; i++){
         v[i] = 0;
      }
   }
};

class SafePolicy : public InitPolicy{
   class VectorException : public std::runtime_error {
      public:
         VectorException(const char* msg) : runtime_error(msg) {}
         VectorException(std::string& msg) : runtime_error(msg) {}
   };

   public:
      static void checkIndex(size_t n, size_t N){
         if(n >= N){
            throw VectorException("Index out of bounds");
         }
      }
};

class FastPolicy{
   public:
      template<typename T>
      static void init(T [], size_t){}
      static void checkIndex(size_t, size_t) {}
};

class InitFastPolicy : public InitPolicy, public FastPolicy {
   public:
      using InitPolicy::init;
};