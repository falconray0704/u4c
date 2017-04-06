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

    for (int i = 0; i < 17; i++)
    //for (int i = 0; i < 16 * 64 * 1024; i++)
    //for (int i = 0; i < UVectorInitSize + 1; i++)
    {
        void ** preDataAddr = uVector.data;
        int preSize = uVector.size;
        int preCount = uVector.count;

        TData * ptd = static_cast<TData *>(malloc(sizeof(TData)));
        ptd->data = i;

        EXPECT_NE(static_cast<TData *>(NULL),ptd);
        EXPECT_EQ(static_cast<void *>(ptd), addObj_UVector(&uVector, static_cast<void *>(ptd)));
        EXPECT_EQ(static_cast<void *>(ptd), static_cast<void *>(uVector.data[uVector.count - 1]));
        EXPECT_EQ(preCount + 1, uVector.count);

        if(preSize != uVector.size)
            countRemalloc++;
        if(preDataAddr != uVector.data)
            countRepage++;
    }

    //EXPECT_EQ(16 * 64 * 1024, uVector.count);
    EXPECT_EQ(17, uVector.count);
    EXPECT_EQ(NULL, deleteObj_UVector(NULL, 0) );
    EXPECT_EQ(NULL, deleteObj_UVector(&uVector, uVector.count) );
    EXPECT_EQ(NULL, deleteObj_UVector(&uVector, uVector.count + 1 ) );
    EXPECT_EQ(NULL, deleteObj_UVector(&uVector, -1 ) );

    int preCount = -1;
    void * expectedObj = NULL;
    void * deletedObj = NULL;

    for (int i = 1, delIdx = 1; i < uVector.count; i++, delIdx++ )
    {
        preCount = uVector.count;
        //int delIdx = uVector.count == 1 ? 0 : i + 1;
        //delIdx--;

        expectedObj = uVector.data[1];
        deletedObj = deleteObj_UVector(&uVector, 1);

        EXPECT_EQ( delIdx, (static_cast<TData *>(deletedObj))->data);
        EXPECT_NE( static_cast<void *>(NULL), deletedObj);
        EXPECT_EQ( expectedObj, deletedObj);

        EXPECT_EQ(preCount, uVector.count + 1 );
        EXPECT_EQ( static_cast<void *>(NULL), uVector.data[preCount - 1]);
        EXPECT_NE( static_cast<void *>(NULL), uVector.data[preCount - 2]);

        free( deletedObj );
    }

    preCount = uVector.count;
    expectedObj = uVector.data[0];
    deletedObj = deleteObj_UVector(&uVector, 0);

    EXPECT_EQ( 0, (static_cast<TData *>(deletedObj))->data);
    EXPECT_NE( static_cast<void *>(NULL), deletedObj);
    EXPECT_EQ( expectedObj, deletedObj);

    EXPECT_EQ(preCount, uVector.count + 1 );
    EXPECT_EQ( static_cast<void *>(NULL), uVector.data[preCount - 1]);
    EXPECT_NE( static_cast<void *>(NULL), uVector.data[preCount - 2]);

    free( deletedObj );

    free(uVector.data);
}

