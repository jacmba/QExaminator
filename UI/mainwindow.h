#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLayout>
#include <questionrepository.h>

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

private:
    Ui::MainWindow *ui;

    QList<Question> questions;
    void loadQuestions();

    void showQuestion();

    void clearLayout(QLayout *layout);

    void checkAnswer();
};
#endif // MAINWINDOW_H
