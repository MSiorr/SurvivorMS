#include "stdafx.h"
#include "GraphicsSettings.h"

GraphicsSettings::GraphicsSettings() {
    this->title = "DEFAULT";
    this->resolution = sf::VideoMode::getDesktopMode();
    this->fullscreen = false;
    this->verticalSync = false;
    this->maxFps = 144;
    this->contextSettings.antialiasingLevel = 0;
    this->videoModes = sf::VideoMode::getFullscreenModes();
}

void GraphicsSettings::saveToFile(const std::string path) {

    std::ofstream ofs(path);

    if (ofs.is_open()) {
        ofs << this->title;
        ofs << this->resolution.width << " " << this->resolution.height;
        ofs << this->maxFps;
        ofs << this->verticalSync;
        ofs << this->fullscreen;
        ofs << this->contextSettings.antialiasingLevel;
    }

    ofs.close();

}

void GraphicsSettings::loadFromFile(const std::string path) {

    std::ifstream ifs(path);

    if (ifs.is_open()) {
        std::getline(ifs, this->title);
        ifs >> this->resolution.width >> this->resolution.height;
        ifs >> this->maxFps;
        ifs >> this->verticalSync;
        ifs >> this->fullscreen;
        ifs >> this->contextSettings.antialiasingLevel;
    }

    ifs.close();

}