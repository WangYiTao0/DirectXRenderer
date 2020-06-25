project "DirectXRenderer"
kind "StaticLib"
language "c++"
cppdialect "c++17"
staticruntime "on"

targetdir("../bin/" .. outputdir .. "/%{prj.name}")
objdir("../bin-obj/" .. outputdir .. "/%{prj.name}")

pchheader "drpch.h"
pchsource "src/drpch.cpp"

characterset ("MBCS")

files
{
    "src/**.h",
    "src/**.cpp"
}

defines
{
    "_CRT_SECURE_NO_WARNINGS"
}

includedirs
{
    "src",
    "%{IncludeDir.ImGui}",
    "3rdPart/assimp/include",
}

links
{
    "ImGui",
    "d3d11.lib",
    "D3DCompiler.lib",
}

filter "system:windows"
    systemversion "latest"

    defines
    {
    
    }

filter "configurations:Debug"
    defines "_DEBUG"
    runtime "Debug"
    symbols "on"

filter "configurations:Release"
    defines "_RELEASE"
    runtime "Release"
    optimize "on"