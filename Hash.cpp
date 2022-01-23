// Name: Kathan Sanghavi
// ID: 201901053

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <cstring>
#include "structs.h"
using namespace std;

template<typename T> // made using template so it can be used for different node structures.
class Hash
{
    private:
        int size;
        LinkList<T> *table;
        
    public:
        Hash(int s)
        {
            size = s; 
            table = new LinkList<T>[s];
        }
        int hashFunction(long int x)
        {
            return x%size;
        }
        void hashInsert(T *n)
        {
            table[hashFunction(n->ID)].linkInsert(n);    
        }
        char* hashDelete(long int ID1) // delete by ID and return the name. Name can be further used if needed.
        {
            char* name = table[hashFunction(ID1)].linkDelete(ID1);
            return name;
        }
        T* hashSearch(long int ID1)
        {
            T* node = table[hashFunction(ID1)].linkSearch(ID1);
            return node;
        }
};