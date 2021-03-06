#include "boardrepresentation.h"
#include "ui_boardrepresentation.h"

boardRepresentation::boardRepresentation(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::boardRepresentation)
{
    ui->setupUi(this);

    //connect each button press to the slot
    QObject::connect(ui->pushButton, &QPushButton::clicked, this, &boardRepresentation::_reportSelectedBoardName);


    //defined here only for debug, please do not forget to delete
    //after parser is ready!!!
    _boardSelectedPicturePath = ":/Pictures/programIco_Kasatka.jpg";


}



boardRepresentation::~boardRepresentation()
{
    delete ui;
}

QString boardRepresentation::boardPicturePath() const
{
    return _boardPicturePath;
}

void boardRepresentation::setBoardPicturePath(const QString &boardPicturePath)
{
    _boardPicturePath = boardPicturePath;
}

QString boardRepresentation::boardDefinitionPath() const
{
    return _boardDefinitionPath;
}

void boardRepresentation::setBoardDefinitionPath(const QString &boardDefinitionPath)
{
    _boardDefinitionPath = boardDefinitionPath;
}

QSize boardRepresentation::sizeOftheDialogWindow() const
{
    return _sizeOftheDialogWindow;
}

void boardRepresentation::setSizeOftheDialogWindow(QSize sizeOftheDialogWindow)
{
    _sizeOftheDialogWindow = sizeOftheDialogWindow;
}

QString boardRepresentation::boardName() const
{
    return _boardName;
}

void boardRepresentation::setBoardName(const QString &boardName)
{
    _boardName = boardName;
}

void boardRepresentation::setBoardReprtesentationGUI()
{
    //let them be the size of 7/8 for all the pictures, other space is for label info
    constexpr double availibaleSpaceHeight = 0.97; // 7/8
    constexpr double availibaleSpaceWidth = 0.75; // 3/4


    int currentNumberOfBoadrs = 2;

    const double boardVerticalSize = _sizeOftheDialogWindow.height()*availibaleSpaceHeight / _totalQuantityOfBoards;
    const double boardHorizontalSize = _sizeOftheDialogWindow.width()*availibaleSpaceWidth / _totalQuantityOfBoards;

    ui->pushButton->setMaximumWidth(static_cast<int>(boardHorizontalSize));
    ui->pushButton->setMaximumHeight(static_cast<int>(boardVerticalSize));
    qDebug() << boardHorizontalSize << "//" << boardVerticalSize;


    qDebug() << _respectingBoardsData.picturePath();

    QImage newImage(_respectingBoardsData.picturePath());
    _somePixmap.convertFromImage(newImage,Qt::ImageConversionFlag::AutoColor);
    QPalette somePalette;
    QBrush someBrush(QBrush(_somePixmap.scaled(static_cast<int>(boardHorizontalSize), static_cast<int>(boardVerticalSize),
                                                               Qt::KeepAspectRatio, Qt::SmoothTransformation)));

    somePalette.setBrush(ui->pushButton->backgroundRole(),
                         someBrush);

    ui->pushButton->setFlat(true);
    ui->pushButton->setAutoFillBackground(true);
    ui->pushButton->setPalette(somePalette);

    ui->pushButton->setText("");

    qDebug() << "Dialog Label Text: " << _respectingBoardsData.definitionPath();
    QFile file(_respectingBoardsData.definitionPath());
    qDebug() << "Lables parsing starts!";
    QString lblText;
    if (file.open(QIODevice::ReadOnly)) // | QIODevice::Text
    {
        while(!file.atEnd())
        {

            QString str = file.readLine();
            //QStringList lst = str.split(";");
            lblText += str;

        }
        ui->label->setText(lblText);
    }


    else
    {
        qDebug()<< "Cannot open this file!";
    }


}

void boardRepresentation::setBoardDefinition(const QString &filename)
{
    QFile file(filename);
    qDebug() << "Lables parsing starts!";


    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        while(!file.atEnd())
        {

            QString str = file.readLine();
            //QStringList lst = str.split(";");

            ui->label->setText(str);
        }
    }

    else
    {
        qDebug()<< "Cannot open this file!";
    }
}

