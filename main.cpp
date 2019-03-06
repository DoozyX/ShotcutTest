#include <QApplication>
#include "Widget.h"

int main(int argc, char* argv[]) {
  QCoreApplication::setOrganizationName("TestShortcut");
  QCoreApplication::setOrganizationDomain("TestShortcut");
  QCoreApplication::setApplicationName("TestShortcut");

  QApplication a(argc, argv);
  Widget w;
  w.show();

  return a.exec();
}
