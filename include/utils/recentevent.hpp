#pragma once

#include <QAbstractButton>
#include <QObject>

// painting
#include <QBrush>
#include <QColor>
#include <QPaintEvent>
#include <QPainter>
#include <QPainterPath>
#include <QRegion>

class RecentEvent : public QAbstractButton
{
	Q_OBJECT

private:
	QPixmap ICON;

public:
	explicit RecentEvent(const QString &icon_path,
			     const QString &tooltip,
			     QWidget	   *parent = nullptr);

protected:
	void paintEvent(QPaintEvent *e) override;
};
