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

#include "utils/recentevent.hpp"

RecentEvent::RecentEvent(const QString &icon_path,
			 const QString &tooltip,
			 QWidget       *parent)
    : QAbstractButton{parent}
{
	setCheckable(false);
	setToolTip(tooltip);
	ICON = QPixmap(icon_path);
}

void RecentEvent::paintEvent(QPaintEvent *e)
{
	QRect	 r = e->rect();
	QPainter painter(this);

	QPainterPath circleBig, circleSmall;
	circleBig.addEllipse(r);
	circleSmall.addEllipse(
	    QRect(r.left() + 5, r.top() + 5, r.width() - 5, r.width() - 5));

	painter.fillPath(circleBig, Qt::red);

	painter.setClipPath(circleSmall);
	painter.drawPixmap(r, ICON);
}
