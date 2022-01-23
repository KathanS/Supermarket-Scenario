// Name: Kathan Sanghavi
// ID: 201901053

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

template<typename T> // made using template so it can be used for different node structures.
class LinkList
{
    private:
        T* head;
        T* tail;
        
    public:
        LinkList(){head = NULL; tail = NULL;}; // Constructor
        
        void linkInsert(T *n)
        {
            long int ID1 = n->ID;
            T* ptr = head;
            if(ptr == NULL)
            {
                n->next = NULL;
                head = n;
                tail = n;
            }
            else
            {
                if(ptr->ID>ID1)
                {
                    n->next = ptr;
                    head = n;
                }
                else
                {
                    while(ptr->next!=NULL && ptr->next->ID<ID1)
                    {
                        ptr = ptr->next;
                    }
                    n->next = ptr->next;
                    ptr->next = n;
                    if(n->next == NULL)
                        tail = n;
                }
            }
        }
        T* linkSearch(long int ID1)
        {
            T* ptr = head;
            while(ptr!=NULL && ptr->ID<ID1)
            {
                ptr = ptr->next;
            }
            if(ptr==NULL||ptr->ID!=ID1)
            {
                return NULL;
            }                
            else
            {
                return ptr;
            }
        }
        char* linkDelete(long int ID1) // delete by ID and return the name. Name can be further used if needed.
        {
            T* ptr = head;
            T* prev = NULL;
            while(ptr!=NULL && ptr->ID<ID1)
            {
                prev = ptr;
                ptr = ptr->next;
            }
            if(ptr==NULL||ptr->ID!=ID1)
            {
                char *r = new char[10];
                strcpy(r,"NOT FOUND");
                return r;
            }
            else if(prev==NULL)
            {
                head = ptr->next;
                if(head==NULL)
                    tail = NULL;
                return ptr->Name;
            }
            else if(ptr->next==NULL)
            {
                tail = prev;
                prev->next = NULL;
                return ptr->Name;
            }
            else
            {
                prev->next = ptr->next;
                return ptr->Name;
            }
        }
        float Compute_Bill() // specifically designed for computing bill from Billing object
        {
            float bill = 0;
            T* ptr = head;
            while(ptr!=NULL)
            {
                bill+=ptr->amount;
                ptr = ptr->next;
            }
            return bill;
        }
        void Print_List() // specifically designed for printing bill from Billing object
        {
            T* ptr = head;
            while(ptr!=NULL)
            {
                cout<<ptr->ID<<"    "<<ptr->Name<<"        "<<ptr->Rate<<"          "<<ptr->Quantity<<"        "<<ptr->amount<<"\n";
                ptr = ptr->next;
            }
        }
};