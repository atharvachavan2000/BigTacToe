//Tic-Tac-Toe on a 9x9 Board
//author : Rohan B.

#include <iostream>
#include <vector>
using namespace std;

class Game{
    vector<vector<int>> board;

public:
    Game(); //init board & add option to choose mode later
    vector<int> validateMove(string move); //check if move is valid
    void applyMove(vector<int> move); //apply move if valid
    void displayBoard(); //display 9x9 board with proper A-I & 1-9 labels
    void playHuman(); //human vs human mode
    void playComp(); //human vs cpu mode
    void botMatch(); //cpu vs cpu mode
    void menu(); //for choosing one of the 3 modes
};

Game::Game(){
    board.resize(9, vector<int>(9, 0)); //init to 0
}

void Game::displayBoard(){
    cout<<"\t";
    for(int i = 0; i <board.size(); i++){
        for(int j = 0; j <board[i].size(); j++){
            if(j == 0 && i != 0)
                cout<<char(i + 64)<<"\t";
            else if(i == 0)
                cout<<j+1<<"\t";
            else{
                cout<<board[i][j]<<"\t";
            }
        }
        cout<<endl;
    }
}

class Bot{

};

int main(){
    Game g;
    g.displayBoard();
    return 0;
}