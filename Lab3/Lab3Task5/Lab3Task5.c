#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define EXAMS 5

typedef enum {
    SUCCESS,
    ERROR_OPEN_FILE,
    ERROR_MALLOC,
    ERROR_SAME_IDS,
} kState;

typedef struct {
    unsigned int id;
    char *firstName;
    char *lastName;
    char *group;
    unsigned char *grades;
} Student;

kState readStudents(const char *filePath, Student **studentsPtr, int *studentCount) {
    FILE *file = fopen(filePath, "r");
    if (file == NULL) {
        return ERROR_OPEN_FILE;
    }

    Student *students = NULL;
    *studentCount = 0;

    while (!feof(file)) {
        students = (Student*)realloc(students, (*studentCount + 1) * sizeof(Student));
        if (students == NULL) {
            fclose(file);
            return ERROR_MALLOC;
        }

        Student *student = &students[*studentCount];
        student->grades = (unsigned char*)malloc(EXAMS * sizeof(unsigned char));
        if (student->grades == NULL) {
            fclose(file);
            return ERROR_MALLOC;
        }

        if (fscanf(file, "%u %ms %ms %ms", &student->id, &student->firstName, &student->lastName, &student->group) != 4) {
            break;
        }
        else {
            for (int i = 0; i < EXAMS; ++i) {
                fscanf(file, "%hhu", &student->grades[i]);
            }
        }
        

        (*studentCount)++;
    }

    fclose(file);
    *studentsPtr = students;
    return SUCCESS;
}

int compareById(const void *a, const void *b) {
    Student *studentA = (Student *)a;
    Student *studentB = (Student *)b;
    return studentA->id - studentB->id;
}

int compareByLastName(const void *a, const void *b) {
    Student *studentA = (Student *)a;
    Student *studentB = (Student *)b;
    return strcmp(studentA->lastName, studentB->lastName);
}

int compareByFirstName(const void *a, const void *b) {
    Student *studentA = (Student *)a;
    Student *studentB = (Student *)b;
    return strcmp(studentA->firstName, studentB->firstName);
}

int compareByGroup(const void *a, const void *b) {
    Student *studentA = (Student *)a;
    Student *studentB = (Student *)b;
    return strcmp(studentA->group, studentB->group);
}

void sortStudents(Student *students, int count, int (*comparator)(const void*, const void*)) {
    qsort(students, count, sizeof(Student), comparator);
}

void printStudentToFile(FILE *file, const Student *student) {
    fprintf(file, "ID: %u\nSurname: %s\nName: %s\nGroup: %s\n", student->id, student->lastName, student->firstName, student->group);
    fprintf(file, "Marks: ");
    for (int i = 0; i < EXAMS; ++i) {
        fprintf(file, "%hhu ", student->grades[i]);
    }
    fprintf(file, "\n\n");
}

double calculateAverageGrade(const Student *student) {
    int sum = 0;
    for (int i = 0; i < EXAMS; ++i) {
        sum += student->grades[i];
    }
    return (double)sum / EXAMS;
}

Student *findStudentById(Student *students, int count, unsigned int id) {
    for (int i = 0; i < count; ++i) {
        if (students[i].id == id) {
            return &students[i];
        }
    }
    return NULL;
}

kState checkIDs(Student *students, int count) {
    for (int i = 0; i < count; ++i) {
        for (int j = i + 1; j < count - 1; ++j) {
            
            if (students[i].id == students[j].id) {
                if (!strcmp(students[i].firstName, students[j].firstName) || !strcmp(students[i].lastName, students[j].lastName) || !strcmp(students[i].group, students[j].group)) {
                    return ERROR_SAME_IDS;
                } 
                
                for (int k = 0; k < EXAMS; ++k) {
                    if (students[i].grades[k] != students[j].grades[k]) {
                        return ERROR_SAME_IDS;
                    }
                }
            }

        }
    }
    return SUCCESS;
}

void findStudentByLastName(FILE* file, Student *students, int count, const char *lastName) {
    int counter = 0;
    for (int i = 0; i < count; ++i) {
        if (strcmp(students[i].lastName, lastName) == 0) {
            printStudentToFile(file, &students[i]);
            counter++;
        }
    }
    if (counter == 0) {
        fprintf(file, "No students with that surname\n");
    }
    return;
}

void findStudentByFirstName(FILE* file, Student *students, int count, const char *firstName) {
    int counter = 0;
    for (int i = 0; i < count; ++i) {
        if (strcmp(students[i].firstName, firstName) == 0) {
            printStudentToFile(file, &students[i]);
            counter++;
        }
    }
    if (counter == 0) {
        fprintf(file, "No students with that name\n");
    }
    return;
}

