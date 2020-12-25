#include<iostream>
using namespace std;

class BST
{
private:

    // defines the node
    struct node
    {
        int key;
        node* left;
        node* right;
        node(int key):key(key),left(nullptr),right(nullptr) {}
    };

    // root pointer
    node* root;

    // creates a new node with two placeholder child nodes
    // returns a pointer to the node
    node* getNewNode(int key)
    {
        node* t;
        t = new node(key);
        t->left = new node(INT_MIN);
        t->right = new node(INT_MAX);
        return t;
    }

    // inserts a node with key, into the BST rooted at root
    node* insertNode(node* root, int key)
    {
        // insert the node by first 'deleting' the placeholder node
        if (isPlaceholderNode(root)){
            delete(root);
            return getNewNode(key);
        }

        // to determine a place to insert the node, traverse left
        if (key < root->key){
            root->left = insertNode(root->left, key);
        }
        else{ // or traverse right
            root->right = insertNode(root->right, key);
        }
        return root;
    }

    // returns true if node is a placeholder node
    //    returns false if it isn't
    bool isPlaceholderNode(node* n)
    {
        return n->key == INT_MAX || n->key == INT_MIN;
    }


    node* minValueNode(node* root)
    {
        node* current = root;

        //search the leftmost tree
        while (!isPlaceholderNode(current) &&  !isPlaceholderNode(current->left)) current = current->left;
        return current;
    }

    node* deleteNode(node* root, int key)
    {
        // node not found
        if(isPlaceholderNode(root))
            return root;


        if(key < (root->key))
        {
            root->left = deleteNode((root->left), key);
        }
        else if (key > (root->key))
        {
            root->right = deleteNode((root->right), key);
        }
        else{   // node found

            // case: node has zero / one right child node
            if (isPlaceholderNode(root->left))
            {
                node *temp = root->right;
                delete(root);
                return temp;
            }
            // case: node has one left-child node
            else if (isPlaceholderNode(root->right))
            {
                node *temp = root->left;
                delete(root);
                return temp;
            }

            // case: node with both children
            //      get successor and then delete the node
            node* temp = minValueNode(root->right);

            // Copy the inorder successor's content to this node
            root->key = temp->key;

            // Delete the inorder successor
            root->right = deleteNode(root->right, temp->key);
        }
        return root;
    }

    // searches for the node with key
    bool search(node* root, int key){
        if(!isPlaceholderNode(root)){
            if(root->key == key){ // found
                return true;
            }
            else{
                if(root->key > key){
                    // look in left-subtree
                    return search(root->left, key);
                }
                else{
                    // look in right-subtree
                    return search(root->right, key);
                }
            }
        }
        else{
            // empty sub-tree
            return false;
        }
    }

    // inorder traversal in BST rooted at root
    void inorder(node *root)
    {
        if (!isPlaceholderNode(root))
        {
            inorder(root->left); // left sub-tree
            cout << (root->key) << " "; // process node
            inorder(root->right); // right sub-tree
        }
    }

public:

    BST():root(nullptr) {}

    void initializeBST()
    {
        // arbitrarily used INT_MAX instead of INT_MIN
        //    for root node it shouldn't matter
        root = new node(INT_MAX);
    }

    // inserts a node with key
    void insertNode(int key)
    {
        root = insertNode(root, key);
    }

    // prints the BST
    void printTree()
    {
        inorder(root);
        cout << endl;
    }

    // deletes the node with key, does nothing if such a node isn't found
    void deleteNode(int key){
        root = deleteNode(root, key);
    }

    // searches for node with key,
    // returns true if found, false otherwise
    bool search(int key){
        if(isPlaceholderNode(root)) return false;
        return search(root, key);
    }

};

int main()
{
    BST bst;
    bst.initializeBST();
    bst.insertNode(9);
    bst.insertNode(0);
    bst.insertNode(12);
    bst.insertNode(2);

    /*
                9
              /  \
            0     12
          /  \   / \
         x   2  x   x
                       (x- placeholder node)
    */

    bst.printTree();  // 0 2 9 12

    cout << "Searching for 0: ";
    if(bst.search(0)) cout << "true" << endl;
    else cout << "false" << endl;

    cout << "Searching for 33: ";
    if(bst.search(33)) cout << "true" << endl;
    else cout << "false" << endl;

    bst.deleteNode(9);
    cout << "after deleting 9: ";
    bst.printTree(); // 0 2 12

    bst.deleteNode(0);
    cout << "after deleting 0: ";
    bst.printTree(); // 2 12


    return 0;
}
