# drinking-philosophers-cpp

Concurrent and Parallel Programming project implementing the **Drinking Philosophers Problem** in C++ using POSIX threads and two synchronization strategies: **Resource Ordering** and **Waiter (Arbiter)**. The model is graph-based — philosophers are vertices, shared bottles are edges.

---

## Project Structure

```
drinking-philosophers-cpp/
│
├── src/
│   ├── main.cpp                        # Entry point; runs all three test cases
│   │
│   ├── common/
│   │   ├── logger.hpp                  # Thread-safe logger (stdout + file)
│   │   ├── metrics.hpp                 # Per-philosopher metrics struct
│   │   └── states.hpp                  # Philosopher state enum (THINKING, THIRSTY, DRINKING)
│   │
│   ├── graphs/
│   │   ├── graph.hpp
│   │   └── graph.cpp                   # Adjacency matrix graph loaded from .txt files
│   │
│   ├── resources/
│   │   ├── bottle.hpp
│   │   ├── bottle.cpp                  # Shared resource (graph edge) with mutex
│   │   ├── bottle_manager.hpp
│   │   └── bottle_manager.cpp          # Creates and indexes all bottles for a graph
│   │
│   ├── philosophers/
│   │   ├── philosopher.hpp
│   │   └── philosopher.cpp             # Philosopher thread: think → thirsty → drink loop
│   │
│   ├── strategies/
│   │   ├── drinking_strategy.hpp       # Abstract base class for synchronization strategies
│   │   ├── ordered_strategy.hpp
│   │   ├── ordered_strategy.cpp        # Acquire bottles in ascending ID order (no deadlock)
│   │   ├── waiter_strategy.hpp
│   │   └── waiter_strategy.cpp         # Centralized arbiter using condition variable
│   │
│   ├── case1.txt                       # Case 1: 5 vertices, circular (degree 2)
│   ├── case2.txt                       # Case 2: 6 vertices, circular (degree 2)
│   └── case3.txt                       # Case 3: 12 vertices, circulant C(12,{1,2,3}) (degree 6)
│
├── build/                              # CMake build output
├── CMakeLists.txt
├── build_and_run.sh                    # Build and run script (generates results.txt)
└── results.txt                         # Execution log (generated at runtime)
```

---

## Test Cases

| Case | File       | Vertices | Topology                     | Drinks |
|------|------------|----------|------------------------------|--------|
| 1    | case1.txt  | 5        | Cycle C₅ (degree 2)          | 6      |
| 2    | case2.txt  | 6        | Cycle C₆ (degree 2)          | 6      |
| 3    | case3.txt  | 12       | Circulant C(12,{1,2,3}) (degree 6) | 3 |

Each case runs with both strategies sequentially.

---

## Synchronization Strategies

### 1. Resource Ordering (`OrderedStrategy`)
Bottles are always acquired in ascending ID order. This eliminates circular wait, preventing deadlocks without a central coordinator.

### 2. Waiter / Arbiter (`WaiterStrategy`)
A centralized waiter tracks which bottles are in use. A philosopher only proceeds when all required bottles are free, using a condition variable for synchronization.

---

## Philosopher Lifecycle

```
Thinking  ──►  Thirsty  ──►  Drinking  ──►  Thinking  ...
```

- **Thinking**: sleeps 0 to `degree(v)` seconds (random)
- **Thirsty**: waits to acquire all adjacent bottles
- **Drinking**: holds bottles for 1 second, then releases

---

## Build & Run

```bash
bash build_and_run.sh
```

Requires CMake and a C++17-compatible compiler. Output is printed to the console and saved to `results.txt`.

---

## References

- Chandy, K. M., & Misra, J. *The Drinking Philosophers Problem* (1984)
- Dijkstra, E. W. *The Dining Philosophers Problem*

## Author
- [**Vinícius dos Santos**](https://github.com/vinicOio222)
- [**Lucas Monteiro Amaral**](https://github.com/Lucas-M-Amaral)
