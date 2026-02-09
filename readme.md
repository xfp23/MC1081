
[中文](./readme.zh.md)

---

# MC1081 Library

A professional C driver for the **MC1081 Capacitance-to-Digital Converter (CDC)**. This library supports single-ended, differential, and mutual capacitance measurements, as well as internal temperature sensing and active shielding configuration.

## 1. Introduction

The MC1081 is a high-precision capacitance measurement chip. This driver provides a hardware-abstracted interface, allowing it to be easily ported to any MCU (STM32, ESP32, Arduino, etc.) by providing simple I2C read/write function pointers.

---

## 2. Quick Start

### Step 1: Define I2C Adapters

You need to provide two functions that match the `MC1081_TransmitFunc_t` and `MC1081_ReceiveFunc_t` signatures.

```c
int my_i2c_transmit(uint8_t *data, size_t len) {
    // Your hardware I2C transmit implementation
    return 0; // Return 0 for success
}

int my_i2c_receive(uint8_t *dst, size_t len) {
    // Your hardware I2C receive implementation
    return 0;  // Return 0 for success
}

```

### Step 2: Initialization

```c
MC1081_Handle_t sensor = NULL;
MC1081_Conf_t config = {
    .Transmit = my_i2c_transmit,
    .Receive = my_i2c_receive
};

if (MC1081_Init(&sensor, &config) == MC1081_OK) {
    // Initialization successful
}

```

### Step 3: Read Data

```c
uint16_t raw_val;
MC1081_GetSigleCHxRaw(sensor, MC1081_DCH_SING_0, &raw_val);

```

---

## 3. API Reference

### Device Management

| Function | Description |
| --- | --- |
| `extern MC1081_Status_t MC1081_Init(MC1081_Handle_t *handle, MC1081_Conf_t *conf)` | Initializes the handle and attaches I2C functions. |
| `extern MC1081_Status_t MC1081_DeInit(MC1081_Handle_t *handle)` | Frees instance memory and resets the handle to NULL. |
| `extern MC1081_Status_t MC1081_SoftWareReset(MC1081_Handle_t handle)` | Triggers a software reset of the MC1081 chip. |
| `extern uint8_t MC1081_CalI2cAddr(MC1081_AddrSel_t add)` | Calculates the 7-bit I2C address based on pin strapping. |

### Data Acquisition

| Function | Description |
| --- | --- |
| `extern MC1081_Status_t MC1081_GetTempRaw(MC1081_Handle_t handle, uint16_t *raw)` | Gets raw internal temperature sensor value. |
| `extern MC1081_Status_t MC1081_GetMCHxRaw(MC1081_Handle_t handle, MC1081_Channel_MCH_t ch, uint16_t *raw)` | Gets raw value from a Mutual Capacitance channel. |
| `extern MC1081_Status_t MC1081_GetSigleCHxRaw(MC1081_Handle_t handle, MC1081_Channel_Single_t ch, uint16_t *raw)` | Gets raw value from a Single-Ended channel. |
| `extern MC1081_Status_t MC1081_GetDiffDCHxRaw(MC1081_Handle_t handle, MC1081_Channel_Diff_t ch, uint16_t *raw)` | Gets raw value from a Differential channel. |

### Status and Overflow

| Function | Description |
| --- | --- |
| `extern MC1081_Status_t MC1081_GetStatus(MC1081_Handle_t handle, uint8_t *isCapConv, uint8_t *isTempConv)` | Checks if conversion is currently in progress. |
| `extern bool MC1081_IsSingleChOverflow(MC1081_Handle_t handle, MC1081_Channel_Single_t ch)` | Checks for overflow in Single-Ended mode. |
| `extern bool MC1081_CheckchxOverflow_Diff(MC1081_Handle_t handle, MC1081_Channel_Diff_t ch)` | Checks for overflow in Differential mode. |
| `extern bool MC1081_IsMChOverflow(MC1081_Handle_t handle, MC1081_Channel_MCH_t ch)` | Checks for overflow in Mutual mode. |
| `extern MC1081_Status_t MC1081_ClearOverflowFlag(MC1081_Handle_t handle)` | Clears all device overflow flags. |

