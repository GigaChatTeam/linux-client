#pragma once

#include <QKeyEvent>
#include <QLineEdit>
#include <QObject>

#include <QPainter>

class NoNewLineQLineEdit : public QLineEdit
{
	Q_OBJECT
public:
	NoNewLineQLineEdit(QWidget *parent);
	NoNewLineQLineEdit(const QString &str, QWidget *parent);
	NoNewLineQLineEdit(const QString &str, bool pw, QWidget *parent);
	~NoNewLineQLineEdit();

	bool	hidden;
	bool	isDefault = true;
	QString defaultText;

	const QString defaultStyleSheet = QString("color: #888888"),
		      changedStyleSheet = QString("color: #000000");

protected:
	void keyPressEvent(QKeyEvent *e) override;
signals:
	void enterPressed();
public slots:
	void setPasswordHide(int ckechboxState);
};
