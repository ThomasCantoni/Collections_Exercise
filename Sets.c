#include "SetsDictionaryElements.h"


int main (int argc,char** args)
{
    set_table* new_set = set_table_new(10);
    char* key_to_insert = "test"; 
    set_insert(new_set,key_to_insert,strlen(key_to_insert));
    int TESTING = 104895;
    set_insert(new_set,&TESTING,GetDigitNumber(TESTING));
    key_to_insert = "Chiave"; 
    set_insert(new_set,key_to_insert,strlen(key_to_insert));
    key_to_insert = "Key"; 
    set_insert(new_set,key_to_insert,strlen(key_to_insert));
    key_to_insert = "Qualcosa"; 
    set_insert(new_set,key_to_insert,strlen(key_to_insert));
    key_to_insert = "ThomasCantoni"; 
    set_insert(new_set,key_to_insert,strlen(key_to_insert));
    key_to_insert = "LastKey"; 
    set_insert(new_set,key_to_insert,strlen(key_to_insert));
    print_set(new_set);
    printf("\n");
    
    //printf("AAAA");
    char* key_to_search = "ThomasCantoni"; 
    set_node* search = search_by_key(new_set,key_to_search);
    printf("Key succesfully found : %s \n",(char*)search->key);
    printf("\n");
   
    
    remove_by_key(new_set,"Qualcosa");
    printf("\n");

    char* key_duplicate = "Key"; 
    printf("INSERTING DUPLICATE KEY \n");
    set_node* check_if_null = set_insert(new_set,key_duplicate,strlen(key_duplicate));

    if(!check_if_null)
    {
        printf("DUPLICATE KEY NOT INSERTED\n");
    }
    print_set(new_set);


    remove_by_key(new_set,"Key");
    print_set(new_set);
    printf("\n");

}