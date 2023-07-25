#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "StateMachine.h"
#include <QDialog>
#include <QFile>
#include <QDebug>

QT_BEGIN_NAMESPACE
    class QAction;
    class QDialogButtonBox;
    class QGroupBox;
    class QLabel;
    class QMenu;
    class QMenuBar;
    class QPushButton;
    class QTextEdit;
QT_END_NAMESPACE

class MainWindow: public QDialog
{
   Q_OBJECT

public:
   MainWindow();
   ~MainWindow();

   void enableButtons(bool enable);
   void setDisplay(const QString& text);
   void setDisplay(const QString &text, const QString &text2, const QString &text3); // Function overload
   void setLogger(const QString& text);
   void fileLogger(const QString &text);

private:
   void createMenu();
   void createHorizontalGroupBoxes();
   void createGridGroupBox();
   void createFormGroupBox();

   enum { NumGridRows = 3, NumButtons = 4 };

   QMenuBar *menuBar;
   QGroupBox *horizontalGroupBox1;
   QGroupBox *GroupBoxLog_horz;
   QGroupBox *gridGroupBox;

   QTextEdit *display;
   QTextEdit *logDisplay;
   QPushButton *buttons[NumButtons];
   QDialogButtonBox *buttonBox;

   QMenu *fileMenu;
   QMenu *adminMenu;
   QAction *exitAction;
   QAction *adminAction;
   QAction *adminAction_out;

   //**************************************************************************
   StateMachine *slotMachine;
   event_e event;

private slots:
   void banknote_100EU();
   void banknote_50EU();
   void gambleSpin();
   void payBalance();

   void enableAdminMode();
   void disableAdminMode();
};

#endif // MAINWINDOW_H
