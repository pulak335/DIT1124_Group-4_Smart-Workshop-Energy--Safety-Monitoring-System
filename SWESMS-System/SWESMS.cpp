#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iomanip>
#include <ctime>

using namespace std;

// Equipment structure
struct Equipment {
    int id;
    string name;
    string type; // "Solar Panel" or "Wind Turbine"
    double capacity; // kW capacity
    double currentUsage; // Current usage in kWh
    bool isActive;
    
    Equipment(int _id, string _name, string _type, double _capacity) 
        : id(_id), name(_name), type(_type), capacity(_capacity), currentUsage(0), isActive(true) {}
};

// Energy System Manager
class SWESMS {
private:
    vector<Equipment> equipmentList;
    int nextEquipmentId;
    
public:
    SWESMS() : nextEquipmentId(1) {}
    
    // Main menu
    void showMainMenu() {
        cout << "\n========================================" << endl;
        cout << "    SWESMS - Solar & Wind Energy System" << endl;
        cout << "========================================" << endl;
        cout << "1. Add Equipment" << endl;
        cout << "2. View Equipment" << endl;
        cout << "3. Update Usage" << endl;
        cout << "4. Generate Daily Report" << endl;
        cout << "5. Generate Weekly Report" << endl;
        cout << "6. Generate Monthly Report" << endl;
        cout << "7. Exit" << endl;
        cout << "========================================" << endl;
        cout << "Enter your choice: ";
    }
    
    // Add new equipment
    void addEquipment() {
        string name, type;
        double capacity;
        int typeChoice;
        
        cout << "\n--- Add New Equipment ---" << endl;
        cout << "Enter equipment name: ";
        cin.ignore();
        getline(cin, name);
        
        cout << "Select equipment type:" << endl;
        cout << "1. Solar Panel" << endl;
        cout << "2. Wind Turbine" << endl;
        cout << "Enter choice (1-2): ";
        cin >> typeChoice;
        
        switch(typeChoice) {
            case 1:
                type = "Solar Panel";
                break;
            case 2:
                type = "Wind Turbine";
                break;
            default:
                cout << "Invalid choice. Defaulting to Solar Panel." << endl;
                type = "Solar Panel";
        }
        
        cout << "Enter capacity (kW): ";
        cin >> capacity;
        
        Equipment newEquipment(nextEquipmentId++, name, type, capacity);
        equipmentList.push_back(newEquipment);
        
        cout << "\nEquipment added successfully!" << endl;
        cout << "ID: " << newEquipment.id << endl;
        cout << "Name: " << newEquipment.name << endl;
        cout << "Type: " << newEquipment.type << endl;
        cout << "Capacity: " << newEquipment.capacity << " kW" << endl;
    }
    
    // View all equipment
    void viewEquipment() {
        cout << "\n--- Equipment List ---" << endl;
        if (equipmentList.empty()) {
            cout << "No equipment found." << endl;
            return;
        }
        
        cout << left << setw(5) << "ID" << setw(20) << "Name" << setw(15) << "Type" 
             << setw(10) << "Capacity" << setw(12) << "Usage(kWh)" << setw(8) << "Status" << endl;
        cout << string(70, '-') << endl;
        
        for (const auto& equipment : equipmentList) {
            cout << left << setw(5) << equipment.id 
                 << setw(20) << equipment.name 
                 << setw(15) << equipment.type
                 << setw(10) << equipment.capacity
                 << setw(12) << fixed << setprecision(2) << equipment.currentUsage
                 << setw(8) << (equipment.isActive ? "Active" : "Inactive") << endl;
        }
    }
    
