#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

__declspec(dllexport) long long* getCollatz(long long n) {
    if (n < 1) {
        return NULL;
    }

    long long* result = (long long*)malloc(2 * sizeof(long long));
    if (result == NULL) {
        return NULL;
    }

    long long k = 0;
    long long biggest = n;

    while (n != 1) {
        // 콜라츠 추측의 수들은 갑자기 어떻게 튈지 모르기 때문에 64비트 최대정수값을 넘기면 자동으로 NULL을 리턴하도록 함
        if (n % 2 == 1) {
            if (n > (LONG_MAX - 1) / 3) {
                free(result); 
                return NULL; 
            }
            n = 3 * n + 1;
        } else {
            n = n / 2;
        }
        k += 1;
        if (n > biggest) {
            biggest = n;
        }
    }

    result[0] = k;
    result[1] = biggest;

    return result;
}

__declspec(dllexport) void freeArray(long long* arr) {
    free(arr);
}
