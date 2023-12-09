/*
 * CanIdMap.cpp
 *
 * Created: 23-01-2021 17:18:15
 *  Author: Toolsbox
 */

#include "CanIdMap.h"

#define HEATPUMP

#ifdef HEATPUMP
TIdMap IdMap[] =
{
    // Device	00 00xx xxxx xxxx xxxx
    // Pump = 0x01, Aux = 0x20, Main = 0x10, CPU = 0x00, Power1 = 0x30, Power2 = 0x60,
    // Pin		xx xx00 0000 0000 0000
    // Main		pin+1
    { 0x10000010, "HP_Temp_HeatWater",		1, TIdMap::eType::AI, TIdMap::eSubType::Temp }, // main AI 1 - T1
    { 0x10004010, "HP_Temp_Outdoor",		2, TIdMap::eType::AI, TIdMap::eSubType::Temp }, // Main AI 2 - T2
    { 0x10008010, "HP_Temp_HotWater",		3, TIdMap::eType::AI, TIdMap::eSubType::Temp }, // Main AI 3 - T3
    { 0x08030010, "HP_DO_LowHighValve",		3, TIdMap::eType::DO, TIdMap::eSubType::None }, // Main DO 3 - Q1
    // Aux		pin-4
    { 0x08014020, "HP_DO_AUX1",				1, TIdMap::eType::DO, TIdMap::eSubType::None }, // AUX DO 1 - Q1
    // Pump
    { 0x08028001, "HP_DO_PumpHeater",		1, TIdMap::eType::DO, TIdMap::eSubType::None }, // Pump DO 1 - E3
    { 0x0802C001, "HP_DO_Fan",				2, TIdMap::eType::DO, TIdMap::eSubType::None }, // Pump DO 2 - G3
    { 0x08030001, "HP_DO_4WaySwitch",		3, TIdMap::eType::DO, TIdMap::eSubType::None }, // Pump DO 3 - Q3
    { 0x08034001, "HP_DO_Heatcabel",		4, TIdMap::eType::DO, TIdMap::eSubType::None }, // Pump DO 4 - E4
    { 0x08038001, "HP_DO_Compressor",		5, TIdMap::eType::DO, TIdMap::eSubType::None }, // Pump DO 5 - K1 R1
    { 0x08018001, "HP_DI_PressostatHigh",	1, TIdMap::eType::DI, TIdMap::eSubType::None }, // Pump DI 1 - HP
    { 0x0801C001, "HP_DI_PumpSafty",		2, TIdMap::eType::DI, TIdMap::eSubType::None }, // Pump DI 2 - MB1 B1
    { 0x08020001, "HP_DI_Fase",				3, TIdMap::eType::DI, TIdMap::eSubType::None }, // Pump DI 3 - L
    { 0x08024001, "HP_DI_PressostatLow",	4, TIdMap::eType::DI, TIdMap::eSubType::None }, // Pump DI 4 - LPL
    { 0x10000001, "HP_Temp_Compressor",		1, TIdMap::eType::AI, TIdMap::eSubType::Temp }, // Pump AI 1 - T6
    { 0x10004001, "HP_Temp_HeatOut",		2, TIdMap::eType::AI, TIdMap::eSubType::Temp }, // Pump AI 2 - T8
    { 0x10008001, "HP_Temp_HeatIn",			3, TIdMap::eType::AI, TIdMap::eSubType::Temp }, // Pump AI 3 - T9
    { 0x1000C001, "HP_Temp_Condensor",		4, TIdMap::eType::AI, TIdMap::eSubType::Temp }, // Pump AI 4 - T10
    { 0x10010001, "HP_Temp_Evaporator",		5, TIdMap::eType::AI, TIdMap::eSubType::Temp }, // Pump AI 5 - T11
    { 0x10014001, "HP_Temp_AirIn",			6, TIdMap::eType::AI, TIdMap::eSubType::Temp }, // Pump AI 6 - T12
};
#endif

