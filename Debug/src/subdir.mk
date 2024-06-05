################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/CounterTimer.c \
../src/Inicializacion.c \
../src/LPC845_GPIO_Dr.c \
../src/SysTick.c \
../src/cr_startup_lpc84x.c \
../src/crp.c \
../src/display.c \
../src/display_lcd.c \
../src/funciones.c \
../src/lcd.c \
../src/maquinas.c \
../src/mtb.c \
../src/oscilador.c \
../src/propiamente.c \
../src/reloj.c \
../src/sensor_dht11.c \
../src/teklado.c \
../src/timers.c \
../src/uart.c 

S_SRCS += \
../src/aeabi_romdiv_patch.s 

C_DEPS += \
./src/CounterTimer.d \
./src/Inicializacion.d \
./src/LPC845_GPIO_Dr.d \
./src/SysTick.d \
./src/cr_startup_lpc84x.d \
./src/crp.d \
./src/display.d \
./src/display_lcd.d \
./src/funciones.d \
./src/lcd.d \
./src/maquinas.d \
./src/mtb.d \
./src/oscilador.d \
./src/propiamente.d \
./src/reloj.d \
./src/sensor_dht11.d \
./src/teklado.d \
./src/timers.d \
./src/uart.d 

OBJS += \
./src/CounterTimer.o \
./src/Inicializacion.o \
./src/LPC845_GPIO_Dr.o \
./src/SysTick.o \
./src/aeabi_romdiv_patch.o \
./src/cr_startup_lpc84x.o \
./src/crp.o \
./src/display.o \
./src/display_lcd.o \
./src/funciones.o \
./src/lcd.o \
./src/maquinas.o \
./src/mtb.o \
./src/oscilador.o \
./src/propiamente.o \
./src/reloj.o \
./src/sensor_dht11.o \
./src/teklado.o \
./src/timers.o \
./src/uart.o 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__CODE_RED -DCORE_M0PLUS -D__MTB_BUFFER_SIZE=256 -D__USE_ROMDIVIDE -D__LPC84X__ -D__REDLIB__ -I"C:\Users\leuma\OneDrive\Desktop\UTN\info2\proyectos\propiamente\inc" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m0 -mthumb -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/%.o: ../src/%.s src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU Assembler'
	arm-none-eabi-gcc -c -x assembler-with-cpp -DDEBUG -D__CODE_RED -DCORE_M0PLUS -D__USE_ROMDIVIDE -D__LPC84X__ -D__REDLIB__ -g3 -mcpu=cortex-m0 -mthumb -specs=redlib.specs -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src

clean-src:
	-$(RM) ./src/CounterTimer.d ./src/CounterTimer.o ./src/Inicializacion.d ./src/Inicializacion.o ./src/LPC845_GPIO_Dr.d ./src/LPC845_GPIO_Dr.o ./src/SysTick.d ./src/SysTick.o ./src/aeabi_romdiv_patch.o ./src/cr_startup_lpc84x.d ./src/cr_startup_lpc84x.o ./src/crp.d ./src/crp.o ./src/display.d ./src/display.o ./src/display_lcd.d ./src/display_lcd.o ./src/funciones.d ./src/funciones.o ./src/lcd.d ./src/lcd.o ./src/maquinas.d ./src/maquinas.o ./src/mtb.d ./src/mtb.o ./src/oscilador.d ./src/oscilador.o ./src/propiamente.d ./src/propiamente.o ./src/reloj.d ./src/reloj.o ./src/sensor_dht11.d ./src/sensor_dht11.o ./src/teklado.d ./src/teklado.o ./src/timers.d ./src/timers.o ./src/uart.d ./src/uart.o

.PHONY: clean-src

