workspace "Typhoon"
	architecture "x86_64"
	startproject "Sandbox"

	configurations 
	{
		"Debug", 
		"Release", 
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"]  	  = "Typhoon/vendor/GLFW/include"
IncludeDir["Glad"]  	  = "Typhoon/vendor/Glad/include"
IncludeDir["ImGui"] 	  = "Typhoon/vendor/imgui"
IncludeDir["glm"]   	  = "Typhoon/vendor/glm"
IncludeDir["stb_image"]   = "Typhoon/vendor/stb_image"

group "Dependencies"
	include "Typhoon/vendor/GLFW"
	include "Typhoon/vendor/Glad"
	include "Typhoon/vendor/imgui"
group ""


project "Typhoon"
	location "Typhoon"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "typhpch.h"
	pchsource "Typhoon/src/typhpch.cpp"

	files 
	{
		"%{prj.name}/src/**.h", 
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/stb_image/**.h",
		"%{prj.name}/vendor/stb_image/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl"
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS"
	}

	includedirs 
	{
		"%{prj.name}/src", 
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb_image}"
	}

	links
	{
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}

	filter "system:windows"
		systemversion "latest"

		defines 
		{ 
			"TYPH_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

	filter "configurations:Debug"
		defines "TYPH_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "TYPH_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "TYPH_DIST"
		runtime "Release"
		optimize "on"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files 
	{
		"%{prj.name}/src/**.h", 
		"%{prj.name}/src/**.cpp"
	}

	includedirs 
	{
		"Typhoon/vendor/spdlog/include", 
		"Typhoon/src",
		"Typhoon/vendor",
		"%{IncludeDir.glm}"
	}

	links 
	{
		"Typhoon"
	}

	filter "system:windows"
		systemversion "latest"

	filter "configurations:Debug"
		defines "TYPH_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "TYPH_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "TYPH_DIST"
		runtime "Release"
		optimize "on"


