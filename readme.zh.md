
[英文](./readme.md)

---

# MC1081 驱动库

这是一个为 **MC1081 电容数字转换器 (CDC)** 编写的专业级 C 语言驱动库。该库支持单端、差分及互电容测量模式，同时包含内置温度传感器读取与有源屏蔽 (Active Shielding) 配置功能。

## 1. 简介

MC1081 是一款高精度的电容测量芯片。本驱动程序提供了一个硬件抽象层接口，通过提供简单的 I2C 读写函数指针，开发者可以轻松将其移植到任何 MCU 平台。

---

## 2. 快速开始

### 第一步：定义 I2C 适配器

您需要根据驱动库定义的 `MC1081_TransmitFunc_t` 和 `MC1081_ReceiveFunc_t` 签名编写两个函数，用于对接您的底层硬件。

```c
// 示例：底层 I2C 发送函数
int my_i2c_transmit(uint8_t *data, size_t len) {
    // 调用您的底层 I2C 发送 API (例如 HAL_I2C_Master_Transmit)
    return 0; // 成功返回 0
}

// 示例：底层 I2C 接收函数
int my_i2c_receive(uint8_t *dst, size_t len) {
    // 调用您的底层 I2C 接收 API
    return 0; // 成功返回 0
}

```

### 第二步：初始化设备

```c
MC1081_Handle_t sensor = NULL; // 必须初始化为 NULL
MC1081_Conf_t config = {
    .Transmit = my_i2c_transmit,
    .Receive = my_i2c_receive
};

// 初始化句柄
if (MC1081_Init(&sensor, &config) == MC1081_OK) {
    // 初始化成功
}

```

### 第三步：读取数据

```c
uint16_t raw_val;
// 读取单端通道 0 的原始数据
MC1081_GetSigleCHxRaw(sensor, MC1081_DCH_SING_0, &raw_val);

```

---

## 3. 所有 API 原型介绍

### 设备管理

| 函数原型 | 描述 |
| --- | --- |
| `MC1081_Status_t MC1081_Init(MC1081_Handle_t *handle, MC1081_Conf_t *conf)` | 初始化设备句柄并分配内存，绑定 I2C 接口。 |
| `MC1081_Status_t MC1081_DeInit(MC1081_Handle_t *handle)` | 反初始化设备，释放内存并将句柄重置为 NULL。 |
| `MC1081_Status_t MC1081_SoftWareReset(MC1081_Handle_t handle)` | 对 MC1081 芯片执行软件复位。 |
| `uint8_t MC1081_CalI2cAddr(MC1081_AddrSel_t add)` | 根据 ADDR 引脚的硬件连接方式计算 7 位 I2C 地址。 |

### 数据采集

| 函数原型 | 描述 |
| --- | --- |
| `MC1081_Status_t MC1081_GetTempRaw(MC1081_Handle_t handle, uint16_t *raw)` | 获取内置温度传感器的原始数值。 |
| `MC1081_Status_t MC1081_GetMCHxRaw(MC1081_Handle_t h, MC1081_Channel_MCH_t ch, uint16_t *raw)` | 获取指定**互电容**通道的原始转换数据。 |
| `MC1081_Status_t MC1081_GetSigleCHxRaw(MC1081_Handle_t h, MC1081_Channel_Single_t ch, uint16_t *raw)` | 获取指定**单端**通道的原始转换数据。 |
| `MC1081_Status_t MC1081_GetDiffDCHxRaw(MC1081_Handle_t h, MC1081_Channel_Diff_t ch, uint16_t *raw)` | 获取指定**双端/差分**通道的原始转换数据。 |

### 状态与溢出监测

