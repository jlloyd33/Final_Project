#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <cctype>
#include <set>

using namespace std;

// A constant for the default dictionary filename.
const string DEFAULT_DICTIONARY_PATH = "word_list.txt";

// A constant for the default input filename.
const string DEFAULT_INPUT_PATH = "test_document.txt";

// Helper function to remove punctuation and convert a string to lowercase.
string clean_word(const string& s)
{
    string cleaned_s;
    for (char c : s) {
        // Only include alphabetic characters.
        if (isalpha(c)) {
            cleaned_s += tolower(c);
        }
    }
    return cleaned_s;
}

int main(int argc, char* argv[])
{
    // Define the file paths for the dictionary and the document to check.
    // Use command-line arguments if provided, otherwise use default values.
    string dictionary_path = DEFAULT_DICTIONARY_PATH;
    string input_path = DEFAULT_INPUT_PATH;

    if (argc > 1) {
        dictionary_path = argv[1];
    }
    if (argc > 2) {
        input_path = argv[2];
    }

    // Load the dictionary into a hash set for fast lookups.
    unordered_set<string> dictionary_words;
    ifstream dict_file(dictionary_path);

    if (!dict_file.is_open())
    {
        cout << "Error: Could not open dictionary file at '" << dictionary_path << "'." << endl;
        cout << "Make sure the file exists and is a plain text file." << endl;
        return 1;
    }

    string word;
    while (dict_file >> word)
    {
        dictionary_words.insert(clean_word(word));
    }
    dict_file.close();
    cout << "Dictionary loaded with " << dictionary_words.size() << " words." << endl;

    // Open the document to check.
    ifstream input_file(input_path);
    if (!input_file.is_open())
    {
        cout << "Error: Could not open input file at '" << input_path << "'." << endl;
        return 1;
    }

    // A set to store unique misspelled words. A set keeps the words sorted and unique.
    set<string> misspelled_words;
    int words_checked = 0;

    // Read the input file word by word.
    while (input_file >> word)
    {
        words_checked++;
        string cleaned = clean_word(word);

        // Check if the cleaned word is in the dictionary.
        if (!cleaned.empty() && dictionary_words.find(cleaned) == dictionary_words.end()) {
            misspelled_words.insert(cleaned);
        }
    }

    input_file.close();

    cout << "\nChecked " << words_checked << " words from '" << input_path << "'." << endl;

    // Print the results.
    if (misspelled_words.empty()) {
        cout << "No spelling errors found." << endl;
    }
    else {
        cout << "\nFound " << misspelled_words.size() << " unique misspelled words:" << endl;
        for (const auto& w : misspelled_words) {
            cout << " - " << w << endl;
        }
    }

    return 0;
}

