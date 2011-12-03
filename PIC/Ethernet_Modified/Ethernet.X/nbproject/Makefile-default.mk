#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
include Makefile

# Environment
# Adding MPLAB X bin directory to path
PATH:=/opt/microchip/mplabx/mplab_ide/mplab_ide/modules/../../bin/:$(PATH)
MKDIR=mkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/Ethernet.X.${IMAGE_TYPE}.cof
else
IMAGE_TYPE=production
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/Ethernet.X.${IMAGE_TYPE}.cof
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/1360937237/enc28j60.o ${OBJECTDIR}/_ext/1360937237/helpers.o ${OBJECTDIR}/_ext/1360937237/main.o

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/1360937237/enc28j60.o ${OBJECTDIR}/_ext/1360937237/helpers.o ${OBJECTDIR}/_ext/1360937237/main.o


CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

# Path to java used to run MPLAB X when this makefile was created
MP_JAVA_PATH="/usr/lib/jvm/java-6-openjdk/jre/bin/"
OS_CURRENT="$(shell uname -s)"
############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
MP_CC="/opt/microchip/mplabc18/v3.40/bin/mcc18"
# MP_BC is not defined
MP_AS="/opt/microchip/mplabc18/v3.40/bin/../mpasm/MPASMWIN"
MP_LD="/opt/microchip/mplabc18/v3.40/bin/mplink"
MP_AR="/opt/microchip/mplabc18/v3.40/bin/mplib"
DEP_GEN=${MP_JAVA_PATH}java -jar "/opt/microchip/mplabx/mplab_ide/mplab_ide/modules/../../bin/extractobjectdependencies.jar" 
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps
MP_CC_DIR="/opt/microchip/mplabc18/v3.40/bin"
# MP_BC_DIR is not defined
MP_AS_DIR="/opt/microchip/mplabc18/v3.40/bin/../mpasm"
MP_LD_DIR="/opt/microchip/mplabc18/v3.40/bin"
MP_AR_DIR="/opt/microchip/mplabc18/v3.40/bin"
# MP_BC_DIR is not defined

.build-conf:  ${BUILD_SUBPROJECTS}
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/Ethernet.X.${IMAGE_TYPE}.cof

MP_PROCESSOR_OPTION=18F2620
MP_PROCESSOR_OPTION_LD=18f2620
MP_LINKER_DEBUG_OPTION= -u_DEBUGCODESTART=0xfdc0 -u_DEBUGCODELEN=0x240 -u_DEBUGDATASTART=0xef4 -u_DEBUGDATALEN=0xb
# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/1360937237/helpers.o: ../src/helpers.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/helpers.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PICKIT2=1 -p$(MP_PROCESSOR_OPTION) -k -sco -DMINIPIC10T -I"../src" -I"../../src" -I"../../../src" -I"../src/time/include" -I"../src/net/include" -I"../src/include" -I"../src/mpfs/include" -I"../src/uart/include"  -I ${MP_CC_DIR}/../h  -fo ${OBJECTDIR}/_ext/1360937237/helpers.o   ../src/helpers.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1360937237/helpers.o 
	
${OBJECTDIR}/_ext/1360937237/main.o: ../src/main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/main.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PICKIT2=1 -p$(MP_PROCESSOR_OPTION) -k -sco -DMINIPIC10T -I"../src" -I"../../src" -I"../../../src" -I"../src/time/include" -I"../src/net/include" -I"../src/include" -I"../src/mpfs/include" -I"../src/uart/include"  -I ${MP_CC_DIR}/../h  -fo ${OBJECTDIR}/_ext/1360937237/main.o   ../src/main.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1360937237/main.o 
	
${OBJECTDIR}/_ext/1360937237/enc28j60.o: ../src/enc28j60.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/enc28j60.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PICKIT2=1 -p$(MP_PROCESSOR_OPTION) -k -sco -DMINIPIC10T -I"../src" -I"../../src" -I"../../../src" -I"../src/time/include" -I"../src/net/include" -I"../src/include" -I"../src/mpfs/include" -I"../src/uart/include"  -I ${MP_CC_DIR}/../h  -fo ${OBJECTDIR}/_ext/1360937237/enc28j60.o   ../src/enc28j60.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1360937237/enc28j60.o 
	
else
${OBJECTDIR}/_ext/1360937237/helpers.o: ../src/helpers.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/helpers.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -k -sco -DMINIPIC10T -I"../src" -I"../../src" -I"../../../src" -I"../src/time/include" -I"../src/net/include" -I"../src/include" -I"../src/mpfs/include" -I"../src/uart/include"  -I ${MP_CC_DIR}/../h  -fo ${OBJECTDIR}/_ext/1360937237/helpers.o   ../src/helpers.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1360937237/helpers.o 
	
${OBJECTDIR}/_ext/1360937237/main.o: ../src/main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/main.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -k -sco -DMINIPIC10T -I"../src" -I"../../src" -I"../../../src" -I"../src/time/include" -I"../src/net/include" -I"../src/include" -I"../src/mpfs/include" -I"../src/uart/include"  -I ${MP_CC_DIR}/../h  -fo ${OBJECTDIR}/_ext/1360937237/main.o   ../src/main.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1360937237/main.o 
	
${OBJECTDIR}/_ext/1360937237/enc28j60.o: ../src/enc28j60.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/enc28j60.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -k -sco -DMINIPIC10T -I"../src" -I"../../src" -I"../../../src" -I"../src/time/include" -I"../src/net/include" -I"../src/include" -I"../src/mpfs/include" -I"../src/uart/include"  -I ${MP_CC_DIR}/../h  -fo ${OBJECTDIR}/_ext/1360937237/enc28j60.o   ../src/enc28j60.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1360937237/enc28j60.o 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/Ethernet.X.${IMAGE_TYPE}.cof: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_LD} $(MP_EXTRA_LD_PRE)   -p$(MP_PROCESSOR_OPTION_LD)  -w -x -u_DEBUG -l"../../../../../../../Program Files/Microchip/MCC18/lib"  -z__MPLAB_BUILD=1  -u_CRUNTIME -z__MPLAB_DEBUG=1 -z__MPLAB_DEBUGGER_PICKIT2=1 $(MP_LINKER_DEBUG_OPTION) -l ${MP_CC_DIR}/../lib  -odist/${CND_CONF}/${IMAGE_TYPE}/Ethernet.X.${IMAGE_TYPE}.cof  ${OBJECTFILES_QUOTED_IF_SPACED}   
else
dist/${CND_CONF}/${IMAGE_TYPE}/Ethernet.X.${IMAGE_TYPE}.cof: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_LD} $(MP_EXTRA_LD_PRE)   -p$(MP_PROCESSOR_OPTION_LD)  -w  -l"../../../../../../../Program Files/Microchip/MCC18/lib"  -z__MPLAB_BUILD=1  -u_CRUNTIME -l ${MP_CC_DIR}/../lib  -odist/${CND_CONF}/${IMAGE_TYPE}/Ethernet.X.${IMAGE_TYPE}.cof  ${OBJECTFILES_QUOTED_IF_SPACED}   
endif


# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf:
	${RM} -r build/default
	${RM} -r dist/default

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(wildcard $(addsuffix .d, ${OBJECTFILES}))
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
