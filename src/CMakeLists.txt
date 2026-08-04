# Add main.c
set(PICOLYTIX_SOURCES ${PICOLYTIX_SOURCES} 
    ${CMAKE_CURRENT_LIST_DIR}/main.c 
    PARENT_SCOPE)

set(PICOLYTIX_INCLUDES ${PICOLYTIX_INCLUDES} 
    ${CMAKE_CURRENT_LIST_DIR} 
    PARENT_SCOPE)

# Add subdirectories
# add_subdirectory(drivers)
# add_subdirectory(usb)