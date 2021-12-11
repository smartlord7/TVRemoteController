// SCREEN_HELPER_H
#ifndef SCREEN_HELPER_H
#define SCREEN_HELPER_H

#include "wtypes.h"
#include <iostream>
using namespace std;

void GetDesktopResolution(int &width, int &height) {
    RECT desktop;
    const HWND hDesktop = GetDesktopWindow();
    GetWindowRect(hDesktop, &desktop);


    height = desktop.right;
    width = desktop.bottom;
}

#endif