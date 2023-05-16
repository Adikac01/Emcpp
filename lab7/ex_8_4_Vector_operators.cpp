#include <iostream>
using namespace std;

template <int N>
class Vector {
    int data[N];
public:
    Vector() {
        cout << " Default constr" << endl;
    }
    Vector(std::initializer_list<int> list) {
        cout << " Init list constr" << endl;
        auto it = list.begin();
        for (int i = 0; i < N; i++) {
            data[i] = *it++;
        }
    }
    Vector(const Vector& m) {
        std::copy(m.data, m.data + N, data);
        cout << " Copy constr" << endl;
    }
    int operator[](int index) const {
        return data[index];
    }
    int& operator[](int index) {
        return data[index];
    }


    friend ostream& operator<<(ostream& out, const Vector& m) {
        for (auto x : m.data) {
            cout << x << ", ";
        }
        return out;
    }
};

template<typename T>
int get(const T& data, int index){
  return data[index];
}

template<>
int get(const int& data, int index){
  return data;
}
template <typename L, typename R, typename Operation>
class Node{
  R right;
  L left;
  Operation op;
public:
  Node(L && _left, R && _right) : left(std::forward<L>(_left)), right(std::forward<R>(_right)){}
  int operator[](int index) const {
    return op(get(left,index), get(right,index));
  }
  template<int N>
  operator Vector<N>() {
    Vector<N> res;
    for (int i = 0; i < N; i++){
      res[i] = (*this)[i];
    }
    return res;
  }
};

template <typename L, typename R>
Node<L,R,std::plus<int>> operator+(L && left, R && right) {
  return Node<L,R,std::plus<int>>(std::forward<L>(left), std::forward<R>(right));
}

template <typename L, typename R>
Node<L,R,std::minus<int>> operator-(L && left, R && right) {
  return Node<L,R,std::minus<int>>(std::forward<L>(left), std::forward<R>(right));
}

template <typename L, typename R>
Node<L,R,std::multiplies<int>> operator*(L && left, R && right) {
  return Node<L,R,std::multiplies<int>>(std::forward<L>(left), std::forward<R>(right));
}


int main(){
  using V = Vector<10>;
  V v{1,2,3,4,5,6,7,8,9,10};
  V x(v);
  V y{4,4,2,5,3,2,3,4,2,1};

  cout << "Lazy operations :\n";
  // It does not create temporary Vectors
  // It computes resulting vector coordinate by coordinate
  // (evaluating whole expression)
  V z = v + x + 3 * y - 2 * x;
  cout << z << endl;

  // Computes only one coordinate of Vector
  int e = (z+x+y)[2];
  cout << " e = " << e << endl;
  return 0;
}
/**
 Init list constr
 Copy constr
 Init list constr
Lazy operations :
 Default constr
12, 12, 6, 15, 9, 6, 9, 12, 6, 3,
e = 11
 */