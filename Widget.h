#pragma once

#include <QSettings>
#include <QShortcut>
#include <QWidget>

#include "KeySequenceLineEdit.h"
#include "uglobalhotkeys.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget {
  Q_OBJECT

 public:
  enum ShortcutList {
    OpenCloseMainNavigation,
    OpenCloseCallMonitor,
    OpenCloseDetailWindow,
    OpenCloseAllWindows,
    OpenHelp,
    OpenPhoneSettings,
    OpenContacts,
    OpenCallHistory,
    HoldUnholdCall,
    StartStopCallRecording,
    TakeCall,
    HangUpCall,
    RedialLastPhoneNumber,
    MuteOnOff,
    DialSelectedArea,
    TurnUpMicrophone,
    TurnDownMicrophone,
    TurnUpSpeaker,
    TurnDownSpeaker,
  };
  Q_ENUM(ShortcutList)

  explicit Widget(QWidget* parent = nullptr);
  ~Widget();

 private:
  Ui::Widget* ui;
  QSettings mSettings;

  UGlobalHotkeys* mHotkeyManager;

  QList<KeySequenceLineEdit*> mShortcutEditList;
  /**
   * @brief mShortcutList <shortcutId: int, shortcutValue: string>
   */
  QMap<size_t, QString> mShortcutValueList;
  QMap<size_t, QString> mShortcutNameList;
  QMap<size_t, std::function<void(Widget&)>> mShortcutSlots;
  QMap<size_t, KeySequenceLineEdit*> mChangedValues;

  QString shortcutListToString(ShortcutList shortcut);

  void enableShortcuts(bool enabled);
  void saveChangedShortcuts();
  void discardChangedShortcuts();
  bool shortcutExists(const QString& shortcut);

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

 private slots:
  void on_okButton_clicked();
  void on_applyButton_clicked();
  void on_cancelButton_clicked();
};
