#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef unsigned char uint8_t;

typedef struct Pick
{
    uint8_t code;
    // 0 - rock
    // 1 - paper
    // 2 - scissors
} Pick;

typedef struct Player
{
    Pick pick;
} Player;

int get_valid_integer()
{
    int value;
    int result = scanf("%d", &value);

    if (result == EOF)
    {
        printf("Nothing has been read\n");
        return -1;
    }

    if (result == 0)
    {
        while (fgetc(stdin) != '\n')
            ;
        return -1;
    }

    if (value < 0 || value > 2)
    {
        return -1;
    }

    return value;
}

Player create_player(uint8_t code)
{
    Pick pick;
    pick.code = code;

    Player player;
    player.pick = pick;

    return player;
}

uint8_t random_pick(uint8_t lower, uint8_t upper)
{
    srand(time(NULL));
    int random = rand();
    uint8_t pick = (random % (upper - lower + 1)) + lower;

    return pick;
}

void show_winner(Player player1, Player player2, uint8_t upper)
{
    uint8_t loses = (player1.pick.code + 1) % (upper + 1);
    uint8_t wins = (player1.pick.code + 2) % (upper + 1);
    uint8_t code = player2.pick.code;

    printf("\n");
    if (code == loses)
    {
        printf("Player 2 won!\n");
    }
    else if (code == wins)
    {
        printf("Player 1 won!\n");
    }
    else
    {
        printf("Tie!");
    }
}

int main(void)
{
    uint8_t lower = 0, upper = 2;
    printf("Enter any integer between 0 and 2\n\n");
    printf("0 = Rock\n1 = Paper\n2 = Scissors\n\n");

    int value = get_valid_integer();

    while (value == -1)
    {
        value = get_valid_integer();
    }

    Player player = create_player(value);
    Player cpu = create_player(random_pick(lower, upper));

    show_winner(player, cpu, upper);

    return 0;
}
