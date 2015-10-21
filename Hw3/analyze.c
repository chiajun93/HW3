#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "weatherio.h"
#include "util.h"

void anaylze(char *, char *, char *);
int getHeaderIndex(char *, char **, int);
float getMinValue(float givenData[], int n);
float getMaxValue(float givenData[], int n);
float getAverage(float givenData[], int n);
void readDataCols(char *dataFile, char *input);
int getTotalDataRows(char *file);
void quick_sort(int *a, int n);
char** splitDate(char *givenDate);

int main(int argc, char *argv[]) {
    int error = validate_format(argv[1]);

    if (error == 0) {
        fprintf(stdout, "Valid!\n");
    } else {
        fprintf(stdout, "Not valid!\n");
    }
    
    char inputCmd[100] = "min Temp 05/21/2010-00:11 05/21/2014-23:14";
    readDataCols(argv[1], inputCmd);
    
    return 0;
}

int getHeaderIndex(char *target, char **header, int headersLength) {
    int i = 0;

    for (i = 0; i < headersLength; i++) {
        if (strcmp(header[i], target) == 0) {
            //printf("%s\n", header[i]);
            return i;
        }
    }
    return -1;
}

void anaylze(char *dataFile, char *inputFile, char *outputFile) {
    //Range target

    readDataCols(dataFile, "min Temp 05/21/2010-00:00 05/21/2014-23:14");
}

float getMinValue(float givenData[], int n) {
    float min = givenData[0];
    int i = 0;

    for (i = 1; i < n; i++) {
        if (givenData[i] < min) {
            min = givenData[i];
//            printf("Value: %f\n", givenData[i]);
        }
    }
    return min;
}

float getMaxValue(float givenData[], int n) {
    float max = givenData[0];
    int i = 0;

    for (i = 1; i < n; i++) {
        if (givenData[i] > max) {
            max = givenData[i];
//            printf("Value: %f\n", givenData[i]);
        }
    }

    return max;
}

float getAverage(float givenData[], int n) {
    float sum = 0.0;
    int i = 0;

    for (i = 0; i < n; i++) {
        sum += givenData[i];
    }

    float avg = sum / n;

    return avg;
}

void readDataCols(char *file, char *input) {

    FILE *fp = fopen(file, "r");

    if (fp == NULL) {
        fprintf(stdout, "Invalid file!");
        exit(1);
    }
    
    //Split the input command parameters
    char *token;
    char **tokArr = (char **)malloc(sizeof(char *) * 5);
    char delimiter[2] = " ";
    int z = 0;
    
    token = strtok(input, delimiter);
    while(token != NULL){
        tokArr[z] = token;
        printf("Token: %s\n", tokArr[z]);
        token = strtok(NULL, delimiter);
        z++;
    }
    free(token);
//    printf("Token Arr: %s\n", tokArr[2]);
    
    //Get the start date
    char **startDateArr = (char **)malloc(sizeof(char*) * 3);
    startDateArr = splitDate(tokArr[2]);
    int startDate = atoi(startDateArr[0]);
    int startTime = atoi(startDateArr[1]);
//    printf("Start date: %d\n", startDate);
//    printf("Start time: %d\n", startTime);
    
    //Get the end date
    char **endtDateArr = (char **)malloc(sizeof(char*) * 3);
    endtDateArr = splitDate(tokArr[3]);
    int endDate = atoi(endtDateArr[0]);
    int endTime = atoi(endtDateArr[1]);
//    printf("End date: %d\n", endDate);
//    printf("End time: %d\n", endTime);
    
    int headersCol = header_columns(file);
    char **headerData = (char **) malloc(sizeof (char *) * (headersCol + 1) );

    int cols = read_header(file, headerData);

    //Another file pointer to count total number of rows.
    //    FILE *getRows = fopen(file, "r");
    //    int rows = 0;
    //    char *header = (char *) malloc(sizeof (char *) * 1000);
    //    fgets(header, 1000, getRows);
    //    while (!feof(getRows)) {
    //        rows++;
    //        fgets(header, 2000, getRows);
    //    }
    //    free(header);
    //    printf("ROWS : %d", rows);
    //    fclose(getRows);

    int numRows = getTotalDataRows(file);

    int j = 0;
    for (j = 0; j < headersCol; j++) {
        printf("header %d: %s\n", j, headerData[j]);
    }

    //Skip headers
    char *str = (char *) malloc(sizeof (char) * (64 * headersCol));
    fgets(str, sizeof(char) * (64 * headersCol), fp);
    free(str);

    //Get date, hrmn, and target indexs
    int dateIdx = getHeaderIndex("Date", headerData, cols);
    int hrMnIdx = getHeaderIndex("HrMn", headerData, cols);
    int targetIdx = getHeaderIndex(tokArr[1], headerData, cols);
    //    printf("Date idx: %d\n", dateIdx);
    //    printf("HrMn idx: %d\n", hrMnIdx);
    //    printf("Target idx: %d\n", targetIdx);

    //Storage for data
    
    float floatData[numRows];
    int intData[numRows];

    for (j = 0; j < numRows; j++) {
        floatData[j] = 0.0;
        intData[j] = 0;
    }

    printf("Num rows: %d\n", numRows);
    int idx = 0;
    int relevantRecs = 0;

    void **readData = (void **) malloc(sizeof (void *) * cols);
    for (idx = 0; idx < numRows; idx++) {

        read_row(fp, headerData, readData);

        int date = *((int *) readData[dateIdx]);
        int hrmn = *((int *) readData[hrMnIdx]);

        if (date >= startDate && date <= endDate) {
            if (hrmn >= startTime & hrmn <= endTime) {
                relevantRecs++;

                printf("Date: %d, HrMn: %d\n", date, hrmn);

                switch (column_type(headerData[targetIdx])) {
                    case FLOAT:
                    {
                        float value = *((float *) readData[targetIdx]);
                        floatData[idx] = value;
                        //printf("Data: %f\n", data[idx]);
                        break;
                    }

                    case INT:
                    {
                        int value = *((int *) readData[targetIdx]);
                        floatData[idx] = value;
//                        printf("Data: %d\n", data[idx]);
                        break;
                    }

                    case STRING:
                    {
                        printf("IT IS A STRING TYPE\n");
                        break;
                    }

                    case CHAR:
                    {
                        printf("IT IS A CHAR TYPE\n");
                        break;
                    }

                    default:
                    {
                        printf("Invalid Type!\n");
                        break;
                    }
                }
                util_cleanup();
            }
        }

        weatherio_cleanup();
    }
    
    float retVal = 0.0;
    
       if(strcmp(tokArr[0],"min") == 0){
            retVal = getMinValue(floatData, relevantRecs);
        }
       else if(strcmp(tokArr[0],"max") == 0){
            retVal = getMaxValue(floatData, relevantRecs);
           
        }
       else if(strcmp(tokArr[0],"average") == 0){
            retVal = getAverage(floatData, relevantRecs);
        }
       else{
            printf("Invalid function command.\n");
           
        }

    printf("Val asked: %f\n", retVal);
    fclose(fp);
}

