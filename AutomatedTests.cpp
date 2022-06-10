#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "dependencies.h"
#include "Book.cpp"
#include "RedBlackTree.cpp"
#include "DataLoader.cpp"

//component test of Book Class
TEST_CASE("Book Class Test"){

    std::vector<std::string> vecOne;
    vecOne.push_back("M. A. H. Dempster");
    vecOne.push_back("Juho Kanniainen");
    vecOne.push_back("John Keane");
    vecOne.push_back("Erik Vynckier");

    int vecOneSize = vecOne.size();

    std::vector<std::string> vecTwo;
    vecTwo.push_back("John C. Mitchell");

    Book bookOne = Book("High-Performance Computing in Finance" , vecOne , "9781315354699" , 4);
    Book bookTwo = Book("Concepts in Programming Languages" , vecTwo , "9780521780988" , 1);
    Book bookThree = Book("High-Performance Computing in Finance" , vecOne , "9781315354691" , 14);

    std::string testStrOne = "Deep Reinforcement Learning Hands-On";
    std::string testStrTwo = "UNIX Administration";
    std::string testStrThree = "High-Performance Computing in Finance";

    SECTION("Testing assignment with constructor"){
        REQUIRE(bookOne.getTitle().compare("High-Performance Computing in Finance") == 0);
        REQUIRE(bookOne.getISBN().compare("9781315354699") == 0);
        REQUIRE(bookOne.getQty() == 4);
        REQUIRE(bookOne.getAuthors().size() == vecOneSize);
        for(int i = 0; i < vecOneSize; i++){
            REQUIRE(bookOne.getAuthors()[i].compare(vecOne[i]) == 0);
        }
    }
    SECTION("Testing Book to Book comparison Operators"){
        REQUIRE((bookOne > bookTwo) == false);
        REQUIRE((bookOne < bookTwo) == true);
        REQUIRE(bookOne == bookThree);
    }
    SECTION("Testing Book to String Comparison Operators"){
        REQUIRE(testStrOne > bookOne);
        REQUIRE(testStrTwo < bookOne);
        REQUIRE(testStrThree == bookOne);
    }
    SECTION("Testing Book quantity removal "){
        REQUIRE(bookOne.removeBook(5) == 4);
        REQUIRE(bookOne.removeBook(2) == 2);
        REQUIRE(bookOne.removeBook(1) == 1);
    }
}

TEST_CASE("Red Black tree function Testing"){
    //creates a tree with preinserted nodes from the text file
    DataLoader dt = DataLoader("books.txt");
    RedBlackTree rb = dt.makeTree();
    std::vector<std::string> vecOne;
    vecOne.push_back("M. A. H. Dempster");

    Book bookOne = Book("Programming for Dummies" , vecOne , "9781315354699" , 4);

    SECTION("Testing if tree is valid post insertion "){
       REQUIRE(rb.isValidRBTree());
    }
    SECTION("Testing Trees searching capabilities"){
        REQUIRE(rb.searchTree("Understanding Machine Learning") != rb.getNullNode());
        REQUIRE(rb.searchTree("Deep Reinforcement Learning Hands-On") != rb.getNullNode());
        REQUIRE(rb.searchTree("Operating Systems In Depth: Design and Programming") != rb.getNullNode());
    }
    SECTION("Testing insertion and tree validity post insertion"){
        REQUIRE(rb.searchTree("Programming for Dummies") == rb.getNullNode());
        rb.insertNode(bookOne);
        REQUIRE(rb.searchTree("Programming for Dummies") != rb.getNullNode());
        REQUIRE(rb.isValidRBTree());
    }
    SECTION("Testing Deletion in Red black tree and check its validity post deletion  "){
        REQUIRE(rb.searchTree("Understanding Machine Learning") != rb.getNullNode());
        rb.deleteNode(rb.searchTree("Understanding Machine Learning"));
        REQUIRE(rb.searchTree("Understanding Machine Learning") == rb.getNullNode());
        REQUIRE(rb.isValidRBTree());
    }
}


