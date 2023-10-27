#ifndef DATABASE_H
#define DATABASE_H

#include "employee.h"
#define MAX_EMPLOYEES 1024


void printDatabase(const struct Employee* employees, int numEmployees);
void lookupById(const struct Employee* employees, int numEmployees);
void lookupByLastName(const struct Employee* employees, int numEmployees);
void addEmployee(struct Employee* employees, int* numEmployees);

#endif // DATABASE_H
