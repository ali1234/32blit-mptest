#pragma once

#include <cstdint>

#include "engine/multiplayer.hpp"

#ifndef ID
#define ID 0x73577357
#endif
#ifndef VERSION
#define VERSION 0
#endif


#pragma pack(push, 1)
struct Message {
    enum Type : uint32_t {
        Ping,
        Pong,
        Bulk,
        StartTestBulk,
        StartTestPing,
        EndTest,
        SyncError,
        TestError,
    };

    static constexpr uint32_t _id = ID;
    static constexpr uint32_t _version = VERSION;
    uint32_t id = _id;
    uint32_t version = _version;
    uint32_t type;
    uint32_t seq;
    uint32_t ms;
    uint32_t us;
    uint32_t oms;
    uint32_t ous;
    uint8_t data[];
};
#pragma pack(pop)
static_assert(sizeof(Message) == 32);

class MessageHandler {

    public:
        enum State : uint8_t {
            Unlinked = 0,
            Linked = 1,
            SyncError = 2,
            TestError = 4,
        };

        // Implement this to handle messages.
        virtual void on_message(const Message &message);
        static void debug();

    private:
        inline static uint32_t time_since_received = 0;

    protected:
        void on_raw_message(const uint8_t *data, const uint16_t length);
        friend void on_message(const uint8_t *data, uint16_t len);

        static void send_raw_message(const uint8_t *message, int length) ;
        static void send_message(Message::Type type, uint32_t seq, uint32_t oms, uint32_t ous, int padding = 0);

        inline static uint8_t mp_state = Unlinked;
};
