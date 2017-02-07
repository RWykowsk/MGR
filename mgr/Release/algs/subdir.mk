################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../algs/BasicAlg.cpp \
../algs/Stripped.cpp \
../algs/SuperFun.cpp \
../algs/SuperFunBA.cpp \
../algs/extBitset.cpp 

OBJS += \
./algs/BasicAlg.o \
./algs/Stripped.o \
./algs/SuperFun.o \
./algs/SuperFunBA.o \
./algs/extBitset.o 

CPP_DEPS += \
./algs/BasicAlg.d \
./algs/Stripped.d \
./algs/SuperFun.d \
./algs/SuperFunBA.d \
./algs/extBitset.d 


# Each subdirectory must supply rules for building sources it contributes
algs/%.o: ../algs/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cygwin C++ Compiler'
	g++ -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


