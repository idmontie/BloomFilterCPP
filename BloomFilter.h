//
//  BloomFilter.h
//  QuickSearchDatabase
//
//  Created by Ivan Montiel on 2/15/12.
//  Copyright (c) 2012 Idea Birth. All rights reserved.
//

#include <string.h>

#ifndef QuickSearchDatabase_BloomFilter_h
#define QuickSearchDatabase_BloomFilter_h

typedef char byte;

/**
 Bloom Filter Class
 By:            Ivan Montiel
 Description:   A probabilistic data structure.
                Hashes elements into a bitarray.
                Returns either "not in" or "might be in" structure.
*/

class BloomFilter {
public: 
    /**
     * Constructor
     */
    BloomFilter(int s = 800) : bitarray(0) {
        s = s / 8 + (s % 8 == 0 ? 0 : 1); // Convert the size to bytes and round up
        this->size = s;
        bitarray = new byte[s];
        for (int i = 0; i < s; i++) {
            bitarray[i] = 0;
        }
    };
    /**
     * Copy Constructor
     */
    BloomFilter(BloomFilter const&) {
       // TODO 
    };
    /**
     * Deconstructor
     */
    ~BloomFilter() {
        delete [] bitarray;
    };
    
    void add(const char* element) {
        // Hash the element
        unsigned int firstHash = hash(element);
        unsigned int secondHash = hash(firstHash);
        unsigned int thirdHash = hash(secondHash);
        
        unsigned int hashed = firstHash % size;
        unsigned int hashed2 = secondHash % size;
        unsigned int hashed3 = thirdHash % size;
        
        bitarray[hashed] |= 1 << (firstHash % 8);
        bitarray[hashed2] |= 1 << (secondHash % 8);
        bitarray[hashed3] |= 1 << (thirdHash % 8);
        
    };
    bool query(const char* element) {
        // Hash the element
        unsigned int firstHash = hash(element);
        unsigned int secondHash = hash(firstHash);
        unsigned int thirdHash = hash(secondHash);
        
        unsigned int hashed = firstHash % size;
        unsigned int hashed2 = secondHash % size;
        unsigned int hashed3 = thirdHash % size;
        
        bool check1 = bitarray[hashed] & (1 << (firstHash % 8));
        bool check2 = bitarray[hashed2] & (1 << (secondHash % 8));
        bool check3 = bitarray[hashed3] & (1 << (thirdHash % 8));
        
        return check1 && check2 && check3;
    };
    
private:
    byte* bitarray;
    int size;
    
    unsigned hash(const char* s) {
        unsigned h = 100714;
        while (*s) {
            h = h * 101 + (unsigned int) *s;
            s++;
        }
        return h;
    }
    unsigned hash(unsigned s) {
        unsigned h = 100714;
        h = h * 101 + (s % 1007533);
        return h;
    }
    

    
};

#endif
