#include <iostream>
#include <list>
#include <cmath>

using namespace std;

string DetectDifferentCharacters(string inputText)
{
    char differentCharacters[inputText.length()];
    bool isCharacterDifferent;

    int size = 0;
    for (char characterFromText : inputText)
    {
        isCharacterDifferent = true;
        for (char characterDifferent : differentCharacters)
        {
            if(characterDifferent == characterFromText)
            {
                isCharacterDifferent = false;
                break;
            }
        }
        if(isCharacterDifferent)
        {
            differentCharacters[size] = characterFromText;

        }
    }

    return differentCharacters;
}

void permute(string a, int l, int r)
{
    // Base case
    if (l == r)
        cout<<a<<endl;
    else
    {
        // Permutations made
        for (int i = l; i <= r; i++)
        {

            // Swapping done
            swap(a[l], a[i]);

            // Recursion called
            permute(a, l+1, r);

            //backtrack
            swap(a[l], a[i]);
        }
    }
}

int main() {

    string inputText;
    cout << "Input some string" << endl;
    cin >> inputText;
    int sizeOfCombinations = pow(DetectDifferentCharacters(inputText).size(), inputText.length());
    string data;
    char arr[DetectDifferentCharacters(inputText).size()];
    permute(inputText, 0, inputText.length() - 1);

    return 0;
}
