#include <stddef.h> // required for NULL
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
static float rehash_treshold = 0.75; 
// if the table reaches 75% capacity then it rehashes everything

static float rehash_multiplier= 1.66; 
// if the rehashed table had 100 nodes it will be rebuilt with 166 nodes
 enum Type
{
    /* 
    0 = value is int , 
    1 = cast to double, 
    2 = to string DIFFERENT FROM s = short, 
    3 = to char, 
    f=float, 
    l=long long , 
    
    */
   Int,
   String,
   Float,
   Double,
   LongLong,
   Unsigned_Int 
};
typedef struct set_node
{
    void* key;                  //8 byte
    int index;                  //4 byte, 
                                //i like to keep the index of the node in the node itself to access it quickly
                                //whenever i have to move it
    size_t key_len;             //4
    struct set_node* next;      //8 byte
    enum Type value_ype;   
    void* value;                //8 byte

}set_node;

typedef struct set_table
{
    struct set_node** nodes;
    size_t hashmap_size;
    int collision_counter;
    
} set_table;
// size_t djb33x_hash(const char *key, const size_t keylen)
// {
//     size_t hash = 5381;
//     for (size_t i = 0; i < keylen; i++)
//     {
//         hash = ((hash << 5) + hash) ^ key[i];
//     }
//     return hash;
// }
set_table* rehash_all_entries2(set_table* received);



int GetDigitNumber(int number)
{
    int count=0;
    while(number!=0)
    {
        number=number/10;
        count++;
    }
    return count;
}
size_t djb33x_hash( void *key)
{
    size_t hash = 5381;
    char* key_as_string = (char* )key;
    int length = strlen(key_as_string);
    for (size_t i = 0; i < length; i++)
    {
        hash = ((hash << 5) + hash) ^ key_as_string[i];
    }
    return hash;
}
size_t calculate_index(set_table* table, void* key)
{
    //size_t key_len = strlen(key);
    size_t hash = djb33x_hash(key);
    size_t index = hash % table->hashmap_size;
    return index;
}
int check_duplicate(set_table* table, void* key)
{
    
    size_t index = calculate_index(table,key);
    if(!strcmp(table->nodes[index]->key,key))
    {
         
         return 1;
    } 
    return 0;
}



struct set_table *set_table_new(const size_t hashmap_size)
{
    struct set_table *table = malloc(sizeof(struct set_table)); //i am creating a new persistent object, so i
    // need to call malloc so that the table won't disappear when exiting the scope
   
    if (!table) //if i cannot allocate memory (for some reason) just abort and return null
    {
        return NULL; 
    }

    table->hashmap_size = hashmap_size;
    table->nodes = calloc(table->hashmap_size, sizeof(struct set_node *));
    //calloc is identical to malloc but clears the memory allocated, setting it to zero

    if (!table->nodes) //again, if i cannot allocate memory for some reason i just abort and return null
    {
        free(table);
        return NULL;
    }
    return table;
}

void print_set2(set_table* to_print,int show_NULLs)
{
    printf("\n table size : %i \n",(int)to_print->hashmap_size);
    for (int i=0;i<(int)to_print->hashmap_size;i++)
    {

        set_node* current_set_node = to_print->nodes[i];
        
        //set_node* current_key_node = current_set_node->next;
            //printf("TEST");
        if(current_set_node)
        {
            

            printf("Key at Index %i : %s  with internal node index: %i \n",i,(char*)current_set_node->key,current_set_node->index); 
            printf("Current node pointer %p \n",current_set_node); 
            if(current_set_node->next)
            {
                set_node* next_node = current_set_node->next;
                printf(" Collision failsafe node : %p  \n",(char*)next_node); 

                printf(" Value at failsafe node: %s \n\n",(char*)next_node->key);
            }
            else
            {
                 printf(" Next node is NULL, which means no collision occurred with this key\n\n"); 
            }


        }
        else if(show_NULLs >0)
        {
            printf("Main node at index %i was null \n",i); 
        }

        
    }
}
void print_set(set_table* to_print)
{
    print_set2(to_print,0);
}

set_node* search_by_key(set_table* to_examine,char* key_to_find)
{
   
    size_t index = calculate_index(to_examine,key_to_find);
    if(to_examine->nodes[index])
    {
        return to_examine->nodes[index] ;

    }
    return NULL;
}

void remove_by_key(set_table* table,void* key_to_remove)
{
    
    size_t index = calculate_index(table,key_to_remove);
    set_node* node_to_remove = table->nodes[index];
    if(node_to_remove)
    {
       // printf("\n INDEX %i \n",(int)index);
       if(node_to_remove->next)
       {

            set_node* replacer = node_to_remove->next;
            //printf("\nCRASH POINT 1%s : HASHMAP %i\n",(char*)key_to_remove,(int)table->hashmap_size);
            printf("\nRemoving collided node %p and replacing it with failsafe node: %p \n",(char*)key_to_remove,replacer->key);

            *node_to_remove = *replacer;
            node_to_remove->next = NULL;
            return;
       }
       else
       {
         //printf("\nCRASH POINT 2%s : HASHMAP %i\n",(char*)key_to_remove,(int)table->hashmap_size);
         free(table->nodes[index]);
         table->nodes[index] = NULL;
         printf("Key removed: %s \n",(char*)key_to_remove);
       }
       
    }
}

struct set_node *set_insert(struct set_table *table,  void *key, const size_t key_len)
{
    size_t hash = djb33x_hash(key);
    size_t index = hash % table->hashmap_size;
    printf("\n Index of new item with key %s : %i\n",(char*)key,(int)index);
    
