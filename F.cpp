#include <iostream>
#include <string>
using namespace std;

// Base class
class Person {
protected:
    string fullName;

public:
    Person() {
        fullName = "";
    }

    virtual void display() {
        cout << "Name: " << fullName << endl;
    }
};

// Student class inherits from Person
class Student : public Person {
private:
    string regNo;
    string course;

public:
    Student() {
        fullName = "";
        regNo = "";
        course = "";
    }

    void setStudent(string n, string r, string c) {
        fullName = n;
        regNo = r;
        course = c;
    }

    string getRegNo() {
        return regNo;
    }

    string getName() {
        return fullName;
    }

    string getCourse() {
        return course;
    }

    void setName(string n) {
        fullName = n;
    }

    void setCourse(string c) {
        course = c;
    }

    void display() override {
        cout << "\nStudent Details" << endl;
        cout << "------------------------" << endl;
        cout << "Full Name          : " << fullName << endl;
        cout << "Registration No    : " << regNo << endl;
        cout << "Course Taken       : " << course << endl;
    }
};

// converts a string to lowercase so reg no comparisons aren't case sensitive
string toLower(string s) {
    for (int i = 0; i < s.length(); i++) {
        s[i] = tolower(s[i]);
    }
    return s;
}

void searchStudent(Student s[], int total, string reg) {
    bool found = false;
    for (int i = 0; i < total; i++) {
        if (toLower(s[i].getRegNo()) == toLower(reg)) {
            s[i].display();
            found = true;
        }
    }
    if (!found) {
        cout << "Student not found!" << endl;
    }
}

bool isDuplicateRegNo(Student s[], int total, string reg) {
    for (int i = 0; i < total; i++) {
        if (toLower(s[i].getRegNo()) == toLower(reg)) {
            return true;
        }
    }
    return false;
}

int findStudentIndex(Student s[], int total, string reg) {
    for (int i = 0; i < total; i++) {
        if (toLower(s[i].getRegNo()) == toLower(reg)) {
            return i;
        }
    }
    return -1;
}

void menu() {
    cout << "\n========== STUDENT MANAGEMENT SYSTEM ==========\n";
    cout << "1. Add Students\n";
    cout << "2. Display Students\n";
    cout << "3. Search Student\n";
    cout << "4. Edit Student\n";
    cout << "5. Delete Student\n";
    cout << "6. Exit\n";
    cout << "Choose Option: ";
}

int main() {
    Student students[50];
    int choice;
    int total = 0;
    bool running = true;

    // pick role at the start
    int roleChoice;
    cout << "1. Admin\n2. Viewer\nChoose role: ";
    cin >> roleChoice;
    cin.ignore();
    bool isAdmin = (roleChoice == 1);

    if (isAdmin)
        cout << "Logged in as Admin.\n";
    else
        cout << "Logged in as Viewer.\n";

    while (running) {
        menu();
        cin >> choice;
        cin.ignore();

        switch (choice) {
        case 1: {
            if (!isAdmin) {
                cout << "You are a viewer, you can't add students.\n";
                break;
            }

            int n;
            cout << "How many students do you want to add? ";
            cin >> n;
            cin.ignore();

            for (int i = 0; i < n; i++) {
                if (total >= 50) {
                    cout << "Storage full, can't add more students.\n";
                    break;
                }

                string name, reg, course;
                cout << "\nStudent " << i + 1 << endl;

                cout << "Enter Full Name: ";
                getline(cin, name);

                cout << "Enter Registration Number: ";
                getline(cin, reg);

                if (isDuplicateRegNo(students, total, reg)) {
                    cout << "That registration number is already used. Skipping.\n";
                    continue;
                }

                cout << "Enter Course Taken: ";
                getline(cin, course);

                students[total].setStudent(name, reg, course);
                total++;
            }

            cout << "\nStudents Added Successfully!" << endl;
            break;
        }

        case 2: {
            if (total == 0) {
                cout << "No students available.\n";
            } else {
                for (int i = 0; i < total; i++) {
                    students[i].display();
                }
            }
            break;
        }

        case 3: {
            if (total == 0) {
                cout << "No records available.\n";
            } else {
                string reg;
                cout << "Enter Registration Number: ";
                getline(cin, reg);
                searchStudent(students, total, reg);
            }
            break;
        }

        case 4: {
            if (!isAdmin) {
                cout << "You are a viewer, you can't edit students.\n";
                break;
            }

            if (total == 0) {
                cout << "No records to edit.\n";
                break;
            }

            string reg;
            cout << "Enter Registration Number to edit: ";
            getline(cin, reg);

            int idx = findStudentIndex(students, total, reg);
            if (idx == -1) {
                cout << "Student not found!\n";
            } else {
                students[idx].display();

                string newName, newCourse;
                cout << "Enter new name: ";
                getline(cin, newName);
                cout << "Enter new course: ";
                getline(cin, newCourse);

                students[idx].setName(newName);
                students[idx].setCourse(newCourse);
                cout << "Updated successfully.\n";
            }
            break;
        }

        case 5: {
            if (!isAdmin) {
                cout << "You are a viewer, you can't delete students.\n";
                break;
            }

            if (total == 0) {
                cout << "No records to delete.\n";
                break;
            }

            string reg;
            cout << "Enter Registration Number to delete: ";
            getline(cin, reg);

            int idx = findStudentIndex(students, total, reg);
            if (idx == -1) {
                cout << "Student not found!\n";
            } else {
                students[idx].display();

                for (int i = idx; i < total - 1; i++) {
                    students[i] = students[i + 1];
                }
                total--;
                cout << "Deleted successfully.\n";
            }
            break;
        }

        case 6:
            running = false;
            cout << "Thank you for using the Student Management System." << endl;
            break;

        default:
            cout << "Invalid Choice!" << endl;
        }
    }

    return 0;
}