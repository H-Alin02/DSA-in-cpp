#ifndef PATTERNMATCHING_H
#define PATTERNMATCHING_H

#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

class PatternMatching {
    protected:
        vector<char> alpha;

    public:
        // Costruttore con passaggio per riferimento costante
        PatternMatching(const vector<char>& alphabet) : alpha(alphabet) {}
        virtual ~PatternMatching() {}
        
        virtual int simpleSearch(const string& text, const string& pattern) = 0;
        virtual vector<int> multiIndexSearch(const string& text, const string& pattern) = 0;
};

// Pattern Matching Naive
class NaivePatternMatching : public PatternMatching {
    public:
        NaivePatternMatching(const vector<char>& alpha) : PatternMatching(alpha) {}
        int simpleSearch(const string& text, const string& pattern) override;
        vector<int> multiIndexSearch(const string& text, const string& pattern) override;
};

// Pattern Matching KMP
class KMP_PatternMatching : public PatternMatching {
    private:
        vector<vector<int>> DFA;

        int find(vector<char> v, char c){
            return std::find(v.begin(), v.end(), c) - v.begin();
        }
        
        void create_DFA(const string& pattern){
            int APLH = alpha.size();
            int m = pattern.length();
            DFA = vector<vector<int>>(APLH, vector<int>(m, 0));

            DFA[find(alpha, pattern[0])][0] = 1;
            for(int x = 0, j = 1; j < m; j++){
                for(int c = 0; c < APLH; c++)
                    DFA[c][j] = DFA[c][x];
                    DFA[find(alpha, pattern[j])][j] = j + 1;
                    x = DFA[find(alpha,pattern[j])][x];
         
            }

            printDFAmatrix(pattern);
        }

        void printDFAmatrix(const string& pattern){
            // Prints the DFA matrix            
            std::cout << "   ";
            for (char c : pattern) {
                std::cout << c << " ";
            }
            std::cout << std::endl;

            for (int i = 0; i < DFA.size(); ++i) {
                std::cout << alpha[i] << "  ";
                for (int value : DFA[i]) {
                    std::cout << value << " ";
                }
                std::cout << std::endl;
            }

            cout << "\n";
        }
    
    public:
        KMP_PatternMatching(const vector<char>& alpha) : PatternMatching(alpha) {}

        int simpleSearch(const string& text, const string& pattern) override{
            create_DFA(pattern);
            int n = text.length();
            int m = pattern.length();
            int i, j;
            for(i = 0, j = 0; i < n && j < m; i++){
                j = DFA[find(alpha, text[i])][j];
            }
            if(j == m) return i-m;
            else return -1;
        }

        vector<int> multiIndexSearch(const string& text, const string& pattern) override{
            create_DFA(pattern);
            int n = text.length();
            int m = pattern.length();
            int i, j;
            vector<int> result;

            for(i = 0, j = 0; i < n; ++i){
                j = DFA[find(alpha, text[i])][j];
                if(j == m){ 
                    result.push_back(i-m+1);
                    j = 0;
                    j = DFA[find(alpha, text[i])][j];
                }
            }

            return result;
        }
};

#endif
