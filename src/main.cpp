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
#include <nlohmann/json.hpp>

#include "gui.hpp"

using json = nlohmann::json;



json data;

size_t parse_json(char* buffer,size_t _size, size_t nmemb, json* data){
    //(_size is always 1)
    //return no. of bytes handled
    //ruh roh if all the data doesnt fit inside the buffer at once
    *data = json::parse(buffer,buffer + nmemb);
    return nmemb;
}

void worker(std::atomic_bool& stop,HyperloopGUI *gui,CURL* curl){
try{
    bool b=false; //put code here to run after the gui is launched
    while(!stop){
        std::this_thread::sleep_for(std::chrono::milliseconds(1000 / 2)); //TODO limit update speed
        //fetches json data, parse_json() will be run
        CURLcode err = curl_easy_perform(curl);
        if(err!=CURLE_OK) throw std::runtime_error("Failed to perform GET request. CURL error: "+std::to_string(err));
        std::cout<<data<<'\n';
        gui->setBatteryTemp(data["tempurature"]);
    }
} catch(const std::exception &e){
    std::cerr<<e.what();
}
}

int main(int argc, char **argv){
try{
    QApplication app(argc, argv);

    auto *gui = new HyperloopGUI();

    //-------- non-GUI code --------//
    curl_global_init(CURL_GLOBAL_DEFAULT);
    CURL* curl = curl_easy_init();
    curl_easy_setopt(curl,CURLOPT_URL,"http://localhost:8000"); //TODO test with https
    curl_easy_setopt(curl,CURLOPT_WRITEFUNCTION, parse_json);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &data); //to pass other data to the function when its called


    //---- Start GUI execution ----//

    std::atomic_bool stop = false;
    std::thread workerThrd(worker,std::ref(stop),gui,curl);

    app.exec();
    
    stop = true;
    workerThrd.join();
    curl_easy_cleanup(curl);
    curl_global_cleanup();
    return 0;

} catch (const std::exception &e){
    std::cerr<<e.what()<<std::endl;
}
}
