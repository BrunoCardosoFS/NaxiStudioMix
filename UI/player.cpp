#include "player.h"
#include "./ui_player.h"

#include <QFileInfo>
#include <QFile>
#include <QDateTime>
#include <QSettings>

#include <QDir>

#include<QDebug>

QSettings settings("NaxiStudio", "NaxiStudio Player");

QString currentFolder;
QString pathDB;

QJsonArray foldersMusic;
QJsonArray foldersJingle;
QJsonArray foldersOther;
QJsonArray foldersCommercial;

player::player(QWidget *parent):QMainWindow(parent), ui(new Ui::player)
{
    ui->setupUi(this);


    initApp();

    connect(ui->listWidget, &QListWidget::itemDoubleClicked, this, &player::loadMediasCatalog);


    // Creating date and time

    dateTime = new QTimer(this);
    updateClock();
    connect(dateTime, SIGNAL(timeout()), this, SLOT(updateClock()));
    dateTime->start(1000);


    // Creating and configuring players

    MPlayer1 = new QMediaPlayer();
    MPlayer1AudioOutput = new QAudioOutput();
    MPlayer1AudioOutput->setVolume(100);
    MPlayer1->setAudioOutput(MPlayer1AudioOutput);

    MPlayer2 = new QMediaPlayer();
    MPlayer2AudioOutput = new QAudioOutput();
    MPlayer2AudioOutput->setVolume(100);
    MPlayer2->setAudioOutput(MPlayer2AudioOutput);

    MPlayer3 = new QMediaPlayer();
    MPlayer3AudioOutput = new QAudioOutput();
    MPlayer3AudioOutput->setVolume(100);
    MPlayer3->setAudioOutput(MPlayer3AudioOutput);


    // Connect players

    connect(MPlayer1, &QMediaPlayer::durationChanged, this, [=](qint64 duration){updateDuration(duration, 0);});
    connect(MPlayer1, &QMediaPlayer::positionChanged, this, [=](qint64 progress){updateProgress(progress, 0);});

    connect(MPlayer1AudioOutput, &QAudioOutput::volumeChanged, this, [=](qint64 vol){qInfo() << vol;});

    connect(MPlayer2, &QMediaPlayer::durationChanged, this, [=](qint64 duration){updateDuration(duration, 1);});
    connect(MPlayer2, &QMediaPlayer::positionChanged, this, [=](qint64 progress){updateProgress(progress, 1);});

    connect(MPlayer3, &QMediaPlayer::durationChanged, this, [=](qint64 duration){updateDuration(duration, 2);});
    connect(MPlayer3, &QMediaPlayer::positionChanged, this, [=](qint64 progress){updateProgress(progress, 2);});
}

player::~player()
{
    delete ui;
}

void player::initApp(){
    qInfo() << "\n";
    qInfo() << settings.value("db");

    if(!settings.contains("db")){
        settings.setValue("db", QCoreApplication::applicationDirPath());
    }

    settings.setValue("db", "D:/Arquivos/Projetos/Qt/NaxiStudio/DB");

    pathDB = settings.value("db").toString();

    openCatalog(pathDB + "/catalog.json");
    on_openMusic2_clicked();

    ui->loadMediaPlayer1->hide();
    ui->loadMediaPlayer1->raise();
    ui->loadMediaPlayer2->hide();
    ui->loadMediaPlayer2->raise();
    ui->loadMediaPlayer3->hide();
    ui->loadMediaPlayer3->raise();
}

// Updating clock
void player::updateClock(){
    QDateTime currentTime = QDateTime::currentDateTime();
    ui->dateTime->setText(currentTime.toString("dd/MM/yyyy  hh:mm:ss"));
}


// Updating player times

void player::updateDuration(qint64 duration, qint8 player)
{
    QList playerSlider = {ui->player1Slider, ui->player2Slider, ui->player3Slider};
    QList playerDuration = {ui->player1Duration, ui->player2Duration, ui->player3Duration};

    QTime totalTime((duration / 3600000) % 60, (duration / 60000) % 60, (duration / 1000) % 60, (duration) % 1000);

    QString timeMediaFormat = "mm:ss:zzz";
    if(duration > 3600000){
        timeMediaFormat = "hh:mm:ss";
    }

    playerSlider[player]->setRange(0, duration / 100);
    playerDuration[player]->setText(totalTime.toString(timeMediaFormat));
}

