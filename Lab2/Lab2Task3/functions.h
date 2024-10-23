#include <stdarg.h>

#include "vector.h"

int findEnterancesInFile(char* substring, char* path, Vector* lines, Vector* chars, Vector* fileIds, int fileId) {
	FILE* fd = fopen(path, "r");
	if (!fd) {
		return ERROR_OPEN_FILE;
	}
	int code;
	int currentLine = 1;
	int currentChar = 1;
	int currentLen = 0;
	int start = 0;
	char currentFile = fgetc(fd);
	char* currentSubstr = substring;

	while (currentFile != EOF) {
		if (currentFile != *currentSubstr) {
			if (*currentSubstr == '\0') {
				code = VectorPush(lines, currentLine);
				if (code != SUCCESS) {
					return code;
				}

				code = VectorPush(chars, currentChar);
				if (code != SUCCESS) {
					return code;
				}

				code = VectorPush(fileIds, fileId);
				if (code != SUCCESS) {
					return code;
				}
			}

			currentSubstr = substring;
			start++;
			fseek(fd, start, SEEK_SET);
			currentFile = fgetc(fd);
			currentChar++;
			if (currentFile == '\n') {
				currentLine++;
				currentChar = 0;
			}
			
			currentLen = 0;
			continue;
		}

		currentFile = fgetc(fd);
		currentSubstr++;
		currentLen++;
	}

	if (*currentSubstr == '\0') {
		code = VectorPush(lines, currentLine);
		if (code != SUCCESS) {
			return code;
		}
		code = VectorPush(chars, currentChar);
		if (code != SUCCESS) {
			return code;
		}

		code = VectorPush(fileIds, fileId);
		if (code != SUCCESS) {
			return code;
		}
	}

	fclose(fd);
	return SUCCESS;
}

int findEnterancesInFiles(Vector* lines, Vector* chars, Vector* fileIds, char* substring, int count, ...) {
	int code;
	va_list args;
	va_start(args, count);

	for (int i = 0; i < count; i++) {
		char* path = va_arg(args, char*);
		code = findEnterancesInFile(substring, path, lines, chars, fileIds, i);
		if (code != SUCCESS) {
			va_end(args);
			return code;
		}
	}
	va_end(args);
	return code;
}