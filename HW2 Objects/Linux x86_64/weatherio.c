#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "weatherio.h"

int validate_format(char *file) {
    FILE *fp;
    fp = fopen(file, "r");
    if (fp == NULL) {
        fprintf(stdout, "Invalid file!");
        exit(1);
    }

    int headersCol = header_columns(file);
    printf("%d\n", headersCol);
    char **headerData = (char **) malloc(sizeof (char *) * headersCol);

    cols = read_header(file, headerData);
    void **temp = (void **) malloc(sizeof (void *) * headersCol);

    temp[0] = headersCol;

    char c;
    int line = 2;
    char *str = (char *) malloc(1000);
    char *row = fgets(str, 1000, fp);
    int error = 0;
    while (!feof(fp)) {
        int error = read_row(fp, headerData, temp);
        if (error != 0) {
            printf("\nError code: %d\n", error);
            printf("\nLine: %d\n", line);
            return line;
        }
        line++;
    }
    fclose(fp);
}

int header_columns(char *file) {
    FILE *fp;
    fp = fopen(file, "r");
    if (fp == NULL) {
        fprintf(stdout, "Invalid file!");
        exit(1);
    }

    char *headers;
    char temp[145];
    int i = 0;
    int headerColumns = 1;

    headers = fgets(temp, sizeof temp, fp);

    while (headers[i] != '\0') {
        if (headers[i] == ',') {
            headerColumns++;
        }

        i++;
    }
    fclose(fp);
    return headerColumns;
}

int read_header(char *file, char **buffer) {
    FILE *fp;
    fp = fopen(file, "r");
    if (fp == NULL) {
        fprintf(stderr, "Invalid file!");
        exit(1);
    }

    buffer[0] = (char *) malloc(64);
    char *p = buffer[0];
    int i = 0;
    char c;

    while ((c = getc(fp)) != '\n') {
        if (c == ',') {
            *p = '\0';
            i++;
            buffer[i] = (char *) malloc(64);
            p = buffer[i];
        } else {
            c = tolower(c);
            *p++ = c;
        }
    }
    *p = '\0';
    fclose(fp);

    return i + 1;
}

