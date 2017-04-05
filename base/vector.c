
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <base/vector.h>

UVector * init_UVector(UVector * const uVector)
{
    if( uVector == NULL)
        return NULL;

    uVector->data = NULL;
    uVector->size = 0;
    uVector->count = 0;

    return uVector;
}

UVector * free_UVector(UVector * const uVector)
{
    if( uVector == NULL)
        return NULL;

    free(uVector->data);
    uVector->data = NULL;
    uVector->size = 0;
    uVector->count = 0;

    return uVector;
}

int size_UVector(UVector const * const uVector)
{
    if( uVector == NULL)
        return -1;
    return uVector->size;
}

int count_UVector(UVector const * const uVector)
{
    if( uVector == NULL)
        return -1;
    return uVector->count;
}

void * addObj_UVector(UVector * const uVector, void * const obj)
{
    if( uVector == NULL || obj == NULL )
        return NULL;

    if (uVector->size == 0)
    {
        uVector->size = UVectorInitSize;
        //uVector->data = malloc(sizeof(void*) * uVector->size);
        uVector->data = calloc(uVector->size,sizeof(void*));

        if(uVector->data == NULL)
        {
            uVector->size = 0;
            return NULL;
        }

        //memset(uVector->data, '\0', sizeof(void * ) * uVector->size);
    }

    if (uVector->size == uVector->count)
    {
        void **newData = realloc(uVector->data, sizeof(void*) * uVector->size * 2);
        if(newData == NULL)
        {
            return NULL;
        }

        uVector->data = newData;
        uVector->size *= 2;
    }

    uVector->data[uVector->count] = obj;
    uVector->count++;

    return obj;
}

void * deleteObj_UVector(UVector * const uVector, int const index)
{
    void * objDeleted = NULL;

    if( uVector == NULL)
        return NULL;

    if (index >= uVector->count)
    {
        return NULL;
    }
    else if (index < 0)
    {
        //printf("------ index invalid:%d ---\n", index);
        return NULL;
    }

    objDeleted = uVector->data[index];

    memcpy(&(uVector->data[index]), &(uVector->data[index + 1]), (uVector->count - index - 1) * sizeof(void*));

    uVector->data[uVector->count - 1] = NULL;
    uVector->count--;

    return objDeleted;
}

void * set_UVector(UVector * const uVector, int const index, void * const obj)
{
    if( uVector == NULL)
        return NULL;

    if (index >= uVector->count)
    {
        return NULL;
    }

    uVector->data[index] = obj;

    return uVector->data[index];
}

void * get_UVector(UVector const * const uVector, int const index)
{
    if( uVector == NULL)
        return NULL;

    if (index >= uVector->count)
    {
        return NULL;
    }

    return uVector->data[index];
}


