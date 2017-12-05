#include "i2crepresentationmodel.h"

I2cRepresentationModel::I2cRepresentationModel(QObject* parent)
                :QAbstractTableModel(parent)
{

}

int I2cRepresentationModel::rowCount(const QModelIndex &/*parent*/) const
{
    return _devices.count();
}

int I2cRepresentationModel::columnCount(const QModelIndex &parent) const
{
    if (parent != QModelIndex()) {
        return 0;
    }
    return ColumnCount;
}

QVariant I2cRepresentationModel::data(const QModelIndex &index, int role) const
{
    if (role != Qt::DisplayRole)
    {
        return {};
    }

    const I2CDevice &device = _devices.at(index.row());
    if (index.column() == Address7bit ) {
        QString hexademical7bit;
        hexademical7bit.setNum((device._I2CdeviceAddress.toInt() >> 1), 16);
        hexademical7bit.push_front("0x");

        return hexademical7bit.toUpper();
    }
    else if (index.column() == Address8bit) {

        QString hexademical8bitRead;
        QString hexademical8bitWrite;
        hexademical8bitWrite.setNum(device._I2CdeviceAddress.toInt(), 16);
        hexademical8bitRead.setNum(device._I2CdeviceAddress.toInt() + 1 , 16);
        QString result = hexademical8bitRead.toUpper() + "(R) // " + hexademical8bitWrite.toUpper() + "(W)";

        return result;

    }
    return device._I2CdeviceName;
}

QVariant I2cRepresentationModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole) {
        return {};
    }

    if (orientation == Qt::Horizontal) {
        static const std::map <Columns, QString> columnNames = {
            {Address7bit, "7 bit address"},
            {Address8bit, "8 bit address"},
            {DeviceName, "Device name"},
        };

        return columnNames.at(static_cast<Columns>(section));
    }
    else if (orientation == Qt::Vertical) {


        return section+1;
    }

    else {
        return {};
    }
}

void I2cRepresentationModel::addDevice(const I2CDevice device)
{
    //const QStringList &strings = str.split('|');
    _devices << device;
    emit layoutChanged();
}
