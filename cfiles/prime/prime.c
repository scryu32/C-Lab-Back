#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// 구조체, 타입스크립트나 자바 클래스 지정하는거 비슷한거임
typedef struct {
    int count;
    int* factors;
} PrimeFactors;

__declspec(dllexport) PrimeFactors getPrimeNumber(int n) {
    PrimeFactors result;
    result.factors = (int*)malloc(sizeof(int) * 64);
    
    if (result.factors == NULL) {
        result.count = 0;
        return result;
    }

    result.count = 0;

    if (n <= 1) {
        result.factors[result.count++] = 1;
        return result;
    }

    for (int i = 2; i <= sqrt(n); i++) {
        while (n % i == 0) {
            result.factors[result.count++] = i;
            n /= i;
        }
    }

    if (n > 1) {
        result.factors[result.count++] = n;
    }

    return result;
}

__declspec(dllexport) void freeArray(int* arr) {
    free(arr);
}
