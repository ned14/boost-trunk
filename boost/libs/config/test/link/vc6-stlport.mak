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


ALL_HEADER=

all : main_dir liblink_test-vc6-stlport-mt-s-1_31_dir ./vc6-stlport/liblink_test-vc6-stlport-mt-s-1_31.lib ./vc6-stlport/liblink_test-vc6-stlport-mt-s-1_31.exe liblink_test-vc6-stlport-mt-sgd-1_31_dir ./vc6-stlport/liblink_test-vc6-stlport-mt-sgd-1_31.lib ./vc6-stlport/liblink_test-vc6-stlport-mt-sgd-1_31.exe link_test-vc6-stlport-mt-gd-1_31_dir ./vc6-stlport/link_test-vc6-stlport-mt-gd-1_31.lib ./vc6-stlport/link_test-vc6-stlport-mt-gd-1_31.exe link_test-vc6-stlport-mt-1_31_dir ./vc6-stlport/link_test-vc6-stlport-mt-1_31.lib ./vc6-stlport/link_test-vc6-stlport-mt-1_31.exe liblink_test-vc6-stlport-mt-1_31_dir ./vc6-stlport/liblink_test-vc6-stlport-mt-1_31.lib ./vc6-stlport/liblink_test-vc6-stlport-mt-1_31.exe liblink_test-vc6-stlport-mt-gd-1_31_dir ./vc6-stlport/liblink_test-vc6-stlport-mt-gd-1_31.lib ./vc6-stlport/liblink_test-vc6-stlport-mt-gd-1_31.exe link_test-vc6-stlport-mt-pgd-1_31_dir ./vc6-stlport/link_test-vc6-stlport-mt-pgd-1_31.lib ./vc6-stlport/link_test-vc6-stlport-mt-pgd-1_31.exe liblink_test-vc6-stlport-mt-spgd-1_31_dir ./vc6-stlport/liblink_test-vc6-stlport-mt-spgd-1_31.lib ./vc6-stlport/liblink_test-vc6-stlport-mt-spgd-1_31.exe liblink_test-vc6-stlport-mt-pgd-1_31_dir ./vc6-stlport/liblink_test-vc6-stlport-mt-pgd-1_31.lib ./vc6-stlport/liblink_test-vc6-stlport-mt-pgd-1_31.exe

clean :  liblink_test-vc6-stlport-mt-s-1_31_clean liblink_test-vc6-stlport-mt-sgd-1_31_clean link_test-vc6-stlport-mt-gd-1_31_clean link_test-vc6-stlport-mt-1_31_clean liblink_test-vc6-stlport-mt-1_31_clean liblink_test-vc6-stlport-mt-gd-1_31_clean link_test-vc6-stlport-mt-pgd-1_31_clean liblink_test-vc6-stlport-mt-spgd-1_31_clean liblink_test-vc6-stlport-mt-pgd-1_31_clean

install : stlport_check all
	copy vc6-stlport\liblink_test-vc6-stlport-mt-s-1_31.lib "$(MSVCDIR)\lib"
	copy vc6-stlport\liblink_test-vc6-stlport-mt-sgd-1_31.lib "$(MSVCDIR)\lib"
	copy vc6-stlport\link_test-vc6-stlport-mt-gd-1_31.lib "$(MSVCDIR)\lib"
	copy vc6-stlport\link_test-vc6-stlport-mt-gd-1_31.dll "$(MSVCDIR)\bin"
	copy vc6-stlport\link_test-vc6-stlport-mt-1_31.lib "$(MSVCDIR)\lib"
	copy vc6-stlport\link_test-vc6-stlport-mt-1_31.dll "$(MSVCDIR)\bin"
	copy vc6-stlport\liblink_test-vc6-stlport-mt-1_31.lib "$(MSVCDIR)\lib"
	copy vc6-stlport\liblink_test-vc6-stlport-mt-gd-1_31.lib "$(MSVCDIR)\lib"
	copy vc6-stlport\link_test-vc6-stlport-mt-pgd-1_31.lib "$(MSVCDIR)\lib"
	copy vc6-stlport\link_test-vc6-stlport-mt-pgd-1_31.dll "$(MSVCDIR)\bin"
	copy vc6-stlport\link_test-vc6-stlport-mt-pgd-1_31.pdb "$(MSVCDIR)\lib"
	copy vc6-stlport\liblink_test-vc6-stlport-mt-spgd-1_31.lib "$(MSVCDIR)\lib"
	copy vc6-stlport\liblink_test-vc6-stlport-mt-spgd-1_31.pdb "$(MSVCDIR)\lib"
	copy vc6-stlport\liblink_test-vc6-stlport-mt-pgd-1_31.lib "$(MSVCDIR)\lib"
	copy vc6-stlport\liblink_test-vc6-stlport-mt-pgd-1_31.pdb "$(MSVCDIR)\lib"

