#include "Widget.h"

#include <QDebug>
#include <QSettings>

#include "ui_Widget.h"

Widget::Widget(QWidget* parent) : QWidget(parent), ui(new Ui::Widget) {
  ui->setupUi(this);

  auto setShortcut = [=](QSettings* settings, QShortcut* shortcut,
                         KeySequenceLineEdit* lineEdit, const QString& key,
                         const QString& defaultValue, void (Widget::*slot)()) {
    auto shotcutValue = settings->value(key, defaultValue).toString();
    lineEdit->setText(shotcutValue);
    connect(lineEdit, &QLineEdit::textChanged, this, [=]() {
      shortcut->setKey(lineEdit->text());
      settings->setValue("shortcuts/" + key, lineEdit->text());
    });
    connect(lineEdit, &KeySequenceLineEdit::focusChanged, this,
            [=](bool focus) {
              qDebug() << "focus changed" << focus;
              this->enableShortcuts(!focus);
            });
    shortcut->setKey(shotcutValue);
    connect(shortcut, &QShortcut::activated, this, slot);
  };

  for (auto i = 0; i < ShortcutList::LAST; ++i) {
    shortcutList.append(new QShortcut(this));
  }

  settings.beginGroup("shortcuts");

  setShortcut(&settings,
              shortcutList[ShortcutList::OpenCloseMainNavigationShortcut],
              ui->openCloseMainNavigationLineEdit, "openCloseMainNavigation",
              "Alt+Ctrl+F9", &Widget::onOpenCloseMainNavigation);

  setShortcut(&settings,
              shortcutList[ShortcutList::OpenCloseCallMonitorShortcut],
              ui->openCloseCallMonitorLineEdit, "openCloseCallMonitor",
              "Alt+Ctrl+F10", &Widget::onOpenCloseCallMonitor);

  setShortcut(&settings,
              shortcutList[ShortcutList::OpenCloseDetailWindowShortcut],
              ui->openCloseDetailWindowLineEdit, "openCloseDetailWindow",
              "Alt+Ctrl+F11", &Widget::onOpenCloseDetailWindow);

  setShortcut(&settings,
              shortcutList[ShortcutList::OpenCloseAllWindowsShortcut],
              ui->openCloseAllWindowsLineEdit, "openCloseAllWindows",
              "Alt+Ctrl+Space", &Widget::onOpenCloseAllWindows);

  setShortcut(&settings, shortcutList[ShortcutList::OpenHelpShortcut],
              ui->openHelpLineEdit, "openHelp", "Ctrl+F1", &Widget::onOpenHelp);

  setShortcut(&settings, shortcutList[ShortcutList::OpenPhoneSettingsShortcut],
              ui->openPhoneLineEdit, "openPhoneSettings", "Ctrl+F2",
              &Widget::onOpenPhoneSettings);

  setShortcut(&settings, shortcutList[ShortcutList::OpenContactsShortcut],
              ui->openContactsLineEdit, "openContactsValue", "Ctrl+F3",
              &Widget::onOpenContacts);

  setShortcut(&settings, shortcutList[ShortcutList::OpenCallHistoryShortcut],
              ui->openCallHisotryLineEdit, "openCallHistory", "Ctrl+F4",
              &Widget::onOpenCallHistory);

  setShortcut(&settings, shortcutList[ShortcutList::HoldUnholdCallShortcut],
              ui->holdUnholdCallLineEdit, "holdUnholdCall", "Ctrl+F5",
              &Widget::onHoldUnholdCall);

  setShortcut(&settings,
              shortcutList[ShortcutList::StartStopCallRecordingShortcut],
              ui->startStopCallRecordingLineEdit, "startStopCallRecording",
              "Alt+Ctrl+O", &Widget::onStartStopCallRecording);

  setShortcut(&settings, shortcutList[ShortcutList::TakeCallShortcut],
              ui->takeCallLineEdit, "takeCall", "Alt+PgUp",
              &Widget::onTakeCall);

  setShortcut(&settings, shortcutList[ShortcutList::HangUpCallShortcut],
              ui->hangUpCallLineEdit, "hangUpCall", "Alt+PgDown",
              &Widget::onHangUpCall);

  setShortcut(&settings,
              shortcutList[ShortcutList::RedialLastPhoneNumberShortcut],
              ui->redialLastPhoneNumberLineEdit, "redialLastPhoneNumber",
              "Alt+Ctrl+R", &Widget::onRedialLastPhoneNumber);

  setShortcut(&settings, shortcutList[ShortcutList::MuteOnOffShortcut],
              ui->muteOnOffLineEdit, "muteOnOff", "Alt+Ctrl+M",
              &Widget::onMuteOnOff);

  setShortcut(&settings, shortcutList[ShortcutList::DialSelectedAreaShortcut],
              ui->dialSelectedAreaLineEdit, "dialSelectedArea", "PAUSE",
              &Widget::onDialSelectedArea);

  setShortcut(&settings, shortcutList[ShortcutList::TurnUpMicrophoneShortcut],
              ui->turnUpMicrophoneLineEdit, "turnUpMicrophone",
              "Alt+Ctrl+Right", &Widget::onTurnUpMicrophone);

  setShortcut(&settings, shortcutList[ShortcutList::TurnDownMicrophoneShortcut],
              ui->turnDownMicrophoneLineEdit, "turnDownMicrophone",
              "Alt+Ctrl+Left", &Widget::onTurnDownMicrophone);

  setShortcut(&settings, shortcutList[ShortcutList::TurnUpSpeakerShortcut],
              ui->turnUpSpeakerLineEdit, "turnUpSpeaker", "Alt+Ctrl+Up",
              &Widget::onTurnUpSpeaker);

  setShortcut(&settings, shortcutList[ShortcutList::TurnDownSpeakerShortcut],
              ui->turnDownSpeakerLineEdit, "turnDownSpeaker", "Alt+Ctrl+Down",
              &Widget::onTurnDownSpeaker);

  settings.endGroup();
}

Widget::~Widget() {
  delete ui;
}

void Widget::enableShortcuts(const bool enabled) {
  for (auto shortcut : shortcutList) {
    shortcut->setEnabled(enabled);
  }
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
