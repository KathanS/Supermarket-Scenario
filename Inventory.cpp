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

class Inventory
{
    private:
        Hash<Item> *Item_list = new Hash<Item>(100);  // I am choosing the 100 as Hash Table Size, it can be chosen according to number of Items in Inventory.
        void Add_item(Item *n)
        {
            Item_list->hashInsert(n);
        }
        char* Delete_item(long int Item_ID1) // Deletes item and returns name of deleted Item. Name can be further used if needed.
        {
            char *name = Item_list->hashDelete(Item_ID1);
            return name;
        }
        void Update_item_Rate(long int Item_ID1,float Rate1) // Replaces Item's Rate with a new rate provided in argument.
        {
            Item *item = Item_list->hashSearch(Item_ID1);
            item->Rate = Rate1;
        }
        void Update_item_Quantity(long int Item_ID1,int Quantity1) // Replaces Quantities of a Item with a new Quantity provided in argument.
        {
            Item *item = Item_list->hashSearch(Item_ID1);
            item->Quantity = Quantity1;
        }
        friend class Manager; // Manager can access all functionalities of Inventory.
    protected:
        Item Get_Product_Info(long int Item_ID,Inventory *I1)
        {
            Item* item = I1->Item_list->hashSearch(Item_ID);
            if(item == NULL) // Indicates Item does not exist.
            {
                Item item1;
                item1.ID = -1;
                return item1;
            }
            else
            {
                Item item1; // Making new Item object, therefore only data of Item will be returned, direct pointer will not be returned due to security reasons.
                item1.ID = item->ID;
                item1.Name = item->Name;
                item1.Rate = item->Rate;
                item1.Quantity = item->Quantity;
                item1.next = NULL;
                return item1;
            }
        }
        void update_stock(long int Item_ID,int change,Inventory *I1) // Increase or decrease number of items (Quantity of Item). 
        {                                                             // Variable 'change' in the function argument should be positive number to increase the Quantity, negative number to decrease the Quantity.
            Item* item = I1->Item_list->hashSearch(Item_ID);
            item->Quantity+=change;
            if(item->Quantity<0)
            {
                item->Quantity-=change;
                cout<<"NOT ENOUGH STOCK\n";
                //exit(0);    //Functionalities like this can be added as per choice of design, when the stock(Quantity) is not enough for demand.
            }
        }
        // I have derived Billing class from Inventory class, therefore Billing will be able to use only Get_Product_Info and update_stock methods, Billing object will not have access to methods other than these.
};
