/*

  ESP32-CAM-Video-Recorder-junior

  This program records an mjpeg avi video to the sd card of an ESP32-CAM.


  It is the junior version of   https://github.com/jameszah/ESP32-CAM-Video-Recorder
  which has 100 other features of wifi, streaming video, http control, telegram updates, pir control,
  touch control, ftp downloads, .... and other things that make it very big and complex.

  Just set a few parameters, compile and download, and it will record on power-on, until sd is full, or power-off.
  Then pull out the sd and move it to your computer, and you will see all but the last file avi which died during the unplug.

  The files will have the name such as:

    desklens10.003.avi

    "desklens" is your devname
    10 - is a number stored in eprom that will increase everytime your device boots
    3 - is the 3rd file created during the current boot

  Small red led on the back blinks with every frame.


  by James Zahary Sep 12, 2020
     jamzah.plc@gmail.com

   - v50 apr 13, 2021 - tidy
   - v50lpmod apr 28, 2021 - shut off low power modem
   - v53 jul 8, 2021 - get rid on no wifi message cloggoing up log file
   - v56 dec 23, 2021 - tzchar to 60 bytes
                      - add esp32 sd filemanager to download files
   - v57 dec 28, 2021 - final changes to https://github.com/jameszah/ESPxWebFlMgr/tree/master/esp32_sd_file_manager
   - v58 dec 30, 2021 - changes for Arduino 1.8.19 and esp32 Board Library 2.0.2
         jan 12, 2022 - add dates to file manager
                      - add simple version of config.txt configuration
   - 58.9 apr 29,2022 - re-connect wifi after failure
                      - correct mdns for wifiman configuration
                      - CAMERA_GRAB_LATEST
                      - enable streaming faster than recording
    -v59.0 may 8,2022 - host mode as an option for wifi
    -v59.3 may 17,2022 - time to camera in ap moce
    -v59.4 may 18,2022 - miltiple photo function, defualt to ap after ssid fails
    -v59.5 may 19, 2022 - improve streaming speed
                        - drop CAMERA_GRAB_LATEST for speed
    -v60.4 jun 15,2022 - two channels of streaming on port 821 and 82 to kept webpage working on port 80
                       - file manager still on 8080
                       - tidy up web page
                       - assume a better frame rate if reboot during recording and no index is written
                       - start wifi after the recording starts to sped things up
     60.4.5  - semaphore and framebuffer2/3 when using capture sytle video streaming
             - wifi dns reset
          .6  - repeat dns every 5 minutes
          .7  - every 15 
          
  https://github.com/jameszah/ESP32-CAM-Video-Recorder-junior

    jameszah/ESP32-CAM-Video-Recorder-junior is licensed under the
    GNU General Public License v3.0

  The is Arduino code, with standard setup for ESP32-CAM
    - Board ESP32 Wrover Module
    - Partition Scheme Huge APP (3MB No OTA)
    - or with AI Thinker ESP32-CAM

  Needs these libraries or better:


  Compiled with Arduino 1.8.19, and esp32-arduino core version 2.0.4, on Sep 13, 2022

Linking everything together...
"C:\\ArduinoPortable\\arduino-1.8.19\\portable\\packages\\esp32\\tools\\xtensa-esp32-elf-gcc\\gcc8_4_0-esp-2021r2-patch3/bin/xtensa-esp32-elf-g++" "-Wl,--Map=C:\\Users\\James\\AppData\\Local\\Temp\\arduino_build_639913/ESP32-CAM-Video-Recorder-junior-60x.4.7.ino.map" "-LC:\\ArduinoPortable\\arduino-1.8.19\\portable\\packages\\esp32\\hardware\\esp32\\2.0.4/tools/sdk/esp32/lib" "-LC:\\ArduinoPortable\\arduino-1.8.19\\portable\\packages\\esp32\\hardware\\esp32\\2.0.4/tools/sdk/esp32/ld" "-LC:\\ArduinoPortable\\arduino-1.8.19\\portable\\packages\\esp32\\hardware\\esp32\\2.0.4/tools/sdk/esp32/qio_qspi" -T esp32.rom.redefined.ld -T memory.ld -T sections.ld -T esp32.rom.ld -T esp32.rom.api.ld -T esp32.rom.libgcc.ld -T esp32.rom.newlib-data.ld -T esp32.rom.syscalls.ld -T esp32.peripherals.ld -mlongcalls -Wno-frame-address -Wl,--cref -Wl,--gc-sections -fno-rtti -fno-lto -u ld_include_hli_vectors_bt -u _Z5setupv -u _Z4loopv -u esp_app_desc -u pthread_include_pthread_impl -u pthread_include_pthread_cond_impl -u pthread_include_pthread_local_storage_impl -u pthread_include_pthread_rwlock_impl -u include_esp_phy_override -u ld_include_highint_hdl -u start_app -u start_app_other_cores -u __ubsan_include -Wl,--wrap=longjmp -u __assert_func -u vfs_include_syscalls_impl -Wl,--undefined=uxTopUsedPriority -u app_main -u newlib_include_heap_impl -u newlib_include_syscalls_impl -u newlib_include_pthread_impl -u newlib_include_assert_impl -u __cxa_guard_dummy -DESP32 -DCORE_DEBUG_LEVEL=0 -DBOARD_HAS_PSRAM -mfix-esp32-psram-cache-issue -mfix-esp32-psram-cache-strategy=memw -DARDUINO_USB_CDC_ON_BOOT=0 -Wl,--start-group "C:\\Users\\James\\AppData\\Local\\Temp\\arduino_build_639913\\sketch\\CRC32.cpp.o" "C:\\Users\\James\\AppData\\Local\\Temp\\arduino_build_639913\\sketch\\ESP32-CAM-Video-Recorder-junior-60x.4.7.ino.cpp.o" "C:\\Users\\James\\AppData\\Local\\Temp\\arduino_build_639913\\sketch\\ESPxWebFlMgr.cpp.o" "C:\\Users\\James\\AppData\\Local\\Temp\\arduino_build_639913\\libraries\\FS\\FS.cpp.o" "C:\\Users\\James\\AppData\\Local\\Temp\\arduino_build_639913\\libraries\\FS\\vfs_api.cpp.o" "C:\\Users\\James\\AppData\\Local\\Temp\\arduino_build_639913\\libraries\\SD\\SD.cpp.o" "C:\\Users\\James\\AppData\\Local\\Temp\\arduino_build_639913\\libraries\\EEPROM\\EEPROM.cpp.o" "C:\\Users\\James\\AppData\\Local\\Temp\\arduino_build_639913\\libraries\\WiFi\\WiFi.cpp.o" "C:\\Users\\James\\AppData\\Local\\Temp\\arduino_build_639913\\libraries\\WiFi\\WiFiAP.cpp.o" "C:\\Users\\James\\AppData\\Local\\Temp\\arduino_build_639913\\libraries\\WiFi\\WiFiClient.cpp.o" "C:\\Users\\James\\AppData\\Local\\Temp\\arduino_build_639913\\libraries\\WiFi\\WiFiGeneric.cpp.o" "C:\\Users\\James\\AppData\\Local\\Temp\\arduino_build_639913\\libraries\\WiFi\\WiFiMulti.cpp.o" "C:\\Users\\James\\AppData\\Local\\Temp\\arduino_build_639913\\libraries\\WiFi\\WiFiSTA.cpp.o" "C:\\Users\\James\\AppData\\Local\\Temp\\arduino_build_639913\\libraries\\WiFi\\WiFiScan.cpp.o" "C:\\Users\\James\\AppData\\Local\\Temp\\arduino_build_639913\\libraries\\WiFi\\WiFiServer.cpp.o" "C:\\Users\\James\\AppData\\Local\\Temp\\arduino_build_639913\\libraries\\WiFi\\WiFiUdp.cpp.o" "C:\\Users\\James\\AppData\\Local\\Temp\\arduino_build_639913\\libraries\\ESPmDNS\\ESPmDNS.cpp.o" "C:\\Users\\James\\AppData\\Local\\Temp\\arduino_build_639913\\libraries\\WebServer\\Parsing.cpp.o" "C:\\Users\\James\\AppData\\Local\\Temp\\arduino_build_639913\\libraries\\WebServer\\WebServer.cpp.o" "C:\\Users\\James\\AppData\\Local\\Temp\\arduino_build_639913\\libraries\\WebServer\\detail\\mimetable.cpp.o" "C:\\Users\\James\\AppData\\Local\\Temp\\arduino_build_639913\\libraries\\HTTPClient\\HTTPClient.cpp.o" "C:\\Users\\James\\AppData\\Local\\Temp\\arduino_build_639913\\libraries\\WiFiClientSecure\\esp_crt_bundle.c.o" "C:\\Users\\James\\AppData\\Local\\Temp\\arduino_build_639913\\libraries\\WiFiClientSecure\\WiFiClientSecure.cpp.o" "C:\\Users\\James\\AppData\\Local\\Temp\\arduino_build_639913\\libraries\\WiFiClientSecure\\ssl_client.cpp.o" "C:\\Users\\James\\AppData\\Local\\Temp\\arduino_build_639913\\core\\core.a" -lesp_ringbuf -lefuse -lesp_ipc -ldriver -lesp_pm -lmbedtls -lapp_update -lbootloader_support -lspi_flash -lnvs_flash -lpthread -lesp_gdbstub -lespcoredump -lesp_phy -lesp_system -lesp_rom -lhal -lvfs -lesp_eth -ltcpip_adapter -lesp_netif -lesp_event -lwpa_supplicant -lesp_wifi -lconsole -llwip -llog -lheap -lsoc -lesp_hw_support -lxtensa -lesp_common -lesp_timer -lfreertos -lnewlib -lcxx -lapp_trace -lasio -lbt -lcbor -lunity -lcmock -lcoap -lnghttp -lesp-tls -lesp_adc_cal -lesp_hid -ltcp_transport -lesp_http_client -lesp_http_server -lesp_https_ota -lesp_https_server -lesp_lcd -lprotobuf-c -lprotocomm -lmdns -lesp_local_ctrl -lsdmmc -lesp_serial_slave_link -lesp_websocket_client -lexpat -lwear_levelling -lfatfs -lfreemodbus -ljsmn -ljson -llibsodium -lmqtt -lopenssl -lperfmon -lspiffs -lulp -lwifi_provisioning -lbutton -lrmaker_common -ljson_parser -ljson_generator -lesp_schedule -lesp_rainmaker -lqrcode -lws2812_led -lesp-dsp -lesp-sr -lesp32-camera -lesp_littlefs -lfb_gfx -lasio -lcbor -lcmock -lunity -lcoap -lesp_lcd -lesp_websocket_client -lexpat -lfreemodbus -ljsmn -llibsodium -lperfmon -lesp_adc_cal -lesp_hid -lfatfs -lwear_levelling -lopenssl -lesp_rainmaker -lesp_local_ctrl -lesp_https_server -lwifi_provisioning -lprotocomm -lbt -lbtdm_app -lprotobuf-c -lmdns -lrmaker_common -lmqtt -ljson_parser -ljson_generator -lesp_schedule -lqrcode -lcat_face_detect -lhuman_face_detect -lcolor_detect -lmfn -ldl -lwakenet -lmultinet -lesp_audio_processor -lesp_audio_front_end -lesp-sr -lwakenet -lmultinet -lesp_audio_processor -lesp_audio_front_end -ljson -lspiffs -ldl_lib -lc_speech_features -lhilexin_wn5 -lhilexin_wn5X2 -lhilexin_wn5X3 -lnihaoxiaozhi_wn5 -lnihaoxiaozhi_wn5X2 -lnihaoxiaozhi_wn5X3 -lnihaoxiaoxin_wn5X3 -lcustomized_word_wn5 -lmultinet2_ch -lesp_tts_chinese -lvoice_set_xiaole -lesp_ringbuf -lefuse -lesp_ipc -ldriver -lesp_pm -lmbedtls -lapp_update -lbootloader_support -lspi_flash -lnvs_flash -lpthread -lesp_gdbstub -lespcoredump -lesp_phy -lesp_system -lesp_rom -lhal -lvfs -lesp_eth -ltcpip_adapter -lesp_netif -lesp_event -lwpa_supplicant -lesp_wifi -lconsole -llwip -llog -lheap -lsoc -lesp_hw_support -lxtensa -lesp_common -lesp_timer -lfreertos -lnewlib -lcxx -lapp_trace -lnghttp -lesp-tls -ltcp_transport -lesp_http_client -lesp_http_server -lesp_https_ota -lsdmmc -lesp_serial_slave_link -lulp -lmbedtls_2 -lmbedcrypto -lmbedx509 -lcoexist -lcore -lespnow -lmesh -lnet80211 -lpp -lsmartconfig -lwapi -lesp_ringbuf -lefuse -lesp_ipc -ldriver -lesp_pm -lmbedtls -lapp_update -lbootloader_support -lspi_flash -lnvs_flash -lpthread -lesp_gdbstub -lespcoredump -lesp_phy -lesp_system -lesp_rom -lhal -lvfs -lesp_eth -ltcpip_adapter -lesp_netif -lesp_event -lwpa_supplicant -lesp_wifi -lconsole -llwip -llog -lheap -lsoc -lesp_hw_support -lxtensa -lesp_common -lesp_timer -lfreertos -lnewlib -lcxx -lapp_trace -lnghttp -lesp-tls -ltcp_transport -lesp_http_client -lesp_http_server -lesp_https_ota -lsdmmc -lesp_serial_slave_link -lulp -lmbedtls_2 -lmbedcrypto -lmbedx509 -lcoexist -lcore -lespnow -lmesh -lnet80211 -lpp -lsmartconfig -lwapi -lesp_ringbuf -lefuse -lesp_ipc -ldriver -lesp_pm -lmbedtls -lapp_update -lbootloader_support -lspi_flash -lnvs_flash -lpthread -lesp_gdbstub -lespcoredump -lesp_phy -lesp_system -lesp_rom -lhal -lvfs -lesp_eth -ltcpip_adapter -lesp_netif -lesp_event -lwpa_supplicant -lesp_wifi -lconsole -llwip -llog -lheap -lsoc -lesp_hw_support -lxtensa -lesp_common -lesp_timer -lfreertos -lnewlib -lcxx -lapp_trace -lnghttp -lesp-tls -ltcp_transport -lesp_http_client -lesp_http_server -lesp_https_ota -lsdmmc -lesp_serial_slave_link -lulp -lmbedtls_2 -lmbedcrypto -lmbedx509 -lcoexist -lcore -lespnow -lmesh -lnet80211 -lpp -lsmartconfig -lwapi -lesp_ringbuf -lefuse -lesp_ipc -ldriver -lesp_pm -lmbedtls -lapp_update -lbootloader_support -lspi_flash -lnvs_flash -lpthread -lesp_gdbstub -lespcoredump -lesp_phy -lesp_system -lesp_rom -lhal -lvfs -lesp_eth -ltcpip_adapter -lesp_netif -lesp_event -lwpa_supplicant -lesp_wifi -lconsole -llwip -llog -lheap -lsoc -lesp_hw_support -lxtensa -lesp_common -lesp_timer -lfreertos -lnewlib -lcxx -lapp_trace -lnghttp -lesp-tls -ltcp_transport -lesp_http_client -lesp_http_server -lesp_https_ota -lsdmmc -lesp_serial_slave_link -lulp -lmbedtls_2 -lmbedcrypto -lmbedx509 -lcoexist -lcore -lespnow -lmesh -lnet80211 -lpp -lsmartconfig -lwapi -lesp_ringbuf -lefuse -lesp_ipc -ldriver -lesp_pm -lmbedtls -lapp_update -lbootloader_support -lspi_flash -lnvs_flash -lpthread -lesp_gdbstub -lespcoredump -lesp_phy -lesp_system -lesp_rom -lhal -lvfs -lesp_eth -ltcpip_adapter -lesp_netif -lesp_event -lwpa_supplicant -lesp_wifi -lconsole -llwip -llog -lheap -lsoc -lesp_hw_support -lxtensa -lesp_common -lesp_timer -lfreertos -lnewlib -lcxx -lapp_trace -lnghttp -lesp-tls -ltcp_transport -lesp_http_client -lesp_http_server -lesp_https_ota -lsdmmc -lesp_serial_slave_link -lulp -lmbedtls_2 -lmbedcrypto -lmbedx509 -lcoexist -lcore -lespnow -lmesh -lnet80211 -lpp -lsmartconfig -lwapi -lphy -lrtc -lesp_phy -lphy -lrtc -lesp_phy -lphy -lrtc -lxt_hal -lm -lnewlib -lstdc++ -lpthread -lgcc -lcxx -lapp_trace -lgcov -lapp_trace -lgcov -lc -Wl,--end-group -Wl,-EL -o "C:\\Users\\James\\AppData\\Local\\Temp\\arduino_build_639913/ESP32-CAM-Video-Recorder-junior-60x.4.7.ino.elf"
"C:\\ArduinoPortable\\arduino-1.8.19\\portable\\packages\\esp32\\tools\\esptool_py\\3.3.0/esptool.exe" --chip esp32 elf2image --flash_mode dio --flash_freq 80m --flash_size 4MB -o "C:\\Users\\James\\AppData\\Local\\Temp\\arduino_build_639913/ESP32-CAM-Video-Recorder-junior-60x.4.7.ino.bin" "C:\\Users\\James\\AppData\\Local\\Temp\\arduino_build_639913/ESP32-CAM-Video-Recorder-junior-60x.4.7.ino.elf"
esptool.py v3.3
Creating esp32 image...
Merged 25 ELF sections
Successfully created esp32 image.
"C:\\ArduinoPortable\\arduino-1.8.19\\portable\\packages\\esp32\\hardware\\esp32\\2.0.4/tools/gen_esp32part.exe" -q "C:\\Users\\James\\AppData\\Local\\Temp\\arduino_build_639913/partitions.csv" "C:\\Users\\James\\AppData\\Local\\Temp\\arduino_build_639913/ESP32-CAM-Video-Recorder-junior-60x.4.7.ino.partitions.bin"
Multiple libraries were found for "WiFi.h"
 Used: C:\ArduinoPortable\arduino-1.8.19\portable\packages\esp32\hardware\esp32\2.0.4\libraries\WiFi
 Not used: C:\ArduinoPortable\arduino-1.8.19\libraries\WiFi
Using library FS at version 2.0.0 in folder: C:\ArduinoPortable\arduino-1.8.19\portable\packages\esp32\hardware\esp32\2.0.4\libraries\FS 
Using librarySD at version 2.0.0 in folder: C:\ArduinoPortable\arduino-1.8.19\portable\packages\esp32\hardware\esp32\2.0.4\libraries\SD 
Using library EEPROM at version 2.0.0 in folder: C:\ArduinoPortable\arduino-1.8.19\portable\packages\esp32\hardware\esp32\2.0.4\libraries\EEPROM 
Using library WiFi at version 2.0.0 in folder: C:\ArduinoPortable\arduino-1.8.19\portable\packages\esp32\hardware\esp32\2.0.4\libraries\WiFi 
Using library ESPmDNS at version 2.0.0 in folder: C:\ArduinoPortable\arduino-1.8.19\portable\packages\esp32\hardware\esp32\2.0.4\libraries\ESPmDNS 
Using library WebServer at version 2.0.0 in folder: C:\ArduinoPortable\arduino-1.8.19\portable\packages\esp32\hardware\esp32\2.0.4\libraries\WebServer 
Using library HTTPClient at version 2.0.0 in folder: C:\ArduinoPortable\arduino-1.8.19\portable\packages\esp32\hardware\esp32\2.0.4\libraries\HTTPClient 
Using library WiFiClientSecure at version 2.0.0 in folder: C:\ArduinoPortable\arduino-1.8.19\portable\packages\esp32\hardware\esp32\2.0.4\libraries\WiFiClientSecure 
"C:\\ArduinoPortable\\arduino-1.8.19\\portable\\packages\\esp32\\tools\\xtensa-esp32-elf-gcc\\gcc8_4_0-esp-2021r2-patch3/bin/xtensa-esp32-elf-size" -A "C:\\Users\\James\\AppData\\Local\\Temp\\arduino_build_639913/ESP32-CAM-Video-Recorder-junior-60x.4.7.ino.elf"
Sketch uses 1033573 bytes (32%) of program storage space. Maximum is 3145728 bytes.
Global variables use 59164 bytes (18%) of dynamic memory, leaving 268516 bytes for local variables. Maximum is 327680 bytes.



*/

