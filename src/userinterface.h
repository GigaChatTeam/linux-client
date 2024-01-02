#pragma once

// custom widgets
#include "mainwidgets/gridscrollingwidget.h"
#include "mainwidgets/messanger.h"
#include "mainwidgets/undefinedpage.h"

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