#ifdef SOLAR
TIdMap IdMap[] =
{
    // Device	0000 0xxx xxxx
    // PC		0000 0000 1010 A
    // UVR4411	0000 0000 0001 1
    // IO44		0000 0001 0000 20
    // Bootloader 0000 0011 1110 3E

    // Selector xxxx x000 0000
    // DIO 1-16	0001 1000 0000 180
    // AIO 1-4  0010 0000 0000 200
    // AIO 5-8  0010 1000 0000 280
    // AIO 9-12 0011 0000 0000 300
    // AIO 13-15 0011 1000 0000 380
    { 0x0000 + 0x200 + 0x1, "S_AI_1_SunCollector",	1, TIdMap::eType::AI, TIdMap::eSubType::Temp }, // UVR1611
    { 0x1000 + 0x200 + 0x1, "S_AI_2_SunExcPriIn",	2, TIdMap::eType::AI, TIdMap::eSubType::Temp }, // UVR1611
    { 0x2000 + 0x200 + 0x1, "S_AI_3_BufferBottom",	3, TIdMap::eType::AI, TIdMap::eSubType::Temp }, // UVR1611
    { 0x3000 + 0x200 + 0x1, "S_AI_4_BufferLow",		4, TIdMap::eType::AI, TIdMap::eSubType::Temp }, // UVR1611

    { 0x4000 + 0x280 + 0x1, "S_AI_5_BufferHigh",	5, TIdMap::eType::AI, TIdMap::eSubType::Temp }, // UVR1611
    { 0x5000 + 0x280 + 0x1, "S_AI_6_BufferTop",		6, TIdMap::eType::AI, TIdMap::eSubType::Temp }, // UVR1611
    { 0x6000 + 0x280 + 0x1, "S_AI_7_HotWater",		7, TIdMap::eType::AI, TIdMap::eSubType::HotWaterTemp }, // UVR1611
    { 0x7000 + 0x280 + 0x1, "S_AI_8_HPIn",			8, TIdMap::eType::AI, TIdMap::eSubType::Temp }, // UVR1611

    { 0x8000 + 0x300 + 0x1, "S_AI_9_SunExcSecOut",	9, TIdMap::eType::AI, TIdMap::eSubType::Temp }, // UVR1611
    { 0x9000 + 0x300 + 0x1, "S_AI_10_FloorPre",		10, TIdMap::eType::AI, TIdMap::eSubType::Temp }, // UVR1611
    { 0xA000 + 0x300 + 0x1, "S_AI_11_HPOut",		11, TIdMap::eType::AI, TIdMap::eSubType::Temp }, // UVR1611
    { 0xB000 + 0x300 + 0x1, "S_AI_12_Outdoor",		12, TIdMap::eType::AI, TIdMap::eSubType::Temp }, // UVR1611

    { 0xC000 + 0x380 + 0x1, "S_AI_13_Indoor",		13, TIdMap::eType::AI, TIdMap::eSubType::IndoorTemp }, // UVR1611
    { 0xD000 + 0x380 + 0x1, "S_AI_14_HPFlow",		14, TIdMap::eType::AI, TIdMap::eSubType::Flow }, // UVR1611
    { 0xE000 + 0x380 + 0x1, "S_AI_15_SunExcPriOut", 15, TIdMap::eType::AI, TIdMap::eSubType::Temp }, // UVR1611
    { 0xF000 + 0x380 + 0x1, "S_AI_16_SunFlow",		16, TIdMap::eType::AI, TIdMap::eSubType::Flow }, // UVR1611

    { 0x0000 + 0x180 + 0x1, "S_DO_1_SunPump1",		1, TIdMap::eType::DO, TIdMap::eSubType::None }, // UVR1611
    { 0x1000 + 0x180 + 0x1, "S_DO_2_SunPump2",		2, TIdMap::eType::DO, TIdMap::eSubType::None }, // UVR1611
    { 0x2000 + 0x180 + 0x1, "S_DO_3_FloorPump",		3, TIdMap::eType::DO, TIdMap::eSubType::None }, // UVR1611
    { 0x3000 + 0x180 + 0x1, "S_DO_4_SunValve",		4, TIdMap::eType::DO, TIdMap::eSubType::None }, // UVR1611
    { 0x4000 + 0x180 + 0x1, "S_DO_5_Heatpump",		5, TIdMap::eType::DO, TIdMap::eSubType::None }, // UVR1611
    { 0x5000 + 0x180 + 0x1, "S_DO_6_HeatpumpPump",	6, TIdMap::eType::DO, TIdMap::eSubType::None }, // UVR1611
    { 0x6000 + 0x180 + 0x1, "S_DO_7_HotWaterPump",	7, TIdMap::eType::DO, TIdMap::eSubType::None }, // UVR1611
    { 0x7000 + 0x180 + 0x1, "S_DO_8_FloorValveOn",	8, TIdMap::eType::DO, TIdMap::eSubType::None }, // UVR1611
    { 0x8000 + 0x180 + 0x1, "S_DO_9_FloorValveOff", 9, TIdMap::eType::DO, TIdMap::eSubType::None }, // UVR1611
    { 0x9000 + 0x180 + 0x1, "S_DO_10_HotWaterRetPump", 10, TIdMap::eType::DO, TIdMap::eSubType::None }, // UVR1611

    { 0x2000 + 0x180 + 0xA, "PC_DO_3_FloorPump",	3, TIdMap::eType::DO, TIdMap::eSubType::None }, // PC
    { 0x3000 + 0x180 + 0xA, "PC_DO_4_SunValve",		4, TIdMap::eType::DO, TIdMap::eSubType::None }, // PC
    { 0x4000 + 0x180 + 0xA, "PC_DO_5_Heatpump",		5, TIdMap::eType::DO, TIdMap::eSubType::None }, // PC
    { 0x7000 + 0x180 + 0xA, "PC_DO_8_FloorValveOn", 8, TIdMap::eType::DO, TIdMap::eSubType::None }, // PC
    { 0x8000 + 0x180 + 0xA, "PC_DO_9_FloorValveOff", 9, TIdMap::eType::DO, TIdMap::eSubType::None }, // PC
    { 0x9000 + 0x180 + 0xA, "PC_DO_10_HotWaterRetPump", 10, TIdMap::eType::DO, TIdMap::eSubType::None }, // PC

    { 0x0000 + 0x200 + 0x1, "S_AO_1_SunPump1",		1, TIdMap::eType::AO, TIdMap::eSubType::PWMValue }, // UVR1611
    { 0x1000 + 0x200 + 0x1, "S_AO_2_SunPump2",		2, TIdMap::eType::AO, TIdMap::eSubType::PWMValue }, // UVR1611
    { 0x5000 + 0x280 + 0x1, "S_AO_6_HeatpumpPump",	6, TIdMap::eType::AO, TIdMap::eSubType::PWMValue }, // UVR1611
    { 0x6000 + 0x280 + 0x1, "S_AO_7_HotWaterPump",	7, TIdMap::eType::AO, TIdMap::eSubType::PWMValue }, // UVR1611

    { 0x0000 + 0x200 + 0xA, "PC_AO_1_SunPump1",		1, TIdMap::eType::AO, TIdMap::eSubType::PWMValue }, // PC
    { 0x1000 + 0x200 + 0xA, "PC_AO_2_SunPump2",		2, TIdMap::eType::AO, TIdMap::eSubType::PWMValue }, // PC
    { 0x5000 + 0x280 + 0xA, "PC_AO_6_HeatpumpPump", 6, TIdMap::eType::AO, TIdMap::eSubType::PWMValue }, // PC
    { 0x6000 + 0x280 + 0xA, "PC_AO_7_HotWaterPump", 7, TIdMap::eType::AO, TIdMap::eSubType::PWMValue }, // PC

    { 0x0000 + 0x200 + 0x20, "S_AI_1_HotWaterRet",	1, TIdMap::eType::AI, TIdMap::eSubType::Temp }, // IO44_32
    { 0x1000 + 0x200 + 0x20, "S_AI_2_AI2",			2, TIdMap::eType::AI, TIdMap::eSubType::Temp }, // IO44_32
    { 0x2000 + 0x200 + 0x20, "S_AI_3_AI3",			3, TIdMap::eType::AI, TIdMap::eSubType::Temp }, // IO44_32
    { 0x3000 + 0x200 + 0x20, "S_DI_4_ELCnt",		4, TIdMap::eType::DI, TIdMap::eSubType::None }, // IO44_32

    { 0x4000 + 0x280 + 0x20, "S_AO_5_AO1",			5, TIdMap::eType::AO, TIdMap::eSubType::V0_10 }, // IO44_32
    { 0x5000 + 0x280 + 0x20, "S_AO_6_AO2",			6, TIdMap::eType::AO, TIdMap::eSubType::V0_10 }, // IO44_32

    { 0x4000 + 0x280 + 0xA, "PC_AO_5_AO1",			5, TIdMap::eType::AO, TIdMap::eSubType::V0_10 }, // PC
    { 0x5000 + 0x280 + 0xA, "PC_AO_6_AO2",			6, TIdMap::eType::AO, TIdMap::eSubType::V0_10 }, // PC

    { 0x4000 + 0x180 + 0x20, "S_DO_5_DO1",			5, TIdMap::eType::DO, TIdMap::eSubType::None }, // IO44_32
    { 0x5000 + 0x180 + 0x20, "S_DO_6_DO2",			6, TIdMap::eType::DO, TIdMap::eSubType::None }, // IO44_32
    { 0x6000 + 0x180 + 0x20, "S_DO_7_DO3",			7, TIdMap::eType::DO, TIdMap::eSubType::None }, // IO44_32
};
#endif

const uint8_t IdMap_Len =  sizeof( IdMap ) / sizeof( TIdMap );
//uint8_t IdMapSize() { return (sizeof(IdMap)/sizeof(TIdMap); };
