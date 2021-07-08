//****************************************
//          START OF THE PROJECT
//****************************************

//****************************************
//  HEADER FILES USED IN THE PROGRAM
//****************************************

#include<iostream>
#include<fstream>
#include<conio.h>
#include<iomanip>
#include<cctype>

using namespace std;

//****************************************
//      CLASS USED IN THE PROGRAM
//****************************************

class account                                       // beginning of the class
{
    int acno;                                       // variable for entering the account number of the user
    char name[50];                                  // variable for entering the name of the user
    int deposite;                                   // variable for entering the amount to be deposited
    char type;                                      // variable for entering the type of the account

public:
    void create_account();                          //function to get data from the user
    void show_account() const;                            //function to show the data on the screen
    void modify();                                  //function to add new data
    void deposit(int);                              //function to accept the amount by the user and add it to the main balance
    void withdraw(int);                             //function to accept the amount by the user and deduct it from the main balance
    void report() const;                            //function to show the information in the tabular form
    int return_account_number() const;              //function to return the account number of the user
    int return_balance() const;                     //function to return the balance amount
    char return_type_of_account() const;            //function to return the type of the account of the user
};                                                  // ending of the class

void account :: create_account()
{
    cout<<"\nEnter the Account Number : ";
    cin>>acno;
    cout<<"\nEnter the Name of the Account Holder : ";
    cin.ignore();
    cin.getline(name,50);
    cout<<"\nEnter the type of the Account : \n1)Savings Account - (s)\n2)Current Account - (c)\n";
    cin>>type;
    type=toupper(type);
    cout<<"\nEnter the Initial Amount (>=500 for Savings Account and >=1000 for Current Account) : ";
    cin>>deposite;
    cout<<"\n\n ACCOUNT CREATED";
}

void account :: show_account() const
{
    cout<<"\nAccount Number : "<<acno;
    cout<<"\nAccount Holder Name : "<<name;
    cout<<"\nType of the Account : "<<type;
    cout<<"\nBalance Amount : "<<deposite;
}

void account :: modify()
{
    cout<<"\nAccount Number : "<<acno;
    cout<<"\nModify Account Holder Name : "<<name;
    cin.ignore();
    cin.getline(name,50);
    cout<<"\nModify the Type of Account : \n1)Savings Account - (s)\n2)Current Account - (c)\n";
    cin>>type;
    type=toupper(type);
    cout<<"\nModify Balance Amount : ";
    cin>>deposite;
}

void account :: deposit(int x)
{
    deposite += x;
}

void account :: withdraw(int x)
{
    deposite -= x;
}

void account :: report() const
{
    cout<<acno<<setw(15)<<""<<name<<setw(13)<<" "<<type<<setw(15)<<" "<<deposite<<endl;
}

int account :: return_account_number() const
{
    return acno;
}

int account :: return_balance() const
{
    return deposite;
}

char account :: return_type_of_account() const
{
    return type;
}


//****************************************
//        FUNCTIONS DECLARATION
//****************************************

void write_account();                                   //function to write record in binary file
void display_details(int);                              //function to display the account details given by the user
void modify_account(int);                               //function to modify the record of the file
void delete_account(int);                               //function to delete record of the file
void display_all();                                     //function to display all the account details
void deposit_withdraw(int , int);                       //function to deposit/withdraw amount for given account
void intro_screen();                                    //function for the introduction screen


//*******************************************
//      FUNCTION TO WRITE IN FILE
//*******************************************
void write_account()
{
    account ac;
    ofstream outfile;
    outfile.open("account.dat",ios::binary | ios::app);
    ac.create_account();
    outfile.write(reinterpret_cast<char*>(&ac),sizeof(account));
    outfile.close();
}

//********************************************
// FUNCTION TO READ SPECIFIC RECORD FROM FILE  
//********************************************

void display_details(int n)
{
    account ac;
    bool flag = false;
    ifstream infile;
    infile.open("account.dat",ios::binary);
    if(!infile)
    {
        cout<<"FILE COULDNOT BE OPENED !! PRESS ANY KEY";
        return;
    }
    cout<<"\nBALANCE DETAILS\n";
    while(infile.read(reinterpret_cast<char*>(&ac),sizeof(account)))
    {
        if(ac.return_account_number() == n)
        {
            ac.show_account();
            flag = true;
        }
    }
    infile.close();
    if(flag == false)
    cout<<"\n\nACCOUNT NUMBER DOESN'T EXIST";
}


//****************************************
//   FUNCTION TO MODIFY RECORD OF FILE
//****************************************

void modify_account(int n)
{
    bool found = false;
    account ac;
    fstream file;
    file.open("account.dat",ios::binary|ios::in|ios::out);
    if(!file)
    {
        cout<<"File couldnot be opened !! Press any key...";
        return;
    }
    while(!file.eof() && found==false)
    {
        file.read(reinterpret_cast<char*>(&ac),sizeof(account));
        if(ac.return_account_number() == n)
        {
            ac.show_account();
            cout<<"\nEnter the new details of the account"<<endl;
            ac.modify();
            int pos = (-1)*static_cast<int>(sizeof(account));
            file.seekp(pos,ios::cur);
            file.write(reinterpret_cast<char*>(&ac),sizeof(account));
            cout<<"\n\nRECORD UPDATED";
            found = true;
        }
    }
    file.close();
    if(found == false)
    cout<<"\n\nRECORD NOT FOUND";
}

