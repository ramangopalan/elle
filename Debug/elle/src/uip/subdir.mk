################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../elle/src/uip/dhcpc.c \
../elle/src/uip/psock.c \
../elle/src/uip/resolv.c \
../elle/src/uip/timer.c \
../elle/src/uip/uip-fw.c \
../elle/src/uip/uip-neighbor.c \
../elle/src/uip/uip-split.c \
../elle/src/uip/uip.c \
../elle/src/uip/uip_arp.c \
../elle/src/uip/uiplib.c 

OBJS += \
./elle/src/uip/dhcpc.o \
./elle/src/uip/psock.o \
./elle/src/uip/resolv.o \
./elle/src/uip/timer.o \
./elle/src/uip/uip-fw.o \
./elle/src/uip/uip-neighbor.o \
./elle/src/uip/uip-split.o \
./elle/src/uip/uip.o \
./elle/src/uip/uip_arp.o \
./elle/src/uip/uiplib.o 

C_DEPS += \
./elle/src/uip/dhcpc.d \
./elle/src/uip/psock.d \
./elle/src/uip/resolv.d \
./elle/src/uip/timer.d \
./elle/src/uip/uip-fw.d \
./elle/src/uip/uip-neighbor.d \
./elle/src/uip/uip-split.d \
./elle/src/uip/uip.d \
./elle/src/uip/uip_arp.d \
./elle/src/uip/uiplib.d 


# Each subdirectory must supply rules for building sources it contributes
elle/src/uip/%.o: ../elle/src/uip/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM-GCC C Compiler'
	"$(TOOLCHAIN_ROOT)/bin/arm-none-eabi-gcc" -MMD -MT "$@" -DXMC4700_F144x2048 -DUSE_MULTIPLE_ALLOCATOR -DLUA_OPTIMIZE_MEMORY=2 -I"$(PROJECT_LOC)/Libraries/XMCLib/inc" -I"$(PROJECT_LOC)/Libraries/CMSIS/Include" -I"$(PROJECT_LOC)/Libraries/CMSIS/Infineon/XMC4700_series/Include" -I"$(PROJECT_LOC)" -I"$(PROJECT_LOC)/Dave/Generated" -I"$(PROJECT_LOC)/Libraries" -O0 -ffunction-sections -fdata-sections -Wall -std=gnu99 -mfloat-abi=softfp -Wa,-adhlns="$@.lst" -pipe -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d) $@" -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mthumb -g -gdwarf-2 -o "$@" "$<" 
	@echo 'Finished building: $<'
	@echo.

