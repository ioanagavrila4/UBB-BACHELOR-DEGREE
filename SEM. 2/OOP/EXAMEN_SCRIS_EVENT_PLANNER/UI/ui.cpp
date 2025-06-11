#include "ui.h"
#include <QMessageBox>
#include <QString>
#include <QSplitter>

// Helper function to convert std::string to QString
QString toQString(const std::string& str) {
    return QString::fromStdString(str);
}

// Helper function to convert QString to std::string
std::string toStdString(const QString& str) {
    return str.toStdString();
}

PersonWindow::PersonWindow(const std::string& name, EventService* srv, QWidget* parent)
    : QMainWindow(parent), personName(name), service(srv) {
    
    setWindowTitle(toQString("Event Planner - " + personName));
    setMinimumSize(800, 600);
    
    QWidget* centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    
    QHBoxLayout* mainLayout = new QHBoxLayout(centralWidget);
    
    // Left side - Event list and controls
    QVBoxLayout* leftLayout = new QVBoxLayout();
    
    // Person location info
    Person person = service->getPersonByName(personName);
    QLabel* locationLabel = new QLabel(toQString("Location: (" + 
        std::to_string(person.latitude) + ", " + std::to_string(person.longitude) + ")"));
    leftLayout->addWidget(locationLabel);
    
    // Nearby events checkbox
    nearbyCheckBox = new QCheckBox("Show only nearby events (within 5 units)");
    leftLayout->addWidget(nearbyCheckBox);
    connect(nearbyCheckBox, &QCheckBox::stateChanged, this, &PersonWindow::onNearbyCheckChanged);
    
    // Event list
    eventList = new QListWidget();
    leftLayout->addWidget(eventList);
    connect(eventList, &QListWidget::itemSelectionChanged, this, &PersonWindow::onEventSelectionChanged);
    
    // Going button for non-organizers
    if (!service->isPersonOrganiser(personName)) {
        goingButton = new QPushButton("Going");
        goingButton->setEnabled(false);
        leftLayout->addWidget(goingButton);
        connect(goingButton, &QPushButton::clicked, this, &PersonWindow::onGoingButtonClicked);
    }
    
    // Add event section for organizers
    if (service->isPersonOrganiser(personName)) {
        QLabel* addEventLabel = new QLabel("Add New Event:");
        leftLayout->addWidget(addEventLabel);
        
        eventNameEdit = new QLineEdit();
        eventNameEdit->setPlaceholderText("Event Name");
        leftLayout->addWidget(eventNameEdit);
        
        eventDescEdit = new QLineEdit();
        eventDescEdit->setPlaceholderText("Description");
        leftLayout->addWidget(eventDescEdit);
        
        eventDateEdit = new QLineEdit();
        eventDateEdit->setPlaceholderText("Date (YYYY-MM-DD)");
        leftLayout->addWidget(eventDateEdit);
        
        eventLatEdit = new QLineEdit();
        eventLatEdit->setPlaceholderText("Latitude");
        leftLayout->addWidget(eventLatEdit);
        
        eventLngEdit = new QLineEdit();
        eventLngEdit->setPlaceholderText("Longitude");
        leftLayout->addWidget(eventLngEdit);
        
        addEventButton = new QPushButton("Add Event");
        leftLayout->addWidget(addEventButton);
        connect(addEventButton, &QPushButton::clicked, this, &PersonWindow::onAddEventClicked);
    }
    
    mainLayout->addLayout(leftLayout);
    
    // Right side - Event details and organizer controls
    QVBoxLayout* rightLayout = new QVBoxLayout();
    
    eventDetails = new QTextEdit();
    eventDetails->setReadOnly(true);
    rightLayout->addWidget(eventDetails);
    
    // Organizer controls
    if (service->isPersonOrganiser(personName)) {
        organizerControls = new QWidget();
        QVBoxLayout* orgLayout = new QVBoxLayout(organizerControls);
        
        QLabel* updateLabel = new QLabel("Update Selected Event:");
        orgLayout->addWidget(updateLabel);
        
        updateDescEdit = new QLineEdit();
        updateDescEdit->setPlaceholderText("New Description");
        orgLayout->addWidget(updateDescEdit);
        
        updateDescButton = new QPushButton("Update Description");
        updateDescButton->setEnabled(false);
        orgLayout->addWidget(updateDescButton);
        connect(updateDescButton, &QPushButton::clicked, this, &PersonWindow::onUpdateDescriptionClicked);
        
        updateDateEdit = new QLineEdit();
        updateDateEdit->setPlaceholderText("New Date (YYYY-MM-DD)");
        orgLayout->addWidget(updateDateEdit);
        
        updateDateButton = new QPushButton("Update Date");
        updateDateButton->setEnabled(false);
        orgLayout->addWidget(updateDateButton);
        connect(updateDateButton, &QPushButton::clicked, this, &PersonWindow::onUpdateDateClicked);
        
        rightLayout->addWidget(organizerControls);
    }
    
    mainLayout->addLayout(rightLayout);
    
    refreshEventList();
}

