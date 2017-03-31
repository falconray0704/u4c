#ifndef U4C_BASE_VECTOR_H
#define U4C_BASE_VECTOR_H


#include <stdio.h>
#include <string.h>

#include <stddef.h>

#include <base/u4cGlobalDef.h>

#ifdef __cplusplus
extern "C" {
#endif

#define UVectorInitSize 16

typedef struct
{
    void** data;
    int size;
    int count;
} UVector;

#define newUVector() { NULL, 0, 0};

UVector * init_UVector(UVector * const uVector);
UVector * free_UVector(UVector * const uVector);

int count_UVector(UVector const * const uVector);

void * addObj_UVector(UVector * const uVector, void * const obj);
void * deleteObj_UVector(UVector * const uVector, int const index);

void * set_UVector(UVector * const uVector, int const index, void * const obj);
void * get_UVector(UVector const * const uVector, int const index);


#ifdef __cplusplus
}
#endif

#endif
