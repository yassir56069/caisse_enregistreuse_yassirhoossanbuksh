#include <stdio.h>
#include <stdlib.h>

struct Dynarry
{
    int *store;
    size_t size;
    size_t used;
};

int init_array( struct Dynarry *arr, int size )
{
    arr->size = size;
    arr->used = 0;
    arr->store = calloc(arr->size, sizeof(int));

    if ( arr->store == NULL)
    {
        fprintf(stderr, "Error 01: Array not Allocated!");
        return 1;
    }

}

int grow_array( struct Dynarry *arr, int growth_factor)
{
    arr->size *= growth_factor;
    arr->store = realloc( arr->store, arr->size * sizeof(int));

    if (arr->store == NULL)
    {
        fprintf(stderr, "Error 01-0: Array Could Not Be Grown!");
        return 1;
    }
    else
    {
        return 0;
    }
}

int insert_array( struct Dynarry *arr, int to_store)
{
    if (arr->used >= arr->size)
    {
        grow_array(arr, 2);
    }

    arr->store[arr->used] = to_store;
    arr->used ++;
    return 0;
}

void free_array( struct Dynarry *arr )
{
    free(arr->store);
}


int main(int argc, char *argv[])
{
    struct Dynarry test;
    
    init_array(&test, 2);

    for (int i = 10; i < 100; i++)
    {
        insert_array(&test, i);
    }

    for (int i = 0 ; i < test.used; i++)
    {
        fprintf(stdout, "Val: %d\n", test.store[i]);
    }

    free_array(&test);
    return 0;
}