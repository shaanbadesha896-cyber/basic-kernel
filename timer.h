#pragma once
#include "cstdint.h"

    extern "C" void timer();

    bool hasSecondpassed();

    void pause(uint32_t seconds_to_wait);