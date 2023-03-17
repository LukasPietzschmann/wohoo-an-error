add_library(wohoo-an-error SHARED main.c)
target_link_libraries(wohoo-an-error pthread)
target_link_options(wohoo-an-error PRIVATE "-Wl,-init,init" "-Wl,-fini,finish")

set(LIB_DEST "/usr/local/lib64")
set(LIB_DEST_ESC "\/usr\/local\/lib64")

add_custom_target(uninstall
	COMMAND rm -f ${LIB_DEST}/$<TARGET_FILE_NAME:wohoo-an-error>
	COMMAND sh ${CMAKE_SOURCE_DIR}/register_for_preloading ${LIB_DEST} $<TARGET_FILE_NAME:wohoo-an-error> un
)

install(TARGETS wohoo-an-error LIBRARY DESTINATION ${LIB_DEST})
install(CODE "execute_process(WORKING_DIRECTORY ${CMAKE_SOURCE_DIR} COMMAND sh ./register_for_preloading ${LIB_DEST} $<TARGET_FILE_NAME:wohoo-an-error> in)")
