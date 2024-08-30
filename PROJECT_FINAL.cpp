#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
using namespace std;
class book 
{
public:
    string book_name;
    string serial_no;
    string author_name;
    string publisher;
    string edition;
    int quantity;
    vector<string> issued_to_students;
    // Default constructor with loadFromFile flag
    book(bool loadFromFile = false) {
        if (!loadFromFile) {
            cout << "Enter the book name: ";
            getline(cin, book_name);
            cout << "Enter the serial number: ";
            getline(cin, serial_no);
            cout << "Enter the Author name: ";
            getline(cin, author_name);
            cout << "Enter Publisher name: ";
            getline(cin, publisher);
            cout << "Enter the edition: ";
            getline(cin, edition);
            cout << "Enter the quantity of books: ";
            cin >> quantity;
        }
    }
    // Add a member function to initialize from a string
    void initializeFromData(const string& data) {
        string blank;
        istringstream iss(data);
        iss.ignore(); // Ignore the type field
        getline(iss,blank,'|');
        getline(iss, book_name, '|');
        getline(iss, serial_no, '|');
        getline(iss, author_name, '|');
        getline(iss, publisher, '|');
        getline(iss, edition, '|');
        iss >> quantity;
    }

void initializeIssuedToStudents(const string& data) {
        string studentID;
        istringstream iss(data);
        iss.ignore(); // Ignore the type field
         getline(iss, studentID);
        // cout<<"Student yaha par:"<<studentID<<endl;
            issued_to_students.push_back(studentID);
        }
};

class student {
public:
    string student_name;
    string uid;
    string branch;
    long long int mob_no;
    vector<string> issued_books;

    // Default constructor with loadFromFile flag
    student(bool loadFromFile = false) {
        if (!loadFromFile) {
            cout << "Enter student name: ";
            //cin.ignore(); // Clear newline character
            getline(cin, student_name);
            cout << "Enter student ID: ";
            getline(cin, uid);
            cout << "Enter student branch: ";
            getline(cin, branch);
            // Clear the newline character before reading the mobile number
            cout << "Enter student mobile number: ";
            cin >> mob_no;
        }
    }
    void initializeIssuedBooks(const string& data) {
        string bookSerial;
        istringstream iss(data);
        iss.ignore();
        getline(iss,bookSerial);
        //cout<<"BOOK YAHA PAR:"<<bookSerial<<endl;
            issued_books.push_back(bookSerial);
    }

    // Add a member function to initialize from a string
    void initializeFromData(const string& data) {
        istringstream iss(data);
        string blank;
        iss.ignore(); // Ignore the type field
        getline(iss,blank,'|');
        getline(iss, student_name, '|');
        getline(iss, uid, '|');
        getline(iss, branch, '|');
        iss >> mob_no;
    }
};

