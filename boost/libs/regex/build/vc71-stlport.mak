#
# auto generated makefile for VC6+STLPort
#
# usage:
# make
#   brings libraries up to date
# make install
#   brings libraries up to date and copies binaries to your VC6 /lib and /bin directories (recomended)
#

#
# Add additional compiler options here:
#
CXXFLAGS=
#
# Add additional include directories here:
#
INCLUDES=
#
# add additional linker flags here:
#
XLFLAGS=
#
# add additional static-library creation flags here:
#
XSFLAGS=

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF "$(MSVCDIR)" == ""
!ERROR Variable MSVCDIR not set.
!ENDIF

!IF "$(STLPORT_PATH)" == ""
!ERROR Variable STLPORT_PATH not set.
!ENDIF


ALL_HEADER= ../../../boost/regex/config.hpp ../../../boost/regex/pattern_except.hpp ../../../boost/regex/regex_traits.hpp ../../../boost/regex/user.hpp ../../../boost/regex/v3/cregex.hpp ../../../boost/regex/v3/fileiter.hpp ../../../boost/regex/v3/instances.hpp ../../../boost/regex/v3/regex.hpp ../../../boost/regex/v3/regex_compile.hpp ../../../boost/regex/v3/regex_cstring.hpp ../../../boost/regex/v3/regex_format.hpp ../../../boost/regex/v3/regex_fwd.hpp ../../../boost/regex/v3/regex_kmp.hpp ../../../boost/regex/v3/regex_library_include.hpp ../../../boost/regex/v3/regex_match.hpp ../../../boost/regex/v3/regex_raw_buffer.hpp ../../../boost/regex/v3/regex_split.hpp ../../../boost/regex/v3/regex_stack.hpp ../../../boost/regex/v3/regex_synch.hpp ../../../boost/regex/v3/regex_traits.hpp ../../../boost/regex/v4/basic_regex.hpp ../../../boost/regex/v4/char_regex_traits.hpp ../../../boost/regex/v4/cregex.hpp ../../../boost/regex/v4/fileiter.hpp ../../../boost/regex/v4/instances.hpp ../../../boost/regex/v4/iterator_category.hpp ../../../boost/regex/v4/iterator_traits.hpp ../../../boost/regex/v4/match_flags.hpp ../../../boost/regex/v4/match_results.hpp ../../../boost/regex/v4/mem_block_cache.hpp ../../../boost/regex/v4/perl_matcher.hpp ../../../boost/regex/v4/perl_matcher_common.hpp ../../../boost/regex/v4/perl_matcher_non_recursive.hpp ../../../boost/regex/v4/perl_matcher_recursive.hpp ../../../boost/regex/v4/regbase.hpp ../../../boost/regex/v4/regex.hpp ../../../boost/regex/v4/regex_compile.hpp ../../../boost/regex/v4/regex_cstring.hpp ../../../boost/regex/v4/regex_format.hpp ../../../boost/regex/v4/regex_fwd.hpp ../../../boost/regex/v4/regex_grep.hpp ../../../boost/regex/v4/regex_iterator.hpp ../../../boost/regex/v4/regex_kmp.hpp ../../../boost/regex/v4/regex_match.hpp ../../../boost/regex/v4/regex_merge.hpp ../../../boost/regex/v4/regex_raw_buffer.hpp ../../../boost/regex/v4/regex_replace.hpp ../../../boost/regex/v4/regex_search.hpp ../../../boost/regex/v4/regex_split.hpp ../../../boost/regex/v4/regex_stack.hpp ../../../boost/regex/v4/regex_synch.hpp ../../../boost/regex/v4/regex_token_iterator.hpp ../../../boost/regex/v4/regex_traits.hpp ../../../boost/regex/v4/states.hpp ../../../boost/regex/v4/sub_match.hpp ../../../boost/regex/config/allocator.hpp ../../../boost/regex/config/borland.hpp ../../../boost/regex/config/cstring.hpp ../../../boost/regex/config/cwchar.hpp ../../../boost/regex/config/regex_library_include.hpp

all : main_dir libboost_regex-vc71-mt-sp-1_32_dir ./vc71-stlport/libboost_regex-vc71-mt-sp-1_32.lib boost_regex-vc71-mt-p-1_32_dir ./vc71-stlport/boost_regex-vc71-mt-p-1_32.lib libboost_regex-vc71-mt-p-1_32_dir ./vc71-stlport/libboost_regex-vc71-mt-p-1_32.lib boost_regex-vc71-mt-gdp-1_32_dir ./vc71-stlport/boost_regex-vc71-mt-gdp-1_32.lib libboost_regex-vc71-mt-sgdp-1_32_dir ./vc71-stlport/libboost_regex-vc71-mt-sgdp-1_32.lib libboost_regex-vc71-mt-gdp-1_32_dir ./vc71-stlport/libboost_regex-vc71-mt-gdp-1_32.lib

clean :  libboost_regex-vc71-mt-sp-1_32_clean boost_regex-vc71-mt-p-1_32_clean libboost_regex-vc71-mt-p-1_32_clean boost_regex-vc71-mt-gdp-1_32_clean libboost_regex-vc71-mt-sgdp-1_32_clean libboost_regex-vc71-mt-gdp-1_32_clean

install : stlport_check all
	copy vc71-stlport\libboost_regex-vc71-mt-sp-1_32.lib "$(MSVCDIR)\lib"
	copy vc71-stlport\boost_regex-vc71-mt-p-1_32.lib "$(MSVCDIR)\lib"
	copy vc71-stlport\boost_regex-vc71-mt-p-1_32.dll "$(MSVCDIR)\bin"
	copy vc71-stlport\libboost_regex-vc71-mt-p-1_32.lib "$(MSVCDIR)\lib"
	copy vc71-stlport\boost_regex-vc71-mt-gdp-1_32.lib "$(MSVCDIR)\lib"
	copy vc71-stlport\boost_regex-vc71-mt-gdp-1_32.dll "$(MSVCDIR)\bin"
	copy vc71-stlport\boost_regex-vc71-mt-gdp-1_32.pdb "$(MSVCDIR)\lib"
	copy vc71-stlport\libboost_regex-vc71-mt-sgdp-1_32.lib "$(MSVCDIR)\lib"
	copy vc71-stlport\libboost_regex-vc71-mt-sgdp-1_32.pdb "$(MSVCDIR)\lib"
	copy vc71-stlport\libboost_regex-vc71-mt-gdp-1_32.lib "$(MSVCDIR)\lib"
	copy vc71-stlport\libboost_regex-vc71-mt-gdp-1_32.pdb "$(MSVCDIR)\lib"

main_dir :
	@if not exist "vc71-stlport\$(NULL)" mkdir vc71-stlport

stlport_check : $(STLPORT_PATH)\stlport\string
	echo


########################################################
#
# section for libboost_regex-vc71-mt-sp-1_32.lib
#
########################################################
vc71-stlport/libboost_regex-vc71-mt-sp-1_32/c_regex_traits.obj: ../src/c_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MT /W3 /GX /O2 /GB /GF /Gy /I$(STLPORT_PATH)\stlport /I..\..\..\ /D_MT /DWIN32 /DNDEBUG /D_MBCS /D_LIB  /c $(CXXFLAGS) -Y- -Fo./vc71-stlport/libboost_regex-vc71-mt-sp-1_32/ -Fdvc71-stlport/libboost_regex-vc71-mt-sp-1_32.pdb ../src/c_regex_traits.cpp

vc71-stlport/libboost_regex-vc71-mt-sp-1_32/c_regex_traits_common.obj: ../src/c_regex_traits_common.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MT /W3 /GX /O2 /GB /GF /Gy /I$(STLPORT_PATH)\stlport /I..\..\..\ /D_MT /DWIN32 /DNDEBUG /D_MBCS /D_LIB  /c $(CXXFLAGS) -Y- -Fo./vc71-stlport/libboost_regex-vc71-mt-sp-1_32/ -Fdvc71-stlport/libboost_regex-vc71-mt-sp-1_32.pdb ../src/c_regex_traits_common.cpp

vc71-stlport/libboost_regex-vc71-mt-sp-1_32/cpp_regex_traits.obj: ../src/cpp_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MT /W3 /GX /O2 /GB /GF /Gy /I$(STLPORT_PATH)\stlport /I..\..\..\ /D_MT /DWIN32 /DNDEBUG /D_MBCS /D_LIB  /c $(CXXFLAGS) -Y- -Fo./vc71-stlport/libboost_regex-vc71-mt-sp-1_32/ -Fdvc71-stlport/libboost_regex-vc71-mt-sp-1_32.pdb ../src/cpp_regex_traits.cpp