main_dir :
	@if not exist "vc6-stlport\$(NULL)" mkdir vc6-stlport

stlport_check : $(STLPORT_PATH)\stlport\string
	echo


########################################################
#
# section for liblink_test-vc6-stlport-mt-s-1_31.lib
#
########################################################
vc6-stlport/liblink_test-vc6-stlport-mt-s-1_31/link_test.obj: link_test.cpp $(ALL_HEADER)
	cl /c $(INCLUDES) /nologo /MT /W3 /GX /O2 /GB /GF /Gy /I$(STLPORT_PATH)\stlport /I..\..\..\..\ /D_MT /DWIN32 /DNDEBUG /D_MBCS /D_LIB  $(CXXFLAGS) -Y- -Fo./vc6-stlport/liblink_test-vc6-stlport-mt-s-1_31/ -Fdvc6-stlport/liblink_test-vc6-stlport-mt-s-1_31.pdb link_test.cpp

liblink_test-vc6-stlport-mt-s-1_31_dir :
	@if not exist "vc6-stlport\liblink_test-vc6-stlport-mt-s-1_31\$(NULL)" mkdir vc6-stlport\liblink_test-vc6-stlport-mt-s-1_31

liblink_test-vc6-stlport-mt-s-1_31_clean :
	del vc6-stlport\liblink_test-vc6-stlport-mt-s-1_31\*.obj
	del vc6-stlport\liblink_test-vc6-stlport-mt-s-1_31\*.idb
	del vc6-stlport\liblink_test-vc6-stlport-mt-s-1_31\*.exp
	del vc6-stlport\liblink_test-vc6-stlport-mt-s-1_31\*.pch

./vc6-stlport/liblink_test-vc6-stlport-mt-s-1_31.lib : vc6-stlport/liblink_test-vc6-stlport-mt-s-1_31/link_test.obj
	link -lib /nologo /out:vc6-stlport/liblink_test-vc6-stlport-mt-s-1_31.lib $(XSFLAGS)  vc6-stlport/liblink_test-vc6-stlport-mt-s-1_31/link_test.obj

./vc6-stlport/liblink_test-vc6-stlport-mt-s-1_31.exe : main.cpp ./vc6-stlport/liblink_test-vc6-stlport-mt-s-1_31.lib
	cl $(INCLUDES) /nologo /MT /W3 /GX /O2 /GB /GF /Gy /I$(STLPORT_PATH)\stlport /I..\..\..\..\ /D_MT /DWIN32 /DNDEBUG /D_MBCS /D_LIB  /DBOOST_LIB_DIAGNOSTIC=1 $(CXXFLAGS) -o ./vc6-stlport/liblink_test-vc6-stlport-mt-s-1_31.exe main.cpp /link /LIBPATH:./vc6-stlport
   vc6-stlport\liblink_test-vc6-stlport-mt-s-1_31.exe

########################################################
#
# section for liblink_test-vc6-stlport-mt-sgd-1_31.lib
#
########################################################
vc6-stlport/liblink_test-vc6-stlport-mt-sgd-1_31/link_test.obj: link_test.cpp $(ALL_HEADER)
	cl /c $(INCLUDES) /nologo /MTd /W3 /Gm /GX /Zi /Od /I$(STLPORT_PATH)\stlport /I..\..\..\..\ /DWIN32 /D_MT /D_DEBUG /D_MBCS /D_LIB /GX  $(CXXFLAGS) -Y- -Fo./vc6-stlport/liblink_test-vc6-stlport-mt-sgd-1_31/ -Fdvc6-stlport/liblink_test-vc6-stlport-mt-sgd-1_31.pdb link_test.cpp

