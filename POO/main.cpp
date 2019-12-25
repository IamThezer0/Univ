#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>

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
class List{
    public:
        Insurance*head;
        void addNode(Insurance*node);
        void insertFile();
        void changeName(string name);
        void displayCategory();
        void deleteName(string name);
        void displayName(string name);
        void saveFile(string period);
};
// Ma duc sa imi fac un ceai si sa ma pun la serial. :)
// Daca ai chef sa te mai uiti peste astea sa vezi daca sunt ok.
//P.S.: Ti pwp si Craciun Fericit. <3
//receptionat :))


int main(){
    
 }