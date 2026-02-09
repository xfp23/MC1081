#include "MC1081.h"
#include "MC1081_reg.h"

// mcor
#define MC1081_CHECKPTR(x)     \
    do                         \
    {                          \
        if (x == NULL)         \
        {                      \
            return MC1081_PARAM_ERR; \
        }                      \
    } while (0)

#define MC1081_CHECKERR(ret)  \
    do                        \
    {                         \
        if (ret != MC1081_OK) \
            return ret;       \
    } while (0)

static inline MC1081_Status_t WriteByte(MC1081_Handle_t handle, uint8_t *data, size_t len)
{
    MC1081_CHECKPTR(handle);
    MC1081_CHECKPTR(data);

    if(handle->conf.Transmit(data,len) != 0)
    {
      return MC1081_WR_ERR;
    }
    return MC1081_OK;
}

static inline MC1081_Status_t ReadByte(MC1081_Handle_t handle, uint8_t *data, size_t len)
{
    if(handle->conf.Receive(data,len) != 0)
    {
      return MC1081_RR_ERR;
    }
    return MC1081_OK;
}

MC1081_Status_t MC1081_Init(MC1081_Handle_t *handle, MC1081_Conf_t *conf)
{
    if (handle == NULL || conf == NULL || (*handle) != NULL)
        return MC1081_PARAM_ERR;

    if(conf->Receive == NULL || conf->Transmit == NULL) return MC1081_ERR;

    (*handle) = (MC1081_Obj_t *)calloc(1, sizeof(MC1081_Obj_t));

    if ((*handle) == NULL)
        return MC1081_MEM_ERR;
    (*handle)->I2c_addr = MC1081_DEFAULT_I2CADDR;

    return MC1081_OK;
}

MC1081_Status_t MC1081_GetTempRaw(MC1081_Handle_t handle, uint16_t *raw)
{
    MC1081_CHECKPTR(handle);
    MC1081_CHECKPTR(raw);

    MC1081_Status_t ret = MC1081_OK;
    uint8_t msb_reg = 0x00;
    uint8_t lsb_reg = 0x01;
    MC1081_TDATA_Reg_t tdata = {0};

    ret = WriteByte(handle, &msb_reg, 1); // 写一个字节
    MC1081_CHECKERR(ret);
    ret = ReadByte(handle, (uint8_t *)&tdata.bytes, 2); // 连续读取2个字节
    MC1081_CHECKERR(ret);

    *raw = tdata.bytes;

    return ret;
}


MC1081_Status_t MC1081_GetMCHxRaw(MC1081_Handle_t handle, MC1081_Channel_MCH_t ch, uint16_t *raw)
{
    MC1081_CHECKPTR(handle);
    MC1081_CHECKPTR(raw);

    uint8_t reg = (4 * (uint8_t)ch) + 4;
    MC1081_Status_t sta = WriteByte(handle, &reg, 1);
    MC1081_CHECKERR(sta);

    uint8_t buf[2] = {0};
    sta = ReadByte(handle, buf, 2);
    MC1081_CHECKERR(sta);

    MC1081_CHDATA_t data = {0};
    data.bits.D_MSB = buf[0];
    data.bits.D_LSB = buf[1];

    *raw = data.bytes;
    return sta;
}

MC1081_Status_t MC1081_GetSigleCHxRaw(MC1081_Handle_t handle, MC1081_Channel_Single_t ch, uint16_t *raw)
{
    MC1081_CHECKPTR(handle);
    MC1081_CHECKPTR(raw);

    uint8_t reg = (2 * (uint8_t)ch) + 2;
    MC1081_Status_t sta = WriteByte(handle, &reg, 1);
    MC1081_CHECKERR(sta);

    uint8_t buf[2] = {0};
    sta = ReadByte(handle, buf, 2);
    MC1081_CHECKERR(sta);

    MC1081_CHDATA_t data = {0};
    data.bits.D_MSB = buf[0];
    data.bits.D_LSB = buf[1];

    *raw = data.bytes;
    return sta;
}

