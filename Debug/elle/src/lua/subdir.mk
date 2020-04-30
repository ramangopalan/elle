################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../elle/src/lua/lapi.c \
../elle/src/lua/lauxlib.c \
../elle/src/lua/lbaselib.c \
../elle/src/lua/lcode.c \
../elle/src/lua/ldblib.c \
../elle/src/lua/ldebug.c \
../elle/src/lua/ldo.c \
../elle/src/lua/ldump.c \
../elle/src/lua/legc.c \
../elle/src/lua/lfunc.c \
../elle/src/lua/lgc.c \
../elle/src/lua/linit.c \
../elle/src/lua/liolib.c \
../elle/src/lua/llex.c \
../elle/src/lua/lmathlib.c \
../elle/src/lua/lmem.c \
../elle/src/lua/loadlib.c \
../elle/src/lua/lobject.c \
../elle/src/lua/lopcodes.c \
../elle/src/lua/loslib.c \
../elle/src/lua/lparser.c \
../elle/src/lua/lrotable.c \
../elle/src/lua/lstate.c \
../elle/src/lua/lstring.c \
../elle/src/lua/lstrlib.c \
../elle/src/lua/ltable.c \
../elle/src/lua/ltablib.c \
../elle/src/lua/ltm.c \
../elle/src/lua/lua.c \
../elle/src/lua/luac.c \
../elle/src/lua/lundump.c \
../elle/src/lua/lvm.c \
../elle/src/lua/lzio.c \
../elle/src/lua/print.c 

OBJS += \
./elle/src/lua/lapi.o \
./elle/src/lua/lauxlib.o \
./elle/src/lua/lbaselib.o \
./elle/src/lua/lcode.o \
./elle/src/lua/ldblib.o \
./elle/src/lua/ldebug.o \
./elle/src/lua/ldo.o \
./elle/src/lua/ldump.o \
./elle/src/lua/legc.o \
./elle/src/lua/lfunc.o \
./elle/src/lua/lgc.o \
./elle/src/lua/linit.o \
./elle/src/lua/liolib.o \
./elle/src/lua/llex.o \
./elle/src/lua/lmathlib.o \
./elle/src/lua/lmem.o \
./elle/src/lua/loadlib.o \
./elle/src/lua/lobject.o \
./elle/src/lua/lopcodes.o \
./elle/src/lua/loslib.o \
./elle/src/lua/lparser.o \
./elle/src/lua/lrotable.o \
./elle/src/lua/lstate.o \
./elle/src/lua/lstring.o \
./elle/src/lua/lstrlib.o \
./elle/src/lua/ltable.o \
./elle/src/lua/ltablib.o \
./elle/src/lua/ltm.o \
./elle/src/lua/lua.o \
./elle/src/lua/luac.o \
./elle/src/lua/lundump.o \
./elle/src/lua/lvm.o \
./elle/src/lua/lzio.o \
./elle/src/lua/print.o 

C_DEPS += \
./elle/src/lua/lapi.d \
./elle/src/lua/lauxlib.d \
./elle/src/lua/lbaselib.d \
./elle/src/lua/lcode.d \
./elle/src/lua/ldblib.d \
./elle/src/lua/ldebug.d \
./elle/src/lua/ldo.d \
./elle/src/lua/ldump.d \
./elle/src/lua/legc.d \
./elle/src/lua/lfunc.d \
./elle/src/lua/lgc.d \
./elle/src/lua/linit.d \
./elle/src/lua/liolib.d \
./elle/src/lua/llex.d \
./elle/src/lua/lmathlib.d \
./elle/src/lua/lmem.d \
./elle/src/lua/loadlib.d \
./elle/src/lua/lobject.d \
./elle/src/lua/lopcodes.d \
./elle/src/lua/loslib.d \
./elle/src/lua/lparser.d \
./elle/src/lua/lrotable.d \
./elle/src/lua/lstate.d \
./elle/src/lua/lstring.d \
./elle/src/lua/lstrlib.d \
./elle/src/lua/ltable.d \
./elle/src/lua/ltablib.d \
./elle/src/lua/ltm.d \
./elle/src/lua/lua.d \
./elle/src/lua/luac.d \
./elle/src/lua/lundump.d \
./elle/src/lua/lvm.d \
./elle/src/lua/lzio.d \
./elle/src/lua/print.d 


# Each subdirectory must supply rules for building sources it contributes
elle/src/lua/%.o: ../elle/src/lua/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM-GCC C Compiler'
	"$(TOOLCHAIN_ROOT)/bin/arm-none-eabi-gcc" -MMD -MT "$@" -DXMC4700_F144x2048 -DUSE_MULTIPLE_ALLOCATOR -DLUA_OPTIMIZE_MEMORY=2 -I"$(PROJECT_LOC)/Libraries/XMCLib/inc" -I"$(PROJECT_LOC)/Libraries/CMSIS/Include" -I"$(PROJECT_LOC)/Libraries/CMSIS/Infineon/XMC4700_series/Include" -I"$(PROJECT_LOC)" -I"$(PROJECT_LOC)/Dave/Generated" -I"$(PROJECT_LOC)/Libraries" -O0 -ffunction-sections -fdata-sections -Wall -std=gnu99 -mfloat-abi=softfp -Wa,-adhlns="$@.lst" -pipe -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d) $@" -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mthumb -g -gdwarf-2 -o "$@" "$<" 
	@echo 'Finished building: $<'
	@echo.

