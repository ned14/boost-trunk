#
# auto generated makefile for C++ Builder
#
# usage:
# make
#   brings libraries up to date
# make install
#   brings libraries up to date and copies binaries to your C++ Builder /lib and /bin directories (recomended)
# make clean
#   removes all temporary files.

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
# add additional libraries to link to here:
#
LIBS=
#
# add additional static-library creation flags here:
#
XSFLAGS=

!ifndef BCROOT
BCROOT=$(MAKEDIR)\..
!endif


ALL_HEADER= ../../../boost/regex/config.hpp ../../../boost/regex/pattern_except.hpp ../../../boost/regex/regex_traits.hpp ../../../boost/regex/user.hpp ../../../boost/regex/detail/fileiter.hpp ../../../boost/regex/detail/regex_compile.hpp ../../../boost/regex/detail/regex_cstring.hpp ../../../boost/regex/detail/regex_format.hpp ../../../boost/regex/detail/regex_kmp.hpp ../../../boost/regex/detail/regex_library_include.hpp ../../../boost/regex/detail/regex_match.hpp ../../../boost/regex/detail/regex_raw_buffer.hpp ../../../boost/regex/detail/regex_split.hpp ../../../boost/regex/detail/regex_stack.hpp ../../../boost/regex/detail/regex_synch.hpp

all : bcb5 bcb5\bcb5re300 bcb5\bcb5re300.lib bcb5\bcb5re300m bcb5\bcb5re300m.lib bcb5\bcb5re300v bcb5\bcb5re300v.lib bcb5\bcb5re300lv bcb5\bcb5re300lv.lib bcb5\bcb5re300lm bcb5\bcb5re300lm.lib bcb5\bcb5re300l bcb5\bcb5re300l.lib

clean :  bcb5re300_clean bcb5re300m_clean bcb5re300v_clean bcb5re300lv_clean bcb5re300lm_clean bcb5re300l_clean

install : all
	copy bcb5\bcb5re300.lib $(BCROOT)\lib
	copy bcb5\bcb5re300m.lib $(BCROOT)\lib
	copy bcb5\bcb5re300v.lib $(BCROOT)\lib
	copy bcb5\bcb5re300lv.lib $(BCROOT)\lib
	copy bcb5\bcb5re300lv.dll $(BCROOT)\bin
	copy bcb5\bcb5re300lm.lib $(BCROOT)\lib
	copy bcb5\bcb5re300lm.dll $(BCROOT)\bin
	copy bcb5\bcb5re300l.lib $(BCROOT)\lib
	copy bcb5\bcb5re300l.dll $(BCROOT)\bin

bcb5 :
	-mkdir bcb5


########################################################
#
# section for bcb5re300.lib
#
########################################################
bcb5\bcb5re300\c_regex_traits.obj: ../src/c_regex_traits.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM- -D_NO_VCL -O2 -w-inl -w-aus -w-rch -w-8012 -w-8037 -w-8057 -DSTRICT; -I$(BCROOT)\include;../../../ $(CXXFLAGS) -obcb5\bcb5re300\c_regex_traits.obj ../src/c_regex_traits.cpp
|

bcb5\bcb5re300\c_regex_traits_common.obj: ../src/c_regex_traits_common.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM- -D_NO_VCL -O2 -w-inl -w-aus -w-rch -w-8012 -w-8037 -w-8057 -DSTRICT; -I$(BCROOT)\include;../../../ $(CXXFLAGS) -obcb5\bcb5re300\c_regex_traits_common.obj ../src/c_regex_traits_common.cpp
|

bcb5\bcb5re300\cpp_regex_traits.obj: ../src/cpp_regex_traits.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM- -D_NO_VCL -O2 -w-inl -w-aus -w-rch -w-8012 -w-8037 -w-8057 -DSTRICT; -I$(BCROOT)\include;../../../ $(CXXFLAGS) -obcb5\bcb5re300\cpp_regex_traits.obj ../src/cpp_regex_traits.cpp
|

bcb5\bcb5re300\cregex.obj: ../src/cregex.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM- -D_NO_VCL -O2 -w-inl -w-aus -w-rch -w-8012 -w-8037 -w-8057 -DSTRICT; -I$(BCROOT)\include;../../../ $(CXXFLAGS) -obcb5\bcb5re300\cregex.obj ../src/cregex.cpp
|