vc71-stlport/libboost_regex-vc71-mt-sp-1_32/cregex.obj: ../src/cregex.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MT /W3 /GX /O2 /GB /GF /Gy /I$(STLPORT_PATH)\stlport /I..\..\..\ /D_MT /DWIN32 /DNDEBUG /D_MBCS /D_LIB  /c $(CXXFLAGS) -Y- -Fo./vc71-stlport/libboost_regex-vc71-mt-sp-1_32/ -Fdvc71-stlport/libboost_regex-vc71-mt-sp-1_32.pdb ../src/cregex.cpp

vc71-stlport/libboost_regex-vc71-mt-sp-1_32/fileiter.obj: ../src/fileiter.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MT /W3 /GX /O2 /GB /GF /Gy /I$(STLPORT_PATH)\stlport /I..\..\..\ /D_MT /DWIN32 /DNDEBUG /D_MBCS /D_LIB  /c $(CXXFLAGS) -Y- -Fo./vc71-stlport/libboost_regex-vc71-mt-sp-1_32/ -Fdvc71-stlport/libboost_regex-vc71-mt-sp-1_32.pdb ../src/fileiter.cpp

vc71-stlport/libboost_regex-vc71-mt-sp-1_32/instances.obj: ../src/instances.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MT /W3 /GX /O2 /GB /GF /Gy /I$(STLPORT_PATH)\stlport /I..\..\..\ /D_MT /DWIN32 /DNDEBUG /D_MBCS /D_LIB  /c $(CXXFLAGS) -Y- -Fo./vc71-stlport/libboost_regex-vc71-mt-sp-1_32/ -Fdvc71-stlport/libboost_regex-vc71-mt-sp-1_32.pdb ../src/instances.cpp

vc71-stlport/libboost_regex-vc71-mt-sp-1_32/posix_api.obj: ../src/posix_api.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MT /W3 /GX /O2 /GB /GF /Gy /I$(STLPORT_PATH)\stlport /I..\..\..\ /D_MT /DWIN32 /DNDEBUG /D_MBCS /D_LIB  /c $(CXXFLAGS) -Y- -Fo./vc71-stlport/libboost_regex-vc71-mt-sp-1_32/ -Fdvc71-stlport/libboost_regex-vc71-mt-sp-1_32.pdb ../src/posix_api.cpp

vc71-stlport/libboost_regex-vc71-mt-sp-1_32/regex.obj: ../src/regex.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MT /W3 /GX /O2 /GB /GF /Gy /I$(STLPORT_PATH)\stlport /I..\..\..\ /D_MT /DWIN32 /DNDEBUG /D_MBCS /D_LIB  /c $(CXXFLAGS) -Y- -Fo./vc71-stlport/libboost_regex-vc71-mt-sp-1_32/ -Fdvc71-stlport/libboost_regex-vc71-mt-sp-1_32.pdb ../src/regex.cpp

vc71-stlport/libboost_regex-vc71-mt-sp-1_32/regex_debug.obj: ../src/regex_debug.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MT /W3 /GX /O2 /GB /GF /Gy /I$(STLPORT_PATH)\stlport /I..\..\..\ /D_MT /DWIN32 /DNDEBUG /D_MBCS /D_LIB  /c $(CXXFLAGS) -Y- -Fo./vc71-stlport/libboost_regex-vc71-mt-sp-1_32/ -Fdvc71-stlport/libboost_regex-vc71-mt-sp-1_32.pdb ../src/regex_debug.cpp

vc71-stlport/libboost_regex-vc71-mt-sp-1_32/regex_synch.obj: ../src/regex_synch.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MT /W3 /GX /O2 /GB /GF /Gy /I$(STLPORT_PATH)\stlport /I..\..\..\ /D_MT /DWIN32 /DNDEBUG /D_MBCS /D_LIB  /c $(CXXFLAGS) -Y- -Fo./vc71-stlport/libboost_regex-vc71-mt-sp-1_32/ -Fdvc71-stlport/libboost_regex-vc71-mt-sp-1_32.pdb ../src/regex_synch.cpp

vc71-stlport/libboost_regex-vc71-mt-sp-1_32/w32_regex_traits.obj: ../src/w32_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MT /W3 /GX /O2 /GB /GF /Gy /I$(STLPORT_PATH)\stlport /I..\..\..\ /D_MT /DWIN32 /DNDEBUG /D_MBCS /D_LIB  /c $(CXXFLAGS) -Y- -Fo./vc71-stlport/libboost_regex-vc71-mt-sp-1_32/ -Fdvc71-stlport/libboost_regex-vc71-mt-sp-1_32.pdb ../src/w32_regex_traits.cpp

vc71-stlport/libboost_regex-vc71-mt-sp-1_32/wide_posix_api.obj: ../src/wide_posix_api.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MT /W3 /GX /O2 /GB /GF /Gy /I$(STLPORT_PATH)\stlport /I..\..\..\ /D_MT /DWIN32 /DNDEBUG /D_MBCS /D_LIB  /c $(CXXFLAGS) -Y- -Fo./vc71-stlport/libboost_regex-vc71-mt-sp-1_32/ -Fdvc71-stlport/libboost_regex-vc71-mt-sp-1_32.pdb ../src/wide_posix_api.cpp

vc71-stlport/libboost_regex-vc71-mt-sp-1_32/winstances.obj: ../src/winstances.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MT /W3 /GX /O2 /GB /GF /Gy /I$(STLPORT_PATH)\stlport /I..\..\..\ /D_MT /DWIN32 /DNDEBUG /D_MBCS /D_LIB  /c $(CXXFLAGS) -Y- -Fo./vc71-stlport/libboost_regex-vc71-mt-sp-1_32/ -Fdvc71-stlport/libboost_regex-vc71-mt-sp-1_32.pdb ../src/winstances.cpp

libboost_regex-vc71-mt-sp-1_32_dir :
	@if not exist "vc71-stlport\libboost_regex-vc71-mt-sp-1_32\$(NULL)" mkdir vc71-stlport\libboost_regex-vc71-mt-sp-1_32

libboost_regex-vc71-mt-sp-1_32_clean :
	del vc71-stlport\libboost_regex-vc71-mt-sp-1_32\*.obj
	del vc71-stlport\libboost_regex-vc71-mt-sp-1_32\*.idb
	del vc71-stlport\libboost_regex-vc71-mt-sp-1_32\*.exp
	del vc71-stlport\libboost_regex-vc71-mt-sp-1_32\*.pch

./vc71-stlport/libboost_regex-vc71-mt-sp-1_32.lib : vc71-stlport/libboost_regex-vc71-mt-sp-1_32/c_regex_traits.obj vc71-stlport/libboost_regex-vc71-mt-sp-1_32/c_regex_traits_common.obj vc71-stlport/libboost_regex-vc71-mt-sp-1_32/cpp_regex_traits.obj vc71-stlport/libboost_regex-vc71-mt-sp-1_32/cregex.obj vc71-stlport/libboost_regex-vc71-mt-sp-1_32/fileiter.obj vc71-stlport/libboost_regex-vc71-mt-sp-1_32/instances.obj vc71-stlport/libboost_regex-vc71-mt-sp-1_32/posix_api.obj vc71-stlport/libboost_regex-vc71-mt-sp-1_32/regex.obj vc71-stlport/libboost_regex-vc71-mt-sp-1_32/regex_debug.obj vc71-stlport/libboost_regex-vc71-mt-sp-1_32/regex_synch.obj vc71-stlport/libboost_regex-vc71-mt-sp-1_32/w32_regex_traits.obj vc71-stlport/libboost_regex-vc71-mt-sp-1_32/wide_posix_api.obj vc71-stlport/libboost_regex-vc71-mt-sp-1_32/winstances.obj
	link -lib /nologo /out:vc71-stlport/libboost_regex-vc71-mt-sp-1_32.lib $(XSFLAGS)  vc71-stlport/libboost_regex-vc71-mt-sp-1_32/c_regex_traits.obj vc71-stlport/libboost_regex-vc71-mt-sp-1_32/c_regex_traits_common.obj vc71-stlport/libboost_regex-vc71-mt-sp-1_32/cpp_regex_traits.obj vc71-stlport/libboost_regex-vc71-mt-sp-1_32/cregex.obj vc71-stlport/libboost_regex-vc71-mt-sp-1_32/fileiter.obj vc71-stlport/libboost_regex-vc71-mt-sp-1_32/instances.obj vc71-stlport/libboost_regex-vc71-mt-sp-1_32/posix_api.obj vc71-stlport/libboost_regex-vc71-mt-sp-1_32/regex.obj vc71-stlport/libboost_regex-vc71-mt-sp-1_32/regex_debug.obj vc71-stlport/libboost_regex-vc71-mt-sp-1_32/regex_synch.obj vc71-stlport/libboost_regex-vc71-mt-sp-1_32/w32_regex_traits.obj vc71-stlport/libboost_regex-vc71-mt-sp-1_32/wide_posix_api.obj vc71-stlport/libboost_regex-vc71-mt-sp-1_32/winstances.obj

