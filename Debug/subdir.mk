################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Button.cpp \
../EraseButtonHandler.cpp \
../Game\ -\ Copy.cpp \
../Game.cpp \
../ImageHandler.cpp \
../InfoButtonHandler.cpp \
../Main\ -\ Copy.cpp \
../Main.cpp \
../Player.cpp \
../TextDisplay.cpp \
../Tile.cpp \
../Unit.cpp \
../UnitFactory.cpp \
../backgroundMap\ 2.cpp \
../backgroundMap.cpp \
../foregroundMap.cpp 

O_SRCS += \
../Button.o \
../EraseButtonHandler.o \
../Game.o \
../ImageHandler.o \
../InfoButtonHandler.o \
../Main.o \
../Player.o \
../TextDisplay.o \
../Tile.o \
../Unit.o \
../UnitFactory.o \
../backgroundMap.o \
../foregroundMap.o 

OBJS += \
./Button.o \
./EraseButtonHandler.o \
./Game\ -\ Copy.o \
./Game.o \
./ImageHandler.o \
./InfoButtonHandler.o \
./Main\ -\ Copy.o \
./Main.o \
./Player.o \
./TextDisplay.o \
./Tile.o \
./Unit.o \
./UnitFactory.o \
./backgroundMap\ 2.o \
./backgroundMap.o \
./foregroundMap.o 

CPP_DEPS += \
./Button.d \
./EraseButtonHandler.d \
./Game\ -\ Copy.d \
./Game.d \
./ImageHandler.d \
./InfoButtonHandler.d \
./Main\ -\ Copy.d \
./Main.d \
./Player.d \
./TextDisplay.d \
./Tile.d \
./Unit.d \
./UnitFactory.d \
./backgroundMap\ 2.d \
./backgroundMap.d \
./foregroundMap.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Game\ -\ Copy.o: ../Game\ -\ Copy.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"Game - Copy.d" -MT"Game\ -\ Copy.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Main\ -\ Copy.o: ../Main\ -\ Copy.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"Main - Copy.d" -MT"Main\ -\ Copy.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

backgroundMap\ 2.o: ../backgroundMap\ 2.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"backgroundMap 2.d" -MT"backgroundMap\ 2.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


