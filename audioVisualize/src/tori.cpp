#include "tori.h"

void Tori::setup() {
    // 上辺
    boxes[0].set(50, 50, 400);
    boxes[0].setPosition(0, 300, -100);

    // 上辺奥
    boxes[1].set(50, 400, 50);
    boxes[1].setPosition(0, 75, -275);

    // 上辺手前
    boxes[2].set(50, 400, 50);
    boxes[2].setPosition(0, 75, 75);
}

void Tori::draw() {
    for (int i = 0; i < 3; i++) {
        boxes[i].draw();
    }
}
