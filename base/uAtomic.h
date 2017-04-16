
#ifndef U4C_BASE_ATOMIC_H
#define U4C_BASE_ATOMIC_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/types.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef int8_t AtomicInt8;
typedef int16_t AtomicInt16;
typedef int32_t AtomicInt32;
typedef int64_t AtomicInt64;

typedef uint8_t AtomicUInt8;
typedef uint16_t AtomicUInt16;
typedef uint32_t AtomicUInt32;
typedef uint64_t AtomicUInt64;


#define atomicInt_get(atomicInt) __sync_val_compare_and_swap(&atomicInt, 0, 0)
#define atomicInt_getAndSet(atomicInt, newValue) __sync_lock_test_and_set(&atomicInt, newValue)
#define atomicInt_getAndAdd(atomicInt, value) __sync_fetch_and_add(&atomicInt, value)
#define atomicInt_addAndGet(atomicInt, value) __sync_add_and_fetch(&atomicInt, value)
#define atomicInt_IncrementAndGet(atomicInt) __sync_add_and_fetch(&atomicInt, 1)
#define atomicInt_DecrementAndGet(atomicInt) __sync_add_and_fetch(&atomicInt, -1)

#ifdef __cplusplus
}
#endif

#endif  // MUDUO_BASE_ATOMIC_H