liblink_test-vc6-stlport-mt-sgd-1_31_dir :
	@if not exist "vc6-stlport\liblink_test-vc6-stlport-mt-sgd-1_31\$(NULL)" mkdir vc6-stlport\liblink_test-vc6-stlport-mt-sgd-1_31

liblink_test-vc6-stlport-mt-sgd-1_31_clean :
	del vc6-stlport\liblink_test-vc6-stlport-mt-sgd-1_31\*.obj
	del vc6-stlport\liblink_test-vc6-stlport-mt-sgd-1_31\*.idb
	del vc6-stlport\liblink_test-vc6-stlport-mt-sgd-1_31\*.exp
	del vc6-stlport\liblink_test-vc6-stlport-mt-sgd-1_31\*.pch

./vc6-stlport/liblink_test-vc6-stlport-mt-sgd-1_31.lib : vc6-stlport/liblink_test-vc6-stlport-mt-sgd-1_31/link_test.obj
	link -lib /nologo /out:vc6-stlport/liblink_test-vc6-stlport-mt-sgd-1_31.lib $(XSFLAGS)  vc6-stlport/liblink_test-vc6-stlport-mt-sgd-1_31/link_test.obj

./vc6-stlport/liblink_test-vc6-stlport-mt-sgd-1_31.exe : main.cpp ./vc6-stlport/liblink_test-vc6-stlport-mt-sgd-1_31.lib
	cl $(INCLUDES) /nologo /MTd /W3 /Gm /GX /Zi /Od /I$(STLPORT_PATH)\stlport /I..\..\..\..\ /DWIN32 /D_MT /D_DEBUG /D_MBCS /D_LIB /GX  /DBOOST_LIB_DIAGNOSTIC=1 $(CXXFLAGS) -o ./vc6-stlport/liblink_test-vc6-stlport-mt-sgd-1_31.exe main.cpp /link /LIBPATH:./vc6-stlport
   vc6-stlport\liblink_test-vc6-stlport-mt-sgd-1_31.exe

########################################################
#
# section for link_test-vc6-stlport-mt-gd-1_31.lib
#
########################################################
vc6-stlport/link_test-vc6-stlport-mt-gd-1_31/link_test.obj: link_test.cpp $(ALL_HEADER)
	cl /c $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I$(STLPORT_PATH)\stlport /I..\..\..\..\ /DBOOST_DYN_LINK /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /GX  $(CXXFLAGS) -Y- -Fo./vc6-stlport/link_test-vc6-stlport-mt-gd-1_31/ -Fdvc6-stlport/link_test-vc6-stlport-mt-gd-1_31.pdb link_test.cpp

link_test-vc6-stlport-mt-gd-1_31_dir :
	@if not exist "vc6-stlport\link_test-vc6-stlport-mt-gd-1_31\$(NULL)" mkdir vc6-stlport\link_test-vc6-stlport-mt-gd-1_31

link_test-vc6-stlport-mt-gd-1_31_clean :
	del vc6-stlport\link_test-vc6-stlport-mt-gd-1_31\*.obj
	del vc6-stlport\link_test-vc6-stlport-mt-gd-1_31\*.idb
	del vc6-stlport\link_test-vc6-stlport-mt-gd-1_31\*.exp
	del vc6-stlport\link_test-vc6-stlport-mt-gd-1_31\*.pch

./vc6-stlport/link_test-vc6-stlport-mt-gd-1_31.lib : vc6-stlport/link_test-vc6-stlport-mt-gd-1_31/link_test.obj
	link kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:yes /pdb:"vc6-stlport/link_test-vc6-stlport-mt-gd-1_31.pdb" /debug /machine:I386 /out:"vc6-stlport/link_test-vc6-stlport-mt-gd-1_31.dll" /implib:"vc6-stlport/link_test-vc6-stlport-mt-gd-1_31.lib" /LIBPATH:$(STLPORT_PATH)\lib $(XLFLAGS)  vc6-stlport/link_test-vc6-stlport-mt-gd-1_31/link_test.obj

