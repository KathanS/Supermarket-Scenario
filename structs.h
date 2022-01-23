// Name: Kathan Sanghavi
// ID: 201901053

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

struct Item
{
    long int ID;    // Item_ID
    char *Name;
    float Rate;
    int Quantity;
    Item* next;
};

struct Item1
{
    long int ID;    // Item_ID
    char *Name;
    float Rate;
    int Quantity;
    float amount;
    Item1* next;
};

struct CustomerData
{
    long int ID;    // Customer_ID
    char* Name;
    float Points;
    CustomerData* next;
};
