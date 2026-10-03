# Library-System
A console-based library management system built in C++. It manages books, borrowers, loans, returns, and library statistics.

## Features

- Import book and borrower records from CSV files
- Search and manage book and borrower records
- Validate new records before adding them
- Track book availability and borrowing history
- Borrow and return books with borrower limits
- Display usage statistics and member information

## Requirements

- A C++ compiler such as MinGW `g++`
- Windows PowerShell or a similar terminal

## Build and Run

Open a terminal in the project folder and run:

```powershell
g++ library.cpp -o library.exe; .\library.exe
```

After the first build, you can run the program again with:

```powershell
.\library.exe
```

When the program asks for the CSV file paths, enter the file names if the CSV files are in the project folder:

```text
BookList.csv
BorrowerList.csv
```

You can also enter full paths, such as:

```text
C:\path\to\project\BookList.csv
C:\path\to\project\BorrowerList.csv
```

Do not include quotation marks around the paths.

## CSV Formats

Book records use this format:

```text
Book ID,Title,Author,Publisher,Year
```

Borrower records use this format:

```text
Last Name,First Name,Contact Number
```

## Project Files

- `library.cpp` - Main application source code
- `BookList.csv` - Book data
- `BorrowerList.csv` - Borrower data
