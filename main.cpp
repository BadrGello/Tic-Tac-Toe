#include <iostream>
#include <cmath>
#define red "\x1B[31m"
#define blue "\x1B[34m"
#define normal "\033[0m"

void initializeGrid(char *grid, int size);
int drawGrid(char *grid);
int drawGridAdvance(char *grid, int size);
int checkWinning(char *grid, int size);
int checkTie(int turns, int size);
int playerMove(char *grid, int position, int pTurn, int mode);
int computerMove(char *grid, int size, int pTurn, int mode);
int mainMenu();
int sizeMenu();
void displayWinner(char winner, int botMode);

int menu;
int botMode=0;
int size = 3;
int turns = 0;
int pTurn=1;
char winner = NULL;


int main(){
    
    char grid[size*size];
    while (true){

        mainMenu();
        system("cls");

        std::cout << "NOW ENTERING GAME.";
        _sleep(700);
        system("cls");
        std::cout << "NOW ENTERING GAME..";
        _sleep(700);
        system("cls");
        std::cout << "NOW ENTERING GAME...";
        _sleep(700);
        system("cls");

        initializeGrid(grid, size);

        pTurn=1;
        while (turns!=size*size){
            system("cls");
            std::cout <<"Player Turn: " << pTurn << "\n";
    
            drawGridAdvance(grid, size);
            playerMove(grid, size, pTurn, botMode);
            computerMove(grid, size, pTurn, botMode);

            //if (turns==size*size-2) _sleep(2000);
            
            if (checkWinning(grid, size)) {
                displayWinner(winner, botMode);
            }
            if (checkTie(turns, size)){
                system("cls");
                std::cout << "It's a Tie!\n";
                _sleep(10000);
                exit(0);
            }
            turns++;
            pTurn=turns%2+1;
              
        }
        
    return 0;
    }
    
}

