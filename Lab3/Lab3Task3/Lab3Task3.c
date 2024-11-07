#include "vector.h"

bool CheckIDs(Vector *v) {
    for (int i = 0; i < v->len; i++) {
        for (int j = i + 1; j < v->len - 1; j++) {
            Employee* first = v->buffer[i];
            Employee* second = v->buffer[j];

            if (first->ID == second->ID) {
                if (!strcmp(first->Name, second->Name) || !strcmp(first->Surname, second->Surname) || first->Salary != second->Salary) {
                    return false;
                }
            }
        }
    }
    return true;
}

kState ParseFile(const char *path, Vector *result) {
    FILE *in = fopen(path, "r");
    if (!in) {
        return ERROR_OPEN_FILE;
    }
    uint64_t id;
    char* name;
    char* surname;
    double salary;
    while (fscanf(in, "%llu %ms %ms %lf", &id, &name, &surname, &salary) == 4) {
        
        if (id < 0 || salary < 0 || id > 100000000000 || salary > 100000000000.0){
            return ERROR_VALIDATE_EMPLOYEE;
        }

        Employee *employee = NewEmployee(id, name, surname, salary);
        if (!employee) {
            fclose(in);
            return ERROR_MALLOC;
        }
        kValidationError err = ValidateEmployee(employee);
        if (err != SUCCESS) {
            fclose(in);
            return ERROR_VALIDATE_EMPLOYEE;
        }
        VectorPush(result, employee);
        free(name);
        free(surname);
    }

    if (fscanf(in, "%llu %ms %ms %lf", &id, &name, &surname, &salary) != EOF) {
        fclose(in);
        return ERROR_PARSING;
    }

    fclose(in);
    return SUCCESS;
}


kState WriteResult(Vector *v, const char *path) {
    FILE *out = fopen(path, "w");
    if (!out) {
        return ERROR_OPEN_FILE;
    }
    FprintVector(v, out);
    fclose(out);
    return SUCCESS;
}

int descendingComp(const void *a, const void *b) {
    const Employee *first = *((const Employee **) a);
    const Employee *second = *((const Employee **) b);
    if (first->Salary != second->Salary) {
        return first->Salary < second->Salary ? 1 : -1;
    }
    int comp = strcmp(first->Surname, second->Surname);
    if (comp != 0) {
        return comp;
    }
    comp = strcmp(first->Name, second->Name);
    if (comp != 0) {
        return comp;
    }
    return first->ID < second->ID;
}

int ascendingComp(const void *a, const void *b) {
    const Employee *first = *((const Employee **) a);
    const Employee *second = *((const Employee **) b);
    if (first->Salary != second->Salary) {
        return first->Salary > second->Salary ? 1 : -1;
    }
    int comp = strcmp(first->Surname, second->Surname);
    if (comp != 0) {
        return -comp;
    }
    comp = strcmp(first->Name, second->Name);
    if (comp != 0) {
        return -comp;
    }
    return first->ID > second->ID;
}

int main(int argc, char **argv) {
    Args *args = ParseArgs(argc, argv);
    if (!args) {
        logErrors(ERROR_MALLOC);
        return ERROR_MALLOC;
    }

    if (args->State != SUCCESS) {
        logErrors(args->State);
        return args->State;
    }

    Vector *vector = CreateVector(2);
    kState code = ParseFile(args->InputPath, vector);
    if (code != SUCCESS) {
        DestroyVector(vector);
        free(args);
        logErrors(code);
        return code;
    }

    if (!CheckIDs(vector)) {
        logErrors(ERROR_SAME_IDS);
        return ERROR_SAME_IDS;
    }

    ComparatorCallback comparators[2];
    comparators[kOptA] = ascendingComp;
    comparators[kOptD] = descendingComp;

    SortVector(vector, comparators[args->Option]);
    code = WriteResult(vector, args->OutputPath);
    if (code != SUCCESS) {
        DestroyVector(vector);
        free(args);
        logErrors(code);
        return code;
    }
    DestroyVector(vector);
    free(args);
    return SUCCESS;
}