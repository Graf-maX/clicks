#pragma once

#include <QObject>

class IMainView
{
public:
    virtual ~IMainView() {}

    virtual void setNumber(const QString& number) = 0;

    virtual void setCount(int rightCount, int wrongCount) = 0;
};

Q_DECLARE_INTERFACE(IMainView, "IMainView")
