#include<iostream>
#include<bits/stdc++.h>
#include <windows.h>
#include<io.h>
#include <fcntl.h>
#include <iomanip>

using namespace std;
#define ORDERSIZE 10

string names[5] = {"Margerita","Peperroni","Coke","Dew","Gralic Bread"};
int prices[5] = {250,300,50,50,100};
bool veg[5] = {true,false,true,true,true};
char categories[5] = {'P','P','D','D','S'};

void WelcomeDisplay();
void LoginDISPLAY();
void AdminOptionDISPLAY();
void DatabaseDISPLAY();
void DatabaseHeaderDISPLAY();
void DatabaseFooterDISPLAY();
void EditMenuDISPLAY();
void CustomerOptionsDISPLAY();
template <class T> 
void MenuDISPLAY(T MENU);
template <class Y> 
void CheckoutDISPLAY(Y BILL);


class item
{
    public:
        string name;
        int price;
        bool veg;
        char category;
};

class menu
{
    public:
        vector<item> pizzas;
        vector<item> drinks;
        vector<item> sides;

        menu()
        {
            for(int i=0;i<5;i++)
            {
                item ex;
                ex.name = names[i];
                ex.price = prices[i];
                ex.veg = veg[i];
                ex.category = categories[i];

                if(ex.category == 'P')
                    pizzas.push_back(ex);
                else if(ex.category == 'D')
                    drinks.push_back(ex);
                else if(ex.category == 'S')
                    sides.push_back(ex);
            }
        }

        void addItem()
        {
            HANDLE console_color;
            console_color = GetStdHandle(STD_OUTPUT_HANDLE);

            item temp;

            SetConsoleTextAttribute(console_color, 2);
            cout<<"\nEnter Item-Name Item-Price Item-Veg(1/0) Item-Category(P,D,S) : ";
            SetConsoleTextAttribute(console_color, 7);

            cin>>temp.name>>temp.price>>temp.veg>>temp.category;
            if(temp.category=='P')
                pizzas.push_back(temp);
            else if(temp.category=='D')
                drinks.push_back(temp);
            else if(temp.category=='S')
                sides.push_back(temp);
            else
            {
                SetConsoleTextAttribute(console_color, 4);
                cout<<"Invalid Input\n";
            }
        }

        void removeItem()
        {
            HANDLE console_color;
            console_color = GetStdHandle(STD_OUTPUT_HANDLE);

            char cat; int id;

            SetConsoleTextAttribute(console_color, 2);
            cout<<"Enter Category(P,D,S) & ID of item you want to remove : ";
            SetConsoleTextAttribute(console_color, 7);

            cin>>cat>>id;
            if(cat=='P')
                pizzas.erase(pizzas.begin() + id);
            else if(cat=='D')
                drinks.erase(drinks.begin() + id);
            else if(cat=='S')
                sides.erase(sides.begin() + id);
            else
            {
                SetConsoleTextAttribute(console_color, 4);
                cout<<"Invalid Input\n";
            }
        }

};

template <class T> 
class Stack {

    public:
        Stack();
        void push(T k);
        T pop();
        T topElement();
        bool isFull();
        bool isEmpty();

    private:
        int top;
        T st[ORDERSIZE];
};

template <class T> 
Stack<T>::Stack() { top = -1; }

template <class T> 
void Stack<T>::push(T k)
{

	if (isFull()) {
		cout << "Stack is full\n";
	}
	st[++top] = k;
}

template <class T> 
bool Stack<T>::isEmpty()
{
	if (top == -1)
		return 1;
	else
		return 0;
}

template <class T> 
bool Stack<T>::isFull()
{
	if (top == (ORDERSIZE - 1))
		return 1;
	else
		return 0;
}

template <class T> 
T Stack<T>::pop()
{
	T popped_element = st[top];
	top--;
	return popped_element;
}

template <class T> 
T Stack<T>::topElement()
{
	T top_element = st[top];
	return top_element;
}

class order
{
    public:
        item Item;
        int quantity;

        void addOrder(item item)
        {
            Item = item;
            quantity = 1;
        }
        void addOrder(item item, int quant)
        {
            Item = item;
            quantity = quant;
        }
};

class bill
{   public:
        Stack<order> order_stack;
        int total;
        float subtotal;
        float taxRate;
        bill()
        {
            total=0;
            subtotal=0;
            taxRate=0.075;
        }
        void append(order orderItem)
        {
            order_stack.push(orderItem);
            total += orderItem.Item.price*orderItem.quantity;
            subtotal += orderItem.Item.price*orderItem.quantity*(1+taxRate);
        }
};

