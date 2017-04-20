/*
 * =====================================================================================
 *
 *       Filename:  UAtomic.cc
 *
 *    Description:  atomic operation for int and unsigned int
 *
 *        Version:  1.0
 *        Created:  04/16/2017 04:07:22 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  FalconRay
 *   Organization:  FalconX
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <gtest/gtest.h>

#include <base/uAtomic.h>

TEST(Base_UAtomic, atomicInt_get)
{
    AtomicUInt8 ui8 = 0xf0 + 8;
    AtomicUInt16 ui16 = 0xff00 + 16;
    AtomicUInt32 ui32 = 0xffff0000 + 32;
    AtomicUInt64 ui64 = 0xffffffff00000000 + 64;

    AtomicInt8 i8 = static_cast<AtomicInt8>(0xe0 + 8);
    AtomicInt16 i16 = static_cast<AtomicInt16>(0xef00 + 16);
    AtomicInt32 i32 = static_cast<AtomicInt32>(0xefff0000 + 32);
    AtomicInt64 i64 = static_cast<AtomicInt64>(0xefffffff00000000 + 64);


    ASSERT_EQ(0xf0 + 8, atomicInt_get(ui8));
    ASSERT_EQ(0xff00 + 16, atomicInt_get(ui16));
    ASSERT_EQ(0xffff0000 + 32, atomicInt_get(ui32));
    ASSERT_EQ(0xffffffff00000000 + 64, atomicInt_get(ui64));

    ASSERT_EQ(static_cast<AtomicInt8>(0xe0 + 8), atomicInt_get(i8));
    ASSERT_EQ(static_cast<AtomicInt16>(0xef00 + 16), atomicInt_get(i16));
    ASSERT_EQ(static_cast<AtomicInt32>(0xefff0000 + 32), atomicInt_get(i32));
    ASSERT_EQ(static_cast<AtomicInt64>(0xefffffff00000000 + 64), atomicInt_get(i64));

}

#define TestTimes 0xfffff

AtomicUInt8 ui8 = 0x55;
AtomicUInt16 ui16 = 0x5555;
AtomicUInt32 ui32 = 0x55555555;
AtomicUInt64 ui64 = 0x5555555555555555;

AtomicInt8 i8 = 0x55;
AtomicInt16 i16 = 0x5555;
AtomicInt32 i32 = 0x55555555;
AtomicInt64 i64 = 0x5555555555555555;

void *setFuc_0x55_atomicInt_getAndSet(void *arg)
{
    int *c = static_cast<int*>(arg);
    int i;

    switch(*c)
    {
        case 1:
            for(i = 0; i < TestTimes; i++)
            {
                AtomicUInt8 _ui8 = atomicInt_getAndSet(ui8, static_cast<AtomicUInt8>(0x55));
                if(_ui8 != static_cast<AtomicUInt8>(0x55))
                {
                    EXPECT_EQ(static_cast<AtomicUInt8>(0xaa), _ui8);
                    //printf("--- [%s]:i:%x, _ui8:%x\n",__func__,i,_ui8);
                }
                else
                    EXPECT_EQ(static_cast<AtomicUInt8>(0x55), _ui8);
            }
            break;
        case 2:
            for(i = 0; i < TestTimes; i++)
            {
                AtomicUInt16 _ui16 = atomicInt_getAndSet(ui16, static_cast<AtomicUInt16>(0x5555));
                if(_ui16 != static_cast<AtomicUInt16>(0x5555))
                    EXPECT_EQ(static_cast<AtomicUInt16>(0xaaaa), _ui16);
                else
                    EXPECT_EQ(static_cast<AtomicUInt16>(0x5555), _ui16);
            }
            break;
        case 3:
            for(i = 0; i < TestTimes; i++)
            {
                AtomicUInt32 _ui32 = atomicInt_getAndSet(ui32, static_cast<AtomicUInt32>(0x55555555));
                if(_ui32 != static_cast<AtomicUInt32>(0x55555555))
                    EXPECT_EQ(static_cast<AtomicUInt32>(0xaaaaaaaa), _ui32);
                else
                    EXPECT_EQ(static_cast<AtomicUInt32>(0x55555555), _ui32);
            }
            break;
        case 4:
            for(i = 0; i < TestTimes; i++)
            {
                AtomicUInt64 _ui64 = atomicInt_getAndSet(ui64, static_cast<AtomicUInt64>(0x5555555555555555));
                if(_ui64 != static_cast<AtomicUInt64>(0x5555555555555555))
                    EXPECT_EQ(static_cast<AtomicUInt64>(0xaaaaaaaaaaaaaaaa), _ui64);
                else
                    EXPECT_EQ(static_cast<AtomicUInt64>(0x5555555555555555), _ui64);
            }
            break;
        case 5:
            for(i = 0; i < TestTimes; i++)
            {
                AtomicInt8 _i8 = atomicInt_getAndSet(i8, static_cast<AtomicInt8>(0x55));
                if(_i8 != static_cast<AtomicInt8>(0x55))
                {
                    EXPECT_EQ(static_cast<AtomicInt8>(0xaa), _i8);
                    //printf("--- [%s]:i:%x, _ui8:%x\n",__func__,i,_ui8);
                }
                else
                    EXPECT_EQ(static_cast<AtomicInt8>(0x55), _i8);
            }
            break;
        case 6:
            for(i = 0; i < TestTimes; i++)
            {
                AtomicInt16 _i16 = atomicInt_getAndSet(i16, static_cast<AtomicInt16>(0x5555));
                if(_i16 != static_cast<AtomicInt16>(0x5555))
                    EXPECT_EQ(static_cast<AtomicInt16>(0xaaaa), _i16);
                else
                    EXPECT_EQ(static_cast<AtomicInt16>(0x5555), _i16);
            }
            break;
        case 7:
            for(i = 0; i < TestTimes; i++)
            {
                AtomicInt32 _i32 = atomicInt_getAndSet(i32, static_cast<AtomicInt32>(0x55555555));
                if(_i32 != static_cast<AtomicInt32>(0x55555555))
                    EXPECT_EQ(static_cast<AtomicInt32>(0xaaaaaaaa), _i32);
                else
                    EXPECT_EQ(static_cast<AtomicInt32>(0x55555555), _i32);
            }
            break;
        case 8:
            for(i = 0; i < TestTimes; i++)
            {
                AtomicInt64 _i64 = atomicInt_getAndSet(i64, static_cast<AtomicInt64>(0x5555555555555555));
                if(_i64 != static_cast<AtomicInt64>(0x5555555555555555))
                    EXPECT_EQ(static_cast<AtomicInt64>(0xaaaaaaaaaaaaaaaa), _i64);
                else
                    EXPECT_EQ(static_cast<AtomicInt64>(0x5555555555555555), _i64);
            }
            break;
    }

    //printf("[%s]:i:%x\n",__func__,i);
    return NULL;
}

void *setFuc_0xaa_atomicInt_getAndSet(void *arg)
{
    int *c = static_cast<int*>(arg);

    switch(*c)
    {
        case 1:
            for(int i = 0; i < TestTimes; i++)
            {
                AtomicUInt8 _ui8 = atomicInt_getAndSet(ui8, static_cast<AtomicUInt8>(0xaa));
                if(_ui8 != static_cast<AtomicUInt8>(0xaa))
                {
                    EXPECT_EQ(static_cast<AtomicUInt8>(0x55), _ui8);
                    //printf("--- [%s]:i:%x, _ui8:%x\n",__func__,i,_ui8);
                }
                else
                    EXPECT_EQ(static_cast<AtomicUInt8>(0xaa), _ui8);
            }
            break;
        case 2:
            for(int i = 0; i < TestTimes; i++)
            {
                AtomicUInt16 _ui16 = atomicInt_getAndSet(ui16, static_cast<AtomicUInt16>(0xaaaa));
                if(_ui16 != static_cast<AtomicUInt16>(0xaaaa))
                    EXPECT_EQ(static_cast<AtomicUInt16>(0x5555), _ui16);
                else
                    EXPECT_EQ(static_cast<AtomicUInt16>(0xaaaa), _ui16);
            }
            break;
        case 3:
            for(int i = 0; i < TestTimes; i++)
            {
                AtomicUInt32 _ui32 = atomicInt_getAndSet(ui32, static_cast<AtomicUInt32>(0xaaaaaaaa));
                if(_ui32 != static_cast<AtomicUInt32>(0xaaaaaaaa))
                    EXPECT_EQ(static_cast<AtomicUInt32>(0x55555555), _ui32);
                else
                    EXPECT_EQ(static_cast<AtomicUInt32>(0xaaaaaaaa), _ui32);
            }
            break;
        case 4:
            for(int i = 0; i < TestTimes; i++)
            {
                AtomicUInt64 _ui64 = atomicInt_getAndSet(ui64, static_cast<AtomicUInt64>(0xaaaaaaaaaaaaaaaa));
                if(_ui64 != static_cast<AtomicUInt64>(0xaaaaaaaaaaaaaaaa))
                    EXPECT_EQ(static_cast<AtomicUInt64>(0x5555555555555555), _ui64);
                else
                    EXPECT_EQ(static_cast<AtomicUInt64>(0xaaaaaaaaaaaaaaaa), _ui64);
            }
            break;
        case 5:
            for(int i = 0; i < TestTimes; i++)
            {
                AtomicInt8 _i8 = atomicInt_getAndSet(i8, static_cast<AtomicInt8>(0xaa));
                if(_i8 != static_cast<AtomicInt8>(0xaa))
                {
                    EXPECT_EQ(static_cast<AtomicInt8>(0x55), _i8);
                    //printf("--- [%s]:i:%x, _ui8:%x\n",__func__,i,_ui8);
                }
                else
                    EXPECT_EQ(static_cast<AtomicInt8>(0xaa), _i8);
            }
            break;
        case 6:
            for(int i = 0; i < TestTimes; i++)
            {
                AtomicInt16 _i16 = atomicInt_getAndSet(i16, static_cast<AtomicInt16>(0xaaaa));
                if(_i16 != static_cast<AtomicInt16>(0xaaaa))
                    EXPECT_EQ(static_cast<AtomicInt16>(0x5555), _i16);
                else
                    EXPECT_EQ(static_cast<AtomicInt16>(0xaaaa), _i16);
            }
            break;
        case 7:
            for(int i = 0; i < TestTimes; i++)
            {
                AtomicInt32 _i32 = atomicInt_getAndSet(i32, static_cast<AtomicInt32>(0xaaaaaaaa));
                if(_i32 != static_cast<AtomicInt32>(0xaaaaaaaa))
                    EXPECT_EQ(static_cast<AtomicInt32>(0x55555555), _i32);
                else
                    EXPECT_EQ(static_cast<AtomicInt32>(0xaaaaaaaa), _i32);
            }
            break;
        case 8:
            for(int i = 0; i < TestTimes; i++)
            {
                AtomicInt64 _i64 = atomicInt_getAndSet(i64, static_cast<AtomicInt64>(0xaaaaaaaaaaaaaaaa));
                if(_i64 != static_cast<AtomicInt64>(0xaaaaaaaaaaaaaaaa))
                    EXPECT_EQ(static_cast<AtomicInt64>(0x5555555555555555), _i64);
                else
                    EXPECT_EQ(static_cast<AtomicInt64>(0xaaaaaaaaaaaaaaaa), _i64);
            }
            break;
    }
    return NULL;
}

void *getFuc_0x55_0xaa_atomicInt_getAndSet(void *arg)
{
    int *c = static_cast<int*>(arg);

    switch(*c)
    {
        case 1:
            for(int i = 0; i < TestTimes; i++)
            {
                AtomicUInt8 _ui8 = atomicInt_get(ui8);
                if(_ui8 == static_cast<AtomicUInt8>(0x55))
                    EXPECT_EQ(static_cast<AtomicUInt8>(0x55), _ui8);
                else
                    EXPECT_EQ(static_cast<AtomicUInt8>(0xaa), _ui8);
            }
            break;
        case 2:
            for(int i = 0; i < TestTimes; i++)
            {
                AtomicUInt16 _ui16 = atomicInt_get(ui16);
                if(_ui16 == static_cast<AtomicUInt16>(0x5555))
                    EXPECT_EQ(static_cast<AtomicUInt16>(0x5555), _ui16);
                else
                    EXPECT_EQ(static_cast<AtomicUInt16>(0xaaaa), _ui16);
            }
            break;
        case 3:
            for(int i = 0; i < TestTimes; i++)
            {
                AtomicUInt32 _ui32 = atomicInt_get(ui32);
                if(_ui32 == static_cast<AtomicUInt32>(0x55555555))
                    EXPECT_EQ(static_cast<AtomicUInt32>(0x55555555), _ui32);
                else
                    EXPECT_EQ(static_cast<AtomicUInt32>(0xaaaaaaaa), _ui32);
            }
            break;
        case 4:
            for(int i = 0; i < TestTimes; i++)
            {
                AtomicUInt64 _ui64 = atomicInt_get(ui64);
                if(_ui64 == static_cast<AtomicUInt64>(0x5555555555555555))
                    EXPECT_EQ(static_cast<AtomicUInt64>(0x5555555555555555), _ui64);
                else
                    EXPECT_EQ(static_cast<AtomicUInt64>(0xaaaaaaaaaaaaaaaa), _ui64);
            }
            break;
        case 5:
            for(int i = 0; i < TestTimes; i++)
            {
                AtomicInt8 _i8 = atomicInt_get(i8);
                if(_i8 == static_cast<AtomicInt8>(0x55))
                    EXPECT_EQ(static_cast<AtomicInt8>(0x55), _i8);
                else
                    EXPECT_EQ(static_cast<AtomicInt8>(0xaa), _i8);
            }
            break;
        case 6:
            for(int i = 0; i < TestTimes; i++)
            {
                AtomicInt16 _i16 = atomicInt_get(i16);
                if(_i16 == static_cast<AtomicInt16>(0x5555))
                    EXPECT_EQ(static_cast<AtomicInt16>(0x5555), _i16);
                else
                    EXPECT_EQ(static_cast<AtomicInt16>(0xaaaa), _i16);
            }
            break;
        case 7:
            for(int i = 0; i < TestTimes; i++)
            {
                AtomicInt32 _i32 = atomicInt_get(i32);
                if(_i32 == static_cast<AtomicInt32>(0x55555555))
                    EXPECT_EQ(static_cast<AtomicInt32>(0x55555555), _i32);
                else
                    EXPECT_EQ(static_cast<AtomicInt32>(0xaaaaaaaa), _i32);
            }
            break;
        case 8:
            for(int i = 0; i < TestTimes; i++)
            {
                AtomicInt64 _i64 = atomicInt_get(i64);
                if(_i64 == static_cast<AtomicInt64>(0x5555555555555555))
                    EXPECT_EQ(static_cast<AtomicInt64>(0x5555555555555555), _i64);
                else
                    EXPECT_EQ(static_cast<AtomicInt64>(0xaaaaaaaaaaaaaaaa), _i64);
            }
            break;
    }
    return NULL;
}

TEST(Base_UAtomic, atomicInt_getAndSet)
{
    pthread_t id[8][3];
    int * cc = NULL;

    for(int i=0;i<8;++i)
    {
        cc = static_cast<int *>(calloc(1,sizeof(int)));
        EXPECT_NE(static_cast<int *>(NULL),cc);
        *cc = i + 1;
        pthread_create(&id[i][0],NULL,setFuc_0x55_atomicInt_getAndSet,static_cast<void *>(cc));
        pthread_create(&id[i][1],NULL,setFuc_0xaa_atomicInt_getAndSet,static_cast<void *>(cc));
        pthread_create(&id[i][2],NULL,getFuc_0x55_0xaa_atomicInt_getAndSet,static_cast<void *>(cc));

    }
    for(int i=0; i < 8; i++)
    {
        for(int j=0; j < 3; j++)
        {
            pthread_join(id[i][j],NULL);
        }
    }

}

typedef struct _tAtomicInt 
{
    int tCaseId;
    int tAddCount;

    AtomicUInt8 ui8;
    AtomicUInt16 ui16;
    AtomicUInt32 ui32;
    AtomicUInt64 ui64;

    AtomicInt8 i8;
    AtomicInt16 i16;
    AtomicInt32 i32;
    AtomicInt64 i64;
} TAtomicInt;

void *addFunc_atomicInt_getAndAdd(void *arg)
{
    TAtomicInt *c = static_cast<TAtomicInt*>(arg);
    int i;

    switch(c->tCaseId)
    {
        case 1:
            for(i = 0; i < c->tAddCount; i++)
            {
                AtomicUInt8 p_ui8 = atomicInt_getAndAdd(c->ui8, static_cast<AtomicUInt8>(0x01));
                AtomicUInt8 a_ui8 = atomicInt_get(c->ui8);
                EXPECT_LT(p_ui8, a_ui8);
            }
            break;
        case 2:
            for(i = 0; i < c->tAddCount; i++)
            {
                AtomicUInt16 p_ui16 = atomicInt_getAndAdd(c->ui16, static_cast<AtomicUInt16>(0x01));
                AtomicUInt16 a_ui16 = atomicInt_get(c->ui16);
                EXPECT_LT(p_ui16, a_ui16);
            }
            break;
        case 3:
            for(i = 0; i < c->tAddCount; i++)
            {
                AtomicUInt32 p_ui32 = atomicInt_getAndAdd(c->ui32, static_cast<AtomicUInt32>(0x01));
                AtomicUInt32 a_ui32 = atomicInt_get(c->ui32);
                EXPECT_LT(p_ui32, a_ui32);
            }
            break;
        case 4:
            for(i = 0; i < c->tAddCount; i++)
            {
                AtomicUInt64 p_ui64 = atomicInt_getAndAdd(c->ui64, static_cast<AtomicUInt64>(0x01));
                AtomicUInt64 a_ui64 = atomicInt_get(c->ui64);
                EXPECT_LT(p_ui64, a_ui64);
            }
            break;
        case 5:
            for(i = 0; i < c->tAddCount; i++)
            {
                AtomicInt8 p_i8 = atomicInt_getAndAdd(c->i8, static_cast<AtomicInt8>(0x01));
                AtomicInt8 a_i8 = atomicInt_get(c->i8);
                EXPECT_LT(p_i8, a_i8);
            }
            break;
        case 6:
            for(i = 0; i < c->tAddCount; i++)
            {
                AtomicInt16 p_i16 = atomicInt_getAndAdd(c->i16, static_cast<AtomicInt16>(0x01));
                AtomicInt16 a_i16 = atomicInt_get(c->i16);
                EXPECT_LT(p_i16, a_i16);
            }
            break;
        case 7:
            for(i = 0; i < c->tAddCount; i++)
            {
                AtomicInt32 p_i32 = atomicInt_getAndAdd(c->i32, static_cast<AtomicInt32>(0x01));
                AtomicInt32 a_i32 = atomicInt_get(c->i32);
                EXPECT_LT(p_i32, a_i32);
            }
            break;
        case 8:
            for(i = 0; i < c->tAddCount; i++)
            {
                AtomicInt64 p_i64 = atomicInt_getAndAdd(c->i64, static_cast<AtomicInt64>(0x01));
                AtomicInt64 a_i64 = atomicInt_get(c->i64);
                EXPECT_LT(p_i64, a_i64);
            }
            break;
    }

    //printf("[%s]:i:%x\n",__func__,i);
    return NULL;
}

TEST(Base_UAtomic, atomicInt_getAndAdd)
{

    for(int i = 0; i < 8; ++i)
    {
        pthread_t id[4];
        TAtomicInt * cc = NULL;

        cc = static_cast<TAtomicInt *>(calloc(1,sizeof(TAtomicInt)));
        EXPECT_NE(static_cast<TAtomicInt *>(NULL),cc);
        cc->tCaseId = i + 1;

        switch(cc->tCaseId)
        {
            case 1:
                cc->tAddCount = static_cast<AtomicUInt8>(0xff / 2);
                //printf("--- tCaseId:%d tAddCount:%d ---\n", cc->tCaseId, cc->tAddCount);
                pthread_create(&id[0],NULL, addFunc_atomicInt_getAndAdd,static_cast<TAtomicInt*>(cc));
                pthread_create(&id[1],NULL, addFunc_atomicInt_getAndAdd,static_cast<TAtomicInt*>(cc));
                pthread_join(id[0],NULL);
                pthread_join(id[1],NULL);
                EXPECT_EQ(static_cast<AtomicUInt8>(0xff -1),cc->ui8);
                free(cc);
                break;
            case 2:
                cc->tAddCount = static_cast<AtomicUInt16>(0xffff / 2);
                //printf("--- tCaseId:%d tAddCount:%d ---\n", cc->tCaseId, cc->tAddCount);
                pthread_create(&id[0],NULL, addFunc_atomicInt_getAndAdd,static_cast<TAtomicInt*>(cc));
                pthread_create(&id[1],NULL, addFunc_atomicInt_getAndAdd,static_cast<TAtomicInt*>(cc));
                pthread_join(id[0],NULL);
                pthread_join(id[1],NULL);
                EXPECT_EQ(static_cast<AtomicUInt16>(0xffff - 1),cc->ui16);
                free(cc);
                break;
            case 3:
                cc->ui32 = static_cast<AtomicUInt32>(0xffff0000);
                cc->tAddCount = 0xffff / 2;
                //printf("--- tCaseId:%d tAddCount:%d ---\n", cc->tCaseId, cc->tAddCount);
                pthread_create(&id[0],NULL, addFunc_atomicInt_getAndAdd,static_cast<TAtomicInt*>(cc));
                pthread_create(&id[1],NULL, addFunc_atomicInt_getAndAdd,static_cast<TAtomicInt*>(cc));
                pthread_join(id[0],NULL);
                pthread_join(id[1],NULL);
                EXPECT_EQ(static_cast<AtomicUInt32>(0xffffffff - 1),cc->ui32);
                free(cc);
                break;
            case 4:
                cc->ui64 = static_cast<AtomicUInt64>(0xffffffffffff0000);
                cc->tAddCount = 0xffff / 2;
                //printf("--- tCaseId:%d tAddCount:%d ---\n", cc->tCaseId, cc->tAddCount);
                pthread_create(&id[0],NULL, addFunc_atomicInt_getAndAdd,static_cast<TAtomicInt*>(cc));
                pthread_create(&id[1],NULL, addFunc_atomicInt_getAndAdd,static_cast<TAtomicInt*>(cc));
                pthread_join(id[0],NULL);
                pthread_join(id[1],NULL);
                EXPECT_EQ(static_cast<AtomicUInt64>(0xffffffffffffffff - 1),cc->ui64);
                free(cc);
                break;
            case 5:
                cc->tAddCount = static_cast<AtomicInt8>(0x7f / 2);
                //printf("--- tCaseId:%d tAddCount:%d ---\n", cc->tCaseId, cc->tAddCount);
                pthread_create(&id[0],NULL, addFunc_atomicInt_getAndAdd,static_cast<TAtomicInt*>(cc));
                pthread_create(&id[1],NULL, addFunc_atomicInt_getAndAdd,static_cast<TAtomicInt*>(cc));
                pthread_join(id[0],NULL);
                pthread_join(id[1],NULL);
                EXPECT_EQ(static_cast<AtomicInt8>(0x7f -1),cc->i8);
                free(cc);
                break;
            case 6:
                cc->tAddCount = static_cast<AtomicInt16>(0x7fff / 2);
                //printf("--- tCaseId:%d tAddCount:%d ---\n", cc->tCaseId, cc->tAddCount);
                pthread_create(&id[0],NULL, addFunc_atomicInt_getAndAdd,static_cast<TAtomicInt*>(cc));
                pthread_create(&id[1],NULL, addFunc_atomicInt_getAndAdd,static_cast<TAtomicInt*>(cc));
                pthread_join(id[0],NULL);
                pthread_join(id[1],NULL);
                EXPECT_EQ(static_cast<AtomicInt16>(0x7fff - 1),cc->i16);
                free(cc);
                break;
            case 7:
                cc->i32 = static_cast<AtomicInt32>(0x7fff0000);
                cc->tAddCount = 0xffff / 2;
                //printf("--- tCaseId:%d tAddCount:%d ---\n", cc->tCaseId, cc->tAddCount);
                pthread_create(&id[0],NULL, addFunc_atomicInt_getAndAdd,static_cast<TAtomicInt*>(cc));
                pthread_create(&id[1],NULL, addFunc_atomicInt_getAndAdd,static_cast<TAtomicInt*>(cc));
                pthread_join(id[0],NULL);
                pthread_join(id[1],NULL);
                EXPECT_EQ(static_cast<AtomicInt32>(0x7fffffff - 1),cc->i32);
                free(cc);
                break;
            case 8:
                cc->i64 = static_cast<AtomicInt64>(0x7fffffffffff0000);
                cc->tAddCount = 0xffff / 2;
                //printf("--- tCaseId:%d tAddCount:%d ---\n", cc->tCaseId, cc->tAddCount);
                pthread_create(&id[0],NULL, addFunc_atomicInt_getAndAdd,static_cast<TAtomicInt*>(cc));
                pthread_create(&id[1],NULL, addFunc_atomicInt_getAndAdd,static_cast<TAtomicInt*>(cc));
                pthread_join(id[0],NULL);
                pthread_join(id[1],NULL);
                EXPECT_EQ(static_cast<AtomicInt64>(0x7fffffffffffffff - 1),cc->i64);
                free(cc);
                break;
        }
    }

}

void *addFunc_atomicInt_addAndGet(void *arg)
{
    TAtomicInt *c = static_cast<TAtomicInt*>(arg);
    int i;

    switch(c->tCaseId)
    {
        case 1:
            for(i = 0; i < c->tAddCount; i++)
            {
                AtomicUInt8 p_ui8 = atomicInt_get(c->ui8);
                AtomicUInt8 a_ui8 = atomicInt_addAndGet(c->ui8, static_cast<AtomicUInt8>(0x01));
                EXPECT_LT(p_ui8, a_ui8);
            }
            break;
        case 2:
            for(i = 0; i < c->tAddCount; i++)
            {
                AtomicUInt16 p_ui16 = atomicInt_get(c->ui16);
                AtomicUInt16 a_ui16 = atomicInt_addAndGet(c->ui16, static_cast<AtomicUInt16>(0x01));
                EXPECT_LT(p_ui16, a_ui16);
            }
            break;
        case 3:
            for(i = 0; i < c->tAddCount; i++)
            {
                AtomicUInt32 p_ui32 = atomicInt_get(c->ui32);
                AtomicUInt32 a_ui32 = atomicInt_addAndGet(c->ui32, static_cast<AtomicUInt32>(0x01));
                EXPECT_LT(p_ui32, a_ui32);
            }
            break;
        case 4:
            for(i = 0; i < c->tAddCount; i++)
            {
                AtomicUInt64 p_ui64 = atomicInt_get(c->ui64);
                AtomicUInt64 a_ui64 = atomicInt_addAndGet(c->ui64, static_cast<AtomicUInt64>(0x01));
                EXPECT_LT(p_ui64, a_ui64);
            }
            break;
        case 5:
            for(i = 0; i < c->tAddCount; i++)
            {
                AtomicInt8 p_i8 = atomicInt_get(c->i8);
                AtomicInt8 a_i8 = atomicInt_addAndGet(c->i8, static_cast<AtomicInt8>(0x01));
                EXPECT_LT(p_i8, a_i8);
            }
            break;
        case 6:
            for(i = 0; i < c->tAddCount; i++)
            {
                AtomicInt16 p_i16 = atomicInt_get(c->i16);
                AtomicInt16 a_i16 = atomicInt_addAndGet(c->i16, static_cast<AtomicInt16>(0x01));
                EXPECT_LT(p_i16, a_i16);
            }
            break;
        case 7:
            for(i = 0; i < c->tAddCount; i++)
            {
                AtomicInt32 p_i32 = atomicInt_get(c->i32);
                AtomicInt32 a_i32 = atomicInt_addAndGet(c->i32, static_cast<AtomicInt32>(0x01));
                EXPECT_LT(p_i32, a_i32);
            }
            break;
        case 8:
            for(i = 0; i < c->tAddCount; i++)
            {
                AtomicInt64 p_i64 = atomicInt_get(c->i64);
                AtomicInt64 a_i64 = atomicInt_addAndGet(c->i64, static_cast<AtomicInt64>(0x01));
                EXPECT_LT(p_i64, a_i64);
            }
            break;
    }

    //printf("[%s]:i:%x\n",__func__,i);
    return NULL;
}

TEST(Base_UAtomic, atomicInt_addAndGet)
{

    for(int i = 0; i < 8; ++i)
    {
        pthread_t id[4];
        TAtomicInt * cc = NULL;

        cc = static_cast<TAtomicInt *>(calloc(1,sizeof(TAtomicInt)));
        EXPECT_NE(static_cast<TAtomicInt *>(NULL),cc);
        cc->tCaseId = i + 1;

        switch(cc->tCaseId)
        {
            case 1:
                cc->tAddCount = static_cast<AtomicUInt8>(0xff / 2);
                //printf("--- tCaseId:%d tAddCount:%d ---\n", cc->tCaseId, cc->tAddCount);
                pthread_create(&id[0],NULL, addFunc_atomicInt_addAndGet,static_cast<TAtomicInt*>(cc));
                pthread_create(&id[1],NULL, addFunc_atomicInt_addAndGet,static_cast<TAtomicInt*>(cc));
                pthread_join(id[0],NULL);
                pthread_join(id[1],NULL);
                EXPECT_EQ(static_cast<AtomicUInt8>(0xff -1),cc->ui8);
                free(cc);
                break;
            case 2:
                cc->tAddCount = static_cast<AtomicUInt16>(0xffff / 2);
                //printf("--- tCaseId:%d tAddCount:%d ---\n", cc->tCaseId, cc->tAddCount);
                pthread_create(&id[0],NULL, addFunc_atomicInt_addAndGet,static_cast<TAtomicInt*>(cc));
                pthread_create(&id[1],NULL, addFunc_atomicInt_addAndGet,static_cast<TAtomicInt*>(cc));
                pthread_join(id[0],NULL);
                pthread_join(id[1],NULL);
                EXPECT_EQ(static_cast<AtomicUInt16>(0xffff - 1),cc->ui16);
                free(cc);
                break;
            case 3:
                cc->ui32 = static_cast<AtomicUInt32>(0xffff0000);
                cc->tAddCount = 0xffff / 2;
                //printf("--- tCaseId:%d tAddCount:%d ---\n", cc->tCaseId, cc->tAddCount);
                pthread_create(&id[0],NULL, addFunc_atomicInt_addAndGet,static_cast<TAtomicInt*>(cc));
                pthread_create(&id[1],NULL, addFunc_atomicInt_addAndGet,static_cast<TAtomicInt*>(cc));
                pthread_join(id[0],NULL);
                pthread_join(id[1],NULL);
                EXPECT_EQ(static_cast<AtomicUInt32>(0xffffffff - 1),cc->ui32);
                free(cc);
                break;
            case 4:
                cc->ui64 = static_cast<AtomicUInt64>(0xffffffffffff0000);
                cc->tAddCount = 0xffff / 2;
                //printf("--- tCaseId:%d tAddCount:%d ---\n", cc->tCaseId, cc->tAddCount);
                pthread_create(&id[0],NULL, addFunc_atomicInt_addAndGet,static_cast<TAtomicInt*>(cc));
                pthread_create(&id[1],NULL, addFunc_atomicInt_addAndGet,static_cast<TAtomicInt*>(cc));
                pthread_join(id[0],NULL);
                pthread_join(id[1],NULL);
                EXPECT_EQ(static_cast<AtomicUInt64>(0xffffffffffffffff - 1),cc->ui64);
                free(cc);
                break;
            case 5:
                cc->tAddCount = static_cast<AtomicInt8>(0x7f / 2);
                //printf("--- tCaseId:%d tAddCount:%d ---\n", cc->tCaseId, cc->tAddCount);
                pthread_create(&id[0],NULL, addFunc_atomicInt_addAndGet,static_cast<TAtomicInt*>(cc));
                pthread_create(&id[1],NULL, addFunc_atomicInt_addAndGet,static_cast<TAtomicInt*>(cc));
                pthread_join(id[0],NULL);
                pthread_join(id[1],NULL);
                EXPECT_EQ(static_cast<AtomicInt8>(0x7f -1),cc->i8);
                free(cc);
                break;
            case 6:
                cc->tAddCount = static_cast<AtomicInt16>(0x7fff / 2);
                //printf("--- tCaseId:%d tAddCount:%d ---\n", cc->tCaseId, cc->tAddCount);
                pthread_create(&id[0],NULL, addFunc_atomicInt_addAndGet,static_cast<TAtomicInt*>(cc));
                pthread_create(&id[1],NULL, addFunc_atomicInt_addAndGet,static_cast<TAtomicInt*>(cc));
                pthread_join(id[0],NULL);
                pthread_join(id[1],NULL);
                EXPECT_EQ(static_cast<AtomicInt16>(0x7fff - 1),cc->i16);
                free(cc);
                break;
            case 7:
                cc->i32 = static_cast<AtomicInt32>(0x7fff0000);
                cc->tAddCount = 0xffff / 2;
                //printf("--- tCaseId:%d tAddCount:%d ---\n", cc->tCaseId, cc->tAddCount);
                pthread_create(&id[0],NULL, addFunc_atomicInt_addAndGet,static_cast<TAtomicInt*>(cc));
                pthread_create(&id[1],NULL, addFunc_atomicInt_addAndGet,static_cast<TAtomicInt*>(cc));
                pthread_join(id[0],NULL);
                pthread_join(id[1],NULL);
                EXPECT_EQ(static_cast<AtomicInt32>(0x7fffffff - 1),cc->i32);
                free(cc);
                break;
            case 8:
                cc->i64 = static_cast<AtomicInt64>(0x7fffffffffff0000);
                cc->tAddCount = 0xffff / 2;
                //printf("--- tCaseId:%d tAddCount:%d ---\n", cc->tCaseId, cc->tAddCount);
                pthread_create(&id[0],NULL, addFunc_atomicInt_addAndGet,static_cast<TAtomicInt*>(cc));
                pthread_create(&id[1],NULL, addFunc_atomicInt_addAndGet,static_cast<TAtomicInt*>(cc));
                pthread_join(id[0],NULL);
                pthread_join(id[1],NULL);
                EXPECT_EQ(static_cast<AtomicInt64>(0x7fffffffffffffff - 1),cc->i64);
                free(cc);
                break;
        }
    }

}

void *addFunc_atomicInt_IncrementAndGet(void *arg)
{
    TAtomicInt *c = static_cast<TAtomicInt*>(arg);
    int i;

    switch(c->tCaseId)
    {
        case 1:
            for(i = 0; i < c->tAddCount; i++)
            {
                AtomicUInt8 p_ui8 = atomicInt_get(c->ui8);
                AtomicUInt8 a_ui8 = atomicInt_IncrementAndGet(c->ui8);
                EXPECT_LT(p_ui8, a_ui8);
            }
            break;
        case 2:
            for(i = 0; i < c->tAddCount; i++)
            {
                AtomicUInt16 p_ui16 = atomicInt_get(c->ui16);
                AtomicUInt16 a_ui16 = atomicInt_IncrementAndGet(c->ui16);
                EXPECT_LT(p_ui16, a_ui16);
            }
            break;
        case 3:
            for(i = 0; i < c->tAddCount; i++)
            {
                AtomicUInt32 p_ui32 = atomicInt_get(c->ui32);
                AtomicUInt32 a_ui32 = atomicInt_IncrementAndGet(c->ui32);
                EXPECT_LT(p_ui32, a_ui32);
            }
            break;
        case 4:
            for(i = 0; i < c->tAddCount; i++)
            {
                AtomicUInt64 p_ui64 = atomicInt_get(c->ui64);
                AtomicUInt64 a_ui64 = atomicInt_IncrementAndGet(c->ui64);
                EXPECT_LT(p_ui64, a_ui64);
            }
            break;
        case 5:
            for(i = 0; i < c->tAddCount; i++)
            {
                AtomicInt8 p_i8 = atomicInt_get(c->i8);
                AtomicInt8 a_i8 = atomicInt_IncrementAndGet(c->i8);
                EXPECT_LT(p_i8, a_i8);
            }
            break;
        case 6:
            for(i = 0; i < c->tAddCount; i++)
            {
                AtomicInt16 p_i16 = atomicInt_get(c->i16);
                AtomicInt16 a_i16 = atomicInt_IncrementAndGet(c->i16);
                EXPECT_LT(p_i16, a_i16);
            }
            break;
        case 7:
            for(i = 0; i < c->tAddCount; i++)
            {
                AtomicInt32 p_i32 = atomicInt_get(c->i32);
                AtomicInt32 a_i32 = atomicInt_IncrementAndGet(c->i32);
                EXPECT_LT(p_i32, a_i32);
            }
            break;
        case 8:
            for(i = 0; i < c->tAddCount; i++)
            {
                AtomicInt64 p_i64 = atomicInt_get(c->i64);
                AtomicInt64 a_i64 = atomicInt_IncrementAndGet(c->i64);
                EXPECT_LT(p_i64, a_i64);
            }
            break;
    }

    //printf("[%s]:i:%x\n",__func__,i);
    return NULL;
}

TEST(Base_UAtomic, atomicInt_atomicInt_IncrementAndGet)
{

    for(int i = 0; i < 8; ++i)
    {
        pthread_t id[4];
        TAtomicInt * cc = NULL;

        cc = static_cast<TAtomicInt *>(calloc(1,sizeof(TAtomicInt)));
        EXPECT_NE(static_cast<TAtomicInt *>(NULL),cc);
        cc->tCaseId = i + 1;

        switch(cc->tCaseId)
        {
            case 1:
                cc->tAddCount = static_cast<AtomicUInt8>(0xff / 2);
                //printf("--- tCaseId:%d tAddCount:%d ---\n", cc->tCaseId, cc->tAddCount);
                pthread_create(&id[0],NULL, addFunc_atomicInt_IncrementAndGet,static_cast<TAtomicInt*>(cc));
                pthread_create(&id[1],NULL, addFunc_atomicInt_IncrementAndGet,static_cast<TAtomicInt*>(cc));
                pthread_join(id[0],NULL);
                pthread_join(id[1],NULL);
                EXPECT_EQ(static_cast<AtomicUInt8>(0xff -1),cc->ui8);
                free(cc);
                break;
            case 2:
                cc->tAddCount = static_cast<AtomicUInt16>(0xffff / 2);
                //printf("--- tCaseId:%d tAddCount:%d ---\n", cc->tCaseId, cc->tAddCount);
                pthread_create(&id[0],NULL, addFunc_atomicInt_IncrementAndGet,static_cast<TAtomicInt*>(cc));
                pthread_create(&id[1],NULL, addFunc_atomicInt_IncrementAndGet,static_cast<TAtomicInt*>(cc));
                pthread_join(id[0],NULL);
                pthread_join(id[1],NULL);
                EXPECT_EQ(static_cast<AtomicUInt16>(0xffff - 1),cc->ui16);
                free(cc);
                break;
            case 3:
                cc->ui32 = static_cast<AtomicUInt32>(0xffff0000);
                cc->tAddCount = 0xffff / 2;
                //printf("--- tCaseId:%d tAddCount:%d ---\n", cc->tCaseId, cc->tAddCount);
                pthread_create(&id[0],NULL, addFunc_atomicInt_IncrementAndGet,static_cast<TAtomicInt*>(cc));
                pthread_create(&id[1],NULL, addFunc_atomicInt_IncrementAndGet,static_cast<TAtomicInt*>(cc));
                pthread_join(id[0],NULL);
                pthread_join(id[1],NULL);
                EXPECT_EQ(static_cast<AtomicUInt32>(0xffffffff - 1),cc->ui32);
                free(cc);
                break;
            case 4:
                cc->ui64 = static_cast<AtomicUInt64>(0xffffffffffff0000);
                cc->tAddCount = 0xffff / 2;
                //printf("--- tCaseId:%d tAddCount:%d ---\n", cc->tCaseId, cc->tAddCount);
                pthread_create(&id[0],NULL, addFunc_atomicInt_IncrementAndGet,static_cast<TAtomicInt*>(cc));
                pthread_create(&id[1],NULL, addFunc_atomicInt_IncrementAndGet,static_cast<TAtomicInt*>(cc));
                pthread_join(id[0],NULL);
                pthread_join(id[1],NULL);
                EXPECT_EQ(static_cast<AtomicUInt64>(0xffffffffffffffff - 1),cc->ui64);
                free(cc);
                break;
            case 5:
                cc->tAddCount = static_cast<AtomicInt8>(0x7f / 2);
                //printf("--- tCaseId:%d tAddCount:%d ---\n", cc->tCaseId, cc->tAddCount);
                pthread_create(&id[0],NULL, addFunc_atomicInt_IncrementAndGet,static_cast<TAtomicInt*>(cc));
                pthread_create(&id[1],NULL, addFunc_atomicInt_IncrementAndGet,static_cast<TAtomicInt*>(cc));
                pthread_join(id[0],NULL);
                pthread_join(id[1],NULL);
                EXPECT_EQ(static_cast<AtomicInt8>(0x7f -1),cc->i8);
                free(cc);
                break;
            case 6:
                cc->tAddCount = static_cast<AtomicInt16>(0x7fff / 2);
                //printf("--- tCaseId:%d tAddCount:%d ---\n", cc->tCaseId, cc->tAddCount);
                pthread_create(&id[0],NULL, addFunc_atomicInt_IncrementAndGet,static_cast<TAtomicInt*>(cc));
                pthread_create(&id[1],NULL, addFunc_atomicInt_IncrementAndGet,static_cast<TAtomicInt*>(cc));
                pthread_join(id[0],NULL);
                pthread_join(id[1],NULL);
                EXPECT_EQ(static_cast<AtomicInt16>(0x7fff - 1),cc->i16);
                free(cc);
                break;
            case 7:
                cc->i32 = static_cast<AtomicInt32>(0x7fff0000);
                cc->tAddCount = 0xffff / 2;
                //printf("--- tCaseId:%d tAddCount:%d ---\n", cc->tCaseId, cc->tAddCount);
                pthread_create(&id[0],NULL, addFunc_atomicInt_IncrementAndGet,static_cast<TAtomicInt*>(cc));
                pthread_create(&id[1],NULL, addFunc_atomicInt_IncrementAndGet,static_cast<TAtomicInt*>(cc));
                pthread_join(id[0],NULL);
                pthread_join(id[1],NULL);
                EXPECT_EQ(static_cast<AtomicInt32>(0x7fffffff - 1),cc->i32);
                free(cc);
                break;
            case 8:
                cc->i64 = static_cast<AtomicInt64>(0x7fffffffffff0000);
                cc->tAddCount = 0xffff / 2;
                //printf("--- tCaseId:%d tAddCount:%d ---\n", cc->tCaseId, cc->tAddCount);
                pthread_create(&id[0],NULL, addFunc_atomicInt_IncrementAndGet,static_cast<TAtomicInt*>(cc));
                pthread_create(&id[1],NULL, addFunc_atomicInt_IncrementAndGet,static_cast<TAtomicInt*>(cc));
                pthread_join(id[0],NULL);
                pthread_join(id[1],NULL);
                EXPECT_EQ(static_cast<AtomicInt64>(0x7fffffffffffffff - 1),cc->i64);
                free(cc);
                break;
        }
    }

}

void *addFunc_atomicInt_DecrementAndGet(void *arg)
{
    TAtomicInt *c = static_cast<TAtomicInt*>(arg);
    int i;

    switch(c->tCaseId)
    {
        case 1:
            for(i = 0; i < c->tAddCount; i++)
            {
                AtomicUInt8 p_ui8 = atomicInt_get(c->ui8);
                AtomicUInt8 a_ui8 = atomicInt_DecrementAndGet(c->ui8);
                EXPECT_GT(p_ui8, a_ui8);
            }
            break;
        case 2:
            for(i = 0; i < c->tAddCount; i++)
            {
                AtomicUInt16 p_ui16 = atomicInt_get(c->ui16);
                AtomicUInt16 a_ui16 = atomicInt_DecrementAndGet(c->ui16);
                EXPECT_GT(p_ui16, a_ui16);
            }
            break;
        case 3:
            for(i = 0; i < c->tAddCount; i++)
            {
                AtomicUInt32 p_ui32 = atomicInt_get(c->ui32);
                AtomicUInt32 a_ui32 = atomicInt_DecrementAndGet(c->ui32);
                EXPECT_GT(p_ui32, a_ui32);
            }
            break;
        case 4:
            for(i = 0; i < c->tAddCount; i++)
            {
                AtomicUInt64 p_ui64 = atomicInt_get(c->ui64);
                AtomicUInt64 a_ui64 = atomicInt_DecrementAndGet(c->ui64);
                EXPECT_GT(p_ui64, a_ui64);
            }
            break;
        case 5:
            for(i = 0; i < c->tAddCount; i++)
            {
                AtomicInt8 p_i8 = atomicInt_get(c->i8);
                AtomicInt8 a_i8 = atomicInt_DecrementAndGet(c->i8);
                EXPECT_GT(p_i8, a_i8);
            }
            break;
        case 6:
            for(i = 0; i < c->tAddCount; i++)
            {
                AtomicInt16 p_i16 = atomicInt_get(c->i16);
                AtomicInt16 a_i16 = atomicInt_DecrementAndGet(c->i16);
                EXPECT_GT(p_i16, a_i16);
            }
            break;
        case 7:
            for(i = 0; i < c->tAddCount; i++)
            {
                AtomicInt32 p_i32 = atomicInt_get(c->i32);
                AtomicInt32 a_i32 = atomicInt_DecrementAndGet(c->i32);
                EXPECT_GT(p_i32, a_i32);
            }
            break;
        case 8:
            for(i = 0; i < c->tAddCount; i++)
            {
                AtomicInt64 p_i64 = atomicInt_get(c->i64);
                AtomicInt64 a_i64 = atomicInt_DecrementAndGet(c->i64);
                EXPECT_GT(p_i64, a_i64);
            }
            break;
    }

    //printf("[%s]:i:%x\n",__func__,i);
    return NULL;
}

TEST(Base_UAtomic, atomicInt_atomicInt_DecrementAndGet)
{

    for(int i = 0; i < 8; ++i)
    {
        pthread_t id[4];
        TAtomicInt * cc = NULL;

        cc = static_cast<TAtomicInt *>(calloc(1,sizeof(TAtomicInt)));
        EXPECT_NE(static_cast<TAtomicInt *>(NULL),cc);
        cc->tCaseId = i + 1;

        switch(cc->tCaseId)
        {
            case 1:
                cc->tAddCount = static_cast<AtomicUInt8>(0xff / 2);
                cc->ui8 = static_cast<AtomicUInt8>(0xff - 1);
                //printf("--- tCaseId:%d tAddCount:%d ---\n", cc->tCaseId, cc->tAddCount);
                pthread_create(&id[0],NULL, addFunc_atomicInt_DecrementAndGet,static_cast<TAtomicInt*>(cc));
                pthread_create(&id[1],NULL, addFunc_atomicInt_DecrementAndGet,static_cast<TAtomicInt*>(cc));
                pthread_join(id[0],NULL);
                pthread_join(id[1],NULL);
                EXPECT_EQ(static_cast<AtomicUInt8>(0x00),cc->ui8);
                free(cc);
                break;
            case 2:
                cc->tAddCount = static_cast<AtomicUInt16>(0xffff / 2);
                cc->ui16 = static_cast<AtomicUInt16>(0xffff - 1);
                //printf("--- tCaseId:%d tAddCount:%d ---\n", cc->tCaseId, cc->tAddCount);
                pthread_create(&id[0],NULL, addFunc_atomicInt_DecrementAndGet,static_cast<TAtomicInt*>(cc));
                pthread_create(&id[1],NULL, addFunc_atomicInt_DecrementAndGet,static_cast<TAtomicInt*>(cc));
                pthread_join(id[0],NULL);
                pthread_join(id[1],NULL);
                EXPECT_EQ(static_cast<AtomicUInt16>(0x00),cc->ui16);
                free(cc);
                break;
            case 3:
                cc->tAddCount = 0xffff / 2;
                cc->ui32 = static_cast<AtomicUInt32>(0xffffffff - 1);
                //printf("--- tCaseId:%d tAddCount:%d ---\n", cc->tCaseId, cc->tAddCount);
                pthread_create(&id[0],NULL, addFunc_atomicInt_DecrementAndGet,static_cast<TAtomicInt*>(cc));
                pthread_create(&id[1],NULL, addFunc_atomicInt_DecrementAndGet,static_cast<TAtomicInt*>(cc));
                pthread_join(id[0],NULL);
                pthread_join(id[1],NULL);
                EXPECT_EQ(static_cast<AtomicUInt32>(0xffff0000),cc->ui32);
                free(cc);
                break;
            case 4:
                cc->tAddCount = 0xffff / 2;
                cc->ui64 = static_cast<AtomicUInt64>(0xffffffffffffffff - 1);
                //printf("--- tCaseId:%d tAddCount:%d ---\n", cc->tCaseId, cc->tAddCount);
                pthread_create(&id[0],NULL, addFunc_atomicInt_DecrementAndGet,static_cast<TAtomicInt*>(cc));
                pthread_create(&id[1],NULL, addFunc_atomicInt_DecrementAndGet,static_cast<TAtomicInt*>(cc));
                pthread_join(id[0],NULL);
                pthread_join(id[1],NULL);
                EXPECT_EQ(static_cast<AtomicUInt64>(0xffffffffffff0000),cc->ui64);
                free(cc);
                break;
            case 5:
                cc->i8 = static_cast<AtomicInt8>(0x7f - 1);
                cc->tAddCount = static_cast<AtomicInt8>(0x7f / 2);
                //printf("--- tCaseId:%d tAddCount:%d ---\n", cc->tCaseId, cc->tAddCount);
                pthread_create(&id[0],NULL, addFunc_atomicInt_DecrementAndGet,static_cast<TAtomicInt*>(cc));
                pthread_create(&id[1],NULL, addFunc_atomicInt_DecrementAndGet,static_cast<TAtomicInt*>(cc));
                pthread_join(id[0],NULL);
                pthread_join(id[1],NULL);
                EXPECT_EQ(static_cast<AtomicInt8>(0x00),cc->i8);
                free(cc);
                break;
            case 6:
                cc->i16 = static_cast<AtomicInt16>(0x7fff - 1);
                cc->tAddCount = static_cast<AtomicInt16>(0x7fff / 2);
                //printf("--- tCaseId:%d tAddCount:%d ---\n", cc->tCaseId, cc->tAddCount);
                pthread_create(&id[0],NULL, addFunc_atomicInt_DecrementAndGet,static_cast<TAtomicInt*>(cc));
                pthread_create(&id[1],NULL, addFunc_atomicInt_DecrementAndGet,static_cast<TAtomicInt*>(cc));
                pthread_join(id[0],NULL);
                pthread_join(id[1],NULL);
                EXPECT_EQ(static_cast<AtomicInt16>(0x00),cc->i16);
                free(cc);
                break;
            case 7:
                cc->i32 = static_cast<AtomicInt32>(0x7fffffff - 1);
                cc->tAddCount = 0xffff / 2;
                //printf("--- tCaseId:%d tAddCount:%d ---\n", cc->tCaseId, cc->tAddCount);
                pthread_create(&id[0],NULL, addFunc_atomicInt_DecrementAndGet,static_cast<TAtomicInt*>(cc));
                pthread_create(&id[1],NULL, addFunc_atomicInt_DecrementAndGet,static_cast<TAtomicInt*>(cc));
                pthread_join(id[0],NULL);
                pthread_join(id[1],NULL);
                EXPECT_EQ(static_cast<AtomicInt32>(0x7fff0000),cc->i32);
                free(cc);
                break;
            case 8:
                cc->i64 = static_cast<AtomicInt64>(0x7fffffffffffffff - 1);
                cc->tAddCount = 0xffff / 2;
                //printf("--- tCaseId:%d tAddCount:%d ---\n", cc->tCaseId, cc->tAddCount);
                pthread_create(&id[0],NULL, addFunc_atomicInt_DecrementAndGet,static_cast<TAtomicInt*>(cc));
                pthread_create(&id[1],NULL, addFunc_atomicInt_DecrementAndGet,static_cast<TAtomicInt*>(cc));
                pthread_join(id[0],NULL);
                pthread_join(id[1],NULL);
                EXPECT_EQ(static_cast<AtomicInt64>(0x7fffffffffff0000),cc->i64);
                free(cc);
                break;
        }
    }

}





