################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../generate/src/Clock_Ip_Cfg.c \
../generate/src/Clock_Ip_VS_0_PBcfg.c \
../generate/src/Eth_43_GMAC_Ipw_VS_0_PBcfg.c \
../generate/src/Eth_43_GMAC_VS_0_PBcfg.c \
../generate/src/Gmac_Ip_Cfg.c \
../generate/src/Gmac_Ip_VS_0_PBcfg.c \
../generate/src/Igf_Port_Ip_Cfg.c \
../generate/src/Igf_Port_Ip_VS_0_PBcfg.c \
../generate/src/Mcu_Cfg.c \
../generate/src/Mcu_VS_0_PBcfg.c \
../generate/src/OsIf_Cfg.c \
../generate/src/Port_Cfg.c \
../generate/src/Port_VS_0_PBcfg.c \
../generate/src/Power_Ip_Cfg.c \
../generate/src/Power_Ip_VS_0_PBcfg.c \
../generate/src/Ram_Ip_Cfg.c \
../generate/src/Ram_Ip_VS_0_PBcfg.c \
../generate/src/Siul2_Port_Ip_VS_0_PBcfg.c \
../generate/src/Tspc_Port_Ip_VS_0_PBcfg.c 

OBJS += \
./generate/src/Clock_Ip_Cfg.o \
./generate/src/Clock_Ip_VS_0_PBcfg.o \
./generate/src/Eth_43_GMAC_Ipw_VS_0_PBcfg.o \
./generate/src/Eth_43_GMAC_VS_0_PBcfg.o \
./generate/src/Gmac_Ip_Cfg.o \
./generate/src/Gmac_Ip_VS_0_PBcfg.o \
./generate/src/Igf_Port_Ip_Cfg.o \
./generate/src/Igf_Port_Ip_VS_0_PBcfg.o \
./generate/src/Mcu_Cfg.o \
./generate/src/Mcu_VS_0_PBcfg.o \
./generate/src/OsIf_Cfg.o \
./generate/src/Port_Cfg.o \
./generate/src/Port_VS_0_PBcfg.o \
./generate/src/Power_Ip_Cfg.o \
./generate/src/Power_Ip_VS_0_PBcfg.o \
./generate/src/Ram_Ip_Cfg.o \
./generate/src/Ram_Ip_VS_0_PBcfg.o \
./generate/src/Siul2_Port_Ip_VS_0_PBcfg.o \
./generate/src/Tspc_Port_Ip_VS_0_PBcfg.o 

C_DEPS += \
./generate/src/Clock_Ip_Cfg.d \
./generate/src/Clock_Ip_VS_0_PBcfg.d \
./generate/src/Eth_43_GMAC_Ipw_VS_0_PBcfg.d \
./generate/src/Eth_43_GMAC_VS_0_PBcfg.d \
./generate/src/Gmac_Ip_Cfg.d \
./generate/src/Gmac_Ip_VS_0_PBcfg.d \
./generate/src/Igf_Port_Ip_Cfg.d \
./generate/src/Igf_Port_Ip_VS_0_PBcfg.d \
./generate/src/Mcu_Cfg.d \
./generate/src/Mcu_VS_0_PBcfg.d \
./generate/src/OsIf_Cfg.d \
./generate/src/Port_Cfg.d \
./generate/src/Port_VS_0_PBcfg.d \
./generate/src/Power_Ip_Cfg.d \
./generate/src/Power_Ip_VS_0_PBcfg.d \
./generate/src/Ram_Ip_Cfg.d \
./generate/src/Ram_Ip_VS_0_PBcfg.d \
./generate/src/Siul2_Port_Ip_VS_0_PBcfg.d \
./generate/src/Tspc_Port_Ip_VS_0_PBcfg.d 


# Each subdirectory must supply rules for building sources it contributes
generate/src/%.o: ../generate/src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@generate/src/Clock_Ip_Cfg.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


