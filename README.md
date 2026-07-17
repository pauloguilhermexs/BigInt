# BigInt - Arbitrary Precision Integer Library

A lightweight, high-performance C++ class designed to represent and perform arithmetic operations on integers with an unlimited number of digits (arbitrary precision). This project was developed as an academic assignment for the Department of Computer Engineering and Automation (DCA) at the Federal University of Rio Grande do Norte (UFRN).

## 🚀 Features

- **Unlimited Precision:** Handles positive, negative, and zero values with as many digits as your system's memory allows[cite: 1].
- **Dynamic Memory Management:** Uses low-level raw pointers (`new[]` and `delete[]`) rather than standard containers to handle digits dynamically and efficiently[cite: 1].
- **Custom Input/Output Streams:** Fully overloaded `<<` and `>>` operators for seamless console interactions[cite: 1].
- **Full Operator Suite:** Implements basic arithmetic, unary signs, pre/post-increment, bitwise-like base-10 shifts (`<<`, `>>`), and relational comparisons[cite: 1].
- **Interactive Command-Line Calculator:** Works out-of-the-box with an interactive CLI mini-calculator that supports step-by-step history and operations[cite: 1].

---

## 🛠️ Architecture & Constraints

To strictly satisfy the strict pedagogical constraints of the course, this library is built **without** advanced modern C++ abstractions[cite: 1]:
- 🚫 **No STL Containers/Algorithms:** Absolutely no `std::vector`, `std::list`, `std::copy`, etc.[cite: 1]
- 🚫 **No Exceptions:** Error handling is managed via stream states (`ios::failbit`) and safe warnings on `std::cerr`[cite: 1].
- 🚫 **No Templates/Inheritance:** Focused purely on clean object-oriented design and raw memory manipulation[cite: 1].

### Internal Representation
Each `BigInt` instance is comprised of three core attributes[cite: 1]:
- `bool neg`: `true` if the number is negative, `false` otherwise[cite: 1].
- `int nDig`: The precise count of digits currently stored ($\ge 1$)[cite: 1].
- `int8_t* d`: A raw dynamic array containing the digits (values `0` through `9`)[cite: 1].

> ⚠️ **Note:** Digits are stored in **reverse order** (the least significant digit is at `d[0]`) to simplify the implementation of manual arithmetic pipelines (like carry and borrow steps)[cite: 1].

---

## ⚙️ Supported Operations

| Operator / Method | Description |
| :--- | :--- |
| `+`, `-` (Binary) | Addition and Subtraction with custom carry/borrow logic[cite: 1]. |
| `*` | Multiplication using digit-by-digit expansion[cite: 1]. |
| `/`, `%`, `division()` | Base-10 long division yielding Quotient and Remainder via successive subtractions[cite: 1]. |
| `!` | Factorial calculator for `BigInt`[cite: 1]. |
| `++`, `--` | Pre-fixed and Post-fixed increment/decrement optimizations[cite: 1]. |
| `<<`, `>>` (Int) | Base-10 shift operators (e.g., `375 << 2` yields `37500`)[cite: 1]. |
| `==`, `!=`, `<`, `<=`, `>`, `>=` | Full set of lexicographical and algebraic comparison operators[cite: 1]. |
| `toInt()` | Safely attempts to downcast the `BigInt` into a native `long long int` with robust overflow clipping and `cerr` notifications[cite: 1]. |

---

## 💻 Getting Started

### Prerequisites
- A modern C++ compiler supporting at least **C++11** (e.g., `g++` or `clang++`).

### Compilation
Compile your custom implementation files alongside the provided test or main interface:

```bash
g++ -std=c++11 main.cpp bigint.cpp -o bigint_calc
