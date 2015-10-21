#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "weatherio.h"

void anaylze(char *, char *, char *);
int getHeaderIndex(char *, char **, int);
char* lowerStrCase(char *);
double getMinValue(FILE *, int);
void readDataCols(char *, int);
int getTotalDataRows(char *file);

int main(int argc, char *argv[]) {
        int error = validate_format(argv[1]);
        
        if (error == 0) {
            fprintf(stdout, "Valid!\n");
        } else {
            fprintf(stdout, "Not valid!\n");
        }
    
        FILE *fp = fopen(argv[1], "r");
    if (fp == NULL) {
        fprintf(stdout, "Invalid file!");
        exit(1);
    }
        
    int headersCol = header_columns(argv[1]) ;
    char **headerData = (char **) malloc(sizeof (char *) * headersCol);
    
    int cols = read_header(argv[1], headerData) - 1;
    
    int j = 0;
    
    for(j = 0; j < headersCol; j++){
            printf("header %d : %s\n", j, headerData[j]);
        }
    
    int numRows = getTotalDataRows(argv[1]);
    
    
    
    char *str = (char *) malloc(sizeof(char) * 1000);
    char *row = fgets(str, 1000, fp);
    
    int dateIdx = getHeaderIndex("Date", headerData, cols);
    int hrMnIdx = getHeaderIndex("HrMn", headerData, cols);
  
    
    //Storage for data
//    int *data = (int *)malloc(sizeof(int) * numRows);
    
    fgets(row, 1000, fp);
    
    printf("Num rows: %d\n", numRows);
    int idx = 0;
//    for(idx = 0 ; idx < numRows; idx++){
        void **temp = (void **)malloc(sizeof(void *) * 20);

        read_row(fp, headerData, temp);
        
//        printf("Date: %d\n", *((int *)temp[3]));
//        int dsc = *((int *)temp[hrMnIdx]);
//        printf("Date: %d, HrMN: %d\n", atoi(temp[dateIdx]), atoi(temp[hrMnIdx]));
//        data[i] = *((int *)readData[idx]);
//        printf("Date: %d\n", data[idx]);
        weatherio_cleanup();
   
//    }
    
    
    fclose(fp);
    
//        anaylze(argv[1],"","" );
//        weatherio_cleanup();
//        util_cleanup();
    return 0;
}

int getHeaderIndex(char *target, char **header, int headersLength){
    int i = 0;
    
    for(i = 0; i < headersLength; i++){
        if(strcmp(header[i], target) == 0 ){
//            printf("%s\n", header[i]);
            return i;
        }
    }
    return - 1;
}

void anaylze(char *dataFile, char *inputFile, char *outputFile){
    //Range target
    
//    int headersCol = header_columns(dataFile) ;
//    char **headerData = (char **) malloc(sizeof (char *) * headersCol);
//    
//    int cols = read_header(dataFile, headerData) - 1;
//    
//    
//    FILE *fp = fopen(dataFile, "r");
//    if (fp == NULL) {
//        fprintf(stdout, "Invalid file!");
//        exit(1);
//    }
//    
//    char *str = (char *) malloc(sizeof(char) * 1000);
//    char *row = fgets(str, 1000, fp);
//    
//    int dateIdx = getHeaderIndex("Date", headerData, cols);
//    int hrMnIdx = getHeaderIndex("HrMn", headerData, cols);
    
//    printf("Date: %d , HrMn: %d\n", dateIdx, hrMnIdx);
    readDataCols(dataFile, 2);
    
//    fclose(fp);
}

double getMinValue(FILE *fp, int targetIdx){
    double min = 0.0;
    int numRows = 0;
    char *row;
    char s[2] = ",";
    char *token;
    char **arr = (char **)malloc(sizeof(char *) * 20);
    
    while(!feof(fp)){
        fgets(row, 100, fp);
        token = strtok(row, s);
        printf("Row %d: %s\n",numRows, row);
        int i = 0;
        while( token != NULL ) 
          {
           arr[i] = token;
           printf("Token : %s\n", arr[i]);
           token = strtok(NULL, s);
           i++;
        }
        numRows++;
    }
    
    return min;
}

void readDataCols(char *file, int targetIdx){
    int headersCol = header_columns(file) ;
    char **headerData = (char **) malloc(sizeof (char *) * headersCol);
    
    int cols = read_header(file, headerData) - 1;
    int numRows = getTotalDataRows(file);
    
    FILE *fp = fopen(file, "r");
<<<<<<< HEAD
    int numRows = 0;
    char *str = (char *) malloc(1000);
    char *row = fgets(str, 1000, fp);
    fgets(row, 1000, fp);
    
    int date[6];
    int hrMn[4];
        
    int headersCol = header_columns(file);
    char **headerData = (char **) malloc(sizeof (char *) * headersCol);
    void **temp = (void **) malloc(sizeof (void *) * headersCol);
    
    while(!feof(fp)){
        read_row(fp, headerData, temp);
        printf("Date: %s, HrMN: %s\n", temp[0], temp[1]);
        break;
    }
    
=======
    if (fp == NULL) {
        fprintf(stdout, "Invalid file!");
        exit(1);
    }
    
    char *str = (char *) malloc(sizeof(char) * 1000);
    char *row = fgets(str, 1000, fp);
    
    int dateIdx = getHeaderIndex("Date", headerData, cols);
    int hrMnIdx = getHeaderIndex("HrMn", headerData, cols);
    
    //Storage for data
//    int *data = (int *)malloc(sizeof(int) * numRows);
    
    fgets(row, 1000, fp);
    
    printf("Num rows: %d\n", numRows);
    int idx = 0;
    for(idx = 0 ; idx < numRows; idx++){
        void **readData = (void **)malloc(sizeof(void *) * 20);
        read_row(fp, headerData, readData);
        
        int abc = *((int *)readData[dateIdx]);
        int dsc = *((int *)readData[hrMnIdx]);
        printf("Date: %d, HrMN: %d\n", atoi(readData[dateIdx]), atoi(readData[hrMnIdx]));
//        data[i] = *((int *)readData[idx]);
//        printf("Date: %d\n", data[idx]);
        weatherio_cleanup();
    }
    
    
>>>>>>> Mac_Working
    fclose(fp);
}

int getTotalDataRows(char *file){
    FILE *fp = fopen(file, "r");
    int rows = 0;
    
    char *header = (char *) malloc(sizeof(char) * 2000);
    char *row = fgets(header, 1000, fp);
    while(!feof(fp)){
        rows++;
        fgets(header, 2000, fp);
    }
    
    return rows;
}
    
char* lowerStrCase(char *str){
    char* arr = malloc(sizeof(sizeof(char) * strlen(str)));
    int i = 0;
    int length = strlen(str);
    for(i = 0; i < length; i++)
    {
        char c = tolower(*str);
        arr[i] = c;
        *str++;
    }
    arr[i] = '\0';
    return arr;
}
