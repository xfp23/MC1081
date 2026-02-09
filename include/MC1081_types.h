/**
 * @file MC1081_types.h
 * @author https://github.com/xfp23
 * @brief
 * @version 0.1
 * @date 2026-02-05
 *
 * @copyright Copyright (c) 2026
 *
 */
#ifndef __MC1081_TYPES_H__
#define __MC1081_TYPES_H__

#include "stdint.h"
#include "stdbool.h"
#include "stdlib.h"

#ifdef __cplusplus
extern "C"
{
#endif

typedef enum
{
    MC1081_OK,
    MC1081_ERR,
    MC1081_PARAM_ERR,
    MC1081_WR_ERR,
    MC1081_RR_ERR,
    MC1081_MEM_ERR,
} MC1081_Status_t;

typedef enum
{
    MC1081_FINDIV_1,
    MC1081_FINDIV_2,
    MC1081_FINDIV_4,
    MC1081_FINDIV_8,
    MC1081_FINDIV_16,
    MC1081_FINDIV_32,
    MC1081_FINDIV_64,
} MC1081_FinDIV_t;

typedef enum
{
    MC1081_FREFDIV_1,
    MC1081_FREFDIV_2,
    MC1081_FREFDIV_4,
    MC1081_FREFDIV_8,
} MC1081_FrefDIV_t;

typedef enum
{
    MC1081_FIN_BUILD_1_CYCLE, // 1 个 FIN 周期建立时间
    MC1081_FIN_BUILD_4_CYCLE, // 4 个 FIN 周期建立时间
} MC1081_FinBuildCycle_t;

typedef enum
{
    MC1081_DCH_0,
    MC1081_DCH_1,
    MC1081_DCH_2,
    MC1081_DCH_3,
    MC1081_DCH_4,
    MC1081_DCH_5,
    MC1081_DCH_6,
    MC1081_DCH_7,
    MC1081_DCH_8,
    MC1081_DCH_9,
    MC1081_DCH_REF, // 基准数据
} MC1081_Channel_t;

typedef enum
{
    MC1081_DCH_DIFF_0,
    MC1081_DCH_DIFF_1,
    MC1081_DCH_DIFF_2,
    MC1081_DCH_DIFF_3,
    MC1081_DCH_DIFF_4,
    MC1081_DCH_DIFF_REF, // 参比通道
} MC1081_Channel_Diff_t;

typedef enum
{
    MC1081_DCH_SING_0,
    MC1081_DCH_SING_1,
    MC1081_DCH_SING_2,
    MC1081_DCH_SING_3,
    MC1081_DCH_SING_4,
    MC1081_DCH_SING_5,
    MC1081_DCH_SING_6,
    MC1081_DCH_SING_7,
    MC1081_DCH_SING_8,
    MC1081_DCH_SING_9,
    MC1081_DCH_SING_REF, // 参比通道

} MC1081_Channel_Single_t;

typedef enum
{
    MC1081_MCH_SING_0,
    MC1081_MCH_SING_1,
    MC1081_MCH_SING_2,
    MC1081_MCH_SING_3,
    MC1081_MCH_SING_4,
} MC1081_Channel_MCH_t; // 互电容通道

typedef enum
{
    MC1081_TEMP_CONV_OFF = 0,
    MC1081_TEMP_CONV_ON,
} MC1081_TempConvState_t;

typedef enum
{
    MC1081_ACTIVE_SHIELD_OFF,
    MC1081_ACTIVE_SHIELD_ON,
}MC1081_ActiveShieldState_t; // 有源屏蔽开关

typedef enum
{
    MC1081_SHIELD_PWR_LOW,
    MC1081_SHIELD_PWR_HIGH,
}MC1081_ActiveShieldPwr_t;

typedef enum
{
    MC1081_SHIELD_HIGHRES, // 表示电容测量端口在非测量期间为高阻状态
    MC1081_SHIELD_GND, // 表示电容测量端口在非测量期间为接地状态
} MC1081_ActiveShieldSel_t;

typedef enum
{
    MC1081_TEMP_TIME_0P3_MS,
    MC1081_TEMP_TIME_1P7_MS,
} MC1081_TempTime_t;

/* 电容振荡输入模式 */
typedef enum
{
    MC1081_CAP_OSC_SINGLE, // 单端模式
    MC1081_CAP_OSC_DIFF,   // 差分模式
} MC1081_CapOscMode_t;

/* 电容测量时间间隔 */
typedef enum
{
    MC1081_CAP_TIME_10S,  // 每 10 s 测量一次
    MC1081_CAP_TIME_1S,   // 每 1 s 测量一次
    MC1081_CAP_TIME_0P1S, // 每 0.1 s 测量一次
    MC1081_CAP_TIME_CONT, // 连续测量
} MC1081_CapTime_t;

/* 频率计数周期平均次数 */
typedef enum
{
    MC1081_CAP_AVG_1,  // 1 次平均
    MC1081_CAP_AVG_4,  // 4 次平均
    MC1081_CAP_AVG_8,  // 8 次平均
    MC1081_CAP_AVG_32, // 32 次平均
} MC1081_CapAvgCycle_t;

/* 电容测量启动控制 */
typedef enum
{
    MC1081_CAP_START_PERIODIC, // 周期测量启动
    MC1081_CAP_START_RESERVED, // 保留
    MC1081_CAP_START_STOP,     // 停止测量
    MC1081_CAP_START_SINGLE,   // 单次测量
} MC1081_CapStartMode_t;

/* 芯片睡眠控制 */
typedef enum
{
    MC1081_CHIP_SLEEP_OFF, // 禁止睡眠
    MC1081_CHIP_SLEEP_ON,  // 使能睡眠
} MC1081_ChipSleep_t;

typedef enum
{
    MC1081_DRCU_4UA,
    MC1081_DRCU_8UA,
    MC1081_DRCU_16UA,
    MC1081_DRCU_42UA,
    MC1081_DRCU_100UA,
    MC1081_DRCU_250UA,
    MC1081_DRCU_500UA,
    MC1081_DRCU_1000UA,
    MC1081_DRCU_2000UA,
} MC1081_DriverCu_t; // 驱动电流

typedef enum
{
    MC1081_AMPOS1_0_2,     // 幅度为 0.2V（内部 LDO 供电）
    MC1081_AMPOS1_0_4,     // 幅度为 0.4V（内部 LDO 供电）
    MC1081_AMPOS1_0_8,     // 幅度为 0.8V（内部 LDO 供电）
    MC1081_AMPOS1_1_2,     // 幅度为 1.2V（内部 LDO 供电）
    MC1081_AMPOS1_2_2_VDD, // 幅度为 2.2V（VDD 供电）
    MC1081_AMPOS1_1_6_VDD, // 幅度为 1.6V（VDD 供电）
    MC1081_AMPOS1_1_2_VDD, // 幅度为 0.2V（VDD 供电）
    MC1081_AMPOS1_0_8_VDD, // 幅度为 0.2V（VDD 供电）
} MC1081_AmplituOS1_t;

typedef enum
{
    MC1081_AMPOS2_0_2, // 幅度为 0.2V（内部 LDO 供电）
    MC1081_AMPOS2_0_4, // 幅度为 0.4V（内部 LDO 供电）
    MC1081_AMPOS2_0_8, // 幅度为 0.8V（内部 LDO 供电）
    MC1081_AMPOS2_1_2, // 幅度为 1.2V（内部 LDO 供电）
    MC1081_AMPOS2_1_6, // 幅度为 1.6V（内部 LDO 供电）
    MC1081_AMPOS2_2_0, // 幅度为 2.0V（内部 LDO 供电）
    MC1081_AMPOS2_2_4, // 幅度为 2.4V（内部 LDO 供电）
} MC1081_AmplituOS2_t;

typedef enum
{
    MC1081_PWR_LOW,  // ldo 低功率模式
    MC1081_PWR_HIGH, // ldo 大功率模式
} MC1081_LdoPwr_t;

/* 电容测量配置结构体 */
typedef struct
{
    MC1081_CapOscMode_t osc_mode;   // 振荡输入模式
    MC1081_CapTime_t interval;      // 测量时间间隔
    MC1081_CapAvgCycle_t avg_cycle; // 周期平均次数
    MC1081_ChipSleep_t sleep;       // 睡眠控制
    MC1081_CapStartMode_t start;    // 启动/停止控制
} MC1081_CapConvConfig_t;

typedef struct
{
    MC1081_FinDIV_t fin_div;          // 时钟分频比
    MC1081_FrefDIV_t fref_div;        // 参考时钟分频
    MC1081_FinBuildCycle_t fin_build; // 建立周期时间
} MC1081_ClockCfg_t;

typedef union
{
    struct __attribute__((packed))
    {
        uint16_t ch0 : 1;    // 单端通道 0 使能 1:使能 0:禁用
        uint16_t ch1 : 1;    // 单端通道 1 使能 1:使能 0:禁用
        uint16_t ch2 : 1;    // 单端通道 2 使能 1:使能 0:禁用
        uint16_t ch3 : 1;    // 单端通道 3 使能 1:使能 0:禁用
        uint16_t ch4 : 1;    // 单端通道 4 使能 1:使能 0:禁用
        uint16_t ch5 : 1;    // 单端通道 5 使能 1:使能 0:禁用
        uint16_t ch6 : 1;    // 单端通道 6 使能 1:使能 0:禁用
        uint16_t ch7 : 1;    // 单端通道 7 使能 1:使能 0:禁用
        uint16_t ch8 : 1;    // 单端通道 8 使能 1:使能 0:禁用
        uint16_t ch9 : 1;    // 单端通道 9 使能 1:使能 0:禁用
        uint16_t ch_ref : 1; // 单端参比通道使能 1:使能 0:禁用
        uint16_t : 5;        // 保留位，必须写 0
    } bits;

    uint16_t value; // 原始 16-bit 寄存器值

} MC1081_ChSingleEn_t;

typedef union
{
    struct __attribute__((packed))
    {
        uint8_t ch1 : 1;    // 双端通道 1 使能 1:使能 0:禁用
        uint8_t ch2 : 1;    // 双端通道 2 使能 1:使能 0:禁用
        uint8_t ch3 : 1;    // 双端通道 3 使能 1:使能 0:禁用
        uint8_t ch4 : 1;    // 双端通道 4 使能 1:使能 0:禁用
        uint8_t ch5 : 1;    // 双端通道 5 使能 1:使能 0:禁用
        uint8_t ch_ref : 1; // 双端参比通道使能 1:使能 0:禁用
        uint8_t : 2;
    } bits;

    uint8_t value; // 原始 16-bit 寄存器值
} MC1081_ChDiffEn_t;

typedef union
{
    struct __attribute__((packed))
    {
        uint8_t Mch1 : 1; // 单端通道 1 使能 1:使能 0:禁用
        uint8_t Mch2 : 1; // 单端通道 2 使能 1:使能 0:禁用
        uint8_t Mch3 : 1; // 单端通道 3 使能 1:使能 0:禁用
        uint8_t Mch4 : 1; // 单端通道 4 使能 1:使能 0:禁用
        uint8_t Mch5 : 1; // 单端通道 5 使能 1:使能 0:禁用
        uint8_t : 3;      // 保留位，必须写 0
    } bits;

    uint8_t value; // 原始 16-bit 寄存器值
} MC1081_MchEn_t;  // 互电容

typedef struct
{
    MC1081_DriverCu_t dr_cu;       // 驱动电流选择
    MC1081_AmplituOS1_t amplitude; // 振幅
    MC1081_LdoPwr_t ldo;           // ldo功率
} MC1081_SingleOSCCfg_t;

typedef struct
{
    MC1081_DriverCu_t dr_cu;       // 驱动电流选择
    MC1081_AmplituOS2_t amplitude; // 振幅
    MC1081_LdoPwr_t ldo;           // ldo功率
} MC1081_DiffOSCCfg_t;

typedef struct 
{
    MC1081_ActiveShieldState_t en; // 开关
    MC1081_ActiveShieldPwr_t pwr; // 功率
    MC1081_ActiveShieldSel_t sel; // 状态选择
}MC1081_ActiveShielCfg;

typedef union 
{
    struct __attribute__((packed)) {
        uint8_t GND :1;
        uint8_t VDD :1;
        uint8_t SDA :1;
        uint8_t SCL :1;
        uint8_t RSV :4; 
    }bits;

    uint8_t value;

}MC1081_AddrSel_t;

typedef int (*MC1081_TransmitFunc_t)(uint8_t *data, size_t len);

typedef int (*MC1081_ReceiveFunc_t)(uint8_t *dst, size_t len);

typedef struct
{
    MC1081_TransmitFunc_t Transmit;
    MC1081_ReceiveFunc_t Receive;
} MC1081_Conf_t;

typedef struct
{
    MC1081_Conf_t conf;
    uint8_t I2c_addr;
} MC1081_Obj_t;

typedef MC1081_Obj_t *MC1081_Handle_t;

#ifdef __cplusplus
}
#endif

#endif

