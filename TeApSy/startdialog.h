#ifndef STARTDIALOG_H
#define STARTDIALOG_H

#include <QDialog>
#include "applicationsettings.h"
#include "boardrepresentation.h"
#include <QDesktopWidget>
#include <QDebug>
#include <QLabel>
#include <QFile>
#include <QPushButton>

#include <QPixmap>
#include <vector>

extern const QString releaseRevision;

namespace Ui {
class StartDialog;
}





class BoardsData {

    QPushButton* _respectingButton;
    QLabel* _respectingLabel;
    QString _picturePath;
    QString _boardSelectedPicturePath;
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
    QString boardSelectedPicturePath() const;
    void setBoardSelectedPicturePath(const QString &boardSelectedPicturePath);
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

    unsigned int theBoardsParser (const QString& filename);
    BoardsData theBoadrsStringParser(const QString& representationString);




    unsigned int boardSelectedByUser() const;
    //_boardSelectedByUser Defined by default like the fisrt board of the all the presented.
    //board are selected by names through signals/slots, but are defined as unsigned int inside
    //the class of Dialog.
    void setBoardSelectedByUser(unsigned int boardSelectedByUser);

private:
    Ui::StartDialog *ui;

    std::vector<BoardsData>_boardsData;
    //std::vector<RepresentationGUI>_GUIelements;
    std::vector<boardRepresentation*>_boardsRepresentationWidgets;

    unsigned int _numberOfBoards;
    unsigned int _boardSelectedByUser;

    QString _currentlySelectedBoard;

signals:
    void showMainWindow(bool);
    void closeTheProgramm(bool);
    void deselectBoard(QString boardName);
    void selectBoard(QString boardName);
    //void numberOfBoards(unsigned int totalBoards);

public slots:

    void btnOKisPressed();
    void btnCancelIsPressed();
    void boardSelected(QString boardName);




};


#endif // STARTDIALOG_H
