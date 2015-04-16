//
//  smpkeys.h
//  btle
//
//  Created by Erkki  on 14/04/15.
//  Copyright (c) 2015 Erkki Silvola. All rights reserved.
//

#ifndef btle_smpkeys_h
#define btle_smpkeys_h

#include "btle/base.h"

namespace btle {

    #define SMP_LRANDOM_LEN 8
    #define SMP_LTK_LEN 16

    class smpkeys: public base
    {
    public:
        smpkeys();
        smpkeys(uint16_t ldiversifier,
                uint8_t  lrandom[SMP_LRANDOM_LEN],
                uint8_t  ltk[SMP_LTK_LEN]);
        smpkeys(const smpkeys& other);

    private:

        uint16_t ldiversifier_;
        uint8_t  lrandom_[SMP_LRANDOM_LEN];
        uint8_t  ltk_[SMP_LTK_LEN];
    };
}

#endif
