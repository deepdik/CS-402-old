#ifndef STATS_H
#define STATS_H

float *readDataFromFile(const char *filename, int *numValues, int *capacity);
float calculateMean(const float *data, int numValues);
float calculateMedian(float *data, int numValues);
float calculateStandardDeviation(const float *data, int numValues, float mean);
void printResults(int numValues, int capacity, float mean, float median, float stddev);

#endif
