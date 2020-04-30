################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../elle/src/remotefs/client.c \
../elle/src/remotefs/elua_os_io.c \
../elle/src/remotefs/elua_rfs.c \
../elle/src/remotefs/remotefs.c 

OBJS += \
./elle/src/remotefs/client.o \
./elle/src/remotefs/elua_os_io.o \
./elle/src/remotefs/elua_rfs.o \
./elle/src/remotefs/remotefs.o 

C_DEPS += \
./elle/src/remotefs/client.d \
./elle/src/remotefs/elua_os_io.d \
./elle/src/remotefs/elua_rfs.d \
./elle/src/remotefs/remotefs.d 


# Each subdirectory must supply rules for building sources it contributes
elle/src/remotefs/%.o: ../elle/src/remotefs/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM-GCC C Compiler'
	"$(TOOLCHAIN_ROOT)/bin/arm-none-eabi-gcc" -MMD -MT "$@" -DXMC4700_F144x2048 -DUSE_MULTIPLE_ALLOCATOR -DLUA_OPTIMIZE_MEMORY=2 -I"$(PROJECT_LOC)/Libraries/XMCLib/inc" -I"$(PROJECT_LOC)/Libraries/CMSIS/Include" -I"$(PROJECT_LOC)/Libraries/CMSIS/Infineon/XMC4700_series/Include" -I"$(PROJECT_LOC)" -I"$(PROJECT_LOC)/Dave/Generated" -I"$(PROJECT_LOC)/Libraries" -O0 -ffunction-sections -fdata-sections -Wall -std=gnu99 -mfloat-abi=softfp -Wa,-adhlns="$@.lst" -pipe -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d) $@" -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mthumb -g -gdwarf-2 -o "$@" "$<" 
	@echo 'Finished building: $<'
	@echo.

