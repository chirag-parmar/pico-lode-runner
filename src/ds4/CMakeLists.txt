add_library(ds4
	ds4.c
)

target_include_directories(ds4 PUBLIC
	.
)

target_link_libraries(ds4 pico_stdlib tinyusb_host tinyusb_board hardware_spi hardware_dma)