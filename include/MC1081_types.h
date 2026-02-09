/**
 * @file MC1081_types.h
 * @author https://github.com/xfp23
 * @brief Type definitions for MC1081 capacitive sensing driver
 * @version 0.1
 * @date 2026-02-05
 *
 * @copyright Copyright (c) 2026
 *
 * This file defines all public types, enums, and data structures used by
 * the MC1081 driver. No hardware access logic is implemented here.
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

/**
 * @brief Driver return status definition
 *
 * Note:
 * - MC1081_MEM_ERR is only expected to be returned by MC1081_Init()
 */
typedef enum
{
    MC1081_OK,        /**< Operation successful */
    MC1081_ERR,       /**< Generic error */
    MC1081_PARAM_ERR, /**< Invalid parameter */
    MC1081_WR_ERR,    /**< Register write error */
    MC1081_RR_ERR,    /**< Register read error */
    MC1081_MEM_ERR,   /**< Memory allocation failure */
} MC1081_Status_t;

/**
 * @brief FIN clock divider selection
 */
typedef enum
{
    MC1081_FINDIV_1,   /**< FIN / 1 */
    MC1081_FINDIV_2,   /**< FIN / 2 */
    MC1081_FINDIV_4,   /**< FIN / 4 */
    MC1081_FINDIV_8,   /**< FIN / 8 */
    MC1081_FINDIV_16,  /**< FIN / 16 */
    MC1081_FINDIV_32,  /**< FIN / 32 */
    MC1081_FINDIV_64,  /**< FIN / 64 */
} MC1081_FinDIV_t;

/**
 * @brief Reference clock divider selection
 */
typedef enum
{
    MC1081_FREFDIV_1, /**< FREF / 1 */
    MC1081_FREFDIV_2, /**< FREF / 2 */
    MC1081_FREFDIV_4, /**< FREF / 4 */
    MC1081_FREFDIV_8, /**< FREF / 8 */
} MC1081_FrefDIV_t;

/**
 * @brief FIN signal build-up cycle selection
 */
typedef enum
{
    MC1081_FIN_BUILD_1_CYCLE, /**< Build time of 1 FIN cycle */
    MC1081_FIN_BUILD_4_CYCLE, /**< Build time of 4 FIN cycles */
} MC1081_FinBuildCycle_t;

/**
 * @brief Generic channel index definition
 */
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
    MC1081_DCH_REF, /**< Reference channel */
} MC1081_Channel_t;

/**
 * @brief Differential channel index definition
 */
typedef enum
{
    MC1081_DCH_DIFF_0,
    MC1081_DCH_DIFF_1,
    MC1081_DCH_DIFF_2,
    MC1081_DCH_DIFF_3,
    MC1081_DCH_DIFF_4,
    MC1081_DCH_DIFF_REF, /**< Differential reference channel */
} MC1081_Channel_Diff_t;

/**
 * @brief Single-ended channel index definition
 */
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
    MC1081_DCH_SING_REF, /**< Single-ended reference channel */
} MC1081_Channel_Single_t;

/**
 * @brief Mutual-capacitance channel index definition
 */
typedef enum
{
    MC1081_MCH_SING_0,
    MC1081_MCH_SING_1,
    MC1081_MCH_SING_2,
    MC1081_MCH_SING_3,
    MC1081_MCH_SING_4,
} MC1081_Channel_MCH_t;

/**
 * @brief Temperature conversion enable state
 */
typedef enum
{
    MC1081_TEMP_CONV_OFF = 0, /**< Temperature conversion disabled */
    MC1081_TEMP_CONV_ON,      /**< Temperature conversion enabled */
} MC1081_TempConvState_t;

/**
 * @brief Active shield enable state
 */
typedef enum
{
    MC1081_ACTIVE_SHIELD_OFF, /**< Active shield disabled */
    MC1081_ACTIVE_SHIELD_ON,  /**< Active shield enabled */
} MC1081_ActiveShieldState_t;

/**
 * @brief Active shield power mode
 */
typedef enum
{
    MC1081_SHIELD_PWR_LOW,  /**< Low power mode */
    MC1081_SHIELD_PWR_HIGH, /**< High power mode */
} MC1081_ActiveShieldPwr_t;

/**
 * @brief Active shield idle-state selection
 */
