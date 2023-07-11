#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define _RED "\033[1;31m"
#define _YELLOW "\033[1;33m"
#define _GREEN "\033[1;32m"
#define _BLUE "\033[1;34m"
#define _RESET "\033[0m"

#define MAX 10

char grid[MAX][MAX];
void start_grid(int);
void draw_grid(int);
void winner(int);
// void show_text_color(char *text, char *color);
void color(int);
// void redraw_grid();

// Global Variable
int quit = 0;

enum Color
{
    RED,
    YELLOW,
    GREEN,
    BLUE,
    RESET
};

int main(/*int argc, char *argv[]*/)
{
    int grid_size;
    srand(time(NULL));
    while (grid_size < 3 || grid_size >= 11)
    {
        color(RED);
        printf("WARNING: The min size is 3 and max size is 10\n");
        color(RESET);
        printf("Enter the size of the grid: ");
        color(GREEN);
        scanf("%d", &grid_size);
        color(RESET);
    };
    start_grid(grid_size);
    draw_grid(grid_size);
    while (!quit)
    {
        int x_coor, y_coor;
        printf("(type 0 to exit) Enter the X coor: ");
        scanf("%d", &x_coor);
        printf("(type 0 to exit) Enter the Y coor: ");
        scanf("%d", &y_coor);
        while (x_coor > grid_size || y_coor > grid_size)
        {
            printf("(type 0 to exit) Enter the X coor: ");
            scanf("%d", &x_coor);
            printf("(type 0 to exit) Enter the Y coor: ");
            scanf("%d", &y_coor);
        }
        if (x_coor == 0 || y_coor == 0)
        {
            color(RED);
            printf("Exit Sucessfully \n");
            color(RESET);
            quit = 1;
        }
        else
        {
            while ((grid[x_coor - 1][y_coor - 1]) == 'X' || (grid[x_coor - 1][y_coor - 1]) == 'O')
            {
                color(RED);
                printf("\nis occuped\n");
                color(RESET);
                draw_grid(grid_size);
                printf("(type 0 to exit) Enter the X coor: ");
                scanf("%d", &x_coor);
                printf("(type 0 to exit) Enter the Y coor: ");
                scanf("%d", &y_coor);
            }
            grid[x_coor - 1][y_coor - 1] = 'X';
            int x_coor_comp, y_coor_comp;
            x_coor_comp = rand() % grid_size;
            y_coor_comp = rand() % grid_size;

            while (grid[x_coor_comp][y_coor_comp] == 'X')
            {
                x_coor_comp = rand() % grid_size;
                y_coor_comp = rand() % grid_size;
            }

            //color(BLUE);
            grid[x_coor_comp][y_coor_comp] = 'O';
            draw_grid(grid_size);
            winner(grid_size);
            color(RESET);
        }
    }
    return 0;
}

void winner(int grid_size)
{
    for (int i = 0; i < grid_size; i++)
    {
        for (int j = 0; j < grid_size; j++)
        {
            if (grid[i][j] == 'X' && grid[i][j + 1] == 'X' && grid[i][j + 2] == 'X' || grid[i][j] == 'X' && grid[i + 1][j] == 'X' && grid[i + 2][j] == 'X' || grid[i][j] == 'X' && grid[i + 1][j + 1] == 'X' && grid[i + 2][j + 2] == 'X' || grid[i][j] == 'X' && grid[i + 1][j - 1] == 'X' && grid[i + 2][j - 2] == 'X')
            {
                color(GREEN);
                printf("\n ##-> PLAYER WIN <-##");
                color(RESET);
                quit = 1;
            }

            if (grid[i][j] == 'O' && grid[i][j + 1] == 'O' && grid[i][j + 2] == 'O' || grid[i][j] == 'O' && grid[i + 1][j] == 'O' && grid[i + 2][j] == 'O' || grid[i][j] == 'O' && grid[i + 1][j + 1] == 'O' && grid[i + 2][j + 2] == 'O' || grid[i][j] == 'O' && grid[i + 1][j - 1] == 'O' && grid[i + 2][j - 2] == 'O')
            {
                color(BLUE);
                printf("\n##-> COMPUTER WIN <-##");
                color(RESET);
                quit = 1;
            }
        }
    }
}

void start_grid(int grid_size)
{
    if (grid_size <= MAX)
    {
        for (int row = 0; row < grid_size; row++)
        {
            for (int col = 0; col < grid_size; col++)
            {
                grid[row][col] = '.';
            }
        }
    }
}

void draw_grid(int grid_size)
{
    if (grid_size <= MAX)
    {
        printf("    ");
        for (int i = 0; i < grid_size; i++)
        {
            color(BLUE);
            printf("%d ", i + 1);
            color(RESET);
        }
        printf("\n");
        for (int row = 0; row < grid_size; row++)
        {
            color(BLUE);
            printf("%d  ", row + 1);
            color(RESET);
            for (int col = 0; col < grid_size; col++)
            {
                putchar(' ');
                if (grid[row][col])
                {
                    if (grid[row][col] == 'O')
                    {
                        color(RED);
                        putchar(grid[row][col]);
                        color(RESET);
                    }
                    else
                    {

                        color(YELLOW);
                        putchar(grid[row][col]);
                        color(RESET);
                    }
                }
                else
                {
                    putchar('.');
                }
            }
            printf("\n");
        }
    }
    else
    {
        printf("The max size is 10");
    }
}

void color(int color)
{
    switch (color)
    {
    case RED:
        printf(_RED);
        break;
    case YELLOW:
        printf(_YELLOW);
        break;
    case RESET:
        printf(_RESET);
        break;

    case GREEN:
        printf(_GREEN);
        break;

    case BLUE:
        printf(_BLUE);
        break;

    default:
        break;
    }
}