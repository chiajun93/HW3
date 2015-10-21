#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "weatherio.h"

//void anaylze(char *, char *, char *);
//int getHeaderIndex(char *, char **, int);
//char* lowerStrCase(char *);
//double getMinValue(FILE *, int);
//void readDataCols(char *, int, int, int);

int main(int argc, char *argv[]) {
//        int error = validate_format(argv[1]);
        
        int num = header_columns(argv[1]);
        
        char **headerData = (char **) malloc(sizeof (char *) * num);

        read_header(argv[1], headerData);
        void **temp = (void **) malloc(sizeof (void *) * num);
        
        FILE *fp;
        fp = fopen(argv[1], "r");
         if (fp == NULL) {
             fprintf(stdout, "Invalid file!\n");
             exit(1);
        }
        
        char *row = (char *)malloc(1000);
        fgets(row, 1000, fp);
        
        int error = read_row(fp, headerData, temp);
        
        printf("%d\n", *((int *)temp[0]));
        
        if (error == 0) {
            fprintf(stdout, "\nValid!");
        } else {
            fprintf(stdout, "\nNot valid!");
        }
    
//    FILE *fp = fopen(argv[1], "r");
//    if (fp == NULL) {
//        fprintf(stdout, "Invalid file!");
//        exit(1);
//    }
//    
//    fclose(fp);
//    anaylze(argv[1], " ", " ");

    return 0;
}
//
//int getHeaderIndex(char *target, char **header, int headersLength){
//    int i = 0;
//    char* lowerTarget;
//    lowerTarget = lowerStrCase(target);
//    
//    for(i = 0; i < headersLength; i++){
//        if(strcmp(header[i], lowerTarget) == 0 ){
//            printf("%s\n", header[i]);
//            return i;
//        }
//    }
//    return - 1;
//}
//
//void anaylze(char *dataFile, char *inputFile, char *outputFile){
//    //Range target
//    
//    int headersCol = header_columns(dataFile);
//    char **headerData = (char **) malloc(sizeof (char *) * headersCol);
//    
//    cols = read_header(dataFile, headerData);
//    
//    
//    FILE *fp = fopen(dataFile, "r");
//    if (fp == NULL) {
//        fprintf(stdout, "Invalid file!");
//        exit(1);
//    }
//    
//    char *str = (char *) malloc(1000);
//    char *row = fgets(str, 1000, fp);
//    
//    int dateIdx = getHeaderIndex("Date", headerData, cols);
//    int hrMnIdx = getHeaderIndex("HrMn", headerData, cols);
//    
//    printf("Date: %d , HrMn: %d\n", dateIdx, hrMnIdx);
//    readDataCols(dataFile, 2, dateIdx, hrMnIdx);
//    
//    fclose(fp);
//}
//
//double getMinValue(FILE *fp, int targetIdx){
//    double min = 0.0;
//    int numRows = 0;
//    char *row;
//    char s[2] = ",";
//    char *token;
//    char **arr = (char **)malloc(sizeof(char *) * 20);
//    
//    while(!feof(fp)){
//        fgets(row, 100, fp);
//        token = strtok(row, s);
//        printf("Row %d: %s\n",numRows, row);
//        int i = 0;
//        while( token != NULL ) 
//          {
//           arr[i] = token;
//           printf("Token : %s\n", arr[i]);
//           token = strtok(NULL, s);
//           i++;
//        }
//        numRows++;
//    }
//    
//    return min;
//}
//
//void readDataCols(char *file, int targetIdx, int dateIdx, int hrMnIdx){
//    FILE *fp = fopen(file, "r");
//    int numRows = 0;
//    char *row = (char *)malloc(sizeof(char) * 1000);
//    char s[2] = ",";
//    char *token;
//    char **arr = (char **)malloc(sizeof(char *) * 20);
//    fgets(row, 1000, fp);
//    int date[6];
//    int hrMn[4];
//    
//    
//    while(!feof(fp)){
//        fgets(row, 1000, fp);
//        token = strtok(row, s);
//        int i = 0;
//        while( token != NULL ) 
//          {
//           arr[i] = token;
////           printf("Token : %s\n", arr[i]);
//           token = strtok(NULL, s);
//           i++;
//        }
//        printf("Date: %s, HrMN: %s\n", arr[dateIdx], arr[hrMnIdx]);
//        
//    }
//    fclose(fp);
//}    
//    
//char* lowerStrCase(char *str){
//    char* arr = malloc(sizeof(sizeof(char) * strlen(str)));
//    int i = 0;
//    int length = strlen(str);
//    for(i = 0; i < length; i++)
//    {
//        char c = tolower(*str);
//        arr[i] = c;
//        *str++;
//    }
//    arr[i] = '\0';
//    return arr;
//}
