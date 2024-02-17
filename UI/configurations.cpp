#include "configurations.h"
#include "ui_configurations.h"

Configurations::Configurations(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Configurations)
{
    ui->setupUi(this);
}

Configurations::~Configurations()
{
    delete ui;
}
