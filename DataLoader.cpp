#include "dependencies.h"
//implemented constructor sets the file access path
DataLoader::DataLoader(std::string path) {
    this->path = path;
}

//make tree method tokenizes input creates book objects and inserts them into the rb tree
RedBlackTree DataLoader::makeTree() {
    //creates the rb tree to hold nodes
    RedBlackTree rb = RedBlackTree();

    //members to hold all the different data type tokens
    std::string titleToken;
    std::string isbnToken;
    std::string qtyTokenStr;
    unsigned int qtyToken;
    std::string authorToken;
    std::vector<std::string> vecToken;

    //string to hold the current line from the stream
    std::string currentLine;
    //int member decides which token is being loaded
    unsigned int currentToken = 0;
    //if stream from provided path
    std::ifstream bookList(path);

    //while loop will load tokens until end of file
    while(std::getline(bookList , currentLine)){
        //if char is a tab load next token
        for(char c : currentLine){
            if(c == '\t'){
                if(currentToken == 1){
                    //last author will not have a semicolon following it so this condition solves that problem
                    authorToken = trimStr(authorToken);
                    vecToken.push_back(authorToken);
                    authorToken = "";
                }
                currentToken++;
                //continue so that none of the tokens appends a tab character to itself
                continue;
            }
            if(currentToken == 0){
                //title token handling
                titleToken+= c;
            }
            else if(currentToken == 1){
                //author token handling
                if(c == ';'){
                    authorToken = trimStr(authorToken);
                    vecToken.push_back(authorToken);
                    authorToken = "";
                    continue;
                }
                authorToken += c;
            }
            else if(currentToken == 2){
                //isbn token handling
                isbnToken+= c;
            }
            else if(currentToken == 3){
                //qty token handling
                qtyTokenStr += c;
            }
        }
        //convert the qty string token to int
        qtyToken = std::stoi(qtyTokenStr);
        //create a book obj from the tokens
        Book b = Book(titleToken , vecToken , isbnToken , qtyToken);
        //insert node to the tree
        rb.insertNode(b);
        //reset token variables
        titleToken = "";
        vecToken.clear();
        isbnToken = "";
        currentToken = 0;
        authorToken = "";
        qtyTokenStr = "";
        qtyToken = 0;
    }
    //return the tree
    return rb;
}

//method to remove the leading spaces from the author strings so that formatting is retained in the print Book function
std::string DataLoader::trimStr(std::string stringToTrim) {
    //finds the index of the first occurrence of a non whitespace character
    int strBegin = stringToTrim.find_first_not_of(' ');
    //returns substring excluding the leading spaces
    return stringToTrim.substr(strBegin , stringToTrim.length());
}