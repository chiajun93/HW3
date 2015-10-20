#include <stdio.h>

int main(int argc, char *argv[]) {
    int error = validate_format(argv[1]);
    if (error == 0) {
        fprintf(stdout, "Valid!\n");
    } else {
        fprintf(stdout, "Not valid!\n");
    }
    return 0;
}