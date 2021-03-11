// mptest - Main.cpp
// Copyright (c) 2021 Alistair Buxton <a.j.buxton@gmail.com>
// GPL-3.0-or-later

#include "32blit.hpp"
#include "engine/multiplayer.hpp"

#include "Stage.hpp"
#include "StageMenu.hpp"


static ButtonState buttons;
static uint32_t prev_update;

static StagePtr stage = nullptr;

void on_message(const uint8_t *data, uint16_t len) {
    stage->on_raw_message(data, len);
}

void init() {
    blit::set_screen_mode(blit::ScreenMode::hires);
    stage = std::make_shared<StageMenu>();
    buttons.update(blit::buttons);
    prev_update = blit::now();

    blit::message_received = on_message;
    blit::enable_multiplayer();
}

void update(uint32_t time) {
    uint32_t time_delta = time - prev_update;
    if (time_delta > 100) time_delta = 20;
    if (time_delta > 0) {
        buttons.update(blit::buttons);
        stage->update(time_delta, buttons);
        if (stage->changed()) stage = stage->next();
        prev_update = time;
    }
}

void render(uint32_t /* time */) {
    stage->render();
    stage->debug();
}


