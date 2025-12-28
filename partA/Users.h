#ifndef USERS_H
#define USERS_H

#include <string>
using namespace std;

enum Role {
    ADMIN = 1,
    OPERATOR = 2
};

struct User {
    Role role;
    int operatorId;       
    string display;  
};

User selectUser(); 

#endif

