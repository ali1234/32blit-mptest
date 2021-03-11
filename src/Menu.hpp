#pragma once

#include <vector>
#include <string>

#include "ButtonState.hpp"

class Menu {
    public:
        Menu(const std::vector<const char *> &items);
        ~Menu();
        void update(ButtonState &buttons);
        void render();
        unsigned get_selected() {return selected;}
        void set_enabled(int item, bool enabled) {disabled[item] = !enabled;};
    private:
        const std::vector<const char *> &items;
        bool *disabled;
        unsigned selected = 0;
};

