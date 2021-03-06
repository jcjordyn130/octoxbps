/*
* This file is part of Octopi, an open-source GUI for pacman.
* Copyright (C) 2013 Alexandre Albuquerque Arnt
*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; either version 2 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program; if not, write to the Free Software
* Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*
*/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "../../src/unixcommand.h"
#include "../../src/xbpsexec.h"

#include <QDialog>
#include <QProcess>
#include <QString>
#include <QMainWindow>
#include <QSystemTrayIcon>

class QIcon;
class QMenu;
class QAction;
class QFileSystemWatcher;
//class PacmanHelperClient;
class SetupDialog;
class TransactionDialog;

#ifdef KSTATUS
  class KStatusNotifierItem;
#endif

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

  explicit MainWindow(QWidget *parent = 0);
  virtual ~MainWindow();
  inline void turnDebugInfoOn() { m_debugInfo = true;}

private slots:

  void pacmanHelperTimerTimeout();
  void afterPacmanHelperSyncDatabase();

  void finishedPkexec(int);
  void execSystemTrayActivated(QSystemTrayIcon::ActivationReason);
  void execSystemTrayKF5();

  void syncDatabase();
  void refreshAppIcon();
  void runOctoXBPS(ExecOpt execOptions = ectn_SYSUPGRADE_EXEC_OPT);
  void runOctoXBPSSysUpgrade();

  inline void startOctoXBPS() { runOctoXBPS(ectn_NORMAL_EXEC_OPT); }
  void aboutOctoXBPSNotifier();
  void hideOctoXBPS();
  void exitNotifier();
  void doSystemUpgrade();
  void doSystemUpgradeFinished();
  void toggleEnableInterface(bool state);
  void showConfigDialog();

private:

  TransactionDialog *m_transactionDialog;
  SetupDialog *m_setupDialog;
  int m_numberOfOutdatedPackages;
  int m_numberOfOutdatedAURPackages;
  bool m_systemUpgradeDialog;
  CommandExecuting m_commandExecuting;
  UnixCommand *m_unixCommand;

  QAction *m_actionOctoXBPS;
  QAction *m_actionSetInterval;
  QAction *m_actionSyncDatabase;
  QAction *m_actionSystemUpgrade;
  QAction *m_actionAbout;
  QAction *m_actionExit;

  QIcon m_icon;
  QMap<QString, OutdatedPackageInfo> *m_outdatedStringList;
  QTimer *m_pacmanHelperTimer;
  bool m_debugInfo;

#ifdef KSTATUS
  KStatusNotifierItem * m_systemTrayIcon;
#else
  QSystemTrayIcon *m_systemTrayIcon;
#endif

  QMenu *m_systemTrayIconMenu;
  QFileSystemWatcher *m_pacmanDatabaseSystemWatcher;
  //PacmanHelperClient *m_pacmanHelperClient;

  bool _isSUAvailable();
  void initSystemTrayIcon();
  void sendNotification(const QString &msg);

  void startPkexec();
};

#endif // MAINWINDOW_H