    // Update equipment usage
    void updateUsage() {
        int equipmentId;
        double newUsage;
        
        cout << "\n--- Update Equipment Usage ---" << endl;
        viewEquipment();
        
        if (equipmentList.empty()) {
            return;
        }
        
        cout << "\nEnter equipment ID to update: ";
        cin >> equipmentId;
        
        bool found = false;
        for (auto& equipment : equipmentList) {
            if (equipment.id == equipmentId) {
                found = true;
                cout << "Current usage for " << equipment.name << ": " << equipment.currentUsage << " kWh" << endl;
                cout << "Enter new usage (kWh): ";
                cin >> newUsage;
                
                equipment.currentUsage = newUsage;
                cout << "Usage updated successfully!" << endl;
                break;
            }
        }
        
        if (!found) {
            cout << "Equipment not found!" << endl;
        }
    }
    
    // Calculate total energy production
    double calculateTotalEnergy() {
        double total = 0;
        for (const auto& equipment : equipmentList) {
            if (equipment.isActive) {
                total += equipment.currentUsage;
            }
        }
        return total;
    }
    
    // Generate daily report
    void generateDailyReport() {
        cout << "\n--- Daily Energy Report ---" << endl;
        cout << "Date: " << __DATE__ << endl;
        cout << "Total Active Equipment: " << countActiveEquipment() << endl;
        cout << "Total Energy Production: " << fixed << setprecision(2) 
             << calculateTotalEnergy() << " kWh" << endl;
        
        if (!equipmentList.empty()) {
            cout << "\nEquipment Performance:" << endl;
            cout << string(50, '-') << endl;
            for (const auto& equipment : equipmentList) {
                if (equipment.isActive) {
                    double efficiency = (equipment.currentUsage / equipment.capacity) * 100;
                    cout << equipment.name << " (" << equipment.type << "): "
                         << equipment.currentUsage << " kWh ("
                         << fixed << setprecision(1) << efficiency << "% efficiency)" << endl;
                }
            }
        }
        
        saveReportToFile("daily_report.txt");
    }
    
    // Generate weekly report
    void generateWeeklyReport() {
        cout << "\n--- Weekly Energy Report ---" << endl;
        cout << "Report Period: Last 7 days" << endl;
        cout << "Total Active Equipment: " << countActiveEquipment() << endl;
        cout << "Estimated Weekly Production: " << fixed << setprecision(2) 
             << calculateTotalEnergy() * 7 << " kWh" << endl;
        
        saveReportToFile("weekly_report.txt");
    }
    
    // Generate monthly report
    void generateMonthlyReport() {
        cout << "\n--- Monthly Energy Report ---" << endl;
        cout << "Report Period: Last 30 days" << endl;
        cout << "Total Active Equipment: " << countActiveEquipment() << endl;
        cout << "Estimated Monthly Production: " << fixed << setprecision(2) 
             << calculateTotalEnergy() * 30 << " kWh" << endl;
        
        saveReportToFile("monthly_report.txt");
    }
    
    // Count active equipment
    int countActiveEquipment() {
        int count = 0;
        for (const auto& equipment : equipmentList) {
            if (equipment.isActive) count++;
        }
        return count;
    }
    
    // Save report to file
    void saveReportToFile(const string& filename) {
        ofstream file(filename);
        if (file.is_open()) {
            file << "SWESMS Energy Report - " << __DATE__ << endl;
            file << "Total Energy Production: " << calculateTotalEnergy() << " kWh" << endl;
            file << "Active Equipment: " << countActiveEquipment() << endl;
            file.close();
            cout << "\nReport saved to " << filename << endl;
        }
    }
};

int main() {
    SWESMS system;
    int choice;
    
    cout << "Welcome to SWESMS - Solar & Wind Energy System Management System!" << endl;
    
    while (true) {
        system.showMainMenu();
        cin >> choice;
        
        switch (choice) {
            case 1:
                system.addEquipment();
                break;
            case 2:
                system.viewEquipment();
                break;
            case 3:
                system.updateUsage();
                break;
            case 4:
                system.generateDailyReport();
                break;
            case 5:
                system.generateWeeklyReport();
                break;
            case 6:
                system.generateMonthlyReport();
                break;
            case 7:
                cout << "Thank you for using SWESMS. Goodbye!" << endl;
                return 0;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
        
        cout << "\nPress Enter to continue...";
        cin.ignore();
        cin.get();
    }
    
    return 0;
}