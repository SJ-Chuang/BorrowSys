#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cstdlib>
#include "system.h"
#include "infoMgr.h"

using namespace std;

System::System(){
	manager = new infoMgr();
	this->manager->readObjectTxt();
	this->manager->readUserTxt();
}

System::~System(){delete manager;}

bool System::Login(){
	string userID, Password;
	char ch;
	const char ENTER = 13;
    const char BackSpace = 8;
	cout << "login as: ";
	cin >> userID;
    cout << endl;
	cout << userID << "\'s password: ";    
    cin >> Password;
	cout << endl << endl;
	if(this->manager->login(userID, Password)){
		this->username = userID;
		return true;
	}
	return false;
}

bool System::Register(){
	string userID, Password, confirm;
	char ch;
	const char ENTER = 13;
    const char BackSpace = 8;
	cout << "User's ID>>>";
	cin >> userID;
    cout << endl;
	cout << userID << "\'s password>>>";
    cin >> Password;
	cout << endl << endl;
	cout << "Confirm password>>>";
    cin >> confirm;
	cout << endl << endl;
	if (confirm.compare(Password) == 0){
		return this->manager->setIDandPassword(userID, Password);
	}else{
		cout << "[Error] Password and confirm password does not match." << endl << endl;
		return false;
	}
}

void System::Borrow(){	
	string response;	
	while(true){
        manager->itemList();
		cout << "Borrow object by entering it's Name or ID.\n\n>>>";
		cin >> response;
        cout << endl;
        if(response.compare("exit") == 0) break;
		if (this->manager->borrowByName(response) || this->manager->borrowByID(response)){
			cout << "Successful borrowing: taking good care of the borrowed item." << endl << endl;
		}else{
			cout << "Object has been borrowed or not exist." << endl << endl;
		}
		cout << "continue borrowing[y/n]";
		cin >> response;
        cout << endl;
        if(response.compare("exit") == 0) break;
		if(response.compare("y") == 0) continue;		
		else break;
	}
}
void System::Return(){
	string response;    
	while(true){
        manager->borrowingList();
		cout << "Return object by entering it's Name or ID.\n\n>>>";
		cin >> response;
        cout << endl;
        if(response.compare("exit") == 0) break;
		if (this->manager->returnByName(response) || this->manager->returnByID(response)){
			cout << "Successful Returning." << endl << endl;
		}else{
			cout << "Object is not exist or haven't been borrowed." << endl << endl;	
		}
		cout << "continue returning[y/n]";
		cin >> response;
        cout << endl;
        if(response.compare("exit") == 0) break;
		if(response.compare("y") == 0) continue;
		else break;
	}
}

void printfile(string filename){
	ifstream file(filename);
	string line;
	while(getline(file, line)){
		cout << line << endl;
	}
	file.close();
}

void System::Execute(){
	string command;
	string state("[Home]");
    cout << endl;
	cout << " BorrowSys 1.0 (2020 OOP-FINAL)" << endl << endl;
	cout << " Type \"help\" for more information." << endl << endl;    
	while(true){
		cout << state << ">>>";
		cin >> command;
        cout << endl;
		if(command.compare("exit") == 0) break;
		if(command.compare("help") == 0){
			printfile("help.txt");
			continue;
		}		
		if(command.compare("login") == 0){
			if(this->Login()){
				printfile("welcome.txt");
                cout << endl;
				state = this->username + "@BorrowSys";
			}
			else cout << "Login Failed: no such user or wrong password." << endl << endl;
			continue;
		}
		if(command.compare("logout") == 0){
			if(state.compare("[Home]")) state = "[Home]";
			else cout << "Please login to your account first." << endl << endl;
			continue;		
		}
		if(command.compare("register") == 0){
			if(this->Register()){
				cout << "successful registration!" << endl << endl;
				cout << "Please login to your account." << endl << endl;
			}
			continue;
		}
		if(command.compare("borrow") == 0){
			if(state.compare("[Home]"))this->Borrow();
			else cout << "Please login to your account first." << endl << endl;		
			continue;
		}		
		if(command.compare("return") == 0){
			if(state.compare("[Home]")) this->Return();
			else cout << "Please login to your account first." << endl << endl;
			continue;
		}
        std::string str = "string";
        const char* cstr = command.c_str();
        std::system(cstr);
	}
}