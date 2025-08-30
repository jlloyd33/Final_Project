#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <cctype>


using namespace std;

// Function to convert a string to lowercase
string toLower(const string & s) 
{
    string lower_s = s;
    transform(lower_s.begin(), lower_s.end(), lower_s.begin(),
        [](unsigned char c) { return tolower(c); });
    return lower_s;
}

// Convert a string to uppercase
string toUpper(const string& s) 
{
    string upper_s = s;
    transform(upper_s.begin(), upper_s.end(), upper_s.begin(),
        [](unsigned char c) { return toupper(c); });
    return upper_s;
}

// Clean a word (remove punctuation and convert to lowercase)
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
   
    // Open the dictionary file and build the word list
    const char* dictionary_path = "\\Users\\jared\\OneDrive\\Documents\\National college\\Word_list.docx";
    cout << "Loading from the provided file: " << dictionary_path << "..." << endl;

    // Using unordered_set for efficient lookups.
    unordered_set<string> dictionary_words;
    ifstream dict_file(dictionary_path);

    if (!dict_file.is_open()) 
    {
        cout << "Error: Dictionary file not found at '" << dictionary_path << "'. Please check the path." << endl;
        return 1;
    }

    string word;
    while (getline(dict_file, word))
    {
        dictionary_words.insert(toLower(word));
    }
    dict_file.close();
    cout << "Dictionary loaded with " << dictionary_words.size() << " words." << endl;

    // Open the file to be checked and create a dummy file if it doesn't exist 
    const char* input = "test_document.txt";
    cout << "\nChecking spelling in file: " << input << "..." << endl;

    // Check if the input file exists, and create a dummy one if not
    ifstream input_check(input);
    if (!input_check.is_open()) 
    {
        ofstream test_file(input);
        test_file << "This is a test document with some speling errors.\n";
        test_file << "The goal is to find the misspelled words, like \"speling\" and \"docment\".\n";
        test_file << "Let's see if the program can catch them.\n";
        test_file << "Anothe word to test is \"Anothe\".\n";
        test_file << "The last words will be \"program\", \"programing\" and \"Python\".\n";
        test_file.close();
        cout << "Created a dummy test file '" << input << "'." << endl;
    }
    input_check.close();

    ifstream input_file(input);
    if (!input_file.is_open())
    {
        cout << "Error: Input file not found at '" << input << "'. Please check the path." << endl;
        return 1;
    }

    unordered_set<string> misspelled_words;

    // Read the input file word by word
    while (input_file >> word) 
    {
        string cleaned_word = clean_word(word);

        // If the cleaned word is not in the dictionary
        if (!cleaned_word.empty() && dictionary_words.find(cleaned_word) == dictionary_words.end()) {
            // Check if we've already printed this word to avoid duplicates.
            if (misspelled_words.find(cleaned_word) == misspelled_words.end()) {
                // Convert to uppercase before printing
                cout << "Misspelled: " << toUpper(cleaned_word) << endl;
                misspelled_words.insert(cleaned_word);
            }
        }
    }

    input_file.close();
    cout << "\nDocument has been checked for spelling errors." << endl;

    return 0;
}
