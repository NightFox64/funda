#include "errors.h"

typedef struct {
	int len;
	int capacity;
	int* buffer;
} Vector;

typedef struct {
	int index;
	Vector* v;
} Iterator;

Vector* CreateVector(int initialCapacity, int* code) {
	*code = SUCCESS;
	Vector* v = (Vector*)malloc(sizeof(Vector*));
	if (v == NULL) {
		*code = ERROR_MALLOC;
		return NULL;
	}

	v->buffer = (int*)malloc(sizeof(int*) * initialCapacity);
	if (v->buffer == NULL) {
		*code = ERROR_MALLOC;
		free(v);
		return NULL;
	}
	v->capacity = initialCapacity;
	v->len = 0;
	return v;
}

void DestroyVector(Vector* v) {
	free(v->buffer);
	free(v);
};

void PrintVector(Vector* v) {
	for (int i = 0; i < v->len; i++) {
		printf("%d ", v->buffer[i]);
	}
	printf("\n");
}

int VectorPush(Vector* v, int value) {
	if (v->len + 1 >= v->capacity) {
		int* newBuffer = (int*)realloc(v->buffer, v->capacity * sizeof(int) * 2);
		if (newBuffer == NULL) {
			return ERROR_MALLOC;
		}

		v->buffer = newBuffer;
		v->capacity *= 2;
	}
	v->buffer[v->len] = value;
	v->len++;
	return SUCCESS;
}

void VectorPop(Vector* v, Iterator* iter) {
	for (int i = iter->index; i + 1 < v->len; i++) {
		v->buffer[i] = v->buffer[i + 1];
	}
	v->len--;
}