#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
#include <string>
// for searching
#include <vector>
#include <algorithm>
#include <sstream>
#include <iterator>
#include <conio.h> // for _getch() in pressAnyKeyToContinue()
using namespace std;

// Class Forward Declarations
class Book;
class Borrower;

// Class Declarations ================================================================
class Book
{
public:
    // Display functions
    void displayBookInfo()
    {
        const int C1_WIDTH = 13, C2_WIDTH = 81, C3_WIDTH = 12; // widths of columns

        cout << setw(C1_WIDTH) << getID() << setw(C2_WIDTH) << getTitle()
             << setw(C3_WIDTH) << (getAvailability() ? "Yes" : "No") << endl;
        cout << setw(C1_WIDTH) << " " << setw(C2_WIDTH) << getAuthor()
             << setw(C3_WIDTH) << " " << endl;
        cout << setw(C1_WIDTH) << " " << setw(C2_WIDTH) << getPublisher()
             << setw(C3_WIDTH) << " " << endl;
        cout << setw(C1_WIDTH) << " " << setw(C2_WIDTH) << getYear()
             << setw(C3_WIDTH) << " " << endl;
        cout << setw(C1_WIDTH) << "____________"
             << setw(C2_WIDTH) << "________________________________________________________________________________"
             << setw(C3_WIDTH) << "___________" << endl;
    }

    void displayBookInfoStats(int i)
    {
        const int C1_WIDTH = 5, C2_WIDTH = 13, C3_WIDTH = 81, C4_WIDTH = 12; // widths of columns

        cout << setw(C1_WIDTH) << i << setw(C2_WIDTH) << getID()
             << setw(C3_WIDTH) << getTitle() << setw(C4_WIDTH) << getBorrowCount() << endl;
        cout << setw(C1_WIDTH) << " " << setw(C2_WIDTH) << " "
             << setw(C3_WIDTH) << getAuthor() << setw(C4_WIDTH) << " " << endl;
        cout << setw(C1_WIDTH) << " " << setw(C2_WIDTH) << " "
             << setw(C3_WIDTH) << getPublisher() << setw(C4_WIDTH) << " " << endl;
        cout << setw(C1_WIDTH) << " " << setw(C2_WIDTH) << " "
             << setw(C3_WIDTH) << getYear() << setw(C4_WIDTH) << " " << endl;
        cout << setw(C1_WIDTH) << "____" << setw(C2_WIDTH) << "____________"
             << setw(C3_WIDTH) << "________________________________________________________________________________"
             << setw(C4_WIDTH) << "___________" << endl;
    }

    // Set functions
    // Set a new book
    void setBookInfo(char i[], char t[], char a[], char p[], int y)
    {
        strcpy(id, i);
        strcpy(title, t);
        strcpy(author, a);
        strcpy(publisher, p);
        year = y;
        isAvailable = true;
        borrowCount = 0;
    }

    // Set Availability of Book
    void setAvailability(bool a)
    {
        isAvailable = a;
    }

    // add Borrower Count of book
    void incrementBorrowCount()
    {
        borrowCount++;
    }

    // Get functions
    const char *getID() const
    {
        return id;
    }

    // Get Book Title
    const char *getTitle() const
    {
        return title;
    }

    // Get Book Author
    const char *getAuthor() const
    {
        return author;
    }

    // Get Publisher
    const char *getPublisher() const
    {
        return publisher;
    }

    // Get Book Year
    int getYear() const
    {
        return year;
    }

    // Get Book Availability
    bool getAvailability() const
    {
        return isAvailable;
    }

    // Get Borrow Count of the Book
    int getBorrowCount() const
    {
        return borrowCount;
    }

private:
    char id[11], title[101], author[51], publisher[51];
    int year, borrowCount;
    bool isAvailable;
    Borrower *borrowedBy;
};

class Borrower
{
public:
    // Set functions
    void setBorrowerInfo(char l[], char f[], int n)
    {
        strcpy(id, getNewID());
        strcpy(lastName, l);
        strcpy(firstName, f);
        contactNo = n;
        numBorrowedBooks = 0;
        totalBookCount = 0;
    }

    void incrementTotalBookCount()
    {
        totalBookCount++;
    }

    // Display Borrower Info in Table Format
    void displayBorrowerInfo()
    {
        const int C1_WIDTH = 13, C2_WIDTH = 48, C3_WIDTH = 20, C4_WIDTH = 25; // widths of columns

        cout << setw(C1_WIDTH) << getID() << setw(C2_WIDTH) << getFullName()
             << setw(C3_WIDTH) << getContactNo() << setw(C4_WIDTH) << getNumBorrowedBooks() << endl;
        cout << setw(C1_WIDTH) << "____________" << setw(C2_WIDTH) << "____________________"
             << setw(C3_WIDTH) << "______________" << setw(C4_WIDTH) << "________________________" << endl;
    }

    // Display Borrower Stats in Table Format with index
    void displayBorrowerInfoStats(int i)
    {
        const int C1_WIDTH = 5, C2_WIDTH = 13, C3_WIDTH = 48, C4_WIDTH = 15, C5_WIDTH = 25; // widths of columns

        cout << setw(C1_WIDTH) << i << setw(C2_WIDTH) << getID() << setw(C3_WIDTH) << getFullName()
             << setw(C4_WIDTH) << getContactNo() << setw(C5_WIDTH) << getTotalBookCount() << endl;
        cout << setw(C1_WIDTH) << "____" << setw(C2_WIDTH) << "____________" << setw(C3_WIDTH) << "____________________"
             << setw(C4_WIDTH) << "______________" << setw(C5_WIDTH) << "________________________" << endl;
    }

    // Add Book to Borrower's List of Borrowed Books
    void addBorrowedBook(Book *book)
    {
        // Check if the borrower has reached the maximum book count
        if (numBorrowedBooks < 5)
        {
            // Add the book to the borrower's list of borrowed books
            borrowedBooks[numBorrowedBooks] = book;
            numBorrowedBooks++;
        }
    }

    // Remove Book to Borrower's List of Borrowed Books
    void removeBorrowedBook(Book *book)
    {
        // Check if the borrower has borrowed at least one book
        if (numBorrowedBooks > 0)
        {
            // Search for the book in the borrower's list of borrowed books, and store the index of the found book
            int index = findBorrowedBook(book);

            // If the book is found, remove it from the array
            for (int i = index; i < numBorrowedBooks - 1; i++)
            {
                borrowedBooks[i] = borrowedBooks[i + 1];
            }
            borrowedBooks[numBorrowedBooks - 1] = nullptr;
            numBorrowedBooks--;
        }
    }

    // Find Book in Borrower's List of Borrowed Books
    int findBorrowedBook(Book *book)
    {
        int index = -1;

        // Search for the book in the borrower's list of borrowed books
        for (int i = 0; i < numBorrowedBooks; i++)
        {
            if (borrowedBooks[i] == book)
            {
                // Book found, store the index of the book
                index = i;
                break;
            }
        }

        return index;
    }

    // Get functions
    const char *getID() const
    {
        return id;
    }

    // Get Full Name
    const char *getFullName() const
    {
        char *fullName = new char[41];
        strcpy(fullName, lastName);
        strcat(fullName, " ");
        strcat(fullName, firstName);
        return fullName;
    }

    // Get Contact Number
    int getContactNo() const
    {
        return contactNo;
    }

    // Get Number of Borrowered Book
    int getNumBorrowedBooks() const
    {
        return numBorrowedBooks;
    }

    // Get List of Borrowed Books
    Book *const *getBorrowedBooks() const
    {
        return borrowedBooks;
    }

    // Get Total Book
    int getTotalBookCount() const
    {
        return totalBookCount;
    }

private:
    char id[9], lastName[11], firstName[31];
    int contactNo, numBorrowedBooks, totalBookCount;
    Book *borrowedBooks[6];

    static int lastBorrowerIDNum; // store the last used ID
    // get a new ID
    char *getNewID()
    {
        // generate new borrower ID
        int idNum = ++lastBorrowerIDNum; // id number set to last used id number + 1
        char *newID = new char[9];       // for storing new borrower ID
        strcpy(newID, "HKCC0000");       // copy the template (start with "HKCC") to newID
        for (int i = 7; i >= 4; i--)
        {
            newID[i] = '0' + idNum % 10;
            idNum /= 10;
        }
        return newID;
    }
};

int Borrower::lastBorrowerIDNum = 0;

// Function Prototypes ===============================================================
// >> R0 Import
void stageImport(Book[], int &, Borrower[], int &);
int importBookList(string, Book[]);
int importBorrowerList(string, Borrower[]);
void extractFields(string, char[][101]);

// >> R0 Main Menu
char stageMainMenu();

// >> R1 Manage Books
void stageManageBooks(Book[], int &); // R1 Menu
void displayBooks(Book[], int);       // R1.1
void searchBook(Book[], int);         // R1.2
void addBook(Book[], int &);          // R1.3
void removeBook(Book[], int &);       // R1.4
void displayBookHeader();             // Complimentry
void displayBookHeaderStats();        // Complimentry

// >> R2 Manage Borrowers
void stageManageBorrowers(Borrower[], int &); // R2 Menu
void displayBorrowers(Borrower[], int);       // R2.1
void searchBorrower(Borrower[], int);         // R2.2
void addBorrower(Borrower[], int &);          // R2.3
void removeBorrower(Borrower[], int &);       // R2.4
void displayBorrowerHeader();                 // Complimentry
void displayBorrowerHeaderStats();            // Complimentry

// >> R3 Borrow Book(s)
void stageBorrowBooks(Book[], int, Borrower[], int);

// >> R4 Return Book(s)
void stageReturnBooks(Book[], int, Borrower[], int);

// >> R5 Useful Feature(s)
void stageFeatures(Book[], int, Borrower[], int); // R5 Menu
void displayFeaturesDescription();                // R5 Description

