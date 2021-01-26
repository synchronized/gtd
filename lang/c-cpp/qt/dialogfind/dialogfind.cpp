#include "dialogfind.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QCheckBox>
#include <QDialog>
#include <QCheckBox>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QDialog>
#include <iostream>

DialogFind::DialogFind(QDialog *parent) : QDialog(parent) {
    label = new QLabel(tr("Find &what:"));
    lineEdit = new QLineEdit;
    label->setBuddy(lineEdit);

    caseCheckBox = new QCheckBox(tr("Match &case"));
    backwardCheckBox = new QCheckBox(tr("Search &backward"));

    findButton = new QPushButton(tr("&Find"));
    findButton->setDefault(true);
    findButton->setEnabled(false);

    closeButton = new QPushButton(tr("Close"));
    connect(lineEdit, SIGNAL(textChanged(const QString &)), this,
            SLOT(enableFindButton(const QString &)));
    connect(findButton, SIGNAL(clicked()), this, SLOT(findClicked()));
    connect(closeButton, SIGNAL(clicked()), this, SLOT(close()));

    connect(this, SIGNAL(findNext()), this, SLOT(findNextHandle()));
    connect(this, SIGNAL(findPrevious()), this, SLOT(findPreviousHandle()));

    QHBoxLayout *topLeftLayout = new QHBoxLayout;
    topLeftLayout->addWidget(label);
    topLeftLayout->addWidget(lineEdit);

    QVBoxLayout *leftLayout = new QVBoxLayout;
    leftLayout->addLayout(topLeftLayout);
    leftLayout->addWidget(caseCheckBox);
    leftLayout->addWidget(backwardCheckBox);

    QVBoxLayout *rightLayout = new QVBoxLayout;
    rightLayout->addWidget(findButton);
    rightLayout->addWidget(closeButton);
    rightLayout->addStretch();

    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addLayout(leftLayout);
    mainLayout->addLayout(rightLayout);
    setLayout(mainLayout);

    setWindowTitle(tr("Find"));
    setFixedHeight(sizeHint().height());
}

DialogFind::~DialogFind() {}

void DialogFind::findClicked() {
    QString text = lineEdit->text();
    Qt::CaseSensitivity cs =
        caseCheckBox->isChecked() ? Qt::CaseInsensitive : Qt::CaseSensitive;
    if (backwardCheckBox->isChecked()) {
        emit findPrevious(text, cs);
    } else {
        emit findNext(text, cs);
    }
}

void DialogFind::enableFindButton(const QString &text) {
    findButton->setEnabled(!text.isEmpty());
}

void DialogFind::findNextHandle(const QString &str, Qt::CaseSensitivity cs) {
  std::cout << "DialogFind::findNextHandle(" << str.toLatin1().data() << "," << cs << ")" << std::endl;
}

void DialogFind::findPreviousHandle(const QString &str, Qt::CaseSensitivity cs) {
  std::cout << "DialogFind::findPreviousHandle(" << qPrintable(str) << "," << cs << ")" << std::endl;
}