bcb5\bcb5re300\fileiter.obj: ../src/fileiter.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM- -D_NO_VCL -O2 -w-inl -w-aus -w-rch -w-8012 -w-8037 -w-8057 -DSTRICT; -I$(BCROOT)\include;../../../ $(CXXFLAGS) -obcb5\bcb5re300\fileiter.obj ../src/fileiter.cpp
|

bcb5\bcb5re300\posix_api.obj: ../src/posix_api.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM- -D_NO_VCL -O2 -w-inl -w-aus -w-rch -w-8012 -w-8037 -w-8057 -DSTRICT; -I$(BCROOT)\include;../../../ $(CXXFLAGS) -obcb5\bcb5re300\posix_api.obj ../src/posix_api.cpp
|

bcb5\bcb5re300\regex.obj: ../src/regex.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM- -D_NO_VCL -O2 -w-inl -w-aus -w-rch -w-8012 -w-8037 -w-8057 -DSTRICT; -I$(BCROOT)\include;../../../ $(CXXFLAGS) -obcb5\bcb5re300\regex.obj ../src/regex.cpp
|

bcb5\bcb5re300\regex_debug.obj: ../src/regex_debug.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM- -D_NO_VCL -O2 -w-inl -w-aus -w-rch -w-8012 -w-8037 -w-8057 -DSTRICT; -I$(BCROOT)\include;../../../ $(CXXFLAGS) -obcb5\bcb5re300\regex_debug.obj ../src/regex_debug.cpp
|

bcb5\bcb5re300\regex_synch.obj: ../src/regex_synch.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM- -D_NO_VCL -O2 -w-inl -w-aus -w-rch -w-8012 -w-8037 -w-8057 -DSTRICT; -I$(BCROOT)\include;../../../ $(CXXFLAGS) -obcb5\bcb5re300\regex_synch.obj ../src/regex_synch.cpp
|

bcb5\bcb5re300\w32_regex_traits.obj: ../src/w32_regex_traits.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM- -D_NO_VCL -O2 -w-inl -w-aus -w-rch -w-8012 -w-8037 -w-8057 -DSTRICT; -I$(BCROOT)\include;../../../ $(CXXFLAGS) -obcb5\bcb5re300\w32_regex_traits.obj ../src/w32_regex_traits.cpp
|

bcb5\bcb5re300\wide_posix_api.obj: ../src/wide_posix_api.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM- -D_NO_VCL -O2 -w-inl -w-aus -w-rch -w-8012 -w-8037 -w-8057 -DSTRICT; -I$(BCROOT)\include;../../../ $(CXXFLAGS) -obcb5\bcb5re300\wide_posix_api.obj ../src/wide_posix_api.cpp
|

bcb5\bcb5re300 : 
	-mkdir bcb5\bcb5re300

bcb5re300_clean :
	del bcb5\bcb5re300\*.obj
	del bcb5\bcb5re300\*.il?
	del bcb5\bcb5re300\*.csm
	del bcb5\bcb5re300\*.tds

bcb5\bcb5re300.lib : bcb5\bcb5re300\c_regex_traits.obj bcb5\bcb5re300\c_regex_traits_common.obj bcb5\bcb5re300\cpp_regex_traits.obj bcb5\bcb5re300\cregex.obj bcb5\bcb5re300\fileiter.obj bcb5\bcb5re300\posix_api.obj bcb5\bcb5re300\regex.obj bcb5\bcb5re300\regex_debug.obj bcb5\bcb5re300\regex_synch.obj bcb5\bcb5re300\w32_regex_traits.obj bcb5\bcb5re300\wide_posix_api.obj
	tlib @&&|
/P32 /C /u /a $(XSFLAGS) bcb5\bcb5re300.lib  +bcb5\bcb5re300\c_regex_traits.obj +bcb5\bcb5re300\c_regex_traits_common.obj +bcb5\bcb5re300\cpp_regex_traits.obj +bcb5\bcb5re300\cregex.obj +bcb5\bcb5re300\fileiter.obj +bcb5\bcb5re300\posix_api.obj +bcb5\bcb5re300\regex.obj +bcb5\bcb5re300\regex_debug.obj +bcb5\bcb5re300\regex_synch.obj +bcb5\bcb5re300\w32_regex_traits.obj +bcb5\bcb5re300\wide_posix_api.obj
|

########################################################
#
# section for bcb5re300m.lib
#
########################################################
bcb5\bcb5re300m\c_regex_traits.obj: ../src/c_regex_traits.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM -D_NO_VCL -O2 -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ $(CXXFLAGS) -obcb5\bcb5re300m\c_regex_traits.obj ../src/c_regex_traits.cpp
|

