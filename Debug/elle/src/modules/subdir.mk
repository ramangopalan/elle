################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../elle/src/modules/adc.c \
../elle/src/modules/bit.c \
../elle/src/modules/bitarray.c \
../elle/src/modules/can.c \
../elle/src/modules/cpu.c \
../elle/src/modules/elua.c \
../elle/src/modules/i2c.c \
../elle/src/modules/lpack.c \
../elle/src/modules/luarpc.c \
../elle/src/modules/net.c \
../elle/src/modules/pd.c \
../elle/src/modules/pio.c \
../elle/src/modules/pwm.c \
../elle/src/modules/spi.c \
../elle/src/modules/term.c \
../elle/src/modules/tmr.c \
../elle/src/modules/uart.c 

OBJS += \
./elle/src/modules/adc.o \
./elle/src/modules/bit.o \
./elle/src/modules/bitarray.o \
./elle/src/modules/can.o \
./elle/src/modules/cpu.o \
./elle/src/modules/elua.o \
./elle/src/modules/i2c.o \
./elle/src/modules/lpack.o \
./elle/src/modules/luarpc.o \
./elle/src/modules/net.o \
./elle/src/modules/pd.o \
./elle/src/modules/pio.o \
./elle/src/modules/pwm.o \
./elle/src/modules/spi.o \
./elle/src/modules/term.o \
./elle/src/modules/tmr.o \
./elle/src/modules/uart.o 

C_DEPS += \
./elle/src/modules/adc.d \
./elle/src/modules/bit.d \
./elle/src/modules/bitarray.d \
./elle/src/modules/can.d \
./elle/src/modules/cpu.d \
./elle/src/modules/elua.d \
./elle/src/modules/i2c.d \
./elle/src/modules/lpack.d \
./elle/src/modules/luarpc.d \
./elle/src/modules/net.d \
./elle/src/modules/pd.d \
./elle/src/modules/pio.d \
./elle/src/modules/pwm.d \
./elle/src/modules/spi.d \
./elle/src/modules/term.d \
./elle/src/modules/tmr.d \
./elle/src/modules/uart.d 


# Each subdirectory must supply rules for building sources it contributes
elle/src/modules/%.o: ../elle/src/modules/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM-GCC C Compiler'
	"$(TOOLCHAIN_ROOT)/bin/arm-none-eabi-gcc" -MMD -MT "$@" -DXMC4700_F144x2048 -DUSE_MULTIPLE_ALLOCATOR -DLUA_OPTIMIZE_MEMORY=2 -I"$(PROJECT_LOC)/Libraries/XMCLib/inc" -I"$(PROJECT_LOC)/Libraries/CMSIS/Include" -I"$(PROJECT_LOC)/Libraries/CMSIS/Infineon/XMC4700_series/Include" -I"$(PROJECT_LOC)" -I"$(PROJECT_LOC)/Dave/Generated" -I"$(PROJECT_LOC)/Libraries" -O0 -ffunction-sections -fdata-sections -Wall -std=gnu99 -mfloat-abi=softfp -Wa,-adhlns="$@.lst" -pipe -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d) $@" -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mthumb -g -gdwarf-2 -o "$@" "$<" 
	@echo 'Finished building: $<'
	@echo.

