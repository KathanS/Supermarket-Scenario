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

class Billing:private Inventory,private Customer
{
    private:                     
        char* Transaction_ID;
        long int customer_ID;
        float Total_amount;
        LinkList<Item1> *Item1_list;    //taking LinkList as Customer will buy limited items.
        Inventory* I; // Billing Object have access to this Inventory only to get product information and update stock.
        Customer* C; // Billing object have access to this Customer object to add customer, update points of customer and to print the customer information.
        
        void assign_customer_Id()    // This will be called in make_payment method. This will calculate the total amount of bill and will update the points of customer.
        {
            Total_amount = Item1_list->Compute_Bill();
            Update_points(customer_ID,Total_amount,C);
        }
        
        string random_Transaction_ID(int n)     // Generates random string of length given in argument.
        {
            char alphabet[26] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 
                          'h', 'i', 'j', 'k', 'l', 'm', 'n',  
                          'o', 'p', 'q', 'r', 's', 't', 'u', 
                          'v', 'w', 'x', 'y', 'z' }; // Numbers and Capital letters can also be added in this array and use the number of elements in this array instead of 26 in for loop to generate random string.
            string random = ""; 
            for (int i = 0; i < n; i++)  
                random = random + alphabet[rand() % 26]; 
      
            return random;               
        }
        
    public:
        Billing(Inventory *I1, Customer *C1){I = I1; C = C1;}; // Constructor -- this will be used for adding Customers to dataset.
        Billing(long int customer_ID1,Inventory* I1,Customer* C1) // Constructor -- this will be used for shopping episode.
        {
            string Transaction_ID1 = random_Transaction_ID(10);
            char *n = new char[Transaction_ID1.size()+1];
            strcpy(n,Transaction_ID1.c_str());
            Transaction_ID = n; 
            customer_ID=customer_ID1; 
            Item1_list=new LinkList<Item1>;
            I = I1;
            C = C1;
        }
        void Buy_item(long int Item_ID1, int Quantity1) // product can be bought by providing product ID and Quantity(number of such products to buy).
        {
            Item item = Get_Product_Info(Item_ID1,I);
            Item1 *item1 = new Item1;
            item1->ID = Item_ID1;
            item1->Quantity = Quantity1;
            item1->Name = item.Name;
            item1->Rate = item.Rate;
            item1->amount = item.Rate*Quantity1;
            Item1_list->linkInsert(item1);
            update_stock(Item_ID1,-Quantity1,I);
        }
        char* Cancel_item(long int Item_ID1) // Cancels item from list.
        {
            Item1* item1 = Item1_list->linkSearch(Item_ID1);
            int change = item1->Quantity;
            char* c = Item1_list->linkDelete(Item_ID1);
            update_stock(Item_ID1,change,I);
            return c;
        }
        void change_Quantity(long int Item_ID1, int change)  // change the quantity of product present in list. Variable 'change' should be Positive number to increase the Quantity and should be negative number to decrease the Quantity.
        {
            Item1 *item1 = Item1_list->linkSearch(Item_ID1);
            item1->Quantity+=change;
            item1->amount = (item1->Quantity)*(item1->Rate); // updates amount
            update_stock(Item_ID1,-change,I);
            
            // Example: Customer previously bought 3 units of particular Product (Quantity=3), but now customer wants to buy only 2 (Quantity=2), change_Quantity function can be used in this case.
        }
        void make_payment()
        {
            assign_customer_Id(); // Calculates Total Amount and updates the Customer Points.
            // Printing Bill
            cout<<"\n";
            cout<<"Transaction_ID: "<<Transaction_ID<<"\n";
            cout<<"Customer_ID:    "<<customer_ID<<"\n";
            cout<<"Product ID    Name         Rate    Quantity    Amount"<<"\n";
            Item1_list->Print_List();
            cout<<"                                      "<<"Total:    "<<Total_amount<<"\n\n";
        }
        void Add_Customer(CustomerData* CD)
        {
            Add_customer(CD,C);
        }
        void get_Customer_Information(long int customer_ID) //This is just for the purpose of checking the updates in Customer Data. (for a demonstration purpose)
        {
            print_customer_information(customer_ID,C);
        }
};