bcb5\bcb5re300m\c_regex_traits_common.obj: ../src/c_regex_traits_common.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM -D_NO_VCL -O2 -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ $(CXXFLAGS) -obcb5\bcb5re300m\c_regex_traits_common.obj ../src/c_regex_traits_common.cpp
|

bcb5\bcb5re300m\cpp_regex_traits.obj: ../src/cpp_regex_traits.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM -D_NO_VCL -O2 -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ $(CXXFLAGS) -obcb5\bcb5re300m\cpp_regex_traits.obj ../src/cpp_regex_traits.cpp
|

bcb5\bcb5re300m\cregex.obj: ../src/cregex.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM -D_NO_VCL -O2 -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ $(CXXFLAGS) -obcb5\bcb5re300m\cregex.obj ../src/cregex.cpp
|

bcb5\bcb5re300m\fileiter.obj: ../src/fileiter.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM -D_NO_VCL -O2 -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ $(CXXFLAGS) -obcb5\bcb5re300m\fileiter.obj ../src/fileiter.cpp
|

bcb5\bcb5re300m\posix_api.obj: ../src/posix_api.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM -D_NO_VCL -O2 -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ $(CXXFLAGS) -obcb5\bcb5re300m\posix_api.obj ../src/posix_api.cpp
|

bcb5\bcb5re300m\regex.obj: ../src/regex.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM -D_NO_VCL -O2 -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ $(CXXFLAGS) -obcb5\bcb5re300m\regex.obj ../src/regex.cpp
|

bcb5\bcb5re300m\regex_debug.obj: ../src/regex_debug.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM -D_NO_VCL -O2 -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ $(CXXFLAGS) -obcb5\bcb5re300m\regex_debug.obj ../src/regex_debug.cpp
|

bcb5\bcb5re300m\regex_synch.obj: ../src/regex_synch.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM -D_NO_VCL -O2 -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ $(CXXFLAGS) -obcb5\bcb5re300m\regex_synch.obj ../src/regex_synch.cpp
|

bcb5\bcb5re300m\w32_regex_traits.obj: ../src/w32_regex_traits.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM -D_NO_VCL -O2 -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ $(CXXFLAGS) -obcb5\bcb5re300m\w32_regex_traits.obj ../src/w32_regex_traits.cpp
|

bcb5\bcb5re300m\wide_posix_api.obj: ../src/wide_posix_api.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM -D_NO_VCL -O2 -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ $(CXXFLAGS) -obcb5\bcb5re300m\wide_posix_api.obj ../src/wide_posix_api.cpp
|

bcb5\bcb5re300m : 
	-mkdir bcb5\bcb5re300m

bcb5re300m_clean :
	del bcb5\bcb5re300m\*.obj
	del bcb5\bcb5re300m\*.il?
	del bcb5\bcb5re300m\*.csm
	del bcb5\bcb5re300m\*.tds

bcb5\bcb5re300m.lib : bcb5\bcb5re300m\c_regex_traits.obj bcb5\bcb5re300m\c_regex_traits_common.obj bcb5\bcb5re300m\cpp_regex_traits.obj bcb5\bcb5re300m\cregex.obj bcb5\bcb5re300m\fileiter.obj bcb5\bcb5re300m\posix_api.obj bcb5\bcb5re300m\regex.obj bcb5\bcb5re300m\regex_debug.obj bcb5\bcb5re300m\regex_synch.obj bcb5\bcb5re300m\w32_regex_traits.obj bcb5\bcb5re300m\wide_posix_api.obj
	tlib @&&|
/P32 /C /u /a $(XSFLAGS) bcb5\bcb5re300m.lib  +bcb5\bcb5re300m\c_regex_traits.obj +bcb5\bcb5re300m\c_regex_traits_common.obj +bcb5\bcb5re300m\cpp_regex_traits.obj +bcb5\bcb5re300m\cregex.obj +bcb5\bcb5re300m\fileiter.obj +bcb5\bcb5re300m\posix_api.obj +bcb5\bcb5re300m\regex.obj +bcb5\bcb5re300m\regex_debug.obj +bcb5\bcb5re300m\regex_synch.obj +bcb5\bcb5re300m\w32_regex_traits.obj +bcb5\bcb5re300m\wide_posix_api.obj
|

