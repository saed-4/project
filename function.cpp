#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <iomanip>

using namespace std;

/* ============================================================
   INPUT HELPERS
   ============================================================ */
int readInt(const string &prompt) {
    int value;
    while (true) {
        cout << prompt;
        cin >> value;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a whole number.\n";
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }
    }
}

string readString(const string &prompt) {
    cout << prompt;
    string value;
    getline(cin, value);
    return value;
}

/* ============================================================
   STUDENT CLASS
   ============================================================ */
class Student {
public:
    int rollNo;
    string name;
    string className;
    int issuedBookId; // -1 means no book currently issued
    bool valid;

    Student(int roll, string n, string c)
        : rollNo(roll), name(move(n)), className(move(c)),
          issuedBookId(-1), valid(true) {}
};

/* ============================================================
   BOOK CLASS
   ============================================================ */
class Book {
public:
    int bookId;
    string title;
    string author;
    int totalCopies;
    int availableCopies;
    bool valid;

    Book(int id, string t, string a, int total)
        : bookId(id), title(move(t)), author(move(a)),
          totalCopies(total), availableCopies(total), valid(true) {}
};

/* ============================================================
   LIBRARY CLASS - holds all data and operations
   ============================================================ */
class Library {
private:
    vector<Student> students;
    vector<Book> books;

    int findStudentIndex(int roll) {
        for (size_t i = 0; i < students.size(); i++)
            if (students[i].valid && students[i].rollNo == roll)
                return static_cast<int>(i);
        return -1;
    }

    int findBookIndex(int id) {
        for (size_t i = 0; i < books.size(); i++)
            if (books[i].valid && books[i].bookId == id)
                return static_cast<int>(i);
        return -1;
    }

public:
    /* ---------------- STUDENT OPERATIONS ---------------- */
    void createStudent() {
        int roll = readInt("Enter Roll No: ");
        if (findStudentIndex(roll) != -1) {
            cout << "A student with this Roll No already exists!\n";
            return;
        }
        string name = readString("Enter Name: ");
        string cls = readString("Enter Class: ");
        students.emplace_back(roll, name, cls);
        cout << "Student record created successfully!\n";
    }

    void displayAllStudents() {
        bool found = false;
        cout << "\n" << left
             << setw(10) << "Roll No" << setw(20) << "Name"
             << setw(15) << "Class" << setw(15) << "Book ID Issued" << "\n";
        for (auto &s : students) {
            if (s.valid) {
                found = true;
                cout << left << setw(10) << s.rollNo << setw(20) << s.name
                     << setw(15) << s.className
                     << setw(15) << (s.issuedBookId == -1 ? string("None") : to_string(s.issuedBookId))
                     << "\n";
            }
        }
        if (!found) cout << "No student records found.\n";
    }

    void displaySpecificStudent() {
        int roll = readInt("Enter Roll No to search: ");
        int idx = findStudentIndex(roll);
        if (idx == -1) { cout << "Student not found!\n"; return; }
        Student &s = students[idx];
        cout << "Roll No: " << s.rollNo << "\n"
             << "Name: " << s.name << "\n"
             << "Class: " << s.className << "\n"
             << "Book ID Issued: " << (s.issuedBookId == -1 ? string("None") : to_string(s.issuedBookId))
             << "\n";
    }

    void modifyStudent() {
        int roll = readInt("Enter Roll No to modify: ");
        int idx = findStudentIndex(roll);
        if (idx == -1) { cout << "Student not found!\n"; return; }
        students[idx].name = readString("Enter new Name: ");
        students[idx].className = readString("Enter new Class: ");
        cout << "Record updated successfully!\n";
    }

    void deleteStudent() {
        int roll = readInt("Enter Roll No to delete: ");
        int idx = findStudentIndex(roll);
        if (idx == -1) { cout << "Student not found!\n"; return; }
        if (students[idx].issuedBookId != -1) {
            cout << "Cannot delete: student still has a book issued. Deposit it first.\n";
            return;
        }
        students[idx].valid = false;
        cout << "Student record deleted successfully!\n";
    }

    /* ---------------- BOOK OPERATIONS ---------------- */
    void createBook() {
        int id = readInt("Enter Book ID: ");
        if (findBookIndex(id) != -1) {
            cout << "A book with this ID already exists!\n";
            return;
        }
        string title = readString("Enter Title: ");
        string author = readString("Enter Author: ");
        int total = readInt("Enter Total Copies: ");
        if (total < 0) total = 0;
        books.emplace_back(id, title, author, total);
        cout << "Book record created successfully!\n";
    }

    void displayAllBooks() {
        bool found = false;
        cout << "\n" << left
             << setw(10) << "Book ID" << setw(30) << "Title"
             << setw(20) << "Author" << setw(10) << "Total"
             << setw(10) << "Available" << "\n";
        for (auto &b : books) {
            if (b.valid) {
                found = true;
                cout << left << setw(10) << b.bookId << setw(30) << b.title
                     << setw(20) << b.author << setw(10) << b.totalCopies
                     << setw(10) << b.availableCopies << "\n";
            }
        }
        if (!found) cout << "No book records found.\n";
    }

