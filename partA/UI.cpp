#include "UI.h"
#include <iostream>
#include <fstream>

using namespace std;

// ---------- BASIC INPUT ----------
static int readChoice(int minV, int maxV) {
    int x;
    cin >> x;
    while (x < minV || x > maxV) {
        cout << "Invalid. Choose again: ";
        cin >> x;
    }
    return x;
}

static string opName(int op) {
    if (op == 1) return "Operator1";
    if (op == 2) return "Operator2";
    return "None";
}

// ---------- LOG VIEW ----------
static void viewLogs() {
    ifstream in("traffic_log.txt");
    if (!in) {
        cout << "No log file yet.\n";
        return;
    }
    cout << "\n=== LOGS (traffic_log.txt) ===\n";
    string line;
  
    cin.ignore();
    while (getline(in, line)) cout << line << "\n";
    cout << "=== END LOGS ===\n";
}

// ---------- PRINT DASHBOARD  ----------
static void printDashboard(const string& who, const Intersection& it) {
    cout << "\nWelcome, " << who << "\n\n";
    cout << "Assigned Intersection: " << it.name << "\n\n";
    cout << "Current State:\n\n";

    string N = lightStateToString(it.lights[0].state);
    string E = lightStateToString(it.lights[1].state);
    string S = lightStateToString(it.lights[2].state);
    string W = lightStateToString(it.lights[3].state);

    // gắn (xxs) chỉ cho hướng đang GREEN
    if (it.lights[0].state == LightState::GREEN) N += " (" + to_string(it.timeRemaining) + "s)";
    if (it.lights[1].state == LightState::GREEN) E += " (" + to_string(it.timeRemaining) + "s)";
    if (it.lights[2].state == LightState::GREEN) S += " (" + to_string(it.timeRemaining) + "s)";
    if (it.lights[3].state == LightState::GREEN) W += " (" + to_string(it.timeRemaining) + "s)";

    cout << "N: " << N << " | S: " << S << " | E: " << E << " | W: " << W << "\n\n";

    cout << "Mode: " << ((it.mode == ControlMode::AUTO) ? "AUTO" : "MANUAL") << "\n\n";


    if (it.mode == ControlMode::AUTO) {
        cout << "Next change in " << it.timeRemaining << " seconds...\n\n";
    } else {
        cout << "Waiting for operator command...\n\n";
    }

    cout << "Log saved: traffic_log.txt\n";
}

static vector<int> assignedList(const SystemData& data, int operatorId) {
    vector<int> list;
    for (int i = 0; i < (int)data.intersections.size(); i++) {
        if (data.assignedOp[i] == operatorId) list.push_back(i);
    }
    return list;
}

static int pickAssignedIntersection(const SystemData& data, int operatorId) {
    vector<int> list = assignedList(data, operatorId);
    if (list.empty()) return -1;
    if ((int)list.size() == 1) return list[0];

    cout << "\nAssigned Intersections:\n";
    for (int k = 0; k < (int)list.size(); k++) {
        cout << k << ") " << data.intersections[list[k]].name << "\n";
    }
    cout << "Choose: ";
    int pick = readChoice(0, (int)list.size() - 1);
    return list[pick];
}

// ---------- TICK ----------
static void tickOne(SystemData& data, int idx) {

    updateAuto(data.intersections[idx]);
}

// ---------- ADMIN MENU ----------
static void adminListAll(const SystemData& data) {
    if (data.intersections.empty()) {
        cout << "No intersections.\n";
        return;
    }
    cout << "\n=== INTERSECTIONS ===\n";
    for (int i = 0; i < (int)data.intersections.size(); i++) {
        cout << "[" << i << "] " << data.intersections[i].name
             << " | Assigned: " << opName(data.assignedOp[i])
             << " | Mode: " << ((data.intersections[i].mode == ControlMode::AUTO) ? "AUTO" : "MANUAL")
             << " | Next: " << data.intersections[i].timeRemaining << "s\n";
    }
}

static int adminPickIndex(const SystemData& data) {
    if (data.intersections.empty()) return -1;
    cout << "Choose intersection index: ";
    int idx = readChoice(0, (int)data.intersections.size() - 1);
    return idx;
}

