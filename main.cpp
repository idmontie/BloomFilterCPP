//
//  main.cpp
//  QuickDatabase
//
//  Created by Ivan Montiel on 2/15/12.
//  Copyright (c) 2012 ASU. All rights reserved.
//

#include "BloomFilter.h"
#include <iostream>
#include <string.h>
#include <assert.h>

using namespace std;

int main (int argc, const char * argv[])
{
    assert(sizeof(byte) == 1);
    
    BloomFilter* bf = new BloomFilter(100);
    
    char input = ' ';
    char * word = new char[255];
    while (input != 'x') {
        cout << "'a' to add, 'q' to query, 'x' to quit: ";
        cin >> input;
        
        switch (input) {
            case 'a':
                //add
                cout << "Type a word in to add: ";
                cin >> word;
                bf->add(word);
                break;
            case 'q':
                // query
                cout << "Type a word to query for: ";
                cin >> word;
                if (bf->query(word)) {
                    cout << word << " might be in the filter." << endl;
                } else {;
                    cout << word << " is not in the filter." << endl;
                }
                break;
                
        }
    }
    
    bf->add("test");            
    bf->add("meow");
    bf->add("Dogma");
    bf->add("meow");
    bf->add("sty");
    bf->add("shy");
    bf->add("peter");
    bf->add("face");
    bf->add("rabid");
    bf->add("banana");
    bf->add("fox");
    bf->add("rose");
    bf->add("muffin");
    bf->add("taxes");
    bf->add("porn");
    bf->add("stack"); // 520 bits stored in 100 bits
    bf->add("leet");
    cout << "boom is in BF: \t\t" << bf->query("boom") << endl;
    cout << "sega is in BF: \t\t" << bf->query("sega") << endl;
    cout << "alpha is in BF: \t" << bf->query("alpha") << endl;
    cout << "test is in BF: \t\t" << bf->query("test") << endl;
    cout << "rabid is in BF: \t" << bf->query("rabid") << endl;

    getchar();
    
    bf->~BloomFilter(); // Clean up
    
    return 0;
}

