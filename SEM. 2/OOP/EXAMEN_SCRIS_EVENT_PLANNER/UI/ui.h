#ifndef UI_H
#define UI_H

#include <QApplication>
#include <QMainWindow>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QListWidget>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QCheckBox>
#include <QComboBox>
#include <QMap>
#include "../Service/service.h"

class PersonWindow : public QMainWindow {
    Q_OBJECT

private:
    std::string personName;
    EventService* service;
    QListWidget* eventList;
    QCheckBox* nearbyCheckBox;
    QTextEdit* eventDetails;
    QPushButton* goingButton;
    QPushButton* addEventButton;
    QLineEdit* eventNameEdit;
    QLineEdit* eventDescEdit;
    QLineEdit* eventDateEdit;
    QLineEdit* eventLatEdit;
    QLineEdit* eventLngEdit;
    QWidget* organizerControls;
    QLineEdit* updateDescEdit;
    QLineEdit* updateDateEdit;
    QPushButton* updateDescButton;
    QPushButton* updateDateButton;

public:
    PersonWindow(const std::string& name, EventService* srv, QWidget* parent = nullptr);
    void refreshEventList();

    private slots:
        void onEventSelectionChanged();
    void onNearbyCheckChanged(int state);
    void onGoingButtonClicked();
    void onAddEventClicked();
    void onUpdateDescriptionClicked();
    void onUpdateDateClicked();

    signals:
        void eventUpdated();
};

class PopularEventsWindow : public QMainWindow {
    Q_OBJECT

private:
    EventService* service;
    QListWidget* eventList;
    QLabel* eventInfo;

public:
    PopularEventsWindow(EventService* srv, QWidget* parent = nullptr);
    void refreshEventList();

    public slots:
        void onEventUpdated();

    private slots:
        void onEventSelectionChanged();
};

class MainUI : public QObject {
    Q_OBJECT

private:
    EventService service;
    QMap<QString, PersonWindow*> personWindows;
    PopularEventsWindow* popularWindow;

public:
    MainUI();
    void startApplication();

    private slots:
        void onEventUpdated();
};

#endif // UI_H