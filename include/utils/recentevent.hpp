/* ----------------------------------------------------------------------------
   gigachat-linux-client - A linux client for gigachat digital ecosystem
   Copyright (C) 2024 Sotov Konstantin A

   This file is part of linux client for gigachat.

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public License
   as published by the Free Software Foundation; either version 3 of
   the License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful, but
   WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
   General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, see <http://www.gnu.org/licenses/>.
   ----------------------------------------------------------------------------
*/

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
