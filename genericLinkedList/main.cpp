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
    list.push_tail(5);
    list.push_tail(4);
    list.push_tail(3);
    list.push_tail(2);
    list.push_tail(6);
    list.push_tail(7);
    list.push_tail(8);
    list.set_by_index(9,7);
    list.set_by_index(10,1);
    list.set_by_index(11,0);
    list.print_list();
    list.reverse();
    list.print_list();
    cout << list[5] << endl;
    cout << "Tester finished successfuly, bye bye :-)" << endl;
    return EXIT_SUCCESS;
}