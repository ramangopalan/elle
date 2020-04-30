################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include elle/src/uip/subdir.mk
-include elle/src/shell/subdir.mk
-include elle/src/serial/subdir.mk
-include elle/src/rxspencer/subdir.mk
-include elle/src/remotefs/subdir.mk
-include elle/src/platform/xmc4700/subdir.mk
-include elle/src/platform/subdir.mk
-include elle/src/newlib/subdir.mk
-include elle/src/modules/subdir.mk
-include elle/src/lua/subdir.mk
-include elle/src/gnu-ed-1.16/subdir.mk
-include elle/src/subdir.mk
-include Startup/subdir.mk
-include Libraries/XMCLib/src/subdir.mk
-include Libraries/Newlib/subdir.mk
-include Dave/Generated/UART/subdir.mk
-include Dave/Generated/TIMER/subdir.mk
-include Dave/Generated/SYSTIMER/subdir.mk
-include Dave/Generated/SDMMC_BLOCK/subdir.mk
-include Dave/Generated/RTC/subdir.mk
-include Dave/Generated/PIN_INTERRUPT/subdir.mk
-include Dave/Generated/INTERRUPT/subdir.mk
-include Dave/Generated/GLOBAL_DMA/subdir.mk
-include Dave/Generated/GLOBAL_CCU4/subdir.mk
-include Dave/Generated/FATFS/ff_Src/subdir.mk
-include Dave/Generated/FATFS/subdir.mk
-include Dave/Generated/DIGITAL_IO/subdir.mk
-include Dave/Generated/CPU_CTRL_XMC4/subdir.mk
-include Dave/Generated/CLOCK_XMC4/subdir.mk
-include Dave/Generated/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
SECONDARY_FLASH += \
Elle.hex \

SECONDARY_LIST += \
Elle.lst \

SECONDARY_SIZE += \
Elle.siz \


LIST_FILES = $(addsuffix .o.lst, $(basename $(OBJS))) 
MAP_FILE = "Elle.map"

TOOLCHAIN_ROOT=C:/DAVE-IDE-4.4.2-64Bit/eclipse/ARM-GCC-49
PROJECT_LOC=C:/DAVE-IDE-4.4.2-64Bit/elle/Elle

# All Target
all: Elle.elf secondary-outputs

# Tool invocations
Elle.elf: $(OBJS) ../linker_script.ld $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: ARM-GCC C Linker'
	$(file >objects.rsp,$(OBJS))
	"$(TOOLCHAIN_ROOT)/bin/arm-none-eabi-gcc" -T"../linker_script.ld" -nostartfiles -Xlinker --gc-sections -specs=nosys.specs -Wl,-Map,$(MAP_FILE) -mfloat-abi=softfp -mfpu=fpv4-sp-d16 -mcpu=cortex-m4 -mthumb -g -gdwarf-2 -o "Elle.elf" "@objects.rsp" $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo.
Elle.hex: Elle.elf
	@echo 'Invoking: ARM-GCC Create Flash Image'
	"$(TOOLCHAIN_ROOT)/bin/arm-none-eabi-objcopy" -O ihex "Elle.elf" "Elle.hex"
	@echo 'Finished building: $@'
	@echo.
Elle.lst: Elle.elf
	@echo 'Invoking: ARM-GCC Create Listing'
	"$(TOOLCHAIN_ROOT)/bin/arm-none-eabi-objdump" -h -S "Elle.elf" > "Elle.lst"
	@echo 'Finished building: $@'
	@echo.
Elle.siz: Elle.elf
	@echo 'Invoking: ARM-GCC Print Size'
	"$(TOOLCHAIN_ROOT)/bin/arm-none-eabi-size" --format=berkeley "Elle.elf"
	@echo 'Finished building: $@'
	@echo.
