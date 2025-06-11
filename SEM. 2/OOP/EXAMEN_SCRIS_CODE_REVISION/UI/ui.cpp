//
// Created by Ioana Gavrila on 09.06.2025.
//

#include "ui.h"
#include <QtWidgets/QApplication>
#include <QtCore/QTimer>
#include <QtGui/QPainter>
#include <QtCore/QDebug>
#include <algorithm>
#include <cmath>

//=============================================================================
// MainWindow Implementation
//=============================================================================

MainWindow::MainWindow(CodeRevisionService* service, QWidget* parent)
    : QMainWindow(parent), service(service), statisticsWindow(nullptr) {

    setWindowTitle("Code Revision System");
    resize(300, 200);

    createProgrammerWindows();
    statisticsWindow = new StatisticsWindow(service, this);

    updateTimer = new QTimer(this);
    connect(updateTimer, &QTimer::timeout, this, &MainWindow::periodicUpdate);
    updateTimer->start(2000);

    showStatisticsWindow();
}

MainWindow::~MainWindow() {
    for (auto* window : programmerWindows) {
        delete window;
    }
    if (statisticsWindow) {
        delete statisticsWindow;
    }
}

void MainWindow::createProgrammerWindows() {
    vector<Member> members = service->getAllMembers();

    for (auto& member : members) {
        string memberName = member.get_name();
        ProgrammerWindow* window = new ProgrammerWindow(memberName, service, this);
        programmerWindows.push_back(window);
        window->show();
    }
}

void MainWindow::showStatisticsWindow() {
    if (statisticsWindow) {
        statisticsWindow->updateStatistics();
        statisticsWindow->show();
    }
}

void MainWindow::updateAllWindows() {
    for (auto* window : programmerWindows) {
        window->updateFileList();
        window->updateStatistics();
    }

    if (statisticsWindow) {
        statisticsWindow->updateStatistics();
    }
}

void MainWindow::onDataChanged() {
    updateAllWindows();
}

void MainWindow::periodicUpdate() {
    updateAllWindows();
}

//=============================================================================
// ProgrammerWindow Implementation
//=============================================================================

ProgrammerWindow::ProgrammerWindow(string& programmerName, CodeRevisionService* service,
                                  MainWindow* mainWindow, QWidget* parent)
    : QWidget(parent), service(service), mainWindow(mainWindow), programmerName(programmerName) {

    setupUI();
    updateFileList();
    updateStatistics();
}

ProgrammerWindow::~ProgrammerWindow() {}

void ProgrammerWindow::setupUI() {
    setWindowTitle(QString::fromStdString(programmerName));
    resize(500, 300);

    mainLayout = new QVBoxLayout(this);

    // Simple file list
    fileListWidget = new QListWidget();
    mainLayout->addWidget(fileListWidget);
    connect(fileListWidget, &QListWidget::itemSelectionChanged,
            this, &ProgrammerWindow::onFileSelectionChanged);

    // Statistics labels
    revisedLabel = new QLabel("Revised: 0");
    remainingLabel = new QLabel("Remaining: 0");
    mainLayout->addWidget(revisedLabel);
    mainLayout->addWidget(remainingLabel);

    // Add file input
    fileNameEdit = new QLineEdit();
    fileNameEdit->setPlaceholderText("File name");
    mainLayout->addWidget(fileNameEdit);

    // Buttons
    addButton = new QPushButton("Add File");
    reviseButton = new QPushButton("Revise File");
    reviseButton->setEnabled(false);

    mainLayout->addWidget(addButton);
    mainLayout->addWidget(reviseButton);

    connect(addButton, &QPushButton::clicked, this, &ProgrammerWindow::onAddFileClicked);
    connect(reviseButton, &QPushButton::clicked, this, &ProgrammerWindow::onReviseClicked);
}

void ProgrammerWindow::updateFileList() {
    fileListWidget->clear();

    vector<SourceFile> allFiles = service->getAllSourceFiles();

    for (auto& file : allFiles) {
        QListWidgetItem* item = new QListWidgetItem();

        QString text = QString::fromStdString(file.get_name()) + " - " +
                      QString::fromStdString(file.get_status()) + " - " +
                      QString::fromStdString(file.get_creator());

        if (!file.get_reviewer().empty()) {
            text += " - " + QString::fromStdString(file.get_reviewer());
        }

        item->setText(text);
        item->setData(Qt::UserRole, QString::fromStdString(file.get_name()));

        if (file.get_status() == "not_revised") {
            QFont font = item->font();
            font.setBold(true);
            item->setFont(font);
        }

        if (file.get_status() == "revised") {
            item->setBackground(QColor(144, 238, 144));
        }

        fileListWidget->addItem(item);
    }
}

void ProgrammerWindow::updateStatistics() {
    Member member = service->getMemberByName(programmerName);

    revisedLabel->setText(QString("Revised: %1").arg(member.get_no_rev_f()));
    remainingLabel->setText(QString("Remaining: %1").arg(member.get_remaining()));

    if (member.is_complete()) {
        QMessageBox::information(this, "Done", "Congratulations! All files revised!");
    }
}

