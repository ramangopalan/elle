################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../elle/src/buf.c \
../elle/src/common.c \
../elle/src/common_fs.c \
../elle/src/common_tmr.c \
../elle/src/common_uart.c \
../elle/src/dlmalloc.c \
../elle/src/elua_adc.c \
../elle/src/elua_int.c \
../elle/src/elua_mmc.c \
../elle/src/elua_mmc_sim.c \
../elle/src/elua_uip.c \
../elle/src/eluarpc.c \
../elle/src/fifo.c \
../elle/src/linenoise.c \
../elle/src/linenoise_posix.c \
../elle/src/luarpc_desktop_serial.c \
../elle/src/luarpc_elua_uart.c \
../elle/src/mmcfs.c \
../elle/src/romfs.c \
../elle/src/salloc.c \
../elle/src/semifs.c \
../elle/src/term.c \
../elle/src/xmodem.c 

OBJS += \
./elle/src/buf.o \
./elle/src/common.o \
./elle/src/common_fs.o \
./elle/src/common_tmr.o \
./elle/src/common_uart.o \
./elle/src/dlmalloc.o \
./elle/src/elua_adc.o \
./elle/src/elua_int.o \
./elle/src/elua_mmc.o \
./elle/src/elua_mmc_sim.o \
./elle/src/elua_uip.o \
./elle/src/eluarpc.o \
./elle/src/fifo.o \
./elle/src/linenoise.o \
./elle/src/linenoise_posix.o \
./elle/src/luarpc_desktop_serial.o \
./elle/src/luarpc_elua_uart.o \
./elle/src/mmcfs.o \
./elle/src/romfs.o \
./elle/src/salloc.o \
./elle/src/semifs.o \
./elle/src/term.o \
./elle/src/xmodem.o 

C_DEPS += \
./elle/src/buf.d \
./elle/src/common.d \
./elle/src/common_fs.d \
./elle/src/common_tmr.d \
./elle/src/common_uart.d \
./elle/src/dlmalloc.d \
./elle/src/elua_adc.d \
./elle/src/elua_int.d \
./elle/src/elua_mmc.d \
./elle/src/elua_mmc_sim.d \
./elle/src/elua_uip.d \
./elle/src/eluarpc.d \
./elle/src/fifo.d \
./elle/src/linenoise.d \
./elle/src/linenoise_posix.d \
./elle/src/luarpc_desktop_serial.d \
./elle/src/luarpc_elua_uart.d \
./elle/src/mmcfs.d \
./elle/src/romfs.d \
./elle/src/salloc.d \
./elle/src/semifs.d \
./elle/src/term.d \
./elle/src/xmodem.d 


# Each subdirectory must supply rules for building sources it contributes
elle/src/%.o: ../elle/src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM-GCC C Compiler'
	"$(TOOLCHAIN_ROOT)/bin/arm-none-eabi-gcc" -MMD -MT "$@" -DXMC4700_F144x2048 -DUSE_MULTIPLE_ALLOCATOR -DLUA_OPTIMIZE_MEMORY=2 -I"$(PROJECT_LOC)/Libraries/XMCLib/inc" -I"$(PROJECT_LOC)/Libraries/CMSIS/Include" -I"$(PROJECT_LOC)/Libraries/CMSIS/Infineon/XMC4700_series/Include" -I"$(PROJECT_LOC)" -I"$(PROJECT_LOC)/Dave/Generated" -I"$(PROJECT_LOC)/Libraries" -O0 -ffunction-sections -fdata-sections -Wall -std=gnu99 -mfloat-abi=softfp -Wa,-adhlns="$@.lst" -pipe -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d) $@" -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mthumb -g -gdwarf-2 -o "$@" "$<" 
	@echo 'Finished building: $<'
	@echo.

