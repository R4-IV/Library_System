#include "dependencies.h"
//red black tree constructor creates a black null node and sets it as the root
//this already satisfies 2 properties of the red black tree, Null leaves are black and root is black
RedBlackTree::RedBlackTree() {
    nullNode = new Node;
    //sets data to representation of null
    nullNode->data = Book();
    //root and null leaves are black
    nullNode->color = BLACK;
    nullNode->leftChild = nullptr;
    nullNode->rightChild = nullptr;
    //sets the root to be equal to null node initially this causes the root parent to be equal to nullptr
    //without proper guards preventing accessing the root parent segmentation faults are likely
    rootNode = nullNode;
}

//insertion function inserts the specified data into the tree
void RedBlackTree::insertNode(Book data) {

    //creates a new red node
    NodePtr insertionNode = new Node;
    insertionNode->color = RED;
    //parent set later when correct place found in tree
    insertionNode->parent = nullptr;
    //sets the provided data to the node
    insertionNode->data = data;
    insertionNode->rightChild = nullNode;
    insertionNode->leftChild = nullNode;

    //current Node starts out as root node and traverses via a loop
    NodePtr currentNode = this->rootNode;
    //parent Node starts out as nullptr because the root node does not have a parent node
    NodePtr parentNode = nullptr;

    //traverse through the tree
    //nullNode determines whether
    while(currentNode != nullNode){
        parentNode = currentNode;
        if(insertionNode->data > currentNode->data){
            currentNode = currentNode->rightChild;
        }
        else{
            currentNode = currentNode->leftChild;
        }
    }
    //sets the inserted node parent property
    insertionNode->parent = parentNode;
    //case when the inserted node is the root node of the tree
    if(parentNode == nullptr){
        rootNode = insertionNode;
        rootNode->color = BLACK;
    }

    else if(insertionNode->data > parentNode->data){
        parentNode->rightChild = insertionNode;
    }
    else{
        parentNode->leftChild = insertionNode;
    }
    //method call to fix any double reds resulting from bst insertion
    fixInsertion(insertionNode);

}

//Returns the tree root node
NodePtr RedBlackTree::getRoot() {
    return rootNode;
}

//returns null node
NodePtr RedBlackTree::getNullNode() {
    return nullNode;
}


NodePtr RedBlackTree::getSuccessor(NodePtr node) {
    //Successor is leftmost node in right subtree
    node = node->rightChild;
    while(node->leftChild != nullNode){
        node = node->leftChild;
    }
    return node;
}


//Prints the tree contents horizontally method used mostly for manual testing to verify whether nodes are correctly allocated
//spacer is a reference as it needs to travel with the function recursively
void RedBlackTree::printTree(const NodePtr node , const std::string& spacer , bool isLeftChild) {
    if(node != nullNode){
        //spacer decides the offset for each subsequent function call
        std::cout << spacer;
        //root will not have any offset hence this case exists
        if(!(node == rootNode)){
            if(isLeftChild){
                //top branch = left children
                std::cout<<"|---";
            }
            else{
                //bottom branch = right children
                std::cout<<"|___";
            }
        } else{
            //initial root node offset
            std::cout<<"---";
        }
        //facilitates the printing of the node in blue if its color property is black
        if(node->color == BLACK){
            const std::string printBlack = "\x1B[34mNode\033[0m\t\t";
            std::cout<<printBlack<<std::endl;
        }
        else{
            //prints node red to the screen
            const std::string printRed = "\x1B[31mNode\033[0m\t\t";
            std::cout<< printRed<<std::endl;
        }
        //recursively call this function on the left and right adding offsets to the spacer based whether the child is
        //left or right
        printTree(node->leftChild , spacer + (isLeftChild ? "│   " : "    "), true);
        printTree(node->rightChild ,spacer + (isLeftChild ? "│   " : "    ") , false);
    }
}

