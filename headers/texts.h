#include "include_define.h"

#ifndef TEXTS_H
#define TEXTS_H

sfText* textTurn(sfFont* font) {
    sfText* text_turn = sfText_create();
    sfText_setString(text_turn, "White Turn!");
    sfText_setFont(text_turn, font);
    sfText_setCharacterSize(text_turn, 48);
    sfText_setPosition(text_turn, (sfVector2f){9 * SQUARE_SIZE, 1 * SQUARE_SIZE});

    return text_turn;
}

sfText* textEvent(sfFont* font) {
    sfText* text_event = sfText_create();
    sfText_setFont(text_event, font);
    sfText_setCharacterSize(text_event, 48);
    sfText_setPosition(text_event, (sfVector2f){9 * SQUARE_SIZE, 2 * SQUARE_SIZE});

    return text_event;
}

sfText* textCount(sfFont* font) {
    sfText* text_count = sfText_create();

    sfText_setFont(text_count, font);
    sfText_setCharacterSize(text_count, 24);
    sfText_setPosition(text_count, (sfVector2f){10 + 8 * SQUARE_SIZE, 10});

    return text_count;
}

#endif