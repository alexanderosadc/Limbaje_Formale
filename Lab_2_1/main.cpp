#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

vector<string> GetStateTransitionsFromFile()
{
    int n;
    vector<string> stateTransitions;
    string line;
    ifstream myfile;

    myfile.open("input");
    if (myfile.is_open())
    {
        getline(myfile, line);
        n = stoi(line);

        for(int i = 0; i < n; i++)
        {
            getline(myfile, line);
            stateTransitions.push_back(line);
        }
        myfile.close();
        return stateTransitions;
    }
    else
        cout << "can't open the file"<<endl;
}

vector <string> GetStates(vector<string> lines)
{
    vector<string> states;

    for(string line: lines)
    {
        string stateToAdd = "";
        stateToAdd = line[0];
        stateToAdd += line[1];
        if (find(states.begin(), states.end(), stateToAdd) != states.end())
        {

        } else
        {
            states.push_back(stateToAdd);
        }

        stateToAdd = "";
        stateToAdd = line[5];
        stateToAdd += line[6];
        if (find(states.begin(), states.end(), stateToAdd) != states.end())
        {

        } else
        {
            states.push_back(stateToAdd);
        }
    }


    return states;
}

string GetTransitions(vector<string> lines)
{
    string transitions;
    bool isAppearInTransaction;


    for(string line: lines)
    {
        isAppearInTransaction = false;
        for(int i = 0; i < transitions.length(); i++)
            if(line[3] == transitions[i])
            {
                isAppearInTransaction = true;
                break;
            }
        if(!isAppearInTransaction)
            transitions += line[3];
    }

    return transitions;
}

string **ConstructNFATransitionTable(vector<string> lines, vector<string> states, string transitions)
{
    string **nfaTransitionTable = new string *[states.size()];
    for(int i = 0; i < states.size(); i++)
    {
        nfaTransitionTable[i] = new string [transitions.length()];
    }

    string firstElement = "";
    string secondElement = "";


    for(int i = 0; i < states.size(); i++)
    {
        cout << states[i] << " ";
        for(int j = 0; j < transitions.length(); j++)
        {
            for(string line : lines)
            {
                firstElement = line[0];
                firstElement += line[1];

                if(states[i] == firstElement)
                {
                    secondElement = line[5];
                    secondElement += line[6];

                    if(transitions[j] == line[3])
                    {
                        cout << secondElement;
                        nfaTransitionTable[i][j] += secondElement;
                    }
                }
            }
            cout << " ";
        }
        cout << endl;
    }

    return nfaTransitionTable;
}

string **ConstructDFATranslationTable(string **nfaTable, int rowLength, int columnLength, vector<string> states)
{
    string **dfaTransitionTable = new string *[rowLength];
    for(int i = 0; i < rowLength; i++)
    {
        dfaTransitionTable[i] = new string [columnLength];
    }

    for(int i = 0; i < columnLength; i++)
    {
        dfaTransitionTable[0][i] = nfaTable[0][i];
    }

    vector<string> usedStates;
    bool canMoveForward = true;
    for(int i = 1; i < rowLength; i++)
    {
        for(int j = 0; j < columnLength; j++)
        {
            cout << "BlahBlah" << endl;
            if(*nfaTable[i - 1, j] != "0")
            {
                for(string item :usedStates)
                {
                    if(item == *nfaTable[i - 1, j])
                    {
                        canMoveForward = false;
                        break;
                    }

                }
                if(canMoveForward)
                {
                    if(nfaTable[i - 1, j]->length() > 2)
                    {
                        string element = "";
                        for(int count = 0; count < nfaTable[i - 1, j]->length(); count += 2)
                        {
                            element = nfaTable[i - 1, j]->c_str()[count];
                            element += nfaTable[i - 1, j]->c_str()[count + 1];

                            int index = 0;
                            for(string item: states)
                            {
                                index++;
                                if(item == element)
                                {
                                    break;
                                }
                            }

                            for(int iTable = 0; iTable < columnLength; iTable++)
                            {
                                dfaTransitionTable[i][j] += nfaTable[index][iTable].c_str();
                            }
                        }
                    } else{
                        string element;
                        element = nfaTable[i - 1][j][0];
                        element += nfaTable[i - 1][j][1];

                        int index = 0;
                        for(string item: states)
                        {
                            index++;
                            if(item == element)
                            {
                                break;
                            }
                        }

                        for(int iTable = 0; iTable < columnLength; iTable++)
                        {
                            dfaTransitionTable[i][j] = nfaTable[index][iTable].c_str();
                        }
                    }
                    usedStates.push_back(*nfaTable[i - 1, j]);
                }
            }
            cout << dfaTransitionTable[i][j] << " ";
            break;
        }
        break;
    }
}

int main() {

    vector<string> statePlusTransitionsNFA;
    vector<string> states;
    string transitions;

    statePlusTransitionsNFA = GetStateTransitionsFromFile();
    transitions = GetTransitions(statePlusTransitionsNFA);
    states = GetStates(statePlusTransitionsNFA);

    string** transitionTableNFA= ConstructNFATransitionTable(statePlusTransitionsNFA, states, transitions);
    string** transitionTableDFA = ConstructDFATranslationTable(transitionTableNFA, states.size(), transitions.length(), states);

    cout << endl << "NFA" << endl << endl;
    for(int i = 0; i < states.size(); i++)
    {
        for(int j = 0; j < transitions.length(); j++)
        {
            if(transitionTableNFA[i][j] != "")
                cout << transitionTableNFA[i][j] << " ";
            else
            {
                transitionTableNFA[i][j] = "0";
                cout << transitionTableNFA[i][j] << " ";
            }
        }
        cout << endl;
    }

    return 0;
}