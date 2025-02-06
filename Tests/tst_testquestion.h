#ifndef TST_TESTQUESTION_H
#define TST_TESTQUESTION_H

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

// #include "tst_testquestion.moc"

#endif // TST_TESTQUESTION_H
