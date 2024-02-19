/////////////////////////////////////////
/*
Author: Ben Kollar (@benkol003)

Issues:
    Stop widgets from filling available space - make as small as possible
*/
/////////////////////////////////////////
#include <thread>
#include <atomic>
#include <iostream>
#include <string>

#include <QApplication>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QGroupBox>

#include <curl/curl.h>

class SubsystemPanel : public QGroupBox {
    public:
    
    SubsystemPanel(const char* title, QWidget* parent) : QGroupBox(title,parent) {
    auto* layout = new QVBoxLayout(this);
    this->setLayout(layout);
    }
};

class StatusWidget : public QWidget {
    Q_OBJECT 
    public:

    QPixmap red;
    QPixmap green;
    QLabel* onlineIcon;

    StatusWidget(const char* text, QWidget* parent) : QWidget(parent) {
        auto* layout = new QHBoxLayout(this);
        this->setLayout(layout);

        auto* textLbl = new QLabel(text,this);
        this->layout()->addWidget(textLbl);

        red = QPixmap(16,16);
        green = QPixmap(16,16);

        red.fill(QColor("red"));
        green.fill(QColor("green"));

        onlineIcon = new QLabel(this);
        this->layout()->addWidget(onlineIcon);
        onlineIcon->setPixmap(red);

    }

    public slots:
    void setOnline(bool b){
        b ? onlineIcon->setPixmap(red) : onlineIcon->setPixmap(green);
    }
};


void worker(std::atomic_bool& stop,StatusWidget* context){
    bool b=false; //put code here to run after the gui is launched
    while(!stop){
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        context->setOnline(b);
        b=!b;
    }
}

int main(int argc, char **argv){
    QApplication app(argc, argv);

    QWidget* window = new QWidget;
    

    auto* topPanels = new QHBoxLayout();
    auto* bottomPanels = new QHBoxLayout();

    auto* windowLayout = new QVBoxLayout();

    windowLayout->addLayout(topPanels);
    windowLayout->addLayout(bottomPanels);

    window->setLayout(windowLayout);

    //--------------- Top Panels ----------------//
    //-------------------------------------------//

    //---- BatteryPanel ----// 

    auto* cameraPanel = new SubsystemPanel("Camera Feed",window);
    topPanels->addWidget(cameraPanel);

    auto* cameraPanelFeed = new QLabel(window);
    cameraPanelFeed->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    cameraPanel->layout()->addWidget(cameraPanelFeed);

    auto cameraCurrentImg = QPixmap("./noCamera.png");
    cameraPanelFeed->setPixmap(cameraCurrentImg.scaled(128,128));

    cameraPanel->show();

    //---- GPS Panel ---//
    auto* gpsPanel = new SubsystemPanel("GPS",window);
    topPanels->addWidget(gpsPanel);

    auto* gpsStatus = new StatusWidget("GPS: ",window);
    gpsPanel->layout()->addWidget(gpsStatus);

    auto* gpsLat = new QLabel("Latitude: N/A",window);
    gpsPanel->layout()->addWidget(gpsLat);

    auto* gpsLong = new QLabel("Longitude: N/A",window);
    gpsPanel->layout()->addWidget(gpsLong);

    gpsPanel->show();


    //-------------------------------------------//
    //-------------------------------------------//



    //------------ Bottom Panels ----------------//
    //-------------------------------------------//

    //---- BatteryPanel ----// 

    auto* batteryPanel = new SubsystemPanel("Battery",window);
    bottomPanels->addWidget(batteryPanel);

    QLabel*  batteryPercent = new QLabel("N/A %",batteryPanel);
    batteryPanel->layout()->addWidget(batteryPercent);

    QLabel*  batteryVoltage = new QLabel("Voltage: N/A V",batteryPanel);
    batteryPanel->layout()->addWidget(batteryVoltage);

    QLabel*  batteryTemp = new QLabel("Tempurature: N/A 'C",batteryPanel);
    batteryPanel->layout()->addWidget(batteryTemp);

    batteryPanel->show();

    //---- Comms Panel ---//
    auto* commsPanel = new SubsystemPanel("Comms",window);
    bottomPanels->addWidget(commsPanel);

    auto* commsStatus = new StatusWidget("Comms: ",window);
    commsPanel->layout()->addWidget(commsStatus);

    auto* commsSSID = new QLabel("SSID: N/A",window);
    commsPanel->layout()->addWidget(commsSSID);

    auto* commsStrength = new QLabel("Signal Strengh: N/A -dBm");
    commsPanel->layout()->addWidget(commsStrength);

    commsPanel->show();

    //-------Braking Panel ------//
    auto* brakingPanel = new SubsystemPanel("Braking",window);
    bottomPanels->addWidget(brakingPanel);

    auto* brakingStatus = new StatusWidget("Braking: ",window);
    brakingPanel->layout()->addWidget(brakingStatus);

    auto* brakingPressure = new QLabel("Pressure: N/A",window);
    brakingPanel->layout()->addWidget(brakingPressure);

    auto* brakingTemp = new QLabel("Tempurature: N/A 'C",window);
    brakingPanel->layout()->addWidget(brakingTemp);

    brakingPanel->show();

    //-------Motor Panel ------//
    auto* motorPanel = new SubsystemPanel("Motor",window);
    bottomPanels->addWidget(motorPanel);

    auto* motorStatus = new StatusWidget("Motor: ",window);
    motorPanel->layout()->addWidget(motorStatus);

    auto* motorSpeed = new QLabel("Speed: N/A",window);
    motorPanel->layout()->addWidget(motorSpeed);

    auto* motorTemp = new QLabel("Tempurature: N/A 'C",window);
    motorPanel->layout()->addWidget(motorTemp);

    motorPanel->show();

    //-------------------------------------------//
    //-------------------------------------------//

    window->show();


    //---- Start GUI execution ----//

    std::atomic_bool stop = false;
    std::thread workerThrd(worker,std::ref(stop),commsStatus);

    app.exec();
    stop = true;
    workerThrd.join();
    return 0;
}

#include "gui.moc" //qmake wont insert the moc code into source files