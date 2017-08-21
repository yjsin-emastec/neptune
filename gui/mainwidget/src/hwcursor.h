#ifndef HWCURSOR_H
#define HWCURSOR_H

#ifdef __cplusplus
        extern "C"{
#endif

extern int hwcursor_move(int, int);
extern int hwcursor_show(int);
#ifdef __cplusplus
}
#endif

#include <QScreenCursor>

class HwCursor : public QScreenCursor 
{
	public:
		virtual void move(int x, int y);
};

#endif