void player::updateProgress(qint64 progress, qint8 player){
    QList playerTime = {ui->player1Time, ui->player2Time, ui->player3Time};
    QList playerSlider = {ui->player1Slider, ui->player2Slider, ui->player3Slider};

    QTime CurrentTime((progress / 3600000) % 60, (progress / 60000) % 60, (progress / 1000) % 60, (progress) % 1000);

    QString timeMediaFormat = "mm:ss:zzz";
    if(progress > 3600000){
        timeMediaFormat = "hh:mm:ss";
    }

    playerSlider[player]->setValue(progress / 100);
    playerTime[player]->setText(CurrentTime.toString(timeMediaFormat));
}


// Temporary buttons

void player::on_openMusic_clicked()
{
    QString FileName = QFileDialog::getOpenFileName(this, tr("Selecionar Audio"), "", tr("MP3 Files (*.mp3)"));
    loadPlayer(0, FileName);
}

void player::on_openMusic1_clicked()
{
    ui->loadMediaPlayer1->setFixedSize(ui->player1->size());
    ui->loadMediaPlayer1->show();
}

void player::on_openMusic2_clicked()
{
    QListWidgetItem *itemJingle = new QListWidgetItem("Vinhetas");
    QListWidgetItem *itemMusic = new QListWidgetItem("Músicas");
    QListWidgetItem *itemCommercial = new QListWidgetItem("Comerciais");
    QListWidgetItem *itemOther = new QListWidgetItem("Outros");

    QFont font("Segoe UI", 10, QFont::Bold);

    itemJingle->setFont(font);
    itemMusic->setFont(font);
    itemCommercial->setFont(font);
    itemOther->setFont(font);

    itemJingle->setFlags(Qt::ItemIsEnabled);
    itemMusic->setFlags(Qt::ItemIsEnabled);
    itemCommercial->setFlags(Qt::ItemIsEnabled);
    itemOther->setFlags(Qt::ItemIsEnabled);

    itemJingle->setData(Qt::TextAlignmentRole, Qt::AlignHCenter);
    itemMusic->setData(Qt::TextAlignmentRole, Qt::AlignHCenter);
    itemCommercial->setData(Qt::TextAlignmentRole, Qt::AlignHCenter);
    itemOther->setData(Qt::TextAlignmentRole, Qt::AlignHCenter);

    ui->listWidget->clear();


    ui->listWidget->addItem(itemJingle);
    foreach (QJsonValue jsonValue, foldersJingle) {
        QJsonObject jsonObject = jsonValue.toObject();

        QListWidgetItem *item = new QListWidgetItem(jsonObject.value("title").toString());

        item->setData(Qt::UserRole + 1, "folder");
        item->setData(Qt::UserRole + 2, jsonObject.value("type").toInt());
        item->setData(Qt::UserRole + 3, jsonObject.value("path").toString());

        ui->listWidget->addItem(item);
    }

    ui->listWidget->addItem(itemMusic);
    foreach (QJsonValue jsonValue, foldersMusic) {
        QJsonObject jsonObject = jsonValue.toObject();

        QListWidgetItem *item = new QListWidgetItem(jsonObject.value("title").toString());

        item->setData(Qt::UserRole + 1, "folder");
        item->setData(Qt::UserRole + 2, jsonObject.value("type").toInt());
        item->setData(Qt::UserRole + 3, jsonObject.value("path").toString());

        ui->listWidget->addItem(item);
    }

    ui->listWidget->addItem(itemOther);
    foreach (QJsonValue jsonValue, foldersOther) {
        QJsonObject jsonObject = jsonValue.toObject();

        QListWidgetItem *item = new QListWidgetItem(jsonObject.value("title").toString());

        item->setData(Qt::UserRole + 1, "folder");
        item->setData(Qt::UserRole + 2, jsonObject.value("type").toInt());
        item->setData(Qt::UserRole + 3, jsonObject.value("path").toString());

        ui->listWidget->addItem(item);
    }

    ui->listWidget->addItem(itemCommercial);
    foreach (QJsonValue jsonValue, foldersCommercial) {
        QJsonObject jsonObject = jsonValue.toObject();

        QListWidgetItem *item = new QListWidgetItem(jsonObject.value("title").toString());

        item->setData(Qt::UserRole + 1, "folder");
        item->setData(Qt::UserRole + 2, jsonObject.value("type").toInt());
        item->setData(Qt::UserRole + 3, jsonObject.value("path").toString());

        ui->listWidget->addItem(item);
    }
}

