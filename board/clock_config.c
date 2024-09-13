/*
 * Copyright 2023 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/***********************************************************************************************************************
 * This file was generated by the MCUXpresso Config Tools. Any manual edits made to this file
 * will be overwritten if the respective MCUXpresso Config Tools is used to update this file.
 **********************************************************************************************************************/
/*
 * How to setup clock using clock driver functions:
 *
 * 1. Setup clock sources.
 *
 * 2. Set up wait states of the flash.
 *
 * 3. Set up all dividers.
 *
 * 4. Set up all selectors to provide selected clocks.
 *
 */

/* clang-format off */
/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
!!GlobalInfo
product: Clocks v12.0
processor: MCXA153
package_id: MCXA153VLH
mcu_data: ksdk2_0
processor_version: 0.13.0
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/
/* clang-format on */

#include "fsl_clock.h"
#include "clock_config.h"


/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/
/* System clock frequency. */
extern uint32_t SystemCoreClock;

/*******************************************************************************
 ************************ BOARD_InitBootClocks function ************************
 ******************************************************************************/
void BOARD_InitBootClocks(void)
{
    BOARD_BootClockFRO48M(kSPC_CoreLDO_MidDriveVoltage, kSPC_CoreLDO_NormalDriveStrength, 
                          kSPC_CoreLDO_MidDriveVoltage, kSPC_CoreLDO_LowDriveStrength);
}

/*******************************************************************************
 ******************** Configuration BOARD_BootClockFRO12M **********************
 ******************************************************************************/
/* clang-format off */
/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
!!Configuration
name: BOARD_BootClockFRO12M
outputs:
- {id: CLK_1M_clock.outFreq, value: 1 MHz}
- {id: CPU_clock.outFreq, value: 12 MHz}
- {id: FRO_12M_clock.outFreq, value: 12 MHz}
- {id: MAIN_clock.outFreq, value: 12 MHz}
- {id: Slow_clock.outFreq, value: 3 MHz}
- {id: System_clock.outFreq, value: 12 MHz}
settings:
- {id: SCGMode, value: SIRC}
- {id: FRO_HF_PERIPHERALS_EN_CFG, value: Disabled}
- {id: MRCC.OSTIMERCLKSEL.sel, value: VBAT.CLK16K_1}
- {id: SCG.SCSSEL.sel, value: SCG.SIRC}
- {id: SCG_FIRCCSR_FIRCEN_CFG, value: Disabled}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/
/* clang-format on */

/*******************************************************************************
 * Variables for BOARD_BootClockFRO12M configuration
 ******************************************************************************/
/*******************************************************************************
 * Code for BOARD_BootClockFRO12M configuration
 ******************************************************************************/
