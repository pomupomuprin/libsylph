#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=

# Macros
PLATFORM=GNU-Linux-x86

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=build/Release/${PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/test/ThisApp.o \
	${OBJECTDIR}/src/Sylph/Core/String.o \
	${OBJECTDIR}/test/Arguments.o \
	${OBJECTDIR}/test/HelloWorld.o \
	${OBJECTDIR}/src/csylph/csylph.o \
	${OBJECTDIR}/src/Sylph.o \
	${OBJECTDIR}/src/Sylph/Core/Util.o \
	${OBJECTDIR}/src/Sylph/Core/Application.o \
	${OBJECTDIR}/src/Sylph/Core/Object.o \
	${OBJECTDIR}/src/Sylph/Core/Vector.o \
	${OBJECTDIR}/src/Sylph/Core/UncaughtExceptionHandler.o \
	${OBJECTDIR}/src/Sylph/Core/Array.o \
	${OBJECTDIR}/src/Sylph/OS/LinuxBundleAppSelf.o \
	${OBJECTDIR}/src/Sylph/Core/HashMap.o

# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=-std=c++0x
CXXFLAGS=-std=c++0x

# Fortran Compiler Flags
FFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=-Llib -lboost -lcord -lgc -lpthread -lbinreloc

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	${MAKE}  -f nbproject/Makefile-Release.mk dist/Release/${PLATFORM}/libsylph.so

dist/Release/${PLATFORM}/libsylph.so: ${OBJECTFILES}
	${MKDIR} -p dist/Release/${PLATFORM}
	${LINK.cc} -dynamiclib -install_name -o dist/Release/${PLATFORM}/libsylph.so -fPIC ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/test/ThisApp.o: test/ThisApp.cpp 
	${MKDIR} -p ${OBJECTDIR}/test
	${RM} $@.d
	$(COMPILE.cc) -O2 -Isrc -Ideps/binreloc -Ideps/boost -Ideps/gc/include -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/test/ThisApp.o test/ThisApp.cpp

${OBJECTDIR}/src/Sylph/Core/String.o: src/Sylph/Core/String.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/Sylph/Core
	${RM} $@.d
	$(COMPILE.cc) -O2 -Isrc -Ideps/binreloc -Ideps/boost -Ideps/gc/include -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/Sylph/Core/String.o src/Sylph/Core/String.cpp

${OBJECTDIR}/test/Arguments.o: test/Arguments.cpp 
	${MKDIR} -p ${OBJECTDIR}/test
	${RM} $@.d
	$(COMPILE.cc) -O2 -Isrc -Ideps/binreloc -Ideps/boost -Ideps/gc/include -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/test/Arguments.o test/Arguments.cpp

${OBJECTDIR}/test/HelloWorld.o: test/HelloWorld.cpp 
	${MKDIR} -p ${OBJECTDIR}/test
	${RM} $@.d
	$(COMPILE.cc) -O2 -Isrc -Ideps/binreloc -Ideps/boost -Ideps/gc/include -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/test/HelloWorld.o test/HelloWorld.cpp

${OBJECTDIR}/src/csylph/csylph.o: src/csylph/csylph.c 
	${MKDIR} -p ${OBJECTDIR}/src/csylph
	${RM} $@.d
	$(COMPILE.c) -O2 -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/csylph/csylph.o src/csylph/csylph.c

${OBJECTDIR}/src/Sylph.o: src/Sylph.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -Isrc -Ideps/binreloc -Ideps/boost -Ideps/gc/include -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/Sylph.o src/Sylph.cpp

${OBJECTDIR}/src/Sylph/Core/Util.o: src/Sylph/Core/Util.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/Sylph/Core
	${RM} $@.d
	$(COMPILE.cc) -O2 -Isrc -Ideps/binreloc -Ideps/boost -Ideps/gc/include -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/Sylph/Core/Util.o src/Sylph/Core/Util.cpp

${OBJECTDIR}/src/Sylph/Core/Application.o: src/Sylph/Core/Application.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/Sylph/Core
	${RM} $@.d
	$(COMPILE.cc) -O2 -Isrc -Ideps/binreloc -Ideps/boost -Ideps/gc/include -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/Sylph/Core/Application.o src/Sylph/Core/Application.cpp

${OBJECTDIR}/src/Sylph/Core/Object.o: src/Sylph/Core/Object.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/Sylph/Core
	${RM} $@.d
	$(COMPILE.cc) -O2 -Isrc -Ideps/binreloc -Ideps/boost -Ideps/gc/include -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/Sylph/Core/Object.o src/Sylph/Core/Object.cpp

${OBJECTDIR}/src/Sylph/Core/Vector.o: src/Sylph/Core/Vector.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/Sylph/Core
	${RM} $@.d
	$(COMPILE.cc) -O2 -Isrc -Ideps/binreloc -Ideps/boost -Ideps/gc/include -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/Sylph/Core/Vector.o src/Sylph/Core/Vector.cpp

${OBJECTDIR}/src/Sylph/Core/UncaughtExceptionHandler.o: src/Sylph/Core/UncaughtExceptionHandler.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/Sylph/Core
	${RM} $@.d
	$(COMPILE.cc) -O2 -Isrc -Ideps/binreloc -Ideps/boost -Ideps/gc/include -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/Sylph/Core/UncaughtExceptionHandler.o src/Sylph/Core/UncaughtExceptionHandler.cpp

${OBJECTDIR}/src/Sylph/Core/Array.o: src/Sylph/Core/Array.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/Sylph/Core
	${RM} $@.d
	$(COMPILE.cc) -O2 -Isrc -Ideps/binreloc -Ideps/boost -Ideps/gc/include -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/Sylph/Core/Array.o src/Sylph/Core/Array.cpp

${OBJECTDIR}/src/Sylph/OS/LinuxBundleAppSelf.o: src/Sylph/OS/LinuxBundleAppSelf.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/Sylph/OS
	${RM} $@.d
	$(COMPILE.cc) -O2 -Isrc -Ideps/binreloc -Ideps/boost -Ideps/gc/include -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/Sylph/OS/LinuxBundleAppSelf.o src/Sylph/OS/LinuxBundleAppSelf.cpp

${OBJECTDIR}/src/Sylph/Core/HashMap.o: src/Sylph/Core/HashMap.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/Sylph/Core
	${RM} $@.d
	$(COMPILE.cc) -O2 -Isrc -Ideps/binreloc -Ideps/boost -Ideps/gc/include -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/Sylph/Core/HashMap.o src/Sylph/Core/HashMap.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf:
	${RM} -r build/Release
	${RM} dist/Release/${PLATFORM}/libsylph.so

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
