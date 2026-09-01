# CHanceC Bytecode

CHance is a C-like language designed to support any developer's ideas. Along with this–to remain portable–CHance uses a vm-ready bytecode called CEIL. Any information, standard, or rule shall be dictated solely in the CESPEC (CHance Specification).

## CHance Specification (CESPEC)

### 1. Stack
1. Permitted Types
    - `i32`: **32-BIT INTEGER**: An integer guaranteed to be 32 bits.
    - `i64`: **64-BIT INTEGER**: An integer guaranteed to be 64 bits.
    - `

### 2. Instructions
1. Loading
    - `ld.l [index16]`: **LOAD LOCAL**: Loads a local from `LOCAL[index16]` and pushes it to the stack.
