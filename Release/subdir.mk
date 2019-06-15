################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
..\sloeber.ino.cpp 

LINK_OBJ += \
.\sloeber.ino.cpp.o 

CPP_DEPS += \
.\sloeber.ino.cpp.d 


# Each subdirectory must supply rules for building sources it contributes
sloeber.ino.cpp.o: ..\sloeber.ino.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"D:\sloeber\/arduinoPlugin/packages/ESP32/tools/xtensa-esp32-elf/bin/xtensa-esp32-elf-g++" -DESP_PLATFORM -DMBEDTLS_CONFIG_FILE="mbedtls/esp_config.h" -DHAVE_CONFIG_H "-ID:\sloeber\/arduinoPlugin/packages/ESP32/tools/sdk/include/config" "-ID:\sloeber\/arduinoPlugin/packages/ESP32/tools/sdk/include/app_trace" "-ID:\sloeber\/arduinoPlugin/packages/ESP32/tools/sdk/include/app_update" "-ID:\sloeber\/arduinoPlugin/packages/ESP32/tools/sdk/include/asio" "-ID:\sloeber\/arduinoPlugin/packages/ESP32/tools/sdk/include/bootloader_support" "-ID:\sloeber\/arduinoPlugin/packages/ESP32/tools/sdk/include/bt" "-ID:\sloeber\/arduinoPlugin/packages/ESP32/tools/sdk/include/coap" "-ID:\sloeber\/arduinoPlugin/packages/ESP32/tools/sdk/include/console" "-ID:\sloeber\/arduinoPlugin/packages/ESP32/tools/sdk/include/driver" "-ID:\sloeber\/arduinoPlugin/packages/ESP32/tools/sdk/include/esp-tls" "-ID:\sloeber\/arduinoPlugin/packages/ESP32/tools/sdk/include/esp32" "-ID:\sloeber\/arduinoPlugin/packages/ESP32/tools/sdk/include/esp_adc_cal" "-ID:\sloeber\/arduinoPlugin/packages/ESP32/tools/sdk/include/esp_event" "-ID:\sloeber\/arduinoPlugin/packages/ESP32/tools/sdk/include/esp_http_client" "-ID:\sloeber\/arduinoPlugin/packages/ESP32/tools/sdk/include/esp_http_server" "-ID:\sloeber\/arduinoPlugin/packages/ESP32/tools/sdk/include/esp_https_ota" "-ID:\sloeber\/arduinoPlugin/packages/ESP32/tools/sdk/include/esp_ringbuf" "-ID:\sloeber\/arduinoPlugin/packages/ESP32/tools/sdk/include/ethernet" "-ID:\sloeber\/arduinoPlugin/packages/ESP32/tools/sdk/include/expat" "-ID:\sloeber\/arduinoPlugin/packages/ESP32/tools/sdk/include/fatfs" "-ID:\sloeber\/arduinoPlugin/packages/ESP32/tools/sdk/include/freemodbus" "-ID:\sloeber\/arduinoPlugin/packages/ESP32/tools/sdk/include/freertos" "-ID:\sloeber\/arduinoPlugin/packages/ESP32/tools/sdk/include/heap" "-ID:\sloeber\/arduinoPlugin/packages/ESP32/tools/sdk/include/idf_test" "-ID:\sloeber\/arduinoPlugin/packages/ESP32/tools/sdk/include/jsmn" "-ID:\sloeber\/arduinoPlugin/packages/ESP32/tools/sdk/include/json" "-ID:\sloeber\/arduinoPlugin/packages/ESP32/tools/sdk/include/libsodium" "-ID:\sloeber\/arduinoPlugin/packages/ESP32/tools/sdk/include/log" "-ID:\sloeber\/arduinoPlugin/packages/ESP32/tools/sdk/include/lwip" "-ID:\sloeber\/arduinoPlugin/packages/ESP32/tools/sdk/include/mbedtls" "-ID:\sloeber\/arduinoPlugin/packages/ESP32/tools/sdk/include/mdns" "-ID:\sloeber\/arduinoPlugin/packages/ESP32/tools/sdk/include/micro-ecc" "-ID:\sloeber\/arduinoPlugin/packages/ESP32/tools/sdk/include/mqtt" "-ID:\sloeber\/arduinoPlugin/packages/ESP32/tools/sdk/include/newlib" "-ID:\sloeber\/arduinoPlugin/packages/ESP32/tools/sdk/include/nghttp" "-ID:\sloeber\/arduinoPlugin/packages/ESP32/tools/sdk/include/nvs_flash" "-ID:\sloeber\/arduinoPlugin/packages/ESP32/tools/sdk/include/openssl" "-ID:\sloeber\/arduinoPlugin/packages/ESP32/tools/sdk/include/protobuf-c" "-ID:\sloeber\/arduinoPlugin/packages/ESP32/tools/sdk/include/protocomm" "-ID:\sloeber\/arduinoPlugin/packages/ESP32/tools/sdk/include/pthread" "-ID:\sloeber\/arduinoPlugin/packages/ESP32/tools/sdk/include/sdmmc" "-ID:\sloeber\/arduinoPlugin/packages/ESP32/tools/sdk/include/smartconfig_ack" "-ID:\sloeber\/arduinoPlugin/packages/ESP32/tools/sdk/include/soc" "-ID:\sloeber\/arduinoPlugin/packages/ESP32/tools/sdk/include/spi_flash" "-ID:\sloeber\/arduinoPlugin/packages/ESP32/tools/sdk/include/spiffs" "-ID:\sloeber\/arduinoPlugin/packages/ESP32/tools/sdk/include/tcp_transport" "-ID:\sloeber\/arduinoPlugin/packages/ESP32/tools/sdk/include/tcpip_adapter" "-ID:\sloeber\/arduinoPlugin/packages/ESP32/tools/sdk/include/ulp" "-ID:\sloeber\/arduinoPlugin/packages/ESP32/tools/sdk/include/vfs" "-ID:\sloeber\/arduinoPlugin/packages/ESP32/tools/sdk/include/wear_levelling" "-ID:\sloeber\/arduinoPlugin/packages/ESP32/tools/sdk/include/wifi_provisioning" "-ID:\sloeber\/arduinoPlugin/packages/ESP32/tools/sdk/include/wpa_supplicant" "-ID:\sloeber\/arduinoPlugin/packages/ESP32/tools/sdk/include/xtensa-debug-module" "-ID:\sloeber\/arduinoPlugin/packages/ESP32/tools/sdk/include/esp32-camera" "-ID:\sloeber\/arduinoPlugin/packages/ESP32/tools/sdk/include/esp-face" "-ID:\sloeber\/arduinoPlugin/packages/ESP32/tools/sdk/include/fb_gfx" -std=gnu++11 -fno-exceptions -Os -g3 -Wpointer-arith -fexceptions -fstack-protector -ffunction-sections -fdata-sections -fstrict-volatile-bitfields -mlongcalls -nostdlib -Wall -Werror=all -Wextra -Wno-error=unused-function -Wno-error=unused-but-set-variable -Wno-error=unused-variable -Wno-error=deprecated-declarations -Wno-unused-parameter -Wno-sign-compare -fno-rtti -MMD -c -DF_CPU=240000000L -DARDUINO=10802 -DARDUINO_ESP32_DEV -DARDUINO_ARCH_ESP32 -DARDUINO_BOARD="ESP32_DEV" -DARDUINO_VARIANT="doitESP32devkitV1"  -DESP32 -DCORE_DEBUG_LEVEL=0    -I"D:\sloeber\arduinoPlugin\packages\ESP32\cores\esp32" -I"D:\sloeber\arduinoPlugin\packages\ESP32\variants\doitESP32devkitV1" -I"D:\sloeber\arduinoPlugin\packages\ESP32\libraries\ESPmDNS\src" -I"D:\sloeber\arduinoPlugin\packages\ESP32\libraries\WebServer\src" -I"D:\sloeber\arduinoPlugin\packages\ESP32\libraries\WiFi\src" -I"D:\sloeber\arduinoPlugin\packages\ESP32\libraries\FS\src" -I"D:\sloeber\arduinoPlugin\packages\ESP32\libraries\EEPROM\src" -I"D:\sloeber\arduinoPlugin\libraries\ArduinoJson\6.11.0\src" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"

	@echo 'Finished building: $<'
	@echo ' '