class User
{
    public:
        string UserName;
        User()  {   UserName="NULL";    };
        void input();
        virtual void initialize() = 0;
};

class Admin : public User
{
    public:
        string Password="root@123";
        string inputPassword;
        void input();
        bool auth()
        {
            HANDLE console_color;
            console_color = GetStdHandle(STD_OUTPUT_HANDLE);
            
            if(inputPassword==Password)
            {
                SetConsoleTextAttribute(console_color, 6);
                cout<<"\nPassword authenticated. WELCOME "<<UserName<<" !!!\n\n";
                SetConsoleTextAttribute(console_color, 7);
                return true;
            }
            else
            {
                SetConsoleTextAttribute(console_color, 4);
                cout<<"\nPassword INVALID. try again!!\n\n";
                SetConsoleTextAttribute(console_color, 7);
                return false;
            }
        }
        void initialize()
        {
            bool trig= false;
            while(trig==false)
            {
                input();
                trig = auth();
            }
        }
        void changePassword()
        {
            HANDLE console_color;
            console_color = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(console_color, 2);

            string curr, newp;
            cout<<"\nEnter Current Password : ";
            SetConsoleTextAttribute(console_color, 7);
            cin>>curr;
            if(curr==Password)
            {
                SetConsoleTextAttribute(console_color, 2);
                cout<<"Enter New Password :";
                SetConsoleTextAttribute(console_color, 7);
                cin>>newp;
                Password=newp;
                SetConsoleTextAttribute(console_color, 3);
                cout<<"\nPassword Changed Successfully!!\n";
                SetConsoleTextAttribute(console_color, 7);
            }
            else
            {
                SetConsoleTextAttribute(console_color, 4);
                cout<<"\nInvalid Password!! Try Again\n";
                SetConsoleTextAttribute(console_color, 7);
            }
        }
};

class Customer : public User
{
    public:
        int phNo;
        string address;
        float orderAmount;
        void input();
        void initialize()
        {
            input();
        }
};

void User::input()
{
    HANDLE console_color;
    console_color = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(console_color, 2);
    cout<<"\nEnter Name : "; 
    SetConsoleTextAttribute(console_color, 7);
    cin>>UserName;
}
void Admin::input() 
{ 
    User::input(); 

    HANDLE console_color;
    console_color = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(console_color, 2);
    cout<<"Enter Password (default - root@123) : ";
    SetConsoleTextAttribute(console_color, 7); 
    cin>>inputPassword;
}
void Customer::input() 
{ 
    User::input(); 

    HANDLE console_color;
    console_color = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(console_color, 2);
    cout<<"Enter Phone No. : "; 
    SetConsoleTextAttribute(console_color, 7); 
    cin>>phNo;
    SetConsoleTextAttribute(console_color, 2);
    cout<<"Enter Address : "; 
    SetConsoleTextAttribute(console_color, 7); 
    cin>>address;
}

class Database
{   public:
        vector<string> CustomerDataName;
        vector<int> CustomerDataPhNo;
        vector<int> CustomerDataOrderAmount;
        vector<string> CustomerDataAddress;

        void append(Customer x)
        {
            CustomerDataName.push_back(x.UserName);
            CustomerDataPhNo.push_back(x.phNo);
            CustomerDataAddress.push_back(x.address);
            CustomerDataOrderAmount.push_back(x.orderAmount);
        }
        void display()
        {
            DatabaseHeaderDISPLAY();
            for (int i=0; i<CustomerDataName.size(); i++)
                cout<<left<<setw(5)<<i<<setw(14)<<CustomerDataName[i]<<setw(14)<<CustomerDataPhNo[i]<<setw(14)<<CustomerDataAddress[i]<<setw(14)<<CustomerDataOrderAmount[i]<<"\n";

            DatabaseFooterDISPLAY();
        }

        template <typename T>
        void sort(vector<T> a)
        {
            for(int i=0;i<a.size();i++)
                for(int j=0;j<a.size()-i-1;j++)
                    if(a[j]>a[j+1])
                    {
                        swap(CustomerDataName[j], CustomerDataName[j+1]);
                        swap(CustomerDataPhNo[j], CustomerDataPhNo[j+1]);
                        swap(CustomerDataAddress[j], CustomerDataAddress[j+1]);
                        swap(CustomerDataOrderAmount[j], CustomerDataOrderAmount[j+1]);
                    }
        }
};