//methods fixes cases of double red nodes that are a result of bst insertion
void RedBlackTree::fixInsertion(NodePtr offender) {
    //offender = node that violates rb tree properties

    //if its a rootNode we return as all that needs to happen is its recoloring
    //this guard needs to be here as fix insertion is called after every insertion and if the root node gets to the
    //next case accessing its parent will result in a segmentation fault
    if(offender == rootNode){
        return;
    }
    //parent node of the offending node
    NodePtr offenderParent = offender->parent;

    if(offenderParent->color != RED){
        //no violation
        return;
    }

    //grandparent node of the offending node
    NodePtr offenderGrandParent = offender->parent->parent;

    //offender uncle
    NodePtr offenderUncle;

    if(offenderParent == offenderGrandParent->rightChild){
        offenderUncle = offenderGrandParent->leftChild;
    }
    else{
        offenderUncle = offenderGrandParent->rightChild;
    }

    if(offenderUncle->color == RED){
        reColor(offenderParent , offenderGrandParent , offenderUncle);
        fixInsertion(offenderGrandParent);
    }
    else if(offenderUncle->color == BLACK){
        //case uncle is black and both parent and child are left nodes "/"
        if(isLeftChild(offender) == true && isLeftChild(offenderParent) == true){
            swapColor(offenderParent);
            swapColor(offenderGrandParent);
            rightRotation(offenderGrandParent);
        }
            //case uncle is black and parent and child are right nodes "\"
        else if(isLeftChild(offender) == false && isLeftChild(offenderParent) == false){
            swapColor(offenderParent);
            swapColor(offenderGrandParent);
            leftRotation(offenderGrandParent);
        }
            //case uncle is black and  parent is left child is right "<"
        else if(isLeftChild(offenderParent) == true && isLeftChild(offender) == false){
            leftRotation(offenderParent);
            fixInsertion(offenderParent);
        }
            //case uncle is black and  parent is right child is left ">"
        else if(isLeftChild(offenderParent) == false && isLeftChild(offender) == true){
            rightRotation(offenderParent);
            fixInsertion(offenderParent);
        }
    }
    //recolors root node to black if any case resulted in being red this preserves the root is black property of the
    //red black tree
    rootNode->color = BLACK;
}

void RedBlackTree::deleteNode(NodePtr node) {
    //guard against passing null nodes
    if(node == nullNode){
        return;
    }
    //deletion of 0 children
    if(node->leftChild == nullNode && node->rightChild == nullNode ){
        if(node == rootNode){
            rootNode = nullNode;
            return;
        }
        if(isLeftChild(node)){
            node->parent->leftChild = nullNode;
            //fixDeletion(node->parent->leftChild , node->color);
        }
        else{
            node->parent->rightChild = nullNode;
            //fixDeletion(node->parent->rightChild , node->color);
        }

        delete node;
    }
    //deletion of 2 children
    else if(node->rightChild != nullNode && node->leftChild != nullNode){
        node->data = getSuccessor(node)->data;
        deleteNode(getSuccessor(node));
    }
    //deletion of one child
    else if(node->rightChild != nullNode || node->leftChild != nullNode){
        if(node->leftChild != nullNode){
            if(node == rootNode){
                rootNode = node->leftChild;
            }
            else if(isLeftChild(node)){
                node->parent->leftChild = node->leftChild;
                node->leftChild->parent = node->parent;
            }
            else {
                node->parent->rightChild = node->leftChild;
                node->leftChild->parent = node->parent;
            }
            //fixDeletion(node->leftChild , node->color);
        }
        else{
            if(node == rootNode){
                rootNode = node->rightChild;
            }
            else if(isLeftChild(node)){
                node->parent->leftChild = node->rightChild;
                node->rightChild->parent = node->parent;
            }
            else{
                node->parent->rightChild = node->rightChild;
                node->rightChild->parent = node->parent;
            }
            //fixDeletion(node->rightChild , node->color);
        }
        delete node;
    }
}

//recolor method swaps the argument node colors as per case recolor in fox insertion
void RedBlackTree::reColor(NodePtr parent , NodePtr grandParent , NodePtr uncle) {
    swapColor(parent);
    swapColor(uncle);
    swapColor(grandParent);
}

