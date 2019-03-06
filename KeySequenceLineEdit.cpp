#include "KeySequenceLineEdit.h"

KeySequenceLineEdit::KeySequenceLineEdit(QWidget* parent) : QLineEdit(parent) {}

KeySequenceLineEdit::KeySequenceLineEdit(const QString& text, QWidget* parent)
    : QLineEdit(text, parent) {}

void KeySequenceLineEdit::keyPressEvent(QKeyEvent* event) {
  if (event->type() == QEvent::KeyPress) {
    auto keyEvent = static_cast<QKeyEvent*>(event);

    int keyInt = keyEvent->key();
    auto key = static_cast<Qt::Key>(keyInt);
    if (key == Qt::Key_unknown) {
      return;
    }
    // the user have clicked just and only the special keys Ctrl, Shift, Alt,
    // Meta.
    if (key == Qt::Key_Control || key == Qt::Key_Shift || key == Qt::Key_Alt ||
        key == Qt::Key_Meta) {
      return;
    }

    // check for a combination of user clicks
    Qt::KeyboardModifiers modifiers = keyEvent->modifiers();
    // if the keyText is empty than it's a special key like F1, F5, ...

    if (modifiers & Qt::ShiftModifier)
      keyInt += Qt::SHIFT;
    if (modifiers & Qt::ControlModifier)
      keyInt += Qt::CTRL;
    if (modifiers & Qt::AltModifier)
      keyInt += Qt::ALT;
    if (modifiers & Qt::MetaModifier)
      keyInt += Qt::META;

    auto newSequence = QKeySequence(keyInt).toString();
    this->setText(newSequence);
  }
}
