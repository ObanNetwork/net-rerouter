workspace "net-rerouter"
	location "./build/"
	targetdir "%{wks.location}/bin/%{cfg.buildcfg}-%{cfg.platform}/"
	objdir "%{wks.location}/obj/%{prj.name}/%{cfg.buildcfg}-%{cfg.platform}/"
	buildlog "%{wks.location}/obj/%{cfg.platform}/%{cfg.buildcfg}-%{prj.name}.log"

	largeaddressaware "on"
	editandcontinue "off"
	staticruntime "on"

	systemversion "latest"
	characterset "unicode"
	warnings "extra"

	flags {
		"noincrementallink",
		"no64bitchecks",
		"shadowedvariables",
		"undefinedidentifiers",
		"multiprocessorcompile",
	}

	platforms {
		"x86",
	}

	configurations {
		"Release",
		"Debug",
	}

	--x86
	filter "platforms:x86"	
		architecture "x86"
	--end

	filter "Release"
		defines "NDEBUG"
		optimize "full"
		runtime "release"
		symbols "off"

	filter "Debug"
		defines "DEBUG"
		optimize "debug"
		runtime "debug"
		symbols "on"

	project "net-rerouter"
		language "c++"
		cppdialect "c++20"
		kind "sharedlib"
		warnings "off"

		pchheader "stdafx.hpp"
		pchsource "./src/stdafx.cpp"
		forceincludes "stdafx.hpp"

		postbuildcommands {
			"cd \"$(OutputPath)\"",
			"call \"..\\..\\..\\tools\\Rename to ASI.bat\" \"$(TargetFileName)\"",
		}

		dependson {
			"ini_rw",
		}

		links {
			"ini_rw",
		}

		includedirs {
			"./src/",

			"./deps/ini_rw/src"
		}

		files {
			"./src/**",
		}

	group "Dependencies"

	project "ini_rw"
		targetname "ini_rw"

		kind "staticlib"

		files {
			"./deps/ini_rw/src/**"
		}

		includedirs {
			"./deps/ini_rw/src/"
		}