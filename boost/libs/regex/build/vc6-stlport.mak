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


ALL_HEADER= ../../../boost/regex/config.hpp ../../../boost/regex/pattern_except.hpp ../../../boost/regex/regex_traits.hpp ../../../boost/regex/user.hpp ../../../boost/regex/v3/cregex.hpp ../../../boost/regex/v3/fileiter.hpp ../../../boost/regex/v3/instances.hpp ../../../boost/regex/v3/regex.hpp ../../../boost/regex/v3/regex_compile.hpp ../../../boost/regex/v3/regex_cstring.hpp ../../../boost/regex/v3/regex_format.hpp ../../../boost/regex/v3/regex_fwd.hpp ../../../boost/regex/v3/regex_kmp.hpp ../../../boost/regex/v3/regex_library_include.hpp ../../../boost/regex/v3/regex_match.hpp ../../../boost/regex/v3/regex_raw_buffer.hpp ../../../boost/regex/v3/regex_split.hpp ../../../boost/regex/v3/regex_stack.hpp ../../../boost/regex/v3/regex_synch.hpp ../../../boost/regex/v3/regex_traits.hpp

all : main_dir libboost_regex_vc6-stlport_ms_dir ./vc6-stlport/libboost_regex_vc6-stlport_ms.lib libboost_regex_vc6-stlport_msd_dir ./vc6-stlport/libboost_regex_vc6-stlport_msd.lib boost_regex_vc6-stlport_mdd_dir ./vc6-stlport/boost_regex_vc6-stlport_mdd.lib boost_regex_vc6-stlport_md_dir ./vc6-stlport/boost_regex_vc6-stlport_md.lib libboost_regex_vc6-stlport_md_dir ./vc6-stlport/libboost_regex_vc6-stlport_md.lib libboost_regex_vc6-stlport_mdd_dir ./vc6-stlport/libboost_regex_vc6-stlport_mdd.lib boost_regex_vc6-stlport_mddd_dir ./vc6-stlport/boost_regex_vc6-stlport_mddd.lib libboost_regex_vc6-stlport_msdd_dir ./vc6-stlport/libboost_regex_vc6-stlport_msdd.lib libboost_regex_vc6-stlport_mddd_dir ./vc6-stlport/libboost_regex_vc6-stlport_mddd.lib

clean :  libboost_regex_vc6-stlport_ms_clean libboost_regex_vc6-stlport_msd_clean boost_regex_vc6-stlport_mdd_clean boost_regex_vc6-stlport_md_clean libboost_regex_vc6-stlport_md_clean libboost_regex_vc6-stlport_mdd_clean boost_regex_vc6-stlport_mddd_clean libboost_regex_vc6-stlport_msdd_clean libboost_regex_vc6-stlport_mddd_clean

install : stlport_check all
	copy vc6-stlport\libboost_regex_vc6-stlport_ms.lib "$(MSVCDIR)\lib"
	copy vc6-stlport\libboost_regex_vc6-stlport_msd.lib "$(MSVCDIR)\lib"
	copy vc6-stlport\boost_regex_vc6-stlport_mdd.lib "$(MSVCDIR)\lib"
	copy vc6-stlport\boost_regex_vc6-stlport_mdd.dll "$(MSVCDIR)\bin"
	copy vc6-stlport\boost_regex_vc6-stlport_md.lib "$(MSVCDIR)\lib"
	copy vc6-stlport\boost_regex_vc6-stlport_md.dll "$(MSVCDIR)\bin"
	copy vc6-stlport\libboost_regex_vc6-stlport_md.lib "$(MSVCDIR)\lib"
	copy vc6-stlport\libboost_regex_vc6-stlport_mdd.lib "$(MSVCDIR)\lib"
	copy vc6-stlport\boost_regex_vc6-stlport_mddd.lib "$(MSVCDIR)\lib"
	copy vc6-stlport\boost_regex_vc6-stlport_mddd.dll "$(MSVCDIR)\bin"
	copy vc6-stlport\boost_regex_vc6-stlport_mddd.pdb "$(MSVCDIR)\lib"
	copy vc6-stlport\libboost_regex_vc6-stlport_msdd.lib "$(MSVCDIR)\lib"
	copy vc6-stlport\libboost_regex_vc6-stlport_msdd.pdb "$(MSVCDIR)\lib"
	copy vc6-stlport\libboost_regex_vc6-stlport_mddd.lib "$(MSVCDIR)\lib"
	copy vc6-stlport\libboost_regex_vc6-stlport_mddd.pdb "$(MSVCDIR)\lib"

main_dir :
	@if not exist "vc6-stlport\$(NULL)" mkdir vc6-stlport

stlport_check : $(STLPORT_PATH)\stlport\string
	echo


########################################################
#
# section for libboost_regex_vc6-stlport_ms.lib
#
########################################################
vc6-stlport/libboost_regex_vc6-stlport_ms/c_regex_traits.obj: ../src/c_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MT /W3 /GX /O2 /GB /GF /Gy /I$(STLPORT_PATH)\stlport /I..\..\..\ /D_MT /DWIN32 /DNDEBUG /D_MBCS /D_LIB /YX /FD /c $(CXXFLAGS) -Fpvc6-stlport/libboost_regex_vc6-stlport_ms/libboost_regex_vc6-stlport_ms.pch -Fo./vc6-stlport/libboost_regex_vc6-stlport_ms/ -Fdvc6-stlport/libboost_regex_vc6-stlport_ms.pdb ../src/c_regex_traits.cpp

vc6-stlport/libboost_regex_vc6-stlport_ms/c_regex_traits_common.obj: ../src/c_regex_traits_common.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MT /W3 /GX /O2 /GB /GF /Gy /I$(STLPORT_PATH)\stlport /I..\..\..\ /D_MT /DWIN32 /DNDEBUG /D_MBCS /D_LIB /YX /FD /c $(CXXFLAGS) -Fpvc6-stlport/libboost_regex_vc6-stlport_ms/libboost_regex_vc6-stlport_ms.pch -Fo./vc6-stlport/libboost_regex_vc6-stlport_ms/ -Fdvc6-stlport/libboost_regex_vc6-stlport_ms.pdb ../src/c_regex_traits_common.cpp

vc6-stlport/libboost_regex_vc6-stlport_ms/cpp_regex_traits.obj: ../src/cpp_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MT /W3 /GX /O2 /GB /GF /Gy /I$(STLPORT_PATH)\stlport /I..\..\..\ /D_MT /DWIN32 /DNDEBUG /D_MBCS /D_LIB /YX /FD /c $(CXXFLAGS) -Fpvc6-stlport/libboost_regex_vc6-stlport_ms/libboost_regex_vc6-stlport_ms.pch -Fo./vc6-stlport/libboost_regex_vc6-stlport_ms/ -Fdvc6-stlport/libboost_regex_vc6-stlport_ms.pdb ../src/cpp_regex_traits.cpp

vc6-stlport/libboost_regex_vc6-stlport_ms/cregex.obj: ../src/cregex.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MT /W3 /GX /O2 /GB /GF /Gy /I$(STLPORT_PATH)\stlport /I..\..\..\ /D_MT /DWIN32 /DNDEBUG /D_MBCS /D_LIB /YX /FD /c $(CXXFLAGS) -Fpvc6-stlport/libboost_regex_vc6-stlport_ms/libboost_regex_vc6-stlport_ms.pch -Fo./vc6-stlport/libboost_regex_vc6-stlport_ms/ -Fdvc6-stlport/libboost_regex_vc6-stlport_ms.pdb ../src/cregex.cpp

vc6-stlport/libboost_regex_vc6-stlport_ms/fileiter.obj: ../src/fileiter.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MT /W3 /GX /O2 /GB /GF /Gy /I$(STLPORT_PATH)\stlport /I..\..\..\ /D_MT /DWIN32 /DNDEBUG /D_MBCS /D_LIB /YX /FD /c $(CXXFLAGS) -Fpvc6-stlport/libboost_regex_vc6-stlport_ms/libboost_regex_vc6-stlport_ms.pch -Fo./vc6-stlport/libboost_regex_vc6-stlport_ms/ -Fdvc6-stlport/libboost_regex_vc6-stlport_ms.pdb ../src/fileiter.cpp

vc6-stlport/libboost_regex_vc6-stlport_ms/instances.obj: ../src/instances.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MT /W3 /GX /O2 /GB /GF /Gy /I$(STLPORT_PATH)\stlport /I..\..\..\ /D_MT /DWIN32 /DNDEBUG /D_MBCS /D_LIB /YX /FD /c $(CXXFLAGS) -Fpvc6-stlport/libboost_regex_vc6-stlport_ms/libboost_regex_vc6-stlport_ms.pch -Fo./vc6-stlport/libboost_regex_vc6-stlport_ms/ -Fdvc6-stlport/libboost_regex_vc6-stlport_ms.pdb ../src/instances.cpp

vc6-stlport/libboost_regex_vc6-stlport_ms/posix_api.obj: ../src/posix_api.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MT /W3 /GX /O2 /GB /GF /Gy /I$(STLPORT_PATH)\stlport /I..\..\..\ /D_MT /DWIN32 /DNDEBUG /D_MBCS /D_LIB /YX /FD /c $(CXXFLAGS) -Fpvc6-stlport/libboost_regex_vc6-stlport_ms/libboost_regex_vc6-stlport_ms.pch -Fo./vc6-stlport/libboost_regex_vc6-stlport_ms/ -Fdvc6-stlport/libboost_regex_vc6-stlport_ms.pdb ../src/posix_api.cpp

vc6-stlport/libboost_regex_vc6-stlport_ms/regex.obj: ../src/regex.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MT /W3 /GX /O2 /GB /GF /Gy /I$(STLPORT_PATH)\stlport /I..\..\..\ /D_MT /DWIN32 /DNDEBUG /D_MBCS /D_LIB /YX /FD /c $(CXXFLAGS) -Fpvc6-stlport/libboost_regex_vc6-stlport_ms/libboost_regex_vc6-stlport_ms.pch -Fo./vc6-stlport/libboost_regex_vc6-stlport_ms/ -Fdvc6-stlport/libboost_regex_vc6-stlport_ms.pdb ../src/regex.cpp

vc6-stlport/libboost_regex_vc6-stlport_ms/regex_debug.obj: ../src/regex_debug.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MT /W3 /GX /O2 /GB /GF /Gy /I$(STLPORT_PATH)\stlport /I..\..\..\ /D_MT /DWIN32 /DNDEBUG /D_MBCS /D_LIB /YX /FD /c $(CXXFLAGS) -Fpvc6-stlport/libboost_regex_vc6-stlport_ms/libboost_regex_vc6-stlport_ms.pch -Fo./vc6-stlport/libboost_regex_vc6-stlport_ms/ -Fdvc6-stlport/libboost_regex_vc6-stlport_ms.pdb ../src/regex_debug.cpp

vc6-stlport/libboost_regex_vc6-stlport_ms/regex_synch.obj: ../src/regex_synch.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MT /W3 /GX /O2 /GB /GF /Gy /I$(STLPORT_PATH)\stlport /I..\..\..\ /D_MT /DWIN32 /DNDEBUG /D_MBCS /D_LIB /YX /FD /c $(CXXFLAGS) -Fpvc6-stlport/libboost_regex_vc6-stlport_ms/libboost_regex_vc6-stlport_ms.pch -Fo./vc6-stlport/libboost_regex_vc6-stlport_ms/ -Fdvc6-stlport/libboost_regex_vc6-stlport_ms.pdb ../src/regex_synch.cpp

vc6-stlport/libboost_regex_vc6-stlport_ms/w32_regex_traits.obj: ../src/w32_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MT /W3 /GX /O2 /GB /GF /Gy /I$(STLPORT_PATH)\stlport /I..\..\..\ /D_MT /DWIN32 /DNDEBUG /D_MBCS /D_LIB /YX /FD /c $(CXXFLAGS) -Fpvc6-stlport/libboost_regex_vc6-stlport_ms/libboost_regex_vc6-stlport_ms.pch -Fo./vc6-stlport/libboost_regex_vc6-stlport_ms/ -Fdvc6-stlport/libboost_regex_vc6-stlport_ms.pdb ../src/w32_regex_traits.cpp

vc6-stlport/libboost_regex_vc6-stlport_ms/wide_posix_api.obj: ../src/wide_posix_api.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MT /W3 /GX /O2 /GB /GF /Gy /I$(STLPORT_PATH)\stlport /I..\..\..\ /D_MT /DWIN32 /DNDEBUG /D_MBCS /D_LIB /YX /FD /c $(CXXFLAGS) -Fpvc6-stlport/libboost_regex_vc6-stlport_ms/libboost_regex_vc6-stlport_ms.pch -Fo./vc6-stlport/libboost_regex_vc6-stlport_ms/ -Fdvc6-stlport/libboost_regex_vc6-stlport_ms.pdb ../src/wide_posix_api.cpp

vc6-stlport/libboost_regex_vc6-stlport_ms/winstances.obj: ../src/winstances.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MT /W3 /GX /O2 /GB /GF /Gy /I$(STLPORT_PATH)\stlport /I..\..\..\ /D_MT /DWIN32 /DNDEBUG /D_MBCS /D_LIB /YX /FD /c $(CXXFLAGS) -Fpvc6-stlport/libboost_regex_vc6-stlport_ms/libboost_regex_vc6-stlport_ms.pch -Fo./vc6-stlport/libboost_regex_vc6-stlport_ms/ -Fdvc6-stlport/libboost_regex_vc6-stlport_ms.pdb ../src/winstances.cpp

