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

class Customer    // stores data of Customers
{
    private:
        Hash<CustomerData> *Customer_list = new Hash<CustomerData>(100);  // I am choosing the 100 as Hash Table Size, it can be chosen according to total number of Customers.
        CustomerData* Get_CustomerData_Pointer(long int customer_ID) 
        {
            CustomerData* CD = Customer_list->hashSearch(customer_ID);
            return CD;
        }
        
    protected:
        void Add_customer(CustomerData *CD,Customer *C1)
        {
            C1->Customer_list->hashInsert(CD);
        }
        void Update_points(long int customer_ID,float Points1, Customer *C1) // adds the points as given in argument to Points of Customer.
        {
            CustomerData* CD = C1->Get_CustomerData_Pointer(customer_ID);
            if(CD == NULL) // CD == NULL, indicates Customer is new, so program will ask to provide name and will add this customer data to database.
            {
                
                cout<<"NEW CUSTOMER: "<<"Please provide name:"<<"\n";
                //take input
                string name;
                getline(cin,name);
                char* c = new char[name.size()+1];
                strcpy(c,name.c_str());
                
                CustomerData* CD1 = new CustomerData;
                CD1->ID = customer_ID;
                CD1->Name = c;
                CD1->Points = Points1;
                C1->Add_customer(CD1,C1);
            }
            else
            {
                CD->Points+=Points1;
            }
        }
        void print_customer_information(long int customer_ID,Customer *C1) // This is just for the purpose of checking the information of Customer.
        {                                                                    // Functionalities similar to Inventory's Get_Product_Info can be added to handle things when Customer with ID provided in argument does not exist.
            CustomerData *CD = C1->Get_CustomerData_Pointer(customer_ID);
            cout<<"Customer ID: "<<CD->ID<<"\n";
            cout<<"Name: "<<CD->Name<<"\n";
            cout<<"Points: "<<CD->Points<<"\n\n";
        }
};