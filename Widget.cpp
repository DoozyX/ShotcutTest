#include "Widget.h"

#include <QDebug>
#include <QSettings>

#include "ui_Widget.h"

Widget::Widget(QWidget* parent) : QWidget(parent), ui(new Ui::Widget) {
  ui->setupUi(this);

  auto setShortcut = [=](QSettings* settings, QShortcut* shortcut,
                         QLineEdit* lineEdit, const QString& key,
                         const QString& defaultValue, void (Widget::*slot)()) {
    auto shotcutValue = settings->value(key, defaultValue).toString();
    lineEdit->setText(shotcutValue);
    connect(lineEdit, &QLineEdit::textChanged, this, [=]() {
      shortcut->setKey(lineEdit->text());
      settings->setValue("shortcuts/" + key, lineEdit->text());
    });
    shortcut->setKey(shotcutValue);
    connect(shortcut, &QShortcut::activated, this, slot);
  };

  settings.beginGroup("shortcuts");

  setShortcut(&settings, &openCloseMainNavigationShortcut,
              ui->openCloseMainNavigationLineEdit, "openCloseMainNavigation",
              "Alt+Ctrl+F9", &Widget::onOpenCloseMainNavigation);

  setShortcut(&settings, &openCloseCallMonitorShortcut,
              ui->openCloseCallMonitorLineEdit, "openCloseCallMonitor",
              "Alt+Ctrl+F10", &Widget::onOpenCloseCallMonitor);

  setShortcut(&settings, &openCloseDetailWindowShortcut,
              ui->openCloseDetailWindowLineEdit, "openCloseDetailWindow",
              "Alt+Ctrl+F11", &Widget::onOpenCloseDetailWindow);

  setShortcut(&settings, &openCloseAllWindowsShortcut,
              ui->openCloseAllWindowsLineEdit, "openCloseAllWindows",
              "Alt+Ctrl+Space", &Widget::onOpenCloseAllWindows);

  setShortcut(&settings, &openHelpShortcut, ui->openHelpLineEdit, "openHelp",
              "Ctrl+F1", &Widget::onOpenHelp);

  setShortcut(&settings, &openPhoneSettingsShortcut, ui->openPhoneLineEdit,
              "openPhoneSettings", "Ctrl+F2", &Widget::onOpenPhoneSettings);

  setShortcut(&settings, &openContactsShortcut, ui->openContactsLineEdit,
              "openContactsValue", "Ctrl+F3", &Widget::onOpenContacts);

  setShortcut(&settings, &openCallHistoryShortcut, ui->openCallHisotryLineEdit,
              "openCallHistory", "Ctrl+F4", &Widget::onOpenCallHistory);

  setShortcut(&settings, &holdUnholdCallShortcut, ui->holdUnholdCallLineEdit,
              "holdUnholdCall", "Ctrl+F5", &Widget::onHoldUnholdCall);

  setShortcut(&settings, &startStopCallRecordingShortcut,
              ui->startStopCallRecordingLineEdit, "startStopCallRecording",
              "Alt+Ctrl+O", &Widget::onStartStopCallRecording);

  setShortcut(&settings, &takeCallShortcut, ui->takeCallLineEdit, "takeCall",
              "Alt+PgUp", &Widget::onTakeCall);

  setShortcut(&settings, &hangUpCallShortcut, ui->hangUpCallLineEdit,
              "hangUpCall", "Alt+PgDown", &Widget::onHangUpCall);

  setShortcut(&settings, &redialLastPhoneNumberShortcut,
              ui->redialLastPhoneNumberLineEdit, "redialLastPhoneNumber",
              "Alt+Ctrl+R", &Widget::onRedialLastPhoneNumber);

  setShortcut(&settings, &muteOnOffShortcut, ui->muteOnOffLineEdit, "muteOnOff",
              "Alt+Ctrl+M", &Widget::onMuteOnOff);

  setShortcut(&settings, &dialSelectedAreaShortcut,
              ui->dialSelectedAreaLineEdit, "dialSelectedArea", "PAUSE",
              &Widget::onDialSelectedArea);

  setShortcut(&settings, &turnUpMicrophoneShortcut,
              ui->turnUpMicrophoneLineEdit, "turnUpMicrophone",
              "Alt+Ctrl+Right", &Widget::onTurnUpMicrophone);

  setShortcut(&settings, &turnDownMicrophoneShortcut,
              ui->turnDownMicrophoneLineEdit, "turnDownMicrophone",
              "Alt+Ctrl+Left", &Widget::onTurnDownMicrophone);

  setShortcut(&settings, &turnUpSpeakerShortcut, ui->turnUpSpeakerLineEdit,
              "turnUpSpeaker", "Alt+Ctrl+Up", &Widget::onTurnUpSpeaker);

  setShortcut(&settings, &turnDownSpeakerShortcut, ui->turnDownSpeakerLineEdit,
              "turnDownSpeaker", "Alt+Ctrl+Down", &Widget::onTurnDownSpeaker);

  settings.endGroup();
}

Widget::~Widget() {
  delete ui;
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
