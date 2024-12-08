# producer-consumer-system

This project implements the classic Producer-Consumer problem in C++ using multithreading and synchronization mechanisms. It simulates the interaction between producers and consumers sharing a bounded buffer, showcasing concurrency handling in modern software development.

## Features
- **Multithreaded Implementation**: Simultaneously run multiple producers and consumers.
- **Synchronization**: Ensures thread-safe access to the shared buffer using mutex locks and condition variables.
- **Configurable**: Easily modify the number of producers, consumers, or buffer size.

## Prerequisites
- C++ compiler supporting C++11 or later
- GNU Make

## Installation
1. Clone the repository:
   ```bash
   git clone https://github.com/sebas-ib/producer-consumer-system.git
   cd producer-consumer-system
   ```


2. Compile the program using the provided Makefile:
   ```bash
   make
   ```

## Usage
Run the executable after compilation:
   ```bash
   ./food_delivery
   ```

### Configuration
Modify the source code to adjust parameters such as:
  Number of producers or consumers
  Buffer size
