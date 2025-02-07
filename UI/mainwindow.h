#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLayout>
#include <QTimer>
#include <questionrepository.h>
#include <app.h>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_checkButton_clicked();

    void on_nextButton_clicked();

    void on_startButton_clicked();

    void on_categoriesList_currentTextChanged(const QString &arg1);

    void on_maxQuestions_valueChanged(int arg1);

    void on_homeButton_clicked();

    void timerTimeout();

private:
    Ui::MainWindow *ui;
    App *app;
    QTimer *timer;

    QList<Question> questions;
    Question currentQuestion;
    void loadQuestions();

    void showQuestion();

    void clearLayout(QLayout *layout);

    void checkAnswer();

    void start();
};
#endif // MAINWINDOW_H
