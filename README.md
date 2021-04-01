# customDataStructures

Name self explanatory\
Custom Data Structures for C++. Started as practice, ended up implementing several useful features

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
  * Object Views - See Note 1
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
  
#### Note 1
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
