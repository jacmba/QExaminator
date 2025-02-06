#include <QtTest>
#include "tst_testquestion.h"
#include "testquestionrepository.h"

int main(int argc, char** args) {
    int status = 0;

    {
        TestQuestion tc;
        status |= QTest::qExec(&tc, argc, args);
    }

    {
        TestQuestionRepository tc;
        status |= QTest::qExec(&tc, argc, args);
    }

    return status;
}
