
#include <iostream>
#include <string>
#include <cctype>
#include <set>
using namespace std;

// Builds the cipher alphabet from the keyword
string makeCipherAlphabet(const string& keyword)
{
    string key;
    set<char> seen;

    for (char ch : keyword)
    {
        char up = toupper(ch);
        if (isalpha(up) && !seen.count(up))
        {
            key += up;
            seen.insert(up);
        }
    }

    for (char ch = 'Z'; ch >= 'A'; ch--)
    {
        if (!seen.count(ch))
        {
            key += ch;
            seen.insert(ch);
        }
    }

    return key;
}

// Encrypts the message using the cipher alphabet
string encryptMessage(const string& message, const string& keyword)
{
    string encryptedMessage = "";
    string cipherAlphabet = makeCipherAlphabet(keyword);
    string standardAlphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    char encryptMap[256] = { 0 };

    for (size_t i = 0; i < standardAlphabet.length(); i++)
    {
        encryptMap[static_cast<unsigned char>(standardAlphabet[i])] = cipherAlphabet[i];
    }

    for (char ch : message)
    {
        char up = toupper(ch);
        if (isalpha(up))
        {
            encryptedMessage += encryptMap[static_cast<unsigned char>(up)];
        }
        else
        {
            encryptedMessage += ch;
        }
    }

    return encryptedMessage;
}

// Decrypts the message using the cipher alphabet
string decryptMessage(const string& encrypted, const string& keyword)
{
    string decryptedMessage = "";
    string cipherAlphabet = makeCipherAlphabet(keyword);
    string standardAlphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    char decryptMap[256] = { 0 };

    for (size_t i = 0; i < cipherAlphabet.length(); i++)
    {
        decryptMap[static_cast<unsigned char>(cipherAlphabet[i])] = standardAlphabet[i];
    }

    for (char ch : encrypted)
    {
        char up = toupper(ch);
        if (isalpha(up))
        {
            decryptedMessage += decryptMap[static_cast<unsigned char>(up)];
        }
        else
        {
            decryptedMessage += ch;
        }
    }

    return decryptedMessage;
}

int main()
{
    string keyword;
    string originalMessage;

    cout << "Enter a keyword for encryption:" << endl;
    getline(cin, keyword);

    cout << "Enter the message to encrypt:" << endl;
    getline(cin, originalMessage);

    string encryptedMessage = encryptMessage(originalMessage, keyword);
    cout << "\nEncrypted message: " << encryptedMessage << endl;

    // Prompt for keyword again before decrypting
    string enteredKeyword;
    cout << "\nTo decrypt the message, enter the keyword:" << endl;
    getline(cin, enteredKeyword);

    if (makeCipherAlphabet(enteredKeyword) == makeCipherAlphabet(keyword))
    {
        string decryptedMessage = decryptMessage(encryptedMessage, enteredKeyword);
        cout << "Decrypted message: " << decryptedMessage << endl;
    }
    else
    {
        cout << "Incorrect keyword. Unable to decrypt the message." << endl;
    }

    return 0;
}

