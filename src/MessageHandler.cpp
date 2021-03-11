// mptest - MessageHandler.cpp
// Copyright (c) 2021 Alistair Buxton <a.j.buxton@gmail.com>
// GPL-3.0-or-later

#include "32blit.hpp"

#include "MessageHandler.hpp"

void MessageHandler::on_raw_message(const uint8_t *data, const uint16_t length) {
    if (length < sizeof(Message)) return;
    Message &message = *((Message*)data);
    if(message.id != Message::_id || message.version != Message::_version) return;
    on_message(message);
}

void MessageHandler::on_message(const Message &message) {
    time_since_received = 0;
    mp_state |= Linked;
}

void MessageHandler::send_raw_message(const uint8_t *message, int length) {
    if (blit::is_multiplayer_connected()) {
        blit::send_message(message, length);
    }
}

void MessageHandler::send_message(Message::Type type, uint32_t seq, uint32_t oms, uint32_t ous, int padding) {
    Message m;
    m.type = type;
    m.seq = seq;
    m.ms = blit::now();
    m.us = blit::now_us();
    m.oms = oms;
    m.ous = ous;
    send_raw_message((uint8_t *)&m, sizeof(Message));
}




void MessageHandler::debug() {
    char status[10];
    blit::screen.pen = blit::Pen(255, 255, 255);
    snprintf(status, 10, "%c%c%c%c",
            blit::is_multiplayer_connected() ? 'M' : '-',
             (mp_state & Linked) ? 'L' : '-',
             (mp_state & TestError) ? 'E' : '-',
             (mp_state & SyncError) ? 'S' : '-'
    );
    blit::screen.text(status, blit::minimal_font, {160, 228}, false, blit::TextAlign::center_h);
}

