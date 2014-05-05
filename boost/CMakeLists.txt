# 筛选器
SET(Boost_Folder "Boost")

# 处理器数目
IF(NOT RF_ProcessorCount)
	INCLUDE(ProcessorCount)
	PROCESSORCOUNT(RF_ProcessorCount)
ENDIF()

# 下载项目
INCLUDE(ExternalProject)
ExternalProject_Add(boost
	DOWNLOAD_NAME boost.tar.bz2
	URL http://jaist.dl.sourceforge.net/project/boost/boost/1.55.0/boost_1_55_0.tar.bz2
	SOURCE_DIR boost
	BINARY_DIR boost-build
	CONFIGURE_COMMAND ""
	BUILD_COMMAND ""
	INSTALL_COMMAND ""
)
SET_TARGET_PROPERTIES(boost PROPERTIES FOLDER ${Boost_Folder})

SET(BOOST_SOURCE_DIR ${CMAKE_CURRENT_BINARY_DIR}/boost)
SET(BOOST_BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR}/boost-build)

SET(BOOST_INCLUDE_DIR "${BOOST_SOURCE_DIR}" CACHE STRING "Boost include dir" FORCE)

# 增加 B2 生成命令
SET(Boost_B2 "${BOOST_SOURCE_DIR}/b2${CMAKE_EXECUTABLE_SUFFIX}")
IF(WIN32)
	ADD_CUSTOM_COMMAND(
		OUTPUT "${Boost_B2}"
		COMMAND cmd /C bootstrap.bat
		WORKING_DIRECTORY "${BOOST_SOURCE_DIR}"
	)
ELSE()
	ADD_CUSTOM_COMMAND(
		OUTPUT "${Boost_B2}"
		COMMAND ./bootstrap.sh
		WORKING_DIRECTORY "${BOOST_SOURCE_DIR}"
	)
ENDIF()
ADD_CUSTOM_TARGET(boost_b2 ALL DEPENDS "${Boost_B2}")
ADD_DEPENDENCIES(boost_b2 boost)
SET_TARGET_PROPERTIES(boost_b2 PROPERTIES FOLDER ${Boost_Folder})


FUNCTION(ADD_Boost_LIBRARY name)

	ADD_LIBRARY(boost_${name} STATIC)
	SET_TARGET_PROPERTIES(boost_${name} PROPERTIES LINKER_LANGUAGE "CXX")
	SET_TARGET_PROPERTIES(boost_${name} PROPERTIES FOLDER ${Boost_Folder})
	
	IF(NOT "${CMAKE_SHARED_LIBRARY_PREFIX}" STREQUAL "lib")
		SET_TARGET_PROPERTIES(boost_${name} PROPERTIES ARCHIVE_OUTPUT_NAME "libboost_${name}")
	ENDIF()
	
	FOREACH(config ${CMAKE_CONFIGURATION_TYPES})
		STRING(TOUPPER ${config} config_up)
		SET_TARGET_PROPERTIES(boost_${name} PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_${config_up} "${BOOST_BINARY_DIR}/${config}/lib")
	ENDFOREACH()
	
	IF(CMAKE_CL_64 EQUAL 1)
		SET(Boost_AddressModel address-model=64)
	ENDIF()
	
	ADD_CUSTOM_COMMAND(TARGET boost_${name} POST_BUILD
		COMMAND ${Boost_B2}
		
			-j${RF_ProcessorCount}
			
			link=static
			runtime-link=static
			variant="$<$<CONFIG:Debug>:debug>$<$<NOT:$<CONFIG:Debug>>:release>"
			
			stage
			--stagedir="${BOOST_BINARY_DIR}/$<CONFIGURATION>"
			
			-sNO_BZIP2=1
			
			--with-${name}
			
			--layout=system

			-q
			
			${Boost_AddressModel}
			
		WORKING_DIRECTORY "${BOOST_SOURCE_DIR}"
	)
	
	FOREACH(lib ${ARGN})
		TARGET_LINK_LIBRARIES(boost_${name} boost_${lib})
	ENDFOREACH()
	
	ADD_DEPENDENCIES(boost_${name} boost_b2)
	
	IF(Boost_Install)
		INSTALL(TARGETS boost_${name} DESTINATION lib)
	ENDIF()
	
ENDFUNCTION()

# 添加 Boost 库项目
ADD_Boost_LIBRARY(atomic)

ADD_Boost_LIBRARY(system)
ADD_Boost_LIBRARY(chrono system)

ADD_Boost_LIBRARY(context)
ADD_Boost_LIBRARY(coroutine context system)

ADD_Boost_LIBRARY(date_time)
ADD_Boost_LIBRARY(exception)
ADD_Boost_LIBRARY(filesystem)
ADD_Boost_LIBRARY(program_options)

ADD_Boost_LIBRARY(thread chrono system)

ADD_Boost_LIBRARY(regex)
ADD_Boost_LIBRARY(graph regex)

ADD_Boost_LIBRARY(iostreams)
ADD_Boost_LIBRARY(locale)

ADD_Boost_LIBRARY(log system date_time filesystem chrono thread)

ADD_Boost_LIBRARY(python)
ADD_Boost_LIBRARY(random)

ADD_Boost_LIBRARY(signals)

ADD_Boost_LIBRARY(timer chrono system)
ADD_Boost_LIBRARY(wave system date_time filesystem chrono thread)