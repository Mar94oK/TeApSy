#include "i2crepresentationmodel.h"

I2cRepresentationModel::I2cRepresentationModel(QObject* parent)
                :QAbstractTableModel(parent)
{

}

int I2cRepresentationModel::rowCount(const QModelIndex &parent) const
{
    return 2;
}

int I2cRepresentationModel::columnCount(const QModelIndex &parent) const
{
    return 3;
}

QVariant I2cRepresentationModel::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole)
    {
       return QString("Row%1, Column%2")
                   .arg(index.row() + 1)
                   .arg(index.column() +1);
    }
    return QVariant();
}
