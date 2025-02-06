#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QRandomGenerator>
#include <QLabel>
#include <QCheckBox>
#include <QRadioButton>
#include <QHBoxLayout>
#include <QLayoutItem>
#include <QWidget>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    loadQuestions();
    ui->setupUi(this);

    showQuestion();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::loadQuestions()
{
    questions = QuestionRepository::loadQuestions("questions.json");
}

void MainWindow::showQuestion()
{
    clearLayout(ui->answersLayout);
    ui->titleLabel->clear();

    if (questions.size() == 0) {
        return;
    }

    int index = QRandomGenerator::global()->bounded(0, questions.size());

    Question question = questions.takeAt(index);

    ui->titleLabel->setText(question.question);

    for (const auto &a : question.answers) {
        QHBoxLayout *row = new QHBoxLayout();
        QLabel *label = new QLabel(a);

        if(question.rightAnswers.size() == 1) {
            QRadioButton *rb = new QRadioButton();
            row->addWidget(rb);
        } else {
            QCheckBox *cb = new QCheckBox();
            row->addWidget(cb);
        }

        row->addWidget(label);
        ui->answersLayout->addLayout(row);
    }
}

void MainWindow::clearLayout(QLayout *layout)
{
    if (!layout) return;  // Ensure layout is valid

    if (!ui->answersLayout) {
        qWarning() << "answersLayout is null!";
        return;
    }

    while (QLayoutItem *item = layout->takeAt(0)) {
        if (!item) {
            qWarning() << "item is null!!";
            continue;
        }

        if (QWidget *widget = item->widget()) {
            widget->hide();  // Hide before deleting
            widget->deleteLater();
        } else if (QLayout *childLayout = item->layout()) {
            clearLayout(childLayout);  // Recursively clear nested layouts
            delete childLayout;
        }
    }
}


void MainWindow::on_checkButton_clicked()
{
    showQuestion();

    // ToDO actually check answer result, etc
}

