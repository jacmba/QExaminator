#include <QtTest>
#include <QObject>
#include <question.h>

class TestQuestion : public QObject
{
    Q_OBJECT

public:
    TestQuestion();
    ~TestQuestion();

private slots:
    void testFromJson();
    void testRightAnswers();
};

TestQuestion::TestQuestion() {}

TestQuestion::~TestQuestion() {}

void TestQuestion::testFromJson() {
    QJsonObject json;
    json["id"] = 1;
    json["category"] = "Test Knowledge";
    json["question"] = "What is C++?";

    QJsonArray answers;
    answers.append("The name of a robot");
    answers.append("A TV channel");
    answers.append("A low level object oriented programming language");
    answers.append("A sports club");
    json["answers"] = answers;

    QJsonArray rightAnswers;
    rightAnswers.append(2);
    json["right_answers"] = rightAnswers;

    Question q = Question::fromJson(json);

    QCOMPARE(q.id, 1);
    QCOMPARE(q.category, "Test Knowledge");
    QCOMPARE(q.question, "What is C++?");
    QCOMPARE(q.answers.size(), 4);
    QCOMPARE(q.answers[2], "A low level object oriented programming language");
    QCOMPARE(q.rightAnswers.size(), 1);
    QCOMPARE(q.rightAnswers[0], 2);
}

void TestQuestion::testRightAnswers() {
    Question q;
    q.rightAnswers = {1, 4, 7};

    QCOMPARE(q.rightAnswers.size(), 3);
    QVERIFY(q.rightAnswers.contains(1));
    QVERIFY(q.rightAnswers.contains(2));
}

QTEST_APPLESS_MAIN(TestQuestion)

#include "tst_testquestion.moc"
