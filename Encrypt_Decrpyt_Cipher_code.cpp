/* ---------------------------------------------------------------------------
** I attest that this following code represents my own work and is subject to
** the plagiarism policy found in the course syllabus.
**
** Class: 	CSC 242
** Assignment: 	Signature Assignment
** File: 	source.cpp
** Description: Work with team members to create a program that encrypts a word with a cipher alphabet and decrypts it as well
** Authors: 	Jared Lloyd, Joshua Najera, Lorenzo Robles
** Date: 	August 30, 2025
** -------------------------------------------------------------------------*/

#include <iostream>
#include <string>
#include <set>
using namespace std;

// Function to generate cipher alphabet from keyword
string makeCipherAlphabet(const string& keyword)
{
	string key;
	set<char> seen;

	// Add letters from the keyword
	for (char ch : keyword)
	{
		char up = toupper(static_cast<unsigned char>(ch));
		if (isalpha(up)  && !seen.count (up))
		{
			key += up;
			seen.insert(up);
		}
	}
	// Add remaining letters of the alphabet in reverse order
	for (char ch = 'Z'; ch >= 'A'; --ch)
	{
		if (!seen.count(ch))
		{
			key += ch;
			seen.insert(ch);
		}
	}
	return key;
}

// Function to decrypt a message using the cipher alphabet
string decryptMessage(const string& cipherText, const string& key)
{
	string decryptedText;
	
	for (char ch : cipherText)
	{
		char up = toupper(static_cast<unsigned char>(ch));
		if (isalpha(up))
		{
			//Find index of letter in cipher alphabet
			size_t index = key.find(up);
			//Replace with corresponding letter in regular alphabet
				char originalChar = 'A' + static_cast<char>(index);	
				decryptedText += originalChar;   
		}
		else
		{
			// Non-alphabetic characters remain unchanged
			decryptedText += ch;
		}
	}
	
	return decryptedText;
}

int main()
{
	string keyword;	
	cout << "Enter keyword: ";
	cin >> keyword;

	// Generate cipher alphabet
	string key = makeCipherAlphabet(keyword);
	cout << "Cipher Alphabet: " << key << endl;

	// Input cipher text to decrypt
	string cipherText;
	cout << "Enter cipher text to decrypt: ";
	cin.ignore(); // Clear newline character from input
	getline(cin, cipherText); //Read full line including spaces

	//Decrypt the message
	string decryptedText = decryptMessage(cipherText, key);
	cout << "Decrypted Text: " << decryptedText << endl;

	return 0;
}