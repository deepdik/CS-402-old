# Employee Management System

## Description
This is a simple Employee Management System written in C. The program allows you to manage employee records, including printing the database, looking up employees by ID, looking up employees by last name, and adding new employees. Employee data is read from an input file.

## Prerequisites
- C compiler (e.g., GCC)

## Building the Program
To build the program, open your terminal and navigate to the project directory. Then, compile the source files using the C compiler (e.g., GCC):

```bash
gcc -o employee_manager main.c employee.c database.c readfile.c
```
## Running the Program
To run the build file use below command:
```bash
# <build file name> <input data file name>
./employee_manager input.txt
```
