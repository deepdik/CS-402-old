#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h> // Include ctype.h for case-insensitive comparison


#include "database.h"
#include "employee.h"


void printDatabase(const struct Employee* employees, int numEmployees) {
    printf("\nNAME\t\tSALARY\t\tID\n");
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


void removeEmployee(struct Employee* employees, int* numEmployees) {
    if (*numEmployees == 0) {
        printf("No employees in the database to remove.\n");
        return;
    }

    int searchId;
    printf("Enter the employee ID to remove: ");
    if (scanf("%d", &searchId) != 1) {
        printf("Invalid input. Please enter a valid employee ID.\n");
        while (getchar() != '\n'); // Clear the input buffer
        return;
    }

    // Find the index of the employee with the specified ID
    int index = -1;
    for (int i = 0; i < *numEmployees; i++) {
        if (employees[i].id == searchId) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        printf("Employee with ID %d not found in the database.\n", searchId);
    } else {
        printf("Employee found:\n");
        printEmployee(&employees[index]);

        int confirm;
        printf("Do you want to remove this employee? (1 for yes, 0 for no): ");
        if (scanf("%d", &confirm) != 1 || (confirm != 0 && confirm != 1)) {
            printf("Invalid input. Please enter 0 or 1.\n");
            while (getchar() != '\n'); // Clear the input buffer
            return;
        }

        if (confirm == 1) {
            // Remove the employee by shifting the remaining employees
            for (int i = index; i < *numEmployees - 1; i++) {
                employees[i] = employees[i + 1];
            }
            (*numEmployees)--;
            printf("Employee with ID %d has been removed from the database.\n", searchId);
        } else {
            printf("Employee with ID %d was not removed.\n", searchId);
        }
    }
}


void updateEmployee(struct Employee* employees, int numEmployees) {
    if (numEmployees == 0) {
        printf("No employees in the database to update.\n");
        return;
    }

    int searchId;
    printf("Enter the employee ID to update: ");
    if (scanf("%d", &searchId) != 1) {
        printf("Invalid input. Please enter a valid employee ID.\n");
        while (getchar() != '\n'); // Clear the input buffer
        return;
    }

    int index = -1; // Index of the employee to update

    for (int i = 0; i < numEmployees; i++) {
        if (employees[i].id == searchId) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        printf("Employee with ID %d not found in the database.\n", searchId);
    } else {
        printf("Employee found:\n");
        printEmployee(&employees[index]);

        int confirm;
        printf("Do you want to update this employee's information? (1 for yes, 0 for no): ");
        if (scanf("%d", &confirm) != 1 || (confirm != 0 && confirm != 1)) {
            printf("Invalid input. Please enter 0 or 1.\n");
            while (getchar() != '\n'); // Clear the input buffer
            return;
        }

        if (confirm == 1) {
            // Prompt the user for each field and ask for confirmation before updating
            printf("Do you want to update the first name? (1 for yes, 0 for no): ");
            if (scanf("%d", &confirm) != 1 || (confirm != 0 && confirm != 1)) {
                printf("Invalid input. Please enter 0 or 1.\n");
                while (getchar() != '\n'); // Clear the input buffer
                return;
            }
            if (confirm == 1) {
                printf("Enter updated first name: ");
                scanf("%64s", employees[index].first_name);
            }

            printf("Do you want to update the last name? (1 for yes, 0 for no): ");
            if (scanf("%d", &confirm) != 1 || (confirm != 0 && confirm != 1)) {
                printf("Invalid input. Please enter 0 or 1.\n");
                while (getchar() != '\n'); // Clear the input buffer
                return;
            }
            if (confirm == 1) {
                printf("Enter updated last name: ");
                scanf("%64s", employees[index].last_name);
            }

            printf("Do you want to update the salary? (1 for yes, 0 for no): ");
            if (scanf("%d", &confirm) != 1 || (confirm != 0 && confirm != 1)) {
                printf("Invalid input. Please enter 0 or 1.\n");
                while (getchar() != '\n'); // Clear the input buffer
                return;
            }
            if (confirm == 1) {
                int updatedSalary;
                while (1) {
                    printf("Enter updated salary (between %d and %d): ", MIN_SALARY, MAX_SALARY);
                    if (scanf("%d", &updatedSalary) != 1) {
                        printf("Invalid input. Please enter a valid salary.\n");
                        while (getchar() != '\n'); // Clear the input buffer
                    } else if (updatedSalary < MIN_SALARY || updatedSalary > MAX_SALARY) {
                        printf("Invalid input. Salary out of range. Please enter a valid salary between %d and %d.\n", MIN_SALARY, MAX_SALARY);
                    } else {
                        employees[index].salary = updatedSalary;
                        break; // Break the loop when a valid salary is entered
                    }
                }
            }

            // You can add more fields to update here if needed

            printf("Employee information updated successfully.\n");
        } else {
            printf("Employee information was not updated.\n");
        }
    }
}


void printHighestSalaries(struct Employee* employees, int numEmployees){
    if (numEmployees == 0) {
        printf("No employees in the database to print.\n");
        return;
    }

    int M;
    printf("Enter the number of employees with the highest salaries to print: ");
    if (scanf("%d", &M) != 1 || M <= 0) {
        printf("Invalid value of M. Please enter a positive integer.\n");
        while (getchar() != '\n'); // Clear the input buffer
        return;
    }

    // Sort employees by salary (in descending order) using counting sort
    int maxSalary = -1;
    for (int i = 0; i < numEmployees; i++) {
        if (employees[i].salary > maxSalary) {
            maxSalary = employees[i].salary;
        }
    }

    int* salaryCount = (int*)calloc(maxSalary + 1, sizeof(int));
    if (salaryCount == NULL) {
        printf("Memory allocation failed.\n");
        return;
    }

    for (int i = 0; i < numEmployees; i++) {
        salaryCount[employees[i].salary]++;
    }

    int printed = 0;
    printf("Top %d Employees with the Highest Salaries:\n\n", M);
    printf("NAME\t\t\tSALARY\t\tID\n");
    printf("---------------------------------------------------------------\n");
    for (int salary = maxSalary; salary >= 0; salary--) {
        for (int i = 0; i < numEmployees; i++) {
            if (employees[i].salary == salary) {
                printf("%s %s\t\t%d\t\t%d\n", employees[i].first_name, employees[i].last_name, employees[i].salary, employees[i].id);
                printed++;
            }

            if (printed == M) {
                break;
            }
        }

        if (printed == M) {
            break;
        }
    }
    printf("---------------------------------------------------------------\n\n");


    free(salaryCount);
}


void findAllEmployeesByLastName(struct Employee* employees, int numEmployees) {
    char searchLastName[MAX_NAME_LENGTH];
    printf("Enter the last name to search for (case-insensitive): ");
    if (scanf("%64s", searchLastName) != 1) {
        printf("Invalid input. Please enter a valid last name.\n");
        while (getchar() != '\n'); // Clear the input buffer
        return;
    }

    int found = 0;
    printf("\nNAME\t\t\tSALARY\t\tID\n");
    printf("---------------------------------------------------------------\n");
    for (int i = 0; i < numEmployees; i++) {
        // Perform a case-insensitive comparison
        if (strcasecmp(employees[i].last_name, searchLastName) == 0) {
            printf("%s %s\t\t%d\t\t%d\n", employees[i].first_name, employees[i].last_name, employees[i].salary, employees[i].id);
            found = 1;
        }
    }
    printf("---------------------------------------------------------------\n\n");


    if (!found) {
        printf("No employees found with last name: %s\n", searchLastName);
    }
}

