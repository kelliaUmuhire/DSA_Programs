#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;
#define MAX_PL

struct Account{
    int accountNum;
    string fname;
    string lname;
    string address;
    string phoneNum;
    string username;
    // char password[MAX_PL];
    string password;
    int balance; //work on to float
};

void createAccount();

void signIn(int &menu, struct Account &account, string &a_line);

void transferMoney(struct Account &account, string &a_line);

void logout(int &menu, struct Account &account);

int main(){
    int opt, auth=0;
    struct Account account;
    string line;

    do{
        if(auth == 1){
        int opt2;
        cout << "\n----------------Welcome " << account.fname << "-------------------\n";
        while(auth==1){
        cout << "\n\t1. Check Balance\n\t2. Transfer Money\n\t3. Log out\n\t4. Exit\n\n";
        cin >> opt2;
        switch(opt2){
            case 1:
                cout << "\n.........Your Balance: "<< account.balance<<"..........\n";
                break;
            case 2:
                transferMoney(account, line);
                break;
            case 3:
                logout(auth, account);
                break;
            case 4:
                exit(0);
                break;
            default:
                cout <<"\nInvalid option\n";
                break;
        }
        }
    }
    if(auth==0){
        cout << "\n-----------------Welcome----------------------\n";
        cout << "\n\t1. Create Account\n\t2. Sign In\n\t3. Exit\n\n";
        cin >> opt;
        switch(opt){
            case 1:
                createAccount();
                signIn(auth, account,line);
                break;
            case 2:
                signIn(auth, account,line);
                break;
            case 3:
                exit(0);
            default:
                cout <<"\nInvalid option\n";
                break;
        }
    }
    } while(auth!=2);
    return 0;
}

int getAccountNumber(){
    ifstream in("bank.txt");
    string line;
    int count=0;
    while(getline(in, line)){
        ++count;
    }
    return count+1;
}

void createAccount(){
    struct Account account;
    cout << "\nFirst Name:\t";
    cin.ignore();
    getline(cin, account.fname);
    cout << "\nLast Name:\t";
    getline(cin, account.lname);
    cout << "\nUsername:\t";
    cin >> account.username;
    cin.ignore();
    cout << "\nAddress:\t";
    getline(cin, account.address);
    cout << "\nPhone Number:\t";
    cin >> account.phoneNum;
    cout << "\nPassword:\t";
    cin >> account.password;
    cout << "\nBalance:\t";
    cin >> account.balance;

    account.accountNum = getAccountNumber();

    ofstream bankf;
    bankf.open("bank.txt", ios::app);

    string a_line = to_string(account.accountNum)+";"+account.fname+";"+account.lname+";"+account.username+";"+account.address+";"+account.phoneNum+";"+account.password+";"+to_string(account.balance);

    bankf << a_line <<endl;

    cout << "\nAccount created\n";
    
    bankf.close();
}

void signIn(int &menu, struct Account &account, string &a_line){
    cout << "\n-------------------Sign in-------------\n";
    ifstream bankf("bank.txt");
    string line, username, password;
    // vector<string> segments;
    string segments[8];

    int fnd=0;

    cin.ignore();
    cout << "\nEnter username:\t";
    getline(cin, username);
    cout << "\nEnter password:\t";
    getline(cin, password);

    while(getline(bankf, line)){
        stringstream ss(line);
        string ln;
        int pos=0;
        while(getline(ss, ln, ';')){
            segments[pos] = ln;
            pos++;
        }
        // if(line.find(username) !=string::npos){
        if(segments[3]==username){
            fnd=1;
            break;
        }
    }

    if(fnd==0){
        cout << "\nUser not found\n";
        return;
    }

    while(password!=segments[6]){
        cout << "\nIncorrect Password. Try again:\t";
        getline(cin, password);
    }

    account.accountNum = stoi(segments[0]);
    account.fname = segments[1];
    account.lname = segments[2];
    account.username = segments[3];
    account.address = segments[4];
    account.phoneNum = segments[5];
    account.password = segments[6];
    account.balance = stoi(segments[7]);

    a_line=line;

    bankf.close();

    menu=1;
}

void transferMoney(struct Account &account, string &a_line){
    int a_num, fnd=0;
    int amount;
    vector<string> lines;

    string line;
    string segments[8];

    cout << "\nEnter account number:\t";
    cin>>a_num;
    cout << "\nEnter amount to transfer:\t";
    cin>>amount;

    //search account
    ifstream bankf("bank.txt");
    while(getline(bankf, line)){
        string ln;
        stringstream ss(line);
        int pos=0;
        while(getline(ss, ln, ';')){
            segments[pos]=ln;
            pos++;
        }
        if((stoi(segments[0]))==a_num){
            fnd=1;
        }
        //push line to lines
        lines.push_back(line);
    }
    bankf.close();

    if(fnd==0){
        cout << "\nAccount not found\n";
        return;
    }

    if(account.balance < amount){
        cout << "\nYou don't have enough balance to transfer the amount\n";
        return;
    }

    account.balance -= amount;
    a_line = to_string(account.accountNum)+";"+account.fname+";"+account.lname+";"+account.username+";"+account.address+";"+account.phoneNum+";"+account.password+";"+to_string(account.balance);
    line = segments[0]+";"+segments[1]+";"+segments[2]+";"+segments[3]+";"+segments[4]+";"+segments[5]+";"+segments[6]+";"+to_string(stoi(segments[7])+amount);

    ofstream bankof;
    bankof.open("bank.txt", ios::out | ios::trunc);
    for(int i=0;i<lines.size();i++){
        if(i==account.accountNum-1){
            bankof << a_line << endl;
        }
        else if(i==a_num-1){
            bankof << line << endl;
        }
        else{
            bankof << lines[i] << endl;
        }
        
    }
    bankof.close();
    cout << "\nMoney transferred!\n";
}

void logout(int &menu, struct Account &account){
    struct Account empty;
    account = empty;
    menu=0;
}