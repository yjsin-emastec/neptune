#ifndef MAINMENU_H
#define MAINMENU_H

#include <QtGui/QDialog>
#include <QPushButton>
#include "ui_mainMenu.h"

class QPushButton;

class MainMenu : public QDialog, public Ui::MainMenu
{
	Q_OBJECT

public:
	MainMenu(QWidget *parent = 0);
	~MainMenu();
	void initMainMenu(void);

public slots:
	void onButtonAudio();

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
	void onButtonClose();
};

#endif // MAINMENU_H
