#pragma once

#include <memory>
#include "32blit.hpp"
#include "MessageHandler.hpp"

#include "ButtonState.hpp"

class Stage;

typedef std::shared_ptr<Stage> StagePtr;

class Stage : public std::enable_shared_from_this<Stage>, public MessageHandler {
    public:
        virtual ~Stage() = default;

        virtual void update(uint32_t, ButtonState) {};
        virtual void render() {};

        StagePtr next();
        bool finished() const;
        bool changed() const;

    protected:
        void finish(StagePtr next);
        void change(StagePtr next);

    private:
        bool _finished = false;
        bool _changed = false;
        StagePtr _next = nullptr;
};
