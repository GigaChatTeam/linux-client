#pragma once

#include <QLineEdit>
#include <QKeyEvent>
#include <QObject>

#include <QPainter>

class NoNewLineQLineEdit : public QLineEdit
{
    Q_OBJECT
public:
    NoNewLineQLineEdit(QWidget* parent);
    NoNewLineQLineEdit(const QString &str, QWidget* parent = nullptr);
    NoNewLineQLineEdit(const QString &str, bool pw, QWidget* parent = nullptr);
    ~NoNewLineQLineEdit();

    bool hidden;
    QString defaultText;

    const QString defaultStyleSheet = QString("color: #888888"),
                  changedStyleSheet = QString("color: #000000");

    inline bool isDefault()
    {
        return defaultText == text();
    }

protected:
    void keyPressEvent(QKeyEvent *e) override;
signals:
    void enterPressed();
public slots:
    void setPasswordHide(int ckechboxState);
};

