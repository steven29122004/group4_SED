#include "Users.h"
#include <iostream>

using namespace std;

static int readChoice(int minV, int maxV) {
    int x;
    cin >> x;
    while (x < minV || x > maxV) {
        cout << "Invalid. Choose again: ";
        cin >> x;
    }
    return x;
}

User selectUser() {
    User u{};
    cout << "Select role:\n";
    cout << "1) Admin\n";
    cout << "2) Operator\n";
    cout << "Choose: ";
    int r = readChoice(1, 2);

    if (r == 1) {
        u.role = ADMIN;
        u.operatorId = 0;
        u.display = "Admin";
        return u;
    }

    u.role = OPERATOR;
    cout << "\nSelect operator:\n";
    cout << "1) Operator1\n";
    cout << "2) Operator2\n";
    cout << "Choose: ";
    u.operatorId = readChoice(1, 2);
    u.display = (u.operatorId == 1) ? "Operator1" : "Operator2";
    return u;
}




