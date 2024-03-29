#include "game.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void spawnNSquare(window, square, n) {
    time_t t;
    int winx = sfWindow_getSize(window).x;
    int sqrx = sfRectangleShape_getSize(square).x;
    int winy = sfWindow_getSize(window).y;
    int sqry = sfRectangleShape_getSize(square).y;
    srand((unsigned) time(&t));

    for (int i = 0; i<n; i++){
        int posx = rand() % (winx - sqrx);
        int posy = rand() % (winy - sqry);
        sfVector2f pos = {posx, posy};
        sfRectangleShape_setPosition(square, pos);

        sfRenderWindow_drawRectangleShape(window, square, NULL);
    }
}


int main()
{
    // Window
    sfVideoMode mode = {800, 450, 32};
    sfRenderWindow *window = sfRenderWindow_create(mode, "CSFML Example", sfTitlebar | sfClose, NULL);
    sfWindow_setFramerateLimit(window, 10);

    // Rectangle
    sfRectangleShape *shape = sfRectangleShape_create();
    sfVector2f vf = {50, 50}, pos = {30, 30};
    sfRectangleShape_setSize(shape, vf);
    sfRectangleShape_setFillColor(shape, sfWhite);
    sfRectangleShape_setOutlineColor(shape, sfBlack);
    sfRectangleShape_setOutlineThickness(shape, 10);
    sfRectangleShape_setPosition(shape, pos);


    // Multiple rectangles
    sfRectangleShape *shapes[8];
    int num_shapes = sizeof(shapes) / sizeof(shapes[0]);
    printf("%d\n", num_shapes);
    for (int i = 0; i < num_shapes; i++) {
        sfRectangleShape *shape = sfRectangleShape_create();
        sfVector2f vf = {50, 50}, pos = {30 + i*60, 30};
        sfRectangleShape_setSize(shape, vf);
        sfRectangleShape_setFillColor(shape, sfRed);
        sfRectangleShape_setOutlineColor(shape, sfBlue);
        sfRectangleShape_setOutlineThickness(shape, 2);
        sfRectangleShape_setPosition(shape, pos);

        shapes[i] = shape;
    }


    // Game loop
    while (sfRenderWindow_isOpen(window))
    {
        sfEvent event;
        while (sfRenderWindow_pollEvent(window, &event))
        {
            if (event.type == sfEvtClosed)
            {
                sfRenderWindow_close(window);
            }
            if (event.type == sfEvtKeyPressed) {
                if (event.key.code == sfKeyEscape) {
                    sfRenderWindow_close(window);
                }
            }
        }

        // Render
        sfRenderWindow_clear(window, sfWhite);

        spawnNSquare(window, shape, 10);

        
        sfRenderWindow_display(window);
    }

    for (int i = 0; i < num_shapes; i++) {
        sfRectangleShape_destroy(shapes[i]);
    }

    sfRenderWindow_destroy(window);

    return 0;
}