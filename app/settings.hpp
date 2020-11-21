#ifndef SETTINGS_HPP
#define SETTINGS_HPP

enum class control_mode {
    mouse,
    keyboard
};

struct Settings {
    bool musicEnabled;
    int musicVolume;
    bool soundsEnabled;
    float soundsVolume;
    control_mode controlMode;
};

#endif //SETTINGS_HPP
