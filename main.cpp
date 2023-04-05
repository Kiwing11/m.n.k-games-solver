//
// Created by k123 on 03.05.2022.
//
#include <iostream>
#include <stdio.h>
#include <string.h>
#define MAXIMIZER '1'
#define MINIMIZER '2'
#define MAX 1000
#define MIN (-1000)
#define WIN 1
#define LOSS (-1)
#define DRAW 0
using namespace std;
bool doesWin(int N, int M, int K, char player, char ** tab);
void printTab(char** arr, int N, int M);
void printPosMov(char** arr, int N, int M, int posMov, char player);

struct Move{
    int x;
    int y;
    Move(){}
    Move(int x, int y){
        this->x = x;
        this->y = y;
    }
};

char otherPlayer(char player){
    if(player == '1')
        return '2';
    return '1';
}

void deleteTab(char** arr, int N, int M){
    for(int i = 0; i < N; i++)
        delete[] arr[i];
    delete[] arr;
}

char** createTab(int N, int M){
    char** tab = new char* [N];
    for(int i=0; i<N; i++)
        tab[i] = new char[M];
    return tab;
}

void fillTab(char** tab, int N, int M){
    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < M; j++){
            cin >> tab[i][j];
        }
    }
}

int countPosMov(char** arr, int N, int M){
    int counter = 0;
    for(int i = 0; i < N; i++){
        for(int j = 0; j < M; j++){
            if(arr[i][j] == '0')
                counter++;
        }
    }
    return counter;
}

int countAndPrintPosMovWithEnd(int N, int M, int K, char player, char** arr){
    int counter = 0;
    for(int i = 0; i < N; i++){
        for(int j = 0; j < M; j++){
            if(arr[i][j] == '0') {
                arr[i][j] = player;
                if(doesWin(N, M, K, player, arr)) {
                    counter = 1;
                    printf("%d\n", counter);
                    printTab(arr,N,M);
                    arr[i][j] = '0';// Przywrócenie poprzedniego stanu planszy
                    return counter;
                }
                else {
                    arr[i][j] = '0';// Przywrócenie poprzedniego stanu planszy
                    counter++;
                }
            }
        }
    }
    printf("%d\n",counter);
    printPosMov(arr,N,M,counter,player);
    return counter;
}

Move ifCanWinInOneTurn(char** arr, int N, int M, int K, char player){
    for(int i = 0; i < N; i++){
        for(int j = 0; j < M; j++){
            if(arr[i][j] == '0') {
                arr[i][j] = player;
                if(doesWin(N, M, K, player, arr)) {
                    arr[i][j] = '0';// Przywrócenie poprzedniego stanu planszy
                    return Move(j,i);
                }
                else {
                    arr[i][j] = '0';// Przywrócenie poprzedniego stanu planszy
                }
            }
        }
    }
    return Move(-1,-1);
}

void printTab(char** arr, int N, int M){
    for(int i = 0; i < N; i++){
        for(int j = 0; j < M; j++){
            printf("%c", arr[i][j]);
            if(j != M-1)
                printf(" ");
        }
        printf("\n");
    }
}

void printPosMov(char** arr, int N, int M, int posMov, char player){
    for(int j = 0; j < N; j++)
    {
        for(int k = 0; k < M; k++){
            if(arr[j][k] == '0'){
                arr[j][k] = player;
                printTab(arr, N, M);
                arr[j][k] = '0';
            }
        }
    }
}

bool doesWin(int N, int M, int K, char player, char ** tab){
    int counter = 0;
    //CHECKING BY ROWS
    for(int i = 0; i < N; i++){
        for(int j = 0; j < M; j++){
            if(tab[i][j] == player) {
                if(++counter == K)
                    return true;
            }
            else
                counter = 0;
        }
        if(counter == K)
            return true;
        counter = 0;
    }
    //CHECKING BY COLUMNS
    for(int i = 0; i < M; i++){
        for(int j = 0; j < N; j++){
            if(tab[j][i] == player) {
                if(++counter == K)
                    return true;
            }
            else
                counter = 0;
        }
        if(counter == K)
            return true;
        counter = 0;
    }
    for (int i = 0; i < N-1; ++i) {
        for (int j = 0; j < M-1; ++j) {

            if(tab[i][j] == player) {
                if(++counter == K)
                    return true;

                int iTemp = i;
                int jTemp = j;

                while(++iTemp != N && ++jTemp != M) {
                    if(tab[iTemp][jTemp] == player){
                        if(++counter == K)
                            return true;
                    }
                    else counter = 0;
                }
                counter = 0;
            }
            else counter = 0;
        }
        counter = 0;
    }
    //AGAINST DIAGONAL
    for (int i = 0; i < N; i++) {
        for(int j = M-1; j > 0; j--) {
            if(tab[i][j] == player) {
                if (++counter == K)
                    return true;

                int iTemp = i;
                int jTemp = j;

                while(++iTemp != N && --jTemp != -1) {
                    if(tab[iTemp][jTemp] == player){
                        if(++counter == K)
                            return true;
                    }
                    else counter = 0;
                }
                counter = 0;
            }
            else counter = 0;
        }
        counter = 0;
    }
    return false;
}