########################################################
#
# section for boost_regex-vc71-mt-p-1_32.lib
#
########################################################
vc71-stlport/boost_regex-vc71-mt-p-1_32/c_regex_traits.obj: ../src/c_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /I$(STLPORT_PATH)\stlport /Gy /I../../../ /DBOOST_REGEX_DYN_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL  /c $(CXXFLAGS) -Y- -Fo./vc71-stlport/boost_regex-vc71-mt-p-1_32/ -Fdvc71-stlport/boost_regex-vc71-mt-p-1_32.pdb ../src/c_regex_traits.cpp

vc71-stlport/boost_regex-vc71-mt-p-1_32/c_regex_traits_common.obj: ../src/c_regex_traits_common.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /I$(STLPORT_PATH)\stlport /Gy /I../../../ /DBOOST_REGEX_DYN_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL  /c $(CXXFLAGS) -Y- -Fo./vc71-stlport/boost_regex-vc71-mt-p-1_32/ -Fdvc71-stlport/boost_regex-vc71-mt-p-1_32.pdb ../src/c_regex_traits_common.cpp

vc71-stlport/boost_regex-vc71-mt-p-1_32/cpp_regex_traits.obj: ../src/cpp_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /I$(STLPORT_PATH)\stlport /Gy /I../../../ /DBOOST_REGEX_DYN_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL  /c $(CXXFLAGS) -Y- -Fo./vc71-stlport/boost_regex-vc71-mt-p-1_32/ -Fdvc71-stlport/boost_regex-vc71-mt-p-1_32.pdb ../src/cpp_regex_traits.cpp

vc71-stlport/boost_regex-vc71-mt-p-1_32/cregex.obj: ../src/cregex.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /I$(STLPORT_PATH)\stlport /Gy /I../../../ /DBOOST_REGEX_DYN_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL  /c $(CXXFLAGS) -Y- -Fo./vc71-stlport/boost_regex-vc71-mt-p-1_32/ -Fdvc71-stlport/boost_regex-vc71-mt-p-1_32.pdb ../src/cregex.cpp

vc71-stlport/boost_regex-vc71-mt-p-1_32/fileiter.obj: ../src/fileiter.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /I$(STLPORT_PATH)\stlport /Gy /I../../../ /DBOOST_REGEX_DYN_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL  /c $(CXXFLAGS) -Y- -Fo./vc71-stlport/boost_regex-vc71-mt-p-1_32/ -Fdvc71-stlport/boost_regex-vc71-mt-p-1_32.pdb ../src/fileiter.cpp

vc71-stlport/boost_regex-vc71-mt-p-1_32/instances.obj: ../src/instances.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /I$(STLPORT_PATH)\stlport /Gy /I../../../ /DBOOST_REGEX_DYN_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL  /c $(CXXFLAGS) -Y- -Fo./vc71-stlport/boost_regex-vc71-mt-p-1_32/ -Fdvc71-stlport/boost_regex-vc71-mt-p-1_32.pdb ../src/instances.cpp

vc71-stlport/boost_regex-vc71-mt-p-1_32/posix_api.obj: ../src/posix_api.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /I$(STLPORT_PATH)\stlport /Gy /I../../../ /DBOOST_REGEX_DYN_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL  /c $(CXXFLAGS) -Y- -Fo./vc71-stlport/boost_regex-vc71-mt-p-1_32/ -Fdvc71-stlport/boost_regex-vc71-mt-p-1_32.pdb ../src/posix_api.cpp

vc71-stlport/boost_regex-vc71-mt-p-1_32/regex.obj: ../src/regex.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /I$(STLPORT_PATH)\stlport /Gy /I../../../ /DBOOST_REGEX_DYN_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL  /c $(CXXFLAGS) -Y- -Fo./vc71-stlport/boost_regex-vc71-mt-p-1_32/ -Fdvc71-stlport/boost_regex-vc71-mt-p-1_32.pdb ../src/regex.cpp

vc71-stlport/boost_regex-vc71-mt-p-1_32/regex_debug.obj: ../src/regex_debug.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /I$(STLPORT_PATH)\stlport /Gy /I../../../ /DBOOST_REGEX_DYN_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL  /c $(CXXFLAGS) -Y- -Fo./vc71-stlport/boost_regex-vc71-mt-p-1_32/ -Fdvc71-stlport/boost_regex-vc71-mt-p-1_32.pdb ../src/regex_debug.cpp

vc71-stlport/boost_regex-vc71-mt-p-1_32/regex_synch.obj: ../src/regex_synch.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /I$(STLPORT_PATH)\stlport /Gy /I../../../ /DBOOST_REGEX_DYN_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL  /c $(CXXFLAGS) -Y- -Fo./vc71-stlport/boost_regex-vc71-mt-p-1_32/ -Fdvc71-stlport/boost_regex-vc71-mt-p-1_32.pdb ../src/regex_synch.cpp

vc71-stlport/boost_regex-vc71-mt-p-1_32/w32_regex_traits.obj: ../src/w32_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /I$(STLPORT_PATH)\stlport /Gy /I../../../ /DBOOST_REGEX_DYN_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL  /c $(CXXFLAGS) -Y- -Fo./vc71-stlport/boost_regex-vc71-mt-p-1_32/ -Fdvc71-stlport/boost_regex-vc71-mt-p-1_32.pdb ../src/w32_regex_traits.cpp

vc71-stlport/boost_regex-vc71-mt-p-1_32/wide_posix_api.obj: ../src/wide_posix_api.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /I$(STLPORT_PATH)\stlport /Gy /I../../../ /DBOOST_REGEX_DYN_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL  /c $(CXXFLAGS) -Y- -Fo./vc71-stlport/boost_regex-vc71-mt-p-1_32/ -Fdvc71-stlport/boost_regex-vc71-mt-p-1_32.pdb ../src/wide_posix_api.cpp

vc71-stlport/boost_regex-vc71-mt-p-1_32/winstances.obj: ../src/winstances.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /I$(STLPORT_PATH)\stlport /Gy /I../../../ /DBOOST_REGEX_DYN_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL  /c $(CXXFLAGS) -Y- -Fo./vc71-stlport/boost_regex-vc71-mt-p-1_32/ -Fdvc71-stlport/boost_regex-vc71-mt-p-1_32.pdb ../src/winstances.cpp

boost_regex-vc71-mt-p-1_32_dir :
	@if not exist "vc71-stlport\boost_regex-vc71-mt-p-1_32\$(NULL)" mkdir vc71-stlport\boost_regex-vc71-mt-p-1_32

boost_regex-vc71-mt-p-1_32_clean :
	del vc71-stlport\boost_regex-vc71-mt-p-1_32\*.obj
	del vc71-stlport\boost_regex-vc71-mt-p-1_32\*.idb
	del vc71-stlport\boost_regex-vc71-mt-p-1_32\*.exp
	del vc71-stlport\boost_regex-vc71-mt-p-1_32\*.pch

./vc71-stlport/boost_regex-vc71-mt-p-1_32.lib : vc71-stlport/boost_regex-vc71-mt-p-1_32/c_regex_traits.obj vc71-stlport/boost_regex-vc71-mt-p-1_32/c_regex_traits_common.obj vc71-stlport/boost_regex-vc71-mt-p-1_32/cpp_regex_traits.obj vc71-stlport/boost_regex-vc71-mt-p-1_32/cregex.obj vc71-stlport/boost_regex-vc71-mt-p-1_32/fileiter.obj vc71-stlport/boost_regex-vc71-mt-p-1_32/instances.obj vc71-stlport/boost_regex-vc71-mt-p-1_32/posix_api.obj vc71-stlport/boost_regex-vc71-mt-p-1_32/regex.obj vc71-stlport/boost_regex-vc71-mt-p-1_32/regex_debug.obj vc71-stlport/boost_regex-vc71-mt-p-1_32/regex_synch.obj vc71-stlport/boost_regex-vc71-mt-p-1_32/w32_regex_traits.obj vc71-stlport/boost_regex-vc71-mt-p-1_32/wide_posix_api.obj vc71-stlport/boost_regex-vc71-mt-p-1_32/winstances.obj
	link kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:yes /pdb:"vc71-stlport/boost_regex-vc71-mt-p-1_32.pdb" /debug /machine:I386 /out:"vc71-stlport/boost_regex-vc71-mt-p-1_32.dll" /implib:"vc71-stlport/boost_regex-vc71-mt-p-1_32.lib" /LIBPATH:$(STLPORT_PATH)\lib $(XLFLAGS)  vc71-stlport/boost_regex-vc71-mt-p-1_32/c_regex_traits.obj vc71-stlport/boost_regex-vc71-mt-p-1_32/c_regex_traits_common.obj vc71-stlport/boost_regex-vc71-mt-p-1_32/cpp_regex_traits.obj vc71-stlport/boost_regex-vc71-mt-p-1_32/cregex.obj vc71-stlport/boost_regex-vc71-mt-p-1_32/fileiter.obj vc71-stlport/boost_regex-vc71-mt-p-1_32/instances.obj vc71-stlport/boost_regex-vc71-mt-p-1_32/posix_api.obj vc71-stlport/boost_regex-vc71-mt-p-1_32/regex.obj vc71-stlport/boost_regex-vc71-mt-p-1_32/regex_debug.obj vc71-stlport/boost_regex-vc71-mt-p-1_32/regex_synch.obj vc71-stlport/boost_regex-vc71-mt-p-1_32/w32_regex_traits.obj vc71-stlport/boost_regex-vc71-mt-p-1_32/wide_posix_api.obj vc71-stlport/boost_regex-vc71-mt-p-1_32/winstances.obj

