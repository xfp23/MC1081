/**
 * @file MC1081_reg.h
 * @author https://github.com/xfp23
 * @brief
 * @version 0.1
 * @date 2026-02-08
 *
 * @copyright Copyright (c) 2026
 *
 */
#ifndef __MC1081_REG_H__
#define __MC1081_REG_H__

#include "stdint.h"

#ifdef __cplusplus
extern "C"
{
#endif

typedef union
{
    struct __attribute__((packed))
    {
        uint8_t T_LSB;
        uint8_t T_MSB;
    } bits;

    uint16_t bytes;
} MC1081_TDATA_Reg_t; // 温度数据寄存器

typedef union
{
    struct __attribute__((packed))
    {
        uint8_t D_LSB;
        uint8_t D_MSB;
    } bits;
    uint16_t bytes;
} MC1081_CHDATA_t;

typedef union
{
    struct __attribute__((packed))
    {
        uint8_t OF1 : 8;
        uint8_t OF2 : 2;   // 对应位 0 ~ 9 表示对应单端通道溢出
        uint8_t OFREF : 1; // 参比通道溢出
        uint8_t MOF : 5;   // 1 表示互电容通道 x 的计数值溢出。
    } bits;

    uint16_t bytes;

} MC1081_OSC1_t; // 通道溢出检查

typedef union
{
    struct __attribute__((packed))
    {
        uint8_t DOF : 5;    // 表示双端电容通道 x 的计数值溢出。
        uint8_t DOFREF : 1; // 表示双端参比通道的计数值溢出
        uint8_t RSV : 2;    //
    } bits;

    uint8_t byte;

} MC1081_OSC2_t;

typedef union
{
    struct __attribute__((packed))
    {
        uint8_t FLAG_CCVT : 1; // 1 表示正在进行电容转换。周期模式下，此标志位维持高，直到发停止命令。0 表示停止电容转换。
        uint8_t FLAG_TCVT : 1; // 1 表示正在进行温度转换。 0 表示停止温度转换
        uint8_t RSV : 2;       // 保留
        uint8_t OF_CLEAR : 1;  // 写 1 清除全部溢出标志位，读取值为0
        uint8_t : 3;
    } bits;

    uint8_t byte;

} MC1081_STATUSReg_t;

typedef union
{
    struct __attribute__((packed))
    {
        uint8_t STC : 1; // 0 : 关闭温度转换 1 ： 启动
        uint8_t RSV : 6;
        uint8_t TCV : 1; // 测温转换时间配置位
    } bits;
    uint8_t byte;
} MC1081_T_CMD_t;

typedef union
{

    struct __attribute__((packed))
    {
        uint8_t OS : 2;
        uint8_t CR : 2;
        uint8_t CAVG : 2;
        uint8_t SLEEP_EN : 1;
        uint8_t OSC_SEL : 1;
    } bits;

    uint8_t byte;

} MC1081_C_CMD_t;

typedef union
{
    struct __attribute__((packed))
    {
        uint8_t FREFDIV : 2; // 参考时钟分频比 NDIVref
        uint8_t : 2;
        uint8_t FINDIV : 3;   // 通道信号分频比 NDIVin
        uint8_t SETTLING : 1; // 设定 fin 的建立周期个数
    } bits;

    uint8_t byte;

} MC1081_DIV_CFG_t;

typedef union
{
    struct __attribute__((packed))
    {
        uint8_t CH_LSB : 8;
        uint8_t CH_MSB : 2;
        uint8_t CH_REF : 1;
        uint8_t RSV : 5;
    } bits;

    uint16_t bytes;

} MC1081_OSC1_CHS_t;

typedef union
{
    struct __attribute__((packed))
    {
        uint8_t MCH : 5;
        uint8_t : 3;
    } bits;

    uint8_t byte;

} MC1081_OSC1_MCHS_t;

typedef union
{
    struct __attribute__((packed))
    {
        uint8_t OSC1_I : 4;
        uint8_t OSC1_V : 3;
        uint8_t OSC1_LDO : 1;
    } bits;

    uint8_t byte;

} MC1081_OSC1_CFG_t;

typedef union
{
    struct __attribute__((packed))
    {
        uint8_t DCH : 5;
        uint8_t DCH_REF : 1;
        uint8_t : 1;
    } bits;

    uint8_t byte;

} MC1081_OSC2_DCHS_t;

typedef union
{
    struct __attribute__((packed))
    {
        uint8_t OSC2_I : 4;
        uint8_t OSC2_V : 3;
        uint8_t OSC2_LDO : 1;
    } bits;

    uint8_t byte;

} MC1081_OSC2_CFG_t;

typedef union
{

    struct __attribute__((packed))
    {
        uint8_t SHLD_EN : 1;
        uint8_t SHLD_HP : 1;
        uint8_t : 4;
        uint8_t CS : 2;
    } bits;

    uint8_t byte;

} MC1081_SHLD_CFG_t;

#ifdef __cplusplus
}
#endif

#endif