void PersonWindow::refreshEventList() {
    eventList->clear();
    
    std::vector<Event> events;
    if (nearbyCheckBox && nearbyCheckBox->isChecked()) {
        events = service->getEventsNearPerson(personName);
    } else {
        events = service->getAllEvents();
    }
    
    for (const auto& event : events) {
        QString itemText = toQString(event.name + " - " + event.date);
        QListWidgetItem* item = new QListWidgetItem(itemText);
        
        // Green background for events organized by this person
        if (event.organiser == personName) {
            item->setBackground(QColor(144, 238, 144)); // Light green
        }
        
        eventList->addItem(item);
    }
}

void PersonWindow::onEventSelectionChanged() {
    QListWidgetItem* current = eventList->currentItem();
    if (!current) {
        eventDetails->clear();
        if (goingButton) goingButton->setEnabled(false);
        if (service->isPersonOrganiser(personName)) {
            updateDescButton->setEnabled(false);
            updateDateButton->setEnabled(false);
        }
        return;
    }
    
    QString itemText = current->text();
    std::string eventName = toStdString(itemText.split(" - ")[0]);
    
    // Find and display event details
    auto events = service->getAllEvents();
    for (const auto& event : events) {
        if (event.name == eventName) {
            QString details = toQString(
                "Name: " + event.name + "\n" +
                "Organizer: " + event.organiser + "\n" +
                "Description: " + event.description + "\n" +
                "Location: (" + std::to_string(event.latitude) + ", " + std::to_string(event.longitude) + ")\n" +
                "Date: " + event.date + "\n" +
                "Attendees (" + std::to_string(event.attendees.size()) + "): "
            );
            
            for (size_t i = 0; i < event.attendees.size(); ++i) {
                details += toQString(event.attendees[i]);
                if (i < event.attendees.size() - 1) details += ", ";
            }
            
            eventDetails->setText(details);
            
            // Enable/disable buttons based on conditions
            if (goingButton) {
                bool isAttending = std::find(event.attendees.begin(), event.attendees.end(), personName) != event.attendees.end();
                goingButton->setEnabled(!isAttending);
            }
            
            if (service->isPersonOrganiser(personName) && event.organiser == personName) {
                updateDescButton->setEnabled(true);
                updateDateButton->setEnabled(true);
            }
            
            break;
        }
    }
}

void PersonWindow::onNearbyCheckChanged(int state) {
    refreshEventList();
}

void PersonWindow::onGoingButtonClicked() {
    QListWidgetItem* current = eventList->currentItem();
    if (!current) return;
    
    QString itemText = current->text();
    std::string eventName = toStdString(itemText.split(" - ")[0]);
    
    if (service->addPersonToEvent(personName, eventName)) {
        QMessageBox::information(this, "Success", "You are now attending this event!");
        onEventSelectionChanged(); // Refresh details
        emit eventUpdated();
    } else {
        QMessageBox::warning(this, "Error", "Could not add you to this event.");
    }
}

void PersonWindow::onAddEventClicked() {
    std::string name = toStdString(eventNameEdit->text());
    std::string desc = toStdString(eventDescEdit->text());
    std::string date = toStdString(eventDateEdit->text());
    double lat = eventLatEdit->text().toDouble();
    double lng = eventLngEdit->text().toDouble();
    
    if (name.empty() || date.empty()) {
        QMessageBox::warning(this, "Error", "Please fill in at least name and date.");
        return;
    }
    
    Event newEvent(personName, name, desc, lat, lng, date);
    if (service->addEvent(newEvent)) {
        QMessageBox::information(this, "Success", "Event added successfully!");
        eventNameEdit->clear();
        eventDescEdit->clear();
        eventDateEdit->clear();
        eventLatEdit->clear();
        eventLngEdit->clear();
        refreshEventList();
        emit eventUpdated();
    } else {
        QMessageBox::warning(this, "Error", "Event with same name and location already exists.");
    }
}

void PersonWindow::onUpdateDescriptionClicked() {
    QListWidgetItem* current = eventList->currentItem();
    if (!current) return;
    
    QString itemText = current->text();
    std::string eventName = toStdString(itemText.split(" - ")[0]);
    std::string newDesc = toStdString(updateDescEdit->text());
    
    if (newDesc.empty()) {
        QMessageBox::warning(this, "Error", "Please enter a new description.");
        return;
    }
    
    if (service->updateEventDescription(eventName, newDesc)) {
        QMessageBox::information(this, "Success", "Description updated!");
        updateDescEdit->clear();
        onEventSelectionChanged(); // Refresh details
        emit eventUpdated();
    } else {
        QMessageBox::warning(this, "Error", "Could not update description.");
    }
}

