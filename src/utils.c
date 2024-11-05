#include "utils.h"

bool collide(float ax1, float ay1, float ax2, float ay2,
             float bx1, float by1, float bx2, float by2) {

    // Possiveis situacoes de nao colisao
    if(ax1 > bx2) return false;
    if(ax2 < bx1) return false;
    if(ay1 > by2) return false;
    if(ay2 < by1) return false;

    return true;
}