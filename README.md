# Bi-Connected Components (BCC) Validator Overview

This C++ program is designed to validate the results of serial and parallel computations related to Bi-connected Components (BCC) in graphs. It compares the results for cut vertices and BCCs from two different computations to ensure consistency and correctness.
Files

    bcc_validator.cpp: Main program file containing the source code.
    test_1.txt: Sample output file from serial computation.
    test_2.txt: Sample output file from parallel computation.

## Compilation

Compile the program using a C++ compiler (e.g., g++):
```shell
    g++ -std=c++17 -O3 -o bcc_validator bcc_validator.cpp
```

## Usage

Run the program with the following command:

```shell
    ./bcc_validator <serial_output_file> <parallel_output_file>

    <serial_output_file>: File containing the results from the serial computation. Example: test_1.txt.
    <parallel_output_file>: File containing the results from the parallel computation. Example: test_2.txt.
```

## Input File Format

Each input file (serial and parallel output files) should follow this format:

    First line: Number of vertices (n) and edges (e).
    Second line: Literal string "cut vertex status".
    Next n lines: Each line contains a vertex number u and its cut vertex status (0 or 1).
    Literal string "vertex BCC number".
    Next n lines: Each line contains a vertex number u and its corresponding BCC number.

### Example:

```shell

5 6
cut vertex status
0 1
1 0
2 1
3 0
4 0
vertex BCC number
0 1
1 2
2 1
3 2
4 3

```

## Output

The program outputs whether the cut vertex and BCC results match between the serial and parallel computations. It then prints the detailed results for further inspection.

## Contributing
Contributions are welcome!