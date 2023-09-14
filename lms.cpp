#include <iostream>
#include <string>
#include <map>
#include <vector>

using namespace std;

// Define the structure for a book
struct Book {
    string title;
    int copies;

    Book(string t, int c) : title(t), copies(c) {}
};

// Define the structure for a node in the Binary Search Tree
struct TreeNode {
    Book data;
    TreeNode* left;
    TreeNode* right;

    TreeNode(Book book) : data(book), left(nullptr), right(nullptr) {}
};

// Class for managing the Binary Search Tree of books
class Library {
private:
    TreeNode* root;
    map<string, int> issuedBooks; // To keep track of issued books

public:
    Library() : root(nullptr) {}

    // Function to insert a book into the BST
    TreeNode* insert(TreeNode* node, Book book) {
        if (node == nullptr) {
            return new TreeNode(book);
        }

        if (book.title < node->data.title) {
            node->left = insert(node->left, book);
        } else if (book.title > node->data.title) {
            node->right = insert(node->right, book);
        }

        return node;
    }

    void insertBook(Book book) {
        root = insert(root, book);
    }

    // Function to search for a book in the BST
    TreeNode* search(TreeNode* node, string title) {
        if (node == nullptr || node->data.title == title) {
            return node;
        }

        if (title < node->data.title) {
            return search(node->left, title);
        } else {
            return search(node->right, title);
        }
    }

    TreeNode* searchBook(string title) {
        return search(root, title);
    }

    // Function to display all books in sorted order
    void displayInOrder(TreeNode* node) {
        if (node == nullptr) {
            return;
        }

        displayInOrder(node->left);
        cout << "Title: " << node->data.title << ", Copies: " << node->data.copies << endl;
        displayInOrder(node->right);
    }

    void displayAllBooks() {
        displayInOrder(root);
    }

    // Function to issue a book
    bool issueBook(string title) {
        TreeNode* bookNode = searchBook(title);
        if (bookNode && bookNode->data.copies > 0) {
            bookNode->data.copies--;
            issuedBooks[title]++;
            return true;
        }
        return false;
    }

    // Function to return a book
    bool returnBook(string title) {
        if (issuedBooks.find(title) != issuedBooks.end() && issuedBooks[title] > 0) {
            TreeNode* bookNode = searchBook(title);
            bookNode->data.copies++;
            issuedBooks[title]--;
            return true;
        }
        return false;
    }
};

int main() {
    Library library;
    vector<string> studentIds; // List of student IDs

    int numStudents;
    cout << "Enter the number of students: ";
    cin >> numStudents;
    cin.ignore(); // Clear newline character

    for (int i = 1; i <= numStudents; i++) {
        string studentId;
        cout << "Enter student ID " << i << ": ";
        getline(cin, studentId);
        studentIds.push_back(studentId);
    }

    // Populate the library with initial books
    library.insertBook(Book("Book A", 5));
    library.insertBook(Book("Book B", 3));
    library.insertBook(Book("Book C", 7));

    int choice;
    string userId;

    do {
        cout << "Library Management System" << endl;
        cout << "1. Display all books" << endl;
        cout << "2. Search for a book" << endl;
        cout << "3. Issue a book" << endl;
        cout << "4. Return a book" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "All Books:" << endl;
                library.displayAllBooks();
                break;
            case 2:
                string searchTitle;
                cout << "Enter the title of the book you want to search for: ";
                cin.ignore();
                getline(cin, searchTitle);
                TreeNode* result = library.searchBook(searchTitle);
                if (result) {
                    cout << "Book Found - Title: " << result->data.title << ", Copies: " << result->data.copies << endl;
                } else {
                    cout << "Book not found." << endl;
                }
                break;
            case 3:
                cout << "Enter your user ID: ";
                cin >> userId;
                if (find(studentIds.begin(), studentIds.end(), userId) != studentIds.end()) {
                    string issueTitle;
                    cout << "Enter the title of the book you want to issue: ";
                    cin.ignore();
                    getline(cin, issueTitle);
                    if (library.issueBook(issueTitle)) {
                        cout << "Book issued successfully." << endl;
                    } else {
                        cout << "Book not available for issuing." << endl;
                    }
                } else {
                    cout << "User not authorized to issue books." << endl;
                }
                break;
            case 4:
                cout << "Enter your user ID: ";
                cin >> userId;
                if (find(studentIds.begin(), studentIds.end(), userId) != studentIds.end()) {
                    string returnTitle;
                    cout << "Enter the title of the book you want to return: ";
                    cin.ignore();
                    getline(cin, returnTitle);
                    if (library.returnBook(returnTitle)) {
                        cout << "Book returned successfully." << endl;
                    } else {
                        cout << "You do not have this book to return." << endl;
                    }
                } else {
                    cout << "User not authorized to return books." << endl;
                }
                break;
            case 5:
                cout << "Exiting the program." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 5);

    return 0;
}
