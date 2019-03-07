#ifndef KEYSEQUENCELINEEDIT_H
#define KEYSEQUENCELINEEDIT_H

#include <QDebug>
#include <QKeyEvent>
#include <QKeySequence>
#include <QLineEdit>

class KeySequenceLineEdit : public QLineEdit {
  Q_OBJECT
 public:
  explicit KeySequenceLineEdit(QWidget* parent = nullptr);
  explicit KeySequenceLineEdit(const QString&, QWidget* parent = nullptr);

  void keyPressEvent(QKeyEvent* event) override;

 protected:
  void focusInEvent(QFocusEvent* event) override;
  void focusOutEvent(QFocusEvent* event) override;

 signals:
  void focusChanged(bool focus);
  void keySequencePressed(const QString& keySequence);
};

#endif  // KEYSEQUENCELINEEDIT_H