########################################################
#
# section for bcb5re300v.lib
#
########################################################
bcb5\bcb5re300v\c_regex_traits.obj: ../src/c_regex_traits.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM -tWV -DJM_USE_VCL -O2 -w-inl -w-aus -w-rch -w-8012 -w-8037 -w-8057 -DSTRICT; -I$(BCROOT)\include;../../../ $(CXXFLAGS) -obcb5\bcb5re300v\c_regex_traits.obj ../src/c_regex_traits.cpp
|

bcb5\bcb5re300v\c_regex_traits_common.obj: ../src/c_regex_traits_common.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM -tWV -DJM_USE_VCL -O2 -w-inl -w-aus -w-rch -w-8012 -w-8037 -w-8057 -DSTRICT; -I$(BCROOT)\include;../../../ $(CXXFLAGS) -obcb5\bcb5re300v\c_regex_traits_common.obj ../src/c_regex_traits_common.cpp
|

bcb5\bcb5re300v\cpp_regex_traits.obj: ../src/cpp_regex_traits.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM -tWV -DJM_USE_VCL -O2 -w-inl -w-aus -w-rch -w-8012 -w-8037 -w-8057 -DSTRICT; -I$(BCROOT)\include;../../../ $(CXXFLAGS) -obcb5\bcb5re300v\cpp_regex_traits.obj ../src/cpp_regex_traits.cpp
|

bcb5\bcb5re300v\cregex.obj: ../src/cregex.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM -tWV -DJM_USE_VCL -O2 -w-inl -w-aus -w-rch -w-8012 -w-8037 -w-8057 -DSTRICT; -I$(BCROOT)\include;../../../ $(CXXFLAGS) -obcb5\bcb5re300v\cregex.obj ../src/cregex.cpp
|

bcb5\bcb5re300v\fileiter.obj: ../src/fileiter.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM -tWV -DJM_USE_VCL -O2 -w-inl -w-aus -w-rch -w-8012 -w-8037 -w-8057 -DSTRICT; -I$(BCROOT)\include;../../../ $(CXXFLAGS) -obcb5\bcb5re300v\fileiter.obj ../src/fileiter.cpp
|

bcb5\bcb5re300v\posix_api.obj: ../src/posix_api.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM -tWV -DJM_USE_VCL -O2 -w-inl -w-aus -w-rch -w-8012 -w-8037 -w-8057 -DSTRICT; -I$(BCROOT)\include;../../../ $(CXXFLAGS) -obcb5\bcb5re300v\posix_api.obj ../src/posix_api.cpp
|

bcb5\bcb5re300v\regex.obj: ../src/regex.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM -tWV -DJM_USE_VCL -O2 -w-inl -w-aus -w-rch -w-8012 -w-8037 -w-8057 -DSTRICT; -I$(BCROOT)\include;../../../ $(CXXFLAGS) -obcb5\bcb5re300v\regex.obj ../src/regex.cpp
|

bcb5\bcb5re300v\regex_debug.obj: ../src/regex_debug.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM -tWV -DJM_USE_VCL -O2 -w-inl -w-aus -w-rch -w-8012 -w-8037 -w-8057 -DSTRICT; -I$(BCROOT)\include;../../../ $(CXXFLAGS) -obcb5\bcb5re300v\regex_debug.obj ../src/regex_debug.cpp
|

bcb5\bcb5re300v\regex_synch.obj: ../src/regex_synch.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM -tWV -DJM_USE_VCL -O2 -w-inl -w-aus -w-rch -w-8012 -w-8037 -w-8057 -DSTRICT; -I$(BCROOT)\include;../../../ $(CXXFLAGS) -obcb5\bcb5re300v\regex_synch.obj ../src/regex_synch.cpp
|

bcb5\bcb5re300v\w32_regex_traits.obj: ../src/w32_regex_traits.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM -tWV -DJM_USE_VCL -O2 -w-inl -w-aus -w-rch -w-8012 -w-8037 -w-8057 -DSTRICT; -I$(BCROOT)\include;../../../ $(CXXFLAGS) -obcb5\bcb5re300v\w32_regex_traits.obj ../src/w32_regex_traits.cpp
|

bcb5\bcb5re300v\wide_posix_api.obj: ../src/wide_posix_api.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWM -tWV -DJM_USE_VCL -O2 -w-inl -w-aus -w-rch -w-8012 -w-8037 -w-8057 -DSTRICT; -I$(BCROOT)\include;../../../ $(CXXFLAGS) -obcb5\bcb5re300v\wide_posix_api.obj ../src/wide_posix_api.cpp
|