########################################################
#
# section for libboost_regex-vc71-mt-p-1_32.lib
#
########################################################
vc71-stlport/libboost_regex-vc71-mt-p-1_32/c_regex_traits.obj: ../src/c_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /Gy /I$(STLPORT_PATH)\stlport /I../../../ /DBOOST_REGEX_STATIC_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL  /c $(CXXFLAGS) -Y- -Fo./vc71-stlport/libboost_regex-vc71-mt-p-1_32/ -Fdvc71-stlport/libboost_regex-vc71-mt-p-1_32.pdb ../src/c_regex_traits.cpp

vc71-stlport/libboost_regex-vc71-mt-p-1_32/c_regex_traits_common.obj: ../src/c_regex_traits_common.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /Gy /I$(STLPORT_PATH)\stlport /I../../../ /DBOOST_REGEX_STATIC_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL  /c $(CXXFLAGS) -Y- -Fo./vc71-stlport/libboost_regex-vc71-mt-p-1_32/ -Fdvc71-stlport/libboost_regex-vc71-mt-p-1_32.pdb ../src/c_regex_traits_common.cpp

vc71-stlport/libboost_regex-vc71-mt-p-1_32/cpp_regex_traits.obj: ../src/cpp_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /Gy /I$(STLPORT_PATH)\stlport /I../../../ /DBOOST_REGEX_STATIC_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL  /c $(CXXFLAGS) -Y- -Fo./vc71-stlport/libboost_regex-vc71-mt-p-1_32/ -Fdvc71-stlport/libboost_regex-vc71-mt-p-1_32.pdb ../src/cpp_regex_traits.cpp

vc71-stlport/libboost_regex-vc71-mt-p-1_32/cregex.obj: ../src/cregex.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /Gy /I$(STLPORT_PATH)\stlport /I../../../ /DBOOST_REGEX_STATIC_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL  /c $(CXXFLAGS) -Y- -Fo./vc71-stlport/libboost_regex-vc71-mt-p-1_32/ -Fdvc71-stlport/libboost_regex-vc71-mt-p-1_32.pdb ../src/cregex.cpp

vc71-stlport/libboost_regex-vc71-mt-p-1_32/fileiter.obj: ../src/fileiter.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /Gy /I$(STLPORT_PATH)\stlport /I../../../ /DBOOST_REGEX_STATIC_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL  /c $(CXXFLAGS) -Y- -Fo./vc71-stlport/libboost_regex-vc71-mt-p-1_32/ -Fdvc71-stlport/libboost_regex-vc71-mt-p-1_32.pdb ../src/fileiter.cpp

vc71-stlport/libboost_regex-vc71-mt-p-1_32/instances.obj: ../src/instances.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /Gy /I$(STLPORT_PATH)\stlport /I../../../ /DBOOST_REGEX_STATIC_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL  /c $(CXXFLAGS) -Y- -Fo./vc71-stlport/libboost_regex-vc71-mt-p-1_32/ -Fdvc71-stlport/libboost_regex-vc71-mt-p-1_32.pdb ../src/instances.cpp

vc71-stlport/libboost_regex-vc71-mt-p-1_32/posix_api.obj: ../src/posix_api.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /Gy /I$(STLPORT_PATH)\stlport /I../../../ /DBOOST_REGEX_STATIC_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL  /c $(CXXFLAGS) -Y- -Fo./vc71-stlport/libboost_regex-vc71-mt-p-1_32/ -Fdvc71-stlport/libboost_regex-vc71-mt-p-1_32.pdb ../src/posix_api.cpp

vc71-stlport/libboost_regex-vc71-mt-p-1_32/regex.obj: ../src/regex.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /Gy /I$(STLPORT_PATH)\stlport /I../../../ /DBOOST_REGEX_STATIC_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL  /c $(CXXFLAGS) -Y- -Fo./vc71-stlport/libboost_regex-vc71-mt-p-1_32/ -Fdvc71-stlport/libboost_regex-vc71-mt-p-1_32.pdb ../src/regex.cpp

vc71-stlport/libboost_regex-vc71-mt-p-1_32/regex_debug.obj: ../src/regex_debug.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /Gy /I$(STLPORT_PATH)\stlport /I../../../ /DBOOST_REGEX_STATIC_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL  /c $(CXXFLAGS) -Y- -Fo./vc71-stlport/libboost_regex-vc71-mt-p-1_32/ -Fdvc71-stlport/libboost_regex-vc71-mt-p-1_32.pdb ../src/regex_debug.cpp

vc71-stlport/libboost_regex-vc71-mt-p-1_32/regex_synch.obj: ../src/regex_synch.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /Gy /I$(STLPORT_PATH)\stlport /I../../../ /DBOOST_REGEX_STATIC_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL  /c $(CXXFLAGS) -Y- -Fo./vc71-stlport/libboost_regex-vc71-mt-p-1_32/ -Fdvc71-stlport/libboost_regex-vc71-mt-p-1_32.pdb ../src/regex_synch.cpp

vc71-stlport/libboost_regex-vc71-mt-p-1_32/w32_regex_traits.obj: ../src/w32_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /Gy /I$(STLPORT_PATH)\stlport /I../../../ /DBOOST_REGEX_STATIC_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL  /c $(CXXFLAGS) -Y- -Fo./vc71-stlport/libboost_regex-vc71-mt-p-1_32/ -Fdvc71-stlport/libboost_regex-vc71-mt-p-1_32.pdb ../src/w32_regex_traits.cpp

vc71-stlport/libboost_regex-vc71-mt-p-1_32/wide_posix_api.obj: ../src/wide_posix_api.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /Gy /I$(STLPORT_PATH)\stlport /I../../../ /DBOOST_REGEX_STATIC_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL  /c $(CXXFLAGS) -Y- -Fo./vc71-stlport/libboost_regex-vc71-mt-p-1_32/ -Fdvc71-stlport/libboost_regex-vc71-mt-p-1_32.pdb ../src/wide_posix_api.cpp

vc71-stlport/libboost_regex-vc71-mt-p-1_32/winstances.obj: ../src/winstances.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /Gy /I$(STLPORT_PATH)\stlport /I../../../ /DBOOST_REGEX_STATIC_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL  /c $(CXXFLAGS) -Y- -Fo./vc71-stlport/libboost_regex-vc71-mt-p-1_32/ -Fdvc71-stlport/libboost_regex-vc71-mt-p-1_32.pdb ../src/winstances.cpp

libboost_regex-vc71-mt-p-1_32_dir :
	@if not exist "vc71-stlport\libboost_regex-vc71-mt-p-1_32\$(NULL)" mkdir vc71-stlport\libboost_regex-vc71-mt-p-1_32

libboost_regex-vc71-mt-p-1_32_clean :
	del vc71-stlport\libboost_regex-vc71-mt-p-1_32\*.obj
	del vc71-stlport\libboost_regex-vc71-mt-p-1_32\*.idb
	del vc71-stlport\libboost_regex-vc71-mt-p-1_32\*.exp
	del vc71-stlport\libboost_regex-vc71-mt-p-1_32\*.pch

