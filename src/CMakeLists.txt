set(
    OUTPUT
    KETI-Policy
)
set (
    SOURCE_FILES
 
)

set(DBus_INCLUDE_DIR /home/keti/KETI_BMC/KETI-APP/sysroots/armv7ahf-vfpv4d16-KETI-linux-gnueabi/usr/include/dbus-c++-1)
include_directories(
   ${POPULATE_SDK_INCLUDE_DIR}
   ${INC_DIR}

)
## Source
link_directories(
    ${POPULATE_SDK_LIBRARY_DIR}
)
# Build
add_executable(${OUTPUT} ${SOURCE_FILES})
target_link_libraries( ${OUTPUT}
    crypto
    ssl
    m
    rt
    uuid
    pthread
    pam
    pam_misc
    boost_system
    boost_log
    boost_log_setup
    boost_thread
)