MC1081_Status_t MC1081_GetDiffDCHxRaw(MC1081_Handle_t handle, MC1081_Channel_Diff_t ch, uint16_t *raw)
{
    MC1081_CHECKPTR(handle);
    MC1081_CHECKPTR(raw);

    uint8_t reg = 0x00;

    if(ch == MC1081_DCH_DIFF_REF)
    {
        reg = MC1081_DCH_REF;
    }
    reg = (2 * (uint8_t)ch) + 2;


    MC1081_Status_t sta = WriteByte(handle, &reg, 1);
    MC1081_CHECKERR(sta);

    uint8_t buf[2] = {0};
    sta = ReadByte(handle, buf, 2);
    MC1081_CHECKERR(sta);

    MC1081_CHDATA_t data = {0};
    data.bits.D_MSB = buf[0];
    data.bits.D_LSB = buf[1];

    *raw = data.bytes;
    return sta;
}

/**
 * @brief 检查单端或参比通道是否溢出
 * @param ch 目标通道 (DCH0-9 或 REF)
 * @return true: 发生溢出, false: 正常
 */
bool MC1081_IsSingleChOverflow(MC1081_Handle_t handle, MC1081_Channel_Single_t ch)
{
    MC1081_CHECKPTR(handle);

    const uint8_t reg_addr = 0x18;
    MC1081_OSC1_t osc_status = {0};

    if (WriteByte(handle, &reg_addr, 1) != MC1081_OK)
        return false;
    if (ReadByte(handle, (uint8_t *)&osc_status.bytes, 2) != MC1081_OK)
        return false;

    return (osc_status.bytes & (1U << (uint8_t)ch)) != 0;
}


bool MC1081_CheckchxOverflow_Diff(MC1081_Handle_t handle, MC1081_Channel_Diff_t ch)
{
    MC1081_CHECKPTR(handle);
    const uint8_t reg_addr = 0x1A;
    MC1081_OSC2_t osc_status = {0};

    if (WriteByte(handle, &reg_addr, 1) != MC1081_OK)
        return false;
    if (ReadByte(handle, (uint8_t *)&osc_status.byte, 2) != MC1081_OK)
        return false;

    return (osc_status.byte & (1U << (uint8_t)ch)) != 0;
}

bool MC1081_IsMChOverflow(MC1081_Handle_t handle, MC1081_Channel_MCH_t ch)
{
    MC1081_CHECKPTR(handle);
    const uint8_t reg_addr = 0x18;
    MC1081_OSC1_t osc_status = {0};

    if (WriteByte(handle, &reg_addr, 1) != MC1081_OK)
        return false;
    if (ReadByte(handle, (uint8_t *)&osc_status.bytes, 2) != MC1081_OK)
        return false;

    return (osc_status.bits.MOF & (1U << (uint8_t)ch)) != 0;
}

MC1081_Status_t MC1081_ClearOverflowFlag(MC1081_Handle_t handle)
{
    MC1081_CHECKPTR(handle);

    const uint8_t reg_addr = 0x1b;

    MC1081_Status_t sta = WriteByte(handle, &reg_addr, 1);
    MC1081_CHECKERR(sta);

    MC1081_STATUSReg_t status = {0};
    sta = ReadByte(handle, &status.byte, 1);
    MC1081_CHECKERR(sta);

    status.bits.OF_CLEAR = 1;
    sta = WriteByte(handle, &status.byte, 1);
    MC1081_CHECKERR(sta);

    return sta;
}

MC1081_Status_t MC1081_GetStatus(MC1081_Handle_t handle, uint8_t *isCapConverting, uint8_t *isTempConverting)
{
    MC1081_CHECKPTR(handle);
    MC1081_CHECKPTR(isCapConverting);
    MC1081_CHECKPTR(isTempConverting);

    const uint8_t reg_addr = 0x1b;

    MC1081_Status_t sta = WriteByte(handle, &reg_addr, 1);
    MC1081_CHECKERR(sta);

    MC1081_STATUSReg_t status = {0};
    sta = ReadByte(handle, &status.byte, 1);
    MC1081_CHECKERR(sta);

    *isCapConverting = status.bits.FLAG_CCVT;
    *isTempConverting = status.bits.FLAG_TCVT;

    return sta;
}

MC1081_Status_t MC1081_TempConfig(MC1081_Handle_t handle, MC1081_TempConvState_t state, MC1081_TempTime_t time)
{
    MC1081_CHECKPTR(handle);

    const uint8_t reg_addr = 0x1C;

    MC1081_T_CMD_t t_cmd = {0};
    t_cmd.bits.STC = state;
    t_cmd.bits.TCV = time;

    uint8_t buf[2] = {0};
    buf[0] = reg_addr;
    buf[1] = t_cmd.byte;

    return WriteByte(handle, &t_cmd.byte, 2);
}

