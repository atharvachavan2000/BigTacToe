//Tic-Tac-Toe on a 9x9 Board
//author : Rohan B.

#include <iostream>
#include <vector>
using namespace std;

class Game{
    vector<vector<int>> board;
    int activePlayer;

public:
    Game(); //init board & add option to choose mode later
    vector<int> validateMove(string move); //check if move is valid
    void applyMove(vector<int> move); //apply move if valid
    int winner(); //who won the game
    void displayBoard(); //display 9x9 board with proper A-I & 1-9 labels
    void playHuman(); //human vs human mode
    void playComp(); //human vs cpu mode
    void botMatch(); //cpu vs cpu mode
    void menu(); //for choosing one of the 3 modes
};

Game::Game(){
    activePlayer = 0; //assume player 1 starts
    board.resize(9, vector<int>(9,-1)); //init to -1
}

void Game::displayBoard(){
    for(int i = 0; i <=board.size(); i++){
        for(int j = 0; j <=board.size(); j++){
            if(j == 0)
                if(i != 0)
                    cout<<char(i + 64)<<"\t";
                else
                    cout<<"\t";
            else if(i == 0)
                cout<<j<<"\t";
            else{
                if(board[i-1][j-1] == 0)
                    cout<<"X"<<"\t";
                else if(board[i-1][j-1] == 1)
                    cout<<"O"<<"\t";
                else
                    cout<<"_"<<"\t";
            }
        }
        cout<<endl<<endl;
    }
}

vector<int> Game::validateMove(string move){
    //invalid input
    if(move.size() != 2)
        return {};
    else if(move[0] < 'A' || move[0] > 'I')
        return {};
    else if(move[1] < '1' || move[1] > '9')
        return {};

    //convert to int coordinates
    int rowPos = move[0] - 65;
    int colPos = move[1] - 49;

    //validate
    if(board[rowPos][colPos] != -1)
        return {};
    else
        return {rowPos, colPos};
}

void Game::applyMove(vector<int> move){
    board[move[0]][move[1]] = activePlayer;
    activePlayer = !activePlayer;
}

int Game::winner(){
    //check board for pairs of 3
    for(int i = 0; i  < board.size(); i++){
        for(int j = 0; j < board.size(); j++){
            if(board[i][j] != -1){
                //vertical
                
            }
        }
    }
    return -1;
}

void Game::playHuman(){
    string move;
    displayBoard();
    while(1){
        cout<<"Player "<<activePlayer + 1<<"'s Turn : "<<endl;
        cin>>move;
        vector<int> m = validateMove(move);
        if(!m.empty())
            applyMove(m);
        else
            cout<<"Invalid Move!!!"<<endl;

        if(winner() != -1){
            cout<<"Player "<<activePlayer + 1<<" Won!!!"<<endl;
            break;
        }

        displayBoard();
    }
}

class Bot{

};

int main(){
    Game g;
    vector<int> v = g.validateMove("A1");
    g.applyMove(v);
    g.displayBoard();
    return 0;
}