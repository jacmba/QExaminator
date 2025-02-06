#ifndef TESTQUESTIONREPOSITORY_H
#define TESTQUESTIONREPOSITORY_H

#include <QObject>

class TestQuestionRepository : public QObject
{
    Q_OBJECT
public:
    explicit TestQuestionRepository(QObject *parent = nullptr);

private slots:
    void testLoadQuestions();
};

#endif // TESTQUESTIONREPOSITORY_H
