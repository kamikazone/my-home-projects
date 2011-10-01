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
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/Ethernet.X.${IMAGE_TYPE}.cof
else
IMAGE_TYPE=production
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/Ethernet.X.${IMAGE_TYPE}.cof
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/1019104662/mpfs.o ${OBJECTDIR}/_ext/1360937237/delay.o ${OBJECTDIR}/_ext/1360937237/main.o ${OBJECTDIR}/_ext/1360937237/mpfsimg.o ${OBJECTDIR}/_ext/659862947/arp.o ${OBJECTDIR}/_ext/659862947/dhcp.o ${OBJECTDIR}/_ext/659862947/dns.o ${OBJECTDIR}/_ext/659862947/enc28j60.o ${OBJECTDIR}/_ext/659862947/helpers.o ${OBJECTDIR}/_ext/659862947/httpd.o ${OBJECTDIR}/_ext/659862947/icmpd.o ${OBJECTDIR}/_ext/659862947/ip.o ${OBJECTDIR}/_ext/659862947/nbns.o ${OBJECTDIR}/_ext/659862947/stacktsk.o ${OBJECTDIR}/_ext/659862947/tcp.o ${OBJECTDIR}/_ext/659862947/tick.o ${OBJECTDIR}/_ext/659862947/udp.o


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
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/Ethernet.X.${IMAGE_TYPE}.cof

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
${OBJECTDIR}/_ext/1360937237/delay.o: ../src/delay.c  nbproject/Makefile-${CND_CONF}.mk
	${RM} ${OBJECTDIR}/_ext/1360937237/delay.o.d 
	${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD2=1 -p$(MP_PROCESSOR_OPTION) -k -sco -DMINIPIC10T -I"../src" -I"../../src" -I"../../../src" -I"../src/time/include" -I"../src/net/include" -I"../src/include" -I"../src/mpfs/include" -I"../src/uart/include"  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1360937237/delay.o   ../src/delay.c  > ${OBJECTDIR}/_ext/1360937237/delay.err 2>&1 ; if [ $$? -eq 0 ] ; then cat ${OBJECTDIR}/_ext/1360937237/delay.err | sed 's/\(^.*:.*:\)\(Warning\)\(.*$$\)/\1 \2:\3/g' ; else cat ${OBJECTDIR}/_ext/1360937237/delay.err | sed 's/\(^.*:.*:\)\(Error\)\(.*$$\)/\1 \2:\3/g' ; exit 1 ; fi
	${MP_CPP}  -MMD ${OBJECTDIR}/_ext/1360937237/delay.o.temp ../src/delay.c __temp_cpp_output__ -D MINIPIC10T -D __18F2620 -D __18CXX -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\src -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\Ethernet.X\\../../src -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\Ethernet.X\\../../../src -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\Ethernet.X\\../src/time/include -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\src\\net\\include -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\src\\include -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\src\\mpfs\\include -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\Ethernet.X\\../src/uart/include -I C:\\Program\ Files\ \(x86\)\\Microchip\\mplabc18\\v3.40\\bin/../h  -D__18F2620
	printf "%s/" ${OBJECTDIR}/_ext/1360937237 > ${OBJECTDIR}/_ext/1360937237/delay.o.d
ifneq (,$(findstring MINGW32,$(OS_CURRENT)))
	cat ${OBJECTDIR}/_ext/1360937237/delay.o.temp | sed -e 's/\\\ /__SPACES__/g' -e's/\\$$/__EOL__/g' -e 's/\\/\//g' -e 's/__SPACES__/\\\ /g' -e 's/__EOL__/\\/g' >> ${OBJECTDIR}/_ext/1360937237/delay.o.d
else
	cat ${OBJECTDIR}/_ext/1360937237/delay.o.temp >> ${OBJECTDIR}/_ext/1360937237/delay.o.d
endif
	${RM} __temp_cpp_output__
${OBJECTDIR}/_ext/659862947/dns.o: ../src/net/dns.c  nbproject/Makefile-${CND_CONF}.mk
	${RM} ${OBJECTDIR}/_ext/659862947/dns.o.d 
	${MKDIR} ${OBJECTDIR}/_ext/659862947 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD2=1 -p$(MP_PROCESSOR_OPTION) -k -sco -DMINIPIC10T -I"../src" -I"../../src" -I"../../../src" -I"../src/time/include" -I"../src/net/include" -I"../src/include" -I"../src/mpfs/include" -I"../src/uart/include"  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/659862947/dns.o   ../src/net/dns.c  > ${OBJECTDIR}/_ext/659862947/dns.err 2>&1 ; if [ $$? -eq 0 ] ; then cat ${OBJECTDIR}/_ext/659862947/dns.err | sed 's/\(^.*:.*:\)\(Warning\)\(.*$$\)/\1 \2:\3/g' ; else cat ${OBJECTDIR}/_ext/659862947/dns.err | sed 's/\(^.*:.*:\)\(Error\)\(.*$$\)/\1 \2:\3/g' ; exit 1 ; fi
	${MP_CPP}  -MMD ${OBJECTDIR}/_ext/659862947/dns.o.temp ../src/net/dns.c __temp_cpp_output__ -D MINIPIC10T -D __18F2620 -D __18CXX -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\src -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\Ethernet.X\\../../src -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\Ethernet.X\\../../../src -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\Ethernet.X\\../src/time/include -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\src\\net\\include -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\src\\include -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\src\\mpfs\\include -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\Ethernet.X\\../src/uart/include -I C:\\Program\ Files\ \(x86\)\\Microchip\\mplabc18\\v3.40\\bin/../h  -D__18F2620
	printf "%s/" ${OBJECTDIR}/_ext/659862947 > ${OBJECTDIR}/_ext/659862947/dns.o.d
ifneq (,$(findstring MINGW32,$(OS_CURRENT)))
	cat ${OBJECTDIR}/_ext/659862947/dns.o.temp | sed -e 's/\\\ /__SPACES__/g' -e's/\\$$/__EOL__/g' -e 's/\\/\//g' -e 's/__SPACES__/\\\ /g' -e 's/__EOL__/\\/g' >> ${OBJECTDIR}/_ext/659862947/dns.o.d
else
	cat ${OBJECTDIR}/_ext/659862947/dns.o.temp >> ${OBJECTDIR}/_ext/659862947/dns.o.d
endif
	${RM} __temp_cpp_output__
${OBJECTDIR}/_ext/659862947/nbns.o: ../src/net/nbns.c  nbproject/Makefile-${CND_CONF}.mk
	${RM} ${OBJECTDIR}/_ext/659862947/nbns.o.d 
	${MKDIR} ${OBJECTDIR}/_ext/659862947 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD2=1 -p$(MP_PROCESSOR_OPTION) -k -sco -DMINIPIC10T -I"../src" -I"../../src" -I"../../../src" -I"../src/time/include" -I"../src/net/include" -I"../src/include" -I"../src/mpfs/include" -I"../src/uart/include"  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/659862947/nbns.o   ../src/net/nbns.c  > ${OBJECTDIR}/_ext/659862947/nbns.err 2>&1 ; if [ $$? -eq 0 ] ; then cat ${OBJECTDIR}/_ext/659862947/nbns.err | sed 's/\(^.*:.*:\)\(Warning\)\(.*$$\)/\1 \2:\3/g' ; else cat ${OBJECTDIR}/_ext/659862947/nbns.err | sed 's/\(^.*:.*:\)\(Error\)\(.*$$\)/\1 \2:\3/g' ; exit 1 ; fi
	${MP_CPP}  -MMD ${OBJECTDIR}/_ext/659862947/nbns.o.temp ../src/net/nbns.c __temp_cpp_output__ -D MINIPIC10T -D __18F2620 -D __18CXX -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\src -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\Ethernet.X\\../../src -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\Ethernet.X\\../../../src -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\Ethernet.X\\../src/time/include -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\src\\net\\include -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\src\\include -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\src\\mpfs\\include -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\Ethernet.X\\../src/uart/include -I C:\\Program\ Files\ \(x86\)\\Microchip\\mplabc18\\v3.40\\bin/../h  -D__18F2620
	printf "%s/" ${OBJECTDIR}/_ext/659862947 > ${OBJECTDIR}/_ext/659862947/nbns.o.d
ifneq (,$(findstring MINGW32,$(OS_CURRENT)))
	cat ${OBJECTDIR}/_ext/659862947/nbns.o.temp | sed -e 's/\\\ /__SPACES__/g' -e's/\\$$/__EOL__/g' -e 's/\\/\//g' -e 's/__SPACES__/\\\ /g' -e 's/__EOL__/\\/g' >> ${OBJECTDIR}/_ext/659862947/nbns.o.d
else
	cat ${OBJECTDIR}/_ext/659862947/nbns.o.temp >> ${OBJECTDIR}/_ext/659862947/nbns.o.d
endif
	${RM} __temp_cpp_output__
${OBJECTDIR}/_ext/659862947/udp.o: ../src/net/udp.c  nbproject/Makefile-${CND_CONF}.mk
	${RM} ${OBJECTDIR}/_ext/659862947/udp.o.d 
	${MKDIR} ${OBJECTDIR}/_ext/659862947 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD2=1 -p$(MP_PROCESSOR_OPTION) -k -sco -DMINIPIC10T -I"../src" -I"../../src" -I"../../../src" -I"../src/time/include" -I"../src/net/include" -I"../src/include" -I"../src/mpfs/include" -I"../src/uart/include"  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/659862947/udp.o   ../src/net/udp.c  > ${OBJECTDIR}/_ext/659862947/udp.err 2>&1 ; if [ $$? -eq 0 ] ; then cat ${OBJECTDIR}/_ext/659862947/udp.err | sed 's/\(^.*:.*:\)\(Warning\)\(.*$$\)/\1 \2:\3/g' ; else cat ${OBJECTDIR}/_ext/659862947/udp.err | sed 's/\(^.*:.*:\)\(Error\)\(.*$$\)/\1 \2:\3/g' ; exit 1 ; fi
	${MP_CPP}  -MMD ${OBJECTDIR}/_ext/659862947/udp.o.temp ../src/net/udp.c __temp_cpp_output__ -D MINIPIC10T -D __18F2620 -D __18CXX -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\src -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\Ethernet.X\\../../src -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\Ethernet.X\\../../../src -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\Ethernet.X\\../src/time/include -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\src\\net\\include -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\src\\include -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\src\\mpfs\\include -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\Ethernet.X\\../src/uart/include -I C:\\Program\ Files\ \(x86\)\\Microchip\\mplabc18\\v3.40\\bin/../h  -D__18F2620
	printf "%s/" ${OBJECTDIR}/_ext/659862947 > ${OBJECTDIR}/_ext/659862947/udp.o.d
ifneq (,$(findstring MINGW32,$(OS_CURRENT)))
	cat ${OBJECTDIR}/_ext/659862947/udp.o.temp | sed -e 's/\\\ /__SPACES__/g' -e's/\\$$/__EOL__/g' -e 's/\\/\//g' -e 's/__SPACES__/\\\ /g' -e 's/__EOL__/\\/g' >> ${OBJECTDIR}/_ext/659862947/udp.o.d
else
	cat ${OBJECTDIR}/_ext/659862947/udp.o.temp >> ${OBJECTDIR}/_ext/659862947/udp.o.d
endif
	${RM} __temp_cpp_output__
${OBJECTDIR}/_ext/659862947/helpers.o: ../src/net/helpers.c  nbproject/Makefile-${CND_CONF}.mk
	${RM} ${OBJECTDIR}/_ext/659862947/helpers.o.d 
	${MKDIR} ${OBJECTDIR}/_ext/659862947 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD2=1 -p$(MP_PROCESSOR_OPTION) -k -sco -DMINIPIC10T -I"../src" -I"../../src" -I"../../../src" -I"../src/time/include" -I"../src/net/include" -I"../src/include" -I"../src/mpfs/include" -I"../src/uart/include"  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/659862947/helpers.o   ../src/net/helpers.c  > ${OBJECTDIR}/_ext/659862947/helpers.err 2>&1 ; if [ $$? -eq 0 ] ; then cat ${OBJECTDIR}/_ext/659862947/helpers.err | sed 's/\(^.*:.*:\)\(Warning\)\(.*$$\)/\1 \2:\3/g' ; else cat ${OBJECTDIR}/_ext/659862947/helpers.err | sed 's/\(^.*:.*:\)\(Error\)\(.*$$\)/\1 \2:\3/g' ; exit 1 ; fi
	${MP_CPP}  -MMD ${OBJECTDIR}/_ext/659862947/helpers.o.temp ../src/net/helpers.c __temp_cpp_output__ -D MINIPIC10T -D __18F2620 -D __18CXX -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\src -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\Ethernet.X\\../../src -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\Ethernet.X\\../../../src -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\Ethernet.X\\../src/time/include -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\src\\net\\include -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\src\\include -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\src\\mpfs\\include -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\Ethernet.X\\../src/uart/include -I C:\\Program\ Files\ \(x86\)\\Microchip\\mplabc18\\v3.40\\bin/../h  -D__18F2620
	printf "%s/" ${OBJECTDIR}/_ext/659862947 > ${OBJECTDIR}/_ext/659862947/helpers.o.d
ifneq (,$(findstring MINGW32,$(OS_CURRENT)))
	cat ${OBJECTDIR}/_ext/659862947/helpers.o.temp | sed -e 's/\\\ /__SPACES__/g' -e's/\\$$/__EOL__/g' -e 's/\\/\//g' -e 's/__SPACES__/\\\ /g' -e 's/__EOL__/\\/g' >> ${OBJECTDIR}/_ext/659862947/helpers.o.d
else
	cat ${OBJECTDIR}/_ext/659862947/helpers.o.temp >> ${OBJECTDIR}/_ext/659862947/helpers.o.d
endif
	${RM} __temp_cpp_output__
${OBJECTDIR}/_ext/1019104662/mpfs.o: ../src/mpfs/mpfs.c  nbproject/Makefile-${CND_CONF}.mk
	${RM} ${OBJECTDIR}/_ext/1019104662/mpfs.o.d 
	${MKDIR} ${OBJECTDIR}/_ext/1019104662 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD2=1 -p$(MP_PROCESSOR_OPTION) -k -sco -DMINIPIC10T -I"../src" -I"../../src" -I"../../../src" -I"../src/time/include" -I"../src/net/include" -I"../src/include" -I"../src/mpfs/include" -I"../src/uart/include"  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1019104662/mpfs.o   ../src/mpfs/mpfs.c  > ${OBJECTDIR}/_ext/1019104662/mpfs.err 2>&1 ; if [ $$? -eq 0 ] ; then cat ${OBJECTDIR}/_ext/1019104662/mpfs.err | sed 's/\(^.*:.*:\)\(Warning\)\(.*$$\)/\1 \2:\3/g' ; else cat ${OBJECTDIR}/_ext/1019104662/mpfs.err | sed 's/\(^.*:.*:\)\(Error\)\(.*$$\)/\1 \2:\3/g' ; exit 1 ; fi
	${MP_CPP}  -MMD ${OBJECTDIR}/_ext/1019104662/mpfs.o.temp ../src/mpfs/mpfs.c __temp_cpp_output__ -D MINIPIC10T -D __18F2620 -D __18CXX -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\src -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\Ethernet.X\\../../src -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\Ethernet.X\\../../../src -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\Ethernet.X\\../src/time/include -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\src\\net\\include -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\src\\include -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\src\\mpfs\\include -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\Ethernet.X\\../src/uart/include -I C:\\Program\ Files\ \(x86\)\\Microchip\\mplabc18\\v3.40\\bin/../h  -D__18F2620
	printf "%s/" ${OBJECTDIR}/_ext/1019104662 > ${OBJECTDIR}/_ext/1019104662/mpfs.o.d
ifneq (,$(findstring MINGW32,$(OS_CURRENT)))
	cat ${OBJECTDIR}/_ext/1019104662/mpfs.o.temp | sed -e 's/\\\ /__SPACES__/g' -e's/\\$$/__EOL__/g' -e 's/\\/\//g' -e 's/__SPACES__/\\\ /g' -e 's/__EOL__/\\/g' >> ${OBJECTDIR}/_ext/1019104662/mpfs.o.d
else
	cat ${OBJECTDIR}/_ext/1019104662/mpfs.o.temp >> ${OBJECTDIR}/_ext/1019104662/mpfs.o.d
endif
	${RM} __temp_cpp_output__
${OBJECTDIR}/_ext/659862947/tick.o: ../src/net/tick.c  nbproject/Makefile-${CND_CONF}.mk
	${RM} ${OBJECTDIR}/_ext/659862947/tick.o.d 
	${MKDIR} ${OBJECTDIR}/_ext/659862947 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD2=1 -p$(MP_PROCESSOR_OPTION) -k -sco -DMINIPIC10T -I"../src" -I"../../src" -I"../../../src" -I"../src/time/include" -I"../src/net/include" -I"../src/include" -I"../src/mpfs/include" -I"../src/uart/include"  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/659862947/tick.o   ../src/net/tick.c  > ${OBJECTDIR}/_ext/659862947/tick.err 2>&1 ; if [ $$? -eq 0 ] ; then cat ${OBJECTDIR}/_ext/659862947/tick.err | sed 's/\(^.*:.*:\)\(Warning\)\(.*$$\)/\1 \2:\3/g' ; else cat ${OBJECTDIR}/_ext/659862947/tick.err | sed 's/\(^.*:.*:\)\(Error\)\(.*$$\)/\1 \2:\3/g' ; exit 1 ; fi
	${MP_CPP}  -MMD ${OBJECTDIR}/_ext/659862947/tick.o.temp ../src/net/tick.c __temp_cpp_output__ -D MINIPIC10T -D __18F2620 -D __18CXX -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\src -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\Ethernet.X\\../../src -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\Ethernet.X\\../../../src -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\Ethernet.X\\../src/time/include -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\src\\net\\include -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\src\\include -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\src\\mpfs\\include -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\Ethernet.X\\../src/uart/include -I C:\\Program\ Files\ \(x86\)\\Microchip\\mplabc18\\v3.40\\bin/../h  -D__18F2620
	printf "%s/" ${OBJECTDIR}/_ext/659862947 > ${OBJECTDIR}/_ext/659862947/tick.o.d
ifneq (,$(findstring MINGW32,$(OS_CURRENT)))
	cat ${OBJECTDIR}/_ext/659862947/tick.o.temp | sed -e 's/\\\ /__SPACES__/g' -e's/\\$$/__EOL__/g' -e 's/\\/\//g' -e 's/__SPACES__/\\\ /g' -e 's/__EOL__/\\/g' >> ${OBJECTDIR}/_ext/659862947/tick.o.d
else
	cat ${OBJECTDIR}/_ext/659862947/tick.o.temp >> ${OBJECTDIR}/_ext/659862947/tick.o.d
endif
	${RM} __temp_cpp_output__
${OBJECTDIR}/_ext/659862947/dhcp.o: ../src/net/dhcp.c  nbproject/Makefile-${CND_CONF}.mk
	${RM} ${OBJECTDIR}/_ext/659862947/dhcp.o.d 
	${MKDIR} ${OBJECTDIR}/_ext/659862947 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD2=1 -p$(MP_PROCESSOR_OPTION) -k -sco -DMINIPIC10T -I"../src" -I"../../src" -I"../../../src" -I"../src/time/include" -I"../src/net/include" -I"../src/include" -I"../src/mpfs/include" -I"../src/uart/include"  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/659862947/dhcp.o   ../src/net/dhcp.c  > ${OBJECTDIR}/_ext/659862947/dhcp.err 2>&1 ; if [ $$? -eq 0 ] ; then cat ${OBJECTDIR}/_ext/659862947/dhcp.err | sed 's/\(^.*:.*:\)\(Warning\)\(.*$$\)/\1 \2:\3/g' ; else cat ${OBJECTDIR}/_ext/659862947/dhcp.err | sed 's/\(^.*:.*:\)\(Error\)\(.*$$\)/\1 \2:\3/g' ; exit 1 ; fi
	${MP_CPP}  -MMD ${OBJECTDIR}/_ext/659862947/dhcp.o.temp ../src/net/dhcp.c __temp_cpp_output__ -D MINIPIC10T -D __18F2620 -D __18CXX -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\src -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\Ethernet.X\\../../src -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\Ethernet.X\\../../../src -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\Ethernet.X\\../src/time/include -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\src\\net\\include -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\src\\include -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\src\\mpfs\\include -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\Ethernet.X\\../src/uart/include -I C:\\Program\ Files\ \(x86\)\\Microchip\\mplabc18\\v3.40\\bin/../h  -D__18F2620
	printf "%s/" ${OBJECTDIR}/_ext/659862947 > ${OBJECTDIR}/_ext/659862947/dhcp.o.d
ifneq (,$(findstring MINGW32,$(OS_CURRENT)))
	cat ${OBJECTDIR}/_ext/659862947/dhcp.o.temp | sed -e 's/\\\ /__SPACES__/g' -e's/\\$$/__EOL__/g' -e 's/\\/\//g' -e 's/__SPACES__/\\\ /g' -e 's/__EOL__/\\/g' >> ${OBJECTDIR}/_ext/659862947/dhcp.o.d
else
	cat ${OBJECTDIR}/_ext/659862947/dhcp.o.temp >> ${OBJECTDIR}/_ext/659862947/dhcp.o.d
endif
	${RM} __temp_cpp_output__
${OBJECTDIR}/_ext/659862947/enc28j60.o: ../src/net/enc28j60.c  nbproject/Makefile-${CND_CONF}.mk
	${RM} ${OBJECTDIR}/_ext/659862947/enc28j60.o.d 
	${MKDIR} ${OBJECTDIR}/_ext/659862947 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD2=1 -p$(MP_PROCESSOR_OPTION) -k -sco -DMINIPIC10T -I"../src" -I"../../src" -I"../../../src" -I"../src/time/include" -I"../src/net/include" -I"../src/include" -I"../src/mpfs/include" -I"../src/uart/include"  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/659862947/enc28j60.o   ../src/net/enc28j60.c  > ${OBJECTDIR}/_ext/659862947/enc28j60.err 2>&1 ; if [ $$? -eq 0 ] ; then cat ${OBJECTDIR}/_ext/659862947/enc28j60.err | sed 's/\(^.*:.*:\)\(Warning\)\(.*$$\)/\1 \2:\3/g' ; else cat ${OBJECTDIR}/_ext/659862947/enc28j60.err | sed 's/\(^.*:.*:\)\(Error\)\(.*$$\)/\1 \2:\3/g' ; exit 1 ; fi
	${MP_CPP}  -MMD ${OBJECTDIR}/_ext/659862947/enc28j60.o.temp ../src/net/enc28j60.c __temp_cpp_output__ -D MINIPIC10T -D __18F2620 -D __18CXX -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\src -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\Ethernet.X\\../../src -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\Ethernet.X\\../../../src -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\Ethernet.X\\../src/time/include -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\src\\net\\include -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\src\\include -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\src\\mpfs\\include -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\Ethernet.X\\../src/uart/include -I C:\\Program\ Files\ \(x86\)\\Microchip\\mplabc18\\v3.40\\bin/../h  -D__18F2620
	printf "%s/" ${OBJECTDIR}/_ext/659862947 > ${OBJECTDIR}/_ext/659862947/enc28j60.o.d
ifneq (,$(findstring MINGW32,$(OS_CURRENT)))
	cat ${OBJECTDIR}/_ext/659862947/enc28j60.o.temp | sed -e 's/\\\ /__SPACES__/g' -e's/\\$$/__EOL__/g' -e 's/\\/\//g' -e 's/__SPACES__/\\\ /g' -e 's/__EOL__/\\/g' >> ${OBJECTDIR}/_ext/659862947/enc28j60.o.d
else
	cat ${OBJECTDIR}/_ext/659862947/enc28j60.o.temp >> ${OBJECTDIR}/_ext/659862947/enc28j60.o.d
endif
	${RM} __temp_cpp_output__
${OBJECTDIR}/_ext/659862947/httpd.o: ../src/net/httpd.c  nbproject/Makefile-${CND_CONF}.mk
	${RM} ${OBJECTDIR}/_ext/659862947/httpd.o.d 
	${MKDIR} ${OBJECTDIR}/_ext/659862947 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD2=1 -p$(MP_PROCESSOR_OPTION) -k -sco -DMINIPIC10T -I"../src" -I"../../src" -I"../../../src" -I"../src/time/include" -I"../src/net/include" -I"../src/include" -I"../src/mpfs/include" -I"../src/uart/include"  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/659862947/httpd.o   ../src/net/httpd.c  > ${OBJECTDIR}/_ext/659862947/httpd.err 2>&1 ; if [ $$? -eq 0 ] ; then cat ${OBJECTDIR}/_ext/659862947/httpd.err | sed 's/\(^.*:.*:\)\(Warning\)\(.*$$\)/\1 \2:\3/g' ; else cat ${OBJECTDIR}/_ext/659862947/httpd.err | sed 's/\(^.*:.*:\)\(Error\)\(.*$$\)/\1 \2:\3/g' ; exit 1 ; fi
	${MP_CPP}  -MMD ${OBJECTDIR}/_ext/659862947/httpd.o.temp ../src/net/httpd.c __temp_cpp_output__ -D MINIPIC10T -D __18F2620 -D __18CXX -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\src -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\Ethernet.X\\../../src -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\Ethernet.X\\../../../src -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\Ethernet.X\\../src/time/include -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\src\\net\\include -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\src\\include -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\src\\mpfs\\include -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\Ethernet.X\\../src/uart/include -I C:\\Program\ Files\ \(x86\)\\Microchip\\mplabc18\\v3.40\\bin/../h  -D__18F2620
	printf "%s/" ${OBJECTDIR}/_ext/659862947 > ${OBJECTDIR}/_ext/659862947/httpd.o.d
ifneq (,$(findstring MINGW32,$(OS_CURRENT)))
	cat ${OBJECTDIR}/_ext/659862947/httpd.o.temp | sed -e 's/\\\ /__SPACES__/g' -e's/\\$$/__EOL__/g' -e 's/\\/\//g' -e 's/__SPACES__/\\\ /g' -e 's/__EOL__/\\/g' >> ${OBJECTDIR}/_ext/659862947/httpd.o.d
else
	cat ${OBJECTDIR}/_ext/659862947/httpd.o.temp >> ${OBJECTDIR}/_ext/659862947/httpd.o.d
endif
	${RM} __temp_cpp_output__
${OBJECTDIR}/_ext/659862947/stacktsk.o: ../src/net/stacktsk.c  nbproject/Makefile-${CND_CONF}.mk
	${RM} ${OBJECTDIR}/_ext/659862947/stacktsk.o.d 
	${MKDIR} ${OBJECTDIR}/_ext/659862947 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD2=1 -p$(MP_PROCESSOR_OPTION) -k -sco -DMINIPIC10T -I"../src" -I"../../src" -I"../../../src" -I"../src/time/include" -I"../src/net/include" -I"../src/include" -I"../src/mpfs/include" -I"../src/uart/include"  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/659862947/stacktsk.o   ../src/net/stacktsk.c  > ${OBJECTDIR}/_ext/659862947/stacktsk.err 2>&1 ; if [ $$? -eq 0 ] ; then cat ${OBJECTDIR}/_ext/659862947/stacktsk.err | sed 's/\(^.*:.*:\)\(Warning\)\(.*$$\)/\1 \2:\3/g' ; else cat ${OBJECTDIR}/_ext/659862947/stacktsk.err | sed 's/\(^.*:.*:\)\(Error\)\(.*$$\)/\1 \2:\3/g' ; exit 1 ; fi
	${MP_CPP}  -MMD ${OBJECTDIR}/_ext/659862947/stacktsk.o.temp ../src/net/stacktsk.c __temp_cpp_output__ -D MINIPIC10T -D __18F2620 -D __18CXX -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\src -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\Ethernet.X\\../../src -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\Ethernet.X\\../../../src -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\Ethernet.X\\../src/time/include -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\src\\net\\include -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\src\\include -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\src\\mpfs\\include -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\Ethernet.X\\../src/uart/include -I C:\\Program\ Files\ \(x86\)\\Microchip\\mplabc18\\v3.40\\bin/../h  -D__18F2620
	printf "%s/" ${OBJECTDIR}/_ext/659862947 > ${OBJECTDIR}/_ext/659862947/stacktsk.o.d
ifneq (,$(findstring MINGW32,$(OS_CURRENT)))
	cat ${OBJECTDIR}/_ext/659862947/stacktsk.o.temp | sed -e 's/\\\ /__SPACES__/g' -e's/\\$$/__EOL__/g' -e 's/\\/\//g' -e 's/__SPACES__/\\\ /g' -e 's/__EOL__/\\/g' >> ${OBJECTDIR}/_ext/659862947/stacktsk.o.d
else
	cat ${OBJECTDIR}/_ext/659862947/stacktsk.o.temp >> ${OBJECTDIR}/_ext/659862947/stacktsk.o.d
endif
	${RM} __temp_cpp_output__
${OBJECTDIR}/_ext/659862947/ip.o: ../src/net/ip.c  nbproject/Makefile-${CND_CONF}.mk
	${RM} ${OBJECTDIR}/_ext/659862947/ip.o.d 
	${MKDIR} ${OBJECTDIR}/_ext/659862947 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD2=1 -p$(MP_PROCESSOR_OPTION) -k -sco -DMINIPIC10T -I"../src" -I"../../src" -I"../../../src" -I"../src/time/include" -I"../src/net/include" -I"../src/include" -I"../src/mpfs/include" -I"../src/uart/include"  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/659862947/ip.o   ../src/net/ip.c  > ${OBJECTDIR}/_ext/659862947/ip.err 2>&1 ; if [ $$? -eq 0 ] ; then cat ${OBJECTDIR}/_ext/659862947/ip.err | sed 's/\(^.*:.*:\)\(Warning\)\(.*$$\)/\1 \2:\3/g' ; else cat ${OBJECTDIR}/_ext/659862947/ip.err | sed 's/\(^.*:.*:\)\(Error\)\(.*$$\)/\1 \2:\3/g' ; exit 1 ; fi
	${MP_CPP}  -MMD ${OBJECTDIR}/_ext/659862947/ip.o.temp ../src/net/ip.c __temp_cpp_output__ -D MINIPIC10T -D __18F2620 -D __18CXX -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\src -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\Ethernet.X\\../../src -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\Ethernet.X\\../../../src -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\Ethernet.X\\../src/time/include -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\src\\net\\include -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\src\\include -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\src\\mpfs\\include -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\Ethernet.X\\../src/uart/include -I C:\\Program\ Files\ \(x86\)\\Microchip\\mplabc18\\v3.40\\bin/../h  -D__18F2620
	printf "%s/" ${OBJECTDIR}/_ext/659862947 > ${OBJECTDIR}/_ext/659862947/ip.o.d
ifneq (,$(findstring MINGW32,$(OS_CURRENT)))
	cat ${OBJECTDIR}/_ext/659862947/ip.o.temp | sed -e 's/\\\ /__SPACES__/g' -e's/\\$$/__EOL__/g' -e 's/\\/\//g' -e 's/__SPACES__/\\\ /g' -e 's/__EOL__/\\/g' >> ${OBJECTDIR}/_ext/659862947/ip.o.d
else
	cat ${OBJECTDIR}/_ext/659862947/ip.o.temp >> ${OBJECTDIR}/_ext/659862947/ip.o.d
endif
	${RM} __temp_cpp_output__
${OBJECTDIR}/_ext/1360937237/mpfsimg.o: ../src/mpfsimg.c  nbproject/Makefile-${CND_CONF}.mk
	${RM} ${OBJECTDIR}/_ext/1360937237/mpfsimg.o.d 
	${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD2=1 -p$(MP_PROCESSOR_OPTION) -k -sco -DMINIPIC10T -I"../src" -I"../../src" -I"../../../src" -I"../src/time/include" -I"../src/net/include" -I"../src/include" -I"../src/mpfs/include" -I"../src/uart/include"  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1360937237/mpfsimg.o   ../src/mpfsimg.c  > ${OBJECTDIR}/_ext/1360937237/mpfsimg.err 2>&1 ; if [ $$? -eq 0 ] ; then cat ${OBJECTDIR}/_ext/1360937237/mpfsimg.err | sed 's/\(^.*:.*:\)\(Warning\)\(.*$$\)/\1 \2:\3/g' ; else cat ${OBJECTDIR}/_ext/1360937237/mpfsimg.err | sed 's/\(^.*:.*:\)\(Error\)\(.*$$\)/\1 \2:\3/g' ; exit 1 ; fi
	${MP_CPP}  -MMD ${OBJECTDIR}/_ext/1360937237/mpfsimg.o.temp ../src/mpfsimg.c __temp_cpp_output__ -D MINIPIC10T -D __18F2620 -D __18CXX -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\src -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\Ethernet.X\\../../src -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\Ethernet.X\\../../../src -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\Ethernet.X\\../src/time/include -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\src\\net\\include -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\src\\include -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\src\\mpfs\\include -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\Ethernet.X\\../src/uart/include -I C:\\Program\ Files\ \(x86\)\\Microchip\\mplabc18\\v3.40\\bin/../h  -D__18F2620
	printf "%s/" ${OBJECTDIR}/_ext/1360937237 > ${OBJECTDIR}/_ext/1360937237/mpfsimg.o.d
ifneq (,$(findstring MINGW32,$(OS_CURRENT)))
	cat ${OBJECTDIR}/_ext/1360937237/mpfsimg.o.temp | sed -e 's/\\\ /__SPACES__/g' -e's/\\$$/__EOL__/g' -e 's/\\/\//g' -e 's/__SPACES__/\\\ /g' -e 's/__EOL__/\\/g' >> ${OBJECTDIR}/_ext/1360937237/mpfsimg.o.d
else
	cat ${OBJECTDIR}/_ext/1360937237/mpfsimg.o.temp >> ${OBJECTDIR}/_ext/1360937237/mpfsimg.o.d
endif
	${RM} __temp_cpp_output__
${OBJECTDIR}/_ext/659862947/tcp.o: ../src/net/tcp.c  nbproject/Makefile-${CND_CONF}.mk
	${RM} ${OBJECTDIR}/_ext/659862947/tcp.o.d 
	${MKDIR} ${OBJECTDIR}/_ext/659862947 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD2=1 -p$(MP_PROCESSOR_OPTION) -k -sco -DMINIPIC10T -I"../src" -I"../../src" -I"../../../src" -I"../src/time/include" -I"../src/net/include" -I"../src/include" -I"../src/mpfs/include" -I"../src/uart/include"  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/659862947/tcp.o   ../src/net/tcp.c  > ${OBJECTDIR}/_ext/659862947/tcp.err 2>&1 ; if [ $$? -eq 0 ] ; then cat ${OBJECTDIR}/_ext/659862947/tcp.err | sed 's/\(^.*:.*:\)\(Warning\)\(.*$$\)/\1 \2:\3/g' ; else cat ${OBJECTDIR}/_ext/659862947/tcp.err | sed 's/\(^.*:.*:\)\(Error\)\(.*$$\)/\1 \2:\3/g' ; exit 1 ; fi
	${MP_CPP}  -MMD ${OBJECTDIR}/_ext/659862947/tcp.o.temp ../src/net/tcp.c __temp_cpp_output__ -D MINIPIC10T -D __18F2620 -D __18CXX -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\src -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\Ethernet.X\\../../src -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\Ethernet.X\\../../../src -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\Ethernet.X\\../src/time/include -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\src\\net\\include -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\src\\include -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\src\\mpfs\\include -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\Ethernet.X\\../src/uart/include -I C:\\Program\ Files\ \(x86\)\\Microchip\\mplabc18\\v3.40\\bin/../h  -D__18F2620
	printf "%s/" ${OBJECTDIR}/_ext/659862947 > ${OBJECTDIR}/_ext/659862947/tcp.o.d
ifneq (,$(findstring MINGW32,$(OS_CURRENT)))
	cat ${OBJECTDIR}/_ext/659862947/tcp.o.temp | sed -e 's/\\\ /__SPACES__/g' -e's/\\$$/__EOL__/g' -e 's/\\/\//g' -e 's/__SPACES__/\\\ /g' -e 's/__EOL__/\\/g' >> ${OBJECTDIR}/_ext/659862947/tcp.o.d
else
	cat ${OBJECTDIR}/_ext/659862947/tcp.o.temp >> ${OBJECTDIR}/_ext/659862947/tcp.o.d
endif
	${RM} __temp_cpp_output__
${OBJECTDIR}/_ext/659862947/icmpd.o: ../src/net/icmpd.c  nbproject/Makefile-${CND_CONF}.mk
	${RM} ${OBJECTDIR}/_ext/659862947/icmpd.o.d 
	${MKDIR} ${OBJECTDIR}/_ext/659862947 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD2=1 -p$(MP_PROCESSOR_OPTION) -k -sco -DMINIPIC10T -I"../src" -I"../../src" -I"../../../src" -I"../src/time/include" -I"../src/net/include" -I"../src/include" -I"../src/mpfs/include" -I"../src/uart/include"  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/659862947/icmpd.o   ../src/net/icmpd.c  > ${OBJECTDIR}/_ext/659862947/icmpd.err 2>&1 ; if [ $$? -eq 0 ] ; then cat ${OBJECTDIR}/_ext/659862947/icmpd.err | sed 's/\(^.*:.*:\)\(Warning\)\(.*$$\)/\1 \2:\3/g' ; else cat ${OBJECTDIR}/_ext/659862947/icmpd.err | sed 's/\(^.*:.*:\)\(Error\)\(.*$$\)/\1 \2:\3/g' ; exit 1 ; fi
	${MP_CPP}  -MMD ${OBJECTDIR}/_ext/659862947/icmpd.o.temp ../src/net/icmpd.c __temp_cpp_output__ -D MINIPIC10T -D __18F2620 -D __18CXX -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\src -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\Ethernet.X\\../../src -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\Ethernet.X\\../../../src -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\Ethernet.X\\../src/time/include -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\src\\net\\include -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\src\\include -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\src\\mpfs\\include -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\Ethernet.X\\../src/uart/include -I C:\\Program\ Files\ \(x86\)\\Microchip\\mplabc18\\v3.40\\bin/../h  -D__18F2620
	printf "%s/" ${OBJECTDIR}/_ext/659862947 > ${OBJECTDIR}/_ext/659862947/icmpd.o.d
ifneq (,$(findstring MINGW32,$(OS_CURRENT)))
	cat ${OBJECTDIR}/_ext/659862947/icmpd.o.temp | sed -e 's/\\\ /__SPACES__/g' -e's/\\$$/__EOL__/g' -e 's/\\/\//g' -e 's/__SPACES__/\\\ /g' -e 's/__EOL__/\\/g' >> ${OBJECTDIR}/_ext/659862947/icmpd.o.d
else
	cat ${OBJECTDIR}/_ext/659862947/icmpd.o.temp >> ${OBJECTDIR}/_ext/659862947/icmpd.o.d
endif
	${RM} __temp_cpp_output__
${OBJECTDIR}/_ext/659862947/arp.o: ../src/net/arp.c  nbproject/Makefile-${CND_CONF}.mk
	${RM} ${OBJECTDIR}/_ext/659862947/arp.o.d 
	${MKDIR} ${OBJECTDIR}/_ext/659862947 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD2=1 -p$(MP_PROCESSOR_OPTION) -k -sco -DMINIPIC10T -I"../src" -I"../../src" -I"../../../src" -I"../src/time/include" -I"../src/net/include" -I"../src/include" -I"../src/mpfs/include" -I"../src/uart/include"  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/659862947/arp.o   ../src/net/arp.c  > ${OBJECTDIR}/_ext/659862947/arp.err 2>&1 ; if [ $$? -eq 0 ] ; then cat ${OBJECTDIR}/_ext/659862947/arp.err | sed 's/\(^.*:.*:\)\(Warning\)\(.*$$\)/\1 \2:\3/g' ; else cat ${OBJECTDIR}/_ext/659862947/arp.err | sed 's/\(^.*:.*:\)\(Error\)\(.*$$\)/\1 \2:\3/g' ; exit 1 ; fi
	${MP_CPP}  -MMD ${OBJECTDIR}/_ext/659862947/arp.o.temp ../src/net/arp.c __temp_cpp_output__ -D MINIPIC10T -D __18F2620 -D __18CXX -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\src -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\Ethernet.X\\../../src -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\Ethernet.X\\../../../src -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\Ethernet.X\\../src/time/include -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\src\\net\\include -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\src\\include -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\src\\mpfs\\include -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\Ethernet.X\\../src/uart/include -I C:\\Program\ Files\ \(x86\)\\Microchip\\mplabc18\\v3.40\\bin/../h  -D__18F2620
	printf "%s/" ${OBJECTDIR}/_ext/659862947 > ${OBJECTDIR}/_ext/659862947/arp.o.d
ifneq (,$(findstring MINGW32,$(OS_CURRENT)))
	cat ${OBJECTDIR}/_ext/659862947/arp.o.temp | sed -e 's/\\\ /__SPACES__/g' -e's/\\$$/__EOL__/g' -e 's/\\/\//g' -e 's/__SPACES__/\\\ /g' -e 's/__EOL__/\\/g' >> ${OBJECTDIR}/_ext/659862947/arp.o.d
else
	cat ${OBJECTDIR}/_ext/659862947/arp.o.temp >> ${OBJECTDIR}/_ext/659862947/arp.o.d
endif
	${RM} __temp_cpp_output__
${OBJECTDIR}/_ext/1360937237/main.o: ../src/main.c  nbproject/Makefile-${CND_CONF}.mk
	${RM} ${OBJECTDIR}/_ext/1360937237/main.o.d 
	${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD2=1 -p$(MP_PROCESSOR_OPTION) -k -sco -DMINIPIC10T -I"../src" -I"../../src" -I"../../../src" -I"../src/time/include" -I"../src/net/include" -I"../src/include" -I"../src/mpfs/include" -I"../src/uart/include"  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1360937237/main.o   ../src/main.c  > ${OBJECTDIR}/_ext/1360937237/main.err 2>&1 ; if [ $$? -eq 0 ] ; then cat ${OBJECTDIR}/_ext/1360937237/main.err | sed 's/\(^.*:.*:\)\(Warning\)\(.*$$\)/\1 \2:\3/g' ; else cat ${OBJECTDIR}/_ext/1360937237/main.err | sed 's/\(^.*:.*:\)\(Error\)\(.*$$\)/\1 \2:\3/g' ; exit 1 ; fi
	${MP_CPP}  -MMD ${OBJECTDIR}/_ext/1360937237/main.o.temp ../src/main.c __temp_cpp_output__ -D MINIPIC10T -D __18F2620 -D __18CXX -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\src -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\Ethernet.X\\../../src -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\Ethernet.X\\../../../src -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\Ethernet.X\\../src/time/include -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\src\\net\\include -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\src\\include -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\src\\mpfs\\include -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\Ethernet.X\\../src/uart/include -I C:\\Program\ Files\ \(x86\)\\Microchip\\mplabc18\\v3.40\\bin/../h  -D__18F2620
	printf "%s/" ${OBJECTDIR}/_ext/1360937237 > ${OBJECTDIR}/_ext/1360937237/main.o.d
ifneq (,$(findstring MINGW32,$(OS_CURRENT)))
	cat ${OBJECTDIR}/_ext/1360937237/main.o.temp | sed -e 's/\\\ /__SPACES__/g' -e's/\\$$/__EOL__/g' -e 's/\\/\//g' -e 's/__SPACES__/\\\ /g' -e 's/__EOL__/\\/g' >> ${OBJECTDIR}/_ext/1360937237/main.o.d
else
	cat ${OBJECTDIR}/_ext/1360937237/main.o.temp >> ${OBJECTDIR}/_ext/1360937237/main.o.d
endif
	${RM} __temp_cpp_output__
else
${OBJECTDIR}/_ext/1360937237/delay.o: ../src/delay.c  nbproject/Makefile-${CND_CONF}.mk
	${RM} ${OBJECTDIR}/_ext/1360937237/delay.o.d 
	${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -k -sco -DMINIPIC10T -I"../src" -I"../../src" -I"../../../src" -I"../src/time/include" -I"../src/net/include" -I"../src/include" -I"../src/mpfs/include" -I"../src/uart/include"  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1360937237/delay.o   ../src/delay.c  > ${OBJECTDIR}/_ext/1360937237/delay.err 2>&1 ; if [ $$? -eq 0 ] ; then cat ${OBJECTDIR}/_ext/1360937237/delay.err | sed 's/\(^.*:.*:\)\(Warning\)\(.*$$\)/\1 \2:\3/g' ; else cat ${OBJECTDIR}/_ext/1360937237/delay.err | sed 's/\(^.*:.*:\)\(Error\)\(.*$$\)/\1 \2:\3/g' ; exit 1 ; fi
	${MP_CPP}  -MMD ${OBJECTDIR}/_ext/1360937237/delay.o.temp ../src/delay.c __temp_cpp_output__ -D MINIPIC10T -D __18F2620 -D __18CXX -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\src -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\Ethernet.X\\../../src -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\Ethernet.X\\../../../src -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\Ethernet.X\\../src/time/include -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\src\\net\\include -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\src\\include -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\src\\mpfs\\include -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\Ethernet.X\\../src/uart/include -I C:\\Program\ Files\ \(x86\)\\Microchip\\mplabc18\\v3.40\\bin/../h  -D__18F2620
	printf "%s/" ${OBJECTDIR}/_ext/1360937237 > ${OBJECTDIR}/_ext/1360937237/delay.o.d
ifneq (,$(findstring MINGW32,$(OS_CURRENT)))
	cat ${OBJECTDIR}/_ext/1360937237/delay.o.temp | sed -e 's/\\\ /__SPACES__/g' -e's/\\$$/__EOL__/g' -e 's/\\/\//g' -e 's/__SPACES__/\\\ /g' -e 's/__EOL__/\\/g' >> ${OBJECTDIR}/_ext/1360937237/delay.o.d
else
	cat ${OBJECTDIR}/_ext/1360937237/delay.o.temp >> ${OBJECTDIR}/_ext/1360937237/delay.o.d
endif
	${RM} __temp_cpp_output__
${OBJECTDIR}/_ext/659862947/dns.o: ../src/net/dns.c  nbproject/Makefile-${CND_CONF}.mk
	${RM} ${OBJECTDIR}/_ext/659862947/dns.o.d 
	${MKDIR} ${OBJECTDIR}/_ext/659862947 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -k -sco -DMINIPIC10T -I"../src" -I"../../src" -I"../../../src" -I"../src/time/include" -I"../src/net/include" -I"../src/include" -I"../src/mpfs/include" -I"../src/uart/include"  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/659862947/dns.o   ../src/net/dns.c  > ${OBJECTDIR}/_ext/659862947/dns.err 2>&1 ; if [ $$? -eq 0 ] ; then cat ${OBJECTDIR}/_ext/659862947/dns.err | sed 's/\(^.*:.*:\)\(Warning\)\(.*$$\)/\1 \2:\3/g' ; else cat ${OBJECTDIR}/_ext/659862947/dns.err | sed 's/\(^.*:.*:\)\(Error\)\(.*$$\)/\1 \2:\3/g' ; exit 1 ; fi
	${MP_CPP}  -MMD ${OBJECTDIR}/_ext/659862947/dns.o.temp ../src/net/dns.c __temp_cpp_output__ -D MINIPIC10T -D __18F2620 -D __18CXX -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\src -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\Ethernet.X\\../../src -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\Ethernet.X\\../../../src -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\Ethernet.X\\../src/time/include -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\src\\net\\include -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\src\\include -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\src\\mpfs\\include -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\Ethernet.X\\../src/uart/include -I C:\\Program\ Files\ \(x86\)\\Microchip\\mplabc18\\v3.40\\bin/../h  -D__18F2620
	printf "%s/" ${OBJECTDIR}/_ext/659862947 > ${OBJECTDIR}/_ext/659862947/dns.o.d
ifneq (,$(findstring MINGW32,$(OS_CURRENT)))
	cat ${OBJECTDIR}/_ext/659862947/dns.o.temp | sed -e 's/\\\ /__SPACES__/g' -e's/\\$$/__EOL__/g' -e 's/\\/\//g' -e 's/__SPACES__/\\\ /g' -e 's/__EOL__/\\/g' >> ${OBJECTDIR}/_ext/659862947/dns.o.d
else
	cat ${OBJECTDIR}/_ext/659862947/dns.o.temp >> ${OBJECTDIR}/_ext/659862947/dns.o.d
endif
	${RM} __temp_cpp_output__
${OBJECTDIR}/_ext/659862947/nbns.o: ../src/net/nbns.c  nbproject/Makefile-${CND_CONF}.mk
	${RM} ${OBJECTDIR}/_ext/659862947/nbns.o.d 
	${MKDIR} ${OBJECTDIR}/_ext/659862947 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -k -sco -DMINIPIC10T -I"../src" -I"../../src" -I"../../../src" -I"../src/time/include" -I"../src/net/include" -I"../src/include" -I"../src/mpfs/include" -I"../src/uart/include"  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/659862947/nbns.o   ../src/net/nbns.c  > ${OBJECTDIR}/_ext/659862947/nbns.err 2>&1 ; if [ $$? -eq 0 ] ; then cat ${OBJECTDIR}/_ext/659862947/nbns.err | sed 's/\(^.*:.*:\)\(Warning\)\(.*$$\)/\1 \2:\3/g' ; else cat ${OBJECTDIR}/_ext/659862947/nbns.err | sed 's/\(^.*:.*:\)\(Error\)\(.*$$\)/\1 \2:\3/g' ; exit 1 ; fi
	${MP_CPP}  -MMD ${OBJECTDIR}/_ext/659862947/nbns.o.temp ../src/net/nbns.c __temp_cpp_output__ -D MINIPIC10T -D __18F2620 -D __18CXX -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\src -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\Ethernet.X\\../../src -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\Ethernet.X\\../../../src -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\Ethernet.X\\../src/time/include -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\src\\net\\include -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\src\\include -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\src\\mpfs\\include -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\Ethernet.X\\../src/uart/include -I C:\\Program\ Files\ \(x86\)\\Microchip\\mplabc18\\v3.40\\bin/../h  -D__18F2620
	printf "%s/" ${OBJECTDIR}/_ext/659862947 > ${OBJECTDIR}/_ext/659862947/nbns.o.d
ifneq (,$(findstring MINGW32,$(OS_CURRENT)))
	cat ${OBJECTDIR}/_ext/659862947/nbns.o.temp | sed -e 's/\\\ /__SPACES__/g' -e's/\\$$/__EOL__/g' -e 's/\\/\//g' -e 's/__SPACES__/\\\ /g' -e 's/__EOL__/\\/g' >> ${OBJECTDIR}/_ext/659862947/nbns.o.d
else
	cat ${OBJECTDIR}/_ext/659862947/nbns.o.temp >> ${OBJECTDIR}/_ext/659862947/nbns.o.d
endif
	${RM} __temp_cpp_output__
${OBJECTDIR}/_ext/659862947/udp.o: ../src/net/udp.c  nbproject/Makefile-${CND_CONF}.mk
	${RM} ${OBJECTDIR}/_ext/659862947/udp.o.d 
	${MKDIR} ${OBJECTDIR}/_ext/659862947 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -k -sco -DMINIPIC10T -I"../src" -I"../../src" -I"../../../src" -I"../src/time/include" -I"../src/net/include" -I"../src/include" -I"../src/mpfs/include" -I"../src/uart/include"  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/659862947/udp.o   ../src/net/udp.c  > ${OBJECTDIR}/_ext/659862947/udp.err 2>&1 ; if [ $$? -eq 0 ] ; then cat ${OBJECTDIR}/_ext/659862947/udp.err | sed 's/\(^.*:.*:\)\(Warning\)\(.*$$\)/\1 \2:\3/g' ; else cat ${OBJECTDIR}/_ext/659862947/udp.err | sed 's/\(^.*:.*:\)\(Error\)\(.*$$\)/\1 \2:\3/g' ; exit 1 ; fi
	${MP_CPP}  -MMD ${OBJECTDIR}/_ext/659862947/udp.o.temp ../src/net/udp.c __temp_cpp_output__ -D MINIPIC10T -D __18F2620 -D __18CXX -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\src -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\Ethernet.X\\../../src -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\Ethernet.X\\../../../src -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\Ethernet.X\\../src/time/include -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\src\\net\\include -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\src\\include -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\src\\mpfs\\include -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\Ethernet.X\\../src/uart/include -I C:\\Program\ Files\ \(x86\)\\Microchip\\mplabc18\\v3.40\\bin/../h  -D__18F2620
	printf "%s/" ${OBJECTDIR}/_ext/659862947 > ${OBJECTDIR}/_ext/659862947/udp.o.d
ifneq (,$(findstring MINGW32,$(OS_CURRENT)))
	cat ${OBJECTDIR}/_ext/659862947/udp.o.temp | sed -e 's/\\\ /__SPACES__/g' -e's/\\$$/__EOL__/g' -e 's/\\/\//g' -e 's/__SPACES__/\\\ /g' -e 's/__EOL__/\\/g' >> ${OBJECTDIR}/_ext/659862947/udp.o.d
else
	cat ${OBJECTDIR}/_ext/659862947/udp.o.temp >> ${OBJECTDIR}/_ext/659862947/udp.o.d
endif
	${RM} __temp_cpp_output__
${OBJECTDIR}/_ext/659862947/helpers.o: ../src/net/helpers.c  nbproject/Makefile-${CND_CONF}.mk
	${RM} ${OBJECTDIR}/_ext/659862947/helpers.o.d 
	${MKDIR} ${OBJECTDIR}/_ext/659862947 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -k -sco -DMINIPIC10T -I"../src" -I"../../src" -I"../../../src" -I"../src/time/include" -I"../src/net/include" -I"../src/include" -I"../src/mpfs/include" -I"../src/uart/include"  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/659862947/helpers.o   ../src/net/helpers.c  > ${OBJECTDIR}/_ext/659862947/helpers.err 2>&1 ; if [ $$? -eq 0 ] ; then cat ${OBJECTDIR}/_ext/659862947/helpers.err | sed 's/\(^.*:.*:\)\(Warning\)\(.*$$\)/\1 \2:\3/g' ; else cat ${OBJECTDIR}/_ext/659862947/helpers.err | sed 's/\(^.*:.*:\)\(Error\)\(.*$$\)/\1 \2:\3/g' ; exit 1 ; fi
	${MP_CPP}  -MMD ${OBJECTDIR}/_ext/659862947/helpers.o.temp ../src/net/helpers.c __temp_cpp_output__ -D MINIPIC10T -D __18F2620 -D __18CXX -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\src -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\Ethernet.X\\../../src -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\Ethernet.X\\../../../src -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\Ethernet.X\\../src/time/include -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\src\\net\\include -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\src\\include -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\src\\mpfs\\include -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\Ethernet.X\\../src/uart/include -I C:\\Program\ Files\ \(x86\)\\Microchip\\mplabc18\\v3.40\\bin/../h  -D__18F2620
	printf "%s/" ${OBJECTDIR}/_ext/659862947 > ${OBJECTDIR}/_ext/659862947/helpers.o.d
ifneq (,$(findstring MINGW32,$(OS_CURRENT)))
	cat ${OBJECTDIR}/_ext/659862947/helpers.o.temp | sed -e 's/\\\ /__SPACES__/g' -e's/\\$$/__EOL__/g' -e 's/\\/\//g' -e 's/__SPACES__/\\\ /g' -e 's/__EOL__/\\/g' >> ${OBJECTDIR}/_ext/659862947/helpers.o.d
else
	cat ${OBJECTDIR}/_ext/659862947/helpers.o.temp >> ${OBJECTDIR}/_ext/659862947/helpers.o.d
endif
	${RM} __temp_cpp_output__
${OBJECTDIR}/_ext/1019104662/mpfs.o: ../src/mpfs/mpfs.c  nbproject/Makefile-${CND_CONF}.mk
	${RM} ${OBJECTDIR}/_ext/1019104662/mpfs.o.d 
	${MKDIR} ${OBJECTDIR}/_ext/1019104662 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -k -sco -DMINIPIC10T -I"../src" -I"../../src" -I"../../../src" -I"../src/time/include" -I"../src/net/include" -I"../src/include" -I"../src/mpfs/include" -I"../src/uart/include"  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1019104662/mpfs.o   ../src/mpfs/mpfs.c  > ${OBJECTDIR}/_ext/1019104662/mpfs.err 2>&1 ; if [ $$? -eq 0 ] ; then cat ${OBJECTDIR}/_ext/1019104662/mpfs.err | sed 's/\(^.*:.*:\)\(Warning\)\(.*$$\)/\1 \2:\3/g' ; else cat ${OBJECTDIR}/_ext/1019104662/mpfs.err | sed 's/\(^.*:.*:\)\(Error\)\(.*$$\)/\1 \2:\3/g' ; exit 1 ; fi
	${MP_CPP}  -MMD ${OBJECTDIR}/_ext/1019104662/mpfs.o.temp ../src/mpfs/mpfs.c __temp_cpp_output__ -D MINIPIC10T -D __18F2620 -D __18CXX -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\src -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\Ethernet.X\\../../src -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\Ethernet.X\\../../../src -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\Ethernet.X\\../src/time/include -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\src\\net\\include -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\src\\include -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\src\\mpfs\\include -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\Ethernet.X\\../src/uart/include -I C:\\Program\ Files\ \(x86\)\\Microchip\\mplabc18\\v3.40\\bin/../h  -D__18F2620
	printf "%s/" ${OBJECTDIR}/_ext/1019104662 > ${OBJECTDIR}/_ext/1019104662/mpfs.o.d
ifneq (,$(findstring MINGW32,$(OS_CURRENT)))
	cat ${OBJECTDIR}/_ext/1019104662/mpfs.o.temp | sed -e 's/\\\ /__SPACES__/g' -e's/\\$$/__EOL__/g' -e 's/\\/\//g' -e 's/__SPACES__/\\\ /g' -e 's/__EOL__/\\/g' >> ${OBJECTDIR}/_ext/1019104662/mpfs.o.d
else
	cat ${OBJECTDIR}/_ext/1019104662/mpfs.o.temp >> ${OBJECTDIR}/_ext/1019104662/mpfs.o.d
endif
	${RM} __temp_cpp_output__
${OBJECTDIR}/_ext/659862947/tick.o: ../src/net/tick.c  nbproject/Makefile-${CND_CONF}.mk
	${RM} ${OBJECTDIR}/_ext/659862947/tick.o.d 
	${MKDIR} ${OBJECTDIR}/_ext/659862947 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -k -sco -DMINIPIC10T -I"../src" -I"../../src" -I"../../../src" -I"../src/time/include" -I"../src/net/include" -I"../src/include" -I"../src/mpfs/include" -I"../src/uart/include"  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/659862947/tick.o   ../src/net/tick.c  > ${OBJECTDIR}/_ext/659862947/tick.err 2>&1 ; if [ $$? -eq 0 ] ; then cat ${OBJECTDIR}/_ext/659862947/tick.err | sed 's/\(^.*:.*:\)\(Warning\)\(.*$$\)/\1 \2:\3/g' ; else cat ${OBJECTDIR}/_ext/659862947/tick.err | sed 's/\(^.*:.*:\)\(Error\)\(.*$$\)/\1 \2:\3/g' ; exit 1 ; fi
	${MP_CPP}  -MMD ${OBJECTDIR}/_ext/659862947/tick.o.temp ../src/net/tick.c __temp_cpp_output__ -D MINIPIC10T -D __18F2620 -D __18CXX -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\src -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\Ethernet.X\\../../src -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\Ethernet.X\\../../../src -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\Ethernet.X\\../src/time/include -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\src\\net\\include -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\src\\include -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\src\\mpfs\\include -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\Ethernet.X\\../src/uart/include -I C:\\Program\ Files\ \(x86\)\\Microchip\\mplabc18\\v3.40\\bin/../h  -D__18F2620
	printf "%s/" ${OBJECTDIR}/_ext/659862947 > ${OBJECTDIR}/_ext/659862947/tick.o.d
ifneq (,$(findstring MINGW32,$(OS_CURRENT)))
	cat ${OBJECTDIR}/_ext/659862947/tick.o.temp | sed -e 's/\\\ /__SPACES__/g' -e's/\\$$/__EOL__/g' -e 's/\\/\//g' -e 's/__SPACES__/\\\ /g' -e 's/__EOL__/\\/g' >> ${OBJECTDIR}/_ext/659862947/tick.o.d
else
	cat ${OBJECTDIR}/_ext/659862947/tick.o.temp >> ${OBJECTDIR}/_ext/659862947/tick.o.d
endif
	${RM} __temp_cpp_output__
${OBJECTDIR}/_ext/659862947/dhcp.o: ../src/net/dhcp.c  nbproject/Makefile-${CND_CONF}.mk
	${RM} ${OBJECTDIR}/_ext/659862947/dhcp.o.d 
	${MKDIR} ${OBJECTDIR}/_ext/659862947 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -k -sco -DMINIPIC10T -I"../src" -I"../../src" -I"../../../src" -I"../src/time/include" -I"../src/net/include" -I"../src/include" -I"../src/mpfs/include" -I"../src/uart/include"  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/659862947/dhcp.o   ../src/net/dhcp.c  > ${OBJECTDIR}/_ext/659862947/dhcp.err 2>&1 ; if [ $$? -eq 0 ] ; then cat ${OBJECTDIR}/_ext/659862947/dhcp.err | sed 's/\(^.*:.*:\)\(Warning\)\(.*$$\)/\1 \2:\3/g' ; else cat ${OBJECTDIR}/_ext/659862947/dhcp.err | sed 's/\(^.*:.*:\)\(Error\)\(.*$$\)/\1 \2:\3/g' ; exit 1 ; fi
	${MP_CPP}  -MMD ${OBJECTDIR}/_ext/659862947/dhcp.o.temp ../src/net/dhcp.c __temp_cpp_output__ -D MINIPIC10T -D __18F2620 -D __18CXX -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\src -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\Ethernet.X\\../../src -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\Ethernet.X\\../../../src -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\Ethernet.X\\../src/time/include -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\src\\net\\include -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\src\\include -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\src\\mpfs\\include -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\Ethernet.X\\../src/uart/include -I C:\\Program\ Files\ \(x86\)\\Microchip\\mplabc18\\v3.40\\bin/../h  -D__18F2620
	printf "%s/" ${OBJECTDIR}/_ext/659862947 > ${OBJECTDIR}/_ext/659862947/dhcp.o.d
ifneq (,$(findstring MINGW32,$(OS_CURRENT)))
	cat ${OBJECTDIR}/_ext/659862947/dhcp.o.temp | sed -e 's/\\\ /__SPACES__/g' -e's/\\$$/__EOL__/g' -e 's/\\/\//g' -e 's/__SPACES__/\\\ /g' -e 's/__EOL__/\\/g' >> ${OBJECTDIR}/_ext/659862947/dhcp.o.d
else
	cat ${OBJECTDIR}/_ext/659862947/dhcp.o.temp >> ${OBJECTDIR}/_ext/659862947/dhcp.o.d
endif
	${RM} __temp_cpp_output__
${OBJECTDIR}/_ext/659862947/enc28j60.o: ../src/net/enc28j60.c  nbproject/Makefile-${CND_CONF}.mk
	${RM} ${OBJECTDIR}/_ext/659862947/enc28j60.o.d 
	${MKDIR} ${OBJECTDIR}/_ext/659862947 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -k -sco -DMINIPIC10T -I"../src" -I"../../src" -I"../../../src" -I"../src/time/include" -I"../src/net/include" -I"../src/include" -I"../src/mpfs/include" -I"../src/uart/include"  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/659862947/enc28j60.o   ../src/net/enc28j60.c  > ${OBJECTDIR}/_ext/659862947/enc28j60.err 2>&1 ; if [ $$? -eq 0 ] ; then cat ${OBJECTDIR}/_ext/659862947/enc28j60.err | sed 's/\(^.*:.*:\)\(Warning\)\(.*$$\)/\1 \2:\3/g' ; else cat ${OBJECTDIR}/_ext/659862947/enc28j60.err | sed 's/\(^.*:.*:\)\(Error\)\(.*$$\)/\1 \2:\3/g' ; exit 1 ; fi
	${MP_CPP}  -MMD ${OBJECTDIR}/_ext/659862947/enc28j60.o.temp ../src/net/enc28j60.c __temp_cpp_output__ -D MINIPIC10T -D __18F2620 -D __18CXX -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\src -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\Ethernet.X\\../../src -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\Ethernet.X\\../../../src -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\Ethernet.X\\../src/time/include -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\src\\net\\include -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\src\\include -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\src\\mpfs\\include -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\Ethernet.X\\../src/uart/include -I C:\\Program\ Files\ \(x86\)\\Microchip\\mplabc18\\v3.40\\bin/../h  -D__18F2620
	printf "%s/" ${OBJECTDIR}/_ext/659862947 > ${OBJECTDIR}/_ext/659862947/enc28j60.o.d
ifneq (,$(findstring MINGW32,$(OS_CURRENT)))
	cat ${OBJECTDIR}/_ext/659862947/enc28j60.o.temp | sed -e 's/\\\ /__SPACES__/g' -e's/\\$$/__EOL__/g' -e 's/\\/\//g' -e 's/__SPACES__/\\\ /g' -e 's/__EOL__/\\/g' >> ${OBJECTDIR}/_ext/659862947/enc28j60.o.d
else
	cat ${OBJECTDIR}/_ext/659862947/enc28j60.o.temp >> ${OBJECTDIR}/_ext/659862947/enc28j60.o.d
endif
	${RM} __temp_cpp_output__
${OBJECTDIR}/_ext/659862947/httpd.o: ../src/net/httpd.c  nbproject/Makefile-${CND_CONF}.mk
	${RM} ${OBJECTDIR}/_ext/659862947/httpd.o.d 
	${MKDIR} ${OBJECTDIR}/_ext/659862947 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -k -sco -DMINIPIC10T -I"../src" -I"../../src" -I"../../../src" -I"../src/time/include" -I"../src/net/include" -I"../src/include" -I"../src/mpfs/include" -I"../src/uart/include"  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/659862947/httpd.o   ../src/net/httpd.c  > ${OBJECTDIR}/_ext/659862947/httpd.err 2>&1 ; if [ $$? -eq 0 ] ; then cat ${OBJECTDIR}/_ext/659862947/httpd.err | sed 's/\(^.*:.*:\)\(Warning\)\(.*$$\)/\1 \2:\3/g' ; else cat ${OBJECTDIR}/_ext/659862947/httpd.err | sed 's/\(^.*:.*:\)\(Error\)\(.*$$\)/\1 \2:\3/g' ; exit 1 ; fi
	${MP_CPP}  -MMD ${OBJECTDIR}/_ext/659862947/httpd.o.temp ../src/net/httpd.c __temp_cpp_output__ -D MINIPIC10T -D __18F2620 -D __18CXX -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\src -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\Ethernet.X\\../../src -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\Ethernet.X\\../../../src -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\Ethernet.X\\../src/time/include -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\src\\net\\include -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\src\\include -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\src\\mpfs\\include -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\Ethernet.X\\../src/uart/include -I C:\\Program\ Files\ \(x86\)\\Microchip\\mplabc18\\v3.40\\bin/../h  -D__18F2620
	printf "%s/" ${OBJECTDIR}/_ext/659862947 > ${OBJECTDIR}/_ext/659862947/httpd.o.d
ifneq (,$(findstring MINGW32,$(OS_CURRENT)))
	cat ${OBJECTDIR}/_ext/659862947/httpd.o.temp | sed -e 's/\\\ /__SPACES__/g' -e's/\\$$/__EOL__/g' -e 's/\\/\//g' -e 's/__SPACES__/\\\ /g' -e 's/__EOL__/\\/g' >> ${OBJECTDIR}/_ext/659862947/httpd.o.d
else
	cat ${OBJECTDIR}/_ext/659862947/httpd.o.temp >> ${OBJECTDIR}/_ext/659862947/httpd.o.d
endif
	${RM} __temp_cpp_output__
${OBJECTDIR}/_ext/659862947/stacktsk.o: ../src/net/stacktsk.c  nbproject/Makefile-${CND_CONF}.mk
	${RM} ${OBJECTDIR}/_ext/659862947/stacktsk.o.d 
	${MKDIR} ${OBJECTDIR}/_ext/659862947 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -k -sco -DMINIPIC10T -I"../src" -I"../../src" -I"../../../src" -I"../src/time/include" -I"../src/net/include" -I"../src/include" -I"../src/mpfs/include" -I"../src/uart/include"  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/659862947/stacktsk.o   ../src/net/stacktsk.c  > ${OBJECTDIR}/_ext/659862947/stacktsk.err 2>&1 ; if [ $$? -eq 0 ] ; then cat ${OBJECTDIR}/_ext/659862947/stacktsk.err | sed 's/\(^.*:.*:\)\(Warning\)\(.*$$\)/\1 \2:\3/g' ; else cat ${OBJECTDIR}/_ext/659862947/stacktsk.err | sed 's/\(^.*:.*:\)\(Error\)\(.*$$\)/\1 \2:\3/g' ; exit 1 ; fi
	${MP_CPP}  -MMD ${OBJECTDIR}/_ext/659862947/stacktsk.o.temp ../src/net/stacktsk.c __temp_cpp_output__ -D MINIPIC10T -D __18F2620 -D __18CXX -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\src -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\Ethernet.X\\../../src -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\Ethernet.X\\../../../src -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\Ethernet.X\\../src/time/include -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\src\\net\\include -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\src\\include -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\src\\mpfs\\include -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\Ethernet.X\\../src/uart/include -I C:\\Program\ Files\ \(x86\)\\Microchip\\mplabc18\\v3.40\\bin/../h  -D__18F2620
	printf "%s/" ${OBJECTDIR}/_ext/659862947 > ${OBJECTDIR}/_ext/659862947/stacktsk.o.d
ifneq (,$(findstring MINGW32,$(OS_CURRENT)))
	cat ${OBJECTDIR}/_ext/659862947/stacktsk.o.temp | sed -e 's/\\\ /__SPACES__/g' -e's/\\$$/__EOL__/g' -e 's/\\/\//g' -e 's/__SPACES__/\\\ /g' -e 's/__EOL__/\\/g' >> ${OBJECTDIR}/_ext/659862947/stacktsk.o.d
else
	cat ${OBJECTDIR}/_ext/659862947/stacktsk.o.temp >> ${OBJECTDIR}/_ext/659862947/stacktsk.o.d
endif
	${RM} __temp_cpp_output__
${OBJECTDIR}/_ext/659862947/ip.o: ../src/net/ip.c  nbproject/Makefile-${CND_CONF}.mk
	${RM} ${OBJECTDIR}/_ext/659862947/ip.o.d 
	${MKDIR} ${OBJECTDIR}/_ext/659862947 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -k -sco -DMINIPIC10T -I"../src" -I"../../src" -I"../../../src" -I"../src/time/include" -I"../src/net/include" -I"../src/include" -I"../src/mpfs/include" -I"../src/uart/include"  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/659862947/ip.o   ../src/net/ip.c  > ${OBJECTDIR}/_ext/659862947/ip.err 2>&1 ; if [ $$? -eq 0 ] ; then cat ${OBJECTDIR}/_ext/659862947/ip.err | sed 's/\(^.*:.*:\)\(Warning\)\(.*$$\)/\1 \2:\3/g' ; else cat ${OBJECTDIR}/_ext/659862947/ip.err | sed 's/\(^.*:.*:\)\(Error\)\(.*$$\)/\1 \2:\3/g' ; exit 1 ; fi
	${MP_CPP}  -MMD ${OBJECTDIR}/_ext/659862947/ip.o.temp ../src/net/ip.c __temp_cpp_output__ -D MINIPIC10T -D __18F2620 -D __18CXX -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\src -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\Ethernet.X\\../../src -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\Ethernet.X\\../../../src -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\Ethernet.X\\../src/time/include -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\src\\net\\include -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\src\\include -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\src\\mpfs\\include -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\Ethernet.X\\../src/uart/include -I C:\\Program\ Files\ \(x86\)\\Microchip\\mplabc18\\v3.40\\bin/../h  -D__18F2620
	printf "%s/" ${OBJECTDIR}/_ext/659862947 > ${OBJECTDIR}/_ext/659862947/ip.o.d
ifneq (,$(findstring MINGW32,$(OS_CURRENT)))
	cat ${OBJECTDIR}/_ext/659862947/ip.o.temp | sed -e 's/\\\ /__SPACES__/g' -e's/\\$$/__EOL__/g' -e 's/\\/\//g' -e 's/__SPACES__/\\\ /g' -e 's/__EOL__/\\/g' >> ${OBJECTDIR}/_ext/659862947/ip.o.d
else
	cat ${OBJECTDIR}/_ext/659862947/ip.o.temp >> ${OBJECTDIR}/_ext/659862947/ip.o.d
endif
	${RM} __temp_cpp_output__
${OBJECTDIR}/_ext/1360937237/mpfsimg.o: ../src/mpfsimg.c  nbproject/Makefile-${CND_CONF}.mk
	${RM} ${OBJECTDIR}/_ext/1360937237/mpfsimg.o.d 
	${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -k -sco -DMINIPIC10T -I"../src" -I"../../src" -I"../../../src" -I"../src/time/include" -I"../src/net/include" -I"../src/include" -I"../src/mpfs/include" -I"../src/uart/include"  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1360937237/mpfsimg.o   ../src/mpfsimg.c  > ${OBJECTDIR}/_ext/1360937237/mpfsimg.err 2>&1 ; if [ $$? -eq 0 ] ; then cat ${OBJECTDIR}/_ext/1360937237/mpfsimg.err | sed 's/\(^.*:.*:\)\(Warning\)\(.*$$\)/\1 \2:\3/g' ; else cat ${OBJECTDIR}/_ext/1360937237/mpfsimg.err | sed 's/\(^.*:.*:\)\(Error\)\(.*$$\)/\1 \2:\3/g' ; exit 1 ; fi
	${MP_CPP}  -MMD ${OBJECTDIR}/_ext/1360937237/mpfsimg.o.temp ../src/mpfsimg.c __temp_cpp_output__ -D MINIPIC10T -D __18F2620 -D __18CXX -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\src -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\Ethernet.X\\../../src -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\Ethernet.X\\../../../src -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\Ethernet.X\\../src/time/include -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\src\\net\\include -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\src\\include -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\src\\mpfs\\include -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\Ethernet.X\\../src/uart/include -I C:\\Program\ Files\ \(x86\)\\Microchip\\mplabc18\\v3.40\\bin/../h  -D__18F2620
	printf "%s/" ${OBJECTDIR}/_ext/1360937237 > ${OBJECTDIR}/_ext/1360937237/mpfsimg.o.d
ifneq (,$(findstring MINGW32,$(OS_CURRENT)))
	cat ${OBJECTDIR}/_ext/1360937237/mpfsimg.o.temp | sed -e 's/\\\ /__SPACES__/g' -e's/\\$$/__EOL__/g' -e 's/\\/\//g' -e 's/__SPACES__/\\\ /g' -e 's/__EOL__/\\/g' >> ${OBJECTDIR}/_ext/1360937237/mpfsimg.o.d
else
	cat ${OBJECTDIR}/_ext/1360937237/mpfsimg.o.temp >> ${OBJECTDIR}/_ext/1360937237/mpfsimg.o.d
endif
	${RM} __temp_cpp_output__
${OBJECTDIR}/_ext/659862947/tcp.o: ../src/net/tcp.c  nbproject/Makefile-${CND_CONF}.mk
	${RM} ${OBJECTDIR}/_ext/659862947/tcp.o.d 
	${MKDIR} ${OBJECTDIR}/_ext/659862947 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -k -sco -DMINIPIC10T -I"../src" -I"../../src" -I"../../../src" -I"../src/time/include" -I"../src/net/include" -I"../src/include" -I"../src/mpfs/include" -I"../src/uart/include"  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/659862947/tcp.o   ../src/net/tcp.c  > ${OBJECTDIR}/_ext/659862947/tcp.err 2>&1 ; if [ $$? -eq 0 ] ; then cat ${OBJECTDIR}/_ext/659862947/tcp.err | sed 's/\(^.*:.*:\)\(Warning\)\(.*$$\)/\1 \2:\3/g' ; else cat ${OBJECTDIR}/_ext/659862947/tcp.err | sed 's/\(^.*:.*:\)\(Error\)\(.*$$\)/\1 \2:\3/g' ; exit 1 ; fi
	${MP_CPP}  -MMD ${OBJECTDIR}/_ext/659862947/tcp.o.temp ../src/net/tcp.c __temp_cpp_output__ -D MINIPIC10T -D __18F2620 -D __18CXX -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\src -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\Ethernet.X\\../../src -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\Ethernet.X\\../../../src -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\Ethernet.X\\../src/time/include -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\src\\net\\include -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\src\\include -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\src\\mpfs\\include -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\Ethernet.X\\../src/uart/include -I C:\\Program\ Files\ \(x86\)\\Microchip\\mplabc18\\v3.40\\bin/../h  -D__18F2620
	printf "%s/" ${OBJECTDIR}/_ext/659862947 > ${OBJECTDIR}/_ext/659862947/tcp.o.d
ifneq (,$(findstring MINGW32,$(OS_CURRENT)))
	cat ${OBJECTDIR}/_ext/659862947/tcp.o.temp | sed -e 's/\\\ /__SPACES__/g' -e's/\\$$/__EOL__/g' -e 's/\\/\//g' -e 's/__SPACES__/\\\ /g' -e 's/__EOL__/\\/g' >> ${OBJECTDIR}/_ext/659862947/tcp.o.d
else
	cat ${OBJECTDIR}/_ext/659862947/tcp.o.temp >> ${OBJECTDIR}/_ext/659862947/tcp.o.d
endif
	${RM} __temp_cpp_output__
${OBJECTDIR}/_ext/659862947/icmpd.o: ../src/net/icmpd.c  nbproject/Makefile-${CND_CONF}.mk
	${RM} ${OBJECTDIR}/_ext/659862947/icmpd.o.d 
	${MKDIR} ${OBJECTDIR}/_ext/659862947 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -k -sco -DMINIPIC10T -I"../src" -I"../../src" -I"../../../src" -I"../src/time/include" -I"../src/net/include" -I"../src/include" -I"../src/mpfs/include" -I"../src/uart/include"  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/659862947/icmpd.o   ../src/net/icmpd.c  > ${OBJECTDIR}/_ext/659862947/icmpd.err 2>&1 ; if [ $$? -eq 0 ] ; then cat ${OBJECTDIR}/_ext/659862947/icmpd.err | sed 's/\(^.*:.*:\)\(Warning\)\(.*$$\)/\1 \2:\3/g' ; else cat ${OBJECTDIR}/_ext/659862947/icmpd.err | sed 's/\(^.*:.*:\)\(Error\)\(.*$$\)/\1 \2:\3/g' ; exit 1 ; fi
	${MP_CPP}  -MMD ${OBJECTDIR}/_ext/659862947/icmpd.o.temp ../src/net/icmpd.c __temp_cpp_output__ -D MINIPIC10T -D __18F2620 -D __18CXX -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\src -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\Ethernet.X\\../../src -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\Ethernet.X\\../../../src -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\Ethernet.X\\../src/time/include -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\src\\net\\include -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\src\\include -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\src\\mpfs\\include -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\Ethernet.X\\../src/uart/include -I C:\\Program\ Files\ \(x86\)\\Microchip\\mplabc18\\v3.40\\bin/../h  -D__18F2620
	printf "%s/" ${OBJECTDIR}/_ext/659862947 > ${OBJECTDIR}/_ext/659862947/icmpd.o.d
ifneq (,$(findstring MINGW32,$(OS_CURRENT)))
	cat ${OBJECTDIR}/_ext/659862947/icmpd.o.temp | sed -e 's/\\\ /__SPACES__/g' -e's/\\$$/__EOL__/g' -e 's/\\/\//g' -e 's/__SPACES__/\\\ /g' -e 's/__EOL__/\\/g' >> ${OBJECTDIR}/_ext/659862947/icmpd.o.d
else
	cat ${OBJECTDIR}/_ext/659862947/icmpd.o.temp >> ${OBJECTDIR}/_ext/659862947/icmpd.o.d
endif
	${RM} __temp_cpp_output__
${OBJECTDIR}/_ext/659862947/arp.o: ../src/net/arp.c  nbproject/Makefile-${CND_CONF}.mk
	${RM} ${OBJECTDIR}/_ext/659862947/arp.o.d 
	${MKDIR} ${OBJECTDIR}/_ext/659862947 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -k -sco -DMINIPIC10T -I"../src" -I"../../src" -I"../../../src" -I"../src/time/include" -I"../src/net/include" -I"../src/include" -I"../src/mpfs/include" -I"../src/uart/include"  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/659862947/arp.o   ../src/net/arp.c  > ${OBJECTDIR}/_ext/659862947/arp.err 2>&1 ; if [ $$? -eq 0 ] ; then cat ${OBJECTDIR}/_ext/659862947/arp.err | sed 's/\(^.*:.*:\)\(Warning\)\(.*$$\)/\1 \2:\3/g' ; else cat ${OBJECTDIR}/_ext/659862947/arp.err | sed 's/\(^.*:.*:\)\(Error\)\(.*$$\)/\1 \2:\3/g' ; exit 1 ; fi
	${MP_CPP}  -MMD ${OBJECTDIR}/_ext/659862947/arp.o.temp ../src/net/arp.c __temp_cpp_output__ -D MINIPIC10T -D __18F2620 -D __18CXX -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\src -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\Ethernet.X\\../../src -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\Ethernet.X\\../../../src -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\Ethernet.X\\../src/time/include -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\src\\net\\include -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\src\\include -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\src\\mpfs\\include -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\Ethernet.X\\../src/uart/include -I C:\\Program\ Files\ \(x86\)\\Microchip\\mplabc18\\v3.40\\bin/../h  -D__18F2620
	printf "%s/" ${OBJECTDIR}/_ext/659862947 > ${OBJECTDIR}/_ext/659862947/arp.o.d
ifneq (,$(findstring MINGW32,$(OS_CURRENT)))
	cat ${OBJECTDIR}/_ext/659862947/arp.o.temp | sed -e 's/\\\ /__SPACES__/g' -e's/\\$$/__EOL__/g' -e 's/\\/\//g' -e 's/__SPACES__/\\\ /g' -e 's/__EOL__/\\/g' >> ${OBJECTDIR}/_ext/659862947/arp.o.d
else
	cat ${OBJECTDIR}/_ext/659862947/arp.o.temp >> ${OBJECTDIR}/_ext/659862947/arp.o.d
endif
	${RM} __temp_cpp_output__
${OBJECTDIR}/_ext/1360937237/main.o: ../src/main.c  nbproject/Makefile-${CND_CONF}.mk
	${RM} ${OBJECTDIR}/_ext/1360937237/main.o.d 
	${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -k -sco -DMINIPIC10T -I"../src" -I"../../src" -I"../../../src" -I"../src/time/include" -I"../src/net/include" -I"../src/include" -I"../src/mpfs/include" -I"../src/uart/include"  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1360937237/main.o   ../src/main.c  > ${OBJECTDIR}/_ext/1360937237/main.err 2>&1 ; if [ $$? -eq 0 ] ; then cat ${OBJECTDIR}/_ext/1360937237/main.err | sed 's/\(^.*:.*:\)\(Warning\)\(.*$$\)/\1 \2:\3/g' ; else cat ${OBJECTDIR}/_ext/1360937237/main.err | sed 's/\(^.*:.*:\)\(Error\)\(.*$$\)/\1 \2:\3/g' ; exit 1 ; fi
	${MP_CPP}  -MMD ${OBJECTDIR}/_ext/1360937237/main.o.temp ../src/main.c __temp_cpp_output__ -D MINIPIC10T -D __18F2620 -D __18CXX -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\src -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\Ethernet.X\\../../src -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\Ethernet.X\\../../../src -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\Ethernet.X\\../src/time/include -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\src\\net\\include -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\src\\include -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\src\\mpfs\\include -I C:\\Users\\Rahul\\Documents\\Projects\\SVN\\PIC\\Ethernet\\Ethernet.X\\../src/uart/include -I C:\\Program\ Files\ \(x86\)\\Microchip\\mplabc18\\v3.40\\bin/../h  -D__18F2620
	printf "%s/" ${OBJECTDIR}/_ext/1360937237 > ${OBJECTDIR}/_ext/1360937237/main.o.d
ifneq (,$(findstring MINGW32,$(OS_CURRENT)))
	cat ${OBJECTDIR}/_ext/1360937237/main.o.temp | sed -e 's/\\\ /__SPACES__/g' -e's/\\$$/__EOL__/g' -e 's/\\/\//g' -e 's/__SPACES__/\\\ /g' -e 's/__EOL__/\\/g' >> ${OBJECTDIR}/_ext/1360937237/main.o.d
else
	cat ${OBJECTDIR}/_ext/1360937237/main.o.temp >> ${OBJECTDIR}/_ext/1360937237/main.o.d
endif
	${RM} __temp_cpp_output__
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/Ethernet.X.${IMAGE_TYPE}.cof: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_LD} $(MP_EXTRA_LD_PRE) ../linker/18f2620.lkr  -p$(MP_PROCESSOR_OPTION_LD)  -w -x -u_DEBUG -l"../../../../../../../Program Files/Microchip/MCC18/lib"  -z__MPLAB_BUILD=1  -u_CRUNTIME -z__MPLAB_DEBUG=1 -z__MPLAB_DEBUGGER_ICD2=1 $(MP_LINKER_DEBUG_OPTION) -l ${MP_CC_DIR}\\..\\lib  -odist/${CND_CONF}/${IMAGE_TYPE}/Ethernet.X.${IMAGE_TYPE}.cof ${OBJECTFILES}      
else
dist/${CND_CONF}/${IMAGE_TYPE}/Ethernet.X.${IMAGE_TYPE}.cof: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_LD} $(MP_EXTRA_LD_PRE) ../linker/18f2620.lkr  -p$(MP_PROCESSOR_OPTION_LD)  -w  -l"../../../../../../../Program Files/Microchip/MCC18/lib"  -z__MPLAB_BUILD=1  -u_CRUNTIME -l ${MP_CC_DIR}\\..\\lib  -odist/${CND_CONF}/${IMAGE_TYPE}/Ethernet.X.${IMAGE_TYPE}.cof ${OBJECTFILES}      
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
