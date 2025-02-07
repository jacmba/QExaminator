#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QRandomGenerator>
#include <QLabel>
#include <QCheckBox>
#include <QRadioButton>
#include <QHBoxLayout>
#include <QLayoutItem>
#include <QWidget>
#include <QAbstractButton>

Question currentQuestion;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    loadQuestions();
    ui->setupUi(this);
    setWindowTitle("QExaminator");
    ui->nextButton->hide();
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
        ui->nextButton->hide();
        ui->checkButton->hide();

        return;
    }

    ui->nextButton->hide();
    ui->checkButton->show();

    int index = QRandomGenerator::global()->bounded(0, questions.size());

    currentQuestion = questions.takeAt(index);

    ui->titleLabel->setText(currentQuestion.question);

    for (const auto &a : currentQuestion.answers) {
        QHBoxLayout *row = new QHBoxLayout();
        row->setAlignment(Qt::AlignLeft);
        QLabel *label = new QLabel(a);

        if(currentQuestion.rightAnswers.size() == 1) {
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

void MainWindow::checkAnswer()
{
    ui->nextButton->show();
    ui->checkButton->hide();

    int fails = 0;

    for (int i = 0; i < ui->answersLayout->count(); i++) {
        QLayoutItem *rowItem = ui->answersLayout->itemAt(i);
        QHBoxLayout *row = dynamic_cast<QHBoxLayout*>(rowItem->layout());

        QLayoutItem *boxItem = row->itemAt(0);
        QAbstractButton *box = dynamic_cast<QAbstractButton*>(boxItem->widget());
        box->setDisabled(true);

        QLayoutItem *textItem = row->itemAt(1);
        QLabel * text = dynamic_cast<QLabel*>(textItem->widget());

        if(!currentQuestion.rightAnswers.contains(i)) {
            text->setStyleSheet("color: red; font-weight: bold; text-decoration: line-through;");

            if (box->isChecked()) {
                fails++;
            }
        } else {
            text->setStyleSheet("color: green; font-weight: bold;");

            if (!box->isChecked()) {
                fails++;
            }
        }
    }

    QLabel *resultLabel = new QLabel("CORRECT !!");
    resultLabel->setAlignment(Qt::AlignCenter);

    if (fails > 0) {
        resultLabel->setText("INCORRECT !!");
        resultLabel->setStyleSheet("color: red; font-weight: bold; border: 2px solid red; padding: 5px; border-radius: 10px;");
    } else {
        resultLabel->setStyleSheet("color: green; font-weight: bold; border: 2px solid green; padding: 5px; border-radius: 10px;");
    }

    ui->answersLayout->addWidget(resultLabel);
}


void MainWindow::on_checkButton_clicked()
{
    checkAnswer();
}


void MainWindow::on_nextButton_clicked()
{
    showQuestion();
}

