#ifndef QUESTION_H
#define QUESTION_H

#include <QJsonObject>
#include <QString>
#include <QStringList>


class Question
{
public:
    int id;
    QString category;
    QString question;
    QStringList answers;
    QList<int> rightAnswers;

    static Question fromJson(const QJsonObject &json);
};

#endif // QUESTION_H
