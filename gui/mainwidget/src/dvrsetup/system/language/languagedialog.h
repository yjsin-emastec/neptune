#ifndef LANGUAGEDIALOG_H
#define LANGUAGEDIALOG_H

#include <QtGui/QDialog>
#include "ui_languagedialog.h"
#include "DVR.h"

class TextMessageDialog;

class LanguageDialog : public QDialog, public Ui::LanguageDialog
{
    Q_OBJECT

public:
    LanguageDialog(QWidget *parent = 0);
    ~LanguageDialog();
	void initLanguageConfig(void);

signals:

public slots:
	void onButtonLanguageUp(void);
	void onButtonLanguageDown(void);
    void onButtonLanguageSave(void);

protected:
	void keyPressEvent(QKeyEvent *event);
	void keyReleaseEvent(QKeyEvent *event);
	
private:
	int indexLanguage;
    TextMessageDialog *msgBox;
    QString previousLanguage;
};

#endif // LANGUAGEDIALOG_H
