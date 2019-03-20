#include <iostream>
#include <bits/stdc++.h>
#define WHITESPACE 2

using namespace std;

/* Define the generic node */
template <class T>
struct node
{
    node<T> *left;
    node<T> *right;
    T data;
};

namespace bt
{
    template <class T>
    class binaryTree
    {
        private:

            node<T> *root;
            int depth;

            /* Create a single Node */
            node<T> *create_node(T data)
            {
                node<T> *newNode = new node<T>();
                newNode->data = data;
                newNode->left = NULL;
                newNode->right = NULL;
                return newNode;
            }

            /* Iterate over the tree and free free resources */
            void destrucRecursive(node<T>* pointer)
            {
                if(pointer)
                {
                    destrucRecursive(pointer->left);
                    destrucRecursive(pointer->right);
                    delete pointer;
                }
            }

            /* Return the node with the min value */
            node<T>* getMin(node<T>* pointer)
            {
                while(pointer->left)
                    pointer = pointer->left;
                return pointer;
            }

            /* Print the node by level */
            void printByLevel(node<T> *root, int space)
            {
                if (root)
                {
                    space += WHITESPACE;
                    printByLevel(root->left, space);
                    cout << endl;
                    for (int i = WHITESPACE; i < space; i++)
                        cout << " ";
                    cout << root->data << endl;
                    
                    printByLevel(root->right, space);
                }
            }

        public:
            binaryTree<T>()
            {
                this->root = NULL;
                this->depth = 0;
            }

            /* Insert Node to the tree */
            int insert(T data)
            {
                if(!this->root)
                {
                    this->root = create_node(data);
                }
                else
                {
                    node<T> *iterarateble = this->root;
                    node<T> *parent;
                    while (iterarateble)
                    {
                        parent = iterarateble;
                        iterarateble = data < iterarateble->data ? iterarateble->left : iterarateble->right;
                    }
                    data < parent->data ? parent->left = create_node(data) : parent->right = create_node(data);
                }
                return 1;
            }

            /* Return the depth of the tree */
            int getDepth(node<T> *root)
            {
                if (!root)
                    return 0;
                else
                {
                    int left = getDepth(root->left);
                    int right = getDepth(root->right);
                    if (left > right)
                        return left + 1;
                    return right + 1;
                }
            }

            /* Beauty version for Tree printing */
            void printBeauty(node<T> *root)
            {
                if(root)
                {
                    printByLevel(root, 10);
                }
            }

            /* Delete Node from the tree */
            node<T> *remove(T data, node<T> *root)
            {
                if (!root)
                    return root;
                if (data < root->data)
                    root->left = remove(data , root->left);
                else if (data > root->data)
                    root->right = remove(data, root->right);
                else
                {
                    if (!root->left)
                    {
                        node<T> *temp = root->right;
                        delete root;
                        return temp;
                    }
                    else if (!root->right)
                    {
                        node<T> *temp = root->left;
                        delete root;
                        return temp;
                    }
                    else
                    {
                        node<T> *temp = getMin(root->right);
                        root->data = temp->data;
                        root->right = remove(temp->data, root->right);
                    }
                }
                return root;
            }

            /* Return the root pointer */
            node<T> *get_root()
            {
                return this->root;
            }

            /* Root setter */
            node<T> *set_root(node<T>* root)
            {
                this->root = root;
            }

            /* Searching for required data */
            node<T> *search(T data, node<T> *root)
            {
                node<T> *iterate = root;
                if (iterate)
                {
                    if (data == iterate->data)
                        return iterate;
                    data > iterate->data ? search(data, iterate->right) : search(data, iterate->left);
                }
                else
                    return NULL;
            }

            /* Inorder printing */
            void inorderPrint(node<T> *root)
            {
                if (root != NULL)
                {
                    inorderPrint(root->left);
                    cout << root->data << " ";
                    inorderPrint(root->right);
                }
            }

            /* Preorder printing */
            void preorderPrint(node<T>* root)
            {
                if (root != NULL)
                {                               
                    cout << root->data << " ";  
                    preorderPrint(root->left);  
                    preorderPrint(root->right); 
                }
            }

            /* Postorder printing */
            void postorderPrint(node<T> *root)
            {
                if (root != NULL)
                {
                    postorderPrint(root->left);
                    postorderPrint(root->right);
                    cout << root->data << " ";
                }
            }

            ~binaryTree()
            {
                destrucRecursive(this->root);
            }
    };
}