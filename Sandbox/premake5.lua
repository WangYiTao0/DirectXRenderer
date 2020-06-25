
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
		"src/**.cpp",
        "asset/shader/**.hlsl",
        "asset/shader/**.hlsli",
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

 shadermodel("5.0")
 shaderassembler("AssemblyCode")
 local shader_dir = "asset/shader/"
 --HLSL files that don't end with 'Extensions' will be ignored as they will be
 --used as includes
  filter("files:**.hlsl")
  flags("ExcludeFromBuild")
  shaderobjectfileoutput(shader_dir.."%{file.basename}"..".cso")
  shaderassembleroutput(shader_dir.."%{file.basename}"..".asm")
  filter("files:**_ps.hlsl")
  removeflags("ExcludeFromBuild")
  shadertype("Pixel")

  filter("files:**_vs.hlsl")
  removeflags("ExcludeFromBuild")
  shadertype("Vertex")

 -- Warnings as errors
 shaderoptions({"/WX"})

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

    defines
    {
        "IS_DEBUG=false"
    }

    links
    {
        "../DirectXRenderer/3rdPart/assimp/bin/Release/assimp-vc142-mt.lib"
    }

    postbuildcommands 
    {
        '{COPY} "../DirectXRenderer/3rdPart/assimp/bin/Release/assimp-vc142-mt.dll" "%{cfg.targetdir}"'
    }