void player::loadMediasCatalog(QListWidgetItem *item){
    if(item->data(Qt::UserRole + 1).toString() == "folder"){
        QDir files(item->data(Qt::UserRole + 3).toString());

        ui->listWidget->clear();

        ui->listWidget->insertItem(0, "Voltar");
        ui->listWidget->item(0)->setData(Qt::TextAlignmentRole, Qt::AlignHCenter);
        ui->listWidget->item(0)->setFont(QFont("Segoe UI", 10, QFont::Bold));

        foreach (QFileInfo qfi, files.entryInfoList()) {
            QString suffix = qfi.completeSuffix();
            if(qfi.isFile() && (suffix == "mp3" || suffix == "wav" || suffix == "opus" || suffix == "aac" || suffix == "flac")){
                ui->listWidget->addItem(qfi.fileName());
            }
        }

        ui->listWidget->verticalScrollBar()->setValue(0);
    }else if(item->text() == "Voltar"){
        on_openMusic2_clicked();
    }
}

void player::openCatalog(QString path){
    QFile catalog(path);
    catalog.open(QFile::ReadOnly | QFile::Text);
    QTextStream dataCatalog(&catalog);
    QString jsonString = dataCatalog.readAll();
    catalog.close();

    QJsonDocument jsonDocument = QJsonDocument::fromJson(jsonString.toUtf8());
    QJsonArray jsonArray = jsonDocument.array();

    foreach (QJsonValue jsonValue, jsonArray) {
        QJsonObject jsonObject = jsonValue.toObject();

        switch (jsonObject.value("type").toInt()) {
        case 0:
            foldersJingle.append(jsonValue);
            break;
        case 1:
            foldersMusic.append(jsonValue);
            break;
        case 2:
            foldersCommercial.append(jsonValue);
            break;
        default:
            foldersOther.append(jsonValue);
            break;
        }
    }
}

void player::on_openPlaylist_clicked()
{
    QString openDir = QFileDialog::getExistingDirectory(this, tr("Open Directory"), "", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

    if(openDir != ""){
        QDir files(openDir);

        foreach (QFileInfo qfi, files.entryInfoList()) {
            QString suffix = qfi.completeSuffix();
            if(qfi.isFile() && (suffix == "mp3" || suffix == "wav" || suffix == "opus" || suffix == "aac" || suffix == "flac")){
                ui->listWidget->addItem(qfi.fileName());
            }
        }
    }
}


// Loading media in player

void player::loadPlayer(qint8 player, QString path)
{
    QList players = {MPlayer1, MPlayer2, MPlayer3};
    QList playersTitle = {ui->player1Title, ui->player2Title, ui->player3Title};

    if(path != ""){
        players[player]->setSource(QUrl::fromLocalFile(path));

        QFileInfo fileInfo(path);
        playersTitle[player]->setText(fileInfo.fileName());
    }
}


// Player 1 controls

void player::on_player1Play_clicked()
{MPlayer1->play();}

void player::on_player1Pause_clicked()
{MPlayer1->pause();}

void player::on_player1Stop_clicked()
{MPlayer1->stop();MPlayer1->setPosition(0);}

void player::on_player1Slider_sliderMoved(int position)
{MPlayer1->setPosition(position * 100);}


// Player 2 controls

void player::on_player2Play_clicked()
{MPlayer2->play();}

void player::on_player2Pause_clicked()
{MPlayer2->pause();}

void player::on_player2Stop_clicked()
{MPlayer2->stop();MPlayer2->setPosition(0);}

void player::on_player2Slider_sliderMoved(int position)
{MPlayer2->setPosition(position * 100);}


// Player 3 controls

void player::on_player3Play_clicked()
{MPlayer3->play();}

void player::on_player3Pause_clicked()
{MPlayer3->pause();}

void player::on_player3Stop_clicked()
{MPlayer3->stop();MPlayer3->setPosition(0);}

void player::on_player3Slider_sliderMoved(int position)
{MPlayer3->setPosition(position * 100);}



void player::on_openConfig_clicked()
{
    windowConfig = new Configurations;
    windowConfig->show();
}

