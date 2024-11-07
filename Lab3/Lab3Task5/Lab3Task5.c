#include "functions.h"

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

            free(lastName);
        } else if (command == 3) {
            char *firstName;
            printf("Input student's name: ");
            scanf("%ms", &firstName);

            findStudentByFirstName(output, students, studentCount, firstName);

            free(firstName);
        } else if (command == 4) {
            char* group;
            printf("Input student's group: ");
            scanf("%ms", &group);

            findStudentByGroup(output, students, studentCount, group);

            free(group);

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