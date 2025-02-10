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
#include <QMessageBox>

int seconds;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    loadQuestions();

    ui->setupUi(this);
    timer = new QTimer(this);
    setWindowTitle("QExaminator");
    start();

    connect(timer, SIGNAL(timeout()), this, SLOT(timerTimeout()));
    timer->setInterval(1000);

    connect(ui->action_About, SIGNAL(triggered()), this, SLOT(showAbout()));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete app;
    delete timer;
}

void MainWindow::loadQuestions()
{
    questions = QuestionRepository::loadQuestions("questions.json");
}

void MainWindow::showQuestion()
{
    clearLayout(ui->answersLayout);
    ui->titleLabel->clear();

    if (app->size() == 0) {
        timer->stop();
        ui->nextButton->hide();
        ui->checkButton->hide();
        ui->hudContainer->hide();
        ui->scoreLabel->setText(QString("Test score: ") + QString::number(app->getScore()) + QString(" %\nTime: " + QString::number(seconds) + "s"));
        ui->finishContainer->show();
        app->setState(AppState::POST_TEST);

        return;
    }

    ui->nextButton->hide();
    ui->checkButton->show();
    ui->hudContainer->show();

    currentQuestion = app->getQuestion();

    ui->progressLabel->setText(QString::number(app->getIndex()) + " of "  + QString::number(app->getMaxQuestions()));
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
        app->increaseScore();
    }

    ui->answersLayout->addWidget(resultLabel);
}

void MainWindow::start()
{
    if (app != nullptr) {
        delete app;
    }

    app = new App(questions);
    ui->nextButton->hide();
    ui->checkButton->hide();
    ui->startButton->show();

    ui->categoriesList->clear();

    ui->categoriesList->addItem("ALL");
    ui->categoriesList->addItems(app->getCategories());
    ui->initContainer->show();
    ui->finishContainer->hide();
    ui->hudContainer->hide();
    app->setState(AppState::INIT);
    app->setMaxQuestions(ui->maxQuestions->value());
    seconds = 0;
    timer->stop();
}

void MainWindow::showAbout()
{
    QMessageBox::about(this, "About QExaminator", "QExaminator v0.9.0\nCopyleft Jacinto Mba 2025");
}


void MainWindow::on_checkButton_clicked()
{
    checkAnswer();
}


void MainWindow::on_nextButton_clicked()
{
    showQuestion();
}


void MainWindow::on_startButton_clicked()
{
    app->setState(AppState::TEST_RUN);
    ui->startButton->hide();
    ui->initContainer->hide();
    showQuestion();
    seconds = 0;
    timer->start();
}


void MainWindow::on_categoriesList_currentTextChanged(const QString &arg1)
{
    app->setFilter(arg1);
}


void MainWindow::on_maxQuestions_valueChanged(int arg1)
{
    app->setMaxQuestions(arg1);
}


void MainWindow::on_homeButton_clicked()
{
    start();
}

void MainWindow::timerTimeout()
{
    seconds++;
    ui->timeLabel->setText(QString::number(seconds) + "s");
}