void initializeGrid(char *grid, int size){

    //fill(grid, grid + size, ' ');
    for (int i=0; i<size*size; i++){
        grid[i] = ' ';
    }

}
int drawGrid(char *grid){

    //The normal 3*3
    std::cout << "1    |2    |3    \n";
    std::cout << "  " << grid[0] << "  |  " << grid[1] << "  |  " << grid[2] << "  \n";
    std::cout << "_____|_____|_____\n";
    std::cout << "4    |5    |6    \n";
    std::cout << "  " << grid[3] << "  |  " << grid[4] << "  |  " << grid[5] << "  \n";
    std::cout << "_____|_____|_____\n";
    std::cout << "7    |8    |9    \n";
    std::cout << "  " << grid[6] << "  |  " << grid[7] << "  |  " << grid[8] << "  \n";
    std::cout << "     |     |     \n";

    return 0;
}
int drawGridAdvance(char *grid, int size){

    //Min size = 3 and max...
    int position=1;
    int k = 0;
    for (int i=0; i<size; i++){
        for (int j=0; j<size; j++){
            std::string positionIndentation = "";
            for (int k=1; k<=5-(int)(log10(position)+1); k++){ //basically, if the position variable is 1 digit, it'll be followed by 4 spaces, 2 digits, 3 spaces and so on, so the loop counts (5 - the number of digits)
                positionIndentation += " ";
            }
            
            if ((j+1)!=size) {
                positionIndentation += "|";
            }
            else {
                positionIndentation += "\n";
            }

            std::cout << position << positionIndentation;
            position++;
        }

        for (int j=0; j<size; j++){
            if ((j+1)!=size) {
                if (grid[k]=='X')  std::cout << "  " << red << grid[k] << normal <<"  |";
                else if (grid[k]=='O') std::cout << "  " << blue << grid[k] << normal <<"  |";
                else std::cout << "  " << grid[k] << "  |";
            }
            else {
                if (grid[k]=='X')  std::cout << "  " << red << grid[k] << normal <<"  \n";
                else if (grid[k]=='O') std::cout << "  " << blue << grid[k] << normal <<"  \n";
                else std::cout << "  " << grid[k] <<"  \n";
            }
            k++;
        }
        
        if ((i+1)!=size){
            for (int j=0; j<size; j++){
            if ((j+1)!=size) std::cout << "_____|";
            else std::cout << "_____\n";
            }
        }
        else {
            for (int j=0; j<size; j++){
            if ((j+1)!=size) std::cout << "     |";
            else std::cout << "     \n";
            }
        }
        
    }
    return 0;

}
int checkWinning(char *grid, int size){

    int status = 0; //false by default
    for (int i=0; i<size*size; i+=size){//move row by row
        for(int j=i; j<i+size-1 ;j++){
            if(grid[j]==grid[j+1] && grid[j]!=' '){
                status = 1;
                winner = grid[j];
            }
            else {
                status = 0;
                break;
            }
        }  
        if (status) return status;
    }

    for (int i=0; i<size; i++){
        for (int j=i; j<size*size-size ;j+=size){//move col by col
            if(grid[j]==grid[j+size] && grid[j]!=' '){
                status = 1;
                winner = grid[j];  
            }
            else {
                status = 0;
                break;
            }
        }
        if (status) return status;
    }

    for (int i=0; i<size*size-size; i+=size+1){//check first diagonal
            if(grid[i]==grid[i+size+1] && grid[i]!=' '){
                status = 1;
                winner = grid[i];
            }
            else {
                status = 0;
                break;
            }
    }
    if (status) return status;

    for (int i=size-1; i<size*size-size; i+=size-1){//check second diagonal
            if(grid[i]==grid[i+size-1] && grid[i]!=' '){
                status = 1;
                winner = grid[i];
            }
            else {
                status = 0;
                break;
            }
    }

    return status;
}
int checkTie(int turns, int size){
    if (turns == size*size-1) return 1;
    return 0;
}
int playerMove(char *grid, int size, int pTurn, int mode){
    bool valid = false;
    int position;
    if (mode!=0 && pTurn==2) return 0;
    do {
        std::cin >> position;
        position--;
        if (position >= 0 && position < size*size && grid[position]==' ') {
            if (pTurn == 1) grid[position] = 'X'; //if pTurn non zero then it's P2 turn
            else if (pTurn == 2 && botMode==0) grid[position] = 'O';
            valid = true;
        }
        //else if () //special negative values for menu

        else if (!valid) std::cout << "Already occupied\n";

    }while(!valid);

    return 0;

}
int computerMove(char *grid, int size, int pTurn, int mode){
    
    if (mode == 0 || pTurn == 1) return 0;

    if (mode == 1){ //random
        int availabePositions[size*size];
        int k=0;
        int avaibleSize=0;
        for (int i=0; i<size*size; i++){
            if (grid[i]==' ') {
                availabePositions[k]=i;
                k++;
                avaibleSize++;
            }
        }

        srand(time(NULL));
        int randomPosition = rand()%avaibleSize ;

        grid[availabePositions[randomPosition]] = 'O';
        return 0;
    }

    else if (mode == 2){ //more thoughtful

        exit(0);
    }
    else if (mode == 3){ //more thoughtful
        exit(0);
    }
}
int mainMenu(){

    bool valid = true;
    std :: string input;
    
    do{
        system("cls");
        std::cout << "1) Start Game\n2) Exit\n";
        std::getline (std::cin, input);

        for (auto& x : input) { //turn the input to all lower
        x = tolower(x); 
        }

        if (input == "1" || input == "1)" || input == "start" || input == "start game")
        {
            system("cls");
            valid = true;
            do{

                system("cls");
                std::cout << "1) 2 Players\n2) Player vs Computer\n3) Return\n";
                std::getline (std::cin, input);
                valid = true;
                int sM;

                for (auto& x : input) { //turn the input to all lower
                x = tolower(x); 

                }

                if (input == "1" || input == "1)")
                {
                    botMode = 0;
                    valid = true;
                    sM = sizeMenu();
                    if (sM==1) valid = false;
                }
                else if (input == "2" || input == "2)")
                {
                    do{

                        system("cls");
                        std::cout << "Computer Mode:\n1) Easy (Random)\n2) Medium\n3) Hard\n4) Return\n";
                        std::getline (std::cin, input);
                        valid = true;

                        if (input == "1" || input == "1)" || input == "easy" || input == "e"){
                            botMode = 1;
                            sM = sizeMenu();
                            if (sM==1) valid = false;
                        }
                        else if (input == "2" || input == "2)" || input == "medium" || input == "m"){
                            botMode = 2;
                            sM = sizeMenu();
                            if (sM==1) valid = false;
                        }
                        else if (input == "3" || input == "3)" || input == "hard" || input == "h"){
                            botMode = 3;
                            sM = sizeMenu();
                            if (sM==1) valid = false;
                        }
                        else if (input == "4" || input == "4)" || input == "return" || input == "r"){
                            valid = false;
                            break;
                        }
                        else {
                            valid = false;
                            std::cout << "Invalid Input!\n";
                        } 

                    }while(!valid);
                    

                }
                else if (input == "3" || input == "3)" || input == "return" || input == "r")
                {
                    break;
                }
                
                else {
                    valid = false;
                    std::cout << "Invalid Input!\n";
                }

            }while(!valid);
            //return 1;
        }

        /*if (input == "2" || input == "2)" || input == "options")
        {
            system("cls");
            return 2;
        }*/

        else if (input == "2" || input == "2)" || input == "exit" || input == "quit")
        {
            system("cls");
            exit(0);
        }
        
        else {
            valid = false;
            system("cls");
        }

    }while(!valid);

    return 0;
}
int sizeMenu(){

        bool valid = true;
        std :: string input;
        int intInput;
        system("cls");
        do{
            
            std :: cout << "Enter gameboard size \nExample: enter 3 for game size 3*3\n1) Return\n";
            std :: getline (std::cin, input);
            valid = true;

            try {  
                int num = std::stoi(input);  
            } catch (std::invalid_argument&e) {  
                system("cls");
                std::cout<< "DON'T ENTER CHARACTERS\n"; 
                valid = false;
                continue; 
            }  

            intInput = stoi(input);
            
            if (input == "1")
            {
                system("cls");
                return 1;
            }
            else if ( intInput > 2 && intInput < 100) size = intInput;
            
            else {
                valid = false;
                system("cls");
                //std::cout << "Invalid Input!\n";
            }

        }while(!valid);
    
    return 0;


    
}
void displayWinner(char winner, int botMode){
    system("cls");
    if (winner == 'X' && botMode == 0) std::cout << "Player 1 Won! " << red << "(X)\n" << normal;
    else if (winner == 'O' && botMode == 0) std::cout << "Player 2 Won! " << blue <<"(O)\n" << normal;
    else if (winner == 'X' && botMode != 0) std::cout << "You Won :)\n";
    else if (winner == 'O' && botMode != 0) std::cout << "You Lost :(\n";
    _sleep(10000);
    exit(0);
}
