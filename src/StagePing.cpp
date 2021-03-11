// mptest - StagePing.cpp
// Copyright (c) 2021 Alistair Buxton <a.j.buxton@gmail.com>
// GPL-3.0-or-later

#include "StagePing.hpp"

void StagePing::update(uint32_t time, ButtonState buttons) {
    StageTest::update(time, buttons);
    if (!started && buttons.pressed(blit::Button::A)) {
        send_test_message(Message::Ping);
        started = true;
    }
}

void StagePing::render() {
    StageTest::render();
    if (!started) {
        blit::screen.text("Press A to start test", blit::minimal_font, {160, 100}, true, blit::TextAlign::center_h);
    }
    blit::screen.text("This test passes a message back and forth as quickly as\n possible.",
                      blit::minimal_font, {14, 180}, true);
}

void StagePing::on_message(const Message &message) {
    StageTest::on_message(message);
    if (message.type == Message::Ping) {
        started = true;
    }
    if (message.type == Message::Pong) {
        send_test_message(Message::Pong, message.ms, message.us);
    }
}
