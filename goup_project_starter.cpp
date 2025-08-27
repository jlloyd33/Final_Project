/* ---------------------------------------------------------------------------
** I attest that this following code represents my own work and is subject to
** the plagiarism policy found in the course syllabus.
**
** Class: 	CSC 242
** Assignment: 	Lesson #
** File: 	source.cpp
** Description:
**
** Author: 	
** Date: 	
** -------------------------------------------------------------------------*/

#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;
int main()
{
    
	ifstream infile; //initialize the file
	infile.open("words.txt"); // have to include the filepath to the file in the parentheses.

	vector<string> library;
	string words;

	//Verify that the file actually opened.
    //If the file opens correctly, the while loop populates the "library vector.
    //If it was unsuccessful, the else statement will output an error message
	if (infile.is_open())
	{
		while (infile >> words) // This loop populates the library vector.
		{
			library.push_back(words);
		}
		infile.close();
	}
	else
	{
		cout << "Error: words.txt could not be opened." << endl;
	}
	cout << "Number of words read: " << library.size() << endl; // This tells you the size of the library vector.

    return 0;
}
