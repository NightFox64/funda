#include "functions.h"

int main() {
	int code;
	Vector* lines = CreateVector(2, &code);
	if (code != SUCCESS) {
		logErrors(code);
		return code;
	}

	Vector* chars = CreateVector(2, &code);
	if (code != SUCCESS) {
		free(lines);
		logErrors(code);
		return code;
	}

	Vector* fileIds = CreateVector(2, &code);
	if (code != SUCCESS) {
		free(chars);
		free(lines);
		logErrors(code);
		return code;
	}

	code = findEnterancesInFiles(lines, chars, fileIds, "n\n\nn", 1, "input_1.txt");

	if (code != SUCCESS) {
		logErrors(code);
		return code;
	}

	for (int i = 0; i < lines->len; i++) {
		printf("Found substring enterance in file with id: %d, on position: line: %d, char: %d\n", fileIds->buffer[i],
			   (lines->buffer[i]) /2 + 1, chars->buffer[i]);
	}

	DestroyVector(lines);
	DestroyVector(chars);
	DestroyVector(fileIds);
	return SUCCESS;
}