./vc6-stlport/link_test-vc6-stlport-mt-gd-1_31.exe : main.cpp ./vc6-stlport/link_test-vc6-stlport-mt-gd-1_31.lib
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I$(STLPORT_PATH)\stlport /I..\..\..\..\ /DBOOST_DYN_LINK /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /GX  /DBOOST_LIB_DIAGNOSTIC=1 $(CXXFLAGS) -o ./vc6-stlport/link_test-vc6-stlport-mt-gd-1_31.exe main.cpp /link /LIBPATH:./vc6-stlport
   vc6-stlport\link_test-vc6-stlport-mt-gd-1_31.exe

########################################################
#
# section for link_test-vc6-stlport-mt-1_31.lib
#
########################################################
vc6-stlport/link_test-vc6-stlport-mt-1_31/link_test.obj: link_test.cpp $(ALL_HEADER)
	cl /c $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /I$(STLPORT_PATH)\stlport /Gy /I..\..\..\..\ /DBOOST_DYN_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL  $(CXXFLAGS) -Y- -Fo./vc6-stlport/link_test-vc6-stlport-mt-1_31/ -Fdvc6-stlport/link_test-vc6-stlport-mt-1_31.pdb link_test.cpp

link_test-vc6-stlport-mt-1_31_dir :
	@if not exist "vc6-stlport\link_test-vc6-stlport-mt-1_31\$(NULL)" mkdir vc6-stlport\link_test-vc6-stlport-mt-1_31

link_test-vc6-stlport-mt-1_31_clean :
	del vc6-stlport\link_test-vc6-stlport-mt-1_31\*.obj
	del vc6-stlport\link_test-vc6-stlport-mt-1_31\*.idb
	del vc6-stlport\link_test-vc6-stlport-mt-1_31\*.exp
	del vc6-stlport\link_test-vc6-stlport-mt-1_31\*.pch

./vc6-stlport/link_test-vc6-stlport-mt-1_31.lib : vc6-stlport/link_test-vc6-stlport-mt-1_31/link_test.obj
	link kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:yes /pdb:"vc6-stlport/link_test-vc6-stlport-mt-1_31.pdb" /debug /machine:I386 /out:"vc6-stlport/link_test-vc6-stlport-mt-1_31.dll" /implib:"vc6-stlport/link_test-vc6-stlport-mt-1_31.lib" /LIBPATH:$(STLPORT_PATH)\lib $(XLFLAGS)  vc6-stlport/link_test-vc6-stlport-mt-1_31/link_test.obj

./vc6-stlport/link_test-vc6-stlport-mt-1_31.exe : main.cpp ./vc6-stlport/link_test-vc6-stlport-mt-1_31.lib
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /I$(STLPORT_PATH)\stlport /Gy /I..\..\..\..\ /DBOOST_DYN_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL  /DBOOST_LIB_DIAGNOSTIC=1 $(CXXFLAGS) -o ./vc6-stlport/link_test-vc6-stlport-mt-1_31.exe main.cpp /link /LIBPATH:./vc6-stlport
   vc6-stlport\link_test-vc6-stlport-mt-1_31.exe

########################################################
#
# section for liblink_test-vc6-stlport-mt-1_31.lib
#
########################################################
vc6-stlport/liblink_test-vc6-stlport-mt-1_31/link_test.obj: link_test.cpp $(ALL_HEADER)
	cl /c $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /Gy /I$(STLPORT_PATH)\stlport /I..\..\..\..\ /DBOOST_REGEX_STATIC_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL  $(CXXFLAGS) -Y- -Fo./vc6-stlport/liblink_test-vc6-stlport-mt-1_31/ -Fdvc6-stlport/liblink_test-vc6-stlport-mt-1_31.pdb link_test.cpp

liblink_test-vc6-stlport-mt-1_31_dir :
	@if not exist "vc6-stlport\liblink_test-vc6-stlport-mt-1_31\$(NULL)" mkdir vc6-stlport\liblink_test-vc6-stlport-mt-1_31