./vc71-stlport/libboost_regex-vc71-mt-p-1_32.lib : vc71-stlport/libboost_regex-vc71-mt-p-1_32/c_regex_traits.obj vc71-stlport/libboost_regex-vc71-mt-p-1_32/c_regex_traits_common.obj vc71-stlport/libboost_regex-vc71-mt-p-1_32/cpp_regex_traits.obj vc71-stlport/libboost_regex-vc71-mt-p-1_32/cregex.obj vc71-stlport/libboost_regex-vc71-mt-p-1_32/fileiter.obj vc71-stlport/libboost_regex-vc71-mt-p-1_32/instances.obj vc71-stlport/libboost_regex-vc71-mt-p-1_32/posix_api.obj vc71-stlport/libboost_regex-vc71-mt-p-1_32/regex.obj vc71-stlport/libboost_regex-vc71-mt-p-1_32/regex_debug.obj vc71-stlport/libboost_regex-vc71-mt-p-1_32/regex_synch.obj vc71-stlport/libboost_regex-vc71-mt-p-1_32/w32_regex_traits.obj vc71-stlport/libboost_regex-vc71-mt-p-1_32/wide_posix_api.obj vc71-stlport/libboost_regex-vc71-mt-p-1_32/winstances.obj
	link -lib /nologo /out:vc71-stlport/libboost_regex-vc71-mt-p-1_32.lib $(XSFLAGS)  vc71-stlport/libboost_regex-vc71-mt-p-1_32/c_regex_traits.obj vc71-stlport/libboost_regex-vc71-mt-p-1_32/c_regex_traits_common.obj vc71-stlport/libboost_regex-vc71-mt-p-1_32/cpp_regex_traits.obj vc71-stlport/libboost_regex-vc71-mt-p-1_32/cregex.obj vc71-stlport/libboost_regex-vc71-mt-p-1_32/fileiter.obj vc71-stlport/libboost_regex-vc71-mt-p-1_32/instances.obj vc71-stlport/libboost_regex-vc71-mt-p-1_32/posix_api.obj vc71-stlport/libboost_regex-vc71-mt-p-1_32/regex.obj vc71-stlport/libboost_regex-vc71-mt-p-1_32/regex_debug.obj vc71-stlport/libboost_regex-vc71-mt-p-1_32/regex_synch.obj vc71-stlport/libboost_regex-vc71-mt-p-1_32/w32_regex_traits.obj vc71-stlport/libboost_regex-vc71-mt-p-1_32/wide_posix_api.obj vc71-stlport/libboost_regex-vc71-mt-p-1_32/winstances.obj

########################################################
#
# section for boost_regex-vc71-mt-gdp-1_32.lib
#
########################################################
vc71-stlport/boost_regex-vc71-mt-gdp-1_32/c_regex_traits.obj: ../src/c_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I$(STLPORT_PATH)\stlport /I../../../ /DBOOST_REGEX_DYN_LINK /D__STL_DEBUG /D_STLP_DEBUG /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /GX /RTC1 /c $(CXXFLAGS) -Y- -Fo./vc71-stlport/boost_regex-vc71-mt-gdp-1_32/ -Fdvc71-stlport/boost_regex-vc71-mt-gdp-1_32.pdb ../src/c_regex_traits.cpp

vc71-stlport/boost_regex-vc71-mt-gdp-1_32/c_regex_traits_common.obj: ../src/c_regex_traits_common.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I$(STLPORT_PATH)\stlport /I../../../ /DBOOST_REGEX_DYN_LINK /D__STL_DEBUG /D_STLP_DEBUG /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /GX /RTC1 /c $(CXXFLAGS) -Y- -Fo./vc71-stlport/boost_regex-vc71-mt-gdp-1_32/ -Fdvc71-stlport/boost_regex-vc71-mt-gdp-1_32.pdb ../src/c_regex_traits_common.cpp

vc71-stlport/boost_regex-vc71-mt-gdp-1_32/cpp_regex_traits.obj: ../src/cpp_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I$(STLPORT_PATH)\stlport /I../../../ /DBOOST_REGEX_DYN_LINK /D__STL_DEBUG /D_STLP_DEBUG /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /GX /RTC1 /c $(CXXFLAGS) -Y- -Fo./vc71-stlport/boost_regex-vc71-mt-gdp-1_32/ -Fdvc71-stlport/boost_regex-vc71-mt-gdp-1_32.pdb ../src/cpp_regex_traits.cpp

vc71-stlport/boost_regex-vc71-mt-gdp-1_32/cregex.obj: ../src/cregex.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I$(STLPORT_PATH)\stlport /I../../../ /DBOOST_REGEX_DYN_LINK /D__STL_DEBUG /D_STLP_DEBUG /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /GX /RTC1 /c $(CXXFLAGS) -Y- -Fo./vc71-stlport/boost_regex-vc71-mt-gdp-1_32/ -Fdvc71-stlport/boost_regex-vc71-mt-gdp-1_32.pdb ../src/cregex.cpp

vc71-stlport/boost_regex-vc71-mt-gdp-1_32/fileiter.obj: ../src/fileiter.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I$(STLPORT_PATH)\stlport /I../../../ /DBOOST_REGEX_DYN_LINK /D__STL_DEBUG /D_STLP_DEBUG /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /GX /RTC1 /c $(CXXFLAGS) -Y- -Fo./vc71-stlport/boost_regex-vc71-mt-gdp-1_32/ -Fdvc71-stlport/boost_regex-vc71-mt-gdp-1_32.pdb ../src/fileiter.cpp

vc71-stlport/boost_regex-vc71-mt-gdp-1_32/instances.obj: ../src/instances.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I$(STLPORT_PATH)\stlport /I../../../ /DBOOST_REGEX_DYN_LINK /D__STL_DEBUG /D_STLP_DEBUG /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /GX /RTC1 /c $(CXXFLAGS) -Y- -Fo./vc71-stlport/boost_regex-vc71-mt-gdp-1_32/ -Fdvc71-stlport/boost_regex-vc71-mt-gdp-1_32.pdb ../src/instances.cpp

vc71-stlport/boost_regex-vc71-mt-gdp-1_32/posix_api.obj: ../src/posix_api.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I$(STLPORT_PATH)\stlport /I../../../ /DBOOST_REGEX_DYN_LINK /D__STL_DEBUG /D_STLP_DEBUG /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /GX /RTC1 /c $(CXXFLAGS) -Y- -Fo./vc71-stlport/boost_regex-vc71-mt-gdp-1_32/ -Fdvc71-stlport/boost_regex-vc71-mt-gdp-1_32.pdb ../src/posix_api.cpp

vc71-stlport/boost_regex-vc71-mt-gdp-1_32/regex.obj: ../src/regex.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I$(STLPORT_PATH)\stlport /I../../../ /DBOOST_REGEX_DYN_LINK /D__STL_DEBUG /D_STLP_DEBUG /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /GX /RTC1 /c $(CXXFLAGS) -Y- -Fo./vc71-stlport/boost_regex-vc71-mt-gdp-1_32/ -Fdvc71-stlport/boost_regex-vc71-mt-gdp-1_32.pdb ../src/regex.cpp

vc71-stlport/boost_regex-vc71-mt-gdp-1_32/regex_debug.obj: ../src/regex_debug.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I$(STLPORT_PATH)\stlport /I../../../ /DBOOST_REGEX_DYN_LINK /D__STL_DEBUG /D_STLP_DEBUG /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /GX /RTC1 /c $(CXXFLAGS) -Y- -Fo./vc71-stlport/boost_regex-vc71-mt-gdp-1_32/ -Fdvc71-stlport/boost_regex-vc71-mt-gdp-1_32.pdb ../src/regex_debug.cpp

vc71-stlport/boost_regex-vc71-mt-gdp-1_32/regex_synch.obj: ../src/regex_synch.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I$(STLPORT_PATH)\stlport /I../../../ /DBOOST_REGEX_DYN_LINK /D__STL_DEBUG /D_STLP_DEBUG /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /GX /RTC1 /c $(CXXFLAGS) -Y- -Fo./vc71-stlport/boost_regex-vc71-mt-gdp-1_32/ -Fdvc71-stlport/boost_regex-vc71-mt-gdp-1_32.pdb ../src/regex_synch.cpp

vc71-stlport/boost_regex-vc71-mt-gdp-1_32/w32_regex_traits.obj: ../src/w32_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I$(STLPORT_PATH)\stlport /I../../../ /DBOOST_REGEX_DYN_LINK /D__STL_DEBUG /D_STLP_DEBUG /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /GX /RTC1 /c $(CXXFLAGS) -Y- -Fo./vc71-stlport/boost_regex-vc71-mt-gdp-1_32/ -Fdvc71-stlport/boost_regex-vc71-mt-gdp-1_32.pdb ../src/w32_regex_traits.cpp

vc71-stlport/boost_regex-vc71-mt-gdp-1_32/wide_posix_api.obj: ../src/wide_posix_api.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I$(STLPORT_PATH)\stlport /I../../../ /DBOOST_REGEX_DYN_LINK /D__STL_DEBUG /D_STLP_DEBUG /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /GX /RTC1 /c $(CXXFLAGS) -Y- -Fo./vc71-stlport/boost_regex-vc71-mt-gdp-1_32/ -Fdvc71-stlport/boost_regex-vc71-mt-gdp-1_32.pdb ../src/wide_posix_api.cpp

vc71-stlport/boost_regex-vc71-mt-gdp-1_32/winstances.obj: ../src/winstances.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I$(STLPORT_PATH)\stlport /I../../../ /DBOOST_REGEX_DYN_LINK /D__STL_DEBUG /D_STLP_DEBUG /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /GX /RTC1 /c $(CXXFLAGS) -Y- -Fo./vc71-stlport/boost_regex-vc71-mt-gdp-1_32/ -Fdvc71-stlport/boost_regex-vc71-mt-gdp-1_32.pdb ../src/winstances.cpp

