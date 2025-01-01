# MIRIS: Graph-Based Money Transfer Management System

MIRIS is a software application developed in C that facilitates the management and monitoring of small monetary transfers between users. It uses an efficient directed multigraph structure to dynamically represent and analyze transactions, allowing users to explore the flow of funds and detect complex interactions in financial networks.

## Features

1. **Dynamic Directed Multigraph**:
   - Represents transactions as directed edges with weights indicating transfer amounts and dates.
   - Organized as an adjacency list, where each node points to a list of its outgoing edges.

2. **Graph Structure**:
   - **Nodes**:
     - A pointer to the account name (`accountName`).
     - A pointer to the list of edges (`struct edge pointer`).
     - A pointer to the next node in the node list.
   - **Edges**:
     - A pointer to the destination node (`to_node`).
     - The transaction amount (`amount`).
     - A pointer to the transaction date (`date`).
     - A pointer to the next edge in the adjacency list.

3. **Hash Table for Fast Access**:
   - Implements a hash table with separate chaining for efficient O(1) lookup.
   - Uses the account name as the key and stores a list of edges for the respective account as the value.

4. **Memory Management**:
   - Includes a custom wrapper for `malloc` named `my_malloc` to track dynamically allocated memory.
   - At program termination, prints the total number of bytes deallocated to ensure proper memory management.

5. **Graph Analysis Capabilities**:
   - Detects cycles and traces the diffusion of funds within the network.
   - Identifies user clusters and evaluates connectivity.

6. **Command-Line Interaction**:
   - Interactive prompt for managing and querying the graph.
   - Supports commands for inserting, deleting, modifying, and analyzing transactions.

## Installation

1. **Prerequisites**:
   - Linux environment.
   - GCC compiler for C/C++.
   - [Valgrind](https://valgrind.org/) for memory analysis.

2. **Compilation**:
   - Clone the repository:
     ```bash
     git clone https://github.com/KimonSMN/miris.git
     cd miris
     ```
   - Use the provided Makefile:
     ```bash
     make
     ```

3. **Execution**:
   - Run the program with:
     ```bash
     ./miris -i inputfile -o outfile
     ```

## Commands

The application supports the following commands:

- **Insert Nodes**: `i(nsert) Ni [Nj Nk ...]`
- **Insert Edge**: `(i)n(sert2) Ni Nj sum date`
- **Delete Nodes**: `d(elete) Ni [Nj Nk ...]`
- **Delete Edge**: `(de)l(ete2) Ni Nj`
- **Modify Edge**: `m(odify) Ni Nj sum sum1 date date1`
- **Outgoing Transactions**: `f(ind) Ni`
- **Incoming Transactions**: `r(eceiving) Ni`
- **Find Cycles**: `c(irclefind) Ni` (Not finished)
- **Trace Flow**: `t(raceflow) Ni m` (Not finished)
- **Check Connectivity**: `(c)o(nnected) Ni Nj` (Not finished)
- **Exit Program**: `e(xit)`

For a detailed description of each command and expected output, refer to the documentation.

## Contribution

Contributions are welcome! Feel free to fork the repository, make changes, and submit a pull request.

## License

This project is licensed under the [MIT License](LICENSE).

## Acknowledgments

This project was developed as part of a university coursework in Operating Systems (Fall 2024) at the Department of Informatics and Telecommunications, University of Athens.
