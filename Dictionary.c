#include "SetsDictionaryElements.h"

set_node* DictionaryInsert(set_table* table, void* key,void* element,enum Type TypeOfValue)
{
    //printf("%i\n",*((int*)element));
    int num = strlen((char*)key);
    set_node* dictionary_node = set_insert(table,key,num);
    printf("HHHHHHHHHHHHHaaaaaaaaHHHHHHHH%llu",table->hashmap_size);
    dictionary_node->value = element;
    dictionary_node->value_ype = TypeOfValue;
    return dictionary_node;
    
}
void* DictionaryGetValue(set_table* table,void* key)
{
    set_node* found = search_by_key(table,key);
    if(found)
    {
        enum Type type= found->value_ype;
        switch(type )
        {
            case Int:
                return (int*) found-> value;
                break;
            case String:
                return (char*)found->value;
                break;
            // case Char:
            //     return (char)found->value;
            //     break;
            case Float:
                return (float*)found->value;
                break;
            case Double:
                return (double*) found->value;
                break;
            case LongLong:
                return (long long*) found-> value;
                break;
            case Unsigned_Int:
                return (unsigned int*) found-> value;
                break;
        }

        
        
    }
    return NULL; 

}

void test(set_table* test)
{
   test->hashmap_size = 666;
   realloc(test,666);
}

int main (int argc,char** args)
{
    // creating a new dictionary
    set_table* new_set = set_table_new(100);

   
    // strings as key, strings as value
    char* key_to_insert = "test1234"; 
    char* string_to_insert = "SomethingSomething";
    DictionaryInsert(new_set,key_to_insert,string_to_insert, Int);

    DictionaryInsert(new_set,"&si","test_value", Int);


    //string as key, int as value
    key_to_insert = "BBB"; 
    int value_to_insert = 666;
    DictionaryInsert(new_set,key_to_insert,&value_to_insert, Int);


    //long as key, long as value
    long long  large_number = 9999999999;
    DictionaryInsert(new_set,&large_number,&large_number,LongLong);

    // READING THE VALUES

    //reading long
    long long* longlong_ptr = DictionaryGetValue(new_set,&large_number);
    long long  longlong_val = *longlong_ptr;
    printf("Extracted longlong : %lld \n",longlong_val);

    //reading string
    char* extracted_string = DictionaryGetValue(new_set,"&si");
    printf("Extracted string: %s \n",extracted_string);

    //reading string
    int* extracted = DictionaryGetValue(new_set,"BBB");
    printf("\nInteger Extracted : %i\n\n", *extracted);

    //removing a key
    remove_by_key(new_set,"BBB");
    
    //printing all keys 
    print_set(new_set);
    printf("Program executed succesfully");
    return 0;
    // REHASHING NON FUNZIONA

    /*
    printf("\n##########################################\n");
    printf("Collision rehashing test, New Table created ");
    printf("\n##########################################\n");

    set_table* new_table_collision = set_table_new(2); // low size to increase likelyhood of collisions
    //printf("\n table collision nodes = %llu",sizeof(new_table_collision->nodes)/sizeof(new_table_collision->nodes[0]));
    //test(new_table_collision);
    realloc_set_table(new_table_collision,20);
    new_table_collision->nodes[1]->index = 700;
    printf("\n %i",new_table_collision->nodes[1]->index);
    printf("\nDEBUG ENDED");
    return 0;
    printf("\n single node size = %llu",sizeof(set_node));
    printf("\n table size = %llu",sizeof(set_table));
    printf("\n table collision size = %llu",sizeof(new_table_collision));
    int example_int = 1;
    DictionaryInsert(new_table_collision,"test",&example_int,Int);
    DictionaryInsert(new_table_collision,"ciao",&example_int,Int);
    DictionaryInsert(new_table_collision,"sbam",&example_int,Int);
    DictionaryInsert(new_table_collision,"asdf",&example_int,Int);

    DictionaryInsert(new_table_collision,"ghjk",&example_int,Int);




    //printf("\n%llu +++++++++ %llu",new_table_collision->hashmap_size,sizeof(new_table_collision));

    //printf("\n%llu +++++++++ %llu",new_table_collision->hashmap_size,sizeof(new_table_collision));
    printf("\nDEBUG ENDED");
    return 0;
    example_int++;
    example_int++;
    DictionaryInsert(new_table_collision,"boom",&example_int,Int);
    example_int++;
    DictionaryInsert(new_table_collision,"lmao",&example_int,Int);

    print_set(new_table_collision);
    printf("%llu +++++++++ %llu",new_table_collision->hashmap_size,sizeof(new_table_collision));
    printf("Program executed succesfully");

    //set_table* new_set_REHASHING = set_table_new(100);
    */
    
}