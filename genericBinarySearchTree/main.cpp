/*
*   Main file for checking the binary tree librery
*   All right reserved to @Asaf Joseph
*   Free for USE
*/

#include "binaryTree.cpp"

using namespace bt;
using namespace std;

int main(int argc, const char *argv[])
{
    binaryTree<int> root;
    root.insert(1);
    root.insert(2);
    root.insert(4);
    root.insert(5);
    root.insert(3);
    root.insert(6);

    cout << "In Order:"  << endl;
    root.inorderPrint(root.get_root());
    cout << endl;
    cout << "Pre Order:" << endl;
    root.preorderPrint(root.get_root());
    cout << endl;
    cout << "Post Order:" << endl;
    root.postorderPrint(root.get_root());
    cout << endl;

    node<int> *temp = root.search(6, root.get_root());
    cout << "Search function: "  << endl;
    if(temp)
        cout << temp->data;
    else
        cout << "Not found";
    cout << endl;
    cout << "Print pre removal tree:";
    root.printBeauty(root.get_root());
    root.set_root(root.remove(1, root.get_root()));
    cout << "Print post removal tree:";
    root.printBeauty(root.get_root());
    return 1;
}