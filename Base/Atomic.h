#ifndef ATOMIC_H
#define ATOMIC_H

#include "TypeDefs.h"
#include <atomic>

#define a_load_relaxed(x) x.load(std::memory_order_relaxed) 
#define a_load_consume(x) x.load(std::memory_order_consume) 
#define a_load_acquire(x) x.load(std::memory_order_acquire) 
#define a_load_acq_rel(x) x.load(std::memory_order_acq_rel) 
#define a_load(x) x.load() 
#define a_store_relaxed(x,v) x.store(v,std::memory_order_relaxed)
#define a_store_release(x,v) x.store(v,std::memory_order_release)
#define a_store(x,v) x.store(v)

//load consume
#define _a_load_c(x) std::atomic_load_explicit(&x,std::memory_order_consume)
//load aquire
#define _a_load_a(x) std::atomic_load_explicit(&x,std::memory_order_acquire)
//load relaxed
#define _a_load_rl(x) std::atomic_load_explicit(&x,std::memory_order_relaxed)
//load seq_cst
#define _a_load_sq(x) std::atomic_load_explicit(&x,std::memory_order_seq_cst) 

#define _a_load_order(x, y) std::atomic_load_explicit(&x, y) 

//store release
#define _a_store_rl(x,y) std::atomic_store_explicit(&x,y,std::memory_order_release)
//store relaxed
#define _a_store_rs(x,y) std::atomic_store_explicit(&x,y,std::memory_order_relaxed)
//store seq_cst
#define _a_store_sq(x,y) std::atomic_store_explicit(&x,y,std::memory_order_seq_cst)
//store compare_exchange
#define _a_ce_w(x,y) std::atomic_compare_exchange_weak(&x,&x,y)

#define _a_store_order(x,y,z) std::atomic_store_explicit(&x, &u, z)

#define a_int8 std::atomic<INT8>
#define a_uint8 std::atomic<UINT8>
#define a_int16 std::atomic<INT16>
#define a_uint16 std::atomic<UINT16>
#define a_int32 std::atomic<INT32>
#define a_uint32 std::atomic<UINT32>
#define a_int64 std::atomic<INT64>
#define a_uint64 std::atomic<UINT64>
#define a_single std::atomic<float>
#define a_double std::atomic<double>
#define a_ptr std::atomic<LPVOID>
#define a_flag std::atomic_flag

#endif