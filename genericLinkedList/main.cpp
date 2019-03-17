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
    list.push_tail(5);
    list.push_tail(5);
    list.push_tail(5);
    list.set_by_index(9,7);
    list.set_by_index(10,1);
    list.set_by_index(11,0);
    cout << "Testing the seters functions: " << endl;
    list.print_list();
    list.reverse();
    cout << "Testing the reverse funcion: " << endl;
    list.print_list();
    cout << "Testing the [] operator: " << list[5] << endl;
    list.remove_by_index(0);
    cout << "Testing the remove by index function: " << endl;
    list.print_list();
    cout << "Testing the search and replace function: " << endl;
    list.search_and_replace(100,5);
    list.print_list();
    cout << "Testin the remove by data function, Deleted elements num: "<< list.remove_by_data(5) << endl;
    list.print_list();
    cout << "Tester finished successfuly, bye bye :-)" << endl;
    return 1;
}