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

private:
    Ui::boardRepresentation *ui;

    QString _boardPicturePath;
    QString _boardDefinitionPath;
    QSize _sizeOftheDialogWindow;
    QString _boardName;

    QPixmap somePixmap;
    QLabel someLabel;
    QBrush someBrush;
    QImage someImage;




};

#endif // BOARDREPRESENTATION_H
