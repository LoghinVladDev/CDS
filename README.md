# customDataStructures

Name self explanatory\
Custom Data Structures for C++. Started as practice, ended up implementing several useful features\
Intended to provide support beyond what STL can offer

## Functionalities and support : 

### Data Structures :
* Concrete Generic Data Structures
  * Double Linked List
  * Single Linked List ( In Work )
  * Ordered, Unordered Sets
  * Hash Maps
  * Unordered Map ( In Work )
  * Ordered Map ( In Work )
  * Dynamic Arrays
  * Static Arrays ( In Work )
* Abstract Generic Data Structures 
  * Object
  * Map
  * MultiMap ( In Work )
  * List
  * SetBase
  * Collection
  * BinaryTree ( Later Update )
* Particular Case Data Structures
  * B-Tree ( Partial Support )
* Utility 
  * JSON - Parsing, Data Structure
  * Range
  * Tuple ( Partial Support )  
  * Random  
  * Object Views - reworked to Sequence - Functional Programming Support
  * Parallel Sequence - Planned
  * Threading
    * Thread
    * Semaphore
    * Mutex
  * Coroutines
    * Generator Functions  
  * Primitives
    * Pointer - Unique, Shared, Foreign
    * Reference
    * Optional
    * Pair
    * String
    * Object Encapsulators 
      * Integer
      * Long
      * Boolean
      * Float
      * Double

## Since 03/06/21: Use Sequence instead of View

### Note 1

#### Issue Fixed Since 02/04/21

Original usecase : 

```c++
String("ABCDADABC").view()
    .map(String::lowerChar)
    .filter(String::isConsonant)
    .filter(String::isLowerChar)
    .distinct()
    .sorted()
    .map(String::upperChar)
    .forEach([](auto c){std::cout << c;});

/// prints nothing
```

Current Runtime:

```c++
String("ABCDADABC").view()
    .map(String::lowerChar)
    .filter(String::isConsonant)
    .filter(String::isLowerChar)
    .distinct()
    .sorted()
    .map(String::upperChar)
    .forEach([](auto c){std::cout << c;});

/// prints BCD
```

#### Original Issue

In regards to Views, some use cases might not entirely work. 
One such case is strict mapper + filter + alterer ordering
Prior to the usage of an alterer (i.e. sorter), all mappers are applied, even ones below

Take the following case : 

```c++
String("ABCDADABC").view()
    .map(String::lowerChar)
    .filter(String::isConsonant)
    .distinct()
    .sorted()
    .forEach([](auto c){std::cout << c;});
/// prints bcd
```

Works just fine

Adding a filter for safety

```c++
String("ABCDADABC").view()
    .map(String::lowerChar)
    .filter(String::isConsonant)
    .filter(String::isLowerChar)
    .distinct()
    .sorted()
    .forEach([](auto c){std::cout << c;});
/// prints bcd again
```

Works fine too, all chars are lower

But if we add a mapper to upper after sorting

```c++
String("ABCDADABC").view()
    .map(String::lowerChar)
    .filter(String::isConsonant)
    .filter(String::isLowerChar)
    .distinct()
    .sorted()
    .map(String::upperChar)
    .forEach([](auto c){std::cout << c;});

/// prints nothing
```

Does not print, even if logically should.

Happens because views are only conceptual, and sorting
happens at the end of the iteration. Pipelining is not staged


Pipeline operations are, regardless of order
pipeline creation 
mapping
filtering
altering
consuming
pipeline destruction
