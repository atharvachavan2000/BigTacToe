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
    //0->Player 1 wins, 1->Player 2 wins, 2->Draw
    int count = 0; //for checking draw condition
    //check board for pairs of 3
    for(int i = 0; i  < board.size(); i++){
        for(int j = 0; j < board.size(); j++){
            if(board[i][j] != -1){
                 count++;
                //vertical
                if(i >= 2 && i <= 6){
                    //NN
                    if(board[i][j] == board[i-1][j] && board[i][j] == board[i-2][j])
                        return board[i][j];
                    //SS
                    else if(board[i][j] == board[i+1][j] && board[i][j] == board[i+2][j])
                        return board[i][j];
                }

                //horizontal
                if(j >=2 && j <=6){
                    //EE
                    if(board[i][j] == board[i][j+1] && board[i][j] == board[i][j+2])
                        return board[i][j];
                    //WW
                    else if(board[i][j] == board[i][j-1] && board[i][j] == board[i][j-2])
                        return board[i][j];
                }

                //diagonal
                if(j >=2 && j <=6 && i >= 2 && i <= 6){
                    //NW
                    if(board[i][j] == board[i-1][j-1] && board[i][j] == board[i-2][j-2])
                        return board[i][j];
                    //SE
                    else if(board[i][j] == board[i+1][j+1] && board[i][j] == board[i+2][j+2])
                        return board[i][j];
                    //NE
                    else if(board[i][j] == board[i-1][j+1] && board[i][j] == board[i-2][j+2])
                        return board[i][j];
                    //SW
                    else if(board[i][j] == board[i+1][j-1] && board[i][j] == board[i+2][j-2])
                        return board[i][j];
                }
            }
        }
    }

    if(count == 81)
        return 2; //draw
    else
        return -1; //match ongoing
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
            if(winner() == 2){
                cout<<"Draw!!!"<<endl;
            }else{
                cout<<"Player "<<!activePlayer + 1<<" Won!!!"<<endl; //use ! as applyMove switches activePlayer
                displayBoard();
                break;
            }
        }

        displayBoard();
    }
}

class Bot{

};

int main(){
    Game g;
    g.playHuman();
    return 0;
}