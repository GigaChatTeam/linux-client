#pragma once

#include <QAbstractScrollArea>
#include <QObject>

class GridScrollingWidget : public QAbstractScrollArea
{
    Q_OBJECT
public:
    explicit GridScrollingWidget(QWidget* parent);
};

