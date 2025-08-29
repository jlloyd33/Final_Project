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

/**
 * @file main.cpp
 * @brief A program that reads words from a file, converts them to uppercase,
 * and identifies words that contain lowercase characters as misspelled.
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cctype>


using namespace std;

/**
 * @brief Converts a given string to all uppercase characters.
 *
 * This function takes a constant reference to a string, creates a modifiable
 * copy, and then iterates through each character to convert it to its
 * uppercase equivalent using the toupper() function.
 *
 * @param str The input string to be converted.
 * @return The new string with all characters converted to uppercase.
 */
string touppercase(const string& str)
{
    string upperstr = str;
    for (int i = 0; i < upperstr.length(); i++)
    {
        upperstr[i] = toupper(static_cast<unsigned char>(upperstr[i]));
    }
    return upperstr;
}

/**
 * @brief Main function of the program.
 *
 * The main function reads words from a file named "words.txt" and stores them
 * in two vectors: one for the original words and one for their uppercase
 * versions. It then compares the words in both vectors and prints any word
 * that contains lowercase characters, labeling it as "Misspelled".
 *
 * @return 0 on successful execution.
 */
int main()
{
    ifstream infile;
    infile.open("words.txt");

    vector<string> library;
    vector<string> upperwords;
    string words;


    if (infile.is_open())
    {
        while (infile >> words)
        {
            library.push_back(words);
            upperwords.push_back(touppercase(words));
        }
        infile.close();
    }
    else
    {
        cout << "Error: words.txt could not be opened." << endl;
    }

    // The program assumes words with lowercase letters are "misspelled."
    for (size_t i = 0; i < library.size(); i++)
    {
        if (library[i] != upperwords[i])
        {
            cout << "Misspelled words" << " " << upperwords[i] << endl;
        }
    }
    
    return 0;
}
