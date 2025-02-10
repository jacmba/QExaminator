#include <QRandomGenerator>
#include "app.h"

App::App(const QList<Question> &questions) {
    for (const auto &q : questions) {
        this->questions.append(q);
        QString category = q.category;

        if (!categories.contains(category)) {
            categories.append(category);
        }
    }

    filteredQuestions.append(questions);

    state = AppState::INIT;
    filter = "ALL";
    maxQuestions = questions.size();
    score = 0;
    questionIndex = 0;
}

AppState App::getState()
{
    return state;
}

int App::getMaxQuestions()
{
    return maxQuestions;
}

Question App::getQuestion()
{
    questionIndex++;
    int index = QRandomGenerator::global()->bounded(0, filteredQuestions.size());
    Question q = filteredQuestions.takeAt(index);
    return q;
}

QString App::getFilter()
{
    return filter;
}

QStringList App::getCategories()
{
    return categories;
}

int App::getScore()
{
    return (double)score / (double)maxQuestions * 100.0;
}

int App::size()
{
    return questionIndex >= maxQuestions ? 0 : filteredQuestions.size();
}

int App::getIndex()
{
    return questionIndex;
}

void App::setState(AppState state)
{
    this->state = state;
}

void App::setFilter(QString filter)
{
    if (filter.isEmpty() || filter == "ALL" || !categories.contains(filter)) {
        return;
    }

    this->filter = filter;

    filteredQuestions.clear();

    for (const auto &q : questions) {
        if (q.category == filter) {
            filteredQuestions.append(q);
        }
    }
}

void App::setMaxQuestions(int maxQuestions)
{
    this->maxQuestions = maxQuestions;
}

void App::increaseScore()
{
    score++;
}
