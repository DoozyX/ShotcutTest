#pragma once

#include <QSettings>
#include <QShortcut>
#include <QWidget>

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
  QSettings settings;

  QList<QShortcut*> shortcutList;
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

  void enableShortcuts(bool enabled);

 private slots:
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