bcb5\bcb5re300v : 
	-mkdir bcb5\bcb5re300v

bcb5re300v_clean :
	del bcb5\bcb5re300v\*.obj
	del bcb5\bcb5re300v\*.il?
	del bcb5\bcb5re300v\*.csm
	del bcb5\bcb5re300v\*.tds

bcb5\bcb5re300v.lib : bcb5\bcb5re300v\c_regex_traits.obj bcb5\bcb5re300v\c_regex_traits_common.obj bcb5\bcb5re300v\cpp_regex_traits.obj bcb5\bcb5re300v\cregex.obj bcb5\bcb5re300v\fileiter.obj bcb5\bcb5re300v\posix_api.obj bcb5\bcb5re300v\regex.obj bcb5\bcb5re300v\regex_debug.obj bcb5\bcb5re300v\regex_synch.obj bcb5\bcb5re300v\w32_regex_traits.obj bcb5\bcb5re300v\wide_posix_api.obj
	tlib @&&|
/P32 /C /u /a $(XSFLAGS) bcb5\bcb5re300v.lib  +bcb5\bcb5re300v\c_regex_traits.obj +bcb5\bcb5re300v\c_regex_traits_common.obj +bcb5\bcb5re300v\cpp_regex_traits.obj +bcb5\bcb5re300v\cregex.obj +bcb5\bcb5re300v\fileiter.obj +bcb5\bcb5re300v\posix_api.obj +bcb5\bcb5re300v\regex.obj +bcb5\bcb5re300v\regex_debug.obj +bcb5\bcb5re300v\regex_synch.obj +bcb5\bcb5re300v\w32_regex_traits.obj +bcb5\bcb5re300v\wide_posix_api.obj
|

########################################################
#
# section for bcb5re300lv.lib
#
########################################################
bcb5\bcb5re300lv\c_regex_traits.obj: ../src/c_regex_traits.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWM -tWR -tWV -DJM_USE_VCL -D_RTLDLL -O2 -w-inl -w-aus -w-rch -w-8012 -w-8037 -w-8057 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb5\bcb5re300lv\c_regex_traits.obj ../src/c_regex_traits.cpp
|

bcb5\bcb5re300lv\c_regex_traits_common.obj: ../src/c_regex_traits_common.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWM -tWR -tWV -DJM_USE_VCL -D_RTLDLL -O2 -w-inl -w-aus -w-rch -w-8012 -w-8037 -w-8057 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb5\bcb5re300lv\c_regex_traits_common.obj ../src/c_regex_traits_common.cpp
|

bcb5\bcb5re300lv\cpp_regex_traits.obj: ../src/cpp_regex_traits.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWM -tWR -tWV -DJM_USE_VCL -D_RTLDLL -O2 -w-inl -w-aus -w-rch -w-8012 -w-8037 -w-8057 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb5\bcb5re300lv\cpp_regex_traits.obj ../src/cpp_regex_traits.cpp
|

bcb5\bcb5re300lv\cregex.obj: ../src/cregex.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWM -tWR -tWV -DJM_USE_VCL -D_RTLDLL -O2 -w-inl -w-aus -w-rch -w-8012 -w-8037 -w-8057 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb5\bcb5re300lv\cregex.obj ../src/cregex.cpp
|

bcb5\bcb5re300lv\fileiter.obj: ../src/fileiter.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWM -tWR -tWV -DJM_USE_VCL -D_RTLDLL -O2 -w-inl -w-aus -w-rch -w-8012 -w-8037 -w-8057 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb5\bcb5re300lv\fileiter.obj ../src/fileiter.cpp
|

bcb5\bcb5re300lv\posix_api.obj: ../src/posix_api.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWM -tWR -tWV -DJM_USE_VCL -D_RTLDLL -O2 -w-inl -w-aus -w-rch -w-8012 -w-8037 -w-8057 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb5\bcb5re300lv\posix_api.obj ../src/posix_api.cpp
|

bcb5\bcb5re300lv\regex.obj: ../src/regex.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWM -tWR -tWV -DJM_USE_VCL -D_RTLDLL -O2 -w-inl -w-aus -w-rch -w-8012 -w-8037 -w-8057 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb5\bcb5re300lv\regex.obj ../src/regex.cpp
|

bcb5\bcb5re300lv\regex_debug.obj: ../src/regex_debug.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWM -tWR -tWV -DJM_USE_VCL -D_RTLDLL -O2 -w-inl -w-aus -w-rch -w-8012 -w-8037 -w-8057 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb5\bcb5re300lv\regex_debug.obj ../src/regex_debug.cpp
|

