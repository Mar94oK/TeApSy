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

    const DeviceACKed &device = _devices.at(index.row());
    if (index.column() == Address7bit ||
            index.column() == Address8bit) {
        return device.address;
    }
    return device.name;
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

void I2cRepresentationModel::addDevice(const QString &str)
{
    const QStringList &strings = str.split('|');
    _devices << DeviceACKed{strings.first().toInt(), strings.last()};
    emit layoutChanged();
}
