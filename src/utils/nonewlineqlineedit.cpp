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

#include "utils/nonewlineqlineedit.hpp"

NoNewLineQLineEdit::NoNewLineQLineEdit(QWidget *parent) : QLineEdit{parent} {}
NoNewLineQLineEdit::NoNewLineQLineEdit(const QString &str, QWidget *parent)
    : QLineEdit(str, parent), hidden{false}, defaultText{str}
{
	setStyleSheet(defaultStyleSheet);
}

NoNewLineQLineEdit::NoNewLineQLineEdit(const QString &str,
				       bool	      pw,
				       QWidget	     *parent)
    : QLineEdit(str, parent), hidden{pw}, defaultText{str}
{
	setStyleSheet(defaultStyleSheet);
}

NoNewLineQLineEdit::~NoNewLineQLineEdit() {}

void NoNewLineQLineEdit::keyPressEvent(QKeyEvent *e)
{
	if (e->key() == Qt::Key_Enter || e->key() == Qt::Key_Return) {
		emit enterPressed();
		return;
	}

	if (isDefault) {
		setText("");
		setStyleSheet(changedStyleSheet);
		isDefault = false;
		if (hidden) setEchoMode(QLineEdit::Password);
	}
	QLineEdit::keyPressEvent(e);
	if (text().isEmpty()) {
		setStyleSheet(defaultStyleSheet);
		setText(defaultText);
		isDefault = true;
		setEchoMode(QLineEdit::Normal);
	}
}

void NoNewLineQLineEdit::setPasswordHide(int ckechboxState)
{
	hidden = ckechboxState == Qt::Unchecked && !isDefault;
	setEchoMode(hidden ? QLineEdit::Password : QLineEdit::Normal);
}
