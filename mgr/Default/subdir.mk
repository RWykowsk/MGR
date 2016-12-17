################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../extBitset.cpp \
../fileUtils.cpp \
../functions.cpp \
../main.cpp \
../menu.cpp 

OBJS += \
./extBitset.o \
./fileUtils.o \
./functions.o \
./main.o \
./menu.o 

CPP_DEPS += \
./extBitset.d \
./fileUtils.d \
./functions.d \
./main.d \
./menu.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