bcb5\bcb5re300lv\regex_synch.obj: ../src/regex_synch.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWM -tWR -tWV -DJM_USE_VCL -D_RTLDLL -O2 -w-inl -w-aus -w-rch -w-8012 -w-8037 -w-8057 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb5\bcb5re300lv\regex_synch.obj ../src/regex_synch.cpp
|

bcb5\bcb5re300lv\w32_regex_traits.obj: ../src/w32_regex_traits.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWM -tWR -tWV -DJM_USE_VCL -D_RTLDLL -O2 -w-inl -w-aus -w-rch -w-8012 -w-8037 -w-8057 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb5\bcb5re300lv\w32_regex_traits.obj ../src/w32_regex_traits.cpp
|

bcb5\bcb5re300lv\wide_posix_api.obj: ../src/wide_posix_api.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWM -tWR -tWV -DJM_USE_VCL -D_RTLDLL -O2 -w-inl -w-aus -w-rch -w-8012 -w-8037 -w-8057 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb5\bcb5re300lv\wide_posix_api.obj ../src/wide_posix_api.cpp
|

bcb5\bcb5re300lv :
	-mkdir bcb5\bcb5re300lv

bcb5re300lv_clean :
	del bcb5\bcb5re300lv\*.obj
	del bcb5\bcb5re300lv\*.il?
	del bcb5\bcb5re300lv\*.csm
	del bcb5\bcb5re300lv\*.tds
	del bcb5\*.tds

bcb5\bcb5re300lv.lib : bcb5\bcb5re300lv\c_regex_traits.obj bcb5\bcb5re300lv\c_regex_traits_common.obj bcb5\bcb5re300lv\cpp_regex_traits.obj bcb5\bcb5re300lv\cregex.obj bcb5\bcb5re300lv\fileiter.obj bcb5\bcb5re300lv\posix_api.obj bcb5\bcb5re300lv\regex.obj bcb5\bcb5re300lv\regex_debug.obj bcb5\bcb5re300lv\regex_synch.obj bcb5\bcb5re300lv\w32_regex_traits.obj bcb5\bcb5re300lv\wide_posix_api.obj
	bcc32 @&&|
-tWD -tWM -tWR -tWV -DJM_USE_VCL -D_RTLDLL -O2 -w-inl -w-aus -w-rch -w-8012 -w-8037 -w-8057 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; -ebcb5\bcb5re300lv.dll $(XLFLAGS)  bcb5\bcb5re300lv\c_regex_traits.obj bcb5\bcb5re300lv\c_regex_traits_common.obj bcb5\bcb5re300lv\cpp_regex_traits.obj bcb5\bcb5re300lv\cregex.obj bcb5\bcb5re300lv\fileiter.obj bcb5\bcb5re300lv\posix_api.obj bcb5\bcb5re300lv\regex.obj bcb5\bcb5re300lv\regex_debug.obj bcb5\bcb5re300lv\regex_synch.obj bcb5\bcb5re300lv\w32_regex_traits.obj bcb5\bcb5re300lv\wide_posix_api.obj $(LIBS)
|
	implib -c bcb5\bcb5re300lv.lib bcb5\bcb5re300lv.dll

########################################################
#
# section for bcb5re300lm.lib
#
########################################################
bcb5\bcb5re300lm\c_regex_traits.obj: ../src/c_regex_traits.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWM -tWR -D_NO_VCL -D_RTLDLL -O2 -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb5\bcb5re300lm\c_regex_traits.obj ../src/c_regex_traits.cpp
|

bcb5\bcb5re300lm\c_regex_traits_common.obj: ../src/c_regex_traits_common.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWM -tWR -D_NO_VCL -D_RTLDLL -O2 -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb5\bcb5re300lm\c_regex_traits_common.obj ../src/c_regex_traits_common.cpp
|

bcb5\bcb5re300lm\cpp_regex_traits.obj: ../src/cpp_regex_traits.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWM -tWR -D_NO_VCL -D_RTLDLL -O2 -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb5\bcb5re300lm\cpp_regex_traits.obj ../src/cpp_regex_traits.cpp
|

bcb5\bcb5re300lm\cregex.obj: ../src/cregex.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWM -tWR -D_NO_VCL -D_RTLDLL -O2 -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb5\bcb5re300lm\cregex.obj ../src/cregex.cpp
|

