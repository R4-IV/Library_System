#ifndef SOURCE_CODE_DATALOADER_H
#define SOURCE_CODE_DATALOADER_H
#include "dependencies.h"

class DataLoader {
private:
    //holds path to the file being read
    std::string path;
    //trim string function removes leading spaces
    std::string trimStr(std::string stringToTrim);
public:
    //constructor takes a std::string argument which is the path to the file being read
    DataLoader(std::string path);
    //creates and returns a red black tree with all nodes inserted from the book list file
    RedBlackTree makeTree();
};
#endif //SOURCE_CODE_DATALOADER_H