void stageStatisticsBooks(Book[], int); // R5.1 Menu
void statsBooksAllDesc(Book[], int);    // R5.1.1
void statsBooksAllAsc(Book[], int);     // R5.1.2
void statsBooksTop10(Book[], int);      // R5.1.3
void statsBooksBottom10(Book[], int);   // R5.1.4

void stageStatisticsBorrowers(Borrower[], int); // R5.2 Menu
void statsBorrowersAllDesc(Borrower[], int);    // R5.2.1
void statsBorrowersAllAsc(Borrower[], int);     // R5.2.2
void statsBorrowersTop10(Borrower[], int);      // R5.2.3
void statsBorrowersBottom10(Borrower[], int);   // R5.2.4

// >> R6 Member List
void stageMemberList();

// >> R7 Exit
void stageExit();

// >> Important functions
void sortBookList(Book[], int);
void sortBorrowerList(Borrower[], int);
void quickSort(char[][105], int, int);
int partition(char[][105], int, int);

// >> Supporting functions

// >> Miscellaneous functions
void goBack(char &);               // go back to previous layer
void pressAnyKeyToContinue();      // "Press any key to continue..."
void displayInvalidInputMessage(); // "Invalid input. Please input again.\n"
char promptForYN(string);          // prompt for Y/N questions

// Global Variables
bool isFirstStart = true;       // flag, preset the user enters the main menu for the first time
bool isFirstTimeFeature = true; // flag, preset the user enters the features menu for the first time (R5)
bool isExit = false;            // flag, preset the user is not exitting the system (R7)
char option = '0';              // storing the option input from the user, preset to be main menu

// Main Function =====================================================================
int main()
{
    Book *bookList = new Book[1001];            // for storing books (max 1000), empty at first
    Borrower *borrowerList = new Borrower[501]; // for storing borrowers (max 500), empty at first
    int bookListSize = 0;                       // for storing size of book list, 0 at first
    int borrowerListSize = 0;                   // for storing size of borrower list, 0 at first

    stageImport(bookList, bookListSize, borrowerList, borrowerListSize);
    do
    {
        switch (stageMainMenu())
        {
        case '1':
            stageManageBooks(bookList, bookListSize);
            break;
        case '2':
            stageManageBorrowers(borrowerList, borrowerListSize);
            break;
        case '3':
            stageBorrowBooks(bookList, bookListSize, borrowerList, borrowerListSize);
            break;
        case '4':
            stageReturnBooks(bookList, bookListSize, borrowerList, borrowerListSize);
            break;
        case '5':
            stageFeatures(bookList, bookListSize, borrowerList, borrowerListSize);
            break;
        case '6':
            stageMemberList();
            break;
        case '7':
            stageExit();
            break;

        default:
            displayInvalidInputMessage();
            pressAnyKeyToContinue();
            break;
        }
    } while (!isExit);

    delete[] bookList;
    delete[] borrowerList;

    cout << "\nThank you for using the system. Goodbye!\n";

    return 0;
}

// Function Definitions ==============================================================
// >> Finished
// >>>> R0
void stageImport(Book bkList[], int &bkSize, Borrower brList[], int &brSize)
{
    string inPath;  // for storing the file path
    fstream inFile; // for testing if the file can be opened

    // Import book list

    // handle the input
    if (promptForYN("Import book list from file?") == 'y')
    {
        cin.ignore(255, '\n'); // ignore the \n when inputting 'y'/'Y'
        cout << "Path of book list file: ";
        getline(cin, inPath);

        inFile.open(inPath); // to check if the file can be opened

        // ask for input again if file cannot be opened
        while (!inFile.is_open())
        {
            cout << "Cannot open file \"" << inPath << "\". Please input again.\n";
            cout << "\n";
            cout << "Path of book list file: ";
            getline(cin, inPath);
            inFile.open(inPath);
        }

        inFile.close(); // close the opened file

        cout << "Importing book list . . . ";
        bkSize = importBookList(inPath, bkList); // update bookListSize
        cout << "Done\n";
    }
    else
    {
        cout << "No book list is imported\n";
    }

    cout << endl;
    sortBookList(bkList, bkSize);

    // Import borrower list

    // handle the input
    if (promptForYN("Import borrower list from file?") == 'y')
    {
        cin.ignore(255, '\n'); // ignore the \n when inputting 'y'/'Y'
        cout << "Path of borrower list file: ";
        getline(cin, inPath);

        inFile.open(inPath); // to check if the file can be opened

        // ask for input again if file cannot be opened
        while (!inFile.is_open())
        {
            cout << "Cannot open file \"" << inPath << "\". Please input again.\n";
            cout << "\n";
            cout << "Path of book list file: ";
            getline(cin, inPath);
            inFile.open(inPath);
        }

        inFile.close(); // close the opened file

        cout << "Importing borrower list . . . ";
        brSize = importBorrowerList(inPath, brList); // update borrowerListSize
        cout << "Done\n";
    }
    else
    {
        cout << "No borrower list is imported\n";
    }

    cout << endl;
    sortBorrowerList(brList, brSize);
}

// Import Borrower List

// Handle the Input
int importBookList(string filename, Book list[])
{
    fstream inFile;            // for handling file
    string line;               // for storing 1 line in a file
    char fields[10][101] = {}; // for storing extracted fields (assume max. 10 fields per line, each field has max. 100 char)
    int countRecords = 0;      // for counting the number of records in csv file

    inFile.open(filename);

    // Asking for Again Inputting If File Cannot Be Opened
    while (getline(inFile, line, '\n'))
    {                                // read line by line until end of file
        extractFields(line, fields); // call function to extract fields from the line

        // add info of new book to the list
        list[countRecords].setBookInfo(fields[0], fields[1], fields[2], fields[3], stoi(fields[4]));

        countRecords++;
    }

    inFile.close(); // Closed the Opened File

    return countRecords;
}

int importBorrowerList(string filename, Borrower list[])
{
    fstream inFile;            // for handling file
    string line;               // for storing 1 line in a file
    char fields[10][101] = {}; // for storing extracted fields (assume max. 10 fields per line, each field has max. 100 char)
    int countRecords = 0;      // for counting the number of records in csv file

    inFile.open(filename);

    while (getline(inFile, line, '\n'))
    {                                // read line by line until end of file
        extractFields(line, fields); // call function to extract fields from the line

        // add info of new borrower to the list
        // cout << id << " " << fields[0] << " " << fields[1] << " " << fields[2] << endl;
        list[countRecords].setBorrowerInfo(fields[0], fields[1], stoi(fields[2]));

        countRecords++;
    }

    inFile.close();

    return countRecords;
}

void extractFields(string line, char fields[][101])
{
    /* Algorithm explanation:
     * There are 2 types of double quotes (quotes) to be handled, opening/closing quotes and two quotes in a row.
     * As both type of quotes are pairs, number of quotes must be even.
     * When there is a quote, there must be a second one.
     * Second in-field quote must be odd. Closing quote must be even.
     * Except closing quote, every second quote (even quotes) should be kept in field.
     * The closing quote (last even quote) of field has to be deleted.
     */

    int ptr = 0;             // pointer to the current modifying character in field
    int numFields = 0;       // (current) number of field
    bool isEvenQuote = true; // if current position is after an even quote (not after an odd quote)

    for (int i = 0; line[i] != '\0'; i++)
    {
        if (line[i] == ',' && isEvenQuote)                    // when encounter comma after even quote (must be closing quote)
        {                                                     // close the field
                                                              // delete excessive quote at the end of current field
            if (ptr > 0 && fields[numFields][ptr - 1] == '"') // check if last character of current field is a quote
            {
                fields[numFields][ptr - 1] = '\0'; // delete the quote by overwrite it with a null-terminator
            }
            else
            {
                fields[numFields][ptr] = '\0'; // add a null-terminator at the end
            }
            numFields++; // add 1 number of field, point to next field position
            ptr = 0;     // reset pointer, point to first character position
        }
        else if (line[i] == '"') // when encounter any quotes (opening/closing/in-field)
        {
            isEvenQuote = !isEvenQuote; // flipping truth value of isEvenQuote
        }
        else // when encounter other normal characters in field
        {
            fields[numFields][ptr] = line[i]; // assign the character into field
            ptr++;                            // point to next character position
        }

        // add a quote after even quotes (including closing quote)
        if (line[i] == '"' && isEvenQuote)
        {
            fields[numFields][ptr] = line[i];
            ptr++;
        }
    }

    // delete excessive quote at the end of last field
    if (ptr > 0 && fields[numFields][ptr - 1] == '"') // check if last character of last field is quote
    {
        fields[numFields][ptr - 1] = '\0'; // delete the quote by overwrite it with a null-terminator
    }
    else
    {
        fields[numFields][ptr] = '\0'; // add a null-terminator at the end
    }
}

