/*****************************************
 *  FileName    [ user.cpp ]
 *  PackageName [ manager ]
 *  Synopsis    [ Define the user class ]
 *  Author      [ Harry Huang ]
*****************************************/

#include "user.h"
#include "object.h"
#include <string>
#include <vector>
#include <iostream>
#include <iomanip>


using namespace std;

bool
User::checkPassWord(string Password){
    if(Password == _passWord) return true;
    else                      return false;
}

object*
User::returnObjectByID(string id){
    vector<object*>::iterator iter = _borrowing.begin();
    for(iter ; iter!=_borrowing.end(); ++iter){
        object* tmpobj = *iter;
        if(tmpobj->getObjectID() == id){
            _borrowing.erase(iter);
            return tmpobj;
        }
    }
    return 0;
}

object*
User::returnObjectByName(string objName){
    vector<object*>::iterator iter = _borrowing.begin();
    for(iter ; iter!=_borrowing.end(); ++iter){
        object* tmpobj = *iter;
        if(tmpobj->getObjectName() == objName){
            _borrowing.erase(iter);
            return tmpobj;
        }
    }
    return 0;
}

void
User::printBorrowing(){
    cout << "Items you Borrowed:" << endl;
    for(int i = 0; i < _borrowing.size(); ++i){
        cout << "\t" << left << setw(10) << _borrowing[i]->getObjectName() 
                                << _borrowing[i]->getObjectID() << endl;
    }
}