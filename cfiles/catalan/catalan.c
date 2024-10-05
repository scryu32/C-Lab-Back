#include<stdio.h>

// __declspec(dllexport) long long factorial(int n) {
//     long long k = 1;
//     for (int i = 2; i <= n; i++) {
//         k *= i;
//     }
//     return k;
// }

// __declspec(dllexport) long long getCatalanArr(int n) {
//     long long bunja, bunmo;
    
//     bunja = factorial(2 * n);
//     bunmo = factorial(n + 1) * factorial(n);
//     printf("%lld\n", bunja/bunmo);
//     printf("%lld\n", bunja);
//     printf("%lld\n", bunmo);
    
//     return bunja / bunmo;
// }

// 팩토리얼을 직접 계산하면 longlong도 감당 못할정도로 숫자가 너무 커짐. 그냥 공식써서 구하는게 빠를거같음

__declspec(dllexport) long long getCatalanArr(int n) {
    long long catalan[n + 1];
    catalan[0] = 1;  // C(0) = 1

    for (int i = 1; i <= n; i++) {
        catalan[i] = 0;
        for (int j = 0; j < i; j++) {
            catalan[i] += catalan[j] * catalan[i - j - 1];
        }
    }
    
    return catalan[n];
}
