/*
 * CanIdMap.h
 *
 * Created: 23-01-2021 16:54:32
 *  Author: Toolsbox
 */


#ifndef CANIDMAP_H_
#define CANIDMAP_H_

#include <stdint.h>

struct TIdMap
{
    enum eType
    {
        UnknowenT = 0,
        IT = 1,
        DI = 2,
        DO = 3,
        AI = 4,
        AO = 5
    };
    enum eSubType
    {
        None = 0,
        Temp = 1,
        IndoorTemp = 2,
        HotWaterTemp = 3,
        Flow = 4,
        Alive = 5,
        Info = 6,
        V0_10 = 7,
        m0_10 = 8,
        PWMPct = 9,
        PWMValue = 10
    };

    uint32_t Id;
    const char *Connection;
    uint8_t Pin;
    eType Type;
    eSubType SubType;
};

extern TIdMap IdMap[];
extern const uint8_t IdMap_Len;

#endif /* CANIDMAP_H_ */