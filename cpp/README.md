# AoC C++

## Notes

### Why am I using the STL helpers
Since I'm using C++ I will use the language in a natural manner, if you want to see a more algorithmic version I will do a C version soon.

### Why C++20?
C++20 is not really brand new, even if it's not fully implemented by some compilers (e.g GCC or Clang) mainly due Modules (P1103R3), they're getting closer to make it as default version, (Cmon we're in 2025 already).

### Why parsing inputs?
Why not, I reject to create .hpp as inputs separatedly.

### How do I compile this?
```cmake -S . -B build -DCMAKE_BUILD_TYPE=Release && cmake --build build```