class Library {
private:
    vector<book> books;
    vector<student> students;
    public:
    // Constructor to load data from a file when the program starts
    Library() {
        loadDataFromFile();
    }
    void addBook() 
    {
        book newBook;
        //Check if the serial number already exists
    for (int i = 0; i < books.size(); i++) {
    if (books[i].serial_no == newBook.serial_no) {
        cout << "Book with serial number " << newBook.serial_no << " already exists." << endl;
        return; // Exit the function if the serial number exists
    }
    }
    books.push_back(newBook);
    cout << "Book added successfully!" << endl;
}
    void upgradeBookQuantity(const string& serialNumber, int additionalQuantity) 
    {
        for (int i = 0; i < books.size(); i++) {
    if (books[i].serial_no == serialNumber) {
        // Found the book with the given serial number
        cout << "Before Upgrade - " << books[i].book_name << ": " << books[i].serial_no << " (" << books[i].edition << " edition)" << endl;
        cout << "Current Quantity: " << books[i].quantity << endl;
        // Increase the quantity of the book
        books[i].quantity += additionalQuantity;
        cout << "After Upgrade - " << books[i].book_name << ": " << books[i].serial_no << " (" << books[i].edition << " edition)" << endl;
        cout << "Updated Quantity: " << books[i].quantity << endl;
        return; // Exit the function after updating
    }
}
        // If the function reaches here, the book with the given serial number was not found
        cout << "Book with serial number " << serialNumber << " not found." << endl;
    }
  void searchBook(const string& identifier) 
{
    bool found = false;
    for (int i = 0; i < books.size(); i++)
    {
        if (books[i].book_name == identifier || books[i].serial_no == identifier) 
        {
            // Match found, display book details
            cout << "Book Name: " << books[i].book_name << endl;
            cout << "Serial Number: " << books[i].serial_no << endl;
            cout << "Author: " << books[i].author_name << endl;
            cout << "Publisher: " << books[i].publisher << endl;
            cout << "Edition: " << books[i].edition << endl;
            cout << "Quantity Available: " << books[i].quantity << endl;

            // Print the list of students who have issued this book
            if (!books[i].issued_to_students.empty()) 
            {
                cout << "Students who have issued this book:" << endl;
                for (const string& studentID : books[i].issued_to_students) 
                {
                    // Find the corresponding student and print their name
                    for (int j = 0; j < students.size(); j++)
                    {
                        if (students[j].uid == studentID) {
                            cout << "Student Name: " << students[j].student_name << endl;
                            break;
                        }
                    }
                }
            } 
            else 
            {
                cout << "No students have issued this book." << endl;
            }
            found = true;
        }
    }
    if (!found)
    {
        cout << "Book not found." << endl;
    }
}
void searchStudent(const string& studentID) 
{
    bool found = false;
    for (const student& student : students) 
    {
        if (student.uid == studentID) 
        {
            // Match found, display student details
            cout << "Student Name: " << student.student_name << endl;
            cout << "Student ID: " << student.uid << endl;
            cout << "Branch: " << student.branch << endl;
            cout << "Mobile Number: " << student.mob_no << endl;

            // Print the list of books issued by this student
            if (!student.issued_books.empty()) 
            {
                cout << "Books issued by this student:" << endl;
                for (const string& bookSerial : student.issued_books) 
                {
                    // Find the corresponding book and print its details
                    for (const book& book : books) 
                    {
                        if (book.serial_no == bookSerial) 
                        {
                            cout << "Book Name: " << book.book_name << endl;
                            cout << "Serial Number: " << book.serial_no << endl;
                            cout << "Author: " << book.author_name << endl;
                            cout << "Publisher: " << book.publisher << endl;
                            cout << "Edition: " << book.edition << endl;
                            cout << "-----------------------------" << endl;
                        }
                    }
                }
            } 
            else 
            {
                cout << "No books issued by this student." << endl;
            }
            found = true;
        }
    }
    if (!found) 
    {
        cout << "Student with ID " << studentID << " not found." << endl;
    }
}
    void showAllBooks()
    {
        if (books.empty()) {
            cout << "No books in the library." << endl;
        } else {
            cout << "List of all books in the library:" << endl;
            for (const book& book : books) {
                cout << "Book Name: " << book.book_name << endl;
                cout << "Serial Number: " << book.serial_no << endl;
                cout << "Author: " << book.author_name << endl;
                cout << "Publisher: " << book.publisher << endl;
                cout << "Edition: " << book.edition << endl;
                cout <<"Quantity: " << book.quantity<<endl;
                cout << "-----------------------------" << endl;
            }
        }
    }
    void issueBook(const string& studentID, const string& serialNumber) {
    // Find the student by their unique identifier (student ID)
    student* foundStudent = nullptr;
    for (student& s : students) 
    {
        if (s.uid == studentID) {
            foundStudent = &s;
            break;
        }
    }

    // If the student is found, proceed to find and issue the book
    if (foundStudent != nullptr) {
        // Find the book by its serial number
        for (book& b : books) {
            if (b.serial_no == serialNumber) {
                // Check if the book is available
                if (b.quantity > 0) {
                    // Book is available, issue it to the student
                    cout << "Book " << b.book_name << " issued to student " << foundStudent->student_name << endl;
                    b.quantity--; // Decrease the book's quantity
                    // Update vectors to keep track of issued books and students who issued the book
                    foundStudent->issued_books.push_back(serialNumber);
                    b.issued_to_students.push_back(studentID);
                    return;
                } else {
                    cout << "Book " << b.book_name << " is not available." << endl;
                    return;
                }
            }
        }
        // If the book is not found
        cout << "Book with serial number " << serialNumber << " not found." << endl;
    } else {
        // If the student is not found
        cout << "Student with ID " << studentID << " not found." << endl;
    }
}