void BOARD_BootClockFRO12M(spc_core_ldo_voltage_level_t active_ldo_voltage, spc_core_ldo_drive_strength_t active_ldo_strength, spc_core_ldo_voltage_level_t lowpower_ldo_voltage, spc_core_ldo_drive_strength_t lowpower_ldo_strength)
{
    uint32_t coreFreq;
    spc_active_mode_core_ldo_option_t ldoOption;
    spc_lowpower_mode_core_ldo_option_t lowpower_ldoOption;
    spc_sram_voltage_config_t sramOption;

    /* Get the CPU Core frequency */
    coreFreq = CLOCK_GetCoreSysClkFreq();

    /* The flow of increasing voltage and frequency */
    if (coreFreq <= BOARD_BOOTCLOCKFRO12M_CORE_CLOCK) {
        /* Set the LDO_CORE VDD regulator level */
        ldoOption.CoreLDOVoltage = active_ldo_voltage;
        ldoOption.CoreLDODriveStrength = active_ldo_strength;
        (void)SPC_SetActiveModeCoreLDORegulatorConfig(SPC0, &ldoOption);
        SPC_SetLowPowerModeBandgapmodeConfig(SPC0, kSPC_BandgapEnabledBufferDisabled);
        lowpower_ldoOption.CoreLDOVoltage = lowpower_ldo_voltage;
        lowpower_ldoOption.CoreLDODriveStrength = lowpower_ldo_strength;
        (void)SPC_SetLowPowerModeCoreLDORegulatorConfig(SPC0, &lowpower_ldoOption);
        SPC_SetLowPowerModeBandgapmodeConfig(SPC0, kSPC_BandgapDisabled);
        /* Configure Flash to support different voltage level and frequency */
        FMU0->FCTRL = (FMU0->FCTRL & ~((uint32_t)FMU_FCTRL_RWSC_MASK)) | (FMU_FCTRL_RWSC(0x0U));
        /* Specifies the operating voltage for the SRAM's read/write timing margin */
        sramOption.operateVoltage = kSPC_sramOperateAt1P0V;
        sramOption.requestVoltageUpdate =  true;
        (void)SPC_SetSRAMOperateVoltage(SPC0, &sramOption);
    }

    CLOCK_SetupFRO12MClocking();                /*!< Setup FRO12M clock */

    CLOCK_AttachClk(kFRO12M_to_MAIN_CLK);       /* !< Switch MAIN_CLK to FRO12M */

    /* The flow of decreasing voltage and frequency */
    if (coreFreq > BOARD_BOOTCLOCKFRO12M_CORE_CLOCK) {
        /* Configure Flash to support different voltage level and frequency */
        FMU0->FCTRL = (FMU0->FCTRL & ~((uint32_t)FMU_FCTRL_RWSC_MASK)) | (FMU_FCTRL_RWSC(0x0U));
        /* Specifies the operating voltage for the SRAM's read/write timing margin */
        sramOption.operateVoltage = kSPC_sramOperateAt1P0V;
        sramOption.requestVoltageUpdate =  true;
        (void)SPC_SetSRAMOperateVoltage(SPC0, &sramOption);
         /* Set the LDO_CORE VDD regulator level */
        ldoOption.CoreLDOVoltage = active_ldo_voltage;
        ldoOption.CoreLDODriveStrength = active_ldo_strength;
        (void)SPC_SetActiveModeCoreLDORegulatorConfig(SPC0, &ldoOption);
        SPC_SetLowPowerModeBandgapmodeConfig(SPC0, kSPC_BandgapEnabledBufferDisabled);
        lowpower_ldoOption.CoreLDOVoltage = lowpower_ldo_voltage;
        lowpower_ldoOption.CoreLDODriveStrength = lowpower_ldo_strength;
        (void)SPC_SetLowPowerModeCoreLDORegulatorConfig(SPC0, &lowpower_ldoOption);
        SPC_SetLowPowerModeBandgapmodeConfig(SPC0, kSPC_BandgapDisabled);
    }

    /*!< Set up clock selectors - Attach clocks to the peripheries */

    /*!< Set up dividers */
    CLOCK_SetClockDiv(kCLOCK_DivAHBCLK, 1U);               /* !< Set AHBCLKDIV divider to value 1 */

    /* Set SystemCoreClock variable */
    SystemCoreClock = BOARD_BOOTCLOCKFRO12M_CORE_CLOCK;
}
/*******************************************************************************
 ******************** Configuration BOARD_BootClockFRO24M **********************
 ******************************************************************************/
/* clang-format off */
/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
!!Configuration
name: BOARD_BootClockFRO24M
outputs:
- {id: CLK_1M_clock.outFreq, value: 1 MHz}
- {id: CLK_48M_clock.outFreq, value: 48 MHz}
- {id: CPU_clock.outFreq, value: 24 MHz}
- {id: FRO_12M_clock.outFreq, value: 12 MHz}
- {id: FRO_HF_DIV_clock.outFreq, value: 48 MHz}
- {id: FRO_HF_clock.outFreq, value: 48 MHz}
- {id: MAIN_clock.outFreq, value: 48 MHz}
- {id: Slow_clock.outFreq, value: 6 MHz}
- {id: System_clock.outFreq, value: 24 MHz}
settings:
- {id: MRCC.OSTIMERCLKSEL.sel, value: VBAT.CLK16K_1}
- {id: SYSCON.AHBCLKDIV.scale, value: '2', locked: true}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/
/* clang-format on */

/*******************************************************************************
 * Variables for BOARD_BootClockFRO24M configuration
 ******************************************************************************/
