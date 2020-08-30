#include<iostream>
#include<windows.h>
#include<conio.h>
#include<string>
#include<cstdlib>
#include<cstring>
#include<fstream>
using namespace std;

int isbn2,index;
int search(int isbn);
int nstaff=0,nstud=0,bkid=0;


COORD coord = {0, 0};

void gotoxy(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

class library
{
public:
    virtual int returnbook(){return 0;}
    virtual int takebook(){return 0;}
    virtual void addbook(){}
    virtual void addstaff(){}
    virtual void adds(){}
    virtual int isb(){return 0;}
    virtual string str(){return"";}
    virtual int sto(){return 0;}
};

library *stud[100],*sta[100],*bks[100];

class library_store:public library
{
public:
    string bookname;
    int isbn;
    int stock;
    library_store():stock(0)
    { }

    int isb(){return isbn;}
    string str(){return bookname;}
    int sto(){ return stock;}

    int returnbook()
    {
        stock++;
        return 1;
    }
    int takebook()
    {
        if(stock>0)
        {
            stock--;
            return 1;
        }
        else
        {
            cout<<"\nThe books are not available!!!";
            return -1;
        }
    }
    void addbook()
    {
        cout<<"Enter name of the book: ";
        cin>>bookname;
        cout<<"Enter book number: ";
        cin>>isbn;
        cout<<"Enter number of books available: ";
        cin>>stock;
    }

};

class staff:public library
{
public:
    string name;
    int bookstaken,id;


    int returnbook()
    {
        int days;
        cout<<"\nEnter book number: ";
        cin>>isbn2;
        index=search(isbn2);
        if(index!=-1)
        {
            cout<<"\nEnter the number of days since the book was borrowed: ";
            cin>>days;
            cout<<"\nExtra fees to be paid: Tk."<<(days-10)*1;
            return bks[index]->returnbook();
        }
        else
        return -1;
    }
        int takebook()
    {
        cout<<"\nEnter Book number: ";
        cin>>isbn2;
        index=search(isbn2);
        if(index!=-1)
        {
        cout<<"\nPlease return the book within 10 days!!!";
        return bks[index]->takebook();
        }
        else
        return -1;
    }
        void addstaff()
    {
        cout<<"\nEnter the name of the staff:";
        cin>>name;
        cout<<"\nEnter the ID of the staff:";
        cin>>id;
    }
};

class students:public library
{
public:
    string name;
    int id;

    int returnbook()
    {
        int days;
        cout<<"\nEnter book number: ";
        cin>>isbn2;
        index=search(isbn2);
        if(index!=-1)
        {
            cout<<"\nEnter the number of days since the book was borrowed: ";
            cin>>days;
            cout<<"\nExtra fees to be paid: Tk."<<(days-5)*1;
            return bks[index]->returnbook();
        }
        else
        return -1;
    }
    int takebook()
    {
        cout<<"\nEnter the book number: ";
        cin>>isbn2;
        index=search(isbn2);
        if(index!=-1)
        {
            cout<<"\nPlease return the book within 10 days!!!";
            return bks[index]->takebook();
        }
            else
            return -1;
    }
        void adds()
    {
        cout<<"\nEnter the name of the student:";
        cin>>name;
        cout<<"\nEnter the ID of the student:";
        cin>>id;
    }
};
///********
///iubat logo
///********
void logo()
{
    //system("color 09");
    cout<<"      ____\n";
    cout<<"     |____|   \t\t___________________________________"<<endl;
    cout<<"^||^ ^^||^^ ^||^\t      WELCOME TO THE LOGIN MENU "<<endl;
    cout<<" ||    ||    ||\t\t___________________________________"<<endl;
    cout<<" || B  ||  A ||"<<endl;
    cout<<" |[____^^____]|"<<endl;
    cout<<"     |____|"<<endl;
}

///***************
///login option
///***************

int login()
{
    int i=0,j=0,c,ck;
    char uname[10];
    char pword[10];
    do
    {
        cout<<"\n\n\n\n\n___________________________________________________"<<endl;
        cout<<"\n\n                      PLEASE LOGIN FIRST                  "<<endl;
        cout<<"\n___________________________________________________"<<endl;
        cout<<"\n\t\tENTER USERNAME     : "<<"\t";
        cin>>uname;
        cout<<"\n\t\tENTER PASSWORD     :  "<<"\t";
        while(i<5)
        {
            pword[i]=getch();
            c=pword[i];
            if(c==13) break;
            else cout<<"*";
            i++;
        }
        pword[i]='\0';
        i=0;
        system("cls");
        if(strcmp(uname,"bappy")==0 && strcmp(pword,"1234")==0)
        {
            ck=1;
            break;
        }
        else
        {
            cout<<".OOPS...Login Unsuccessful"<<endl;
            j++;
            getch();
            system("cls");
        }
    }
    while(j<=2);
    if(j>2)
    {
        cout<<"\n\n\t_________________________________________"<<endl;
        cout<<"\n\n\t ! SORRY YOU HAVE ENTERED THE WRONG\n\t   USER NAME OR PASSWORD FOR MANY TIMES "<<endl;
        cout<<"\n\n\t_________________________________________"<<endl;
        ck=0;
        getch();
        exit(0);
    }
    system("cls");
    return ck;
}


void display()
{
    ofstream out("test.txt");
    out<<"************ The available books are ************\n";
    out<<"\nThe available books are:\n\nNumber\t-\tName\t-\tStock\n";
    cout<<"\nThe available books are:\n\nNumber\t-\tName\t-\tStock\n";
    for(int i=0;i<bkid;i++)
    {
        cout<<"\n"<<bks[i]->isb()<<"\t-\t"<<bks[i]->str()<<"\t-\t"<<bks[i]->sto();
        out<<"\n"<<bks[i]->isb()<<"\t-\t"<<bks[i]->str()<<"\t-\t"<<bks[i]->sto();
    }
    out.close();
}

void staf()
{
    char ch;
    int id,rep=1;
    system("cls");
    logo();

    cout<<"\nEnter staff library number: ";
    cin>>id;
    id--;
    while(rep==1)
    {
        system("cls");
        logo();
        cout<<"\nSTAFF\n-----\n";
        cout<<"\n1.Display books\n2.Take book\n3.Return book\n4.Go to main menu\n";
        cin>>ch;
        switch(ch)
        {
            case '1':
            display();
            break;
            case '2':
            if(sta[id]->takebook()==-1)
            cout<<"\nInvalid Number!!!";
            else
            cout<<"\nPlease wait...";
            break;
            case '3':
            if(sta[id]->returnbook()==-1)
            cout<<"\nInvalid Number!!!";
            else
            cout<<"\nPlease wait...\n";
            break;
            case '4':
            rep=0;
            break;
        }
        getch();
    }
}

void student()
{
    char ch;
    int id,cont=1;
    system("cls");
    logo();
    cout<<"\nSTUDENT\n--------\n";
    cout<<"Enter library number: ";
    cin>>id;
    id--;
    while(cont==1)
    {
        system("cls");
        logo();
        cout<<"\n1.Display books\n2.Take books\n3.Return book\n4.Go to main menu\n";
        cin>>ch;
        switch(ch)
        {
            case '1': display();
            break;

            case '2': if(stud[id]->takebook()==-1)
            cout<<"\nInvalid Number!!!";
            else
            cout<<"\nPlease wait...\n";
            break;

            case '3': if(stud[id]->returnbook()==-1)
            cout<<"\nInvalid Number!!!";
            else
            cout<<"\nPlease wait...\n";
            break;

            case '4': cont=0;
            break;
        }
        getch();
    }
}

void admin()
{
    char ch;
    int rep=1;
    system("cls");
    logo();
    while(rep==1)
    {
        system("cls");
        logo();
        cout<<"\nDATABASE\n---------\n\n1.Add staff\n2.Add student\n3.Add books\n4.Display\n5.Exit\n";
        cin>>ch;
        switch(ch)
        {
            case '1': sta[nstaff]=new staff;
            sta[nstaff]->addstaff();
            nstaff++;
            cout<<"\nYour serial number is: "<<nstaff<<endl;
            break;

            case '2': stud[nstud]=new students;
            stud[nstud]->adds();
            nstud++;
            cout<<"\nYour serial number is: "<<nstud<<endl;
            break;

            case '3': bks[bkid]=new library_store;
            bks[bkid]->addbook();
            bkid++;
            break;

            case '4': display();
            break;

            case '5': rep=0;
            break;

            default :{
                cout<<"********Invalid input********\n";
            }
        }
        cout<<"\nPress Enter to continue:";
        getch();
    }
}

int search(int isbn)
{
    for(int i=0;i<bkid;i++)
    {
        if(bks[i]->isb()==isbn)
        return i;
    }
    cout<<"Book is not found!!!";
    return -1;
}

int main()
{

    logo();
    char choice;
    int cont=1;
    while(cont==1)
    {
        system("cls");
        logo();
        cout<<"\n1.Administrator\n2.Staff\n3.Student\n4.Exit\nEnter your choice: ";
        cin>>choice;
        switch(choice)
        {
            case '1':
                {
                    system("cls");
                    int ck=login();
                    if(ck==1){
                        system("cls");
                        logo();
                         admin();
                    }
                    else{
                        system("cls");
                        logo();
                        cout<<"\n\nInvalid Entry!!";
                        break;
                    }
                }

            break;

            case '2':{
                system("cls");
                logo();
                staf();
                break;
            }

            case '3': {
                system("cls");
                logo();
                student();
            break;
            }

            case '4': cont=0;
            break;

            default: {
                system("cls");
                logo();
                cout<<"\n\nInvalid Entry!!!!!!!!\n\n";
            }
        }
    }
    return 0;
}
