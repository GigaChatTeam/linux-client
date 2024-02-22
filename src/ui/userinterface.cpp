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

#include "ui/userinterface.hpp"

void UserInterface::constructWindowArray()
{
	tabs = {std::make_tuple(QIcon(":resources/icon1.png"),
				"Tab with scrolling windows",
				new ScrollingWidget(this)),
		std::make_tuple(QIcon(":resources/icon2.png"),
				"Tab that is actually twitch",
				new GridScrollingWidget(this)),
		std::make_tuple(QIcon(":resources/icon3.png"),
				"Tab that i don't know what the...",
				new UndefinedPage(this))};
}
void UserInterface::constructTabWidget()
{
	for (const auto &[Icon, Title, Widget] : tabs)
		addTab(Widget, Icon, Title);
	setTabPosition(TabPosition::South);
	setElideMode(Qt::ElideMiddle);
}

UserInterface::UserInterface(QWidget *parent) : QTabWidget{parent}
{
	constructWindowArray();
	constructTabWidget();
}

UserInterface::~UserInterface() { DEBUG("DELETET USERINTERFACE: " << this); }