libboost_regex_vc6-stlport_ms_dir :
	@if not exist "vc6-stlport\libboost_regex_vc6-stlport_ms\$(NULL)" mkdir vc6-stlport\libboost_regex_vc6-stlport_ms

libboost_regex_vc6-stlport_ms_clean :
	del vc6-stlport\libboost_regex_vc6-stlport_ms\*.obj
	del vc6-stlport\libboost_regex_vc6-stlport_ms\*.idb
	del vc6-stlport\libboost_regex_vc6-stlport_ms\*.exp
	del vc6-stlport\libboost_regex_vc6-stlport_ms\*.pch

./vc6-stlport/libboost_regex_vc6-stlport_ms.lib : vc6-stlport/libboost_regex_vc6-stlport_ms/c_regex_traits.obj vc6-stlport/libboost_regex_vc6-stlport_ms/c_regex_traits_common.obj vc6-stlport/libboost_regex_vc6-stlport_ms/cpp_regex_traits.obj vc6-stlport/libboost_regex_vc6-stlport_ms/cregex.obj vc6-stlport/libboost_regex_vc6-stlport_ms/fileiter.obj vc6-stlport/libboost_regex_vc6-stlport_ms/instances.obj vc6-stlport/libboost_regex_vc6-stlport_ms/posix_api.obj vc6-stlport/libboost_regex_vc6-stlport_ms/regex.obj vc6-stlport/libboost_regex_vc6-stlport_ms/regex_debug.obj vc6-stlport/libboost_regex_vc6-stlport_ms/regex_synch.obj vc6-stlport/libboost_regex_vc6-stlport_ms/w32_regex_traits.obj vc6-stlport/libboost_regex_vc6-stlport_ms/wide_posix_api.obj vc6-stlport/libboost_regex_vc6-stlport_ms/winstances.obj
	link -lib /nologo /out:vc6-stlport/libboost_regex_vc6-stlport_ms.lib $(XSFLAGS)  vc6-stlport/libboost_regex_vc6-stlport_ms/c_regex_traits.obj vc6-stlport/libboost_regex_vc6-stlport_ms/c_regex_traits_common.obj vc6-stlport/libboost_regex_vc6-stlport_ms/cpp_regex_traits.obj vc6-stlport/libboost_regex_vc6-stlport_ms/cregex.obj vc6-stlport/libboost_regex_vc6-stlport_ms/fileiter.obj vc6-stlport/libboost_regex_vc6-stlport_ms/instances.obj vc6-stlport/libboost_regex_vc6-stlport_ms/posix_api.obj vc6-stlport/libboost_regex_vc6-stlport_ms/regex.obj vc6-stlport/libboost_regex_vc6-stlport_ms/regex_debug.obj vc6-stlport/libboost_regex_vc6-stlport_ms/regex_synch.obj vc6-stlport/libboost_regex_vc6-stlport_ms/w32_regex_traits.obj vc6-stlport/libboost_regex_vc6-stlport_ms/wide_posix_api.obj vc6-stlport/libboost_regex_vc6-stlport_ms/winstances.obj

########################################################
#
# section for libboost_regex_vc6-stlport_msd.lib
#
########################################################
vc6-stlport/libboost_regex_vc6-stlport_msd/c_regex_traits.obj: ../src/c_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MTd /W3 /Gm /GX /Zi /Od /I$(STLPORT_PATH)\stlport /I..\..\..\ /DWIN32 /D_MT /D_DEBUG /D_MBCS /D_LIB /YX /FD /GZ  /c $(CXXFLAGS) -Fpvc6-stlport/libboost_regex_vc6-stlport_msd/libboost_regex_vc6-stlport_msd.pch -Fo./vc6-stlport/libboost_regex_vc6-stlport_msd/ -Fdvc6-stlport/libboost_regex_vc6-stlport_msd.pdb ../src/c_regex_traits.cpp

vc6-stlport/libboost_regex_vc6-stlport_msd/c_regex_traits_common.obj: ../src/c_regex_traits_common.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MTd /W3 /Gm /GX /Zi /Od /I$(STLPORT_PATH)\stlport /I..\..\..\ /DWIN32 /D_MT /D_DEBUG /D_MBCS /D_LIB /YX /FD /GZ  /c $(CXXFLAGS) -Fpvc6-stlport/libboost_regex_vc6-stlport_msd/libboost_regex_vc6-stlport_msd.pch -Fo./vc6-stlport/libboost_regex_vc6-stlport_msd/ -Fdvc6-stlport/libboost_regex_vc6-stlport_msd.pdb ../src/c_regex_traits_common.cpp

vc6-stlport/libboost_regex_vc6-stlport_msd/cpp_regex_traits.obj: ../src/cpp_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MTd /W3 /Gm /GX /Zi /Od /I$(STLPORT_PATH)\stlport /I..\..\..\ /DWIN32 /D_MT /D_DEBUG /D_MBCS /D_LIB /YX /FD /GZ  /c $(CXXFLAGS) -Fpvc6-stlport/libboost_regex_vc6-stlport_msd/libboost_regex_vc6-stlport_msd.pch -Fo./vc6-stlport/libboost_regex_vc6-stlport_msd/ -Fdvc6-stlport/libboost_regex_vc6-stlport_msd.pdb ../src/cpp_regex_traits.cpp

vc6-stlport/libboost_regex_vc6-stlport_msd/cregex.obj: ../src/cregex.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MTd /W3 /Gm /GX /Zi /Od /I$(STLPORT_PATH)\stlport /I..\..\..\ /DWIN32 /D_MT /D_DEBUG /D_MBCS /D_LIB /YX /FD /GZ  /c $(CXXFLAGS) -Fpvc6-stlport/libboost_regex_vc6-stlport_msd/libboost_regex_vc6-stlport_msd.pch -Fo./vc6-stlport/libboost_regex_vc6-stlport_msd/ -Fdvc6-stlport/libboost_regex_vc6-stlport_msd.pdb ../src/cregex.cpp

vc6-stlport/libboost_regex_vc6-stlport_msd/fileiter.obj: ../src/fileiter.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MTd /W3 /Gm /GX /Zi /Od /I$(STLPORT_PATH)\stlport /I..\..\..\ /DWIN32 /D_MT /D_DEBUG /D_MBCS /D_LIB /YX /FD /GZ  /c $(CXXFLAGS) -Fpvc6-stlport/libboost_regex_vc6-stlport_msd/libboost_regex_vc6-stlport_msd.pch -Fo./vc6-stlport/libboost_regex_vc6-stlport_msd/ -Fdvc6-stlport/libboost_regex_vc6-stlport_msd.pdb ../src/fileiter.cpp

vc6-stlport/libboost_regex_vc6-stlport_msd/instances.obj: ../src/instances.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MTd /W3 /Gm /GX /Zi /Od /I$(STLPORT_PATH)\stlport /I..\..\..\ /DWIN32 /D_MT /D_DEBUG /D_MBCS /D_LIB /YX /FD /GZ  /c $(CXXFLAGS) -Fpvc6-stlport/libboost_regex_vc6-stlport_msd/libboost_regex_vc6-stlport_msd.pch -Fo./vc6-stlport/libboost_regex_vc6-stlport_msd/ -Fdvc6-stlport/libboost_regex_vc6-stlport_msd.pdb ../src/instances.cpp

vc6-stlport/libboost_regex_vc6-stlport_msd/posix_api.obj: ../src/posix_api.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MTd /W3 /Gm /GX /Zi /Od /I$(STLPORT_PATH)\stlport /I..\..\..\ /DWIN32 /D_MT /D_DEBUG /D_MBCS /D_LIB /YX /FD /GZ  /c $(CXXFLAGS) -Fpvc6-stlport/libboost_regex_vc6-stlport_msd/libboost_regex_vc6-stlport_msd.pch -Fo./vc6-stlport/libboost_regex_vc6-stlport_msd/ -Fdvc6-stlport/libboost_regex_vc6-stlport_msd.pdb ../src/posix_api.cpp

vc6-stlport/libboost_regex_vc6-stlport_msd/regex.obj: ../src/regex.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MTd /W3 /Gm /GX /Zi /Od /I$(STLPORT_PATH)\stlport /I..\..\..\ /DWIN32 /D_MT /D_DEBUG /D_MBCS /D_LIB /YX /FD /GZ  /c $(CXXFLAGS) -Fpvc6-stlport/libboost_regex_vc6-stlport_msd/libboost_regex_vc6-stlport_msd.pch -Fo./vc6-stlport/libboost_regex_vc6-stlport_msd/ -Fdvc6-stlport/libboost_regex_vc6-stlport_msd.pdb ../src/regex.cpp

vc6-stlport/libboost_regex_vc6-stlport_msd/regex_debug.obj: ../src/regex_debug.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MTd /W3 /Gm /GX /Zi /Od /I$(STLPORT_PATH)\stlport /I..\..\..\ /DWIN32 /D_MT /D_DEBUG /D_MBCS /D_LIB /YX /FD /GZ  /c $(CXXFLAGS) -Fpvc6-stlport/libboost_regex_vc6-stlport_msd/libboost_regex_vc6-stlport_msd.pch -Fo./vc6-stlport/libboost_regex_vc6-stlport_msd/ -Fdvc6-stlport/libboost_regex_vc6-stlport_msd.pdb ../src/regex_debug.cpp

vc6-stlport/libboost_regex_vc6-stlport_msd/regex_synch.obj: ../src/regex_synch.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MTd /W3 /Gm /GX /Zi /Od /I$(STLPORT_PATH)\stlport /I..\..\..\ /DWIN32 /D_MT /D_DEBUG /D_MBCS /D_LIB /YX /FD /GZ  /c $(CXXFLAGS) -Fpvc6-stlport/libboost_regex_vc6-stlport_msd/libboost_regex_vc6-stlport_msd.pch -Fo./vc6-stlport/libboost_regex_vc6-stlport_msd/ -Fdvc6-stlport/libboost_regex_vc6-stlport_msd.pdb ../src/regex_synch.cpp

vc6-stlport/libboost_regex_vc6-stlport_msd/w32_regex_traits.obj: ../src/w32_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MTd /W3 /Gm /GX /Zi /Od /I$(STLPORT_PATH)\stlport /I..\..\..\ /DWIN32 /D_MT /D_DEBUG /D_MBCS /D_LIB /YX /FD /GZ  /c $(CXXFLAGS) -Fpvc6-stlport/libboost_regex_vc6-stlport_msd/libboost_regex_vc6-stlport_msd.pch -Fo./vc6-stlport/libboost_regex_vc6-stlport_msd/ -Fdvc6-stlport/libboost_regex_vc6-stlport_msd.pdb ../src/w32_regex_traits.cpp

vc6-stlport/libboost_regex_vc6-stlport_msd/wide_posix_api.obj: ../src/wide_posix_api.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MTd /W3 /Gm /GX /Zi /Od /I$(STLPORT_PATH)\stlport /I..\..\..\ /DWIN32 /D_MT /D_DEBUG /D_MBCS /D_LIB /YX /FD /GZ  /c $(CXXFLAGS) -Fpvc6-stlport/libboost_regex_vc6-stlport_msd/libboost_regex_vc6-stlport_msd.pch -Fo./vc6-stlport/libboost_regex_vc6-stlport_msd/ -Fdvc6-stlport/libboost_regex_vc6-stlport_msd.pdb ../src/wide_posix_api.cpp

vc6-stlport/libboost_regex_vc6-stlport_msd/winstances.obj: ../src/winstances.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MTd /W3 /Gm /GX /Zi /Od /I$(STLPORT_PATH)\stlport /I..\..\..\ /DWIN32 /D_MT /D_DEBUG /D_MBCS /D_LIB /YX /FD /GZ  /c $(CXXFLAGS) -Fpvc6-stlport/libboost_regex_vc6-stlport_msd/libboost_regex_vc6-stlport_msd.pch -Fo./vc6-stlport/libboost_regex_vc6-stlport_msd/ -Fdvc6-stlport/libboost_regex_vc6-stlport_msd.pdb ../src/winstances.cpp

libboost_regex_vc6-stlport_msd_dir :
	@if not exist "vc6-stlport\libboost_regex_vc6-stlport_msd\$(NULL)" mkdir vc6-stlport\libboost_regex_vc6-stlport_msd

libboost_regex_vc6-stlport_msd_clean :
	del vc6-stlport\libboost_regex_vc6-stlport_msd\*.obj
	del vc6-stlport\libboost_regex_vc6-stlport_msd\*.idb
	del vc6-stlport\libboost_regex_vc6-stlport_msd\*.exp
	del vc6-stlport\libboost_regex_vc6-stlport_msd\*.pch

