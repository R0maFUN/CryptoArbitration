#pragma once

#include <QObject>
#include <QDebug>

class TestViewModel : public QObject
{
    Q_OBJECT
public:
    explicit TestViewModel();
    ~TestViewModel()
    {
        qDebug() << "~TestViewModel";
    }

    Q_INVOKABLE void testTest()
    {
        qDebug() << "TestViewModel::testTest()";
    }

signals:

};