int main()
{
    Admin ADMIN;
    Database CUSTOMERDATA;
    menu MENU;
    int ch=0;

    WelcomeDisplay();

    while(ch!=3)
    {
        LoginDISPLAY();
        cin>>ch;

        switch(ch)
        {
            case 1:
            {
                ADMIN.initialize();
                while(ch!=4)
                {
                    AdminOptionDISPLAY();
                    cin>>ch;
                    switch(ch)
                    {
                        case 1:
                        {
                            int ch2=0;
                            while(ch2!=2)
                            {
                                DatabaseDISPLAY();
                                cin>>ch2;

                                switch(ch2)
                                {
                                    case 1:
                                    {
                                        CUSTOMERDATA.display();
                                        break;
                                    }
                                    // case 2:
                                    // {
                                    //     CUSTOMERDATA.sort<string>(CUSTOMERDATA.CustomerDataName);
                                    //     CUSTOMERDATA.display();
                                    //     break;
                                    // }
                                    // case 3:
                                    // {
                                    //     CUSTOMERDATA.sort<int>(CUSTOMERDATA.CustomerDataOrderAmount);
                                    //     CUSTOMERDATA.display();
                                    //     break;
                                    // }
                                    case 2:
                                    {
                                        break;
                                    }
                                    default :
                                    {
                                        cout<<"INVALID CHOICE!! INPUT AGAIN\n";
                                    }
                                }
                            }  
                            break;
                        }
                        case 2:
                        {
                            int ch2=0;
                            while(ch2!=4)
                            {
                                EditMenuDISPLAY();
                                cin>>ch2;

                                switch(ch2)
                                {
                                    case 1:
                                    {
                                        MenuDISPLAY(MENU);
                                        break;
                                    }
                                    case 2:
                                    {
                                        MENU.addItem();
                                        MenuDISPLAY(MENU);
                                        break;
                                    }
                                    case 3:
                                    {
                                        MenuDISPLAY(MENU);
                                        MENU.removeItem();
                                        MenuDISPLAY(MENU);
                                        break;
                                    }
                                    case 4:
                                    {
                                        break;
                                    }
                                    default :
                                    {
                                        cout<<"INVALID CHOICE!! INPUT AGAIN\n";
                                    }
                                }
                            }
                            break;
                        }
                        case 3:
                        {
                            ADMIN.changePassword();
                            break;
                        }
                        case 4:
                        {
                            break;
                        }
                        default :
                        {
                            cout<<"INVALID CHOICE!! INPUT AGAIN\n";
                        }
                    }
                }
                ch=1;
                break;
            }

            case 2:
            {
                Customer CUSTOMER;
                CUSTOMER.initialize();
                bill BILL;
                while(ch!=4 && ch!=3)
                {
                    CustomerOptionsDISPLAY();
                    cin>>ch;
                    switch(ch)
                    {
                        case 1:
                        {
                            MenuDISPLAY(MENU);
                            break;
                        }
                        case 2:
                        {
                            HANDLE console_color;
                            console_color = GetStdHandle(STD_OUTPUT_HANDLE);

                            string ch2="Yes";
                            while(ch2!="No")
                            {
                                char cat; int ID, num;
                                order temp;
                                SetConsoleTextAttribute(console_color, 2);
                                cout<<"\nEnter Item Category , Item ID , Quantity : ";
                                SetConsoleTextAttribute(console_color, 7);
                                cin>>cat>>ID>>num;
                                if(cat=='P')
                                {
                                    if(ID<MENU.pizzas.size())
                                    {
                                        temp.addOrder(MENU.pizzas[ID],num);
                                        BILL.append(temp);
                                    }
                                    else
                                    {
                                        SetConsoleTextAttribute(console_color, 4);
                                        cout<<"Invalid Item!!\n";
                                        SetConsoleTextAttribute(console_color, 7);
                                    }
                                }
                                else if(cat=='D')
                                {
                                    if(ID<MENU.drinks.size())
                                    {
                                        temp.addOrder(MENU.drinks[ID],num);
                                        BILL.append(temp);
                                    }
                                    else
                                    {
                                        SetConsoleTextAttribute(console_color, 4);
                                        cout<<"Invalid Item!!\n";
                                        SetConsoleTextAttribute(console_color, 7);
                                    }
                                }
                                else if(cat=='S')
                                {
                                    if(ID<MENU.sides.size())
                                    {
                                        temp.addOrder(MENU.sides[ID],num);
                                        BILL.append(temp);
                                    }
                                    else
                                    {
                                        SetConsoleTextAttribute(console_color, 4);
                                        cout<<"Invalid Item!!\n";
                                        SetConsoleTextAttribute(console_color, 7);
                                    }
                                }
                                else
                                {
                                    SetConsoleTextAttribute(console_color, 4);
                                    cout<<"Invalid Category..Try Again!!";
                                    SetConsoleTextAttribute(console_color, 7);
                                }

                                SetConsoleTextAttribute(console_color, 1);
                                cout<<"\nDo You Want To Add Another Item?";
                                SetConsoleTextAttribute(console_color, 2);
                                cout<<" ( Yes / No ) : ";
                                SetConsoleTextAttribute(console_color, 7);
                                cin>>ch2;
                            }
                            break;
                        }
                        case 3:
                        {
                            CheckoutDISPLAY(BILL);
                            CUSTOMER.orderAmount = BILL.total;
                            CUSTOMERDATA.append(CUSTOMER);
                            break;
                        }
                        case 4:
                        {
                            CUSTOMER.orderAmount = BILL.total;
                            CUSTOMERDATA.append(CUSTOMER);
                            break;
                        }
                        default :
                        {
                            cout<<"INVALID CHOICE!! INPUT AGAIN\n";
                        }
                    }
                }
                ch=2;
                break;
            }

            case 3:
            {
                return 0;
            }

            default :
            {
                cout<<"INVALID CHOICE!! INPUT AGAIN\n";
            }
        }
    }
    
    return 0;
}














