#include <stdio.h>
#include <math.h>
#include <stdlib.h>

__declspec(dllexport) char* getquadraticEquationAnswer(float a, float b, float c) {
    char* result = (char*)malloc(100 * sizeof(char));
    float discriminant = b * b - 4 * a * c;

    if (discriminant > 0) {
        sprintf(result, "%.2f, %.2f", 
                (-b + sqrt(discriminant)) / (2 * a), 
                (-b - sqrt(discriminant)) / (2 * a));
    } else if (discriminant == 0) {
        sprintf(result, "x = %.2f", -b / (2 * a));
    } else {
        sprintf(result, "%.2f + %.2fi, %.2f - %.2fi", 
                -b / (2 * a), sqrt(-discriminant) / (2 * a), 
                -b / (2 * a), sqrt(-discriminant) / (2 * a));
    }

    return result;
}


__declspec(dllexport) void freeArray(char* array) {
    free(array);
}