char stageMainMenu()
{
    char option;

    if (isFirstStart)
    { // grand title for first visit
        cout << "                ,gggg,                                                               \n"
                "               d8\" \"8I         ,dPYb,                                                \n"
                "               88  ,dP         IP'`Yb                                                \n"
                "            8888888P\"     gg   I8  8I                                                \n"
                "               88         \"\"   I8  8'                                                \n"
                "               88         gg   I8 dP      ,gggggg,    ,gggg,gg   ,gggggg,  gg     gg \n"
                "          ,aa,_88         88   I8dP   88ggdP\"\"\"\"8I   dP\"  \"Y8I   dP\"\"\"\"8I  I8     8I \n"
                "         dP\" \"88P         88   I8P    8I        8I  i8'    ,8I  ,8'    8I  I8,   ,8I \n"
                "         Yb,_,d88b,,_   _,88,_,d8b,  ,8I        Y8,,d8,   ,d8b,,dP     Y8,,d8b, ,d8I \n"
                "          \"Y8P\"  \"Y888888P\"\"Y88P'\"Y88P\"'        `Y8P\"Y8888P\"`Y88P      `Y8P\"\"Y88P\"888\n"
                "   __     __)                                          __                       ,d8I'\n"
                "  (, /|  /|                                        (__/  )                    ,dP'8I \n"
                "    / | / |  _  __   _   _    _ ___    _ __  _/_     /      _  _/_  _ ___    ,8\"  8I \n"
                " ) /  |/  |_(_(_/ (_(_(_(_/__(/_// (__(/_/ (_(__  ) /  (_/_/_)_(___(/_// (_  I8   8I \n"
                "(_/   '                .-/                       (_/  .-/                    `8, ,8I \n"
                "                      (_/                            (_/                      `Y8P\"  \n\n";
        isFirstStart = false;
    }
    else
    { // lite title for
        cout << " ____________________________________________ \n"
                "|                                            |\n"
                "|     _                                      |\n"
                "|     /      ,   /                           |\n"
                "|    /          /__   )__    __   )__        |\n"
                "|   /      /   /   ) /   ) /   ) /   ) /   / |\n"
                "| _/____/_/___(___/_/_____(___(_/_____(___/_ |\n"
                "|                                        /   |\n"
                "|                                    (_ /    |\n"
                "|____________________________________________|\n\n";
    }
    cout << "**********************************************\n"
            "******  __________Main Menu___________  ******\n"
            "****    [ 1 ]  Manage books               ****\n"
            "***     [ 2 ]  Manage borrowers            ***\n"
            "**      [ 3 ]  Borrow book(s)               **\n"
            "**      [ 4 ]  Return book(s)               **\n"
            "**      [ 5 ]  Feature: Statistics          **\n"
            "***     [ 6 ]  Member List                 ***\n"
            "****    [ 7 ]  Exit                       ****\n"
            "******                                  ******\n"
            "**********************************************\n"
            "Option (1 - 7): ";
    cin >> option;
    cout << endl;
    return option;
}

// >>>> R1 Manage Books
void stageManageBooks(Book bkList[], int &bkSize)
{
    char option;
    do
    {
        cout << "**********************************************\n"
                "******           Manage Books           ******\n"
                "***     [ 1 ]  Display Books               ***\n"
                "**      [ 2 ]  Search Book                  **\n"
                "**      [ 3 ]  Add Book                     **\n"
                "**      [ 4 ]  Remove Book                  **\n"
                "***     [ 5 ]  Back                        ***\n"
                "******                                  ******\n"
                "**********************************************\n"
                "Option (1 - 5): ";
        cin >> option;
        cout << endl;

        switch (option)
        {
        case '1':
            displayBooks(bkList, bkSize);
            break;
        case '2':
            searchBook(bkList, bkSize);
            break;
        case '3':
            addBook(bkList, bkSize);
            break;
        case '4':
            removeBook(bkList, bkSize);
            break;
        case '5':
            goBack(option);
            break;

        default:
            displayInvalidInputMessage();
            pressAnyKeyToContinue();
            break;
        }
    } while (option != '0');
}
// >>>>>> R1.1 Display Books
void displayBooks(Book list[], int size)
{
    const int ITEMS_PER_PAGE = 10;                // number of books to show per page
    int pageNum = 1;                              // current page number, 1 at first
    int totalPageNum = size / ITEMS_PER_PAGE + 1; // total page number, initialized

    // in case there are no books in book list
    if (size == 0)
    {
        cout << "No books to display.\n";
        pressAnyKeyToContinue();
        return;
    }

    // sort book list
    sortBookList(list, size);

    // display books
    for (int i = 0; i < size; i++)
    {
        // display header for each page
        if (i % ITEMS_PER_PAGE == 0)
        {
            displayBookHeader();
        }

        // display book details
        list[i].displayBookInfo();

        // display page number and pause
        if ((i + 1) % ITEMS_PER_PAGE == 0 || i == size - 1)
        {
            cout << "<" << pageNum << "/" << totalPageNum << ">" << endl;
            pageNum++;
            pressAnyKeyToContinue();
        }
    }
}
// >>>>>> R1.2 Search Book
void searchBook(Book list[], int size)
{
    string input;
    cin.ignore(255, '\n');
    do
    {
        cout << "Enter keywords to search: ";
        getline(cin, input);
        if (input.empty())
        {
            displayInvalidInputMessage();
            cout << endl;
        }
    } while (input.empty());

    // Convert input to lowercase
    string searchTerm = input;
    bool exactMatch = false;
    vector<string> keywords;

    // Check if the search term is an exact match
    if (searchTerm.front() == '"' && searchTerm.back() == '"')
    {
        exactMatch = true;
        searchTerm = searchTerm.substr(1, searchTerm.length() - 2);
    }
    // Split the search term into keywords
    else
    {
        istringstream iss(searchTerm);
        copy(istream_iterator<string>(iss), istream_iterator<string>(), back_inserter(keywords));
    }

    int booksFound = 0;
    vector<Book> foundBooks;

    for (int i = 0; i < size; i++)
    {
        Book &book = list[i];
        string id = book.getID();
        string title = book.getTitle();
        string author = book.getAuthor();
        string publisher = book.getPublisher();

        // Convert to lowercase
        for (int i = 0; i < id.size(); i++)
        {
            id[i] = tolower(id[i]);
        }

        for (int i = 0; i < title.size(); i++)
        {
            title[i] = tolower(title[i]);
        }

        for (int i = 0; i < author.size(); i++)
        {
            author[i] = tolower(author[i]);
        }

        for (int i = 0; i < publisher.size(); i++)
        {
            publisher[i] = tolower(publisher[i]);
        }

        bool found = false;

        // Check if the search term is an exact match
        if (exactMatch)
        {
            string phrase = searchTerm;
            for (int i = 0; i < phrase.size(); i++)
            {
                phrase[i] = tolower(phrase[i]);
            }

            if (id.find(phrase) != string::npos || title.find(phrase) != string::npos ||
                author.find(phrase) != string::npos || publisher.find(phrase) != string::npos)
            {
                found = true;
            }
        }
        // Check if any of the keywords match
        else
        {
            for (const string &keyword : keywords)
            {
                string kw = keyword;
                for (int i = 0; i < kw.size(); i++)
                {
                    kw[i] = tolower(kw[i]);
                }

                if (id.find(kw) != string::npos || title.find(kw) != string::npos ||
                    author.find(kw) != string::npos || publisher.find(kw) != string::npos)
                {
                    found = true;
                    break;
                }
            }
        }
        // Add the book to the list of found books
        if (found)
        {
            foundBooks.push_back(book);
            booksFound++;
        }
    }

    // Check booksfound or not, if not then Display no books found message
    if (booksFound == 0)
    {
        cout << "No books found. Please try again with different keywords." << endl;
        cout << endl;
    }
    // If Check booksfound > 0 , then Display the list of found books
    else
    {
        displayBookHeader();
        for (Book &book : foundBooks)
        {
            book.displayBookInfo();
        }
    }
    pressAnyKeyToContinue();
}
// >>>>>> R1.3 Add Book
void addBook(Book list[], int &size)
{
    string strBookID, strBookTitle, strBookAuthor, strBookPub;
    char bookID[11], bookTitle[101], bookAuthor[51], bookPub[51];
    int bookYear;
    bool isFullSize, isValidInput, isUniqueID, isUniqueTitleYear, isValidYear;

    cout << "<< Add Book >>\n";

    // Full Size: size reached maximum of 1000 books
    isFullSize = (size >= 1000);
    if (isFullSize)
    {
        cout << "Book list is full!\n";
        pressAnyKeyToContinue();
        return;
    }

    cout << "Please input book details:\n";

    cin.ignore(255, '\n');
    cout << "ID: ";
    getline(cin, strBookID);
    cout << "Title: ";
    getline(cin, strBookTitle);
    cout << "Author: ";
    getline(cin, strBookAuthor);
    cout << "Publisher: ";
    getline(cin, strBookPub);
    cout << "Year: ";
    cin >> bookYear;
    if (cin.fail()) // check whether last input was failed
    {
        cin.clear(); // reset the input error status to no error
    }
    cout << endl;

    // Check input sizes
    isValidInput = true;

    // Check input ID size
    if (strBookID.size() <= 0)
    {
        cout << "ID cannot be empty!\n";
        isValidInput = false;
    }
    if (strBookID.size() > 10)
    {
        cout << "ID is too long!\n";
        isValidInput = false;
    }
    if (isValidInput)
    {
        strcpy(bookID, strBookID.c_str());
    }

    // Check input title size
    if (strBookTitle.size() <= 0)
    {
        cout << "Title cannot be empty!\n";
        isValidInput = false;
    }
    if (strBookTitle.size() > 100)
    {
        cout << "Title is too long!\n";
        isValidInput = false;
    }
    if (isValidInput)
    {
        strcpy(bookTitle, strBookTitle.c_str());
    }

    // Check input author size
    if (strBookAuthor.size() <= 0)
    {
        cout << "Author cannot be empty!\n";
        isValidInput = false;
    }
    if (strBookAuthor.size() > 50)
    {
        cout << "Author is too long!\n";
        isValidInput = false;
    }
    if (isValidInput)
    {
        strcpy(bookAuthor, strBookAuthor.c_str());
    }

    // Check input publisher size
    if (strBookPub.size() <= 0)
    {
        cout << "Publisher cannot be empty!\n";
        isValidInput = false;
    }
    if (strBookPub.size() > 10)
    {
        cout << "Publisher is too long!\n";
        isValidInput = false;
    }
    if (isValidInput)
    {
        strcpy(bookPub, strBookPub.c_str());
    }

    // Unique ID: distinct from existing books
    isUniqueID = true;
    for (int i = 0; i < size; i++)
    {
        isUniqueID = (strcmp(bookID, list[i].getID()) != 0);
        if (!isUniqueID)
        {
            cout << "ID is not unique!\n";
            break;
        }
    }

    // Unique TitleYear: not the same title + year
    isUniqueTitleYear = true;
    for (int i = 0; i < size; i++)
    {
        isUniqueTitleYear = !(strcmp(bookTitle, list[i].getTitle()) == 0 && bookYear == list[i].getYear());
        if (!isUniqueTitleYear)
        {
            cout << "Book of the same version already exists!\n";
            break;
        }
    }

    // Valid Year: 1800 - 2023
    isValidYear = (bookYear >= 1800) && (bookYear <= 2023);
    if (!isValidYear)
    {
        cout << "Invalid year! (not in 1800 - 2023)\n";
    }

    // add book if all fields are valid
    if (!isFullSize && isValidInput && isUniqueID && isUniqueTitleYear && isValidYear)
    {
        list[size].setBookInfo(bookID, bookTitle, bookAuthor, bookPub, bookYear);
        size++;
        sortBookList(list, size);
        cout << "Book record added.\n";
    }
    else
    {
        cout << "Book record not added.\n";
    }

    pressAnyKeyToContinue();
}
// >>>>>> R1.4 Remove Book
void removeBook(Book list[], int &size)
{
    // Get Book ID
    char id[11];
    cout << "Enter the book ID to remove: ";
    cin.ignore(255, '\n');
    cin.getline(id, 11);
    cout << endl;
    // Check If Book ID Exists
    int index = -1;
    // Find Book
    for (int i = 0; i < size; i++)
    {
        if (strcmp(id, list[i].getID()) == 0)
        {
            index = i;
            break;
        }
    }
    // If the Book Not Found
    if (index == -1)
    {
        cout << "Book ID not found.\n";
        pressAnyKeyToContinue();
        return;
    }
    // Check Book Availability
    if (!list[index].getAvailability())
    {
        cout << "Book is currently not available and cannot be removed.\n";
        pressAnyKeyToContinue();
        return;
    }

    // Display book details
    cout << "Book Details:\n";
    displayBookHeader();
    list[index].displayBookInfo();
    cout << endl;

    // Confirm deletion
    if (promptForYN("Are you sure you want to remove this book?") == 'y')
    {
        for (int i = index; i < size - 1; i++)
        {
            list[i] = list[i + 1];
        }
        size--;
        cout << "Book removed successfully.\n";
    }
    else
    {
        cout << "Book removal cancelled.\n";
    }

    pressAnyKeyToContinue();
}
// >>>>>> R1 Complimentry Functions
void displayBookHeader()
{
    const int C1_WIDTH = 13, C2_WIDTH = 81, C3_WIDTH = 12; // width of the 3 columns

    cout << left << setw(C1_WIDTH) << "ID" << setw(C2_WIDTH) << "Book Details"
         << setw(C3_WIDTH) << "Avalability" << endl;
    cout << setw(C1_WIDTH) << "============" << setw(C2_WIDTH) << "================================================================================"
         << setw(C3_WIDTH) << "===========" << endl;
}