./vc6-stlport/libboost_regex_vc6-stlport_msd.lib : vc6-stlport/libboost_regex_vc6-stlport_msd/c_regex_traits.obj vc6-stlport/libboost_regex_vc6-stlport_msd/c_regex_traits_common.obj vc6-stlport/libboost_regex_vc6-stlport_msd/cpp_regex_traits.obj vc6-stlport/libboost_regex_vc6-stlport_msd/cregex.obj vc6-stlport/libboost_regex_vc6-stlport_msd/fileiter.obj vc6-stlport/libboost_regex_vc6-stlport_msd/instances.obj vc6-stlport/libboost_regex_vc6-stlport_msd/posix_api.obj vc6-stlport/libboost_regex_vc6-stlport_msd/regex.obj vc6-stlport/libboost_regex_vc6-stlport_msd/regex_debug.obj vc6-stlport/libboost_regex_vc6-stlport_msd/regex_synch.obj vc6-stlport/libboost_regex_vc6-stlport_msd/w32_regex_traits.obj vc6-stlport/libboost_regex_vc6-stlport_msd/wide_posix_api.obj vc6-stlport/libboost_regex_vc6-stlport_msd/winstances.obj
	link -lib /nologo /out:vc6-stlport/libboost_regex_vc6-stlport_msd.lib $(XSFLAGS)  vc6-stlport/libboost_regex_vc6-stlport_msd/c_regex_traits.obj vc6-stlport/libboost_regex_vc6-stlport_msd/c_regex_traits_common.obj vc6-stlport/libboost_regex_vc6-stlport_msd/cpp_regex_traits.obj vc6-stlport/libboost_regex_vc6-stlport_msd/cregex.obj vc6-stlport/libboost_regex_vc6-stlport_msd/fileiter.obj vc6-stlport/libboost_regex_vc6-stlport_msd/instances.obj vc6-stlport/libboost_regex_vc6-stlport_msd/posix_api.obj vc6-stlport/libboost_regex_vc6-stlport_msd/regex.obj vc6-stlport/libboost_regex_vc6-stlport_msd/regex_debug.obj vc6-stlport/libboost_regex_vc6-stlport_msd/regex_synch.obj vc6-stlport/libboost_regex_vc6-stlport_msd/w32_regex_traits.obj vc6-stlport/libboost_regex_vc6-stlport_msd/wide_posix_api.obj vc6-stlport/libboost_regex_vc6-stlport_msd/winstances.obj

########################################################
#
# section for boost_regex_vc6-stlport_mdd.lib
#
########################################################
vc6-stlport/boost_regex_vc6-stlport_mdd/c_regex_traits.obj: ../src/c_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I$(STLPORT_PATH)\stlport /I../../../ /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /YX /FD /GZ  /c $(CXXFLAGS) -Fpvc6-stlport/boost_regex_vc6-stlport_mdd/boost_regex_vc6-stlport_mdd.pch -Fo./vc6-stlport/boost_regex_vc6-stlport_mdd/ -Fdvc6-stlport/boost_regex_vc6-stlport_mdd.pdb ../src/c_regex_traits.cpp

vc6-stlport/boost_regex_vc6-stlport_mdd/c_regex_traits_common.obj: ../src/c_regex_traits_common.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I$(STLPORT_PATH)\stlport /I../../../ /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /YX /FD /GZ  /c $(CXXFLAGS) -Fpvc6-stlport/boost_regex_vc6-stlport_mdd/boost_regex_vc6-stlport_mdd.pch -Fo./vc6-stlport/boost_regex_vc6-stlport_mdd/ -Fdvc6-stlport/boost_regex_vc6-stlport_mdd.pdb ../src/c_regex_traits_common.cpp

vc6-stlport/boost_regex_vc6-stlport_mdd/cpp_regex_traits.obj: ../src/cpp_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I$(STLPORT_PATH)\stlport /I../../../ /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /YX /FD /GZ  /c $(CXXFLAGS) -Fpvc6-stlport/boost_regex_vc6-stlport_mdd/boost_regex_vc6-stlport_mdd.pch -Fo./vc6-stlport/boost_regex_vc6-stlport_mdd/ -Fdvc6-stlport/boost_regex_vc6-stlport_mdd.pdb ../src/cpp_regex_traits.cpp

vc6-stlport/boost_regex_vc6-stlport_mdd/cregex.obj: ../src/cregex.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I$(STLPORT_PATH)\stlport /I../../../ /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /YX /FD /GZ  /c $(CXXFLAGS) -Fpvc6-stlport/boost_regex_vc6-stlport_mdd/boost_regex_vc6-stlport_mdd.pch -Fo./vc6-stlport/boost_regex_vc6-stlport_mdd/ -Fdvc6-stlport/boost_regex_vc6-stlport_mdd.pdb ../src/cregex.cpp

vc6-stlport/boost_regex_vc6-stlport_mdd/fileiter.obj: ../src/fileiter.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I$(STLPORT_PATH)\stlport /I../../../ /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /YX /FD /GZ  /c $(CXXFLAGS) -Fpvc6-stlport/boost_regex_vc6-stlport_mdd/boost_regex_vc6-stlport_mdd.pch -Fo./vc6-stlport/boost_regex_vc6-stlport_mdd/ -Fdvc6-stlport/boost_regex_vc6-stlport_mdd.pdb ../src/fileiter.cpp

vc6-stlport/boost_regex_vc6-stlport_mdd/instances.obj: ../src/instances.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I$(STLPORT_PATH)\stlport /I../../../ /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /YX /FD /GZ  /c $(CXXFLAGS) -Fpvc6-stlport/boost_regex_vc6-stlport_mdd/boost_regex_vc6-stlport_mdd.pch -Fo./vc6-stlport/boost_regex_vc6-stlport_mdd/ -Fdvc6-stlport/boost_regex_vc6-stlport_mdd.pdb ../src/instances.cpp

vc6-stlport/boost_regex_vc6-stlport_mdd/posix_api.obj: ../src/posix_api.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I$(STLPORT_PATH)\stlport /I../../../ /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /YX /FD /GZ  /c $(CXXFLAGS) -Fpvc6-stlport/boost_regex_vc6-stlport_mdd/boost_regex_vc6-stlport_mdd.pch -Fo./vc6-stlport/boost_regex_vc6-stlport_mdd/ -Fdvc6-stlport/boost_regex_vc6-stlport_mdd.pdb ../src/posix_api.cpp

vc6-stlport/boost_regex_vc6-stlport_mdd/regex.obj: ../src/regex.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I$(STLPORT_PATH)\stlport /I../../../ /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /YX /FD /GZ  /c $(CXXFLAGS) -Fpvc6-stlport/boost_regex_vc6-stlport_mdd/boost_regex_vc6-stlport_mdd.pch -Fo./vc6-stlport/boost_regex_vc6-stlport_mdd/ -Fdvc6-stlport/boost_regex_vc6-stlport_mdd.pdb ../src/regex.cpp

vc6-stlport/boost_regex_vc6-stlport_mdd/regex_debug.obj: ../src/regex_debug.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I$(STLPORT_PATH)\stlport /I../../../ /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /YX /FD /GZ  /c $(CXXFLAGS) -Fpvc6-stlport/boost_regex_vc6-stlport_mdd/boost_regex_vc6-stlport_mdd.pch -Fo./vc6-stlport/boost_regex_vc6-stlport_mdd/ -Fdvc6-stlport/boost_regex_vc6-stlport_mdd.pdb ../src/regex_debug.cpp

vc6-stlport/boost_regex_vc6-stlport_mdd/regex_synch.obj: ../src/regex_synch.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I$(STLPORT_PATH)\stlport /I../../../ /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /YX /FD /GZ  /c $(CXXFLAGS) -Fpvc6-stlport/boost_regex_vc6-stlport_mdd/boost_regex_vc6-stlport_mdd.pch -Fo./vc6-stlport/boost_regex_vc6-stlport_mdd/ -Fdvc6-stlport/boost_regex_vc6-stlport_mdd.pdb ../src/regex_synch.cpp

vc6-stlport/boost_regex_vc6-stlport_mdd/w32_regex_traits.obj: ../src/w32_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I$(STLPORT_PATH)\stlport /I../../../ /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /YX /FD /GZ  /c $(CXXFLAGS) -Fpvc6-stlport/boost_regex_vc6-stlport_mdd/boost_regex_vc6-stlport_mdd.pch -Fo./vc6-stlport/boost_regex_vc6-stlport_mdd/ -Fdvc6-stlport/boost_regex_vc6-stlport_mdd.pdb ../src/w32_regex_traits.cpp

vc6-stlport/boost_regex_vc6-stlport_mdd/wide_posix_api.obj: ../src/wide_posix_api.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I$(STLPORT_PATH)\stlport /I../../../ /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /YX /FD /GZ  /c $(CXXFLAGS) -Fpvc6-stlport/boost_regex_vc6-stlport_mdd/boost_regex_vc6-stlport_mdd.pch -Fo./vc6-stlport/boost_regex_vc6-stlport_mdd/ -Fdvc6-stlport/boost_regex_vc6-stlport_mdd.pdb ../src/wide_posix_api.cpp

vc6-stlport/boost_regex_vc6-stlport_mdd/winstances.obj: ../src/winstances.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I$(STLPORT_PATH)\stlport /I../../../ /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /YX /FD /GZ  /c $(CXXFLAGS) -Fpvc6-stlport/boost_regex_vc6-stlport_mdd/boost_regex_vc6-stlport_mdd.pch -Fo./vc6-stlport/boost_regex_vc6-stlport_mdd/ -Fdvc6-stlport/boost_regex_vc6-stlport_mdd.pdb ../src/winstances.cpp

boost_regex_vc6-stlport_mdd_dir :
	@if not exist "vc6-stlport\boost_regex_vc6-stlport_mdd\$(NULL)" mkdir vc6-stlport\boost_regex_vc6-stlport_mdd

boost_regex_vc6-stlport_mdd_clean :
	del vc6-stlport\boost_regex_vc6-stlport_mdd\*.obj
	del vc6-stlport\boost_regex_vc6-stlport_mdd\*.idb
	del vc6-stlport\boost_regex_vc6-stlport_mdd\*.exp
	del vc6-stlport\boost_regex_vc6-stlport_mdd\*.pch

./vc6-stlport/boost_regex_vc6-stlport_mdd.lib : vc6-stlport/boost_regex_vc6-stlport_mdd/c_regex_traits.obj vc6-stlport/boost_regex_vc6-stlport_mdd/c_regex_traits_common.obj vc6-stlport/boost_regex_vc6-stlport_mdd/cpp_regex_traits.obj vc6-stlport/boost_regex_vc6-stlport_mdd/cregex.obj vc6-stlport/boost_regex_vc6-stlport_mdd/fileiter.obj vc6-stlport/boost_regex_vc6-stlport_mdd/instances.obj vc6-stlport/boost_regex_vc6-stlport_mdd/posix_api.obj vc6-stlport/boost_regex_vc6-stlport_mdd/regex.obj vc6-stlport/boost_regex_vc6-stlport_mdd/regex_debug.obj vc6-stlport/boost_regex_vc6-stlport_mdd/regex_synch.obj vc6-stlport/boost_regex_vc6-stlport_mdd/w32_regex_traits.obj vc6-stlport/boost_regex_vc6-stlport_mdd/wide_posix_api.obj vc6-stlport/boost_regex_vc6-stlport_mdd/winstances.obj
	link kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:yes /pdb:"vc6-stlport/boost_regex_vc6-stlport_mdd.pdb" /debug /machine:I386 /out:"vc6-stlport/boost_regex_vc6-stlport_mdd.dll" /implib:"vc6-stlport/boost_regex_vc6-stlport_mdd.lib" /LIBPATH:$(STLPORT_PATH)\lib $(XLFLAGS)  vc6-stlport/boost_regex_vc6-stlport_mdd/c_regex_traits.obj vc6-stlport/boost_regex_vc6-stlport_mdd/c_regex_traits_common.obj vc6-stlport/boost_regex_vc6-stlport_mdd/cpp_regex_traits.obj vc6-stlport/boost_regex_vc6-stlport_mdd/cregex.obj vc6-stlport/boost_regex_vc6-stlport_mdd/fileiter.obj vc6-stlport/boost_regex_vc6-stlport_mdd/instances.obj vc6-stlport/boost_regex_vc6-stlport_mdd/posix_api.obj vc6-stlport/boost_regex_vc6-stlport_mdd/regex.obj vc6-stlport/boost_regex_vc6-stlport_mdd/regex_debug.obj vc6-stlport/boost_regex_vc6-stlport_mdd/regex_synch.obj vc6-stlport/boost_regex_vc6-stlport_mdd/w32_regex_traits.obj vc6-stlport/boost_regex_vc6-stlport_mdd/wide_posix_api.obj vc6-stlport/boost_regex_vc6-stlport_mdd/winstances.obj

########################################################
#
# section for boost_regex_vc6-stlport_md.lib
#
########################################################
vc6-stlport/boost_regex_vc6-stlport_md/c_regex_traits.obj: ../src/c_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /I$(STLPORT_PATH)\stlport /Gy /I../../../ /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /YX /FD /c $(CXXFLAGS) -Fpvc6-stlport/boost_regex_vc6-stlport_md/boost_regex_vc6-stlport_md.pch -Fo./vc6-stlport/boost_regex_vc6-stlport_md/ -Fdvc6-stlport/boost_regex_vc6-stlport_md.pdb ../src/c_regex_traits.cpp

vc6-stlport/boost_regex_vc6-stlport_md/c_regex_traits_common.obj: ../src/c_regex_traits_common.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /I$(STLPORT_PATH)\stlport /Gy /I../../../ /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /YX /FD /c $(CXXFLAGS) -Fpvc6-stlport/boost_regex_vc6-stlport_md/boost_regex_vc6-stlport_md.pch -Fo./vc6-stlport/boost_regex_vc6-stlport_md/ -Fdvc6-stlport/boost_regex_vc6-stlport_md.pdb ../src/c_regex_traits_common.cpp

