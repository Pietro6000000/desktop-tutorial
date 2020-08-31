#include <stdio.h>
#include <string.h> // strncmp
#include <stdbool.h> // bool
#include <ctype.h> // isdigit
 
#define ROW_COUNT 3
#define COL_COUNT 3
#define CELL_COUNT 3*3
#define HLINE "-------------"
#define X_SIDE 1
#define O_SIDE 0
 
const char default_board[ROW_COUNT][COL_COUNT] = {
    "123",
    "456",
    "789"
};
 
// Siccome ci sono solo due possibili caratteri, X e O, li rappresento con bool. O = false e X = true
// sides[] viene usato per ricevere il carattere del giocatore, perche fin dei conti, bool e un int che puo essere 0 o 1.
const char sides[] = {'O', 'X'};
 
typedef enum { X_Won, O_Won, Draw, Ongoing } Status_t;
 
 
void visualize_board(const char board[ROW_COUNT][COL_COUNT])
{
    for (int i = 0; i < ROW_COUNT; i++)
    {
        printf("|");
 
        for (int j = 0; j < COL_COUNT; j++)
            printf(" %c |", board[i][j]);
 
        if (i != ROW_COUNT-1)
        {
            printf("\n");
            printf("%s\n", HLINE);
        }
    }
}
 
void update_board(const char board[ROW_COUNT][COL_COUNT])
{
    printf("\n\n\n\n\n");
    visualize_board(board);
}
 
 
// Controlla lo stato della partita
Status_t check_status(const char board[ROW_COUNT][COL_COUNT])
{
    // controlla le righe per vedere se uno ha vinto. viene usato strncmp, vedere se la riga e uguale a XXX o OOO
    for (int i = 0; i < ROW_COUNT; i++)
    {
        if (strncmp(board[i], "XXX", 3) == 0)
            return X_Won;
        else if (strncmp(board[i], "OOO", 3) == 0)
            return O_Won;
    }
 
    // controlla le colonne. non possiamo usare strncmp qui pero
    for (int i = 0; i < COL_COUNT; i++)
    {
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i])
        {
            if (board[0][i] == sides[X_SIDE])
                return X_Won;
            else if (board[0][i] == sides[O_SIDE])
                return O_Won;
        }
    }
 
    // controlla le diagonali
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2])
    {
        if (board[0][0] == sides[X_SIDE])
            return X_Won;
        else if (board[0][0] == sides[O_SIDE])
            return O_Won;
    }
 
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0])
    {
        if (board[0][2] == sides[X_SIDE])
            return X_Won;
        else if (board[0][2] == sides[O_SIDE])
            return O_Won;
    }
 
    // se a questo punto tutte le celle non sono riempite, significa che la partita non e finita
    for (int i = 0; i < ROW_COUNT; i++)
        for (int j = 0; j < COL_COUNT; j++)
            if (isdigit(board[i][j]))
                return Ongoing;
 
    // a questo punto l'unica possibilita e che la partita e sullo stallo.
    return Draw;
}
 
Status_t game()
{
    // il lato del giocatore. per cambiarlo fai semplicemente !side, perche side e un bool
    bool side = X_SIDE;
    char board[ROW_COUNT][COL_COUNT] = {};
 
    // inizializza il campo
    for (int i = 0; i < ROW_COUNT; i++)
        for (int j = 0; j < COL_COUNT; j++)
            board[i][j] = default_board[i][j];
 
    // il numero dalla cella. in altre parole, e la distanza di una cella dalla prima cella.
    // il numero della cella e uguale a ROW_COUNT * x + y
    int cell_num = 0;
 
    visualize_board(board);
    while (true)
    {
        printf("\n\n%c: ", sides[side]);
        scanf("%d", &cell_num);
 
        // otteniamo le coordinate della cella. siccome ROW_COUNT = 3, cell_num % 3 e uguale a y (il resto)
        // x otteniamo da un'equazione lineare
        int y = (cell_num-1) % 3;
        int x = ((cell_num-1) - y)/3;
 
        // se l'input e valido
        if ((cell_num >= 1 && cell_num <= 9) && isdigit(board[x][y]))
        {
            board[x][y] = sides[side];
            update_board(board);
 
            Status_t status = check_status(board);
            if (status != Ongoing)
                return status;
 
            side = !side;
        }
        else
        {
            printf("That cell is occupied or does not exist, try again!");
        }
    }
 
    return Draw;
}
 
int main()
{
    Status_t result = game();
    printf("\n");
 
    switch(result)
    {
    case X_Won: {
        printf("X won");
        break;
    }
 
    case O_Won: {
        printf("O won");
        break;
    }
 
    default: printf("Draw");
    }
 
    return 0;
}