    struct set_node *head = table->nodes[index];
    if (!head)  //if no collision then proceed normally
    {
        table->nodes[index] = malloc(sizeof(struct set_node));
        if (!table->nodes[index])
        {
            return NULL;
        }
        table->nodes[index]->key = key;
        table->nodes[index]->key_len = key_len;
        table->nodes[index]->next = NULL;
        table->nodes[index]->index = index;
        return table->nodes[index];
    }
    if(check_duplicate(table,key)>0)
    {
        printf("\n Duplicate key detected!   %s \n " , (char*)key);
        return NULL;
    }
    
    table->collision_counter ++;
    printf("\nCOLLISION DETECTED AT INDEX %i !\n",(int)index);
    printf("\nCOLLISION COUNTER : %i !\n\n",(int)table->collision_counter);
    if(head->next || table->collision_counter >= (float)(table->hashmap_size*rehash_treshold))
    {
         printf("\nToo many collisions found in the dictionary, rehashing all entries\n");
         printf("\n hashmap size : %i and collision counter %i\n",(int)table->hashmap_size,table->collision_counter);

         //table = rehash_all_entries(table);
         rehash_all_entries2(table);
         return set_insert(table,key,key_len);
         
         //index = calculate_index(table,key);
         

    }


    
    head = table->nodes[index];
    struct set_node *new_item = malloc(sizeof(struct set_node));
    if (!new_item)
    {
        return NULL;
    }
    new_item->key = key;
    new_item->key_len = key_len;
    new_item->index = index;
    new_item->next = NULL;
    struct set_node* tail = head;
    while (head)
    {
        
        tail = head;
        head = head->next;
    }
    tail->next = new_item;
    printf("NEW ITEM PTR %p \n",new_item);
    return tail;
}
set_table* realloc_set_table(set_table* to_extend, int node_number)
{
    ///set_table* received = to_extend;
    int old_size = to_extend->hashmap_size;
    size_t new_size = 1+ node_number*sizeof(set_node);
    //table->nodes = calloc(table->hashmap_size, sizeof(struct set_node *));
    set_node** old_node_ptr = to_extend->nodes;
    to_extend->nodes  = realloc(to_extend->nodes,new_size);
    //printf("\n %s ",(char*)to_extend->nodes[old_size +1]->key);
    printf ("\n old size : %d  \n",old_size);

    for (int i = 0; i < old_size; i++)
    {
        //printf("\n MANNAGGIA %s \n",to_extend->nodes[i]-> key);
       *to_extend->nodes[i] = *old_node_ptr[i];
       printf ("\n nodes processed: %d of %d \n",(int)i,node_number);
    }
    
    free(*old_node_ptr);
    //printf("\nAAAAAAAAAAAAAAAAAAAAAAA   %i",to_extend->nodes[new_size]);
    to_extend->hashmap_size = new_size;
    
    //printf("\n New size %llu  and actual hashmap size %llu",to_extend->hashmap_size,sizeof(to_extend->nodes));
    return to_extend;
}
set_table* rehash_all_entries2(set_table* to_rehash)
{
    ///set_table* received = to_extend;
    int old_size = to_rehash->hashmap_size;
    int new_node_number = old_size * rehash_multiplier;
    size_t new_size =new_node_number*sizeof(set_node);
    printf("\n old pointer =  %p",to_rehash->nodes);
    //table->nodes = calloc(table->hashmap_size, sizeof(struct set_node *));
    set_node** old_node_ptr = to_rehash->nodes;
    to_rehash->nodes  = calloc(new_node_number,new_size);
    to_rehash->hashmap_size = (int) new_node_number;
    printf("\n new pointer =  %p with new node: %i \n",to_rehash->nodes,new_node_number);
    for (int i = 0; i < old_size; i++)
    {
        printf("\n Moving all old nodes to new allocation. Loop number %i",i);
       // to_rehash->nodes[i] = old_node_ptr[i];
        set_node* to_move = old_node_ptr[i];
        if(to_move)
        {
            set_insert(to_rehash,to_move->key,to_move->key_len);
            
            set_node* failsafe_key = to_move->next;
            if(failsafe_key)
            {
                set_insert(to_rehash,failsafe_key->key,failsafe_key->key_len);
            }


        }
    }
    to_rehash->collision_counter =0;
    free(old_node_ptr);
    return to_rehash;
}
set_table* rehash_all_entries(set_table* to_rehash)
{
    //set_table* to_rehash = received;
    int original_size = to_rehash->hashmap_size;
    
    size_t new_size = (original_size*1.5);
    realloc_set_table(to_rehash,new_size);
    printf("\n !!!! table collision nodes = %llu",sizeof(to_rehash->nodes)/sizeof(to_rehash->nodes[0]));
    //printf("\n !!!!!!!!!new size %llu",to_rehash->hashmap_size);
    //i extend the dictionary by fifty percent of it's current length 
    for (int i = 0; i < original_size; i++)
    {
        if(to_rehash->nodes[i]) // if the node i want to move doesn't exist then i just skip a loop
        {
            set_node* to_move_elsewhere = to_rehash->nodes[i];
            //printf("\nCRASH POINT %s \n",(char*)to_move_elsewhere->key);
            printf("\n %i CRASH POINT CRASH POINT CRASH POINT CRASH POINT CRASH POINT \n",i);
            //printf("\n %s - %i \n",to_move_elsewhere->key,to_move_elsewhere->index);

            remove_by_key(to_rehash,to_move_elsewhere->key);

            set_node* node_inserted = set_insert(to_rehash,to_move_elsewhere->key,to_move_elsewhere->key_len);
            if(node_inserted)
            {
                    node_inserted->value = to_move_elsewhere->value;

            }

        }

    }
    return to_rehash;
    
}
