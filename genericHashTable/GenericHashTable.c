#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "GenericHashTable.h"

/*
@Written by: Asaf Joseph @ID: 203819065.
Description: Implementation of hash table under the right condition.
In the following file you will find the logic of the function mention at the header.
You will be able to easily add/remove/search object at your hash table with this program.
I hope you will find it usefull and easy to read.
P.S further documentation can be found down at the code. 
*/

/**"Private functions"**/
int expand(Table *table);
int addByHash(Table *table, Object *object, int hashKey);

Table *createTable(int size, int dType, int listLength) // Table "constructor", , Function will return NULL on memory allocation fail
{
    if (size < 0 || listLength < 0)
    {
        printf("Invalid table size, return NULL");
        return NULL;
    }
    if (dType != STR_TYPE && dType != INT_TYPE)
    {
        printf("Invalid table type, return NULL");
        return NULL;
    }
    Table *table = (Table *)malloc(sizeof(Table));
    if (table != NULL)
    {
        table->dType = dType;
        table->listLength = listLength;
        table->size = size;
        table->d = 1;
        table->currentElemets = 0;
        table->arr = (Object **)malloc(size * sizeof(Object *));
        if (table->arr == NULL)
        {
            printf("Hash array malloc has failed, return NULL\n");
            return NULL;
        }
        for (int i = 0; i < size; i++)
        {
            table->arr[i] = NULL;
        }
        return table;
    }
    printf("Table malloc has failed, return NULL\n");
    return NULL;
}

Object *createObject(void *data) // Object "constructor", Function will return NULL on memory allocation fail
{
    Object *object = (Object *)malloc(sizeof(Object));
    if (object != NULL)
    {
        object->currentListLength = 0;
        object->data = data;
        object->next = NULL;
        return object;
    }
    printf("Object malloc has failed, return NULL\n");
    return NULL;
}

int add(Table *table, void *data) // Function will return ERROR (-1) at memory allocation fail or adding fail
{
    if (data == NULL)
    {
        printf("Invalid data, return -1\n");
        return ERROR;
    }
    int hashKey = ERROR;
    Object *object;
    int addAttemp = ERROR;
    if (table->dType == INT_TYPE) // Hashing with int data
    {
        object = createObject((int *)data);
        if (object == NULL)
        {
            printf("Object malloc has failed, return -1 from add function\n");
            return ERROR;
        }
        hashKey = (table->d * intHashFun((int *)object->data, table->size / table->d));
    }
    else // Hashing with String data
    {
        char *stringObj = (char *)malloc(strlen((char *)data) * sizeof(char) + 1);
        if (stringObj == NULL)
        {
            printf("Object malloc has failed, return -1 from add function\n");
            return ERROR;
        }
        strcpy(stringObj, (char *)data);
        object = createObject((char *)stringObj);
        if (object == NULL)
        {
            printf("Object malloc has failed, return -1 from add function\n");
            return ERROR;
        }
        hashKey = (table->d * strHashFun(object->data, table->size / table->d));
    }
    while (addAttemp == ERROR)
    {
        if (table->arr[hashKey] != NULL)
        {
            if (table->currentElemets == table->listLength * table->size)
            {
                if (expand(table) == ERROR)
                {
                    printf("Realloc has failed, the return value is -1\n");
                    return ERROR; // realloc has failed
                }

                hashKey = (2 * hashKey);
            }
            else if (table->arr[hashKey]->currentListLength == table->listLength)
            {
                for (int i = hashKey + 1; i < hashKey + table->d; i++)
                {
                    addAttemp = addByHash(table, object, i);
                    if (addAttemp != ERROR)
                        return addAttemp;
                }
                if (expand(table) == ERROR)
                {
                    printf("Realloc has failed, the return value is -1\n");
                    return ERROR; // realloc has failed
                }
                hashKey = (2 * hashKey);
            }
            else
                addAttemp = addByHash(table, object, hashKey);
        }
        else
            addAttemp = addByHash(table, object, hashKey);
    }
    return addAttemp;
}

int addByHash(Table *table, Object *object, int hashKey) // private to handle the multiple request for adding
{
    if (table->arr[hashKey] == NULL && hashKey > ERROR)
    {
        table->arr[hashKey] = object;
        table->arr[hashKey]->currentListLength = 1;
        table->currentElemets++;
        return hashKey;
    }
    else
    {
        // If there is still place in the list, Add to the end
        if (table->arr[hashKey]->currentListLength < table->listLength)
        {
            Object *p = table->arr[hashKey];
            while (p->next)
            {
                p = p->next;
            }
            table->arr[hashKey]->currentListLength++;
            table->currentElemets++;
            p->next = object;
            return hashKey;
        }
    }
    return ERROR;
}

