################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../source/PES_Project_5.c \
../source/System.c \
../source/circularbuffer.c \
../source/count_characters.c \
../source/led_control.c \
../source/logger.c \
../source/mtb.c \
../source/semihost_hardfault.c \
../source/test.c \
../source/timestamp.c \
../source/uart.c 

OBJS += \
./source/PES_Project_5.o \
./source/System.o \
./source/circularbuffer.o \
./source/count_characters.o \
./source/led_control.o \
./source/logger.o \
./source/mtb.o \
./source/semihost_hardfault.o \
./source/test.o \
./source/timestamp.o \
./source/uart.o 

C_DEPS += \
./source/PES_Project_5.d \
./source/System.d \
./source/circularbuffer.d \
./source/count_characters.d \
./source/led_control.d \
./source/logger.d \
./source/mtb.d \
./source/semihost_hardfault.d \
./source/test.d \
./source/timestamp.d \
./source/uart.d 


# Each subdirectory must supply rules for building sources it contributes
source/%.o: ../source/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DCPU_MKL25Z128VLK4 -DCPU_MKL25Z128VLK4_cm0plus -DFSL_RTOS_BM -DSDK_OS_BAREMETAL -DSDK_DEBUGCONSOLE=0 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -DSDK_DEBUGCONSOLE_UART -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -D__REDLIB__ -I../board -I../source -I../ -I../drivers -I../CMSIS -I../utilities -I../startup -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


