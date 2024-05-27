################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include wiseconnect3_sdk_3.2.0/components/service/network_manager/src/subdir.mk
-include wiseconnect3_sdk_3.2.0/components/service/network_manager/si91x/subdir.mk
-include wiseconnect3_sdk_3.2.0/components/service/bsd_socket/si91x_socket/subdir.mk
-include wiseconnect3_sdk_3.2.0/components/protocol/wifi/src/subdir.mk
-include wiseconnect3_sdk_3.2.0/components/protocol/wifi/si91x/subdir.mk
-include wiseconnect3_sdk_3.2.0/components/device/silabs/si91x/wireless/threading/subdir.mk
-include wiseconnect3_sdk_3.2.0/components/device/silabs/si91x/wireless/src/subdir.mk
-include wiseconnect3_sdk_3.2.0/components/device/silabs/si91x/wireless/socket/src/subdir.mk
-include wiseconnect3_sdk_3.2.0/components/device/silabs/si91x/wireless/sl_net/src/subdir.mk
-include wiseconnect3_sdk_3.2.0/components/device/silabs/si91x/wireless/memory/subdir.mk
-include wiseconnect3_sdk_3.2.0/components/device/silabs/si91x/wireless/icmp/subdir.mk
-include wiseconnect3_sdk_3.2.0/components/device/silabs/si91x/wireless/host_mcu/si91x/subdir.mk
-include wiseconnect3_sdk_3.2.0/components/device/silabs/si91x/wireless/firmware_upgrade/subdir.mk
-include wiseconnect3_sdk_3.2.0/components/device/silabs/si91x/wireless/errno/src/subdir.mk
-include wiseconnect3_sdk_3.2.0/components/device/silabs/si91x/wireless/asynchronous_socket/src/subdir.mk
-include wiseconnect3_sdk_3.2.0/components/device/silabs/si91x/wireless/ahb_interface/src/subdir.mk
-include wiseconnect3_sdk_3.2.0/components/device/silabs/si91x/mcu/drivers/systemlevel/src/subdir.mk
-include wiseconnect3_sdk_3.2.0/components/device/silabs/si91x/mcu/drivers/peripheral_drivers/src/subdir.mk
-include wiseconnect3_sdk_3.2.0/components/device/silabs/si91x/mcu/drivers/cmsis_driver/subdir.mk
-include wiseconnect3_sdk_3.2.0/components/device/silabs/si91x/mcu/core/config/src/subdir.mk
-include wiseconnect3_sdk_3.2.0/components/device/silabs/si91x/mcu/core/common/src/subdir.mk
-include wiseconnect3_sdk_3.2.0/components/device/silabs/si91x/mcu/core/chip/src/iPMU_prog/iPMU_dotc/subdir.mk
-include wiseconnect3_sdk_3.2.0/components/device/silabs/si91x/mcu/core/chip/src/subdir.mk
-include wiseconnect3_sdk_3.2.0/components/common/src/subdir.mk
-include wiseconnect3_sdk_3.2.0/components/board/silabs/src/subdir.mk
-include gecko_sdk_4.4.3/util/third_party/freertos/kernel/portable/MemMang/subdir.mk
-include gecko_sdk_4.4.3/util/third_party/freertos/kernel/portable/GCC/ARM_CM4F/subdir.mk
-include gecko_sdk_4.4.3/util/third_party/freertos/kernel/subdir.mk
-include gecko_sdk_4.4.3/util/third_party/freertos/cmsis/Source/subdir.mk
-include gecko_sdk_4.4.3/platform/service/system/src/subdir.mk
-include gecko_sdk_4.4.3/platform/service/mem_pool/src/subdir.mk
-include gecko_sdk_4.4.3/platform/emlib/src/subdir.mk
-include gecko_sdk_4.4.3/platform/common/src/subdir.mk
-include gecko_sdk_4.4.3/platform/CMSIS/RTOS2/Source/subdir.mk
-include autogen/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := twt_remote_app_w320
BUILD_ARTIFACT_EXTENSION := axf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all:
	+@$(MAKE) --no-print-directory main-build && $(MAKE) --no-print-directory post-build

# Main-build Target
main-build: twt_remote_app_w320.axf

