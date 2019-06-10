#include <QApplication>
#include <QTranslator>
#include <QTextCodec>
#include <glib.h>
#include "main/mainwidget.h"
#include "main/mainglobal.h"
#include "test/testwidget.h"
#include "hal/diskserviceimpl.h"
#include "hwcursor.h"

extern QScreenCursor *qt_screencursor;

extern int gIsFrameBufferOpen;

static void hal_init(void)
{
    if(utils_get_bootmode() == 1)
    {
        DiskService::setImpl(new AppmgrDiskService);
    }
    else
    {
        DiskService::setImpl(new TestmgrDiskService);
    }
}
static void set_font(void)
{
    int fontsize = 20;

    QFont myfont("unifont");
    myfont.setPointSize(fontsize);
    QApplication::setFont(myfont);
}
int appl_main(int argc, char *argv[])
{
    int mainWidth = 800;
    int mainHeight = 600;

    if(!g_thread_supported())
    {
        g_thread_init(NULL);
    }

    appmgr_init(&mainWidth, &mainHeight);

    hal_init();

    QApplication app(argc, argv);

    gIsFrameBufferOpen++;

    qt_screencursor->move(-30, -30);
    qt_screencursor->hide();

    set_font();

    MainWidget mainWindow(mainWidth, mainHeight);
    mainWindow.show();

    if(mainHeight == 720)
    {
        app.setOverrideCursor(QCursor(QPixmap(":/images/cursor.png"), 1, 1));
    }
    else
    {
        app.setOverrideCursor(QCursor(QPixmap(":/images/cursor2.png"), 1, 1));
    }

    return app.exec();
}
int test_main(int argc, char *argv[])
{
    if(testmgr_init() < 0)
    {
        return 0;
    }

    hal_init();

    QApplication app(argc, argv);

    gIsFrameBufferOpen++;

    set_font();

    TestWidget testWindow;
    testWindow.show();

    app.setOverrideCursor(QCursor(QPixmap(":/images/cursor.png"), 1, 1));

    return app.exec();
}
int main(int argc, char *argv[])
{
    if(utils_get_bootmode() == 1)
    {
        return appl_main(argc, argv);
    }
    else
    {
        return test_main(argc, argv);
    }
}