liblink_test-vc6-stlport-mt-1_31_clean :
	del vc6-stlport\liblink_test-vc6-stlport-mt-1_31\*.obj
	del vc6-stlport\liblink_test-vc6-stlport-mt-1_31\*.idb
	del vc6-stlport\liblink_test-vc6-stlport-mt-1_31\*.exp
	del vc6-stlport\liblink_test-vc6-stlport-mt-1_31\*.pch

./vc6-stlport/liblink_test-vc6-stlport-mt-1_31.lib : vc6-stlport/liblink_test-vc6-stlport-mt-1_31/link_test.obj
	link -lib /nologo /out:vc6-stlport/liblink_test-vc6-stlport-mt-1_31.lib $(XSFLAGS)  vc6-stlport/liblink_test-vc6-stlport-mt-1_31/link_test.obj

./vc6-stlport/liblink_test-vc6-stlport-mt-1_31.exe : main.cpp ./vc6-stlport/liblink_test-vc6-stlport-mt-1_31.lib
	cl $(INCLUDES) /nologo /MD /W3 /GX /O2 /GB /GF /Gy /I$(STLPORT_PATH)\stlport /I..\..\..\..\ /DBOOST_REGEX_STATIC_LINK /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL  /DBOOST_LIB_DIAGNOSTIC=1 $(CXXFLAGS) -o ./vc6-stlport/liblink_test-vc6-stlport-mt-1_31.exe main.cpp /link /LIBPATH:./vc6-stlport
   vc6-stlport\liblink_test-vc6-stlport-mt-1_31.exe

########################################################
#
# section for liblink_test-vc6-stlport-mt-gd-1_31.lib
#
########################################################
vc6-stlport/liblink_test-vc6-stlport-mt-gd-1_31/link_test.obj: link_test.cpp $(ALL_HEADER)
	cl /c $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I$(STLPORT_PATH)\stlport /I..\..\..\..\ /DBOOST_REGEX_STATIC_LINK /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /GX  $(CXXFLAGS) -Y- -Fo./vc6-stlport/liblink_test-vc6-stlport-mt-gd-1_31/ -Fdvc6-stlport/liblink_test-vc6-stlport-mt-gd-1_31.pdb link_test.cpp

liblink_test-vc6-stlport-mt-gd-1_31_dir :
	@if not exist "vc6-stlport\liblink_test-vc6-stlport-mt-gd-1_31\$(NULL)" mkdir vc6-stlport\liblink_test-vc6-stlport-mt-gd-1_31

liblink_test-vc6-stlport-mt-gd-1_31_clean :
	del vc6-stlport\liblink_test-vc6-stlport-mt-gd-1_31\*.obj
	del vc6-stlport\liblink_test-vc6-stlport-mt-gd-1_31\*.idb
	del vc6-stlport\liblink_test-vc6-stlport-mt-gd-1_31\*.exp
	del vc6-stlport\liblink_test-vc6-stlport-mt-gd-1_31\*.pch

./vc6-stlport/liblink_test-vc6-stlport-mt-gd-1_31.lib : vc6-stlport/liblink_test-vc6-stlport-mt-gd-1_31/link_test.obj
	link -lib /nologo /out:vc6-stlport/liblink_test-vc6-stlport-mt-gd-1_31.lib $(XSFLAGS)  vc6-stlport/liblink_test-vc6-stlport-mt-gd-1_31/link_test.obj

./vc6-stlport/liblink_test-vc6-stlport-mt-gd-1_31.exe : main.cpp ./vc6-stlport/liblink_test-vc6-stlport-mt-gd-1_31.lib
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I$(STLPORT_PATH)\stlport /I..\..\..\..\ /DBOOST_REGEX_STATIC_LINK /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /GX  /DBOOST_LIB_DIAGNOSTIC=1 $(CXXFLAGS) -o ./vc6-stlport/liblink_test-vc6-stlport-mt-gd-1_31.exe main.cpp /link /LIBPATH:./vc6-stlport
   vc6-stlport\liblink_test-vc6-stlport-mt-gd-1_31.exe

