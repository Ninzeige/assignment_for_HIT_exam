#include <ctype.h>
#include <form.h>
#include <ncurses.h>
#include <string.h>
#include "interface.h"

void initialize_colors()
{
    start_color();
    short background_color;
#ifdef NCURSES_VERSION
    if (use_default_colors() == OK)
        background_color = -1;
    else
        background_color = COLOR_BLACK;
#else
    background_color = COLOR_BLACK;
#endif
    init_pair(cyan_color, COLOR_CYAN, background_color);
    init_pair(red_color, COLOR_RED, background_color);
    init_pair(green_color, COLOR_GREEN, background_color);
    init_pair(yellow_color, COLOR_YELLOW, background_color);
    init_pair(blue_color, COLOR_BLUE, background_color);
    init_pair(magenta_color, COLOR_MAGENTA, background_color);
}

void driver(int ch, FORM *form)
{
    switch (ch)
    {
    case KEY_DOWN:
        form_driver(form, REQ_NEXT_FIELD);
        form_driver(form, REQ_END_LINE);
        break;

    case KEY_UP:
        form_driver(form, REQ_PREV_FIELD);
        form_driver(form, REQ_END_LINE);
        break;

    case KEY_LEFT:
        form_driver(form, REQ_PREV_CHAR);
        break;

    case KEY_RIGHT:
        form_driver(form, REQ_NEXT_CHAR);
        break;

    // Delete the char before cursor
    case KEY_BACKSPACE:
    case 127:
        form_driver(form, REQ_DEL_PREV);
        break;

    // Delete the char under the cursor
    case KEY_DC:
        form_driver(form, REQ_DEL_CHAR);
        break;

    default:
        form_driver(form, ch);
        break;
    }
}

char *trim_whitespaces(char *str)
{
    char *end;

    // trim leading space
    while (isspace(*str))
        str++;

    if (*str == 0) // all spaces?
        return str;

    // trim trailing space
    end = str + strnlen(str, 128) - 1;

    while (end > str && isspace(*end))
        end--;

    // write new null terminator
    *(end + 1) = '\0';

    return str;
}
