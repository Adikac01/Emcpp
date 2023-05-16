#include <iostream>
#include <fstream>
#include <vector>
#include <map>

using namespace std;

/**
 * Trie structure
 */
class Trie {
public:
    static void printSentence(const vector<string>& sentence) {
        for (const auto& w : sentence)
            cout << w << " ";
    }

    void add(const vector<string>& sentence) {
        cout << "Adding: ";
        printSentence(sentence);
        cout << "\n";

        Node* current = &root;
        for (const string& word : sentence) {
            current = &(current->children[word]);
        }
        current->isEndOfSentence = true;
    }

    void printPossibleEndings(const vector<string>& beginningOfSentence) {
        cout << "Endings for \"";
        printSentence(beginningOfSentence);
        cout << "\" are:\n";

        Node* current = &root;
        for (const string& word : beginningOfSentence) {
            auto it = current->children.find(word);
            if (it == current->children.end()) {
                cout << "No possible endings.\n";
                return;
            }
            current = &(it->second);
        }

        vector<string> sentence = beginningOfSentence;
        traverse(current, sentence);
    }

    void load(const string& fileName) {
        ifstream file(fileName);
        if (!file) {
            cerr << "Error when opening file " << fileName << endl;
            return;
        }

        string word;
        vector<string> sentence;
        while (file >> word) {
            sentence.push_back(word);
            // Is it the end of the sentence?
            if (word.find_last_of('.') != string::npos) {
                add(sentence);
                sentence.clear();
            }
        }
    }

private:
    struct Node {
        map<string, Node> children;
        bool isEndOfSentence = false;
    };

    Node root;

    void traverse(Node* current, vector<string>& sentence) {
        if (current->isEndOfSentence) {
            printSentence(sentence);
            cout << endl;
        }

        for (auto& pair : current->children) {
            sentence.push_back(pair.first);
            traverse(&pair.second, sentence);
            sentence.pop_back();
        }
    }

    void traverse(const Node* current, vector<string>& sentence) {
        if (current->isEndOfSentence) {
            printSentence(sentence);
            cout << endl;
        }

        for (const auto& pair : current->children) {
            sentence.push_back(pair.first);
            traverse(&pair.second, sentence);
            sentence.pop_back();
        }
    }
};

int main() {
    Trie dictionary;
    dictionary.load("sample.txt");

    dictionary.printPossibleEndings({"Curiosity"});
    dictionary.printPossibleEndings({"Curiosity", "killed"});
    dictionary.printPossibleEndings({"The", "mouse", "was", "killed"});

    return 0;
}