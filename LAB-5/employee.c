#include <stdio.h>
#include <string.h>

#include "employee.h"


void printEmployee(const struct Employee* employee) {
    printf("NAME\t\tSALARY\t\tID\n");
    printf("---------------------------------------------------------------\n");
    printf("%s %s\t%d\t\t%d\n", employee->first_name, employee->last_name, employee->salary, employee->id);
    printf("---------------------------------------------------------------\n\n");
}

int validateEmployee(const struct Employee* employee) {
    return (employee->id >= MIN_ID && employee->id <= MAX_ID) &&
           (employee->salary >= MIN_SALARY && employee->salary <= MAX_SALARY);
}

int getNextAvailableId(const struct Employee* employees, int numEmployees) {
    int nextId = MIN_ID;
    for (int i = 0; i < numEmployees; i++) {
        if (employees[i].id >= nextId) {
            nextId = employees[i].id + 1;
        }
    }
    return nextId;
}


void readAndSortEmployeeData(struct Employee* employees, int* numEmployees) {
    // Read and parse the employee data from the input file
    // Sort the employees by their ID in ascending order
    for (int i = 0; i < *numEmployees - 1; i++) {
        for (int j = 0; j < *numEmployees - i - 1; j++) {
            if (employees[j].id > employees[j + 1].id) {
                // Swap the employees
                struct Employee temp = employees[j];
                employees[j] = employees[j + 1];
                employees[j + 1] = temp;
            }
        }
    }
}







