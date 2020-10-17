
    project "Sandbox"
	kind "WindowedApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

    buildoptions
    {
        "/permissive-",
        "/sdl",
        "/w34265",
    }

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
	    "src/**.c", 
	    "src/**.hpp", 
	    "src/**.cpp" ,
        "asset/shader/**.hlsl",
        "asset/shader/**.hlsli",
    }
    
    includedirs
    {
        "../DirectXRenderer/src",
        "../DirectXRenderer/3rdPart",
        "../DirectXRenderer/3rdPart/assimp/include",
        "../DirectXRenderer/3rdPart/DirectXTex/include",
        "../DirectXRenderer/%{IncludeDir.ImGui}",
    }

    links
    {
        "DirectXRenderer"
    }

    postbuildcommands 
	{
		'{COPY} "asset" "%{cfg.targetdir}/asset"'
	}

    filter "system:windows"
    systemversion "latest"

    defines
    {

    }

 shadermodel("5.0")
 --shaderassembler("AssemblyCode")
 local shader_dir_cso = "asset/shader/cso/"
 --local shader_dir_asm = "asset/shader/asm/"
 --HLSL files that don't end with 'Extensions' will be ignored as they will be
 --used as includes
  filter("files:**.hlsl")
  flags("ExcludeFromBuild")
  shaderobjectfileoutput(shader_dir_cso.."%{file.basename}"..".cso")
  --shaderassembleroutput(shader_dir_asm.."%{file.basename}"..".asm")
  filter("files:**_PS.hlsl")
  removeflags("ExcludeFromBuild")
  shadertype("Pixel")

  filter("files:**_VS.hlsl")
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
        "../DirectXRenderer/3rdPart/assimp/bin/Debug/assimp-vc142-mtd.lib",
        "../DirectXRenderer/3rdPart/assimp/bin/Debug/IrrXMLd.lib",
        "../DirectXRenderer/3rdPart/DirectXTex/lib/Debug/DirectXTex.lib"
    }

    postbuildcommands 
    {
       '{COPY} "../DirectXRenderer/3rdPart/assimp/bin/Debug/assimp-vc142-mtd.dll" "%{cfg.targetdir}"',
       '{COPY} "../DirectXRenderer/3rdPart/assimp/bin/Debug/zlibd1.dll" "%{cfg.targetdir}"',
    }

filter "configurations:Release"
    defines "_RELEASE"
    runtime "Release"
    optimize "Speed"

    defines
    {
        "IS_DEBUG=false",
        "NDEBUG"
    }

    links
    {
        "../DirectXRenderer/3rdPart/assimp/bin/Release/assimp-vc142-mt.lib",
        "../DirectXRenderer/3rdPart/assimp/bin/Release/IrrXML.lib",
        "../DirectXRenderer/3rdPart/DirectXTex/lib/Release/DirectXTex.lib",
     }

    postbuildcommands 
    {
        '{COPY} "../DirectXRenderer/3rdPart/assimp/bin/Release/assimp-vc142-mt.dll" "%{cfg.targetdir}"',
        '{COPY} "../DirectXRenderer/3rdPart/assimp/bin/Release/zlib1.dll" "%{cfg.targetdir}"',
    }
