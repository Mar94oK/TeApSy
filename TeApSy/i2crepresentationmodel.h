#ifndef I2CREPRESENTATIONMODEL_H
#define I2CREPRESENTATIONMODEL_H


#include <QAbstractTableModel>
#include <sipsapphirerefboard.h>
#include <QDebug>

enum Columns {
    Address7bit,
    Address8bit,
    DeviceName,
    ColumnCount
};

struct DeviceACKed{
    int address;
    QString name;
};

class I2cRepresentationModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    I2cRepresentationModel(QObject *parent);
    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    virtual int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    virtual QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

    void addDevice(const I2CDevice);

private:
    QVector<I2CDevice> _devices;
};

#endif // I2CREPRESENTATIONMODEL_H
