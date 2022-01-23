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

class Manager 
{
    private:
        long int ID;
        char *Name;
        Inventory* I; // Manager will have full access to this Inventory.

    public:
        Manager(long int ID1,char *Name1,Inventory* I1){ID = ID1; Name = Name1; I = I1;};  // constructor
        void Add_item(Item *i)
        {
            I->Add_item(i);
        }
        char* Delete_item(long int Item_ID1)
        {
            return I->Delete_item(Item_ID1);
        }
        void Update_item_Rate(long int Item_ID1,float Rate1) // Replaces Item's Rate with a new rate provided in argument.
        {
            I->Update_item_Rate(Item_ID1,Rate1);
        }
        void Update_item_Quantity(long int Item_ID1,int Quantity1) // Replaces Quantities of a Item with a new Quantity provided in argument.
        {
            I->Update_item_Quantity(Item_ID1,Quantity1);
        }
        void Get_Product_Info(long int Item_ID1) // This will print the information of product.
        {
            Item i = I->Get_Product_Info(Item_ID1,I);
            if(i.ID==-1)
            {
                cout<<"Product does not exist.\n";
            }
            else
            {
                cout<<"Item_ID: "<<i.ID<<"\n";
                cout<<"Name: "<<i.Name<<"\n";
                cout<<"Rate: "<<i.Rate<<"\n";
                cout<<"Quantity: "<<i.Quantity<<"\n\n";
            }
        }
        void change_stock(long int Item_ID,int change)// Increase or decrease number of items (Quantity of Item). 
        {                                             // Variable 'change' in the function argument should be positive number to increase the Quantity, negative number to decrease the Quantity.
            I->update_stock(Item_ID,change,I);
        }
    // As described in ppt, I have designed Manager Class in a way such that it will not have access to Customer Database.
};
