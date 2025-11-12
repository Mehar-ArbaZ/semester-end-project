#include <iostream>
#include <fstream>
#include <string>
using namespace std;

const int maxEmployees = 10;

// Hardcoded login credentials
const string adminUsername = "admin";
const string adminPassword = "hr123";

class Employee {
public:
    int empId;
    string name;
    string department;
    float salary;

    Employee() {
        empId = 0;
        name = "";
        department = "";
        salary = 0.0;
    }

    void inputDetails() {
        cout << "\nEnter Employee ID: ";
        cin >> empId;
        cin.ignore();
        cout << "Enter Name: ";
        getline(cin, name);
        cout << "Enter Department: ";
        getline(cin, department);
        cout << "Enter Salary: ";
        cin >> salary;
    }

    void display() {
        cout << "\nEmployee ID: " << empId;
        cout << "\nName: " << name;
        cout << "\nDepartment: " << department;
        cout << "\nSalary: RS" << salary << endl;
    }

    void updateSalary(float newSalary) {
        salary = newSalary;
    }
};

class HRManagement {
private:
    Employee employees[maxEmployees];
    int empCount;

public:
    HRManagement() {
        empCount = 0;
    }

    void addEmployee() {
        if (empCount < maxEmployees) {
            employees[empCount].inputDetails();
            empCount++;
            cout << "\nEmployee added successfully.\n";
        } else {
            cout << "\nEmployee limit reached!\n";
        }
    }

    void viewAllEmployees() {
        if (empCount == 0) {
            cout << "\nNo employees to display.\n";
            return;
        }

        cout << "\nAll Employee Records:\n";
        for (int i = 0; i < empCount; i++) {
            employees[i].display();
        }
    }

    void searchEmployee() {
        int id;
        cout << "Enter Employee ID to search: ";
        cin >> id;

        for (int i = 0; i < empCount; i++) {
            if (employees[i].empId == id) {
                employees[i].display();
                return;
            }
        }

        cout << "Employee not found!\n";
    }

    void updateEmployeeSalary() {
        int id;
        float newSalary;
        cout << "Enter Employee ID to update salary: ";
        cin >> id;

        for (int i = 0; i < empCount; i++) {
            if (employees[i].empId == id) {
                cout << "Enter new salary: ";
                cin >> newSalary;
                employees[i].updateSalary(newSalary);
                cout << "Salary updated successfully.\n";
                return;
            }
        }

        cout << "Employee not found!\n";
    }

    void recruitmentProcess() {
        if (empCount >= maxEmployees) {
            cout << "\nCannot recruit. Maximum employees reached.\n";
            return;
        }

        string name, department;
        float testScore;

        cin.ignore();
        cout << "\n--- Recruitment Process ---\n";
        cout << "Enter Candidate Name: ";
        getline(cin, name);
        cout << "Enter Department to Hire For: ";
        getline(cin, department);
        cout << "Enter Candidate Test Score (0-100): ";
        cin >> testScore;

        if (testScore >= 60) {
            cout << "\nCandidate passed. Proceeding to hire...\n";
            employees[empCount].empId = 1000 + empCount;
            employees[empCount].name = name;
            employees[empCount].department = department;
            employees[empCount].salary = 30000; // default starting salary
            empCount++;
            cout << "Candidate hired successfully!\n";
        } else {
            cout << "Candidate did not qualify.\n";
        }
    }

    void deleteEmployee() {
        int id;
        cout << "Enter Employee ID to delete: ";
        cin >> id;

        for (int i = 0; i < empCount; i++) {
            if (employees[i].empId == id) {
                // Shift employees to remove the one at index i
                for (int j = i; j < empCount - 1; j++) {
                    employees[j] = employees[j + 1];
                }
                empCount--;
                cout << "Employee deleted successfully.\n";
                return;
            }
        }
        cout << "Employee not found.\n";
    }

    void saveToFile() {
        ofstream fout("employees.txt");
        if (!fout) {
            cout << "Error opening file to save.\n";
            return;
        }

        for (int i = 0; i < empCount; i++) {
            fout << employees[i].empId << ","
                 << employees[i].name << ","
                 << employees[i].department << ","
                 << employees[i].salary << "\n";
        }

        fout.close();
        cout << "Data saved to file successfully.\n";
    }

    void loadFromFile() {
        ifstream fin("employees.txt");
        if (!fin) {
            cout << "No saved data found.\n";
            return;
        }

        empCount = 0;
        while (fin >> employees[empCount].empId) {
            fin.ignore(); // skip comma
            getline(fin, employees[empCount].name, ',');
            getline(fin, employees[empCount].department, ',');
            fin >> employees[empCount].salary;
            fin.ignore(); // skip newline
            empCount++;
            if (empCount >= maxEmployees) break;
        }

        fin.close();
        cout << "Data loaded from file.\n";
    }
};

// Login function
bool login() {
    string user, pass;
    cout << "======= LOGIN PAGE =======\n";
    cout << "Enter username: ";
    cin >> user;
    cout << "Enter password: ";
    cin >> pass;

    if (user == adminUsername && pass == adminPassword) {
        cout << "Login successful.\n";
        return true;
    } else {
        cout << "Invalid credentials. Access denied.\n";
        return false;
    }
}

int main() {
    if (!login()) return 0;

    HRManagement hr;
    hr.loadFromFile(); // Load existing data

    int choice;

    do {
        cout << "\n========== HR MANAGEMENT SYSTEM ==========\n";
        cout << "1. Add Employee\n";
        cout << "2. View All Employees\n";
        cout << "3. Search Employee by ID\n";
        cout << "4. Update Employee Salary\n";
        cout << "5. Recruitment Process\n";
        cout << "6. Delete Employee\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            hr.addEmployee();
            break;
        case 2:
            hr.viewAllEmployees();
            break;
        case 3:
            hr.searchEmployee();
            break;
        case 4:
            hr.updateEmployeeSalary();
            break;
        case 5:
            hr.recruitmentProcess();
            break;
        case 6:
            hr.deleteEmployee();
            break;
        case 7:
            hr.saveToFile(); // Save data before exiting
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid choice! Try again.\n";
        }

    } while (choice != 7);

    return 0;
}

