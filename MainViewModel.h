#pragma once

#include <QObject>
#include <QDebug>
#include <QSharedPointer>

#include "TestViewModel.h"

class MainViewModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(TestViewModel* testViewModel READ testViewModel CONSTANT)
public:
    explicit MainViewModel();

    Q_INVOKABLE void test()
    {
        qDebug() << "MainViewModel::test()";
    }

    TestViewModel * testViewModel()
    {
        return m_testViewModel.get();
    }

private:
    QSharedPointer<TestViewModel> m_testViewModel;
};
