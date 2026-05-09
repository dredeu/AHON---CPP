#include <ctime>
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <fstream>
#include <sstream>
using namespace std;

void Exit(){
    cout << "     THANK YOU FOR USING AHON.\n";
    cout << "            STAY SAFE!";
    exit (0);
}

//STRUCTS
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

vector <Barangay> barangays;

void Save(){
    fstream myFile;
    myFile.open("areas.txt", ios::out);

   for (int i = 0; i < barangays.size(); i++){
    myFile << barangays[i].name << "\n";
    myFile << barangays[i].numberOfHouseholds << "\n";
    myFile << barangays[i].riskLevel << "\n";
    myFile << barangays[i].events.size() << "\n";

    for (int j = 0; j < barangays[i].events.size(); j++){
        myFile << barangays[i].events[j].date << "\n";
        myFile << barangays[i].events[j].rainfall << "\n";
        myFile << barangays[i].events[j].householdsAffected << "\n";
        myFile << barangays[i].events[j].casualties << "\n";
        myFile << barangays[i].events[j].severity << "\n";
    }
}
    myFile.close();
}

void Load(){
    fstream myFile;
    myFile.open("areas.txt", ios::in);

    Barangay b;
    while (getline(myFile, b.name)){
        myFile >> b.numberOfHouseholds;
        myFile.ignore();
        getline(myFile, b.riskLevel);

        int eventCount;
        myFile >> eventCount;
        myFile.ignore();

        for (int i = 0; i < eventCount; i++){
            FloodEvent f;
            getline(myFile, f.date);
            myFile >> f.rainfall;
            myFile.ignore();
            myFile >> f.householdsAffected;
            myFile.ignore();
            myFile >> f.casualties;
            myFile.ignore();
            getline(myFile, f.severity);
            b.events.push_back(f);
        }
        barangays.push_back(b);
        b.events.clear();
    }
    myFile.close();
}

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

    Save();
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

    Save();
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

void Riskflagger(int foundIndex){
    time_t now = time(0);
    tm* today = localtime(&now);

    int floodCount = 0, highCount = 0, moderateCount = 0;
    int currentYear = today->tm_year + 1900;
    int currentMonth = today->tm_mon + 1;
    int totalHouseholds = barangays[foundIndex].numberOfHouseholds;

    for (int i = 0; i < barangays[foundIndex].events.size(); i++){
        FloodEvent f = barangays[foundIndex].events[i];
        
        int eventYear  = stoi(f.date.substr(0, 4));
        int eventMonth = stoi(f.date.substr(5, 2));

        int totalMonthsToday = currentYear * 12 + currentMonth;
        int totalMonthsEvent = eventYear * 12 + eventMonth;

        if (totalMonthsToday - totalMonthsEvent <= 12){
            floodCount++;
            float percentage = ((float)f.householdsAffected / totalHouseholds) * 100;

            if (f.casualties >= 10 || percentage >= 50 || f.rainfall > 30){
                highCount++;
            }
            else if (f.casualties >= 5 || percentage >= 25 || f.rainfall >= 15){
                moderateCount++;
            }
        }
    }

    if (floodCount >= 3 && highCount >= 3){
        barangays[foundIndex].riskLevel = "HIGH";
    }
    else if (floodCount >= 3 && moderateCount >= 3){
        barangays[foundIndex].riskLevel = "MEDIUM";
    }
    else {
        barangays[foundIndex].riskLevel = "LOW";
    }

    cout << "Risk Level automatically updated to: " << barangays[foundIndex].riskLevel << "\n";
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
    //cout << "Severity [LOW/MODERATE/HIGH]: "; cin >> f.severity;                                -automated

    //SEVERITY
    string severity;                                                                                    //percentage based of rainfall return
    float percentage = (f.householdsAffected / barangays[foundIndex].numberOfHouseholds) * 100;           // 100-year-return (very catastrophic rainfall event)
    if (f.casualties >= 10 || percentage >= 50){                                                        // if 50% or above ang affected household, SEVERITY LEVEL: HIGH
        severity = "HIGH";
    }
    else if (f.casualties >= 5 || percentage >= 10){
        severity = "MODERATE";
    }
    else{
        severity = "LOW";
    }
    
    barangays[foundIndex].events.push_back(f);
    cout << "FLOOD EVENT LOGGED!\n";
    
    cout << "-----------------------------------\n";
    cout << "\nSEVERITY: " << severity << endl;


    //RAINFALL ASSESSMENT
    string rainfallAssesment;
    if (f.rainfall > 30){
        rainfallAssesment = "CONDITION: CRITICAL\nACTION: Begin evacuation immediately";
    }
    else if (f.rainfall >= 15){
        rainfallAssesment = "CONDITION: WARNING\nACTION: Prepare for possible evacuation!";
    }
    else {
       rainfallAssesment = "CONDITION: NORMAL\nACTION: Monitor rainfall levels.";
    }

    cout << rainfallAssesment << endl;
    Riskflagger(foundIndex);
Save();

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
        cout << "[1] UPDATE [2] LOG A FLOOD EVENT [3] EXIT\n";
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

void risklevelSummary(){
    cout << "\n====================================\n";
    cout << "          RISK LEVEL SUMMARY\n";
    cout << "====================================\n";
    cout << "HIGH RISK BARANGAY(s):\n";
    for (int i = 0; i<barangays.size(); i ++){
        if (barangays[i].riskLevel == "HIGH"){
                cout <<" - " << barangays[i].name <<"\n";
        }
    }
    cout << "\n-----------------------------------\n";
    cout << "MEDIUM RISK BARANGAY(s):\n";
    for (int i = 0; i<barangays.size(); i ++){
        if (barangays[i].riskLevel == "MEDIUM"){
                cout <<" - " << barangays[i].name <<"\n";
        }
    }
    cout << "\n-----------------------------------\n";
    cout << "LOW RISK BARANGAY(s):\n";
    for (int i = 0; i<barangays.size(); i ++){
        if (barangays[i].riskLevel == "LOW"){
                cout <<" - " << barangays[i].name <<"\n";
        }
    }
        int risklvl_action;
        cout << "\n-----------------------------------\n";
        cout << "[1] MAIN MENU              [2] EXIT\n";
        cout << "-----------------------------------\n";

        do {
            cout << "Select an action: ";
            cin >> risklvl_action;
            cin.ignore();
            cout << "\n-----------------------------------\n";

                if (risklvl_action == 1){
                    return;
                }
                else if (risklvl_action == 2){
                    Exit();
                }
                else {
                    cout << "INVALID INPUT!\n";
                }

        } while (risklvl_action != 1 && risklvl_action != 2);
}

int main(){
    Load();
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
        risklevelSummary();
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

/* 
Ano pa kulang guide
✅ manage, Search, Main, Exit, Add, Update,Log, Rainfall Assessmnent, Auto risk flagging, Risk Level Summary, File Handling
❌ 
*/