void displayBookHeaderStats()
{
    const int C1_WIDTH = 5, C2_WIDTH = 13, C3_WIDTH = 81, C4_WIDTH = 12; // width of the 3 columns

    cout << left << setw(C1_WIDTH) << "#" << setw(C2_WIDTH) << "ID"
         << setw(C3_WIDTH) << "Book Details" << setw(C4_WIDTH) << "Borr. freq." << endl;
    cout << setw(C1_WIDTH) << "====" << setw(C2_WIDTH) << "============"
         << setw(C3_WIDTH) << "================================================================================" << setw(C4_WIDTH) << "===========" << endl;
}

// >>>> R2 Manage Borrowers
void stageManageBorrowers(Borrower brList[], int &brSize)
{
    char option;
    do
    {
        cout << "**********************************************\n"
                "******         Manage Borrowers         ******\n"
                "***     [ 1 ]  Display Borrowers           ***\n"
                "**      [ 2 ]  Search Borrower              **\n"
                "**      [ 3 ]  Add Borrower                 **\n"
                "**      [ 4 ]  Remove Borrower              **\n"
                "***     [ 5 ]  Back                        ***\n"
                "******                                  ******\n"
                "**********************************************\n"
                "Option (1 - 5): ";
        cin >> option;
        cout << endl;

        switch (option)
        {
        case '1':
            displayBorrowers(brList, brSize);
            break;
        case '2':
            searchBorrower(brList, brSize);
            break;
        case '3':
            addBorrower(brList, brSize);
            break;
        case '4':
            removeBorrower(brList, brSize);
            break;
        case '5':
            goBack(option);
            break;

        default:
            displayInvalidInputMessage();
            pressAnyKeyToContinue();
            break;
        }
    } while (option != '0');
}
// >>>>>> R2.1 Display Borrowers
void displayBorrowers(Borrower list[], int size)
{
    const int ITEMS_PER_PAGE = 20;                // number of borrowers to show per page
    int pageNum = 1;                              // current page number, 1 at first
    int totalPageNum = size / ITEMS_PER_PAGE + 1; // total page number, initialized

    // in case there are no borrowers in borrower list
    if (size == 0)
    {
        cout << "No borrowers to display.\n";
        pressAnyKeyToContinue();
        return;
    }

    // sort borrower list
    sortBorrowerList(list, size);

    // display borrowers
    for (int i = 0; i < size; i++)
    {
        // display header for each page
        if (i % ITEMS_PER_PAGE == 0)
        {
            displayBorrowerHeader();
        }

        // display borrower details
        list[i].displayBorrowerInfo();

        // display page number and pause
        if ((i + 1) % ITEMS_PER_PAGE == 0 || i == size - 1)
        {
            cout << "<" << pageNum << "/" << totalPageNum << ">" << endl;
            pageNum++;
            pressAnyKeyToContinue();
        }
    }
}
// >>>>>> R2.2 Search Borrower
void searchBorrower(Borrower borrowerList[], int borrowerListSize)
{
    cout << "Please input ID: ";
    string input;
    cin.ignore(255, '\n');
    getline(cin, input);
    cout << endl;

    // Check if empty input
    if (input.empty())
    {
        cout << "No borrower ID entered. Returning to main menu.\n";
        pressAnyKeyToContinue();
        return;
    }

    // Check if input length = 8
    if (input.length() != 8)
    {
        cout << "Borrower ID must be 8 character.\n";
        pressAnyKeyToContinue();
        return;
    }

    // Convert input to lowercase
    string searchTerm = input;
    bool exactMatch = false;

    // Check if the search term is an exact match
    if (searchTerm.front() == '"' && searchTerm.back() == '"')
    {
        exactMatch = true;
        searchTerm = searchTerm.substr(1, searchTerm.length() - 2);
    }

    int borrowersFound = 0;
    vector<Borrower> foundBorrowers;

    // Search by ID
    for (int i = 0; i < borrowerListSize; i++)
    {
        Borrower &borrower = borrowerList[i];
        string id = borrower.getID();

        // Convert to lowercase
        for (int i = 0; i < id.size(); i++)
        {
            id[i] = tolower(id[i]);
        }

        bool found = false;

        // Check if the search term is an exact match
        if (exactMatch)
        {
            string phrase = searchTerm;
            for (int i = 0; i < phrase.size(); i++)
            {
                phrase[i] = tolower(phrase[i]);
            }

            if (id == phrase)
            {
                found = true;
            }
        }
        else
        // Check if the search term is a substring
        {
            string kw = searchTerm;
            for (int i = 0; i < kw.size(); i++)
            {
                kw[i] = tolower(kw[i]);
            }

            if (id == kw)
            {
                found = true;
            }
        }

        // Add to found borrowers
        if (found)
        {
            foundBorrowers.push_back(borrower);
            borrowersFound++;
        }
    }

    // Search by name
    if (borrowersFound == 0)
    {
        cout << "No borrowers found." << endl;
    }
    // Display found borrowers
    else
    {
        displayBorrowerHeader();
        for (Borrower &borrower : foundBorrowers)
        {
            borrower.displayBorrowerInfo();
            cout << endl;

            // Display borrowed books
            if (borrower.getNumBorrowedBooks() == 0)
            {
                cout << "No books are borrowed by " << borrower.getFullName() << ".\n";
                continue;
            }

            displayBookHeader();
            for (int i = 0; i < borrower.getNumBorrowedBooks(); i++)
            {
                borrower.getBorrowedBooks()[i]->displayBookInfo();
            }
        }
    }

    pressAnyKeyToContinue();
}
// >>>>>> R2.3 Add Borrower
void addBorrower(Borrower list[], int &size)
{
    string strBorrowerLastName, strBorrowerFirstName;
    char borrowerLastName[11], borrowerFirstName[31];
    int borrowerContactNo;
    bool isFullSize, isValidInput, isValidContactNo;

    cout << "<< Add borrower >>\n";

    // Full Size: size reached maximum of 1000 borrowers
    isFullSize = (size >= 500);
    if (isFullSize)
    {
        cout << "Borrower list is full!\n";
        pressAnyKeyToContinue();
        return;
    }
    // Check Book Details
    cout << "Please input borrower details:\n";

    cin.ignore(255, '\n');
    cout << "Last Name: ";
    getline(cin, strBorrowerLastName);
    cout << "First Name: ";
    getline(cin, strBorrowerFirstName);
    cout << "Contact Number: ";
    cin >> borrowerContactNo;
    if (cin.fail()) // check whether last input was failed
    {
        cin.clear(); // reset the input error status to no error
    }
    cout << endl;

    // Check input sizes
    isValidInput = true;

    // Check input last name size
    if (strBorrowerLastName.size() <= 0)
    {
        cout << "Last name cannot be empty!\n";
        isValidInput = false;
    }
    if (strBorrowerLastName.size() > 10)
    {
        cout << "Last name is too long!\n";
        isValidInput = false;
    }
    if (isValidInput)
    {
        strcpy(borrowerLastName, strBorrowerLastName.c_str());
    }

    // Check input first name size
    if (strBorrowerFirstName.size() <= 0)
    {
        cout << "First name cannot be empty!\n";
        isValidInput = false;
    }
    if (strBorrowerFirstName.size() > 30)
    {
        cout << "First name is too long!\n";
        isValidInput = false;
    }
    if (isValidInput)
    {
        strcpy(borrowerFirstName, strBorrowerFirstName.c_str());
    }

    // convert LAST NAME to UPPER CASE
    for (int i = 0; i < strlen(borrowerLastName); i++)
    {
        borrowerLastName[i] = toupper(borrowerLastName[i]);
    }

    // Capitalize each word of First Name
    for (int i = 0; i < strlen(borrowerFirstName); i++)
    {
        if (i == 0 || borrowerFirstName[i - 1] == ' ')
        {
            borrowerFirstName[i] = toupper(borrowerFirstName[i]);
        }
        else
        {
            borrowerFirstName[i] = tolower(borrowerFirstName[i]);
        }
    }

    // valid contact number: 8-digit and begins with 2/3/5/6/9
    switch (borrowerContactNo / 10000000)
    {
    case 2:
    case 3:
    case 5:
    case 6:
    case 9:
        isValidContactNo = true;
        break;

    default:
        isValidContactNo = false;
        cout << "Invalid contact number!\n";
        break;
    }

    // add borrower if all fields are valid
    if (!isFullSize && isValidContactNo)
    {
        list[size].setBorrowerInfo(borrowerLastName, borrowerFirstName, borrowerContactNo);
        cout << "Borrower ID of " << list[size].getFullName() << " is " << list[size].getID() << ".\n";
        size++;
        sortBorrowerList(list, size);
        cout << "Borrower record added.\n";
    }
    else
    {
        cout << "Borrower record not added.\n";
    }

    pressAnyKeyToContinue();
}
// >>>>>> R2.4 Remove Borrower
void removeBorrower(Borrower list[], int &size)
{
    char borrowerID[9];
    cout << "Enter the Borrower ID to remove: ";
    cin.ignore(255, '\n');
    cin.getline(borrowerID, 9);
    cout << endl;

    int index = -1;
    // Search For Borrower
    for (int i = 0; i < size; i++)
    {
        if (strcmp(borrowerID, list[i].getID()) == 0)
        {
            index = i;
            break;
        }
    }
    // Borrower Not Found
    if (index == -1)
    {
        cout << "Borrower ID not found.\n";
        pressAnyKeyToContinue();
        return;
    }
    // Check If Borrower Has Borrowed Books
    if (list[index].getNumBorrowedBooks() > 0)
    {
        cout << "Borrower is currently not available and cannot be removed.\n";
        return;
    }

    cout << "Borrowers Details:\n";
    displayBorrowerHeader();
    list[index].displayBorrowerInfo();
    cout << endl;

    // Confirm deletion
    if (promptForYN("Are you sure to remove this borrower?") == 'y')
    {
        for (int i = index; i < size - 1; i++)
        {
            list[i] = list[i + 1];
        }
        size--;
        cout << "Borrower removed successfully.\n";
    }
    else
    {
        cout << "Borrower removal cancelled.\n";
    }

    pressAnyKeyToContinue();
}
// >>>>>> R2 Complimentry Functions
void displayBorrowerHeader()
{
    const int C1_WIDTH = 13, C2_WIDTH = 48, C3_WIDTH = 20, C4_WIDTH = 25; // width of the 4 columns

    cout << left << setw(C1_WIDTH) << "ID" << setw(C2_WIDTH) << "Name"
         << setw(C3_WIDTH) << "Contact Number" << setw(C4_WIDTH) << "Number of books borrowed" << endl;
    cout << setw(C1_WIDTH) << "============" << setw(C2_WIDTH) << "===================="
         << setw(C3_WIDTH) << "==============" << setw(C4_WIDTH) << "========================" << endl;
}