# Tool invocations
twt_remote_app_w320.axf: $(OBJS) $(USER_OBJS) makefile objects.mk $(OPTIONAL_TOOL_DEPS)
	@echo 'Building target: $@'
	@echo 'Invoking: GNU ARM C Linker'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m4 -mthumb -T "C:\Users\ch.wang\SimplicityStudio\v5_workspace\twt_remote_app_w320\autogen\linkerfile_SoC.ld" -u _printf_float -Wl,--no-warn-rwx-segments -Xlinker --gc-sections -Xlinker -Map="twt_remote_app_w320.map" -mfpu=fpv4-sp-d16 -mfloat-abi=softfp --specs=nano.specs -o twt_remote_app_w320.axf -Wl,--start-group "./app.o" "./main.o" "./autogen/sl_event_handler.o" "./gecko_sdk_4.4.3/platform/CMSIS/RTOS2/Source/os_systick.o" "./gecko_sdk_4.4.3/platform/common/src/sl_assert.o" "./gecko_sdk_4.4.3/platform/common/src/sl_slist.o" "./gecko_sdk_4.4.3/platform/common/src/sl_string.o" "./gecko_sdk_4.4.3/platform/common/src/sli_cmsis_os2_ext_task_register.o" "./gecko_sdk_4.4.3/platform/emlib/src/em_core.o" "./gecko_sdk_4.4.3/platform/service/mem_pool/src/sl_mem_pool.o" "./gecko_sdk_4.4.3/platform/service/system/src/sl_system_init.o" "./gecko_sdk_4.4.3/platform/service/system/src/sl_system_kernel.o" "./gecko_sdk_4.4.3/util/third_party/freertos/cmsis/Source/cmsis_os2.o" "./gecko_sdk_4.4.3/util/third_party/freertos/kernel/croutine.o" "./gecko_sdk_4.4.3/util/third_party/freertos/kernel/event_groups.o" "./gecko_sdk_4.4.3/util/third_party/freertos/kernel/list.o" "./gecko_sdk_4.4.3/util/third_party/freertos/kernel/queue.o" "./gecko_sdk_4.4.3/util/third_party/freertos/kernel/stream_buffer.o" "./gecko_sdk_4.4.3/util/third_party/freertos/kernel/tasks.o" "./gecko_sdk_4.4.3/util/third_party/freertos/kernel/timers.o" "./gecko_sdk_4.4.3/util/third_party/freertos/kernel/portable/GCC/ARM_CM4F/port.o" "./gecko_sdk_4.4.3/util/third_party/freertos/kernel/portable/MemMang/heap_4.o" "./wiseconnect3_sdk_3.2.0/components/board/silabs/src/rsi_board.o" "./wiseconnect3_sdk_3.2.0/components/common/src/sl_utility.o" "./wiseconnect3_sdk_3.2.0/components/device/silabs/si91x/mcu/core/chip/src/iPMU_prog/iPMU_dotc/ipmu_apis.o" "./wiseconnect3_sdk_3.2.0/components/device/silabs/si91x/mcu/core/chip/src/iPMU_prog/iPMU_dotc/rsi_system_config_917.o" "./wiseconnect3_sdk_3.2.0/components/device/silabs/si91x/mcu/core/chip/src/rsi_deepsleep_soc.o" "./wiseconnect3_sdk_3.2.0/components/device/silabs/si91x/mcu/core/chip/src/rsi_ps_ram_func.o" "./wiseconnect3_sdk_3.2.0/components/device/silabs/si91x/mcu/core/chip/src/startup_si91x.o" "./wiseconnect3_sdk_3.2.0/components/device/silabs/si91x/mcu/core/chip/src/system_si91x.o" "./wiseconnect3_sdk_3.2.0/components/device/silabs/si91x/mcu/core/common/src/rsi_debug.o" "./wiseconnect3_sdk_3.2.0/components/device/silabs/si91x/mcu/core/common/src/sl_si91x_stack_object_declare.o" "./wiseconnect3_sdk_3.2.0/components/device/silabs/si91x/mcu/core/common/src/syscalls.o" "./wiseconnect3_sdk_3.2.0/components/device/silabs/si91x/mcu/core/config/src/rsi_nvic_priorities_config.o" "./wiseconnect3_sdk_3.2.0/components/device/silabs/si91x/mcu/drivers/cmsis_driver/UDMA.o" "./wiseconnect3_sdk_3.2.0/components/device/silabs/si91x/mcu/drivers/cmsis_driver/USART.o" "./wiseconnect3_sdk_3.2.0/components/device/silabs/si91x/mcu/drivers/peripheral_drivers/src/clock_update.o" "./wiseconnect3_sdk_3.2.0/components/device/silabs/si91x/mcu/drivers/peripheral_drivers/src/rsi_crc.o" "./wiseconnect3_sdk_3.2.0/components/device/silabs/si91x/mcu/drivers/peripheral_drivers/src/rsi_egpio.o" "./wiseconnect3_sdk_3.2.0/components/device/silabs/si91x/mcu/drivers/peripheral_drivers/src/rsi_timers.o" "./wiseconnect3_sdk_3.2.0/components/device/silabs/si91x/mcu/drivers/peripheral_drivers/src/rsi_udma.o" "./wiseconnect3_sdk_3.2.0/components/device/silabs/si91x/mcu/drivers/peripheral_drivers/src/rsi_udma_wrapper.o" "./wiseconnect3_sdk_3.2.0/components/device/silabs/si91x/mcu/drivers/peripheral_drivers/src/rsi_usart.o" "./wiseconnect3_sdk_3.2.0/components/device/silabs/si91x/mcu/drivers/systemlevel/src/rsi_ipmu.o" "./wiseconnect3_sdk_3.2.0/components/device/silabs/si91x/mcu/drivers/systemlevel/src/rsi_pll.o" "./wiseconnect3_sdk_3.2.0/components/device/silabs/si91x/mcu/drivers/systemlevel/src/rsi_power_save.o" "./wiseconnect3_sdk_3.2.0/components/device/silabs/si91x/mcu/drivers/systemlevel/src/rsi_rtc.o" "./wiseconnect3_sdk_3.2.0/components/device/silabs/si91x/mcu/drivers/systemlevel/src/rsi_temp_sensor.o" "./wiseconnect3_sdk_3.2.0/components/device/silabs/si91x/mcu/drivers/systemlevel/src/rsi_time_period.o" "./wiseconnect3_sdk_3.2.0/components/device/silabs/si91x/mcu/drivers/systemlevel/src/rsi_ulpss_clk.o" "./wiseconnect3_sdk_3.2.0/components/device/silabs/si91x/mcu/drivers/systemlevel/src/rsi_wwdt.o" "./wiseconnect3_sdk_3.2.0/components/device/silabs/si91x/wireless/ahb_interface/src/rsi_hal_mcu_m4_ram.o" "./wiseconnect3_sdk_3.2.0/components/device/silabs/si91x/wireless/ahb_interface/src/rsi_hal_mcu_m4_rom.o" "./wiseconnect3_sdk_3.2.0/components/device/silabs/si91x/wireless/ahb_interface/src/sl_platform.o" "./wiseconnect3_sdk_3.2.0/components/device/silabs/si91x/wireless/ahb_interface/src/sl_platform_wireless.o" "./wiseconnect3_sdk_3.2.0/components/device/silabs/si91x/wireless/ahb_interface/src/sl_si91x_bus.o" "./wiseconnect3_sdk_3.2.0/components/device/silabs/si91x/wireless/ahb_interface/src/sl_si91x_timer.o" "./wiseconnect3_sdk_3.2.0/components/device/silabs/si91x/wireless/ahb_interface/src/sli_siwx917_soc.o" "./wiseconnect3_sdk_3.2.0/components/device/silabs/si91x/wireless/asynchronous_socket/src/sl_si91x_socket.o" "./wiseconnect3_sdk_3.2.0/components/device/silabs/si91x/wireless/errno/src/sl_si91x_errno.o" "./wiseconnect3_sdk_3.2.0/components/device/silabs/si91x/wireless/firmware_upgrade/firmware_upgradation.o" "./wiseconnect3_sdk_3.2.0/components/device/silabs/si91x/wireless/host_mcu/si91x/siwx917_soc_ncp_host.o" "./wiseconnect3_sdk_3.2.0/components/device/silabs/si91x/wireless/icmp/sl_net_ping.o" "./wiseconnect3_sdk_3.2.0/components/device/silabs/si91x/wireless/memory/mem_pool_buffer_quota.o" "./wiseconnect3_sdk_3.2.0/components/device/silabs/si91x/wireless/sl_net/src/sl_net_rsi_utility.o" "./wiseconnect3_sdk_3.2.0/components/device/silabs/si91x/wireless/sl_net/src/sl_net_si91x_integration_handler.o" "./wiseconnect3_sdk_3.2.0/components/device/silabs/si91x/wireless/sl_net/src/sl_si91x_net_credentials.o" "./wiseconnect3_sdk_3.2.0/components/device/silabs/si91x/wireless/sl_net/src/sl_si91x_net_internal_stack.o" "./wiseconnect3_sdk_3.2.0/components/device/silabs/si91x/wireless/socket/src/sl_si91x_socket_utility.o" "./wiseconnect3_sdk_3.2.0/components/device/silabs/si91x/wireless/src/sl_rsi_utility.o" "./wiseconnect3_sdk_3.2.0/components/device/silabs/si91x/wireless/src/sl_si91x_callback_framework.o" "./wiseconnect3_sdk_3.2.0/components/device/silabs/si91x/wireless/src/sl_si91x_driver.o" "./wiseconnect3_sdk_3.2.0/components/device/silabs/si91x/wireless/threading/sli_si91x_multithreaded.o" "./wiseconnect3_sdk_3.2.0/components/protocol/wifi/si91x/sl_wifi.o" "./wiseconnect3_sdk_3.2.0/components/protocol/wifi/src/sl_wifi_callback_framework.o" "./wiseconnect3_sdk_3.2.0/components/service/bsd_socket/si91x_socket/sl_si91x_bsd_socket.o" "./wiseconnect3_sdk_3.2.0/components/service/network_manager/si91x/sl_net_si91x.o" "./wiseconnect3_sdk_3.2.0/components/service/network_manager/src/sl_net.o" "./wiseconnect3_sdk_3.2.0/components/service/network_manager/src/sl_net_basic_certificate_store.o" "./wiseconnect3_sdk_3.2.0/components/service/network_manager/src/sl_net_basic_credentials.o" "./wiseconnect3_sdk_3.2.0/components/service/network_manager/src/sl_net_basic_profiles.o" -lgcc -lnosys -lc -lm -Wl,--end-group -Wl,--start-group -lgcc -lc -lnosys -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

	@echo 'Building out file: twt_remote_app_w320.out'
	arm-none-eabi-objcopy "twt_remote_app_w320.axf" "twt_remote_app_w320.out"
	@echo ' '

	@echo 'Building hex file: twt_remote_app_w320.hex'
	arm-none-eabi-objcopy -O ihex "twt_remote_app_w320.axf" "twt_remote_app_w320.hex"
	@echo ' '

	@echo 'Building bin file: twt_remote_app_w320.bin'
	arm-none-eabi-objcopy -O binary "twt_remote_app_w320.axf" "twt_remote_app_w320.bin"
	@echo ' '

	@echo 'Building s37 file: twt_remote_app_w320.s37'
	arm-none-eabi-objcopy -O srec "twt_remote_app_w320.axf" "twt_remote_app_w320.s37"
	@echo ' '

	@echo 'Running size tool'
	arm-none-eabi-size "twt_remote_app_w320.axf" -A
	@echo ' '

# Other Targets
clean:
	-@$(foreach FILE, $(EXECUTABLES), $(shell $(RM) $(FILE)) )
	-@$(foreach FILE, $(OBJS), $(shell $(RM) $(FILE)) )
	-@$(foreach FILE, $(C_DEPS), $(shell $(RM) $(FILE)) )
	-$(RM) twt_remote_app_w320.axf
	-@echo ' '

post-build:
	-"C:\SiliconLabs\SimplicityStudio\v5\developer\adapter_packs\commander\commander.exe" postbuild "C:\Users\ch.wang\SimplicityStudio\v5_workspace\twt_remote_app_w320/twt_remote_app_w320.slpb" --parameter build_dir:"C:\Users\ch.wang\SimplicityStudio\v5_workspace\twt_remote_app_w320\GNU ARM v12.2.1 - Default"
	-@echo ' '

.PHONY: all clean dependents main-build post-build

-include ../makefile.targets
