#include "dependencies.h"

//implemented constructor
Gui::Gui(RedBlackTree &tree) {
    this->tree = tree;
}
//run function provides all the text based prompt required for the system
void Gui::run() {
    std::cout<<std::endl;
    std::cout<<"Welcome to the library system"<<std::endl;

    //loop prompt until exit is selected
    while (true){
        std::cout<<std::endl;
        std::cout<<"Select an Option"<<std::endl;
        std::cout<<std::endl;
        std::cout<<"Add Book........1"<<std::endl;
        std::cout<<"Remove Book.....2"<<std::endl;
        std::cout<<"Search Book.....3"<<std::endl;
        std::cout<<"Exit............4"<<std::endl;
        std::cout<<">> ";
        int userIn;
        std::cin >> userIn;
        //makes sure the input is an int
        if (std::cin.fail()) {
            std::cout<<std::endl;
            std::cout<<"Incorrect input try again"<<std::endl;
            std::cin.clear();
            std::cin.ignore(1000 , '\n');
            continue;
        }
        //prevents an int out of bounds of the specified selection
        else if(userIn > 4 || userIn < 1){
            std::cout<<std::endl;
            std::cout<<"Input out of bounds try again"<<std::endl;
            std::cin.clear();
            std::cin.ignore(1000 , '\n');
            continue;
        }
        //holds the search string in searching/deletion selection
        std::string searchString;
        int amountToRemove;
        //variables used in switch statement that required prior declaration
        int newBookAmount;
        std::string newBookTitle = "";
        std::string newBookIsbn = "";
        std::string newBookAuthor = "";
        std::vector<std::string> newBookAuthorVec;
        bool allDigits = true;
        int userSelection;
        NodePtr foundNode;
        NodePtr  removalNode;
        Book newBook = Book();

        //cases based on what the user selected
        switch (userIn) {
            //add new book to system
            case 1:
                std::cout<<"Add a new book to the library system"<<std::endl;
                std::cout<<std::endl;
                std::cout<<"Enter new book Title: "<<std::endl;
                std::cout<<">> ";
                std::cin.ignore(1000 , '\n');
                std::getline(std::cin , newBookTitle);
                std::cout<<"Enter new book ISBN: "<<std::endl;
                while(true){
                    allDigits = true;
                    std::cout<<">> ";
                    std::getline(std::cin , newBookIsbn);
                    if(!(newBookIsbn.length() == 10 || newBookIsbn.length() == 13)){
                        std::cout<<"Incorrect ISBN number length, please provide an isbn with either 10 or 13 digits"<<std::endl;
                        continue;
                    }
                    else{
                        for(char c : newBookIsbn){
                            if(c - '0' < 0 || c - '0' > 9){
                                allDigits = false;
                            }
                        }
                        if(allDigits){
                            break;
                        }
                        else{
                            std::cout<<"The ISBN number must only contain digits"<<std::endl;
                            continue;
                        }
                    }
                }
                std::cout<<"Enter new book Quantity: "<<std::endl;
                while(true){
                    std::cout<<">> ";
                    std::cin >> newBookAmount;
                    if (std::cin.fail()) {
                        std::cout<<std::endl;
                        std::cout<<"Book amount must be a non negative integer"<<std::endl;
                        std::cin.clear();
                        std::cin.ignore(1000 , '\n');
                        continue;
                    }
                    else if(newBookAmount < 0 ){
                        std::cout<<std::endl;
                        std::cout<<"Book amount must be a non negative integer"<<std::endl;
                        std::cin.clear();
                        std::cin.ignore(1000 , '\n');
                        continue;
                    } else{
                        break;
                    }
                }
                std::cout<<"Enter new book Author: "<<std::endl;
                std::cout<<">> ";
                std::cin.ignore(1000 , '\n');
                std::getline(std::cin , newBookAuthor);
                newBookAuthorVec.push_back(newBookAuthor);
                while(true){
                    std::cout<<"Add another Author? "<<std::endl;
                    std::cout<<"Yes........1"<<std::endl;
                    std::cout<<"No.........2"<<std::endl;
                    std::cout<<std::endl;
                    std::cout<<">> ";
                    std::cin >> userSelection;
                    if (std::cin.fail()) {
                        std::cout<<std::endl;
                        std::cout<<"Incorrect input try again"<<std::endl;
                        std::cin.clear();
                        std::cin.ignore(1000 , '\n');
                        continue;
                    }
                    else if(!(userSelection == 1 || userSelection == 2)){
                        std::cout<<std::endl;
                        std::cout<<"Incorrect input try again"<<std::endl;
                        std::cin.clear();
                        std::cin.ignore(1000 , '\n');
                        continue;
                    }

                    if(userSelection == 2){
                        break;
                    }
                    if(userSelection == 1){
                        std::cout<<"Enter new book Author: "<<std::endl;
                        std::cout<<">> ";
                        std::cin.ignore(1000 , '\n');
                        std::getline(std::cin , newBookAuthor);
                        newBookAuthorVec.push_back(newBookAuthor);
                        continue;
                    }
                }
                newBook = Book(newBookTitle , newBookAuthorVec , newBookIsbn , newBookAmount);
                std::cout<<std::endl;
                std::cout<<"Preview: "<<std::endl;
                std::cout<<newBook<<std::endl;
                tree.insertNode(newBook);
                break;
            case 2:
                //case 2 book removal
                std::cout<<"Enter the title for removal"<<std::endl;
                std::cout<<">> ";
                std::cin.ignore(1000 , '\n');
                std::getline(std::cin , searchString);
                removalNode = tree.searchTree(searchString);
                if(removalNode == tree.getNullNode()){
                    //prevents the deletion function being called with a null node
                    std::cout<<"No Book with \""<<searchString <<"\" title found"<<std::endl;
                }
                else{
                    std::cout<<"Book for removal: "<<std::endl;
                    std::cout<<removalNode->data<<std::endl;
                    while (true){
                        std::cout<<"Enter an amount for removal:"<<std::endl;
                        std::cout<<">> ";
                        std::cin >> amountToRemove;
                        if (std::cin.fail()) {
                            std::cout<<std::endl;
                            std::cout<<"Incorrect input try again"<<std::endl;
                            std::cin.clear();
                            std::cin.ignore(1000 , '\n');
                            continue;
                        }
                        else if(amountToRemove <= 0 ){
                            std::cout<<"Cannot Remove negative or zero copies of the book"<<std::endl;
                            continue;
                        }
                        else{
                            break;
                        }
                    }
                    int resultingAmount = removalNode->data.removeBook(amountToRemove);
                    if(resultingAmount == 0){
                        tree.deleteNode(removalNode);
                        std::cout<<"Book removed from the system"<<std::endl;
                    }
                    else{
                        std::cout<<"New Quantity: "<< resultingAmount<<std::endl;
                    }
                }
                break;
            case 3:
                //case 3 searching
                std::cout<<"Enter the title for searching"<<std::endl;
                std::cout<<">> ";
                std::cin.ignore(1000 , '\n');
                std::getline(std::cin , searchString);
                foundNode = tree.searchTree(searchString);
                //handles case where the title is not found
                if(foundNode == tree.getNullNode()){
                    std::cout<<"No Book with \""<<searchString <<"\" title found"<<std::endl;
                }
                else{
                    std::cout<<"Result: "<<std::endl;
                    std::cout<<foundNode->data<<std::endl;
                }
                break;
            case 4:
                //case 4 exit from the system
                exit(0);
        }
    }
}


