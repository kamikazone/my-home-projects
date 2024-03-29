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
MKDIR=mkdir -p
RM=rm -f 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/Ethernet_Modified.${IMAGE_TYPE}.cof
else
IMAGE_TYPE=production
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/Ethernet_Modified.${IMAGE_TYPE}.cof
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/1360937237/enc28j60.o ${OBJECTDIR}/_ext/1360937237/eth_driver.o ${OBJECTDIR}/_ext/1360937237/main.o


CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

# Path to java used to run MPLAB X when this makefile was created
MP_JAVA_PATH=C:\\Program\ Files\ \(x86\)\\Java\\jre6/bin/
OS_CURRENT="$(shell uname -s)"
############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
MP_CC=C:\\Program\ Files\ \(x86\)\\Microchip\\mplabc18\\v3.40\\bin\\mcc18.exe
# MP_BC is not defined
MP_AS=C:\\Program\ Files\ \(x86\)\\Microchip\\mplabc18\\v3.40\\bin\\..\\mpasm\\MPASMWIN.exe
MP_LD=C:\\Program\ Files\ \(x86\)\\Microchip\\mplabc18\\v3.40\\bin\\mplink.exe
MP_AR=C:\\Program\ Files\ \(x86\)\\Microchip\\mplabc18\\v3.40\\bin\\mplib.exe
# MP_BC is not defined
MP_CC_DIR=C:\\Program\ Files\ \(x86\)\\Microchip\\mplabc18\\v3.40\\bin
# MP_BC_DIR is not defined
MP_AS_DIR=C:\\Program\ Files\ \(x86\)\\Microchip\\mplabc18\\v3.40\\bin\\..\\mpasm
MP_LD_DIR=C:\\Program\ Files\ \(x86\)\\Microchip\\mplabc18\\v3.40\\bin
MP_AR_DIR=C:\\Program\ Files\ \(x86\)\\Microchip\\mplabc18\\v3.40\\bin
# MP_BC_DIR is not defined

# This makefile will use a C preprocessor to generate dependency files
MP_CPP=C:/Program\ Files\ \(x86\)/Microchip/MPLABX/mplab_ide/mplab_ide/modules/../../bin/mplab-cpp

.build-conf: ${BUILD_SUBPROJECTS}
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/Ethernet_Modified.${IMAGE_TYPE}.cof

MP_PROCESSOR_OPTION=18F2620
MP_PROCESSOR_OPTION_LD=18f2620
MP_LINKER_DEBUG_OPTION= -u_DEBUGCODESTART=0xfd80 -u_DEBUGCODELEN=0x280 -u_DEBUGDATASTART=0xef4 -u_DEBUGDATALEN=0xb
# ------------------------------------------------------------------------------------
# Rules for buildStep: createRevGrep
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
__revgrep__:   nbproject/Makefile-${CND_CONF}.mk
	@echo 'grep -q $$@' > __revgrep__
	@echo 'if [ "$$?" -ne "0" ]; then' >> __revgrep__
	@echo '  exit 0' >> __revgrep__
	@echo 'else' >> __revgrep__
	@echo '  exit 1' >> __revgrep__
	@echo 'fi' >> __revgrep__
	@chmod +x __revgrep__
