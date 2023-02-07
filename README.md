# cpp-concurrency
Learning about Concurrency using Modern C++

## What is concurrency?

Doing tasks concurrently : i.e doing two or more 'things' at the same time. Multiple things can happen at once, and the order matters. This may require some tasks to wait for another tasks (i.e synchronization is required). This is in contrast to parallelism, where everthing happens at the same time and instantaneously. 

Reason for concurrency : Better performance, and also out of necessity! (for example, in a orchestra, often times multiple instruments will play at the same time, and all have to be in synchronized fashion).

In a single core environment, context switching is used to achieve concurrency (i.e at a particular instant of time only one task is getting executed, but the task getting executed gets swtiched efficiently and appears as if multiple task happen at once.)

In a multi core environment, each core can be executing a task. That is, concurrency is achieved by parallelism.


## What is a thread?

It is a 'light weight process'. A single process can have many threads. Each thread will have its own stack frame, register set, PC, SP, etc. Each thread maintains its own 'State'.

However, the heap / code / data can be shared. Allows us to have multiple 'paths' / 'control flows' at the same time.

## What is data race?

When multiple threads are sharing a resource and some of them read / write to it, data might be inconsistent.
While one thread is writing into the resource, another thread might be reading in the *old* value, causing non determinism. We may or may not get expected results, due to which we need methods of solving data races.

Solution? Using locks / mutexes!
They ensure that a block of code is executed by only one thread at a time.

## Preventing dead locks
If a mutex / lock is never unlocked, we get into a dead lock. To prevent this, use std::lock_guard, which is based on RAII, so whenver lock_guard goes out of scope, the destructor will unlock the underlying mutex that was passed into the constructor.

std::scoped_lock is similar to lock_guard, but we can have several mutexes. It is a C++17 feature.

## Atomics
If a shared resource is very simple (i.e primitive / trivially copyable), std::atomic can be used rather than mutexes / lock guards.