########################################################
#
# section for link_test-vc6-stlport-mt-pgd-1_31.lib
#
########################################################
vc6-stlport/link_test-vc6-stlport-mt-pgd-1_31/link_test.obj: link_test.cpp $(ALL_HEADER)
	cl /c $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I$(STLPORT_PATH)\stlport /I..\..\..\..\ /DBOOST_DYN_LINK /D__STL_DEBUG /D_STLP_DEBUG /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /GX  $(CXXFLAGS) -Y- -Fo./vc6-stlport/link_test-vc6-stlport-mt-pgd-1_31/ -Fdvc6-stlport/link_test-vc6-stlport-mt-pgd-1_31.pdb link_test.cpp

link_test-vc6-stlport-mt-pgd-1_31_dir :
	@if not exist "vc6-stlport\link_test-vc6-stlport-mt-pgd-1_31\$(NULL)" mkdir vc6-stlport\link_test-vc6-stlport-mt-pgd-1_31

link_test-vc6-stlport-mt-pgd-1_31_clean :
	del vc6-stlport\link_test-vc6-stlport-mt-pgd-1_31\*.obj
	del vc6-stlport\link_test-vc6-stlport-mt-pgd-1_31\*.idb
	del vc6-stlport\link_test-vc6-stlport-mt-pgd-1_31\*.exp
	del vc6-stlport\link_test-vc6-stlport-mt-pgd-1_31\*.pch

./vc6-stlport/link_test-vc6-stlport-mt-pgd-1_31.lib : vc6-stlport/link_test-vc6-stlport-mt-pgd-1_31/link_test.obj
	link kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:yes /pdb:"vc6-stlport/link_test-vc6-stlport-mt-pgd-1_31.pdb" /debug /machine:I386 /out:"vc6-stlport/link_test-vc6-stlport-mt-pgd-1_31.dll" /implib:"vc6-stlport/link_test-vc6-stlport-mt-pgd-1_31.lib" /LIBPATH:$(STLPORT_PATH)\lib $(XLFLAGS)  vc6-stlport/link_test-vc6-stlport-mt-pgd-1_31/link_test.obj

./vc6-stlport/link_test-vc6-stlport-mt-pgd-1_31.exe : main.cpp ./vc6-stlport/link_test-vc6-stlport-mt-pgd-1_31.lib
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I$(STLPORT_PATH)\stlport /I..\..\..\..\ /DBOOST_DYN_LINK /D__STL_DEBUG /D_STLP_DEBUG /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /GX  /DBOOST_LIB_DIAGNOSTIC=1 $(CXXFLAGS) -o ./vc6-stlport/link_test-vc6-stlport-mt-pgd-1_31.exe main.cpp /link /LIBPATH:./vc6-stlport
   vc6-stlport\link_test-vc6-stlport-mt-pgd-1_31.exe

########################################################
#
# section for liblink_test-vc6-stlport-mt-spgd-1_31.lib
#
########################################################
vc6-stlport/liblink_test-vc6-stlport-mt-spgd-1_31/link_test.obj: link_test.cpp $(ALL_HEADER)
	cl /c $(INCLUDES) /nologo /MTd /W3 /Gm /GX /Zi /Od /I$(STLPORT_PATH)\stlport /I..\..\..\..\ /D__STL_DEBUG /D_STLP_DEBUG /DWIN32 /D_MT /D_DEBUG /D_MBCS /D_LIB /GX  $(CXXFLAGS) -Y- -Fo./vc6-stlport/liblink_test-vc6-stlport-mt-spgd-1_31/ -Fdvc6-stlport/liblink_test-vc6-stlport-mt-spgd-1_31.pdb link_test.cpp

liblink_test-vc6-stlport-mt-spgd-1_31_dir :
	@if not exist "vc6-stlport\liblink_test-vc6-stlport-mt-spgd-1_31\$(NULL)" mkdir vc6-stlport\liblink_test-vc6-stlport-mt-spgd-1_31

liblink_test-vc6-stlport-mt-spgd-1_31_clean :
	del vc6-stlport\liblink_test-vc6-stlport-mt-spgd-1_31\*.obj
	del vc6-stlport\liblink_test-vc6-stlport-mt-spgd-1_31\*.idb
	del vc6-stlport\liblink_test-vc6-stlport-mt-spgd-1_31\*.exp
	del vc6-stlport\liblink_test-vc6-stlport-mt-spgd-1_31\*.pch

