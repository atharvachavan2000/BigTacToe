//Tic-Tac-Toe on a 9x9 Board
//author : Rohan B.

#include <iostream>
#include <vector>
#include <chrono>
using namespace std;

class Bot{
    vector<vector<int>> botBoard;
    int botActivePlayer;
public:
    void setBoard(vector<vector<int>> b, int a);
    int evaluate();
    int alphaBeta(int depth, bool isMax, int alpha, int beta);
    string findMove();
};

void Bot::setBoard(vector<vector<int>> b, int a){
    botBoard = b;
    botActivePlayer = a;
}

int Bot::evaluate(){
    return int(rand());
}

int Bot::alphaBeta(int depth, bool isMax, int alpha, int beta){
    int value = evaluate();
    if(value == 1000 || value == -1000 || depth == 5) return value;

    if(isMax){
        int best = -1000;
        for(int i = 0; i  < botBoard.size(); i++){
            for(int j = 0; j < botBoard.size(); j++){
                if(botBoard[i][j] == -1){
                    //make the move
                    botBoard[i][j] == botActivePlayer;
                    //find max value
                    best = max(best, alphaBeta(depth+1, !isMax, alpha, beta));
                    alpha = max(alpha, best);
                    //undo move
                    botBoard[i][j] == -1;
                    //alpha-beta pruning
                    if(beta <= alpha)
                        goto lab1; //break out of all loops
                }
            }
        }
        lab1:return best;
    }

    else{
        int best = 1000;
        for(int i = 0; i  < botBoard.size(); i++){
            for(int j = 0; j < botBoard.size(); j++){
                if(botBoard[i][j] == -1){
                    //make the move
                    botBoard[i][j] == botActivePlayer;
                    //find max value
                    best = min(best, alphaBeta(depth+1, !isMax, alpha, beta));
                    beta = min(beta, best);
                    //undo move
                    botBoard[i][j] == -1;
                    //alpha-beta pruning
                    if(beta <= alpha)
                        goto lab2; //break out of all loops
                }
            }
        }
        lab2:return best;
    }
}

string Bot::findMove(){
    int bestVal = -1000;
    string bestMove;
    for(int i = 0; i  < botBoard.size(); i++){
        for(int j = 0; j < botBoard.size(); j++){
            if(botBoard[i][j] == -1){
                //make the move
                botBoard[i][j] == botActivePlayer;
                //find max value
                int moveVal = alphaBeta(0, false, -1000, 1000);
                //undo move
                botBoard[i][j] == -1;
                //update best move
                if(moveVal > bestVal){
                    bestVal = moveVal;
                    bestMove += char(i + 65);
                    bestMove += char(j + 49);
                }                   
            }
        }
    }
    cout<<bestMove<<endl;
    return bestMove;
}

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

void Game::playComp(){
    Bot b;
    string move;
    displayBoard();
    while(1){
        if(activePlayer == 1){
            b.setBoard(board, activePlayer);
            cout<<"Bot's Move : "<<endl;

            auto start = chrono::high_resolution_clock::now();
            move = b.findMove();
            auto stop = chrono::high_resolution_clock::now();
		    auto duration = chrono::duration_cast<chrono::milliseconds>(stop - start);
		    cout << "Time taken: " << duration.count() << "ms" << endl;

            vector<int> m2 = validateMove(move);
            applyMove(m2);
        }else{

        cout<<"Player "<<activePlayer + 1<<"'s Turn : "<<endl;
        cin>>move;
        vector<int> m = validateMove(move);
        if(!m.empty())
            applyMove(m);
        else
            cout<<"Invalid Move!!!"<<endl;

        }

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

void Game::botMatch(){
    Bot b1, b2;
    string move;
    displayBoard();
    while(1){
        b1.setBoard(board, activePlayer);
        cout<<"Bot 1's Move : "<<endl;

        auto start = chrono::high_resolution_clock::now();
        move = b1.findMove();
        auto stop = chrono::high_resolution_clock::now();
		auto duration = chrono::duration_cast<chrono::milliseconds>(stop - start);
		cout << "Time taken: " << duration.count() << "ms" << endl;

        vector<int> m2 = validateMove(move);
        applyMove(m2);

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
        
        b2.setBoard(board, activePlayer);
        cout<<"Bot 2's Move : "<<endl;

        start = chrono::high_resolution_clock::now();
        move = b2.findMove();
        stop = chrono::high_resolution_clock::now();
		duration = chrono::duration_cast<chrono::milliseconds>(stop - start);
		cout << "Time taken: " << duration.count() << "ms" << endl;

        vector<int> m1 = validateMove(move);
        applyMove(m1);

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

int main(){
    Game g;
    g.botMatch();
    return 0;
}