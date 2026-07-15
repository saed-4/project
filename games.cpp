#include <iostream> //so the computer understands how to print things to your screen (cout) and read keyboard keys (cin).
#include <string>//because plain C++ doesn't inherently know what words or sentences are; it only knows single letters (char)

using namespace std;//This tells the compiler that whenever we type cout, cin, string, or endl, we mean the standard versions

// ============================
// Book Class
// ============================
class Book {
private:  //variables can only be modified by code written inside this specific class
    int id;
    string title;
    string author;
    int quantity;
    int issuedCopies;

public://can be globally used
    Book() {id = 0; title = ""; author = ""; quantity = 0; issuedCopies = 0;} //This constructor forces every blank box of the declared array to start safely at zero.
    Book(int id_no, string booktitle, string bookauthor, int qty) { //OVERLOAD CONSTRUCTOR
        id = id_no;
        title = booktitle;
        author = bookauthor;
        quantity = qty;
        issuedCopies = 0;
    }
//these are functions that help return the private variables eg id
    int getId() const { return id; } //we used const keyword to only look at the data without altering it 
    string getTitle() const { return title; }
    string getAuthor() const { return author; }
    int getQuantity() const { return quantity; }
    int getIssuedCopies() const { return issuedCopies; }
    int getAvailableCopies() const { 
        return quantity - issuedCopies; 
    }
    void increaseIssued() { issuedCopies = issuedCopies + 1; }
    void decreaseIssued() { issuedCopies = issuedCopies - 1; }
    
    
    void display() const { //Prints out all the book's information.
        cout << "ID: " << id 
             << " | Title: " << title
             << " | Author: " << author
             << " | Available: " << getAvailableCopies() << "/" << quantity << endl;
    }
};


// *************************
// Member Class
// *************************
class Member {
private:
    int id;
    string name;
    int borrowedBooks[10]; //array for = member can only have 10 book
    int borrowedCount;//

public:
    Member() { id = 0; name = ""; borrowedCount = 0;}//constructor

    Member(int memberId, string memberName) {
        id = memberId;
        name = memberName;
        borrowedCount = 0;
    }

    int getId() const { return id; }
    string getName() const { return name; }
    int getBorrowedCount() const { return borrowedCount; }

    void borrowBook(int bookId) {
        if (borrowedCount < 10) {
            borrowedBooks[borrowedCount] = bookId;
            borrowedCount  += 1;//to scale up the counter
        }
    }
/*Search: The outer for loop checks each item in the borrowedBooks list to find a match for the bookId.
Find: The if statement checks when borrowedBooks[i] == bookId.Shift:
The inner for loop copies the next book into the current spot. It repeats this to shift all the books that came after the removed book one space to the left.Update:
 The code decreases borrowedCount by 1 to show there is one less book in the list.
Exit: The return statement stops the function once the book is found and removed.*/
    void returnBook(int bookId) {
        for (int i = 0; i < borrowedCount; i++) {//The code uses a for loop to look at the books one by one. It compares each book's ID to the one being returned.
            if (borrowedBooks[i] == bookId) {//Once it finds the book at position i, a second loop starts. It copies the book from position j + 1 into position j. This shifts all the remaining books one slot to the left.
                for (int j = i; j < borrowedCount - 1; j++) {
                    borrowedBooks[j] = borrowedBooks[j + 1];
                }
                borrowedCount = borrowedCount - 1;
                return;// for early exit
            }
        }
    }

    void display() const {
        cout << "Member ID: " << id << " | Name: " << name << " | Books borrowed: " << borrowedCount << "/10" << endl;
    }
};



// ****************************
//        Library Class
// ******************************
class Library {
private:
    Book books[100];
    int bookCount;
    Member members[50];
    int memberCount;

public:
    Library() {
        bookCount = 0;
        memberCount = 0;
    }

    void addBook(Book newBook) {
        if (bookCount >= 100) {
            cout << "Error: Library is full. Cannot add more books." << endl;
            return;
        }
        for (int i = 0; i < bookCount; i++) {
            if (books[i].getId() == newBook.getId()) {
                cout << "Error: Book ID " << newBook.getId() << " already exists!" << endl;
                return;
            }
        }
        books[bookCount] = newBook;
        bookCount += 1;
        cout << "Book added successfully." << endl;
    }

    void addMember(Member newMember) {
        if (memberCount >= 50) {
            cout << "Error: Registry is full. Cannot add more members." << endl;
            return;
        }
        for (int i = 0; i < memberCount; i++) {
            if (members[i].getId() == newMember.getId()) {
                cout << "Error: Member ID " << newMember.getId() << " already exists!" << endl;
                return;
            }
        }
        members[memberCount] = newMember;
        memberCount += 1;
        cout << "Member registered successfully." << endl;
    }

    void displayAllBooks() const {
        if (bookCount == 0) {
            cout << "No books in the library." << endl;
            return;
        }
        for (int i = 0; i < bookCount; i++) {
            books[i].display();
        }
    }

    void displayAllMembers() const {
        if (memberCount == 0) {
            cout << "No registered members in the system." << endl;
            return;
        }
        for (int i = 0; i < memberCount; i++) {
            members[i].display();
        }
    }

    void searchBookById(int searchId) const {
        for (int i = 0; i < bookCount; i++) {
            if (books[i].getId() == searchId) {
                cout << "Book found!" << endl;
                books[i].display();
                return;
            }
        }
        cout << "Book with ID " << searchId << " not found." << endl;
    }

