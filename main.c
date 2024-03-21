#include <SFML/Graphics.h>
#include <SFML/Window.h>

int main()
{
    sfVideoMode mode = {800, 450, 32};
    sfRenderWindow *window = sfRenderWindow_create(mode, "CSFML Example", sfResize | sfClose, NULL);

    sfRectangleShape *shape = sfRectangleShape_create();
    sfVector2f vf = {200, 200}, pos = {30, 30};
    sfRectangleShape_setSize(shape, vf);
    sfRectangleShape_setFillColor(shape, sfRed);
    sfRectangleShape_setPosition(shape, pos);

    while (sfRenderWindow_isOpen(window))
    {
        sfEvent event;
        while (sfRenderWindow_pollEvent(window, &event))
        {
            if (event.type == sfEvtClosed)
            {
                sfRenderWindow_close(window);
            }
        }

        sfRenderWindow_clear(window, sfBlack);
        sfRenderWindow_drawRectangleShape(window, shape, NULL);
        sfRenderWindow_display(window);
    }

    sfRectangleShape_destroy(shape);
    sfRenderWindow_destroy(window);

    return 0;
}