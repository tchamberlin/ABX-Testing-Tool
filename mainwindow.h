#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "scorekeeper.h"

#include <QMainWindow>
#include <QUrl>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    Q_ENUMS(Selections)

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    enum Selections
    {
        X_is_A,
        X_is_B
    };

private slots:
    void on_actionOpen_triggered();

    void on_X_is_A_button_pressed();

    void on_X_is_B_button_pressed();

    void updateLabels(ScoreKeeper::Score currentScore, ScoreKeeper::Score expectedScore);

signals:
    void loadSoundsRequest(QUrl sound_1, QUrl sound_2);
    void guessMade(ScoreKeeper::Guesses guess);
    void startNewTrialRequest();


private:
    Ui::MainWindow *ui;

    ScoreKeeper *score_keeper;

    void selectionMade(Selections selection);
};

#endif // MAINWINDOW_H
