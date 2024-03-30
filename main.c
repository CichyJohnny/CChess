#include <SFML/Graphics.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 800
#define SQUARE_SIZE 100

sfRectangleShape* createSquare(sfVector2f position, sfVector2f size, sfColor color) {
    sfRectangleShape* square = sfRectangleShape_create();
    sfRectangleShape_setPosition(square, position);
    sfRectangleShape_setSize(square, size);
    sfRectangleShape_setFillColor(square, color);
    return square;
}

void drawChessboard(sfRenderWindow* window, sfRectangleShape* squares[8][8]) {
    for (int i=0; i<8; i++) {
        for (int j=0; j<8; j++) {
            sfRenderWindow_drawRectangleShape(window, squares[i][j], NULL);
        }
    }
}

int main() {
    sfVideoMode mode = {WINDOW_WIDTH, WINDOW_HEIGHT, 32};
    sfRenderWindow* window = sfRenderWindow_create(mode, "Chessboard", sfDefaultStyle, NULL);
    sfRenderWindow_setFramerateLimit(window, 60);

    sfRectangleShape* squares[8][8];

    for (int i=0; i<8; i++) {
        for (int j=0; j<8; j++) {
            sfVector2f position = {j * SQUARE_SIZE, i * SQUARE_SIZE};
            sfVector2f size = {SQUARE_SIZE, SQUARE_SIZE};
            sfColor color;
            if ((i + j) % 2 == 0)
                color = sfColor_fromRGB(209, 139, 71); // Brown color for squares
            else
                color = sfColor_fromRGB(255, 206, 158); // Cream color for squares
            squares[i][j] = createSquare(position, size, color);
        }
    }

    while (sfRenderWindow_isOpen(window)) {
        sfEvent event;
        while (sfRenderWindow_pollEvent(window, &event)) {
            if (event.type == sfEvtClosed) {
                sfRenderWindow_close(window);
            }
            else if (event.type == sfEvtKeyPressed) {
                if (event.key.code == sfKeyEscape) {
                    sfRenderWindow_close(window);
                }
            }
            else if (event.type == sfEvtMouseButtonPressed) {
                if (event.mouseButton.button == sfMouseLeft) {
                    // Get the position of the mouse click
                    sfVector2i mousePos = {event.mouseButton.x, event.mouseButton.y};
                    // Check which square was clicked and make it disappear
                    int col = mousePos.x / SQUARE_SIZE;
                    int row = mousePos.y / SQUARE_SIZE;
                    if (col >= 0 && col < 8 && row >= 0 && row < 8) {
                        sfRectangleShape_setSize(squares[row][col], (sfVector2f){0, 0});
                    }
                }
            }
        }

        sfRenderWindow_clear(window, sfWhite);
        drawChessboard(window, squares);
        sfRenderWindow_display(window);
    }

    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            sfRectangleShape_destroy(squares[i][j]);
        }
    }

    sfRenderWindow_destroy(window);

    return 0;
}
