#ifndef SOURCE_CODE_REDBLACKTREE_H
#define SOURCE_CODE_REDBLACKTREE_H


class RedBlackTree {
private:
    //tracks the tree root node
    NodePtr rootNode;
    //keeps a pointer to null node which is the terminating point for most functions
    NodePtr nullNode;
    //keeps a vector lattice this is purely for testing purposes used by the is valid tree method
    std::vector<std::vector<NodePtr>> nodeVec;

    //private deletion related methods
    void fixDeletion(NodePtr replacement , Color deletedColor);

    //helper function returns true if the provided pointer is the left child false will indicate the inverse
    bool isLeftChild(NodePtr node);

    //successor method used in deletion
    NodePtr getSuccessor(NodePtr node);

    //function that fixes double red cases post insertion
    void fixInsertion(NodePtr node);

    //swaps the provided node from red to black / black to red
    void swapColor(NodePtr node);

    //recolor one of the cases for fixing insertion will swap the colors of all nodes in the arguments
    void reColor(NodePtr parent , NodePtr grandParent , NodePtr uncle);

    //left/right rotation methods used in both fixing post insertion double reds as well as fixing post deletion double blacks
    void leftRotation(NodePtr node);
    void rightRotation(NodePtr node);


public:
    //red black tree constructors
    RedBlackTree();

    //delete function
    void deleteNode(NodePtr node);
    //insertion function
    void insertNode(Book data);

    //insertion function
    NodePtr searchTree(std::string data);

    //horizontal representation of the tree during development it would print node data as it was originally implemented
    //with integers now it instead will display "node" in its appropriate color,
    void printTree(const NodePtr node , const std::string& spacer , bool isLeftChild);
    //returns root of the tree
    NodePtr getRoot();
    //returns null Node for comparison in gui class
    NodePtr getNullNode();

    //method that returns whether the red black tree full fills all the properties
    bool isValidRBTree();
    //valid tree helper functions first
    void isValidTreeInternals(NodePtr node , std::vector<NodePtr>& nodePath);
    bool isValidTreeAnalysis(std::vector<std::vector<NodePtr>>& nodeVec);
    void inOrderPrint(NodePtr node);
};


#endif //SOURCE_CODE_REDBLACKTREE_H
