#pragma once

#include <QApplication>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QGroupBox>

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


class HyperloopGUI {
    public:

    QWidget *window;
    QHBoxLayout *topPanels, *bottomPanels;
    QVBoxLayout *windowLayout;
    SubsystemPanel *cameraPanel, *gpsPanel, *imuPanel, *heatMapPanel, *batteryPanel, *commsPanel, *brakingPanel, *motorPanel;
    StatusWidget *gpsStatus, *imuStatus, *commsStatus, *brakingStatus, *motorStatus;
    QLabel *cameraPanelFeed, *gpsLat, *gpsLong, *imuPitch, *imuRoll, *heatMapFeed, *batteryPercent, *batteryVoltage, *batteryTemp,
    *commsSSID, *commsStrength, *brakingPressure, *brakingTemp, *motorSpeed, *motorTemp;

    HyperloopGUI(){
    window = new QWidget;


    topPanels = new QHBoxLayout();
    bottomPanels = new QHBoxLayout();

    windowLayout = new QVBoxLayout();

    windowLayout->addLayout(topPanels);
    windowLayout->addLayout(bottomPanels);

    window->setLayout(windowLayout);

    //--------------- Top Panels ----------------//
    //-------------------------------------------//

    //---- BatteryPanel ----// 

    cameraPanel = new SubsystemPanel("Camera Feed",window);
    topPanels->addWidget(cameraPanel);

    cameraPanelFeed = new QLabel(window);
    cameraPanelFeed->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    cameraPanel->layout()->addWidget(cameraPanelFeed);

    auto cameraCurrentImg = QPixmap("./noCamera.png");
    cameraPanelFeed->setPixmap(cameraCurrentImg.scaled(128,128));

    cameraPanel->show();

    //---- GPS Panel ---//
    gpsPanel = new SubsystemPanel("GPS",window);
    topPanels->addWidget(gpsPanel);

    gpsStatus = new StatusWidget("GPS: ",window);
    gpsPanel->layout()->addWidget(gpsStatus);

    gpsLat = new QLabel("Latitude: N/A",window);
    gpsPanel->layout()->addWidget(gpsLat);

    gpsLong = new QLabel("Longitude: N/A",window);
    gpsPanel->layout()->addWidget(gpsLong);

    gpsPanel->show();

    //-------IMU Panel ------//
    imuPanel = new SubsystemPanel("IMU",window);
    topPanels->addWidget(imuPanel);

    imuStatus = new StatusWidget("IMU: ",window);
    imuPanel->layout()->addWidget(imuStatus);

    imuPitch = new QLabel("Pitch: N/A",window);
    imuPanel->layout()->addWidget(imuPitch);

    imuRoll = new QLabel("Roll: N/A",window);
    imuPanel->layout()->addWidget(imuRoll);

    imuPanel->show();

    //-------Heat Map Panel ------//
    heatMapPanel = new SubsystemPanel("Heat Map",window);
    topPanels->addWidget(heatMapPanel);

    heatMapFeed = new QLabel(window);
    heatMapFeed->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    heatMapPanel->layout()->addWidget(heatMapFeed);

    auto heatMapCurrentImg = QPixmap("./noHeatMap.png");
    heatMapFeed->setPixmap(heatMapCurrentImg.scaled(128,128));

    heatMapPanel->show();
    //-------------------------------------------//
    //-------------------------------------------//



    //------------ Bottom Panels ----------------//
    //-------------------------------------------//

    //---- BatteryPanel ----// 

    batteryPanel = new SubsystemPanel("Battery",window);
    bottomPanels->addWidget(batteryPanel);

    batteryPercent = new QLabel("N/A %",batteryPanel);
    batteryPanel->layout()->addWidget(batteryPercent);

    batteryVoltage = new QLabel("Voltage: N/A V",batteryPanel);
    batteryPanel->layout()->addWidget(batteryVoltage);

    batteryTemp = new QLabel("Tempurature: N/A 'C",batteryPanel);
    batteryPanel->layout()->addWidget(batteryTemp);

    batteryPanel->show();

    //---- Comms Panel ---//
    commsPanel = new SubsystemPanel("Comms",window);
    bottomPanels->addWidget(commsPanel);

    commsStatus = new StatusWidget("Comms: ",window);
    commsPanel->layout()->addWidget(commsStatus);

    commsSSID = new QLabel("SSID: N/A",window);
    commsPanel->layout()->addWidget(commsSSID);

    commsStrength = new QLabel("Signal Strengh: N/A -dBm");
    commsPanel->layout()->addWidget(commsStrength);

    commsPanel->show();

    //-------Braking Panel ------//
    brakingPanel = new SubsystemPanel("Braking",window);
    bottomPanels->addWidget(brakingPanel);

    brakingStatus = new StatusWidget("Braking: ",window);
    brakingPanel->layout()->addWidget(brakingStatus);

    brakingPressure = new QLabel("Pressure: N/A",window);
    brakingPanel->layout()->addWidget(brakingPressure);

    brakingTemp = new QLabel("Tempurature: N/A 'C",window);
    brakingPanel->layout()->addWidget(brakingTemp);

    brakingPanel->show();

    //-------Motor Panel ------//
    motorPanel = new SubsystemPanel("Motor",window);
    bottomPanels->addWidget(motorPanel);

    motorStatus = new StatusWidget("Motor: ",window);
    motorPanel->layout()->addWidget(motorStatus);

    motorSpeed = new QLabel("Speed: N/A",window);
    motorPanel->layout()->addWidget(motorSpeed);

    motorTemp = new QLabel("Tempurature: N/A 'C",window);
    motorPanel->layout()->addWidget(motorTemp);

    motorPanel->show();

    //-------------------------------------------//
    //-------------------------------------------//

    window->show();    
    }

    void setBatteryTemp(float t){
        auto st = std::to_string(t);
        st="Tempurature: "+st.substr(0, st.find(".")+2) + " °C"; //limit no. of decimal points
        batteryTemp->setText(st.c_str());
    }
};