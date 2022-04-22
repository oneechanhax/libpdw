
/*
 * Libpdw: Primitives Done Well!
 * Copyright (C) 2022 Rebekah Rowe
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <X11/Xutil.h> // For xlibs keycodes, window geometry
#include <bitset> // For caching pressed keys

#include "functional.hpp"

#include "../example-src/lib/xoverlay.h"
#include "input.hpp"

namespace input {

cat::Event<std::pair<int, int>> bounds_event;
cat::Event<std::pair<int, int>> mouse_event;
cat::Event<CatKey, bool> key_event;

std::string_view key_names[static_cast<int>(CatKey::CATKEY_COUNT)] = {
    "NONE", "0",
    "1", "2",
    "3", "4",
    "5", "6",
    "7", "8",
    "9", "A",
    "B", "C",
    "D", "E",
    "F", "G",
    "H", "I",
    "J", "K",
    "L", "M",
    "N", "O",
    "P", "Q",
    "R", "S",
    "T", "U",
    "V", "W",
    "X", "Y",
    "Z",

    "ESCAPE", "LBRACKET",
    "RBRACKET", "SEMICOLON",
    "APOSTROPHE", "BACKQUOTE",
    "COMMA", "PERIOD",
    "SLASH", "BACKSLASH",
    "MINUS", "EQUAL",
    "ENTER", "SPACE",
    "BACKSPACE", "TAB",
    "CAPSLOCK",

    "INSERT", "DELETE",
    "HOME", "END",
    "PAGEUP", "PAGEDOWN",

    "LSHIFT", "RSHIFT",
    "LALT", "RALT",
    "LCONTROL", "RCONTROL",

    "PAD_0", "PAD_1",
    "PAD_2", "PAD_3",
    "PAD_4", "PAD_5",
    "PAD_6", "PAD_7",
    "PAD_8", "PAD_9",

    "PAD_DIVIDE", "PAD_MULTIPLY",
    "PAD_MINUS", "PAD_PLUS",
    "PAD_ENTER", "PAD_DECIMAL",

    "UP", "LEFT",
    "DOWN", "RIGHT",

    "F1", "F2",
    "F3", "F4",
    "F5", "F6",
    "F7", "F8",
    "F9", "F10",
    "F11", "F12",

    "MOUSE_1", "MOUSE_2",
    "MOUSE_3", "MOUSE_4",
    "MOUSE_5", "M_WHEEL_UP",
    "M_WHEEL_DOWN"
};

// Stores potential conversions between xlib's keycodes and cathooks catkeys. Add more as nessesary! /usr/include/X11/keysymdef.h
static const std::pair<int, CatKey> xlibToCatVar[] = {
    { XK_0, CATKEY_0 }, { XK_1, CATKEY_1 }, { XK_2, CATKEY_2 },
    { XK_3, CATKEY_3 }, { XK_4, CATKEY_4 }, { XK_5, CATKEY_5 },
    { XK_6, CATKEY_6 }, { XK_7, CATKEY_7 }, { XK_8, CATKEY_8 },
    { XK_9, CATKEY_9 }, { XK_A, CATKEY_A }, { XK_B, CATKEY_B },
    { XK_C, CATKEY_C }, { XK_D, CATKEY_D }, { XK_E, CATKEY_E },
    { XK_F, CATKEY_F }, { XK_G, CATKEY_G }, { XK_H, CATKEY_H },
    { XK_I, CATKEY_I }, { XK_J, CATKEY_J }, { XK_K, CATKEY_K },
    { XK_L, CATKEY_L }, { XK_M, CATKEY_M }, { XK_N, CATKEY_N },
    { XK_O, CATKEY_O }, { XK_P, CATKEY_P }, { XK_Q, CATKEY_Q },
    { XK_R, CATKEY_R }, { XK_S, CATKEY_S }, { XK_T, CATKEY_T },
    { XK_U, CATKEY_U }, { XK_V, CATKEY_V }, { XK_W, CATKEY_W },
    { XK_X, CATKEY_X }, { XK_Y, CATKEY_Y }, { XK_Z, CATKEY_Z },

    { XK_Escape, CATKEY_ESCAPE }, { XK_bracketleft, CATKEY_LBRACKET },
    { XK_bracketright, CATKEY_RBRACKET }, { XK_semicolon, CATKEY_SEMICOLON },
    { XK_apostrophe, CATKEY_APOSTROPHE }, { XK_apostrophe, CATKEY_COMMA },
    { XK_period, CATKEY_PERIOD }, { XK_slash, CATKEY_SLASH },
    { XK_backslash, CATKEY_BACKSLASH }, { XK_minus, CATKEY_MINUS },
    { XK_equal, CATKEY_EQUAL }, { XK_Return, CATKEY_ENTER },
    { XK_space, CATKEY_SPACE }, { XK_BackSpace, CATKEY_BACKSPACE },
    { XK_Tab, CATKEY_TAB }, { XK_Caps_Lock, CATKEY_CAPSLOCK },

    { XK_Insert, CATKEY_INSERT }, { XK_Delete, CATKEY_DELETE },
    { XK_Home, CATKEY_HOME }, { XK_End, CATKEY_END },
    { XK_Page_Up, CATKEY_PAGEUP }, { XK_Page_Down, CATKEY_PAGEDOWN },

    { XK_Shift_L, CATKEY_LSHIFT }, { XK_Shift_R, CATKEY_RSHIFT },
    { XK_Alt_L, CATKEY_LALT }, { XK_Alt_R, CATKEY_RALT },
    { XK_Control_L, CATKEY_LCONTROL }, { XK_Control_R, CATKEY_RCONTROL },

    { XK_KP_0, CATKEY_PAD_0 }, { XK_KP_1, CATKEY_PAD_1 }, { XK_KP_2, CATKEY_PAD_2 },
    { XK_KP_3, CATKEY_PAD_3 }, { XK_KP_4, CATKEY_PAD_4 }, { XK_KP_5, CATKEY_PAD_5 },
    { XK_KP_6, CATKEY_PAD_6 }, { XK_KP_7, CATKEY_PAD_7 }, { XK_KP_8, CATKEY_PAD_8 },
    { XK_KP_9, CATKEY_PAD_9 },

    { XK_KP_Divide, CATKEY_PAD_DIVIDE }, { XK_KP_Multiply, CATKEY_PAD_MULTIPLY },
    { XK_KP_Subtract, CATKEY_PAD_MINUS }, { XK_KP_Add, CATKEY_PAD_PLUS },
    { XK_KP_Enter, CATKEY_PAD_ENTER }, { XK_KP_Decimal, CATKEY_PAD_DECIMAL },

    { XK_Up, CATKEY_UP }, { XK_Left, CATKEY_LEFT },
    { XK_Down, CATKEY_DOWN }, { XK_Right, CATKEY_RIGHT },

    { XK_F1, CATKEY_F1 }, { XK_F2, CATKEY_F2 }, { XK_F3, CATKEY_F3 },
    { XK_F4, CATKEY_F4 }, { XK_F5, CATKEY_F5 }, { XK_F6, CATKEY_F6 },
    { XK_F7, CATKEY_F7 }, { XK_F8, CATKEY_F8 }, { XK_F9, CATKEY_F9 },
    { XK_F10, CATKEY_F10 }, { XK_F11, CATKEY_F11 }, { XK_F12, CATKEY_F12 },

    { XK_Pointer_DfltBtnPrev, CATKEY_M_WHEEL_UP }, { XK_Pointer_DfltBtnNext, CATKEY_M_WHEEL_DOWN }
};

// Used to store depressed keys
static std::bitset<CATKEY_COUNT> pressed_buttons;

// Mouse info
static std::pair<int, int> mouse(-1, -1);

// Screen height and width
static std::pair<int, int> bounds(-1, -1);

// Request this to update the input system on button, mouse, and window info
void RefreshInput() {
    if (!xoverlay_library.display || !xoverlay_library.window)
        return;

    // Get window bounds
    if (xoverlay_library.width != bounds.first || xoverlay_library.height != bounds.second) { // Activate on change
        bounds = std::make_pair(xoverlay_library.width, xoverlay_library.height);
        input::bounds_event.Emit(bounds);
    }

    // Update mouse position
    Window root_return, child_return;
    int root_x, root_y, mousex, mousey;
    unsigned int mask_return;
    if (XQueryPointer(xoverlay_library.display, xoverlay_library.window, &root_return, &child_return, &root_x, &root_y, &mousex, &mousey, &mask_return)) { // only update the cursor if this returns true
        if ((mousex != mouse.first || mousey != mouse.second) // Activate on change
            && (mousex >= 0 && mousey >= 0 && mousex <= bounds.first && mousey <= bounds.second)) { // Clamp positions to the window
            mouse = std::make_pair(mousex, mousey);
            input::mouse_event.Emit(mouse);
        }
        // We did a pointer query so check our buttons too!
        bool s = (mask_return & (Button1Mask));
        if (s != pressed_buttons[CATKEY_MOUSE_1]) {
            pressed_buttons[CATKEY_MOUSE_1] = s;
            input::key_event.Emit(CATKEY_MOUSE_1, s);
        }
        s = (mask_return & (Button2Mask));
        if (s != pressed_buttons[CATKEY_MOUSE_2]) {
            pressed_buttons[CATKEY_MOUSE_2] = s;
            input::key_event.Emit(CATKEY_MOUSE_2, s);
        }
        s = (mask_return & (Button3Mask));
        if (s != pressed_buttons[CATKEY_MOUSE_3]) {
            pressed_buttons[CATKEY_MOUSE_3] = s;
            input::key_event.Emit(CATKEY_MOUSE_3, s);
        }
        // Mouse 4-5 dont work for some reason. XLib doesnt like them...
    }

    // Find depressed keys and save them to the stored map
    char keys[32];
    XQueryKeymap(xoverlay_library.display, keys);
    // Recurse through the map looking for depressed keys
    for (const auto& current : xlibToCatVar) {

        // Get the keycode for the key we are looking for...
        int current_key = XKeysymToKeycode(xoverlay_library.display, current.first);

        // Use the keymap with bitwise logic to get state, oof this took forever to make
        bool pressed = (keys[current_key / 8] & (1 << (current_key % 8)));
        if (pressed != pressed_buttons[current.second]) {
            pressed_buttons[current.second] = pressed;
            input::key_event.Emit(current.second, pressed);
        }
    }
}

bool GetKey(CatKey k) {
    return pressed_buttons[k];
}
std::pair<int, int> GetMouse() {
    return mouse;
}
std::pair<int, int> GetBounds() {
    return bounds;
}

} // namespace input
