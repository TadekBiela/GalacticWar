#ifndef SETTINGS_HPP
#define SETTINGS_HPP

enum class control_type {
    mouse,
    keyboard
};

struct Settings {
    bool musicEnabled;
    int musicVolume;
    bool soundsEnabled;
    float soundsVolume;
    control_type controlType;
};

#endif //SETTINGS_HPP
