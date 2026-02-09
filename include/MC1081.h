/**
 * @file MC1081.h
 * @author https://github.com/xfp23
 * @brief Driver interface for the MC1081 Capacitance-to-Digital Converter.
 * @version 0.1
 * @date 2026-02-05
 * * @copyright Copyright (c) 2026
 * */

#ifndef __MC1081_H__
#define __MC1081_H__

#include "MC1081_types.h"

#ifdef __cplusplus
extern "C"
{
#endif

/** @brief Default I2C slave address for MC1081 */
#define MC1081_DEFAULT_I2CADDR (0x71)

/**
 * @brief Initializes the device instance handle. 
 * @note The handle must be initialized to `NULL` before calling this function.
 * @param handle [out] Pointer to the device handle to be initialized.
 * @param conf   [in]  Pointer to the configuration structure.
 * @return MC1081_Status_t Operation status code.
 */
extern MC1081_Status_t MC1081_Init(MC1081_Handle_t *handle, MC1081_Conf_t *conf);

/**
 * @brief Reads the raw temperature value.
 * @param handle [in]  Device handle.
 * @param raw    [out] Pointer to store the raw temperature data.
 * @return MC1081_Status_t Operation status code.
 */
extern MC1081_Status_t MC1081_GetTempRaw(MC1081_Handle_t handle, uint16_t *raw);

/**
 * @brief Reads the raw value from a specific Mutual Capacitance (MCH) channel.
 * @param handle [in]  Device handle.
 * @param ch     [in]  Mutual capacitance channel index.
 * @param raw    [out] Pointer to store the raw conversion data.
 * @return MC1081_Status_t Operation status code.
 */
extern MC1081_Status_t MC1081_GetMCHxRaw(MC1081_Handle_t handle, MC1081_Channel_MCH_t ch, uint16_t *raw);

/**
 * @brief Reads the raw value from a Single-Ended channel.
 * @param handle [in]  Device handle.
 * @param ch     [in]  Single-ended channel index.
 * @param raw    [out] Pointer to store the raw conversion data.
 * @return MC1081_Status_t Operation status code.
 */
extern MC1081_Status_t MC1081_GetSigleCHxRaw(MC1081_Handle_t handle, MC1081_Channel_Single_t ch, uint16_t *raw);

/**
 * @brief Reads the raw value from a Differential channel.
 * @param handle [in]  Device handle.
 * @param ch     [in]  Differential channel index.
 * @param raw    [out] Pointer to store the raw conversion data.
 * @return MC1081_Status_t Operation status code.
 */
extern MC1081_Status_t MC1081_GetDiffDCHxRaw(MC1081_Handle_t handle, MC1081_Channel_Diff_t ch, uint16_t *raw);

/**
 * @brief Checks if a Single-Ended channel has an overflow condition.
 * @param handle [in] Device handle.
 * @param ch     [in] Single-ended channel index.
 * @return true if overflowed, false otherwise.
 */
extern bool MC1081_IsSingleChOverflow(MC1081_Handle_t handle, MC1081_Channel_Single_t ch);

/**
 * @brief Checks if a Differential channel has an overflow condition.
 * @param handle [in] Device handle.
 * @param ch     [in] Differential channel index.
 * @return true if overflowed, false otherwise.
 */
extern bool MC1081_CheckchxOverflow_Diff(MC1081_Handle_t handle, MC1081_Channel_Diff_t ch);

/**
 * @brief Checks if a Mutual Capacitance (MCH) channel has an overflow condition.
 * @param handle [in] Device handle.
 * @param ch     [in] Mutual capacitance channel index.
 * @return true if overflowed, false otherwise.
 */
extern bool MC1081_IsMChOverflow(MC1081_Handle_t handle, MC1081_Channel_MCH_t ch);

/**
 * @brief Clears all overflow flags in the device.
 * @param handle [in] Device handle.
 * @return MC1081_Status_t Operation status code.
 */
extern MC1081_Status_t MC1081_ClearOverflowFlag(MC1081_Handle_t handle);

/**
 * @brief Gets the current conversion status of the chip.
 * @param handle           [in]  Device handle.
 * @param isCapConverting  [out] Pointer to store capacitance conversion status (1: busy, 0: idle).
 * @param isTempConverting [out] Pointer to store temperature conversion status (1: busy, 0: idle).
 * @return MC1081_Status_t Operation status code.
 */
extern MC1081_Status_t MC1081_GetStatus(MC1081_Handle_t handle, uint8_t *isCapConverting, uint8_t *isTempConverting);

/**
 * @brief Configures temperature measurement settings.
 * @param handle [in] Device handle.
 * @param state  [in] Conversion state (Enabled/Disabled).
 * @param time   [in] Conversion interval/time configuration.
 * @return MC1081_Status_t Operation status code.
 */
extern MC1081_Status_t MC1081_TempConfig(MC1081_Handle_t handle, MC1081_TempConvState_t state, MC1081_TempTime_t time);

/**
 * @brief Sets the capacitance measurement configuration.
 * @param handle [in] Device handle.
 * @param conf   [in] Configuration structure for capacitance conversion.
 * @return MC1081_Status_t Operation status code.
 */
extern MC1081_Status_t MC1081_CapMeasureSet(MC1081_Handle_t handle, MC1081_CapConvConfig_t conf);

/**
 * @brief Retrieves the current capacitance measurement configuration.
 * @param handle [in]  Device handle.
 * @param conf   [out] Pointer to store the current configuration.
 * @return MC1081_Status_t Operation status code.
 */
extern MC1081_Status_t MC1081_CapMeasureGet(MC1081_Handle_t handle, MC1081_CapConvConfig_t *conf);

/**
 * @brief Sets the FIN cycle duration.
 * @param handle [in] Device handle.
 * @param cycle  [in] Cycle duration value (Recommended: 0xFE).
 * @return MC1081_Status_t Operation status code.
 */
extern MC1081_Status_t MC1081_SetFinCycle(MC1081_Handle_t handle, uint8_t cycle);

/**
 * @brief Gets the current FIN cycle duration.
 * @param handle [in]  Device handle.
 * @param cycle  [out] Pointer to store the cycle duration value.
 * @return MC1081_Status_t Operation status code.
 */
extern MC1081_Status_t MC1081_GetFinCycle(MC1081_Handle_t handle, uint8_t *cycle);

/**
 * @brief Configures the internal clock settings.
 * @param handle [in] Device handle.
 * @param cfg    [in] Clock configuration structure.
 * @return MC1081_Status_t Operation status code.
 */
extern MC1081_Status_t MC1081_SetClockConfig(MC1081_Handle_t handle, MC1081_ClockCfg_t cfg);

/**
 * @brief Retrieves the current clock configuration.
 * @param handle [in]  Device handle.
 * @param cfg    [out] Pointer to store the clock configuration.
 * @return MC1081_Status_t Operation status code.
 */
extern MC1081_Status_t MC1081_GetClockConfig(MC1081_Handle_t handle, MC1081_ClockCfg_t *cfg);

/**
 * @brief Enables or disables specific Single-Ended channels.
 * @param handle   [in] Device handle.
 * @param ChSingle [in] Bitmask for single-ended channels (1 to enable).
 * @return MC1081_Status_t Operation status code.
 */
extern MC1081_Status_t MC1081_ChSingleEnableSet(MC1081_Handle_t handle, MC1081_ChSingleEn_t ChSingle);

/**
 * @brief Retrieves the enable status of Single-Ended channels.
 * @param handle   [in]  Device handle.
 * @param ChSingle [out] Pointer to store the channel enable bitmask.
 * @return MC1081_Status_t Operation status code.
 */
extern MC1081_Status_t MC1081_ChSingleEnableGet(MC1081_Handle_t handle, MC1081_ChSingleEn_t *ChSingle);

/**
 * @brief Enables or disables specific Mutual Capacitance (MCH) channels.
 * @param handle [in] Device handle.
 * @param Mchx   [in] Bitmask for MCH channels (1 to enable).
 * @return MC1081_Status_t Operation status code.
 */
extern MC1081_Status_t MC1081_MchxEnableSet(MC1081_Handle_t handle, MC1081_MchEn_t Mchx);

/**
 * @brief Retrieves the enable status of Mutual Capacitance (MCH) channels.
 * @param handle [in]  Device handle.
 * @param Mchx   [out] Pointer to store the MCH channel enable bitmask.
 * @return MC1081_Status_t Operation status code.
 */
extern MC1081_Status_t MC1081_MchxEnableGet(MC1081_Handle_t handle, MC1081_MchEn_t *Mchx);

/**
 * @brief Configures the oscillator settings for Single-Ended mode.
 * @param handle [in] Device handle.
 * @param cfg    [in] Oscillator configuration structure.
 * @return MC1081_Status_t Operation status code.
 */
extern MC1081_Status_t MC1081_SingleOSCSet(MC1081_Handle_t handle, MC1081_SingleOSCCfg_t cfg);

/**
 * @brief Retrieves the oscillator settings for Single-Ended mode.
 * @param handle [in]  Device handle.
 * @param cfg    [out] Pointer to store the oscillator configuration.
 * @return MC1081_Status_t Operation status code.
 */
extern MC1081_Status_t MC1081_SingleOSCGet(MC1081_Handle_t handle, MC1081_SingleOSCCfg_t *cfg);

/**
 * @brief Enables or disables specific Differential channels.
 * @param handle [in] Device handle.
 * @param diffen [in] Bitmask for differential channels (1 to enable).
 * @return MC1081_Status_t Operation status code.
 */
extern MC1081_Status_t MC1081_ChDiffEnableSet(MC1081_Handle_t handle, MC1081_ChDiffEn_t diffen);

/**
 * @brief Retrieves the enable status of Differential channels.
 * @param handle [in]  Device handle.
 * @param diffen [out] Pointer to store the differential channel enable bitmask.
 * @return MC1081_Status_t Operation status code.
 */
extern MC1081_Status_t MC1081_ChDiffEnableGet(MC1081_Handle_t handle, MC1081_ChDiffEn_t *diffen);

/**
 * @brief Configures the oscillator settings for Differential mode.
 * @param handle [in] Device handle.
 * @param cfg    [in] Oscillator configuration structure.
 * @return MC1081_Status_t Operation status code.
 */
extern MC1081_Status_t MC1081_DiffOSCSet(MC1081_Handle_t handle, MC1081_DiffOSCCfg_t cfg);

/**
 * @brief Retrieves the oscillator settings for Differential mode.
 * @param handle [in]  Device handle.
 * @param cfg    [out] Pointer to store the oscillator configuration.
 * @return MC1081_Status_t Operation status code.
 */
extern MC1081_Status_t MC1081_DiffOSCGet(MC1081_Handle_t handle, MC1081_DiffOSCCfg_t *cfg);

/**
 * @brief Configures the Active Shielding feature.
 * @param handle [in] Device handle.
 * @param cfg    [in] Shielding configuration.
 * @return MC1081_Status_t Operation status code.
 */
extern MC1081_Status_t MC1081_ActiveShieldSet(MC1081_Handle_t handle, MC1081_ActiveShielCfg cfg);

/**
 * @brief Reads the current Active Shielding configuration from the chip.
 * @param handle [in]  Device handle.
 * @param cfg    [out] Pointer to store the shielding configuration.
 * @return MC1081_Status_t Operation status code.
 */
extern MC1081_Status_t MC1081_ActiveShieldGet(MC1081_Handle_t handle, MC1081_ActiveShielCfg *cfg);

/**
 * @brief Performs a software reset on the chip.
 * @param handle [in] Device handle.
 * @return MC1081_Status_t Operation status code.
 */
extern MC1081_Status_t MC1081_SoftWareReset(MC1081_Handle_t handle);

/**
 * @brief Calculates the I2C address based on hardware ADDR pin strapping.
 * @note For MC1081L, the address is fixed to MC1081_DEFAULT_I2CADDR.
 * @param add [in] Address selection configuration based on hardware pins.
 * @return uint8_t The resulting 7-bit I2C address.
 */
extern uint8_t MC1081_CalI2cAddr(MC1081_AddrSel_t add);

/**
 * @brief De-initializes the device and releases allocated instance memory.
 * @param handle [in/out] Pointer to the device handle to be cleared.
 * @return MC1081_Status_t Operation status code.
 */
extern MC1081_Status_t MC1081_DeInit(MC1081_Handle_t *handle);

#ifdef __cplusplus
}
#endif

#endif /* __MC1081_H__ */