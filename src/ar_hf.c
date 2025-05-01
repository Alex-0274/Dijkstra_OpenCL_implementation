#include <stdio.h>
#include <stdlib.h>
char* ar_read_file(const char* file_name) {
	FILE *file = fopen(file_name, "r");
	fseek(file, 0, SEEK_END);
	int length = ftell(file);
	fseek(file, 0, SEEK_SET);
	char *file_data = (char*)malloc(length + 1);
	fread(file_data, 1, length, file);
	file_data[length] = '\0';
	fclose(file);
	return file_data;
}