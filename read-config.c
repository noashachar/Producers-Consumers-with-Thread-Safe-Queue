#include "read-config.h"

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

int* find_numbers(const char* filename, int* count) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("fopen failed");
        return NULL;
    }

    int capacity = 10;  // Initial capacity for the array
    int size = 0;  // Number of numbers found
    int* numbers = malloc(capacity * sizeof(int));
    if (!numbers) {
        perror("malloc failed");
        fclose(file);
        return NULL;
    }

    char buffer[20];  // buffer to hold the characters for a number
    int index = 0;  // current index in buffer

    char ch;
    while ((ch = fgetc(file)) != EOF) {
        if (isdigit(ch)) {
            buffer[index++] = ch;  // store the digit in the buffer
        } 
        else if (index > 0) {  // if the buffer contains a number
            buffer[index] = '\0';  // null-terminate the string

            int number = atoi(buffer);  // convert the string to a number

            if (size == capacity) {  // Grow the array if necessary
                capacity *= 2;
                int* new_numbers = realloc(numbers, capacity * sizeof(int));
                if (!new_numbers) {
                    perror("realloc failed");
                    free(numbers);
                    fclose(file);
                    return NULL;
                }
                numbers = new_numbers;
            }

            numbers[size++] = number;
            index = 0;  // reset the index for the next number
        }
    }

    // handle the last number in the file (if any)
    if (index > 0) {
        buffer[index] = '\0';
        numbers[size++] = atoi(buffer);
    }

    fclose(file);

    // Shrink the array to the final size
    int* final_numbers = realloc(numbers, size * sizeof(int));
    if (!final_numbers) {
        perror("realloc failed shrinking");
        free(numbers);
        return NULL;
    }

    *count = size;
    return final_numbers;
}
