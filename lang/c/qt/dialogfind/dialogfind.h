#ifndef _DIALOGFIND_H
#define _DIALOGFIND_H

#include <QDialog>

class QCheckBox;
class QLabel;
class QLineEdit;
class QPushButton;

class DialogFind : public QDialog {
    Q_OBJECT
   public:
    DialogFind(QDialog *parent = 0);
    ~DialogFind();
   signals:
    void findNext(const QString &str, Qt::CaseSensitivity cs);
    void findPrevious(const QString &str, Qt::CaseSensitivity cs);

   private slots:

    void findClicked();
    void enableFindButton(const QString &text);

   private:
    QLabel *label;
    QLineEdit *lineEdit;
    QCheckBox *caseCheckBox;
    QCheckBox *backwardCheckBox;
    QPushButton *findButton;
    QPushButton *closeButton;

    void findNextHandle(const QString &str, Qt::CaseSensitivity cs);
    void findPreviousHandle(const QString &str, Qt::CaseSensitivity cs);
};

#endif  // _DIALOGFIND_H
