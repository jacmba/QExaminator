#ifndef QUESTIONREPOSITORY_H
#define QUESTIONREPOSITORY_H

#include <QList>
#include <QString>
#include <question.h>

class QuestionRepository
{
public:
    static QList<Question> loadQuestions(const QString &filePath);
};

#endif // QUESTIONREPOSITORY_H