    void displaySpecificBook() {
        int id = readInt("Enter Book ID to search: ");
        int idx = findBookIndex(id);
        if (idx == -1) { cout << "Book not found!\n"; return; }
        Book &b = books[idx];
        cout << "Book ID: " << b.bookId << "\n"
             << "Title: " << b.title << "\n"
             << "Author: " << b.author << "\n"
             << "Total: " << b.totalCopies << "\n"
             << "Available: " << b.availableCopies << "\n";
    }

    void modifyBook() {
        int id = readInt("Enter Book ID to modify: ");
        int idx = findBookIndex(id);
        if (idx == -1) { cout << "Book not found!\n"; return; }
        books[idx].title = readString("Enter new Title: ");
        books[idx].author = readString("Enter new Author: ");
        int newTotal = readInt("Enter new Total Copies: ");
        int issuedCount = books[idx].totalCopies - books[idx].availableCopies;
        if (newTotal < issuedCount) {
            cout << "Cannot set total below number currently issued (" << issuedCount << ")!\n";
            return;
        }
        books[idx].totalCopies = newTotal;
        books[idx].availableCopies = newTotal - issuedCount;
        cout << "Book updated successfully!\n";
    }

    void deleteBook() {
        int id = readInt("Enter Book ID to delete: ");
        int idx = findBookIndex(id);
        if (idx == -1) { cout << "Book not found!\n"; return; }
        if (books[idx].availableCopies != books[idx].totalCopies) {
            cout << "Cannot delete: some copies are still issued.\n";
            return;
        }
        books[idx].valid = false;
        cout << "Book record deleted successfully!\n";
    }

    /* ---------------- ISSUE / DEPOSIT ---------------- */
    void issueBook() {
        int roll = readInt("Enter Student Roll No: ");
        int sIdx = findStudentIndex(roll);
        if (sIdx == -1) { cout << "Student not found!\n"; return; }

        if (students[sIdx].issuedBookId != -1) {
            cout << "This student already has a book issued (ID: "
                 << students[sIdx].issuedBookId << "). Deposit it first.\n";
            return;
        }

        int bookId = readInt("Enter Book ID: ");
        int bIdx = findBookIndex(bookId);
        if (bIdx == -1) { cout << "Book not found!\n"; return; }

        if (books[bIdx].availableCopies <= 0) {
            cout << "No copies available currently!\n";
            return;
        }

        books[bIdx].availableCopies--;
        students[sIdx].issuedBookId = books[bIdx].bookId;
        cout << "Book issued successfully!\n";
    }

    void depositBook() {
        int roll = readInt("Enter Student Roll No: ");
        int sIdx = findStudentIndex(roll);
        if (sIdx == -1) { cout << "Student not found!\n"; return; }

        if (students[sIdx].issuedBookId == -1) {
            cout << "No book issued to this student.\n";
            return;
        }

        int bIdx = findBookIndex(students[sIdx].issuedBookId);
        if (bIdx != -1) {
            books[bIdx].availableCopies++;
        }
        students[sIdx].issuedBookId = -1;
        cout << "Book deposited successfully!\n";
    }
};

/* ============================================================
   MENUS
   ============================================================ */
void adminMenu(Library &lib) {
    int choice;
    do {
        cout << "\n===== ADMINISTRATOR MENU =====\n";
        cout << "1. Create Student Record\n";
        cout << "2. Display All Student Records\n";
        cout << "3. Display Specific Student Record\n";
        cout << "4. Modify Student Record\n";
        cout << "5. Delete Student Record\n";
        cout << "6. Create Book\n";
        cout << "7. Display All Books\n";
        cout << "8. Display Specific Book\n";
        cout << "9. Modify Book\n";
        cout << "10. Delete Book\n";
        cout << "0. Back to Main Menu\n";
        choice = readInt("Enter your choice: ");

        switch (choice) {
            case 1: lib.createStudent(); break;
            case 2: lib.displayAllStudents(); break;
            case 3: lib.displaySpecificStudent(); break;
            case 4: lib.modifyStudent(); break;
            case 5: lib.deleteStudent(); break;
            case 6: lib.createBook(); break;
            case 7: lib.displayAllBooks(); break;
            case 8: lib.displaySpecificBook(); break;
            case 9: lib.modifyBook(); break;
            case 10: lib.deleteBook(); break;
            case 0: cout << "Returning to Main Menu...\n"; break;
            default: cout << "Invalid choice!\n";
        }
    } while (choice != 0);
}

void mainMenu(Library &lib) {
    int choice;
    do {
        cout << "\n===== SCHOOL LIBRARY MANAGEMENT SYSTEM =====\n";
        cout << "1. Administrator\n";
        cout << "2. Issuing a Book\n";
        cout << "3. Depositing a Book\n";
        cout << "0. Exit\n";
        choice = readInt("Enter your choice: ");

        switch (choice) {
            case 1: adminMenu(lib); break;
            case 2: lib.issueBook(); break;
            case 3: lib.depositBook(); break;
            case 0: cout << "Exiting the system. Goodbye!\n"; break;
            default: cout << "Invalid choice! Try again.\n";
        }
    } while (choice != 0);
}

int main() {
    Library lib;
    mainMenu(lib);
    return 0;
}