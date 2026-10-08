#ifndef INPUT_H
#define INPUT_H

typedef struct {
    int algorithm;
    int sizeChoice;
    int wallsOn;
    int startPressed;
    int newMaze;
} InputState;

void input_init(void);
void input_update(InputState *input);

#endif