int minimax(char** arr, int N, int M, int K, char player){
    if(doesWin(N, M, K, MAXIMIZER, arr)) {
        return WIN;
    }
    if(doesWin(N, M, K, MINIMIZER, arr)) {
        return LOSS;
    }
    if(countPosMov(arr,N,M) == 0) {
        return DRAW;
    }

    if(player == MAXIMIZER){
        int best = MIN;
            for (int i = 0; i < N; i++) {
                for (int j = 0; j < M; j++) {
                    if (arr[i][j] == '0') {
                        arr[i][j] = player;

                        int tmp = minimax(arr, N, M, K, MINIMIZER);
                        if(best < tmp)
                            best = tmp;

                        arr[i][j] = '0'; // Przywrócenie poprzedniego stanu planszy
                        if(best == 1)
                            return 1;
                    }
                }
            }
        return best;
    }
    else{
        int best = MAX;
            for (int i = 0; i < N; i++) {
                for (int j = 0; j < M; j++) {
                    if (arr[i][j] == '0') {
                        arr[i][j] = player;

                        int tmp = minimax(arr, N, M, K, MAXIMIZER);
                        if(best > tmp)
                            best = tmp;

                        arr[i][j] = '0'; // Przywrócenie poprzedniego stanu planszy
                        if(best == -1)
                            return -1;
                    }
                }
            }
        return best;
        }
}

Move findBestMove(char** arr, int N, int M, int K, char player){
    int best_MAXIMIZER = MIN;
    int best_MINIMIZER = MAX;
    Move bestMove;
    bestMove.x = -1;
    bestMove.y = -1;

    Move tmpMove = ifCanWinInOneTurn(arr, N, M, K, otherPlayer(player)); // JEŚLI OPONENT MOZE WYGRAC W 1 POSUNIECIU
    if(tmpMove.y != -1){    // ZNALEZIONO TAKIE POSUNIECIE, ZE WYGRYWA W 1 RUCHU
        arr[tmpMove.y][tmpMove.x] = player;
        return tmpMove;
    }
    else {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                if (arr[i][j] == '0') {
                    arr[i][j] = player;

                    int thisMoveScore = minimax(arr, N, M, K, otherPlayer(player));

                    arr[i][j] = '0'; // Przywrócenie poprzedniego stanu planszy

                    if (player == MAXIMIZER) {
                        if (thisMoveScore > best_MAXIMIZER) {
                            bestMove.x = j;
                            bestMove.y = i;
                            best_MAXIMIZER = thisMoveScore;
                        }
                    }
                    if (player == MINIMIZER) {
                        if (thisMoveScore < best_MINIMIZER) {
                            bestMove.x = j;
                            bestMove.y = i;
                            best_MINIMIZER = thisMoveScore;
                        }
                    }
                }
            }
        }
        return bestMove;
    }
}

bool checkIfGameEnded(char** arr, int N, int M, int K){
    if (doesWin(N, M, K, MAXIMIZER, arr)) {
        printf("%s\n", "FIRST_PLAYER_WINS");
        return true;
    }
    if (doesWin(N, M, K, MINIMIZER, arr)) {
        printf("%s\n", "SECOND_PLAYER_WINS");
        return true;
    }
    if(countPosMov(arr,N,M) == 0) {
        printf("%s\n", "BOTH_PLAYERS_TIE");
        return true;
    }
    return false;
}

void solveGame(char** arr, int N, int M, int K, char player){
    if(!checkIfGameEnded(arr, N, M, K)) {
        if (ifCanWinInOneTurn(arr, N, M, K, player).y != -1) {
            if (player == MAXIMIZER)
                printf("%s\n", "FIRST_PLAYER_WINS");
            else
                printf("%s\n", "SECOND_PLAYER_WINS");
            return;
        }

        while (true) {
            if (doesWin(N, M, K, MAXIMIZER, arr)) {
                printf("%s\n", "FIRST_PLAYER_WINS");
                return;
            }
            if (doesWin(N, M, K, MINIMIZER, arr)) {
                printf("%s\n", "SECOND_PLAYER_WINS");
                return;
            }
            if (countPosMov(arr, N, M) == 0) {
                printf("%s\n", "BOTH_PLAYERS_TIE");
                return;
            }
            Move bestMove = findBestMove(arr, N, M, K, player);
            arr[bestMove.y][bestMove.x] = player;
            if (ifCanWinInOneTurn(arr, N, M, K, otherPlayer(player)).y != -1) {
                if (otherPlayer(player) == MAXIMIZER)
                    printf("%s\n", "FIRST_PLAYER_WINS");
                else
                    printf("%s\n", "SECOND_PLAYER_WINS");
                return;
            }
            player = otherPlayer(player);
        }
    }
}

int main(){
    char cmd [33];
    int N = 0;
    int M =0;
    int K = 0;
    char player = '0';
    char otherPlayer = '0';


    while(true){
        if(feof(stdin)!=0)
        {
            break;
        }

        cin >> cmd >> N >> M >> K >> player;
        if(player == '1')
            otherPlayer = '2';
        else
            otherPlayer = '1';

        if(strcmp(cmd, "GEN_ALL_POS_MOV") == 0)
        {
            char** array = createTab(N, M);
            fillTab(array,N,M);

            if(doesWin(N, M, K, player, array) || doesWin(N, M, K, otherPlayer, array))
                printf("0\n");
            else{
                int posMov = countPosMov(array, N, M);
                printf("%d\n",posMov);
                printPosMov(array, N, M, posMov, player);

            }

            deleteTab(array,N,M);
        }
        else if(strcmp(cmd, "GEN_ALL_POS_MOV_CUT_IF_GAME_OVER") == 0){
            char** array = createTab(N, M);
            fillTab(array,N,M);

            if(doesWin(N, M, K, player, array) || doesWin(N, M, K, otherPlayer, array))
                printf("0\n");
            else{
                countAndPrintPosMovWithEnd(N, M, K, player, array);
            }

            deleteTab(array,N,M);
        }
        else if(strcmp(cmd, "SOLVE_GAME_STATE") == 0){
            char** array = createTab(N, M);
            fillTab(array, N, M);
            solveGame(array,N,M,K,player);
            deleteTab(array, N, M);
        }
        else
            return 0;
    }
    return 0;
}

