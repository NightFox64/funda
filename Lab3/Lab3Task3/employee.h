#include "arguments.h"

typedef struct {
    uint64_t ID;
    char* Name;
    char* Surname;
    double Salary;
} Employee;

typedef enum {
    VALID,
    EMPTY_NAME,
    EMPTY_SURNAME,
    INVALID_NAME,
    INVALID_SURNAME,
    NEGATIVE_SALARY
} kValidationError;

kValidationError ValidateEmployee(Employee *employee) {
    if (!employee->Name) {
        return EMPTY_NAME;
    }

    if (!employee->Surname) {
        return EMPTY_SURNAME;
    }

    if (employee->Salary < 0.0) {
        return NEGATIVE_SALARY;
    }

    for (char *i = employee->Name; *i; i++) {
        if (((*i > 'Z' || *i < 'A') && (*i > 'z' || *i < 'a'))) {
            return INVALID_NAME;
        }
    }

    for (char *i = employee->Name; *i; i++) {
        if (((*i > 'Z' || *i < 'A') && (*i > 'z' || *i < 'a'))) {
            return INVALID_SURNAME;
        }
    }

    return VALID;
}

Employee *NewEmployee(uint64_t id, char *name, char *surname, double salary) {
    Employee *result = (Employee*)malloc(sizeof(Employee));
    if (!result) {
        return NULL;
    }

    result->ID = id;
    result->Name = strdup(name);
    if (!result->Name) {
        free(result);
        return NULL;
    }

    result->Surname = strdup(surname);
    if (!result->Surname) {
        free(result->Name);
        free(result);
        return NULL;
    }

    result->Salary = salary;
    return result;
}


void DestroyEmployee(Employee *employee) {
    free(employee->Name);
    free(employee->Surname);
    free(employee);
}
