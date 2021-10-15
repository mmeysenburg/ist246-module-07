#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <list>
#include <ratio>
#include <set>

int main() {
    std::list<std::string> dllDict;
    std::set<std::string> bstDict;

    // load the dictionaries
    std::ifstream dictInFile("dictionary.txt");
    std::string word;
    while(dictInFile >> word) {
        dllDict.push_back(word);
        bstDict.insert(word);
    }
    dictInFile.close();

    // prompt for file to check
    std::cout << "Enter file name: ";
    std::string fileName;
    std::cin >> fileName;

    // check spelling with bst
    std::set<std::string> bstMisspelled;
    std::ifstream bstInFile(fileName);

    std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
    while(bstInFile >> word) {
        if(bstDict.find(word) == bstDict.end()) {
            bstMisspelled.insert(word);
        }
    }
    std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
    bstInFile.close();

    std::chrono::duration<double> elapsed = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);
    
    std::cout << "*** BST DICTIONARY ***" << std::endl;
    std::cout << "Found " << bstMisspelled.size() << " misspelled words in " << elapsed.count() << "s." << std::endl;

    // check spelling with dll
    std::set<std::string> dllMisspelled;
    std::ifstream dllInFile(fileName);

    t1 = std::chrono::high_resolution_clock::now();
    while(dllInFile >> word) {
        std::list<std::string>::iterator it;
        it = std::find(dllDict.begin(), dllDict.end(), word);
        if(it == dllDict.end()) {
            dllMisspelled.insert(word);
        }
    }
    t2 = std::chrono::high_resolution_clock::now();

    dllInFile.close();

    elapsed = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);
    
    std::cout << "*** DLL DICTIONARY ***" << std::endl;
    std::cout << "Found " << dllMisspelled.size() << " misspelled words in " << elapsed.count() << "s." << std::endl;

    return EXIT_SUCCESS;
}