/*******************************************************************************
 * Code for BOARD_BootClockFRO24M configuration
 ******************************************************************************/
void BOARD_BootClockFRO24M(void)
{
    uint32_t coreFreq;
    spc_active_mode_core_ldo_option_t ldoOption;
    spc_sram_voltage_config_t sramOption;

    /* Get the CPU Core frequency */
    coreFreq = CLOCK_GetCoreSysClkFreq();

    /* The flow of increasing voltage and frequency */
    if (coreFreq <= BOARD_BOOTCLOCKFRO24M_CORE_CLOCK) {
        /* Set the LDO_CORE VDD regulator level */
        ldoOption.CoreLDOVoltage = kSPC_CoreLDO_MidDriveVoltage;
        ldoOption.CoreLDODriveStrength = kSPC_CoreLDO_NormalDriveStrength;
        (void)SPC_SetActiveModeCoreLDORegulatorConfig(SPC0, &ldoOption);
        /* Configure Flash to support different voltage level and frequency */
        FMU0->FCTRL = (FMU0->FCTRL & ~((uint32_t)FMU_FCTRL_RWSC_MASK)) | (FMU_FCTRL_RWSC(0x0U));
        /* Specifies the operating voltage for the SRAM's read/write timing margin */
        sramOption.operateVoltage = kSPC_sramOperateAt1P0V;
        sramOption.requestVoltageUpdate =  true;
        (void)SPC_SetSRAMOperateVoltage(SPC0, &sramOption);
    }

    CLOCK_SetupFROHFClocking(48000000U);               /*!< Enable FRO HF(48MHz) output */

    CLOCK_SetupFRO12MClocking();                /*!< Setup FRO12M clock */

    CLOCK_AttachClk(kFRO_HF_to_MAIN_CLK);       /* !< Switch MAIN_CLK to FRO_HF */

    /* The flow of decreasing voltage and frequency */
    if (coreFreq > BOARD_BOOTCLOCKFRO24M_CORE_CLOCK) {
        /* Configure Flash to support different voltage level and frequency */
        FMU0->FCTRL = (FMU0->FCTRL & ~((uint32_t)FMU_FCTRL_RWSC_MASK)) | (FMU_FCTRL_RWSC(0x0U));
        /* Specifies the operating voltage for the SRAM's read/write timing margin */
        sramOption.operateVoltage = kSPC_sramOperateAt1P0V;
        sramOption.requestVoltageUpdate =  true;
        (void)SPC_SetSRAMOperateVoltage(SPC0, &sramOption);
        /* Set the LDO_CORE VDD regulator level */
        ldoOption.CoreLDOVoltage = kSPC_CoreLDO_MidDriveVoltage;
        ldoOption.CoreLDODriveStrength = kSPC_CoreLDO_NormalDriveStrength;
        (void)SPC_SetActiveModeCoreLDORegulatorConfig(SPC0, &ldoOption);
    }

    /*!< Set up clock selectors - Attach clocks to the peripheries */

    /*!< Set up dividers */
    CLOCK_SetClockDiv(kCLOCK_DivAHBCLK, 2U);               /* !< Set AHBCLKDIV divider to value 2 */
    CLOCK_SetClockDiv(kCLOCK_DivFRO_HF_DIV, 1U);           /* !< Set FROHFDIV divider to value 1 */

    /* Set SystemCoreClock variable */
    SystemCoreClock = BOARD_BOOTCLOCKFRO24M_CORE_CLOCK;
}
/*******************************************************************************
 ******************** Configuration BOARD_BootClockFRO48M **********************
 ******************************************************************************/
/* clang-format off */
/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
!!Configuration
name: BOARD_BootClockFRO48M
outputs:
- {id: CLK_1M_clock.outFreq, value: 1 MHz}
- {id: CLK_48M_clock.outFreq, value: 48 MHz}
- {id: CPU_clock.outFreq, value: 48 MHz}
- {id: FRO_12M_clock.outFreq, value: 12 MHz}
- {id: FRO_HF_DIV_clock.outFreq, value: 48 MHz}
- {id: FRO_HF_clock.outFreq, value: 48 MHz}
- {id: MAIN_clock.outFreq, value: 48 MHz}
- {id: Slow_clock.outFreq, value: 12 MHz}
- {id: System_clock.outFreq, value: 48 MHz}
settings:
- {id: MRCC.OSTIMERCLKSEL.sel, value: VBAT.CLK16K_1}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/
/* clang-format on */