bcb5\bcb5re300lm\fileiter.obj: ../src/fileiter.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWM -tWR -D_NO_VCL -D_RTLDLL -O2 -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb5\bcb5re300lm\fileiter.obj ../src/fileiter.cpp
|

bcb5\bcb5re300lm\posix_api.obj: ../src/posix_api.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWM -tWR -D_NO_VCL -D_RTLDLL -O2 -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb5\bcb5re300lm\posix_api.obj ../src/posix_api.cpp
|

bcb5\bcb5re300lm\regex.obj: ../src/regex.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWM -tWR -D_NO_VCL -D_RTLDLL -O2 -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb5\bcb5re300lm\regex.obj ../src/regex.cpp
|

bcb5\bcb5re300lm\regex_debug.obj: ../src/regex_debug.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWM -tWR -D_NO_VCL -D_RTLDLL -O2 -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb5\bcb5re300lm\regex_debug.obj ../src/regex_debug.cpp
|

bcb5\bcb5re300lm\regex_synch.obj: ../src/regex_synch.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWM -tWR -D_NO_VCL -D_RTLDLL -O2 -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb5\bcb5re300lm\regex_synch.obj ../src/regex_synch.cpp
|

bcb5\bcb5re300lm\w32_regex_traits.obj: ../src/w32_regex_traits.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWM -tWR -D_NO_VCL -D_RTLDLL -O2 -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb5\bcb5re300lm\w32_regex_traits.obj ../src/w32_regex_traits.cpp
|

bcb5\bcb5re300lm\wide_posix_api.obj: ../src/wide_posix_api.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWM -tWR -D_NO_VCL -D_RTLDLL -O2 -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb5\bcb5re300lm\wide_posix_api.obj ../src/wide_posix_api.cpp
|

bcb5\bcb5re300lm :
	-mkdir bcb5\bcb5re300lm

bcb5re300lm_clean :
	del bcb5\bcb5re300lm\*.obj
	del bcb5\bcb5re300lm\*.il?
	del bcb5\bcb5re300lm\*.csm
	del bcb5\bcb5re300lm\*.tds
	del bcb5\*.tds

bcb5\bcb5re300lm.lib : bcb5\bcb5re300lm\c_regex_traits.obj bcb5\bcb5re300lm\c_regex_traits_common.obj bcb5\bcb5re300lm\cpp_regex_traits.obj bcb5\bcb5re300lm\cregex.obj bcb5\bcb5re300lm\fileiter.obj bcb5\bcb5re300lm\posix_api.obj bcb5\bcb5re300lm\regex.obj bcb5\bcb5re300lm\regex_debug.obj bcb5\bcb5re300lm\regex_synch.obj bcb5\bcb5re300lm\w32_regex_traits.obj bcb5\bcb5re300lm\wide_posix_api.obj
	bcc32 @&&|
-tWD -tWM -tWR -D_NO_VCL -D_RTLDLL -O2 -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; -ebcb5\bcb5re300lm.dll $(XLFLAGS)  bcb5\bcb5re300lm\c_regex_traits.obj bcb5\bcb5re300lm\c_regex_traits_common.obj bcb5\bcb5re300lm\cpp_regex_traits.obj bcb5\bcb5re300lm\cregex.obj bcb5\bcb5re300lm\fileiter.obj bcb5\bcb5re300lm\posix_api.obj bcb5\bcb5re300lm\regex.obj bcb5\bcb5re300lm\regex_debug.obj bcb5\bcb5re300lm\regex_synch.obj bcb5\bcb5re300lm\w32_regex_traits.obj bcb5\bcb5re300lm\wide_posix_api.obj $(LIBS)
|
	implib -c bcb5\bcb5re300lm.lib bcb5\bcb5re300lm.dll

########################################################
#
# section for bcb5re300l.lib
#
########################################################
bcb5\bcb5re300l\c_regex_traits.obj: ../src/c_regex_traits.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWR -tWM- -D_NO_VCL -D_RTLDLL -O2 -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb5\bcb5re300l\c_regex_traits.obj ../src/c_regex_traits.cpp
|

bcb5\bcb5re300l\c_regex_traits_common.obj: ../src/c_regex_traits_common.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWR -tWM- -D_NO_VCL -D_RTLDLL -O2 -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb5\bcb5re300l\c_regex_traits_common.obj ../src/c_regex_traits_common.cpp
|

