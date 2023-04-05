## The program supports 3 commands:
### ``` GEN_ALL_POS_MOV N M K ActivePlayer``` -  generating all possible moves along with their number
### ``` GEN_ALL_POS_MOV_CUT_IF_GAME_OVER N M K ActivePlayer``` - generating all possible moves along with their number, in case one of them is winning or ending, generating only the first of them
### ``` SOLVE_GAME_STATE N M K ActivePlayer``` - solve the game, and provide one of the three possible answers: FIRST_ PLAYER _WINS, SECOND_PLAYER_WINS, BOTH_PLAYERS_TIE.
## Example:
### Input:
```
GEN_ALL_POS_MOV_CUT_IF_GAME_OVER 3 3 3 1
0 2 1
2 2 1
0 1 0
```
### Output:
```
1
0 2 1
2 2 1
0 1 1
```
### Input:
```
SOLVE_GAME_STATE 3 3 3 2
1 0 0
0 0 0
0 0 0
```
### Output:
```
BOTH_PLAYERS_TIE
```
