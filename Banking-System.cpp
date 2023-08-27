/*Features it should have-
open an account
balancy enquiry
deposit
withdrawal
close an account
show all accoubts
quit
when open an account-get first name,last name,initial amount---then show first name,last name,account number,balance
when show all acounts-show al details after account number
*data should be stored in a file*
when balance enquiry-ask for account number then show details of acount
when deposit-ask for acct no. and amount, then show details of acnt
when withdrawal-ask for acct no. then amount then show all details

*/
#include<iostream>
#include<fstream>
#include<map>
#include<cstdlib>
#include<vector>
using namespace std;

#define MIN_BALANCE 500
class Insufficientfunds{};

class Account{
    string fname;
    string lname;
    float balance;
    long accountNumber;
    static long nextaccountnumber; 
    public:
    Account (){}   
    Account (string firstn,string lastn,float bal);
    long getaccountnumber();
    static void setlastaccountnumber(long accno);
    void deposit(float amount);
    void withdraw(float amount);
    friend ofstream &operator<<(ofstream &ofs,Account &oa);
    friend ifstream &operator>>(ifstream &ifs,Account &oa);
    friend ostream &operator<<(ostream &os,Account &oa);
};
long Account::nextaccountnumber=0;
class Bank{
    map<long,Account>mapping;
    public:
    Bank();
    Account openaccount(string fname,string lname,float bal);
    Account balenquiry(long accno);
    Account deposit(long accno,float amount);
    Account withdraw(long accno,float amount);
    void closeaccount(long accno);
    void showAllaccounts();
    ~Bank();
};

int main(){
    int choice;
    string fname,lname;
    float balance;
    float amount;
    long accno;
    Bank b;
    Account acc;
    cout<<"Banking System: "<<endl;
    do{
        cout<<"What do you wish to do?"<<endl;
        cout<<"1. Open an Account"<<endl;
        cout<<"2. Balance Enquiry"<<endl;
        cout<<"3. Deposit"<<endl;
        cout<<"4. Withdrawal"<<endl;
        cout<<"5. Close an Account"<<endl;
        cout<<"6. Show all Accounts"<<endl;
        cout<<"7. Quit"<<endl;
        cout<<"Enter you choice:";
        cin>>choice;
        switch (choice)
        {
        case 1: cout<<"Enter your first name: ";
                cin>>fname;
                cout<<"Enter your last name: ";
                cin>>lname;  
                cout<<"Enter initial balance: ";
                cin>>balance;
                acc=b.openaccount(fname,lname,balance);
                cout<<"Account is created"<<endl;                
                cout<<acc;
                break;
        
        case 2: cout<<"Enter your account number: ";
                cin>>accno;
                acc=b.balenquiry(accno);
                cout<<"Your Account Details:"<<endl;
                cout<<acc;
                break;
        
        case 3: cout<<"Enter account numer: ";
                cin>>accno;
                cout<<"Enter amount: ";
                cin>>amount;
                acc=b.deposit(accno,amount);
                cout<<"Amount is Deposited"<<endl;
                cout<<acc;
                break;

        case 4: cout<<"Enter account number: ";
                cin>>accno;
                cout<<"Enter amount: ";
                cin>>amount;
                acc=b.withdraw(accno,amount);
                cout<<"Amount is withdrawn"<<endl;
                cout<<acc;
                break;

        case 5: cout<<"Enter account number: ";
                cin>>accno;
                b.closeaccount(accno);
                cout<<"Account is closed"<<endl;  

        case 6: b.showAllaccounts();  
                break;    

        case 7: break;

        default: cout<<"Enter correct choice: ";
                 exit(0);               
        }

    }while(choice!=7);

return 0;
}    

Account::Account(string firstn,string lastn,float bal ){
    nextaccountnumber++;
    accountNumber=nextaccountnumber;
    fname=firstn;
    lname=lastn;
    balance=bal;
    
}

long Account::getaccountnumber(){
        return accountNumber;
}
void Account::setlastaccountnumber(long accno){
    nextaccountnumber=accno;
}
void Account::deposit(float amount){
    balance+=amount;
}
void Account::withdraw(float amount){
    if(balance-amount<MIN_BALANCE){
        throw Insufficientfunds();
    }
    balance-=amount;            
}
ofstream &operator<<(ofstream &ofs,Account &oa){
    ofs<<oa.accountNumber<<endl;
    ofs<<oa.fname<<endl;
    ofs<<oa.lname<<endl;
    ofs<<oa.balance<<endl;
    return ofs;
}

ifstream &operator>>(ifstream &ifs,Account &oa){
    ifs>>oa.accountNumber;
    ifs>>oa.fname;
    ifs>>oa.lname;
    ifs>>oa.balance;
    return ifs;
}

ostream &operator<<(ostream &os,Account &oa){
    os<<"First Name: "<<oa.fname<<endl;
    os<<"Last Name: "<<oa.lname<<endl;
    os<<"Account Number: "<<oa.accountNumber<<endl;
    os<<"Balance: "<<oa.balance<<endl;
    return os;
}
Bank::Bank(){
    Account acc;
    ifstream ifs;
    ifs.open("Bank.data");
    if(!ifs){
        return;
    }
    while(!ifs.eof()){
        ifs>>acc;
        mapping.insert(pair<long,Account>(acc.getaccountnumber(),acc));
    }
    Account::setlastaccountnumber(acc.getaccountnumber());
    ifs.close();

}

Account Bank:: openaccount(string fname,string lname,float bal){
    Account a(fname,lname,bal);
    ofstream ofs;
    mapping.insert(pair<long,Account>(a.getaccountnumber(),a));
    ofs.open("Bank.data");
    map<long,Account>::iterator itr;
    for(itr=mapping.begin();itr!=mapping.end();itr++){
        ofs<<itr->second;
    }
    ofs.close();
    return a;

}
Account Bank:: balenquiry(long accno){
    map<long,Account>::iterator itr=mapping.find(accno);
    return itr->second;
}
Account Bank:: deposit(long accno,float amount){
    map<long,Account>::iterator itr=mapping.find(accno);
    itr->second.deposit(amount);
    return itr->second;
}
Account Bank:: withdraw(long accno,float amount){
    map<long,Account>::iterator itr=mapping.find(accno);
    itr->second.withdraw(amount);
    return itr->second;
}
void Bank::closeaccount(long accno){
    map<long,Account>::iterator itr=mapping.find(accno);
    cout<<"Account Deleted!"<<endl;
    mapping.erase(accno);
}
void Bank::showAllaccounts(){
    map<long,Account>::iterator itr;
    for(itr=mapping.begin();itr!=mapping.end();itr++){
        cout<<"Account "<<itr->first<<endl<<itr->second<<endl;
    }
}
Bank::~Bank(){
    ofstream ofs;
    ofs.open("Bank.data");
    map<long,Account>::iterator itr;
    for(itr=mapping.begin();itr!=mapping.end();itr++){
        ofs<<itr->second;
    }
    ofs.close();
}