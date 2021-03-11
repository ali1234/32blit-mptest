// mptest - StageMenu.cpp
// Copyright (c) 2021 Alistair Buxton <a.j.buxton@gmail.com>
// GPL-3.0-or-later

#include "32blit.hpp"

#include "StageMenu.hpp"
#include "StageBulk.hpp"
#include "StagePing.hpp"



void StageMenu::update(uint32_t time, ButtonState buttons) {
    menu.update(buttons);
    menu.set_enabled(1, mp_state & Linked);
    if (!finished()) {
        if (buttons.pressed(blit::Button::A) && (blit::is_multiplayer_connected())) {
            switch (menu.get_selected()) {
                case 0:
                    finish(std::make_shared<StageBulk>());
                    send_message(Message::StartTestBulk, 0, 0, 0);
                    break;
                case 1:
                    finish(std::make_shared<StagePing>());
                    send_message(Message::StartTestPing, 0, 0, 0);
                    break;
                default:
                    break;
            }
        }
    }
}

void StageMenu::render() {
    blit::screen.pen = blit::Pen(0, 0, 0);
    blit::screen.clear();
    menu.render();
}

void StageMenu::on_message(const Message &message) {
    MessageHandler::on_message(message);
    switch(message.type) {
        case Message::StartTestBulk:
            finish(std::make_shared<StageBulk>());
            break;
        case Message::StartTestPing:
            finish(std::make_shared<StagePing>());
            break;
        default:
            break;
    }
}
