/*
#include "uAtomic.h"


type atomicInt_get(type *ptrAtomicInt){ return __sync_val_compare_and_swap(ptrAtomicInt, 0, 0);}
type atomicInt_getAndSet(type *ptrAtomicInt, type newValue) { return __sync_lock_test_and_set(ptrAtomicInt, newValue);}
type atomicInt_getAndAdd(type *ptrAtomicInt, type atomicInt) { return __sync_fetch_and_add(ptrAtomicInt, atomicInt);}
type atomicInt_addAndGet(type *ptrAtomicInt, type atomicInt) { return __sync_add_and_fetch(ptrAtomicInt, atomicInt);}
type atomicInt_IncrementAndGet(type *ptrAtomicInt) { return __sync_add_and_fetch(ptrAtomicInt, 1);}
type atomicInt_DecrementAndGet(type *ptrAtomicInt) { return __sync_add_and_fetch(ptrAtomicInt, -1);}
*/
