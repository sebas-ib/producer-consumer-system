
# producer-consumer-system

This project implements the classic Producer-Consumer problem in C++ using multithreading and synchronization mechanisms. It simulates the interaction between producers and consumers sharing a bounded buffer.

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
   ./fooddelivery
   ```

### Command-Line Options
The program accepts the following optional arguments:
   - `-n`: Number of delivery requests (default: 100)
   - `-a`: Service time for producer A in milliseconds
   - `-b`: Service time for producer B in milliseconds
   - `-p`: Time for pizza production in milliseconds
   - `-s`: Time for sandwich production in milliseconds
   
   Example:
   ```bash
   ./fooddelivery -n 150 -a 5 -b 7 -p 2 -s 3
   ```

### Default Behavior
If no arguments are provided, the program runs with:
   - 100 delivery requests
   - Service and production times set to zero

### Configuration
   Arguments:
   ```bash
   # [-n Num of Delivery Requests] [-a Time for Service A to deliver (ms)] [-b Time for Service B to deliver (ms)] [-p Time for Pizza to be made (ms)] [-s Time for Sandwich to be made (ms)]
   ```

## Notes

### Expected Deprecation Warnings on macOS
On macOS, you may see the following warnings during compilation:
   ```bash
   warning: 'sem_init' is deprecated [-Wdeprecated-declarations]
   ```
These warnings occur because the macOS SDK marks `sem_init` as deprecated. These warnings can be ignored when running in a Linux environment.

### Recommended Environment for Running the Code
To avoid these deprecation warnings and ensure the code runs as expected, I recommend running the program in a Linux-based environment. I used the second approach to get around this; however, if you aren't an SDSU student, the first approach is also an option:

1. **Virtual Machine (VM)**:
   Use a Linux-based virtual machine through tools like VMware or VirtualBox to create a development environment.

2. **CLion's Remote Development Feature**:
   Connect to a remote Linux machine via SSH (e.g., your SDSU Edoras account) and run the program in a Linux environment.