| 函数原型 | 描述 |
| --- | --- |
| `MC1081_Status_t MC1081_GetStatus(MC1081_Handle_t h, uint8_t *isCapConv, uint8_t *isTempConv)` | 获取芯片当前状态（电容或温度是否正在转换中）。 |
| `bool MC1081_IsSingleChOverflow(MC1081_Handle_t h, MC1081_Channel_Single_t ch)` | 检查单端通道是否发生数据溢出。 |
| `bool MC1081_CheckchxOverflow_Diff(MC1081_Handle_t h, MC1081_Channel_Diff_t ch)` | 检查双端/差分通道是否发生数据溢出。 |
| `bool MC1081_IsMChOverflow(MC1081_Handle_t h, MC1081_Channel_MCH_t ch)` | 检查互电容通道是否发生数据溢出。 |
| `MC1081_Status_t MC1081_ClearOverflowFlag(MC1081_Handle_t handle)` | 清除芯片内部所有的溢出标志位。 |

### 参数配置

| 函数原型 | 描述 |
| --- | --- |
| `MC1081_Status_t MC1081_TempConfig(MC1081_Handle_t h, MC1081_TempConvState_t s, MC1081_TempTime_t t)` | 配置温度测量开关及转换间隔时间。 |
| `MC1081_Status_t MC1081_CapMeasureSet(MC1081_Handle_t h, MC1081_CapConvConfig_t conf)` | 配置电容测量的模式、间隔、平均次数等核心参数。 |
| `MC1081_Status_t MC1081_SetClockConfig(MC1081_Handle_t h, MC1081_ClockCfg_t cfg)` | 设置芯片内部时钟分频比。 |
| `MC1081_Status_t MC1081_ChSingleEnableSet(MC1081_Handle_t h, MC1081_ChSingleEn_t ch)` | 使能或禁用特定的单端测量通道（通过位掩码）。 |
| `MC1081_Status_t MC1081_MchxEnableSet(MC1081_Handle_t h, MC1081_MchEn_t mch)` | 使能或禁用特定的互电容测量通道。 |
| `MC1081_Status_t MC1081_ActiveShieldSet(MC1081_Handle_t h, MC1081_ActiveShielCfg cfg)` | 配置有源屏蔽（Active Shielding）功能的开关与功率。 |

---

## 4. 结构体类型介绍

### `MC1081_CapConvConfig_t` (电容测量配置)

用于定义电容转换的核心行为。

* `osc_mode`: 振荡输入模式（单端/差分）。
* `interval`: 测量时间间隔（10s, 1s, 0.1s, 连续）。
* `avg_cycle`: 硬件平均次数（1, 4, 8, 32 次）。
* `sleep`: 睡眠控制（使能/禁止）。
* `start`: 启动控制（周期测量、单次测量、停止）。

### `MC1081_ClockCfg_t` (时钟配置)

* `fin_div`: 输入频率分频。
* `fref_div`: 参考频率分频。
* `fin_build`: 建立时间周期设置。

### `MC1081_Conf_t` (用户回调配置)

* `Transmit`: I2C 发送函数指针。
* `Receive`: I2C 接收函数指针。

### `MC1081_ActiveShielCfg` (有源屏蔽配置)

* `en`: 有源屏蔽开关。
* `pwr`: 功率模式（低功率/高功率）。
* `sel`: 非测量期间的状态选择（高阻或接地）。

---

## 5. 枚举值类型

### 操作状态 (`MC1081_Status_t`)

* `MC1081_OK`: 操作成功。
* `MC1081_ERR`: 通用错误。
* `MC1081_PARAM_ERR`: 参数错误。
* `MC1081_WR_ERR`: I2C 写错误。
* `MC1081_RR_ERR`: I2C 读错误。
* `MC1081_MEM_ERR`: 内存分配失败。

### 驱动电流 (`MC1081_DriverCu_t`)

定义测量端的驱动电流能力，范围从 `4uA` 到 `2000uA`。

### 振荡幅度 (`MC1081_AmplituOS1_t` & `MC1081_AmplituOS2_t`)

定义测量信号的电压幅值（如 `0.2V`, `1.2V`, 或直接由 `VDD` 供电的电压等级）。

### 地址选择 (`MC1081_AddrSel_t`)

用于 `MC1081_CalI2cAddr` 函数，对应硬件 ADDR 引脚连接到 GND, VDD, SDA 或 SCL。

---
