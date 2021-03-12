// mptest - StageTest.cpp
// Copyright (c) 2021 Alistair Buxton <a.j.buxton@gmail.com>
// GPL-3.0-or-later

#include <cinttypes>
#include "StageTest.hpp"
#include "StageMenu.hpp"


void StageTest::on_message(const Message &message) {
    StageMenu::on_message(message);

    if (message.type == Message::Pong) {
        uint32_t lat = (blit::now() - message.oms) * 1000;
        if (lat == 0) {
            lat = blit::now_us() - message.ous;
        }
        if (lat < lat_min) lat_min = lat;
        if (lat > lat_max) lat_max = lat;
        lat_ave = ((lat_ave*9) + lat) / 10;
    }


    switch (message.type) {
        case Message::EndTest:
            finish(std::make_shared<StageMenu>());
            break;
        case Message::Ping:
            send_test_message(Message::Pong, message.ms, message.us);
            /* fall through */
        default:
            if (message.seq != recv_count++) mp_state |= TestError;
            break;
    }
}

void StageTest::send_test_message(Message::Type type, uint32_t oms, uint32_t ous, int padding) {
    send_message(type, send_count++, oms, ous, padding);

    switch(type) {
        case Message::Ping:
            ping_count++;
            break;
        case Message::Pong:
            pong_count++;
            break;
        default:
            break;
    }
}

void StageTest::update(uint32_t time, ButtonState buttons) {
    if (buttons.pressed(blit::Button::B)) {
        finish(std::make_shared<StageMenu>());
        send_test_message(Message::EndTest);
    } else if (!blit::is_multiplayer_connected()) {
        finish(std::make_shared<StageMenu>());
    }
}

void StageTest::render() {
    blit::screen.pen = blit::Pen(0, 0, 0);
    blit::screen.clear();
    blit::screen.pen = blit::Pen(255, 255, 255);
    char buffer[100];
#define X 22
#define Y 20
    blit::screen.text("      Sent   Received       Ping       Pong", blit::minimal_font, blit::Point(X, Y), false);
    snprintf(buffer, 100, "%10" PRIu32 " %10" PRIu32 " %10" PRIu32 " %10" PRIu32 "", send_count, recv_count, ping_count, pong_count);
    blit::screen.text(buffer, blit::minimal_font, blit::Point(X, Y+10), false);
    blit::screen.text("   Latency (ms)   Min        Max        Ave", blit::minimal_font, blit::Point(X, Y+30), false);
    snprintf(buffer, 100, "           %10.1f %10.1f %10.1f", (double)(lat_min/1000.0), (double)(lat_max/1000.0), (double)(lat_ave/1000.0));
    blit::screen.text(buffer, blit::minimal_font, blit::Point(X, Y+40), false);
}