//****************************************
//  FUNCTION TO DELETE RECORD OF FILE
//****************************************

void delete_account(int n)
{
    account ac;
    ifstream infile;
    ofstream outfile;
    infile.open("account.dat",ios::binary);
    if(!infile)
    {
        cout<<"FILE COULDNOT BE OPENED !! PRESS ANY KEY...";
        return;
    }
    outfile.open("temp.dat",ios::binary);
    infile.seekg(0,ios::beg);
    while(infile.read(reinterpret_cast<char*>(&ac),sizeof(account)))
    {
        if(ac.return_account_number() != n)
        {
            outfile.write(reinterpret_cast<char*>(&ac),sizeof(account));
        }
    }
    infile.close();
    outfile.close();
    remove("account.dat");
    rename("temp.dat" , "account.dat");
    cout<<"\n\n\tRECORD DELETED";
}

//************************************************
//  FUNCTION TO DISPLAY ALL ACCOUNT DEPOSIT LIST
//************************************************

void display_all()
{
    account ac;
    ifstream infile;
    infile.open("account.dat",ios::binary);
    if(!infile)
    {
        cout<<"FILE COULDNOT BE OPENED !! PRESS ANY KEY...";
        return;
    }
    cout<<"\n\n\t\tACCOUNT HOLDER LIST\n\n";
    cout<<"================================================================\n";
    cout<<"A/c No.          Name            Type            Balance\n";
    cout<<"================================================================\n";
    while(infile.read(reinterpret_cast<char*>(&ac),sizeof(account)));
    {
        ac.report();
    }
    infile.close();
}

//********************************************
//  FUNCTION TO DEPOSIT AND WITHDRAW AMOUNT
//********************************************

void deposit_withdraw(int n,int option)
{
    int amt;
    bool found = false;
    account ac;
    fstream file;
    file.open("account.dat",ios::binary|ios::in|ios::out);
    if(!file)
    {
        cout<<"FILE COULDNOT BE OPENED !! PRESS ANY KEY...";
        return;
    }
    while(!file.eof() && found == false)
    {
        file.read(reinterpret_cast<char*>(&ac),sizeof(account));
        if(ac.return_account_number() == n)
        {
            ac.show_account();
            if(option==1)
            {
                cout<<"\n\nEnter the amount to be deposited : ";
                cin>>amt;
                ac.deposit(amt);
            }
            if(option==2)
            {
                cout<<"\n\nEnter the amount to be deposited : ";
                cin>>amt;
                int bal = ac.return_balance() - amt;
                if((bal<500 && ac.return_type_of_account()=='S') || (bal<1000 && ac.return_type_of_account()=='C'))
                cout<<"INSUFFICIENT BALANCE";
                else
                ac.withdraw(amt);
            }
            int pos = (-1)*static_cast<int>(sizeof(account));
            file.seekp(pos,ios::cur);
            file.write(reinterpret_cast<char*>(&ac),sizeof(account));
            cout<<"\n\n\tRECORD UPDATED";
            found = true;
        }
    }
    file.close();
    if(found == false)
    cout<<"\n\nRECORD NOT FOUND";
}

//****************************************
//       INTRODUCTION FUNCTION
//****************************************

void intro_screen()
{
    cout<<"\n\n\n\tBANK";
    cout<<"\n\n\tMANAGEMENT";
    cout<<"\n\n\tSYSTEM";
    cout<<"\n\n\n\nMADE BY :- SAM";
    cout<<"\n\nCOLLEGE : CET,BBSR";
    cin.get();
}


//****************************************
//   THE MAIN FUNCTION OF THE PROGRAM
//****************************************

int main()                                           
{
    char ch;
    int num;
    intro_screen();
    do
    {
        system("cls");
        cout<<"\n\n\n\tMAIN MENU";
        cout<<"\n\n\t01.NEW ACCOUNT";
        cout<<"\n\n\t02.DEPOSIT AMOUNT";
        cout<<"\n\n\t03.WITHDRAW AMOUNT";
        cout<<"\n\n\t04.BALANCE ENQUIRY";
        cout<<"\n\n\t05.ALL ACCOUNT HOLDER LIST";
        cout<<"\n\n\t06.CLOSE ACCOUNT";
        cout<<"\n\n\t07.MODIFY AN ACCOUNT";
        cout<<"\n\n\t08.EXIT";
        cout<<"\n\n\tSELECT YOUR OPTION (1-8) : ";
        cin>>ch;
        system("cls");
        switch(ch)
        {
            case '1':
            write_account();
            break;
            case '2':
            cout<<"\n\n\tEnter your Account Number : ";
            cin>>num;
            deposit_withdraw(num,1);
            break;
            case '3':
            cout<<"\n\n\tEnter your Account Number : ";
            cin>>num;
            deposit_withdraw(num,2);
            break;
            case '4':
            cout<<"\n\n\tEnter your Account Number : ";
            cin>>num;
            display_details(num);
            break;
            case '5':
            display_all();
            break;
            case '6':
            cout<<"\n\n\tEnter your Account Number : ";
            cin>>num;
            delete_account(num);
            break;
            case '7':
            cout<<"\n\n\tEnter your Account Number : ";
            cin>>num;
            modify_account(num);
            break;
            case '8':
            cout<<"Thank You for using Bank services";
            break;
            default:
            cout<<"\a";
        }
        cin.ignore();
        cin.get();
    } while(ch != '8');
    return 0;
}

//****************************************
//         END OF THE PROJECT
//****************************************