MC1081_Status_t MC1081_CapMeasureSet(MC1081_Handle_t handle, MC1081_CapConvConfig_t conf)
{
    MC1081_CHECKPTR(handle);

    uint8_t reg_addr = 0x1D;

    MC1081_C_CMD_t c_cmd = {0};
    c_cmd.bits.CAVG = conf.avg_cycle;
    c_cmd.bits.SLEEP_EN = conf.sleep;
    c_cmd.bits.OSC_SEL = conf.osc_mode;
    c_cmd.bits.CR = conf.interval;
    c_cmd.bits.OS = conf.start;

    uint8_t buf[2] = {0};
    buf[0] = reg_addr;
    buf[1] = c_cmd.byte;

    return WriteByte(handle, buf, 2);
}

MC1081_Status_t MC1081_CapMeasureGet(MC1081_Handle_t handle, MC1081_CapConvConfig_t *conf)
{
    MC1081_CHECKPTR(handle);
    MC1081_CHECKPTR(conf);

    uint8_t reg_addr = 0x1D;

    MC1081_Status_t sta = WriteByte(handle, &reg_addr, 1);
    MC1081_CHECKERR(sta);

    MC1081_C_CMD_t c_cmd = {0};
    sta = ReadByte(handle, &c_cmd.byte, 1);
    MC1081_CHECKERR(sta);

    conf->avg_cycle = c_cmd.bits.CAVG;
    conf->interval = c_cmd.bits.CR;
    conf->osc_mode = c_cmd.bits.OSC_SEL;
    conf->sleep = c_cmd.bits.SLEEP_EN;
    conf->start = c_cmd.bits.OS;

    return sta;
}

/**
 * @brief 设定 fin 的测量周期个数 N
 *
 * @param handle
 * @param cycle
 * @return MC1081_Status_t
 */
MC1081_Status_t MC1081_SetFinCycle(MC1081_Handle_t handle, uint8_t cycle)
{
    MC1081_CHECKPTR(handle);

    uint8_t data[2] = {0x1E, 0x00};
    data[1] = cycle;

    return WriteByte(handle, data, 2);
}

MC1081_Status_t MC1081_GetFinCycle(MC1081_Handle_t handle, uint8_t *cycle)
{
    MC1081_CHECKPTR(handle);
    MC1081_CHECKPTR(cycle);

    uint8_t data[2] = {0x1E, 0x00};

    MC1081_Status_t sta = WriteByte(handle, &data[0], 1);
    MC1081_CHECKERR(sta);

    sta = ReadByte(handle, &data[1], 1);
    MC1081_CHECKERR(sta);

    *cycle = data[1];

    return sta;
}

/**
 * @brief 时钟配置
 *
 * @return MC1081_Status_t
 */
MC1081_Status_t MC1081_SetClockConfig(MC1081_Handle_t handle, MC1081_ClockCfg_t cfg)
{
    MC1081_CHECKPTR(handle);

    MC1081_DIV_CFG_t div_cfg = {0};

    div_cfg.bits.FINDIV = cfg.fin_div;
    div_cfg.bits.SETTLING = cfg.fin_build;
    div_cfg.bits.FREFDIV = cfg.fref_div;

    uint8_t data[2] = {0x1F, 0x00};
    data[1] = div_cfg.byte;
    return WriteByte(handle, data, 2);
}

MC1081_Status_t MC1081_GetClockConfig(MC1081_Handle_t handle, MC1081_ClockCfg_t *cfg)
{
    MC1081_CHECKPTR(handle);
    MC1081_CHECKPTR(cfg);

    MC1081_DIV_CFG_t div_cfg = {0};

    uint8_t reg_addr = 0x1F;
    MC1081_Status_t sta = WriteByte(handle, &reg_addr, 1);
    MC1081_CHECKERR(sta);

    sta = ReadByte(handle, &div_cfg.byte, 1);
    MC1081_CHECKERR(sta);

    cfg->fin_build = div_cfg.bits.SETTLING;
    cfg->fin_div = div_cfg.bits.FINDIV;
    cfg->fref_div = div_cfg.bits.FREFDIV;

    return sta;
}

