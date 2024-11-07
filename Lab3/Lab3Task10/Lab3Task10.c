#include "tree.h"

bool sameFile(char *input, char *output) {
    char* resbuf1 = (char*)malloc(sizeof(char) * MAX_PATH);
    if (resbuf1 == NULL){
        return true;
    }
    DWORD res1 = GetFullPathName(input, MAX_PATH, resbuf1, &resbuf1);
    char* resbuf2 = (char*)malloc(sizeof(char) * MAX_PATH);
    if (resbuf2 == NULL){
        free(resbuf1);
        return true;
    }
    DWORD res2 = GetFullPathName(output, MAX_PATH, resbuf2, &resbuf2);
    if (res1 != 0 && res2 != 0) {
        if (!strcmp(resbuf1, resbuf2)){
            return true;
        }
    }
    return false;
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        logErrors(ERROR_ARGS);
        return ERROR_ARGS;
    }

    if (sameFile(argv[1], argv[2])) {
        logErrors(ERROR_SAME_FILES);
        return ERROR_SAME_FILES;
    }

    FILE* inputFile = fopen(argv[1], "r");
    if (!inputFile) {
        logErrors(ERROR_OPEN_FILE);
        return ERROR_OPEN_FILE;
    }

    FILE* outputFile = fopen(argv[2], "w");
    if (!outputFile) {
        logErrors(ERROR_OPEN_FILE);
        fclose(inputFile);
        return ERROR_OPEN_FILE;
    }

    char* line;
    while (fscanf(inputFile, "%ms", &line) != EOF) {
        printf("%s\n", line);
        line[strcspn(line, "\n")] = '\0';

        int index = 0;
        Node* root = buildTree(line, &index);

        printTree(outputFile, root, 0);
        fprintf(outputFile, "\n");

        freeTree(root);
    }

    fclose(inputFile);
    fclose(outputFile);

    return 0;
}