#ifndef SYSTEM_H
#define SYSTEM_H
#include <iostream>
#include <string>
#include <vector>

class infoMgr;

class System{
	public:
		System();
		~System();
		void Execute();
		bool Login();
		bool Register();
		void Borrow();
		void Return();
		
	private:
		infoMgr* manager;
		std::string username;
};
#endif