/*******************************************************************************
 * Variables for BOARD_BootClockFRO48M configuration
 ******************************************************************************/
/*******************************************************************************
 * Code for BOARD_BootClockFRO48M configuration
 ******************************************************************************/
void BOARD_BootClockFRO48M(spc_core_ldo_voltage_level_t active_ldo_voltage, spc_core_ldo_drive_strength_t active_ldo_strength, spc_core_ldo_voltage_level_t lowpower_ldo_voltage, spc_core_ldo_drive_strength_t lowpower_ldo_strength)
{
    uint32_t coreFreq;
    spc_active_mode_core_ldo_option_t ldoOption;
    spc_lowpower_mode_core_ldo_option_t lowpower_ldoOption;
    spc_sram_voltage_config_t sramOption;

    /* Get the CPU Core frequency */
    coreFreq = CLOCK_GetCoreSysClkFreq();

    /* The flow of increasing voltage and frequency */
    if (coreFreq <= BOARD_BOOTCLOCKFRO48M_CORE_CLOCK) {
        /* Set the LDO_CORE VDD regulator level */
        ldoOption.CoreLDOVoltage = active_ldo_voltage;
        ldoOption.CoreLDODriveStrength = active_ldo_strength;
        (void)SPC_SetActiveModeCoreLDORegulatorConfig(SPC0, &ldoOption);
        SPC_SetLowPowerModeBandgapmodeConfig(SPC0, kSPC_BandgapEnabledBufferDisabled);
        lowpower_ldoOption.CoreLDOVoltage = lowpower_ldo_voltage;
        lowpower_ldoOption.CoreLDODriveStrength = lowpower_ldo_strength;
        (void)SPC_SetLowPowerModeCoreLDORegulatorConfig(SPC0, &lowpower_ldoOption);
        SPC_SetLowPowerModeBandgapmodeConfig(SPC0, kSPC_BandgapDisabled);
        /* Configure Flash to support different voltage level and frequency */
        FMU0->FCTRL = (FMU0->FCTRL & ~((uint32_t)FMU_FCTRL_RWSC_MASK)) | (FMU_FCTRL_RWSC(0x1U));
        /* Specifies the operating voltage for the SRAM's read/write timing margin */
        sramOption.operateVoltage = kSPC_sramOperateAt1P0V;
        sramOption.requestVoltageUpdate =  true;
        (void)SPC_SetSRAMOperateVoltage(SPC0, &sramOption);
    }

    CLOCK_SetupFROHFClocking(48000000U);               /*!< Enable FRO HF(48MHz) output */

    CLOCK_SetupFRO12MClocking();                /*!< Setup FRO12M clock */

    CLOCK_AttachClk(kFRO_HF_to_MAIN_CLK);       /* !< Switch MAIN_CLK to FRO_HF */

    /* The flow of decreasing voltage and frequency */
    if (coreFreq > BOARD_BOOTCLOCKFRO48M_CORE_CLOCK) {
        /* Configure Flash to support different voltage level and frequency */
        FMU0->FCTRL = (FMU0->FCTRL & ~((uint32_t)FMU_FCTRL_RWSC_MASK)) | (FMU_FCTRL_RWSC(0x1U));
        /* Specifies the operating voltage for the SRAM's read/write timing margin */
        sramOption.operateVoltage = kSPC_sramOperateAt1P0V;
        sramOption.requestVoltageUpdate =  true;
        (void)SPC_SetSRAMOperateVoltage(SPC0, &sramOption);
        /* Set the LDO_CORE VDD regulator level */
        ldoOption.CoreLDOVoltage = active_ldo_voltage;
        ldoOption.CoreLDODriveStrength = active_ldo_strength;
        (void)SPC_SetActiveModeCoreLDORegulatorConfig(SPC0, &ldoOption);
        SPC_SetLowPowerModeBandgapmodeConfig(SPC0, kSPC_BandgapEnabledBufferDisabled);
        lowpower_ldoOption.CoreLDOVoltage = lowpower_ldo_voltage;
        lowpower_ldoOption.CoreLDODriveStrength = lowpower_ldo_strength;
        (void)SPC_SetLowPowerModeCoreLDORegulatorConfig(SPC0, &lowpower_ldoOption);
        SPC_SetLowPowerModeBandgapmodeConfig(SPC0, kSPC_BandgapDisabled);
    }

    /*!< Set up clock selectors - Attach clocks to the peripheries */

    /*!< Set up dividers */
    CLOCK_SetClockDiv(kCLOCK_DivAHBCLK, 1U);               /* !< Set AHBCLKDIV divider to value 1 */
    CLOCK_SetClockDiv(kCLOCK_DivFRO_HF_DIV, 1U);           /* !< Set FROHFDIV divider to value 1 */

    /* Set SystemCoreClock variable */
    SystemCoreClock = BOARD_BOOTCLOCKFRO48M_CORE_CLOCK;
}
/*******************************************************************************
 ******************** Configuration BOARD_BootClockFRO64M **********************
 ******************************************************************************/
