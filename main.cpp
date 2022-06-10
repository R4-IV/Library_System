#include "dependencies.h"
int main(int argc, char **argv){
    //Handles passing path to booklist from commandLine
    if(argc == 1 ){
        DataLoader dt = DataLoader("books.txt");
        RedBlackTree rb = dt.makeTree();
        Gui gui = Gui(rb);
        gui.run();
    }
    else if(argc == 2){
        DataLoader dt = DataLoader(argv[1]);
        RedBlackTree rb = dt.makeTree();
        Gui gui = Gui(rb);
        gui.run();
    }
    else{
        std::cout<<"Too many arguments"<<std::endl;
    }
    return 0;
}


