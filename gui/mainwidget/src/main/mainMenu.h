#ifndef MAINMENU_H
#define MAINMENU_H

#include <QtGui/QDialog>
#include <QPushButton>
#include "ui_mainMenu.h"
#include "ui_mainMenu1080p.h"
#include "ui/customwidget/customimagelabel.h"

class MainMenu : public QDialog
{
	Q_OBJECT

public:
	MainMenu(QWidget *parent = 0);
	~MainMenu();
	void initMainMenu(void);

private:
    int audioStatus;

    void setAudioOut(int index);

    QFrame              *frame;
    CustomImageLabel    *buttonSetup;
    CustomImageLabel    *buttonSearch;
    CustomImageLabel    *buttonNotAvailable;
    CustomImageLabel    *buttonAudio;
    CustomImageLabel    *buttonShutdown;
    CustomImageLabel    *buttonClose;

    QLabel              *labelSetupText;
    QLabel              *labelSearchText;
    QLabel              *labelNotAvailableText;
    QLabel              *labelAudioText;
    QLabel              *labelShutdownText;
    QLabel              *labelCloseText;

public slots:
	void onButtonAudio();
	void onButtonClose();
    void onUpdateAudioButton();

signals:
	void setupClicked();
	void searchClicked();
	void shutdownClicked(void);
	void setAudioMute(void);
    void setAudio(int);
	void enterMainMenu(void);
	void exitMainMenu(void);
    void changePrevAudio(int ch);

protected:
	int indexAudio;
	void keyPressEvent(QKeyEvent *event);

private slots:
	void onButtonSetup();
	void onButtonSearch();
	void onButtonShutdown();

    void setFocusSetup();
    void setFocusSearch();
    void setFocusAudio();
    void setFocusShutdown();
    void setFocusClose();

private:
    QPixmap iconImageNormal[6];
    QPixmap iconImageFocus[6];

    void changeFocus(int n);
    void updateAudioIcon(int audioNum);

    int iconSize;
};

#endif // MAINMENU_H
