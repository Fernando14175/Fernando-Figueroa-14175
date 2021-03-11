#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/Lab5.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/Lab5.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=
else
COMPARISON_BUILD=
endif

ifdef SUB_IMAGE_ADDRESS

else
SUB_IMAGE_ADDRESS_COMMAND=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=lab5.s mimacro.s conversor.s RETARDOS.s display.s

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/lab5.o ${OBJECTDIR}/mimacro.o ${OBJECTDIR}/conversor.o ${OBJECTDIR}/RETARDOS.o ${OBJECTDIR}/display.o
POSSIBLE_DEPFILES=${OBJECTDIR}/lab5.o.d ${OBJECTDIR}/mimacro.o.d ${OBJECTDIR}/conversor.o.d ${OBJECTDIR}/RETARDOS.o.d ${OBJECTDIR}/display.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/lab5.o ${OBJECTDIR}/mimacro.o ${OBJECTDIR}/conversor.o ${OBJECTDIR}/RETARDOS.o ${OBJECTDIR}/display.o

# Source Files
SOURCEFILES=lab5.s mimacro.s conversor.s RETARDOS.s display.s



CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/Lab5.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=PIC16F877A
# ------------------------------------------------------------------------------------
# Rules for buildStep: pic-as-assembler
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/lab5.o: lab5.s  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/lab5.o 
	${MP_AS} -mcpu=PIC16F877A -c \
	-o ${OBJECTDIR}/lab5.o \
	lab5.s \
	 -msummary=+mem,-psect,-class,-hex,-file,-sha1,-sha256,-xml,-xmlfull -fmax-errors=20 -mwarn=0 -xassembler-with-cpp
	
${OBJECTDIR}/mimacro.o: mimacro.s  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/mimacro.o 
	${MP_AS} -mcpu=PIC16F877A -c \
	-o ${OBJECTDIR}/mimacro.o \
	mimacro.s \
	 -msummary=+mem,-psect,-class,-hex,-file,-sha1,-sha256,-xml,-xmlfull -fmax-errors=20 -mwarn=0 -xassembler-with-cpp
	
${OBJECTDIR}/conversor.o: conversor.s  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/conversor.o 
	${MP_AS} -mcpu=PIC16F877A -c \
	-o ${OBJECTDIR}/conversor.o \
	conversor.s \
	 -msummary=+mem,-psect,-class,-hex,-file,-sha1,-sha256,-xml,-xmlfull -fmax-errors=20 -mwarn=0 -xassembler-with-cpp
	
${OBJECTDIR}/RETARDOS.o: RETARDOS.s  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/RETARDOS.o 
	${MP_AS} -mcpu=PIC16F877A -c \
	-o ${OBJECTDIR}/RETARDOS.o \
	RETARDOS.s \
	 -msummary=+mem,-psect,-class,-hex,-file,-sha1,-sha256,-xml,-xmlfull -fmax-errors=20 -mwarn=0 -xassembler-with-cpp
	
${OBJECTDIR}/display.o: display.s  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/display.o 
	${MP_AS} -mcpu=PIC16F877A -c \
	-o ${OBJECTDIR}/display.o \
	display.s \
	 -msummary=+mem,-psect,-class,-hex,-file,-sha1,-sha256,-xml,-xmlfull -fmax-errors=20 -mwarn=0 -xassembler-with-cpp
	
else
${OBJECTDIR}/lab5.o: lab5.s  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/lab5.o 
	${MP_AS} -mcpu=PIC16F877A -c \
	-o ${OBJECTDIR}/lab5.o \
	lab5.s \
	 -msummary=+mem,-psect,-class,-hex,-file,-sha1,-sha256,-xml,-xmlfull -fmax-errors=20 -mwarn=0 -xassembler-with-cpp
	
${OBJECTDIR}/mimacro.o: mimacro.s  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/mimacro.o 
	${MP_AS} -mcpu=PIC16F877A -c \
	-o ${OBJECTDIR}/mimacro.o \
	mimacro.s \
	 -msummary=+mem,-psect,-class,-hex,-file,-sha1,-sha256,-xml,-xmlfull -fmax-errors=20 -mwarn=0 -xassembler-with-cpp
	
${OBJECTDIR}/conversor.o: conversor.s  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/conversor.o 
	${MP_AS} -mcpu=PIC16F877A -c \
	-o ${OBJECTDIR}/conversor.o \
	conversor.s \
	 -msummary=+mem,-psect,-class,-hex,-file,-sha1,-sha256,-xml,-xmlfull -fmax-errors=20 -mwarn=0 -xassembler-with-cpp
	
${OBJECTDIR}/RETARDOS.o: RETARDOS.s  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/RETARDOS.o 
	${MP_AS} -mcpu=PIC16F877A -c \
	-o ${OBJECTDIR}/RETARDOS.o \
	RETARDOS.s \
	 -msummary=+mem,-psect,-class,-hex,-file,-sha1,-sha256,-xml,-xmlfull -fmax-errors=20 -mwarn=0 -xassembler-with-cpp
	
${OBJECTDIR}/display.o: display.s  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/display.o 
	${MP_AS} -mcpu=PIC16F877A -c \
	-o ${OBJECTDIR}/display.o \
	display.s \
	 -msummary=+mem,-psect,-class,-hex,-file,-sha1,-sha256,-xml,-xmlfull -fmax-errors=20 -mwarn=0 -xassembler-with-cpp
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: pic-as-linker
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/Lab5.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_LD} -mcpu=PIC16F877A ${OBJECTFILES_QUOTED_IF_SPACED} \
	-o dist/${CND_CONF}/${IMAGE_TYPE}/Lab5.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} \
	 -msummary=+mem,-psect,-class,-hex,-file,-sha1,-sha256,-xml,-xmlfull -mcallgraph=std -mno-download-hex
else
dist/${CND_CONF}/${IMAGE_TYPE}/Lab5.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_LD} -mcpu=PIC16F877A ${OBJECTFILES_QUOTED_IF_SPACED} \
	-o dist/${CND_CONF}/${IMAGE_TYPE}/Lab5.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} \
	 -msummary=+mem,-psect,-class,-hex,-file,-sha1,-sha256,-xml,-xmlfull -mcallgraph=std -mno-download-hex
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/default
	${RM} -r dist/default

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
