#include <iostream>
#define SUCCESS 1
#define FAILURE -1
using namespace std;

/* Define the generic node */
template <class T>
struct node
{
    node<T> *next;
    T data;
};

namespace gll
{
    template<class T>
    class genericLinkedList
    {
        private:

            node<T> *head;
            node<T> *tail;
            int length = 0;

            /* Single Node Constructor */
            node<T>* create_node(T data)
            {
                node<T>* newNode = new node<T>;
                newNode->data = data;
                newNode->next = NULL;
                return newNode;
            }

        public:
            genericLinkedList<T>()
            {
                head = tail = NULL;
            }

            /* Insert Node to the end of the list */
            int insert(T data) 
            {
                if(!head){
                    head = create_node(data);
                    tail = head;
                    length++;
                }
                else{
                    node<T>* ptr = create_node(data);
                    tail->next = ptr;
                    tail = ptr;
                    length++;
                }
            }

            /* Push Node to the head of the list */
            int push_head(T data){
                if(!head){
                    insert(data);
                    return 1;
                }
                node<T>* newNode = create_node(data);
                newNode->next = head;
                head = newNode;
                return 1;
            }

            /* Return the list length */
            int get_list_length(){
                return this->length;
            }

            /* Insert Node to the the required place by index */
            int set_by_index(T data, int index)
            {
                if(index > length - 1){
                    cout << "List length: " << length <<  " is less then required index [0-N]: " << index << endl;
                    return -1;
                }
                
                if(index == 0 || !head){
                    push_head(data);
                    return 1;
                }

                node<T>* curr = head;
                for(int i = 0 ; i < index ; i++){
                    curr = curr->next;
                }
                node<T>* newNode = create_node(data);
                newNode->next = curr->next;
                curr->next = newNode;
                return 1;
            }
            
            T get(int index)
            {

            }

            int remove_by_data(T data)
            {

            }

            int remove_by_index(int index)
            {

            }

            bool search(T data)
            {

            }

            int search_and_replace(T data)
            {

            }

            T operator[](int index)
            {

            }

            void reverse()
            {

            }

            void print_list()
            {
                node<T>* temp = head;
                while(temp->next != NULL){
                    cout << temp->data << " ---> ";
                    temp = temp->next;
                }
                cout << temp->data << endl;
            }

            ~genericLinkedList()
            {
                node<T>* p = head;
                node<T>* temp;
                while(p){
                    temp = p;
                    p = p->next;
                    delete temp;
                }
            }
    };
} // namespace gll