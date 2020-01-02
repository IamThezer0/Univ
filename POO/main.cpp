#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <ostream>
#include <istream>
#include <fstream>

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
           lastName,
           period;
    int CNP,
        type;
        Insurance *next;
public:
    Insurance( string f_name, string l_name, int cod, string per, int tip)
    {
        firstName = f_name;
        lastName = l_name;
        CNP = cod;
        period = per;
        type = tip; 
        next = NULL;
    }
    int getType(){
        return type;
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
        cout<<"Type: "<<getType()<<endl;
    }
    virtual void displayFile(){
        ofstream file;
        file.open("file/path");
        if(file.is_open()){
            file<<getType()<<" ";
            file<<firstName<<" ";
            file<<lastName<<" ";
            file<<CNP<<" ";
            file<<period<<" ";
            file.close();
        }else
        {
                cout<<"\nnu se poate deschide fisierul!";
        }
        
    }
    friend class List;
};
class travelInsurance : public Insurance{
    string destination;
public:
    travelInsurance(string f_name, string l_name, int cod, string per, int tip, string dest) : Insurance(f_name, l_name,cod,per,tip)
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
    carInsurance(string f_name, string l_name, int cod, string per, int tip, string car_t, string car_m) : Insurance( f_name, l_name, cod, per, tip)
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
           lst_name,
           period;
    int cnp, // plm daca e schimbi tu, nu am inspiratie acum.
        tip;
public:
    friend ostream &operator <<(ostream &out, Overload &ov);
    friend istream &operator >>(istream &in, Overload &ov);
//am impresia ca astea nu trebuie neaparat
//le comentez momentan sa vedem
    string returnfrsName(){
        return frt_name;
    }
    string returnlst_name(){
        return lst_name;
    }
    int returnCNP(){
        return cnp;
    }
    string returnPeriod(){
        return period;
    }
    int returnType(){
        return tip;
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
    try{
        cout<<"\nGive the CNP of the insured: "<<endl;
        cin>>ov.cnp;
        if(ov.cnp<0)
            throw Exception("valoarea este invalida!!",ov.cnp);
    }
    catch(Exception ex){
        do{
            cout<<"introduceti cnp valid: "<<endl;
            cin>>ov.cnp;
        }while(ov.cnp<0);
    }
    cout<<"\nGive the period of the insurance: "<<endl;
    cin>>ov.period;
    cout<<"\nGive the type of insurance: "<<endl;
    cin>>ov.tip;
    return in;
}
class List{
    public:
        Insurance*head;
        void addNode(Insurance*node);
        void insert();
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
             while(obj->next && (obj->next)->lastName < add->lastName)
                obj = obj->next;
            add->next = obj-> next;
            obj->next = add;
        }
        
    }
    else
        head = add;
}

void List::changeName(string name, string newName)
{
    Insurance *obj;
    obj = head;
    while(obj)
    {
        if(name == newName)
            obj->setName(newName);
        obj=obj->next;
    }
}
void citireFisier(List &l){//citirea din fisier
    ifstream file("file_path.txt");
    string fileLine,
            nume="Nume",
            prenume="Prenume",
            destinatie="Destinatie",
            perioada="Perioada",
            marcaAuto="Marca auto",
            modelAuto="Model auto";
    int cnp,tip;
    travelInsurance *ti;
    carInsurance *ci;
    if(file.is_open()){
        while(getline(file,fileLine)){
            tip=stoi(fileLine,nullptr,10);
            cout<<"\n"<<tip;
            if(tip==0){
                ti=new travelInsurance(nume,prenume,cnp,perioada,tip,destinatie);
                l.addNode(ti);
            }
            else{
                ci=new carInsurance(nume,prenume,cnp,perioada,tip,marcaAuto,modelAuto);
                l.addNode(ci);
            }
        }
        file.close();
    }else
        cout<<"\nFile cannot be opened!!";

}
void List::insert(){
    string carType,
            carModel,
            destination;
    Insurance *ins;
    Overload stream;
    cout<<stream;
    cin>>stream;
    if(stream.returnType()==0)//daca s-a ales travel insurance
    {
        travelInsurance*ti;
        
        cout<<"Destination: "<<endl;
        cin>>destination;
        ti=new travelInsurance(stream.returnfrsName(),stream.returnlst_name(),stream.returnCNP(),stream.returnPeriod(),stream.returnType(),destination);
        ins=ti;
        addNode(ti);
    }else{
        carInsurance*ci;
        cout<<"The type of the car is: "<<endl;
        cin>>carType;
        cout<<"The model of the car is: "<<endl;
        cin>>carModel;
        ci=new carInsurance(stream.returnfrsName(),stream.returnlst_name(),stream.returnCNP(),stream.returnPeriod(),stream.returnType(),carType,carModel);
        ins=ci;
        addNode(ins);
    }
}
void List::displayCategory(){
    Insurance*ins;
    ins=head;
    if(!ins)
        cout<<"\nEmpty list!";
    else{
        cout<<"Car insurance: ";
        while(ins){
            if(ins->type==0){
                ins->display();
                ins->displayFile();
            }
            ins=ins->next;
        }
        ins=head;
        cout<<"Travel insurance: ";
        while(ins){
            if(ins->type==1){
                ins->display();
                ins->displayFile();
            }
            ins=ins->next;
        }
    }
}

//P.S.: Ti pwp si Craciun Fericit. <3
//receptionat :))
// Coma alcoolica fericita <3
//ba ,dc plm scriem tot in engleza ? :D :D
//am schimbat perioada din int in string, ex(2019-2020)

int main(){
    
 }