void WelcomeDisplay()
{
    _setmode(_fileno(stdout), _O_U16TEXT);

    HANDLE console_color;
	console_color = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(console_color, 6);
    wcout<<L"\n\nＷＥＬＣＯＭＥ ＴＯ ＴＨＥ ＲＥＳＴＡＵＲＡＮＴ\n";
    SetConsoleTextAttribute(console_color, 7);
}
void LoginDISPLAY()
{
    _setmode(_fileno(stdout), _O_U16TEXT);

    HANDLE console_color;
	console_color = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(console_color, 7);

    wcout<<L"\n\u250f";
    for(int i=0;i<7;i++)
        wcout<<L"\u2501";
    wcout<<setw(2)<<" ";
    SetConsoleTextAttribute(console_color, 3);
    wcout<<"LOGIN";
    SetConsoleTextAttribute(console_color, 7);
    wcout<<setw(4)<<" ";
    for(int i=0;i<7;i++)
        wcout<<L"\u2501";
    wcout<<L"\u2513\n";
    wcout<<left<<L"\u2503"<<setw(25)<<" "<<L"\u2503\n";
    wcout<<left<<L"\u2503"<<setw(5)<<" "<<setw(15)<<"1 >> Admin"<<setw(5)<<" "<<L"\u2503\n";
    wcout<<left<<L"\u2503"<<setw(5)<<" "<<setw(15)<<"2 >> Customer"<<setw(5)<<" "<<L"\u2503\n";
    wcout<<left<<L"\u2503"<<setw(5)<<" "<<setw(15)<<"3 >> Exit"<<setw(5)<<" "<<L"\u2503\n";
    wcout<<left<<L"\u2503"<<setw(25)<<" "<<L"\u2503\n";
    wcout<<L"\u2517";
    for(int i=0;i<25;i++)
        wcout<<L"\u2501";
    wcout<<L"\u251B\n";
    SetConsoleTextAttribute(console_color, 2);
    wcout<<"Enter your choice : ";
    SetConsoleTextAttribute(console_color, 7);

    _setmode(_fileno(stdout), _O_TEXT);
}

void AdminOptionDISPLAY()
{
    _setmode(_fileno(stdout), _O_U16TEXT);

    HANDLE console_color;
	console_color = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(console_color, 7);

    wcout<<L"\n\u250f";
    for(int i=0;i<7;i++)
        wcout<<L"\u2501";
    wcout<<setw(4)<<" ";
    SetConsoleTextAttribute(console_color, 3);
    wcout<<"ADMIN OPTIONS";
    SetConsoleTextAttribute(console_color, 7);
    wcout<<setw(5)<<" ";
    for(int i=0;i<7;i++)
        wcout<<L"\u2501";
    wcout<<L"\u2513\n";
    wcout<<left<<L"\u2503"<<setw(36)<<" "<<L"\u2503\n";
    wcout<<left<<L"\u2503"<<setw(6)<<" "<<setw(22)<<"1 >> Customer Database"<<setw(8)<<" "<<L"\u2503\n";
    wcout<<left<<L"\u2503"<<setw(6)<<" "<<setw(22)<<"2 >> Edit Menu"<<setw(8)<<" "<<L"\u2503\n";
    wcout<<left<<L"\u2503"<<setw(6)<<" "<<setw(22)<<"3 >> Change Password"<<setw(8)<<" "<<L"\u2503\n";
    wcout<<left<<L"\u2503"<<setw(6)<<" "<<setw(22)<<"4 >> Logout"<<setw(8)<<" "<<L"\u2503\n";
    wcout<<left<<L"\u2503"<<setw(36)<<" "<<L"\u2503\n";
    wcout<<L"\u2517";
    for(int i=0;i<36;i++)
        wcout<<L"\u2501";
    wcout<<L"\u251B\n";
    SetConsoleTextAttribute(console_color, 2);
    wcout<<"Enter your choice : ";
    SetConsoleTextAttribute(console_color, 7);

    _setmode(_fileno(stdout), _O_TEXT);
}