boost_regex-vc71-mt-gdp-1_32_dir :
	@if not exist "vc71-stlport\boost_regex-vc71-mt-gdp-1_32\$(NULL)" mkdir vc71-stlport\boost_regex-vc71-mt-gdp-1_32

boost_regex-vc71-mt-gdp-1_32_clean :
	del vc71-stlport\boost_regex-vc71-mt-gdp-1_32\*.obj
	del vc71-stlport\boost_regex-vc71-mt-gdp-1_32\*.idb
	del vc71-stlport\boost_regex-vc71-mt-gdp-1_32\*.exp
	del vc71-stlport\boost_regex-vc71-mt-gdp-1_32\*.pch

./vc71-stlport/boost_regex-vc71-mt-gdp-1_32.lib : vc71-stlport/boost_regex-vc71-mt-gdp-1_32/c_regex_traits.obj vc71-stlport/boost_regex-vc71-mt-gdp-1_32/c_regex_traits_common.obj vc71-stlport/boost_regex-vc71-mt-gdp-1_32/cpp_regex_traits.obj vc71-stlport/boost_regex-vc71-mt-gdp-1_32/cregex.obj vc71-stlport/boost_regex-vc71-mt-gdp-1_32/fileiter.obj vc71-stlport/boost_regex-vc71-mt-gdp-1_32/instances.obj vc71-stlport/boost_regex-vc71-mt-gdp-1_32/posix_api.obj vc71-stlport/boost_regex-vc71-mt-gdp-1_32/regex.obj vc71-stlport/boost_regex-vc71-mt-gdp-1_32/regex_debug.obj vc71-stlport/boost_regex-vc71-mt-gdp-1_32/regex_synch.obj vc71-stlport/boost_regex-vc71-mt-gdp-1_32/w32_regex_traits.obj vc71-stlport/boost_regex-vc71-mt-gdp-1_32/wide_posix_api.obj vc71-stlport/boost_regex-vc71-mt-gdp-1_32/winstances.obj
	link kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:yes /pdb:"vc71-stlport/boost_regex-vc71-mt-gdp-1_32.pdb" /debug /machine:I386 /out:"vc71-stlport/boost_regex-vc71-mt-gdp-1_32.dll" /implib:"vc71-stlport/boost_regex-vc71-mt-gdp-1_32.lib" /LIBPATH:$(STLPORT_PATH)\lib $(XLFLAGS)  vc71-stlport/boost_regex-vc71-mt-gdp-1_32/c_regex_traits.obj vc71-stlport/boost_regex-vc71-mt-gdp-1_32/c_regex_traits_common.obj vc71-stlport/boost_regex-vc71-mt-gdp-1_32/cpp_regex_traits.obj vc71-stlport/boost_regex-vc71-mt-gdp-1_32/cregex.obj vc71-stlport/boost_regex-vc71-mt-gdp-1_32/fileiter.obj vc71-stlport/boost_regex-vc71-mt-gdp-1_32/instances.obj vc71-stlport/boost_regex-vc71-mt-gdp-1_32/posix_api.obj vc71-stlport/boost_regex-vc71-mt-gdp-1_32/regex.obj vc71-stlport/boost_regex-vc71-mt-gdp-1_32/regex_debug.obj vc71-stlport/boost_regex-vc71-mt-gdp-1_32/regex_synch.obj vc71-stlport/boost_regex-vc71-mt-gdp-1_32/w32_regex_traits.obj vc71-stlport/boost_regex-vc71-mt-gdp-1_32/wide_posix_api.obj vc71-stlport/boost_regex-vc71-mt-gdp-1_32/winstances.obj

########################################################
#
# section for libboost_regex-vc71-mt-sgdp-1_32.lib
#
########################################################
vc71-stlport/libboost_regex-vc71-mt-sgdp-1_32/c_regex_traits.obj: ../src/c_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MTd /W3 /Gm /GX /Zi /Od /I$(STLPORT_PATH)\stlport /I..\..\..\ /D__STL_DEBUG /D_STLP_DEBUG /DWIN32 /D_MT /D_DEBUG /D_MBCS /D_LIB /GX /RTC1 /c $(CXXFLAGS) -Y- -Fo./vc71-stlport/libboost_regex-vc71-mt-sgdp-1_32/ -Fdvc71-stlport/libboost_regex-vc71-mt-sgdp-1_32.pdb ../src/c_regex_traits.cpp

vc71-stlport/libboost_regex-vc71-mt-sgdp-1_32/c_regex_traits_common.obj: ../src/c_regex_traits_common.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MTd /W3 /Gm /GX /Zi /Od /I$(STLPORT_PATH)\stlport /I..\..\..\ /D__STL_DEBUG /D_STLP_DEBUG /DWIN32 /D_MT /D_DEBUG /D_MBCS /D_LIB /GX /RTC1 /c $(CXXFLAGS) -Y- -Fo./vc71-stlport/libboost_regex-vc71-mt-sgdp-1_32/ -Fdvc71-stlport/libboost_regex-vc71-mt-sgdp-1_32.pdb ../src/c_regex_traits_common.cpp

vc71-stlport/libboost_regex-vc71-mt-sgdp-1_32/cpp_regex_traits.obj: ../src/cpp_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MTd /W3 /Gm /GX /Zi /Od /I$(STLPORT_PATH)\stlport /I..\..\..\ /D__STL_DEBUG /D_STLP_DEBUG /DWIN32 /D_MT /D_DEBUG /D_MBCS /D_LIB /GX /RTC1 /c $(CXXFLAGS) -Y- -Fo./vc71-stlport/libboost_regex-vc71-mt-sgdp-1_32/ -Fdvc71-stlport/libboost_regex-vc71-mt-sgdp-1_32.pdb ../src/cpp_regex_traits.cpp

vc71-stlport/libboost_regex-vc71-mt-sgdp-1_32/cregex.obj: ../src/cregex.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MTd /W3 /Gm /GX /Zi /Od /I$(STLPORT_PATH)\stlport /I..\..\..\ /D__STL_DEBUG /D_STLP_DEBUG /DWIN32 /D_MT /D_DEBUG /D_MBCS /D_LIB /GX /RTC1 /c $(CXXFLAGS) -Y- -Fo./vc71-stlport/libboost_regex-vc71-mt-sgdp-1_32/ -Fdvc71-stlport/libboost_regex-vc71-mt-sgdp-1_32.pdb ../src/cregex.cpp

vc71-stlport/libboost_regex-vc71-mt-sgdp-1_32/fileiter.obj: ../src/fileiter.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MTd /W3 /Gm /GX /Zi /Od /I$(STLPORT_PATH)\stlport /I..\..\..\ /D__STL_DEBUG /D_STLP_DEBUG /DWIN32 /D_MT /D_DEBUG /D_MBCS /D_LIB /GX /RTC1 /c $(CXXFLAGS) -Y- -Fo./vc71-stlport/libboost_regex-vc71-mt-sgdp-1_32/ -Fdvc71-stlport/libboost_regex-vc71-mt-sgdp-1_32.pdb ../src/fileiter.cpp

vc71-stlport/libboost_regex-vc71-mt-sgdp-1_32/instances.obj: ../src/instances.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MTd /W3 /Gm /GX /Zi /Od /I$(STLPORT_PATH)\stlport /I..\..\..\ /D__STL_DEBUG /D_STLP_DEBUG /DWIN32 /D_MT /D_DEBUG /D_MBCS /D_LIB /GX /RTC1 /c $(CXXFLAGS) -Y- -Fo./vc71-stlport/libboost_regex-vc71-mt-sgdp-1_32/ -Fdvc71-stlport/libboost_regex-vc71-mt-sgdp-1_32.pdb ../src/instances.cpp

vc71-stlport/libboost_regex-vc71-mt-sgdp-1_32/posix_api.obj: ../src/posix_api.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MTd /W3 /Gm /GX /Zi /Od /I$(STLPORT_PATH)\stlport /I..\..\..\ /D__STL_DEBUG /D_STLP_DEBUG /DWIN32 /D_MT /D_DEBUG /D_MBCS /D_LIB /GX /RTC1 /c $(CXXFLAGS) -Y- -Fo./vc71-stlport/libboost_regex-vc71-mt-sgdp-1_32/ -Fdvc71-stlport/libboost_regex-vc71-mt-sgdp-1_32.pdb ../src/posix_api.cpp

vc71-stlport/libboost_regex-vc71-mt-sgdp-1_32/regex.obj: ../src/regex.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MTd /W3 /Gm /GX /Zi /Od /I$(STLPORT_PATH)\stlport /I..\..\..\ /D__STL_DEBUG /D_STLP_DEBUG /DWIN32 /D_MT /D_DEBUG /D_MBCS /D_LIB /GX /RTC1 /c $(CXXFLAGS) -Y- -Fo./vc71-stlport/libboost_regex-vc71-mt-sgdp-1_32/ -Fdvc71-stlport/libboost_regex-vc71-mt-sgdp-1_32.pdb ../src/regex.cpp

