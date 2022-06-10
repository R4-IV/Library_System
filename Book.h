#ifndef SOURCE_CODE_BOOK_H
#define SOURCE_CODE_BOOK_H
#include "dependencies.h"
class Book {

private:
    //member variables
    std::string title;
    //facilitates an unknown amount of authors that is 1 or more
    std::vector<std::string> authors;
    //would store in either int[10] or char[10] however because ISBN-13 is a thing strings containers are easier
    std::string isbnNumber;
    //qty won't be negative hence unsigned int
    unsigned int qty;

public:
    //constructor
    Book();
    Book(std::string title , std::vector<std::string> authors , std::string isbNumber , unsigned int qty);

    //friend operators

    //ostream operator overloaded to display all the book information when << is used with a Book Object
    friend std::ostream& operator << (std::ostream& out , const Book& book);

    //operator < comparison between book objects greater than
    friend bool operator<( const Book& bookOne , const Book& bookTwo);
    friend bool operator<( const std::string& string , const Book& book);

    //operator > comparison between book objects less than
    friend bool operator>( const Book& bookOne , const Book& bookTwo);
    friend bool operator>( const std::string& string , const Book& book);

    //== operator fo object comparison equal object
    friend bool operator==( const Book& bookOne , const Book& bookTwo);
    friend bool operator==( const std::string& , const Book& book);

    //
    //returns the books title
    std::string getTitle();

    //returns the authors vector
    std::vector<std::string> getAuthors();

    //gets ISBN number
    std::string getISBN();

    //returns the book current qty
    unsigned int getQty();

    //remove a copy of this book
    int removeBook(int amount);
};
#endif //SOURCE_CODE_BOOK_H

