#ifndef DYNAMIC_VECTOR_H
#define DYNAMIC_VECTOR_H

#include <memory>
#include <iostream>
#include <stdexcept>

template<typename T, std::size_t N>
class Vector;

template<typename T>
class Vector<T,0>{

   std::unique_ptr<T[]> data;
   std::size_t sz;


public:

   typedef T value_type;
   typedef std::size_t size_type;
   typedef T* pointer;
   typedef T& reference;
   typedef const T& const_reference;


   Vector() : data(nullptr), sz(0) {}

   Vector(size_type newSize) : data(std::make_unique<T[]>(newSize)), sz(newSize) {

   };

   Vector(const Vector& other) : data(std::make_unique<T[]>(other.sz)),sz(other.sz){
      for(int i = 0; i < other.sz; i++){
         data[i] = other.data[i];
      }
   }

   Vector& operator=(const Vector& other) {
      if(this != other){
         data = make_unique<T[]>(other.sz);
         std::copy(other.data, other.data + other.sz, data);
      }
      return *this;
   }

   Vector(Vector&& other) : sz(other.sz) ,data(std::move(other.data)){}

   Vector& operator=(Vector&& other){
      if(this != other){
         sz = other.sz;
         data = std::move(other.data);
      }
      return *this;
   }

   Vector(const std::initializer_list<T>& list) : sz(list.size()) , data(make_unique<T[]>(list.size())){
      std::copy(list.begin(),list.end(),data.get());
   }

   ~Vector() = default;

   void resize(size_type newSize) {
        auto temp = std::make_unique<T[]>(newSize);
        auto last = std::copy(data.get(),data.get() + std::min(sz,newSize), temp.get());
        data = std::move(temp);
        sz = newSize;
    }

   constexpr std::size_t size() const {
      return sz;
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

    friend Vector operator+(const Vector& u, const Vector& v) {
       if(v.size() != u.size()) throw VectorException("Incompatible sizes");
        Vector<T,0> result(u.sz);
        for (std::size_t i = 0; i < u.sz; ++i) {
            result[i] = u[i] + v[i];
        }
        return result;
    }

    friend std::ostream &operator<<(std::ostream &out, const Vector & v) {
        for(int i = 0; i < v.sz; ++i){
            out << v.data[i] << " ";
        }
        return out;
    }

   template <std::size_t N>
   explicit operator Vector<T, N>() const {
       if(N != u.size()) throw VectorException("Incompatible sizes");
      Vector<T, N> result;
      for (std::size_t i = 0; i < N; ++i) {
         result[i] = data[i];
      }
      return result;
   }

   template <std::size_t N>
   friend Vector<T, N> operator+(const Vector<T, N>& u, const Vector<T, 0>& v) {
      Vector<T, N> result;
       if(N != u.size()) throw VectorException("Incompatible sizes");
      for (std::size_t i = 0; i < N; ++i) {
         result[i] = u[i] + v[i];
      }
      return result;
   }
   
   template <std::size_t N>
   friend Vector<T,N> operator+(const Vector<T, 0>& u, const Vector<T, N>& v)
    {
       if(N != u.size()) throw VectorException("Incompatible sizes");
        Vector<T, N> result;
        for (size_t i = 0; i < N; ++i)
        {
            result[i] = u.get(i) + v[i];
        }
        return result;
    }
    


};


class VectorException : public std::runtime_error {
public:
    VectorException(const std::string& msg) : std::runtime_error(msg) { }
};
#endif //DYNAMIC_VECTOR_H