################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../unit_tests/sp_point_unit_test.c 

OBJS += \
./unit_tests/sp_point_unit_test.o 

C_DEPS += \
./unit_tests/sp_point_unit_test.d 


# Each subdirectory must supply rules for building sources it contributes
unit_tests/%.o: ../unit_tests/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


