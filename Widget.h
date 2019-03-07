#pragma once

#include <QSettings>
#include <QShortcut>
#include <QWidget>

#include "KeySequenceLineEdit.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget {
  Q_OBJECT

 public:
  explicit Widget(QWidget* parent = nullptr);
  ~Widget();

 private:
  Ui::Widget* ui;
  QSettings mSettings;

  QList<KeySequenceLineEdit*> mShortcutEditList;
  QList<QShortcut*> mShortcutList;
  enum ShortcutList {
    OpenCloseMainNavigationShortcut,
    OpenCloseCallMonitorShortcut,
    OpenCloseDetailWindowShortcut,
    OpenCloseAllWindowsShortcut,
    OpenHelpShortcut,
    OpenPhoneSettingsShortcut,
    OpenContactsShortcut,
    OpenCallHistoryShortcut,
    HoldUnholdCallShortcut,
    StartStopCallRecordingShortcut,
    TakeCallShortcut,
    HangUpCallShortcut,
    RedialLastPhoneNumberShortcut,
    MuteOnOffShortcut,
    DialSelectedAreaShortcut,
    TurnUpMicrophoneShortcut,
    TurnDownMicrophoneShortcut,
    TurnUpSpeakerShortcut,
    TurnDownSpeakerShortcut,
    LAST
  };

  QMap<QShortcut*, KeySequenceLineEdit*> mChangedValues;

  void enableShortcuts(bool enabled);
  void saveChangedShortcuts();
  void discardChangedShortcuts();
  bool shortcutExists(const QString& shortcut);

 private slots:
  void on_okButton_clicked();
  void on_applyButton_clicked();
  void on_cancelButton_clicked();

  void onOpenCloseMainNavigation();
  void onOpenCloseCallMonitor();
  void onOpenCloseDetailWindow();
  void onOpenCloseAllWindows();
  void onOpenHelp();
  void onOpenPhoneSettings();
  void onOpenContacts();
  void onOpenCallHistory();
  void onHoldUnholdCall();
  void onStartStopCallRecording();
  void onTakeCall();
  void onHangUpCall();
  void onRedialLastPhoneNumber();
  void onMuteOnOff();
  void onDialSelectedArea();
  void onTurnUpMicrophone();
  void onTurnDownMicrophone();
  void onTurnUpSpeaker();
  void onTurnDownSpeaker();
};
