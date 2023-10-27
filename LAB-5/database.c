#include <stdio.h>
#include <string.h>

#include "database.h"
#include "employee.h"


void printDatabase(const struct Employee* employees, int numEmployees) {
    printf("NAME\t\tSALARY\t\tID\n");
    printf("---------------------------------------------------------------\n");
    for (int i = 0; i < numEmployees; i++) {
        printf("%s %s\t%d\t\t%d\n", employees[i].first_name, employees[i].last_name, employees[i].salary, employees[i].id);
    }
    printf("---------------------------------------------------------------\n");
    printf("Number of Employees (%d)\n", numEmployees);
}

// Function to lookup employee by ID
void lookupById(const struct Employee* employees, int numEmployees) {
    int searchId;
    printf("Enter a 6 digit employee id: ");
    if (scanf("%d", &searchId) != 1 || searchId < MIN_ID || searchId > MAX_ID) {
        printf("Invalid input. Please enter a valid 6-digit ID.\n");
        while (getchar() != '\n'); // Clear the input buffer
        return;
    }

    for (int i = 0; i < numEmployees; i++) {
        if (employees[i].id == searchId) {
            printEmployee(&employees[i]);
            return;
        }
    }

    printf("Employee with id %d not found in DB\n", searchId);
}

// Function to lookup employee by last name
void lookupByLastName(const struct Employee* employees, int numEmployees) {
    char searchLastName[MAX_NAME_LENGTH];
    printf("Enter Employee's last name (no extra spaces): ");
    if (scanf("%64s", searchLastName) != 1) {
        printf("Invalid input. Please enter a valid last name.\n");
        while (getchar() != '\n'); // Clear the input buffer
        return;
    }

    int found = 0;
    for (int i = 0; i < numEmployees; i++) {
        if (strcmp(employees[i].last_name, searchLastName) == 0) {
            printEmployee(&employees[i]);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("No employees found with last name: %s\n", searchLastName);
    }
}

// Function to add an employee
void addEmployee(struct Employee* employees, int* numEmployees) {
    if (*numEmployees >= MAX_EMPLOYEES) {
        printf("Cannot add more employees. Maximum capacity reached.\n");
        return;
    }

    struct Employee newEmployee;

    // Prompt for and validate the first name
    do {
        printf("Enter the first name of the employee: ");
        if (scanf("%64s", newEmployee.first_name) != 1) {
            printf("Invalid input. Please enter a valid first name.\n");
            while (getchar() != '\n'); // Clear the input buffer
        }
    } while (strlen(newEmployee.first_name) == 0);

    // Prompt for and validate the last name
    do {
        printf("Enter the last name of the employee: ");
        if (scanf("%64s", newEmployee.last_name) != 1) {
            printf("Invalid input. Please enter a valid last name.\n");
            while (getchar() != '\n'); // Clear the input buffer
        }
    } while (strlen(newEmployee.last_name) == 0);

    // Prompt for and validate the salary
    do {
        printf("Enter employee's salary (%d to %d): ", MIN_SALARY, MAX_SALARY);
        if (scanf("%d", &newEmployee.salary) != 1 || newEmployee.salary < MIN_SALARY || newEmployee.salary > MAX_SALARY) {
            printf("Invalid input. Please enter a valid salary.\n");
            while (getchar() != '\n'); // Clear the input buffer
        }
    } while (newEmployee.salary < MIN_SALARY || newEmployee.salary > MAX_SALARY);

    // Find the next available ID
    int nextId = MIN_ID;
    for (int i = 0; i < *numEmployees; i++) {
        if (employees[i].id >= nextId) {
            nextId = employees[i].id + 1;
        }
    }
    newEmployee.id = nextId;

    int confirm;

    do {
        printf("Do you want to add the following employee to the DB?\n");
        printf("\t%s %s, salary: %d\n", newEmployee.first_name, newEmployee.last_name, newEmployee.salary);
        printf("Enter 1 for yes, 0 for no: ");

        if (scanf("%d", &confirm) != 1 || (confirm != 0 && confirm != 1)) {
            printf("Invalid input. Please enter 0 or 1.\n");
            while (getchar() != '\n'); // Clear the input buffer
        }
    } while (confirm != 0 && confirm != 1);

    if (confirm == 1) {
        employees[*numEmployees] = newEmployee;
        (*numEmployees)++;
        printf("Employee added to the database.\n");
    } else {
        printf("Employee not added to the database.\n");
    }
}
