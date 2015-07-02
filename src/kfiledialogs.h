#pragma once

#include <QtCore/QString>

class KFileDialogs
{
public:

    static void error(const QString &message, QWidget *parent = 0);
    static void message(const QString &message, QWidget *parent = 0);
};