vc71-stlport/libboost_regex-vc71-mt-sgdp-1_32/regex_debug.obj: ../src/regex_debug.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MTd /W3 /Gm /GX /Zi /Od /I$(STLPORT_PATH)\stlport /I..\..\..\ /D__STL_DEBUG /D_STLP_DEBUG /DWIN32 /D_MT /D_DEBUG /D_MBCS /D_LIB /GX /RTC1 /c $(CXXFLAGS) -Y- -Fo./vc71-stlport/libboost_regex-vc71-mt-sgdp-1_32/ -Fdvc71-stlport/libboost_regex-vc71-mt-sgdp-1_32.pdb ../src/regex_debug.cpp

vc71-stlport/libboost_regex-vc71-mt-sgdp-1_32/regex_synch.obj: ../src/regex_synch.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MTd /W3 /Gm /GX /Zi /Od /I$(STLPORT_PATH)\stlport /I..\..\..\ /D__STL_DEBUG /D_STLP_DEBUG /DWIN32 /D_MT /D_DEBUG /D_MBCS /D_LIB /GX /RTC1 /c $(CXXFLAGS) -Y- -Fo./vc71-stlport/libboost_regex-vc71-mt-sgdp-1_32/ -Fdvc71-stlport/libboost_regex-vc71-mt-sgdp-1_32.pdb ../src/regex_synch.cpp

vc71-stlport/libboost_regex-vc71-mt-sgdp-1_32/w32_regex_traits.obj: ../src/w32_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MTd /W3 /Gm /GX /Zi /Od /I$(STLPORT_PATH)\stlport /I..\..\..\ /D__STL_DEBUG /D_STLP_DEBUG /DWIN32 /D_MT /D_DEBUG /D_MBCS /D_LIB /GX /RTC1 /c $(CXXFLAGS) -Y- -Fo./vc71-stlport/libboost_regex-vc71-mt-sgdp-1_32/ -Fdvc71-stlport/libboost_regex-vc71-mt-sgdp-1_32.pdb ../src/w32_regex_traits.cpp

vc71-stlport/libboost_regex-vc71-mt-sgdp-1_32/wide_posix_api.obj: ../src/wide_posix_api.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MTd /W3 /Gm /GX /Zi /Od /I$(STLPORT_PATH)\stlport /I..\..\..\ /D__STL_DEBUG /D_STLP_DEBUG /DWIN32 /D_MT /D_DEBUG /D_MBCS /D_LIB /GX /RTC1 /c $(CXXFLAGS) -Y- -Fo./vc71-stlport/libboost_regex-vc71-mt-sgdp-1_32/ -Fdvc71-stlport/libboost_regex-vc71-mt-sgdp-1_32.pdb ../src/wide_posix_api.cpp

vc71-stlport/libboost_regex-vc71-mt-sgdp-1_32/winstances.obj: ../src/winstances.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MTd /W3 /Gm /GX /Zi /Od /I$(STLPORT_PATH)\stlport /I..\..\..\ /D__STL_DEBUG /D_STLP_DEBUG /DWIN32 /D_MT /D_DEBUG /D_MBCS /D_LIB /GX /RTC1 /c $(CXXFLAGS) -Y- -Fo./vc71-stlport/libboost_regex-vc71-mt-sgdp-1_32/ -Fdvc71-stlport/libboost_regex-vc71-mt-sgdp-1_32.pdb ../src/winstances.cpp

libboost_regex-vc71-mt-sgdp-1_32_dir :
	@if not exist "vc71-stlport\libboost_regex-vc71-mt-sgdp-1_32\$(NULL)" mkdir vc71-stlport\libboost_regex-vc71-mt-sgdp-1_32

libboost_regex-vc71-mt-sgdp-1_32_clean :
	del vc71-stlport\libboost_regex-vc71-mt-sgdp-1_32\*.obj
	del vc71-stlport\libboost_regex-vc71-mt-sgdp-1_32\*.idb
	del vc71-stlport\libboost_regex-vc71-mt-sgdp-1_32\*.exp
	del vc71-stlport\libboost_regex-vc71-mt-sgdp-1_32\*.pch

./vc71-stlport/libboost_regex-vc71-mt-sgdp-1_32.lib : vc71-stlport/libboost_regex-vc71-mt-sgdp-1_32/c_regex_traits.obj vc71-stlport/libboost_regex-vc71-mt-sgdp-1_32/c_regex_traits_common.obj vc71-stlport/libboost_regex-vc71-mt-sgdp-1_32/cpp_regex_traits.obj vc71-stlport/libboost_regex-vc71-mt-sgdp-1_32/cregex.obj vc71-stlport/libboost_regex-vc71-mt-sgdp-1_32/fileiter.obj vc71-stlport/libboost_regex-vc71-mt-sgdp-1_32/instances.obj vc71-stlport/libboost_regex-vc71-mt-sgdp-1_32/posix_api.obj vc71-stlport/libboost_regex-vc71-mt-sgdp-1_32/regex.obj vc71-stlport/libboost_regex-vc71-mt-sgdp-1_32/regex_debug.obj vc71-stlport/libboost_regex-vc71-mt-sgdp-1_32/regex_synch.obj vc71-stlport/libboost_regex-vc71-mt-sgdp-1_32/w32_regex_traits.obj vc71-stlport/libboost_regex-vc71-mt-sgdp-1_32/wide_posix_api.obj vc71-stlport/libboost_regex-vc71-mt-sgdp-1_32/winstances.obj
	link -lib /nologo /out:vc71-stlport/libboost_regex-vc71-mt-sgdp-1_32.lib $(XSFLAGS)  vc71-stlport/libboost_regex-vc71-mt-sgdp-1_32/c_regex_traits.obj vc71-stlport/libboost_regex-vc71-mt-sgdp-1_32/c_regex_traits_common.obj vc71-stlport/libboost_regex-vc71-mt-sgdp-1_32/cpp_regex_traits.obj vc71-stlport/libboost_regex-vc71-mt-sgdp-1_32/cregex.obj vc71-stlport/libboost_regex-vc71-mt-sgdp-1_32/fileiter.obj vc71-stlport/libboost_regex-vc71-mt-sgdp-1_32/instances.obj vc71-stlport/libboost_regex-vc71-mt-sgdp-1_32/posix_api.obj vc71-stlport/libboost_regex-vc71-mt-sgdp-1_32/regex.obj vc71-stlport/libboost_regex-vc71-mt-sgdp-1_32/regex_debug.obj vc71-stlport/libboost_regex-vc71-mt-sgdp-1_32/regex_synch.obj vc71-stlport/libboost_regex-vc71-mt-sgdp-1_32/w32_regex_traits.obj vc71-stlport/libboost_regex-vc71-mt-sgdp-1_32/wide_posix_api.obj vc71-stlport/libboost_regex-vc71-mt-sgdp-1_32/winstances.obj

########################################################
#
# section for libboost_regex-vc71-mt-gdp-1_32.lib
#
########################################################
vc71-stlport/libboost_regex-vc71-mt-gdp-1_32/c_regex_traits.obj: ../src/c_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I$(STLPORT_PATH)\stlport /I../../../ /DBOOST_REGEX_STATIC_LINK /D__STL_DEBUG /D_STLP_DEBUG /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /GX /RTC1 /c $(CXXFLAGS) -Y- -Fo./vc71-stlport/libboost_regex-vc71-mt-gdp-1_32/ -Fdvc71-stlport/libboost_regex-vc71-mt-gdp-1_32.pdb ../src/c_regex_traits.cpp

vc71-stlport/libboost_regex-vc71-mt-gdp-1_32/c_regex_traits_common.obj: ../src/c_regex_traits_common.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I$(STLPORT_PATH)\stlport /I../../../ /DBOOST_REGEX_STATIC_LINK /D__STL_DEBUG /D_STLP_DEBUG /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /GX /RTC1 /c $(CXXFLAGS) -Y- -Fo./vc71-stlport/libboost_regex-vc71-mt-gdp-1_32/ -Fdvc71-stlport/libboost_regex-vc71-mt-gdp-1_32.pdb ../src/c_regex_traits_common.cpp

vc71-stlport/libboost_regex-vc71-mt-gdp-1_32/cpp_regex_traits.obj: ../src/cpp_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I$(STLPORT_PATH)\stlport /I../../../ /DBOOST_REGEX_STATIC_LINK /D__STL_DEBUG /D_STLP_DEBUG /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /GX /RTC1 /c $(CXXFLAGS) -Y- -Fo./vc71-stlport/libboost_regex-vc71-mt-gdp-1_32/ -Fdvc71-stlport/libboost_regex-vc71-mt-gdp-1_32.pdb ../src/cpp_regex_traits.cpp

