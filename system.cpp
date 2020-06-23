#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <conio.h>
#include "system.h"
#include "infomgr.h"

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
	cout << "login as: ";
	cin >> userID;
	cout << userID << "\'s password: ";
	while((ch = getch()) != ENTER)
    {
        Password += ch;
        cout << '*';
    }
	cout << endl;
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
	cout << "User's ID>>>";
	cin >> userID;
	cout << userID << "\'s password>>>";	
	while((ch = getch()) != ENTER)
    {
        Password += ch;
        cout << '*';
    }
	cout << endl;
	cout << "Confirm password>>>";
	while((ch = getch()) != ENTER)
    {
        confirm += ch;
        cout << '*';
    }
	cout << endl;
	if (confirm.compare(Password) == 0){
		return this->manager->setIDandPassword(userID, Password);
	}else{
		cout << "[Error] Password and confirm password does not match." << endl;
		return false;
	}
}

void System::Borrow(){	
	string response;
	manager->itemList();
	while(true){
		cout << "Borrow object by enter it's Name or ID.\n>>>";
		cin >> response;
		if (this->manager->borrowByName(response) || this->manager->borrowByID(response)){
			cout << "Successful borrowing: taking good care of the borrowed item." << endl;		
		}else{
			cout << "Object has been borrowed or not exist." << endl;		
		}
		cout << "continue borrowing[y/n]";
		cin >> response;
		if(response.compare("y") == 0) continue;		
		else break;
	}
}
void System::Return(){
	string response;
	while(true){
		cout << "Return object by enter it's Name or ID.\n>>>";
		cin >> response;
		if (this->manager->returnByName(response) || this->manager->returnByID(response)){
			cout << "Successful Returning." << endl;	
		}else{
			cout << "Object is not exist or haven't been borrowed." << endl;		
		}
		cout << "continue returning[y/n]";
		cin >> response;
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
	cout << "BorrowSys 1.0 (2020 OOP-FINAL)" << endl;
	cout << "Type \"help\" for more information." << endl;
	while(true){
		cout << state << ">>>";
		cin >> command;
		if(command.compare("exit()") == 0) break;
		if(command.compare("help") == 0){
			printfile("help.txt");
			continue;
		}		
		if(command.compare("login()") == 0){
			if(this->Login()){
				printfile("welcome.txt");
				state = this->username + "@BorrowSys";
			}
			else cout << "Login Failed: no such user or wrong password." << endl;
			continue;
		}
		if(command.compare("logout()") == 0){
			if(state.compare("[Home]")) state = "[Home]";
			else cout << "Please login to your account first." << endl;
			continue;		
		}
		if(command.compare("reg()") == 0){
			if(this->Register()){
				cout << "successful registration!" << endl;
				cout << "Please login to your account." << endl;
			}
			continue;
		}
		if(command.compare("borrow()") == 0){
			if(state.compare("[Home]"))this->Borrow();
			else cout << "Please login to your account first." << endl;			
			continue;
		}		
		if(command.compare("return()") == 0){
			if(state.compare("[Home]")) this->Return();
			else cout << "Please login to your account first." << endl;
			continue;
		}
		cout << "CommandError: command \'" << command << "\' is not defined." << endl;		
	}	
}