bcb5\bcb5re300l\cpp_regex_traits.obj: ../src/cpp_regex_traits.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWR -tWM- -D_NO_VCL -D_RTLDLL -O2 -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb5\bcb5re300l\cpp_regex_traits.obj ../src/cpp_regex_traits.cpp
|

bcb5\bcb5re300l\cregex.obj: ../src/cregex.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWR -tWM- -D_NO_VCL -D_RTLDLL -O2 -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb5\bcb5re300l\cregex.obj ../src/cregex.cpp
|

bcb5\bcb5re300l\fileiter.obj: ../src/fileiter.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWR -tWM- -D_NO_VCL -D_RTLDLL -O2 -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb5\bcb5re300l\fileiter.obj ../src/fileiter.cpp
|

bcb5\bcb5re300l\posix_api.obj: ../src/posix_api.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWR -tWM- -D_NO_VCL -D_RTLDLL -O2 -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb5\bcb5re300l\posix_api.obj ../src/posix_api.cpp
|

bcb5\bcb5re300l\regex.obj: ../src/regex.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWR -tWM- -D_NO_VCL -D_RTLDLL -O2 -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb5\bcb5re300l\regex.obj ../src/regex.cpp
|

bcb5\bcb5re300l\regex_debug.obj: ../src/regex_debug.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWR -tWM- -D_NO_VCL -D_RTLDLL -O2 -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb5\bcb5re300l\regex_debug.obj ../src/regex_debug.cpp
|

bcb5\bcb5re300l\regex_synch.obj: ../src/regex_synch.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWR -tWM- -D_NO_VCL -D_RTLDLL -O2 -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb5\bcb5re300l\regex_synch.obj ../src/regex_synch.cpp
|

bcb5\bcb5re300l\w32_regex_traits.obj: ../src/w32_regex_traits.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWR -tWM- -D_NO_VCL -D_RTLDLL -O2 -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb5\bcb5re300l\w32_regex_traits.obj ../src/w32_regex_traits.cpp
|

bcb5\bcb5re300l\wide_posix_api.obj: ../src/wide_posix_api.cpp $(ALL_HEADER)
	bcc32 @&&|
-c $(INCLUDES) -tWD -tWR -tWM- -D_NO_VCL -D_RTLDLL -O2 -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; $(CXXFLAGS) -obcb5\bcb5re300l\wide_posix_api.obj ../src/wide_posix_api.cpp
|

bcb5\bcb5re300l :
	-mkdir bcb5\bcb5re300l

bcb5re300l_clean :
	del bcb5\bcb5re300l\*.obj
	del bcb5\bcb5re300l\*.il?
	del bcb5\bcb5re300l\*.csm
	del bcb5\bcb5re300l\*.tds
	del bcb5\*.tds

bcb5\bcb5re300l.lib : bcb5\bcb5re300l\c_regex_traits.obj bcb5\bcb5re300l\c_regex_traits_common.obj bcb5\bcb5re300l\cpp_regex_traits.obj bcb5\bcb5re300l\cregex.obj bcb5\bcb5re300l\fileiter.obj bcb5\bcb5re300l\posix_api.obj bcb5\bcb5re300l\regex.obj bcb5\bcb5re300l\regex_debug.obj bcb5\bcb5re300l\regex_synch.obj bcb5\bcb5re300l\w32_regex_traits.obj bcb5\bcb5re300l\wide_posix_api.obj
	bcc32 @&&|
-tWD -tWR -tWM- -D_NO_VCL -D_RTLDLL -O2 -w-inl -w-aus -w-rch -w-8012 -w-8057 -w-8037 -DSTRICT; -I$(BCROOT)\include;../../../ -L$(BCROOT)\lib;$(BCROOT)\lib\release; -ebcb5\bcb5re300l.dll $(XLFLAGS)  bcb5\bcb5re300l\c_regex_traits.obj bcb5\bcb5re300l\c_regex_traits_common.obj bcb5\bcb5re300l\cpp_regex_traits.obj bcb5\bcb5re300l\cregex.obj bcb5\bcb5re300l\fileiter.obj bcb5\bcb5re300l\posix_api.obj bcb5\bcb5re300l\regex.obj bcb5\bcb5re300l\regex_debug.obj bcb5\bcb5re300l\regex_synch.obj bcb5\bcb5re300l\w32_regex_traits.obj bcb5\bcb5re300l\wide_posix_api.obj $(LIBS)
|
	implib -c bcb5\bcb5re300l.lib bcb5\bcb5re300l.dll

