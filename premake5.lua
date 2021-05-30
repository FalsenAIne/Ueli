function queryTerminal(command)
    local success, handle = pcall(io.popen, command)
    if not success then 
        return ""
    end

    result = handle:read("*a")
    handle:close()
    result = string.gsub(result, "\n$", "") -- remove trailing whitespace
    return result
end

function getPythonPath()
    local p = queryTerminal('python -c "import sys; import os; print(os.path.dirname(sys.executable))"')
    
    -- sanitize path before returning it
    p = string.gsub(p, "\\\\", "\\") -- replace double backslash
    p = string.gsub(p, "\\", "/") -- flip slashes
    return p
end

function getPythonLib()
    return queryTerminal("python -c \"import sys; import os; import glob; path = os.path.dirname(sys.executable); libs = glob.glob(path + '/libs/python*'); print(os.path.splitext(os.path.basename(libs[-1]))[0]);\"")
end

pythonPath      = getPythonPath()
pythonIncludePath = pythonPath .. "/include/"
pythonLibPath     = pythonPath .. "/libs/"
pythonLib         = getPythonLib()

-- if pythonPath == "" or pythonLib == "" then
--     error("Failed to find python path!")
if pythonPath == "" then
    error("Failed to find python path!")
else
    print("Python includes: " .. pythonIncludePath)
    print("Python libs: " .. pythonLibPath)
    print("lib: " .. pythonLib)
end

workspace "Ueli"
	architecture "x86_64"
	startproject "Test"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["spdlog"] = "%{wks.location}/Ueli/ThirdParty/spdlog/include"

-- group "Dependencies"
-- 	include "BIGOSengine/ThirdParty/imgui"
-- 	include "BIGOSengine/ThirdParty/Glad"
-- group ""

project "Ueli"
	location "Ueli"
	kind "SharedLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "off"

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
		"%{prj.name}/src",
		"%{IncludeDir.spdlog}"
	}

	libdirs     
	{ 

	}

	filter "files:**.c"
		flags {"NoPCH"}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"UELI_PLATFORM_WINDOWS",
			"UELI_BUILD_DLL",
			"VK_USE_PLATFORM_WIN32_KHR",
			"VK_NO_PROTOTYPES",
			"BUILD_VK"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Test")
		}

	filter "configurations:Debug"
		defines "UELI_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "UELI_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "UELI_DIST"
		runtime "Release"
		optimize "on"

project "Test"
	location "Test"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "off"
		
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
		
	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}
		
	includedirs 
	{
		"Ueli/src",
		"Ueli/ThirdParty",
		"%{IncludeDir.spdlog}",
		"%{wks.location}/Test/ThirdParty"
	}
		
	links
	{
		"Ueli"
	}
		
		
	filter "system:windows"
		systemversion "latest"
		
		defines
		{
			"UELI_PLATFORM_WINDOWS",
			"VK_USE_PLATFORM_WIN32_KHR"
		}
		
		filter "configurations:Debug"
			defines "UELI_DEBUG"
			runtime "Debug"
			symbols "on"
		
		filter "configurations:Release"
			defines "UELI_RELEASE"
			runtime "Release"
			optimize "on"
		
		filter "configurations:Dist"
			defines "UELI_DIST"
			runtime "Release"
			optimize "on"

project "PythonModule"
	location "PythonModule"
	kind "SharedLib"
	
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
	targetname("pybind_test") -- this name must match the module name in the macro PYBIND11_MODULE(group6_pybind_test, m)
	targetextension(".pyd")

	files 
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs 
	{
		pythonIncludePath,
		"%{wks.location}/PythonModule/ThirdParty/pybind11/include"
	}

	libdirs     
	{ 
		pythonLibPath 
	}
	
	postbuildcommands 
	{
		"{COPY} %{cfg.targetdir}/pybind_test.pyd %{cfg.targetdir}/../../../modules/"
	}

	filter "system:windows"
		systemversion "latest"
		
		defines
		{
			"UELI_PLATFORM_WINDOWS",
			"VK_USE_PLATFORM_WIN32_KHR"
		}

		-- symbolspath '$(TargetName).pdb'
		
		filter "configurations:Debug"
			defines "UELI_DEBUG"
			runtime "Debug"
			symbols "on"

			links 
			{ 
				"python39_d.lib"
			}
		
		filter "configurations:Release"
			defines "UELI_RELEASE"
			runtime "Release"
			optimize "on"

			links 
			{ 
				"python39.lib"
			}
		
		filter "configurations:Dist"
			defines "UELI_DIST"
			runtime "Release"
			optimize "on"