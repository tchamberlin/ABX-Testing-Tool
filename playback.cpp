#include "playback.h"
#include "ui_playback.h"

#include <QTime>

Playback::Playback(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Playback)
{
    ui->setupUi(this);

    player_A = new Player(0, QMediaPlayer::LowLatency);
    player_B = new Player(0, QMediaPlayer::LowLatency);
    player_X = new Player(0, QMediaPlayer::LowLatency);

    // TODO: check that setting the parent will automatically clean these up on exit
    thread_A = new QThread(this);
    thread_B = new QThread(this);
    thread_X = new QThread(this);

    player_A->moveToThread(thread_A);
    player_B->moveToThread(thread_B);
    player_X->moveToThread(thread_X);



    current_player = NULL;
    last_player = NULL;

    QTime time = QTime::currentTime();
    qsrand((uint)time.msec());

    connect(ui->checkBox_loop, SIGNAL(toggled(bool)), player_A, SLOT(playbackModeChanged(bool)));
    connect(ui->checkBox_loop, SIGNAL(toggled(bool)), player_B, SLOT(playbackModeChanged(bool)));
    connect(ui->checkBox_loop, SIGNAL(toggled(bool)), player_X, SLOT(playbackModeChanged(bool)));

    connect(player_A, SIGNAL(durationChanged(qint64)), this, SLOT(durationChanged(qint64)));
    connect(player_B, SIGNAL(durationChanged(qint64)), this, SLOT(durationChanged(qint64)));
    connect(player_X, SIGNAL(durationChanged(qint64)), this, SLOT(durationChanged(qint64)));


    connect(player_A, SIGNAL(positionChanged(qint64)), this, SLOT(positionChanged(qint64)));
    connect(player_B, SIGNAL(positionChanged(qint64)), this, SLOT(positionChanged(qint64)));
    connect(player_X, SIGNAL(positionChanged(qint64)), this, SLOT(positionChanged(qint64)));

    connect(ui->horizontalSlider, SIGNAL(playbackPosChanged(qint64)), this, SLOT(setPlaybackPosition(qint64)));

    // Error handling
    connect(player_A, SIGNAL(error(QMediaPlayer::Error)), this, SLOT(handlePlayerError(QMediaPlayer::Error)));
    connect(player_B, SIGNAL(error(QMediaPlayer::Error)), this, SLOT(handlePlayerError(QMediaPlayer::Error)));
    connect(player_X, SIGNAL(error(QMediaPlayer::Error)), this, SLOT(handlePlayerError(QMediaPlayer::Error)));

//    connect(player_A, SIGNAL(soundChanged()),


//    connect(ui->horizontalSlider, SIGNAL(sliderMoved(int)), this, SLOT());

    thread_A->start();
    thread_B->start();
    thread_X->start();
}

void Playback::durationChanged(qint64 len)
{
    qDebug() << "Duration changed to: " << len << endl;
    qDebug() << "Player A media status: " << player_A->mediaStatus() << endl;
    qDebug() << "Player B media status: " << player_B->mediaStatus() << endl;
    qDebug() << "Player X media status: " << player_X->mediaStatus() << endl;

    if (ui->horizontalSlider->maximum() == 0 ||
        ui->horizontalSlider->maximum() == len)
    {
        ui->horizontalSlider->setMaximum(len);
    }
    else
    {
        qDebug() << "Sound length anomally. All sounds should be the same length." << endl;
    }
}

void Playback::positionChanged(qint64 pos)
{
    // THIS WILL BREAK WITH LONG ENOUGH FILES
    ui->horizontalSlider->setValue(pos);
}

void Playback::setPlaybackPosition(qint64 pos)
{
//    qDebug() << "Setting Position" << endl;
    if (pos <= ui->horizontalSlider->maximum())
        current_player->setPosition(pos);
    else
        qDebug() << "Position requested that is outside the bounds of the slider." << endl;
}

Playback::~Playback()
{
    delete ui;
}

void Playback::loadSounds(QUrl sound_1, QUrl sound_2)
{
    this->sound_1 = sound_1;
    this->sound_2 = sound_2;

    startNewTrial();
}

void Playback::startNewTrial()
{
    //    current_player->stop();

    qDebug() << "Starting new trial" << endl;

    if (qrand() % 2 == 0)
    {
        player_A->changeSound(sound_1);
        player_B->changeSound(sound_2);
    }
    else
    {
        player_A->changeSound(sound_2);
        player_B->changeSound(sound_1);
    }

    if (qrand() % 2 == 0)
    {
        player_X->changeSound(sound_1);
    }
    else
    {
        player_X->changeSound(sound_2);
    }
}

bool Playback::switchToPlayer(Player *p)
{
    if (p->state() == Player::PlayingState)
        return false;

    last_player = current_player;
    current_player = p;

    qint64 pos;
    if (last_player != NULL)
        pos = last_player->position();
    else
        pos = 0;

//    qDebug() << "pos: " << pos << endl;

    if (p == player_A)
    {
        player_A->setPosition(pos);
        player_B->stop();
        player_X->stop();
        player_A->play();
    }
    else if (p == player_B)
    {
        player_B->setPosition(pos);
        player_A->stop();
        player_X->stop();
        player_B->play();
    }
    else if (p == player_X)
    {
        player_X->setPosition(pos);
        player_A->stop();
        player_B->stop();
        player_X->play();
    }
    else
    {
        qDebug() << "Cannot switch players. Invalid player specified." << endl;
        return false;
    }

    return true;
}

void Playback::handlePlayerError(QMediaPlayer::Error error)
{
    qDebug() << "Player error: " << error << endl;
}


QUrl Playback::getUrlA()
{
    return player_A->getUrl();
}

QUrl Playback::getUrlB()
{
    return player_B->getUrl();
}

QUrl Playback::getUrlX()
{
    return player_X->getUrl();
}

void Playback::on_pushButton_play_pressed()
{
    if (ui->radioButton_A->isChecked())
        switchToPlayer(player_A);
    else if (ui->radioButton_B->isChecked())
        switchToPlayer(player_B);
    else if (ui->radioButton_X->isChecked())
        switchToPlayer(player_X);
    else
        qDebug() << "No sound is selected" << endl;
}

void Playback::on_radioButton_A_pressed()
{
    switchToPlayer(player_A);
}

void Playback::on_radioButton_B_pressed()
{
    switchToPlayer(player_B);
}

void Playback::on_radioButton_X_pressed()
{
    switchToPlayer(player_X);
}

void Playback::on_pushButton_pause_pressed()
{
    current_player->pause();
}

void Playback::on_pushButton_stop_pressed()
{
    current_player->stop();
}
