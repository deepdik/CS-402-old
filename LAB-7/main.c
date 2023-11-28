#include <stdio.h>
#include <stdlib.h>
#include "stats.h"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <input_file>\n", argv[0]);
        return 1;
    }

    const char *filename = argv[1];
    int numValues, capacity, numModes;
    float *data = readDataFromFile(filename, &numValues, &capacity);

    if (numValues == 0) {
        printf("No data found in the input file.\n");
        free(data);
        return 1;
    }

    float mean = calculateMean(data, numValues);
    float median = calculateMedian(data, numValues);
    float stddev = calculateStandardDeviation(data, numValues, mean);
    
    float *modes = calculateMode(data, numValues, &numModes);

    float geometricMean = calculateGeometricMean(data, numValues);
    float harmonicMean = calculateHarmonicMean(data, numValues);

    printResults(numValues, capacity, mean, median, stddev, modes, numModes, geometricMean, harmonicMean);

    free(data);
    free(modes);
    return 0;
}
