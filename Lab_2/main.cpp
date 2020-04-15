#include <iostream>
#include <string>
#include <regex>
#include <iterator>
#include <vector>

using namespace std;

int main()
{
    string str = "";
    
    cin >> str;

    vector<pair<string, string>> v
    {
        {"[0-9]+" , "NUMBERS"} ,
        {"[a-zA-Z]+" , "STRING"},
        {"[*]", "TIMES"},
        {"[+]", "PLUS"},
        {"[-]", "MINUS"},
        {"[/]", "DIVIDE"}
        {"[;]", "SEMICOLOMN"}
    };

    string reg;

    for(auto const& x : v)
        reg += "(" + x.first + ")|";

    reg.pop_back();
    cout << reg << endl;

    regex re(reg, regex::extended);

    auto words_begin = sregex_iterator(str.begin(), str.end(), re);
    auto words_end = sregex_iterator();

    for(auto it = words_begin; it != words_end; ++it)
    {
        size_t index = 0;

        for( ; index < it->size(); ++index)
            if(!it->str(index + 1).empty()) // determine which submatch was matched
                break;

        cout << it->str() << "\t" << v[index].second << std::endl;
    }

    return 0;
}