vc6-stlport/boost_regex_vc6-stlport_md/cpp_regex_traits.obj: ../src/cpp_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /I$(STLPORT_PATH)\stlport /Gy /I../../../ /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /YX /FD /c $(CXXFLAGS) -Fpvc6-stlport/boost_regex_vc6-stlport_md/boost_regex_vc6-stlport_md.pch -Fo./vc6-stlport/boost_regex_vc6-stlport_md/ -Fdvc6-stlport/boost_regex_vc6-stlport_md.pdb ../src/cpp_regex_traits.cpp

vc6-stlport/boost_regex_vc6-stlport_md/cregex.obj: ../src/cregex.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /I$(STLPORT_PATH)\stlport /Gy /I../../../ /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /YX /FD /c $(CXXFLAGS) -Fpvc6-stlport/boost_regex_vc6-stlport_md/boost_regex_vc6-stlport_md.pch -Fo./vc6-stlport/boost_regex_vc6-stlport_md/ -Fdvc6-stlport/boost_regex_vc6-stlport_md.pdb ../src/cregex.cpp

vc6-stlport/boost_regex_vc6-stlport_md/fileiter.obj: ../src/fileiter.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /I$(STLPORT_PATH)\stlport /Gy /I../../../ /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /YX /FD /c $(CXXFLAGS) -Fpvc6-stlport/boost_regex_vc6-stlport_md/boost_regex_vc6-stlport_md.pch -Fo./vc6-stlport/boost_regex_vc6-stlport_md/ -Fdvc6-stlport/boost_regex_vc6-stlport_md.pdb ../src/fileiter.cpp

vc6-stlport/boost_regex_vc6-stlport_md/instances.obj: ../src/instances.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /I$(STLPORT_PATH)\stlport /Gy /I../../../ /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /YX /FD /c $(CXXFLAGS) -Fpvc6-stlport/boost_regex_vc6-stlport_md/boost_regex_vc6-stlport_md.pch -Fo./vc6-stlport/boost_regex_vc6-stlport_md/ -Fdvc6-stlport/boost_regex_vc6-stlport_md.pdb ../src/instances.cpp

vc6-stlport/boost_regex_vc6-stlport_md/posix_api.obj: ../src/posix_api.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /I$(STLPORT_PATH)\stlport /Gy /I../../../ /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /YX /FD /c $(CXXFLAGS) -Fpvc6-stlport/boost_regex_vc6-stlport_md/boost_regex_vc6-stlport_md.pch -Fo./vc6-stlport/boost_regex_vc6-stlport_md/ -Fdvc6-stlport/boost_regex_vc6-stlport_md.pdb ../src/posix_api.cpp

vc6-stlport/boost_regex_vc6-stlport_md/regex.obj: ../src/regex.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /I$(STLPORT_PATH)\stlport /Gy /I../../../ /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /YX /FD /c $(CXXFLAGS) -Fpvc6-stlport/boost_regex_vc6-stlport_md/boost_regex_vc6-stlport_md.pch -Fo./vc6-stlport/boost_regex_vc6-stlport_md/ -Fdvc6-stlport/boost_regex_vc6-stlport_md.pdb ../src/regex.cpp

vc6-stlport/boost_regex_vc6-stlport_md/regex_debug.obj: ../src/regex_debug.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /I$(STLPORT_PATH)\stlport /Gy /I../../../ /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /YX /FD /c $(CXXFLAGS) -Fpvc6-stlport/boost_regex_vc6-stlport_md/boost_regex_vc6-stlport_md.pch -Fo./vc6-stlport/boost_regex_vc6-stlport_md/ -Fdvc6-stlport/boost_regex_vc6-stlport_md.pdb ../src/regex_debug.cpp

vc6-stlport/boost_regex_vc6-stlport_md/regex_synch.obj: ../src/regex_synch.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /I$(STLPORT_PATH)\stlport /Gy /I../../../ /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /YX /FD /c $(CXXFLAGS) -Fpvc6-stlport/boost_regex_vc6-stlport_md/boost_regex_vc6-stlport_md.pch -Fo./vc6-stlport/boost_regex_vc6-stlport_md/ -Fdvc6-stlport/boost_regex_vc6-stlport_md.pdb ../src/regex_synch.cpp

vc6-stlport/boost_regex_vc6-stlport_md/w32_regex_traits.obj: ../src/w32_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /I$(STLPORT_PATH)\stlport /Gy /I../../../ /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /YX /FD /c $(CXXFLAGS) -Fpvc6-stlport/boost_regex_vc6-stlport_md/boost_regex_vc6-stlport_md.pch -Fo./vc6-stlport/boost_regex_vc6-stlport_md/ -Fdvc6-stlport/boost_regex_vc6-stlport_md.pdb ../src/w32_regex_traits.cpp

vc6-stlport/boost_regex_vc6-stlport_md/wide_posix_api.obj: ../src/wide_posix_api.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /I$(STLPORT_PATH)\stlport /Gy /I../../../ /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /YX /FD /c $(CXXFLAGS) -Fpvc6-stlport/boost_regex_vc6-stlport_md/boost_regex_vc6-stlport_md.pch -Fo./vc6-stlport/boost_regex_vc6-stlport_md/ -Fdvc6-stlport/boost_regex_vc6-stlport_md.pdb ../src/wide_posix_api.cpp

vc6-stlport/boost_regex_vc6-stlport_md/winstances.obj: ../src/winstances.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /I$(STLPORT_PATH)\stlport /Gy /I../../../ /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /YX /FD /c $(CXXFLAGS) -Fpvc6-stlport/boost_regex_vc6-stlport_md/boost_regex_vc6-stlport_md.pch -Fo./vc6-stlport/boost_regex_vc6-stlport_md/ -Fdvc6-stlport/boost_regex_vc6-stlport_md.pdb ../src/winstances.cpp

boost_regex_vc6-stlport_md_dir :
	@if not exist "vc6-stlport\boost_regex_vc6-stlport_md\$(NULL)" mkdir vc6-stlport\boost_regex_vc6-stlport_md

boost_regex_vc6-stlport_md_clean :
	del vc6-stlport\boost_regex_vc6-stlport_md\*.obj
	del vc6-stlport\boost_regex_vc6-stlport_md\*.idb
	del vc6-stlport\boost_regex_vc6-stlport_md\*.exp
	del vc6-stlport\boost_regex_vc6-stlport_md\*.pch

./vc6-stlport/boost_regex_vc6-stlport_md.lib : vc6-stlport/boost_regex_vc6-stlport_md/c_regex_traits.obj vc6-stlport/boost_regex_vc6-stlport_md/c_regex_traits_common.obj vc6-stlport/boost_regex_vc6-stlport_md/cpp_regex_traits.obj vc6-stlport/boost_regex_vc6-stlport_md/cregex.obj vc6-stlport/boost_regex_vc6-stlport_md/fileiter.obj vc6-stlport/boost_regex_vc6-stlport_md/instances.obj vc6-stlport/boost_regex_vc6-stlport_md/posix_api.obj vc6-stlport/boost_regex_vc6-stlport_md/regex.obj vc6-stlport/boost_regex_vc6-stlport_md/regex_debug.obj vc6-stlport/boost_regex_vc6-stlport_md/regex_synch.obj vc6-stlport/boost_regex_vc6-stlport_md/w32_regex_traits.obj vc6-stlport/boost_regex_vc6-stlport_md/wide_posix_api.obj vc6-stlport/boost_regex_vc6-stlport_md/winstances.obj
	link kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:yes /pdb:"vc6-stlport/boost_regex_vc6-stlport_md.pdb" /debug /machine:I386 /out:"vc6-stlport/boost_regex_vc6-stlport_md.dll" /implib:"vc6-stlport/boost_regex_vc6-stlport_md.lib" /LIBPATH:$(STLPORT_PATH)\lib $(XLFLAGS)  vc6-stlport/boost_regex_vc6-stlport_md/c_regex_traits.obj vc6-stlport/boost_regex_vc6-stlport_md/c_regex_traits_common.obj vc6-stlport/boost_regex_vc6-stlport_md/cpp_regex_traits.obj vc6-stlport/boost_regex_vc6-stlport_md/cregex.obj vc6-stlport/boost_regex_vc6-stlport_md/fileiter.obj vc6-stlport/boost_regex_vc6-stlport_md/instances.obj vc6-stlport/boost_regex_vc6-stlport_md/posix_api.obj vc6-stlport/boost_regex_vc6-stlport_md/regex.obj vc6-stlport/boost_regex_vc6-stlport_md/regex_debug.obj vc6-stlport/boost_regex_vc6-stlport_md/regex_synch.obj vc6-stlport/boost_regex_vc6-stlport_md/w32_regex_traits.obj vc6-stlport/boost_regex_vc6-stlport_md/wide_posix_api.obj vc6-stlport/boost_regex_vc6-stlport_md/winstances.obj

########################################################
#
# section for libboost_regex_vc6-stlport_md.lib
#
########################################################
vc6-stlport/libboost_regex_vc6-stlport_md/c_regex_traits.obj: ../src/c_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /Gy /I$(STLPORT_PATH)\stlport /I../../../ /DBOOST_REGEX_STATIC_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /YX /FD /c $(CXXFLAGS) -Fpvc6-stlport/libboost_regex_vc6-stlport_md/libboost_regex_vc6-stlport_md.pch -Fo./vc6-stlport/libboost_regex_vc6-stlport_md/ -Fdvc6-stlport/libboost_regex_vc6-stlport_md.pdb ../src/c_regex_traits.cpp

vc6-stlport/libboost_regex_vc6-stlport_md/c_regex_traits_common.obj: ../src/c_regex_traits_common.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /Gy /I$(STLPORT_PATH)\stlport /I../../../ /DBOOST_REGEX_STATIC_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /YX /FD /c $(CXXFLAGS) -Fpvc6-stlport/libboost_regex_vc6-stlport_md/libboost_regex_vc6-stlport_md.pch -Fo./vc6-stlport/libboost_regex_vc6-stlport_md/ -Fdvc6-stlport/libboost_regex_vc6-stlport_md.pdb ../src/c_regex_traits_common.cpp

vc6-stlport/libboost_regex_vc6-stlport_md/cpp_regex_traits.obj: ../src/cpp_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /Gy /I$(STLPORT_PATH)\stlport /I../../../ /DBOOST_REGEX_STATIC_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /YX /FD /c $(CXXFLAGS) -Fpvc6-stlport/libboost_regex_vc6-stlport_md/libboost_regex_vc6-stlport_md.pch -Fo./vc6-stlport/libboost_regex_vc6-stlport_md/ -Fdvc6-stlport/libboost_regex_vc6-stlport_md.pdb ../src/cpp_regex_traits.cpp

vc6-stlport/libboost_regex_vc6-stlport_md/cregex.obj: ../src/cregex.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /Gy /I$(STLPORT_PATH)\stlport /I../../../ /DBOOST_REGEX_STATIC_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /YX /FD /c $(CXXFLAGS) -Fpvc6-stlport/libboost_regex_vc6-stlport_md/libboost_regex_vc6-stlport_md.pch -Fo./vc6-stlport/libboost_regex_vc6-stlport_md/ -Fdvc6-stlport/libboost_regex_vc6-stlport_md.pdb ../src/cregex.cpp

vc6-stlport/libboost_regex_vc6-stlport_md/fileiter.obj: ../src/fileiter.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /Gy /I$(STLPORT_PATH)\stlport /I../../../ /DBOOST_REGEX_STATIC_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /YX /FD /c $(CXXFLAGS) -Fpvc6-stlport/libboost_regex_vc6-stlport_md/libboost_regex_vc6-stlport_md.pch -Fo./vc6-stlport/libboost_regex_vc6-stlport_md/ -Fdvc6-stlport/libboost_regex_vc6-stlport_md.pdb ../src/fileiter.cpp

vc6-stlport/libboost_regex_vc6-stlport_md/instances.obj: ../src/instances.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /Gy /I$(STLPORT_PATH)\stlport /I../../../ /DBOOST_REGEX_STATIC_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /YX /FD /c $(CXXFLAGS) -Fpvc6-stlport/libboost_regex_vc6-stlport_md/libboost_regex_vc6-stlport_md.pch -Fo./vc6-stlport/libboost_regex_vc6-stlport_md/ -Fdvc6-stlport/libboost_regex_vc6-stlport_md.pdb ../src/instances.cpp

vc6-stlport/libboost_regex_vc6-stlport_md/posix_api.obj: ../src/posix_api.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /Gy /I$(STLPORT_PATH)\stlport /I../../../ /DBOOST_REGEX_STATIC_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /YX /FD /c $(CXXFLAGS) -Fpvc6-stlport/libboost_regex_vc6-stlport_md/libboost_regex_vc6-stlport_md.pch -Fo./vc6-stlport/libboost_regex_vc6-stlport_md/ -Fdvc6-stlport/libboost_regex_vc6-stlport_md.pdb ../src/posix_api.cpp