void DatabaseDISPLAY()
{
    HANDLE console_color;
	console_color = GetStdHandle(STD_OUTPUT_HANDLE);
    _setmode(_fileno(stdout), _O_U16TEXT);

    SetConsoleTextAttribute(console_color, 7);

    wcout<<L"\n\u250f";
    for(int i=0;i<9;i++)
        wcout<<L"\u2501";
    wcout<<setw(5)<<" ";
    SetConsoleTextAttribute(console_color, 3);
    wcout<<"DATABASE";
    SetConsoleTextAttribute(console_color, 7);
    wcout<<setw(5)<<" ";
    for(int i=0;i<9;i++)
        wcout<<L"\u2501";
    wcout<<L"\u2513\n";
    wcout<<left<<L"\u2503"<<setw(36)<<" "<<L"\u2503\n";
    wcout<<left<<L"\u2503"<<setw(6)<<" "<<setw(22)<<"1 >> View Database"<<setw(8)<<" "<<L"\u2503\n";
    // wcout<<left<<L"\u2503"<<setw(6)<<" "<<setw(22)<<"2 >> Sort By Name"<<setw(8)<<" "<<L"\u2503\n";
    // wcout<<left<<L"\u2503"<<setw(6)<<" "<<setw(22)<<"3 >> Sort By Order Amount"<<setw(5)<<" "<<L"\u2503\n";
    wcout<<left<<L"\u2503"<<setw(6)<<" "<<setw(22)<<"2 >> Go Back"<<setw(8)<<" "<<L"\u2503\n";
    wcout<<left<<L"\u2503"<<setw(36)<<" "<<L"\u2503\n";
    wcout<<L"\u2517";
    for(int i=0;i<36;i++)
        wcout<<L"\u2501";
    wcout<<L"\u251B\n";
    SetConsoleTextAttribute(console_color, 2);
    wcout<<"Enter your choice : ";
    SetConsoleTextAttribute(console_color, 7);

    _setmode(_fileno(stdout), _O_TEXT);
}

void DatabaseHeaderDISPLAY()
{
    HANDLE console_color;
	console_color = GetStdHandle(STD_OUTPUT_HANDLE);
    _setmode(_fileno(stdout), _O_U16TEXT);

    wcout<<"\n\n";
    for(int i=0;i<65;i++)
        wcout<<L"\u2501";
    wcout<<"\n";

    SetConsoleTextAttribute(console_color, 5);
    wcout<<left<<setw(5)<<"ID"<<setw(14)<<"Name"<<setw(14)<<"Phone No."<<setw(14)<<"Address"<<setw(14)<<"Order Amount";
    SetConsoleTextAttribute(console_color, 7);
    
    wcout<<"\n";
    for(int i=0;i<65;i++)
        wcout<<L"\u2501";
    wcout<<"\n";

    _setmode(_fileno(stdout), _O_TEXT);
}

void DatabaseFooterDISPLAY()
{
    _setmode(_fileno(stdout), _O_U16TEXT);
    wcout<<"\n";
    for(int i=0;i<65;i++)
        wcout<<L"\u2501";
    wcout<<"\n\n";

    _setmode(_fileno(stdout), _O_TEXT);
}

