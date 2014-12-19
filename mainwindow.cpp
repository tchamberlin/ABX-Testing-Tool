#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Create an instance of a ScoreKeeper that will keep track of correct/incorrect answers and provide statistics on them
    score_keeper = new ScoreKeeper(this);

    // Upon retrieving the two sound file URLs, send a request to Playback to open them and assign them to the Players
    connect(this, SIGNAL(loadSoundsRequest(QUrl,QUrl)), ui->playbackWidget, SLOT(loadSounds(QUrl,QUrl)));
    // When a guess is made by the user, send whether it was correct or incorrect to ScoreKeeper
    connect(this, SIGNAL(guessMade(ScoreKeeper::Guesses)), score_keeper, SLOT(guessMade(ScoreKeeper::Guesses)));
    // When the user makes a guess, Playback starts a new trial
    connect(this, SIGNAL(startNewTrialRequest()), ui->playbackWidget, SLOT(startNewTrial()));
    // When ScoreKeeper has updated its scores, it notifies this window to update their display
    connect(score_keeper, SIGNAL(scoreUpdated(ScoreKeeper::Score,ScoreKeeper::Score)), this, SLOT(updateLabels(ScoreKeeper::Score,ScoreKeeper::Score)));
}

MainWindow::~MainWindow()
{
    delete ui;
//    delete score_keeper;
}

void MainWindow::updateLabels(ScoreKeeper::Score currentScore, ScoreKeeper::Score expectedScore)
{
    QString score_val_label_text = QString::number(currentScore.numberCorrect) + "/" + QString::number(currentScore.totalGuesses);
    QString prob_val_label_text = QString::number(expectedScore.numberCorrect) + "/" + QString::number(expectedScore.totalGuesses);
    ui->score_val_label->setText(score_val_label_text);
    ui->prob_val_label->setText(prob_val_label_text);
}

void MainWindow::selectionMade(Selections selection)
{
    QUrl A_Url = ui->playbackWidget->getUrlA();
    QUrl B_Url = ui->playbackWidget->getUrlB();
    QUrl X_Url = ui->playbackWidget->getUrlX();

//    qDebug() << "A: " << A_Url << endl;
//    qDebug() << "B: " << B_Url << endl;
//    qDebug() << "X: " << X_Url << endl;

    if (selection == X_is_A)
    {
        if (X_Url == A_Url)
            emit guessMade(ScoreKeeper::Correct);
        else if (X_Url == B_Url)
            emit guessMade(ScoreKeeper::Incorrect);
        else
            qDebug() << "X is not either A or B. Something has gone terribly wrong." << endl;

    }
    else if (selection == X_is_B)
    {
        if (X_Url == B_Url)
            emit guessMade(ScoreKeeper::Correct);
        else if (X_Url == A_Url)
            emit guessMade(ScoreKeeper::Incorrect);
        else
            qDebug() << "X is not either A or B. Something has gone terribly wrong." << endl;
    }
    else
    {
        qDebug() << "Invalid Selection state" << endl;
    }

    emit startNewTrialRequest();
}

void MainWindow::on_actionOpen_triggered()
{
    //From http://www.qtcentre.org/threads/18815-Select-multiple-files-from-QFileDialog
    QFileDialog dialog(this);

    dialog.setDirectory(QDir::homePath());
    dialog.setFileMode(QFileDialog::ExistingFiles);
    dialog.setNameFilter("*.wav ;; All files (*.*)");

    QStringList fileNames;
    if (dialog.exec())
        fileNames = dialog.selectedFiles();

    if (fileNames.length() == 2)
    {
        QUrl sound_1 = QUrl::fromLocalFile(fileNames.at(0));
        QUrl sound_2 = QUrl::fromLocalFile(fileNames.at(1));

        emit loadSoundsRequest(sound_1, sound_2);
    }
    else
    {
        qDebug() << "You must select exactly two files" << endl;
    }
}


void MainWindow::on_X_is_A_button_pressed()
{
    selectionMade(X_is_A);
}

void MainWindow::on_X_is_B_button_pressed()
{
    selectionMade(X_is_B);
}
