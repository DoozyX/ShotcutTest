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

  // TODO: replace shortcut parent to be app?
  QShortcut openCloseMainNavigationShortcut{this};
  QShortcut openCloseCallMonitorShortcut{this};
  QShortcut openCloseDetailWindowShortcut{this};
  QShortcut openCloseAllWindowsShortcut{this};
  QShortcut openHelpShortcut{this};
  QShortcut openPhoneSettingsShortcut{this};
  QShortcut openContactsShortcut{this};
  QShortcut openCallHistoryShortcut{this};
  QShortcut holdUnholdCallShortcut{this};
  QShortcut startStopCallRecordingShortcut{this};
  QShortcut takeCallShortcut{this};
  QShortcut hangUpCallShortcut{this};
  QShortcut redialLastPhoneNumberShortcut{this};
  QShortcut muteOnOffShortcut{this};
  QShortcut dialSelectedAreaShortcut{this};
  QShortcut turnUpMicrophoneShortcut{this};
  QShortcut turnDownMicrophoneShortcut{this};
  QShortcut turnUpSpeakerShortcut{this};
  QShortcut turnDownSpeakerShortcut{this};

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
