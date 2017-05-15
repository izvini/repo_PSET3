/**
 * fifteen.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Implements Game of Fifteen (generalized to d x d).
 *
 * Usage: fifteen d
 *
 * whereby the board's dimensions are to be d x d,
 * where d must be in [DIM_MIN,DIM_MAX]
 *
 * Note that usleep is obsolete, but it offers more granularity than
 * sleep and is simpler to use than nanosleep; `man usleep` for more.
 */
 
#define _XOPEN_SOURCE 500

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// constants
#define DIM_MIN 3
#define DIM_MAX 9

// board
int board[DIM_MAX][DIM_MAX];

// dimensions
int dimen;

// prototypes
void clear(void);
void greet(void);
void init(void);
void draw(void);
bool move(int tile);
bool won(void);


int main(int argc, string argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        printf("Usage: fifteen d\n");
        return 1;
    }

    // ensure valid dimensions
    dimen = atoi(argv[1]);
    if (dimen < DIM_MIN || dimen > DIM_MAX)
    {
        printf("Board must be between %i x %i and %i x %i, inclusive.\n",
            DIM_MIN, DIM_MIN, DIM_MAX, DIM_MAX);
        return 2;
    }

    // open log
    FILE* file = fopen("log.txt", "w");
    if (file == NULL)
    {
        return 3;
    }

    // greet user with instructions
    greet();

    // initialize the board
    init();

    // accept moves until game is won
    while (true)
    {
        // clear the screen
        clear();

        // draw the current state of the board
        draw();

        // log the current state of the board (for testing)
        for (int i = 0; i < dimen; i++)
        {
            for (int j = 0; j < dimen; j++)
            {
                fprintf(file, "%i", board[i][j]);
                if (j < dimen - 1)
                {
                    fprintf(file, "|");
                }
            }
            fprintf(file, "\n");
        }
        fflush(file);

        // check for win
        if (won())
        {
            printf("ftw!\n");
            break;
        }

        // prompt for move
        printf("Tile to move: ");
        int tile = GetInt();
        
        // quit if user inputs 0 (for testing)
        if (tile == 0)
        {
            break;
        }

        // log move (for testing)
        fprintf(file, "%i\n", tile);
        fflush(file);

        // move if possible, else report illegality
        if (!move(tile))
        {
            printf("\nIllegal move.\n");
            usleep(500000);
        }

        // sleep thread for animation's sake
        usleep(500000);
    }
    
    // close log
    fclose(file);

    // success
    return 0;
}

/**
 * Clears screen using ANSI escape sequences.
 */
void clear(void)
{
    printf("\033[2J");
    printf("\033[%d;%dH", 0, 0);
}

/**
 * Greets player.
 */
void greet(void)
{
    clear();
    printf("WELCOME TO GAME OF FIFTEEN\n");
    usleep(2000000);
}

/**
 * Initializes the game's board with tiles numbered 1 through d*d - 1
 * (i.e., fills 2D array with values but does not actually print them).  
 */
void init(void)
{
    
    int var = dimen * dimen - 1 ;
    for(int i = 0; i < dimen ; i++)
    {
        for(int j = 0;j < dimen ;j++)
        {
            board[i][j] = var;
            var--;
        }
    }
    if ( dimen % 2 == 0)
    {
        int t = board[dimen - 1][dimen - 2];
        board[dimen - 1][dimen - 2] = board[dimen - 1][dimen - 3];
        board[dimen - 1][dimen - 3] = t;
    }
        
}

/**
 * Prints the board in its current state.
 */
void draw(void)
{
    // printing the values of the board elements
    for( int i = 0 ; i < dimen ; i++)
    {
        for( int j = 0; j < dimen ; j++)
        {
            printf(" %2d ",board[i][j]);
        }
        printf("\n");
    }
}

/**
 * If tile borders empty space, moves tile and returns true, else
 * returns false. 
 */
bool move(int tile)
{
   
    int x = 0, y = 0, atile = 0, btile = 0;
    for(int i = 0 ; i < dimen ; i++)
    {
        for(int j = 0; j < dimen; j++)
        {
            if (board[i][j] == 0)
            {
                x = i;
                y = j;
            }
            
        }
    }
    for(int i = 0 ; i < dimen ; i++)
    {
        for(int j = 0; j < dimen; j++)
        {
            if (board[i][j] == tile)
            {
                atile = i;
                btile = j;
            }
        }
    }
    // checking for the validity of tile's move
    if (btile == y && (atile == x - 1 || atile == x + 1 ))
    {
        int t = board[x][y];
        board[x][y] = board[atile][btile];
        board[atile][btile] = t;
        return true;
    }  
    else if(atile == x && (btile == y - 1 || btile == y + 1))
    {
        int t = board[x][y];
        board[x][y] = board[atile][btile];
        board[atile][btile] = t;
        return true;
    }
        
    else
    {
        return false;
    } 
}

/**
 * Returns true if game is won (i.e., board is in winning configuration), 
 * else false.
 */
bool won(void)
{
    int var1 = 1;
    int k = 0;
    for(int i = 0; i < dimen ;i++)
    {
        for(int j = 0; j < dimen ; j++)
        {
            if (board[i][j] == var1 )
            {
                k++;
            }
            var1++;
        }
        
        }

    
    if (k == dimen * dimen - 1)
    {
        return true;
    }
    else
    {
        return false;
    }
}