/* clang-format off */
/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
!!Configuration
name: BOARD_BootClockFRO64M
outputs:
- {id: CLK_1M_clock.outFreq, value: 1 MHz}
- {id: CLK_48M_clock.outFreq, value: 48 MHz}
- {id: CPU_clock.outFreq, value: 64 MHz}
- {id: FRO_12M_clock.outFreq, value: 12 MHz}
- {id: FRO_HF_DIV_clock.outFreq, value: 64 MHz}
- {id: FRO_HF_clock.outFreq, value: 64 MHz}
- {id: MAIN_clock.outFreq, value: 64 MHz}
- {id: Slow_clock.outFreq, value: 16 MHz}
- {id: System_clock.outFreq, value: 64 MHz}
settings:
- {id: VDD_CORE, value: voltage_1v1}
- {id: MRCC.FROHFDIV.scale, value: '1', locked: true}
- {id: MRCC.OSTIMERCLKSEL.sel, value: VBAT.CLK16K_1}
- {id: SYSCON.AHBCLKDIV.scale, value: '1', locked: true}
sources:
- {id: SCG.FIRC.outFreq, value: 64 MHz}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/
/* clang-format on */

/*******************************************************************************
 * Variables for BOARD_BootClockFRO64M configuration
 ******************************************************************************/
/*******************************************************************************
 * Code for BOARD_BootClockFRO64M configuration
 ******************************************************************************/