//#define LOG_LOCAL_LEVEL ESP_LOG_VERBOSE
#include "esp_log.h"
#include "esp_http_server.h"
#include "esp_camera.h"
#include "sensor.h"
#include "WiFi.h"
#include "esp_wifi.h"
#include <errno.h>
#include <string.h>
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// user edits here:

static const char vernum[] = "v60.4.7";
char devname[30];
String devstr =  "desklens";

enum RecorderWifiMode : uint8_t {
  RECORDER_WIFI_OFF = 0,
  RECORDER_WIFI_STA = 1,
  RECORDER_WIFI_AP = 2
};

int wifi_mode = RECORDER_WIFI_OFF;
int wifi_ip_mode = 0;         // STA only: 0 = DHCP/mDNS, 1 = static IPv4

// https://sites.google.com/a/usapiens.com/opnode/time-zones  -- find your timezone here
String TIMEZONE = "GMT0BST,M3.5.0/01,M10.5.0/02";
//String TIMEZONE = "MST7MDT,M3.2.0/2:00:00,M11.1.0/2:00:00";
#define Lots_of_Stats 1
#define blinking 0

const int DEFAULT_FRAME_SIZE_INDEX = 11;        // Stable config index: HD 1280x720
const int DEFAULT_FRAME_BUFFER_SIZE_INDEX = 13; // Stable config index: UXGA 1600x1200
const int MIN_FRAME_SIZE_INDEX = 0;
const int MAX_FRAME_SIZE_INDEX = 21;

int framesize = DEFAULT_FRAME_SIZE_INDEX;
int quality = 12;
int framesizeconfig = DEFAULT_FRAME_BUFFER_SIZE_INDEX;
int qualityconfig = 5;
int buffersconfig = 3;
int avi_length = 1800;            // how long a movie in seconds -- 1800 sec = 30 min
int frame_interval = 0;          // record at full speed
int speed_up_factor = 1;          // play at realtime
int stream_delay = 500;           // minimum of 500 ms delay between frames
int MagicNumber = 12;                // change this number to reset the eprom in your esp32 for file numbers
int max_recordings = 0;           // 0 records continuously until stopped
uint32_t completed_recordings = 0;
const uint32_t AVI_FLUSH_INTERVAL_MS = 1000;
const uint32_t SD_TASK_STACK_SIZE = 8192;
const uint32_t SD_STACK_LOG_INTERVAL_WRITES = 100;
uint32_t last_avi_flush_time = 0;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
bool configfile = false;
bool InternetOff = true;
bool reboot_now = false;
bool restart_now = false;
bool wifi_suppressed_after_brownout = false;
volatile bool safe_stop_requested = false;
volatile bool recording_closed_for_shutdown = false;
volatile bool safe_stop_complete = false;
String cssid;
String cpass;
String czone;
String cstaticip;
String cgateway;
String csubnet;
String configured_dns;

TaskHandle_t the_camera_loop_task;
TaskHandle_t the_sd_loop_task;
volatile uint32_t sd_task_min_free_stack_bytes = SD_TASK_STACK_SIZE;

static SemaphoreHandle_t wait_for_sd;
static SemaphoreHandle_t sd_go;
SemaphoreHandle_t baton;

long current_frame_time;
long last_frame_time;


// https://github.com/espressif/esp32-camera/issues/182
#define fbs 8 // was 64 -- how many kb of static ram for psram -> sram buffer for sd write
uint8_t framebuffer_static[fbs * 1024 + 20];

// ===== カメラピン設定（XIAO ESP32S3 Sense用）=====変更
#define PWDN_GPIO_NUM    -1
#define RESET_GPIO_NUM   -1
#define XCLK_GPIO_NUM    10
#define SIOD_GPIO_NUM    40
#define SIOC_GPIO_NUM    39

#define Y9_GPIO_NUM      48
#define Y8_GPIO_NUM      11
#define Y7_GPIO_NUM      12
#define Y6_GPIO_NUM      14
#define Y5_GPIO_NUM      16
#define Y4_GPIO_NUM      18
#define Y3_GPIO_NUM      17
#define Y2_GPIO_NUM      15
#define VSYNC_GPIO_NUM   38
#define HREF_GPIO_NUM    47
#define PCLK_GPIO_NUM    13

camera_fb_t * fb_curr = NULL;
camera_fb_t * fb_next = NULL;

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "nvs_flash.h"
#include "nvs.h"

static esp_err_t cam_err;
float most_recent_fps = 0;
int most_recent_avg_framesize = 0;

uint8_t* framebuffer;
uint8_t* framebuffer2;
uint8_t* framebuffer3;

const size_t WEB_FRAMEBUFFER_CAPACITY = 512 * 1024;

int framebuffer_len;
int framebuffer3_len;
long framebuffer_time = 0;
long framebuffer3_time = 0;

int first = 1;
long frame_start = 0;
long frame_end = 0;
long frame_total = 0;
long frame_average = 0;
long loop_average = 0;
long loop_total = 0;
long total_frame_data = 0;
long last_frame_length = 0;
int done = 0;
long avi_start_time = 0;
long avi_end_time = 0;
int start_record = 0;
int start_record_2nd_opinion = -2;
int start_record_1st_opinion = -1;

int we_are_already_stopped = 0;
long total_delay = 0;
long bytes_before_last_100_frames = 0;
long time_before_last_100_frames = 0;

long time_in_loop = 0;
long time_in_camera = 0;
long time_in_sd = 0;
long time_in_good = 0;
long time_total = 0;
long time_in_web1 = 0;
long time_in_web2 = 0;
long delay_wait_for_sd = 0;
long wait_for_cam = 0;

int do_it_now = 0;
int gframe_cnt;
int gfblen;
int gj;
int  gmdelay;
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  Avi Writer Stuff here

void camera_setting(sensor_t *sensor); //変更
int64_t avi_start_time_exact; //変更
// MicroSD
#include "driver/sdmmc_host.h"
#include "driver/sdmmc_defs.h"
#include "sdmmc_cmd.h"
#include "esp_vfs_fat.h"
#include "FS.h"
#include "SD.h" //変更
#include "SPI.h" //変更

File logfile;
File avifile;
File idxfile;
File timestampFile;
File illuminanceFile;

char avi_file_name[100];

static int i = 0;
uint32_t frame_cnt = 0;
uint16_t remnant = 0;
uint32_t length = 0;
uint32_t startms;
uint32_t elapsedms;
uint32_t uVideoLen = 0;

int bad_jpg = 0;
int extend_jpg = 0;
int normal_jpg = 0;

int file_number = 0;
int file_group = 0;
long boot_time = 0;

long totalp;
long totalw;

#define BUFFSIZE 512

uint8_t buf[BUFFSIZE];

#define AVIOFFSET 240 // AVI main header length

unsigned long movi_size = 0;
unsigned long jpeg_size = 0;
unsigned long idx_offset = 0;

uint8_t zero_buf[4] = {0x00, 0x00, 0x00, 0x00};
uint8_t dc_buf[4] = {0x30, 0x30, 0x64, 0x63};    // "00dc"
uint8_t dc_and_zero_buf[8] = {0x30, 0x30, 0x64, 0x63, 0x00, 0x00, 0x00, 0x00};

uint8_t avi1_buf[4] = {0x41, 0x56, 0x49, 0x31};    // "AVI1"
uint8_t idx1_buf[4] = {0x69, 0x64, 0x78, 0x31};    // "idx1"


// config.txt uses the recorder's original, stable 0-21 frame-size indexes.
// Do not cast those indexes directly to framesize_t: esp32-camera has added enum
// members over time, which changes the numeric values of later FRAMESIZE_* items.
static bool is_valid_frame_size_index(int index) {
  return index >= MIN_FRAME_SIZE_INDEX && index <= MAX_FRAME_SIZE_INDEX;
}

static framesize_t driver_frame_size_from_index(int index) {
  switch (index) {
    case 0:  return FRAMESIZE_96X96;
    case 1:  return FRAMESIZE_QQVGA;
    case 2:  return FRAMESIZE_QCIF;
    case 3:  return FRAMESIZE_HQVGA;
    case 4:  return FRAMESIZE_240X240;
    case 5:  return FRAMESIZE_QVGA;
    case 6:  return FRAMESIZE_CIF;
    case 7:  return FRAMESIZE_HVGA;
    case 8:  return FRAMESIZE_VGA;
    case 9:  return FRAMESIZE_SVGA;
    case 10: return FRAMESIZE_XGA;
    case 11: return FRAMESIZE_HD;
    case 12: return FRAMESIZE_SXGA;
    case 13: return FRAMESIZE_UXGA;
    case 14: return FRAMESIZE_FHD;
    case 15: return FRAMESIZE_P_HD;
    case 16: return FRAMESIZE_P_3MP;
    case 17: return FRAMESIZE_QXGA;
    case 18: return FRAMESIZE_QHD;
    case 19: return FRAMESIZE_WQXGA;
    case 20: return FRAMESIZE_P_FHD;
    case 21: return FRAMESIZE_QSXGA;
    default: return FRAMESIZE_HD;
  }
}

const int avi_header[AVIOFFSET] PROGMEM = {
  0x52, 0x49, 0x46, 0x46, 0xD8, 0x01, 0x0E, 0x00, 0x41, 0x56, 0x49, 0x20, 0x4C, 0x49, 0x53, 0x54,
  0xD0, 0x00, 0x00, 0x00, 0x68, 0x64, 0x72, 0x6C, 0x61, 0x76, 0x69, 0x68, 0x38, 0x00, 0x00, 0x00,
  0xA0, 0x86, 0x01, 0x00, 0x80, 0x66, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00,
  0x64, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x80, 0x02, 0x00, 0x00, 0xe0, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x4C, 0x49, 0x53, 0x54, 0x84, 0x00, 0x00, 0x00,
  0x73, 0x74, 0x72, 0x6C, 0x73, 0x74, 0x72, 0x68, 0x30, 0x00, 0x00, 0x00, 0x76, 0x69, 0x64, 0x73,
  0x4D, 0x4A, 0x50, 0x47, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x73, 0x74, 0x72, 0x66,
  0x28, 0x00, 0x00, 0x00, 0x28, 0x00, 0x00, 0x00, 0x80, 0x02, 0x00, 0x00, 0xe0, 0x01, 0x00, 0x00,
  0x01, 0x00, 0x18, 0x00, 0x4D, 0x4A, 0x50, 0x47, 0x00, 0x84, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x49, 0x4E, 0x46, 0x4F,
  0x10, 0x00, 0x00, 0x00, 0x6A, 0x61, 0x6D, 0x65, 0x73, 0x7A, 0x61, 0x68, 0x61, 0x72, 0x79, 0x20,
  0x76, 0x36, 0x30, 0x20, 0x4C, 0x49, 0x53, 0x54, 0x00, 0x01, 0x0E, 0x00, 0x6D, 0x6F, 0x76, 0x69,
};


//
// Writes an uint32_t in Big Endian at current file position
//
static void inline print_quartet(unsigned long i, File fd) {

  uint8_t y[4];
  y[0] = i % 0x100;
  y[1] = (i >> 8) % 0x100;
  y[2] = (i >> 16) % 0x100;
  y[3] = (i >> 24) % 0x100;
  size_t i1_err = fd.write(y , 4);
}

static void inline write_quartet_to_buffer(uint8_t *destination, uint32_t value) {
  destination[0] = value & 0xFF;
  destination[1] = (value >> 8) & 0xFF;
  destination[2] = (value >> 16) & 0xFF;
  destination[3] = (value >> 24) & 0xFF;
}

//
// Writes 2 uint32_t in Big Endian at current file position
//
static void inline print_2quartet(unsigned long i, unsigned long j, File fd) {

  uint8_t y[8];
  y[0] = i % 0x100;
  y[1] = (i >> 8) % 0x100;
  y[2] = (i >> 16) % 0x100;
  y[3] = (i >> 24) % 0x100;
  y[4] = j % 0x100;
  y[5] = (j >> 8) % 0x100;
  y[6] = (j >> 16) % 0x100;
  y[7] = (j >> 24) % 0x100;
  size_t i1_err = fd.write(y , 8);
}

//
// if we have no camera, or sd card, then flash rear led on and off to warn the human SOS - SOS
//
void major_fail() {

  Serial.println(" ");
  logfile.close();

  for  (int i = 0;  i < 10; i++) {                 // 10 loops or about 100 seconds then reboot
    for (int j = 0; j < 3; j++) {
      digitalWrite(33, LOW);   delay(150);
      digitalWrite(33, HIGH);  delay(150);
    }
    delay(1000);

    for (int j = 0; j < 3; j++) {
      digitalWrite(33, LOW);  delay(500);
      digitalWrite(33, HIGH); delay(500);
    }
    delay(1000);
    Serial.print("Major Fail  "); Serial.print(i); Serial.print(" / "); Serial.println(10);
  }

  ESP.restart();
}



//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//

