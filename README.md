# KKY-UI

[![Build Status](https://travis-ci.org/peldax/KKY-UI.svg?branch=master)](https://travis-ci.org/peldax/KKY-UI)

##### First semester 2015/2016
##### Programming language - C++
##### Language of Comments - English

This is semestral work for subject KKY / UI (Artificial Inteligence) at University of West Bohemia - Faculty of Applied Sciences.

This little application computes the fastest way how to spill a fluid between different bottles to get desired amount in each bottle.
This algorithm uses Hill-Climbing ranking system to enormously enhance its performance compared to standard BFS.

Please note that Hill-Climbing is not A* algorithm.

## Example

You can either insert data manualy...

```
Insert number of units:
> 3
Insert maximum size of 1. unit:
> 9
Insert maximum size of 2. unit:
> 8
Insert maximum size of 3. unit:
> 2
Insert desired state of 1. unit:
> 4
Insert desired state of 2. unit:
> 3
Insert desired state of 3. unit:
> 2
Insert initial state of 1. unit:
> 9
Insert initial state of 2. unit:
> 0
Insert initial state of 3. unit:
> 0
```

...or pass them as parameters (sizes of units, desired state, initial state)

##### ./KKY-UI 9 8 2 4 3 2 9 0 0

### Output:
 
 ```
 9 0 0
Moved from unit #1 to unit #3
 7 0 2
Moved from unit #1 to unit #2
 0 7 2
Moved from unit #3 to unit #1
 2 7 0
Moved from unit #2 to unit #3
 2 5 2
Moved from unit #3 to unit #1
 4 5 0
Moved from unit #2 to unit #3
 4 3 2
```

## Build

Sources are automatically tested for build errors (using Travis CI) on Linux and OSX, using both gcc and clang.

```
cd sources
mkdir build
cd build
cmake ..
make
```