void EditMenuDISPLAY()
{
    _setmode(_fileno(stdout), _O_U16TEXT);

    HANDLE console_color;
	console_color = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(console_color, 7);

    wcout<<L"\n\u250f";
    for(int i=0;i<7;i++)
        wcout<<L"\u2501";
    wcout<<setw(5)<<" ";
    SetConsoleTextAttribute(console_color, 3);
    wcout<<"MENU OPTIONS";
    SetConsoleTextAttribute(console_color, 7);
    wcout<<setw(5)<<" ";
    for(int i=0;i<7;i++)
        wcout<<L"\u2501";
    wcout<<L"\u2513\n";
    wcout<<left<<L"\u2503"<<setw(36)<<" "<<L"\u2503\n";
    wcout<<left<<L"\u2503"<<setw(6)<<" "<<setw(22)<<"1 >> View Menu"<<setw(8)<<" "<<L"\u2503\n";
    wcout<<left<<L"\u2503"<<setw(6)<<" "<<setw(22)<<"2 >> Add Item"<<setw(8)<<" "<<L"\u2503\n";
    wcout<<left<<L"\u2503"<<setw(6)<<" "<<setw(22)<<"3 >> Remove Item"<<setw(8)<<" "<<L"\u2503\n";
    wcout<<left<<L"\u2503"<<setw(6)<<" "<<setw(22)<<"4 >> Go Back"<<setw(8)<<" "<<L"\u2503\n";
    wcout<<left<<L"\u2503"<<setw(36)<<" "<<L"\u2503\n";
    wcout<<L"\u2517";
    for(int i=0;i<36;i++)
        wcout<<L"\u2501";
    wcout<<L"\u251B\n";
    SetConsoleTextAttribute(console_color, 2);
    wcout<<"Enter your choice : ";
    SetConsoleTextAttribute(console_color, 7);

    _setmode(_fileno(stdout), _O_TEXT);
}

template <class T> 
void MenuDISPLAY(T MENU)
{
     _setmode(_fileno(stdout), _O_U16TEXT);

    HANDLE console_color;
	console_color = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(console_color, 7);

    int size = ( MENU.pizzas.size() > MENU.drinks.size() ? 
                    ( MENU.pizzas.size() > MENU.sides.size() ?
                        MENU.pizzas.size() : MENU.sides.size()) :  
                            ( MENU.drinks.size()> MENU.sides.size() ? 
                                MENU.drinks.size() : MENU.sides.size()) );

    wcout<<L"\n\u250f";
    for(int i=0;i<50;i++)
        wcout<<L"\u2501";
    wcout<<setw(5)<<" ";
    SetConsoleTextAttribute(console_color, 3);
    wcout<<"MENU";
    SetConsoleTextAttribute(console_color, 7);
    wcout<<setw(5)<<" ";
    for(int i=0;i<50;i++)
        wcout<<L"\u2501";
    wcout<<L"\u2513\n";

    wcout<<left<<L"\u2503"<<setw(114)<<" "<<L"\u2503\n";

    wcout<<left<<L"\u2503";
    SetConsoleTextAttribute(console_color, 6);
    wcout<<setw(14)<<" "<<"Pizzas (P)"<<setw(14)<<" ";
    wcout<<setw(14)<<" "<<"Drinks (D)"<<setw(14)<<" ";
    wcout<<setw(15)<<" "<<"Sides (S)"<<setw(14)<<" ";
    SetConsoleTextAttribute(console_color, 7);
    wcout<<L"\u2503\n";

    wcout<<left<<L"\u2503";
    wcout<<setw(3)<<" "<<"--------------------------------"<<setw(3)<<" ";
    wcout<<setw(3)<<" "<<"--------------------------------"<<setw(3)<<" ";
    wcout<<setw(3)<<" "<<"--------------------------------"<<setw(3)<<" ";
    wcout<<L"\u2503\n";

    wcout<<left<<L"\u2503";
    SetConsoleTextAttribute(console_color, 5);
    wcout<<setw(5)<<" "<<setw(3)<<"ID"<<setw(13)<<"Name"<<setw(9)<<"Price"<<setw(3)<<"Veg"<<setw(5)<<" ";
    wcout<<setw(5)<<" "<<setw(3)<<"ID"<<setw(13)<<"Name"<<setw(9)<<"Price"<<setw(3)<<"Veg"<<setw(5)<<" ";
    wcout<<setw(5)<<" "<<setw(3)<<"ID"<<setw(13)<<"Name"<<setw(9)<<"Price"<<setw(3)<<"Veg"<<setw(5)<<" ";
    SetConsoleTextAttribute(console_color, 7);
    wcout<<L"\u2503\n";

    wcout<<left<<L"\u2503";
    wcout<<setw(3)<<" "<<"--------------------------------"<<setw(3)<<" ";
    wcout<<setw(3)<<" "<<"--------------------------------"<<setw(3)<<" ";
    wcout<<setw(3)<<" "<<"--------------------------------"<<setw(3)<<" ";
    wcout<<L"\u2503\n";

    for(int i=0;i<size;i++)
    {
        wcout<<left<<L"\u2503";

        if(i<MENU.pizzas.size())
        {
            _setmode(_fileno(stdout), _O_TEXT);
            cout<<setw(5)<<" "<<left<<setw(3)<<i<<setw(13)<<MENU.pizzas[i].name<<setw(9)<<MENU.pizzas[i].price;
            
            _setmode(_fileno(stdout), _O_U16TEXT);
            if(MENU.pizzas[i].veg)
            {
                SetConsoleTextAttribute(console_color, 2);
                wcout<<setw(3)<<"-"<<setw(5)<<" ";
            }
            else
            {
                SetConsoleTextAttribute(console_color, 4);
                wcout<<setw(3)<<"X"<<setw(5)<<" ";
            }
            SetConsoleTextAttribute(console_color, 7);
        }
        else
        {
            wcout<<setw(38)<<" ";
        }

        if(i<MENU.drinks.size())
        {
            _setmode(_fileno(stdout), _O_TEXT);
            cout<<setw(5)<<" "<<left<<setw(3)<<i<<setw(13)<<MENU.drinks[i].name<<setw(9)<<MENU.drinks[i].price;
            
            _setmode(_fileno(stdout), _O_U16TEXT);
            if(MENU.drinks[i].veg)
            {
                SetConsoleTextAttribute(console_color, 2);
                wcout<<setw(3)<<"-"<<setw(5)<<" ";
            }
            else
            {
                SetConsoleTextAttribute(console_color, 4);
                wcout<<setw(3)<<"X"<<setw(5)<<" ";
            }
            SetConsoleTextAttribute(console_color, 7);
        }
        else
        {
            wcout<<setw(38)<<" ";
        }

        if(i<MENU.sides.size())
        {
            _setmode(_fileno(stdout), _O_TEXT);
            cout<<setw(5)<<" "<<left<<setw(3)<<i<<setw(13)<<MENU.sides[i].name<<setw(9)<<MENU.sides[i].price;
            
            _setmode(_fileno(stdout), _O_U16TEXT);
            if(MENU.sides[i].veg)
            {
                SetConsoleTextAttribute(console_color, 2);
                wcout<<setw(3)<<"-"<<setw(5)<<" ";
            }
            else
            {
                SetConsoleTextAttribute(console_color, 4);
                wcout<<setw(3)<<"X"<<setw(5)<<" ";
            }
            SetConsoleTextAttribute(console_color, 7);
        }
        else
        {
            wcout<<setw(38)<<" ";
        }

        wcout<<L"\u2503\n";
    }


    wcout<<left<<L"\u2503"<<setw(114)<<" "<<L"\u2503\n";

    wcout<<L"\u2517";
    for(int i=0;i<114;i++)
        wcout<<L"\u2501";
    wcout<<L"\u251B\n";

    _setmode(_fileno(stdout), _O_TEXT);

}