//left rotation method
void RedBlackTree::leftRotation(NodePtr node) {
    NodePtr swapNode = node->rightChild;
    node->rightChild = swapNode->leftChild;

    if(swapNode->leftChild != nullNode){
        swapNode->leftChild->parent = node;
    }
    swapNode->parent = node->parent;

    if(node->parent == nullptr){
        rootNode = swapNode;
    }
    else if(isLeftChild(node)){
        node->parent->leftChild = swapNode;
    }
    else{
        node->parent->rightChild = swapNode;
    }

    swapNode->leftChild = node;
    node->parent = swapNode;
}

//does everything left rotation does but inverse
void RedBlackTree::rightRotation(NodePtr node) {
    NodePtr swapNode = node->leftChild;
    node->leftChild = swapNode->rightChild;

    if(swapNode->rightChild != nullNode){
        swapNode->rightChild->parent = node;
    }
    swapNode->parent = node->parent;

    if(node->parent == nullptr){
        rootNode = swapNode;
    }
    else if(node == node->parent->rightChild){
        node->parent->rightChild = swapNode;
    }
    else{
        node->parent->leftChild = swapNode;
    }

    swapNode->rightChild = node;
    node->parent = swapNode;
}

//swaps the color of the target node if red -> black , black->red
void RedBlackTree::swapColor(NodePtr node) {
    if(node->color == RED){
        node->color = BLACK;
    }
    else{
        node->color = RED;
    }
}

//method to search tree based on data
NodePtr RedBlackTree::searchTree(std::string data) {
    //starting point for the search
    NodePtr currentNode = rootNode;

    //loop continues to traverse based on node data until it finds a the target node or a null node
    while(currentNode != nullNode){
        if(data > currentNode->data){
            currentNode = currentNode->rightChild;
        }
        else if(data < currentNode->data){
            currentNode = currentNode->leftChild;
        } else if(data == currentNode->data){
            return currentNode;
        }
    }
    //returns null node if node if the method doesnt find the requested node
    return nullNode;
}

//method checks if target node is the left child of its parent if result is false it can be assumed that it is the right child
bool RedBlackTree::isLeftChild(NodePtr node) {
    if(node->parent->leftChild == node){
        return true;
    }
    return false;
}

//fix tree to comply with rb tree requirements currently non functional
void RedBlackTree::fixDeletion(NodePtr problemNode, Color deletedColor) {

    if(deletedColor == RED){
        return;
    }
    else if(deletedColor == BLACK){
        //case 0 if the double black is the root
        if(problemNode == rootNode){
            return;
        }
        //required NodePtr for all cases pertaining to node deletion
        NodePtr problemParent = problemNode->parent;

        NodePtr problemSibling;
        Color leftChildOfSibling;
        Color rightChildOfSibling;

        if(problemParent->leftChild == problemNode){
            problemSibling = problemParent->rightChild;
        }
        else{
            problemSibling = problemParent->leftChild;
        }

        leftChildOfSibling = problemSibling->leftChild->color;
        rightChildOfSibling = problemSibling->rightChild->color;

        //case 1: replacement sibling is red
        if(problemSibling->color == RED){
            problemSibling->color = BLACK;
            problemParent->color = RED;

            if(isLeftChild(problemNode)){
                leftRotation(problemParent);
                problemSibling = problemParent->rightChild;
            }
            else{
                rightRotation(problemParent);
                problemSibling = problemParent->leftChild;
            }
            fixDeletion(problemNode , problemNode->color);
        }
            //case 2 both sibling and children black
        else if(problemSibling->color == BLACK && leftChildOfSibling == BLACK && rightChildOfSibling == BLACK){
            swapColor(problemSibling);
            problemNode = problemNode->parent;
            if(problemNode->color == RED){
                swapColor(problemNode);
                return;
            }
            else{
                fixDeletion(problemNode , problemNode->color);
            }
        }
            //case 3.1
        else if(problemSibling->color == BLACK && isLeftChild(problemNode) && leftChildOfSibling == RED && rightChildOfSibling == BLACK){
            problemSibling->leftChild->color = BLACK;
            problemSibling->color = RED;
            rightRotation(problemSibling);
            problemSibling = problemParent->rightChild;
            fixDeletion(problemNode , problemNode->color);
        }
            //case 3.2
        else if(problemSibling->color == BLACK && isLeftChild(problemNode) == false && leftChildOfSibling == BLACK && rightChildOfSibling == RED){
            problemSibling->rightChild->color = BLACK;
            problemSibling->color = RED;
            leftRotation(problemSibling);
            problemSibling = problemParent->leftChild;
            fixDeletion(problemNode , problemNode->color);
        }
            //case 4.1
        else if(problemSibling->color == BLACK && isLeftChild(problemNode) && rightChildOfSibling == RED){
            problemSibling->color = problemParent->color;
            problemParent->color = BLACK;
            problemSibling->rightChild->color = BLACK;
            leftRotation(problemParent);
        }
            //case 4.2
        else if(problemSibling->color == BLACK && isLeftChild(problemNode) == false && leftChildOfSibling == RED){
            problemSibling->color = problemParent->color;
            problemParent->color = BLACK;
            problemSibling->leftChild->color = BLACK;
            rightRotation(problemParent);
        }
    }
}


