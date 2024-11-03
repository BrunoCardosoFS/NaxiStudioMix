#include "playerwidget.h"
#include "ui_playerwidget.h"


PlayerWidget::PlayerWidget(QWidget *parent):QGroupBox(parent), ui(new Ui::PlayerWidget)
{
    ui->setupUi(this);

    this->Player = new AudioPlayer(this);

    connect(this->Player, &AudioPlayer::durationChanged, this, &PlayerWidget::updateDuration);
    connect(this->Player, &AudioPlayer::positionChanged, this, &PlayerWidget::updatePosition);
    connect(this->Player, &AudioPlayer::titleChanged, this, &PlayerWidget::updateTitle);


    this->Player->setSource("D:/MEDIA/MÚSICAS/Hits Sertanejo/Luan Santana, Luísa Sonza - Coração Cigano.mp3");
}

PlayerWidget::~PlayerWidget()
{
    delete ui;
}


void PlayerWidget::on_play_clicked()
{
    this->Player->play();
}


void PlayerWidget::on_pause_clicked()
{
    this->Player->pause();
}


void PlayerWidget::on_stop_clicked()
{
    this->Player->stop();
}

void PlayerWidget::updateDuration(qint64 durationms, QString duration){
    ui->slider->setRange(0, durationms/100);
    ui->duration->setText(duration);
}

void PlayerWidget::updatePosition(qint64 positionms, QString position){
    ui->slider->setValue(positionms/100);
    ui->position->setText(position);
}

void PlayerWidget::updateTitle(QString title){
    ui->title->setText(title);
}


void PlayerWidget::on_slider_sliderMoved(int position)
{
    this->Player->setPosition(position*100)
}