vc71-stlport/libboost_regex-vc71-mt-gdp-1_32/cregex.obj: ../src/cregex.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I$(STLPORT_PATH)\stlport /I../../../ /DBOOST_REGEX_STATIC_LINK /D__STL_DEBUG /D_STLP_DEBUG /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /GX /RTC1 /c $(CXXFLAGS) -Y- -Fo./vc71-stlport/libboost_regex-vc71-mt-gdp-1_32/ -Fdvc71-stlport/libboost_regex-vc71-mt-gdp-1_32.pdb ../src/cregex.cpp

vc71-stlport/libboost_regex-vc71-mt-gdp-1_32/fileiter.obj: ../src/fileiter.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I$(STLPORT_PATH)\stlport /I../../../ /DBOOST_REGEX_STATIC_LINK /D__STL_DEBUG /D_STLP_DEBUG /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /GX /RTC1 /c $(CXXFLAGS) -Y- -Fo./vc71-stlport/libboost_regex-vc71-mt-gdp-1_32/ -Fdvc71-stlport/libboost_regex-vc71-mt-gdp-1_32.pdb ../src/fileiter.cpp

vc71-stlport/libboost_regex-vc71-mt-gdp-1_32/instances.obj: ../src/instances.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I$(STLPORT_PATH)\stlport /I../../../ /DBOOST_REGEX_STATIC_LINK /D__STL_DEBUG /D_STLP_DEBUG /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /GX /RTC1 /c $(CXXFLAGS) -Y- -Fo./vc71-stlport/libboost_regex-vc71-mt-gdp-1_32/ -Fdvc71-stlport/libboost_regex-vc71-mt-gdp-1_32.pdb ../src/instances.cpp

vc71-stlport/libboost_regex-vc71-mt-gdp-1_32/posix_api.obj: ../src/posix_api.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I$(STLPORT_PATH)\stlport /I../../../ /DBOOST_REGEX_STATIC_LINK /D__STL_DEBUG /D_STLP_DEBUG /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /GX /RTC1 /c $(CXXFLAGS) -Y- -Fo./vc71-stlport/libboost_regex-vc71-mt-gdp-1_32/ -Fdvc71-stlport/libboost_regex-vc71-mt-gdp-1_32.pdb ../src/posix_api.cpp

vc71-stlport/libboost_regex-vc71-mt-gdp-1_32/regex.obj: ../src/regex.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I$(STLPORT_PATH)\stlport /I../../../ /DBOOST_REGEX_STATIC_LINK /D__STL_DEBUG /D_STLP_DEBUG /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /GX /RTC1 /c $(CXXFLAGS) -Y- -Fo./vc71-stlport/libboost_regex-vc71-mt-gdp-1_32/ -Fdvc71-stlport/libboost_regex-vc71-mt-gdp-1_32.pdb ../src/regex.cpp

vc71-stlport/libboost_regex-vc71-mt-gdp-1_32/regex_debug.obj: ../src/regex_debug.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I$(STLPORT_PATH)\stlport /I../../../ /DBOOST_REGEX_STATIC_LINK /D__STL_DEBUG /D_STLP_DEBUG /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /GX /RTC1 /c $(CXXFLAGS) -Y- -Fo./vc71-stlport/libboost_regex-vc71-mt-gdp-1_32/ -Fdvc71-stlport/libboost_regex-vc71-mt-gdp-1_32.pdb ../src/regex_debug.cpp

vc71-stlport/libboost_regex-vc71-mt-gdp-1_32/regex_synch.obj: ../src/regex_synch.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I$(STLPORT_PATH)\stlport /I../../../ /DBOOST_REGEX_STATIC_LINK /D__STL_DEBUG /D_STLP_DEBUG /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /GX /RTC1 /c $(CXXFLAGS) -Y- -Fo./vc71-stlport/libboost_regex-vc71-mt-gdp-1_32/ -Fdvc71-stlport/libboost_regex-vc71-mt-gdp-1_32.pdb ../src/regex_synch.cpp

vc71-stlport/libboost_regex-vc71-mt-gdp-1_32/w32_regex_traits.obj: ../src/w32_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I$(STLPORT_PATH)\stlport /I../../../ /DBOOST_REGEX_STATIC_LINK /D__STL_DEBUG /D_STLP_DEBUG /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /GX /RTC1 /c $(CXXFLAGS) -Y- -Fo./vc71-stlport/libboost_regex-vc71-mt-gdp-1_32/ -Fdvc71-stlport/libboost_regex-vc71-mt-gdp-1_32.pdb ../src/w32_regex_traits.cpp

vc71-stlport/libboost_regex-vc71-mt-gdp-1_32/wide_posix_api.obj: ../src/wide_posix_api.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I$(STLPORT_PATH)\stlport /I../../../ /DBOOST_REGEX_STATIC_LINK /D__STL_DEBUG /D_STLP_DEBUG /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /GX /RTC1 /c $(CXXFLAGS) -Y- -Fo./vc71-stlport/libboost_regex-vc71-mt-gdp-1_32/ -Fdvc71-stlport/libboost_regex-vc71-mt-gdp-1_32.pdb ../src/wide_posix_api.cpp

vc71-stlport/libboost_regex-vc71-mt-gdp-1_32/winstances.obj: ../src/winstances.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I$(STLPORT_PATH)\stlport /I../../../ /DBOOST_REGEX_STATIC_LINK /D__STL_DEBUG /D_STLP_DEBUG /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /GX /RTC1 /c $(CXXFLAGS) -Y- -Fo./vc71-stlport/libboost_regex-vc71-mt-gdp-1_32/ -Fdvc71-stlport/libboost_regex-vc71-mt-gdp-1_32.pdb ../src/winstances.cpp

libboost_regex-vc71-mt-gdp-1_32_dir :
	@if not exist "vc71-stlport\libboost_regex-vc71-mt-gdp-1_32\$(NULL)" mkdir vc71-stlport\libboost_regex-vc71-mt-gdp-1_32

libboost_regex-vc71-mt-gdp-1_32_clean :
	del vc71-stlport\libboost_regex-vc71-mt-gdp-1_32\*.obj
	del vc71-stlport\libboost_regex-vc71-mt-gdp-1_32\*.idb
	del vc71-stlport\libboost_regex-vc71-mt-gdp-1_32\*.exp
	del vc71-stlport\libboost_regex-vc71-mt-gdp-1_32\*.pch

./vc71-stlport/libboost_regex-vc71-mt-gdp-1_32.lib : vc71-stlport/libboost_regex-vc71-mt-gdp-1_32/c_regex_traits.obj vc71-stlport/libboost_regex-vc71-mt-gdp-1_32/c_regex_traits_common.obj vc71-stlport/libboost_regex-vc71-mt-gdp-1_32/cpp_regex_traits.obj vc71-stlport/libboost_regex-vc71-mt-gdp-1_32/cregex.obj vc71-stlport/libboost_regex-vc71-mt-gdp-1_32/fileiter.obj vc71-stlport/libboost_regex-vc71-mt-gdp-1_32/instances.obj vc71-stlport/libboost_regex-vc71-mt-gdp-1_32/posix_api.obj vc71-stlport/libboost_regex-vc71-mt-gdp-1_32/regex.obj vc71-stlport/libboost_regex-vc71-mt-gdp-1_32/regex_debug.obj vc71-stlport/libboost_regex-vc71-mt-gdp-1_32/regex_synch.obj vc71-stlport/libboost_regex-vc71-mt-gdp-1_32/w32_regex_traits.obj vc71-stlport/libboost_regex-vc71-mt-gdp-1_32/wide_posix_api.obj vc71-stlport/libboost_regex-vc71-mt-gdp-1_32/winstances.obj
	link -lib /nologo /out:vc71-stlport/libboost_regex-vc71-mt-gdp-1_32.lib $(XSFLAGS)  vc71-stlport/libboost_regex-vc71-mt-gdp-1_32/c_regex_traits.obj vc71-stlport/libboost_regex-vc71-mt-gdp-1_32/c_regex_traits_common.obj vc71-stlport/libboost_regex-vc71-mt-gdp-1_32/cpp_regex_traits.obj vc71-stlport/libboost_regex-vc71-mt-gdp-1_32/cregex.obj vc71-stlport/libboost_regex-vc71-mt-gdp-1_32/fileiter.obj vc71-stlport/libboost_regex-vc71-mt-gdp-1_32/instances.obj vc71-stlport/libboost_regex-vc71-mt-gdp-1_32/posix_api.obj vc71-stlport/libboost_regex-vc71-mt-gdp-1_32/regex.obj vc71-stlport/libboost_regex-vc71-mt-gdp-1_32/regex_debug.obj vc71-stlport/libboost_regex-vc71-mt-gdp-1_32/regex_synch.obj vc71-stlport/libboost_regex-vc71-mt-gdp-1_32/w32_regex_traits.obj vc71-stlport/libboost_regex-vc71-mt-gdp-1_32/wide_posix_api.obj vc71-stlport/libboost_regex-vc71-mt-gdp-1_32/winstances.obj

