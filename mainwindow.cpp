#include <QtWidgets>
#include <QColor>
#include <QLabel>
#include <QPixmap>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>

#include "AppInfo.h"
#include "mainwindow.h"

MainWindow::MainWindow() {
    slotMachine = new StateMachine(this);

    createMenu();
    createHorizontalGroupBoxes();
    createGridGroupBox();

    fileLogger("\t Admin Log Busy");

    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok
                                     | QDialogButtonBox::Cancel);
    connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->setMenuBar(menuBar);
    mainLayout->addWidget(horizontalGroupBox1);
    mainLayout->addWidget(gridGroupBox);
    mainLayout->addWidget(GroupBoxLog_horz);
    mainLayout->addWidget(buttonBox);

    setLayout(mainLayout);
    setWindowTitle(tr(APPNAME_VERSION));

    slotMachine->handleEvent(E_INIT);
}

MainWindow::~MainWindow() {
    fileLogger(logDisplay->toPlainText());
}

void MainWindow::enableButtons(bool enable) {
    for (int i = 0; i < NumButtons; i++) {
        buttons[i]->setEnabled(enable);
    }
}

void MainWindow::setDisplay(const QString &text) {
    display->setText(text);
    display->update();
}

void MainWindow::setDisplay(const QString &text, const QString &text2, const QString &text3) {
    display->setText(text + "\n" + text2 + "\n" + text3);
    display->update();
}

void MainWindow::setLogger(const QString &text) {
    logDisplay->moveCursor(QTextCursor::End);
    logDisplay->insertPlainText("\n" + text);
    logDisplay->moveCursor(QTextCursor::End);
}

void MainWindow::fileLogger(const QString &text) {
    QFile logFile("adminLogs.txt");

    if(!logFile.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this,"title","file not open");
    }
    QTextStream log_out(&logFile);
    log_out << text << "\n";
    logFile.close();
}

void MainWindow::createMenu() {
    menuBar = new QMenuBar;
    fileMenu = new QMenu(tr("&File"), this);
    adminMenu = new QMenu(tr("&AdminPanel"), this);

    exitAction = fileMenu->addAction(tr("E&xit"));
    adminAction = adminMenu->addAction(tr("Show Admin Log"));
    adminAction_out = adminMenu->addAction(tr("Hide Admin Log"));

    menuBar->addMenu(fileMenu);
    menuBar->addMenu(adminMenu);
    connect(exitAction, SIGNAL(triggered()), this, SLOT(accept()));
    connect(adminAction, SIGNAL(triggered()), this, SLOT(enableAdminMode()));
    connect(adminAction_out, SIGNAL(triggered()), this, SLOT(disableAdminMode()));
}

void MainWindow::createHorizontalGroupBoxes() {
    // HorizontalGroupBox 1 -----------------------------------------------------
    horizontalGroupBox1 = new QGroupBox(tr("Simulate Hardware Triggers"));
    QHBoxLayout *layout1 = new QHBoxLayout;

    buttons[0] = new QPushButton(tr("100EU"));
    layout1->addWidget(buttons[0]);
    connect(buttons[0], SIGNAL(released()), this, SLOT(banknote_100EU()));

    buttons[1] = new QPushButton(tr("50EU"));
    layout1->addWidget(buttons[1]);
    connect(buttons[1], SIGNAL(released()), this, SLOT(banknote_50EU()));

    buttons[2] = new QPushButton(tr("SPIN"));
    layout1->addWidget(buttons[2]);
    connect(buttons[2], SIGNAL(released()), this, SLOT(gambleSpin()));

    buttons[3] = new QPushButton(tr("Payout"));
    layout1->addWidget(buttons[3]);
    connect(buttons[3], SIGNAL(released()), this, SLOT(payBalance()));

    enableButtons(false);
    horizontalGroupBox1->setLayout(layout1);

    // HorizontalGroupBox 2 -----------------------------------------------------
    GroupBoxLog_horz = new QGroupBox(tr("Admin Log"));
    QHBoxLayout *log_layout = new QHBoxLayout;

    logDisplay = new QTextEdit("Logging started", this);
    logDisplay->setOverwriteMode(false);
    logDisplay->setReadOnly(true);
    logDisplay->setMinimumHeight(150);

    log_layout->addWidget(logDisplay);
    GroupBoxLog_horz->setLayout(log_layout);
    GroupBoxLog_horz->hide();
}

void MainWindow::createGridGroupBox() {
    gridGroupBox = new QGroupBox(tr("User Display"));
    QGridLayout *displayLayout = new QGridLayout;

    display = new QTextEdit(this);
    display->setReadOnly(true);
    display->setTextColor(QColor(0,0,255));
    display->setFontPointSize(18);
    display->setMinimumWidth(500);
    display->setFixedHeight(150);
    display->setOverwriteMode(true);

    displayLayout->addWidget(display, 0, 1, 1, 5);
    displayLayout->setColumnStretch(1, 10);
    displayLayout->setColumnStretch(2, 20);
    gridGroupBox->setLayout(displayLayout);
}

/// GUI event handlers

void MainWindow::banknote_100EU() {
    slotMachine->handleEvent(E_INSERT_100EU);
}

void MainWindow::banknote_50EU() {
    slotMachine->handleEvent(E_INSERT_50EU);
}

void MainWindow::gambleSpin() {
    slotMachine->handleEvent(E_SPIN);
}

void MainWindow::payBalance() {
    slotMachine->handleEvent(E_PAY_BALANCE);
}

void MainWindow::enableAdminMode() {
    GroupBoxLog_horz->show();
}

void MainWindow::disableAdminMode() {
    GroupBoxLog_horz->hide();
}

