#include <iostream>
#include <vector>
using namespace std;

// ---------- DATA STRUCTURES ----------
struct Student {
    int rollNo;
    string name;
    string className;
    int issuedBookId;   // -1 means this student has no book right now
};

struct Book {
    int bookId;
    string title;
    string author;
    int totalCopies;
    int availableCopies;
};

vector<Student> students;
vector<Book> books;

// ---------- HELPER: FIND A STUDENT BY ROLL NO ----------
int findStudent(int roll) {
    for (size_t i = 0; i < students.size(); i++) {
        if (students[i].rollNo == roll)
            return i;          // found it, return its position
    }
    return -1;                 // not found
}

// ---------- HELPER: FIND A BOOK BY ID ----------
int findBook(int id) {
    for (size_t i = 0; i < books.size(); i++) {
        if (books[i].bookId == id)
            return i;
    }
    return -1;
}

// ---------- STUDENT FUNCTIONS ----------
void createStudent() {
    Student s;
    cout << "Enter Roll No: ";
    cin >> s.rollNo;
    cout << "Enter Name: ";
    cin >> s.name;
    cout << "Enter Class: ";
    cin >> s.className;
    s.issuedBookId = -1;        // no book issued yet

    students.push_back(s);
    cout << "Student added successfully!\n";
}

void displayAllStudents() {
    cout << "\nRoll No | Name | Class | Book Issued\n";
    for (size_t i = 0; i < students.size(); i++) {
        cout << students[i].rollNo << " | "
             << students[i].name << " | "
             << students[i].className << " | ";
        if (students[i].issuedBookId == -1)
            cout << "None\n";
        else
            cout << students[i].issuedBookId << "\n";
    }
}

void displaySpecificStudent() {
    int roll;
    cout << "Enter Roll No: ";
    cin >> roll;
    int i = findStudent(roll);
    if (i == -1) {
        cout << "Student not found.\n";
        return;
    }
    cout << "Name: " << students[i].name << "\n";
    cout << "Class: " << students[i].className << "\n";
    if (students[i].issuedBookId == -1)
        cout << "Book Issued: None\n";
    else
        cout << "Book Issued: " << students[i].issuedBookId << "\n";
}

void modifyStudent() {
    int roll;
    cout << "Enter Roll No to modify: ";
    cin >> roll;
    int i = findStudent(roll);
    if (i == -1) {
        cout << "Student not found.\n";
        return;
    }
    cout << "Enter new Name: ";
    cin >> students[i].name;
    cout << "Enter new Class: ";
    cin >> students[i].className;
    cout << "Updated successfully!\n";
}

void deleteStudent() {
    int roll;
    cout << "Enter Roll No to delete: ";
    cin >> roll;
    int i = findStudent(roll);
    if (i == -1) {
        cout << "Student not found.\n";
        return;
    }
    students.erase(students.begin() + i);
    cout << "Student deleted successfully!\n";
}

// ---------- BOOK FUNCTIONS ----------
void createBook() {
    Book b;
    cout << "Enter Book ID: ";
    cin >> b.bookId;
    cout << "Enter Title: ";
    cin >> b.title;
    cout << "Enter Author: ";
    cin >> b.author;
    cout << "Enter Total Copies: ";
    cin >> b.totalCopies;
    b.availableCopies = b.totalCopies;

    books.push_back(b);
    cout << "Book added successfully!\n";
}

void displayAllBooks() {
    cout << "\nBook ID | Title | Author | Total | Available\n";
    for (size_t i = 0; i < books.size(); i++) {
        cout << books[i].bookId << " | "
             << books[i].title << " | "
             << books[i].author << " | "
             << books[i].totalCopies << " | "
             << books[i].availableCopies << "\n";
    }
}

void displaySpecificBook() {
    int id;
    cout << "Enter Book ID: ";
    cin >> id;
    int i = findBook(id);
    if (i == -1) {
        cout << "Book not found.\n";
        return;
    }
    cout << "Title: " << books[i].title << "\n";
    cout << "Author: " << books[i].author << "\n";
    cout << "Available Copies: " << books[i].availableCopies << "\n";
}

