// mptest - StageBulk.cpp
// Copyright (c) 2021 Alistair Buxton <a.j.buxton@gmail.com>
// GPL-3.0-or-later

#include "StageBulk.hpp"

void StageBulk::update(uint32_t time, ButtonState buttons) {
    static uint32_t last_send = 0;
    static uint32_t next_send = 500;
    last_send += time;
    if (last_send > next_send && blit::is_multiplayer_connected() && !(mp_state & TestError)) {
        int count = (rand() & 0x7) + 1;
        for (int n=0; n<count; n++) {
            if (rand() & 1)
                send_test_message(Message::Bulk, 0, 0, rand() & 0xff);
            else
                send_test_message(Message::Ping, 0, 0, 0);
        }
        last_send = 0;
        next_send = (rand() & 0xff) + 50;
    }
    StageTest::update(time, buttons);
}

void StageBulk::render() {
    StageTest::render();
    blit::screen.text("This test sends bulk messages with random size at random\n"
                      "intervals. It may send up to eight messages at once. It also\n"
                      "sends and responds to Ping messages to measure latency.",
                      blit::minimal_font, {14, 180}, true);
}


