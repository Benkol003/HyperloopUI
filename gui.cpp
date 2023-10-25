#include <QApplication>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>

int main(int argc, char **argv){
    QApplication app(argc, argv);

    QWidget* window = new QWidget;

    QVBoxLayout* BatteryPanel = new QVBoxLayout();
    QLabel*  BatteryPercent = new QLabel("N/A %",window);
    QLabel*  BatteryVoltage = new QLabel("Voltage: N/A V",window);
    QLabel*  BatteryTemp = new QLabel("Tempurature: N/A 'C",window);

    QHBoxLayout* CommStatusPanel = new QHBoxLayout();
    QLabel* CommStatus = new QLabel("Comms status: ",window);
    QPixmap pixmap(16,16);
    pixmap.fill(QColor("red"));
    QLabel* CommStatusIcon = new QLabel(window);
    CommStatusIcon->setPixmap(pixmap);
    CommStatusPanel->addWidget(CommStatus);
    CommStatusPanel->addWidget(CommStatusIcon);



    BatteryPanel->addWidget(BatteryPercent);
    BatteryPanel->addWidget(BatteryVoltage);
    BatteryPanel->addWidget(BatteryTemp);
    BatteryPanel->addLayout(CommStatusPanel);
    
    //BatteryVoltage->show();
    //BatteryPercent->show();
    //BatteryTemp->show();
    //CommStatus->show();
    //CommStatusIcon->show();

    QFrame* BatteryFrame = new QFrame(window);
    int padding = 10; // Set your desired padding value
    BatteryFrame->setContentsMargins(padding, padding, padding, padding);
    BatteryFrame->setFrameStyle(QFrame::StyledPanel);
    BatteryFrame->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

    BatteryFrame->setLayout(BatteryPanel);
    
    BatteryFrame->show();
    window->show();

    app.exec();
    return 0;
}