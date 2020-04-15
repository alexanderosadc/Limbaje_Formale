#include <iostream>
#include <list>
#include <cmath>

using namespace std;

bool Automata(string str){
    int state = 0;
    for (char c: str){
        for (int i = 0; i < str.length(); i++) {
            if (c == 'a' && state == 0){
                state = 1;
            }
            else if (c == 'b' && state == 1){
                state=0;
            }
            else if (c == 'a' && state == 1){
                state=2;
            }
            else if (c == 'b' && state == 3){
                state=0;
            }
            else if (c == 'a' && state == 2){
                state=3;
            }
        }
    }

    return state == 3;
}

int main() {

    string inputText;
    cout << "Input some string" << endl;
    cin >> inputText;
    cout << Automata(inputText) << endl;


    return 0;
}