#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<stdbool.h>

// 천장 여부 넣으면 캐릭터 뽑아줌
// 완벽하게 만들었으니 절대 건들지말것
// 출력값 [0, 74] 같은식 ( 첫번째값은 0 혹은 1로 0이 픽업, 1이 픽뚫임 )
int* getCharacterArr(int* ceiling) {
    int* result = (int*)malloc(2 * sizeof(int));
    bool getFiveStar = false;
    int nowTimes = 0;
    int probabilityUP = 0;

    while (!getFiveStar) {
        nowTimes += 1;
        if (nowTimes > 73) {
            probabilityUP += 60;
        }
        int randomNumber = (rand() % 1000) + 1;

        if (randomNumber <= 6 + probabilityUP) {
            getFiveStar = true;
            if (*ceiling == 0) {
                int checkPickUp = rand() % 2;
                if (checkPickUp == 0) {
                    result[0] = 0; // 픽업
                } else {
                    int doublePickUp = rand() % 20;
                    if (doublePickUp == 0) {
                        result[0] = 0; // 픽업
                    } else {
                        result[0] = 1; // 픽뚫
                    }
                }
            } else {
                result[0] = 0; // 픽업
            }
            result[1] = nowTimes; // 돌린 횟수
        }
    }
    return result;
}

int** getOneSimTime(int consellation, int* totalPulls) {
    int nowConstellation = 0; // 최대 6
    int fiveStarNum = 0;
    int ceiling = 0;
    int maxStars = 12;
    int** result = (int**)malloc(maxStars * sizeof(int*));
    
    while (consellation >= nowConstellation) {
        int* myArray = getCharacterArr(&ceiling);
        result[fiveStarNum] = myArray;
        *totalPulls += myArray[1];
        fiveStarNum += 1;

        // 최대 배열 크기 초과 방지
        if (fiveStarNum >= maxStars) {
            maxStars *= 2; // 배열 크기 두 배로 증가
            result = (int**)realloc(result, maxStars * sizeof(int*));
        }
    }

    return result;
}

int main() {
    srand((unsigned int)time(NULL));
    int totalPulls = 0;
    int** myArray = getOneSimTime(6, &totalPulls);

    // 결과 출력
    for (int i = 0; i < 12; i++) {
        if (myArray[i] != NULL) {
            printf("Type: %d, Pulls: %d\n", myArray[i][0], myArray[i][1]);
            free(myArray[i]); // 동적 할당 해제
        }
    }
    free(myArray); // 배열 해제

    printf("Total pulls: %d\n", totalPulls);
    getchar();
}