### Configuration

| Function | Description |
| --- | --- |
| `extern MC1081_Status_t MC1081_TempConfig(MC1081_Handle_t handle, MC1081_TempConvState_t state, MC1081_TempTime_t time)` | Sets temperature measurement interval/state. |
| `extern MC1081_Status_t MC1081_CapMeasureSet(MC1081_Handle_t handle, MC1081_CapConvConfig_t conf)` | Configures measurement mode and interval. |
| `extern MC1081_Status_t MC1081_SetClockConfig(MC1081_Handle_t handle, MC1081_ClockCfg_t cfg)` | Configures internal clock dividers. |
| `extern MC1081_Status_t MC1081_ChSingleEnableSet(MC1081_Handle_t handle, MC1081_ChSingleEn_t ChSingle)` | Enables specific Single-Ended channels. |
| `extern MC1081_Status_t MC1081_MchxEnableSet(MC1081_Handle_t handle, MC1081_MchEn_t Mchx)` | Enables specific Mutual Capacitance channels. |
| `extern MC1081_Status_t MC1081_ActiveShieldSet(MC1081_Handle_t handle, MC1081_ActiveShielCfg cfg)` | Configures Active Shielding parameters. |

---

## 4. Structures Reference

### `MC1081_CapConvConfig_t`

Defines the core behavior of the capacitance measurement.

```c
typedef struct {
    MC1081_CapOscMode_t osc_mode;    // Single or Differential
    MC1081_CapTime_t interval;       // Measurement frequency (10s, 1s, 0.1s, Cont)
    MC1081_CapAvgCycle_t avg_cycle;  // Hardware averaging (1, 4, 8, 32)
    MC1081_ChipSleep_t sleep;        // Enable/Disable auto-sleep
    MC1081_CapStartMode_t start;     // Periodic, Single, or Stop
} MC1081_CapConvConfig_t;

```

### `MC1081_Conf_t`

Hardware interface configuration.

```c
typedef struct {
    MC1081_TransmitFunc_t Transmit; // Function pointer for I2C Write
    MC1081_ReceiveFunc_t Receive;   // Function pointer for I2C Read
} MC1081_Conf_t;

```

### `MC1081_ActiveShielCfg`

Active shielding configuration.

```c
typedef struct {
    MC1081_ActiveShieldState_t en;  // ON/OFF
    MC1081_ActiveShieldPwr_t pwr;   // Low/High Power
    MC1081_ActiveShieldSel_t sel;   // High-Z or GND during non-measuring periods
} MC1081_ActiveShielCfg;

```

---

## 5. Enumerations Reference

### Status Codes (`MC1081_Status_t`)

* `MC1081_OK`: Operation successful.
* `MC1081_ERR`: General error.
* `MC1081_PARAM_ERR`: Invalid parameter.
* `MC1081_WR_ERR`: I2C Write failure.
* `MC1081_RR_ERR`: I2C Read failure.

### Measurement Intervals (`MC1081_CapTime_t`)

* `MC1081_CAP_TIME_10S`: Every 10 seconds.
* `MC1081_CAP_TIME_1S`: Every 1 second.
* `MC1081_CAP_TIME_0P1S`: Every 0.1 seconds.
* `MC1081_CAP_TIME_CONT`: Continuous mode.

### Driver Current (`MC1081_DriverCu_t`)

Selectable from `MC1081_DRCU_4UA` (4μA) up to `MC1081_DRCU_2000UA` (2000μA).

### Oscillator Amplitude (`MC1081_AmplituOS1_t` & `MC1081_AmplituOS2_t`)

* Defines the voltage amplitude of the oscillation signal (e.g., `0.2V`, `1.2V`, or `VDD` levels).

---
