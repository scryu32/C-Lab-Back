#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

// 돌린 횟수를 가져오는 함수
int getCharacterTimes() {
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
        }
    }
    return nowTimes;
}

// 픽업인지 아닌지 확인하는 함수
// 픽업은 1, 픽뚫은 0을 리턴
int getCharacterPickUP() {
    int randomNumber = (rand() % 100) + 1;
    return (randomNumber <= 55) ? 1 : 0;
}

// 구조체
typedef struct {
    int totalTimes;
    int charlist[12][2];
} GenshinResult;

//구조체로 된거 반환함
GenshinResult* getGenshinCharacterPickUP(int constellation) {
    GenshinResult* result = (GenshinResult*)malloc(sizeof(GenshinResult));
    result->totalTimes = 0;
    int nowConstellation = 0;
    int checkPickUp;
    int ceiling = 0;
    int fivestars = 0;

    while (nowConstellation <= constellation && fivestars < 12) {
        int times = getCharacterTimes();
        result->totalTimes += times;

        // 천장이 없는 경우만 계산
        if (ceiling == 0) {
            checkPickUp = getCharacterPickUP();
            if (checkPickUp == 0) {
                ceiling = 1; // 픽뚫
                result->charlist[fivestars][0] = 0;
            } else {
                ceiling = 0;
                nowConstellation += 1;
                result->charlist[fivestars][0] = 1;
            }
        } else {
            nowConstellation += 1;
            result->charlist[fivestars][0] = 1;
        }
        result->charlist[fivestars][1] = times;
        fivestars += 1;
    }

    return result;
}

// 최종 함수
__declspec(dllexport) void get_simulation_result(int constellation, int simTimes, int ticket, int* mostLowest, int* resultArray, int* myRank) {
    srand(time(NULL));
    int lowest = ticket;
    int charlist[12][2];
    *myRank = 0;

    *mostLowest = ticket;
    
    for (int sim = 0; sim < simTimes; sim++) {
        int nowConstellation = 0;
        int allTimes = 0;
        int checkPickUp;
        int ceiling = 0;
        int fivestars = 0;

        while (nowConstellation <= constellation) {
            int times = getCharacterTimes();
            allTimes += times;

            if (ceiling == 0) {
                checkPickUp = getCharacterPickUP();
                if (checkPickUp == 0) {
                    ceiling = 1; // 픽뚫
                    charlist[fivestars][0] = 0;
                } else {
                    ceiling = 0;
                    nowConstellation += 1;
                    charlist[fivestars][0] = 1;
                }
            } else {
                nowConstellation += 1;
                charlist[fivestars][0] = 1;
            }

            charlist[fivestars][1] = times;
            fivestars += 1;
        }

        if (allTimes < *mostLowest) {
            *mostLowest = allTimes;
            for (int i = 0; i < 12; i++) {
                resultArray[2 * i] = charlist[i][0];
                resultArray[2 * i + 1] = charlist[i][1];
            }
        }
        if (allTimes < ticket) {
            *myRank += 1;
        }
    }
}







// 밑에 코드는 이중포인터가 들어가고 좀더 효율적인 코드 구조를 생각해냈기 때문에 폐기함
// 천장 여부 넣으면 캐릭터 뽑아줌
// 완벽하게 만들었으니 절대 건들지말것
// 출력값 [0, 74] 같은식 ( 첫번째값은 0 혹은 1로 0이 픽업, 1이 픽뚫임 )
// int* getCharacterArr(int* ceiling) {
//     int* result = (int*)malloc(2 * sizeof(int));
//     bool getFiveStar = false;
//     int nowTimes = 0;
//     int probabilityUP = 0;

//     while (!getFiveStar) {
//         nowTimes += 1;
//         if (nowTimes > 73) {
//             probabilityUP += 60;
//         }
//         int randomNumber = (rand() % 1000) + 1;

//         if (randomNumber <= 6 + probabilityUP) {
//             getFiveStar = true;
//             if (*ceiling == 0) {
//                 int checkPickUp = rand() % 2;
//                 if (checkPickUp == 0) {
//                     result[0] = 0; // 픽업
//                 } else {
//                     int doublePickUp = rand() % 20;
//                     if (doublePickUp == 0) {
//                         result[0] = 0; // 픽업
//                     } else {
//                         result[0] = 1; // 픽뚫
//                     }
//                 }
//             } else {
//                 result[0] = 0; // 픽업
//             }
//             result[1] = nowTimes; // 돌린 횟수
//         }
//     }
//     return result;
// }

// int** getOneSimTime(int consellation, int* totalPulls) {
//     int nowConstellation = 0; // 최대 6
//     int fiveStarNum = 0;
//     int ceiling = 0;
//     int maxStars = 12;
//     int** result = (int**)malloc(maxStars * sizeof(int*));
    
//     while (consellation >= nowConstellation) {
//         int* myArray = getCharacterArr(&ceiling);
//         result[fiveStarNum] = myArray;
//         *totalPulls += myArray[1];
//         fiveStarNum += 1;
//         if (fiveStarNum >= maxStars) {
//             maxStars *= 2; 
//             result = (int**)realloc(result, maxStars * sizeof(int*));
//         }
//     }

//     return result;
// }

// int main() {
//     srand((unsigned int)time(NULL));
//     int totalPulls = 0;
//     int** myArray = getOneSimTime(6, &totalPulls);

//     // 결과 출력
//     for (int i = 0; i < 12; i++) {
//         if (myArray[i] != NULL) {
//             printf("Type: %d, Pulls: %d\n", myArray[i][0], myArray[i][1]);
//             free(myArray[i]); // 동적 할당 해제
//         }
//     }
//     free(myArray); // 배열 해제

//     printf("Total pulls: %d\n", totalPulls);
//     getchar();
// }
