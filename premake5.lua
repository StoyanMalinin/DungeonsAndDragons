workspace "DungeonsAndDragons"
    configurations { "Debug", "Release" }

project "DungeonsAndDragons"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    files { "src/**.h", "src/**.cpp", "src/**.hpp", "tests/**.cpp", "tests/**.h", "tests/**.hpp" }

    filter { "configurations:Debug" }
        defines { "DEBUG", "_CRT_SECURE_NO_WARNINGS" }
        symbols "On"
        targetdir "bin/Debug"
		
    filter { "configurations:Release" }
        defines { "NDEBUG", "_CRT_SECURE_NO_WARNINGS" }
        optimize "On"
        targetdir "bin/Release"