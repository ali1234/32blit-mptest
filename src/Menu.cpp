// mptest - Menu.cpp
// Copyright (c) 2021 Alistair Buxton <a.j.buxton@gmail.com>
// GPL-3.0-or-later

#include "32blit.hpp"
#include "Menu.hpp"

Menu::Menu(const std::vector<const char *> &items) : items(items) {
    disabled = new bool[items.size()]{};
}

Menu::~Menu() {
    delete disabled;
}

void Menu::update(ButtonState &buttons) {
    if (buttons.pressed(blit::Button::DPAD_DOWN)) {
        selected = (selected + 1) % items.size();
    } else if (buttons.pressed(blit::Button::DPAD_UP)) {
        selected = (selected + items.size() - 1) % items.size();
    }
}

void Menu::render() {
    unsigned n = 0;
    blit::screen.pen = blit::Pen(255, 255, 255);
    for (const auto &item: items) {
        if (n == selected) blit::screen.text(">", blit::minimal_font, blit::Point(120, 100 + (n * 12)));
        blit::screen.text(item, blit::minimal_font, blit::Point(130, 100 + (n * 12)));
        n++;
    }
}