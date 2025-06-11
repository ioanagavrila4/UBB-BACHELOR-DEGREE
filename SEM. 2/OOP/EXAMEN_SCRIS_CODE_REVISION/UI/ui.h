//
// Created by Ioana Gavrila on 09.06.2025.
//

#pragma once

#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QListWidgetItem>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMessageBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QProgressBar>
#include <QtCore/QTimer>
#include <QPainter>
#include <vector>
#include <map>
#include "../Service/service.h"

using namespace std;

// Forward declarations
class ProgrammerWindow;
class StatisticsWindow;

// Main Application Window
class MainWindow : public QMainWindow {
    Q_OBJECT

private:
    CodeRevisionService* service;
    vector<ProgrammerWindow*> programmerWindows;
    StatisticsWindow* statisticsWindow;
    QTimer* updateTimer;

public:
    MainWindow(CodeRevisionService* service, QWidget* parent = nullptr);
    ~MainWindow();

    void createProgrammerWindows();
    void showStatisticsWindow();
    void updateAllWindows();

public slots:
    void onDataChanged();

private slots:
    void periodicUpdate();
};

// Individual Programmer Window
class ProgrammerWindow : public QWidget {
    Q_OBJECT

private:
    CodeRevisionService* service;
    MainWindow* mainWindow;
    string programmerName;

    // Basic UI Components
    QVBoxLayout* mainLayout;
    QListWidget* fileListWidget;
    QLabel* revisedLabel;
    QLabel* remainingLabel;
    QLineEdit* fileNameEdit;
    QPushButton* addButton;
    QPushButton* reviseButton;

public:
    ProgrammerWindow(string& programmerName, CodeRevisionService* service,
                    MainWindow* mainWindow, QWidget* parent = nullptr);
    ~ProgrammerWindow();

    void updateFileList();
    void updateStatistics();
    string getProgrammerName() { return programmerName; }

private slots:
    void onAddFileClicked();
    void onReviseClicked();
    void onFileSelectionChanged();

private:
    void setupUI();
};

// Statistics Window with Custom Painting
class StatisticsCircleWidget : public QWidget {
    Q_OBJECT

private:
    map<string, pair<int, int>> statistics; // name -> (revised, total)
    vector<string> completedProgrammers;

public:
    StatisticsCircleWidget(QWidget* parent = nullptr);
    void updateStatistics(map<string, pair<int, int>>& stats,
                         vector<string>& completed);

protected:
    void paintEvent(QPaintEvent* event) override;

private:
    QColor getCircleColor(string& programmer);
    int calculateRadius(int revised, int total, int maxRadius = 50);
};

class StatisticsWindow : public QWidget {
    Q_OBJECT

private:
    CodeRevisionService* service;
    MainWindow* mainWindow;

    QVBoxLayout* mainLayout;
    QLabel* titleLabel;
    StatisticsCircleWidget* circleWidget;
    QPushButton* refreshButton;

public:
    StatisticsWindow(CodeRevisionService* service, MainWindow* mainWindow,
                    QWidget* parent = nullptr);
    ~StatisticsWindow();

    void updateStatistics();

public slots:
    void onRefreshClicked();

private:
    void setupUI();
};

// Application Class
class CodeRevisionApp {
private:
    QApplication* app;
    CodeRevisionService* service;
    MainWindow* mainWindow;

public:
    CodeRevisionApp(int argc, char* argv[], string& membersFile,
                   string& sourceFilesFile);
    ~CodeRevisionApp();

    int run();
};