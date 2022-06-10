#ifndef SOURCE_CODE_NODE_H
#define SOURCE_CODE_NODE_H
//Enum type used to distinguish between red and black nodes
enum Color {RED,BLACK};

//Node class contains parent and children pointers , the color property and a pointer to the data it contains

class Node {
public:
    Node* parent;
    Node* leftChild;
    Node* rightChild;
    Book data;
    Color color;
};
//creates an alias for node* to improve code readability
typedef Node* NodePtr;
#endif //SOURCE_CODE_NODE_H
