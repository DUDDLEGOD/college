/*AIM:
Company maintains employee information as employee ID, name, designation and salary.
Allow user to add, delete information of employee. 
Display information of particular employee.
If employee does not exist an appropriate message is displayed.
If it is, then the system displays the employee details. 
Use sequential file to maintain the data.

1. Create File
2. Open File
3. Read File
4. Write in File
5. Update in File
6. Search in File
7. Display File

INPUT: Employee Information

OUTPUT: Employee Information in Sequential File  

Author: Ashish Dange
*/
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>

using namespace std;

struct Employee {
  int EID;
  char name[50];
  char designation[50];
  float salary;
};

class SequentialFile {
  private:
    const char* filename = "employee.dat";
    Employee getEmployeeInput() {
      Employee emp;
      cout << "Enter Employee ID: ";
      cin >> emp.EID;
      cin.ignore();
      cout << "Enter Employee Name: ";
      cin.getline(emp.name, 50);
      cout << "Enter Employee Designation: ";
      cin.getline(emp.designation, 50);
      cout << "Enter Employee Salary: ";
      cin >> emp.salary;
      return emp;
    }

  public:
    void addRecord() {
      ofstream out(filename, ios::app | ios::binary);
      if (!out) { cout << "Error opening file!\n"; return; }
      cout << "\n--- Add New Employee ---\n";
      Employee emp = getEmployeeInput();
      out.write((char*)&emp, sizeof(Employee));
      out.close();
      cout << "Record inserted successfully!\n";
    }

    void displayAll() {
      ifstream in(filename, ios::in | ios::binary);
      if (!in) { cout << "\nNo records found or file does not exist.\n"; return; }
      cout << "\n--------------------------------------------------------------\n";
      cout << left << setw(10) << "EMP ID" << setw(20) << "NAME" << setw(20) << "DESIGNATION" << "SALARY\n";
      cout << "--------------------------------------------------------------\n";
      Employee emp;
      while (in.read((char*)&emp, sizeof(Employee))) {
        cout << left << setw(10) << emp.EID 
          << setw(20) << emp.name 
          << setw(20) << emp.designation 
          << emp.salary << "\n";
      }
      in.close();
      cout << "--------------------------------------------------------------\n";
    }

    void searchRecord(const char* targetName) {
      ifstream in(filename, ios::in | ios::binary);
      if (!in) { cout << "\nFile not found.\n"; return; }
      Employee emp;
      bool found = false;
      while (in.read((char*)&emp, sizeof(Employee))) {
        if (strcmp(emp.name, targetName) == 0) {
          cout << "\n--- Record Found ---\n";
          cout << "ID: " << emp.EID << "\nName: " << emp.name 
            << "\nDesignation: " << emp.designation << "\nSalary: " << emp.salary << "\n";
          found = true;
          break;
        }
      }
      if (!found) cout << "\nRecord not found!\n";
      in.close();
    }

    void updateRecord(const char* targetName) {
      fstream file(filename, ios::in | ios::out | ios::binary);
      if (!file) { cout << "\nFile not found.\n"; return; }
      Employee emp;
      bool found = false;
      int recordIndex = 0;
      while (file.read((char*)&emp, sizeof(Employee))) {
        if (strcmp(emp.name, targetName) == 0) {
          cout << "\nRecord Found! Enter new details:\n";
          Employee updatedEmp = getEmployeeInput();
          file.seekp(recordIndex * sizeof(Employee), ios::beg);
          file.write((char*)&updatedEmp, sizeof(Employee));
          cout << "Record updated successfully!\n";
          found = true;
          break;
        }
        recordIndex++; 
      }
      if (!found) cout << "\nRecord not found!\n";
      file.close();
    }

    void deleteRecord(const char* targetName) {
      ifstream in(filename, ios::in | ios::binary);
      if (!in) { cout << "\nFile not found.\n"; return; }
      ofstream tempFile("temp.dat", ios::out | ios::binary);
      Employee emp;
      bool found = false;
      while (in.read((char*)&emp, sizeof(Employee))) {
        if (strcmp(emp.name, targetName) != 0) {
          tempFile.write((char*)&emp, sizeof(Employee));
        } else {
          found = true; 
        }
      }
      in.close();
      tempFile.close();
      if (found) {
        remove(filename); 
        rename("temp.dat", filename);
        cout << "\nRecord deleted successfully!\n";
      } else {
        remove("temp.dat");
        cout << "\nRecord not found!\n";
      }
    }
};

int main() {
  SequentialFile fileManager;
  char searchName[50];
  int choice = 0;

  while (choice != 6) {
    cout << "\n--- Employee Database ---\n";
    cout << "1. Add Employee\n2. Display All\n3. Search Employee\n";
    cout << "4. Update Employee\n5. Delete Employee\n6. Exit\n";
    cout << "Choice: ";

    cin >> choice;

    switch (choice) {
      case 1:
        fileManager.addRecord();
        break;
      case 2:
        fileManager.displayAll();
        break;
      case 3:
        cout << "Enter Name to Search: ";
        cin >> ws; 
        cin.getline(searchName, 50);
        fileManager.searchRecord(searchName);
        break;
      case 4:
        cout << "Enter Name to Update: ";
        cin >> ws;
        cin.getline(searchName, 50);
        fileManager.updateRecord(searchName);
        break;
      case 5:
        cout << "Enter Name to Delete: ";
        cin >> ws;
        cin.getline(searchName, 50);
        fileManager.deleteRecord(searchName);
        break;
      case 6:
        cout << "Exiting...\n";
        break;
      default:
        cout << "Invalid choice!\n";
    }
  }
  return 0;
}
