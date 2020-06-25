
    project "Sandbox"
	kind "WindowedApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("../bin/" .. outputdir .. "/%{prj.name}")
	objdir ("../bin-obj/" .. outputdir .. "/%{prj.name}")

    characterset ("MBCS")

    flags
    {
        "MultiProcessorCompile"
    }

	files
	{
		"src/**.h",
		"src/**.cpp"
    }
    
    includedirs
    {
        "../DirectXRenderer/src",
        "../DirectXRenderer/3rdPart",
        "../DirectXRenderer/%{IncludeDir.ImGui}"
    }

    links
    {
        "DirectXRenderer"
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

    links
    {
        "../DirectXRenderer/3rdPart/assimp/bin/Debug/assimp-vc142-mtd.lib"
    }

    postbuildcommands 
    {
        '{COPY} "../DirectXRenderer/3rdPart/assimp/bin/Debug/assimp-vc142-mtd.dll" "%{cfg.targetdir}"'
    }

filter "configurations:Release"
    defines "_RELEASE"
    runtime "Release"
    optimize "on"

    links
    {
        "../DirectXRenderer/3rdPart/assimp/bin/Release/assimp-vc142-mt.lib"
    }

    postbuildcommands 
    {
        '{COPY} "../DirectXRenderer/3rdPart/assimp/bin/Release/assimp-vc142-mt.dll" "%{cfg.targetdir}"'
    }
