#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>
#include <algorithm>

using namespace std;

struct Book
{
  string ISBN;
  string title;
  string author;
  int edition;
  int quantity;
  double price;
};

void readFirst(vector<Book>& records, ifstream& inputFile, string& action);
void categoryChoice(vector<Book>& records, ifstream& inputFile, string& action);
void display(vector<Book>& records);
void add(vector<Book>& records, ifstream& inputFile);
void searchBook(vector<Book>& records, ifstream& inputFile);
void searchAuthor(vector<Book>& records, ifstream& inputFile);
void deleteISBN(vector<Book>& records, ifstream& inputFile);
void updatePrice(vector<Book>& records, ifstream& inputFile);
void updateQuantity(vector<Book>& records, ifstream& inputFile);
void sort(vector<Book>& records);
bool predicate(Book a, Book b);
void save(vector<Book>& records, string& action);

int main() {
  //vector declaration for our struct Book
  vector<Book> records;
  string action;
  
  //open stream to bookstoreTrans.txt
  ifstream inputFile;
  inputFile.open("bookstoreTrans.txt");

  //initialize action with the return value of readFirst()
  do {
  readFirst(records, inputFile, action);
  categoryChoice(records, inputFile, action);
  } while (action != "exit");

  inputFile.close();

  return 0;
}

void readFirst(vector<Book>& records, ifstream& inputFile, string& action) {
  inputFile >> action;
}

void categoryChoice(vector<Book>& records, ifstream& inputFile, string& action) {
  if (action == "display")
    display(records);
  else if (action == "add")
    add(records, inputFile);
  else if (action == "searchBook")
    searchBook(records, inputFile);
  else if (action == "searchAuthor")
    searchAuthor(records, inputFile);
  else if (action == "delete")
    deleteISBN(records, inputFile);
  else if (action == "updatePrice")
    updatePrice(records, inputFile);
  else if (action == "updateQuantity")
    updateQuantity(records, inputFile);
  else if (action == "sort")
    sort(records);
  else if (action == "save")
    save(records, action);
}

void display(vector<Book>& records) {
  cout << fixed << setprecision(2)
       << setw(11) << "ISBN"
       << setw(42) << "Title"
       << setw(18) << "Author"
       << setw(8) << "Edition"
       << setw(13) << "Quantity"
       << setw(10) << "Price"
       << endl;

  for (int i = 0; i <= 102; i++)
    cout << "-";
  cout << endl;

  for(int i = 0; i < records.size(); i++) {
    cout << fixed << setprecision(2)
	 << setw(11) << records[i].ISBN
	 << setw(42) << records[i].title
	 << setw(18) << records[i].author
	 << setw(8) << records[i].edition
	 << setw(13) << records[i].quantity
	 << setw(10) << records[i].price
	 << endl;
  }
}

void add(vector<Book>& records, ifstream& inputFile) {
  Book temp;
  bool exists = false;
  
  inputFile >> temp.ISBN
	    >> temp.title
	    >> temp.author
	    >> temp.edition
	    >> temp.quantity
	    >> temp.price;

  if (records.size() == 0)
    records.push_back(temp);
  else {
    for (int i = 0; i < records.size(); i++) {
      if (temp.ISBN == records[i].ISBN) {
	records[i].quantity += 1;
	
	cout << temp.ISBN << " already exists in the database. The number of copies is now " << records[i].quantity << endl;

	exists = true;
      }
    }
  }

  if (exists == false) {
    records.push_back(temp);
    cout << temp.ISBN << " successfully added to the database..." << endl;
  }
}

void searchBook(vector<Book>& records, ifstream& inputFile) {
  string bookTitle;
  bool exists = false;

  inputFile >> bookTitle;

  cout << "Book search results for the keyword: " << bookTitle << "..." << endl;

  for (int i = 0; i < records.size(); i++) {
    int p = 0;
    p = records[i].title.find(bookTitle, 0);

    if (p >= 0) {
      cout << records[i].ISBN << " "
	   << records[i].title << " "
	   << records[i].author << " "
	   << records[i].quantity << endl;
      exists = true;
    }
  }

  if (exists == false)
    cout << "Sorry, no matching book exists" << endl;
}

void searchAuthor(vector<Book>& records, ifstream& inputFile) {
  string bookAuthor;
  bool exists = false;

  inputFile >> bookAuthor;

  cout << "Searching for author " << bookAuthor << "..." << endl;

  for (int i = 0; i < records.size(); i++) {
    int p = 0;
    p = records[i].author.find(bookAuthor, 0);

    if (p >= 0) {
      cout << records[i].ISBN << " "
           << records[i].title << " "
           << records[i].author << " "
           << records[i].quantity << endl;
      exists = true;
    }
  }

  if (exists == false)
    cout << "Sorry, no matching book exists." << endl;
}

void deleteISBN(vector<Book>& records, ifstream& inputFile) {
  string bookISBN;
  bool exists = false;
  
  inputFile >> bookISBN;

  for (int i = 0; i < records.size(); i++) {
    if (bookISBN == records[i].ISBN) {
      exists = true;

      records.erase(records.begin() + 1);
      cout << bookISBN << " successfully deleted." << endl;
    }
  }

  if (exists == false)
    cout << bookISBN << " does not exist and could not be deleted." << endl;
  
}

void updatePrice(vector<Book>& records, ifstream& inputFile) {
  string bookISBN;
  double newPrice;
  bool exists = false;

  inputFile >> bookISBN >> newPrice;

  for (int i = 0; i < records.size(); i++) {
    if (bookISBN == records[i].ISBN) {
      records[i].price = newPrice;

      cout << bookISBN << " price successfully updated to " << newPrice << endl;

      exists = true;
    }
  }

  if (exists == false)
    cout << bookISBN << " does not exist and its price cannot be updated." << endl;
}

void updateQuantity(vector<Book>& records, ifstream& inputFile) {
  string bookISBN;
  int newQuantity;
  bool exists = false;

  inputFile >> bookISBN >> newQuantity;

  for (int i = 0; i < records.size(); i++) {
    if (bookISBN == records[i].ISBN) {
      records[i].quantity = newQuantity;

      cout << bookISBN << " quantity successfully updated to " << newQuantity << endl;

      exists = true;
    }
  }

  if (exists == false)
    cout << bookISBN << " does not exist and its quantity cannot be updated." << endl;

}

void sort(vector<Book>& records) {
  sort(records.begin(), records.end(), predicate);

  cout << "Bookstore database successfully sorted..." << endl;

}

bool predicate(Book a, Book b) {
  if (a.title == b.title) {
    if (a.edition < b.edition)
      return true;
    else
      return false;
  }
  else if (a.title < b.title)
    return true;
  else
    return false;
}

void save(vector<Book>& records, string& action) {
  ofstream outputFile;
  outputFile.open("bookstoreOut.txt");

  for (int i = 0; i < records.size(); i++) {
    outputFile << records[i].ISBN << " "
	       << records[i].title << " "
	       << records[i].author << " "
	       << records[i].edition << " "
	       << records[i].quantity << " "
	       << records[i].price << " "
	       << endl;
  }

  cout << "Bookstore database successfull saved..." << endl;

  outputFile.close();

  action = "exit";
}
