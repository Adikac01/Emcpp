
#ifndef STATIC_VECTOR_H
#define STATIC_VECTOR_H


#include <memory>
#include <iostream>
#include <cassert>
#include <vector>
#include <cmath>



template <typename T, size_t N>
class Vector{
    T data[N];

private:

   Vector(bool) {
      for(int i = 0; i < N; i++){
         data[i] = T(5);
      }
   }

public:
    typedef T value_type;
    typedef std::size_t  size_type;
    typedef T* pointer;
    typedef T& reference;
    typedef const T& const_reference;

    Vector() {
      for(int i = 0; i < N; i++){   
         data[i] = T();
      }
    }
    Vector(const Vector & v) {
      for(int i = 0; i < N; i++){
         data[i] = v[i];
      }
    }
   Vector &operator=(const Vector & m){
      for (size_type i = 0; i < N; i++) {
            data[i] = m[i];
        }
        return *this;
   }
   Vector(const std::initializer_list<T> &list){
        // auto l = list.begin();
        // for(int i = 0; i < N; i++){
        //     data[i] = *(l++);
        // }
        std::copy(list.begin(), list.end(), data);
   }

    friend Vector operator+ (const  Vector<T,N> & u, const Vector<T,N> & v ){
    Vector<T,N> result;
    for(int i = 0; i < N; i++){
        result[i] = u[i] + v[i];  
    }
    return result;
    }




    constexpr size_type size() const {
        return N;
    }

    const_reference get(size_type index) const {
        return data[index];
    }

    void set(size_type index, const_reference value) {
        data[index] = value;
    }

    reference operator[](size_type index){
        return data[index];
    }
    const_reference operator[](size_type index) const{
        return data[index];
    }

    friend std::ostream &operator<<(std::ostream &out, const Vector & v) {
        for( auto elem: v.data ){
            out << elem << " ";
        }
        return out;
    }
    
    template <typename S, size_t M>
    explicit operator Vector<S, M>() const
    {
        Vector<S, M> result;
        for (size_t i = 0; i < N; ++i)
        {
            result[i] = static_cast<S>(data[i]);
        }
        return result;
    }

    
    explicit operator Vector<T,0>() {
        Vector<T,0> result(N);
        for(int i = 0; i < N; i++){
            result[i] += data[i];
        }
        return result;
    }
    
};



#endif //STATIC_VECTOR_H