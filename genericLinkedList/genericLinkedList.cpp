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
            int length;

            /* Single Node Constructor */
            node<T>* create_node(T data)
            {
                node<T>* newNode = new node<T>();
                newNode->data = data;
                newNode->next = NULL;
                return newNode;
            }

            /* Return the Node of element by required index */
            node<T>* get(int index)
            {
                if(index > this->length - 1)
                    return NULL;
                node<T>* curr = head;
                for(int i = 0; i < index ; i++)
                    curr = curr->next;
                return curr;
            }

            /* Remove Node */
            void remove(node<T>* pNode)
            {
                node<T> **curr = &head;
                while((*curr) != pNode)
                    curr = &(*curr)->next;
                *curr = pNode->next;
                delete pNode;
            }

            /* Concating two lists */
            void concat(genericLinkedList<T> *other)
            {
                if (!other->head)
                    return;
                node<T> *curr = other->head;
                while (curr)
                {
                    node<T> *tmp = create_node(curr->data);
                    this->tail->next = tmp;
                    this->tail = this->tail->next;
                    curr = curr->next;
                }
                this->length+=other->length;
            }

        public:
            genericLinkedList<T>()
            {
                head = tail = NULL;
                this->length = 0;
            }

            /* Insert Node to the end of the list */
            int push_tail(T data) 
            {
                node<T> *ptr = create_node(data);
                if(!head){
                    head = ptr;
                    tail = head;   
                }
                else{
                    tail->next = ptr;
                    tail = ptr;
                }
                this->length++;
                return 1;
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

            /* Return the list head */
            node<T> * get_head(){
                return this->head;
            }

            /* Return the list tail */
            node<T> *get_tail()
            {
                return this->tail;
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


            /* Remove all the element with the required data - return the Count of the deleted elements: returns 0 for failure and count for success */
            int remove_by_data(T data)
            {
                node<T>* curr = search(data);
                int counter = 0;
                while(curr){
                    remove(curr);
                    curr = search(data);
                    this->length--;
                    counter++;
                }
                return counter;
            }

            /* Remove the element int the required index: returns -1 for failure and 1 for success */
            int remove_by_index(int index)
            {
                node<T> *temp = get(index);
                if(!temp)
                    return -1;
                remove(temp);
                this->length--;
                return 1;
            }

            /* Search Node by data of element */
            node<T>* search(T data)
            {
                node<T>* curr = head;
                while(curr)
                {
                    if(curr->data == data)
                        return curr;
                    curr = curr->next;
                }
                return NULL; 
            }

            /* Copy list */
            genericLinkedList<T> *copy_me(genericLinkedList<T> *list)
            {
                genericLinkedList<T> *newList = new genericLinkedList<T>();
                newList->push_head(this->head->data);
                node<T> *curr = this->head;
                while (curr)
                {
                    newList->push_tail(curr->data);
                    curr = curr->next;
                    newList->length++;
                }
                return newList;
            }

            /* Search Node by data, and replace it with a new element - it will replace the first Node that found */
            int search_and_replace(T newData, T oldData)
            {
                node<T>* curr = get(oldData);
                /* Check for Node existence */
                if(!curr)
                    return -1;
                curr->data = newData;
            }

            /* Implement the += operator */
            void operator+=(genericLinkedList<T>* list)
            {
                concat(list);
            }

            /* Implement the -= operator */
            void operator-=(genericLinkedList<T> *other)
            {
                if (!other->head)
                    return;
                int counter = 0;
                node<T> *curr = other->head;
                while (curr)
                {
                    remove_by_data(curr->data);
                    counter++;
                    curr = curr->next;
                }
                this->length -= counter;
            }

            /* Implement the - operator */
            genericLinkedList<T> *operator-(genericLinkedList<T> *list)
            {
                genericLinkedList<T> *newList = copy_me(list);
                *newList -= list;
                return newList;
            }

            /* Implement the + operator */
            genericLinkedList<T>* operator+(genericLinkedList<T>* list)
            {
                genericLinkedList<T> *newList = copy_me(list);
                *newList += list;
                return newList;
            }

            /* Implement the [] operator */
            T operator[](int index)
            {
                return get(index)->data;
            }

            /* Reversing the list */
            void reverse()
            {
                if(!head)
                    return;
                this->tail = head;
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

            /* Printing the list */
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
                node<T>* curr = head;
                node<T>* next;
                while (curr)
                {
                    next = curr->next;
                    delete curr;
                    curr = next;
                }
                this->head = NULL;
            }
    };
} // namespace gll