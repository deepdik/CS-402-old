#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "stats.h"

// Function to read data from a file and store it in a dynamically allocated array
float *readDataFromFile(const char *filename, int *numValues, int *capacity) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        exit(1);
    }

    *capacity = 20; // Initial capacity of the array
    *numValues = 0;
    float *data = (float *)malloc(sizeof(float) * *capacity);

    if (data == NULL) {
        perror("Error allocating memory");
        exit(1);
    }

    float value;
    while (fscanf(file, "%f", &value) == 1) {
        if (*numValues == *capacity) {
            // If the array is full, allocate a new array with double the capacity
            *capacity *= 2;
            data = (float *)realloc(data, sizeof(float) * *capacity);
            if (data == NULL) {
                perror("Error reallocating memory");
                exit(1);
            }
        }
        data[(*numValues)++] = value;
    }

    fclose(file);
    return data;
}

// Function to compute the mean of the data
float calculateMean(const float *data, int numValues) {
    float sum = 0.0;
    for (int i = 0; i < numValues; i++) {
        sum += data[i];
    }
    return sum / numValues;
}

// Function to compute the median of the data
float calculateMedian(float *data, int numValues) {
    // Sort the data
    for (int i = 0; i < numValues - 1; i++) {
        for (int j = 0; j < numValues - i - 1; j++) {
            if (data[j] > data[j + 1]) {
                float temp = data[j];
                data[j] = data[j + 1];
                data[j + 1] = temp;
            }
        }
    }

    if (numValues % 2 == 0) {
        // If the number of values is even, average the two middle values
        int middle1 = numValues / 2 - 1;
        int middle2 = numValues / 2;
        return (data[middle1] + data[middle2]) / 2.0;
    } else {
        // If the number of values is odd, return the middle value
        return data[numValues / 2];
    }
}

// Function to compute the standard deviation of the data
float calculateStandardDeviation(const float *data, int numValues, float mean) {
    float sum = 0.0;
    for (int i = 0; i < numValues; i++) {
        sum += (data[i] - mean) * (data[i] - mean);
    }
    return sqrt(sum / numValues);
}

// Function to print the results
void printResults(int numValues, int capacity, float mean, float median, float stddev) {
    printf("Results:\n");
    printf("--------\n");
    printf("Num values:            %d\n", numValues);
    printf("      mean:        %.3f\n", mean);
    printf("    median:        %.3f\n", median);
    printf("    stddev:        %.3f\n", stddev);
    printf("Unused array capacity: %d\n", capacity - numValues);
}