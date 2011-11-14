################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
O_SRCS += \
../enc28j60.o \
../ip_arp_udp.o \
../main.o \
../test0.o \
../test1.o \
../test2.o \
../timeout.o 

C_SRCS += \
../enc28j60.c \
../ip_arp_udp.c \
../main.c \
../test0.c \
../test1.c \
../test2.c \
../test_readSiliconRev.c \
../timeout.c 

OBJS += \
./enc28j60.o \
./ip_arp_udp.o \
./main.o \
./test0.o \
./test1.o \
./test2.o \
./test_readSiliconRev.o \
./timeout.o 

C_DEPS += \
./enc28j60.d \
./ip_arp_udp.d \
./main.d \
./test0.d \
./test1.d \
./test2.d \
./test_readSiliconRev.d \
./timeout.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega88 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


