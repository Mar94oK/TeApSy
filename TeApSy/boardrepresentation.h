#ifndef BOARDREPRESENTATION_H
#define BOARDREPRESENTATION_H


#include <QPushButton>
#include <QString>
#include <QPixmap>
#include <QDebug>
#include <QFile>
#include <QLabel>
#include <QFile>
#include <vector>
#include <QSize>
#include <QWidget>


namespace Ui {
class boardRepresentation;
}

class boardRepresentation : public QWidget
{
    Q_OBJECT

public:
    explicit boardRepresentation(QWidget *parent = 0);

    ~boardRepresentation();

    QString boardPicturePath() const;
    void setBoardPicturePath(const QString &boardPicturePath);

    QString boardDefinitionPath() const;
    void setBoardDefinitionPath(const QString &boardDefinitionPath);

    QSize sizeOftheDialogWindow() const;
    void setSizeOftheDialogWindow(QSize sizeOftheDialogWindow);

    QString boardName() const;
    void setBoardName(const QString &boardName);

    void setBoardReprtesentationGUI();
    void setBoardDefinition(const QString &filename);

    QSize theButtonSize() const;


    int totalQuantityOfBoards() const;
    void setTotalQuantityOfBoards(int totalQuantityOfBoards);

private:
    Ui::boardRepresentation *ui;

    QString _boardPicturePath;
    //this variable should be defined in the respecting boards.cvs table!
    //as debug stage, this is defined in the constructor
    QString _boardSelectedPicturePath;
    QString _boardDefinitionPath;
    QSize _sizeOftheDialogWindow;
    QString _boardName;
    int _totalQuantityOfBoards;

    QPixmap _somePixmap;
    QLabel _someLabel;
    QBrush _someBrush;
    QImage _someImage;

    bool _isPressed;

signals:
    void _reportSelectedBoardName_Signal(QString theBoardName);


public slots:

    void _reportSelectedBoardName();
    void _setTheButtonAsSelected(QString boardName);
    void _setTheButtonAsNotSelected(QString boardName);
    //void _setTotalBoardsQuantity(unsigned int totalBoards);

};

#endif // BOARDREPRESENTATION_H
