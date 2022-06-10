#include "dependencies.h"

//implementation of the book constructor
Book::Book() {
    std::vector<std::string> emptyVec;
    this->title = "";
    this->authors = emptyVec;
    this->isbnNumber = "";
    this->qty = 0;
}
Book::Book(const std::string title, std::vector<std::string> authors, const std::string isbnNumber, unsigned int qty) {
    this->title = title;
    this->authors = authors;
    this->isbnNumber = isbnNumber;
    this->qty = qty;
}

//implemented overloaded output stream method
std::ostream& operator << (std::ostream& out , const Book& book){
    const std::string authorPrefix = "            ";
    //keeps track of the first author occurrence in the for loop so that the prefix spacer is only applied from the second
    //call onwards
    bool firstOccurrence = true;

    out << "Title:      " << book.title << std::endl;
    out << "ISBN:       " << book.isbnNumber << std::endl;
    out << "Quantity:   " <<book.qty << std::endl;
    out << "Author(s):  ";
    for(std::string author : book.authors){
        if(!firstOccurrence){
            out << authorPrefix;
        }
        out << author << std::endl;
        firstOccurrence = false;
    }
    return out;
}

//Implemented less than operator used for lexicographical ordering of nodes in the tree
bool operator<( const Book& bookOne , const Book& bookTwo){
    if(bookOne.title.compare(bookTwo.title) > 0){
        return true;
    }
    else{
        return false;
    }
}
//Implemented less than operator used for searching tree lexicographically
bool operator<( const std::string& string , const Book& book){
    if(string.compare(book.title) > 0){
        return true;
    }
    else{
        return false;
    }
}

//Implemented greater than operator used for lexicographical ordering of nodes in the tree
bool operator>(const Book& bookOne , const Book& bookTwo){
    if(bookOne.title.compare(bookTwo.title) < 0){
        return true;
    }
    else{ return false;}
}
//Implemented greater than operator used for searching tree lexicographically
bool operator>(const std::string& string , const Book& book){
    if(string.compare(book.title) < 0){
        return true;
    }
    else{ return false;}
}
//== operator used for the edge case where a double entry
bool operator==(const Book& bookOne , const Book& bookTwo){
    if(bookOne.title.compare(bookTwo.title) == 0){
        return true;
    }
    else{
        return false;
    }
}
//== operator used to find matching nodes in search and delete
bool operator==(const std::string& string , const Book& book){
    if(string.compare(book.title) == 0){
        return true;
    }
    else{
        return false;
    }
}

//getter method will mostly be used in the unit testing portion of the program as
//Node comparison operators will be used for insertion only the get title method is likely to be used in searching

//Implemented get title method
std::string Book::getTitle() {
    return title;
}

//Implemented get Isbn method
std::string Book::getISBN() {
    return isbnNumber;
}

//implemented get qty method
unsigned int Book::getQty() {
    return qty;
}

//Implemented gets author vectors
std::vector<std::string> Book::getAuthors() {
    return authors;
}

//implemented remove book function
int Book::removeBook(int amount) {
    //case: attempting to remove an amount greater than the currently available stock
    if(amount >  this->qty){
        std::cout<<"Quantity selected greater than currently available stock"<<std::endl;
        std::cout<<"Quantity will be unchanged try again with correct stock level"<<std::endl;
    }
    //removing an amount less than or equal to the stock
    else {
        this->qty = this->qty - amount;
    }
    //returns the current qty after book removal this will additionally be passed to the node delete function
    //which will delete the node if the book qty is 0
    return this->qty;
}













