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
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-MacOSX
CND_DLIB_EXT=dylib
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/_ext/2079673924/analyze.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS="/Users/chiajuntai/Dropbox/ISU/COM S 327/HW3/HW Objects 2.01/Mac OS X/util.o" "/Users/chiajuntai/Dropbox/ISU/COM S 327/HW3/HW Objects 2.01/Mac OS X/weatherio.o"  

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/hw3

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/hw3: /Users/chiajuntai/Dropbox/ISU/COM\ S\ 327/HW3/HW\ Objects\ 2.01/Mac\ OS\ X/util.o

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/hw3: /Users/chiajuntai/Dropbox/ISU/COM\ S\ 327/HW3/HW\ Objects\ 2.01/Mac\ OS\ X/weatherio.o

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/hw3: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.c} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/hw3 ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/_ext/2079673924/analyze.o: /Users/chiajuntai/Dropbox/ISU/COM\ S\ 327/HW3/Hw3/analyze.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/2079673924
	${RM} "$@.d"
	$(COMPILE.c) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/2079673924/analyze.o /Users/chiajuntai/Dropbox/ISU/COM\ S\ 327/HW3/Hw3/analyze.c

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/hw3

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
