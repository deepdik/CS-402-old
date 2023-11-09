#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#define MAX_NAME_LENGTH 65
#define MIN_ID 100000
#define MAX_ID 999999
#define MIN_SALARY 30000
#define MAX_SALARY 150000

struct Employee {
    int id;
    char first_name[MAX_NAME_LENGTH];
    char last_name[MAX_NAME_LENGTH];
    int salary;
};

void printEmployee(const struct Employee* employee);
int validateEmployee(const struct Employee* employee);
int getNextAvailableId(const struct Employee* employees, int numEmployees);
void readAndSortEmployeeData(struct Employee* employees, int* numEmployees);

#endif // EMPLOYEE_H
