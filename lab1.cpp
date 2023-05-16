#include <iostream>
#include <algorithm>
using namespace std;

class Matrix
{
   size_t N = 0, M = 0;
   double *data = nullptr;

public:
   Matrix(){
      cout << "Default constructor called\n";
   }
   Matrix(size_t n, size_t m) : N(n), M(m), data(new double[n * m]){
      std::fill(data, data + N * M, 0.0);
      cout << "Size constructor called\n";
   }
   Matrix(initializer_list<initializer_list<double>> list) : N(list.size()){
      size_t m = 0;
      for (const auto &row : list){
         m = std::max(m, row.size());
      }
      M = m;
      data = (new double[N * M]);
      double *p = data;
      for (auto &row : list){
         auto last = std::copy(row.begin(), row.end(), p);
         std::fill(last, p += m, 0.0);
      }
      cout << "Initializer list constructor called\n";
   }
   double &operator()(size_t i, size_t j){
      return data[(i - 1) * M + j - 1];
   }
   double operator()(size_t i, size_t j) const{
      return data[(i - 1) * M + j - 1];
   }
   friend std::ostream &operator<<(std::ostream &out, const Matrix &m){
      double *p = m.data;
      for (size_t i = 1; i <= m.N * m.M; i++)
      {
         out << *(p + i - 1) << " ";
         if (i % m.M == 0)
            out << "\n";
      }
      return out;
   }
   Matrix & operator=(const Matrix& matrix){
      if(this != &matrix){
         N = matrix.N;
         M = matrix.M;
         data = matrix.data;
         cout << "copy assignment operator\n";
      }
      return *this;
   }
   Matrix(const Matrix& matrix) : N(matrix.N), M(matrix.M), data(matrix.data){
      cout << "copy constructor\n";
   }
   ~Matrix(){
      delete[] data;
   }

   Matrix operator-() const {
      Matrix newMatrix(N,M);
      for(auto i = 0; i < N*M; i++){
         *(newMatrix.data+i) = -(*(data+i));
      }
      cout << "unary operator\n";
      return newMatrix;
   }

   Matrix & operator=(Matrix && matrix){
      if(this != &matrix){
         swap(data, matrix.data);
         M = matrix.M;
         N = matrix.N;
         cout << "move assignment operator\n";
      }
      return *this;
   }
   
   Matrix(Matrix&& matrix) : N(matrix.N), M(matrix.M), data(matrix.data){
      matrix.data = nullptr;
      cout << "move constructor\n";
   }
};

class MatrixWithLabel : public Matrix {
   size_t N = 0, M = 0;
   double *data = nullptr;
   string label = "";
   public:
      using Matrix::Matrix;
      string getLabel(){
         return label;
      }
      void setLabel(string nLabel){
         label = nLabel;
      }
      MatrixWithLabel(string label, int n, int m) : Matrix(n,m){
         cout << "label size constructor\n";
         this->label = label;
         std::fill(data, data + N * M, 0.0);
      }
      MatrixWithLabel(string label, initializer_list<initializer_list<double>> list) : Matrix(list){
         this->label = label;
         cout << "label Initializer list constructor called\n";
   }
};

int main()
{

   Matrix m1;
   Matrix m2(3, 4);
   Matrix m3({{1, 2, 3}, {32, 23, 22}, {3, 234, 23, 44}});
   cout << m2(1, 1) << endl; // 0
   cout << m3(2, 2) << endl; // 23
   cout << m3;

   cout << "Copy semantics \n";
   Matrix m4 = m2;
   m4 = m3;

   cout << "Move semantics \n";
   Matrix m7 = std::move(m2);
   m4 = -m3;

   cout << "Copy elision \n";
    Matrix m6 = -m4;
    Matrix * pm = new Matrix(-m4);
    cout << m6(2,1) << endl; // 32

   cout << "Inheritance \n";
   MatrixWithLabel l0("B", 3, 4);
   MatrixWithLabel l1({{1,2},{4,5}});
   l1.setLabel("A");
   MatrixWithLabel l2 = l1;
   MatrixWithLabel l3 = std::move(l1);
   cout << l2.getLabel() << " " << l3.getLabel() << endl;
   // 	cout << l1.getLabel() << endl;

   return 0;
}