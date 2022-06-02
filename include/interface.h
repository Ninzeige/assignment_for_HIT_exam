#ifndef HIT_ITF_H_
#define HIT_ITF_H_
#include <form.h>

enum interface_color
{
    cyan_color = 1,
    yellow_color,
    magenta_color,
    green_color,
    red_color,
    blue_color,
};


void initialize_colors();

void driver(int ch, FORM *form);
char *trim_whitespaces(char *str);

#endif /* HIT_ITF_H_ */