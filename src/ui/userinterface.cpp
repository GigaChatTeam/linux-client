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