void displayBorrowerHeaderStats()
{
    const int C1_WIDTH = 5, C2_WIDTH = 13, C3_WIDTH = 48, C4_WIDTH = 15, C5_WIDTH = 25; // width of the 4 columns

    cout << left << setw(C1_WIDTH) << "#" << setw(C2_WIDTH) << "ID" << setw(C3_WIDTH) << "Name"
         << setw(C4_WIDTH) << "Contact Number" << setw(C5_WIDTH) << "Books borrowed (All time)" << endl;
    cout << setw(C1_WIDTH) << "====" << setw(C2_WIDTH) << "============" << setw(C3_WIDTH) << "===================="
         << setw(C4_WIDTH) << "==============" << setw(C5_WIDTH) << "=========================" << endl;
}

// >>>> R3 Borrow Books
void stageBorrowBooks(Book bkList[], int bkSize, Borrower brList[], int brSize)
{
    // Prompt for borrower ID
    cout << "Enter borrower ID: ";
    cin.ignore(255, '\n');
    string borrowerID;
    getline(cin, borrowerID);

    // Check input size
    if (borrowerID.size() <= 0)
    {
        cout << "Error: Borrower ID cannot be empty." << endl;
        pressAnyKeyToContinue();
        goBack(option);
        return;
    }

    // Convert borrower ID to uppercase
    for (int i = 0; i < borrowerID.size(); i++)
    {
        borrowerID[i] = toupper(borrowerID[i]);
    }

    // Find the borrower with the specified ID
    Borrower *borrower = nullptr;
    for (int i = 0; i < brSize; i++)
    {
        if (brList[i].getID() == borrowerID)
        {
            borrower = &brList[i];
            break;
        }
    }

    // If the borrower is not found, print an error message and return
    if (borrower == nullptr)
    {
        cout << "Error: Borrower not found." << endl;
        pressAnyKeyToContinue();
        goBack(option);
        return;
    }

    // Check if the borrower has reached the maximum book count
    if (borrower->getNumBorrowedBooks() >= 5)
    {
        cout << "Error: Borrower has no remaining quota." << endl;
        pressAnyKeyToContinue();
        goBack(option);
        return;
    }

    // Borrow books one at a time
    int borrowCount = 0;
    while (true)
    {
        // Print remaining quota for the borrower
        cout << "\nRemaining quota: " << 5 - borrower->getNumBorrowedBooks() << endl;

        // Check if borrower has reached max quota
        if (borrower->getNumBorrowedBooks() >= 5)
        {
            cout << "Borrower has no more quota.\n";
            break;
        }

        // Prompt for book ID
        cout << "Enter book ID (or \"done\" to finish): ";
        string bookID;
        getline(cin, bookID);

        if (bookID == "done")
        {
            break;
        }

        // Find the book with the specified ID
        Book *book = nullptr;
        for (int i = 0; i < bkSize; i++)
        {
            if (bkList[i].getID() == bookID)
            {
                book = &bkList[i];
                break;
            }
        }

        // If the book is not found, print an error message and continue with the next book ID
        if (book == nullptr)
        {
            cout << "Error: Book with ID \"" << bookID << "\" not found." << endl;
            continue;
        }

        // If the book is already borrowed, print an error message and continue with the next book ID
        if (book->getAvailability() == false)
        {
            cout << "Error: Book with ID \"" << bookID << "\" is already borrowed." << endl;
            continue;
        }

        // Borrow the book and add it to the borrower's list of borrowed books
        book->setAvailability(false);
        book->incrementBorrowCount();
        borrower->addBorrowedBook(book);
        borrower->incrementTotalBookCount();
        borrowCount++;

        cout << "Book with ID \"" << bookID << "\" borrowed successfully." << endl;
    }

    // Print number of books borrowed
    cout << borrowCount << (borrowCount == 1 ? " book" : " books") << " borrowed." << endl;

    pressAnyKeyToContinue();
    goBack(option);
}

// >>>> R4 Return Books
void stageReturnBooks(Book bkList[], int bkSize, Borrower brList[], int brSize)
{
    // Prompt for borrower ID
    cout << "Enter borrower ID: ";
    cin.ignore(255, '\n');
    string borrowerID;
    getline(cin, borrowerID);
    cout << endl;

    // Convert the borrower ID to uppercase
    for (int i = 0; i < borrowerID.size(); i++)
    {
        borrowerID[i] = toupper(borrowerID[i]);
    }

    // Find the borrower with the specified ID
    Borrower *borrower = nullptr;
    for (int i = 0; i < brSize; i++)
    {
        if (brList[i].getID() == borrowerID)
        {
            borrower = &brList[i];
            break;
        }
    }

    // If the borrower is not found, print an error message and return
    if (borrower == nullptr)
    {
        cout << "Error: Borrower not found." << endl;
        pressAnyKeyToContinue();
        goBack(option);
        return;
    }

    // Check if the borrower has no borrowed books
    if (borrower->getNumBorrowedBooks() <= 0)
    {
        cout << "Error: Borrower has no borrowed books." << endl;
        pressAnyKeyToContinue();
        goBack(option);
        return;
    }

    // Print the borrower's borrowed books
    cout << "Borrowed books:" << endl;
    displayBookHeader();
    for (int i = 0; i < borrower->getNumBorrowedBooks(); i++)
    {
        borrower->getBorrowedBooks()[i]->displayBookInfo();
    }

    // Prompt for book IDs to return
    int returnCount = 0;
    while (true)
    {
        cout << endl;
        cout << "Enter book ID to return (or 'done' to finish): ";
        string bookID;
        getline(cin, bookID);
        cout << endl;

        // Check if the user entered "done"
        if (bookID == "done")
        {
            break;
        }

        // Find the book with the specified ID
        Book *book = nullptr;
        for (int i = 0; i < bkSize; i++)
        {
            if (bkList[i].getID() == bookID)
            {
                book = &bkList[i];
                break;
            }
        }

        // If the book is not found, print an error message and continue with the next book ID
        if (book == nullptr)
        {
            cout << "Error: Book with ID \"" << bookID << "\" not found.\n";
            continue;
        }

        // If the book is not borrowed by the borrower, print an error message and continue with the next book ID
        if (borrower->findBorrowedBook(book) == -1)
        {
            cout << "Error: Book with ID \"" << bookID << "\" not borrowed by borrower.\n";
            continue;
        }

        // Return the book and remove it from the borrower's list of borrowed books
        book->setAvailability(true);
        borrower->removeBorrowedBook(book);
        returnCount++;

        cout << "Book with ID \"" << bookID << "\" returned successfully.\n";
    }

    // Print number of books returned
    cout << returnCount << (returnCount == 1 ? " book" : " books") << " returned." << endl;

    pressAnyKeyToContinue();
    goBack(option);
}

