#
# very basic VC6 makefile for timer
#
CXX=cl
CXXFLAGS=/Oityb1 /GF /Gy -GX -DSTRICT -I../../../../ -I./ 
LIBS=/link /LIBPATH:..\..\lib\vc6 kernel32.lib user32.lib 
EXE=.exe
OBJ=.obj

LIBDEP= ../../../../boost/re_detail/regex_options.hpp ../../../../boost/re_detail/regex_config.hpp

regex_timer$(EXE) : regex_timer$(OBJ) timer$(OBJ)
	$(CXX) -o timer$(EXE) timer$(OBJ) regex_timer$(OBJ) $(LIBS)

regex_timer$(OBJ) : regex_timer.cpp $(LIBDEP)
	$(CXX) -c $(CXXFLAGS) regex_timer.cpp

timer$(OBJ) : ../../../timer/timer.cpp $(LIBDEP)
	$(CXX) -c $(CXXFLAGS) ../../../timer/timer.cpp











