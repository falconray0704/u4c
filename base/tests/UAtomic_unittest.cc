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
                AtomicInt8 _i8 = atomicInt_getAndSet(i8, 0x55);
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

