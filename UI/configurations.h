#ifndef CONFIGURATIONS_H
#define CONFIGURATIONS_H

#include <QMainWindow>

namespace Ui {
class Configurations;
}

class Configurations : public QMainWindow
{
    Q_OBJECT

public:
    explicit Configurations(QWidget *parent = nullptr);
    ~Configurations();

private:
    Ui::Configurations *ui;
};

#endif // CONFIGURATIONS_H