void CustomerOptionsDISPLAY()
{
    _setmode(_fileno(stdout), _O_U16TEXT);

    HANDLE console_color;
	console_color = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(console_color, 7);

    wcout<<L"\n\u250f";
    for(int i=0;i<6;i++)
        wcout<<L"\u2501";
    wcout<<setw(4)<<" ";
    SetConsoleTextAttribute(console_color, 3);
    wcout<<"CUSTOMER OPTIONS";
    SetConsoleTextAttribute(console_color, 7);
    wcout<<setw(4)<<" ";
    for(int i=0;i<6;i++)
        wcout<<L"\u2501";
    wcout<<L"\u2513\n";
    wcout<<left<<L"\u2503"<<setw(36)<<" "<<L"\u2503\n";
    wcout<<left<<L"\u2503"<<setw(6)<<" "<<setw(22)<<"1 >> View Menu"<<setw(8)<<" "<<L"\u2503\n";
    wcout<<left<<L"\u2503"<<setw(6)<<" "<<setw(22)<<"2 >> Add Items"<<setw(8)<<" "<<L"\u2503\n";
    wcout<<left<<L"\u2503"<<setw(6)<<" "<<setw(22)<<"3 >> Checkout"<<setw(8)<<" "<<L"\u2503\n";
    wcout<<left<<L"\u2503"<<setw(6)<<" "<<setw(22)<<"4 >> Logout"<<setw(8)<<" "<<L"\u2503\n";
    wcout<<left<<L"\u2503"<<setw(36)<<" "<<L"\u2503\n";
    wcout<<L"\u2517";
    for(int i=0;i<36;i++)
        wcout<<L"\u2501";
    wcout<<L"\u251B\n";
    SetConsoleTextAttribute(console_color, 2);
    wcout<<"Enter your choice : ";
    SetConsoleTextAttribute(console_color, 7);

    _setmode(_fileno(stdout), _O_TEXT);
}

