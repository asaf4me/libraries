#include <iostream>
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
            int push_tail(T data) 
            {
                if(!head){
                    head = create_node(data);
                    tail = head;
                    this->length++;
                }
                else{
                    node<T>* ptr = create_node(data);
                    tail->next = ptr;
                    tail = ptr;
                    this->length++;
                }
            }

            /* Push Node to the head of the list */
            int push_head(T data){
                if(!head){
                    push_tail(data);
                    return 1;
                }
                node<T>* newNode = create_node(data);
                newNode->next = head;
                head = newNode;
                this->length++;
                return 1;
            }

            /* Return the list length */
            int get_list_length(){
                return this->length;
            }

            /* Insert Node to the the required place by index */
            int set_by_index(T data, int index)
            {   
                if(index == 0 || !head){
                    push_head(data);
                    return 1;
                }
                
                node<T>* curr = head;
                for(int i = 0 ; i < index - 1 ; i++){
                    curr = curr->next;
                }

                node<T>* newNode = create_node(data);
                newNode->next = curr->next;
                curr->next = newNode;
                this->length++;

                if( index == this->length - 1)
                    tail = newNode;
                return 1;
            }
            
            /* Return the data of element by required index */
            T get(int index)
            {
                if(index > this->length - 1)
                    return -1;
                node<T>* curr = head;
                for(int i = 0; i < index ; i++)
                    curr = curr->next;
                return curr->data;
            }

            int remove_node(node<T>* node)
            {

            }

            int remove_by_data(T data)
            {

            }

            int remove_by_index(int index)
            {

            }

            /* Search node by data of element */
            bool search(T data)
            {
                node<T>* curr = head;
                while(curr)
                {
                    if(curr->data == data)
                        return true;
                }
                return false; 
            }

            /* Search node by data, and replace it with a new element */
            int search_and_replace(T data)
            {

            }

            /* Remove existing element from required index and replace it with a new element */
            int remove_and_replace(int index)
            {

            }

            genericLinkedList concat(genericLinkedList list_1, genericLinkedList list_2)
            {

            }

            // genericLinkedList operator+(genericLinkedList list_1, genericLinkedList list_2)
            // {
            //     return concat(list_1, list_2);
            // }

            T operator[](int index)
            {
                return get(index);
            }

            void reverse()
            {
                if(!head)
                    return;
                node<T>* curr = head;
                node<T>* prev = NULL;
                node<T>* next = NULL;
                while(curr){
                    next = curr->next;
                    curr->next = prev;
                    prev = curr;
                    curr = next;
                }
                head = prev;
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