static void config_camera() {

  camera_config_t config;

  //Serial.println("config camera");

  config.ledc_channel = LEDC_CHANNEL_0;
  config.ledc_timer = LEDC_TIMER_0;
  config.pin_d0 = Y2_GPIO_NUM;
  config.pin_d1 = Y3_GPIO_NUM;
  config.pin_d2 = Y4_GPIO_NUM;
  config.pin_d3 = Y5_GPIO_NUM;
  config.pin_d4 = Y6_GPIO_NUM;
  config.pin_d5 = Y7_GPIO_NUM;
  config.pin_d6 = Y8_GPIO_NUM;
  config.pin_d7 = Y9_GPIO_NUM;
  config.pin_xclk = XCLK_GPIO_NUM;
  config.pin_pclk = PCLK_GPIO_NUM;
  config.pin_vsync = VSYNC_GPIO_NUM;
  config.pin_href = HREF_GPIO_NUM;
  config.pin_sscb_sda = SIOD_GPIO_NUM;
  config.pin_sscb_scl = SIOC_GPIO_NUM;
  config.pin_pwdn = PWDN_GPIO_NUM;
  config.pin_reset = RESET_GPIO_NUM;

  config.xclk_freq_hz = 20000000;     // 10000000 or 20000000 -- 100 is faster with v1.04  // 200 is faster with v1.06 // 16500000 is an option

  config.pixel_format = PIXFORMAT_JPEG;

  framesize_t initial_driver_frame_size = driver_frame_size_from_index(framesizeconfig);
  framesize_t recording_driver_frame_size = driver_frame_size_from_index(framesize);
  Serial.printf("Frame config index %d -> driver enum %d, quality config %d, buffers config %d\n",
                framesizeconfig, (int)initial_driver_frame_size, qualityconfig, buffersconfig);
  config.frame_size = initial_driver_frame_size;
  config.jpeg_quality = qualityconfig;
  config.fb_count = buffersconfig;

  // https://github.com/espressif/esp32-camera/issues/357#issuecomment-1047086477
  //config.grab_mode      = CAMERA_GRAB_LATEST;

  if (Lots_of_Stats) {
    Serial.printf("Before camera config ...");
    Serial.printf("Internal Total heap %d, internal Free Heap %d, ", ESP.getHeapSize(), ESP.getFreeHeap());
    Serial.printf("SPIRam Total heap   %d, SPIRam Free Heap   %d\n", ESP.getPsramSize(), ESP.getFreePsram());
  }
  esp_err_t cam_err = ESP_FAIL;
  int attempt = 5;
  while (attempt && cam_err != ESP_OK) {
    cam_err = esp_camera_init(&config);
    if (cam_err != ESP_OK) {
      Serial.printf("Camera init failed with error 0x%x", cam_err);
      digitalWrite(PWDN_GPIO_NUM, 1);
      delay(500);
      digitalWrite(PWDN_GPIO_NUM, 0); // power cycle the camera (OV2640)
      attempt--;
    }
  }

  if (Lots_of_Stats) {
    Serial.printf("After  camera config ...");
    Serial.printf("Internal Total heap %d, internal Free Heap %d, ", ESP.getHeapSize(), ESP.getFreeHeap());
    Serial.printf("SPIRam Total heap   %d, SPIRam Free Heap   %d\n", ESP.getPsramSize(), ESP.getFreePsram());
  }

  if (cam_err != ESP_OK) {
    major_fail();
  }

  sensor_t * ss = esp_camera_sensor_get();

  ///ss->set_hmirror(ss, 1);        // 0 = disable , 1 = enable
  ///ss->set_vflip(ss, 1);          // 0 = disable , 1 = enable

  Serial.printf("\nCamera started correctly, Type is %x (hex) of 9650, 7725, 2640, 3660, 5640\n\n", ss->id.PID);

  if (ss->id.PID == OV5640_PID ) {
    //Serial.println("56 - going mirror");
    ss->set_hmirror(ss, 1);        // 0 = disable , 1 = enable
  } else {
    ss->set_hmirror(ss, 0);        // 0 = disable , 1 = enable
  }

  ss->set_quality(ss, quality);
  if (ss->set_framesize(ss, recording_driver_frame_size) != 0) {
    Serial.printf("Failed to set recording frame-size index %d (driver enum %d)\n",
                  framesize, (int)recording_driver_frame_size);
    major_fail();
  }
  Serial.printf("Recording frame-size index %d -> driver enum %d\n",
                framesize, (int)recording_driver_frame_size);

  ss->set_brightness(ss, 1);  //up the blightness just a bit
  ss->set_saturation(ss, -2); //lower the saturation

  delay(500);
  for (int j = 0; j < 10; j++) {
    camera_fb_t * fb = esp_camera_fb_get(); // get_good_jpeg();
    if (!fb) {
      Serial.println("Camera Capture Failed");
    } else {
      Serial.print("Pic, len="); Serial.print(fb->len);
      Serial.printf(", size=%ux%u, new fb %X\n",
                    (unsigned int)fb->width, (unsigned int)fb->height, (long)fb->buf);
      esp_camera_fb_return(fb);
      delay(10);
    }
  }
  Serial.printf("End of setup ...");
  Serial.printf("Internal Total heap %d, internal Free Heap %d, ", ESP.getHeapSize(), ESP.getFreeHeap());
  Serial.printf("SPIRam Total heap   %d, SPIRam Free Heap   %d\n", ESP.getPsramSize(), ESP.getFreePsram());
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//

#define SD_SPI_MOSI  9
#define SD_SPI_MISO  8
#define SD_SPI_SCK   7
#define SD_SPI_CS    21
const uint32_t SD_SPI_FREQUENCY = 10000000;

static esp_err_t init_sdcard()
{
  // 1. SPIバスの初期化: ピンを明示的に設定
  // SPI.begin(sck, miso, mosi, cs);
  SPI.begin(SD_SPI_SCK, SD_SPI_MISO, SD_SPI_MOSI, SD_SPI_CS);
  
  // 2. SD.hライブラリを使用してSDカードを初期化
  // SD.begin()の呼び出しは、SPIバスが設定された後に行う
  if (!SD.begin(SD_SPI_CS, SPI, SD_SPI_FREQUENCY)) {
    Serial.println("SD card initialization failed! (SPI Mode)");
    // 元のコードのメッセージとMajor Failを発動
    // 付近の Major Fail につながる
    Serial.println("Do you have an SD Card installed?");
    major_fail();
    return ESP_FAIL; // エラーコードを返す
  }
  
  // 3. 成功時の処理 (元のロジックをSD.hに置き換え)
  // 付近のロジックに相当
  Serial.printf("SD.begin success at %lu Hz\n", (unsigned long)SD_SPI_FREQUENCY); // 成功ログを追加
  uint8_t cardType = SD.cardType();

  // ... (カードタイプ表示のロジックはSDからSDに置き換える) ...
  
  uint64_t cardSize = SD.cardSize() / (1024 * 1024);
  Serial.printf("SD Card Size: %lluMB\n", cardSize);
  
  // SD.hはSD.hと同じ File クラスを使用するため、ファイル操作は変更不要
  
  return ESP_OK;
}

#include "config.h" 

String read_config_value(File &config_file) {
  if (!config_file.available()) return "";

  String value = config_file.readStringUntil('\n');
  value.replace("\r", "");

  // A value may contain spaces. Treat // as a comment only at the beginning
  // of the line or when it is preceded by whitespace.
  for (int i = 0; i + 1 < value.length(); ++i) {
    if (value.charAt(i) == '/' && value.charAt(i + 1) == '/' &&
        (i == 0 || value.charAt(i - 1) == ' ' || value.charAt(i - 1) == '\t')) {
      value.remove(i);
      break;
    }
  }

  value.trim();
  return value;
}

bool is_config_integer(const String &value) {
  if (value.length() == 0) return false;

  int start = value.charAt(0) == '-' ? 1 : 0;
  if (start == value.length()) return false;

  for (int i = start; i < value.length(); ++i) {
    if (value.charAt(i) < '0' || value.charAt(i) > '9') return false;
  }
  return true;
}

bool is_single_digit_config_value(const String &value) {
  return value.length() == 1 && value.charAt(0) >= '0' && value.charAt(0) <= '9';
}

void read_config_file() {

  // if there is a config.txt, use it plus defaults
  // else use defaults, and create a config.txt

  // put a file "config.txt" onto SD card, to set parameters different from your hardcoded parameters
  // it should look like this - one paramter per line, in the correct order, followed by 2 spaces, and any comments you choose
  /*
    ~~~ old config.txt file ~~~
    desklens  // camera name for files, mdns, etc
    11  // framesize 9=svga, 10=xga, 11=hd, 12=sxga, 13=uxga, 14=fhd, 17=qxga, 18=qhd, 21=qsxga
    8  // quality 0-63, lower the better, 10 good start, must be higher than "quality config"
    11  // framesize config - must be equal or higher than framesize
    5  / quality config - high q 0..5, med q 6..10, low q 11+
    3  // buffers - 1 is half speed of 3, but you might run out od memory with 3 and framesize > uxga
    900  // length of video in seconds
    0  // interval - ms between frames - 0 for fastest, or 500 for 2fps, 10000 for 10 sec/frame
    1  // speedup - multiply framerate - 1 for realtime, 24 for record at 1fps, play at 24fps or24x
    0  // streamdelay - ms between streaming frames - 0 for fast as possible, 500 for 2fps
    4  // 0 no internet, 1 get time then shutoff, 2 streaming using wifiman, 3 for use ssid names below default off, 4 names below default on
    MST7MDT,M3.2.0/2:00:00,M11.1.0/2:00:00  // timezone - this is mountain time, find timezone here https://sites.google.com/a/usapiens.com/opnode/time-zones
    ssid1234  // ssid
    mrpeanut  // ssid password

    ~~~ current config.txt file ~~~
    desklens  // camera name
    11  // framesize  11=hd
    1800  // length of video in seconds
    0  // recording count; 0 = unlimited
    0  // interval - ms between recording frames
    1  // speedup - multiply framerate
    0  // streamdelay - ms between streaming frames
    GMT // timezone
    0  // wifi mode: 0=off, 1=sta, 2=ap
    YOUR_WIFI_SSID  // STA network SSID, or AP name in AP mode
    YOUR_WIFI_PASSWORD  // STA password, or AP password in AP mode
    0  // STA IP mode: 0=DHCP/mDNS, 1=static IPv4
    192.168.1.123  // static IPv4 address
    192.168.1.1  // gateway
    255.255.255.0  // subnet mask
    192.168.1.1  // DNS server
    ~~~

    In STA/DHCP mode, browse to http://<camera-name>.local/.
    In STA/static mode, browse to the configured static IPv4 address.
    In AP mode, join the configured SSID and browse to http://192.168.4.1/.

    The previous 16-line layout and old config files with SSID on line 8 remain supported.
  */

  String cname = "desklens";
  int cframesize = DEFAULT_FRAME_SIZE_INDEX;
  int cquality = 12;
  int cframesizeconfig = DEFAULT_FRAME_BUFFER_SIZE_INDEX;
  int cqualityconfig = 5;
  int cbuffersconfig = 4; //58.9
  int clength = 1800;
  int cinterval = 0;
  int cspeedup = 1;
  int cstreamdelay = 0;
  int cwifimode = RECORDER_WIFI_OFF;
  int cwifiipmode = 0;
  String czone = "GMT";
  cssid = "ssid1234";
  cpass = "YOUR_WIFI_PASSWORD";
  int crecordingcount = 0;
  String cstaticipvalue = "192.168.1.123";
  String cgatewayvalue = "192.168.1.1";
  String csubnetvalue = "255.255.255.0";
  String cdnsvalue = "192.168.1.1";

  File config_file =SD.open("/config.txt", "r");
  if (config_file) {

    Serial.println("Reading config.txt");
    String config_values[16];
    int config_value_count = 0;
    while (config_value_count < 16 && config_file.available()) {
      config_values[config_value_count++] = read_config_value(config_file);
    }
    config_file.close();

    if (config_value_count > 0 && config_values[0].length() > 0) cname = config_values[0];
    if (config_value_count > 1 && is_config_integer(config_values[1])) cframesize = config_values[1].toInt();
    if (config_value_count > 2 && is_config_integer(config_values[2])) clength = config_values[2].toInt();

    bool reordered_layout = config_value_count >= 16 && is_single_digit_config_value(config_values[8]);
    bool previous_explicit_layout = !reordered_layout && config_value_count >= 16 &&
                                    is_single_digit_config_value(config_values[7]);

    if (reordered_layout) {
      // Current layout: recording count is line 4 and WiFi mode is line 9.
      if (is_config_integer(config_values[3])) crecordingcount = config_values[3].toInt();
      if (is_config_integer(config_values[4])) cinterval = config_values[4].toInt();
      if (is_config_integer(config_values[5])) cspeedup = config_values[5].toInt();
      if (is_config_integer(config_values[6])) cstreamdelay = config_values[6].toInt();
      if (config_values[7].length() > 0) czone = config_values[7];
      cwifimode = config_values[8].toInt();
      if (config_values[9].length() > 0) cssid = config_values[9];
      if (config_values[10].length() > 0) cpass = config_values[10];
    } else if (previous_explicit_layout) {
      // Previous 16-line layout: recording count was line 11 and WiFi mode line 8.
      Serial.println("Previous config layout detected; recording count on line 11 is supported");
      if (is_config_integer(config_values[3])) cinterval = config_values[3].toInt();
      if (is_config_integer(config_values[4])) cspeedup = config_values[4].toInt();
      if (is_config_integer(config_values[5])) cstreamdelay = config_values[5].toInt();
      if (config_values[6].length() > 0) czone = config_values[6];
      cwifimode = config_values[7].toInt();
      if (config_values[8].length() > 0) cssid = config_values[8];
      if (config_values[9].length() > 0) cpass = config_values[9];
      if (is_config_integer(config_values[10])) crecordingcount = config_values[10].toInt();
    } else {
      // Legacy layout: line 8 was the SSID and special SSIDs selected the mode.
      if (config_value_count > 3 && is_config_integer(config_values[3])) cinterval = config_values[3].toInt();
      if (config_value_count > 4 && is_config_integer(config_values[4])) cspeedup = config_values[4].toInt();
      if (config_value_count > 5 && is_config_integer(config_values[5])) cstreamdelay = config_values[5].toInt();
      if (config_value_count > 6 && config_values[6].length() > 0) czone = config_values[6];
      if (config_value_count > 7 && config_values[7].length() > 0) cssid = config_values[7];
      if (config_value_count > 8 && config_values[8].length() > 0) cpass = config_values[8];
      if (config_value_count > 9 && is_config_integer(config_values[9])) crecordingcount = config_values[9].toInt();

      if (cssid.equalsIgnoreCase("ssid1234")) {
        cwifimode = RECORDER_WIFI_OFF;
      } else if (cssid.equalsIgnoreCase("wifiman") || cssid.equalsIgnoreCase("ap")) {
        cwifimode = RECORDER_WIFI_AP;
      } else {
        cwifimode = RECORDER_WIFI_STA;
      }
    }

    if (reordered_layout || previous_explicit_layout) {
      if (is_config_integer(config_values[11])) cwifiipmode = config_values[11].toInt();
      if (config_values[12].length() > 0) cstaticipvalue = config_values[12];
      if (config_values[13].length() > 0) cgatewayvalue = config_values[13];
      if (config_values[14].length() > 0) csubnetvalue = config_values[14];
      if (config_values[15].length() > 0) cdnsvalue = config_values[15];

      if (cwifimode < RECORDER_WIFI_OFF || cwifimode > RECORDER_WIFI_AP) {
        Serial.println("Invalid wifi mode; forcing WiFi off");
        cwifimode = RECORDER_WIFI_OFF;
      }
    }
  } else {
    Serial.println("Failed to open config.txt - writing a default");

    // lets make a simple.txt config file
    File new_simple =SD.open("/config.txt", "w");
    new_simple.write((const uint8_t *)config_txt, config_txt_len);
    new_simple.close();
    cwifimode = RECORDER_WIFI_OFF;
  }

  if (crecordingcount < 0) crecordingcount = 0;
  if (!is_valid_frame_size_index(cframesize)) {
    Serial.printf("Invalid frame-size index %d; using %d (HD 1280x720)\n",
                  cframesize, DEFAULT_FRAME_SIZE_INDEX);
    cframesize = DEFAULT_FRAME_SIZE_INDEX;
  }
  if (!is_valid_frame_size_index(cframesizeconfig)) {
    Serial.printf("Invalid frame-buffer size index %d; using %d (UXGA 1600x1200)\n",
                  cframesizeconfig, DEFAULT_FRAME_BUFFER_SIZE_INDEX);
    cframesizeconfig = DEFAULT_FRAME_BUFFER_SIZE_INDEX;
  }
  if (cwifiipmode != 0 && cwifiipmode != 1) {
    Serial.println("Invalid STA IP mode; using DHCP/mDNS");
    cwifiipmode = 0;
  }

  Serial.printf("=========   Data fram config.txt and defaults  =========\n");
  Serial.printf("Name %s\n", cname); logfile.printf("Name %s\n", cname);
  Serial.printf("Framesize %d\n", cframesize); logfile.printf("Framesize %d\n", cframesize);
  Serial.printf("Quality %d\n", cquality); logfile.printf("Quality %d\n", cquality);
  Serial.printf("Framesize config %d\n", cframesizeconfig); logfile.printf("Framesize config%d\n", cframesizeconfig);
  Serial.printf("Quality config %d\n", cqualityconfig); logfile.printf("Quality config%d\n", cqualityconfig);
  Serial.printf("Buffers config %d\n", cbuffersconfig); logfile.printf("Buffers config %d\n", cbuffersconfig);
  Serial.printf("Length %d\n", clength); logfile.printf("Length %d\n", clength);
  Serial.printf("Interval %d\n", cinterval); logfile.printf("Interval %d\n", cinterval);
  Serial.printf("Speedup %d\n", cspeedup); logfile.printf("Speedup %d\n", cspeedup);
  Serial.printf("Recording count %d (0 = unlimited)\n", crecordingcount); logfile.printf("Recording count %d (0 = unlimited)\n", crecordingcount);
  Serial.printf("Streamdelay %d\n", cstreamdelay); logfile.printf("Streamdelay %d\n", cstreamdelay);
  Serial.printf("WiFi mode %d (0=off, 1=sta, 2=ap)\n", cwifimode); logfile.printf("WiFi mode %d (0=off, 1=sta, 2=ap)\n", cwifimode);
  Serial.printf("Zone len %d, %s\n", czone.length(), czone.c_str()); //logfile.printf("Zone len %d, %s\n", czone.length(), czone);
  Serial.printf("ssid %s\n", cssid); logfile.printf("ssid %s\n", cssid);

  if (cwifimode == RECORDER_WIFI_STA && cwifiipmode == 0) {
    Serial.printf("Web address: http://%s.local/\n", cname.c_str());
  } else if (cwifimode == RECORDER_WIFI_STA) {
    Serial.printf("Web address: http://%s/\n", cstaticipvalue.c_str());
  } else if (cwifimode == RECORDER_WIFI_AP) {
    Serial.println("Web address: http://192.168.4.1/");
  }


  framesize = cframesize;
  quality = cquality;
  framesizeconfig = cframesizeconfig;
  qualityconfig = cqualityconfig;
  buffersconfig = cbuffersconfig;
  avi_length = clength;
  frame_interval = cinterval;
  speed_up_factor = cspeedup;
  stream_delay = cstreamdelay;
  max_recordings = crecordingcount;
  wifi_mode = cwifimode;
  wifi_ip_mode = cwifiipmode;
  cstaticip = cstaticipvalue;
  cgateway = cgatewayvalue;
  csubnet = csubnetvalue;
  configured_dns = cdnsvalue;
  configfile = true;
  TIMEZONE = czone;

  snprintf(devname, sizeof(devname), "%s", cname.c_str());

}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
//  delete_old_stuff() - delete oldest files to free diskspace
//

void listDir( const char * dirname, uint8_t levels) {

  Serial.printf("Listing directory: %s\n", "/");

  File root =SD.open("/");
  if (!root) {
    Serial.println("Failed to open directory");
    return;
  }
  if (!root.isDirectory()) {
    Serial.println("Not a directory");
    return;
  }

  File filex = root.openNextFile();
  while (filex) {
    if (filex.isDirectory()) {
      Serial.print("  DIR : ");
      Serial.println(filex.name());
      if (levels) {
        listDir( filex.name(), levels - 1);
      }
    } else {
      Serial.print("  FILE: ");
      Serial.print(filex.name());
      Serial.print("  SIZE: ");
      Serial.println(filex.size());
    }
    filex = root.openNextFile();
  }
}

bool deleteFolderOrFile(const char * val);

void delete_old_stuff() {

  uint64_t total_bytes = SD.totalBytes();
  uint64_t used_bytes = SD.usedBytes();

  Serial.printf("Total space: %lluMB\n", total_bytes / (1024 * 1024));
  Serial.printf("Used space: %lluMB\n", used_bytes / (1024 * 1024));

  if (total_bytes == 0 || used_bytes > total_bytes) {
    Serial.println("Invalid SD capacity information. Cleanup stopped; check or reformat the SD card.");
    return;
  }

  //listDir( "/", 0);

  float full = (float)used_bytes / (float)total_bytes;
  if (full  <  0.8) {
    Serial.printf("Nothing deleted, %.1f%% disk full\n", 100.0 * full);
  } else {
    Serial.printf("Disk is %.1f%% full ... deleting oldest file\n", 100.0 * full);
    const uint16_t max_delete_attempts = 100;
    uint16_t delete_attempts = 0;
    while (full > 0.8) {

      if (delete_attempts >= max_delete_attempts) {
        Serial.println("Cleanup reached its deletion limit. Check the SD card before recording more video.");
        break;
      }
      delete_attempts++;

      double del_number = 999999999;
      char del_numbername[50] = {0};

      File f =SD.open("/");
      if (!f || !f.isDirectory()) {
        Serial.println("Could not open the SD root directory. Cleanup stopped.");
        if (f) f.close();
        break;
      }

      File file = f.openNextFile();

      while (file) {
        //Serial.println(file.name());
        if (!file.isDirectory()) {

          char foldname[50] = {0};
          snprintf(foldname, sizeof(foldname), "%s", file.name());
          for ( int x = 0; x < 49 && foldname[x] != '\0'; x++) {
            if ( (foldname[x] >= 0x30 && foldname[x] <= 0x39) || foldname[x] == 0x2E) {
            } else {
              if (foldname[x] != 0) foldname[x] = 0x20;
            }
          }

          double i = atof(foldname);
          if ( i > 0 && i < del_number) {
            snprintf(del_numbername, sizeof(del_numbername), "%s", file.name());
            del_number = i;
          }
          //Serial.printf("Name is %s, number is %f\n", foldname, i);
        }
        file.close();
        file = f.openNextFile();

      }
      f.close();

      if (del_number >= 999999999 || del_numbername[0] == '\0') {
        Serial.println("No deletable file was found. Cleanup stopped to avoid an infinite loop.");
        break;
      }

      Serial.printf("Lowest is Name is %s, number is %f\n", del_numbername, del_number);
      uint64_t used_before_delete = used_bytes;
      if (!deleteFolderOrFile(del_numbername)) {
        Serial.println("Deletion failed. Cleanup stopped to avoid an infinite loop.");
        break;
      }
      used_bytes = SD.usedBytes();

      if (used_bytes > total_bytes || used_bytes >= used_before_delete) {
        Serial.println("Deletion made no measurable progress. Cleanup stopped; check or reformat the SD card.");
        break;
      }

      full = (float)used_bytes / (float)total_bytes;
      Serial.printf("Disk is %.1f%% full ... \n", 100.0 * full);
    }
  }
}

bool deleteFolderOrFile(const char * val) {
  // Function provided by user @gemi254
  Serial.printf("Deleting : %s\n", val);
  String target = String(val);
  if (!target.startsWith("/")) target = "/" + target;

  File f =SD.open(target);
  if (!f) {
    Serial.printf("Failed to open %s\n", val);
    return false;
  }

  if (f.isDirectory()) {
    bool all_children_deleted = true;
    File file = f.openNextFile();
    while (file) {
      String child_name = file.name();
      if (file.isDirectory()) {
        Serial.print("  DIR : ");
        Serial.println(child_name);
        all_children_deleted = false;
        file.close();
      } else {
        Serial.print("  FILE: ");
        Serial.print(child_name);
        Serial.print("  SIZE: ");
        Serial.print(file.size());
        file.close();
        if (SD.remove(child_name)) {
          Serial.println(" deleted.");
        } else {
          Serial.println(" FAILED.");
          all_children_deleted = false;
        }
      }
      file = f.openNextFile();
    }
    f.close();
    //Remove the dir
    if (SD.rmdir(target)) {
      Serial.printf("Dir %s removed\n", val);
      return all_children_deleted;
    } else {
      Serial.println("Remove dir failed");
      return false;
    }

  } else {
    //Remove the file
    f.close();
    if (SD.remove(target)) {
      Serial.printf("File %s deleted\n", val);
      return true;
    } else {
      Serial.println("Delete failed");
      return false;
    }
  }
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
//  get_good_jpeg()  - take a picture and make sure it has a good jpeg
//
camera_fb_t *  get_good_jpeg() {

  camera_fb_t * fb;

  long start;
  int failures = 0;

  do {
    int fblen = 0;
    int foundffd9 = 0;
    long bp = millis();
    long mstart = micros();

    fb = esp_camera_fb_get();
    if (!fb) {
      Serial.println("Camera Capture Failed");
      failures++;
    } else {
      long mdelay = micros() - mstart;

      int get_fail = 0;

      totalp = totalp + millis() - bp;
      time_in_camera = totalp;

      fblen = fb->len;

      for (int j = 1; j <= 1025; j++) {
        if (fb->buf[fblen - j] != 0xD9) {
          // no d9, try next for
        } else {                                     //Serial.println("Found a D9");
          if (fb->buf[fblen - j - 1] == 0xFF ) {     //Serial.print("Found the FFD9, junk is "); Serial.println(j);
            if (j == 1) {
              normal_jpg++;
            } else {
              extend_jpg++;
            }
            foundffd9 = 1;
            if (Lots_of_Stats) {
              if (j > 900) {                             //  rarely happens - sometimes on 2640
                Serial.print("Frame "); Serial.print(frame_cnt); logfile.print("Frame "); logfile.print(frame_cnt);
                Serial.print(", Len = "); Serial.print(fblen); logfile.print(", Len = "); logfile.print(fblen);
                //Serial.print(", Correct Len = "); Serial.print(fblen - j + 1);
                Serial.print(", Extra Bytes = "); Serial.println( j - 1); logfile.print(", Extra Bytes = "); logfile.println( j - 1);
                logfile.flush();
              }

              if ( frame_cnt % 100 == 50) {
                gframe_cnt = frame_cnt;
                gfblen = fblen;
                gj = j;
                gmdelay = mdelay;
                //Serial.printf("Frame %6d, len %6d, extra  %4d, cam time %7d ", frame_cnt, fblen, j - 1, mdelay / 1000);
                //logfile.printf("Frame %6d, len %6d, extra  %4d, cam time %7d ", frame_cnt, fblen, j - 1, mdelay / 1000);
                do_it_now = 1;
              }
            }
            break;
          }
        }
      }

      if (!foundffd9) {
        bad_jpg++;
        Serial.printf("Bad jpeg, Frame %d, Len = %d \n", frame_cnt, fblen);
        logfile.printf("Bad jpeg, Frame %d, Len = %d\n", frame_cnt, fblen);

        esp_camera_fb_return(fb);
        failures++;

      } else {
        break;
        // count up the useless bytes
      }
    }

  } while (failures < 10);   // normally leave the loop with a break()

  // if we get 10 bad frames in a row, then quality parameters are too high - set them lower (+5), and start new movie
  if (failures == 10) {
    Serial.printf("10 failures");
    logfile.printf("10 failures");
    logfile.flush();

    sensor_t * ss = esp_camera_sensor_get();
    int qual = ss->status.quality ;
    ss->set_quality(ss, qual + 5);
    quality = qual + 5;
    Serial.printf("\n\nDecreasing quality due to frame failures %d -> %d\n\n", qual, qual + 5);
    logfile.printf("\n\nDecreasing quality due to frame failures %d -> %d\n\n", qual, qual + 5);
    delay(1000);

    start_record = 0;
    //reboot_now = true;
  }
  return fb;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
//  eprom functions  - increment the file_group, so files are always unique
//

#include <EEPROM.h>

struct eprom_data {
  int eprom_good;
  int file_group;
};

void do_eprom_read() {

  eprom_data ed;

  EEPROM.begin(200);
  EEPROM.get(0, ed);
  EEPROM.end();

  if (ed.eprom_good == MagicNumber) {
    Serial.println("Good settings in the EPROM ");
    file_group = ed.file_group;
    file_group++;
    Serial.print("New File Group "); Serial.println(file_group );
  } else {
    Serial.println("No settings in EPROM - Starting with File Group 1 ");
    file_group = 1;
  }
  file_number = 1;
}

void do_eprom_write() {

  eprom_data ed;
  ed.eprom_good = MagicNumber;
  ed.file_group  = file_group;

  Serial.println("Writing to EPROM ...");

  EEPROM.begin(200);
  EEPROM.put(0, ed);
  EEPROM.commit();
  EEPROM.end();
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Make the avi functions
//
//   start_avi() - open the file and write headers using the first captured frame
//   another_pic_avi() - write one more frame of movie
//   end_avi() - write the final parameters and close the file


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// start_avi - open the files and write in headers
//

static void start_avi(const camera_fb_t *first_frame) {

  long start = millis();

  if (first_frame == NULL || first_frame->width == 0 || first_frame->height == 0) {
    Serial.println("Cannot start AVI: first camera frame has no valid dimensions");
    major_fail();
    return;
  }

  uint32_t avi_width = first_frame->width;
  uint32_t avi_height = first_frame->height;

  Serial.println("Starting an avi ");

  sprintf(avi_file_name, "/%s%d.%03d.avi",  devname, file_group, file_number);

  file_number++;

  avifile =SD.open(avi_file_name, "w");
  idxfile =SD.open("/idx.tmp", "w");

  if (avifile) {
    Serial.printf("File open: %s\n", avi_file_name);
    logfile.printf("File open: %s\n", avi_file_name);
  }  else  {
    Serial.println("Could not open file");
    major_fail();
  }

  if (idxfile)  {
    //Serial.printf("File open: %s\n", "//idx.tmp");
  }  else  {
    Serial.println("Could not open file /idx.tmp");
    major_fail();
  }

  for ( i = 0; i < AVIOFFSET; i++) {
    char ch = pgm_read_byte(&avi_header[i]);
    buf[i] = ch;
  }

  // Use the dimensions reported by the camera frame itself. This keeps the
  // MJPEG payload and AVI headers consistent across esp32-camera versions.
  write_quartet_to_buffer(buf + 0x40, avi_width);
  write_quartet_to_buffer(buf + 0xA8, avi_width);
  write_quartet_to_buffer(buf + 0x44, avi_height);
  write_quartet_to_buffer(buf + 0xAC, avi_height);

  Serial.printf("AVI dimensions %ux%u from first captured frame\n",
                (unsigned int)avi_width, (unsigned int)avi_height);
  logfile.printf("AVI dimensions %ux%u from first captured frame\n",
                 (unsigned int)avi_width, (unsigned int)avi_height);

  size_t err = avifile.write(buf, AVIOFFSET);

  uint8_t ex_fps = 1;
  if (frame_interval == 0) {
    if (framesize >= 11) {
      ex_fps = 12.5 * speed_up_factor ;;
    } else {
      ex_fps = 25.0 * speed_up_factor;
    }
  } else {
    ex_fps = round(1000.0 / frame_interval * speed_up_factor);
  }

  avifile.seek( 0x84 , SeekSet);
  print_quartet((int)ex_fps, avifile);

  avifile.seek( AVIOFFSET, SeekSet);

  Serial.print(F("\nRecording "));
  Serial.print(avi_length);
  Serial.println(" seconds.");

  startms = millis();

  totalp = 0;
  totalw = 0;

  jpeg_size = 0;
  movi_size = 0;
  uVideoLen = 0;
  idx_offset = 4;

  bad_jpg = 0;
  extend_jpg = 0;
  normal_jpg = 0;

  time_in_loop = 0;
  time_in_camera = 0;
  time_in_sd = 0;
  time_in_good = 0;
  time_total = 0;
  time_in_web1 = 0;
  time_in_web2 = 0;
  delay_wait_for_sd = 0;
  wait_for_cam = 0;

  time_in_sd += (millis() - start);

  logfile.flush();
  avifile.flush();
  idxfile.flush();
  last_avi_flush_time = millis();

} // end of start avi

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
//  another_save_avi saves another frame to the avi file, uodates index
//           -- pass in a fb pointer to the frame to add
//

static void another_save_avi(camera_fb_t * fb ) {

  long start = millis();

  int fblen;
  fblen = fb->len;

  int fb_block_length;
  uint8_t* fb_block_start;

  jpeg_size = fblen;

  remnant = (4 - (jpeg_size & 0x00000003)) & 0x00000003;

  long bw = millis();
  long frame_write_start = millis();

  framebuffer_static[0] = 0x30;       // "00dc"
  framebuffer_static[1] = 0x30;
  framebuffer_static[2] = 0x64;
  framebuffer_static[3] = 0x63;

  int jpeg_size_rem = jpeg_size + remnant;

  framebuffer_static[4] = jpeg_size_rem % 0x100;
  framebuffer_static[5] = (jpeg_size_rem >> 8) % 0x100;
  framebuffer_static[6] = (jpeg_size_rem >> 16) % 0x100;
  framebuffer_static[7] = (jpeg_size_rem >> 24) % 0x100;

  fb_block_start = fb->buf;

  if (fblen > fbs * 1024 - 8 ) {                     // fbs is the size of frame buffer static
    fb_block_length = fbs * 1024;
    fblen = fblen - (fbs * 1024 - 8);
    memcpy(framebuffer_static + 8, fb_block_start, fb_block_length - 8);
    fb_block_start = fb_block_start + fb_block_length - 8;

  } else {
    fb_block_length = fblen + 8  + remnant;
    memcpy(framebuffer_static + 8, fb_block_start,  fblen);
    fblen = 0;
  }

  size_t err = avifile.write(framebuffer_static, fb_block_length);

  if (err != fb_block_length) {
    Serial.print("Error on avi write: err = "); Serial.print(err);
    Serial.print(" len = "); Serial.println(fb_block_length);
    logfile.print("Error on avi write: err = "); logfile.print(err);
    logfile.print(" len = "); logfile.println(fb_block_length);
  }

  while (fblen > 0) {

    if (fblen > fbs * 1024) {
      fb_block_length = fbs * 1024;
      fblen = fblen - fb_block_length;
    } else {
      fb_block_length = fblen  + remnant;
      fblen = 0;
    }

    memcpy(framebuffer_static, fb_block_start, fb_block_length);

    size_t err = avifile.write(framebuffer_static,  fb_block_length);

    if (err != fb_block_length) {
      Serial.print("Error on avi write: err = "); Serial.print(err);
      Serial.print(" len = "); Serial.println(fb_block_length);
    }

    fb_block_start = fb_block_start + fb_block_length;
    delay(0);
  }


  movi_size += jpeg_size;
  uVideoLen += jpeg_size;
  long frame_write_end = millis();

  print_2quartet(idx_offset, jpeg_size, idxfile);

  idx_offset = idx_offset + jpeg_size + remnant + 8;

  movi_size = movi_size + remnant;

  if ( do_it_now == 1 && frame_cnt < 1011) {
    do_it_now = 0;
    Serial.printf("Frame %6d, len %6d, extra  %4d, cam time %7d,  sd time %4d -- \n", gframe_cnt, gfblen, gj - 1, gmdelay / 1000, millis() - bw);
    logfile.printf("Frame % 6d, len % 6d, extra  % 4d, cam time % 7d,  sd time % 4d -- \n", gframe_cnt, gfblen, gj - 1, gmdelay / 1000, millis() - bw);
    //Serial.printf(" sd time %4d -- \n",  millis() - bw);
    //logfile.printf(" sd time %4d -- \n",  millis() - bw);
    logfile.flush();
  }

  totalw = totalw + millis() - bw;
  time_in_sd += (millis() - start);

  if ((uint32_t)(millis() - last_avi_flush_time) >= AVI_FLUSH_INTERVAL_MS) {
    avifile.flush();
    idxfile.flush();
    last_avi_flush_time = millis();
  }


} // end of another_pic_avi

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
//  end_avi writes the index, and closes the files
//

static void end_avi() {

  long start = millis();

  unsigned long current_end = avifile.position();

  Serial.println("End of avi - closing the files");
  logfile.println("End of avi - closing the files");

  if (frame_cnt <  5 ) {
    Serial.println("Recording screwed up, less than 5 frames, forget index\n");
    idxfile.flush();
    avifile.flush();
    idxfile.close();
    avifile.close();
    int xx = remove("/idx.tmp");
    int yy = remove(avi_file_name);

  } else {

    elapsedms = millis() - startms;

    float fRealFPS = (1000.0f * (float)frame_cnt) / ((float)elapsedms) * speed_up_factor;

    float fmicroseconds_per_frame = 1000000.0f / fRealFPS;
    uint8_t iAttainedFPS = round(fRealFPS) ;
    uint32_t us_per_frame = round(fmicroseconds_per_frame);

    //Modify the MJPEG header from the beginning of the file, overwriting various placeholders

    avifile.seek( 4 , SeekSet);
    print_quartet(movi_size + 240 + 16 * frame_cnt + 8 * frame_cnt, avifile);

    avifile.seek( 0x20 , SeekSet);
    print_quartet(us_per_frame, avifile);

    unsigned long max_bytes_per_sec = (1.0f * movi_size * iAttainedFPS) / frame_cnt;

    avifile.seek( 0x24 , SeekSet);
    print_quartet(max_bytes_per_sec, avifile);

    avifile.seek( 0x30 , SeekSet);
    print_quartet(frame_cnt, avifile);

    avifile.seek( 0x8c , SeekSet);
    print_quartet(frame_cnt, avifile);

    avifile.seek( 0x84 , SeekSet);
    print_quartet((int)iAttainedFPS, avifile);

    avifile.seek( 0xe8 , SeekSet);
    print_quartet(movi_size + frame_cnt * 8 + 4, avifile);

    Serial.println(F("\n*** Video recorded and saved ***\n"));

    Serial.printf("Recorded %5d frames in %5d seconds\n", frame_cnt, elapsedms / 1000);
    Serial.printf("File size is %u bytes\n", movi_size + 12 * frame_cnt + 4);
    Serial.printf("Adjusted FPS is %5.2f\n", fRealFPS);
    Serial.printf("Max data rate is %lu bytes/s\n", max_bytes_per_sec);
    Serial.printf("Frame duration is %d us\n", us_per_frame);
    Serial.printf("Average frame length is %d bytes\n", uVideoLen / frame_cnt);
    Serial.print("Average picture time (ms) "); Serial.println( 1.0 * totalp / frame_cnt);
    Serial.print("Average write time (ms)   "); Serial.println( 1.0 * totalw / frame_cnt );
    Serial.print("Normal jpg % ");  Serial.println( 100.0 * normal_jpg / frame_cnt, 1 );
    Serial.print("Extend jpg % ");  Serial.println( 100.0 * extend_jpg / frame_cnt, 1 );
    Serial.print("Bad    jpg % ");  Serial.println( 100.0 * bad_jpg / frame_cnt, 5 );

    Serial.printf("Writng the index, %d frames\n", frame_cnt);

    logfile.printf("Recorded %5d frames in %5d seconds\n", frame_cnt, elapsedms / 1000);
    logfile.printf("File size is %u bytes\n", movi_size + 12 * frame_cnt + 4);
    logfile.printf("Adjusted FPS is %5.2f\n", fRealFPS);
    logfile.printf("Max data rate is %lu bytes/s\n", max_bytes_per_sec);
    logfile.printf("Frame duration is %d us\n", us_per_frame);
    logfile.printf("Average frame length is %d bytes\n", uVideoLen / frame_cnt);
    logfile.print("Average picture time (ms) "); logfile.println( 1.0 * totalp / frame_cnt);
    logfile.print("Average write time (ms)   "); logfile.println( 1.0 * totalw / frame_cnt );
    logfile.print("Normal jpg % ");  logfile.println( 100.0 * normal_jpg / frame_cnt, 1 );
    logfile.print("Extend jpg % ");  logfile.println( 100.0 * extend_jpg / frame_cnt, 1 );
    logfile.print("Bad    jpg % ");  logfile.println( 100.0 * bad_jpg / frame_cnt, 5 );

    logfile.printf("Writng the index, %d frames\n", frame_cnt);

    avifile.seek( current_end , SeekSet);

    idxfile.flush();
    idxfile.close();

    size_t i1_err = avifile.write(idx1_buf, 4);

    print_quartet(frame_cnt * 16, avifile);

    idxfile =SD.open("/idx.tmp", "r");

    if (idxfile)  {
      //Serial.printf("File open: %s\n", "//idx.tmp");
      //logfile.printf("File open: %s\n", "/idx.tmp");
    }  else  {
      Serial.println("Could not open index file");
      logfile.println("Could not open index file");
      major_fail();
    }

    char * AteBytes;
    AteBytes = (char*) malloc (8);

    for (int i = 0; i < frame_cnt; i++) {
      size_t res = idxfile.readBytes( AteBytes, 8);
      size_t i1_err = avifile.write(dc_buf, 4);
      size_t i2_err = avifile.write(zero_buf, 4);
      size_t i3_err = avifile.write((uint8_t *)AteBytes, 8);
    }

    free(AteBytes);

    idxfile.close();
    avifile.flush();
    avifile.close();

    int xx =SD.remove("/idx.tmp");
  }

  Serial.println("---");  logfile.println("---");

  time_in_sd += (millis() - start);

  Serial.println("");
  time_total = millis() - startms;
  Serial.printf("waiting for cam %10dms, %4.1f%%\n", wait_for_cam , 100.0 * wait_for_cam  / time_total);
  Serial.printf("Time in camera  %10dms, %4.1f%%\n", time_in_camera, 100.0 * time_in_camera / time_total);
  Serial.printf("waiting for sd  %10dms, %4.1f%%\n", delay_wait_for_sd , 100.0 * delay_wait_for_sd  / time_total);
  Serial.printf("Time in sd      %10dms, %4.1f%%\n", time_in_sd    , 100.0 * time_in_sd     / time_total);
  Serial.printf("web (core 1)    %10dms, %4.1f%%\n", time_in_web1  , 100.0 * time_in_web1   / time_total);
  Serial.printf("web (core 0)    %10dms, %4.1f%%\n", time_in_web2  , 100.0 * time_in_web2   / time_total);
  Serial.printf("time total      %10dms, %4.1f%%\n", time_total    , 100.0 * time_total     / time_total);

  logfile.printf("waiting for cam %10dms, %4.1f%%\n", wait_for_cam , 100.0 * wait_for_cam  / time_total);
  logfile.printf("Time in camera  %10dms, %4.1f%%\n", time_in_camera, 100.0 * time_in_camera / time_total);
  logfile.printf("waiting for sd  %10dms, %4.1f%%\n", delay_wait_for_sd , 100.0 * delay_wait_for_sd  / time_total);
  logfile.printf("Time in sd      %10dms, %4.1f%%\n", time_in_sd    , 100.0 * time_in_sd     / time_total);
  logfile.printf("web (core 1)    %10dms, %4.1f%%\n", time_in_web1  , 100.0 * time_in_web1   / time_total);
  logfile.printf("web (core 0)    %10dms, %4.1f%%\n", time_in_web2  , 100.0 * time_in_web2   / time_total);
  logfile.printf("time total      %10dms, %4.1f%%\n", time_total    , 100.0 * time_total     / time_total);

  Serial.printf("SD task minimum free stack since startup: %u / %u bytes\n",
                sd_task_min_free_stack_bytes, SD_TASK_STACK_SIZE);
  logfile.printf("SD task minimum free stack since startup: %u / %u bytes\n",
                 sd_task_min_free_stack_bytes, SD_TASK_STACK_SIZE);

  logfile.flush();

}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Time
#include "time.h"

// Workaround for the WebServer.h vs esp_http_server.h problem  https://github.com/tzapu/WiFiManager/issues/1184
/*
  #define _HTTP_Method_H_

  typedef enum {
  jHTTP_GET     = 0b00000001,
  jHTTP_POST    = 0b00000010,
  jHTTP_DELETE  = 0b00000100,
  jHTTP_PUT     = 0b00001000,
  jHTTP_PATCH   = 0b00010000,
  jHTTP_HEAD    = 0b00100000,
  jHTTP_OPTIONS = 0b01000000,
  jHTTP_ANY     = 0b01111111,
  } HTTPMethod;
*/
//#include "C:\ArduinoPortable\arduino-1.8.19\portable\packages\esp32\hardware\esp32\2.0.3\libraries\WiFi\src\WiFi.h"
//#include "C:\ArduinoPortable\sketch\libraries\WiFiManager\WiFiManager.h"
//#include "WiFiManager.h"
#include "ESPmDNS.h"

#include "ESPxWebFlMgr.h"          //v56
const word filemanagerport = 8080;
ESPxWebFlMgr filemgr(filemanagerport); // we want a different port than the webserver


time_t now;
struct tm timeinfo;
char localip[20];
WiFiEventId_t eventID;

const wifi_power_t WIFI_TX_POWER_INITIAL = WIFI_POWER_13dBm;
const wifi_power_t WIFI_TX_POWER_FALLBACK = WIFI_POWER_15dBm;
const uint32_t WIFI_STA_CONNECT_TIMEOUT_MS = 16000;
const uint32_t WIFI_POWER_STAGE_DELAY_MS = 500;
const uint32_t WIFI_INTERFACE_START_TIMEOUT_MS = 1000;
volatile bool wifi_disconnect_reason_available = false;
volatile uint8_t last_wifi_disconnect_reason = WIFI_REASON_UNSPECIFIED;
bool wifi_event_handler_registered = false;

void register_wifi_diagnostics() {
  if (wifi_event_handler_registered) return;

  eventID = WiFi.onEvent([](WiFiEvent_t event, WiFiEventInfo_t info) {
    uint8_t reason = info.wifi_sta_disconnected.reason;
    last_wifi_disconnect_reason = reason;
    wifi_disconnect_reason_available = true;
    Serial.printf("\nWiFi disconnected: reason=%u (%s), status=%d\n",
                  reason,
                  WiFi.disconnectReasonName((wifi_err_reason_t)reason),
                  WiFi.status());
  }, ARDUINO_EVENT_WIFI_STA_DISCONNECTED);

  wifi_event_handler_registered = eventID != 0;
  if (!wifi_event_handler_registered) {
    Serial.println("WARNING: Failed to register WiFi disconnect diagnostics");
  }
}

bool wait_for_wifi_interface_start(bool station_mode) {
  uint32_t started_at = millis();
  while ((station_mode ? !WiFi.STA.started() : !WiFi.AP.started()) &&
         (uint32_t)(millis() - started_at) < WIFI_INTERFACE_START_TIMEOUT_MS) {
    delay(10);
  }
  return station_mode ? WiFi.STA.started() : WiFi.AP.started();
}

void report_sta_connection_failure() {
  int status = WiFi.status();
  if (wifi_disconnect_reason_available) {
    uint8_t reason = last_wifi_disconnect_reason;
    const char *reason_name = WiFi.disconnectReasonName((wifi_err_reason_t)reason);
    Serial.printf("STA connection failed: status=%d, reason=%u (%s); AP fallback is disabled\n",
                  status, reason, reason_name);
    if (logfile) {
      logfile.printf("STA connection failed: status=%d, reason=%u (%s)\n",
                     status, reason, reason_name);
    }
  } else {
    Serial.printf("STA connection failed: status=%d, no disconnect reason was reported; AP fallback is disabled\n",
                  status);
    if (logfile) {
      logfile.printf("STA connection failed: status=%d, no disconnect reason was reported\n",
                     status);
    }
  }
}

void stop_wifi_completely() {
  MDNS.end();
  WiFi.disconnect(true, false);
  WiFi.mode(WIFI_OFF);
  InternetOff = true;
}

bool set_wifi_tx_power(wifi_power_t power, const char *label) {
  if (WiFi.setTxPower(power)) {
    Serial.printf("WiFi TX power set to %s\n", label);
    return true;
  }

  Serial.printf("WARNING: Failed to set WiFi TX power to %s\n", label);
  return false;
}

bool set_sta_power_save(wifi_ps_type_t mode, const char *description) {
  if (wifi_mode != RECORDER_WIFI_STA || WiFi.status() != WL_CONNECTED) return true;

  if (WiFi.setSleep(mode)) {
    Serial.println(description);
    return true;
  }

  Serial.printf("WARNING: Failed to change WiFi power save mode (%s)\n", description);
  return false;
}

bool wait_for_sta_connection() {
  uint32_t started_at = millis();
  while (WiFi.status() != WL_CONNECTED &&
         (uint32_t)(millis() - started_at) < WIFI_STA_CONNECT_TIMEOUT_MS) {
    delay(1000);
    Serial.print(".");
  }
  return WiFi.status() == WL_CONNECTED;
}

bool connect_sta_at_power(wifi_power_t power, const char *label) {
  set_wifi_tx_power(power, label);
  wifi_disconnect_reason_available = false;
  last_wifi_disconnect_reason = WIFI_REASON_UNSPECIFIED;

  wl_status_t begin_status = WiFi.begin(cssid.c_str(), cpass.c_str());
  Serial.printf("WiFi.begin initial status at %s: %d\n", label, begin_status);

  if (wait_for_sta_connection()) {
    Serial.printf("\nSTA connected at %s; RSSI %ld dBm, channel %ld\n",
                  label, (long)WiFi.RSSI(), (long)WiFi.channel());
    return true;
  }

  Serial.println();
  report_sta_connection_failure();
  return false;
}

void apply_idle_sta_power_save() {
  if (!set_sta_power_save(WIFI_PS_MIN_MODEM,
                          "WiFi minimum modem sleep enabled while live stream is idle")) {
    Serial.println("WiFi will remain active without modem sleep");
  }
}

void apply_streaming_sta_power() {
  if (!set_sta_power_save(WIFI_PS_NONE,
                          "WiFi modem sleep disabled for live stream")) {
    Serial.println("Live stream will continue with the current WiFi power-save setting");
  }
}

void apply_initial_ap_power() {
  if (!set_wifi_tx_power(WIFI_TX_POWER_INITIAL, "13 dBm")) {
    Serial.println("AP will continue with the current WiFi TX power");
  }
}

void restore_idle_sta_power_save() {
  if (wifi_mode == RECORDER_WIFI_STA && WiFi.status() == WL_CONNECTED) {
    if (WiFi.setSleep(WIFI_PS_MIN_MODEM)) {
      Serial.println("WiFi minimum modem sleep restored after live stream");
    } else {
      Serial.println("WARNING: Failed to restore WiFi minimum modem sleep");
    }
  }
}

bool init_wifi() {
  if (wifi_mode == RECORDER_WIFI_OFF) {
    stop_wifi_completely();
    return false;
  }

  if (wifi_mode == RECORDER_WIFI_STA) {
    if (cssid.length() == 0 || cssid.length() > 32 || cpass.length() > 64) {
      Serial.println("Invalid STA SSID or password length");
      stop_wifi_completely();
      return false;
    }

    WiFi.disconnect(true, false);
    WiFi.setHostname(devname);
    register_wifi_diagnostics();
    if (!WiFi.mode(WIFI_STA) || !wait_for_wifi_interface_start(true)) {
      Serial.println("Failed to start the WiFi STA interface");
      stop_wifi_completely();
      return false;
    }

    // Keep the radio awake while authenticating. Idle modem sleep is enabled
    // only after the STA has connected successfully.
    WiFi.setSleep(WIFI_PS_NONE);

    if (wifi_ip_mode == 1) {
      IPAddress static_ip;
      IPAddress gateway;
      IPAddress subnet;
      IPAddress dns;
      if (!static_ip.fromString(cstaticip) || !gateway.fromString(cgateway) ||
          !subnet.fromString(csubnet) || !dns.fromString(configured_dns)) {
        Serial.println("Invalid static IPv4 configuration");
        stop_wifi_completely();
        return false;
      }
      if (!WiFi.config(static_ip, gateway, subnet, dns)) {
        Serial.println("Failed to apply static IPv4 configuration");
        stop_wifi_completely();
        return false;
      }
    }

    Serial.printf("Connecting to STA SSID >%s<\n", cssid.c_str());
    bool connected = connect_sta_at_power(WIFI_TX_POWER_INITIAL, "13 dBm");

    if (!connected) {
      Serial.println("Retrying STA connection with 15 dBm TX power");
      WiFi.disconnect(false, false);
      delay(WIFI_POWER_STAGE_DELAY_MS);
      connected = connect_sta_at_power(WIFI_TX_POWER_FALLBACK, "15 dBm");
    }

    if (!connected) {
      stop_wifi_completely();
      return false;
    }

    apply_idle_sta_power_save();

    configTime(0, 0, "pool.ntp.org");
    char tzchar[60];

    snprintf(tzchar, sizeof(tzchar), "%s", TIMEZONE.c_str());
    Serial.printf("Char >%s<\n", tzchar);
    setenv("TZ", tzchar, 1);
    tzset();

    time(&now);

    int timeAttempts = 0;
    while (now < 15 && timeAttempts++ < 15) {
      delay(1000);
      Serial.print("o");
      time(&now);
    }

    Serial.print("\nLocal time: "); Serial.print(ctime(&now));
    sprintf(localip, "%s", WiFi.localIP().toString().c_str());
    Serial.print("IP: "); Serial.println(localip); Serial.println(" ");
    InternetOff = false;
  } else if (wifi_mode == RECORDER_WIFI_AP) {
    if (cssid.length() == 0 || cssid.length() > 32 ||
        cpass.length() < 8 || cpass.length() > 63) {
      Serial.println("AP SSID must be 1-32 characters and password 8-63 characters");
      stop_wifi_completely();
      return false;
    }

    Serial.printf("Setting AP with SSID >%s<\n", cssid.c_str());
    WiFi.disconnect(true, false);
    WiFi.setHostname(devname);
    if (!WiFi.mode(WIFI_MODE_AP) || !wait_for_wifi_interface_start(false)) {
      Serial.println("Failed to start the WiFi AP interface");
      stop_wifi_completely();
      return false;
    }
    apply_initial_ap_power();

    IPAddress ap_ip(192, 168, 4, 1);
    IPAddress ap_gateway(192, 168, 4, 1);
    IPAddress ap_subnet(255, 255, 255, 0);
    if (!WiFi.softAPConfig(ap_ip, ap_gateway, ap_subnet) ||
        !WiFi.softAP(cssid.c_str(), cpass.c_str())) {
      Serial.println("Failed to start AP");
      stop_wifi_completely();
      return false;
    }

    IPAddress IP = WiFi.softAPIP();
    Serial.print("AP IP address: ");
    Serial.println(IP);

    sprintf(localip, "%s", WiFi.softAPIP().toString().c_str());
    Serial.print("IP: "); Serial.println(localip); Serial.println(" ");
    InternetOff = false;
  }

  if (!MDNS.begin(devname)) {
    Serial.println("Error setting up MDNS responder!");
  } else {
    MDNS.addService("http", "tcp", 80);
    Serial.printf("mDNS responder started: http://%s.local/\n", devname);
  }

  if (wifi_mode == RECORDER_WIFI_STA) {
    wifi_ps_type_t power_save_type;
    if (esp_wifi_get_ps(&power_save_type) == ESP_OK) {
      Serial.printf("WiFi power save mode: %d (1 = minimum modem sleep)\n", power_save_type);
    }
  }

  return true;
}

bool init_wifi_with_power_staging() {
  uint32_t previous_cpu_mhz = getCpuFrequencyMhz();
  bool cpu_frequency_reduced = false;

  if (previous_cpu_mhz > 80) {
    cpu_frequency_reduced = setCpuFrequencyMhz(80);
    if (cpu_frequency_reduced) {
      Serial.printf("CPU frequency temporarily reduced: %u -> 80 MHz\n", previous_cpu_mhz);
    } else {
      Serial.println("WARNING: Failed to reduce CPU frequency for WiFi startup");
    }
  }

  delay(WIFI_POWER_STAGE_DELAY_MS);
  bool success = init_wifi();
  delay(WIFI_POWER_STAGE_DELAY_MS);

  if (cpu_frequency_reduced) {
    if (setCpuFrequencyMhz(previous_cpu_mhz)) {
      Serial.printf("CPU frequency restored to %u MHz\n", previous_cpu_mhz);
    } else {
      Serial.printf("WARNING: Failed to restore CPU frequency to %u MHz\n", previous_cpu_mhz);
    }
  }

  delay(WIFI_POWER_STAGE_DELAY_MS);
  return success;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
//
#include <HTTPClient.h>

httpd_handle_t camera_httpd = NULL;
httpd_handle_t stream_httpd_81 = NULL;

char the_page[4200];

static esp_err_t capture_handler(httpd_req_t *req) {

  long start = millis();

  camera_fb_t * fb = NULL;
  esp_err_t res = ESP_OK;
  char fname[100];
  int file_number = 0;

  //Serial.print("capture, core ");  Serial.print(xPortGetCoreID());
  //Serial.print(", priority = "); Serial.println(uxTaskPriorityGet(NULL));

  file_number++;

  sprintf(fname, "inline; filename=capture_%d.jpg", file_number);

  xSemaphoreTake( baton, portMAX_DELAY );

  if (framebuffer_time > (millis() - 200)) {
    //Serial.printf("*");
    framebuffer3_len = framebuffer_len;
    framebuffer3_time = framebuffer_time;
    memcpy(framebuffer3, framebuffer,  framebuffer_len);  // v59.5
    xSemaphoreGive( baton );
  } else {
    xSemaphoreGive( baton );
    fb = esp_camera_fb_get(); //get_good_jpeg();
    //Serial.println("capp take");
    if (!fb) {
      Serial.println("Photos - Camera Capture Failed");
    } else {
      xSemaphoreTake( baton, portMAX_DELAY );
      framebuffer3_len = fb->len;
      framebuffer3_time = millis();
      memcpy(framebuffer3, fb->buf, fb->len);
      xSemaphoreGive( baton );
      esp_camera_fb_return(fb);
    }
  }

  httpd_resp_set_type(req, "image/jpeg");
  httpd_resp_set_hdr(req, "Content-Disposition", fname);

  res = httpd_resp_send(req, (const char *)framebuffer3, framebuffer3_len);

  time_in_web1 += (millis() - start);

  return res;
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
//
static esp_err_t index_handler(httpd_req_t *req) {

  long start = millis();

  Serial.print("http index, core ");  Serial.print(xPortGetCoreID());
  Serial.print(", priority = "); Serial.println(uxTaskPriorityGet(NULL));

  const char the_message[] = "Status";

  time(&now);
  const char *strdate = ctime(&now);

  int tot =SD.totalBytes() / (1024 * 1024);
  int use =SD.usedBytes() / (1024 * 1024);
  long rssi = WiFi.RSSI();

  const char msg[] PROGMEM = R"rawliteral(<!doctype html>
<html>
<head>
<meta charset="utf-8">
<meta name="viewport" content="width=device-width,initial-scale=1">
<title>%s ESP32-CAM Video Recorder Junior</title>
</head>
<body>
<h1>%s<br>ESP32-CAM Video Recorder Junior %s <br><font color="red">%s</font></h1><br>

 Used / Total SD Space <font color="red"> %d MB / %d MB</font>, Rssi %d<br>

 Filename: %s <br>
 Framesize %d, Quality %d, Frame %d <br>
 Record Interval %dms, Stream Interval %dms <br>
 Avg framesize %d, fps %.1f <br>
 Time left in current video %d seconds<br>

 <h3><a href="http://%s/">http://%s/</a></h3>
 <h3>Streaming</h3>
 <a href="http://%s:81/stream"><button>Live stream</button></a>
 <h3>Series of pictures</h3>
 <a href="http://%s/photos"><button>10 x 3 sec</button> </a>
 <a href="http://%s/fphotos"><button>10 x 1 sec</button></a>
 <a href="http://%s/sphotos"><button>120 x 15 sec</button></a> 
 <h4><a href="http://%s:%d"><button>File Manager - download, delete, edit config.txt </button></a></h4>
 <div id="image-container"></div>
 <h4><a href="http://%s/restart"><button>End recording, and start new video (write the index) </button></a></h4>
 <h4><a href="http://%s/reboot"><button>End recording, and reboot (using new settings)</button> </a></h4>
 <br>
SourceCode:  https://github.com/jameszah/ESP32-CAM-Video-Recorder-junior/<br>
One-Click Installer: https://jameszah.github.io/ESP32-CAM-VideoCam/<br>
James Zahary - May 18, 2022<br>
<a href="https://ko-fi.com/jameszah">Free coffee (not AP mode)</a>
<script>
document.addEventListener('DOMContentLoaded', function() {
  var c = document.location.origin;
    const ic = document.getElementById('image-container'); 
  const x =  new Date();
  var timing = x.getTime() / 1000;
  
  ic.insertAdjacentHTML('beforeend','<a href="http://%s/time?time='+timing+'">Send time to camera (in AP mode) ==>   </a>') 
  ic.insertAdjacentHTML('beforeend',Date())
  ic.insertAdjacentHTML('beforeend','<br>')
})
</script>
<br>
</body>
</html>)rawliteral";

  int time_left = (- millis() +  (avi_start_time + avi_length * 1000)) / 1000;
  if (start_record == 0) {
    time_left = 0;
  }

  sprintf(the_page, msg, devname, devname, vernum, strdate, use, tot, rssi, avi_file_name,
          framesize, quality, frame_cnt, frame_interval, stream_delay,
          most_recent_avg_framesize, most_recent_fps, time_left,
          localip, localip,
          localip,
          localip, localip, localip,
          localip, filemanagerport,
          localip, localip, localip);

  httpd_resp_send(req, the_page, strlen(the_page));

  time_in_web1 += (millis() - start);
  return ESP_OK;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
//
static esp_err_t time_handler(httpd_req_t *req) {
  esp_err_t res = ESP_OK;

  char  buf[120];
  size_t buf_len;
  char  new_res[20];
  struct tm timeinfo;
  time_t now;

  buf_len = httpd_req_get_url_query_len(req) + 1;
  if (buf_len > 1) {
    if (httpd_req_get_url_query_str(req, buf, buf_len) == ESP_OK) {
      Serial.printf("Found URL query => %s", buf);
      char param[32];

      if (httpd_query_key_value(buf, "time", param, sizeof(param)) == ESP_OK) {

        now = (time_t)atol(param);
        //Serial.print("new time: "); Serial.println(ctime(&now));
        //Serial.printf(">%i<", now);

        char tzchar[60];
        TIMEZONE.toCharArray(tzchar, TIMEZONE.length() + 1);        // name of your camera for mDNS, Router, and filenames
        setenv("TZ", tzchar, 1);  // mountain time zone from #define at top
        tzset();

        struct timeval tv;
        tv.tv_sec = now;
        tv.tv_usec = 0;
        settimeofday(&tv, NULL);

        time(&now);
        //localtime_r(&now, &timeinfo);
        Serial.print("\nLocal time: "); Serial.println(ctime(&now));

        time_t rawtime;
        struct tm * ptm;
        time ( &rawtime );
        ptm = gmtime ( &rawtime );
        Serial.printf ("GMT: %2d:%02d\n", (ptm->tm_hour) % 24, ptm->tm_min);


      }
    }
  }
  const char the_message[] = "Status";

  time(&now);
  const char *strdate = ctime(&now);

  const char msg[] PROGMEM = R"rawliteral(<!doctype html>
<html>
<head>
<meta charset="utf-8">
<meta name="viewport" content="width=device-width,initial-scale=1">
<title>%s ESP32-CAM Video Recorder Junior</title>
</head>
<body>
<h1>%s<br>ESP32-CAM Video Recorder Junior %s <br><font color="red">%s</font></h1><br>
 <br>
 got a time sync ...
 <br>


</body>
</html>)rawliteral";

  sprintf(the_page, msg, devname, devname, vernum, strdate );

  httpd_resp_send(req, the_page, strlen(the_page));

  return ESP_OK;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
//
static esp_err_t photos_handler(httpd_req_t *req) {

  long start = millis();

  Serial.print("http photos, core ");  Serial.print(xPortGetCoreID());
  Serial.print(", priority = "); Serial.println(uxTaskPriorityGet(NULL));
  //Serial.printf("Internal Total heap %d, internal Free Heap %d\n", ESP.getHeapSize(), ESP.getFreeHeap());
  //Serial.printf("SPIRam Total heap   %d, SPIRam Free Heap   %d\n", ESP.getPsramSize(), ESP.getFreePsram());

  const char the_message[] = "Status";

  time(&now);
  const char *strdate = ctime(&now);

  const char msg[] PROGMEM = R"rawliteral(<!doctype html>
<html>
<head>
<meta charset="utf-8">
<meta name="viewport" content="width=device-width,initial-scale=1">
<title>%s ESP32-CAM Video Recorder Junior</title>
</head>
<body>
<h1>%s<br>ESP32-CAM Video Recorder Junior %s <br><font color="red">%s</font></h1><br>
 <br>
 One photo every 3 seconds for 30 seconds - roll forward or back - refresh for more live photos
 <br>

<br><div id="image-container"></div>
<script>
document.addEventListener('DOMContentLoaded', function() {
  var c = document.location.origin;
  const ic = document.getElementById('image-container');  
  var i = 1;
  
  var timing = 3000; // time between snapshots for multiple shots

  function loop() {
    ic.insertAdjacentHTML('beforeend','<img src="'+`${c}/capture?_cb=${Date.now()}`+'">')
    ic.insertAdjacentHTML('beforeend','<br>')
    ic.insertAdjacentHTML('beforeend',Date())
    ic.insertAdjacentHTML('beforeend','<br>')

    i = i + 1;
    if ( i <= 10 ) {             // 10 frames
      window.setTimeout(loop, timing);
    }
  }
  loop();
  
})
</script><br>
</body>
</html>)rawliteral";

  sprintf(the_page, msg, devname, devname, vernum, strdate );

  httpd_resp_send(req, the_page, strlen(the_page));
  time_in_web1 += (millis() - start);
  return ESP_OK;
}

static esp_err_t fphotos_handler(httpd_req_t *req) {

  long start = millis();

  Serial.print("http photos, core ");  Serial.print(xPortGetCoreID());
  Serial.print(", priority = "); Serial.println(uxTaskPriorityGet(NULL));
  //Serial.printf("Internal Total heap %d, internal Free Heap %d\n", ESP.getHeapSize(), ESP.getFreeHeap());
  //Serial.printf("SPIRam Total heap   %d, SPIRam Free Heap   %d\n", ESP.getPsramSize(), ESP.getFreePsram());

  const char the_message[] = "Status";

  time(&now);
  const char *strdate = ctime(&now);

  const char msg[] PROGMEM = R"rawliteral(<!doctype html>
<html>
<head>
<meta charset="utf-8">
<meta name="viewport" content="width=device-width,initial-scale=1">
<title>%s ESP32-CAM Video Recorder Junior</title>
</head>
<body>
<h1>%s<br>ESP32-CAM Video Recorder Junior %s <br><font color="red">%s</font></h1><br>
 <br>
 One photo every 1 seconds for 10 seconds - roll forward or back - refresh for more live photos
 <br>

<br><div id="image-container"></div>
<script>
document.addEventListener('DOMContentLoaded', function() {
  var c = document.location.origin;
  const ic = document.getElementById('image-container');  
  var i = 1;
  
  var timing = 1000; // time between snapshots for multiple shots

  function loop() {
    ic.insertAdjacentHTML('beforeend','<img src="'+`${c}/capture?_cb=${Date.now()}`+'">')
    ic.insertAdjacentHTML('beforeend','<br>')
    ic.insertAdjacentHTML('beforeend',Date())
    ic.insertAdjacentHTML('beforeend','<br>')

    i = i + 1;
    if ( i <= 10 ) {             // 10 frames
      window.setTimeout(loop, timing);
    }
  }
  loop();
  
})
</script><br>
</body>
</html>)rawliteral";

  sprintf(the_page, msg, devname, devname, vernum, strdate );

  httpd_resp_send(req, the_page, strlen(the_page));
  time_in_web1 += (millis() - start);
  return ESP_OK;
}

static esp_err_t sphotos_handler(httpd_req_t *req) {

  long start = millis();

  Serial.print("http photos, core ");  Serial.print(xPortGetCoreID());
  Serial.print(", priority = "); Serial.println(uxTaskPriorityGet(NULL));
  //Serial.printf("Internal Total heap %d, internal Free Heap %d\n", ESP.getHeapSize(), ESP.getFreeHeap());
  //Serial.printf("SPIRam Total heap   %d, SPIRam Free Heap   %d\n", ESP.getPsramSize(), ESP.getFreePsram());

  const char the_message[] = "Status";

  time(&now);
  const char *strdate = ctime(&now);

  const char msg[] PROGMEM = R"rawliteral(<!doctype html>
<html>
<head>
<meta charset="utf-8">
<meta name="viewport" content="width=device-width,initial-scale=1">
<title>%s ESP32-CAM Video Recorder Junior</title>
</head>
<body>
<h1>%s<br>ESP32-CAM Video Recorder Junior %s <br><font color="red">%s</font></h1><br>
 <br>
 One photo every 15 seconds for 30 minutes - roll forward or back - refresh for more live photos
 <br>

<br><div id="image-container"></div>
<script>
document.addEventListener('DOMContentLoaded', function() {
  var c = document.location.origin;
  const ic = document.getElementById('image-container');  
  var i = 1;
  
  var timing = 15000; // time between snapshots for multiple shots

  function loop() {
    ic.insertAdjacentHTML('beforeend','<img src="'+`${c}/capture?_cb=${Date.now()}`+'">')
    ic.insertAdjacentHTML('beforeend','<br>')
    ic.insertAdjacentHTML('beforeend',Date())
    ic.insertAdjacentHTML('beforeend','<br>')

    i = i + 1;
    if ( i <= 120 ) {             
      window.setTimeout(loop, timing);
    }
  }
  loop();
  
})
</script><br>
</body>
</html>)rawliteral";

  sprintf(the_page, msg, devname, devname, vernum, strdate );

  httpd_resp_send(req, the_page, strlen(the_page));
  time_in_web1 += (millis() - start);
  return ESP_OK;
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
//
static esp_err_t reboot_handler(httpd_req_t *req) {

  long start = millis();

  Serial.print("http reboot, core ");  Serial.print(xPortGetCoreID());
  Serial.print(", priority = "); Serial.println(uxTaskPriorityGet(NULL));
  //Serial.printf("Internal Total heap %d, internal Free Heap %d\n", ESP.getHeapSize(), ESP.getFreeHeap());
  //Serial.printf("SPIRam Total heap   %d, SPIRam Free Heap   %d\n", ESP.getPsramSize(), ESP.getFreePsram());

  reboot_now = true;

  const char the_message[] = "Status";

  time(&now);
  const char *strdate = ctime(&now);

  const char msg[] PROGMEM = R"rawliteral(<!doctype html>
<html>
<head>
<meta charset="utf-8">
<meta name="viewport" content="width=device-width,initial-scale=1">
<title>%s ESP32-CAM Video Recorder Junior</title>
</head>
<body>
<h1>%s<br>ESP32-CAM Video Recorder Junior %s <br><font color="red">%s</font></h1><br>
 <br>
 Ending current recording, and rebooting ...
 <br>

<br>
</body>
</html>)rawliteral";

  sprintf(the_page, msg, devname, devname, vernum, strdate );

  httpd_resp_send(req, the_page, strlen(the_page));
  time_in_web1 += (millis() - start);

  return ESP_OK;
}

static esp_err_t restart_handler(httpd_req_t *req) {

  long start = millis();

  Serial.print("http restart, core ");  Serial.print(xPortGetCoreID());
  Serial.print(", priority = "); Serial.println(uxTaskPriorityGet(NULL));
  //Serial.printf("Internal Total heap %d, internal Free Heap %d\n", ESP.getHeapSize(), ESP.getFreeHeap());
  //Serial.printf("SPIRam Total heap   %d, SPIRam Free Heap   %d\n", ESP.getPsramSize(), ESP.getFreePsram());

  restart_now = true;

  const char the_message[] = "Status";

  time(&now);
  const char *strdate = ctime(&now);

  const char msg[] PROGMEM = R"rawliteral(<!doctype html>
<html>
<head>
<meta charset="utf-8">
<meta name="viewport" content="width=device-width,initial-scale=1">
<title>%s ESP32-CAM Video Recorder Junior</title>
</head>
<body>
<h1>%s<br>ESP32-CAM Video Recorder Junior %s <br><font color="red">%s</font></h1><br>
 <br>
 Ending current recording, and starting next video ...
 <br>
<br>
</body>
</html>)rawliteral";

  sprintf(the_page, msg, devname, devname, vernum, strdate );

  httpd_resp_send(req, the_page, strlen(the_page));
  time_in_web1 += (millis() - start);

  return ESP_OK;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
//  Streaming stuff based on Random Nerd
//

volatile bool stream_81 = false;
volatile bool stream_frame_needed = false;
volatile uint32_t stream_frame_sequence = 0;

#define PART_BOUNDARY "123456789000000000000987654321"

static const char* _STREAM_CONTENT_TYPE = "multipart/x-mixed-replace;boundary=" PART_BOUNDARY;
static const char* _STREAM_BOUNDARY = "\r\n--" PART_BOUNDARY "\r\n";
static const char* _STREAM_PART = "Content-Type: image/jpeg\r\nContent-Length: %u\r\n\r\n";
const uint32_t STREAM_FRAME_WAIT_TIMEOUT_MS = 2000;
const uint16_t STREAM_SEND_TIMEOUT_SECONDS = 5;

void copy_frame_for_active_stream(camera_fb_t *frame) {
  if (!stream_81 || !stream_frame_needed || frame == NULL) return;

  if (frame->len > WEB_FRAMEBUFFER_CAPACITY) {
    Serial.printf("Stream frame too large: %u > %u bytes\n",
                  (unsigned int)frame->len,
                  (unsigned int)WEB_FRAMEBUFFER_CAPACITY);
    stream_frame_needed = false;
    return;
  }

  xSemaphoreTake(baton, portMAX_DELAY);
  if (stream_81 && stream_frame_needed) {
    framebuffer_len = frame->len;
    memcpy(framebuffer, frame->buf, frame->len);
    framebuffer_time = millis();
    stream_frame_sequence++;
    stream_frame_needed = false;
  }
  xSemaphoreGive(baton);
}

bool copy_next_stream_frame(uint32_t previous_sequence,
                            uint32_t *copied_sequence,
                            size_t *copied_length) {
  uint32_t wait_started_at = millis();

  while (stream_81 && !safe_stop_requested &&
         (uint32_t)(millis() - wait_started_at) < STREAM_FRAME_WAIT_TIMEOUT_MS) {
    bool copied = false;

    xSemaphoreTake(baton, portMAX_DELAY);
    if (stream_frame_sequence != previous_sequence &&
        framebuffer_len > 0 &&
        (size_t)framebuffer_len <= WEB_FRAMEBUFFER_CAPACITY) {
      *copied_length = framebuffer_len;
      memcpy(framebuffer2, framebuffer, *copied_length);
      *copied_sequence = stream_frame_sequence;
      copied = true;
    }
    xSemaphoreGive(baton);

    if (copied) return true;
    delay(10);
  }

  return false;
}

esp_err_t send_stream_chunk(httpd_req_t *req,
                            const char *data,
                            size_t length,
                            const char *stage) {
  uint32_t send_started_at = millis();
  errno = 0;
  esp_err_t result = httpd_resp_send_chunk(req, data, length);
  int socket_errno = errno;
  if (result != ESP_OK) {
    int32_t rssi = wifi_mode == RECORDER_WIFI_STA && WiFi.status() == WL_CONNECTED
                     ? WiFi.RSSI()
                     : 0;
    Serial.printf("Live stream %s send failed: 0x%x (%s), %u bytes after %u ms; errno=%d (%s)",
                  stage,
                  result,
                  esp_err_to_name(result),
                  (unsigned int)length,
                  (unsigned int)(millis() - send_started_at),
                  socket_errno,
                  socket_errno == 0 ? "not reported" : strerror(socket_errno));
    if (rssi != 0) Serial.printf(", RSSI %ld dBm", (long)rssi);
    Serial.println();
  }
  return result;
}

static esp_err_t stream_81_handler(httpd_req_t *req) {
  if (stream_81) {
    httpd_resp_set_status(req, "503 Service Unavailable");
    httpd_resp_set_type(req, "text/plain");
    httpd_resp_set_hdr(req, "Retry-After", "2");
    httpd_resp_sendstr(req, "A live-stream client is already connected.\n");
    return ESP_OK;
  }

  Serial.print("live stream handler, core ");  Serial.print(xPortGetCoreID());
  Serial.print(", priority = "); Serial.println(uxTaskPriorityGet(NULL));

  const uint32_t handler_started_at = millis();
  uint32_t stream_frames = 0;
  uint32_t last_sequence;
  int socket_fd = httpd_req_to_sockfd(req);
  esp_err_t result = ESP_OK;

  xSemaphoreTake(baton, portMAX_DELAY);
  last_sequence = stream_frame_sequence;
  xSemaphoreGive(baton);

  stream_81 = true;
  stream_frame_needed = true;
  apply_streaming_sta_power();

  result = httpd_resp_set_type(req, _STREAM_CONTENT_TYPE);
  if (result == ESP_OK) result = httpd_resp_set_hdr(req, "Cache-Control", "no-store, no-cache, must-revalidate");
  if (result == ESP_OK) result = httpd_resp_set_hdr(req, "Pragma", "no-cache");

  while (result == ESP_OK && stream_81 && !safe_stop_requested) {
    size_t jpg_length = 0;
    uint32_t copied_sequence = last_sequence;

    if (!copy_next_stream_frame(last_sequence, &copied_sequence, &jpg_length)) {
      if (stream_81 && !safe_stop_requested) {
        Serial.println("Live stream frame wait timed out; waiting for the next camera frame");
        stream_frame_needed = true;
      }
      continue;
    }

    last_sequence = copied_sequence;
    char part_buffer[96];
    size_t part_length = snprintf(part_buffer, sizeof(part_buffer), _STREAM_PART, jpg_length);
    uint32_t send_started_at = millis();

    result = send_stream_chunk(req, _STREAM_BOUNDARY, strlen(_STREAM_BOUNDARY), "boundary");
    if (result == ESP_OK) result = send_stream_chunk(req, part_buffer, part_length, "header");
    if (result == ESP_OK) {
      result = send_stream_chunk(req, (const char *)framebuffer2, jpg_length, "JPEG");
    }

    if (result != ESP_OK) break;

    stream_frames++;
    if (Lots_of_Stats && stream_frames % 100 == 10) {
      float stream_fps = 1000.0f * stream_frames / (millis() - handler_started_at);
      Serial.printf("Live stream at %.2f fps\n", stream_fps);
    }

    uint32_t send_elapsed = millis() - send_started_at;
    int32_t remaining_delay = stream_delay - (int32_t)send_elapsed;
    delay(remaining_delay > 10 ? remaining_delay : 10);

    // Request one new camera frame only after the previous frame has been sent.
    // Slow clients therefore drop intermediate frames instead of building a queue.
    stream_frame_needed = true;
  }

  stream_frame_needed = false;
  stream_81 = false;
  restore_idle_sta_power_save();

  if (result == ESP_OK) {
    httpd_resp_send_chunk(req, NULL, 0);
  } else if (socket_fd >= 0) {
    httpd_sess_trigger_close(req->handle, socket_fd);
  }

  time_in_web1 += millis() - handler_started_at;
  Serial.printf("Live stream closed after %u frames\n", stream_frames);
  return result;
}

void start_Stream_81_server() {
  if (stream_httpd_81 != NULL) return;

  httpd_config_t config2 = HTTPD_DEFAULT_CONFIG();
  config2.server_port = 81;
  config2.ctrl_port = 32123; //         = 32768,
  config2.stack_size = 6144;
  config2.backlog_conn = 1;
  config2.lru_purge_enable = true;
  config2.recv_wait_timeout = STREAM_SEND_TIMEOUT_SECONDS;
  config2.send_wait_timeout = STREAM_SEND_TIMEOUT_SECONDS;
  Serial.print("http Stream task prio: "); Serial.println(config2.task_priority);

  httpd_uri_t stream_uri = {
    .uri       = "/stream",
    .method    = HTTP_GET,
    .handler   = stream_81_handler,
    .user_ctx  = NULL
  };

  if (httpd_start(&stream_httpd_81, &config2) == ESP_OK) {
    httpd_register_uri_handler(stream_httpd_81, &stream_uri);
    Serial.println("Live stream http started on port 81 (one client, 5 second send timeout)");
  } else {
    Serial.println("Error with stream start 81");
  }
}

////////////////////////////////

void startCameraServer() {
  if (camera_httpd != NULL) return;

  httpd_config_t config = HTTPD_DEFAULT_CONFIG();
  config.max_uri_handlers = 8;
  config.stack_size = 4096 + 1024;

  Serial.print("http task prio: "); Serial.println(config.task_priority);

  httpd_uri_t index_uri = {
    .uri       = "/",
    .method    = HTTP_GET,
    .handler   = index_handler,
    .user_ctx  = NULL
  };
  httpd_uri_t capture_uri = {
    .uri       = "/capture",
    .method    = HTTP_GET,
    .handler   = capture_handler,
    .user_ctx  = NULL
  };
  //  httpd_uri_t stream_uri = {
  //    .uri       = "/stream",
  //    .method    = HTTP_GET,
  //    .handler   = stream_handler,
  //    .user_ctx  = NULL
  //  };

  httpd_uri_t photos_uri = {
    .uri       = "/photos",
    .method    = HTTP_GET,
    .handler   = photos_handler,
    .user_ctx  = NULL
  };

  httpd_uri_t fphotos_uri = {
    .uri       = "/fphotos",
    .method    = HTTP_GET,
    .handler   = fphotos_handler,
    .user_ctx  = NULL
  };

  httpd_uri_t sphotos_uri = {
    .uri       = "/sphotos",
    .method    = HTTP_GET,
    .handler   = sphotos_handler,
    .user_ctx  = NULL
  };

  httpd_uri_t reboot_uri = {
    .uri       = "/reboot",
    .method    = HTTP_GET,
    .handler   = reboot_handler,
    .user_ctx  = NULL
  };

  httpd_uri_t restart_uri = {
    .uri       = "/restart",
    .method    = HTTP_GET,
    .handler   = restart_handler,
    .user_ctx  = NULL
  };

  httpd_uri_t time_uri = {
    .uri       = "/time",
    .method    = HTTP_GET,
    .handler   = time_handler,
    .user_ctx  = NULL
  };

  if (httpd_start(&camera_httpd, &config) == ESP_OK) {
    httpd_register_uri_handler(camera_httpd, &index_uri);
    httpd_register_uri_handler(camera_httpd, &capture_uri);
    //    httpd_register_uri_handler(camera_httpd, &stream_uri);
    httpd_register_uri_handler(camera_httpd, &photos_uri);
    httpd_register_uri_handler(camera_httpd, &fphotos_uri);
    httpd_register_uri_handler(camera_httpd, &sphotos_uri);
    httpd_register_uri_handler(camera_httpd, &reboot_uri);
    httpd_register_uri_handler(camera_httpd, &restart_uri);
    httpd_register_uri_handler(camera_httpd, &time_uri);
  }

  Serial.println("Camera http started");
}

void stopCameraServer() {
  stream_81 = false;
  stream_frame_needed = false;

  if (camera_httpd != NULL) {
    httpd_stop(camera_httpd);
    camera_httpd = NULL;
  }
  if (stream_httpd_81 != NULL) {
    httpd_stop(stream_httpd_81);
    stream_httpd_81 = NULL;
  }
}

void the_camera_loop (void* pvParameter);
void the_sd_loop (void* pvParameter);
void delete_old_stuff();


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

int delete_old_stuff_flag = 0;

const int lightSensorPin = 4; // 6 照度センサーを接続したGPIOピンをD8/A8 (GPIO7)に変更 // 照度センサーを接続したGPIOピン追加
const int GPIOGNDPin = 5;
const int GPIOVPin = 6;
const int SAFE_STOP_BUTTON_PIN = 0;       // XIAO ESP32S3 Sense BOOT button
const uint32_t SAFE_STOP_HOLD_MS = 1500;

bool safe_stop_button_pressed = false;
bool safe_stop_button_latched = false;
uint32_t safe_stop_button_pressed_at = 0;
bool safe_stop_led_on = false;
uint32_t safe_stop_led_changed_at = 0;

long wakeup;
long last_wakeup = 0;

void poll_safe_stop_button() {
  bool pressed = digitalRead(SAFE_STOP_BUTTON_PIN) == LOW;

  if (!pressed) {
    safe_stop_button_pressed = false;
    return;
  }

  if (!safe_stop_button_pressed) {
    safe_stop_button_pressed = true;
    safe_stop_button_pressed_at = millis();
    return;
  }

  if (!safe_stop_button_latched &&
      (uint32_t)(millis() - safe_stop_button_pressed_at) >= SAFE_STOP_HOLD_MS) {
    safe_stop_button_latched = true;
    safe_stop_requested = true;
    Serial.println("BOOT held for 1.5 seconds: finishing the current AVI and safely unmounting the SD card.");
  }
}

void close_file_for_safe_shutdown(File &file) {
  if (file) {
    file.flush();
    file.close();
  }
}

void perform_safe_sd_shutdown() {
  Serial.println("Finalizing files and unmounting the SD card ...");
  if (logfile) {
    logfile.println("Safe stop: finalizing files and unmounting the SD card.");
    logfile.flush();
  }

  // The camera task has already finished end_avi() before setting
  // recording_closed_for_shutdown. These first two closes are defensive.
  close_file_for_safe_shutdown(avifile);
  close_file_for_safe_shutdown(idxfile);
  close_file_for_safe_shutdown(timestampFile);
  close_file_for_safe_shutdown(illuminanceFile);
  close_file_for_safe_shutdown(logfile);
  SD.end();

  digitalWrite(GPIOGNDPin, LOW);
  digitalWrite(GPIOVPin, HIGH);
  safe_stop_led_on = true;
  safe_stop_led_changed_at = millis();
  safe_stop_complete = true;
  Serial.println("SD card unmounted. Slow LED blink means it is safe to remove power.");
}

void park_camera_for_safe_shutdown() {
  recording_closed_for_shutdown = true;
  while (!safe_stop_complete) {
    vTaskDelay(pdMS_TO_TICKS(20));
  }
  vTaskDelete(NULL);
}

bool wifi_switch_requests_on() {
  int first_sample = digitalRead(44);
  delay(20);
  int second_sample = digitalRead(44);
  return first_sample == HIGH && second_sample == HIGH;
}

void setup() {

  Serial.begin(115200);
  Serial.println("\n\n---");

  //pinMode(21, OUTPUT);             // little red led on back of chip をGPIO21に変更
  //digitalWrite(21, LOW); // turn on the red LED on the back of chip

  //pinMode(4, OUTPUT); // Blinding Disk-Avtive Light はカメラピンとの競合を避けるためコメントアウト
  //digitalWrite(4, LOW);             // turn off

// ★ 録画中LEDピン (GPIO 2) の設定 ★以下２行追加
  //pinMode(RecordingLED, OUTPUT);
  //digitalWrite(RecordingLED, LOW); // 初期状態は消灯 (LOWで消灯と仮定)
  pinMode(GPIOGNDPin, OUTPUT);
  digitalWrite(GPIOGNDPin, LOW); // 初期状態は消灯 (LOWで消灯と仮定)
  pinMode(GPIOVPin, OUTPUT);
  digitalWrite(GPIOVPin, LOW); // 初期状態は消灯 (LOWで消灯と仮定)
  pinMode(SAFE_STOP_BUTTON_PIN, INPUT_PULLUP);

  pinMode(43, INPUT_PULLUP); // pull this down to stop recording をGPIO43に変更
  pinMode(44, INPUT_PULLUP);        // pull this down switch wifi をGPIO44に変更

  //Serial.setDebugOutput(true);

  Serial.println("                                    ");
  Serial.println("-------------------------------------");
  Serial.printf("ESP32-CAM-Video-Recorder-junior %s\n", vernum);
  #ifdef ESP_ARDUINO_VERSION_STR
  Serial.printf("ESP32 Arduino core: %s\n", ESP_ARDUINO_VERSION_STR);
  #else
  Serial.println("ESP32 Arduino core: unknown");
  #endif
  Serial.println("-------------------------------------");

  Serial.print("setup, core ");  Serial.print(xPortGetCoreID());
  Serial.print(", priority = "); Serial.println(uxTaskPriorityGet(NULL));

  esp_reset_reason_t reason = esp_reset_reason();

  logfile.print("--- reboot ------ because: ");
  Serial.print("--- reboot ------ because: ");

  switch (reason) {
    case ESP_RST_UNKNOWN : Serial.println("ESP_RST_UNKNOWN"); logfile.println("ESP_RST_UNKNOWN"); break;
    case ESP_RST_POWERON : Serial.println("ESP_RST_POWERON"); logfile.println("ESP_RST_POWERON"); break;
    case ESP_RST_EXT : Serial.println("ESP_RST_EXT"); logfile.println("ESP_RST_EXT"); break;
    case ESP_RST_SW : Serial.println("ESP_RST_SW"); logfile.println("ESP_RST_SW"); break;
    case ESP_RST_PANIC : Serial.println("ESP_RST_PANIC"); logfile.println("ESP_RST_PANIC"); break;
    case ESP_RST_INT_WDT : Serial.println("ESP_RST_INT_WDT"); logfile.println("ESP_RST_INT_WDT"); break;
    case ESP_RST_TASK_WDT : Serial.println("ESP_RST_TASK_WDT"); logfile.println("ESP_RST_TASK_WDT"); break;
    case ESP_RST_WDT : Serial.println("ESP_RST_WDT"); logfile.println("ESP_RST_WDT"); break;
    case ESP_RST_DEEPSLEEP : Serial.println("ESP_RST_DEEPSLEEP"); logfile.println("ESP_RST_DEEPSLEEP"); break;
    case ESP_RST_BROWNOUT : Serial.println("ESP_RST_BROWNOUT"); logfile.println("ESP_RST_BROWNOUT"); break;
    case ESP_RST_SDIO : Serial.println("ESP_RST_SDIO"); logfile.println("ESP_RST_SDIO"); break;
    default  : Serial.println("Reset resaon"); logfile.println("ESP ???"); break;
  }

  //Serial.printf("Internal Total heap %d, internal Free Heap %d\n", ESP.getHeapSize(), ESP.getFreeHeap());
  //Serial.printf("SPIRam Total heap   %d, SPIRam Free Heap   %d\n", ESP.getPsramSize(), ESP.getFreePsram());


  do_eprom_read();

  // SD camera init
  Serial.println("Mounting the SD card ...");
  esp_err_t card_err = init_sdcard();
  if (card_err != ESP_OK) {
    Serial.printf("SD Card init failed with error 0x%x", card_err);
    major_fail();
    return;
  }

  devstr.toCharArray(devname, devstr.length());          // name of your camera for mDNS, Router, and filenames

  Serial.println("Try to get parameters from config.txt ...");

  read_config_file();

  bool wifi_requested_at_startup =
    wifi_mode != RECORDER_WIFI_OFF && wifi_switch_requests_on();

  if (reason == ESP_RST_BROWNOUT && wifi_mode != RECORDER_WIFI_OFF) {
    wifi_suppressed_after_brownout = true;
    Serial.println("Brownout recovery: WiFi is disabled for this boot to prevent a reset loop");
    stop_wifi_completely();
  } else if (wifi_requested_at_startup) {
    Serial.println("Starting WiFi before camera initialization with power staging ...");
    if (!init_wifi_with_power_staging()) {
      Serial.println("Startup WiFi failed; recording will continue with WiFi off");
    }
  } else {
    stop_wifi_completely();
  }

  // Persist the file group only after the high-current WiFi startup phase.
  // A WiFi brownout therefore cannot write EEPROM on every reboot attempt.
  do_eprom_write();

  char logname[50];
  sprintf(logname, "/%s%04d.999.txt",  devname, file_group);
  Serial.printf("Creating logfile %s\n",  logname);
  logfile = SD.open(logname, FILE_WRITE);

  //追加
  //char timestampname[50];
  char timestampname[100];
  //sprintf(timestampname, "/%s%d.time.csv",  devname, file_group);
  sprintf(timestampname, "/%s%04d.%03d.time.csv",  devname, file_group, file_number);
  Serial.printf("Creating timestampFile %s\n",  timestampname);
  timestampFile = SD.open(timestampname, FILE_WRITE);
  if (!timestampFile) {
    Serial.println("Failed to open timestamp file");
  } else {
    timestampFile.println("frame_number,timestamp_ms");
    //timestampFile.close();
  }
//追加
  char illuminancename[100];
  sprintf(illuminancename, "/%s%04d.%03d.illuminance.csv",  devname, file_group, file_number);
  Serial.printf("Creating illuminanceFile %s\n",  illuminancename);
  illuminanceFile = SD.open(illuminancename, FILE_WRITE);
  if (!illuminanceFile) {
    Serial.println("Failed to open illuminance file");
  } else {
    illuminanceFile.println("frame_number,illuminance");
  }


  if (!logfile) {
    Serial.println("Failed to open logfile for writing");
  } else {
    #ifdef ESP_ARDUINO_VERSION_STR
    logfile.printf("ESP32 Arduino core: %s\n", ESP_ARDUINO_VERSION_STR);
    #else
    logfile.println("ESP32 Arduino core: unknown");
    #endif
    if (reason == ESP_RST_BROWNOUT) {
      logfile.println("Reset reason: ESP_RST_BROWNOUT");
    }
    if (wifi_suppressed_after_brownout) {
      logfile.println("Brownout recovery: WiFi disabled for this boot");
    }
  }
  Serial.println("Setting up the camera ...");
  config_camera();

  Serial.println("Checking SD for available space ...");
  delete_old_stuff();
  framebuffer = (uint8_t*)ps_malloc(WEB_FRAMEBUFFER_CAPACITY); // latest camera frame for Web clients
  framebuffer2 = (uint8_t*)ps_malloc(WEB_FRAMEBUFFER_CAPACITY); // frame currently being sent to the stream client
  framebuffer3 = (uint8_t*)ps_malloc(WEB_FRAMEBUFFER_CAPACITY); // still-image capture response

  if (framebuffer == NULL || framebuffer2 == NULL || framebuffer3 == NULL) {
    Serial.println("Failed to allocate Web frame buffers in PSRAM");
    if (logfile) logfile.println("Failed to allocate Web frame buffers in PSRAM");
    major_fail();
    return;
  }

  Serial.println("Creating the_camera_loop_task");

  wait_for_sd = xSemaphoreCreateBinary(); //xSemaphoreCreateMutex();
  sd_go = xSemaphoreCreateBinary(); //xSemaphoreCreateMutex();
  baton = xSemaphoreCreateMutex();

  // prio 6 - higher than the camera loop(), and the streaming
  xTaskCreatePinnedToCore( the_camera_loop, "the_camera_loop", 3000, NULL, 6, &the_camera_loop_task, 0); // prio 3, core 0 //v56 core 1 as http dominating 0 ... back to 0, raise prio

  delay(100);

  // prio 4 - higher than the cam_loop(), and the streaming
  BaseType_t sd_task_create_result = xTaskCreatePinnedToCore(
    the_sd_loop, "the_sd_loop", SD_TASK_STACK_SIZE, NULL, 4, &the_sd_loop_task, 1);  // prio 4, core 1

  if (sd_task_create_result != pdPASS || the_sd_loop_task == NULL) {
    Serial.printf("Failed to create the_sd_loop task (result %d)\n", (int)sd_task_create_result);
    if (logfile) {
      logfile.printf("Failed to create the_sd_loop task (result %d)\n", (int)sd_task_create_result);
      logfile.flush();
    }
    major_fail();
  }

  delay(200);

  boot_time = millis();

  const char *strdate = ctime(&now);
  logfile.println(strdate);

  //digitalWrite(33, HIGH);         // red light turns off when setup is complete
    //追記
  sensor_t *sensor = esp_camera_sensor_get();
  camera_setting(sensor);

  if (!InternetOff) {
    Serial.println("Starting Web Services ...");
    startCameraServer();
    start_Stream_81_server();
    filemgr.begin();
    filemgr.setBackGroundColor("Gray");
    Serial.print("Open Filemanager with http://");
    if (wifi_mode == RECORDER_WIFI_AP) {
      Serial.print(WiFi.softAPIP());
    } else {
      Serial.print(WiFi.localIP());
    }
    Serial.print(":");
    Serial.print(filemanagerport);
    Serial.println("/");
  }

  Serial.println("  End of setup()\n\n");
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// the_sd_loop()
//

void the_sd_loop (void* pvParameter) {

  Serial.print("the_sd_loop, core ");  Serial.print(xPortGetCoreID());
  Serial.print(", priority = "); Serial.println(uxTaskPriorityGet(NULL));
  sd_task_min_free_stack_bytes = (uint32_t)uxTaskGetStackHighWaterMark(NULL);
  Serial.printf("SD task stack: %u bytes; minimum free at startup: %u bytes\n",
                SD_TASK_STACK_SIZE, sd_task_min_free_stack_bytes);
  if (logfile) {
    logfile.printf("SD task stack: %u bytes; minimum free at startup: %u bytes\n",
                   SD_TASK_STACK_SIZE, sd_task_min_free_stack_bytes);
  }

  uint32_t completed_sd_writes = 0;

  while (1) {
    xSemaphoreTake( sd_go, portMAX_DELAY );            // we wait for camera loop to tell us to go
    another_save_avi( fb_curr);                        // do the actual sd wrte
    completed_sd_writes++;
    sd_task_min_free_stack_bytes = (uint32_t)uxTaskGetStackHighWaterMark(NULL);

    if (completed_sd_writes == 1 ||
        completed_sd_writes % SD_STACK_LOG_INTERVAL_WRITES == 0) {
      Serial.printf("SD task minimum free stack after %u writes: %u / %u bytes\n",
                    completed_sd_writes, sd_task_min_free_stack_bytes, SD_TASK_STACK_SIZE);
      if (logfile) {
        logfile.printf("SD task minimum free stack after %u writes: %u / %u bytes\n",
                       completed_sd_writes, sd_task_min_free_stack_bytes, SD_TASK_STACK_SIZE);
      }
    }

    xSemaphoreGive( wait_for_sd );                     // tell camera loop we are done
  }
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// the_camera_loop()


void loop() {
  poll_safe_stop_button();

  if (safe_stop_requested) {
    // Latch recording off and stop every service that can access the camera or SD card.
    start_record = 0;
    if (!InternetOff) {
      filemgr.end();
      stopCameraServer();
      stop_wifi_completely();
    }

    if (recording_closed_for_shutdown && !safe_stop_complete) {
      perform_safe_sd_shutdown();
    }

    if (safe_stop_complete &&
        (uint32_t)(millis() - safe_stop_led_changed_at) >= 500) {
      safe_stop_led_changed_at = millis();
      safe_stop_led_on = !safe_stop_led_on;
      digitalWrite(GPIOVPin, safe_stop_led_on ? HIGH : LOW);
    }

    delay(50);
    return;
  }

  long run_time = millis() - boot_time;

  if (delete_old_stuff_flag == 1) {
    delete_old_stuff_flag = 0;
    delete_old_stuff();
  }
  start_record_2nd_opinion = start_record_1st_opinion;
  start_record_1st_opinion = digitalRead(43); // Pin 12を43に変更

  if (start_record_1st_opinion == start_record_2nd_opinion ) {
    if (start_record_1st_opinion > 0 ) start_record = 1;
    else start_record = 0;
  }

  int read13 = digitalRead(44); // Pin 13を44に変更 
  delay(20);
  read13 = read13 + digitalRead(44); // Pin 13を44に変更 // get 2 opinions to help poor soldering

  if (wifi_mode != RECORDER_WIFI_OFF && !wifi_suppressed_after_brownout) {
    if (read13 > 0) {
      read13 = 0;
    } else {
      read13 = 2;
    }
  }

  if (wifi_mode != RECORDER_WIFI_OFF && !wifi_suppressed_after_brownout) {
    if (read13 == 2 && !InternetOff) {
      Serial.println("Shutting off wifi ..."); logfile.println("Shutting off wifi ...");
      filemgr.end();
      stopCameraServer();
      stop_wifi_completely();
    }
    static uint32_t next_wifi_retry = 0;
    if (read13 == 0 && InternetOff && (int32_t)(millis() - next_wifi_retry) >= 0) {
      next_wifi_retry = millis() + 30000;
      Serial.println("Starting the wifi ...");  logfile.println("Starting the wifi ...");
      if (init_wifi()) {
        Serial.println("Starting Web Services ...");
        startCameraServer();
        start_Stream_81_server();
        filemgr.begin();
        filemgr.setBackGroundColor("Gray");
        InternetOff = false;
      } else {
        Serial.println("WiFi start failed; retrying in 30 seconds");
      }
    }
  }

  wakeup = millis();
  if (!InternetOff && (wakeup - last_wakeup > (15  * 60 * 1000) )) {       // 15 minutes追加インターネットoff
    last_wakeup = millis();
    if (!InternetOff && wifi_mode == RECORDER_WIFI_STA) {
      if (WiFi.status() != WL_CONNECTED) {

        Serial.println("***** WiFi reconnect *****");
        WiFi.reconnect();
        delay(8000);

        if (WiFi.status() != WL_CONNECTED) {
          Serial.println("***** WiFi rerestart *****");
          init_wifi();
        }
      }
    }

    time(&now);
    Serial.print("\nLocal time: "); Serial.print(ctime(&now));
    if (WiFi.status() != WL_CONNECTED) {
      sprintf(localip, "%s", WiFi.softAPIP().toString().c_str());
      Serial.print("IP: "); Serial.println(localip); Serial.println(" ");
    } else {
      sprintf(localip, "%s", WiFi.localIP().toString().c_str());
      Serial.print("IP: "); Serial.println(localip); Serial.println(" ");
    }

    if (!MDNS.begin(devname)) {
      Serial.println("Error setting up MDNS responder!");
    } else {
      Serial.printf("mDNS responder started '%s'\n", devname);
    }
  }


  if (reboot_now == true) {
    Serial.println(" \n\n\n Rebooting ... \n\n\n");
    delay(2000);
    ESP.restart();
  }
  if (!InternetOff) {
    filemgr.handleClient();  //v56
  }
  delay(200);

}


void the_camera_loop (void* pvParameter) {

  Serial.print("the camera loop, core ");  Serial.print(xPortGetCoreID());
  Serial.print(", priority = "); Serial.println(uxTaskPriorityGet(NULL));

  frame_cnt = 0;
  start_record_2nd_opinion = digitalRead(43); //12→４３
  start_record_1st_opinion = digitalRead(43);
  start_record = 0;

  delay(1000);

  while (1) {

    if (safe_stop_requested && frame_cnt == 0) {
      park_camera_for_safe_shutdown();
      return;
    }

    // if (frame_cnt == 0 && start_record == 0)  // do nothing
    // if (frame_cnt == 0 && start_record == 1)  // start a movie
    // if (frame_cnt > 0 && start_record == 0)   // stop the movie
    // if (frame_cnt > 0 && start_record != 0)   // another frame

    ///////////////////  NOTHING TO DO //////////////////
    if (frame_cnt == 0 && start_record == 0) {
      // ★ 待機中はLEDが消灯していることを確認 ★追加
      //digitalWrite(RecordingLEDV, LOW);
      //digitalWrite(RecordingLEDGND, LOW);
      digitalWrite(GPIOGNDPin, LOW);
      digitalWrite(GPIOVPin, LOW);

      // While recording is stopped, the camera task remains the sole owner of
      // camera capture and produces a frame only when the stream client asks.
      if (stream_81 && stream_frame_needed) {
        camera_fb_t *stream_frame = esp_camera_fb_get();
        if (stream_frame != NULL) {
          copy_frame_for_active_stream(stream_frame);
          esp_camera_fb_return(stream_frame);
        } else {
          Serial.println("Live stream camera capture failed");
        }
        delay(10);
        continue;
      }
      
      // Serial.println("Do nothing");
      if (we_are_already_stopped == 0) Serial.println("\n\nDisconnect Pin 12 from GND to start recording.\n\n");
      we_are_already_stopped = 1;
      delay(100);

      ///////////////////  START A MOVIE  //////////////////
    } else if (frame_cnt == 0 && start_record == 1) {

      //Serial.println("Ready to start");

      we_are_already_stopped = 0;
      // ★ 録画開始時にLEDを点灯 (HIGH) ★追加
      //digitalWrite(RecordingLEDV, HIGH);
      //digitalWrite(RecordingLEDGND, LOW);
      digitalWrite(GPIOGNDPin, LOW);
      digitalWrite(GPIOVPin, HIGH);


      //delete_old_stuff(); // move to loop

      avi_start_time = millis();
      //追加
      avi_start_time_exact = esp_timer_get_time();
      Serial.printf("\nStart the avi ... at %d\n", avi_start_time);
      Serial.printf("Framesize %d, quality %d, length %d seconds\n\n", framesize, quality, avi_length);
      logfile.printf("\nStart the avi ... at %d\n", avi_start_time);
      logfile.printf("Framesize %d, quality %d, length %d seconds\n\n", framesize, quality, avi_length);
      logfile.flush();

      frame_cnt++;

      long wait_for_cam_start = millis();
      fb_curr = get_good_jpeg();                     // should take zero time
      wait_for_cam += millis() - wait_for_cam_start;

      start_avi(fb_curr);

      wait_for_cam_start = millis();
      fb_next = get_good_jpeg();                    // should take nearly zero time due to time spent writing header
      copy_frame_for_active_stream(fb_next);
      wait_for_cam += millis() - wait_for_cam_start;
      xSemaphoreGive( sd_go );                     // trigger sd write to write first frame

      //if (blinking) digitalWrite(21, frame_cnt % 2);                // blink

      ///////////////////  END THE MOVIE //////////////////
    } else if ( restart_now || reboot_now || (frame_cnt > 0 && start_record == 0) ||  millis() > (avi_start_time + avi_length * 1000)) { // end the avi
      
      // ★ 録画終了時にLEDを消灯 (LOW) ★追加
      //digitalWrite(RecordingLEDV, LOW);
      //digitalWrite(RecordingLEDGND, LOW);
      digitalWrite(GPIOGNDPin, LOW);
      digitalWrite(GPIOVPin, LOW);


      Serial.println("End the Avi");
      restart_now = false;

      xSemaphoreTake( wait_for_sd, portMAX_DELAY );
      esp_camera_fb_return(fb_curr);

      frame_cnt++;
      fb_curr = fb_next;
      fb_next = NULL;

      xSemaphoreGive( sd_go );                  // save final frame of movie

      //if (blinking)  digitalWrite(21, frame_cnt % 2);

      xSemaphoreTake( wait_for_sd, portMAX_DELAY );    // wait for final frame of movie to be written

      esp_camera_fb_return(fb_curr);
      fb_curr = NULL;

      bool completed_video = frame_cnt >= 5;
      end_avi();                                // end the movie

      //if (blinking) digitalWrite(21, HIGH);          // light off

      avi_end_time = millis();

      float fps = 1.0 * frame_cnt / ((avi_end_time - avi_start_time) / 1000) ;

      Serial.printf("End the avi at %d.  It was %d frames, %d ms at %.2f fps...\n", millis(), frame_cnt, avi_end_time, avi_end_time - avi_start_time, fps);
      logfile.printf("End the avi at %d.  It was %d frames, %d ms at %.2f fps...\n", millis(), frame_cnt, avi_end_time, avi_end_time - avi_start_time, fps);

      if (completed_video) {
        completed_recordings++;
        Serial.printf("Completed recordings: %u", completed_recordings);
        logfile.printf("Completed recordings: %u", completed_recordings);
        if (max_recordings > 0) {
          Serial.printf(" / %d\n", max_recordings);
          logfile.printf(" / %d\n", max_recordings);
        } else {
          Serial.println(" / unlimited");
          logfile.println(" / unlimited");
        }

        if (max_recordings > 0 && completed_recordings >= (uint32_t)max_recordings) {
          safe_stop_requested = true;
          Serial.println("Configured recording count reached: safely stopping.");
          logfile.println("Configured recording count reached: safely stopping.");
        }
      }

      if (safe_stop_requested) {
        frame_cnt = 0;
        park_camera_for_safe_shutdown();
        return;
      }

      delete_old_stuff_flag = 1;
      delay(50);

      if (!reboot_now) frame_cnt = 0;             // start recording again on the next loop

      ///////////////////  ANOTHER FRAME  //////////////////
    } else if (frame_cnt > 0 && start_record != 0) {  // another frame of the avi

      //Serial.println("Another frame");

      current_frame_time = millis();
      if (current_frame_time - last_frame_time < frame_interval) {
        delay(frame_interval - (current_frame_time - last_frame_time));             // delay for timelapse
      }
      last_frame_time = millis();

      frame_cnt++;

      long delay_wait_for_sd_start = millis();
      xSemaphoreTake( wait_for_sd, portMAX_DELAY );             // make sure sd writer is done
      delay_wait_for_sd += millis() - delay_wait_for_sd_start;

      esp_camera_fb_return(fb_curr);

      fb_curr = fb_next;           // we will write a frame, and get the camera preparing a new one

      xSemaphoreGive( sd_go );             // write the frame in fb_curr

      long wait_for_cam_start = millis();
      fb_next = get_good_jpeg();               // should take near zero, unless the sd is faster than the camera, when we will have to wait for the camera
      copy_frame_for_active_stream(fb_next);
      wait_for_cam += millis() - wait_for_cam_start;

      //if (blinking) digitalWrite(21, frame_cnt % 2);

      if (frame_cnt % 100 == 10 ) {     // print some status every 100 frames
        if (frame_cnt == 10) {
          bytes_before_last_100_frames = movi_size;
          time_before_last_100_frames = millis();
          most_recent_fps = 0;
          most_recent_avg_framesize = 0;
        } else {

          most_recent_fps = 100.0 / ((millis() - time_before_last_100_frames) / 1000.0) ;
          most_recent_avg_framesize = (movi_size - bytes_before_last_100_frames) / 100;

          if (Lots_of_Stats && frame_cnt < 1011) {
            Serial.printf("So far: %04d frames, in %6.1f seconds, for last 100 frames: avg frame size %6.1f kb, %.2f fps ...\n", frame_cnt, 0.001 * (millis() - avi_start_time), 1.0 / 1024  * most_recent_avg_framesize, most_recent_fps);
            logfile.printf("So far: %04d frames, in %6.1f seconds, for last 100 frames: avg frame size %6.1f kb, %.2f fps ...\n", frame_cnt, 0.001 * (millis() - avi_start_time), 1.0 / 1024  * most_recent_avg_framesize, most_recent_fps);
          }


          total_delay = 0;

          bytes_before_last_100_frames = movi_size;
          time_before_last_100_frames = millis();
        }
      }
      //追加
      if ( timestampFile ) {
        //timestampFile.printf("%d,%llu\n", frame_cnt, 0.001 * (millis() - avi_start_time));
        float elapsed_sec = (float)(esp_timer_get_time() - avi_start_time_exact) * 0.000001;
        timestampFile.printf("%d,%.6f\n", frame_cnt, elapsed_sec);
        if (frame_cnt % 100 == 10 ){
          timestampFile.flush();
        }
      }
      //
      if ( illuminanceFile ) {
        //int total = 0;
        int readings = 20; // 何回測定するか

        // 5回測定して合計を計算
        //for (int i = 0; i < readings; i++) {
        //  total += analogRead(lightSensorPin);
        //  //delay(10); // 少し待つ（必要に応じて調整）
        //}

        // 平均を計算
        //int sensorValue = total / readings;

        // 電圧に変換
        //float voltage = sensorValue * (3.3 / 4095.0);

        //int sensorValue = analogRead(lightSensorPin);
        //float voltage = sensorValue * (3.3 / 4095.0); // ADC値から電圧に変換
        //illuminanceFile.printf("%d,%.6f\n", frame_cnt, voltage);

        char buffer[256];   // 十分余裕あり
        int buf_pos = 0;

        for (int i = 0; i < readings; i++) {
          int sensorValue = analogRead(lightSensorPin);

          // mVに変換（float不使用）
          int voltage_mV = sensorValue * 3300 / 4095;

          // バッファに追記
          buf_pos += snprintf(
            buffer + buf_pos,
            sizeof(buffer) - buf_pos,
            "%d,%d\n",
            frame_cnt,
            voltage_mV
          );
        }

        // まとめて1回だけ書き込み
        illuminanceFile.write((uint8_t*)buffer, buf_pos);

        if (frame_cnt % 100 == 10 ){
          illuminanceFile.flush();
        }
      }
    }
  }
}


void camera_setting(sensor_t *sensor){
  sensor->set_exposure_ctrl(sensor, 0);
  sensor->set_aec2(sensor, 0); 
  sensor->set_aec_value(sensor, 70); //head2-40, head1-50 
  //sensor->set_special_effect(sensor, 5); 
  sensor->set_agc_gain(sensor, 5); 
  //sensor->set_hmirror(sensor, 1); 
  //sensor->set_vflip(sensor, 1); 
  sensor->set_raw_gma(sensor, 0); 
  sensor->set_whitebal(sensor, 0); 
  sensor->set_awb_gain(sensor, 0); 
  sensor->set_gain_ctrl(sensor, 0); 
  //sensor->set_lenc(sensor, 0); 
  //sensor->set_dcw(sensor, 1); 
  //sensor->set_bpc(sensor, 0); 
  //sensor->set_wpc(sensor, 1); 
  }
