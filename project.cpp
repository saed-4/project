#include <iostream>
#include <string>
using namespace std;
/*book class 
with private :forces all access to go through methods you control,
 so you can enforce rules and catch bad data at one single point, 
 instead of it being possible to corrupt the object from anywhere in your code.
 data are private but methods are public*/

class Book{
private:
  int id;
  string title;
  string author;
  int quantity;
  bool isIssued;

public:
Book(int id_no=0,string booktitle="",string bookauthor="",int qty=0){ //constructor that assign values
     id = id_no;
    title = booktitle;
    author = bookauthor;
    quantity = qty;
    isIssued = false;//new books added are not automatically issued
}
int getId() const { return id; } //function that ONLY gets data doesn't change it --const keyword
string getTitle() const { return title; }
string getAuthor() const { return author; }
int getQuantity() const { return quantity; }
bool getIsIssued() const { return isIssued; }

void setQuantity(int qty) { quantity = qty; }
void setIsIssued(bool status) { isIssued = status; }
//const for reading
void display() const { // void = no return we use cout to print
    cout << "ID: " << id 
         << " | Title: " << title
         << " | Author: " << author
         << " | Qty: " << quantity
         << " | Issued: " << (isIssued ? "Yes" : "No") << endl;//ternary operator  condition ? valueIfTrue : valueIfFalse 
}                                                                //(isIssued ? "Yes" : "No") was used to output a readeable true or false instead of 1 and 0

};
// ============================
// Member Class
// Represents a library member who can borrow books
// ============================
class Member {
private:
    int id;
    string name;
    int borrowedBooks[10]; // holds up to 10 borrowed book IDs
    int borrowedCount;

public:
    Member(int memberId, string memberName) {
        id = memberId;
        name = memberName;
        borrowedCount = 0;
    }

    int getId() const { return id; }
    string getName() const { return name; }

    void borrowBook(int bookId) {
        if (borrowedCount < 10) {
            borrowedBooks[borrowedCount] = bookId;
            borrowedCount = borrowedCount + 1;
        } else {
            cout<< "This member has borrowed the maximum number of books." << endl;
        }
    }
// return function
    void returnBook(int bookId) {
        for (int i = 0; i < borrowedCount; i++) {
            if (borrowedBooks[i] == bookId) {
                for (int j = i; j < borrowedCount - 1; j++) {
                    borrowedBooks[j] = borrowedBooks[j + 1];
                }
                borrowedCount = borrowedCount - 1;
                return;
            }
        }
    }

    void display() const {
        cout << "Member ID: " << id << " | Name: " << name << " | Books borrowed: " << borrowedCount << endl;
    }
};


//library class
// Manages a collection of Book objects
class Library{
private:
    Book books[100]; // array used for a fixed storage
    int bookCount; //to count the book used
// ADD THESE TWO LINES:
    Member members[50]; // A row of 50 empty member slots
    int memberCount;    // Tracks how many members are registered

public:
  
Library(){
  bookCount = 0; //starting state  0 books
  memberCount = 0;
}