void RedBlackTree::isValidTreeInternals(NodePtr node , std::vector<NodePtr>& nodePath){
    if(node != nullNode){
        nodePath.push_back(node);
        //calls on rest of tree recursively
        isValidTreeInternals(node->leftChild , nodePath);
        isValidTreeInternals(node->rightChild, nodePath);
        //rolls back the node so alternative paths can use the same vector to output their path
        nodePath.pop_back();
    }
        //if the node is a leaf add it to the path vector
    else{
        //because recursion is used on both sides all paths return as doubles these if conditions make sure only one is added
        if(nodeVec.empty()){
            nodeVec.push_back(nodePath);
        }
        else if(nodeVec.back() != nodePath){
            nodeVec.push_back(nodePath);
        }
    }
}


bool RedBlackTree::isValidTreeAnalysis(std::vector<std::vector<NodePtr>>& nodeVec){
    bool isLastNodeRed = false;
    bool isThisNodeRed = false;
    int blackNodeNum = 0;
    std::vector<int> noOfBlackNodes;
    int firstBlackNodeNum = 0;

    //checks if root node is black
    if(rootNode->color != BLACK){
        std::cout<<"Root Not BLack Violation "<<std::endl;
        return false;
    }

    for(std::vector<NodePtr> n : nodeVec){
        for(NodePtr node : n){

            //checks the color of this node against red the aim here is to check this nodes property
            //and then pass it onto the previous node variable if both are true the tree has violated double red
            if(node->color == RED){
                isThisNodeRed = true;
            }
            else{
                isThisNodeRed = false;
            }

            if(isThisNodeRed == true && isLastNodeRed == true){
                std::cout<<"Double Red Violation "<<std::endl;
                return false;
            }
            if(node->color == BLACK){
                blackNodeNum++;
            }
            isLastNodeRed = isThisNodeRed;
        }
        noOfBlackNodes.push_back(blackNodeNum);
        isThisNodeRed = false;
        isLastNodeRed = false;
        blackNodeNum = 0;
    }

    for(int i : noOfBlackNodes){
        if(firstBlackNodeNum == 0){
            firstBlackNodeNum = i;
        }
        else if(firstBlackNodeNum != i){
            std::cout<<"Black Height of tree Violation "<<std::endl;
            return false;
        }
    }

    std::cout<<"Tree is Valid: Yes"<<std::endl;
    std::cout<<"Root Color: Black" <<std::endl;
    std::cout<<"Double Red Violation: No"<<std::endl;
    std::cout<<"Black Height of tree " << firstBlackNodeNum <<std::endl;
    return true;
}


bool RedBlackTree::isValidRBTree(){
    std::vector<NodePtr> vec;
    isValidTreeInternals(rootNode , vec);
    if(isValidTreeAnalysis(nodeVec)){
        nodeVec.clear();
        return true;
    }
    nodeVec.clear();
    return false;
}

//inorder print function
void RedBlackTree::inOrderPrint(NodePtr node) {
    if(node != nullNode){
        inOrderPrint(node->leftChild);
        std::cout<<node->data<<std::endl;
        inOrderPrint(node->rightChild);
    }
}