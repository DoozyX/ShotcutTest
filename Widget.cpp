#include "Widget.h"

#include <QDebug>
#include <QMessageBox>
#include <QSettings>

#include "ui_Widget.h"

Widget::Widget(QWidget* parent) : QWidget(parent), ui(new Ui::Widget) {
  ui->setupUi(this);

  mHotkeyManager = new UGlobalHotkeys();
  auto setupShortcut = [=](QSettings* settings, ShortcutList shortcutId,
                           KeySequenceLineEdit* lineEdit,
                           const QString& defaultValue,
                           std::function<void(Widget&)> slot) {
    mShortcutEditList.append(lineEdit);
    auto key = this->shortcutListToString(shortcutId);
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
                mChangedValues[shortcutId] = lineEdit;
              }
            });
    connect(lineEdit, &KeySequenceLineEdit::focusChanged, this,
            [=](bool focus) { this->enableShortcuts(!focus); });
    mHotkeyManager->registerHotkey(shotcutValue, shortcutId);
    mShortcutValueList[shortcutId] = shotcutValue;
    mShortcutSlots[shortcutId] = slot;
  };

  mSettings.beginGroup("shortcuts");

  setupShortcut(&mSettings, ShortcutList::OpenCloseMainNavigation,
                ui->openCloseMainNavigationLineEdit, "Alt+Ctrl+F9",
                &Widget::onOpenCloseMainNavigation);

  setupShortcut(&mSettings, ShortcutList::OpenCloseCallMonitor,
                ui->openCloseCallMonitorLineEdit, "Alt+Ctrl+F10",
                &Widget::onOpenCloseCallMonitor);

  setupShortcut(&mSettings, ShortcutList::OpenCloseDetailWindow,
                ui->openCloseDetailWindowLineEdit, "Alt+Ctrl+F11",
                &Widget::onOpenCloseDetailWindow);

  setupShortcut(&mSettings, ShortcutList::OpenCloseAllWindows,
                ui->openCloseAllWindowsLineEdit, "Alt+Ctrl+Space",
                &Widget::onOpenCloseAllWindows);

  setupShortcut(&mSettings, ShortcutList::OpenHelp, ui->openHelpLineEdit,
                "Ctrl+F1", &Widget::onOpenHelp);

  setupShortcut(&mSettings, ShortcutList::OpenPhoneSettings,
                ui->openPhoneLineEdit, "Ctrl+F2", &Widget::onOpenPhoneSettings);

  setupShortcut(&mSettings, ShortcutList::OpenContacts,
                ui->openContactsLineEdit, "Ctrl+F3", &Widget::onOpenContacts);

  setupShortcut(&mSettings, ShortcutList::OpenCallHistory,
                ui->openCallHisotryLineEdit, "Ctrl+F4",
                &Widget::onOpenCallHistory);

  setupShortcut(&mSettings, ShortcutList::HoldUnholdCall,
                ui->holdUnholdCallLineEdit, "Ctrl+F5",
                &Widget::onHoldUnholdCall);

  setupShortcut(&mSettings, ShortcutList::StartStopCallRecording,
                ui->startStopCallRecordingLineEdit, "Alt+Ctrl+O",
                &Widget::onStartStopCallRecording);

  setupShortcut(&mSettings, ShortcutList::TakeCall, ui->takeCallLineEdit,
                "Alt+PgUp", &Widget::onTakeCall);

  setupShortcut(&mSettings, ShortcutList::HangUpCall, ui->hangUpCallLineEdit,
                "Alt+PgDown", &Widget::onHangUpCall);

  setupShortcut(&mSettings, ShortcutList::RedialLastPhoneNumber,
                ui->redialLastPhoneNumberLineEdit, "Alt+Ctrl+R",
                &Widget::onRedialLastPhoneNumber);

  setupShortcut(&mSettings, ShortcutList::MuteOnOff, ui->muteOnOffLineEdit,
                "Alt+Ctrl+M", &Widget::onMuteOnOff);

  setupShortcut(&mSettings, ShortcutList::DialSelectedArea,
                ui->dialSelectedAreaLineEdit, "PAUSE",
                &Widget::onDialSelectedArea);

  setupShortcut(&mSettings, ShortcutList::TurnUpMicrophone,
                ui->turnUpMicrophoneLineEdit, "Alt+Ctrl+Right",
                &Widget::onTurnUpMicrophone);

  setupShortcut(&mSettings, ShortcutList::TurnDownMicrophone,
                ui->turnDownMicrophoneLineEdit, "Alt+Ctrl+Left",
                &Widget::onTurnDownMicrophone);

  setupShortcut(&mSettings, ShortcutList::TurnUpSpeaker,
                ui->turnUpSpeakerLineEdit, "Alt+Ctrl+Up",
                &Widget::onTurnUpSpeaker);

  setupShortcut(&mSettings, ShortcutList::TurnDownSpeaker,
                ui->turnDownSpeakerLineEdit, "Alt+Ctrl+Down",
                &Widget::onTurnDownSpeaker);

  mSettings.endGroup();

  connect(mHotkeyManager, &UGlobalHotkeys::activated,
          [=](size_t id) { mShortcutSlots[id](*this); });

  ui->cancelButton->setFocus();
}

Widget::~Widget() {
  delete ui;
}

QString Widget::shortcutListToString(Widget::ShortcutList shortcut) {
  return QVariant::fromValue(shortcut).toString();
}

void Widget::enableShortcuts(const bool enabled) {
  if (enabled) {
    QMapIterator<size_t, QString> shortcuts(mShortcutValueList);
    while (shortcuts.hasNext()) {
      shortcuts.next();
      auto shortcutID = shortcuts.key();
      auto shortcutValue = shortcuts.value();
      mHotkeyManager->registerHotkey(shortcutValue, shortcutID);
    }
  } else {
    mHotkeyManager->unregisterAllHotkeys();
  }
}

void Widget::saveChangedShortcuts() {
  QMapIterator<size_t, KeySequenceLineEdit*> changedValue(mChangedValues);
  while (changedValue.hasNext()) {
    changedValue.next();
    auto shortcut = changedValue.key();
    auto lineEdit = changedValue.value();
    auto value = lineEdit->text();
    auto key = shortcutListToString(static_cast<ShortcutList>(shortcut));
    mHotkeyManager->registerHotkey(value, shortcut);
    mSettings.setValue("shortcuts/" + key, value);
  }
  mChangedValues.clear();
}

void Widget::discardChangedShortcuts() {
  QMapIterator<size_t, KeySequenceLineEdit*> changedValue(mChangedValues);
  while (changedValue.hasNext()) {
    changedValue.next();
    auto shortcut = changedValue.key();
    auto lineEdit = changedValue.value();
    lineEdit->setText(mShortcutValueList[shortcut]);
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
