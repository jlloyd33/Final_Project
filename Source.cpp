#include <iostream>
#include <string>
#include <set>
using namespace std;

int main()
{
    string keyword;
    cout << "Enter a keyword: ";
    cin >> keyword;

    string key;         // final cipher alphabet
    set<char> seen;     // tracks letters already used

    // Add letters from keyword
    for (char ch : keyword)
    {
        char up = toupper(static_cast<unsigned char>(ch));  // uppercase safely
        if (isalpha(up) && !seen.count(up))  // only add new letters
        {
            key += up;
            seen.insert(up);
        }
    }

    // Add remaining letters of alphabet in reverse order
    for (char ch = 'Z'; ch >= 'A'; ch--)
    {
        if (!seen.count(ch))
        {
            key += ch;
            seen.insert(ch);
        }
    }

    cout << "Cipher alphabet: " << key << endl;

    return 0;
}