void findStudentByGroup(FILE* file, Student *students, int count, const char *group) {
    int counter = 0;
    for (int i = 0; i < count; ++i) {
        if (strcmp(students[i].group, group) == 0) {
            printStudentToFile(file, &students[i]);
            counter++;
        }
    }
    if (counter == 0) {
        fprintf(file, "No students from that group\n");
    }
    return;
}

void DestroyStudent(Student *student) {
    free(student->firstName);
    free(student->lastName);
    free(student->group);
    free(student->grades);
}

void writeStudentsWithAboveAverage(FILE *file, Student *students, int count, double avg) {
    fprintf(file, "Students with above-average grades:\n");
    for (int i = 0; i < count; ++i) {
        double studentAvg = calculateAverageGrade(&students[i]);
        if (studentAvg > avg) {
            fprintf(file, "Surname: %s, Name: %s\n", students[i].lastName, students[i].firstName);
        }
    }
    fprintf(file, "\n\n");
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <student_file> <output_file>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *inputFile = argv[1];
    const char *outputFile = argv[2];

    int studentCount;
    Student *students;

    kState result = readStudents(inputFile, &students, &studentCount);
    if (result != SUCCESS) {
        if (result == ERROR_OPEN_FILE) {
            printf("Error: failed to open file with students %s\n", inputFile);
        } else if (result == ERROR_MALLOC) {
            printf("Error: failed to allocate memory\n");
        }
        return EXIT_FAILURE;
    }

    FILE *output = fopen(outputFile, "w");
    if (output == NULL) {
        printf("Error: failed to open output file %s\n", outputFile);
        return EXIT_FAILURE;
    }

    if (checkIDs(students, studentCount) != SUCCESS) {
        printf("There are different people with the same ID\n");
        return ERROR_SAME_IDS;
    }

    int command;
    while (1) {
        printf("\nCommands:\n");
        printf("1. Search with ID\n");
        printf("2. Search with surname\n");
        printf("3. Search with name\n");
        printf("4. Search with group\n");
        printf("5. Sort\n");
        printf("6. See all students with above-average marks\n");
        printf("7. Exit\n");
        printf("Input the number of command: ");
        scanf("%d", &command);

        if (command == 1) {
            unsigned int idToFind;
            printf("Input student's ID: ");
            scanf("%u", &idToFind);

            Student *foundStudent = findStudentById(students, studentCount, idToFind);
            if (foundStudent) {
                printStudentToFile(output, foundStudent);
            } else {
                fprintf(output, "Student with ID %u didn't find\n", idToFind);
            }

        } else if (command == 2) {
            char* lastName;
            printf("Input student's surname: ");
            scanf("%ms", &lastName);

            findStudentByLastName(output, students, studentCount, lastName);

        } else if (command == 3) {
            char *firstName;
            printf("Input student's name: ");
            scanf("%ms", &firstName);

            findStudentByFirstName(output, students, studentCount, firstName);


        } else if (command == 4) {
            char* group;
            printf("Input student's group: ");
            scanf("%ms", &group);

            findStudentByGroup(output, students, studentCount, group);

        } else if (command == 5) {
            printf("Sort with:\n");
            printf("1. ID\n");
            printf("2. Surname\n");
            printf("3. Name\n");
            printf("4. Group\n");
            printf("Input number of the sort key: ");
            int sortOption;
            scanf("%d", &sortOption);

            if (sortOption == 1) {
                sortStudents(students, studentCount, compareById);
            } else if (sortOption == 2) {
                sortStudents(students, studentCount, compareByLastName);
            } else if (sortOption == 3) {
                sortStudents(students, studentCount, compareByFirstName);
            } else if (sortOption == 4) {
                sortStudents(students, studentCount, compareByGroup);
            }

            for (int i = 0; i < studentCount; ++i) {
                printStudentToFile(output, &students[i]);
            }

        } else if (command == 6) {
            double totalAvg = 0.0;
            for (int i = 0; i < studentCount; ++i) {
                totalAvg += calculateAverageGrade(&students[i]);
            }
            totalAvg /= studentCount;

            writeStudentsWithAboveAverage(output, students, studentCount, totalAvg);

        } else if (command == 7) {
            break;
        }
    }

    fclose(output);

    for (int i = 0; i < studentCount; ++i) {
        DestroyStudent(&students[i]);
    }
    free(students);

    return EXIT_SUCCESS;
}