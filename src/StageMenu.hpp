#pragma once

#include "Stage.hpp"
#include "Menu.hpp"

class StageMenu : public Stage {
    public:
        void update(uint32_t time, ButtonState buttons) override;
        void render() override;
        void on_message(const Message &message) override;
    private:
        const static inline std::vector<const char *> items = {"Bulk Test", "Ping Pong Test"};
        Menu menu = Menu(items);
};
