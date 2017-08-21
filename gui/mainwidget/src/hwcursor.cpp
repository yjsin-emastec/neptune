#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <linux/kd.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <sys/time.h>
#include <string.h>
#include <errno.h>

#include <QtGui>
#include "hwcursor.h"
#include "appmgr.h"

void HwCursor::move(int x, int y) 
{
	hwcursor_move(x, y);
	appmgr_hwcursor_position(x, y);
} 