QSize boardRepresentation::theButtonSize() const
{
    return ui->pushButton->size();

}

int boardRepresentation::totalQuantityOfBoards() const
{
    return _totalQuantityOfBoards;
}

void boardRepresentation::setTotalQuantityOfBoards(int totalQuantityOfBoards)
{
    _totalQuantityOfBoards = totalQuantityOfBoards;
}

QString boardRepresentation::boardSelectedPicturePath() const
{
    return _boardSelectedPicturePath;
}

void boardRepresentation::setBoardSelectedPicturePath(const QString &boardSelectedPicturePath)
{
    _boardSelectedPicturePath = boardSelectedPicturePath;
}

BoardsData boardRepresentation::respectingBoardsData() const
{
    return _respectingBoardsData;
}

void boardRepresentation::setRespectingBoardsData(const BoardsData &respectingBoardsData)
{
    _respectingBoardsData = respectingBoardsData;
}

void boardRepresentation::_reportSelectedBoardName()
{
    //change the button view state;
    _isPressed = true;
    //also reports to all the other buttons to change teir state
    emit _reportSelectedBoardName_Signal(_respectingBoardsData.name());

}

void boardRepresentation::_setTheButtonAsSelected(QString boardName)
{


    if (_respectingBoardsData.name() != boardName) return;//not for this board


    //let them be the size of 7/8 for all the pictures, other space is for label info
    constexpr double availibaleSpaceHeight = 0.97; // 7/8
    constexpr double availibaleSpaceWidth = 0.75; // 3/4

    //this Widget must receive this parameter
    //_totalQuantityOfBoards = 2;

    double boardVerticalSize = _sizeOftheDialogWindow.height()*availibaleSpaceHeight / _totalQuantityOfBoards;
    double boardHorizontalSize = _sizeOftheDialogWindow.width()*availibaleSpaceWidth / _totalQuantityOfBoards;

    _isPressed = true;

    QImage newImage(_respectingBoardsData.boardSelectedPicturePath());
    _somePixmap.convertFromImage(newImage,Qt::ImageConversionFlag::AutoColor);
    QPalette somePalette;
    QBrush someBrush(QBrush(_somePixmap.scaled(static_cast<int>(boardHorizontalSize), static_cast<int>(boardVerticalSize),
                                               Qt::KeepAspectRatio, Qt::SmoothTransformation)));

    somePalette.setBrush(ui->pushButton->backgroundRole(),
                         someBrush);
    ui->pushButton->setPalette(somePalette);

}

void boardRepresentation::_setTheButtonAsNotSelected(QString boardName)
{
    if (_respectingBoardsData.name() != boardName) return;//not for this board


    //let them be the size of 7/8 for all the pictures, other space is for label info
    constexpr double availibaleSpaceHeight = 0.97; // 7/8
    constexpr double availibaleSpaceWidth = 0.75; // 3/4

    //this Widget must receive this parameter
    int currentNumberOfBoadrs = 2;

    const double boardVerticalSize = _sizeOftheDialogWindow.height()*availibaleSpaceHeight / currentNumberOfBoadrs;
    const double boardHorizontalSize = _sizeOftheDialogWindow.width()*availibaleSpaceWidth / currentNumberOfBoadrs;

    _isPressed = true;

    QImage newImage(_respectingBoardsData.picturePath());
    _somePixmap.convertFromImage(newImage,Qt::ImageConversionFlag::AutoColor);
    QPalette somePalette;
    QBrush someBrush(QBrush(_somePixmap.scaled(static_cast<int>(boardHorizontalSize), static_cast<int>(boardVerticalSize),
                                               Qt::KeepAspectRatio, Qt::SmoothTransformation)));

    somePalette.setBrush(ui->pushButton->backgroundRole(),
                         someBrush);
    ui->pushButton->setPalette(somePalette);
}

//void boardRepresentation::_setTotalBoardsQuantity(unsigned int totalBoards)
//{
//    _totalQuantityOfBoards = totalBoards;
//}