vc6-stlport/libboost_regex_vc6-stlport_md/regex.obj: ../src/regex.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /Gy /I$(STLPORT_PATH)\stlport /I../../../ /DBOOST_REGEX_STATIC_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /YX /FD /c $(CXXFLAGS) -Fpvc6-stlport/libboost_regex_vc6-stlport_md/libboost_regex_vc6-stlport_md.pch -Fo./vc6-stlport/libboost_regex_vc6-stlport_md/ -Fdvc6-stlport/libboost_regex_vc6-stlport_md.pdb ../src/regex.cpp

vc6-stlport/libboost_regex_vc6-stlport_md/regex_debug.obj: ../src/regex_debug.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /Gy /I$(STLPORT_PATH)\stlport /I../../../ /DBOOST_REGEX_STATIC_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /YX /FD /c $(CXXFLAGS) -Fpvc6-stlport/libboost_regex_vc6-stlport_md/libboost_regex_vc6-stlport_md.pch -Fo./vc6-stlport/libboost_regex_vc6-stlport_md/ -Fdvc6-stlport/libboost_regex_vc6-stlport_md.pdb ../src/regex_debug.cpp

vc6-stlport/libboost_regex_vc6-stlport_md/regex_synch.obj: ../src/regex_synch.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /Gy /I$(STLPORT_PATH)\stlport /I../../../ /DBOOST_REGEX_STATIC_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /YX /FD /c $(CXXFLAGS) -Fpvc6-stlport/libboost_regex_vc6-stlport_md/libboost_regex_vc6-stlport_md.pch -Fo./vc6-stlport/libboost_regex_vc6-stlport_md/ -Fdvc6-stlport/libboost_regex_vc6-stlport_md.pdb ../src/regex_synch.cpp

vc6-stlport/libboost_regex_vc6-stlport_md/w32_regex_traits.obj: ../src/w32_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /Gy /I$(STLPORT_PATH)\stlport /I../../../ /DBOOST_REGEX_STATIC_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /YX /FD /c $(CXXFLAGS) -Fpvc6-stlport/libboost_regex_vc6-stlport_md/libboost_regex_vc6-stlport_md.pch -Fo./vc6-stlport/libboost_regex_vc6-stlport_md/ -Fdvc6-stlport/libboost_regex_vc6-stlport_md.pdb ../src/w32_regex_traits.cpp

vc6-stlport/libboost_regex_vc6-stlport_md/wide_posix_api.obj: ../src/wide_posix_api.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /Gy /I$(STLPORT_PATH)\stlport /I../../../ /DBOOST_REGEX_STATIC_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /YX /FD /c $(CXXFLAGS) -Fpvc6-stlport/libboost_regex_vc6-stlport_md/libboost_regex_vc6-stlport_md.pch -Fo./vc6-stlport/libboost_regex_vc6-stlport_md/ -Fdvc6-stlport/libboost_regex_vc6-stlport_md.pdb ../src/wide_posix_api.cpp

vc6-stlport/libboost_regex_vc6-stlport_md/winstances.obj: ../src/winstances.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /Gy /I$(STLPORT_PATH)\stlport /I../../../ /DBOOST_REGEX_STATIC_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /YX /FD /c $(CXXFLAGS) -Fpvc6-stlport/libboost_regex_vc6-stlport_md/libboost_regex_vc6-stlport_md.pch -Fo./vc6-stlport/libboost_regex_vc6-stlport_md/ -Fdvc6-stlport/libboost_regex_vc6-stlport_md.pdb ../src/winstances.cpp

libboost_regex_vc6-stlport_md_dir :
	@if not exist "vc6-stlport\libboost_regex_vc6-stlport_md\$(NULL)" mkdir vc6-stlport\libboost_regex_vc6-stlport_md

libboost_regex_vc6-stlport_md_clean :
	del vc6-stlport\libboost_regex_vc6-stlport_md\*.obj
	del vc6-stlport\libboost_regex_vc6-stlport_md\*.idb
	del vc6-stlport\libboost_regex_vc6-stlport_md\*.exp
	del vc6-stlport\libboost_regex_vc6-stlport_md\*.pch

./vc6-stlport/libboost_regex_vc6-stlport_md.lib : vc6-stlport/libboost_regex_vc6-stlport_md/c_regex_traits.obj vc6-stlport/libboost_regex_vc6-stlport_md/c_regex_traits_common.obj vc6-stlport/libboost_regex_vc6-stlport_md/cpp_regex_traits.obj vc6-stlport/libboost_regex_vc6-stlport_md/cregex.obj vc6-stlport/libboost_regex_vc6-stlport_md/fileiter.obj vc6-stlport/libboost_regex_vc6-stlport_md/instances.obj vc6-stlport/libboost_regex_vc6-stlport_md/posix_api.obj vc6-stlport/libboost_regex_vc6-stlport_md/regex.obj vc6-stlport/libboost_regex_vc6-stlport_md/regex_debug.obj vc6-stlport/libboost_regex_vc6-stlport_md/regex_synch.obj vc6-stlport/libboost_regex_vc6-stlport_md/w32_regex_traits.obj vc6-stlport/libboost_regex_vc6-stlport_md/wide_posix_api.obj vc6-stlport/libboost_regex_vc6-stlport_md/winstances.obj
	link -lib /nologo /out:vc6-stlport/libboost_regex_vc6-stlport_md.lib $(XSFLAGS)  vc6-stlport/libboost_regex_vc6-stlport_md/c_regex_traits.obj vc6-stlport/libboost_regex_vc6-stlport_md/c_regex_traits_common.obj vc6-stlport/libboost_regex_vc6-stlport_md/cpp_regex_traits.obj vc6-stlport/libboost_regex_vc6-stlport_md/cregex.obj vc6-stlport/libboost_regex_vc6-stlport_md/fileiter.obj vc6-stlport/libboost_regex_vc6-stlport_md/instances.obj vc6-stlport/libboost_regex_vc6-stlport_md/posix_api.obj vc6-stlport/libboost_regex_vc6-stlport_md/regex.obj vc6-stlport/libboost_regex_vc6-stlport_md/regex_debug.obj vc6-stlport/libboost_regex_vc6-stlport_md/regex_synch.obj vc6-stlport/libboost_regex_vc6-stlport_md/w32_regex_traits.obj vc6-stlport/libboost_regex_vc6-stlport_md/wide_posix_api.obj vc6-stlport/libboost_regex_vc6-stlport_md/winstances.obj

########################################################
#
# section for libboost_regex_vc6-stlport_mdd.lib
#
########################################################
vc6-stlport/libboost_regex_vc6-stlport_mdd/c_regex_traits.obj: ../src/c_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I$(STLPORT_PATH)\stlport /I../../../ /DBOOST_REGEX_STATIC_LINK /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /YX /FD /GZ  /c $(CXXFLAGS) -Fpvc6-stlport/libboost_regex_vc6-stlport_mdd/libboost_regex_vc6-stlport_mdd.pch -Fo./vc6-stlport/libboost_regex_vc6-stlport_mdd/ -Fdvc6-stlport/libboost_regex_vc6-stlport_mdd.pdb ../src/c_regex_traits.cpp

vc6-stlport/libboost_regex_vc6-stlport_mdd/c_regex_traits_common.obj: ../src/c_regex_traits_common.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I$(STLPORT_PATH)\stlport /I../../../ /DBOOST_REGEX_STATIC_LINK /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /YX /FD /GZ  /c $(CXXFLAGS) -Fpvc6-stlport/libboost_regex_vc6-stlport_mdd/libboost_regex_vc6-stlport_mdd.pch -Fo./vc6-stlport/libboost_regex_vc6-stlport_mdd/ -Fdvc6-stlport/libboost_regex_vc6-stlport_mdd.pdb ../src/c_regex_traits_common.cpp

vc6-stlport/libboost_regex_vc6-stlport_mdd/cpp_regex_traits.obj: ../src/cpp_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I$(STLPORT_PATH)\stlport /I../../../ /DBOOST_REGEX_STATIC_LINK /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /YX /FD /GZ  /c $(CXXFLAGS) -Fpvc6-stlport/libboost_regex_vc6-stlport_mdd/libboost_regex_vc6-stlport_mdd.pch -Fo./vc6-stlport/libboost_regex_vc6-stlport_mdd/ -Fdvc6-stlport/libboost_regex_vc6-stlport_mdd.pdb ../src/cpp_regex_traits.cpp

vc6-stlport/libboost_regex_vc6-stlport_mdd/cregex.obj: ../src/cregex.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I$(STLPORT_PATH)\stlport /I../../../ /DBOOST_REGEX_STATIC_LINK /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /YX /FD /GZ  /c $(CXXFLAGS) -Fpvc6-stlport/libboost_regex_vc6-stlport_mdd/libboost_regex_vc6-stlport_mdd.pch -Fo./vc6-stlport/libboost_regex_vc6-stlport_mdd/ -Fdvc6-stlport/libboost_regex_vc6-stlport_mdd.pdb ../src/cregex.cpp

vc6-stlport/libboost_regex_vc6-stlport_mdd/fileiter.obj: ../src/fileiter.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I$(STLPORT_PATH)\stlport /I../../../ /DBOOST_REGEX_STATIC_LINK /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /YX /FD /GZ  /c $(CXXFLAGS) -Fpvc6-stlport/libboost_regex_vc6-stlport_mdd/libboost_regex_vc6-stlport_mdd.pch -Fo./vc6-stlport/libboost_regex_vc6-stlport_mdd/ -Fdvc6-stlport/libboost_regex_vc6-stlport_mdd.pdb ../src/fileiter.cpp

vc6-stlport/libboost_regex_vc6-stlport_mdd/instances.obj: ../src/instances.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I$(STLPORT_PATH)\stlport /I../../../ /DBOOST_REGEX_STATIC_LINK /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /YX /FD /GZ  /c $(CXXFLAGS) -Fpvc6-stlport/libboost_regex_vc6-stlport_mdd/libboost_regex_vc6-stlport_mdd.pch -Fo./vc6-stlport/libboost_regex_vc6-stlport_mdd/ -Fdvc6-stlport/libboost_regex_vc6-stlport_mdd.pdb ../src/instances.cpp

vc6-stlport/libboost_regex_vc6-stlport_mdd/posix_api.obj: ../src/posix_api.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I$(STLPORT_PATH)\stlport /I../../../ /DBOOST_REGEX_STATIC_LINK /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /YX /FD /GZ  /c $(CXXFLAGS) -Fpvc6-stlport/libboost_regex_vc6-stlport_mdd/libboost_regex_vc6-stlport_mdd.pch -Fo./vc6-stlport/libboost_regex_vc6-stlport_mdd/ -Fdvc6-stlport/libboost_regex_vc6-stlport_mdd.pdb ../src/posix_api.cpp

vc6-stlport/libboost_regex_vc6-stlport_mdd/regex.obj: ../src/regex.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I$(STLPORT_PATH)\stlport /I../../../ /DBOOST_REGEX_STATIC_LINK /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /YX /FD /GZ  /c $(CXXFLAGS) -Fpvc6-stlport/libboost_regex_vc6-stlport_mdd/libboost_regex_vc6-stlport_mdd.pch -Fo./vc6-stlport/libboost_regex_vc6-stlport_mdd/ -Fdvc6-stlport/libboost_regex_vc6-stlport_mdd.pdb ../src/regex.cpp

vc6-stlport/libboost_regex_vc6-stlport_mdd/regex_debug.obj: ../src/regex_debug.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I$(STLPORT_PATH)\stlport /I../../../ /DBOOST_REGEX_STATIC_LINK /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /YX /FD /GZ  /c $(CXXFLAGS) -Fpvc6-stlport/libboost_regex_vc6-stlport_mdd/libboost_regex_vc6-stlport_mdd.pch -Fo./vc6-stlport/libboost_regex_vc6-stlport_mdd/ -Fdvc6-stlport/libboost_regex_vc6-stlport_mdd.pdb ../src/regex_debug.cpp

vc6-stlport/libboost_regex_vc6-stlport_mdd/regex_synch.obj: ../src/regex_synch.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I$(STLPORT_PATH)\stlport /I../../../ /DBOOST_REGEX_STATIC_LINK /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /YX /FD /GZ  /c $(CXXFLAGS) -Fpvc6-stlport/libboost_regex_vc6-stlport_mdd/libboost_regex_vc6-stlport_mdd.pch -Fo./vc6-stlport/libboost_regex_vc6-stlport_mdd/ -Fdvc6-stlport/libboost_regex_vc6-stlport_mdd.pdb ../src/regex_synch.cpp

vc6-stlport/libboost_regex_vc6-stlport_mdd/w32_regex_traits.obj: ../src/w32_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I$(STLPORT_PATH)\stlport /I../../../ /DBOOST_REGEX_STATIC_LINK /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /YX /FD /GZ  /c $(CXXFLAGS) -Fpvc6-stlport/libboost_regex_vc6-stlport_mdd/libboost_regex_vc6-stlport_mdd.pch -Fo./vc6-stlport/libboost_regex_vc6-stlport_mdd/ -Fdvc6-stlport/libboost_regex_vc6-stlport_mdd.pdb ../src/w32_regex_traits.cpp

