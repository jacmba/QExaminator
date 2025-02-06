#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include "questionrepository.h"

QList<Question> QuestionRepository::loadQuestions(const QString &filePath)
{
    QList<Question> questions;

    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "Could not open file " << filePath;
        return questions;
    }

    QByteArray jsonData = file.readAll();
    file.close();

    QJsonDocument jDoc = QJsonDocument::fromJson(jsonData);
    if (!jDoc.isArray()) {
        qWarning() << "Invalid JSON format";
        return questions;
    }

    QJsonArray jArray = jDoc.array();
    for (const auto &item : jArray) {
        if (item.isObject()) {
            Question q = Question::fromJson(item.toObject());
            questions.append(q);
        }
    }

    return questions;
}
