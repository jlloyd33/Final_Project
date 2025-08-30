
/* ---------------------------------------------------------------------------
** I attest that this following code represents my own work and is subject to
** the plagiarism policy found in the course syllabus.
**
** Class: 	CSC 242
** Assignment: 	Lesson # chapters 7 & 8
** File: 	CypherFinal.cpp
** Description: This program implements a keyword-based substitution cipher
**
** Author: 	Jared Lloyd, Lorenzo Robles, Joshua Najera
** Date: 	08/30/2025
** -------------------------------------------------------------------------*/

#include <iostream>
#include <string>
#include <cctype>
#include <set>
#include <fstream>
using namespace std;

/** * @brief Generates a cipher alphabet based on a keyword.
 *
 * This function creates a substitution cipher alphabet by first adding
 * unique letters from the keyword (converted to uppercase), followed by
 * the remaining letters of the alphabet in reverse order.
 *
 * @param keyword The keyword used to generate the cipher alphabet.
 * @return A string representing the cipher alphabet.
 */


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

/**
 * @brief Encrypts a message using a keyword-based cipher alphabet.
 *
 * This function maps each letter of the standard alphabet to a cipher
 * alphabet generated from the keyword and applies the mapping to the input message.
 * Non-alphabetic characters are preserved.
 *
 * @param message The original message to encrypt.
 * @param keyword The keyword used to generate the cipher alphabet.
 * @return The encrypted message.
 */
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

/**
 * @brief Decrypts a message using a keyword-based cipher alphabet.
 *
 * This function reverses the cipher mapping created from the keyword,
 * converting each letter in the encrypted message back to its original form.
 * Non-alphabetic characters are preserved.
 *
 * @param encrypted The encrypted message to decrypt.
 * @param keyword The keyword used to generate the cipher alphabet.
 * @return The decrypted message.
 */
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

/**
 * @brief Main function to run the encryption and decryption process.
 *
 * Prompts the user for a keyword and a message to encrypt. Then asks
 * for the keyword again to decrypt the message. If the keyword matches,
 * the message is decrypted; otherwise, an error is shown.
 *
 * @return int Exit status.
 */

int main()
{
    string keyword;
    string originalMessage;

    cout << "Enter a keyword for encryption:" << endl;
    getline(cin, keyword);

    
    ifstream secretmessage("Text.txt");
    

    if (secretmessage.is_open())
    {
        getline(secretmessage, originalMessage); // Read entire file content
    }
    else
        {
        cout << "Unable to open file." << endl;
        return 1;
	}
	secretmessage.close();

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