vc6-stlport/libboost_regex_vc6-stlport_mdd/wide_posix_api.obj: ../src/wide_posix_api.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I$(STLPORT_PATH)\stlport /I../../../ /DBOOST_REGEX_STATIC_LINK /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /YX /FD /GZ  /c $(CXXFLAGS) -Fpvc6-stlport/libboost_regex_vc6-stlport_mdd/libboost_regex_vc6-stlport_mdd.pch -Fo./vc6-stlport/libboost_regex_vc6-stlport_mdd/ -Fdvc6-stlport/libboost_regex_vc6-stlport_mdd.pdb ../src/wide_posix_api.cpp

vc6-stlport/libboost_regex_vc6-stlport_mdd/winstances.obj: ../src/winstances.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I$(STLPORT_PATH)\stlport /I../../../ /DBOOST_REGEX_STATIC_LINK /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /YX /FD /GZ  /c $(CXXFLAGS) -Fpvc6-stlport/libboost_regex_vc6-stlport_mdd/libboost_regex_vc6-stlport_mdd.pch -Fo./vc6-stlport/libboost_regex_vc6-stlport_mdd/ -Fdvc6-stlport/libboost_regex_vc6-stlport_mdd.pdb ../src/winstances.cpp

libboost_regex_vc6-stlport_mdd_dir :
	@if not exist "vc6-stlport\libboost_regex_vc6-stlport_mdd\$(NULL)" mkdir vc6-stlport\libboost_regex_vc6-stlport_mdd

libboost_regex_vc6-stlport_mdd_clean :
	del vc6-stlport\libboost_regex_vc6-stlport_mdd\*.obj
	del vc6-stlport\libboost_regex_vc6-stlport_mdd\*.idb
	del vc6-stlport\libboost_regex_vc6-stlport_mdd\*.exp
	del vc6-stlport\libboost_regex_vc6-stlport_mdd\*.pch

./vc6-stlport/libboost_regex_vc6-stlport_mdd.lib : vc6-stlport/libboost_regex_vc6-stlport_mdd/c_regex_traits.obj vc6-stlport/libboost_regex_vc6-stlport_mdd/c_regex_traits_common.obj vc6-stlport/libboost_regex_vc6-stlport_mdd/cpp_regex_traits.obj vc6-stlport/libboost_regex_vc6-stlport_mdd/cregex.obj vc6-stlport/libboost_regex_vc6-stlport_mdd/fileiter.obj vc6-stlport/libboost_regex_vc6-stlport_mdd/instances.obj vc6-stlport/libboost_regex_vc6-stlport_mdd/posix_api.obj vc6-stlport/libboost_regex_vc6-stlport_mdd/regex.obj vc6-stlport/libboost_regex_vc6-stlport_mdd/regex_debug.obj vc6-stlport/libboost_regex_vc6-stlport_mdd/regex_synch.obj vc6-stlport/libboost_regex_vc6-stlport_mdd/w32_regex_traits.obj vc6-stlport/libboost_regex_vc6-stlport_mdd/wide_posix_api.obj vc6-stlport/libboost_regex_vc6-stlport_mdd/winstances.obj
	link -lib /nologo /out:vc6-stlport/libboost_regex_vc6-stlport_mdd.lib $(XSFLAGS)  vc6-stlport/libboost_regex_vc6-stlport_mdd/c_regex_traits.obj vc6-stlport/libboost_regex_vc6-stlport_mdd/c_regex_traits_common.obj vc6-stlport/libboost_regex_vc6-stlport_mdd/cpp_regex_traits.obj vc6-stlport/libboost_regex_vc6-stlport_mdd/cregex.obj vc6-stlport/libboost_regex_vc6-stlport_mdd/fileiter.obj vc6-stlport/libboost_regex_vc6-stlport_mdd/instances.obj vc6-stlport/libboost_regex_vc6-stlport_mdd/posix_api.obj vc6-stlport/libboost_regex_vc6-stlport_mdd/regex.obj vc6-stlport/libboost_regex_vc6-stlport_mdd/regex_debug.obj vc6-stlport/libboost_regex_vc6-stlport_mdd/regex_synch.obj vc6-stlport/libboost_regex_vc6-stlport_mdd/w32_regex_traits.obj vc6-stlport/libboost_regex_vc6-stlport_mdd/wide_posix_api.obj vc6-stlport/libboost_regex_vc6-stlport_mdd/winstances.obj

########################################################
#
# section for boost_regex_vc6-stlport_mddd.lib
#
########################################################
vc6-stlport/boost_regex_vc6-stlport_mddd/c_regex_traits.obj: ../src/c_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I$(STLPORT_PATH)\stlport /I../../../ /D__STL_DEBUG /D_STLP_DEBUG /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /FD /GZ  /c $(CXXFLAGS) -Fpvc6-stlport/boost_regex_vc6-stlport_mddd/boost_regex_vc6-stlport_mddd.pch -Fo./vc6-stlport/boost_regex_vc6-stlport_mddd/ -Fdvc6-stlport/boost_regex_vc6-stlport_mddd.pdb ../src/c_regex_traits.cpp

vc6-stlport/boost_regex_vc6-stlport_mddd/c_regex_traits_common.obj: ../src/c_regex_traits_common.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I$(STLPORT_PATH)\stlport /I../../../ /D__STL_DEBUG /D_STLP_DEBUG /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /FD /GZ  /c $(CXXFLAGS) -Fpvc6-stlport/boost_regex_vc6-stlport_mddd/boost_regex_vc6-stlport_mddd.pch -Fo./vc6-stlport/boost_regex_vc6-stlport_mddd/ -Fdvc6-stlport/boost_regex_vc6-stlport_mddd.pdb ../src/c_regex_traits_common.cpp

vc6-stlport/boost_regex_vc6-stlport_mddd/cpp_regex_traits.obj: ../src/cpp_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I$(STLPORT_PATH)\stlport /I../../../ /D__STL_DEBUG /D_STLP_DEBUG /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /FD /GZ  /c $(CXXFLAGS) -Fpvc6-stlport/boost_regex_vc6-stlport_mddd/boost_regex_vc6-stlport_mddd.pch -Fo./vc6-stlport/boost_regex_vc6-stlport_mddd/ -Fdvc6-stlport/boost_regex_vc6-stlport_mddd.pdb ../src/cpp_regex_traits.cpp

vc6-stlport/boost_regex_vc6-stlport_mddd/cregex.obj: ../src/cregex.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I$(STLPORT_PATH)\stlport /I../../../ /D__STL_DEBUG /D_STLP_DEBUG /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /FD /GZ  /c $(CXXFLAGS) -Fpvc6-stlport/boost_regex_vc6-stlport_mddd/boost_regex_vc6-stlport_mddd.pch -Fo./vc6-stlport/boost_regex_vc6-stlport_mddd/ -Fdvc6-stlport/boost_regex_vc6-stlport_mddd.pdb ../src/cregex.cpp

vc6-stlport/boost_regex_vc6-stlport_mddd/fileiter.obj: ../src/fileiter.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I$(STLPORT_PATH)\stlport /I../../../ /D__STL_DEBUG /D_STLP_DEBUG /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /FD /GZ  /c $(CXXFLAGS) -Fpvc6-stlport/boost_regex_vc6-stlport_mddd/boost_regex_vc6-stlport_mddd.pch -Fo./vc6-stlport/boost_regex_vc6-stlport_mddd/ -Fdvc6-stlport/boost_regex_vc6-stlport_mddd.pdb ../src/fileiter.cpp

vc6-stlport/boost_regex_vc6-stlport_mddd/instances.obj: ../src/instances.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I$(STLPORT_PATH)\stlport /I../../../ /D__STL_DEBUG /D_STLP_DEBUG /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /FD /GZ  /c $(CXXFLAGS) -Fpvc6-stlport/boost_regex_vc6-stlport_mddd/boost_regex_vc6-stlport_mddd.pch -Fo./vc6-stlport/boost_regex_vc6-stlport_mddd/ -Fdvc6-stlport/boost_regex_vc6-stlport_mddd.pdb ../src/instances.cpp

vc6-stlport/boost_regex_vc6-stlport_mddd/posix_api.obj: ../src/posix_api.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I$(STLPORT_PATH)\stlport /I../../../ /D__STL_DEBUG /D_STLP_DEBUG /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /FD /GZ  /c $(CXXFLAGS) -Fpvc6-stlport/boost_regex_vc6-stlport_mddd/boost_regex_vc6-stlport_mddd.pch -Fo./vc6-stlport/boost_regex_vc6-stlport_mddd/ -Fdvc6-stlport/boost_regex_vc6-stlport_mddd.pdb ../src/posix_api.cpp

vc6-stlport/boost_regex_vc6-stlport_mddd/regex.obj: ../src/regex.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I$(STLPORT_PATH)\stlport /I../../../ /D__STL_DEBUG /D_STLP_DEBUG /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /FD /GZ  /c $(CXXFLAGS) -Fpvc6-stlport/boost_regex_vc6-stlport_mddd/boost_regex_vc6-stlport_mddd.pch -Fo./vc6-stlport/boost_regex_vc6-stlport_mddd/ -Fdvc6-stlport/boost_regex_vc6-stlport_mddd.pdb ../src/regex.cpp

vc6-stlport/boost_regex_vc6-stlport_mddd/regex_debug.obj: ../src/regex_debug.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I$(STLPORT_PATH)\stlport /I../../../ /D__STL_DEBUG /D_STLP_DEBUG /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /FD /GZ  /c $(CXXFLAGS) -Fpvc6-stlport/boost_regex_vc6-stlport_mddd/boost_regex_vc6-stlport_mddd.pch -Fo./vc6-stlport/boost_regex_vc6-stlport_mddd/ -Fdvc6-stlport/boost_regex_vc6-stlport_mddd.pdb ../src/regex_debug.cpp

vc6-stlport/boost_regex_vc6-stlport_mddd/regex_synch.obj: ../src/regex_synch.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I$(STLPORT_PATH)\stlport /I../../../ /D__STL_DEBUG /D_STLP_DEBUG /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /FD /GZ  /c $(CXXFLAGS) -Fpvc6-stlport/boost_regex_vc6-stlport_mddd/boost_regex_vc6-stlport_mddd.pch -Fo./vc6-stlport/boost_regex_vc6-stlport_mddd/ -Fdvc6-stlport/boost_regex_vc6-stlport_mddd.pdb ../src/regex_synch.cpp

vc6-stlport/boost_regex_vc6-stlport_mddd/w32_regex_traits.obj: ../src/w32_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I$(STLPORT_PATH)\stlport /I../../../ /D__STL_DEBUG /D_STLP_DEBUG /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /FD /GZ  /c $(CXXFLAGS) -Fpvc6-stlport/boost_regex_vc6-stlport_mddd/boost_regex_vc6-stlport_mddd.pch -Fo./vc6-stlport/boost_regex_vc6-stlport_mddd/ -Fdvc6-stlport/boost_regex_vc6-stlport_mddd.pdb ../src/w32_regex_traits.cpp

vc6-stlport/boost_regex_vc6-stlport_mddd/wide_posix_api.obj: ../src/wide_posix_api.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I$(STLPORT_PATH)\stlport /I../../../ /D__STL_DEBUG /D_STLP_DEBUG /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /FD /GZ  /c $(CXXFLAGS) -Fpvc6-stlport/boost_regex_vc6-stlport_mddd/boost_regex_vc6-stlport_mddd.pch -Fo./vc6-stlport/boost_regex_vc6-stlport_mddd/ -Fdvc6-stlport/boost_regex_vc6-stlport_mddd.pdb ../src/wide_posix_api.cpp

vc6-stlport/boost_regex_vc6-stlport_mddd/winstances.obj: ../src/winstances.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I$(STLPORT_PATH)\stlport /I../../../ /D__STL_DEBUG /D_STLP_DEBUG /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /FD /GZ  /c $(CXXFLAGS) -Fpvc6-stlport/boost_regex_vc6-stlport_mddd/boost_regex_vc6-stlport_mddd.pch -Fo./vc6-stlport/boost_regex_vc6-stlport_mddd/ -Fdvc6-stlport/boost_regex_vc6-stlport_mddd.pdb ../src/winstances.cpp

boost_regex_vc6-stlport_mddd_dir :
	@if not exist "vc6-stlport\boost_regex_vc6-stlport_mddd\$(NULL)" mkdir vc6-stlport\boost_regex_vc6-stlport_mddd

boost_regex_vc6-stlport_mddd_clean :
	del vc6-stlport\boost_regex_vc6-stlport_mddd\*.obj
	del vc6-stlport\boost_regex_vc6-stlport_mddd\*.idb
	del vc6-stlport\boost_regex_vc6-stlport_mddd\*.exp
	del vc6-stlport\boost_regex_vc6-stlport_mddd\*.pch