void PersonWindow::onUpdateDateClicked() {
    QListWidgetItem* current = eventList->currentItem();
    if (!current) return;
    
    QString itemText = current->text();
    std::string eventName = toStdString(itemText.split(" - ")[0]);
    std::string newDate = toStdString(updateDateEdit->text());
    
    if (newDate.empty()) {
        QMessageBox::warning(this, "Error", "Please enter a new date.");
        return;
    }
    
    if (service->updateEventDate(eventName, newDate)) {
        QMessageBox::information(this, "Success", "Date updated!");
        updateDateEdit->clear();
        refreshEventList(); // Refresh list to show new date
        onEventSelectionChanged(); // Refresh details
        emit eventUpdated();
    } else {
        QMessageBox::warning(this, "Error", "Could not update date.");
    }
}

// Popular Events Window Implementation
PopularEventsWindow::PopularEventsWindow(EventService* srv, QWidget* parent)
    : QMainWindow(parent), service(srv) {
    
    setWindowTitle("Popular Events");
    setMinimumSize(600, 400);
    
    QWidget* centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    
    QVBoxLayout* layout = new QVBoxLayout(centralWidget);
    
    QLabel* titleLabel = new QLabel("Most Popular Events (by attendance):");
    layout->addWidget(titleLabel);
    
    eventList = new QListWidget();
    layout->addWidget(eventList);
    connect(eventList, &QListWidget::itemSelectionChanged, this, &PopularEventsWindow::onEventSelectionChanged);
    
    eventInfo = new QLabel();
    eventInfo->setWordWrap(true);
    layout->addWidget(eventInfo);
    
    refreshEventList();
}

void PopularEventsWindow::refreshEventList() {
    eventList->clear();
    
    auto events = service->getPopularEvents();
    for (const auto& event : events) {
        QString itemText = toQString(event.name + " - " + event.description + 
                                   " (" + std::to_string(event.attendees.size()) + " attendees)");
        eventList->addItem(itemText);
    }
}

void PopularEventsWindow::onEventSelectionChanged() {
    QListWidgetItem* current = eventList->currentItem();
    if (!current) {
        eventInfo->clear();
        return;
    }
    
    QString itemText = current->text();
    std::string eventName = toStdString(itemText.split(" - ")[0]);
    
    auto events = service->getPopularEvents();
    for (const auto& event : events) {
        if (event.name == eventName) {
            QString info = toQString(
                "Name: " + event.name + "\n" +
                "Description: " + event.description + "\n" +
                "Location: (" + std::to_string(event.latitude) + ", " + std::to_string(event.longitude) + ")\n" +
                "Date: " + event.date + "\n" +
                "Time: N/A\n" +
                "Attendees: " + std::to_string(event.attendees.size())
            );
            eventInfo->setText(info);
            break;
        }
    }
}

void PopularEventsWindow::onEventUpdated() {
    refreshEventList();
}

// Main UI Implementation
MainUI::MainUI() {
    // Load data
    service.loadEventsFromFile("/Users/ioanagavrila/CLionProjects/EXAMEN_SCRIS_EVENT_PLANNER/Service/events.txt");
    service.loadPeopleFromFile("/Users/ioanagavrila/CLionProjects/EXAMEN_SCRIS_EVENT_PLANNER/Service/people.txt");

    popularWindow = nullptr;
}

void MainUI::startApplication() {
    // Create windows for each person
    auto people = service.getAllPeople();

    for (const auto& person : people) {
        PersonWindow* window = new PersonWindow(person.name, &service);
        personWindows[toQString(person.name)] = window;

        // Connect event update signal
        connect(window, &PersonWindow::eventUpdated, this, &MainUI::onEventUpdated);

        window->show();
    }

    // Create popular events window
    popularWindow = new PopularEventsWindow(&service);
    popularWindow->show();
}

void MainUI::onEventUpdated() {
    // Refresh all person windows
    for (auto it = personWindows.begin(); it != personWindows.end(); ++it) {
        it.value()->refreshEventList();
    }

    // Refresh popular events window
    if (popularWindow) {
        popularWindow->refreshEventList();
    }

    // Save events to file
    service.saveEventsToFile("/Users/ioanagavrila/CLionProjects/EXAMEN_SCRIS_EVENT_PLANNER/Service/events.txt");
}

