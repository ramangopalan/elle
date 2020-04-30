################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../elle/src/newlib/devman.c \
../elle/src/newlib/genstd.c \
../elle/src/newlib/stdtcp.c \
../elle/src/newlib/stubs.c 

OBJS += \
./elle/src/newlib/devman.o \
./elle/src/newlib/genstd.o \
./elle/src/newlib/stdtcp.o \
./elle/src/newlib/stubs.o 

C_DEPS += \
./elle/src/newlib/devman.d \
./elle/src/newlib/genstd.d \
./elle/src/newlib/stdtcp.d \
./elle/src/newlib/stubs.d 


# Each subdirectory must supply rules for building sources it contributes
elle/src/newlib/%.o: ../elle/src/newlib/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM-GCC C Compiler'
	"$(TOOLCHAIN_ROOT)/bin/arm-none-eabi-gcc" -MMD -MT "$@" -DXMC4700_F144x2048 -DUSE_MULTIPLE_ALLOCATOR -DLUA_OPTIMIZE_MEMORY=2 -I"$(PROJECT_LOC)/Libraries/XMCLib/inc" -I"$(PROJECT_LOC)/Libraries/CMSIS/Include" -I"$(PROJECT_LOC)/Libraries/CMSIS/Infineon/XMC4700_series/Include" -I"$(PROJECT_LOC)" -I"$(PROJECT_LOC)/Dave/Generated" -I"$(PROJECT_LOC)/Libraries" -O0 -ffunction-sections -fdata-sections -Wall -std=gnu99 -mfloat-abi=softfp -Wa,-adhlns="$@.lst" -pipe -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d) $@" -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mthumb -g -gdwarf-2 -o "$@" "$<" 
	@echo 'Finished building: $<'
	@echo.