int expand(Table *table) // expending the table by factor 2, function will return -1 if it failed
{
    table->arr = (Object **)realloc(table->arr, 2 * table->size * (sizeof(Object *)));
    if (table->arr == NULL)
    {
        printf("Hash array malloc has failed, return -1 from expand function\n");
        return ERROR;
    }

    table->size = table->size * 2;
    table->d = 2 * table->d;
    for (int i = table->size / 2; i < table->size; i++) // Garbage collector
    {
        table->arr[i] = NULL;
    }
    for (int i = (table->size) / 2 - 1; i > 0; i--)
    {
        if (table->arr[i] != NULL)
        {
            table->arr[i * 2] = table->arr[i];
            table->arr[i] = NULL;
        }
    }
    return !ERROR;
}

int removeObj(Table *table, void *data) // removing object from the table, function will return -1 if it failed
{
    if (data == NULL)
    {
        printf("Invalid data, return -1\n");
        return ERROR;
    }
    int hashKey = ERROR;
    if (table->dType == INT_TYPE) // Hashing with int data
        hashKey = (table->d * intHashFun(data, table->size / table->d));
    else // Hashing with String data
        hashKey = (table->d * strHashFun(data, table->size / table->d));

    for (int i = hashKey; i < hashKey + table->d; i++)
    {
        Object *myNode = table->arr[i], *previous = NULL;
        while (myNode != NULL)
        {
            if (isEqual(table->dType, myNode->data, data) == EQUAL)
            {
                table->arr[i]->currentListLength--;
                if (previous == NULL)
                    table->arr[i] = myNode->next;
                else
                    previous->next = myNode->next;
                freeObject(myNode, table->dType); //need to free up the memory to prevent memory leak
                table->currentElemets--;
                return i;
            }
            previous = myNode;
            myNode = myNode->next;
        }
    }
    return ERROR;
}

int intHashFun(int *key, int origSize) // Hashing the int
{
    return MOD(*key, origSize);
}

int strHashFun(char *key, int origSize) // Hashing the string
{
    int hashKey = 0;
    for (int i = 0; i < strlen(key); i++)
        hashKey += (int)key[i];
    return hashKey % origSize;
}

int isEqual(int type, void *data1, void *data2) // determine whatever two objects are equal
{
    if (data1 == NULL || data2 == NULL)
    {
        printf("Invalid data to compare, return -1\n");
        return ERROR;
    }
    if (type == INT_TYPE) // Int Compare
    {
        if (*(int *)data1 == *(int *)data2)
            return EQUAL;
        else
            return NOT_EQUAL;
    }
    else //String Compare
    {
        return strcmp((char *)data1, (char *)data2);
    }
}

Object *search(Table *table, void *data) // searching for an object at the hash table
{
    if (data == NULL)
    {
        printf("Invalid data, return NULL\n");
        return NULL;
    }
    int hashKey = ERROR;
    if (table->dType == INT_TYPE) // Hashing with int data
        hashKey = (table->d * intHashFun(data, table->size / table->d));
    else // Hashing with String data
        hashKey = (table->d * strHashFun(data, table->size / table->d));

    Object *object;
    for (int i = hashKey; i < hashKey + table->d; i++)
    {
        object = table->arr[i];
        while (object)
        {
            if (isEqual(table->dType, object->data, data) == 0)
                return object;
            object = object->next;
        }
    }
    return NULL;
}

void printTable(Table *table) // table print
{
    for (int i = 0; i < table->size; i++)
    {
        if (table->arr[i] != NULL)
        {
            printf("[%d]\t", i);
            Object *p = table->arr[i];
            while (p)
            {
                if (table->dType == INT_TYPE)
                {
                    if (p->next == NULL)
                        printf("%d", *(int *)p->data);
                    else
                        printf("%d \t-->\t ", *(int *)p->data);
                }
                else
                {
                    if (p->next == NULL)
                        printf("%s", (char *)p->data);
                    else
                        printf("%s \t-->\t ", (char *)p->data);
                }
                p = p->next;
            }
            printf("\n");
        }
        else
            printf("[%d]\t\n", i);
    }
}

void freeTable(Table *table) // free all the table
{
    if (table == NULL)
    {
        return;
    }
    for (int i = 0; i < table->size; i++)
    {
        if (table->arr[i] != NULL)
        {
            Object *p = table->arr[i];
            Object *temp;
            while (p)
            {
                temp = p;
                p = p->next;
                freeObject(temp, table->dType);
            }
        }
    }
    free(table->arr);
    free(table);
}

void freeObject(Object *obj, int type) // free object
{
    if (type == STR_TYPE) // free String
    {
        free(obj->data);
        free(obj);
    }
    else // free Int
        free(obj);
}
