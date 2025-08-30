#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <set>
using namespace std;

int main()
{
	// Build cipher alphabet from keyword
	string makeCipherAlphabet(const string& keyword)

	string key;			// this will hold the final cipher alphabet
	set<char> seen;		// tracks letters that have been added to key

	// Add letters from keyword to key (uppercase, no duplicates)
	for (char ch : keyword)  // inspect each letter of the keyword
	{
		char up = toupper(ch);  // convert to uppercase
		if (isalpha(up) && !seen.count(up))  // if it's a letter and not already used add it
		{
			key += up;          // add to key
			seen.insert(up);    // mark as seen
		}
	}
	// Add remaining letters of alphabet in reverse order	
	for (char ch = 'Z'; ch >= 'A'; ch--)  // loops in reverse order from Z to A
	{
		if (!seen.count(ch))  // revise to see if not already in key
		{
			key += ch;       // add new letter to key
			seen.insert(ch); // mark letter as seen
		}
	}
	return key; // final cipher alphabet
}    // continuation of makeCipherAlphabet