    void returnBook(const string& studentID, const string& serialNumber) 
    {
        bool studentFound = false;
        bool bookFound = false;

        // Find the student by their unique identifier (student ID)
        for (student& student : students) {
            if (student.uid == studentID) {
                studentFound = true;
                // Find the book by its serial number
                for (book& book : books) {
                    if (book.serial_no == serialNumber) {
                        bookFound = true;
                        // Book was returned; update availability
                        cout << "Book " << book.book_name << " returned by student " << student.student_name << endl;
                        book.quantity++; // Increase the book's quantity
                        // Remove the book from the student's issued_books vector
                        for (auto it = student.issued_books.begin(); it != student.issued_books.end(); ++it) {
                            if (*it == serialNumber) {
                                student.issued_books.erase(it);
                                break;
                            }
                        }
                        // Remove the student from the book's issued_to_students vector
                        for (auto it = book.issued_to_students.begin(); it != book.issued_to_students.end(); ++it) {
                            if (*it == studentID) {
                                book.issued_to_students.erase(it);
                                break;
                            }
                        }
                        return;
                    }
                }
                if (!bookFound) {
                    cout << "Book with serial number " << serialNumber << " not found." << endl;
                }
            }
        }
        if (!studentFound) {
            cout << "Student with ID " << studentID << " not found." << endl;
        }
    }
    void registerStudent() 
    {
        student newStudent;
        // Check if the student UID already exists
        for (const student& existingStudent : students) 
        {
            if (existingStudent.uid == newStudent.uid) 
            {
                cout << "Student with ID " << newStudent.uid << " already exists." << endl;
                return; // Exit the function and return to the main menu
            }
        }
        students.push_back(newStudent);
        cout << "Student registered successfully!" << endl;
    }
    void unregisterStudent(const string& studentID)
    {
        bool found = false;
        // Find the student by their unique identifier (student ID)
        for (auto it = students.begin(); it != students.end(); ++it) {
            if (it->uid == studentID) {
                students.erase(it); // Remove the student from the list
                found = true;
                cout << "Student with ID " << studentID << " unregistered successfully!" << endl;
                break;
            }
        }
        if (!found) {
            cout << "Student with ID " << studentID << " not found." << endl;
        }
    }
    void showAllStudents() 
    {
        if (students.empty()) 
        {
            cout << "No students are registered." << endl;
        }
         else 
         {
            cout << "List of all registered students:" << endl;
            for (const student& student : students) 
            {
                cout << "Student Name: " << student.student_name << endl;
                cout << "Student ID: " << student.uid << endl;
                cout << "Branch: " << student.branch << endl;
                cout << "Mobile Number: " << student.mob_no << endl;
                cout << "-----------------------------" << endl;
            }
        }
    }
    void loadDataFromFile() {
    ifstream inputFile("library_data.txt");
    if (!inputFile.is_open()) {
        cout << "Failed to open the file for loading data." << endl;
        return;
    }
    books.clear();
    students.clear();
    string line;
    while (getline(inputFile, line)) {
        istringstream iss(line);
        string type;
        iss >> type;
        if (type[0] == 'B') 
        {
            book b(true); // Pass true to skip user prompts
            b.initializeFromData(line); // Initialize book data from the line
            books.push_back(b);
        } 
        else if (type[0] == 'S') {
            student s(true); // Pass true to skip user prompts
            s.initializeFromData(line); // Initialize student data from the line
            students.push_back(s);
        } 
        else if (type[0] == 'I') {
            string studentID, bookSerial;
            string blank;
            istringstream iss(line);
            iss.ignore();
            getline(iss,blank,'|');
            getline(iss, studentID, '|'); // Read until the next '|'
            getline(iss, bookSerial, '|'); // Read until the next '|'
            //cout<<"Student Id:"<<studentID<<endl;
            //cout<<"BOOK SERIAL:"<<bookSerial<<endl;
            // Find the student and book by their IDs and link them
            for (student& s : students) {
                if (s.uid == studentID) {
                    // Initialize issued_books vector
                    //cout<<"ANDAR DEKH LO Student Id:"<<studentID<<endl;
                    //cout<<"ANDAR DEKH LO BOOK SERIAL:"<<bookSerial<<endl;
                    //cout<<"YAHA TOH THK HAI "<<endl;
                    s.initializeIssuedBooks(" "+bookSerial);
                    break;
                }
            }
            for (book& b : books) {
                if (b.serial_no == bookSerial) {
                    //cout<<"YAHA par bhi  THK HAI "<<endl;
                    //cout<<"ANDAR DEKH LO Student Id:"<<studentID<<endl;
                    //cout<<"ANDAR DEKH LO BOOK SERIAL:"<<bookSerial<<endl;
                    // Initialize issued_to_students vector
                    b.initializeIssuedToStudents(" "+studentID);
                    break;
                }
            }
        } 
    }
    inputFile.close();
    cout << "Data loaded from file." << endl;
}
void deleteBook(const string& serialNumber) {
    // Check if the book is issued by any student
    for (const student& s : students) {
        if (find(s.issued_books.begin(), s.issued_books.end(), serialNumber) != s.issued_books.end()) {
            cout << "Book with serial number " << serialNumber << " is issued by a student and cannot be deleted." << endl;
            return;
        }
    }

    // If the book is not issued, delete it
    for (auto it = books.begin(); it != books.end(); ++it) {
        if (it->serial_no == serialNumber) {
            books.erase(it);
            cout << "Book with serial number " << serialNumber << " has been deleted." << endl;
            return;
        }
    }

    // If the book is not found
    cout << "Book with serial number " << serialNumber << " not found." << endl;
}


void saveDataToFile() {
    ofstream outputFile("library_data.txt");
    if (!outputFile.is_open()) {
        cout << "Failed to open the file for saving data." << endl;
        return;
    }
    // Save books to the file
    for (const book& b : books) {
        outputFile << "Book|" << b.book_name << "|" << b.serial_no << "|" << b.author_name << "|" << b.publisher << "|" << b.edition << "|" << b.quantity << endl;
    }
    // Save students to the file
    for (const student& s : students) {
        outputFile << "Student|" << s.student_name << "|" << s.uid << "|" << s.branch << "|" << s.mob_no << endl;
        // Save the books issued by this student
        for (const string& bookSerial : s.issued_books) {
            outputFile << "IssuedByStudent|" << s.uid << "|" << bookSerial << endl;
        }
    }
    outputFile.close();
    cout << "Data saved to file." << endl;
}

};
int main()
{
    cout << "WELCOME TO THE LIBRARY MANAGEMENT SYSTEM" << endl;
    cout << "=============================================" << endl;
    cout << "CREATOR:" << endl;
    cout << "RAJ MOHNANI: 22BCS15430" << endl;
    cout << "==============================================" << endl;
    Library library; // Create a Library object to manage the system
    while (true)
    {
        cout << "MENU" << endl;
        cout << "1. ADD NEW BOOK" << endl;
        cout << "2. REGISTER STUDENT" << endl;
        cout << "3. ISSUE A BOOK" << endl;
        cout << "4. RETURN A BOOK" << endl;
        cout << "5. SEARCH A BOOK" << endl;
        cout << "6. UPGRADE THE QUANTITY OF BOOK" << endl;
        cout << "7. SHOW ALL BOOKS" << endl;
        cout << "8. UNREGISTER STUDENT" << endl;
        cout << "9. SEARCH A STUDENT" << endl;
        cout << "10. SHOW ALL REGISTERED STUDENTS" << endl;
        cout << "11. REMOVE A BOOK "<<endl;
        cout << "12. EXIT APPLICATION" << endl;
        cout << "==============================================" << endl;
        int choice;
        cout << "ENTER YOUR CHOICE: ";
        cin >> choice;
        cin.ignore();
        switch (choice)
        {
            case 1:
                library.addBook();
                break;
            case 2:
                library.registerStudent();
                break;
            case 3:
                {
                    string studentID, serialNumber;
                    cout << "Enter student ID: ";
                    getline(cin, studentID);
                    cout << "Enter book serial number: ";
                    getline(cin, serialNumber);
                    library.issueBook(studentID, serialNumber);
                }
                break;
            case 4:
                {
                    string studentID, serialNumber;
                    cout << "Enter student ID: ";
                    getline(cin, studentID);
                    cout << "Enter book serial number: ";
                    getline(cin, serialNumber);
                    library.returnBook(studentID, serialNumber);
                }
                break;
            case 5:
                {
                    string identifier;
                    cout << "Enter the book name or serial number to search: ";
                    getline(cin, identifier);
                    library.searchBook(identifier);
                }
                break;
            case 6:
                {
                    string serialNumber;
                    int additionalQuantity;
                    cout << "Enter the serial number of the book: ";
                    getline(cin, serialNumber);
                    cout << "Enter the additional quantity: ";
                    cin >> additionalQuantity;
                    library.upgradeBookQuantity(serialNumber, additionalQuantity);
                }
                break;
            case 7:
                library.showAllBooks();
                break;
            case 8:
                {
                    string studentID;
                    cout << "Enter the student ID to unregister: ";
                    getline(cin, studentID);
                    library.unregisterStudent(studentID);
                }
                break;
            case 9: 
                {
                    string studentID;
                    cout << "Enter the student ID to search: ";
                    getline(cin, studentID);
                    library.searchStudent(studentID);
                }
                break;
            case 10:
                library.showAllStudents();
                break;
            case 11: // New case for deleting a book
                {
                    string serialNumber;
                    cout << "Enter the serial number of the book to delete: ";
                    getline(cin, serialNumber);
                    library.deleteBook(serialNumber);
                }
                break;
            case 12:
                library.saveDataToFile();
                cout << "EXIT SUCCESSFUL" << endl;
                return 0;
            default:
                cout << "Invalid choice. Please enter a valid option." << endl;
        }
    }
    return 0;
}
