#include "button.h"

button::button(const QString &text, QWidget *parent) : QToolButton(parent) {
    setText(text);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
}
