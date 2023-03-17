add_library(wohoo-an-error SHARED main.c)
target_link_libraries(wohoo-an-error pthread)
target_link_options(wohoo-an-error PRIVATE "-Wl,-init,init" "-Wl,-fini,finish")

set(LIB_DEST "/usr/local/lib64")
install(TARGETS wohoo-an-error LIBRARY DESTINATION ${LIB_DEST})
install(CODE "execute_process(WORKING_DIRECTORY ${CMAKE_SOURCE_DIR} COMMAND sh ./register_for_preloading ${LIB_DEST} $<TARGET_FILE_NAME:wohoo-an-error>)")
