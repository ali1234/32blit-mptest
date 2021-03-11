#pragma once

#include "StageTest.hpp"

class StagePing : public StageTest {
    public:
        void update(uint32_t time, ButtonState buttons) override;
        void render() override;
        void on_message(const Message &message) override;
    private:
        bool started = false;
};
