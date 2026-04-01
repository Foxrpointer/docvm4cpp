add_rules("mode.debug", "mode.release")
add_includedirs("./include")
-- add_toolchains("mingw", {sdk = "D:/_CODE/_ENVIRONMENT/mingw64"})\
-- 用这个命令来添加 mode.release 的 toolchain 和 debugger：
-- ($) xmake f -p windows -a x86_64 -m release \
-- --toolchain=mingw --sdk=D:\_CODE\_ENVIRONMENT\mingw64 -c \
-- --debugger=D:\_CODE\_ENVIRONMENT\mingw64\bin\gdb

-- 编译器 SDK Libs的路径，记得改掉，换成自己的
lib_dir = "D:\\_CODE\\_ENVIRONMENT\\mingw64\\x86_64-w64-mingw32\\lib\\"

target("docvm4cpp")
    set_kind("binary")
    add_files("src/*.cpp", "src/*.c")

    add_links("./lib/libglfw3.a")
    add_links(lib_dir .. "libopengl32.a")
    add_links(lib_dir .. "libuser32.a")
    add_links(lib_dir .. "libgdi32.a")
    add_links(lib_dir .. "libshell32.a")

    set_symbols("debug")    -- 启用调试符号

--
-- If you want to known more usage about xmake, please see https://xmake.io
--
-- ## FAQ
--
-- You can enter the project directory firstly before building project.
--
--   $ cd projectdir
--
-- 1. How to build project?
--
--   $ xmake
--
-- 2. How to configure project?
--
--   $ xmake f -p [macosx|linux|iphoneos ..] -a [x86_64|i386|arm64 ..] -m [debug|release]
--
-- 3. Where is the build output directory?
--
--   The default output directory is `./build` and you can configure the output directory.
--
--   $ xmake f -o outputdir
--   $ xmake
--
-- 4. How to run and debug target after building project?
--
--   $ xmake run [targetname]
--   $ xmake run -d [targetname]
--
-- 5. How to install target to the system directory or other output directory?
--
--   $ xmake install
--   $ xmake install -o installdir
--
-- 6. Add some frequently-used compilation flags in xmake.lua
--
-- @code
--    -- add debug and release modes
--    add_rules("mode.debug", "mode.release")
--
--    -- add macro definition
--    add_defines("NDEBUG", "_GNU_SOURCE=1")
--
--    -- set warning all as error
--    set_warnings("all", "error")
--
--    -- set language: c99, c++11
--    set_languages("c99", "c++11")
--
--    -- set optimization: none, faster, fastest, smallest
--    set_optimize("fastest")
--
--    -- add include search directories
--    add_includedirs("/usr/include", "/usr/local/include")
--
--    -- add link libraries and search directories
--    add_links("tbox")
--    add_linkdirs("/usr/local/lib", "/usr/lib")
--
--    -- add system link libraries
--    add_syslinks("z", "pthread")
--
--    -- add compilation and link flags
--    add_cxflags("-stdnolib", "-fno-strict-aliasing")
--    add_ldflags("-L/usr/local/lib", "-lpthread", {force = true})
--
-- @endcode
--

