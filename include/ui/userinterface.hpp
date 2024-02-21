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
