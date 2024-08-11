#include "miniplayer.h"
#include "ui_miniplayer.h"

#include <QFileInfo>
#include <QDebug>

MiniPlayer::MiniPlayer(QWidget *parent, QString path):QWidget(parent), ui(new Ui::MiniPlayer)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_DeleteOnClose);

    this->setWindowFlags(Qt::Window | Qt::WindowStaysOnTopHint);

    this->player = new QMediaPlayer(this);
    this->output = new QAudioOutput(this);
    this->output->setVolume(100);
    this->player->setAudioOutput(this->output);

    connect(this->player, &QMediaPlayer::durationChanged, this, &MiniPlayer::durationChanged);
    connect(this->player, &QMediaPlayer::positionChanged, this, &MiniPlayer::positionChanged);

    QFileInfo fileInfo(path);
    ui->Title->setText(fileInfo.fileName());

    this->player->setSource(QUrl::fromLocalFile(path));
    this->isReapeat = false;
}

MiniPlayer::~MiniPlayer()
{
    delete ui;
}

QString MiniPlayer::int2time(qint64 time){
    QTime totalTime((time / 3600000) % 60, (time / 60000) % 60, (time / 1000) % 60, (time) % 1000);

    QString timeMediaFormat = "mm:ss:zzz";
    if(time > 3600000){
        timeMediaFormat = "hh:mm:ss";
    }

    return totalTime.toString(timeMediaFormat);
}

void MiniPlayer::durationChanged(qint64 duration){
    ui->AudioSlider->setRange(0, (duration/100));
    ui->Duration->setText(int2time(duration));
    this->audioDuration = duration;
}

void MiniPlayer::positionChanged(qint64 position){
    ui->AudioSlider->setValue(position / 100);
    ui->Position->setText(int2time(position));

    if(this->isReapeat && (position >= this->audioDuration)){
        this->player->setPosition(0);
        this->player->play();
    }
}



void MiniPlayer::on_AudioSlider_sliderMoved(int position)
{
    this->player->setPosition(position*100);
}


void MiniPlayer::on_AudioSlider_sliderPressed()
{
    // this->player->pause();
}


void MiniPlayer::on_AudioSlider_sliderReleased()
{
    // this->player->play();
}


void MiniPlayer::on_Play_clicked()
{
    this->player->play();
}

void MiniPlayer::on_Pause_clicked()
{
    this->player->pause();
}

void MiniPlayer::on_Stop_clicked()
{
    this->player->pause();
    this->player->setPosition(0);
}


void MiniPlayer::on_Repeat_clicked()
{
    if(this->isReapeat){
        this->isReapeat = false;
        ui->Repeat->setIcon(QIcon(":/images/icons/not-repeat.svg"));
    }else{
        this->isReapeat = true;
        ui->Repeat->setIcon(QIcon(":/images/icons/repeat.svg"));
    }
}

