#include "Widget.h"

#include <QDebug>
#include <QMessageBox>
#include <QSettings>

#include "ui_Widget.h"

Widget::Widget(QWidget* parent) : QWidget(parent), ui(new Ui::Widget) {
  ui->setupUi(this);

  auto setShortcut = [=](QSettings* settings, QShortcut* shortcut,
                         KeySequenceLineEdit* lineEdit, const QString& key,
                         const QString& defaultValue, void (Widget::*slot)()) {
    mShortcutEditList.append(lineEdit);
    auto shotcutValue = settings->value(key, defaultValue).toString();
    lineEdit->setText(shotcutValue);
    connect(lineEdit, &KeySequenceLineEdit::keySequencePressed, this,
            [=](const QString& keySquence) {
              if (this->shortcutExists(keySquence)) {
                QMessageBox::warning(this, tr("Shortcut exists!"),
                                     tr("New shortcut already exist.\nPlease "
                                        "record other shortcut."));
              } else {
                lineEdit->setText(keySquence);
                mChangedValues[shortcut] = lineEdit;
              }
            });
    connect(lineEdit, &KeySequenceLineEdit::focusChanged, this,
            [=](bool focus) { this->enableShortcuts(!focus); });
    shortcut->setKey(shotcutValue);
    shortcut->setObjectName("shortcuts/" + key);
    connect(shortcut, &QShortcut::activated, this, slot);
  };

  for (auto i = 0; i < ShortcutList::LAST; ++i) {
    mShortcutList.append(new QShortcut(this));
  }

  mSettings.beginGroup("shortcuts");

  setShortcut(&mSettings,
              mShortcutList[ShortcutList::OpenCloseMainNavigationShortcut],
              ui->openCloseMainNavigationLineEdit, "openCloseMainNavigation",
              "Alt+Ctrl+F9", &Widget::onOpenCloseMainNavigation);

  setShortcut(&mSettings,
              mShortcutList[ShortcutList::OpenCloseCallMonitorShortcut],
              ui->openCloseCallMonitorLineEdit, "openCloseCallMonitor",
              "Alt+Ctrl+F10", &Widget::onOpenCloseCallMonitor);

  setShortcut(&mSettings,
              mShortcutList[ShortcutList::OpenCloseDetailWindowShortcut],
              ui->openCloseDetailWindowLineEdit, "openCloseDetailWindow",
              "Alt+Ctrl+F11", &Widget::onOpenCloseDetailWindow);

  setShortcut(&mSettings,
              mShortcutList[ShortcutList::OpenCloseAllWindowsShortcut],
              ui->openCloseAllWindowsLineEdit, "openCloseAllWindows",
              "Alt+Ctrl+Space", &Widget::onOpenCloseAllWindows);

  setShortcut(&mSettings, mShortcutList[ShortcutList::OpenHelpShortcut],
              ui->openHelpLineEdit, "openHelp", "Ctrl+F1", &Widget::onOpenHelp);

  setShortcut(&mSettings,
              mShortcutList[ShortcutList::OpenPhoneSettingsShortcut],
              ui->openPhoneLineEdit, "openPhoneSettings", "Ctrl+F2",
              &Widget::onOpenPhoneSettings);

  setShortcut(&mSettings, mShortcutList[ShortcutList::OpenContactsShortcut],
              ui->openContactsLineEdit, "openContactsValue", "Ctrl+F3",
              &Widget::onOpenContacts);

  setShortcut(&mSettings, mShortcutList[ShortcutList::OpenCallHistoryShortcut],
              ui->openCallHisotryLineEdit, "openCallHistory", "Ctrl+F4",
              &Widget::onOpenCallHistory);

  setShortcut(&mSettings, mShortcutList[ShortcutList::HoldUnholdCallShortcut],
              ui->holdUnholdCallLineEdit, "holdUnholdCall", "Ctrl+F5",
              &Widget::onHoldUnholdCall);

  setShortcut(&mSettings,
              mShortcutList[ShortcutList::StartStopCallRecordingShortcut],
              ui->startStopCallRecordingLineEdit, "startStopCallRecording",
              "Alt+Ctrl+O", &Widget::onStartStopCallRecording);

  setShortcut(&mSettings, mShortcutList[ShortcutList::TakeCallShortcut],
              ui->takeCallLineEdit, "takeCall", "Alt+PgUp",
              &Widget::onTakeCall);

  setShortcut(&mSettings, mShortcutList[ShortcutList::HangUpCallShortcut],
              ui->hangUpCallLineEdit, "hangUpCall", "Alt+PgDown",
              &Widget::onHangUpCall);

  setShortcut(&mSettings,
              mShortcutList[ShortcutList::RedialLastPhoneNumberShortcut],
              ui->redialLastPhoneNumberLineEdit, "redialLastPhoneNumber",
              "Alt+Ctrl+R", &Widget::onRedialLastPhoneNumber);

  setShortcut(&mSettings, mShortcutList[ShortcutList::MuteOnOffShortcut],
              ui->muteOnOffLineEdit, "muteOnOff", "Alt+Ctrl+M",
              &Widget::onMuteOnOff);

  setShortcut(&mSettings, mShortcutList[ShortcutList::DialSelectedAreaShortcut],
              ui->dialSelectedAreaLineEdit, "dialSelectedArea", "PAUSE",
              &Widget::onDialSelectedArea);

  setShortcut(&mSettings, mShortcutList[ShortcutList::TurnUpMicrophoneShortcut],
              ui->turnUpMicrophoneLineEdit, "turnUpMicrophone",
              "Alt+Ctrl+Right", &Widget::onTurnUpMicrophone);

  setShortcut(&mSettings,
              mShortcutList[ShortcutList::TurnDownMicrophoneShortcut],
              ui->turnDownMicrophoneLineEdit, "turnDownMicrophone",
              "Alt+Ctrl+Left", &Widget::onTurnDownMicrophone);

  setShortcut(&mSettings, mShortcutList[ShortcutList::TurnUpSpeakerShortcut],
              ui->turnUpSpeakerLineEdit, "turnUpSpeaker", "Alt+Ctrl+Up",
              &Widget::onTurnUpSpeaker);

  setShortcut(&mSettings, mShortcutList[ShortcutList::TurnDownSpeakerShortcut],
              ui->turnDownSpeakerLineEdit, "turnDownSpeaker", "Alt+Ctrl+Down",
              &Widget::onTurnDownSpeaker);

  mSettings.endGroup();

  ui->cancelButton->setFocus();
}

