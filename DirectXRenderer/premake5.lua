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
	"src/**.c", 
	"src/**.hpp", 
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
    "3rdPart",
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
    defines "DR_DEBUG"
    runtime "Debug"
    symbols "on"
    defines
    {
        "IS_DEBUG=true"
    }

    links
    {
        "3rdPart/DirectXTex/lib/Debug/DirectXTex.lib"
    }

filter "configurations:Release"
    defines "DR_RELEASE"
    runtime "Release"
    optimize "on"

    defines
    {
        "IS_DEBUG=false"
    }

    links
    {
        "3rdPart/DirectXTex/lib/Release/DirectXTex.lib"
    }