/*****************************************
 *  FileName    [ object.cpp ]
 *  PackageName [ manager ]
 *  Synopsis    [ Define the object class ]
 *  Author      [ Harry Huang ]
*****************************************/

#include "object.h"
#include "user.h"
#include <string>
#include <vector>
#include <iostream>

using namespace std;

bool
object::isAvailable(){
	
    if(_borrower) return false;

    else          return true;
}