int getTotalDataRows(char *file) {
    FILE *readFile = fopen(file, "r");
    int rows = 0;

    char *header = (char *) malloc(sizeof (char *) * 1000);
    fgets(header, 1000, readFile);
    while (!feof(readFile)) {
        rows++;
        fgets(header, 2000, readFile);
    }
    free(header);

    fclose(readFile);
    return rows;
}

char** splitDate(char *givenDate){
    char *splitedItem;
    char **dateTokArr = (char **)malloc(sizeof(char *) * 4);
    char delimiter[2] = "/";
  
    splitedItem = strtok(givenDate, delimiter);
    int z = 0;
    while(splitedItem != NULL){
        dateTokArr[z] = splitedItem;
//        printf( "Token: %s\n", dateTokArr[z]);
        splitedItem = strtok(NULL, delimiter);
        z++;
    }
    
    //Split date and hrmn
    delimiter[0] = '-';
    splitedItem = strtok(dateTokArr[2], delimiter);
//    printf("Date Splited: %s\n", splitedItem);
    
    splitedItem = strtok(NULL, delimiter);
//    printf( "HRMN: %s\n", splitedItem);
    
    //Split Hr and Mn
    delimiter[0] = ':';
    char *hr = (char *)malloc(sizeof(char) * 2);
    char *mn = (char *)malloc(sizeof(char) * 2);
    char *hrMnArr = (char *)malloc(sizeof(char) * 5);
    hr = strtok(splitedItem, delimiter);
    mn = strtok(NULL, delimiter);
//    printf("Hr: %s, Mn: %s\n", hr, mn);
    
    //Append time to match data format
    strcat(hrMnArr,hr);
    strcat(hrMnArr,mn);
//    printf("Time: %s\n",hrMnArr);
    
    //Append date to match data format
    char *dateArr = (char *)malloc(sizeof(char) * 7);
    strcat(dateArr, dateTokArr[2]);
    strcat(dateArr, dateTokArr[0]);
    strcat(dateArr, dateTokArr[1]);
   
    char **dateInfo = (char **)malloc(sizeof(char *) * 3);
    dateInfo[0] = dateArr;
    dateInfo[1] = hrMnArr;
    
    return dateInfo;
}

void freeDoublePt(char **givenDp, int n){
    int i = 0;
    
    for(i = 0; i < n; i++){
        free(givenDp[i]);
    }
    free(givenDp);
}

void quick_sort(int *a, int n) {
    if (n < 2)
        return;
    int p = a[n / 2];
    int *l = a;
    int *r = a + n - 1;
    while (l <= r) {
        if (*l < p) {
            l++;
        } else if (*r > p) {
            r--;
        } else {
            int t = *l;
            *l = *r;
            *r = t;
            l++;
            r--;
        }
    }
    quick_sort(a, r - a + 1);
    quick_sort(l, a + n - l);
}