void BOARD_BootClockFRO64M(void)
{
    uint32_t coreFreq;
    spc_active_mode_core_ldo_option_t ldoOption;
    spc_sram_voltage_config_t sramOption;

    /* Get the CPU Core frequency */
    coreFreq = CLOCK_GetCoreSysClkFreq();

    /* The flow of increasing voltage and frequency */
    if (coreFreq <= BOARD_BOOTCLOCKFRO64M_CORE_CLOCK) {
        /* Set the LDO_CORE VDD regulator level */
        ldoOption.CoreLDOVoltage = kSPC_CoreLDO_NormalVoltage;
        ldoOption.CoreLDODriveStrength = kSPC_CoreLDO_NormalDriveStrength;
        (void)SPC_SetActiveModeCoreLDORegulatorConfig(SPC0, &ldoOption);
        /* Configure Flash to support different voltage level and frequency */
        FMU0->FCTRL = (FMU0->FCTRL & ~((uint32_t)FMU_FCTRL_RWSC_MASK)) | (FMU_FCTRL_RWSC(0x1U));
        /* Specifies the operating voltage for the SRAM's read/write timing margin */
        sramOption.operateVoltage = kSPC_sramOperateAt1P1V;
        sramOption.requestVoltageUpdate =  true;
        (void)SPC_SetSRAMOperateVoltage(SPC0, &sramOption);
    }

    CLOCK_SetupFROHFClocking(64000000U);               /*!< Enable FRO HF(64MHz) output */

    CLOCK_SetupFRO12MClocking();                /*!< Setup FRO12M clock */

    CLOCK_AttachClk(kFRO_HF_to_MAIN_CLK);       /* !< Switch MAIN_CLK to FRO_HF */

    /* The flow of decreasing voltage and frequency */
    if (coreFreq > BOARD_BOOTCLOCKFRO64M_CORE_CLOCK) {
        /* Configure Flash to support different voltage level and frequency */
        FMU0->FCTRL = (FMU0->FCTRL & ~((uint32_t)FMU_FCTRL_RWSC_MASK)) | (FMU_FCTRL_RWSC(0x1U));
        /* Specifies the operating voltage for the SRAM's read/write timing margin */
        sramOption.operateVoltage = kSPC_sramOperateAt1P1V;
        sramOption.requestVoltageUpdate =  true;
        (void)SPC_SetSRAMOperateVoltage(SPC0, &sramOption);
        /* Set the LDO_CORE VDD regulator level */
        ldoOption.CoreLDOVoltage = kSPC_CoreLDO_NormalVoltage;
        ldoOption.CoreLDODriveStrength = kSPC_CoreLDO_NormalDriveStrength;
        (void)SPC_SetActiveModeCoreLDORegulatorConfig(SPC0, &ldoOption);
    }

    /*!< Set up clock selectors - Attach clocks to the peripheries */

    /*!< Set up dividers */
    CLOCK_SetClockDiv(kCLOCK_DivAHBCLK, 1U);               /* !< Set AHBCLKDIV divider to value 1 */
    CLOCK_SetClockDiv(kCLOCK_DivFRO_HF_DIV, 1U);           /* !< Set FROHFDIV divider to value 1 */

    /* Set SystemCoreClock variable */
    SystemCoreClock = BOARD_BOOTCLOCKFRO64M_CORE_CLOCK;
}
/*******************************************************************************
 ******************** Configuration BOARD_BootClockFRO96M **********************
 ******************************************************************************/
/* clang-format off */
/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
!!Configuration
name: BOARD_BootClockFRO96M
called_from_default_init: true
outputs:
- {id: CLK_1M_clock.outFreq, value: 1 MHz}
- {id: CLK_48M_clock.outFreq, value: 48 MHz}
- {id: CPU_clock.outFreq, value: 96 MHz}
- {id: FRO_12M_clock.outFreq, value: 12 MHz}
- {id: FRO_HF_DIV_clock.outFreq, value: 96 MHz}
- {id: FRO_HF_clock.outFreq, value: 96 MHz}
- {id: MAIN_clock.outFreq, value: 96 MHz}
- {id: Slow_clock.outFreq, value: 24 MHz}
- {id: System_clock.outFreq, value: 96 MHz}
settings:
- {id: VDD_CORE, value: voltage_1v1}
- {id: CLKOUTDIV_HALT, value: Enable}
- {id: MRCC.FROHFDIV.scale, value: '1', locked: true}
- {id: MRCC.OSTIMERCLKSEL.sel, value: VBAT.CLK16K_1}
- {id: SYSCON.AHBCLKDIV.scale, value: '1', locked: true}
sources:
- {id: SCG.FIRC.outFreq, value: 96 MHz}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/
/* clang-format on */

/*******************************************************************************
 * Variables for BOARD_BootClockFRO96M configuration
 ******************************************************************************/
/*******************************************************************************
 * Code for BOARD_BootClockFRO96M configuration
 ******************************************************************************/
