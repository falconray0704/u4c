/*
 * =====================================================================================
 *
 *       Filename:  Vector.cc
 *
 *    Description:  unitest for UVector
 *
 *        Version:  1.0
 *        Created:  04/01/2017 10:50:12 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  FalconRay
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <gtest/gtest.h>
#include <base/vector.h>

TEST(Base_UVector, init_UVector)
{
    UVector uVector = create_UVector();

    EXPECT_EQ(static_cast<UVector *>(NULL), init_UVector(NULL));

    EXPECT_NE(static_cast<UVector *>(NULL), init_UVector(&uVector));
    EXPECT_EQ(NULL, uVector.data);
    EXPECT_EQ(0, uVector.size);
    EXPECT_EQ(0, uVector.count);
}

TEST(Base_UVector, free_UVector)
{

    UVector uVector = create_UVector();

    EXPECT_EQ(static_cast<UVector *>(NULL), free_UVector(NULL));

    uVector.size = UVectorInitSize;
    uVector.data = static_cast<void **>(malloc( sizeof(void * ) * uVector.size));

    EXPECT_NE(static_cast<UVector *>(NULL), free_UVector(&uVector));
    EXPECT_EQ(static_cast<void **>(NULL), uVector.data);
    EXPECT_EQ(0, uVector.size);
    EXPECT_EQ(0, uVector.count);

}

typedef struct { int data; } TData;
#define create_TData(data) { data }

TEST(Base_UVector, addObj_UVector)
{

    UVector uVector = create_UVector();

    EXPECT_NE(static_cast<UVector *>(NULL), init_UVector(&uVector));

    TData tdn;
    EXPECT_EQ(static_cast<void *>(NULL), addObj_UVector(NULL, static_cast<void *>(&tdn)));
    EXPECT_EQ(static_cast<void *>(NULL), addObj_UVector(&uVector, static_cast<void *>(NULL)));
    EXPECT_EQ(static_cast<void *>(NULL), addObj_UVector(NULL, static_cast<void *>(NULL)));

    EXPECT_EQ(static_cast<void **>(NULL), uVector.data);
    EXPECT_EQ(0, uVector.size);
    EXPECT_EQ(0, uVector.count);

    int countRemalloc = 0;
    int countRepage = 0;

    for (int i = 0; i < 16 * 64 * 1024; i++)
    //for (int i = 0; i < UVectorInitSize + 1; i++)
    {
        void ** preDataAddr = uVector.data;
        int preSize = uVector.size;
        int preCount = uVector.count;

        TData * ptd = static_cast<TData *>(malloc(sizeof(TData)));
        EXPECT_NE(static_cast<TData *>(NULL),ptd);

        EXPECT_EQ(static_cast<void *>(ptd), addObj_UVector(&uVector, static_cast<void *>(ptd)));
        EXPECT_EQ(static_cast<void *>(ptd), static_cast<void *>(uVector.data[uVector.count - 1]));
        EXPECT_EQ(preCount + 1, uVector.count);

        if(preSize != uVector.size)
            countRemalloc++;
        if(preDataAddr != uVector.data)
            countRepage++;

        free(ptd);
    }

    free(uVector.data);
    printf("===== remalloc: %d times\n",countRemalloc);
    printf("===== repage: %d times\n",countRepage);

}

TEST(Base_UVector, deleteObj_UVector)
{

    UVector uVector = create_UVector();

    EXPECT_NE(static_cast<UVector *>(NULL), init_UVector(&uVector));

    TData tdn;
    EXPECT_EQ(static_cast<void *>(NULL), addObj_UVector(NULL, static_cast<void *>(&tdn)));
    EXPECT_EQ(static_cast<void *>(NULL), addObj_UVector(&uVector, static_cast<void *>(NULL)));
    EXPECT_EQ(static_cast<void *>(NULL), addObj_UVector(NULL, static_cast<void *>(NULL)));

    EXPECT_EQ(static_cast<void **>(NULL), uVector.data);
    EXPECT_EQ(0, uVector.size);
    EXPECT_EQ(0, uVector.count);

    int countRemalloc = 0;
    int countRepage = 0;

    for (int i = 0; i < 16 * 64 * 1024; i++)
    //for (int i = 0; i < UVectorInitSize + 1; i++)
    {
        void ** preDataAddr = uVector.data;
        int preSize = uVector.size;
        int preCount = uVector.count;

        TData * ptd = static_cast<TData *>(malloc(sizeof(TData)));
        EXPECT_NE(static_cast<TData *>(NULL),ptd);

        EXPECT_EQ(static_cast<void *>(ptd), addObj_UVector(&uVector, static_cast<void *>(ptd)));
        EXPECT_EQ(static_cast<void *>(ptd), static_cast<void *>(uVector.data[uVector.count - 1]));
        EXPECT_EQ(preCount + 1, uVector.count);

        if(preSize != uVector.size)
            countRemalloc++;
        if(preDataAddr != uVector.data)
            countRepage++;
    }

    EXPECT_EQ(16 * 64 * 1024, uVector.count);
    EXPECT_EQ(NULL, deleteObj_UVector(NULL, 0) );
    EXPECT_EQ(NULL, deleteObj_UVector(&uVector, uVector.count) );
    EXPECT_EQ(NULL, deleteObj_UVector(&uVector, uVector.count + 1 ) );
    EXPECT_EQ(NULL, deleteObj_UVector(&uVector, -1 ) );

    for (; uVector.count > 0; )
    {
        int preCount = uVector.count;
        int centerIdx = uVector.count == 1 ? 1 : uVector.count / 2;
        centerIdx--;

        void * expectedObj = uVector.data[centerIdx];
        void * deletedObj = deleteObj_UVector(&uVector, centerIdx);

        EXPECT_NE( static_cast<void *>(NULL), deletedObj);
        EXPECT_EQ( expectedObj, deletedObj);

        EXPECT_EQ(preCount, uVector.count + 1 );
        EXPECT_EQ( static_cast<void *>(NULL), uVector.data[preCount - 1]);
        EXPECT_NE( static_cast<void *>(NULL), uVector.data[preCount - 2]);

        free( deletedObj );


    }

    free(uVector.data);

}