// >>>> R5 Useful Features
void stageFeatures(Book bkList[], int bkSize, Borrower brList[], int brSize)
{
    char option;

    if (isFirstTimeFeature)
    {
        displayFeaturesDescription();
        isFirstTimeFeature = false;
    }

    do
    {
        cout << "**********************************************\n"
                "*****             Statistics             *****\n"
                "***     [ 1 ] Stats about Books            ***\n"
                "**      [ 2 ] Stats about Borrowers         **\n"
                "**      [ 3 ] Description                   **\n"
                "***     [ 4 ] Back                         ***\n"
                "*****                                    *****\n"
                "**********************************************\n"
                "Option (1 - 4): ";
        cin >> option;
        cout << endl;

        switch (option)
        {
        case '1':
            stageStatisticsBooks(bkList, bkSize);
            break;
        case '2':
            stageStatisticsBorrowers(brList, brSize);
            break;
        case '3':
            displayFeaturesDescription();
            break;
        case '4':
            goBack(option);
            break;

        default:
            displayInvalidInputMessage();
            pressAnyKeyToContinue();
            break;
        }
    } while (option != '0');
}
// >>>>>> R5.1
void stageStatisticsBooks(Book bkList[], int bkSize)
{
    char option;

    do
    {
        cout << "**********************************************\n"
                "******        Statistics - Books        ******\n"
                "***     [ 1 ]  All (Descending Freq.)      ***\n"
                "**      [ 2 ]  All (Ascending Freq.)        **\n"
                "**      [ 3 ]  10 Most borrowed books       **\n"
                "**      [ 4 ]  10 Least borrowed books      **\n"
                "***     [ 5 ]  Back                        ***\n"
                "******                                  ******\n"
                "**********************************************\n"
                "Option (1 - 5): ";
        cin >> option;
        cout << endl;

        switch (option)
        {
        case '1':
            statsBooksAllDesc(bkList, bkSize);
            break;
        case '2':
            statsBooksAllAsc(bkList, bkSize);
            break;
        case '3':
            statsBooksTop10(bkList, bkSize);
            break;
        case '4':
            statsBooksBottom10(bkList, bkSize);
            break;
        case '5':
            goBack(option);
            break;

        default:
            displayInvalidInputMessage();
            pressAnyKeyToContinue();
            break;
        }
    } while (option != '0');
}
// >>>>>> R5.2
void stageStatisticsBorrowers(Borrower brList[], int brSize)
{
    char option;

    do
    {
        cout << "**********************************************\n"
                "******      Statistics - Borrowers      ******\n"
                "***     [ 1 ]  All (Descending Freq.)      ***\n"
                "**      [ 2 ]  All (Ascending Freq.)        **\n"
                "**      [ 3 ]  Top 10 borrowers             **\n"
                "**      [ 4 ]  Bottom 10 borrowers          **\n"
                "***     [ 5 ]  Back                        ***\n"
                "******                                  ******\n"
                "**********************************************\n"
                "Option (1 - 5): ";
        cin >> option;
        cout << endl;

        switch (option)
        {
        case '1':
            statsBorrowersAllDesc(brList, brSize);
            break;
        case '2':
            statsBorrowersAllAsc(brList, brSize);
            break;
        case '3':
            statsBorrowersTop10(brList, brSize);
            break;
        case '4':
            statsBorrowersBottom10(brList, brSize);
            break;
        case '5':
            goBack(option);
            break;

        default:
            displayInvalidInputMessage();
            pressAnyKeyToContinue();
            break;
        }
    } while (option != '0');
}
// >>>> R5 Description
void displayFeaturesDescription()
{
    cout << "<< Useful Features Description >>\n\n";
    cout << ">> The statistics features offer users a comprehensive understanding of the library's lending patterns, book popularity, and the most active borrowers.\n\n";
    cout << ">> The system provides two menu options, one for book statistics and another for borrower statistics.\n\n";
    cout << ">> The following options are available:\n\n";

    cout << "1. Statistics about Books (at least borrowed once):\n";
    cout << "   1.1. Display all books sorted by descending frequency of borrowing.\n";
    cout << "   1.2. Display all books sorted by ascending frequency of borrowing.\n";
    cout << "   1.3. Display the 10 most borrowed books.\n";
    cout << "   1.4. Display the 10 least borrowed books.\n\n";

    cout << "2. Statistics about Borrowers (at least borrowed once):\n";
    cout << "   2.1. Display all borrowers sorted by descending frequency of borrowing.\n";
    cout << "   2.2. Display all borrowers sorted by ascending frequency of borrowing.\n";
    cout << "   2.3. Display the top 10 borrowers.\n";
    cout << "   2.4. Display the bottom 10 borrowers.\n\n";

    cout << ">> To access these features, navigate through the menu options provided in the program.\n\n";
    cout << ">> By analyzing this data, library administrators can make informed purchasing decisions and ensure that the library stocks books that are popular among its users.\n";
    pressAnyKeyToContinue();
}
// >>>> R5.1.1
void statsBooksAllDesc(Book list[], int size)
{
    bool hasBorrowedBooks = false;
    for (int i = 0; i < size; i++)
    {
        if (list[i].getBorrowCount() > 0)
        {
            hasBorrowedBooks = true;
            break;
        }
    }

    cout << "Books sorted by descending frequency of borrowing (at least once):\n";

    if (!hasBorrowedBooks)
    {
        cout << "No books to display.\n";
        pressAnyKeyToContinue();
        return;
    }

    // Sort books by ascending frequency of borrowing
    sort(list, list + size, [](const Book &b1, const Book &b2)
         {
            if (b1.getBorrowCount() != b2.getBorrowCount()) {
                return b1.getBorrowCount() > b2.getBorrowCount();
            }
            else {
                // If the borrower count is the same, compare titles and years
                if (strcmp(b1.getTitle(), b2.getTitle()) != 0) {
                    return strcmp(b1.getTitle(), b2.getTitle()) < 0;
                }
                else {
                    return b1.getYear() < b2.getYear();
                }
            } });

    displayBookHeaderStats();
    for (int i = 0; i < size; i++)
    {
        if (list[i].getBorrowCount() > 0)
        {
            list[i].displayBookInfoStats(i + 1);
        }
    }

    sortBookList(list, size);
    pressAnyKeyToContinue();
}
// >>>> R5.1.2
void statsBooksAllAsc(Book list[], int size)
{
    bool hasBorrowedBooks = false;
    for (int i = 0; i < size; i++)
    {
        if (list[i].getBorrowCount() > 0)
        {
            hasBorrowedBooks = true;
            break;
        }
    }

    cout << "Books sorted by ascending frequency of borrowing (at least once):\n";

    if (!hasBorrowedBooks)
    {
        cout << "No books to display.\n";
        pressAnyKeyToContinue();
        return;
    }

    // Sort books by ascending frequency of borrowing
    sort(list, list + size, [](const Book &b1, const Book &b2)
         {
            if (b1.getBorrowCount() != b2.getBorrowCount()) {
                return b1.getBorrowCount() < b2.getBorrowCount();
            }
            else {
                // If the borrower count is the same, compare titles and years
                if (strcmp(b1.getTitle(), b2.getTitle()) != 0) {
                    return strcmp(b1.getTitle(), b2.getTitle()) < 0;
                }
                else {
                    return b1.getYear() < b2.getYear();
                }
            } });

    displayBookHeaderStats();
    int rank = 0;
    for (int i = 0; i < size; i++)
    {
        if (list[i].getBorrowCount() > 0)
        {
            rank++;
            list[i].displayBookInfoStats(rank);
        }
    }

    sortBookList(list, size);
    pressAnyKeyToContinue();
}
// >>>> R5.1.3
void statsBooksTop10(Book list[], int size)
{
    bool hasBorrowedBooks = false;
    for (int i = 0; i < size; i++)
    {
        if (list[i].getBorrowCount() > 0)
        {
            hasBorrowedBooks = true;
            break;
        }
    }

    cout << "Top 10 Most Borrowed Books (at least once):\n";

    if (!hasBorrowedBooks)
    {
        cout << "No books to display.\n";
        pressAnyKeyToContinue();
        return;
    }

    // Sort books by ascending frequency of borrowing
    sort(list, list + size, [](const Book &b1, const Book &b2)
         {
            if (b1.getBorrowCount() != b2.getBorrowCount()) {
                return b1.getBorrowCount() > b2.getBorrowCount();
            }
            else {
                // If the borrower count is the same, compare titles and years
                if (strcmp(b1.getTitle(), b2.getTitle()) != 0) {
                    return strcmp(b1.getTitle(), b2.getTitle()) < 0;
                }
                else {
                    return b1.getYear() < b2.getYear();
                }
            } });

    displayBookHeaderStats();
    int displayedBooks = 0;
    int maxItemLength = 0;
    for (int i = 0; i < 10; i++)
    {
        // Display books that are borrowed at least once
        if (list[i].getBorrowCount() > 0)
        {
            displayedBooks++;
            list[i].displayBookInfoStats(displayedBooks);
            if (strlen(list[i].getTitle()) >= maxItemLength)
            {
                maxItemLength = (int)strlen(list[i].getTitle());
            }
        }

        // Check if already displayed 10 books
        if (displayedBooks >= 10)
        {
            break;
        }
    }

    if (displayedBooks < 10)
    {
        cout << "No other books to display.\n";
    }

    pressAnyKeyToContinue();

    // Display bar chart
    cout << "Bar chart:\n";
    cout << setw(maxItemLength) << "Book Title"
         << " | Frequency\n";
    for (int i = 0; i < 110; i++)
    {
        if (i == maxItemLength + 1)
        {
            cout << "|";
            continue;
        }
        cout << "=";
    }
    cout << endl;
    for (int i = 0; i < 10; i++)
    {
        // Display books that are borrowed at least once
        if (list[i].getBorrowCount() > 0)
        {
            cout << setw(maxItemLength) << list[i].getTitle() << " |";
            for (int j = 0; j < list[i].getBorrowCount(); j++)
            {
                cout << " *";
            }
            cout << "\n";
            cout << setw(maxItemLength) << " "
                 << " |\n";
        }
    }

    sortBookList(list, size);
    pressAnyKeyToContinue();
}
// >>>> R5.1.4
void statsBooksBottom10(Book list[], int size)
{
    bool hasBorrowedBooks = false;
    for (int i = 0; i < size; i++)
    {
        if (list[i].getBorrowCount() > 0)
        {
            hasBorrowedBooks = true;
            break;
        }
    }

    cout << "Top 10 Least Borrowed Books (at least once):\n\n";

    if (!hasBorrowedBooks)
    {
        cout << "No books to display.\n";
        pressAnyKeyToContinue();
        return;
    }

    // Sort books by ascending frequency of borrowing
    sort(list, list + size, [](const Book &b1, const Book &b2)
         {
            if (b1.getBorrowCount() != b2.getBorrowCount()) {
                return b1.getBorrowCount() < b2.getBorrowCount();
            }
            else {
                // If the borrower count is the same, compare titles and years
                if (strcmp(b1.getTitle(), b2.getTitle()) != 0) {
                    return strcmp(b1.getTitle(), b2.getTitle()) < 0;
                }
                else {
                    return b1.getYear() < b2.getYear();
                }
            } });

    displayBookHeaderStats();
    int displayedBooks = 0;
    int maxItemLength = 0;
    int startPos = size;
    for (int i = 0; i < size; i++)
    {
        // Display books that are borrowed at least once
        if (list[i].getBorrowCount() > 0)
        {
            displayedBooks++;
            list[i].displayBookInfoStats(displayedBooks);
            if (strlen(list[i].getTitle()) >= maxItemLength)
            {
                maxItemLength = (int)strlen(list[i].getTitle());
            }
            startPos = min(startPos, i);
        }

        // Check if already displayed 10 books
        if (displayedBooks >= 10)
        {
            break;
        }
    }

    if (displayedBooks < 10)
    {
        cout << "No other books to display.\n";
    }

    pressAnyKeyToContinue();

    // Display bar chart
    cout << "Bar chart:\n";
    cout << setw(maxItemLength) << "Book Title"
         << " | Frequency\n";
    for (int i = 0; i < 110; i++)
    {
        if (i == maxItemLength + 1)
        {
            cout << "|";
            continue;
        }
        cout << "=";
    }
    cout << endl;
    for (int i = startPos; i < size && i - startPos < 10; i++)
    {
        // Display books that are borrowed at least once
        if (list[i].getBorrowCount() > 0)
        {
            cout << setw(maxItemLength) << list[i].getTitle() << " |";
            for (int j = 0; j < list[i].getBorrowCount(); j++)
            {
                cout << " *";
            }
            cout << "\n";
            cout << setw(maxItemLength) << " "
                 << " |\n";
        }
    }

    sortBookList(list, size);
    pressAnyKeyToContinue();
}
// >>>> R5.2.1
void statsBorrowersAllDesc(Borrower list[], int size)
{
    bool hasBorrowedBorrowers = false;
    for (int i = 0; i < size; i++)
    {
        if (list[i].getTotalBookCount() > 0)
        {
            hasBorrowedBorrowers = true;
            break;
        }
    }

    cout << "Borrowers sorted by descending frequency of borrowing (at least once):\n";

    if (!hasBorrowedBorrowers)
    {
        cout << "No Borrowers to display.\n";
        pressAnyKeyToContinue();
        return;
    }

    // Sort Borrowers by ascending frequency of borrowing
    sort(list, list + size, [](const Borrower &b1, const Borrower &b2)
         {
            if (b1.getTotalBookCount() != b2.getTotalBookCount()) {
                return b1.getTotalBookCount() > b2.getTotalBookCount();
            }
            else {
                // If the borrower count is the same, compare names and IDs
                if (strcmp(b1.getFullName(), b2.getFullName()) != 0) {
                    return strcmp(b1.getFullName(), b2.getFullName()) < 0;
                }
                else {
                    return b1.getID() < b2.getID();
                }
            } });

    displayBorrowerHeaderStats();
    for (int i = 0; i < size; i++)
    {
        if (list[i].getTotalBookCount() > 0)
        {
            list[i].displayBorrowerInfoStats(i);
        }
    }

    sortBorrowerList(list, size);
    pressAnyKeyToContinue();
}
// >>>> R5.2.2
void statsBorrowersAllAsc(Borrower list[], int size)
{
    bool hasBorrowedBorrowers = false;
    for (int i = 0; i < size; i++)
    {
        if (list[i].getTotalBookCount() > 0)
        {
            hasBorrowedBorrowers = true;
            break;
        }
    }

    cout << "Borrowers sorted by ascending frequency of borrowing (at least once):\n";

    if (!hasBorrowedBorrowers)
    {
        cout << "No Borrowers to display.\n";
        pressAnyKeyToContinue();
        return;
    }

    // Sort Borrowers by ascending frequency of borrowing
    sort(list, list + size, [](const Borrower &b1, const Borrower &b2)
         {
            if (b1.getTotalBookCount() != b2.getTotalBookCount()) {
                return b1.getTotalBookCount() < b2.getTotalBookCount();
            }
            else {
                // If the borrower count is the same, compare names and IDs
                if (strcmp(b1.getFullName(), b2.getFullName()) != 0) {
                    return strcmp(b1.getFullName(), b2.getFullName()) < 0;
                }
                else {
                    return b1.getID() < b2.getID();
                }
            } });
    // Displaying the Borrower Header of Statistics
    displayBorrowerHeaderStats();
    int rank = 0;
    for (int i = 0; i < size; i++)
    {
        if (list[i].getTotalBookCount() > 0)
        {
            rank++;
            list[i].displayBorrowerInfoStats(rank);
        }
    }

    sortBorrowerList(list, size);
    pressAnyKeyToContinue();
}
// >>>> R5.2.3
void statsBorrowersTop10(Borrower list[], int size)
{
    bool hasBorrowedBorrowers = false;
    for (int i = 0; i < size; i++)
    {
        if (list[i].getTotalBookCount() > 0)
        {
            hasBorrowedBorrowers = true;
            break;
        }
    }

    cout << "Top 10 Borrowers with Most Books Borrowed All Time (at least one):\n";

    if (!hasBorrowedBorrowers)
    {
        cout << "No Borrowers to display.\n";
        pressAnyKeyToContinue();
        return;
    }

    // Sort Borrowers by ascending frequency of borrowing
    sort(list, list + size, [](const Borrower &b1, const Borrower &b2)
         {
            if (b1.getTotalBookCount() != b2.getTotalBookCount()) {
                return b1.getTotalBookCount() > b2.getTotalBookCount();
            }
            else {
                // If the borrower count is the same, compare names and IDs
                if (strcmp(b1.getFullName(), b2.getFullName()) != 0) {
                    return strcmp(b1.getFullName(), b2.getFullName()) < 0;
                }
                else {
                    return b1.getID() < b2.getID();
                }
            } });

    displayBorrowerHeaderStats();
    int displayedBorrowers = 0;
    int maxItemLength = 0;
    for (int i = 0; i < size; i++)
    {
        // Display borrowers that borrowed at least once
        if (list[i].getTotalBookCount() > 0)
        {
            displayedBorrowers++;
            list[i].displayBorrowerInfoStats(displayedBorrowers);
            if (strlen(list[i].getFullName()) >= maxItemLength)
            {
                maxItemLength = (int)strlen(list[i].getFullName());
            }
        }

        // Check if already displayed 10 borrowers
        if (displayedBorrowers >= 10)
        {
            break;
        }
    }

    if (displayedBorrowers < 10)
    {
        cout << "No other borrowers to display.\n";
    }

    pressAnyKeyToContinue();

    // Display bar chart
    cout << "Bar chart:\n";
    cout << setw(maxItemLength) << "Book Title"
         << " | Frequency\n";
    for (int i = 0; i < 110; i++)
    {
        if (i == maxItemLength + 1)
        {
            cout << "|";
            continue;
        }
        cout << "=";
    }
    cout << endl;
    for (int i = 0; i < 10; i++)
    {
        // Display books that are borrowed at least once
        if (list[i].getTotalBookCount() > 0)
        {
            cout << setw(maxItemLength) << list[i].getFullName() << " |";
            for (int j = 0; j < list[i].getTotalBookCount(); j++)
            {
                cout << " *";
            }
            cout << "\n";
            cout << setw(maxItemLength) << " "
                 << " |\n";
        }
    }

    sortBorrowerList(list, size);
    pressAnyKeyToContinue();
}
// >>>> R5.2.4
void statsBorrowersBottom10(Borrower list[], int size)
{
    bool hasBorrowedBorrowers = false;
    for (int i = 0; i < size; i++)
    {
        if (list[i].getTotalBookCount() > 0)
        {
            hasBorrowedBorrowers = true;
            break;
        }
    }

    cout << "Top 10 Borrowers with Least Books Borrowed All Time (at least one):\n";

    if (!hasBorrowedBorrowers)
    {
        cout << "No Borrowers to display.\n";
        pressAnyKeyToContinue();
        return;
    }

    // Sort Borrowers by ascending frequency of borrowing
    sort(list, list + size, [](const Borrower &b1, const Borrower &b2)
         {
            if (b1.getTotalBookCount() != b2.getTotalBookCount()) {
                return b1.getTotalBookCount() < b2.getTotalBookCount();
            }
            else {
                // If the borrower count is the same, compare names and IDs
                if (strcmp(b1.getFullName(), b2.getFullName()) != 0) {
                    return strcmp(b1.getFullName(), b2.getFullName()) < 0;
                }
                else {
                    return b1.getID() < b2.getID();
                }
            } });

    displayBorrowerHeaderStats();
    int displayedBorrowers = 0;
    int maxItemLength = 0;
    int startPos = size;
    for (int i = 0; i < size; i++)
    {
        // Display borrowers that borrowed at least once
        if (list[i].getTotalBookCount() > 0)
        {
            displayedBorrowers++;
            list[i].displayBorrowerInfoStats(displayedBorrowers);
            if (strlen(list[i].getFullName()) >= maxItemLength)
            {
                maxItemLength = (int)strlen(list[i].getFullName());
            }
            startPos = min(startPos, i);
        }

        // Check if already displayed 10 borrowers
        if (displayedBorrowers >= 10)
        {
            break;
        }
    }

    if (displayedBorrowers < 10)
    {
        cout << "No other borrowers to display.\n";
    }

    pressAnyKeyToContinue();

    // Display bar chart
    cout << "Bar chart:\n";
    cout << setw(maxItemLength) << "Book Title"
         << " | Frequency\n";
    for (int i = 0; i < 110; i++)
    {
        if (i == maxItemLength + 1)
        {
            cout << "|";
            continue;
        }
        cout << "=";
    }
    cout << endl;
    for (int i = startPos; i < size && i - startPos < 10; i++)
    {
        // Display books that are borrowed at least once
        if (list[i].getTotalBookCount() > 0)
        {
            cout << setw(maxItemLength) << list[i].getFullName() << " |";
            for (int j = 0; j < list[i].getTotalBookCount(); j++)
            {
                cout << " *";
            }
            cout << "\n";
            cout << setw(maxItemLength) << " "
                 << " |\n";
        }
    }

    sortBorrowerList(list, size);
    pressAnyKeyToContinue();
}

