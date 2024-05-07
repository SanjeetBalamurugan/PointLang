-- premake5.lua
local io = require "io"

function is_windows()
  return package.config:sub(1,1) == "\\"
end

function is_unix()
  return not is_windows()
end

local function get_program_path(program_name)
  local command = "which"
  if is_windows() then
    command = "where"
  end
  local handle = io.popen(command.." "..program_name)
  
  if handle == nil then
    return nil
  end

  local path = handle:read("a")
  handle:close()
  return path
end


workspace "PointLang"
   configurations { "Debug", "Release" }

project "PointLang"
   kind "ConsoleApp"
   language "C++"
   targetdir "bin/%{cfg.buildcfg}"

   files { "src/**.h", "src/**.cpp" }

  local mold = get_program_path("mold")
  if mold ~= nil then
    linkoptions { "-fuse-ld=mold" }
  end

   filter "configurations:Debug"
      defines { "DEBUG" }
      symbols "On"

   filter "configurations:Release"
      defines { "NDEBUG" }
      optimize "On"

  
  