typedef enum
{
    MC1081_SHIELD_HIGHRES, /**< High-impedance during non-measurement */
    MC1081_SHIELD_GND,     /**< Grounded during non-measurement */
} MC1081_ActiveShieldSel_t;

/**
 * @brief Temperature conversion time selection
 */
typedef enum
{
    MC1081_TEMP_TIME_0P3_MS, /**< 0.3 ms conversion time */
    MC1081_TEMP_TIME_1P7_MS, /**< 1.7 ms conversion time */
} MC1081_TempTime_t;

/**
 * @brief Capacitive oscillator input mode
 */
typedef enum
{
    MC1081_CAP_OSC_SINGLE, /**< Single-ended mode */
    MC1081_CAP_OSC_DIFF,   /**< Differential mode */
} MC1081_CapOscMode_t;

/**
 * @brief Capacitive measurement interval
 */
typedef enum
{
    MC1081_CAP_TIME_10S,  /**< Measure every 10 seconds */
    MC1081_CAP_TIME_1S,   /**< Measure every 1 second */
    MC1081_CAP_TIME_0P1S, /**< Measure every 0.1 second */
    MC1081_CAP_TIME_CONT, /**< Continuous measurement */
} MC1081_CapTime_t;

/**
 * @brief Frequency counter averaging cycles
 */
typedef enum
{
    MC1081_CAP_AVG_1,  /**< 1-cycle average */
    MC1081_CAP_AVG_4,  /**< 4-cycle average */
    MC1081_CAP_AVG_8,  /**< 8-cycle average */
    MC1081_CAP_AVG_32, /**< 32-cycle average */
} MC1081_CapAvgCycle_t;

/**
 * @brief Capacitive measurement start control
 */
typedef enum
{
    MC1081_CAP_START_PERIODIC, /**< Start periodic measurement */
    MC1081_CAP_START_RESERVED, /**< Reserved */
    MC1081_CAP_START_STOP,     /**< Stop measurement */
    MC1081_CAP_START_SINGLE,   /**< Single-shot measurement */
} MC1081_CapStartMode_t;

/**
 * @brief Chip sleep control
 */
typedef enum
{
    MC1081_CHIP_SLEEP_OFF, /**< Sleep disabled */
    MC1081_CHIP_SLEEP_ON,  /**< Sleep enabled */
} MC1081_ChipSleep_t;

/**
 * @brief Oscillator driver current selection
 */
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
} MC1081_DriverCu_t;

/**
 * @brief Oscillator amplitude selection (OS1 path)
 */
typedef enum
{
    MC1081_AMPOS1_0_2,
    MC1081_AMPOS1_0_4,
    MC1081_AMPOS1_0_8,
    MC1081_AMPOS1_1_2,
    MC1081_AMPOS1_2_2_VDD,
    MC1081_AMPOS1_1_6_VDD,
    MC1081_AMPOS1_1_2_VDD,
    MC1081_AMPOS1_0_8_VDD,
} MC1081_AmplituOS1_t;

/**
 * @brief Oscillator amplitude selection (OS2 path)
 */
typedef enum
{
    MC1081_AMPOS2_0_2,
    MC1081_AMPOS2_0_4,
    MC1081_AMPOS2_0_8,
    MC1081_AMPOS2_1_2,
    MC1081_AMPOS2_1_6,
    MC1081_AMPOS2_2_0,
    MC1081_AMPOS2_2_4,
} MC1081_AmplituOS2_t;

/**
 * @brief Internal LDO power mode
 */
typedef enum
{
    MC1081_PWR_LOW,  /**< Low power LDO mode */
    MC1081_PWR_HIGH, /**< High power LDO mode */
} MC1081_LdoPwr_t;

/**
 * @brief Capacitive conversion configuration structure
 */
typedef struct
{
    MC1081_CapOscMode_t osc_mode;   /**< Oscillator input mode */
    MC1081_CapTime_t interval;      /**< Measurement interval */
    MC1081_CapAvgCycle_t avg_cycle; /**< Averaging cycles */
    MC1081_ChipSleep_t sleep;       /**< Sleep control */
    MC1081_CapStartMode_t start;    /**< Start/stop control */
} MC1081_CapConvConfig_t;

/**
 * @brief Clock configuration structure
 */
typedef struct
{
    MC1081_FinDIV_t fin_div;          /**< FIN divider */
    MC1081_FrefDIV_t fref_div;        /**< Reference divider */
    MC1081_FinBuildCycle_t fin_build; /**< FIN build-up cycles */
} MC1081_ClockCfg_t;

