/**
 * @file example.c
 * @brief MC1081 Capacitance-to-Digital Converter 使用示例
 */

#include <stdio.h>
#include "MC1081.h"

/* ---------------- 1. 硬件抽象层实现 (I2C 适配) ---------------- */

/**
 * @brief 用户自定义 I2C 写函数
 * @note 这里的实现取决于你的 MCU 平台 (如 STM32 HAL, ESP-IDF, Arduino 等)
 */
int my_i2c_transmit(uint8_t *data, size_t len) {
    // 示例: HAL_I2C_Master_Transmit(&hi2c1, MC1081_ADDR, data, len, 100);
    // 成功返回 0，失败返回非 0
    return 0; 
}

/**
 * @brief 用户自定义 I2C 读函数
 */
int my_i2c_receive(uint8_t *dst, size_t len) {
    // 示例: HAL_I2C_Master_Receive(&hi2c1, MC1081_ADDR, dst, len, 100);
    return 0;
}

/* ---------------- 2. 主程序逻辑 ---------------- */

int main(void) {
    MC1081_Status_t status;
    MC1081_Handle_t sensor = NULL; // 必须初始化为 NULL

    // 配置 I2C 回调
    MC1081_Conf_t dev_conf = {
        .Transmit = my_i2c_transmit,
        .Receive = my_i2c_receive
    };

    printf("Initializing MC1081...\n");

    /* Step 1: 初始化设备句柄 */
    status = MC1081_Init(&sensor, &dev_conf);
    if (status != MC1081_OK) {
        printf("Init Failed! Error code: %d\n", status);
        return -1;
    }

    /* Step 2: 软件复位 (确保芯片处于干净状态) */
    MC1081_SoftWareReset(sensor);

    /* Step 3: 配置时钟与电容测量参数 */
    // 设置时钟分频
    MC1081_ClockCfg_t clk_cfg = {
        .fin_div = MC1081_FINDIV_8,
        .fref_div = MC1081_FREFDIV_4,
        .fin_build = MC1081_FIN_BUILD_4_CYCLE
    };
    MC1081_SetClockConfig(sensor, clk_cfg);

    // 设置测量参数: 连续测量模式, 8次平均
    MC1081_CapConvConfig_t cap_cfg = {
        .osc_mode = MC1081_CAP_OSC_SINGLE,  // 单端模式
        .interval = MC1081_CAP_TIME_CONT,   // 连续测量
        .avg_cycle = MC1081_CAP_AVG_8,      // 8次平均
        .sleep = MC1081_CHIP_SLEEP_OFF,     // 不进入睡眠
        .start = MC1081_CAP_START_PERIODIC  // 启动测量周期
    };
    MC1081_CapMeasureSet(sensor, cap_cfg);

    /* Step 4: 使能需要测量的通道 */
    MC1081_ChSingleEn_t ch_en = { .value = 0 };
    ch_en.bits.ch0 = 1;     // 使能通道 0
    ch_en.bits.ch1 = 1;     // 使能通道 1
    ch_en.bits.ch_ref = 1;  // 使能参考通道
    MC1081_ChSingleEnableSet(sensor, ch_en);

    /* Step 5: 配置温度测量 (开启, 每 0.3ms 转换一次) */
    MC1081_TempConfig(sensor, MC1081_TEMP_CONV_ON, MC1081_TEMP_TIME_0P3_MS);

    printf("MC1081 Configured. Starting data read loop...\n");

    /* Step 6: 循环读取数据 */
    while (1) {
        uint16_t cap_raw = 0;
        uint16_t temp_raw = 0;
        uint8_t is_cap_busy, is_temp_busy;

        // 检查芯片状态
        MC1081_GetStatus(sensor, &is_cap_busy, &is_temp_busy);

        if (!is_cap_busy) {
            // 读取通道 0 原始值
            if (MC1081_GetSigleCHxRaw(sensor, MC1081_DCH_SING_0, &cap_raw) == MC1081_OK) {
                printf("CH0 Raw: %u ", cap_raw);
                
                // 检查是否溢出
                if (MC1081_IsSingleChOverflow(sensor, MC1081_DCH_SING_0)) {
                    printf("[OVERFLOW!] ");
                    MC1081_ClearOverflowFlag(sensor);
                }
            }
        }

        if (!is_temp_busy) {
            // 读取温度原始值
            if (MC1081_GetTempRaw(sensor, &temp_raw) == MC1081_OK) {
                printf("| Temp Raw: %u", temp_raw);
            }
        }

        printf("\n");

        // 适当延时，实际应用中可根据 interval 调整
        // HAL_Delay(100); 
    }

    /* Step 7: 程序结束时释放内存 */
    MC1081_DeInit(&sensor);

    return 0;
}