else
__revgrep__:   nbproject/Makefile-${CND_CONF}.mk
	@echo 'grep -q $$@' > __revgrep__
	@echo 'if [ "$$?" -ne "0" ]; then' >> __revgrep__
	@echo '  exit 0' >> __revgrep__
	@echo 'else' >> __revgrep__
	@echo '  exit 1' >> __revgrep__
	@echo 'fi' >> __revgrep__
	@chmod +x __revgrep__
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/1360937237/main.o: ../src/main.c  nbproject/Makefile-${CND_CONF}.mk
	${RM} ${OBJECTDIR}/_ext/1360937237/main.o.d 
	${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD2=1 -p$(MP_PROCESSOR_OPTION) -k -sco -DMINIPIC10T -I"../src" -I"../../src" -I"../../../src" -I"../src/time/include" -I"../src/net/include" -I"../src/include" -I"../src/mpfs/include" -I"../src/uart/include"  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1360937237/main.o   ../src/main.c  > ${OBJECTDIR}/_ext/1360937237/main.err 2>&1 ; if [ $$? -eq 0 ] ; then cat ${OBJECTDIR}/_ext/1360937237/main.err | sed 's/\(^.*:.*:\)\(Warning\)\(.*$$\)/\1 \2:\3/g' ; else cat ${OBJECTDIR}/_ext/1360937237/main.err | sed 's/\(^.*:.*:\)\(Error\)\(.*$$\)/\1 \2:\3/g' ; exit 1 ; fi
	${MP_CPP}  -MMD ${OBJECTDIR}/_ext/1360937237/main.o.temp ../src/main.c __temp_cpp_output__ -D MINIPIC10T -D __18F2620 -D __18CXX -I C:\\Users\\Rahul\\Documents\\Projects\\PIC\\Ethernet_Modified\\src -I C:\\Users\\Rahul\\Documents\\Projects\\PIC\\Ethernet_Modified\\Ethernet_Modified\\../../src -I C:\\Users\\Rahul\\Documents\\Projects\\PIC\\Ethernet_Modified\\Ethernet_Modified\\../../../src -I C:\\Users\\Rahul\\Documents\\Projects\\PIC\\Ethernet_Modified\\Ethernet_Modified\\../src/time/include -I C:\\Users\\Rahul\\Documents\\Projects\\PIC\\Ethernet_Modified\\Ethernet_Modified\\../src/net/include -I C:\\Users\\Rahul\\Documents\\Projects\\PIC\\Ethernet_Modified\\Ethernet_Modified\\../src/include -I C:\\Users\\Rahul\\Documents\\Projects\\PIC\\Ethernet_Modified\\Ethernet_Modified\\../src/mpfs/include -I C:\\Users\\Rahul\\Documents\\Projects\\PIC\\Ethernet_Modified\\Ethernet_Modified\\../src/uart/include -I C:\\Program\ Files\ \(x86\)\\Microchip\\mplabc18\\v3.40\\bin/../h  -D__18F2620
	printf "%s/" ${OBJECTDIR}/_ext/1360937237 > ${OBJECTDIR}/_ext/1360937237/main.o.d
ifneq (,$(findstring MINGW32,$(OS_CURRENT)))
	cat ${OBJECTDIR}/_ext/1360937237/main.o.temp | sed -e 's/\\\ /__SPACES__/g' -e's/\\$$/__EOL__/g' -e 's/\\/\//g' -e 's/__SPACES__/\\\ /g' -e 's/__EOL__/\\/g' >> ${OBJECTDIR}/_ext/1360937237/main.o.d
else
	cat ${OBJECTDIR}/_ext/1360937237/main.o.temp >> ${OBJECTDIR}/_ext/1360937237/main.o.d
endif
	${RM} __temp_cpp_output__
${OBJECTDIR}/_ext/1360937237/eth_driver.o: ../src/eth_driver.c  nbproject/Makefile-${CND_CONF}.mk
	${RM} ${OBJECTDIR}/_ext/1360937237/eth_driver.o.d 
	${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD2=1 -p$(MP_PROCESSOR_OPTION) -k -sco -DMINIPIC10T -I"../src" -I"../../src" -I"../../../src" -I"../src/time/include" -I"../src/net/include" -I"../src/include" -I"../src/mpfs/include" -I"../src/uart/include"  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1360937237/eth_driver.o   ../src/eth_driver.c  > ${OBJECTDIR}/_ext/1360937237/eth_driver.err 2>&1 ; if [ $$? -eq 0 ] ; then cat ${OBJECTDIR}/_ext/1360937237/eth_driver.err | sed 's/\(^.*:.*:\)\(Warning\)\(.*$$\)/\1 \2:\3/g' ; else cat ${OBJECTDIR}/_ext/1360937237/eth_driver.err | sed 's/\(^.*:.*:\)\(Error\)\(.*$$\)/\1 \2:\3/g' ; exit 1 ; fi
	${MP_CPP}  -MMD ${OBJECTDIR}/_ext/1360937237/eth_driver.o.temp ../src/eth_driver.c __temp_cpp_output__ -D MINIPIC10T -D __18F2620 -D __18CXX -I C:\\Users\\Rahul\\Documents\\Projects\\PIC\\Ethernet_Modified\\src -I C:\\Users\\Rahul\\Documents\\Projects\\PIC\\Ethernet_Modified\\Ethernet_Modified\\../../src -I C:\\Users\\Rahul\\Documents\\Projects\\PIC\\Ethernet_Modified\\Ethernet_Modified\\../../../src -I C:\\Users\\Rahul\\Documents\\Projects\\PIC\\Ethernet_Modified\\Ethernet_Modified\\../src/time/include -I C:\\Users\\Rahul\\Documents\\Projects\\PIC\\Ethernet_Modified\\Ethernet_Modified\\../src/net/include -I C:\\Users\\Rahul\\Documents\\Projects\\PIC\\Ethernet_Modified\\Ethernet_Modified\\../src/include -I C:\\Users\\Rahul\\Documents\\Projects\\PIC\\Ethernet_Modified\\Ethernet_Modified\\../src/mpfs/include -I C:\\Users\\Rahul\\Documents\\Projects\\PIC\\Ethernet_Modified\\Ethernet_Modified\\../src/uart/include -I C:\\Program\ Files\ \(x86\)\\Microchip\\mplabc18\\v3.40\\bin/../h  -D__18F2620
	printf "%s/" ${OBJECTDIR}/_ext/1360937237 > ${OBJECTDIR}/_ext/1360937237/eth_driver.o.d
ifneq (,$(findstring MINGW32,$(OS_CURRENT)))
	cat ${OBJECTDIR}/_ext/1360937237/eth_driver.o.temp | sed -e 's/\\\ /__SPACES__/g' -e's/\\$$/__EOL__/g' -e 's/\\/\//g' -e 's/__SPACES__/\\\ /g' -e 's/__EOL__/\\/g' >> ${OBJECTDIR}/_ext/1360937237/eth_driver.o.d
else
	cat ${OBJECTDIR}/_ext/1360937237/eth_driver.o.temp >> ${OBJECTDIR}/_ext/1360937237/eth_driver.o.d
endif
	${RM} __temp_cpp_output__
${OBJECTDIR}/_ext/1360937237/enc28j60.o: ../src/enc28j60.c  nbproject/Makefile-${CND_CONF}.mk
	${RM} ${OBJECTDIR}/_ext/1360937237/enc28j60.o.d 
	${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD2=1 -p$(MP_PROCESSOR_OPTION) -k -sco -DMINIPIC10T -I"../src" -I"../../src" -I"../../../src" -I"../src/time/include" -I"../src/net/include" -I"../src/include" -I"../src/mpfs/include" -I"../src/uart/include"  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1360937237/enc28j60.o   ../src/enc28j60.c  > ${OBJECTDIR}/_ext/1360937237/enc28j60.err 2>&1 ; if [ $$? -eq 0 ] ; then cat ${OBJECTDIR}/_ext/1360937237/enc28j60.err | sed 's/\(^.*:.*:\)\(Warning\)\(.*$$\)/\1 \2:\3/g' ; else cat ${OBJECTDIR}/_ext/1360937237/enc28j60.err | sed 's/\(^.*:.*:\)\(Error\)\(.*$$\)/\1 \2:\3/g' ; exit 1 ; fi
	${MP_CPP}  -MMD ${OBJECTDIR}/_ext/1360937237/enc28j60.o.temp ../src/enc28j60.c __temp_cpp_output__ -D MINIPIC10T -D __18F2620 -D __18CXX -I C:\\Users\\Rahul\\Documents\\Projects\\PIC\\Ethernet_Modified\\src -I C:\\Users\\Rahul\\Documents\\Projects\\PIC\\Ethernet_Modified\\Ethernet_Modified\\../../src -I C:\\Users\\Rahul\\Documents\\Projects\\PIC\\Ethernet_Modified\\Ethernet_Modified\\../../../src -I C:\\Users\\Rahul\\Documents\\Projects\\PIC\\Ethernet_Modified\\Ethernet_Modified\\../src/time/include -I C:\\Users\\Rahul\\Documents\\Projects\\PIC\\Ethernet_Modified\\Ethernet_Modified\\../src/net/include -I C:\\Users\\Rahul\\Documents\\Projects\\PIC\\Ethernet_Modified\\Ethernet_Modified\\../src/include -I C:\\Users\\Rahul\\Documents\\Projects\\PIC\\Ethernet_Modified\\Ethernet_Modified\\../src/mpfs/include -I C:\\Users\\Rahul\\Documents\\Projects\\PIC\\Ethernet_Modified\\Ethernet_Modified\\../src/uart/include -I C:\\Program\ Files\ \(x86\)\\Microchip\\mplabc18\\v3.40\\bin/../h  -D__18F2620
	printf "%s/" ${OBJECTDIR}/_ext/1360937237 > ${OBJECTDIR}/_ext/1360937237/enc28j60.o.d
ifneq (,$(findstring MINGW32,$(OS_CURRENT)))
	cat ${OBJECTDIR}/_ext/1360937237/enc28j60.o.temp | sed -e 's/\\\ /__SPACES__/g' -e's/\\$$/__EOL__/g' -e 's/\\/\//g' -e 's/__SPACES__/\\\ /g' -e 's/__EOL__/\\/g' >> ${OBJECTDIR}/_ext/1360937237/enc28j60.o.d
else
	cat ${OBJECTDIR}/_ext/1360937237/enc28j60.o.temp >> ${OBJECTDIR}/_ext/1360937237/enc28j60.o.d
endif
	${RM} __temp_cpp_output__
else
${OBJECTDIR}/_ext/1360937237/main.o: ../src/main.c  nbproject/Makefile-${CND_CONF}.mk
	${RM} ${OBJECTDIR}/_ext/1360937237/main.o.d 
	${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -k -sco -DMINIPIC10T -I"../src" -I"../../src" -I"../../../src" -I"../src/time/include" -I"../src/net/include" -I"../src/include" -I"../src/mpfs/include" -I"../src/uart/include"  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1360937237/main.o   ../src/main.c  > ${OBJECTDIR}/_ext/1360937237/main.err 2>&1 ; if [ $$? -eq 0 ] ; then cat ${OBJECTDIR}/_ext/1360937237/main.err | sed 's/\(^.*:.*:\)\(Warning\)\(.*$$\)/\1 \2:\3/g' ; else cat ${OBJECTDIR}/_ext/1360937237/main.err | sed 's/\(^.*:.*:\)\(Error\)\(.*$$\)/\1 \2:\3/g' ; exit 1 ; fi
	${MP_CPP}  -MMD ${OBJECTDIR}/_ext/1360937237/main.o.temp ../src/main.c __temp_cpp_output__ -D MINIPIC10T -D __18F2620 -D __18CXX -I C:\\Users\\Rahul\\Documents\\Projects\\PIC\\Ethernet_Modified\\src -I C:\\Users\\Rahul\\Documents\\Projects\\PIC\\Ethernet_Modified\\Ethernet_Modified\\../../src -I C:\\Users\\Rahul\\Documents\\Projects\\PIC\\Ethernet_Modified\\Ethernet_Modified\\../../../src -I C:\\Users\\Rahul\\Documents\\Projects\\PIC\\Ethernet_Modified\\Ethernet_Modified\\../src/time/include -I C:\\Users\\Rahul\\Documents\\Projects\\PIC\\Ethernet_Modified\\Ethernet_Modified\\../src/net/include -I C:\\Users\\Rahul\\Documents\\Projects\\PIC\\Ethernet_Modified\\Ethernet_Modified\\../src/include -I C:\\Users\\Rahul\\Documents\\Projects\\PIC\\Ethernet_Modified\\Ethernet_Modified\\../src/mpfs/include -I C:\\Users\\Rahul\\Documents\\Projects\\PIC\\Ethernet_Modified\\Ethernet_Modified\\../src/uart/include -I C:\\Program\ Files\ \(x86\)\\Microchip\\mplabc18\\v3.40\\bin/../h  -D__18F2620
	printf "%s/" ${OBJECTDIR}/_ext/1360937237 > ${OBJECTDIR}/_ext/1360937237/main.o.d
ifneq (,$(findstring MINGW32,$(OS_CURRENT)))
	cat ${OBJECTDIR}/_ext/1360937237/main.o.temp | sed -e 's/\\\ /__SPACES__/g' -e's/\\$$/__EOL__/g' -e 's/\\/\//g' -e 's/__SPACES__/\\\ /g' -e 's/__EOL__/\\/g' >> ${OBJECTDIR}/_ext/1360937237/main.o.d
else
	cat ${OBJECTDIR}/_ext/1360937237/main.o.temp >> ${OBJECTDIR}/_ext/1360937237/main.o.d
endif
	${RM} __temp_cpp_output__
${OBJECTDIR}/_ext/1360937237/eth_driver.o: ../src/eth_driver.c  nbproject/Makefile-${CND_CONF}.mk
	${RM} ${OBJECTDIR}/_ext/1360937237/eth_driver.o.d 
	${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -k -sco -DMINIPIC10T -I"../src" -I"../../src" -I"../../../src" -I"../src/time/include" -I"../src/net/include" -I"../src/include" -I"../src/mpfs/include" -I"../src/uart/include"  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1360937237/eth_driver.o   ../src/eth_driver.c  > ${OBJECTDIR}/_ext/1360937237/eth_driver.err 2>&1 ; if [ $$? -eq 0 ] ; then cat ${OBJECTDIR}/_ext/1360937237/eth_driver.err | sed 's/\(^.*:.*:\)\(Warning\)\(.*$$\)/\1 \2:\3/g' ; else cat ${OBJECTDIR}/_ext/1360937237/eth_driver.err | sed 's/\(^.*:.*:\)\(Error\)\(.*$$\)/\1 \2:\3/g' ; exit 1 ; fi
	${MP_CPP}  -MMD ${OBJECTDIR}/_ext/1360937237/eth_driver.o.temp ../src/eth_driver.c __temp_cpp_output__ -D MINIPIC10T -D __18F2620 -D __18CXX -I C:\\Users\\Rahul\\Documents\\Projects\\PIC\\Ethernet_Modified\\src -I C:\\Users\\Rahul\\Documents\\Projects\\PIC\\Ethernet_Modified\\Ethernet_Modified\\../../src -I C:\\Users\\Rahul\\Documents\\Projects\\PIC\\Ethernet_Modified\\Ethernet_Modified\\../../../src -I C:\\Users\\Rahul\\Documents\\Projects\\PIC\\Ethernet_Modified\\Ethernet_Modified\\../src/time/include -I C:\\Users\\Rahul\\Documents\\Projects\\PIC\\Ethernet_Modified\\Ethernet_Modified\\../src/net/include -I C:\\Users\\Rahul\\Documents\\Projects\\PIC\\Ethernet_Modified\\Ethernet_Modified\\../src/include -I C:\\Users\\Rahul\\Documents\\Projects\\PIC\\Ethernet_Modified\\Ethernet_Modified\\../src/mpfs/include -I C:\\Users\\Rahul\\Documents\\Projects\\PIC\\Ethernet_Modified\\Ethernet_Modified\\../src/uart/include -I C:\\Program\ Files\ \(x86\)\\Microchip\\mplabc18\\v3.40\\bin/../h  -D__18F2620
	printf "%s/" ${OBJECTDIR}/_ext/1360937237 > ${OBJECTDIR}/_ext/1360937237/eth_driver.o.d
ifneq (,$(findstring MINGW32,$(OS_CURRENT)))
	cat ${OBJECTDIR}/_ext/1360937237/eth_driver.o.temp | sed -e 's/\\\ /__SPACES__/g' -e's/\\$$/__EOL__/g' -e 's/\\/\//g' -e 's/__SPACES__/\\\ /g' -e 's/__EOL__/\\/g' >> ${OBJECTDIR}/_ext/1360937237/eth_driver.o.d
else
	cat ${OBJECTDIR}/_ext/1360937237/eth_driver.o.temp >> ${OBJECTDIR}/_ext/1360937237/eth_driver.o.d
endif
	${RM} __temp_cpp_output__
${OBJECTDIR}/_ext/1360937237/enc28j60.o: ../src/enc28j60.c  nbproject/Makefile-${CND_CONF}.mk
	${RM} ${OBJECTDIR}/_ext/1360937237/enc28j60.o.d 
	${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -k -sco -DMINIPIC10T -I"../src" -I"../../src" -I"../../../src" -I"../src/time/include" -I"../src/net/include" -I"../src/include" -I"../src/mpfs/include" -I"../src/uart/include"  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1360937237/enc28j60.o   ../src/enc28j60.c  > ${OBJECTDIR}/_ext/1360937237/enc28j60.err 2>&1 ; if [ $$? -eq 0 ] ; then cat ${OBJECTDIR}/_ext/1360937237/enc28j60.err | sed 's/\(^.*:.*:\)\(Warning\)\(.*$$\)/\1 \2:\3/g' ; else cat ${OBJECTDIR}/_ext/1360937237/enc28j60.err | sed 's/\(^.*:.*:\)\(Error\)\(.*$$\)/\1 \2:\3/g' ; exit 1 ; fi
	${MP_CPP}  -MMD ${OBJECTDIR}/_ext/1360937237/enc28j60.o.temp ../src/enc28j60.c __temp_cpp_output__ -D MINIPIC10T -D __18F2620 -D __18CXX -I C:\\Users\\Rahul\\Documents\\Projects\\PIC\\Ethernet_Modified\\src -I C:\\Users\\Rahul\\Documents\\Projects\\PIC\\Ethernet_Modified\\Ethernet_Modified\\../../src -I C:\\Users\\Rahul\\Documents\\Projects\\PIC\\Ethernet_Modified\\Ethernet_Modified\\../../../src -I C:\\Users\\Rahul\\Documents\\Projects\\PIC\\Ethernet_Modified\\Ethernet_Modified\\../src/time/include -I C:\\Users\\Rahul\\Documents\\Projects\\PIC\\Ethernet_Modified\\Ethernet_Modified\\../src/net/include -I C:\\Users\\Rahul\\Documents\\Projects\\PIC\\Ethernet_Modified\\Ethernet_Modified\\../src/include -I C:\\Users\\Rahul\\Documents\\Projects\\PIC\\Ethernet_Modified\\Ethernet_Modified\\../src/mpfs/include -I C:\\Users\\Rahul\\Documents\\Projects\\PIC\\Ethernet_Modified\\Ethernet_Modified\\../src/uart/include -I C:\\Program\ Files\ \(x86\)\\Microchip\\mplabc18\\v3.40\\bin/../h  -D__18F2620
	printf "%s/" ${OBJECTDIR}/_ext/1360937237 > ${OBJECTDIR}/_ext/1360937237/enc28j60.o.d
ifneq (,$(findstring MINGW32,$(OS_CURRENT)))
	cat ${OBJECTDIR}/_ext/1360937237/enc28j60.o.temp | sed -e 's/\\\ /__SPACES__/g' -e's/\\$$/__EOL__/g' -e 's/\\/\//g' -e 's/__SPACES__/\\\ /g' -e 's/__EOL__/\\/g' >> ${OBJECTDIR}/_ext/1360937237/enc28j60.o.d
else
	cat ${OBJECTDIR}/_ext/1360937237/enc28j60.o.temp >> ${OBJECTDIR}/_ext/1360937237/enc28j60.o.d
endif
	${RM} __temp_cpp_output__
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/Ethernet_Modified.${IMAGE_TYPE}.cof: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_LD} $(MP_EXTRA_LD_PRE)   -p$(MP_PROCESSOR_OPTION_LD)  -w -x -u_DEBUG -l"../../../../../../../Program Files/Microchip/MCC18/lib"  -z__MPLAB_BUILD=1  -u_CRUNTIME -z__MPLAB_DEBUG=1 -z__MPLAB_DEBUGGER_ICD2=1 $(MP_LINKER_DEBUG_OPTION) -l ${MP_CC_DIR}\\..\\lib  -odist/${CND_CONF}/${IMAGE_TYPE}/Ethernet_Modified.${IMAGE_TYPE}.cof ${OBJECTFILES}      
else
dist/${CND_CONF}/${IMAGE_TYPE}/Ethernet_Modified.${IMAGE_TYPE}.cof: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_LD} $(MP_EXTRA_LD_PRE)   -p$(MP_PROCESSOR_OPTION_LD)  -w  -l"../../../../../../../Program Files/Microchip/MCC18/lib"  -z__MPLAB_BUILD=1  -u_CRUNTIME -l ${MP_CC_DIR}\\..\\lib  -odist/${CND_CONF}/${IMAGE_TYPE}/Ethernet_Modified.${IMAGE_TYPE}.cof ${OBJECTFILES}      
endif


# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf:
	${RM} -r build/default
	${RM} -r dist/default

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
