#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
using namespace std;

void Exit(){
    cout << "     THANK YOU FOR USING AHON.\n";
    cout << "            STAY SAFE!";
    exit (0);
}

struct FloodEvent {
    string date;
    float rainfall;
    int householdsAffected;
    int casualties;
    string severity;
};

struct Barangay {
    string name;
    int numberOfHouseholds;
    string riskLevel;
    vector<FloodEvent> events;
};

vector<Barangay> barangays;

void addBarangay(){
    Barangay b;
    int add_action;
    
    cout << "\n====================================\n";
    cout << "          ADD BARANGAY\n";
    cout << "====================================\n";
    cout << "Name: ";
    getline (cin, b.name);
    cout << "No. of Households: ";
    cin >> b.numberOfHouseholds;
    cout << "Risk Level [HIGH/MEDIUM/LOW]: ";
    cin.ignore();
    getline (cin, b.riskLevel);
    
    barangays.push_back(b);

    cout << "\nBARANGAY SAVED!\n";
    cout << "-----------------------------------\n";
    cout << "[1] MAIN MENU              [2] EXIT\n";
    cout << "-----------------------------------\n";

        do {
            cout << "Select an action: ";
            cin >> add_action;
            cin.ignore();
            cout << "-----------------------------------\n";

                if (add_action == 1){
                    return;
                }
                else if (add_action == 2){
                    Exit();
                }
                else {
                    cout << "INVALID INPUT!\n";
                }

        } while (add_action != 1 && add_action != 2);
}

void updateBarangay(int foundIndex){
    int add_action;
    
    cout << "\n====================================\n";
    cout << "          UPDATE BARANGAY\n";
    cout << "====================================\n";
    cout << "New Name: ";
    getline (cin, barangays[foundIndex].name);
    cout << "New No. of Households: ";
    cin >> barangays[foundIndex].numberOfHouseholds;
    cout << "New Risk Level [LOW/MEDIUM/HIGH]: ";
    cin.ignore();
    getline (cin, barangays[foundIndex].riskLevel);

    cout << "BARANGAY UPDATED!\n";

    cout << "-----------------------------------\n";
    cout << "[1] MAIN MENU              [2] EXIT\n";
    cout << "-----------------------------------\n";

        do {
            cout << "Select an action: ";
            cin >> add_action;
            cin.ignore();
            cout << "-----------------------------------\n";

                if (add_action == 1){
                    return;
                }
                else if (add_action == 2){
                    Exit();
                }
                else {
                    cout << "INVALID INPUT!\n";
                }

        } while (add_action != 1 && add_action != 2);

}

void logFloodEvent(int foundIndex){
    FloodEvent f;
    int FloodEvent_action;

    cout << "\n====================================\n";
    cout << "          LOG A FLOOD EVENT\n";
    cout << "====================================\n";
    cout << "Date (YYYY-MM-DD): ";
    cin >> f.date;
    cout << "Rainfall (mm): ";
    cin >> f.rainfall;
    cout << "Household Affected: ";
    cin >> f.householdsAffected;
    cout << "Casualties: ";
    cin >> f.casualties;
    cout << "Severity [LOW/MODERATE/HIGH]: ";
    cin >> f.severity;

    barangays[foundIndex].events.push_back(f);

    cout << "FLOOD EVENT LOGGED!\n";

    cout << "-----------------------------------\n";
    cout << "[1] MAIN MENU              [2] EXIT\n";
    cout << "-----------------------------------\n";

        do {
            cout << "Select an action: ";
            cin >> FloodEvent_action;
            cin.ignore();
            cout << "-----------------------------------\n";

                if (FloodEvent_action == 1){
                    return;
                }
                else if (FloodEvent_action == 2){
                    Exit();
                }
                else {
                    cout << "INVALID INPUT!\n";
                }

        } while (FloodEvent_action != 1 && FloodEvent_action != 2);

}

void manage(){
    string search;
    int foundIndex = -1;

    cout << "\n====================================\n";
    cout << "          MANAGE BARANGAYS\n";
    cout << "====================================\n";
    cout << "Search A barangay: ";
    getline (cin, search);

    for (int i = 0; i < barangays.size(); i++ ){
        if (barangays[i].name == search){
            foundIndex = i;
            break;
        }
    }

    if (foundIndex == -1){
        int pick;
        cout << "-----------------------------------\n";
        cout << "         BARANGAY NOT FOUND!\n";
        cout << "[1] ADD BARANGAY           [2] EXIT\n";
        cout << "-----------------------------------\n";

        do {
            cout << "Select an action: ";
            cin >> pick;
            cin.ignore();
            cout << "\n-----------------------------------\n";

                if (pick == 1){
                    addBarangay();
                    return;
                }
                else if (pick == 2){
                    Exit();
                }
                else {
                    cout << "INVALID INPUT!\n";
                }

        } while (pick != 1 && pick != 2);
    }

    else {
    int details_action;
        cout << "\n-----------------------------------\n";
        cout << "          BARANGAY DETAILS\n";
        cout << left << setw(25) << "Name:"                 << barangays[foundIndex].name << "\n";
        cout << left << setw(25) << "Number of Households:" << barangays[foundIndex].numberOfHouseholds << "\n";
        cout << left << setw(25) << "Risk Level:"           << barangays[foundIndex].riskLevel << "\n";
        cout << "-----------------------------------\n";
        cout << "[1] UPDATE [2] LOG A FLOOD EVENT [4] EXIT\n";
        cout << "-----------------------------------\n";
        
        do {
            cout << "Select an action [1-3]: ";
            cin >> details_action;
            cin.ignore();
            cout << "\n-----------------------------------\n";

                if (details_action == 1){
                    updateBarangay(foundIndex); //update-- kulang pa
                    return;
                }
                else if (details_action == 2){
                    logFloodEvent(foundIndex); //log a flood event
                    return;
                }
                else if (details_action == 3){
                    Exit();
                }
                else {
                    cout << "INVALID INPUT!\n";
                }
        } while (details_action < 1 || details_action > 3);
    }

return;
}

void risk_level(){
    cout << "Nyikyak";
}

int main(){
    Barangay b;
    b.name = "San Jose";
    b.numberOfHouseholds = 120;
    b.riskLevel = "High";
    barangays.push_back(b); 

int pick;

do {
    cout << "===================================\n";
    cout << "            AHON SYSTEM\n";
    cout << "Area Hazard & Overflow Notification\n";
    cout << "===================================\n";
    cout << "             MAIN MENU\n";
    cout << "[1] Manage Barangays\n";
    cout << "[2] View Risk Level Summary\n";
    cout << "[3] Exit\n";
    cout << "-----------------------------------\n";

    cout << "Select an action [1-3]: ";
    cin >> pick;
    cin.ignore();
    cout << "-----------------------------------\n";

    if (pick == 1){
        manage();
    }
    else if (pick == 2){
        risk_level();
    }
    else if (pick == 3){
        Exit();
    }
    else {
        cout << "INVALID INPUT!\n";
    }

} while (pick != 3);

    return 0;
}

// Ano pa kulang guide
// ✅ manage, Search, Main, Exit, Add, Update,Log
// ❌ Risk Level Summary, yung vector and struct di pa ayos (what if mag file handling)