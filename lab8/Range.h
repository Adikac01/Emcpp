#ifndef LAB6_RANGE_H
#define LAB6_RANGE_H

#include <iterator>

template <typename T>
class Range{
   T start;
   T stop;
   T step;

public:
   Range(T _start, T _stop, T _step) : start(_start) , stop(_stop), step(_step) {}

   Range(T _stop) : start(0), stop(_stop), step(1) {}

   Range(T _start, T _stop): start(_start), stop(_stop), step(1) {}

   class Iterator {
      T current;
      T step;
      
   public:
        using iterator_category = std::input_iterator_tag;
        using value_type = T;
        using difference_type = T;
        using pointer = T*;
        using reference = T&;
      Iterator(T _current, T _step) : current(_current), step(_step) {}

      Iterator& operator++(){
         current += step;
         return *this;
      }

      Iterator operator++(int) {
         Iterator temp = *this;
         ++(*this);
         return temp;
      }

      bool operator==(const Iterator& other) const {
         return current == other.current;
      }
      
      bool operator!=(const Iterator& other) const {
          if (step > 0)
            return current < other.current;
         else
            return current > other.current;
      }

      T operator*() const{
         return current;
      }
   };
   Iterator begin() const {
      return Iterator(start, step);
   }
   Iterator end() const {
      return Iterator(stop, step);
   }
};

template<typename T>
Range<T> make_range(T stop){
   return Range<T>(0,stop);
}

template<typename T>
Range<T> make_range(T start, T stop, T step = 1){
   return Range<T>(start,stop,step);
}


#endif //LAB6_RANGE_H
