#include <stddef.h> // required for NULL
#include <stdio.h>
#include <stdlib.h>
#include "LinkedListElements.h"


list_node* list_get_tail(list_node** head)
{
    list_node* current_node = *head; //this means first node of the linkedlist when written like this
    list_node* last_node = NULL;
    while (current_node)
    {
        last_node = current_node;
        current_node = current_node->next;
    }
    return last_node;
}

list_node* list_append(struct list_node** head,struct list_node* item)
{
    list_node* tail = list_get_tail(head);
    if (!tail) //if linkedlist is empty then the item becomes the head
    {
        *head = item;
    }
    else //else the item gets appended after the tail
    {
        tail->next = item;
    }
    item->next = NULL; //next node must be null
    return item;
}

list_node* list_pop( list_node** head)
{
    list_node* current_node = *head;
    if (!current_node)
    {
        return NULL;
    }
    *head = (*head)->next;
    current_node->next = NULL;
    return current_node;
}
string_item* string_item_new(const char* string)
{
    string_item* item = malloc(sizeof(string_item)); 
    // i need to create a new string_item so i need 
    // to allocate an amount of memory equal to the byte size of string_item
    // i dont need to allocate memory for the string because i just need the pointer (8 byte) 
    if (!item)
    {
        return NULL;
    }
    item->string = string;
    return item;
}
list_node* remove_node(struct list_node** head,struct list_node* item_to_replace)
{
    
    list_node* current_node = *head;
    list_node* next_node= current_node->next;
    while(current_node->next)
    {
        
        if(next_node == item_to_replace)
        {
            list_node* node_after= next_node->next;
            next_node->next = NULL;
            current_node->next = node_after;
            free(next_node);
            return current_node;
        }
        current_node = next_node;
        next_node = current_node->next;
    }
    return current_node;
    
}
#define NEW_STRING_NODE(str) string_item_new(str)
#define APPEND(linkedList,NewString) list_append((list_node**)&linkedList,&(NEW_STRING_NODE(NewString))->node);
int main(int argc,char** args)
{
    // string_item* my_linked_list = NULL;
    // list_append((list_node**) &my_linked_list, ( list_node *)string_item_new("Hello World"));
    // list_append((list_node**) &my_linked_list, ( list_node *)string_item_new("Test001"));
    // list_append((list_node**) &my_linked_list, ( list_node *)string_item_new("Test002"));
    // list_append((list_node**) &my_linked_list, ( list_node *)string_item_new("Last Item of the Linked List"));
    string_item* my_linked_list = NULL;
    
  
    APPEND(my_linked_list,"Hello World");
    APPEND(my_linked_list,"IS IT WORKING");
    APPEND(my_linked_list,"Test01");

    string_item* newString =  string_item_new("Test002");
    list_append((list_node**) &my_linked_list, &newString->node);

    remove_node((list_node**) &my_linked_list,&newString->node);

    APPEND(my_linked_list,"Last Item of the LinkedList");
    
    string_item * string1 = my_linked_list;
    while (string1)
    {
        printf("%s\n", string1->string);
        string1= (struct string_item *)string1->node.next;
    }
     invert_LinkedList((list_node**) &my_linked_list);
    

    printf("\n#####################################\n");
    struct string_item* string = my_linked_list;
    
    PrintList(my_linked_list);
    
    
    return 0;
}