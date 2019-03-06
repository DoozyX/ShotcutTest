#ifndef KEYSEQUENCELINEEDIT_H
#define KEYSEQUENCELINEEDIT_H

#include <QDebug>
#include <QKeyEvent>
#include <QKeySequence>
#include <QLineEdit>

class KeySequenceLineEdit : public QLineEdit {
 public:
  explicit KeySequenceLineEdit(QWidget* parent = nullptr);
  explicit KeySequenceLineEdit(const QString&, QWidget* parent = nullptr);

  void keyPressEvent(QKeyEvent* event) override;
};

#endif  // KEYSEQUENCELINEEDIT_H
