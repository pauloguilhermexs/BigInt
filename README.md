# BigInt - Arbitrary Precision Integer Library

A lightweight, high-performance C++ class designed to represent and perform arithmetic operations on integers with an unlimited number of digits (arbitrary precision). 

## 🚀 Features

- **Unlimited Precision:** Handles positive, negative, and zero values with as many digits as your system's memory allows.
- **Dynamic Memory Management:** Uses low-level raw pointers (`new[]` and `delete[]`) rather than standard containers to handle digits dynamically and efficiently.
- **Custom Input/Output Streams:** Fully overloaded `<<` and `>>` operators for seamless console interactions.
- **Full Operator Suite:** Implements basic arithmetic, unary signs, pre/post-increment, bitwise-like base-10 shifts (`<<`, `>>`), and relational comparisons.
- **Interactive Command-Line Calculator:** Works out-of-the-box with an interactive CLI mini-calculator that supports step-by-step history and operations.

---

## 🛠️ Architecture & Constraints

To strictly satisfy the strict pedagogical constraints of the course, this library is built **without** advanced modern C++ abstractions:
- 🚫 **No STL Containers/Algorithms:** Absolutely no `std::vector`, `std::list`, `std::copy`, etc.
- 🚫 **No Exceptions:** Error handling is managed via stream states (`ios::failbit`) and safe warnings on `std::cerr`.
- 🚫 **No Templates/Inheritance:** Focused purely on clean object-oriented design and raw memory manipulation.

### Internal Representation
Each `BigInt` instance is comprised of three core attributes:
- `bool neg`: `true` if the number is negative, `false` otherwise.
- `int nDig`: The precise count of digits currently stored ($\ge 1$).
- `int8_t* d`: A raw dynamic array containing the digits (values `0` through `9`).

> ⚠️ **Note:** Digits are stored in **reverse order** (the least significant digit is at `d[0]`) to simplify the implementation of manual arithmetic pipelines (like carry and borrow steps).

---

## ⚙️ Supported Operations

| Operator / Method | Description |
| :--- | :--- |
| `+`, `-` (Binary) | Addition and Subtraction with custom carry/borrow logic. |
| `*` | Multiplication using digit-by-digit expansion. |
| `/`, `%`, `division()` | Base-10 long division yielding Quotient and Remainder via successive subtractions. |
| `!` | Factorial calculator for `BigInt`. |
| `++`, `--` | Pre-fixed and Post-fixed increment/decrement optimizations. |
| `<<`, `>>` (Int) | Base-10 shift operators (e.g., `375 << 2` yields `37500`). |
| `==`, `!=`, `<`, `<=`, `>`, `>=` | Full set of lexicographical and algebraic comparison operators. |
| `toInt()` | Safely attempts to downcast the `BigInt` into a native `long long int` with robust overflow clipping and `cerr` notifications. |

---

## 💻 Getting Started

### Prerequisites
- A modern C++ compiler supporting at least **C++11** (e.g., `g++` or `clang++`).

### Compilation
Compile your custom implementation files alongside the provided test or main interface:

```bash
g++ -std=c++11 main.cpp bigint.cpp -o bigint_calc
