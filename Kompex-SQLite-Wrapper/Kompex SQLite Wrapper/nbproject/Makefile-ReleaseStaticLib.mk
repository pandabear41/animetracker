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
CCC=g++-4.4
CXX=g++-4.4
FC=
AS=as

# Macros
CND_PLATFORM=GNU-Linux-x86
CND_CONF=ReleaseStaticLib
CND_DISTDIR=dist

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=build/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/_ext/_DOTDOT/src/KompexSQLiteStatement.o \
	${OBJECTDIR}/_ext/_DOTDOT/src/KompexSQLiteDatabase.o \
	${OBJECTDIR}/_ext/_DOTDOT/src/sqlite3.o

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
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	${MAKE}  -f nbproject/Makefile-ReleaseStaticLib.mk ../lib/release/KompexSQLiteWrapper_Static.a

../lib/release/KompexSQLiteWrapper_Static.a: ${OBJECTFILES}
	${MKDIR} -p ../lib/release
	${RM} ../lib/release/KompexSQLiteWrapper_Static.a
	${AR} rv ../lib/release/KompexSQLiteWrapper_Static.a ${OBJECTFILES} 
	$(RANLIB) ../lib/release/KompexSQLiteWrapper_Static.a

${OBJECTDIR}/_ext/_DOTDOT/src/KompexSQLiteStatement.o: nbproject/Makefile-${CND_CONF}.mk ../src/KompexSQLiteStatement.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/_DOTDOT/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../inc -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/_DOTDOT/src/KompexSQLiteStatement.o ../src/KompexSQLiteStatement.cpp

${OBJECTDIR}/_ext/_DOTDOT/src/KompexSQLiteDatabase.o: nbproject/Makefile-${CND_CONF}.mk ../src/KompexSQLiteDatabase.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/_DOTDOT/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../inc -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/_DOTDOT/src/KompexSQLiteDatabase.o ../src/KompexSQLiteDatabase.cpp

${OBJECTDIR}/_ext/_DOTDOT/src/sqlite3.o: nbproject/Makefile-${CND_CONF}.mk ../src/sqlite3.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/_DOTDOT/src
	${RM} $@.d
	$(COMPILE.c) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/_DOTDOT/src/sqlite3.o ../src/sqlite3.c

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf:
	${RM} -r build/ReleaseStaticLib
	${RM} ../lib/release/KompexSQLiteWrapper_Static.a

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
