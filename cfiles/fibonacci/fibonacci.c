#include<stdio.h>
#include<stdlib.h>

// 롱롱써야 숫자 64비트정수까지 저장되는거라 좀더 큰값까지 됨
long long Fibonacci(int n){
    if (n <= 1){
        return n;
    }
    long long result = 0;
    long long iterA = 0, iterB = 1;

    for (int i = 2; i <= n; i++) {
        result = iterA + iterB;
        iterA = iterB;
        iterB = result;
    }
    // 재귀함수 안쓰는이유 : 메모리 호출 너무 깊어지고 성능도 안좋음
    return result;
}

// 앞에 붙어있는거는 동적 메모리 사용, 즉 포인터로 반환하겠다는소리
// + dll파일로 컴파일 할게요~ 라는 소리
__declspec(dllexport)  long long* getFibonacci(int k){
    long long* arr = (long long*)malloc(k * sizeof(long long)); //malloc은 동적으로 메모리 할당하겠다는 소리, 값 들어오면 메모리 차지하는정도 늘릴게요 라는 소리임
    for (int i=0; i < k; i++) {
        arr[i] = Fibonacci(i);
    }
    return arr;
}

// 메모리에 배열을 저장하면 영구적으로 저장되기 때문에 없애줘야함. 가비지 컬렉터 안되있는 언어들 특징
__declspec(dllexport) void freeArray(long long* arr) {
    free(arr);
}