#ifndef STATS_H
#define STATS_H

float *readDataFromFile(const char *filename, int *numValues, int *capacity);
float calculateMean(const float *data, int numValues);
float calculateMedian(float *data, int numValues);
float calculateStandardDeviation(const float *data, int numValues, float mean);
float *calculateMode(const float *data, int numValues, int *numModes);
float calculateGeometricMean(const float *data, int numValues);
float calculateHarmonicMean(const float *data, int numValues);
void printResults(int numValues, int capacity, float mean, float median, float stddev, float *modes, int numModes, float geometricMean, float harmonicMean);

#endif