MC1081_Status_t MC1081_ChSingleEnableSet(MC1081_Handle_t handle, MC1081_ChSingleEn_t ChSingle)
{
    MC1081_CHECKPTR(handle);

    MC1081_OSC1_CHS_t osc1_chs = {0};

    osc1_chs.bytes = ChSingle.value;

    uint8_t data[3] = {0x20, 0x00, 0x00};
    data[1] = (uint8_t)(osc1_chs.bytes & 0x00FF);
    data[2] = (uint8_t)((osc1_chs.bytes & 0xFF00) >> 8);

    return WriteByte(handle, data, 3);
}

MC1081_Status_t MC1081_ChSingleEnableGet(MC1081_Handle_t handle, MC1081_ChSingleEn_t *ChSingle)
{
    MC1081_CHECKPTR(handle);
    MC1081_CHECKPTR(ChSingle);

    MC1081_OSC1_CHS_t osc1_chs = {0};

    uint8_t reg_addr = 0x20;
    MC1081_Status_t sta = WriteByte(handle, &reg_addr, 1);
    MC1081_CHECKERR(sta);

    sta = ReadByte(handle, (uint8_t *)&osc1_chs.bytes, 2);
    MC1081_CHECKERR(sta);

    ChSingle->value = osc1_chs.bytes;

    return sta;
}

MC1081_Status_t MC1081_MchxEnableSet(MC1081_Handle_t handle, MC1081_MchEn_t Mchx)
{
    MC1081_CHECKPTR(handle);

    MC1081_OSC1_MCHS_t osc1_mchs = {0};

    uint8_t reg_addr = 0x22;
    osc1_mchs.byte = Mchx.value;

    uint8_t data[2] = {0};
    data[0] = reg_addr;
    data[1] = osc1_mchs.byte;
    return WriteByte(handle, data, 2);
}

MC1081_Status_t MC1081_MchxEnableGet(MC1081_Handle_t handle, MC1081_MchEn_t *Mchx)
{
    MC1081_CHECKPTR(handle);
    MC1081_CHECKPTR(Mchx);

    MC1081_OSC1_MCHS_t osc1_mchs = {0};

    uint8_t reg_addr = 0x22;

    MC1081_Status_t sta = WriteByte(handle, &reg_addr, 1);
    MC1081_CHECKERR(sta);

    sta = ReadByte(handle, &osc1_mchs.byte, 1);
    MC1081_CHECKERR(sta);

    Mchx->value = osc1_mchs.byte;
    return sta;
}

MC1081_Status_t MC1081_SingleOSCSet(MC1081_Handle_t handle, MC1081_SingleOSCCfg_t cfg)
{
    MC1081_CHECKPTR(handle);

    MC1081_OSC1_CFG_t os1_cfg = {0};

    os1_cfg.bits.OSC1_V = cfg.amplitude;
    os1_cfg.bits.OSC1_I = cfg.dr_cu;
    os1_cfg.bits.OSC1_LDO = cfg.ldo;

    uint8_t data[2] = {0x23, 0x00};
    data[1] = os1_cfg.byte;

    return WriteByte(handle, data, 2);
}

MC1081_Status_t MC1081_SingleOSCGet(MC1081_Handle_t handle, MC1081_SingleOSCCfg_t *cfg)
{
    MC1081_CHECKPTR(handle);
    MC1081_CHECKPTR(cfg);

    uint8_t reg_addr = 0x23;
    MC1081_OSC1_CFG_t os1_cfg = {0};

    MC1081_Status_t sta = WriteByte(handle, &reg_addr, 1);
    MC1081_CHECKERR(sta);

    sta = ReadByte(handle, &os1_cfg.byte, 1);
    MC1081_CHECKERR(sta);
    cfg->amplitude = os1_cfg.bits.OSC1_V;
    cfg->dr_cu = os1_cfg.bits.OSC1_I;
    cfg->ldo = os1_cfg.bits.OSC1_LDO;
    return sta;
}

MC1081_Status_t MC1081_ChDiffEnableSet(MC1081_Handle_t handle, MC1081_ChDiffEn_t diffen)
{
    MC1081_CHECKPTR(handle);

    uint8_t data[2] = {0x24, 0x00};
    MC1081_OSC2_DCHS_t osc2_dchs = {0};

    osc2_dchs.byte = diffen.value;
    data[1] = osc2_dchs.byte;

    return WriteByte(handle, data, 2);
}

