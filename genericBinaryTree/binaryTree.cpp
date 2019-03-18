#include <iostream>
#include <bits/stdc++.h>

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
                node<T> *newNode = new node<T>;
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
                this->depth++;
                return 1;
            }

            int remove(T data, node<T> *root)
            {
                node<T> *iterate = root;
                if (!iterate)
                    return -1;
                if (iterate->data == data)
                {
                    if (!iterate->left || !iterate->right)
                        delete iterate;
                    else
                    {

                    }
                    this->depth--;
                    return 1;
                }
                data > iterate->data ? remove(data, root->right) : remove(data, root->left);
            }

            /* Return the root pointer */
            node<T> *get_root()
            {
                return this->root;
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