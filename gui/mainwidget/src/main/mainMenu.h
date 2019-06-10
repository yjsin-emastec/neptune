#ifndef MAINMENU_H
#define MAINMENU_H

#include <QtGui/QDialog>
#include <QPushButton>
#include "ui_mainMenu.h"
#include "ui_mainMenu1080p.h"

class MainMenu : public QDialog
{
	Q_OBJECT

public:
	MainMenu(QWidget *parent = 0);
	~MainMenu();
	void initMainMenu(void);

private:
    int audioStatus;

    QPushButton *buttonSetup;
    QPushButton *buttonSearch;
    QPushButton *buttonAudio;
    QPushButton *buttonShutdown;
    QPushButton *buttonClose;
    QFrame      *frame;

public slots:
	void onButtonAudio();
	void onButtonClose();
    void onUpdateAudioButton();

signals:
	void setupClicked();
	void searchClicked();
	void shutdownClicked(void);
	void setAudioMute(void);
	void setAudio1(void);
	void setAudio2(void);
	void setAudio3(void);
	void setAudio4(void);
	void enterMainMenu(void);
	void exitMainMenu(void);

protected:
	int indexAudio;
	void keyPressEvent(QKeyEvent *event);

private slots:
	void onButtonSetup();
	void onButtonSearch();
	void onButtonShutdown();
};

#endif // MAINMENU_H