MC1081_Status_t MC1081_ChDiffEnableGet(MC1081_Handle_t handle, MC1081_ChDiffEn_t *diffen)
{
    MC1081_CHECKPTR(handle);
    MC1081_CHECKPTR(diffen);

    uint8_t reg_addr = 0x24;
    MC1081_OSC2_DCHS_t osc2_dchs = {0};

    MC1081_Status_t sta = WriteByte(handle, &reg_addr, 1);
    MC1081_CHECKERR(sta);

    sta = ReadByte(handle, &osc2_dchs.byte, 1);
    MC1081_CHECKERR(sta);

    diffen->value = osc2_dchs.byte;
    return sta;
}

MC1081_Status_t MC1081_DiffOSCSet(MC1081_Handle_t handle, MC1081_DiffOSCCfg_t cfg)
{
    MC1081_CHECKPTR(handle);

    uint8_t data[2] = {0x25, 0x00};
    MC1081_OSC2_CFG_t os2_cfg = {0};

    os2_cfg.bits.OSC2_I = cfg.dr_cu;
    os2_cfg.bits.OSC2_V = cfg.amplitude;
    os2_cfg.bits.OSC2_LDO = cfg.ldo;

    data[1] = os2_cfg.byte;

    return WriteByte(handle, data, 2);
}

MC1081_Status_t MC1081_DiffOSCGet(MC1081_Handle_t handle, MC1081_DiffOSCCfg_t *cfg)
{
    MC1081_CHECKPTR(handle);
    MC1081_CHECKPTR(cfg);
    
    MC1081_OSC2_CFG_t os2_cfg = {0};

    uint8_t reg_addr = 0x25;

    MC1081_Status_t sta = WriteByte(handle, &reg_addr, 1);
    MC1081_CHECKERR(sta);

    sta = ReadByte(handle, &os2_cfg.byte, 1);
    MC1081_CHECKERR(sta);

    cfg->amplitude = os2_cfg.bits.OSC2_V;
    cfg->dr_cu = os2_cfg.bits.OSC2_I;
    cfg->ldo = os2_cfg.bits.OSC2_LDO;

    return sta;
}

MC1081_Status_t MC1081_SoftWareReset(MC1081_Handle_t handle)
{
    MC1081_CHECKPTR(handle);

    uint8_t data[2] = {0x69, 0x7A};

    return WriteByte(handle, data, 2);
}


MC1081_Status_t MC1081_ActiveShieldSet(MC1081_Handle_t handle,MC1081_ActiveShielCfg cfg)
{
    MC1081_CHECKPTR(handle);

    MC1081_SHLD_CFG_t shld_cfg = {0};
    shld_cfg.bits.CS = cfg.sel;
    shld_cfg.bits.SHLD_EN = cfg.en;
    shld_cfg.bits.SHLD_HP = cfg.pwr;

    uint8_t data[2] = {0x26,0x00};
    data[1] = shld_cfg.byte;

    return WriteByte(handle,data,2);
}

MC1081_Status_t MC1081_ActiveShieldGet(MC1081_Handle_t handle,MC1081_ActiveShielCfg *cfg)
{
    MC1081_CHECKPTR(handle);
    MC1081_CHECKPTR(cfg);

    MC1081_SHLD_CFG_t shld_cfg = {0};
    uint8_t reg_addr = 0x26;

    MC1081_Status_t sta = WriteByte(handle,&reg_addr,1);
    MC1081_CHECKERR(sta);

    sta = ReadByte(handle,&shld_cfg.byte,1);
    MC1081_CHECKERR(sta);

    cfg->pwr = shld_cfg.bits.SHLD_HP;
    cfg->sel = shld_cfg.bits.CS;
    cfg->en = shld_cfg.bits.SHLD_EN;

    return sta;
}

MC1081_Status_t MC1081_DeInit(MC1081_Handle_t *handle)
{
    MC1081_CHECKPTR(handle);
    MC1081_CHECKPTR(*handle);

    free(*handle);
    *handle = NULL;

    return MC1081_OK;
}

uint8_t MC1081_CalI2cAddr(MC1081_AddrSel_t add)
{
    add.bits.RSV = 0x07;
    return add.value;
}
