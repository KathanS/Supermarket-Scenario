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

// ---------------------------------------------- //

// Support Library

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

// ------------------------------------------------- //


// -------------------------------------------------- //

// Manager, Inventory, Customer, Billing Class.

class Manager;
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
// ------------------------------------------------------------------ //


int main()
{
    Inventory *I = new Inventory;
    Customer *C = new Customer;
    
    // Manager 
    string name = "ABC";
    char* name1 = new char[name.size()+1];
    strcpy(name1,name.c_str());    
    Manager M(111,name1,I);
    
    // Billing
    Billing *B = new Billing(I,C);
    
    
    // Dataset
    long INVENTORY_DATASET[100][4] = {
{111100000001,1,100,20},{111100000002,2,110,20},{111100000003,3,120,20},{111100000004,4,130,20},{111100000005,5,140,20},{111100000006,6,150,20},{111100000007,7,160,20},{111100000008,8,170,20},{111100000009,9,180,20},{111100000010,10,190,20},
{111100000011,11,200,20},{111100000012,12,210,20},{111100000013,13,220,20},{111100000014,14,230,20},{111100000015,15,240,20},{111100000016,16,250,20},{111100000017,17,260,20},{111100000018,18,270,20},{111100000019,19,280,20},{111100000020,20,290,20},
{111100000021,21,300,20},{111100000022,22,310,20},{111100000023,23,320,20},{111100000024,24,330,20},{111100000025,25,340,20},{111100000026,26,350,20},{111100000027,27,360,20},{111100000028,28,370,20},{111100000029,29,380,20},{111100000030,30,390,20},
{111100000031,31,400,20},{111100000032,32,410,20},{111100000033,33,420,20},{111100000034,34,430,20},{111100000035,35,440,20},{111100000036,36,450,20},{111100000037,37,460,20},{111100000038,38,470,20},{111100000039,39,480,20},{111100000040,40,490,20},
{111100000041,41,500,20},{111100000042,42,510,20},{111100000043,43,520,20},{111100000044,44,530,20},{111100000045,45,540,20},{111100000046,46,550,20},{111100000047,47,560,20},{111100000048,48,570,20},{111100000049,49,580,20},{222200001111,50,590,20},
{222200001114,51,600,20},{222200001117,52,610,20},{222200001120,53,620,20},{222200001123,54,630,20},{222200001126,55,640,20},{222200001129,56,650,20},{222200001132,57,660,20},{222200001135,58,670,20},{222200001138,59,680,20},{222200001141,60,690,20},
{222200001144,61,700,20},{222200001147,62,710,20},{222200001150,63,720,20},{222200001153,64,730,20},{222200001156,65,740,20},{222200001159,66,750,20},{222200001162,67,760,20},{222200001165,68,770,20},{222200001168,69,780,20},{222200001171,70,790,20},
{222200001174,71,800,20},{222200001177,72,810,20},{222200001180,73,820,20},{222200001183,74,830,20},{222200001186,75,840,20},{222200001189,76,850,20},{222200001192,77,860,20},{222200001195,78,870,20},{222200001198,79,880,20},{222200001201,80,890,20},
{222200001204,81,900,20},{222200001207,82,910,20},{222200001210,83,920,20},{222200001213,84,930,20},{222200001216,85,940,20},{222200001219,86,950,20},{222200001222,87,960,20},{222200001225,88,970,20},{222200001228,89,980,20},{222200001231,90,990,20},
{222200001234,91,1000,20},{222200001237,92,1010,20},{222200001240,93,1020,20},{222200001243,94,1030,20},{222200001246,95,1040,20},{222200001249,96,1050,20},{222200001252,97,1060,20},{222200001255,98,1070,20},{222200001258,99,1080,20},{222200001261,100,1090,20},
};
long CUSTOMER_DATASET[100][3] = {
{9400000001,1,0},{9400000002,2,0},{9400000003,3,0},{9400000004,4,0},{9400000005,5,0},{9400000006,6,0},{9400000007,7,0},{9400000008,8,0},{9400000009,9,0},{9400000010,10,0},
{9400000011,11,0},{9400000012,12,0},{9400000013,13,0},{9400000014,14,0},{9400000015,15,0},{9400000016,16,0},{9400000017,17,0},{9400000018,18,0},{9400000019,19,0},{9400000020,20,0},
{9400000021,21,0},{9400000022,22,0},{9400000023,23,0},{9400000024,24,0},{9400000025,25,0},{9400000026,26,0},{9400000027,27,0},{9400000028,28,0},{9400000029,29,0},{9400000030,30,0},
{9400000031,31,0},{9400000032,32,0},{9400000033,33,0},{9400000034,34,0},{9400000035,35,0},{9400000036,36,0},{9400000037,37,0},{9400000038,38,0},{9400000039,39,0},{9400000040,40,0},
{9400000041,41,0},{9400000042,42,0},{9400000043,43,0},{9400000044,44,0},{9400000045,45,0},{9400000046,46,0},{9400000047,47,0},{9400000048,48,0},{9400000049,49,0},{9400000050,50,0},
{9400000051,51,0},{9400000052,52,0},{9400000053,53,0},{9400000054,54,0},{9400000055,55,0},{9400000056,56,0},{9400000057,57,0},{9400000058,58,0},{9400000059,59,0},{9400000060,60,0},
{9400000061,61,0},{9400000062,62,0},{9400000063,63,0},{9400000064,64,0},{9400000065,65,0},{9400000066,66,0},{9400000067,67,0},{9400000068,68,0},{9400000069,69,0},{9400000070,70,0},
{9400000071,71,0},{9400000072,72,0},{9400000073,73,0},{9400000074,74,0},{9400000075,75,0},{9400000076,76,0},{9400000077,77,0},{9400000078,78,0},{9400000079,79,0},{9400000080,80,0},
{9400000081,81,0},{9400000082,82,0},{9400000083,83,0},{9400000084,84,0},{9400000085,85,0},{9400000086,86,0},{9400000087,87,0},{9400000088,88,0},{9400000089,89,0},{9400000090,90,0},
{9400000091,91,0},{9400000092,92,0},{9400000093,93,0},{9400000094,94,0},{9400000095,95,0},{9400000096,96,0},{9400000097,97,0},{9400000098,98,0},{9400000099,99,0},{9400000100,100,0},
};
    
    
    // Manager reads Inventory Dataset and uploads data to Inventory object.
    Item *n = NULL;
    
    for(int i=0;i<100;i++)
    {
        n = new Item;
        n->ID = INVENTORY_DATASET[i][0];
        name = to_string(INVENTORY_DATASET[i][1]);
        name1 = new char[name.size()+1];
        strcpy(name1,name.c_str());
        n->Name = name1;
        n->Rate = INVENTORY_DATASET[i][2];
        n->Quantity = INVENTORY_DATASET[i][3];
        M.Add_item(n);
    }
    
    // Billing object reads Customer Dataset and uploads data to Customer object.
    CustomerData *cd = NULL;
    
    for(int i=0;i<100;i++)
    {
        cd = new CustomerData;
        cd->ID = CUSTOMER_DATASET[i][0];
        name = to_string(CUSTOMER_DATASET[i][1]);
        name1 = new char[name.size()+1];
        strcpy(name1,name.c_str());
        cd->Name = name1;
        cd->Points = CUSTOMER_DATASET[i][2];
        B->Add_Customer(cd);
    }
    
    
    // Shopping episode -- Test Case
    long Customer_ID1 = 9400000011;
    long Items[3] = {111100000011,222200001114,222200001234};    // Customer wants to buy these items. //More items can be added to Items and Quantities array to buy those.
    int Quantities[3] = {3,1,2};
    B = new Billing(Customer_ID1,I,C); // Billing object
    int nI = sizeof(Items)/sizeof(Items[0]);
    for(int i=0;i<nI;i++)
    {
        B->Buy_item(Items[i],Quantities[i]);
    }
    B->make_payment();
    
    
    
    // Manager checks product information
    long mItems[3] = {111100000011,222200001114,222200001234};
    int nmI = sizeof(mItems)/sizeof(mItems[0]);
    
    for(int i=0;i<nmI;i++)
    {
        M.Get_Product_Info(mItems[i]);
    }
    
// ---------------------------------------------------------------------//
    
// Demo of other Functionalities
    
/*    B->get_Customer_Information(Customer_ID1); // Check Customer Data.
    
    // Adding some new Items
    
    n = new Item;
    n->ID = 115100000001;
    n->Rate = 45.90;
    n->Quantity = 100;
    name = "Bread";
    name1 = new char[name.size()+1];
    strcpy(name1,name.c_str());
    n->Name = name1;
    M.Add_item(n);
    
    n = new Item;
    n->ID = 259100000001;
    n->Rate = 100;
    n->Quantity = 35;
    name = "Butter";
    name1 = new char[name.size()+1];
    strcpy(name1,name.c_str());
    n->Name = name1;
    M.Add_item(n);
    
    n = new Item;
    n->ID = 365100000001;
    n->Rate = 80;
    n->Quantity = 70;
    name = "Milk";
    name1 = new char[name.size()+1];
    strcpy(name1,name.c_str());
    n->Name = name1;
    M.Add_item(n);
    
    
    // Shopping Episode
    
    B = new Billing(9999999999,I,C);
    B->Buy_item(259100000001,3);
    B->Buy_item(115100000001,5);
    B->Buy_item(365100000001,3);
    B->Cancel_item(365100000001); // Customer wanted to cancel this item from list.
    B->change_Quantity(115100000001,-2);    // Customer wanted to change the quantity of product from list.
    B->make_payment();        // As the customer is new, program will ask to provide name and will add this customer to database.
        
    B->get_Customer_Information(9999999999);    // Checking Customer Information
    
    // Demo of other Manager Functionalities
    M.Get_Product_Info(115100000001);
    M.Update_item_Rate(115100000001,90);
    M.change_stock(115100000001,100);
    M.Update_item_Quantity(365100000001,60);

    M.Get_Product_Info(115100000001);
    M.Get_Product_Info(259100000001);
    M.Get_Product_Info(365100000001);
    
    cout<<M.Delete_item(259100000001)<<" deleted."<<"\n";
    M.Get_Product_Info(259100000001);
    cout<<"\n";*/
    
    
    return 0;
}
