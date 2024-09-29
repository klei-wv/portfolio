#include <stdio.h>

#define ROWS 6
#define COLS 7
#define NONE -1
#define RED 1
#define YELLOW 2

int board[ROWS][COLS];
int winner = 0;
int player = RED;

void init_board()  // initializes the board to be empty
{
    int i, j;
    for (i = 0; i < ROWS; i++)
    {
        for (j = 0; j < COLS; j++)
        {
            board[i][j] = NONE;
        }
    }
}

void print_board()  // Prints the board
{
    int i, j;
    printf("\n\n\n\n");
    for (i = 0; i < ROWS; i++)
    {
        printf("\t\t\t\t\t\t");
        for (j = 0; j < COLS; j++)
        {
            if (board[i][j] == RED)
            {
                printf("X ");
            } else if (board[i][j] == YELLOW)
            {
                printf("O ");
            } else {
                printf(". ");
            }
        }
        printf("\n");
    }
    printf("\t\t\t\t\t\t1 2 3 4 5 6 7\n");
}

int drop_piece(int col) // Function for the user to drop a piece
{
    int row;
    for (row = ROWS - 1; row >= 0; row--)
        {
        if (board[row][col] == NONE) // Checks if the selected part of the board is empty
        {
            board[row][col] = player;
            return row;
        }
    }
    return -1; // Restricts the user from entering an invalid move
}

    void play_game()
    {
    system("cls");
    int drop_piece(int col, int current_player) // Function for the user to drop a piece
    {
    int row;
    for (row = ROWS - 1; row >= 0; row--) // Lets the user start from the bottom row
        {
        if (board[row][col] == NONE) // Checks if the board is empty
        {
            board[row][col] = current_player;
            break;
        }
    }
    if(row < 0)  // Restricts the user from making moves if the board is full
    return -1;
    return row;
}

    int winner = NONE;
    int current_player = RED;
    int turns_taken = 0;
    init_board();
    while (winner == NONE && turns_taken < ROWS * COLS) // Loop for the users taking turns
        {
        print_board();
        int col;
        printf("\n\n\n\t\t\t\tPlayer %d's turn. Enter a column (1-7): ", current_player);
        scanf("%d", &col);
        system("cls"); // Clears the screen every time a user make a move

        if (col < 1 || col > COLS) // Check if the user's input is appropriate (1-7)
        {
            printf("\n\t\t\t\tInvalid move. Please enter a valid column.\n");
            continue;
        }

        if(board[0][col-1] != NONE) // Check if the top row of the selected column is not full
        {
            printf("\n\t\t\t\t\tInvalid move. Column is full.\n");
            continue;
        }
        int row = drop_piece(col - 1, current_player);
        turns_taken++;
        winner = check_winner(row, col - 1);
        if (winner != NONE) // Declares that there is a winner
        {
            printf("\n\n\t\t\t\t\tPlayer %d wins!\n", winner);
            printf("\n\n\t\t\t\t\tYou can view the list of winners in winners.txt.\n", winner);
            reset_game();
        }
        else if(turns_taken == ROWS * COLS) // Declares that there is no winner (draw)
            printf("\nIt's a draw!\n");
        current_player = (current_player == RED) ? YELLOW : RED;
    }
    return 0;
}


int check_winner(int last_row, int last_col) // Function to check if there is a winner (either horizontal, vertical, or diagonal)
{
    int i, count;

    // check horizontal
    count = 0;
    for (i = last_col; i >= 0; i--)
        {
        if (board[last_row][i] == board[last_row][last_col])
        {
            count++;
        } else
        {
            break;
        }
    }
    for (i = last_col + 1; i < COLS; i++)
    {
        if (board[last_row][i] == board[last_row][last_col])
        {
            count++;
        } else
        {
            break;
        }
    }

if (count >= 4)
{
    char winner = board[last_row][last_col];
        if (winner != NONE)
        {
            // file handling to write winner to text file
            FILE *fp;
            fp = fopen("winners.txt", "a");
            fprintf(fp, "Game winner: Player %d\n", winner); // Prints the winner on the specific game
            fclose(fp);
            return winner;
            reset_game();
        }
}

    // check vertical
    count = 1;
    for (i = last_row - 1; i >= 0; i--)
    {
        if (board[i][last_col] == board[last_row][last_col])
        {
            count++;
        } else
        {
            break;
        }
    }
    for (i = last_row + 1; i < ROWS; i++)
    {
        if (board[i][last_col] == board[last_row][last_col])
        {
            count++;
        } else
        {
            break;
        }
    }
if (count >= 4)
{
    char winner = board[last_row][last_col];
        if (winner != NONE)
        {
            // file handling to write winner to text file
            FILE *fp;
            fp = fopen("winners.txt", "a");
            fprintf(fp, "Game winner: Player %d\n", winner); // Prints the winner on the specific game
            fclose(fp);
            return winner;
            reset_game();
        }
}

    // check diagonal (top-right to bottom-left)
    count = 0;
    int j;
        for (i = last_row, j = last_col; i >= 0 && j < COLS; i--, j++)
            {
            if (board[i][j] == board[last_row][last_col])
            {
                count++;
                } else
                {
            break;
            }
        }
        for (i = last_row + 1, j = last_col - 1; i < ROWS && j >= 0; i++, j--)
        {
            if (board[i][j] == board[last_row][last_col])
            {
                count++;
                } else
                {
            break;
            }
        }
if (count >= 4)
{
    char winner = board[last_row][last_col];
        if (winner != NONE)
        {
            // file handling to write winner to text file
            FILE *fp;
            fp = fopen("winners.txt", "a");
            fprintf(fp, "Game winner: Player %d\n", winner); // Prints the winner on the specific game
            fclose(fp);
            return winner;
            reset_game();
        }
}
        return NONE;
        }

void reset_game()
{
    int again;
    {
        printf("\n\t\t\tDo you want to try again?, [Press Y if Yes and N if No to return to menu]: ");
        again = getch();

        if (again == 'n' || again == 'N')
            return;
        else if(again == 'y' || again == 'Y')
            init_board();
    }
}


int main()
{
    int choice;

    while(1)
    {
        system("cls");
        printf("\n\n\n");
        printf("\t\t\t\t\t=======================================\n");
        printf("\t\t\t\t\t||           Connect 4 Menu          ||\n");
        printf("\t\t\t\t\t||-----------------------------------||\n");
        printf("\t\t\t\t\t||                                   ||\n");
        printf("\t\t\t\t\t||             1. Play               ||\n");
        printf("\t\t\t\t\t||             2. Exit               ||\n");
        printf("\t\t\t\t\t||                                   ||\n");
        printf("\t\t\t\t\t=======================================\n");
        printf("\t\t\t\t\t\tEnter your choice: ");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1: init_board();
                    play_game();
                    break;

            case 2: return 0;

            default: printf("\nInvalid choice. Please enter 1-2 only.\n");
                    system("pause");
                    main();
                    break;
        }
    }
}





