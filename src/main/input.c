#include "input.h"

NUContData inputData[1];

inline s8 getStickX() {
    return inputData->stick_x;
}

inline s8 getStickY() {
    return inputData->stick_y;
}

inline int isAPressed() {
    return inputData->button & A_BUTTON;
}

inline int isBPressed() {
    return inputData->button & B_BUTTON;
}