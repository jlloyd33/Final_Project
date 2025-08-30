/* ---------------------------------------------------------------------------
** I attest that this following code represents my own work and is subject to
** the plagiarism policy found in the course syllabus.
**
** Class: 	CSC 242
** Assignment: 	Lesson #5
** File: 	source.cpp
** Description:
**
** Author: Jared Lloyd, Joshua Najera, and Lorenzo Robles
** Date:8/30/2025
** -------------------------------------------------------------------------*/

#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <algorithm>
#include <cctype>

using namespace std;

// Function to convert a string to lowercase
// This version is more robust and uses the C++ locale system.
string toLower(const string& s)
{
    string lower_s = s;
    transform(lower_s.begin(), lower_s.end(), lower_s.begin(),
        [](unsigned char c) { return tolower(c); });
    return lower_s;
}

// Function to clean a word (remove punctuation and convert to lowercase)
string clean_word(const string& s)
{
    string cleaned_s;
    for (char c : s) {
        if (isalpha(c)) {
            cleaned_s += tolower(c);
        }
    }
    return cleaned_s;
}

int main()
{
    // Dictionary Loading 
    // Use a relative path to make the program portable.
    const char* dictionary_path = "wordlist.txt";
    cout << "Loading dictionary from: " << dictionary_path << "..." << endl;

    // Using set for efficient lookups.
    set<string> dictionary_words;
    ifstream dict_file(dictionary_path);
    // open the dictionary file and check if it opened successfully and shown with error message if not
    if (!dict_file.is_open())
    {
        cout << "Error: Dictionary file not found at '" << dictionary_path << "'.\n";
        cout << "Please ensure you have a plain text file named 'wordlist.txt' with one word per line." << endl;
        return 1;
    }
    // Read each word from the dictionary file and store it in the set
    string word;
    while (getline(dict_file, word))
    {
        dictionary_words.insert(toLower(word));
    }
    dict_file.close();
    cout << "Dictionary loaded with " << dictionary_words.size() << " words." << endl;

    // Input File Handling
    const char* input_path = "input_document.txt";
    cout << "\nChecking spelling in file: " << input_path << "..." << endl;

    // Check if the input file exists, and create a dummy one if it doesn't.
    // The program will continue after creating the file.
    ifstream input_check(input_path);
    if (!input_check.is_open())
    {
        ofstream test_file(input_path);
        test_file << "This is a test document with some speling errors.\n";
        test_file << "The goal is to find the misspelled words, like \"speling\" and \"docment\".\n";
        test_file << "Let's see if the program can catch them.\n";
        test_file << "Anothe word to test is \"Anothe\".\n";
        test_file << "The last words will be \"program\", \"programing\" and \"Python\".\n";
        test_file.close();
        cout << "Created a dummy test file '" << input_path << "'." << endl;
        // Re-open the file after creating it
        input_check.open(input_path);
    }
    input_check.close();
    // Open the input file for reading
    ifstream input_file(input_path);
    if (!input_file.is_open())
    {
        cout << "Error: Input file could not be opened at '" << input_path << "'. Please check file permissions." << endl;
        return 1;
    }
    // Set to track already printed misspelled words to avoid duplicates
    set<string> misspelled_words;

    // Read the input file word by word
    while (input_file >> word)
    {
        string cleaned_word = clean_word(word);

        // Check if the cleaned word is in the dictionary and is not empty.
        if (!cleaned_word.empty() && dictionary_words.find(cleaned_word) == dictionary_words.end()) {
            // Check if we've already printed this word to avoid duplicates.
            if (misspelled_words.find(cleaned_word) == misspelled_words.end()) {
                cout << "Misspelled: " << cleaned_word << endl;
                misspelled_words.insert(cleaned_word);
            }
        }
    }

    input_file.close();
    cout << "\nDocument has been checked for spelling errors." << endl;

    return 0;
}