/**
 * @brief Single-ended channel enable bitfield
 */
typedef union
{
    struct __attribute__((packed))
    {
        uint16_t ch0 : 1;
        uint16_t ch1 : 1;
        uint16_t ch2 : 1;
        uint16_t ch3 : 1;
        uint16_t ch4 : 1;
        uint16_t ch5 : 1;
        uint16_t ch6 : 1;
        uint16_t ch7 : 1;
        uint16_t ch8 : 1;
        uint16_t ch9 : 1;
        uint16_t ch_ref : 1;
        uint16_t : 5;
    } bits;

    uint16_t value; /**< Raw 16-bit register value */
} MC1081_ChSingleEn_t;

/**
 * @brief Differential channel enable bitfield
 */
typedef union
{
    struct __attribute__((packed))
    {
        uint8_t ch1 : 1;
        uint8_t ch2 : 1;
        uint8_t ch3 : 1;
        uint8_t ch4 : 1;
        uint8_t ch5 : 1;
        uint8_t ch_ref : 1;
        uint8_t : 2;
    } bits;

    uint8_t value; /**< Raw register value */
} MC1081_ChDiffEn_t;

/**
 * @brief Mutual-capacitance channel enable bitfield
 */
typedef union
{
    struct __attribute__((packed))
    {
        uint8_t Mch1 : 1;
        uint8_t Mch2 : 1;
        uint8_t Mch3 : 1;
        uint8_t Mch4 : 1;
        uint8_t Mch5 : 1;
        uint8_t : 3;
    } bits;

    uint8_t value; /**< Raw register value */
} MC1081_MchEn_t;

/**
 * @brief Single-ended oscillator configuration
 */
typedef struct
{
    MC1081_DriverCu_t dr_cu;        /**< Driver current */
    MC1081_AmplituOS1_t amplitude; /**< Oscillation amplitude */
    MC1081_LdoPwr_t ldo;            /**< LDO power mode */
} MC1081_SingleOSCCfg_t;

/**
 * @brief Differential oscillator configuration
 */
typedef struct
{
    MC1081_DriverCu_t dr_cu;        /**< Driver current */
    MC1081_AmplituOS2_t amplitude; /**< Oscillation amplitude */
    MC1081_LdoPwr_t ldo;            /**< LDO power mode */
} MC1081_DiffOSCCfg_t;

/**
 * @brief Active shield configuration structure
 */
typedef struct
{
    MC1081_ActiveShieldState_t en; /**< Enable state */
    MC1081_ActiveShieldPwr_t pwr;  /**< Power mode */
    MC1081_ActiveShieldSel_t sel;  /**< Idle-state selection */
} MC1081_ActiveShielCfg;

/**
 * @brief I2C address selection bitfield
 */
typedef union
{
    struct __attribute__((packed))
    {
        uint8_t GND : 1; /**< ADDR pin tied to GND */
        uint8_t VDD : 1; /**< ADDR pin tied to VDD */
        uint8_t SDA : 1; /**< ADDR pin tied to SDA */
        uint8_t SCL : 1; /**< ADDR pin tied to SCL */
        uint8_t RSV : 4; /**< Reserved */
    } bits;

    uint8_t value; /**< Raw address selection value */
} MC1081_AddrSel_t;

/**
 * @brief Low-level transmit function prototype
 */
typedef int (*MC1081_TransmitFunc_t)(const uint8_t *data, const size_t len);

/**
 * @brief Low-level receive function prototype
 */
typedef int (*MC1081_ReceiveFunc_t)(const uint8_t *dst, const size_t len);

/**
 * @brief Communication interface configuration
 */
typedef struct
{
    MC1081_TransmitFunc_t Transmit; /**< Transmit callback */
    MC1081_ReceiveFunc_t Receive;   /**< Receive callback */
} MC1081_Conf_t;

/**
 * @brief MC1081 object instance
 */
typedef struct
{
    MC1081_Conf_t conf; /**< Communication configuration */
    uint8_t I2c_addr;   /**< I2C device address */
} MC1081_Obj_t;

/**
 * @brief MC1081 handle type
 */
typedef MC1081_Obj_t *MC1081_Handle_t;

#ifdef __cplusplus
}
#endif

#endif
