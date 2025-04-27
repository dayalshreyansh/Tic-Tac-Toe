#include <iostream>
#include <cctype>
#include <string>
using namespace std;
class Player{
private:
    char symbol;
    string name;
public:
    //constructor
    Player(char sym='X',string n="Player X"):symbol(sym),name(n){}
    //getter method
    char getSymbol() const {return symbol;}
    string getName() const {return name;}
};
class Board
{
private:
    char grid[3][3]; // 3x3 grid for tic-tac-toe
    int filledCells; // number of filled cells
public:
    Board():filledCells(0){
        for(int i=0;i<3;i++){
            for(int j=0;j<3;j++){
                grid[i][j]=' ';
            }
        }
    }
    void drawboard() const{
        cout<<"--------------"<<endl;
        for(int i=0;i<3;i++){
            cout<<"| ";
            for(int j=0;j<3;j++){
                if (grid[i][j] == 'X') cout << "\033[1;31m" << grid[i][j] << "\033[0m | "; // Red
                else if (grid[i][j] == 'O') cout << "\033[1;34m" << grid[i][j] << "\033[0m | "; // Blue
                else cout << grid[i][j] << " | ";
            }
            cout<<endl<<"--------------"<<endl;
        }
    }
    //fuction to check legal move
    bool isValidMove(int row,int col)const{
        return(row<3 && col<3 && col>=0 && row>=0 && grid[row][col]==' ');
    }
    //make a move
    void makeMove(int row,int col,char symbol){
        if(isValidMove(row,col)){
            grid[row][col]=symbol;
            filledCells+=1;
        }
    }
    //Undo Move
    void undoMove(int row, int col) {
        if (row >= 0 && row < 3 && col >= 0 && col < 3 && grid[row][col] != ' ') {
            grid[row][col] = ' ';
            filledCells--;
        }
    }
    //Check win for a symbol
    bool checkWin(char symbol){
        //Check rows
        for(int i=0;i<3;i++){
            if(grid[i][0]==symbol && grid[i][1]==symbol && grid[i][2]==symbol){
                return true;
            }
        }
        //check column
        for(int i=0;i<3;i++){
            if(grid[0][i]==symbol && grid[1][i]==symbol && grid[2][i]==symbol){
                return true;
            }
        }
        //CHeck diagonals
        if(grid[0][0]==symbol && grid[1][1]==symbol && grid[2][2]==symbol){
            return true;
        }
        if(grid[0][2]==symbol && grid[1][1]==symbol && grid[2][0]==symbol){
            return true;
        }
        return false;
    }
    //method to check is Full
    bool isFull()const{
        if(filledCells==9){
            return true;
        }
        return false;
    }
    //method to get no of full 
    int getFilledCells()const{
        return filledCells;
    }
    ~Board(){};
};

class TicTacToe{
private:
    Board board;
    Player players[2];
    int currentPlayerIndex;
    bool vsComputer;
public:
    TicTacToe():currentPlayerIndex(0){
        players[0]=Player('X',"Player X");
        players[1]=Player('O',"Player O");
        cout<<"Select Mode:\n1. Player vs Player\n2. Player vs Computer\nEnter choice: ";
        int choice;
        cin>>choice;
        vsComputer=(choice==2);

    }
    //method to evaluate the board
    int evaluateBoard(){
        if(board.checkWin(players[1].getSymbol())){
            return +10;
        }else if(board.checkWin(players[0].getSymbol())){
            return -10;
        }
        return 0;
    }
    //Minimax logic
    int minimax(Board& currentBoard,int depth,bool isMax){
        int score=evaluateBoard();

        if(score==10){return score-depth;}
        if(score==-10){return score+depth;}
        if(currentBoard.isFull()) return 0;

        if(isMax){
            int best=-1000;
            for(int i=0;i<3;i++){
                for(int j=0;j<3;j++){
                    if(currentBoard.isValidMove(i,j)){
                    currentBoard.makeMove(i,j,players[1].getSymbol());
                    best=max(best,minimax(currentBoard,depth+1,!isMax));
                    currentBoard.undoMove(i,j);
                }}
            }
            return best;
        }else{
            int best=1000;
            for(int i=0;i<3;i++){
                for(int j=0;j<3;j++){
                    if(currentBoard.isValidMove(i,j)){
                        currentBoard.makeMove(i,j,players[0].getSymbol());
                        best=min(best,minimax(currentBoard,depth+1,!isMax));
                        currentBoard.undoMove(i,j);
                    }
                }
            }
            return best;
        }
    }
    //fing bestMove
    pair<int,int> findBestMove(){
        int bestVal = -1000;
        pair<int,int> bestMove={-1,-1};

        for(int i=0;i<3;i++){
            for(int j=0;j<3;j++){
                if(board.isValidMove(i,j)){
                    board.makeMove(i,j,players[1].getSymbol());
                    int moveVal=minimax(board,0,false);
                    board.undoMove(i,j);

                    if(moveVal>bestVal){
                        bestMove={i,j};
                        bestVal=moveVal;
                    }
                }
            }
            
        }
        return bestMove;
    }
    //Method to Get current player;
    Player& getCurrentPlayer(){
        return players[currentPlayerIndex];
    }
    //Method to switch turns
    void switchTurn(){
        currentPlayerIndex=(currentPlayerIndex+1)%2;
    }
    //Method to play;
    void play(){
        int row,col;
        cout<<"Welcomr to Tic-Tac-Toe!!"<<endl;
        while(!board.isFull()){
            board.drawboard();

            Player& currentPlayer=getCurrentPlayer();
            if(vsComputer && currentPlayerIndex==1){
                cout<<"Computer is thinking..."<<endl;
                pair<int,int> bestMove = findBestMove();
                row = bestMove.first;
                col = bestMove.second;
                cout<<"Computer chooses: "<<row+1<<" "<<col+1<<endl;
            }else{
                while(true){
                    cout<<currentPlayer.getName()<<"("<< currentPlayer.getSymbol()<<"),enter row(1-3) and col(1-3): ";
                    cin>>row>>col;
                    row--;
                    col--;
                    if(board.isValidMove(row,col)){
                        break;
                    }else{
                        cout<<"Invalid Move.Try again."<<endl;
                    }
                }
            }
            board.makeMove(row,col,currentPlayer.getSymbol());

            if(board.checkWin(currentPlayer.getSymbol())){
                board.drawboard();
                cout<< currentPlayer.getName()<<" Wins!!"<<endl;
                return;
            }
            switchTurn();
        }
        board.drawboard();
        cout << "It's a draw!" << endl;
    }
};

int main(){
    TicTacToe game;
    game.play();
    return 0;
}
