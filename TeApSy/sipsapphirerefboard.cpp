#include "sipsapphirerefboard.h"

SiPSapphireRefBoard::SiPSapphireRefBoard()
{

}

QString SipSapphireCommand::command() const
{
    return _command;
}

QString SipSapphireCommand::commandTitle() const
{
    return _commandTitle;
}

SipSapphireCommand::SipSapphireCommand(QString commandTitle, QString command)
{
    _command = command;
    _commandTitle = commandTitle;
}
