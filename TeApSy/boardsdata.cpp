#include "boardsdata.h"


QString BoardsData::definitionPath() const
{
    return _definitionPath;
}

void BoardsData::setDefinitionPath(const QString &definitionPath)
{
    _definitionPath = definitionPath;
}

QPushButton *BoardsData::respectingButton() const
{
    return _respectingButton;
}

void BoardsData::setRespectingButton(QPushButton *respectingButton)
{
    _respectingButton = respectingButton;
}

QLabel *BoardsData::respectingLabel() const
{
    return _respectingLabel;
}

void BoardsData::setRespectingLabel(QLabel *respectingLabel)
{
    _respectingLabel = respectingLabel;
}

QString BoardsData::name() const
{
    return _name;
}

void BoardsData::setName(const QString &name)
{
    _name = name;
}

QString BoardsData::boardSelectedPicturePath() const
{
    return _boardSelectedPicturePath;
}

void BoardsData::setBoardSelectedPicturePath(const QString &boardSelectedPicturePath)
{
    _boardSelectedPicturePath = boardSelectedPicturePath;
}

BoardsData::BoardsData()
{

}

QString BoardsData::picturePath() const
{
    return _picturePath;
}

void BoardsData::setPicturePath(const QString &picturePath)
{
    _picturePath = picturePath;
}
