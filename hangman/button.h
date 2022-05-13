#ifndef BUTTON_H
#define BUTTON_H

#include <QToolButton>

class button : public QToolButton
{
    Q_OBJECT
public:
    explicit button(const QString &text, QWidget *parent = nullptr);
};

#endif // BUTTON_H