static void adminMenu(SystemData& data) {
    while (true) {
        cout << "\n=== ADMIN MENU ===\n";
        cout << "1) List intersections\n";
        cout << "2) Add intersection\n";
        cout << "3) Remove intersection\n";
        cout << "4) Set durations (green/yellow)\n";
        cout << "5) Assign operator to intersection\n";
        cout << "6) View logs\n";
        cout << "7) Tick 1 second (AUTO only)\n";
        cout << "0) Back\n";
        cout << "Choose: ";

        int c = readChoice(0, 7);
        if (c == 0) return;

        if (c == 1) {
            adminListAll(data);
        }
        else if (c == 2) {
            cout << "Intersection name (no spaces): ";
            string name;
            cin >> name;

            Intersection it{};
            initIntersection(it, name);

            data.intersections.push_back(it);
            data.assignedOp.push_back(0);

            cout << "Added.\n";
        }
        else if (c == 3) {
            adminListAll(data);
            int idx = adminPickIndex(data);
            if (idx < 0) continue;

            cout << "Removed: " << data.intersections[idx].name << "\n";
            data.intersections.erase(data.intersections.begin() + idx);
            data.assignedOp.erase(data.assignedOp.begin() + idx);
        }
        else if (c == 4) {
            adminListAll(data);
            int idx = adminPickIndex(data);
            if (idx < 0) continue;

            cout << "Green duration: ";
            int g; cin >> g;
            cout << "Yellow duration: ";
            int y; cin >> y;

            setDurations(data.intersections[idx], g, y);
            cout << "Updated durations.\n";
        }
        else if (c == 5) {
            adminListAll(data);
            int idx = adminPickIndex(data);
            if (idx < 0) continue;

            cout << "Assign to (0=None, 1=Operator1, 2=Operator2): ";
            int op = readChoice(0, 2);
            data.assignedOp[idx] = op;

            cout << "Assigned: " << opName(op) << "\n";
        }
        else if (c == 6) {
            viewLogs();
        }
        else if (c == 7) {

            for (int i = 0; i < (int)data.intersections.size(); i++) tickOne(data, i);
            cout << "Ticked 1 second.\n";
        }
    }
}

// ---------- OPERATOR MENU ----------
static void operatorMenu(SystemData& data, const User& u) {
    int idx = pickAssignedIntersection(data, u.operatorId);

    if (idx == -1) {
        cout << "\nWelcome, " << u.display << "\n\n";
        cout << "Assigned Intersection: None\n\n";
        return;
    }


    printDashboard(u.display, data.intersections[idx]);

    while (true) {
        cout << "\n=== OPERATOR MENU (" << u.display << ") ===\n";
        cout << "1) Show dashboard\n";
        cout << "2) Switch AUTO/MANUAL\n";
        cout << "3) Manual set GREEN\n";
        cout << "4) Tick 1 second\n";
        cout << "5) View logs\n";
        cout << "0) Back\n";
        cout << "Choose: ";

        int c = readChoice(0, 5);
        if (c == 0) return;


        idx = pickAssignedIntersection(data, u.operatorId);
        if (idx == -1) {
            cout << "No assigned intersections.\n";
            continue;
        }

        Intersection& it = data.intersections[idx];

        if (c == 1) {
            printDashboard(u.display, it);
        }
        else if (c == 2) {
            cout << "1) AUTO\n";
            cout << "2) MANUAL\n";
            cout << "Choose: ";
            int m = readChoice(1, 2);

            if (m == 1) {
                it.mode = ControlMode::AUTO;
                logChange(it.name, directionToString(it.currentDirection), "AUTO MODE");
                cout << "Switched to AUTO.\n";
                printDashboard(u.display, it);
            } else {

                it.mode = ControlMode::MANUAL;
                cout << "Set GREEN direction now (0=North,1=East,2=South,3=West): ";
                int dir = readChoice(0, 3);

                setManualGreen(it, dir); 
                logChange(it.name, directionToString(it.currentDirection), "MANUAL MODE");
                cout << "Switched to MANUAL and set GREEN.\n";
                printDashboard(u.display, it);
            }
        }
        else if (c == 3) {

            if (it.mode != ControlMode::MANUAL) {
                cout << "You must switch to MANUAL first.\n";
                continue;
            }
            cout << "Direction (0=North,1=East,2=South,3=West): ";
            int dir = readChoice(0, 3);
            setManualGreen(it, dir);
            printDashboard(u.display, it);
        }
        else if (c == 4) {
            if (it.mode == ControlMode::MANUAL) {
                cout << "Manual mode: waiting for operator command (no auto change).\n";
                printDashboard(u.display, it);
            } else {
                tickOne(data, idx);
                cout << "Ticked 1 second.\n";
                printDashboard(u.display, it);
            }
        }
        else if (c == 5) {
            viewLogs();
        }
    }
}

void runUI(SystemData& data) {

    if (data.intersections.empty()) {
        Intersection demo{};
        initIntersection(demo, "NguyenVanLinh");
        data.intersections.push_back(demo);
        data.assignedOp.push_back(1); 
    }

    while (true) {
        cout << "\n=== SMART CITY TRAFFIC SYSTEM ===\n";
        User u = selectUser();

        if (u.role == ADMIN) adminMenu(data);
        else operatorMenu(data, u);

        cout << "\nContinue? (1=Yes, 0=No): ";
        int cont = readChoice(0, 1);
        if (cont == 0) break;
    }
}


