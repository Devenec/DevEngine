cmake_minimum_required(VERSION 2.8)

set(SOURCE_FILES
	source/Application.cpp
	source/Error.cpp
	source/Log.cpp
	source/LogBuffer.cpp
	source/LogManager.cpp
	source/Memory.cpp
	source/Rectangle.cpp
	source/String.cpp
	source/Types.cpp
	source/debug/AllocationTracker.cpp
	source/debug/Assert.cpp
	source/maths/Angle.cpp
	source/maths/Matrix4.cpp
	source/maths/Vector2.cpp
	source/maths/Vector3.cpp
	source/maths/Vector4.cpp
	source/memory/AllocationPolicy.cpp
	source/memory/AllocationPolicyBase.cpp
)

set(INCLUDE_DIRECTORIES
	include
	../platform/include
)

include_directories(${INCLUDE_DIRECTORIES})
add_library(core STATIC ${SOURCE_FILES})
