#include <iostream>
#include <vector>
#include <string>
#include <ctime>

using namespace std;

class Book {
public:
    string title;
    string author;
    int id;
    bool available;
    time_t dueDate;
    double fineRate;

    Book(string title, string author, int id, double fineRate) : title(title), author(author), id(id), available(true), fineRate(fineRate) {}

    void display() {
        cout << "Title: " << title << endl;
        cout << "Author: " << author << endl;
        cout << "ID: " << id << endl;
        cout << "Status: " << (available ? "Available" : "Checked out") << endl;
        if (!available) {
            cout << "Due Date: " << ctime(&dueDate);
        }
    }

    double calculateFine() {
        time_t now;
        time(&now);
        double fine = 0.0;
        if (!available && dueDate < now) {
            double secondsLate = difftime(now, dueDate);
            fine = fineRate * (secondsLate / 3600); // Fine per hour
        }
        return fine;
    }
};

class Library {
private:
    vector<Book> books;

public:
    void addBook(string title, string author, int id, double fineRate) {
        books.push_back(Book(title, author, id, fineRate));
    }

    void displayBooks() {
        for (const Book& book : books) {
            book.display();
            cout << "----------------------" << endl;
        }
    }

    void checkOutBook(int id, int daysToReturn) {
        for (Book& book : books) {
            if (book.id == id && book.available) {
                book.available = false;
                time_t now;
                time(&now);
                book.dueDate = now + daysToReturn * 24 * 60 * 60; // Calculate due date in seconds
                cout << "Book with ID " << id << " has been checked out. Due in " << daysToReturn << " days." << endl;
                return;
            }
        }
        cout << "Book not found or is already checked out." << endl;
    }

    void returnBook(int id) {
        for (Book& book : books) {
            if (book.id == id && !book.available) {
                book.available = true;
                double fine = book.calculateFine();
                cout << "Book with ID " << id << " has been returned." << endl;
                if (fine > 0.0) {
                    cout << "Fine: $" << fine << endl;
                }
                return;
            }
        }
        cout << "Book not found or is already available." << endl;
    }
};

int main() {
    Library library;
    int choice;

    do {
        cout << "Library Management System" << endl;
        cout << "1. Add Book" << endl;
        cout << "2. Display Books" << endl;
        cout << "3. Check Out Book" << endl;
        cout << "4. Return Book" << endl;
        cout << "5. Quit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                string title, author;
                int id;
                double fineRate;
                cout << "Enter book title: ";
                cin.ignore();
                getline(cin, title);
                cout << "Enter author: ";
                getline(cin, author);
                cout << "Enter book ID: ";
                cin >> id;
                cout << "Enter fine rate per hour: $";
                cin >> fineRate;
                library.addBook(title, author, id, fineRate);
                break;
            }
            case 2:
                library.displayBooks();
                break;
            case 3: {
                int id, daysToReturn;
                cout << "Enter book ID to check out: ";
                cin >> id;
                cout << "Enter the number of days to return: ";
                cin >> daysToReturn;
                library.checkOutBook(id, daysToReturn);
                break;
            }
            case 4: {
                int id;
                cout << "Enter book ID to return: ";
                cin >> id;
                library.returnBook(id);
                break;
            }
        }
    } while (choice != 5);

    return 0;
}