TEST(Base_UVector, get_UVector)
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

    for (int i = 0; i < 17; i++)
    {
        void ** preDataAddr = uVector.data;
        int preSize = uVector.size;
        int preCount = uVector.count;

        TData * ptd = static_cast<TData *>(malloc(sizeof(TData)));
        ptd->data = i;

        EXPECT_NE(static_cast<TData *>(NULL),ptd);
        EXPECT_EQ(static_cast<void *>(ptd), addObj_UVector(&uVector, static_cast<void *>(ptd)));
        EXPECT_EQ(static_cast<void *>(ptd), static_cast<void *>(uVector.data[uVector.count - 1]));
        EXPECT_EQ(preCount + 1, uVector.count);

        if(preSize != uVector.size)
            countRemalloc++;
        if(preDataAddr != uVector.data)
            countRepage++;
    }

    int preCount = -1;
    void * expectedObj = NULL;

    EXPECT_EQ(static_cast<void *>(NULL), get_UVector(NULL, 0)); 
    EXPECT_EQ(static_cast<void *>(NULL), get_UVector(&uVector, -1));
    EXPECT_EQ(static_cast<void *>(NULL), get_UVector(&uVector, 17));
    EXPECT_EQ(static_cast<void *>(NULL), get_UVector(&uVector, 18));

    for (int i = 0; i < uVector.count; i++)
    {
        void * getObj = NULL;

        preCount = uVector.count;
        expectedObj = uVector.data[i];
        getObj = get_UVector(&uVector, i);

        EXPECT_NE( static_cast<void *>(NULL), getObj);
        EXPECT_EQ( expectedObj, getObj);
        EXPECT_EQ( i, static_cast<TData*>(getObj)->data);
        EXPECT_EQ(preCount, uVector.count );
    }

    EXPECT_EQ(17, uVector.count);
    EXPECT_EQ(NULL, deleteObj_UVector(NULL, 0) );
    EXPECT_EQ(NULL, deleteObj_UVector(&uVector, uVector.count) );
    EXPECT_EQ(NULL, deleteObj_UVector(&uVector, uVector.count + 1 ) );
    EXPECT_EQ(NULL, deleteObj_UVector(&uVector, -1 ) );

    preCount = -1;
    expectedObj = NULL;
    void * deletedObj = NULL;

    for (int i = 1, delIdx = 1; i < uVector.count; i++, delIdx++ )
    {
        preCount = uVector.count;
        //int delIdx = uVector.count == 1 ? 0 : i + 1;
        //delIdx--;

        expectedObj = uVector.data[1];
        deletedObj = deleteObj_UVector(&uVector, 1);

        EXPECT_EQ( delIdx, (static_cast<TData *>(deletedObj))->data);
        EXPECT_NE( static_cast<void *>(NULL), deletedObj);
        EXPECT_EQ( expectedObj, deletedObj);

        EXPECT_EQ(preCount, uVector.count + 1 );
        EXPECT_EQ( static_cast<void *>(NULL), uVector.data[preCount - 1]);
        EXPECT_NE( static_cast<void *>(NULL), uVector.data[preCount - 2]);

        free( deletedObj );
    }

    preCount = uVector.count;
    expectedObj = uVector.data[0];
    deletedObj = deleteObj_UVector(&uVector, 0);

    EXPECT_EQ( 0, (static_cast<TData *>(deletedObj))->data);
    EXPECT_NE( static_cast<void *>(NULL), deletedObj);
    EXPECT_EQ( expectedObj, deletedObj);

    EXPECT_EQ(preCount, uVector.count + 1 );
    EXPECT_EQ( static_cast<void *>(NULL), uVector.data[preCount - 1]);
    EXPECT_NE( static_cast<void *>(NULL), uVector.data[preCount - 2]);

    free( deletedObj );

    free(uVector.data);
}