# Other Targets
clean:
	-$(RM) $(SECONDARY_FLASH)$(SECONDARY_LIST)$(SECONDARY_SIZE)$(ARM_GCC_FOR_XMC_LINKER_OUTPUT_TYPE_OUTPUTS)$(S_DEPS)$(S_UPPER_DEPS)$(C_DEPS)
	-$(RM) Dave/Generated/CLOCK_XMC4/clock_xmc4.o Dave/Generated/CLOCK_XMC4/clock_xmc4_conf.o Dave/Generated/CPU_CTRL_XMC4/cpu_ctrl_xmc4.o Dave/Generated/CPU_CTRL_XMC4/cpu_ctrl_xmc4_conf.o Dave/Generated/DAVE.o Dave/Generated/DIGITAL_IO/digital_io.o Dave/Generated/DIGITAL_IO/digital_io_conf.o Dave/Generated/FATFS/fatfs.o Dave/Generated/FATFS/fatfs_conf.o Dave/Generated/FATFS/sltha.o Dave/Generated/FATFS/ff_Src/ff.o Dave/Generated/FATFS/ff_Src/syscall.o Dave/Generated/GLOBAL_CCU4/global_ccu4.o Dave/Generated/GLOBAL_CCU4/global_ccu4_conf.o Dave/Generated/GLOBAL_DMA/global_dma.o Dave/Generated/GLOBAL_DMA/global_dma_conf.o Dave/Generated/INTERRUPT/interrupt.o Dave/Generated/INTERRUPT/interrupt_conf.o Dave/Generated/PIN_INTERRUPT/pin_interrupt.o Dave/Generated/PIN_INTERRUPT/pin_interrupt_conf.o Dave/Generated/RTC/rtc.o Dave/Generated/RTC/rtc_conf.o Dave/Generated/SDMMC_BLOCK/sdmmc_block.o Dave/Generated/SDMMC_BLOCK/sdmmc_block_conf.o Dave/Generated/SDMMC_BLOCK/sdmmc_block_private_sd.o Dave/Generated/SYSTIMER/systimer.o Dave/Generated/SYSTIMER/systimer_conf.o Dave/Generated/TIMER/timer.o Dave/Generated/TIMER/timer_conf.o Dave/Generated/UART/uart.o Dave/Generated/UART/uart_conf.o Libraries/Newlib/syscalls.o Libraries/XMCLib/src/xmc4_eru.o Libraries/XMCLib/src/xmc4_flash.o Libraries/XMCLib/src/xmc4_gpio.o Libraries/XMCLib/src/xmc4_rtc.o Libraries/XMCLib/src/xmc4_scu.o Libraries/XMCLib/src/xmc_can.o Libraries/XMCLib/src/xmc_ccu4.o Libraries/XMCLib/src/xmc_ccu8.o Libraries/XMCLib/src/xmc_common.o Libraries/XMCLib/src/xmc_dac.o Libraries/XMCLib/src/xmc_dma.o Libraries/XMCLib/src/xmc_dsd.o Libraries/XMCLib/src/xmc_ebu.o Libraries/XMCLib/src/xmc_ecat.o Libraries/XMCLib/src/xmc_eru.o Libraries/XMCLib/src/xmc_eth_mac.o Libraries/XMCLib/src/xmc_eth_phy_dp83848.o Libraries/XMCLib/src/xmc_eth_phy_ksz8031rnl.o Libraries/XMCLib/src/xmc_eth_phy_ksz8081rnb.o Libraries/XMCLib/src/xmc_fce.o Libraries/XMCLib/src/xmc_gpio.o 
	-$(RM) Libraries/XMCLib/src/xmc_hrpwm.o Libraries/XMCLib/src/xmc_i2c.o Libraries/XMCLib/src/xmc_i2s.o Libraries/XMCLib/src/xmc_ledts.o Libraries/XMCLib/src/xmc_posif.o Libraries/XMCLib/src/xmc_rtc.o Libraries/XMCLib/src/xmc_sdmmc.o Libraries/XMCLib/src/xmc_spi.o Libraries/XMCLib/src/xmc_uart.o Libraries/XMCLib/src/xmc_usbd.o Libraries/XMCLib/src/xmc_usbh.o Libraries/XMCLib/src/xmc_usic.o Libraries/XMCLib/src/xmc_vadc.o Libraries/XMCLib/src/xmc_wdt.o Startup/startup_XMC4700.o Startup/system_XMC4700.o elle/src/buf.o elle/src/common.o elle/src/common_fs.o elle/src/common_tmr.o elle/src/common_uart.o elle/src/dlmalloc.o elle/src/elua_adc.o elle/src/elua_int.o elle/src/elua_mmc.o elle/src/elua_mmc_sim.o elle/src/elua_uip.o elle/src/eluarpc.o elle/src/fifo.o elle/src/linenoise.o elle/src/linenoise_posix.o elle/src/luarpc_desktop_serial.o elle/src/luarpc_elua_uart.o elle/src/mmcfs.o elle/src/romfs.o elle/src/salloc.o elle/src/semifs.o elle/src/term.o elle/src/xmodem.o elle/src/gnu-ed-1.16/buffer.o elle/src/gnu-ed-1.16/carg_parser.o elle/src/gnu-ed-1.16/global.o elle/src/gnu-ed-1.16/io.o elle/src/gnu-ed-1.16/main.o elle/src/gnu-ed-1.16/main_loop.o elle/src/gnu-ed-1.16/regex.o elle/src/gnu-ed-1.16/signal.o elle/src/lua/lapi.o elle/src/lua/lauxlib.o elle/src/lua/lbaselib.o elle/src/lua/lcode.o elle/src/lua/ldblib.o elle/src/lua/ldebug.o elle/src/lua/ldo.o elle/src/lua/ldump.o elle/src/lua/legc.o elle/src/lua/lfunc.o elle/src/lua/lgc.o elle/src/lua/linit.o elle/src/lua/liolib.o elle/src/lua/llex.o elle/src/lua/lmathlib.o elle/src/lua/lmem.o elle/src/lua/loadlib.o elle/src/lua/lobject.o elle/src/lua/lopcodes.o elle/src/lua/loslib.o elle/src/lua/lparser.o elle/src/lua/lrotable.o elle/src/lua/lstate.o elle/src/lua/lstring.o elle/src/lua/lstrlib.o elle/src/lua/ltable.o elle/src/lua/ltablib.o elle/src/lua/ltm.o elle/src/lua/lua.o elle/src/lua/luac.o elle/src/lua/lundump.o elle/src/lua/lvm.o elle/src/lua/lzio.o elle/src/lua/print.o 
	-$(RM) elle/src/modules/adc.o elle/src/modules/bit.o elle/src/modules/bitarray.o elle/src/modules/can.o elle/src/modules/cpu.o elle/src/modules/elua.o elle/src/modules/i2c.o elle/src/modules/lpack.o elle/src/modules/luarpc.o elle/src/modules/net.o elle/src/modules/pd.o elle/src/modules/pio.o elle/src/modules/pwm.o elle/src/modules/spi.o elle/src/modules/term.o elle/src/modules/tmr.o elle/src/modules/uart.o elle/src/newlib/devman.o elle/src/newlib/genstd.o elle/src/newlib/stdtcp.o elle/src/newlib/stubs.o elle/src/platform/arm_cortex_interrupts.o elle/src/platform/cortex_utils.o elle/src/platform/xmc4700/dwt.o elle/src/platform/xmc4700/lcd.o elle/src/platform/xmc4700/platform.o elle/src/platform/xmc4700/ps2.o elle/src/remotefs/client.o elle/src/remotefs/elua_os_io.o elle/src/remotefs/elua_rfs.o elle/src/remotefs/remotefs.o elle/src/rxspencer/debug.o elle/src/rxspencer/main.o elle/src/rxspencer/regcomp.o elle/src/rxspencer/regerror.o elle/src/rxspencer/regexec.o elle/src/rxspencer/regfree.o elle/src/rxspencer/split.o elle/src/serial/serial_posix.o elle/src/serial/serial_win32.o elle/src/shell/shell.o elle/src/shell/shell_adv_cp_mv.o elle/src/shell/shell_adv_rm.o elle/src/shell/shell_cat.o elle/src/shell/shell_clear.o elle/src/shell/shell_ed.o elle/src/shell/shell_help.o elle/src/shell/shell_ls.o elle/src/shell/shell_lua.o elle/src/shell/shell_luac.o elle/src/shell/shell_mkdir.o elle/src/shell/shell_recv.o elle/src/shell/shell_ver.o elle/src/shell/shell_wofmt.o elle/src/uip/dhcpc.o elle/src/uip/psock.o elle/src/uip/resolv.o elle/src/uip/timer.o elle/src/uip/uip-fw.o elle/src/uip/uip-neighbor.o elle/src/uip/uip-split.o elle/src/uip/uip.o elle/src/uip/uip_arp.o elle/src/uip/uiplib.o main.o  Elle.elf $(LIST_FILES) $(MAP_FILE) objects.rsp
	-@echo.
secondary-outputs: $(SECONDARY_FLASH) $(SECONDARY_LIST) $(SECONDARY_SIZE)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
