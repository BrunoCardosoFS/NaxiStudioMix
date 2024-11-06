#include "playerwidget.h"
#include "ui_playerwidget.h"

#include <QDebug>


PlayerWidget::PlayerWidget(QWidget *parent):QGroupBox(parent), ui(new Ui::PlayerWidget)
{
    ui->setupUi(this);

    this->loadPath = "";
    this->Player = new AudioPlayer(this);
    this->isPlaying = false;

    connect(this->Player, &AudioPlayer::durationChanged, this, &PlayerWidget::updateDuration);
    connect(this->Player, &AudioPlayer::positionChanged, this, &PlayerWidget::updatePosition);
    connect(this->Player, &AudioPlayer::titleChanged, this, &PlayerWidget::updateTitle);

    this->readyLoad = false;
    ui->load_media->hide();
}

PlayerWidget::~PlayerWidget()
{
    delete ui;
}

bool PlayerWidget::setDevice(QString key){
    return this->Player->setDevice(key);
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

void PlayerWidget::setPlayShortcut(QString key){
    ui->play->setShortcut(QKeySequence(key));
}

void PlayerWidget::setPauseShortcut(QString key){
    ui->pause->setShortcut(QKeySequence(key));
}

void PlayerWidget::setStopShortcut(QString key){
    ui->stop->setShortcut(QKeySequence(key));
}

void PlayerWidget::loadPlayer(QString path){
    if(!this->Player->isPlaying){
        this->loadPath = path;
        this->readyLoad = true;
        ui->control_area->hide();
        ui->load_media->show();
    }
}

void PlayerWidget::unloadPlayer(){
    this->readyLoad = false;
    ui->control_area->show();
    ui->load_media->hide();
}

void PlayerWidget::on_slider_sliderMoved(int position)
{
    this->Player->setPosition(position*100);
}

void PlayerWidget::on_slider_sliderPressed()
{
    if(this->Player->isPlaying){
        this->isPlaying = true;
        this->Player->pause();
    }else{
        this->isPlaying = false;
    }
}

void PlayerWidget::on_slider_sliderReleased()
{
    if(this->isPlaying){
        this->Player->play();
    }
}

void PlayerWidget::on_load_media_clicked()
{
    this->Player->setSource(this->loadPath);
    emit loaded();
    unloadPlayer();
}


