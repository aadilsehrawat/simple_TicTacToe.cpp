#include<iostream>
using namespace std;

void printAvailable(bool available[9]){
    cout<<"\n\nAvailable positions: ";
    // Printing Avaialable Move Positions
    for (int i=1; i<10; i++){
        if (available[i-1]==true)
        cout<<i<<" ";
    }
}

void printBoards(char matrix[3][3], bool available[9]){
    cout<<"\nAvailable\tCurrent\n";
    cout<<"Positions:\tBoard:\n";
    for (int i=0; i<3; i++){
        // Printing Avaialable Moves
        for (int j=0; j<3; j++){
            if (available[(i*3)+j])
            cout<<(i*3)+j+1<<" ";
            else
            cout<<"# ";
        }
        
        cout<<"\t\t";
        // Printing Current Board Status
        for (int j=0; j<3; j++){
            if (matrix[i][j]==0)
            cout<<"_ ";
            else
            cout<<matrix[i][j]<<" ";
        }
    cout<<endl;
    }
}

int getNextMove(bool available[9], char move){
    int next;
    while(true){
        printAvailable(available);
        cout<<"\nPlease select a position out of available positions ("<<move<<"'s Turn): ";
        cin>>next;
        // Check if the move is safe or not, and set move to unsafe once move is taken
        if (next>=1 && next<=9 && available[next-1]==true){
            available[next-1]=false;
            break;
        }
        else if (next>=1 && next<=9)
        cout<<"\nPosition not available.";
        
        else
        cout<<"\nInvalid Choice.";
    }
    return next;
}

void updateBoard(char matrix[3][3], int nextMove, char move){
    // Update the board with O or X for the move chosen
    matrix[(nextMove-1)/3][(nextMove-1)%3]=move;
}

char checkResult(char matrix[3][3]){
    // Checking status for all rows and columns
    for (int i=0; i<3; i++){
        // Checking status rows-wise
        if (matrix[i][0]==matrix[i][1] && matrix[i][0]==matrix[i][2])
            return matrix[i][0];
        // Checking status column-wise
        if (matrix[0][i]==matrix[1][i] && matrix[0][i]==matrix[2][i])
            return matrix[0][i];
    }
    // Checking status for right diagonal
    if (matrix[1][1]==matrix[0][0] && matrix[1][1]==matrix[2][2])
        return matrix[1][1];
    // Checking status for left diagonal
    if (matrix[1][1]==matrix[0][2] && matrix[1][1]==matrix[2][0])
        return matrix[1][1];
    // Returning a random character (! in this case) if no winning case found
    return '!';
}

int main(){
    cout<<"\nTIC - TAC - TOE";
    cout<<"\n2 Player Mode\n\n";
    int nextMove;
    // Initializing an available array with all moves marked as safe
    bool available[9]={1,1,1,1,1,1,1,1,1};
    // Initializing a board matrix 2D-array with all moves marked as 0 which will later be marked as O or X
    char matrix[3][3]={0,0,0,0,0,0,0,0,0}, result;

    printBoards(matrix, available);
    for (int i=1; i<10; i++){
        // Starting from move 1 to move 9. All odd moves are for Player X and all Even moves are for Player O
        if (i%2!=0){
            nextMove = getNextMove(available, 'X');
            updateBoard(matrix, nextMove, 'X');
        }
        else{
            nextMove = getNextMove(available, 'O');
            updateBoard(matrix, nextMove, 'O');
        }

        printBoards(matrix, available);
        // After 4 moves (i.e. on 5th move) we can start to check if we have a winner after each move
        if (i>4){
            result = checkResult(matrix);
            // Check if we have a winner and if yes then break out of the loop after prining the winning player
            if (result=='X'||result=='O'){
                cout<<"\n\n====== "<<result<<" WON !"<<" ======\n\n";
                break;
            }
        }
    }
    // If at the end of 9th iteration we still have not got X or O as a result, the game is a draw
    if (result=='!')
    cout<<"\n\n====== "<<" GAME DRAW !"<<" ======\n\n";
    
    cout<<"\n";
}