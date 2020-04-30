################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../elle/src/compiler/asm.c \
../elle/src/compiler/ast.c \
../elle/src/compiler/error.c \
../elle/src/compiler/gen.c \
../elle/src/compiler/input.c \
../elle/src/compiler/lex.c \
../elle/src/compiler/main.c \
../elle/src/compiler/parser.c \
../elle/src/compiler/stack.c \
../elle/src/compiler/sym.c \
../elle/src/compiler/vm.c 

OBJS += \
./elle/src/compiler/asm.o \
./elle/src/compiler/ast.o \
./elle/src/compiler/error.o \
./elle/src/compiler/gen.o \
./elle/src/compiler/input.o \
./elle/src/compiler/lex.o \
./elle/src/compiler/main.o \
./elle/src/compiler/parser.o \
./elle/src/compiler/stack.o \
./elle/src/compiler/sym.o \
./elle/src/compiler/vm.o 

C_DEPS += \
./elle/src/compiler/asm.d \
./elle/src/compiler/ast.d \
./elle/src/compiler/error.d \
./elle/src/compiler/gen.d \
./elle/src/compiler/input.d \
./elle/src/compiler/lex.d \
./elle/src/compiler/main.d \
./elle/src/compiler/parser.d \
./elle/src/compiler/stack.d \
./elle/src/compiler/sym.d \
./elle/src/compiler/vm.d 


# Each subdirectory must supply rules for building sources it contributes
elle/src/compiler/%.o: ../elle/src/compiler/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM-GCC C Compiler'
	"$(TOOLCHAIN_ROOT)/bin/arm-none-eabi-gcc" -MMD -MT "$@" -DXMC4700_F144x2048 -DUSE_MULTIPLE_ALLOCATOR -DLUA_OPTIMIZE_MEMORY=2 -DMIN_OPT_LEVEL=2 -I"$(PROJECT_LOC)/Libraries/XMCLib/inc" -I"$(PROJECT_LOC)/Libraries/CMSIS/Include" -I"$(PROJECT_LOC)/Libraries/CMSIS/Infineon/XMC4700_series/Include" -I"$(PROJECT_LOC)" -I"$(PROJECT_LOC)/Dave/Generated" -I"$(PROJECT_LOC)/Libraries" -O0 -ffunction-sections -fdata-sections -Wall -std=gnu99 -mfloat-abi=softfp -Wa,-adhlns="$@.lst" -pipe -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d) $@" -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mthumb -g -gdwarf-2 -o "$@" "$<" 
	@echo 'Finished building: $<'
	@echo.

