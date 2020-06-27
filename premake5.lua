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

    flags
    {
        "MultiProcessorCompile"
    }

    outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to 
IncludeDir = {}
IncludeDir["ImGui"] = "3rdPart/imgui"

-- Projects
group "Dependencies"
    include "DirectXRenderer/3rdPart/imgui"
group ""

include "DirectXRenderer"
include "Sandbox"
--include "DrTool"

