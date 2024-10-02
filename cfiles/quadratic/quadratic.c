#include <stdio.h>
#include <math.h>
#include <stdlib.h>

__declspec(dllexport) char* getquadraticEquationAnswer(float a, float b, float c) {
    char* result = (char*)malloc(100 * sizeof(char));  // 메모리 동적 할당
    float discriminant = b * b - 4 * a * c;

    if (discriminant > 0) {
        sprintf(result, "x1 = %.2f, x2 = %.2f", 
                (-b + sqrt(discriminant)) / (2 * a), 
                (-b - sqrt(discriminant)) / (2 * a));
    } else if (discriminant == 0) {
        sprintf(result, "x = %.2f", -b / (2 * a));
    } else {
        sprintf(result, "x1 = %.2f + %.2fi, x2 = %.2f - %.2fi", 
                -b / (2 * a), sqrt(-discriminant) / (2 * a), 
                -b / (2 * a), sqrt(-discriminant) / (2 * a));
    }

    return result;  // 결과 반환
}

// 메모리 해제를 위한 함수
__declspec(dllexport) void freeArray(char* array) {
    free(array);
}
