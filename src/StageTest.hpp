#pragma once

#include "StageMenu.hpp"

class StageTest : public StageMenu {
    public:
        void update(uint32_t time, ButtonState buttons) override;
        void render() override;
        void on_message(const Message &message) override;
    protected:
        uint32_t recv_count = 0, send_count = 0, ping_count = 0, pong_count = 0;
        uint32_t lat_min = 0xffffffff, lat_max = 0, lat_ave = 1000;
        void send_test_message(Message::Type type, uint32_t oms = 0, uint32_t ous = 0, int padding = 0);
};
