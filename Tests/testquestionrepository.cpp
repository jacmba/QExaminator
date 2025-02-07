#include <QtTest>
#include <QString>
#include <QFile>
#include <QList>
#include <questionrepository.h>

#include "testquestionrepository.h"

TestQuestionRepository::TestQuestionRepository(QObject *parent)
    : QObject{parent}
{}

void TestQuestionRepository::testLoadQuestions()
{
    QString filePath = QFINDTESTDATA("test_questions.json");

    QFile file(filePath);
    QVERIFY2(file.exists(), "Check test JSON file should exist");

    QuestionRepository repo;
    QList<Question> questions = repo.loadQuestions(filePath);

    QCOMPARE(questions.size(), 3);
    QCOMPARE(questions[0].category, QString("General Knowledge"));
    QCOMPARE(questions[0].question, QString("What is the capital of France?"));
    QCOMPARE(questions[0].answers.size(), 3);
    QCOMPARE(questions[0].rightAnswers, QList<int>{0});
    QCOMPARE(questions[2].question, QString("Which of these are properties of OOP?"));
    QCOMPARE(questions[2].category, QString("Computing Knowledge"));
    QCOMPARE(questions[2].answers.size(), 3);
    QVERIFY(questions[2].rightAnswers.contains(0));
    QVERIFY(questions[2].rightAnswers.contains(2));
}
