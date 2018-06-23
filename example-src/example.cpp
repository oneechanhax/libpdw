
#include "lib/xoverlay.h"
#include "lib/glez.h"

#include "input.hpp"

int main() {
    xoverlay_init();
    glez_init(xoverlay_library.width, xoverlay_library.height);

    xoverlay_show();
    while (1) {
        input::RefreshInput();
        // Must be called in that order.
        xoverlay_draw_begin();
        glez_begin(); {

            glez_rect(100, 300, 200, 100, glez_rgba(255, 0, 128, 255));
            auto mouse = input::GetMouse();
            glez_rect(mouse.first - 6, mouse.second - 6, 12, 12, glez_rgba(255, 0, 128, 255));
        } glez_end();
        xoverlay_draw_end();
    }
    return 0;
}
