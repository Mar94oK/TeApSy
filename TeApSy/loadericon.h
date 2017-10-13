#ifndef LOADERICON_H
#define LOADERICON_H

#include <QWidget>
#include <QRect>
#include <QDesktopWidget>

namespace Ui {
class LoaderIcon;
}

class LoaderIcon : public QWidget
{
    Q_OBJECT

public:
    explicit LoaderIcon(QWidget *parent = 0);
    ~LoaderIcon();

private:
    Ui::LoaderIcon *ui;
};

#endif // LOADERICON_H
