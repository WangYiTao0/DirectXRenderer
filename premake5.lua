include "./3rdPart/premake/premake_customization/solution_items.lua"


workspace "DirectXRenderer"
    architecture "x64"
    targetdir "build"
    startproject "Sandbox"

    configurations
    {
        "Debug",
        "Release",
        "Dist"
    }

    solution_items
	{
		".editorconfig",
    }
    
    flags
    {
        "MultiProcessorCompile"
    }

    outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to 
IncludeDir = {}
IncludeDir["ImGui"] = "3rdPart/imgui"

LibraryDir = {}

-- Projects
group "Dependencies"
    include "3rdPart/premake"
    include "DirectXRenderer/3rdPart/imgui"
group ""

include "DirectXRenderer"
include "Sandbox"
--include "DrTool"

