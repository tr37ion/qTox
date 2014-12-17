/*
    Copyright (C) 2014 by Project Tox <https://tox.im>

    This file is part of qTox, a Qt-based graphical interface for Tox.

    This program is libre software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.
    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

    See the COPYING file for more details.
*/

#include <QDebug>
#if defined(Q_OS_UNIX) && !defined(__APPLE__) && !defined(__MACH__)
#include "src/platform/timer.h"
#include <X11/extensions/scrnsaver.h>


uint32_t Platform::getIdleTime()
{
    uint32_t idleTime = 0;

    Display *display = XOpenDisplay(NULL);
    if (!display)
    {
        qDebug() << "XOpenDisplay(NULL) failed";
        return 0;
    }

    int32_t x11event = 0, x11error = 0;
    static int32_t hasExtension = XScreenSaverQueryExtension(display, &x11event, &x11error);
    if (hasExtension)
    {
        XScreenSaverInfo *info = XScreenSaverAllocInfo();
        if (info)
        {
            XScreenSaverQueryInfo(display, DefaultRootWindow(display), info);
            idleTime = info->idle;
            XFree(info);
        }
        else
            qDebug() << "XScreenSaverAllocInfo() failed";
    }
    XCloseDisplay(display);
    return idleTime;
}

#endif  // Q_OS_UNIX
