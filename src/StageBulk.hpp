#pragma once

#include "StageTest.hpp"


class StageBulk : public StageTest {
    public:
        void update(uint32_t time, ButtonState buttons) override;
        void render() override;
};
