#ifndef SOURCE_CODE_GUI_H
#define SOURCE_CODE_GUI_H
#include "dependencies.h"
class Gui {
private:
    //holds the tree that the gui works with
    RedBlackTree tree;
public:
    //constructor assigns the gui a red black tree
    Gui(RedBlackTree& tree);
    //method to run/output the command line for the librarian
    void run();
};
#endif //SOURCE_CODE_GUI_H
