#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <ostream>
#include <istream>

using namespace std;

class List;

class Exception{
    public:
    string message;
    int data;
    Exception()
    {
        message = "";
        data = 0;
    }
    Exception(string mesage, int data)
    {
        message = mesage;
        data = data;
    }
};
class Insurance{
    string firstName,
           lastName;
    int CNP,
        period,
        type;
        Insurance *next;
public:
    Insurance( string f_name, string l_name, int cod, int per, int tip)
    {
        firstName = f_name;
        lastName = l_name;
        CNP = cod;
        period = per;
        type = tip; 
        next = NULL;
    }
    void setName(string newName)
    {
        firstName = newName;
    }
    virtual void display()
    {
        cout<<"------------------------------------\n";
        cout<<"First name is : "<<firstName<<endl;
        cout<<"Last name is : "<<lastName<<endl;
        cout<<"The CNP of the client is: "<<CNP<<endl;
        cout<<"The period of insurance is: "<<period<<endl;
    }
    friend class List;
};
class travelInsurance : public Insurance{
    string destination;
public:
    travelInsurance(string f_name, string l_name, int cod, int per, int tip, string dest) : Insurance(f_name, l_name,cod,per,tip)
    {
        destination = dest;
    }
    void display()
    {
        Insurance::display();
        cout<<"The destination of travel is: "<<destination<<endl; 
    }
    friend class List;
};

class carInsurance : public Insurance
{
    string carType;
    string carModel;
public:
    carInsurance(string f_name, string l_name, int cod, int per, int tip, string car_t, string car_m) : Insurance( f_name, l_name, cod, per, tip)
    {
        carType = car_t;
        carModel = car_m;
    }
    void display()
    {
        Insurance::display();
        cout<<"The type of the car is: "<<carType <<endl;
        cout<<"The model of the car is: "<<carModel<<endl;
    }
    friend class List;
};
class Overload
{
    string frt_name,
           lst_name;
    int CeNePe, // plm daca e schimbi tu, nu am inspiratie acum.
        periode, //same here.
        tippp;
public:
    friend ostream &operator <<(ostream &out, Overload &ov);
    friend istream &operator >>(istream &in, Overload &ov);

    string returnfrsName(){
        return frt_name;
    }
    string returnlst_name(){
        return lst_name;
    }
    int returnCNP(){
        return CeNePe;
    }
    int returnPeriode(){
        return periode;
    }
    int returnType(){
        return tippp;
    }
};
ostream &operator <<(ostream &out, Overload &ov)
{
    cout<<"\n The insurance dates will be required soon: "<<endl;
    cout<<endl;
    return out;
}

istream &operator >>(istream &in, Overload &ov)
{
    cout<<"\nGive the first name of the insured: "<<endl;
    cin>>ov.frt_name;
    cout<<"\nGive the last name of the insured: "<<endl;
    cin>>ov.lst_name;
    cout<<"\nGive the CNP of the insured: "<<endl;
    cin>>ov.CeNePe;
    cout<<"\nGive the period of the insurance: "<<endl;
    cin>>ov.periode;
    cout<<"\nGive the type of insurance: "<<endl;
    cin>>ov.tippp;
    return in;
}
class List{
    public:
        Insurance*head;
        void addNode(Insurance*node);
        void insertFile();
        void changeName(string name, string nouName);
        void displayCategory();
        void deleteName(string name);
        void displayName(string name);
        void saveFile(string period);
};

void List::addNode(Insurance *add)
{
    Insurance *obj;
    obj = head;
    if(obj)
    {
        if(add->lastName < obj->lastName)
        {
            add->next = head;
            head = add;
        }
        else
        {  
             while(obj->next && (obj->next)->lastName < add->firstName)
                obj = obj->next;
            add->next = obj-> next;
            obj->next = add;
        }
        
    }
    else
        head = add;
}

void List::changeName(string name, string nouName)
{
    Insurance *obj;
    obj = head;
    while(obj)
    {
        if(name == nouName)
            obj->setName(nouName);
        obj=obj->next;
    }
}

//P.S.: Ti pwp si Craciun Fericit. <3
//receptionat :))
// Coma alcoolica fericita <3


int main(){
    
 }