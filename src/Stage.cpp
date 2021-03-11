// mptest - Stage.cpp
// Copyright (c) 2021 Alistair Buxton <a.j.buxton@gmail.com>
// GPL-3.0-or-later

#include "Stage.hpp"


void Stage::change(StagePtr next) {
    _next = next;
    _changed = true;
}

void Stage::finish(StagePtr next) {
    change(next);
    _finished = true;
}

bool Stage::changed() const {
    return _changed;
}

bool Stage::finished() const {
    return _finished;
}

StagePtr Stage::next() {
    _changed = false;
    StagePtr __next = _next;
    _next = nullptr;
    return __next;
}


