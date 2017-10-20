#include "boardrepresentation.h"
#include "ui_boardrepresentation.h"

boardRepresentation::boardRepresentation(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::boardRepresentation)
{
    ui->setupUi(this);

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
    float availibaleSpaceHeight = 0.875; // 7/8
    float availibaleSpaceWidth = 0.75; // 3/4
    int currentNumberOfBoadrs = 2;

    const float boardVerticalSize = _sizeOftheDialogWindow.height()*availibaleSpaceHeight / currentNumberOfBoadrs;
    const float boardHorizontalSize = _sizeOftheDialogWindow.width()*availibaleSpaceWidth / currentNumberOfBoadrs;

    ui->pushButton->setMaximumWidth(static_cast<int>(boardHorizontalSize));
    ui->pushButton->setMaximumHeight(static_cast<int>(boardVerticalSize));


    QPixmap pxmpBoard(_boardPicturePath);
    QPalette plteBoard;

    plteBoard.setBrush(ui->pushButton->backgroundRole(),
    QBrush(pxmpBoard.scaled(static_cast<int>(boardHorizontalSize), static_cast<int>(boardVerticalSize),
                                                           Qt::KeepAspectRatio, Qt::SmoothTransformation)));

    ui->pushButton->setFlat(true);
    ui->pushButton->setAutoFillBackground(true);
    ui->pushButton->setPalette(plteBoard);

    ui->label->setText("Something");
}
