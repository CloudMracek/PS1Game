cmake_minimum_required(VERSION 3.20)

project(
	bandwidth-engine
	LANGUAGES    C CXX ASM
	VERSION      1.0.0
	DESCRIPTION  "My super-duper engine"
	HOMEPAGE_URL "https://www.youtube.com/channel/UCzp1RaZ3HmejKl723qlKOAw"
)

file(GLOB MODELS models/*.c)
file(GLOB TEXTURES textures/*.tim)

psn00bsdk_add_executable(
	bandwidth STATIC
	main.c
	display.c
	textures.c
	input.c
	${MODELS}
)

foreach(TEXTURE ${TEXTURES})
	get_filename_component(BARENAME ${TEXTURE} NAME)
	string(REGEX REPLACE "\\.[^.]*$" "" TEXTURE_NAME ${BARENAME})
	psn00bsdk_target_incbin(bandwidth PRIVATE ${TEXTURE_NAME} ${TEXTURE})
endforeach()

#psn00bsdk_target_incbin(bandwidth PRIVATE bandwidth_face textures/bandwidth_face.tim)

psn00bsdk_add_cd_image(
	iso      # Target name
	template # Output file name (= bandwidth.bin + bandwidth.cue)
	iso.xml  # Path to config file
	DEPENDS bandwidth
)
