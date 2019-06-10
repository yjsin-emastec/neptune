#ifndef LANGUAGEDIALOG_H
#define LANGUAGEDIALOG_H

#include <QtGui/QDialog>
#include "ui_languagedialog.h"
#include "ui_languagedialog1080p.h"
#include "DVR.h"

class TextMessageDialog;

class LanguageDialog : public QDialog
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

    QFrame *frame;
    QLineEdit *lineEditLanguage;
    QPushButton *buttonLanguageUp;
    QPushButton *buttonLanguageDown;
    QPushButton *buttonSave;
    QPushButton *buttonClose;
};

#endif // LANGUAGEDIALOG_H
