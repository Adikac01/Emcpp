#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <numeric>
#include <cctype>
#include <map>
using namespace std;

/**
 * Removes all non alphanumeric characters from given word and converts to lower case.
 * @param[in,out] word on return word consist only of lower case characters.
 */
void toLowerAlpha(std::string & s1) {
    s1.erase(std::remove_if(s1.begin(),s1.end(),[](char c){return !std::isalnum(c);}), s1.end());

    std::transform(s1.cbegin(), s1.cend(), s1.begin(), [](char c){return std::tolower(c);});
}

int main(){
    int count = 0;
    std::string word;
    map<string, int> c;
    std::vector<int> v;
    while( cin >> word) {
       toLowerAlpha(word);
       if(word != ""){
           c[word]++;
           count++;
       }
    }
    multimap<int, string, greater<int>> m2;
    for(auto& it : c){
        m2.insert({it.second,it.first});
    }
    cout << "Number of distinct words : " << c.size() << endl;
    cout << "\nThe top 20 most popular words: \n";
    int i = 0;
    for (auto& it : m2) {
        cout << it.second << " : " << it.first << endl;
        if (i++ == 20) break;
    }
    return 0;
}
/*
 * Expected output for ./words < hamletEN.txt

Number of distinct words : 4726

The top 20 most popular words:
the : 1145
and : 967
to : 745
of : 673
i : 569
you : 550
a : 536
my : 514
hamlet : 465
in : 437
it : 417
that : 391
is : 340
not : 315
lord : 311
this : 297
his : 296
but : 271
with : 268
for : 248
your : 242

*/