void BOARD_BootClockFRO96M(spc_core_ldo_voltage_level_t active_ldo_voltage, spc_core_ldo_drive_strength_t active_ldo_strength, spc_core_ldo_voltage_level_t lowpower_ldo_voltage, spc_core_ldo_drive_strength_t lowpower_ldo_strength)
{
    uint32_t coreFreq;
    spc_active_mode_core_ldo_option_t ldoOption;
    spc_lowpower_mode_core_ldo_option_t lowpower_ldoOption;
    spc_sram_voltage_config_t sramOption;

    /* Get the CPU Core frequency */
    coreFreq = CLOCK_GetCoreSysClkFreq();

    /* The flow of increasing voltage and frequency */
    if (coreFreq <= BOARD_BOOTCLOCKFRO96M_CORE_CLOCK) {
        /* Set the LDO_CORE VDD regulator level */
        ldoOption.CoreLDOVoltage = active_ldo_voltage;
        ldoOption.CoreLDODriveStrength = active_ldo_strength;
        (void)SPC_SetActiveModeCoreLDORegulatorConfig(SPC0, &ldoOption);
        SPC_SetLowPowerModeBandgapmodeConfig(SPC0, kSPC_BandgapEnabledBufferDisabled);
        lowpower_ldoOption.CoreLDOVoltage = lowpower_ldo_voltage;
        lowpower_ldoOption.CoreLDODriveStrength = lowpower_ldo_strength;
        (void)SPC_SetLowPowerModeCoreLDORegulatorConfig(SPC0, &lowpower_ldoOption);
        SPC_SetLowPowerModeBandgapmodeConfig(SPC0, kSPC_BandgapDisabled);
        /* Configure Flash to support different voltage level and frequency */
        FMU0->FCTRL = (FMU0->FCTRL & ~((uint32_t)FMU_FCTRL_RWSC_MASK)) | (FMU_FCTRL_RWSC(0x2U));
        /* Specifies the operating voltage for the SRAM's read/write timing margin */
        sramOption.operateVoltage = kSPC_sramOperateAt1P1V;
        sramOption.requestVoltageUpdate =  true;
        (void)SPC_SetSRAMOperateVoltage(SPC0, &sramOption);
    }

    CLOCK_SetupFROHFClocking(96000000U);               /*!< Enable FRO HF(96MHz) output */

    CLOCK_SetupFRO12MClocking();                /*!< Setup FRO12M clock */

    CLOCK_AttachClk(kFRO_HF_to_MAIN_CLK);       /* !< Switch MAIN_CLK to FRO_HF */

    /* The flow of decreasing voltage and frequency */
    if (coreFreq > BOARD_BOOTCLOCKFRO96M_CORE_CLOCK) {
        /* Configure Flash to support different voltage level and frequency */
        FMU0->FCTRL = (FMU0->FCTRL & ~((uint32_t)FMU_FCTRL_RWSC_MASK)) | (FMU_FCTRL_RWSC(0x2U));
        /* Specifies the operating voltage for the SRAM's read/write timing margin */
        sramOption.operateVoltage = kSPC_sramOperateAt1P1V;
        sramOption.requestVoltageUpdate =  true;
        (void)SPC_SetSRAMOperateVoltage(SPC0, &sramOption);
        /* Set the LDO_CORE VDD regulator level */
        ldoOption.CoreLDOVoltage = active_ldo_voltage;
        ldoOption.CoreLDODriveStrength = active_ldo_strength;
        (void)SPC_SetActiveModeCoreLDORegulatorConfig(SPC0, &ldoOption);
        SPC_SetLowPowerModeBandgapmodeConfig(SPC0, kSPC_BandgapEnabledBufferDisabled);
        lowpower_ldoOption.CoreLDOVoltage = lowpower_ldo_voltage;
        lowpower_ldoOption.CoreLDODriveStrength = lowpower_ldo_strength;
        (void)SPC_SetLowPowerModeCoreLDORegulatorConfig(SPC0, &lowpower_ldoOption);
        SPC_SetLowPowerModeBandgapmodeConfig(SPC0, kSPC_BandgapDisabled);
    }

    /*!< Set up clock selectors - Attach clocks to the peripheries */

    /*!< Set up dividers */
    CLOCK_SetClockDiv(kCLOCK_DivAHBCLK, 1U);               /* !< Set AHBCLKDIV divider to value 1 */
    CLOCK_SetClockDiv(kCLOCK_DivFRO_HF_DIV, 1U);           /* !< Set FROHFDIV divider to value 1 */

    /* Set SystemCoreClock variable */
    SystemCoreClock = BOARD_BOOTCLOCKFRO96M_CORE_CLOCK;
}