void ProgrammerWindow::onAddFileClicked() {
    QString fileName = fileNameEdit->text();

    if (fileName.isEmpty()) {
        QMessageBox::warning(this, "Error", "Enter file name");
        return;
    }

    string fileNameStr = fileName.toStdString();
    bool success = service->addSourceFile(fileNameStr, programmerName);

    if (success) {
        fileNameEdit->clear();
        updateFileList();
        mainWindow->onDataChanged();
    } else {
        QMessageBox::warning(this, "Error", "Cannot add file");
    }
}

void ProgrammerWindow::onReviseClicked() {
    QListWidgetItem* item = fileListWidget->currentItem();
    if (!item) {
        QMessageBox::warning(this, "Error", "Select a file");
        return;
    }

    QString fileName = item->data(Qt::UserRole).toString();
    string fileNameStr = fileName.toStdString();

    if (!service->canReviseFile(fileNameStr, programmerName)) {
        QMessageBox::warning(this, "Error", "Cannot revise this file");
        return;
    }

    bool success = service->reviseFile(fileNameStr, programmerName);

    if (success) {
        updateFileList();
        updateStatistics();
        mainWindow->onDataChanged();
    }
}

void ProgrammerWindow::onFileSelectionChanged() {
    QListWidgetItem* item = fileListWidget->currentItem();

    if (item) {
        QString fileName = item->data(Qt::UserRole).toString();
        string fileNameStr = fileName.toStdString();
        bool canRevise = service->canReviseFile(fileNameStr, programmerName);
        reviseButton->setEnabled(canRevise);
    } else {
        reviseButton->setEnabled(false);
    }
}

//=============================================================================
// StatisticsCircleWidget Implementation
//=============================================================================

StatisticsCircleWidget::StatisticsCircleWidget(QWidget* parent) : QWidget(parent) {
    resize(400, 300);
}

void StatisticsCircleWidget::updateStatistics(map<string, pair<int, int>>& stats,
                                            vector<string>& completed) {
    statistics = stats;
    completedProgrammers = completed;
    update();
}

void StatisticsCircleWidget::paintEvent(QPaintEvent* event) {
    QPainter painter(this);

    if (statistics.empty()) {
        painter.drawText(10, 20, "No data");
        return;
    }

    int x = 20;
    int y = 30;

    for (auto& entry : statistics) {
        string name = entry.first;
        int revised = entry.second.first;
        int total = entry.second.second;

        // Simple circle
        int radius = 15;
        if (total > 0) {
            radius = 10 + (revised * 20) / total;
        }

        QColor color = Qt::gray;


        painter.setBrush(color);
        painter.drawEllipse(x, y, radius * 2, radius * 2);

        painter.drawText(x, y + radius * 2 + 15, QString::fromStdString(name));
        painter.drawText(x, y + radius * 2 + 30, QString("%1/%2").arg(revised).arg(total));

        x += 100;
        if (x > 300) {
            x = 20;
            y += 80;
        }
    }
}
QColor StatisticsCircleWidget::getCircleColor(string& programmer) {
    return Qt::gray;
}

int StatisticsCircleWidget::calculateRadius(int revised, int total, int maxRadius) {
    if (total == 0) return 10;
    return 10 + (revised * maxRadius) / total;
}

//=============================================================================
// StatisticsWindow Implementation
//=============================================================================

StatisticsWindow::StatisticsWindow(CodeRevisionService* service, MainWindow* mainWindow,
                                  QWidget* parent)
    : QWidget(parent), service(service), mainWindow(mainWindow) {

    setupUI();
}

StatisticsWindow::~StatisticsWindow() {}

void StatisticsWindow::setupUI() {
    setWindowTitle("Statistics");
    resize(450, 350);

    mainLayout = new QVBoxLayout(this);

    titleLabel = new QLabel("Statistics");
    mainLayout->addWidget(titleLabel);

    circleWidget = new StatisticsCircleWidget();
    mainLayout->addWidget(circleWidget);

    refreshButton = new QPushButton("Refresh");
    connect(refreshButton, &QPushButton::clicked, this, &StatisticsWindow::onRefreshClicked);
    mainLayout->addWidget(refreshButton);
}

void StatisticsWindow::updateStatistics() {
    map<string, pair<int, int>> stats = service->getProgrammerStatistics();
    vector<string> completed = service->getCompletedProgrammers();

    circleWidget->updateStatistics(stats, completed);
}

void StatisticsWindow::onRefreshClicked() {
    updateStatistics();
}

//=============================================================================
// CodeRevisionApp Implementation
//=============================================================================

CodeRevisionApp::CodeRevisionApp(int argc, char* argv[], string& membersFile,
                               string& sourceFilesFile) {
    app = new QApplication(argc, argv);
    service = new CodeRevisionService(membersFile, sourceFilesFile);
    mainWindow = new MainWindow(service);
}

CodeRevisionApp::~CodeRevisionApp() {
    delete mainWindow;
    delete service;
    delete app;
}

int CodeRevisionApp::run() {
    return app->exec();
}