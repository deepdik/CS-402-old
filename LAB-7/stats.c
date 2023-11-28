#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "stats.h"
#include <stdbool.h>

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


// Function to check if all values in the dataset are unique
bool allValuesUnique(const float *data, int numValues) {
    for (int i = 0; i < numValues - 1; i++) {
        for (int j = i + 1; j < numValues; j++) {
            if (data[i] == data[j]) {
                return false;
            }
        }
    }
    return true;
}

// Modified calculateMode function
float *calculateMode(const float *data, int numValues, int *numModes) {
    if (numValues == 0 || allValuesUnique(data, numValues)) {
        *numModes = 0;
        return NULL;  // No mode for an empty set or when all values are unique
    }

    int maxStreak = 1;
    int currentStreak = 1;
    int modeCount = 1;
    float mode = data[0];

    for (int i = 0; i < numValues - 1; i++) {
        if (data[i] == data[i + 1]) {
            currentStreak++;
        } else {
            currentStreak = 1;
        }

        if (currentStreak > maxStreak) {
            maxStreak = currentStreak;
            modeCount = 1;
            mode = data[i];
        } else if (currentStreak == maxStreak) {
            // If the current streak equals the maximum streak, consider it another mode
            modeCount++;
        }
    }

    // Check if all values occurred only once
    if (maxStreak == 1) {
        *numModes = 0;
        return NULL;
    }

    *numModes = modeCount;
    
    // Allocate memory for the modes array
    float *modes = malloc(sizeof(float) * modeCount);
    if (modes == NULL) {
        perror("Error allocating memory");
        exit(1);
    }

    // Fill the modes array
    for (int i = 0; i < modeCount; i++) {
        modes[i] = mode;
    }

    return modes;
}



float calculateGeometricMean(const float *data, int numValues) {
    if (numValues == 0) {
        return 0;  // Geometric mean is undefined for an empty set
    }

    // Calculate the product of all values
    double product = 1.0;

    for (int i = 0; i < numValues; i++) {
        if (data[i] <= 0) {
            // Geometric mean is undefined for non-positive values
            return 0;
        }
        product *= data[i];
    }

    // Calculate the geometric mean
    return pow(product, 1.0 / numValues);
}

float calculateHarmonicMean(const float *data, int numValues) {
    if (numValues == 0) {
        return 0;  // Harmonic mean is undefined for an empty set
    }

    // Calculate the sum of reciprocals
    double reciprocalSum = 0.0;

    for (int i = 0; i < numValues; i++) {
        if (data[i] == 0) {
            // Harmonic mean is undefined if any value is zero
            return 0;
        }
        reciprocalSum += 1.0 / data[i];
    }

    // Calculate the harmonic mean
    return numValues / reciprocalSum;
}


// Function to print the results
void printResults(int numValues, int capacity, float mean, float median, float stddev, float *modes, int numModes, float geometricMean, float harmonicMean) {
    printf("Results:\n");
    printf("--------\n");
    printf("Num values:            %d\n", numValues);
    printf("      mean:        %.3f\n", mean);
    printf("    median:        %.3f\n", median);
    printf("    stddev:        %.3f\n", stddev);

    if (numModes == 0) {
        printf("      mode:       (0.000) No mode found. All values are unique\n");
    } else {
        printf("      mode(s):");
        for (int i = 0; i < numModes; i++) {
            printf(" %.3f", modes[i]);
        }
        printf("\n");
    }

    printf("  geometric mean:  %.3f\n", geometricMean);
    printf("  harmonic mean:   %.3f\n", harmonicMean);
    printf("Unused array capacity: %d\n", capacity - numValues);
}