./vc6-stlport/liblink_test-vc6-stlport-mt-spgd-1_31.lib : vc6-stlport/liblink_test-vc6-stlport-mt-spgd-1_31/link_test.obj
	link -lib /nologo /out:vc6-stlport/liblink_test-vc6-stlport-mt-spgd-1_31.lib $(XSFLAGS)  vc6-stlport/liblink_test-vc6-stlport-mt-spgd-1_31/link_test.obj

./vc6-stlport/liblink_test-vc6-stlport-mt-spgd-1_31.exe : main.cpp ./vc6-stlport/liblink_test-vc6-stlport-mt-spgd-1_31.lib
	cl $(INCLUDES) /nologo /MTd /W3 /Gm /GX /Zi /Od /I$(STLPORT_PATH)\stlport /I..\..\..\..\ /D__STL_DEBUG /D_STLP_DEBUG /DWIN32 /D_MT /D_DEBUG /D_MBCS /D_LIB /GX  /DBOOST_LIB_DIAGNOSTIC=1 $(CXXFLAGS) -o ./vc6-stlport/liblink_test-vc6-stlport-mt-spgd-1_31.exe main.cpp /link /LIBPATH:./vc6-stlport
   vc6-stlport\liblink_test-vc6-stlport-mt-spgd-1_31.exe

########################################################
#
# section for liblink_test-vc6-stlport-mt-pgd-1_31.lib
#
########################################################
vc6-stlport/liblink_test-vc6-stlport-mt-pgd-1_31/link_test.obj: link_test.cpp $(ALL_HEADER)
	cl /c $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I$(STLPORT_PATH)\stlport /I..\..\..\..\ /DBOOST_REGEX_STATIC_LINK /D__STL_DEBUG /D_STLP_DEBUG /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /GX  $(CXXFLAGS) -Y- -Fo./vc6-stlport/liblink_test-vc6-stlport-mt-pgd-1_31/ -Fdvc6-stlport/liblink_test-vc6-stlport-mt-pgd-1_31.pdb link_test.cpp

liblink_test-vc6-stlport-mt-pgd-1_31_dir :
	@if not exist "vc6-stlport\liblink_test-vc6-stlport-mt-pgd-1_31\$(NULL)" mkdir vc6-stlport\liblink_test-vc6-stlport-mt-pgd-1_31

liblink_test-vc6-stlport-mt-pgd-1_31_clean :
	del vc6-stlport\liblink_test-vc6-stlport-mt-pgd-1_31\*.obj
	del vc6-stlport\liblink_test-vc6-stlport-mt-pgd-1_31\*.idb
	del vc6-stlport\liblink_test-vc6-stlport-mt-pgd-1_31\*.exp
	del vc6-stlport\liblink_test-vc6-stlport-mt-pgd-1_31\*.pch

./vc6-stlport/liblink_test-vc6-stlport-mt-pgd-1_31.lib : vc6-stlport/liblink_test-vc6-stlport-mt-pgd-1_31/link_test.obj
	link -lib /nologo /out:vc6-stlport/liblink_test-vc6-stlport-mt-pgd-1_31.lib $(XSFLAGS)  vc6-stlport/liblink_test-vc6-stlport-mt-pgd-1_31/link_test.obj

./vc6-stlport/liblink_test-vc6-stlport-mt-pgd-1_31.exe : main.cpp ./vc6-stlport/liblink_test-vc6-stlport-mt-pgd-1_31.lib
	cl $(INCLUDES) /nologo /MDd /W3 /Gm /GX /Zi /Od /I$(STLPORT_PATH)\stlport /I..\..\..\..\ /DBOOST_REGEX_STATIC_LINK /D__STL_DEBUG /D_STLP_DEBUG /D_DEBUG /DWIN32 /D_WINDOWS /D_MBCS /DUSRDLL /GX  /DBOOST_LIB_DIAGNOSTIC=1 $(CXXFLAGS) -o ./vc6-stlport/liblink_test-vc6-stlport-mt-pgd-1_31.exe main.cpp /link /LIBPATH:./vc6-stlport
   vc6-stlport\liblink_test-vc6-stlport-mt-pgd-1_31.exe