./vc6-stlport/boost_regex_vc6-stlport_mddd.lib : vc6-stlport/boost_regex_vc6-stlport_mddd/c_regex_traits.obj vc6-stlport/boost_regex_vc6-stlport_mddd/c_regex_traits_common.obj vc6-stlport/boost_regex_vc6-stlport_mddd/cpp_regex_traits.obj vc6-stlport/boost_regex_vc6-stlport_mddd/cregex.obj vc6-stlport/boost_regex_vc6-stlport_mddd/fileiter.obj vc6-stlport/boost_regex_vc6-stlport_mddd/instances.obj vc6-stlport/boost_regex_vc6-stlport_mddd/posix_api.obj vc6-stlport/boost_regex_vc6-stlport_mddd/regex.obj vc6-stlport/boost_regex_vc6-stlport_mddd/regex_debug.obj vc6-stlport/boost_regex_vc6-stlport_mddd/regex_synch.obj vc6-stlport/boost_regex_vc6-stlport_mddd/w32_regex_traits.obj vc6-stlport/boost_regex_vc6-stlport_mddd/wide_posix_api.obj vc6-stlport/boost_regex_vc6-stlport_mddd/winstances.obj
	link kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:yes /pdb:"vc6-stlport/boost_regex_vc6-stlport_mddd.pdb" /debug /machine:I386 /out:"vc6-stlport/boost_regex_vc6-stlport_mddd.dll" /implib:"vc6-stlport/boost_regex_vc6-stlport_mddd.lib" /LIBPATH:$(STLPORT_PATH)\lib $(XLFLAGS)  vc6-stlport/boost_regex_vc6-stlport_mddd/c_regex_traits.obj vc6-stlport/boost_regex_vc6-stlport_mddd/c_regex_traits_common.obj vc6-stlport/boost_regex_vc6-stlport_mddd/cpp_regex_traits.obj vc6-stlport/boost_regex_vc6-stlport_mddd/cregex.obj vc6-stlport/boost_regex_vc6-stlport_mddd/fileiter.obj vc6-stlport/boost_regex_vc6-stlport_mddd/instances.obj vc6-stlport/boost_regex_vc6-stlport_mddd/posix_api.obj vc6-stlport/boost_regex_vc6-stlport_mddd/regex.obj vc6-stlport/boost_regex_vc6-stlport_mddd/regex_debug.obj vc6-stlport/boost_regex_vc6-stlport_mddd/regex_synch.obj vc6-stlport/boost_regex_vc6-stlport_mddd/w32_regex_traits.obj vc6-stlport/boost_regex_vc6-stlport_mddd/wide_posix_api.obj vc6-stlport/boost_regex_vc6-stlport_mddd/winstances.obj

########################################################
#
# section for libboost_regex_vc6-stlport_msdd.lib
#
########################################################
vc6-stlport/libboost_regex_vc6-stlport_msdd/c_regex_traits.obj: ../src/c_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MTd /W3 /Gm /GX /Zi /Od /I$(STLPORT_PATH)\stlport /I..\..\..\ /D__STL_DEBUG /D_STLP_DEBUG /DWIN32 /D_MT /D_DEBUG /D_MBCS /D_LIB /YX /FD /GZ  /c $(CXXFLAGS) -Fpvc6-stlport/libboost_regex_vc6-stlport_msdd/libboost_regex_vc6-stlport_msdd.pch -Fo./vc6-stlport/libboost_regex_vc6-stlport_msdd/ -Fdvc6-stlport/libboost_regex_vc6-stlport_msdd.pdb ../src/c_regex_traits.cpp

vc6-stlport/libboost_regex_vc6-stlport_msdd/c_regex_traits_common.obj: ../src/c_regex_traits_common.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MTd /W3 /Gm /GX /Zi /Od /I$(STLPORT_PATH)\stlport /I..\..\..\ /D__STL_DEBUG /D_STLP_DEBUG /DWIN32 /D_MT /D_DEBUG /D_MBCS /D_LIB /YX /FD /GZ  /c $(CXXFLAGS) -Fpvc6-stlport/libboost_regex_vc6-stlport_msdd/libboost_regex_vc6-stlport_msdd.pch -Fo./vc6-stlport/libboost_regex_vc6-stlport_msdd/ -Fdvc6-stlport/libboost_regex_vc6-stlport_msdd.pdb ../src/c_regex_traits_common.cpp

vc6-stlport/libboost_regex_vc6-stlport_msdd/cpp_regex_traits.obj: ../src/cpp_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MTd /W3 /Gm /GX /Zi /Od /I$(STLPORT_PATH)\stlport /I..\..\..\ /D__STL_DEBUG /D_STLP_DEBUG /DWIN32 /D_MT /D_DEBUG /D_MBCS /D_LIB /YX /FD /GZ  /c $(CXXFLAGS) -Fpvc6-stlport/libboost_regex_vc6-stlport_msdd/libboost_regex_vc6-stlport_msdd.pch -Fo./vc6-stlport/libboost_regex_vc6-stlport_msdd/ -Fdvc6-stlport/libboost_regex_vc6-stlport_msdd.pdb ../src/cpp_regex_traits.cpp

vc6-stlport/libboost_regex_vc6-stlport_msdd/cregex.obj: ../src/cregex.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MTd /W3 /Gm /GX /Zi /Od /I$(STLPORT_PATH)\stlport /I..\..\..\ /D__STL_DEBUG /D_STLP_DEBUG /DWIN32 /D_MT /D_DEBUG /D_MBCS /D_LIB /YX /FD /GZ  /c $(CXXFLAGS) -Fpvc6-stlport/libboost_regex_vc6-stlport_msdd/libboost_regex_vc6-stlport_msdd.pch -Fo./vc6-stlport/libboost_regex_vc6-stlport_msdd/ -Fdvc6-stlport/libboost_regex_vc6-stlport_msdd.pdb ../src/cregex.cpp

vc6-stlport/libboost_regex_vc6-stlport_msdd/fileiter.obj: ../src/fileiter.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MTd /W3 /Gm /GX /Zi /Od /I$(STLPORT_PATH)\stlport /I..\..\..\ /D__STL_DEBUG /D_STLP_DEBUG /DWIN32 /D_MT /D_DEBUG /D_MBCS /D_LIB /YX /FD /GZ  /c $(CXXFLAGS) -Fpvc6-stlport/libboost_regex_vc6-stlport_msdd/libboost_regex_vc6-stlport_msdd.pch -Fo./vc6-stlport/libboost_regex_vc6-stlport_msdd/ -Fdvc6-stlport/libboost_regex_vc6-stlport_msdd.pdb ../src/fileiter.cpp

vc6-stlport/libboost_regex_vc6-stlport_msdd/instances.obj: ../src/instances.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MTd /W3 /Gm /GX /Zi /Od /I$(STLPORT_PATH)\stlport /I..\..\..\ /D__STL_DEBUG /D_STLP_DEBUG /DWIN32 /D_MT /D_DEBUG /D_MBCS /D_LIB /YX /FD /GZ  /c $(CXXFLAGS) -Fpvc6-stlport/libboost_regex_vc6-stlport_msdd/libboost_regex_vc6-stlport_msdd.pch -Fo./vc6-stlport/libboost_regex_vc6-stlport_msdd/ -Fdvc6-stlport/libboost_regex_vc6-stlport_msdd.pdb ../src/instances.cpp

vc6-stlport/libboost_regex_vc6-stlport_msdd/posix_api.obj: ../src/posix_api.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MTd /W3 /Gm /GX /Zi /Od /I$(STLPORT_PATH)\stlport /I..\..\..\ /D__STL_DEBUG /D_STLP_DEBUG /DWIN32 /D_MT /D_DEBUG /D_MBCS /D_LIB /YX /FD /GZ  /c $(CXXFLAGS) -Fpvc6-stlport/libboost_regex_vc6-stlport_msdd/libboost_regex_vc6-stlport_msdd.pch -Fo./vc6-stlport/libboost_regex_vc6-stlport_msdd/ -Fdvc6-stlport/libboost_regex_vc6-stlport_msdd.pdb ../src/posix_api.cpp

vc6-stlport/libboost_regex_vc6-stlport_msdd/regex.obj: ../src/regex.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MTd /W3 /Gm /GX /Zi /Od /I$(STLPORT_PATH)\stlport /I..\..\..\ /D__STL_DEBUG /D_STLP_DEBUG /DWIN32 /D_MT /D_DEBUG /D_MBCS /D_LIB /YX /FD /GZ  /c $(CXXFLAGS) -Fpvc6-stlport/libboost_regex_vc6-stlport_msdd/libboost_regex_vc6-stlport_msdd.pch -Fo./vc6-stlport/libboost_regex_vc6-stlport_msdd/ -Fdvc6-stlport/libboost_regex_vc6-stlport_msdd.pdb ../src/regex.cpp

vc6-stlport/libboost_regex_vc6-stlport_msdd/regex_debug.obj: ../src/regex_debug.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MTd /W3 /Gm /GX /Zi /Od /I$(STLPORT_PATH)\stlport /I..\..\..\ /D__STL_DEBUG /D_STLP_DEBUG /DWIN32 /D_MT /D_DEBUG /D_MBCS /D_LIB /YX /FD /GZ  /c $(CXXFLAGS) -Fpvc6-stlport/libboost_regex_vc6-stlport_msdd/libboost_regex_vc6-stlport_msdd.pch -Fo./vc6-stlport/libboost_regex_vc6-stlport_msdd/ -Fdvc6-stlport/libboost_regex_vc6-stlport_msdd.pdb ../src/regex_debug.cpp

vc6-stlport/libboost_regex_vc6-stlport_msdd/regex_synch.obj: ../src/regex_synch.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MTd /W3 /Gm /GX /Zi /Od /I$(STLPORT_PATH)\stlport /I..\..\..\ /D__STL_DEBUG /D_STLP_DEBUG /DWIN32 /D_MT /D_DEBUG /D_MBCS /D_LIB /YX /FD /GZ  /c $(CXXFLAGS) -Fpvc6-stlport/libboost_regex_vc6-stlport_msdd/libboost_regex_vc6-stlport_msdd.pch -Fo./vc6-stlport/libboost_regex_vc6-stlport_msdd/ -Fdvc6-stlport/libboost_regex_vc6-stlport_msdd.pdb ../src/regex_synch.cpp

vc6-stlport/libboost_regex_vc6-stlport_msdd/w32_regex_traits.obj: ../src/w32_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MTd /W3 /Gm /GX /Zi /Od /I$(STLPORT_PATH)\stlport /I..\..\..\ /D__STL_DEBUG /D_STLP_DEBUG /DWIN32 /D_MT /D_DEBUG /D_MBCS /D_LIB /YX /FD /GZ  /c $(CXXFLAGS) -Fpvc6-stlport/libboost_regex_vc6-stlport_msdd/libboost_regex_vc6-stlport_msdd.pch -Fo./vc6-stlport/libboost_regex_vc6-stlport_msdd/ -Fdvc6-stlport/libboost_regex_vc6-stlport_msdd.pdb ../src/w32_regex_traits.cpp

vc6-stlport/libboost_regex_vc6-stlport_msdd/wide_posix_api.obj: ../src/wide_posix_api.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MTd /W3 /Gm /GX /Zi /Od /I$(STLPORT_PATH)\stlport /I..\..\..\ /D__STL_DEBUG /D_STLP_DEBUG /DWIN32 /D_MT /D_DEBUG /D_MBCS /D_LIB /YX /FD /GZ  /c $(CXXFLAGS) -Fpvc6-stlport/libboost_regex_vc6-stlport_msdd/libboost_regex_vc6-stlport_msdd.pch -Fo./vc6-stlport/libboost_regex_vc6-stlport_msdd/ -Fdvc6-stlport/libboost_regex_vc6-stlport_msdd.pdb ../src/wide_posix_api.cpp

vc6-stlport/libboost_regex_vc6-stlport_msdd/winstances.obj: ../src/winstances.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MTd /W3 /Gm /GX /Zi /Od /I$(STLPORT_PATH)\stlport /I..\..\..\ /D__STL_DEBUG /D_STLP_DEBUG /DWIN32 /D_MT /D_DEBUG /D_MBCS /D_LIB /YX /FD /GZ  /c $(CXXFLAGS) -Fpvc6-stlport/libboost_regex_vc6-stlport_msdd/libboost_regex_vc6-stlport_msdd.pch -Fo./vc6-stlport/libboost_regex_vc6-stlport_msdd/ -Fdvc6-stlport/libboost_regex_vc6-stlport_msdd.pdb ../src/winstances.cpp

libboost_regex_vc6-stlport_msdd_dir :
	@if not exist "vc6-stlport\libboost_regex_vc6-stlport_msdd\$(NULL)" mkdir vc6-stlport\libboost_regex_vc6-stlport_msdd

libboost_regex_vc6-stlport_msdd_clean :
	del vc6-stlport\libboost_regex_vc6-stlport_msdd\*.obj
	del vc6-stlport\libboost_regex_vc6-stlport_msdd\*.idb
	del vc6-stlport\libboost_regex_vc6-stlport_msdd\*.exp
	del vc6-stlport\libboost_regex_vc6-stlport_msdd\*.pch

