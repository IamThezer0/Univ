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
        file.open("F:/univer/proiect/Univ/POO/fileDocument.txt");
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
    virtual void fileWrite(){
        ofstream file;
        file.open("F:/univer/proiect/Univ/POO/newFile.txt",ios::out|ios::app);
        file<<getType()<<" "<<firstName<<" "<<lastName<<" "<<CNP<<" "<<period<<" ";
        file.close();
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
    void fileWrite(){
        Insurance::fileWrite();
        ofstream file;
        file.open("F:/univer/proiect/Univ/POO/newFile.txt",ios::out|ios::app);
        file<<destination;
        file.close();
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
    void fileWrite(){
        Insurance::fileWrite();
        ofstream file;
        file.open("F:/univer/proiect/Univ/POO/newFile.txt",ios::out|ios::app);
        file<<carType<<" "<<carModel<<endl;
        file.close();
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
        void deleteName(string fName, string lName);
        void displayName(string name);
        void saveFilePeriod(string period);
        void saveFile();
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


void citireFisier(List &l){//citirea din fisier
    ifstream file("F:/univer/proiect/Univ/POO/fileDocument.txt");
    string fileLine,
            nume="Nume",
            prenume="Prenume",
            destinatie="Destinatie",
            perioada="Perioada",
            marcaAuto="Marca auto",
            modelAuto="Model auto";
    int cnp,tip;
    Insurance*ins;
    
    
    if(file.is_open()){
        while(file>>tip>>nume>>prenume>>cnp>>perioada){
            if (tip==1) file>>destinatie;
            else file>>marcaAuto>>modelAuto;
            if(tip==1){
                travelInsurance *ti;
                ti=new travelInsurance(nume,prenume,cnp,perioada,tip,destinatie);
                ins=ti;
                l.addNode(ins);
            }
            else{
                carInsurance *ci;
                ci=new carInsurance(nume,prenume,cnp,perioada,tip,marcaAuto,modelAuto);
               ins=ci;
                l.addNode(ins);
            }
        }
        file.close();
    }else
        cout<<"\nFile cannot be opened!!";

}
void insert(List &l,int x){
    string carType,
            carModel,
            destination;
    Insurance *ins;
    Overload stream;
    cout<<stream;
    cin>>stream;
    if(x==0)//daca s-a ales travel insurance
    {
        travelInsurance*ti;
        
        cout<<"Destination: "<<endl;
        cin>>destination;
        ti=new travelInsurance(stream.returnfrsName(),stream.returnlst_name(),stream.returnCNP(),stream.returnPeriod(),stream.returnType(),destination);
        ins=ti;
        l.addNode(ti);
    }else if(x==1){
        carInsurance*ci;
        cout<<"The type of the car is: "<<endl;
        cin>>carType;
        cout<<"The model of the car is: "<<endl;
        cin>>carModel;
        ci=new carInsurance(stream.returnfrsName(),stream.returnlst_name(),stream.returnCNP(),stream.returnPeriod(),stream.returnType(),carType,carModel);
        ins=ci;
        l.addNode(ins);
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
void List::deleteName(string fName, string lName){
    Insurance *x, *y; // nu am inspiratie man, schimbam dupa
    x=y=head;
    if(x)
    {
        while(x && x->firstName !=fName && x->lastName !=lName){
            y = x;
            x = x->next;
        }
        if(x)
        {
            if(x != y)
            {
                y->next = x->next;
                delete x;
            }
            else
            {
                head = x->next;
                delete x;
            }
            
        }
        else
            cout<<" Numele nu exista! "<<endl;
    }
    else
        cout<<" Lista este vida! "<<endl;
}
void List::saveFile(){
    Insurance*ins;
    ins=head;
    if(!ins)cout<<"\nempty list!";
    else while(ins){
        ins->fileWrite();
        ins=ins->next;
    }
}
void List::saveFilePeriod(string period){//salvarea dupa perioada
    Insurance*ins;
    ins=head;
    if(!ins)
        cout <<"\nEmpty List!";
    else while(ins){
        if(ins->period==period)
            ins->fileWrite();
        ins=ins->next;

    }
}
void List::changeName(string name, string newName)
{
    Insurance *obj;
    obj = head;
    while(obj)
    {
        if(obj->firstName==name)
            obj->setName(newName);
        obj=obj->next;
    }
}
int main(){
    int opt;
    List l;
    l.head=NULL;
    while(1){
        cout << "\n\n[1]Incarcare informații dintr-un fisier.\n";
		cout << "[2]Adaugarea unei asigurari noi\n";
		cout << "[3]Afisare asigurarilor pe categorie si salvarea in fisier.\n";
		cout << "[4]Stergere dupa nume si prenume.\n";
		cout << "[5]Modificarea numelui.\n";
        cout << "xxxxx--[6]Sortarea listei dupa nume.\n";
		cout << "[7]Salvarea într-un fisier a asigurarilor dupa perioada citia de la tastatura\n";
		cout << "[0]Iesire.\n";
		cout << "Dati optiunea dvs: ";
		cin >> opt;
        switch(opt){
            case 0:return 0;
            case 1:citireFisier(l);
                 break;
            case 2:{ int aux;
                cout<<"Travel insurance(0)/car insurance (1): ";
                cin>>aux;
                try{
                    if(aux>1)
                        throw Exception("Wrong option",aux);
                    if (!aux) insert(l,0);
                    else insert(l,1);
                }
                catch(Exception ex){
                    cout<<ex.message;
                    cout<<ex.data<<endl;
                }
            }
                break;
            case 3: l.displayCategory();
                	l.saveFile();
            break;
            case 4: {string firstName,lastName;
                        cout<<"\nFirst name: ";
                        cin>>firstName;
                        cout<<"\nLast Name: ";
                        cin>>lastName;
                        l.deleteName(firstName,lastName);
            }break;
            case 5: { string name,newName;
                        cout<<"\nwanted name: ";
                        cin>>name;
                        cout<<"\nNew Name: ";
                        cin>>newName;
                        l.changeName(name,newName);
             } break;
            case 7:{
                    string period;
                    cout<<"\nPeriod: ";
                    cin>>period;
                    l.saveFilePeriod(period);
                } break;
            default:cout<<"\nWrong option!";
        }
    }
    return 0;
 }
 //parca merge bine
 //nu merge cum trebuie citirea din fisier
 //imi citeste doar tipul ,asta trebuie sa faca,doar ca rescrie fisierul fix asa "1 prenume nume 0 period"
 