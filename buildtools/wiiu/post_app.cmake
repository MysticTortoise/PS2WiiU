romfs_add(CrossShift2 "assets")

wut_create_rpx(CrossShift2)
install(FILES "${CMAKE_CURRENT_BINARY_DIR}/crossshift2.rpx"
     DESTINATION "${CMAKE_INSTALL_PREFIX}")