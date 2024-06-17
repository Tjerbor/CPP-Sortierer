################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
C:/Users/Thiemo/Documents/emb/CPP-Sortierer/Src/Bargraf.cpp \
C:/Users/Thiemo/Documents/emb/CPP-Sortierer/Src/lib.cpp \
C:/Users/Thiemo/Documents/emb/CPP-Sortierer/Src/main.cpp \
C:/Users/Thiemo/Documents/emb/CPP-Sortierer/Src/state.cpp 

S_SRCS += \
../startup.s 

S_DEPS += \
./Src/startup.d 

OBJS += \
./Src/Bargraf.o \
./Src/lib.o \
./Src/main.o \
./Src/startup.o \
./Src/state.o 

CPP_DEPS += \
./Src/Bargraf.d \
./Src/lib.d \
./Src/main.d \
./Src/state.d 


# Each subdirectory must supply rules for building sources it contributes
Src/Bargraf.o: C:/Users/Thiemo/Documents/emb/CPP-Sortierer/Src/Bargraf.cpp Src/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m3 -std=gnu++14 -g3 -DSTM32L100xC -DMCU_STM32L100xC -DCOMPILER_GCC -DOSCSRC=HSE_BYPASS -DOSCFREQ=8000 -c -I"C:/Users/Thiemo/Documents/emb/EmbSysLib-01.04.00/Src" -I"C:/Users/Thiemo/Documents/emb/EmbSysLib-01.04.00/Src/Hardware/MCU/STM32L1xx" -I"C:/Users/Thiemo/Documents/emb/EmbSysLib-01.04.00/Src/Hardware/MCU/STM32L1xx/Sys/GCC" -I../../../../Src -I../../../../Src/Board/STM32L100-Discovery -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Src/lib.o: C:/Users/Thiemo/Documents/emb/CPP-Sortierer/Src/lib.cpp Src/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m3 -std=gnu++14 -g3 -DSTM32L100xC -DMCU_STM32L100xC -DCOMPILER_GCC -DOSCSRC=HSE_BYPASS -DOSCFREQ=8000 -c -I"C:/Users/Thiemo/Documents/emb/EmbSysLib-01.04.00/Src" -I"C:/Users/Thiemo/Documents/emb/EmbSysLib-01.04.00/Src/Hardware/MCU/STM32L1xx" -I"C:/Users/Thiemo/Documents/emb/EmbSysLib-01.04.00/Src/Hardware/MCU/STM32L1xx/Sys/GCC" -I../../../../Src -I../../../../Src/Board/STM32L100-Discovery -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Src/main.o: C:/Users/Thiemo/Documents/emb/CPP-Sortierer/Src/main.cpp Src/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m3 -std=gnu++20 -g3 -DSTM32L100xC -DMCU_STM32L100xC -DCOMPILER_GCC -DOSCSRC=HSE_BYPASS -DOSCFREQ=8000 -c -I"C:/Users/Thiemo/Documents/emb/EmbSysLib-01.04.00/Src" -I"C:/Users/Thiemo/Documents/emb/EmbSysLib-01.04.00/Src/Hardware/MCU/STM32L1xx" -I"C:/Users/Thiemo/Documents/emb/EmbSysLib-01.04.00/Src/Hardware/MCU/STM32L1xx/Sys/GCC" -I../../../../Src -I../../../../Src/Board/STM32L100-Discovery -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Src/startup.o: C:/Users/Thiemo/Documents/emb/CPP-Sortierer/Project/STM32L100-Discovery/STM32CubeIDE/startup.s Src/subdir.mk
	arm-none-eabi-gcc -mcpu=cortex-m3 -g3 -DDEBUG -DPROJECT_CPP -c -I"C:/Users/Thiemo/Documents/emb/EmbSysLib-01.04.00/Src/Hardware/MCU/STM32L1xx/Sys/GCC" -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@" "$<"
Src/state.o: C:/Users/Thiemo/Documents/emb/CPP-Sortierer/Src/state.cpp Src/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m3 -std=gnu++14 -g3 -DSTM32L100xC -DMCU_STM32L100xC -DCOMPILER_GCC -DOSCSRC=HSE_BYPASS -DOSCFREQ=8000 -c -I"C:/Users/Thiemo/Documents/emb/EmbSysLib-01.04.00/Src" -I"C:/Users/Thiemo/Documents/emb/EmbSysLib-01.04.00/Src/Hardware/MCU/STM32L1xx" -I"C:/Users/Thiemo/Documents/emb/EmbSysLib-01.04.00/Src/Hardware/MCU/STM32L1xx/Sys/GCC" -I../../../../Src -I../../../../Src/Board/STM32L100-Discovery -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Src

clean-Src:
	-$(RM) ./Src/Bargraf.cyclo ./Src/Bargraf.d ./Src/Bargraf.o ./Src/Bargraf.su ./Src/lib.cyclo ./Src/lib.d ./Src/lib.o ./Src/lib.su ./Src/main.cyclo ./Src/main.d ./Src/main.o ./Src/main.su ./Src/startup.d ./Src/startup.o ./Src/state.cyclo ./Src/state.d ./Src/state.o ./Src/state.su

.PHONY: clean-Src

