#include <iostream>
#include <algorithm>
#include <memory>
#include "MyString.h"
using namespace std;

class String{
   using string = emcpp::MyString;
//    using string = std::string;

/// Store a pointer to dynamically allocated string!
    std::shared_ptr<string> str = nullptr;

public:

    String():str(make_shared<string>()){};     /// creates an empty string
    String(const char * str) : str(make_shared<string>(str)){};  /// copy C-string
    String(const String & s) : str(s.str){};            /// no copy        /// no copy
    String operator=(const String & s){
        if(this != &s){
            this->str = s.str;
        }
        return *this;
    }; /// no copy
    /// makes a copy of a string if it has more than one reference.
    void set(int index, char ch){
        if(str.use_count() > 1){
            str = make_shared<string>(*str);
        }
        *(str->begin() + index) = ch;
    };
    /// no copy
    char get(int index) const{
        return *(str->begin() + index);
    }
    /// creates a new string only if both strings are non empty
     friend String operator+(String a, String b){
        if(a.str->length() == 0){
            return b;
        }
        if(b.str->length() == 0){
            return a;
        }
        return String((*(a.str) + *(b.str)).c_str());
    }
    friend std::ostream & operator<< (std::ostream & out, String s){
        int n = s.str->length();
        for (auto i = 0; i < n; i++){
            out << *(s.str->begin() + i);
        }
        return out;
    };
};
