#include<iostream>
#include<string>  
#include<fstream>


using namespace std;
enum Genre { Romance = 1, Thriller = 2, Comedy = 3, History = 4, Biographical = 5, Fiction = 6, Science = 7, Commerce = 8, Actuality = 9, Social = 10 };
enum Status { Borrowed, OnShelf };
char keyWord[100]; //title of the book that we are searching for.
/**
This is the class for library.
The library admits a member, and issue a book.
*/
class Library {
public:
	string bookId; //Id of the book
	float  bookPrice; //Price of book

	/**
	This is the constructor for the library
	*/
	Library()
	{
		bookPrice = 0;
		bookId = "";
	}


	//virtual void issue_book(){} //inherited by Transaction class


};
/**
This class will create a book object
addBook, viewAllBooks, searchBook
*/

class Book :public Library {
public:
	string bookId = ""; //Id of the book
	float  bookPrice = 0.0; //Price of book
	char bookTitle[100];//title of the book
	char bookAuthor[100]; //author of the book
	Genre genre;
	string state;
	int genreUser = 0;

	void setBook() {
		cout << "Enter book id: ";
		cin >> bookId;
		cin.ignore();
		cout << "Enter book name: ";
		cin.getline(bookTitle, 100);
		cout << "Enter author name: ";
		cin.getline(bookAuthor, 100);
		cout << "Enter price: ";
		cin >> bookPrice;
		cout << "Enter the genre of the book: (follow the guidelines)." << endl;
		cout << "Romance=1, Thriller=2, Comedy=3, History=4, Biographical=5, Fiction=6, Science=7, Commerce=8, Actuality=9, Social =10:" << endl;
		cin >> genreUser;
		//Get the genre
		switch (genreUser)
		{
		case Romance:
			genre = Romance;
			break;
		case Thriller:
			genre = Thriller;
			break;
		case Comedy:
			genre = Comedy;
			break;
		case History:
			genre = History;
			break;
		case Biographical:
			genre = Biographical;
			break;
		case Fiction:
			genre = Fiction;
			break;
		case Science:
			genre = Science;
			break;
		case Commerce:
			genre = Commerce;
			break;
		case Actuality:
			genre = Actuality;
			break;
		case Social:
			genre = Social;
			break;

		default:
			cout << "ERROR - please enter values (1-10)";
			break;
		}

	}

    void display()
	{
		cout << "*****************************************" << endl;
		cout << "Title  : " << bookTitle << endl;
		cin.ignore();
		cout << "ID     : " << bookId << endl;
		cin.ignore();
		cout << "Author : " << bookAuthor << endl;
		cin.ignore();
		cout << "Price  : " << bookPrice << endl;
		cin.ignore();
		cout << "*****************************************" << endl;
	}

	virtual void addBook() {}
	virtual void viewAllbooks() {}
	virtual void searchBook(){}
	virtual void deleteBook(){}
};
/**
This class creates a member.
*/
class Member {
public:
	string memberId;
	char memberName[50];

	Member()
	{
		cout << "Enter your name here: " << endl;
		cin.getline(memberName, 50);

		cout << "Enter your library ID here: " << endl;
		cin >> memberId;
	}
};

/**
This class creates a transaction
*/
class Transaction :public Book, Library {
public:
	Book novel;
	

	void addBook()
	{
		novel.setBook();
		fstream wr;
		wr.open("book_data.txt", ios::app);
		wr.write((char*)&novel, sizeof(novel));

		cout << "Book added successfully to our records!" << endl;
	}

	void viewAllbooks()
	{
		fstream rd;
		rd.open("book_data.txt", ios::in);
		rd.seekg(0, ios::end);
		int size = rd.tellg() / sizeof(novel);
		rd.seekg(0, ios::beg);
		cout << "This is the size of the file " << size << endl;
		for (int i = 1; i <= size; i++)
		{
            rd.read((char*)&novel, sizeof(novel));
			novel.display();
		}
	}
	
	void searchBook()
	{
		cout << "Enter the title that you want to search : " << endl;
		cin >>keyWord;
		ifstream myfile;
		myfile.open("book_data.txt");
		string title;
		while (getline(myfile, title)) {
			if (title.find(keyWord) != string::npos) {
				cout << "Found!" << endl;
			}
			else {
				cout << "Sorry, we do not have that book"<<endl;
			}
		}
		myfile.close();
	}

	void deleteBook()
	{
		string line, name;
		cout << "Please enter the name of record you want to delete: ";
		cin >> name;
		ifstream myfile;
		myfile.open("book_data.txt");
		ofstream temp;
		temp.open("temp.txt");
		while (getline(myfile, line))
		{
			if (line != name)
				temp << line << endl;
			cout << line <<endl;
		}
		cout << "The record with the name " << name << " has been deleted if it exsisted" << endl;
		myfile.close();
		temp.close();
		remove("book_data.txt");
		rename("temp.txt", "book_data.txt");


	}

};
int main()
{
	int choice;
	int numberOfBooks;
	Book* currentBook;

	Transaction currentT;
	Member customer;

	cout << "Nice seeing you today, " << customer.memberName << " ." << endl;
	cout << "How many books do you want to borrow today?" << endl;
	cin >> numberOfBooks;
	if (numberOfBooks > 0 && numberOfBooks <3)
	{

		cout << "********************* Welcome To Star Trek Library ********************" << endl;
		while (1)
		{
			cout << "What would you like to do today ?" << endl;
			cout << "1. Add Book" << endl;
			cout << "2. View all Books" << endl;
			cout << "3. Search Book" << endl;
			cout << "4. Delete Book" << endl;
			cin >> choice;

			switch (choice)
			{
			case 1:
				Book * newBook;
				newBook = &currentT;
				newBook->addBook();
				break;
			case 2:
				currentBook = &currentT;
				currentBook->viewAllbooks();
				cout << "Hope this helps." << endl;
				break;
			
			case 3:
				currentBook = &currentT;
				currentBook->searchBook();
				break;
			case 4:
				currentBook = &currentT;
				currentBook->deleteBook();
				break;

			default:
				cout << "Please select from our menu." << endl;

			}


		}
		cout << "Thank You for visiting today." << endl;
	}
	else
	{
		cout << "SORRY NO MORE BOOKS CAN BE ISSUED" << endl;
	}
	return 0;

}

