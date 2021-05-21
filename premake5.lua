workspace "Ueli"
	architecture "x86_64"
	startproject "Ueli"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
-- IncludeDir["ImGui"] = "%{wks.location}/BIGOSengine/ThirdParty/imgui"
-- 
-- group "Dependencies"
-- 	include "BIGOSengine/ThirdParty/imgui"
-- 	include "BIGOSengine/ThirdParty/Glad"
-- group ""

project "Ueli"
	location "Ueli"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	-- pchheader "bgspch.h"
	-- pchsource "BIGOSengine/src/bgspch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS"
	}

	includedirs
	{
		"%{prj.name}/src"
		-- "%{IncludeDir.spdlog}",
	}

	links 
	{ 

	}

	filter "files:**.c"
		flags {"NoPCH"}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"BGS_PLATFORM_WINDOWS",
			"VK_USE_PLATFORM_WIN32_KHR",
			"VK_NO_PROTOTYPES",
			"BUILD_VK"
		}

	filter "configurations:Debug"
		defines "U_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "U_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "U_DIST"
		runtime "Release"
		optimize "on"