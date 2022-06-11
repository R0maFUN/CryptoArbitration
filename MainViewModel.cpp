#include "MainViewModel.h"

#include <QSharedPointer>

MainViewModel::MainViewModel()
{
    m_testViewModel = QSharedPointer<TestViewModel>::create();
}
