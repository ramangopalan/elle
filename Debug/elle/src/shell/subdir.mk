################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../elle/src/shell/shell.c \
../elle/src/shell/shell_adv_cp_mv.c \
../elle/src/shell/shell_adv_rm.c \
../elle/src/shell/shell_cat.c \
../elle/src/shell/shell_clear.c \
../elle/src/shell/shell_ed.c \
../elle/src/shell/shell_help.c \
../elle/src/shell/shell_ls.c \
../elle/src/shell/shell_lua.c \
../elle/src/shell/shell_luac.c \
../elle/src/shell/shell_mkdir.c \
../elle/src/shell/shell_recv.c \
../elle/src/shell/shell_ver.c \
../elle/src/shell/shell_wofmt.c 

OBJS += \
./elle/src/shell/shell.o \
./elle/src/shell/shell_adv_cp_mv.o \
./elle/src/shell/shell_adv_rm.o \
./elle/src/shell/shell_cat.o \
./elle/src/shell/shell_clear.o \
./elle/src/shell/shell_ed.o \
./elle/src/shell/shell_help.o \
./elle/src/shell/shell_ls.o \
./elle/src/shell/shell_lua.o \
./elle/src/shell/shell_luac.o \
./elle/src/shell/shell_mkdir.o \
./elle/src/shell/shell_recv.o \
./elle/src/shell/shell_ver.o \
./elle/src/shell/shell_wofmt.o 

C_DEPS += \
./elle/src/shell/shell.d \
./elle/src/shell/shell_adv_cp_mv.d \
./elle/src/shell/shell_adv_rm.d \
./elle/src/shell/shell_cat.d \
./elle/src/shell/shell_clear.d \
./elle/src/shell/shell_ed.d \
./elle/src/shell/shell_help.d \
./elle/src/shell/shell_ls.d \
./elle/src/shell/shell_lua.d \
./elle/src/shell/shell_luac.d \
./elle/src/shell/shell_mkdir.d \
./elle/src/shell/shell_recv.d \
./elle/src/shell/shell_ver.d \
./elle/src/shell/shell_wofmt.d 


# Each subdirectory must supply rules for building sources it contributes
elle/src/shell/%.o: ../elle/src/shell/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM-GCC C Compiler'
	"$(TOOLCHAIN_ROOT)/bin/arm-none-eabi-gcc" -MMD -MT "$@" -DXMC4700_F144x2048 -DUSE_MULTIPLE_ALLOCATOR -DLUA_OPTIMIZE_MEMORY=2 -I"$(PROJECT_LOC)/Libraries/XMCLib/inc" -I"$(PROJECT_LOC)/Libraries/CMSIS/Include" -I"$(PROJECT_LOC)/Libraries/CMSIS/Infineon/XMC4700_series/Include" -I"$(PROJECT_LOC)" -I"$(PROJECT_LOC)/Dave/Generated" -I"$(PROJECT_LOC)/Libraries" -O0 -ffunction-sections -fdata-sections -Wall -std=gnu99 -mfloat-abi=softfp -Wa,-adhlns="$@.lst" -pipe -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d) $@" -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mthumb -g -gdwarf-2 -o "$@" "$<" 
	@echo 'Finished building: $<'
	@echo.

