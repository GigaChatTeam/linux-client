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

// custom widgets
#include "ui/mainwidgets/gridscrollingwidget.hpp"
#include "ui/mainwidgets/messanger.hpp"
#include "ui/mainwidgets/undefinedpage.hpp"

#include <QObject>

// utility
#include <QString>
#include <array>
#include <tuple>
#include <utility>

// widgets
#include <QTabWidget>
#include <QWidget>

class UserInterface : public QTabWidget
{
	Q_OBJECT

public:
	typedef std::tuple<QIcon, QString, QWidget *> window_type;

	std::array<window_type, 3> tabs;

	void constructWindowArray();
	void constructTabWidget();
	explicit UserInterface(QWidget *parent = nullptr);
	~UserInterface();
};
