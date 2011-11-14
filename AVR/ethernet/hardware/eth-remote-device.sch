v 20040111 1
C 36400 24600 1 0 0 gnd-1.sym
C 37100 25900 1 270 0 vccarrow-1.sym
{
T 37600 25700 5 10 1 1 0 0 1
value=3V3
}
T 27300 26700 9 16 1 0 0 0 1
Ethernet remote device controller/sensor
T 22600 16400 9 12 1 0 0 0 2
(C) Guido Socher, tuxgraphics.org
http://tuxgraphics.org/electronics/
C 36300 25800 1 270 0 capacitor-2.sym
{
T 36100 25600 5 10 1 1 0 0 1
refdes=C1
T 36000 25000 5 10 1 1 0 0 1
value=10uF
T 36300 25800 5 10 0 1 0 0 1
footprint=RADIAL_CAN 200
}
C 23600 19100 1 0 0 ATMEGA-88DIP_ph.sym
{
T 25900 25000 5 10 1 1 0 6 1
refdes=U1
T 23800 18800 5 10 1 1 0 0 1
value=ATMEGA88
T 23600 19100 5 10 0 1 0 0 1
footprint=DIP28N
}
C 21100 25600 1 0 0 vccarrow-1.sym
{
T 21100 26100 5 10 1 1 0 0 1
value=3V3
}
C 21300 25600 1 90 1 resistor-2.sym
{
T 21600 24600 5 10 1 1 0 6 1
refdes=R1
T 21400 24900 5 10 1 1 270 6 1
value=10K
T 21300 25600 5 10 0 1 0 2 1
footprint=R0w4
}
C 26200 21400 1 270 0 vccarrow-1.sym
C 26500 22000 1 90 0 gnd-1.sym
C 23300 21800 1 270 0 gnd-1.sym
C 23600 22000 1 90 0 vccarrow-1.sym
{
T 23200 22100 5 10 1 1 180 0 1
value=3V3
}
C 26900 20600 1 180 1 resistor-2.sym
{
T 28000 20600 5 10 1 1 0 6 1
refdes=R2
T 27100 20600 5 10 1 1 180 6 1
value=270
T 26900 20600 5 10 0 1 90 2 1
footprint=R0w4
}
C 29000 18400 1 180 0 connector5-1.sym
{
T 29000 19100 5 10 1 1 180 0 1
refdes=CONN1
T 29000 18700 5 10 1 1 180 0 1
value=firmware_IN
T 29000 18400 5 10 0 1 0 0 1
footprint=CONNECTOR 5 1
}
C 27000 18300 1 270 0 gnd-1.sym
T 28000 18000 9 10 1 0 0 0 1
SCK
T 28000 17700 9 10 1 0 0 0 1
MISO
T 28000 17400 9 10 1 0 0 0 1
MOSI
T 28000 17100 9 10 1 0 0 0 1
Reset
T 28000 18300 9 10 1 0 0 0 1
GND
N 26200 20500 26900 20500 4
N 26800 20900 26800 17900 4
N 26800 17900 27300 17900 4
N 26600 20500 26600 17600 4
N 26600 17600 27300 17600 4
N 26400 17300 27300 17300 4
N 21200 17000 27300 17000 4
N 26400 20100 26400 17300 4
C 36900 25800 1 270 0 capacitor-1.sym
{
T 37700 25500 5 10 1 1 180 0 1
refdes=C2
T 38500 25200 5 10 1 1 180 0 1
value=100nF or 47nF
T 36900 25800 5 10 0 1 90 0 1
footprint=C100
}
C 31500 18300 1 0 0 enc28j60_ph.sym
{
T 33800 24200 5 10 1 1 0 6 1
refdes=U2
}
C 35000 21500 1 270 1 crystal-1.sym
{
T 35300 21700 5 10 1 1 90 2 1
refdes=U3
T 34200 22000 5 10 1 1 180 6 1
value=25MHz
T 35000 21500 5 10 0 1 90 2 1
footprint=R0w8
}
C 36000 21300 1 0 1 capacitor-1.sym
{
T 35900 21900 5 10 1 1 270 2 1
refdes=C3
T 35700 21400 5 10 1 1 180 6 1
value=18pF
T 36000 21300 5 10 0 1 180 6 1
footprint=C100
}
C 36000 22000 1 0 1 capacitor-1.sym
{
T 35900 22600 5 10 1 1 270 2 1
refdes=C4
T 35700 22100 5 10 1 1 180 6 1
value=18pF
T 36000 22000 5 10 0 1 180 6 1
footprint=C100
}
C 36300 21600 1 90 1 gnd-1.sym
C 36300 22300 1 90 1 gnd-1.sym
N 34700 22100 34700 22200 4
N 34700 22200 35100 22200 4
N 34100 21700 34700 21700 4
N 34700 21700 34700 21500 4
N 34700 21500 35100 21500 4
C 31500 23900 1 180 0 capacitor-2.sym
{
T 30700 24100 5 10 1 1 270 0 1
refdes=C5
T 30700 23500 5 10 1 1 270 0 1
value=10uF
T 31500 23900 5 10 0 1 270 0 1
footprint=RADIAL_CAN 200
}
C 30300 23800 1 270 0 gnd-1.sym
C 31200 23400 1 270 0 gnd-1.sym
C 34100 23800 1 270 0 vccarrow-1.sym
{
T 34500 23600 5 10 1 1 0 0 1
value=3V3
}
C 35200 22800 1 0 1 resistor-2.sym
{
T 35400 23000 5 10 1 1 0 6 1
refdes=R3
T 34200 22800 5 10 1 1 180 6 1
value=270
T 35200 22800 5 10 0 1 270 2 1
footprint=R0w8
}
N 34100 22900 34300 22900 4
C 35000 23200 1 0 1 resistor-2.sym
{
T 35200 23400 5 10 1 1 0 6 1
refdes=R4
T 34100 23200 5 10 1 1 180 6 1
value=270
T 35000 23200 5 10 0 1 270 2 1
footprint=R0w8
}
C 31400 17600 1 270 1 resistor-2.sym
{
T 31400 18700 5 10 1 1 90 6 1
refdes=R5
T 32000 17900 5 10 1 1 0 6 1
value=2K7
T 31400 17600 5 10 0 1 180 2 1
footprint=R0w8
}
C 35900 17400 1 270 1 resistor-4.sym
{
T 36200 17500 5 10 1 1 90 2 1
refdes=R6
T 35600 17600 5 10 1 1 0 0 1
value=50
T 35900 17400 5 10 0 1 0 0 1
footprint=R0w8
}
C 35900 16800 1 270 1 resistor-4.sym
{
T 36200 16900 5 10 1 1 90 2 1
refdes=R7
T 35600 16900 5 10 1 1 0 0 1
value=50
T 35900 16800 5 10 0 1 0 0 1
footprint=R0w8
}
C 35100 17100 1 0 0 capacitor-1.sym
{
T 35200 17700 5 10 1 1 270 0 1
refdes=C6
T 35400 17200 5 10 1 1 180 0 1
value=10nF
T 35100 17100 5 10 0 1 180 0 1
footprint=C100
}
C 34800 17400 1 270 0 gnd-1.sym
N 36000 17400 36000 17200 4
C 35500 19200 1 270 1 resistor-4.sym
{
T 35800 19300 5 10 1 1 90 2 1
refdes=R8
T 35200 19400 5 10 1 1 0 0 1
value=50
T 35500 19200 5 10 0 1 0 0 1
footprint=R0w8
}
C 34700 18900 1 0 0 capacitor-1.sym
{
T 34800 19500 5 10 1 1 270 0 1
refdes=C7
T 35000 19000 5 10 1 1 180 0 1
value=10nF
T 34700 18900 5 10 0 1 180 0 1
footprint=C100
}
C 35500 18600 1 270 1 resistor-4.sym
{
T 35800 18700 5 10 1 1 90 2 1
refdes=R9
T 35200 18700 5 10 1 1 0 0 1
value=50
T 35500 18600 5 10 0 1 0 0 1
footprint=R0w8
}
C 34400 19200 1 270 0 gnd-1.sym
N 34100 19300 34500 19300 4
N 36000 19800 36000 19100 4
N 35600 19000 35600 19200 4
N 36300 18600 34500 18600 4
N 34500 18600 34500 18900 4
N 34500 18900 34100 18900 4
N 34500 19600 36300 19600 4
N 34500 19600 34500 19300 4
C 35900 20800 1 0 0 vccarrow-1.sym
{
T 36200 20900 5 10 1 1 0 0 1
value=3V3
}
C 31400 17300 1 0 0 gnd-1.sym
N 26200 20900 31500 20900 4
N 26200 20100 29000 20100 4
N 29000 20100 29000 21300 4
N 29000 21300 31500 21300 4
N 27800 20500 28600 20500 4
N 28600 20500 28600 21700 4
N 28600 21700 31500 21700 4
N 31500 18900 30800 18900 4
N 30800 18900 30800 17200 4
N 30800 17200 33200 17200 4
N 33200 17200 33200 17800 4
N 33200 17800 36300 17800 4
N 31500 19300 30400 19300 4
N 30400 19300 30400 16800 4
N 30400 16800 36300 16800 4
N 26200 19700 29500 19700 4
N 29500 20500 31500 20500 4
N 21200 24500 23600 24500 4
C 31800 25300 1 0 0 connector2-1.sym
{
T 31800 26100 5 10 1 1 0 0 1
refdes=CONN2
T 31400 25000 5 10 1 1 0 0 1
value=RawDC-IN (5-9V)
T 31800 25300 5 10 0 1 0 0 1
footprint=CONNECTOR 2 1
}
N 31500 22500 30200 22500 4
N 30200 22500 30200 26200 4
N 30200 26200 22300 26200 4
N 22300 26200 22300 23300 4
N 22300 23300 23600 23300 4
N 21200 17000 21200 24700 4
N 29900 19300 29900 20100 4
N 29900 20100 31500 20100 4
C 34400 21400 1 90 1 gnd-1.sym
C 34400 19800 1 90 1 gnd-1.sym
C 34400 21000 1 90 1 gnd-1.sym
C 31200 19800 1 270 0 gnd-1.sym
C 34100 20200 1 270 0 vccarrow-1.sym
{
T 34500 20000 5 10 1 1 0 0 1
value=3V3
}
C 34100 20600 1 270 0 vccarrow-1.sym
{
T 34500 20400 5 10 1 1 0 0 1
value=3V3
}
C 34100 18600 1 270 0 vccarrow-1.sym
{
T 34000 18200 5 10 1 1 0 0 1
value=3V3
}
C 34100 22600 1 270 0 vccarrow-1.sym
{
T 34500 22400 5 10 1 1 0 0 1
value=3V3
}
N 34100 22100 34700 22100 4
C 20100 21300 1 0 0 gnd-1.sym
C 20100 18200 1 0 0 gnd-1.sym
C 21500 18900 1 0 0 resistor-2.sym
{
T 22500 18600 5 10 1 1 270 8 1
refdes=R10
T 22200 18800 5 10 1 1 180 0 1
value=1K
T 21500 18900 5 10 0 1 270 0 1
footprint=R0w8
}
N 22400 19000 22800 19000 4
N 22800 19000 22800 19700 4
N 22800 19700 23600 19700 4
N 20800 19000 21500 19000 4
C 19300 19300 1 0 0 diode-1.sym
{
T 19600 19800 5 10 1 1 0 0 1
refdes=D1
T 19300 19300 5 10 0 1 0 0 1
footprint=ALF300
T 18800 19600 5 10 1 1 0 0 1
value=BAY69
}
C 19200 19200 1 0 0 gnd-1.sym
C 26200 22600 1 180 1 resistor-2.sym
{
T 27300 22600 5 10 1 1 0 6 1
refdes=R11
T 26400 22600 5 10 1 1 180 6 1
value=1K
T 26200 22600 5 10 0 1 90 2 1
footprint=R0w8
}
C 26200 23000 1 180 1 resistor-2.sym
{
T 27300 23000 5 10 1 1 0 6 1
refdes=R12
T 26400 23000 5 10 1 1 180 6 1
value=1K
T 26200 23000 5 10 0 1 90 2 1
footprint=R0w8
}
C 26200 23400 1 180 1 resistor-2.sym
{
T 27300 23400 5 10 1 1 0 6 1
refdes=R13
T 26400 23400 5 10 1 1 180 6 1
value=1K
T 26200 23400 5 10 0 1 90 2 1
footprint=R0w8
}
C 27100 21500 1 0 1 capacitor-1.sym
{
T 27000 22100 5 10 1 1 270 2 1
refdes=C8
T 26800 21600 5 10 1 1 180 6 1
value=47nF or 100nF
T 27100 21500 5 10 0 1 180 6 1
footprint=C100
}
C 27400 21800 1 90 1 gnd-1.sym
C 29400 18100 1 270 1 resistor-2.sym
{
T 29100 19100 5 10 1 1 180 6 1
refdes=R14
T 29300 18800 5 10 1 1 90 6 1
value=10K
T 29400 18100 5 10 0 1 180 2 1
footprint=R0w4
}
C 29600 18100 1 180 0 vccarrow-1.sym
{
T 29600 17600 5 10 1 1 180 0 1
value=3V3
}
N 29500 19000 29500 20500 4
C 34400 25200 1 0 0 lm2937-33.sym
{
T 35800 26200 5 10 1 1 0 6 1
refdes=U4
T 34400 25200 5 10 0 1 0 0 1
footprint=TO220SW
}
N 33500 25800 34400 25800 4
N 33500 25500 33500 24900 4
N 33500 24900 37100 24900 4
N 35200 25200 35200 24900 4
N 36000 25800 37100 25800 4
C 33800 25800 1 0 0 vddarrow-1.sym
{
T 33400 26200 5 10 1 1 0 0 1
value=RAWDC
}
C 20100 20400 1 0 0 vddarrow-1.sym
{
T 19700 20800 5 10 1 1 0 0 1
value=RAWDC
}
N 29900 19300 27700 19300 4
N 27700 19300 27700 18600 4
N 27700 18600 23600 18600 4
N 23600 18600 23600 19300 4
C 23500 17700 1 270 1 resistor-2.sym
{
T 23200 18700 5 10 1 1 180 6 1
refdes=R15
T 23400 18400 5 10 1 1 90 6 1
value=10K
T 23500 17700 5 10 1 1 180 2 1
footprint=R0w8
}
C 23700 17700 1 180 0 vccarrow-1.sym
{
T 24200 17500 5 10 1 1 180 0 1
value=3V3
}
T 34600 17500 9 10 1 0 0 0 1
P8
T 35700 23000 9 10 1 0 0 0 1
B=Yellow
T 35500 23500 9 10 1 0 0 0 1
A=Green
C 33700 25800 1 270 0 capacitor-1.sym
{
T 34500 25500 5 10 1 1 180 0 1
refdes=C9
T 35300 25200 5 10 1 1 180 0 1
value=100nF or 47nF
T 33700 25800 5 10 0 1 90 0 1
footprint=C200
}
C 27900 23800 1 0 0 vccarrow-1.sym
{
T 27900 24200 5 10 1 1 0 0 1
value=3V3
}
C 25200 18100 1 180 1 led-2.sym
{
T 25500 18300 5 10 1 1 180 6 1
refdes=D2
T 25200 18100 5 10 0 1 180 6 1
footprint=LED 3
}
C 24300 17900 1 0 0 resistor-2.sym
{
T 24500 17800 5 10 1 1 0 8 1
refdes=R16
T 25000 17800 5 10 1 1 180 0 1
value=270
T 24300 17900 5 10 0 1 270 0 1
footprint=R0w4
}
N 26200 19300 26200 18000 4
N 26200 18000 26100 18000 4
N 23600 17700 23900 17700 4
N 23900 17700 23900 18000 4
N 23900 18000 24300 18000 4
C 31500 22000 1 90 0 testpt-1.sym
{
T 31100 22100 5 10 1 1 90 0 1
refdes=TP1
T 31500 22000 5 10 0 1 0 0 1
footprint=CONNECTOR 1 1
}
C 26900 25600 1 270 0 capacitor-1.sym
{
T 27700 25300 5 10 1 1 180 0 1
refdes=C10
T 28500 25000 5 10 1 1 180 0 1
value=100nF or 47nF
T 26900 25600 5 10 0 1 90 0 1
footprint=C100
}
C 27000 25600 1 0 0 vccarrow-1.sym
{
T 27700 25900 5 10 1 1 180 0 1
value=3V3
}
C 27000 24400 1 0 0 gnd-1.sym
C 18500 19900 1 0 0 connector2-1.sym
{
T 18500 20700 5 10 1 1 0 0 1
refdes=CONN3
T 18500 19900 5 10 0 1 0 0 1
footprint=CONNECTOR 2 1
}
N 20200 19500 20200 20100 4
C 18500 21400 1 0 0 connector9-1.sym
{
T 18600 24300 5 10 1 1 0 0 1
refdes=J1
T 19100 24100 5 10 1 1 0 0 1
value=IO-port
T 18500 21400 5 10 0 1 0 0 1
footprint=CONNECTOR 9 1
}
N 23600 20100 20600 20100 4
N 20600 20100 20600 21900 4
N 20200 21900 20600 21900 4
N 23600 20500 20800 20500 4
N 20800 20500 20800 22200 4
N 20800 22200 20200 22200 4
N 23600 20900 21000 20900 4
N 21000 20900 21000 22500 4
N 21000 22500 20200 22500 4
N 23600 21300 21400 21300 4
N 21400 21300 21400 22800 4
N 21400 22800 20200 22800 4
N 23600 22500 21600 22500 4
N 21600 22500 21600 23100 4
N 21600 23100 20200 23100 4
N 23600 22900 21800 22900 4
N 21800 22900 21800 23400 4
N 21800 23400 20200 23400 4
N 23600 23700 20200 23700 4
N 23600 24100 20600 24100 4
N 20600 24100 20600 24000 4
N 20200 24000 20600 24000 4
N 27100 23300 27900 23300 4
N 27900 23300 27900 23200 4
N 27900 23200 28000 23200 4
N 27100 22900 28000 22900 4
N 27100 22500 27900 22500 4
N 28000 22600 27900 22600 4
N 27900 22600 27900 22500 4
C 27700 22200 1 270 1 gnd-1.sym
C 29700 22100 1 0 1 connector6-1.sym
{
T 29600 24100 5 10 1 1 0 6 1
refdes=CONN4
T 28200 23900 5 10 1 1 0 0 1
value=Analog-IN
T 29700 22100 5 10 0 1 0 0 1
footprint=CONNECTOR 6 1
}
C 26200 23800 1 180 1 resistor-2.sym
{
T 27000 23900 5 10 1 1 0 6 1
refdes=R17
T 26400 23800 5 10 1 1 180 6 1
value=1K
T 26200 23800 5 10 0 1 90 2 1
footprint=R0w8
}
N 27100 23700 27600 23700 4
N 27600 23700 27600 23500 4
N 27600 23500 28000 23500 4
C 36100 19800 1 90 0 coil-2.sym
{
T 35800 20000 5 10 1 1 90 0 1
refdes=L1
T 36100 19800 5 10 0 1 0 0 1
footprint=R0w4
}
C 36800 15500 1 0 0 magjack.sym
{
T 38636 20970 5 10 1 1 0 0 1
refdes=T1
T 36800 15500 5 10 0 1 0 0 1
footprint=magjack08b01x1t03_pcb_element
}
C 38700 15200 1 0 1 gnd-1.sym
N 36300 17800 36300 17900 4
N 36300 17900 36800 17900 4
N 36800 16700 36300 16700 4
N 36300 16700 36300 16800 4
N 36300 18600 36300 18500 4
N 36300 18500 36800 18500 4
N 35600 19100 36800 19100 4
N 36300 19600 36300 19700 4
N 36300 19700 36800 19700 4
C 36500 16500 1 270 0 gnd-1.sym
C 36500 20600 1 270 0 gnd-1.sym
N 35200 22900 36400 22900 4
N 36400 22900 36400 20000 4
N 36400 20000 36800 20000 4
N 35000 23300 40100 23300 4
N 40100 23300 40100 15100 4
N 40100 15100 36700 15100 4
N 36700 15100 36700 15900 4
N 36700 15900 36800 15900 4
C 20800 18500 1 0 1 BC547-1.sym
{
T 19900 19000 5 10 1 1 0 6 1
refdes=Q1
T 20800 18500 5 10 0 1 0 0 1
footprint=TO92_BC5x7
T 19300 18500 5 10 1 1 0 0 1
value=BC548 
}
C 28500 25600 1 270 0 capacitor-1.sym
{
T 29300 25300 5 10 1 1 180 0 1
refdes=C11
T 30100 25000 5 10 1 1 180 0 1
value=100nF or 47nF
T 28500 25600 5 10 0 1 90 0 1
footprint=C100
}
N 27100 25600 28700 25600 4
N 28700 24700 27100 24700 4
