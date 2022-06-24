#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

struct Record{
    int id;
    string time;
    string name;
    string place;
    string duration;
    string note;
};

void addRecord();

void viewRecord();

void editRecord();

void deleteRecord();

void editPassword();

string getCurrentPassword();

int main(){
    int opt;
    string password;
    string c_password = getCurrentPassword();

    std::cout << "\n\n**********PASSWORD PROTECTED DIARY**********\n\n\nEnter Password:\t";

    std::getline(cin, password);

    while(c_password.compare(password)){
        std::cout << "\nIncorrect Password. Try again:\t";
        std::getline(cin, password);
    }
    
    while(true){
        std::cout << "\t\tMENU:\n\t------------------------\n\n\t[1] ADD RECORD\n\t[2] VIEW RECORD\n\t[3] EDIT RECORD\n\t[4] DELETE RECORD\n\t[5] EDIT PASSWORD\n\t[6] EXIT\n";
        std::cout <<"\nEnter your choice:\t";
        cin>>opt;

        switch(opt){
            case 1:
                addRecord();
                break;
            case 2:
                viewRecord();
                break;
            case 3:
                editRecord();
                break;
            case 4:
                deleteRecord();
                break;
            case 5:
                editPassword();
                break;
            case 6:
                exit(0);
            default:
                std::cout << "\nInvalid option\n";
                break;
        }
    }
    
    return 0;
}

int getId(){
    ifstream diaryf("diary.txt");
    string line;
    int count=0;
    while(std::getline(diaryf, line)){
        count+=1;
    }
    //line one for diary password
    return count+1;
}

void addRecord(){
    ofstream diaryf;
    diaryf.open("diary.txt", ios::app);
    struct Record record;

    record.id = getId();

    if(record.id==1){
        diaryf << "gunsforhire" << endl; //add default password;
    }

    std::cout << "\nEnter Name:\t";
    cin.ignore();
    std::getline(cin, record.name);
    std::cout << "\nEnter Time:\t";
    std::getline(cin, record.time);
    std::cout << "\nEnter Place:\t";
    std::getline(cin, record.place);
    std::cout << "\nEnter Duration:\t";
    std::getline(cin, record.duration);
    std::cout << "\nEnter note:\t";
    std::getline(cin, record.note);

    string line = to_string(record.id)+";"+record.name+";"+record.time+";"+record.place+";"+record.duration+";"+record.note;

    diaryf << line << endl;
    diaryf.close();

    std::cout << "\nRecord Added. ID: "<<record.id<<endl; 
}

bool findRecord(int id, struct Record &record, int &a_line){
    ifstream diaryf("diary.txt");
    string line;
    bool found=false;

    std::getline(diaryf, line);
    int pos=1;
    while(std::getline(diaryf, line)){
        pos++;
        stringstream ss(line);
        string wrd;
        std::getline(ss, wrd, ';');
        if(stoi(wrd)==id){
            record.id = stoi(wrd);
            std::getline(ss, wrd, ';');
            record.name = wrd;
            std::getline(ss, wrd, ';');
            record.time = wrd;
            std::getline(ss, wrd, ';');
            record.place = wrd;
            std::getline(ss, wrd, ';');
            record.duration = wrd;
            std::getline(ss, wrd, ';');
            record.note = wrd;
            found = true;
            a_line=pos;
            break;
        }
    }

    diaryf.close();
    return found;
}

vector<string> getRecordsLines(){
    ifstream diaryf("diary.txt");
    string line;
    vector<string> lines;

    while(std::getline(diaryf, line)){
        lines.push_back(line);
    }

    diaryf.close();

    return lines;
}

string getCurrentPassword(){
    ifstream diaryf("diary.txt");
    string line;

    std::getline(diaryf, line);

    diaryf.close();
    return line;    
}


void viewRecord(){
    int id;
    struct Record record;
    int line;

    std::cout << "\nEnter Record ID: \t";
    cin>>id;

    if(!findRecord(id, record, line)){
        std::cout << "\nRecord not found\n\n";
    }
    else{
        std::cout << "\n########Record "<< record.id<<" #########";
        std::cout << "\nName:\t "<<record.name;
        std::cout << "\nTime:\t "<<record.time;
        std::cout << "\nPlace:\t "<<record.place;
        std::cout << "\nDuration:\t "<<record.duration;
        std::cout << "\nNote:\t "<<record.note<<"\n\n";
    }
}


void editRecord(){
    int id;
    struct Record record;
    string field;
    int line;

    std::cout << "\nEnter Record ID: \t";
    cin>>id;

    if(!findRecord(id, record, line)){
        std::cout << "\nRecord not found\n\n";
    }
    std::cout << "\nLeave the field empty if you want to leave them as they're in the diary. \n";
    std::cout << "\nEnter name:\t";
    cin.ignore();
    std::getline(cin, field);
    if(field!=""){
        record.name = field;
    }
    std::cout << "\nEnter time:\t";
    std::getline(cin, field);
    if(field!=""){
        record.time = field;
    }
    std::cout << "\nEnter place:\t";
    std::getline(cin, field);
    if(field!=""){
        record.place = field;
    }
    std::cout << "\nEnter duration:\t";
    std::getline(cin, field);
    if(field!=""){
        record.duration = field;
    }
    std::cout << "\nEnter note:\t";
    std::getline(cin, field);
    if(field!=""){
        record.note = field;
    }

    string n_line = to_string(record.id)+";"+record.name+";"+record.time+";"+record.place+";"+record.duration+";"+record.note;
    //edit file
    vector<string> lines = getRecordsLines();

    ofstream diaryf;
    diaryf.open("diary.txt", ios::out | ios::trunc);

    int pos=1;
    for(string ln:lines){
        if(line==pos){
            diaryf << n_line << endl;
        }else{
            diaryf << ln <<endl;
        }
        pos++;
    }

    diaryf.close();

    std::cout << "\nRecord Updated!\n";
}

void deleteRecord(){
    int id;
    struct Record record;
    string field;
    int line;

    std::cout << "\nEnter Record ID: \t";
    cin>>id;

    if(!findRecord(id, record, line)){
        std::cout << "\nRecord not found\n\n";
    } else{
        vector<string> lines = getRecordsLines();

        ofstream diaryf;
        diaryf.open("diary.txt", ios::out | ios::trunc);

        int pos=1;
        for(string ln:lines){
            if(line==pos){
                continue;
            }else{
                diaryf << ln <<endl;
            }
            pos++;
        }

        diaryf.close();

        std::cout << "\nRecord Deleted!\n";
    }
}

void editPassword(){
    string c_pass;
    string n_pass;
    std::cout << "\nEnter current password:\t";
    cin.ignore();
    std::getline(cin, c_pass);
    std::cout << "\nEnter new password:\t";
    std::getline(cin, n_pass);

    string password = getCurrentPassword();

    while(password.compare(c_pass)){
        std::cout << "\nIncorrect Password. Try again:\t";
        std::getline(cin, c_pass);
    }
    
        vector<string> lines = getRecordsLines();

    ofstream diaryf;
    diaryf.open("diary.txt", ios::out | ios::trunc);

    int pos=1;
    for(string ln:lines){
        if(pos==1){
            diaryf << n_pass << endl;
        }else{
            diaryf << ln <<endl;
        }
        pos++;
    }

    diaryf.close();

    std::cout << "\nPassword Updated!\n";
    
}