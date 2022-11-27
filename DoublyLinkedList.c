#include <stddef.h> // required for NULL
#include <stdio.h>
#include <stdlib.h>
#include "LinkedListElements.h"

list_double_node* list_get_tail(list_double_node** head)
{
    list_double_node* current_node = *head; //this means first node of the linkedlist when written like this
    list_double_node* last_node = NULL;
    while (current_node)
    {
        last_node = current_node;
        current_node = current_node->next;
    }
    return last_node;
}

struct list_double_node *list_append(struct list_double_node **head, struct list_double_node *item)
{
    struct list_double_node *tail = list_get_tail(head);
    if (!tail)
    {
        *head = item;
    }
    else
    {
        tail->next = item;
    }
    item->prev = tail;
    item->next = NULL;
    return item;
}
string_item_double* string_item_new(const char* string)
{
    string_item_double* item = malloc(sizeof(string_item)); 
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
list_double_node* remove_node(struct list_double_node** head,struct list_double_node* item_to_replace)
{
    
    list_double_node* current_node = *head;
    list_double_node* next_node= current_node->next;
    while(current_node->next)
    {
        //printf("current: %p \n",current_node);
        if(next_node == item_to_replace)
        {
            list_double_node* node_after= next_node->next;
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


void add_after(struct list_double_node **head, struct list_double_node* item,struct list_double_node* after_this_node)
{
    list_double_node* current_node = *head; //this means first node of the linkedlist when written like this
           
    while (current_node)
    {
          
        if(current_node == after_this_node)
        {
            list_double_node* current_next_node;
            current_next_node = current_node->next;
            current_node->next = item;
            item->prev = current_node;
            item->next = current_next_node;
            if(current_next_node)
            {
                current_next_node->prev = item;
            }
            
           // printf("Success");
            return;
        }
       
        current_node = current_node->next;
    }
    
}
void add_before(struct list_double_node **head, struct list_double_node* item,struct list_double_node* before_this_node)
{
    list_double_node* current_node = *head; //this means first node of the linkedlist when written like this
           
    while (current_node)
    {
            
        if(current_node == before_this_node)
        {
            list_double_node* current_prev_node;
            current_prev_node = current_node->prev;
            current_node->prev = item;
            item->next = current_node;
            item->prev = current_prev_node;
            if(current_prev_node)
            {
                current_prev_node->next = item;
            }
            
            printf("Success");
            return;
        }
       
        current_node = current_node->next;
    }
    
}
#define NEW_STRING_NODE(str) string_item_new(str)
#define APPEND(linkedList,NewString) list_append((list_double_node**)&linkedList,&(NEW_STRING_NODE(NewString))->node)

int main(int argc,char** args)
{
    string_item_double* my_linked_list = NULL;
    
  
    APPEND(my_linked_list,"Hello World");
    APPEND(my_linked_list,"LET'S GOOOOOOOO");
    APPEND(my_linked_list,"Test01");

    string_item_double* newString =  string_item_new("Test002");
    list_append((list_double_node**) &my_linked_list, &newString->node);
    
    string_item_double* node_to_add_after_another = string_item_new("ADD THIS AFTER TEST 02");
    add_after((list_double_node**) &my_linked_list, &node_to_add_after_another->node, &newString->node);


    string_item_double* node_to_add_before_another = string_item_new("ADD THIS BEFORE TEST 02");
    add_before((list_double_node**) &my_linked_list, &node_to_add_before_another->node, &newString->node);

    
    //remove_node((list_double_node**) &my_linked_list,&newString->node);

    APPEND(my_linked_list,"Last Item of the LinkedList");
    

    string_item_double *string_item = my_linked_list;
    while (string_item)
    {
        printf("%s\n", string_item->string);
        string_item = (struct string_item_double *)string_item->node.next;
    }
    return 0;
}