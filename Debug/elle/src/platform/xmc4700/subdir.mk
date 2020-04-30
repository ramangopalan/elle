################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../elle/src/platform/xmc4700/dwt.c \
../elle/src/platform/xmc4700/lcd.c \
../elle/src/platform/xmc4700/platform.c \
../elle/src/platform/xmc4700/ps2.c 

OBJS += \
./elle/src/platform/xmc4700/dwt.o \
./elle/src/platform/xmc4700/lcd.o \
./elle/src/platform/xmc4700/platform.o \
./elle/src/platform/xmc4700/ps2.o 

C_DEPS += \
./elle/src/platform/xmc4700/dwt.d \
./elle/src/platform/xmc4700/lcd.d \
./elle/src/platform/xmc4700/platform.d \
./elle/src/platform/xmc4700/ps2.d 


# Each subdirectory must supply rules for building sources it contributes
elle/src/platform/xmc4700/%.o: ../elle/src/platform/xmc4700/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM-GCC C Compiler'
	"$(TOOLCHAIN_ROOT)/bin/arm-none-eabi-gcc" -MMD -MT "$@" -DXMC4700_F144x2048 -DUSE_MULTIPLE_ALLOCATOR -DLUA_OPTIMIZE_MEMORY=2 -I"$(PROJECT_LOC)/Libraries/XMCLib/inc" -I"$(PROJECT_LOC)/Libraries/CMSIS/Include" -I"$(PROJECT_LOC)/Libraries/CMSIS/Infineon/XMC4700_series/Include" -I"$(PROJECT_LOC)" -I"$(PROJECT_LOC)/Dave/Generated" -I"$(PROJECT_LOC)/Libraries" -O0 -ffunction-sections -fdata-sections -Wall -std=gnu99 -mfloat-abi=softfp -Wa,-adhlns="$@.lst" -pipe -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d) $@" -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mthumb -g -gdwarf-2 -o "$@" "$<" 
	@echo 'Finished building: $<'
	@echo.

