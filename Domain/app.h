#ifndef APP_H
#define APP_H

#include <QList>
#include <QString>
#include "app_state.h"
#include "question.h"

class App
{
public:
    App(const QList<Question> &questions);

    AppState getState();
    int getMaxQuestions();
    Question getQuestion();
    QString getFilter();
    QStringList getCategories();
    int getScore();
    int size();

    void setState(AppState state);
    void setFilter(QString filter);
    void setMaxQuestions(int maxQuestions);
    void increaseScore();

private:
    AppState state;
    QList<Question> questions;
    QList<Question> filteredQuestions;
    QString filter;
    QStringList categories;
    int maxQuestions;
    int score;
    int questionIndex;
};

#endif // APP_H
