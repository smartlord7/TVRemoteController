// SCREEN_HELPER_H
#ifndef SCREEN_HELPER_H
#define SCREEN_HELPER_H

#include <X11/Xlib.h>

void GetDesktopResolution(int &width, int &height) {
    Display *d = XOpenDisplay(nullptr);
    Screen *s = DefaultScreenOfDisplay(d);
    width = s->width;
    height = s->height;
}

#endif