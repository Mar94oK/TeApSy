#ifndef I2CREPRESENTATIONMODEL_H
#define I2CREPRESENTATIONMODEL_H


#include <QAbstractTableModel>


class I2cRepresentationModel : public QAbstractTableModel
{
    Q_OBJECT

public:

    I2cRepresentationModel(QObject *parent);
    int rowCount(const QModelIndex &parent = QModelIndex()) const ;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

};

#endif // I2CREPRESENTATIONMODEL_H
