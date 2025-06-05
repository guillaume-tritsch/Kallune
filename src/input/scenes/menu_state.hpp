#pragma once
#include "utils/state.hpp"

struct MenuState {
    ButtonState playButton {DEFAULT};
    ButtonState settingsButton {DEFAULT};
    ButtonState exitButton {DEFAULT};

    void update(InputState state);
};