template <class Y> 
void CheckoutDISPLAY(Y BILL)
{
    _setmode(_fileno(stdout), _O_U16TEXT);

    HANDLE console_color;
	console_color = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(console_color, 7);

    wcout<<"   __";
    for(int i=0;i<60;i++)
        wcout<<"_";
    wcout<<"\n";

    wcout<<" / \\ ";
    for(int i=0;i<60;i++)
        wcout<<" ";
    wcout<<"\\.\n";

    wcout<<"|   |";
    for(int i=0;i<23;i++)
        wcout<<" ";
    SetConsoleTextAttribute(console_color, 6);
    wcout<<"ORDER SUMMARY ";
    SetConsoleTextAttribute(console_color, 7);
    for(int i=0;i<23;i++)
        wcout<<" ";
    wcout<<"|.\n";

    wcout<<" \\_ |";
    for(int i=0;i<17;i++)
        wcout<<" ";
    wcout<<"--------------------------";
    for(int i=0;i<17;i++)
        wcout<<" ";
    wcout<<"|.\n";

    wcout<<"    |";
    for(int i=0;i<60;i++)
        wcout<<" ";
    wcout<<"|.\n";

    wcout<<"    |";
    SetConsoleTextAttribute(console_color, 5);
    wcout<<setw(6)<<" "<<left<<setw(12)<<"Item Name"<<setw(12)<<"Quantity"<<setw(12)<<"Unit Price"<<setw(12)<<"Price"<<setw(6)<<" ";
    SetConsoleTextAttribute(console_color, 7);
    wcout<<"|.\n";

    wcout<<"    |";
    for(int i=0;i<5;i++)
        wcout<<" ";
    for(int i=0;i<50;i++)
        wcout<<"-";
    for(int i=0;i<5;i++)
        wcout<<" ";
    wcout<<"|.\n";

    order temp;
    _setmode(_fileno(stdout), _O_TEXT);
    while(!BILL.order_stack.isEmpty())
    {
        temp = BILL.order_stack.pop();
        cout<<"    |";
        cout<<setw(6)<<" "<<left<<setw(12)<<temp.Item.name<<setw(12)<<temp.quantity<<setw(12)<<temp.Item.price<<setw(12)<<temp.Item.price*temp.quantity<<setw(6)<<" ";
        cout<<"|.\n";
    }

    cout<<"    |";
    for(int i=0;i<5;i++)
        cout<<" ";
    for(int i=0;i<50;i++)
        cout<<"-";
    for(int i=0;i<5;i++)
        cout<<" ";
    cout<<"|.\n";

    cout<<"    |"<<setw(30)<<" "<<setw(12)<<"Total"<<setw(13)<<BILL.total<<setw(5)<<" ";
    cout<<"|.\n";

    cout<<"    |"<<setw(30)<<" "<<setw(12)<<"TaxRate"<<setw(13)<<BILL.taxRate*100<<setw(5)<<" ";
    cout<<"|.\n";

    cout<<"    |"<<setw(30)<<" "<<setw(12)<<"Subtotal";
    SetConsoleTextAttribute(console_color, 2);
    cout<<setw(13)<<BILL.subtotal<<setw(5)<<" ";
    SetConsoleTextAttribute(console_color, 7);
    cout<<"|.\n";

    _setmode(_fileno(stdout), _O_U16TEXT);

    wcout<<"    |";
    for(int i=0;i<5;i++)
        wcout<<" ";
    for(int i=0;i<50;i++)
        wcout<<"-";
    for(int i=0;i<5;i++)
        wcout<<" ";
    wcout<<"|.\n";

    wcout<<"    |";
    for(int i=0;i<60;i++)
        wcout<<" ";
    wcout<<"|.\n";

    wcout<<"    |"<<setw(11)<<" ";
    SetConsoleTextAttribute(console_color, 6);
    wcout<<"!! THANK YOU FOR PLACING YOUR ORDER !!";
    SetConsoleTextAttribute(console_color, 7);
    wcout<<setw(11)<<" "<<"|.\n";

    wcout<<"    |";
    for(int i=0;i<60;i++)
        wcout<<" ";
    wcout<<"|.\n";

    wcout<<"    |   ";
    for(int i=0;i<57;i++)
        wcout<<"_";
    wcout<<"|___\n";

    wcout<<"    |  /";
    for(int i=0;i<57;i++)
        wcout<<" ";
    wcout<<"   /.\n";

    wcout<<"    \\_/_";
    for(int i=0;i<57;i++)
        wcout<<"_";
    wcout<<"__/.\n";
}