/*
*   Main file for checking the generic linked list librery
*   All right reserved to @Asaf Joseph
*   Free for USE
*/
#include "genericLinkedList.cpp"

using namespace gll;
using namespace std;

int main(int argc, const char* argv[])
{
    genericLinkedList<int> list;
    list.insert(5);
    list.insert(4);
    list.insert(3);
    list.insert(2);
    list.insert(6);
    list.insert(7);
    list.insert(8);
    list.set_by_index(9,6);
    list.set_by_index(10,1);
    list.set_by_index(11,0);
    list.print_list();
    cout << "Tester finished successfuly, bye bye :-)" << endl;
    return EXIT_SUCCESS;
}