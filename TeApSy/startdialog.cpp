#include "startdialog.h"
#include "ui_startdialog.h"



StartDialog::StartDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StartDialog)
{
    ui->setupUi(this);


    //set the Dialog Title
    setWindowTitle("Select the Board");


    //connect main buttons of Dialog with Dialog Slots, which are emmiting signals to main Application (close/show)
    QObject::connect(this->ui->buttonBox, &QDialogButtonBox::accepted, this, &StartDialog::btnOKisPressed);
    QObject::connect(this->ui->buttonBox, &QDialogButtonBox::rejected, this, &StartDialog::btnCancelIsPressed);

    //set build version Text
    const float sizeOflabelAboutProgramm = static_cast<float>(0.1);
    ui->lblAboutProgramm->setText(( QString("TeApSy build ")+releaseRevision));
    ui->lblAboutProgramm->setMaximumHeight(static_cast<int>(size().height()*sizeOflabelAboutProgramm));





    qDebug() << "Dialog size width: " << size().width();
    qDebug() << "Dialog size height: " << size().height();


    //fixing the size of the Dialog
    setMaximumSize(size());
    setMinimumSize(size());



    //set The Available Boards Buttons
    //set the buttons
    _numberOfBoards = theBoardsParser(":/Tables/Boards/Boards.csv");


    for (unsigned int var = 0; var < _numberOfBoards; var++) {

        _boardsRepresentationWidgets.insert(_boardsRepresentationWidgets.begin(),new boardRepresentation(this));
        _boardsRepresentationWidgets.front()->setSizeOftheDialogWindow(size());
        _boardsRepresentationWidgets.front()->setBoardPicturePath(_boardsData[var].picturePath());
        _boardsRepresentationWidgets.front()->setBoardDefinitionPath(_boardsData[var].definitionPath());
        _boardsRepresentationWidgets.front()->setBoardName(_boardsData[var].name());

    }
    for (unsigned int var = 0; var < _boardsRepresentationWidgets.size(); var++) {

        ui->lytBoards->addWidget(_boardsRepresentationWidgets[var]);
        _boardsRepresentationWidgets[var]->setBoardReprtesentationGUI();
        //_boardsRepresentationWidgets[var]->setBoardDefinition(_boardsData[var].definitionPath());


    }







}

StartDialog::~StartDialog()
{
    delete ui;
}

unsigned int StartDialog::theBoardsParser(const QString &filename)
{
    QFile file(filename);
    qDebug() << "Boards parsing starts!";
    unsigned int i = 0;

    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        while(!file.atEnd())
        {

            QString str = file.readLine();
            //QStringList lst = str.split(";");

            _boardsData.insert(_boardsData.begin(), theBoadrsStringParser(str));
            ++i; //number of boards;
        }
    }

    else
    {
        qDebug()<< "Cannot open this file!";
    }
    return i;

}

BoardsData StartDialog::theBoadrsStringParser(const QString &representationString)
{
    BoardsData theBoard;
    QStringList lst = representationString.split(";");
    theBoard.setName(lst.first());
    lst.removeFirst();
    theBoard.setPicturePath(lst.first());
    lst.removeFirst();
    theBoard.setDefinitionPath(lst.first());

    return theBoard;

}

void StartDialog::btnOKisPressed()
{
    emit showMainWindow(true);
}

void StartDialog::btnCancelIsPressed()
{
    emit closeTheProgramm(true);
}

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