// >>>> R6 Member List
void stageMemberList()
{
    const int C1_WIDTH = 23, C2_WIDTH = 12, C3_WIDTH = 7; // width of the 3 columns
    cout << left << "<< Group 18 Member List >>\n";

    cout << " ____________________________________________ " << endl;
    cout << "|" << setw(C1_WIDTH) << "Name"
         << "|" << setw(C2_WIDTH) << "Student ID"
         << "|" << setw(C3_WIDTH) << "Class"
         << "|" << endl;
    cout << "|_______________________|____________|_______|" << endl;
    cout << "|" << setw(C1_WIDTH) << "HUSSAIN Abrar"
         << "|" << setw(C2_WIDTH) << "22011387A"
         << "|" << setw(C3_WIDTH) << "201A"
         << "|" << endl;
    cout << "|" << setw(C1_WIDTH) << "KO Tsz Hin"
         << "|" << setw(C2_WIDTH) << "22094895A"
         << "|" << setw(C3_WIDTH) << "201C"
         << "|" << endl;
    cout << "|" << setw(C1_WIDTH) << "LIU Shing Yui Terry"
         << "|" << setw(C2_WIDTH) << "22165850A"
         << "|" << setw(C3_WIDTH) << "201C"
         << "|" << endl;
    cout << "|" << setw(C1_WIDTH) << "SZE-TO Lam Ting"
         << "|" << setw(C2_WIDTH) << "22142338A"
         << "|" << setw(C3_WIDTH) << "201A"
         << "|" << endl;
    cout << "|" << setw(C1_WIDTH) << "WONG Ki Sum"
         << "|" << setw(C2_WIDTH) << "22127650A"
         << "|" << setw(C3_WIDTH) << "201C"
         << "|" << endl;
    cout << "|" << setw(C1_WIDTH) << "YEE Cheuk Hin"
         << "|" << setw(C2_WIDTH) << "22130980A"
         << "|" << setw(C3_WIDTH) << "201C"
         << "|" << endl;
    cout << "|_______________________|____________|_______|" << endl
         << endl;

    pressAnyKeyToContinue();
    goBack(option);
}