void modifyBook() {
    int id;
    cout << "Enter Book ID to modify: ";
    cin >> id;
    int i = findBook(id);
    if (i == -1) {
        cout << "Book not found.\n";
        return;
    }
    cout << "Enter new Title: ";
    cin >> books[i].title;
    cout << "Enter new Author: ";
    cin >> books[i].author;
    cout << "Updated successfully!\n";
}

void deleteBook() {
    int id;
    cout << "Enter Book ID to delete: ";
    cin >> id;
    int i = findBook(id);
    if (i == -1) {
        cout << "Book not found.\n";
        return;
    }
    books.erase(books.begin() + i);
    cout << "Book deleted successfully!\n";
}

// ---------- ISSUE / DEPOSIT ----------
void issueBook() {
    int roll, id;
    cout << "Enter Student Roll No: ";
    cin >> roll;
    int s = findStudent(roll);
    if (s == -1) {
        cout << "Student not found.\n";
        return;
    }
    if (students[s].issuedBookId != -1) {
        cout << "This student already has a book. Deposit it first.\n";
        return;
    }

    cout << "Enter Book ID: ";
    cin >> id;
    int b = findBook(id);
    if (b == -1) {
        cout << "Book not found.\n";
        return;
    }
    if (books[b].availableCopies <= 0) {
        cout << "No copies available.\n";
        return;
    }

    books[b].availableCopies--;          // one less copy on the shelf
    students[s].issuedBookId = books[b].bookId;   // record who has it
    cout << "Book issued successfully!\n";
}

void depositBook() {
    int roll;
    cout << "Enter Student Roll No: ";
    cin >> roll;
    int s = findStudent(roll);
    if (s == -1) {
        cout << "Student not found.\n";
        return;
    }
    if (students[s].issuedBookId == -1) {
        cout << "This student has no book to deposit.\n";
        return;
    }

    int b = findBook(students[s].issuedBookId);
    if (b != -1) {
        books[b].availableCopies++;      // one more copy back on shelf
    }
    students[s].issuedBookId = -1;       // student no longer holds a book
    cout << "Book deposited successfully!\n";
}

// ---------- MENUS ----------
void adminMenu() {
    int choice;
    do {
        cout << "\n---- ADMIN MENU ----\n";
        cout << "1. Create Student\n";
        cout << "2. Display All Students\n";
        cout << "3. Display Specific Student\n";
        cout << "4. Modify Student\n";
        cout << "5. Delete Student\n";
        cout << "6. Create Book\n";
        cout << "7. Display All Books\n";
        cout << "8. Display Specific Book\n";
        cout << "9. Modify Book\n";
        cout << "10. Delete Book\n";
        cout << "0. Back\n";
        cout << "Choice: ";
        cin >> choice;

        switch (choice) {
            case 1: createStudent(); break;
            case 2: displayAllStudents(); break;
            case 3: displaySpecificStudent(); break;
            case 4: modifyStudent(); break;
            case 5: deleteStudent(); break;
            case 6: createBook(); break;
            case 7: displayAllBooks(); break;
            case 8: displaySpecificBook(); break;
            case 9: modifyBook(); break;
            case 10: deleteBook(); break;
            case 0: cout << "Returning to Main Menu...\n"; break;
            default: cout << "Invalid choice.\n";
        }
    } while (choice != 0);
}

int main() {
    int choice;
    do {
        cout << "\n==== SCHOOL LIBRARY SYSTEM ====\n";
        cout << "1. Administrator\n";
        cout << "2. Issue a Book\n";
        cout << "3. Deposit a Book\n";
        cout << "0. Exit\n";
        cout << "Choice: ";
        cin >> choice;

        switch (choice) {
            case 1: adminMenu(); break;
            case 2: issueBook(); break;
            case 3: depositBook(); break;
            case 0: cout << "Goodbye!\n"; break;
            default: cout << "Invalid choice.\n";
        }
    } while (choice != 0);

    return 0;
}