#ifndef BOARDSDATA_H
#define BOARDSDATA_H

#include <QString>
#include <QLabel>
#include <QPushButton>
#include <QWidget>



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

#endif // BOARDSDATA_H
