#include "question.h"

#include <QJsonArray>

Question Question::fromJson(const QJsonObject &json) {
    Question q;

    q.id = json["id"].toInt();
    q.category = json["category"].toString();
    q.question = json["question"].toString();

    QJsonArray answers = json["answers"].toArray();
    for (const auto &a : answers) {
        q.answers.append(a.toString());
    }

    QJsonArray rightAnswers = json["right_answers"].toArray();
    for (const auto &a : rightAnswers) {
        q.rightAnswers.append(a.toInt());
    }

    return q;
}