// >>>> R7 Exit
void stageExit()
{
    if (promptForYN("Are you sure to exit the system?") == 'y')
    {
        isExit = true;
    }
    else
    {
        cout << endl;
        isFirstStart = true; // a secret way for user to trigger the grand title again
        goBack(option);
    }
}

// >>>> Important
void sortBookList(Book list[], int size)
{
    Book *tempList = new Book[size]; // for storing the original book list
    // copy original book list to tempList
    for (int i = 0; i < size; i++)
    {
        tempList[i] = list[i];
    }

    char(*titles)[105] = new char[size][105]; // for storing the titles
    // copy the titles from book list
    for (int i = 0; i < size; i++)
    {
        strcpy(titles[i], list[i].getTitle());
        // append year after titles to sort different year version of
        char str[5];                               // to store year
        snprintf(str, 5, "%d", list[i].getYear()); // turn year from int into char[]
        strcat(titles[i], str);                    //
    }
    quickSort(titles, 0, size - 1); // sort the titles with QuickSort algorithm

    // rearrange the book list based on the sorted titles
    for (int i = 0; i < size; i++)
    {
        char yearChar[5];
        memcpy(yearChar, &titles[i][strlen(titles[i]) - 4], 4);
        yearChar[4] = '\0';
        int yearInt = stoi(yearChar);
        titles[i][strlen(titles[i]) - 4] = '\0';
        for (int j = 0; j < size; j++)
        {
            if (strcmp(titles[i], tempList[j].getTitle()) == 0 && yearInt == tempList[j].getYear())
            {
                list[i] = tempList[j];
                break;
            }
        }
    }

    // free dynamically allocated memory
    delete[] tempList;
    delete[] titles;
}

void sortBorrowerList(Borrower list[], int size)
{
    Borrower *tempList = new Borrower[size]; // for storing the original borrower list
    // copy original borrower list to tempList
    for (int i = 0; i < size; i++)
    {
        tempList[i] = list[i];
    }

    char(*names)[105] = new char[size][105]; // for storing the names
    // copy the titles from book list
    for (int i = 0; i < size; i++)
    {
        strcpy(names[i], list[i].getFullName());
    }
    quickSort(names, 0, size - 1); // sort the names with QuickSort algorithm

    // rearrange the borrower list based on the sorted names
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (strcmp(names[i], tempList[j].getFullName()) == 0)
            {
                list[i] = tempList[j];
                break;
            }
        }
    }

    // free dynamically allocated memory
    delete[] tempList;
    delete[] names;
}

void quickSort(char arr[][105], int start, int end)
{
    // base case: if the subarray contains 0 or 1 element, it is already sorted
    if (start >= end)
        return;

    // partition the subarray and get the pivot index
    int p = partition(arr, start, end);

    // recursive call to quickSort on the left subarray
    quickSort(arr, start, p - 1);

    // recursive call to quickSort on the right subarray
    quickSort(arr, p + 1, end);
}

int partition(char arr[][105], int start, int end)
{
    // select the first element in the subarray as the pivot
    char pivot[101];
    strcpy(pivot, arr[start]);

    // count the number of elements less than or equal to the pivot
    int count = 0;
    for (int i = start + 1; i <= end; i++)
    {
        if (strcmp(arr[i], pivot) <= 0)
            count++;
    }

    // calculate the pivot index based on the count
    int pivotIndex = start + count;

    // swap the pivot element with the element at the pivot index
    char temp[101];
    strcpy(temp, arr[pivotIndex]);
    strcpy(arr[pivotIndex], arr[start]);
    strcpy(arr[start], temp);

    // partition the subarray by iterating through it from both ends
    int i = start, j = end;
    while (i < pivotIndex && j > pivotIndex)
    {
        // find an element on the left side that is greater than the pivot
        while (strcmp(arr[i], pivot) <= 0)
        {
            i++;
        }

        // find an element on the right side that is less than or equal to the pivot
        while (strcmp(arr[j], pivot) > 0)
        {
            j--;
        }

        // if the left and right indices have not crossed, swap the elements and update the indices
        if (i < pivotIndex && j > pivotIndex)
        {
            char temp[101];
            strcpy(temp, arr[i]);
            strcpy(arr[i], arr[j]);
            strcpy(arr[j], temp);
            i++;
            j--;
        }
    }

    // return the final pivot index
    return pivotIndex;
}

// >>>> Misc.
void goBack(char &o)
{
    o = '0';
}

void pressAnyKeyToContinue()
{
    cout << "\nPress any key to continue...";
    (void)_getch();
    cout << "\n\n";
}

void displayInvalidInputMessage()
{
    cout << "Invalid input. Please input again.\n";
}

char promptForYN(string msg)
{
    char input;

    do
    { // ask for input until it is valid
        cout << msg << " [Y/N]: ";
        cin >> input;
        input = tolower(input);
        if (!(input == 'y' || input == 'n'))
        {
            displayInvalidInputMessage();
        }
    } while (!(input == 'y' || input == 'n'));

    return input;
}
