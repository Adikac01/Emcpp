
template<typename T>
class VectorTraits {
public:
    typedef T ValueType;
    typedef const ValueType& ReturnType;
    typedef const ValueType ScalarType;

    static ValueType mult(ScalarType x, ReturnType y) {
        return x * y;
    }

    static ValueType value() {
        return T{};
    }
};

template<>
class VectorTraits<int> {
public:
    typedef int ValueType;
    typedef ValueType ReturnType;
    typedef ValueType ScalarType;

    static ValueType mult(ScalarType x, ReturnType y) {
        return x * y;
    }

    static ValueType value() {
        return 0;
    }
};

template<>
class VectorTraits<double> {
public:
    typedef double ValueType;
    typedef ValueType ReturnType;
    typedef ValueType ScalarType;

    static ValueType mult(ScalarType x, ReturnType y) {
        return x * y;
    }

    static ValueType value() {
        return 0;
    }
};

template<>
class VectorTraits<std::string> {
public:
    typedef int ScalarType;
    typedef std::string ValueType;
    typedef const ValueType& ReturnType;

    static ValueType mult(ScalarType x, ReturnType y) {
        ValueType temp{};
        for (int i = 0; i < x; ++i) {
            temp += y;
        }
        return temp;
    }

    static ValueType value() {
        return "0";
    }
};