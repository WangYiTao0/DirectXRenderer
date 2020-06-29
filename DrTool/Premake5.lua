project "DrTool"
kind "WindowedApp"
language "C++"
cppdialect "C++17"
staticruntime "on"

targetdir ("../bin/" .. outputdir .. "/%{prj.name}")
objdir ("../bin-obj/" .. outputdir .. "/%{prj.name}")

buildoptions
{
    "/permissive-",
    "/sdl"
}

characterset ("MBCS")

flags
{
    "MultiProcessorCompile"
}

files
{
    "src/**.h", 
    "src/**.c", 
    "src/**.hpp", 
    "src/**.cpp" ,
}

includedirs
{
    "../DirectXRenderer/src",
    "../DirectXRenderer/3rdPart",
    "../DirectXRenderer/3rdPart/assimp/include",
    "../DirectXRenderer/3rdPart/DirectXTex/include",
}

links
{
    "DirectXRenderer",
}

filter "system:windows"
systemversion "latest"

filter "configurations:Debug"
    defines "_DEBUG"
    runtime "Debug"
    symbols "on"
    defines
    {
        "IS_DEBUG=true"
    }
    links
    {
        "../DirectXRenderer/3rdPart/assimp/bin/Debug/assimp-vc142-mtd.lib",
        "../DirectXRenderer/3rdPart/assimp/bin/Debug/IrrXMLd.lib",
        "../DirectXRenderer/3rdPart/DirectXTex/lib/Debug/DirectXTex.lib"
    }

filter "configurations:Release"
    defines "_RELEASE"
    runtime "Release"
    optimize "on"

    defines
    {
        "IS_DEBUG=false",
        "NDEBUG"
    }

    links
    {
        "../DirectXRenderer/3rdPart/assimp/bin/Release/assimp-vc142-mt.lib",
        "../DirectXRenderer/3rdPart/assimp/bin/Release/IrrXMLd.lib",
        "../DirectXRenderer/3rdPart/DirectXTex/lib/Debug/DirectXTex.lib",
     }