Widget::~Widget() {
  delete ui;
}

void Widget::enableShortcuts(const bool enabled) {
  for (auto shortcut : mShortcutList) {
    shortcut->setEnabled(enabled);
  }
}

void Widget::saveChangedShortcuts() {
  QMapIterator<QShortcut*, KeySequenceLineEdit*> changedValue(mChangedValues);
  while (changedValue.hasNext()) {
    changedValue.next();
    auto shortcut = changedValue.key();
    auto lineEdit = changedValue.value();
    auto value = lineEdit->text();
    shortcut->setKey(value);
    mSettings.setValue(shortcut->objectName(), value);
  }
  mChangedValues.clear();
}

void Widget::discardChangedShortcuts() {
  QMapIterator<QShortcut*, KeySequenceLineEdit*> changedValue(mChangedValues);
  while (changedValue.hasNext()) {
    changedValue.next();
    auto shortcut = changedValue.key();
    auto lineEdit = changedValue.value();
    lineEdit->setText(shortcut->key().toString());
  }
  mChangedValues.clear();
}

bool Widget::shortcutExists(const QString& shortcut) {
  for (auto lineEdit : mShortcutEditList) {
    if (lineEdit->text() == shortcut) {
      return true;
    }
  }
  return false;
}

void Widget::on_okButton_clicked() {
  saveChangedShortcuts();
  // TODO: close window?
}

void Widget::on_applyButton_clicked() {
  saveChangedShortcuts();
}

void Widget::on_cancelButton_clicked() {
  discardChangedShortcuts();
  // TODO: close window?
}

void Widget::onOpenCloseMainNavigation() {
  qDebug() << "handle " << Q_FUNC_INFO;
}

void Widget::onOpenCloseCallMonitor() {
  qDebug() << "handle " << Q_FUNC_INFO;
}

void Widget::onOpenCloseDetailWindow() {
  qDebug() << "handle " << Q_FUNC_INFO;
}

void Widget::onOpenCloseAllWindows() {
  qDebug() << "handle " << Q_FUNC_INFO;
}

void Widget::onOpenHelp() {
  qDebug() << "handle " << Q_FUNC_INFO;
}

void Widget::onOpenPhoneSettings() {
  qDebug() << "handle " << Q_FUNC_INFO;
}

void Widget::onOpenContacts() {
  qDebug() << "handle " << Q_FUNC_INFO;
}

void Widget::onOpenCallHistory() {
  qDebug() << "handle " << Q_FUNC_INFO;
}

void Widget::onHoldUnholdCall() {
  qDebug() << "handle " << Q_FUNC_INFO;
}

void Widget::onStartStopCallRecording() {
  qDebug() << "handle " << Q_FUNC_INFO;
}

void Widget::onTakeCall() {
  qDebug() << "handle " << Q_FUNC_INFO;
}

void Widget::onHangUpCall() {
  qDebug() << "handle " << Q_FUNC_INFO;
}

void Widget::onRedialLastPhoneNumber() {
  qDebug() << "handle " << Q_FUNC_INFO;
}

void Widget::onMuteOnOff() {
  qDebug() << "handle " << Q_FUNC_INFO;
}

void Widget::onDialSelectedArea() {
  qDebug() << "handle " << Q_FUNC_INFO;
}

void Widget::onTurnUpMicrophone() {
  qDebug() << "handle " << Q_FUNC_INFO;
}

void Widget::onTurnDownMicrophone() {
  qDebug() << "handle " << Q_FUNC_INFO;
}

void Widget::onTurnUpSpeaker() {
  qDebug() << "handle " << Q_FUNC_INFO;
}

void Widget::onTurnDownSpeaker() {
  qDebug() << "handle " << Q_FUNC_INFO;
}
