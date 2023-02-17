# customDataStructures

Name self explanatory\
Custom Data Structures for C++. Started as practice, ended up implementing several useful features\
Intended to provide support/accidental efficiency beyond what STL can offer.

## Functionalities and support : 

### Data Structures :
* Concrete Generic Data Structures
  * Collection
    * MutableCollection
      * List
        * Array
        * LinkedList
        * StaticArray ( Planned for CDS 0.2 )
          * HeapStaticArray ( Planned for CDS 0.2 )
          * StackStaticArray ( Planned for CDS 0.2 )
      * Map
        * HashMap
        * LinkedHashMap
        * TreeMap
      * Queue
        * ListQueue ( Planned for CDS 0.2 )
        * PriorityQueue ( Planned for CDS 0.2 )
      * Stack ( Planned for CDS 0.2 )
    * Set
      * HashSet
      * LinkedHashSet
      * TreeSet
* Primitives
  * Object
  * String - Scalable to any UTF format. std::string (stl) & QString (Qt) compatible
  * Primitive Data Type Wrappers - Int, Long, Float, ... ( TBD if kept )
  * Tuple
  * Union
  * Pair
  * Optional
  * Sequence ( In Re-Work, Planned for CDS 0.2 ) - Kotlin Sequence equivalent
  * ParallelSequence ( Planned for later releases )
  * Regex ( Planned for later releases )
  * Range 
  * Smart Pointers:
    * UniquePointer
    * SharedPointer
    * AtomicSharedPointer ( Rework Planned for CDS 0.2 )
    * ForeignPointer
* Functional Interfaces
  * Function wrapper - static functions / lambdas
  * Functional Interfaces and function object wrappers - simillar to Java Consumer/Supplier/Predicate/Function model, but scalable to 'n' parameters
  * Random
  * Generator ( Rework Required, Planned for later releases ) - co-routines
  * Time ( Planned for later releases )
  * Argument Parser ( Planned for later releases )
* Template Metaprogramming Basic Support - Platform / Compiler Independent behaviour
* Networking Objects
  * Socket ( Rework Required, planned for later releases )
  * Request ( Planned for later releases )
* Platform Dependent Objects
  * File ( Planned for later releases )
  * Path
* Stream Objects ( In/Out/String, Planned for later releases )
* Threading Objects
  * Atomic - Wrapper for stl Atomics for now.
  * Mutex
  * Thread
  * Object Locks
    * Lock
    * GroupLock
    * DeferredLock
  * Synchronized ( Planned for CDS 0.2 )
  * Semaphore
  * Async
  * Timer ( Planned for later releases ) - Periodic Callback Object
* Cryptography Functions ( Planned for later releases )