  /* adding book function
books[100] = 100 empty boxes, numbered 0–99, each able to hold one Book
bookCount = a number that tracks two things at once: how many books exist and the index of the next empty box
Check there's room: if (bookCount < 100) — make sure we haven't filled all 100 boxes.
Place the book: books[bookCount] = newBook; — drop the new book into the next empty box (whichever index bookCount currently is).
Update the count: bookCount = bookCount + 1; — since one more box is now filled, and the next empty box is one further along.
If full: print a message instead of trying to add — since there's no room left.
*/

void addBook(Book newBook){
    if(bookCount < 100){
        books[bookCount] = newBook;
        bookCount +=1;//************ */
    }else{
     cout << "Library is full. Cannot add more books." << endl;
    }
}

//display function
void displayAllBooks() const{
    if(bookCount == 0){
        cout<< "No books in the library." << endl;
     }
      else{
        for(int i=0; i<bookCount ;i++){
            books[i].display();//"take the book sitting in box number i, and run its own display() method to print its details."
        }
    }
}
// searching book
void searchBook(int searchId) const {
    for (int i = 0; i < bookCount; i++) {
        if (books[i].getId() == searchId) {
            cout << "Book found!" << endl;
            books[i].display();
            return;
        }
    }
    cout << "Book with ID " << searchId << " not found." << endl;
}

// removing a bookk function
void removeBook(int removeId) {
    for (int i = 0; i < bookCount; i++) {
        if (books[i].getId() == removeId) {
            for (int j = i; j < bookCount - 1; j++) {
                books[j] = books[j + 1];
            }
            bookCount = bookCount - 1;
            cout << "Book removed successfully." << endl;
            return;
        }
    }
    cout << "Book with ID " << removeId << " not found." << endl;
}

// issuing function (changing book status)
void issueBook(int issueId, int memberId) {
    int bookIndex = -1;
    int memberIndex = -1;

    // 1. Find the book slot
    for (int i = 0; i < bookCount; i++) {
        if (books[i].getId() == issueId) {
            bookIndex = i;
            break;
        }
    }

    // 2. Find the member slot
    for (int i = 0; i < memberCount; i++) {
        if (members[i].getId() == memberId) {
            memberIndex = i;
            break;
        }
    }

    // 3. Verify both exist
    if (bookIndex == -1) { cout << "Book not found." << endl; return; }
    if (memberIndex == -1) { cout << "Member not found." << endl; return; }

    // 4. Check if the book is already out
    if (books[bookIndex].getIsIssued() == true) {
        cout << "Book is already issued." << endl;
        return;
    }

    // 5. Link them together
    books[bookIndex].setIsIssued(true);              // Mark book as out
    members[memberIndex].borrowBook(issueId);        // Give book ID to member
    cout << "Book issued successfully to " << members[memberIndex].getName() << endl;
}
    }
    cout << "Book with ID " << issueId << " not found." << endl;
}

// return function (opposite of issuing function)
void returnBook(int returnId) {
    for (int i = 0; i < bookCount; i++) {
        if (books[i].getId() == returnId) {
            if (books[i].getIsIssued() == false) {
                cout << "This book was not issued." << endl;
            } else {
                books[i].setIsIssued(false);
                cout << "Book returned successfully." << endl;
            }
            return;
        }
    }
    cout << "Book with ID " << returnId << " not found." << endl;
}
void addMember(Member newMember) {
    if (memberCount < 50) {
        members[memberCount] = newMember;
        memberCount += 1;
        cout << "Member registered successfully." << endl;
    } else {
        cout << "Library is full. Cannot add more members." << endl;
    }
}
};
int main() {
    Library lib;
    int choice;

    while (true) {
        cout << endl;
        cout << "===== Library Menu =====" << endl;
        cout << "1. Add Book" << endl;
        cout << "2. Display All Books" << endl;
        cout << "3. Search Book" << endl;
        cout << "4. Remove Book" << endl;
        cout << "5. Issue Book" << endl;
        cout << "6. Return Book" << endl;
        cout << "0. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                int id, qty;
                string title, author;
                cout << "Enter book ID: ";
                cin >> id;
                cout << "Enter title: ";
                cin.ignore();
                getline(cin, title);
                cout << "Enter author: ";
                getline(cin, author);
                cout << "Enter quantity: ";
                cin >> qty;

                Book newBook(id, title, author, qty);
                lib.addBook(newBook);
                cout << "Book added successfully." << endl;
                break;
            }
            case 2: {
                lib.displayAllBooks();
                break;
            }
            case 3: {
                int id;
                cout << "Enter book ID to search: ";
                cin >> id;
                lib.searchBook(id);
                break;
            }
            case 4: {
                int id;
                cout << "Enter book ID to remove: ";
                cin >> id;
                lib.removeBook(id);
                break;
            }
            case 5: {
                int id;
                cout << "Enter book ID to issue: ";
                cin >> id;
                lib.issueBook(id);
                break;
            }
            case 6: {
                int id;
                cout << "Enter book ID to return: ";
                cin >> id;
                lib.returnBook(id);
                break;
            }
            case 0: {
                cout << "Exiting program." << endl;
                break;
            }
            default: {
                cout << "Invalid choice. Try again." << endl;
                break;
            }
        }

        if (choice == 0) {
            break;
        }
    }

    return 0;
}