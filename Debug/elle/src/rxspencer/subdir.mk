################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../elle/src/rxspencer/debug.c \
../elle/src/rxspencer/main.c \
../elle/src/rxspencer/regcomp.c \
../elle/src/rxspencer/regerror.c \
../elle/src/rxspencer/regexec.c \
../elle/src/rxspencer/regfree.c \
../elle/src/rxspencer/split.c 

OBJS += \
./elle/src/rxspencer/debug.o \
./elle/src/rxspencer/main.o \
./elle/src/rxspencer/regcomp.o \
./elle/src/rxspencer/regerror.o \
./elle/src/rxspencer/regexec.o \
./elle/src/rxspencer/regfree.o \
./elle/src/rxspencer/split.o 

C_DEPS += \
./elle/src/rxspencer/debug.d \
./elle/src/rxspencer/main.d \
./elle/src/rxspencer/regcomp.d \
./elle/src/rxspencer/regerror.d \
./elle/src/rxspencer/regexec.d \
./elle/src/rxspencer/regfree.d \
./elle/src/rxspencer/split.d 


# Each subdirectory must supply rules for building sources it contributes
elle/src/rxspencer/%.o: ../elle/src/rxspencer/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM-GCC C Compiler'
	"$(TOOLCHAIN_ROOT)/bin/arm-none-eabi-gcc" -MMD -MT "$@" -DXMC4700_F144x2048 -DUSE_MULTIPLE_ALLOCATOR -DLUA_OPTIMIZE_MEMORY=2 -I"$(PROJECT_LOC)/Libraries/XMCLib/inc" -I"$(PROJECT_LOC)/Libraries/CMSIS/Include" -I"$(PROJECT_LOC)/Libraries/CMSIS/Infineon/XMC4700_series/Include" -I"$(PROJECT_LOC)" -I"$(PROJECT_LOC)/Dave/Generated" -I"$(PROJECT_LOC)/Libraries" -O0 -ffunction-sections -fdata-sections -Wall -std=gnu99 -mfloat-abi=softfp -Wa,-adhlns="$@.lst" -pipe -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d) $@" -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mthumb -g -gdwarf-2 -o "$@" "$<" 
	@echo 'Finished building: $<'
	@echo.