./vc6-stlport/libboost_regex_vc6-stlport_msdd.lib : vc6-stlport/libboost_regex_vc6-stlport_msdd/c_regex_traits.obj vc6-stlport/libboost_regex_vc6-stlport_msdd/c_regex_traits_common.obj vc6-stlport/libboost_regex_vc6-stlport_msdd/cpp_regex_traits.obj vc6-stlport/libboost_regex_vc6-stlport_msdd/cregex.obj vc6-stlport/libboost_regex_vc6-stlport_msdd/fileiter.obj vc6-stlport/libboost_regex_vc6-stlport_msdd/instances.obj vc6-stlport/libboost_regex_vc6-stlport_msdd/posix_api.obj vc6-stlport/libboost_regex_vc6-stlport_msdd/regex.obj vc6-stlport/libboost_regex_vc6-stlport_msdd/regex_debug.obj vc6-stlport/libboost_regex_vc6-stlport_msdd/regex_synch.obj vc6-stlport/libboost_regex_vc6-stlport_msdd/w32_regex_traits.obj vc6-stlport/libboost_regex_vc6-stlport_msdd/wide_posix_api.obj vc6-stlport/libboost_regex_vc6-stlport_msdd/winstances.obj
	link -lib /nologo /out:vc6-stlport/libboost_regex_vc6-stlport_msdd.lib $(XSFLAGS)  vc6-stlport/libboost_regex_vc6-stlport_msdd/c_regex_traits.obj vc6-stlport/libboost_regex_vc6-stlport_msdd/c_regex_traits_common.obj vc6-stlport/libboost_regex_vc6-stlport_msdd/cpp_regex_traits.obj vc6-stlport/libboost_regex_vc6-stlport_msdd/cregex.obj vc6-stlport/libboost_regex_vc6-stlport_msdd/fileiter.obj vc6-stlport/libboost_regex_vc6-stlport_msdd/instances.obj vc6-stlport/libboost_regex_vc6-stlport_msdd/posix_api.obj vc6-stlport/libboost_regex_vc6-stlport_msdd/regex.obj vc6-stlport/libboost_regex_vc6-stlport_msdd/regex_debug.obj vc6-stlport/libboost_regex_vc6-stlport_msdd/regex_synch.obj vc6-stlport/libboost_regex_vc6-stlport_msdd/w32_regex_traits.obj vc6-stlport/libboost_regex_vc6-stlport_msdd/wide_posix_api.obj vc6-stlport/libboost_regex_vc6-stlport_msdd/winstances.obj

########################################################
#
# section for libboost_regex_vc6-stlport_mddd.lib
#
########################################################
vc6-stlport/libboost_regex_vc6-stlport_mddd/c_regex_traits.obj: ../src/c_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I$(STLPORT_PATH)\stlport /I../../../ /DBOOST_REGEX_STATIC_LINK /D__STL_DEBUG /D_STLP_DEBUG /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /FD /GZ  /c $(CXXFLAGS) -Fpvc6-stlport/libboost_regex_vc6-stlport_mddd/libboost_regex_vc6-stlport_mddd.pch -Fo./vc6-stlport/libboost_regex_vc6-stlport_mddd/ -Fdvc6-stlport/libboost_regex_vc6-stlport_mddd.pdb ../src/c_regex_traits.cpp

vc6-stlport/libboost_regex_vc6-stlport_mddd/c_regex_traits_common.obj: ../src/c_regex_traits_common.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I$(STLPORT_PATH)\stlport /I../../../ /DBOOST_REGEX_STATIC_LINK /D__STL_DEBUG /D_STLP_DEBUG /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /FD /GZ  /c $(CXXFLAGS) -Fpvc6-stlport/libboost_regex_vc6-stlport_mddd/libboost_regex_vc6-stlport_mddd.pch -Fo./vc6-stlport/libboost_regex_vc6-stlport_mddd/ -Fdvc6-stlport/libboost_regex_vc6-stlport_mddd.pdb ../src/c_regex_traits_common.cpp

vc6-stlport/libboost_regex_vc6-stlport_mddd/cpp_regex_traits.obj: ../src/cpp_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I$(STLPORT_PATH)\stlport /I../../../ /DBOOST_REGEX_STATIC_LINK /D__STL_DEBUG /D_STLP_DEBUG /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /FD /GZ  /c $(CXXFLAGS) -Fpvc6-stlport/libboost_regex_vc6-stlport_mddd/libboost_regex_vc6-stlport_mddd.pch -Fo./vc6-stlport/libboost_regex_vc6-stlport_mddd/ -Fdvc6-stlport/libboost_regex_vc6-stlport_mddd.pdb ../src/cpp_regex_traits.cpp

vc6-stlport/libboost_regex_vc6-stlport_mddd/cregex.obj: ../src/cregex.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I$(STLPORT_PATH)\stlport /I../../../ /DBOOST_REGEX_STATIC_LINK /D__STL_DEBUG /D_STLP_DEBUG /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /FD /GZ  /c $(CXXFLAGS) -Fpvc6-stlport/libboost_regex_vc6-stlport_mddd/libboost_regex_vc6-stlport_mddd.pch -Fo./vc6-stlport/libboost_regex_vc6-stlport_mddd/ -Fdvc6-stlport/libboost_regex_vc6-stlport_mddd.pdb ../src/cregex.cpp

vc6-stlport/libboost_regex_vc6-stlport_mddd/fileiter.obj: ../src/fileiter.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I$(STLPORT_PATH)\stlport /I../../../ /DBOOST_REGEX_STATIC_LINK /D__STL_DEBUG /D_STLP_DEBUG /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /FD /GZ  /c $(CXXFLAGS) -Fpvc6-stlport/libboost_regex_vc6-stlport_mddd/libboost_regex_vc6-stlport_mddd.pch -Fo./vc6-stlport/libboost_regex_vc6-stlport_mddd/ -Fdvc6-stlport/libboost_regex_vc6-stlport_mddd.pdb ../src/fileiter.cpp

vc6-stlport/libboost_regex_vc6-stlport_mddd/instances.obj: ../src/instances.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I$(STLPORT_PATH)\stlport /I../../../ /DBOOST_REGEX_STATIC_LINK /D__STL_DEBUG /D_STLP_DEBUG /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /FD /GZ  /c $(CXXFLAGS) -Fpvc6-stlport/libboost_regex_vc6-stlport_mddd/libboost_regex_vc6-stlport_mddd.pch -Fo./vc6-stlport/libboost_regex_vc6-stlport_mddd/ -Fdvc6-stlport/libboost_regex_vc6-stlport_mddd.pdb ../src/instances.cpp

vc6-stlport/libboost_regex_vc6-stlport_mddd/posix_api.obj: ../src/posix_api.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I$(STLPORT_PATH)\stlport /I../../../ /DBOOST_REGEX_STATIC_LINK /D__STL_DEBUG /D_STLP_DEBUG /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /FD /GZ  /c $(CXXFLAGS) -Fpvc6-stlport/libboost_regex_vc6-stlport_mddd/libboost_regex_vc6-stlport_mddd.pch -Fo./vc6-stlport/libboost_regex_vc6-stlport_mddd/ -Fdvc6-stlport/libboost_regex_vc6-stlport_mddd.pdb ../src/posix_api.cpp

vc6-stlport/libboost_regex_vc6-stlport_mddd/regex.obj: ../src/regex.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I$(STLPORT_PATH)\stlport /I../../../ /DBOOST_REGEX_STATIC_LINK /D__STL_DEBUG /D_STLP_DEBUG /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /FD /GZ  /c $(CXXFLAGS) -Fpvc6-stlport/libboost_regex_vc6-stlport_mddd/libboost_regex_vc6-stlport_mddd.pch -Fo./vc6-stlport/libboost_regex_vc6-stlport_mddd/ -Fdvc6-stlport/libboost_regex_vc6-stlport_mddd.pdb ../src/regex.cpp

vc6-stlport/libboost_regex_vc6-stlport_mddd/regex_debug.obj: ../src/regex_debug.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I$(STLPORT_PATH)\stlport /I../../../ /DBOOST_REGEX_STATIC_LINK /D__STL_DEBUG /D_STLP_DEBUG /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /FD /GZ  /c $(CXXFLAGS) -Fpvc6-stlport/libboost_regex_vc6-stlport_mddd/libboost_regex_vc6-stlport_mddd.pch -Fo./vc6-stlport/libboost_regex_vc6-stlport_mddd/ -Fdvc6-stlport/libboost_regex_vc6-stlport_mddd.pdb ../src/regex_debug.cpp

vc6-stlport/libboost_regex_vc6-stlport_mddd/regex_synch.obj: ../src/regex_synch.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I$(STLPORT_PATH)\stlport /I../../../ /DBOOST_REGEX_STATIC_LINK /D__STL_DEBUG /D_STLP_DEBUG /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /FD /GZ  /c $(CXXFLAGS) -Fpvc6-stlport/libboost_regex_vc6-stlport_mddd/libboost_regex_vc6-stlport_mddd.pch -Fo./vc6-stlport/libboost_regex_vc6-stlport_mddd/ -Fdvc6-stlport/libboost_regex_vc6-stlport_mddd.pdb ../src/regex_synch.cpp

vc6-stlport/libboost_regex_vc6-stlport_mddd/w32_regex_traits.obj: ../src/w32_regex_traits.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I$(STLPORT_PATH)\stlport /I../../../ /DBOOST_REGEX_STATIC_LINK /D__STL_DEBUG /D_STLP_DEBUG /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /FD /GZ  /c $(CXXFLAGS) -Fpvc6-stlport/libboost_regex_vc6-stlport_mddd/libboost_regex_vc6-stlport_mddd.pch -Fo./vc6-stlport/libboost_regex_vc6-stlport_mddd/ -Fdvc6-stlport/libboost_regex_vc6-stlport_mddd.pdb ../src/w32_regex_traits.cpp

vc6-stlport/libboost_regex_vc6-stlport_mddd/wide_posix_api.obj: ../src/wide_posix_api.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I$(STLPORT_PATH)\stlport /I../../../ /DBOOST_REGEX_STATIC_LINK /D__STL_DEBUG /D_STLP_DEBUG /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /FD /GZ  /c $(CXXFLAGS) -Fpvc6-stlport/libboost_regex_vc6-stlport_mddd/libboost_regex_vc6-stlport_mddd.pch -Fo./vc6-stlport/libboost_regex_vc6-stlport_mddd/ -Fdvc6-stlport/libboost_regex_vc6-stlport_mddd.pdb ../src/wide_posix_api.cpp

vc6-stlport/libboost_regex_vc6-stlport_mddd/winstances.obj: ../src/winstances.cpp $(ALL_HEADER)
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I$(STLPORT_PATH)\stlport /I../../../ /DBOOST_REGEX_STATIC_LINK /D__STL_DEBUG /D_STLP_DEBUG /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /FD /GZ  /c $(CXXFLAGS) -Fpvc6-stlport/libboost_regex_vc6-stlport_mddd/libboost_regex_vc6-stlport_mddd.pch -Fo./vc6-stlport/libboost_regex_vc6-stlport_mddd/ -Fdvc6-stlport/libboost_regex_vc6-stlport_mddd.pdb ../src/winstances.cpp

libboost_regex_vc6-stlport_mddd_dir :
	@if not exist "vc6-stlport\libboost_regex_vc6-stlport_mddd\$(NULL)" mkdir vc6-stlport\libboost_regex_vc6-stlport_mddd

libboost_regex_vc6-stlport_mddd_clean :
	del vc6-stlport\libboost_regex_vc6-stlport_mddd\*.obj
	del vc6-stlport\libboost_regex_vc6-stlport_mddd\*.idb
	del vc6-stlport\libboost_regex_vc6-stlport_mddd\*.exp
	del vc6-stlport\libboost_regex_vc6-stlport_mddd\*.pch

./vc6-stlport/libboost_regex_vc6-stlport_mddd.lib : vc6-stlport/libboost_regex_vc6-stlport_mddd/c_regex_traits.obj vc6-stlport/libboost_regex_vc6-stlport_mddd/c_regex_traits_common.obj vc6-stlport/libboost_regex_vc6-stlport_mddd/cpp_regex_traits.obj vc6-stlport/libboost_regex_vc6-stlport_mddd/cregex.obj vc6-stlport/libboost_regex_vc6-stlport_mddd/fileiter.obj vc6-stlport/libboost_regex_vc6-stlport_mddd/instances.obj vc6-stlport/libboost_regex_vc6-stlport_mddd/posix_api.obj vc6-stlport/libboost_regex_vc6-stlport_mddd/regex.obj vc6-stlport/libboost_regex_vc6-stlport_mddd/regex_debug.obj vc6-stlport/libboost_regex_vc6-stlport_mddd/regex_synch.obj vc6-stlport/libboost_regex_vc6-stlport_mddd/w32_regex_traits.obj vc6-stlport/libboost_regex_vc6-stlport_mddd/wide_posix_api.obj vc6-stlport/libboost_regex_vc6-stlport_mddd/winstances.obj
	link -lib /nologo /out:vc6-stlport/libboost_regex_vc6-stlport_mddd.lib $(XSFLAGS)  vc6-stlport/libboost_regex_vc6-stlport_mddd/c_regex_traits.obj vc6-stlport/libboost_regex_vc6-stlport_mddd/c_regex_traits_common.obj vc6-stlport/libboost_regex_vc6-stlport_mddd/cpp_regex_traits.obj vc6-stlport/libboost_regex_vc6-stlport_mddd/cregex.obj vc6-stlport/libboost_regex_vc6-stlport_mddd/fileiter.obj vc6-stlport/libboost_regex_vc6-stlport_mddd/instances.obj vc6-stlport/libboost_regex_vc6-stlport_mddd/posix_api.obj vc6-stlport/libboost_regex_vc6-stlport_mddd/regex.obj vc6-stlport/libboost_regex_vc6-stlport_mddd/regex_debug.obj vc6-stlport/libboost_regex_vc6-stlport_mddd/regex_synch.obj vc6-stlport/libboost_regex_vc6-stlport_mddd/w32_regex_traits.obj vc6-stlport/libboost_regex_vc6-stlport_mddd/wide_posix_api.obj vc6-stlport/libboost_regex_vc6-stlport_mddd/winstances.obj

