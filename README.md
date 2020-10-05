# memoryManagement
This program shows the functionality of the follow page replacement algorithms: LRU and Working Set.

### Main idea

This project is implemented in C language, and the main idea is to visually represent two of the most famous page replacing algorithms in memory management.

### Page table

There are several types of page tables, which are optimized for different requirements. In this project we tried to implement the Inverted Page Table format.

### Modules, compiling and running

We simply have 2 folders: 1) Working Set
                          2) WSClock

*Both of these folders has the LRU implementation.*

### Working Set

This folder contains the "simple" working set algorithm.
To compile just type ```make```

And to run: ``` ./main WS frames q MaxReports WindowSize ```

https://www.informit.com/articles/article.aspx?p=25260&seqNum=9

### WSClock

This folder contains an alternative algorithm for working set, the "clock algorithm" .

To compile just type  ```make```

And to run: ``` ./main WS Frames q MaxReports ```

https://www.informit.com/articles/article.aspx?p=25260&seqNum=10

### LRU

In both folders,to choose and run the LRU algorithm,simple type:

```make ```

``` ./main LRU Frames q MaxReports  ```

https://www.geeksforgeeks.org/program-for-least-recently-used-lru-page-replacement-algorithm/

### Further Informations

This project has also the explanation of the project in greek (LS.pdf) , and the necessary informations in greek (P2Greek.pdf). 

*This project is part of the course: Operational Systems , Winter of 2019. University of Athens, DiT.*




