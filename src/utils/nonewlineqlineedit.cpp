#include "nonewlineqlineedit.h"

NoNewLineQLineEdit::NoNewLineQLineEdit(QWidget* parent)
    : QLineEdit{parent} {}
NoNewLineQLineEdit::NoNewLineQLineEdit(const QString &str, QWidget* parent)
    : QLineEdit(str, parent), hidden{false}, defaultText{str} {setStyleSheet(defaultStyleSheet);}

NoNewLineQLineEdit::NoNewLineQLineEdit(const QString &str, bool pw, QWidget *parent)
    : QLineEdit(str, parent), hidden{pw}, defaultText{str} {setStyleSheet(defaultStyleSheet);}

NoNewLineQLineEdit::~NoNewLineQLineEdit(){}

void NoNewLineQLineEdit::keyPressEvent(QKeyEvent *e)
{

    if(e->key() == Qt::Key_Enter || e->key() == Qt::Key_Return)
    {
        emit enterPressed();
        return;
    }

    if (isDefault)
    {
        setText("");
        setStyleSheet(changedStyleSheet);
        isDefault = false;
        if (hidden) setEchoMode(QLineEdit::Password);
    }
    QLineEdit::keyPressEvent(e);
    if (text().isEmpty())
    {
        setStyleSheet(defaultStyleSheet);
        setText(defaultText);
        isDefault = true;
        setEchoMode(QLineEdit::Normal);
    }
}

void NoNewLineQLineEdit::setPasswordHide(int ckechboxState)
{
    hidden = ckechboxState == Qt::Unchecked && !isDefault;
    setEchoMode(hidden ? QLineEdit::Password: QLineEdit::Normal);
}