    void searchBookByTitle(string searchTitle) const {
        bool found = false;
        for (int i = 0; i < bookCount; i++) {
            if (books[i].getTitle() == searchTitle) {
                if (!found) cout << "Matching Book(s) found:" << endl;
                books[i].display();
                found = true;
            }
        }
        if (!found) {
            cout << "No book found with title: \"" << searchTitle << "\"" << endl;
        }
    }

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

    void issueBook(int issueId, int memberId) {
        int bookIndex = -1;
        int memberIndex = -1;

        for (int i = 0; i < bookCount; i++) {
            if (books[i].getId() == issueId) { bookIndex = i; break; }
        }
        for (int i = 0; i < memberCount; i++) {
            if (members[i].getId() == memberId) { memberIndex = i; break; }
        }

        if (bookIndex == -1) { cout << "Error: Book ID not found." << endl; return; }
        if (memberIndex == -1) { cout << "Error: Member ID not found." << endl; return; }

        if (books[bookIndex].getAvailableCopies() <= 0) {
            cout << "Error: All copies of this book are currently checked out!" << endl;
            return;
        }
        if (members[memberIndex].getBorrowedCount() >= 10) {
            cout << "Error: Member has reached their limit of 10 books." << endl;
            return;
        }

        books[bookIndex].increaseIssued();
        members[memberIndex].borrowBook(issueId);
        cout << "Success: Book copy issued to " << members[memberIndex].getName() << "." << endl;
    }

    void returnBook(int returnId, int memberId) {
        int bookIndex = -1;
        int memberIndex = -1;

        for (int i = 0; i < bookCount; i++) {
            if (books[i].getId() == returnId) { bookIndex = i; break; }
        }
        for (int i = 0; i < memberCount; i++) {
            if (members[i].getId() == memberId) { memberIndex = i; break; }
        }

        if (bookIndex == -1) { cout << "Error: Book ID not found." << endl; return; }
        if (memberIndex == -1) { cout << "Error: Member ID not found." << endl; return; }

        if (books[bookIndex].getIssuedCopies() <= 0) {
            cout << "Error: No copies of this book are marked as issued." << endl;
            return;
        }

        books[bookIndex].decreaseIssued();
        members[memberIndex].returnBook(returnId);
        cout << "Success: Book copy returned from " << members[memberIndex].getName() << "." << endl;
    }
};

// ============================
// Input Protection Helper Function
// ============================
int getSafeIntegerInput() {
    int input;
    while (true) {
        cin >> input;
        if (cin.fail()) {
            cout << "Invalid input! Please enter numbers only: ";
            cin.clear();
            cin.ignore(1000, '\n');
        } else {
            return input;
        }
    }
}

// ============================
// Main Execution
// ============================
int main() {
    Library lib;
    int choice;

    while (true) {
        cout << "\n===== Library Menu =====" << endl;
        cout << "1. Add Book" << endl;
        cout << "2. Display All Books" << endl;
        cout << "3. Register Member" << endl;    
        cout << "4. Display All Members" << endl; 
        cout << "5. Issue Book" << endl;
        cout << "6. Return Book" << endl;
        cout << "7. Search Book" << endl;
        cout << "8. Remove Book" << endl;
        cout << "0. Exit" << endl;
        cout << "Enter your choice: ";
        
        choice = getSafeIntegerInput();

        if (choice == 0) {
            cout << "Exiting program." << endl;
            break;
        }

        switch (choice) {
            case 1: {
                int id, qty;
                string title, author;
                cout << "Enter book ID: "; id = getSafeIntegerInput();
                cout << "Enter title: "; cin.ignore(); getline(cin, title);
                cout << "Enter author: "; getline(cin, author);
                cout << "Enter quantity: "; qty = getSafeIntegerInput();

                lib.addBook(Book(id, title, author, qty));
                break;
            }
            case 2:
                lib.displayAllBooks();
                break;

            case 3: {
                int mid;
                string mname;
                cout << "Enter member ID: "; mid = getSafeIntegerInput();
                cout << "Enter member name: "; cin.ignore(); getline(cin, mname);

                lib.addMember(Member(mid, mname));
                break;
            }
            case 4:
                lib.displayAllMembers();
                break;

            case 5: {
                int bid, mid;
                cout << "Enter book ID to issue: "; bid = getSafeIntegerInput();
                cout << "Enter member ID: "; mid = getSafeIntegerInput();
                lib.issueBook(bid, mid);
                break;
            }
            case 6: {
                int bid, mid;
                cout << "Enter book ID to return: "; bid = getSafeIntegerInput();
                cout << "Enter member ID: "; mid = getSafeIntegerInput();
                lib.returnBook(bid, mid);
                break;
            }
            case 7: {
                int searchChoice;
                cout << "1. Search by ID\n2. Search by Title\nEnter sub-choice: ";
                searchChoice = getSafeIntegerInput();

                if (searchChoice == 1) {
                    cout << "Enter book ID to search: ";
                    int id = getSafeIntegerInput();
                    lib.searchBookById(id);
                } else if (searchChoice == 2) {
                    string title;
                    cout << "Enter book title to search: ";
                    cin.ignore();
                    getline(cin, title);
                    lib.searchBookByTitle(title);
                } else {
                    cout << "Invalid search option." << endl;
                }
                break;
            }
            case 8: {
                int id;
                cout << "Enter book ID to remove: "; id = getSafeIntegerInput();
                lib.removeBook(id);
                break;
            }
            default:
                cout << "Invalid choice. Try again." << endl;
                break;
        }
    }

    return 0;
}