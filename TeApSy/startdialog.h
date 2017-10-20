#ifndef STARTDIALOG_H
#define STARTDIALOG_H

#include <QDialog>
#include "applicationsettings.h"
#include <QDesktopWidget>
#include <QDebug>
#include <QLabel>
#include <QFile>
#include <QPushButton>
#include <boardrepresentation.h>

extern const QString releaseRevision;

namespace Ui {
class StartDialog;
}






class BoardsData {

    QPushButton* _respectingButton;
    QLabel* _respectingLabel;
    QString _picturePath;
    QString _definitionPath;
    QString _name;

public:

    BoardsData();

    QString picturePath() const;
    void setPicturePath(const QString &picturePath);
    QString definitionPath() const;
    void setDefinitionPath(const QString &definitionPath);
    QPushButton *respectingButton() const;
    void setRespectingButton(QPushButton *respectingButton);
    QLabel *respectingLabel() const;
    void setRespectingLabel(QLabel *respectingLabel);
    QString name() const;
    void setName(const QString &name);
};

struct RepresentationGUI {
    QPushButton* btn;
    QLabel* lbl;

};


class StartDialog : public QDialog
{
    Q_OBJECT

public:
    explicit StartDialog(QWidget *parent = 0);
    ~StartDialog();

    int theBoardsParser (const QString& filename);
    BoardsData theBoadrsStringParser(const QString& representationString);


private:
    Ui::StartDialog *ui;

    std::vector<BoardsData>_boardsData;
    std::vector<RepresentationGUI>_GUIelements;
    std::vector<boardRepresentation*>_boardsRepresentationWidgets;

    int _numberOfBoards;



signals:
    void showMainWindow(bool);
    void closeTheProgramm(bool);


public slots:
    void btnOKisPressed();
    void btnCancelIsPressed();




};


#endif // STARTDIALOG_H