TEST(Base_UVector, set_UVector)
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

    for (int i = 0; i < 17; i++)
    {
        void ** preDataAddr = uVector.data;
        int preSize = uVector.size;
        int preCount = uVector.count;

        TData * ptd = static_cast<TData *>(malloc(sizeof(TData)));
        ptd->data = i;

        EXPECT_NE(static_cast<TData *>(NULL),ptd);
        EXPECT_EQ(static_cast<void *>(ptd), addObj_UVector(&uVector, static_cast<void *>(ptd)));
        EXPECT_EQ(static_cast<void *>(ptd), static_cast<void *>(uVector.data[uVector.count - 1]));
        EXPECT_EQ(preCount + 1, uVector.count);

        if(preSize != uVector.size)
            countRemalloc++;
        if(preDataAddr != uVector.data)
            countRepage++;
    }

    int preCount = -1;
    void * expectedObj = NULL;

    EXPECT_EQ(static_cast<void *>(NULL), get_UVector(NULL, 0)); 
    EXPECT_EQ(static_cast<void *>(NULL), get_UVector(&uVector, -1));
    EXPECT_EQ(static_cast<void *>(NULL), get_UVector(&uVector, 17));
    EXPECT_EQ(static_cast<void *>(NULL), get_UVector(&uVector, 18));
    for (int i = 0; i < uVector.count; i++)
    {
        void * getObj = NULL;

        preCount = uVector.count;
        expectedObj = uVector.data[i];
        getObj = get_UVector(&uVector, i);

        EXPECT_NE( static_cast<void *>(NULL), getObj);
        EXPECT_EQ( expectedObj, getObj);
        EXPECT_EQ( i, static_cast<TData*>(getObj)->data);
        EXPECT_EQ(preCount, uVector.count );
    }


    TData tt = {100};
    EXPECT_EQ(static_cast<void *>(NULL), set_UVector(NULL, 0, &tt ));

    EXPECT_EQ(static_cast<void *>(NULL), set_UVector(&uVector, -1,&tt ));
    EXPECT_EQ(static_cast<void *>(NULL), set_UVector(&uVector, 17, &tt));
    EXPECT_EQ(static_cast<void *>(NULL), set_UVector(&uVector, 18, &tt));

    EXPECT_EQ(static_cast<void *>(NULL), set_UVector(&uVector, 16, NULL ));
    for (int i = 0; i < uVector.count; i++)
    {
        void * oldObj = NULL;

        preCount = uVector.count;
        expectedObj = uVector.data[i];
        TData * ptd = static_cast<TData *>(malloc(sizeof(TData)));
        EXPECT_NE( static_cast<TData *>(NULL), ptd);
        ptd->data = i + 17;

        oldObj = set_UVector(&uVector, i, static_cast<void *>(ptd));

        EXPECT_NE( static_cast<void *>(NULL), oldObj);
        EXPECT_EQ( i, static_cast<TData *>(oldObj)->data);
        EXPECT_EQ( uVector.data[i], ptd);
        EXPECT_EQ( static_cast<TData *>(uVector.data[i])->data, i + 17);

        EXPECT_EQ(preCount, uVector.count );
    }

    for (int i = 0; i < uVector.count; i++)
    {
        void * getObj = NULL;

        preCount = uVector.count;
        expectedObj = uVector.data[i];
        getObj = get_UVector(&uVector, i);

        EXPECT_NE( static_cast<void *>(NULL), getObj);
        EXPECT_EQ( expectedObj, getObj);
        EXPECT_EQ( i + 17, static_cast<TData*>(getObj)->data);
        EXPECT_EQ(preCount, uVector.count );
    }

    EXPECT_EQ(17, uVector.count);
    EXPECT_EQ(NULL, deleteObj_UVector(NULL, 0) );
    EXPECT_EQ(NULL, deleteObj_UVector(&uVector, uVector.count) );
    EXPECT_EQ(NULL, deleteObj_UVector(&uVector, uVector.count + 1 ) );
    EXPECT_EQ(NULL, deleteObj_UVector(&uVector, -1 ) );

    preCount = -1;
    expectedObj = NULL;
    void * deletedObj = NULL;

    for (int i = 1, delIdx = 1; i < uVector.count; i++, delIdx++ )
    {
        preCount = uVector.count;
        //int delIdx = uVector.count == 1 ? 0 : i + 1;
        //delIdx--;

        expectedObj = uVector.data[1];
        deletedObj = deleteObj_UVector(&uVector, 1);

        EXPECT_EQ( delIdx + 17, (static_cast<TData *>(deletedObj))->data);
        EXPECT_NE( static_cast<void *>(NULL), deletedObj);
        EXPECT_EQ( expectedObj, deletedObj);

        EXPECT_EQ(preCount, uVector.count + 1 );
        EXPECT_EQ( static_cast<void *>(NULL), uVector.data[preCount - 1]);
        EXPECT_NE( static_cast<void *>(NULL), uVector.data[preCount - 2]);

        free( deletedObj );
    }

    preCount = uVector.count;
    expectedObj = uVector.data[0];
    deletedObj = deleteObj_UVector(&uVector, 0);

    EXPECT_EQ( 0 + 17, (static_cast<TData *>(deletedObj))->data);
    EXPECT_NE( static_cast<void *>(NULL), deletedObj);
    EXPECT_EQ( expectedObj, deletedObj);

    EXPECT_EQ(preCount, uVector.count + 1 );
    EXPECT_EQ( static_cast<void *>(NULL), uVector.data[preCount - 1]);
    EXPECT_NE( static_cast<void *>(NULL), uVector.data[preCount - 2]);

    free( deletedObj );

    free(uVector.data);
}