int read_row(FILE *fp, char **headers, void **buffer) {

    char *p;
    char c;
    int i = 0;
    int j = 0;
    int unique[cols];
    char *header;

    header = headers[0];
    printf("%s\n", headers[0]);

    for (j = 0; j < cols; j++) {
        unique[j] = 0;
    }

    for (j = 0; j < cols; j++) {
        if (strcmp(headers[j], "") == 0) {
            return INVALID_HEADER;
        } else if (strcmp(headers[j], "identification name") == 0) {
            unique[j]++;
        } else if (strcmp(headers[j], "usaf") == 0) {
            unique[j]++;
        } else if (strcmp(headers[j], "ncdc") == 0) {
            unique[j]++;
        } else if (strcmp(headers[j], "date") == 0) {
            unique[j]++;
        } else if (strcmp(headers[j], "hrmn") == 0) {
            unique[j]++;
        } else if (strcmp(headers[j], "i") == 0) {
            unique[j]++;
        } else if (strcmp(headers[j], "type") == 0) {
            unique[j]++;
        } else if (strcmp(headers[j], "qcp") == 0) {
            unique[j]++;
        } else if (strcmp(headers[j], "wind dir") == 0) {
            unique[j]++;
        } else if (strcmp(headers[j], "wind dir q") == 0) {
            unique[j]++;
        } else if (strcmp(headers[j], "wind dir i") == 0) {
            unique[j]++;
        } else if (strcmp(headers[j], "wind spd") == 0) {
            unique[j]++;
        } else if (strcmp(headers[j], "wind spd q") == 0) {
            unique[j]++;
        } else if (strcmp(headers[j], "temp") == 0) {
            unique[j]++;
        } else if (strcmp(headers[j], "temp q") == 0) {
            unique[j]++;
        } else if (strcmp(headers[j], "dewpt") == 0) {
            unique[j]++;
        } else if (strcmp(headers[j], "dewpt q") == 0) {
            unique[j]++;
        } else if (strcmp(headers[j], "slp") == 0) {
            unique[j]++;
        } else if (strcmp(headers[j], "slp q") == 0) {
            unique[j]++;
        } else if (strcmp(headers[j], "rhx") == 0) {
            unique[j]++;
        } else {
            return INVALID_HEADER;
        }
    }

    for (j = 0; j < cols; j++) {
        if (unique[j] > 1) {
            return INVALID_HEADER;
        }
    }
    printf("\n");
    char *array[] = {
        "AERO",
        "AUST",
        "AUTO",
        "BOGUS",
        "BRAZ",
        "COOPD",
        "COOPS",
        "CRB",
        "CRN05",
        "CRN15",
        "FM-12",
        "FM-13",
        "FM-14",
        "FM-15",
        "FM-16",
        "FM-18",
        "GREEN",
        "MESOS",
        "MEXIC",
        "NSRDB",
        "PCP15",
        "PCP60",
        "S-S-A",
        "SA-AU",
        "SAO",
        "SAOSP",
        "SHEF",
        "SMARS",
        "SOD",
        "SOM",
        "SURF",
        "SY-AE",
        "SY-AU",
        "SY-MT",
        "SY-SA",
        "WBO",
        "WNO",
    };

    while ((c = getc(fp)) != '\n' && c != EOF) {

        if (strcmp(headers[i], "identification name") == 0) {
            buffer[i] = (char *) malloc(sizeof (char) * 64);
        } else if (strcmp(headers[i], "usaf") == 0) {
            buffer[i] = (int *) malloc(sizeof (int));
        } else if (strcmp(headers[i], "ncdc") == 0) {
            buffer[i] = (int *) malloc(sizeof (int));
        } else if (strcmp(headers[i], "date") == 0) {
            buffer[i] = (int *) malloc(sizeof (int));
        } else if (strcmp(headers[i], "hrmn") == 0) {
            buffer[i] = (int *) malloc(sizeof (int));
        } else if (strcmp(headers[i], "i") == 0) {
            buffer[i] = (char *) malloc(sizeof (char) * 1);
        } else if (strcmp(headers[i], "type") == 0) {
            buffer[i] = (char *) malloc(sizeof (char) * 5);
        } else if (strcmp(headers[i], "qcp") == 0) {
            buffer[i] = (char *) malloc(sizeof (char) * 4);
        } else if (strcmp(headers[i], "wind dir") == 0) {
            buffer[i] = (int *) malloc(sizeof (int));
        } else if (strcmp(headers[i], "wind dir q") == 0) {
            buffer[i] = (int *) malloc(sizeof (int));
        } else if (strcmp(headers[i], "wind dir i") == 0) {
            buffer[i] = (char *) malloc(sizeof (char) * 1);
        } else if (strcmp(headers[i], "wind spd") == 0) {
            buffer[i] = (double *) malloc(sizeof (double) * 4);
        } else if (strcmp(headers[i], "wind spd q") == 0) {
            buffer[i] = (int *) malloc(sizeof (int) * 1);
        } else if (strcmp(headers[i], "temp") == 0) {
            buffer[i] = (double *) malloc(sizeof (double) * 6);
        } else if (strcmp(headers[i], "temp q") == 0) {
            buffer[i] = (char *) malloc(sizeof (char) * 1);
        } else if (strcmp(headers[i], "dewpt") == 0) {
            buffer[i] = (double *) malloc(sizeof (double) * 6);
        } else if (strcmp(headers[i], "dewpt q") == 0) {
            buffer[i] = (int *) malloc(sizeof (int) * 1);
        } else if (strcmp(headers[i], "slp") == 0) {
            buffer[i] = (double *) malloc(sizeof (double) * 5);
        } else if (strcmp(headers[i], "slp q") == 0) {
            buffer[i] = (int *) malloc(sizeof (int) * 1);
        } else if (strcmp(headers[i], "rhx") == 0) {
            buffer[i] = (int *) malloc(sizeof (int) * 3);
        } else {
            return 1;
        }

        p = buffer[i];

        while (c != ',' && c != '\n' && c != EOF) {
            *p++ = c;
            c = getc(fp);
        }

        *p = '\0';

        printf("%s ,", buffer[i]);

        if (c == '\n') {
            break;
        }

        if (c != EOF) {
            i++;
            p = buffer[i];
        }
    }

    for (j = 0; j < i; j++) {
        int type = 0;
        int idx;
        char *pt = buffer[j];

        if (strcmp(headers[j], "identification name") == 0) {

        } else if (strcmp(headers[j], "usaf") == 0) {
            if (strlen(buffer[j]) > 6) {
                return INVALID_DATA_LENGTH;
            } else {
                type = 7;
            }
        } else if (strcmp(headers[j], "ncdc") == 0) {
            if (strlen(buffer[j]) > 5) {
                return INVALID_DATA_LENGTH;
            }
        } else if (strcmp(headers[j], "date") == 0) {
            if (strlen(buffer[j]) > 8) {
                return INVALID_DATA_LENGTH;
            } else {
                type = 7;
            }
        } else if (strcmp(headers[j], "hrmn") == 0) {
            if (strlen(buffer[j]) > 4) {
                return INVALID_DATA_LENGTH;
            } else {
                type = 7;
            }
        } else if (strcmp(headers[j], "i") == 0) {
            if (strlen(buffer[j]) > 1) {
                return INVALID_DATA_LENGTH;
            } else {
                type = 3;
            }
        } else if (strcmp(headers[j], "type") == 0) {
            if ((strlen(buffer[j]) <= 0)) {
                continue;
            } else if (strlen(buffer[j]) > 5) {
                return INVALID_DATA_LENGTH;
            } else {
                type = 6;
            }
        } else if (strcmp(headers[j], "qcp") == 0) {
            if (strlen(buffer[j]) > 4) {
                return INVALID_DATA_LENGTH;
            } else {

            }
        } else if (strcmp(headers[j], "wind dir") == 0) {
            if (strlen(buffer[j]) > 3) {
                return INVALID_DATA_LENGTH;
            } else {
                type = 1;
            }
        } else if (strcmp(headers[j], "wind dir q") == 0) {
            if (strlen(buffer[j]) > 1) {
                return INVALID_DATA_LENGTH;
            } else {
                if (atoi(pt) == 8) {
                    return -2;
                }
                type = 1;
            }
        } else if (strcmp(headers[j], "wind dir i") == 0) {
            if (strlen(buffer[j]) <= 0) {
                continue;
            } else if (strlen(buffer[j]) > 1) {
                return INVALID_DATA_LENGTH;
            } else {
                type = 4;
            }
        } else if (strcmp(headers[j], "wind spd") == 0) {
            if (strlen(buffer[j]) > 5) {
                return INVALID_DATA_LENGTH;
            } else {
                type = 2;
            }
        } else if (strcmp(headers[j], "wind spd q") == 0) {
            if (strlen(buffer[j]) > 1) {
                return INVALID_DATA_LENGTH;
            } else {
                if (atoi(pt) == 8) {
                    return -2;
                }
                type = 1;
            }
        } else if (strcmp(headers[j], "temp") == 0) {
            if (strlen(buffer[j]) > 6) {
                return INVALID_DATA_LENGTH;
            } else {
                type = 2;
            }
        } else if (strcmp(headers[j], "temp q") == 0) {
            if (strlen(buffer[j]) > 1) {
                return INVALID_DATA_LENGTH;
            } else {
                type = 5;
            }
        } else if (strcmp(headers[j], "dewpt") == 0) {
            if (strlen(buffer[j]) > 6) {
                return INVALID_DATA_LENGTH;
            } else {
                type = 2;
            }
        } else if (strcmp(headers[j], "dewpt q") == 0) {
            if (strlen(buffer[j]) > 1) {
                return INVALID_DATA_LENGTH;
            } else if (atoi(pt) == 8) {
                return -2;
            }
        } else if (strcmp(headers[j], "slp") == 0) {
            if (strlen(buffer[j]) > 6) {
                return INVALID_DATA_LENGTH;
            } else {
                type = 2;
            }
        } else if (strcmp(headers[j], "slp q") == 0) {
            if (strlen(buffer[j]) > 1) {
                return INVALID_DATA_LENGTH;
            } else {
                type = 1;
            }
        } else if (strcmp(headers[j], "rhx") == 0) {
            if (strlen(buffer[j]) > 3) {
                return INVALID_DATA_LENGTH;
            } else {
                type = 1;
            }
        } else {
            return 1;
        }

        if (type == 7) {
            for (idx = 0; idx < strlen(buffer[j]); idx++) {
                if (!isdigit(*pt)) {
                    return -2;
                } else {
                    *pt++;
                }
            }
        } else if (type == 1) {
            for (idx = 0; idx < strlen(buffer[j]); idx++) {
                if (*pt == ' ') {
                    *p++;
                } else if (!isdigit(*pt)) {
                    return -2;
                } else {
                    *pt++;
                }
            }
        } else if (type == 2) {
            for (idx = 0; idx < strlen(buffer[j]); idx++) {
                if (*pt == ' ') {
                    *p++;
                } else if (*pt != '.' && !isdigit(*pt) && *pt != '-' && *pt != '+') {
                    return -2;
                } else {
                    *pt++;
                }
            }
        } else if (type == 3) {

            if (*pt == ' ') {
                *p++;
            } else if (*pt == '9' || *pt == '0' || *pt > 'N') {
                return -2;
            } else {
                *pt++;
            }
        } else if (type == 4) {
            if (*pt == ' ') {
                *p++;
            } else if (*pt == '9' || (*pt >= 'A' && *pt <= 'C') || *pt == 'H' || *pt == 'N' || *pt == 'Q' || *pt == 'R' || *pt == 'T' || *pt == 'V') {
                *pt++;
            } else {
                return -2;
            }
        } else if (type == 5) {
            if (isdigit(*pt) || *pt == 'A' || *pt == 'C' || *pt == 'I' || *pt == 'M' || *pt == 'P' || *pt == 'R' || *pt == 'U' || *pt == '\0') {
                *pt++;
            } else {
                return -2;
            }
        } else if (type == 6) {
            int found = 0;
            if (*pt == ' ') {
                found = 1;
                for (idx = 0; idx < strlen(buffer[j]); idx++) {
                    *p++;
                }
            } else {
                for (idx = 0; idx < 36; idx++) {
                    if (strcmp(pt, array[idx]) == 0) {
                        found = 1;
                    }
                }
            }

            if (found == 0) {
                return -2;
            }
        }
        printf("\ni: %d , cols: %d\n", i, cols);
        if (cols != i + 1) {
            return -4;
        }


    }
    return 0;
}