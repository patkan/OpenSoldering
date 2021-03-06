EESchema Schematic File Version 2
LIBS:i2c
LIBS:power
LIBS:device
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:special
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
LIBS:INA
LIBS:JBC-Lötkolbenmodul-cache
EELAYER 24 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 2 2
Title "Anzeigemodul für Temperatur und Status"
Date "03 Okt 2014"
Rev "0.1"
Comp "Höraufsche Elektrowerkstätten"
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L 74HC595 U201
U 1 1 542FC9F2
P 4900 2050
F 0 "U201" H 5050 2650 70  0000 C CNN
F 1 "74HC595" H 4900 1450 70  0000 C CNN
F 2 "SMD_Packages:SO-16-N" H 4900 2050 60  0001 C CNN
F 3 "" H 4900 2050 60  0000 C CNN
	1    4900 2050
	1    0    0    -1  
$EndComp
$Comp
L 74HC595 U202
U 1 1 542FCAE4
P 4900 3750
F 0 "U202" H 5050 4350 70  0000 C CNN
F 1 "74HC595" H 4900 3150 70  0000 C CNN
F 2 "SMD_Packages:SO-16-N" H 4900 3750 60  0001 C CNN
F 3 "" H 4900 3750 60  0000 C CNN
	1    4900 3750
	1    0    0    -1  
$EndComp
$Comp
L 74HC595 U203
U 1 1 542FCB7C
P 4900 5450
F 0 "U203" H 5050 6050 70  0000 C CNN
F 1 "74HC595" H 4900 4850 70  0000 C CNN
F 2 "SMD_Packages:SO-16-N" H 4900 5450 60  0001 C CNN
F 3 "" H 4900 5450 60  0000 C CNN
	1    4900 5450
	1    0    0    -1  
$EndComp
Text HLabel 1750 1600 0    60   Input ~ 0
seg_data
Text HLabel 1750 1700 0    60   Input ~ 0
seg_shift
Text HLabel 1750 1800 0    60   Input ~ 0
seg_latch
Wire Wire Line
	2700 1600 4200 1600
Wire Wire Line
	4200 3500 3900 3500
Wire Wire Line
	3900 1700 3900 5200
Connection ~ 3900 1800
Wire Wire Line
	3900 5200 4200 5200
Connection ~ 3900 3500
Wire Wire Line
	3850 5500 4200 5500
Wire Wire Line
	3850 1800 3850 5500
Connection ~ 3850 2100
Wire Wire Line
	4200 3800 3850 3800
Connection ~ 3850 3800
Wire Wire Line
	5600 2500 5600 2900
Wire Wire Line
	5600 2900 4200 2900
Wire Wire Line
	4200 2900 4200 3300
Wire Wire Line
	5600 4200 5600 4600
Wire Wire Line
	5600 4600 4200 4600
Wire Wire Line
	4200 4600 4200 5000
NoConn ~ 5600 5900
$Comp
L R_PACK4 RP201
U 1 1 542FD4DB
P 6100 1550
F 0 "RP201" H 6100 2000 40  0000 C CNN
F 1 "220" H 6100 1500 40  0000 C CNN
F 2 "Resistors_SMD:R_Cat16-4" H 6100 1550 60  0001 C CNN
F 3 "" H 6100 1550 60  0000 C CNN
	1    6100 1550
	1    0    0    1   
$EndComp
$Comp
L R_PACK4 RP202
U 1 1 542FD50A
P 6100 1950
F 0 "RP202" H 6100 2400 40  0000 C CNN
F 1 "220" H 6100 1900 40  0000 C CNN
F 2 "Resistors_SMD:R_Cat16-4" H 6100 1950 60  0001 C CNN
F 3 "" H 6100 1950 60  0000 C CNN
	1    6100 1950
	1    0    0    1   
$EndComp
Wire Wire Line
	5900 1600 5600 1600
Wire Wire Line
	5600 1700 5900 1700
Wire Wire Line
	5900 1800 5600 1800
Wire Wire Line
	5600 1900 5900 1900
Wire Wire Line
	5600 2000 5900 2000
Wire Wire Line
	5600 2100 5900 2100
Wire Wire Line
	5600 2200 5900 2200
Wire Wire Line
	5600 2300 5900 2300
$Comp
L 7SEGMENTS AFF201
U 1 1 542FD69A
P 7900 2000
F 0 "AFF201" H 7900 2550 60  0000 C CNN
F 1 "7SEGMENTS" H 7900 1550 60  0000 C CNN
F 2 "Sockets_DIP:DIP-10__300_ELL" H 7900 2000 60  0001 C CNN
F 3 "" H 7900 2000 60  0000 C CNN
	1    7900 2000
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR084
U 1 1 542FEFB4
P 1750 1900
F 0 "#PWR084" H 1750 1990 20  0001 C CNN
F 1 "+5V" H 1750 1990 30  0000 C CNN
F 2 "" H 1750 1900 60  0000 C CNN
F 3 "" H 1750 1900 60  0000 C CNN
	1    1750 1900
	0    -1   -1   0   
$EndComp
$Comp
L GND #PWR085
U 1 1 542FEFCF
P 1750 2000
F 0 "#PWR085" H 1750 2000 30  0001 C CNN
F 1 "GND" H 1750 1930 30  0001 C CNN
F 2 "" H 1750 2000 60  0000 C CNN
F 3 "" H 1750 2000 60  0000 C CNN
	1    1750 2000
	0    1    1    0   
$EndComp
Wire Wire Line
	1750 2000 1950 2000
Wire Wire Line
	1950 1900 1750 1900
Wire Wire Line
	1750 1800 1950 1800
Wire Wire Line
	1950 1700 1750 1700
Wire Wire Line
	1750 1600 1950 1600
Wire Wire Line
	2700 1700 3900 1700
Wire Wire Line
	3900 1800 4200 1800
Wire Wire Line
	3850 2100 4200 2100
Wire Wire Line
	3850 1800 2700 1800
Text Notes 1500 1350 0    60   ~ 0
Konnektor, damit die kleine Platine mit\nden 7-seg-Anzeigen von der Hauptplatine\nabgesetzt in die Frontplatte passt.
$Comp
L VDD #PWR086
U 1 1 543002A1
P 2700 1900
F 0 "#PWR086" H 2700 2000 30  0001 C CNN
F 1 "VDD" H 2700 2010 30  0000 C CNN
F 2 "" H 2700 1900 60  0000 C CNN
F 3 "" H 2700 1900 60  0000 C CNN
	1    2700 1900
	0    1    1    0   
$EndComp
$Comp
L VDD #PWR087
U 1 1 54300389
P 4600 1500
F 0 "#PWR087" H 4600 1600 30  0001 C CNN
F 1 "VDD" H 4600 1610 30  0000 C CNN
F 2 "" H 4600 1500 60  0000 C CNN
F 3 "" H 4600 1500 60  0000 C CNN
	1    4600 1500
	1    0    0    -1  
$EndComp
$Comp
L VDD #PWR088
U 1 1 543003A3
P 4200 1900
F 0 "#PWR088" H 4200 2000 30  0001 C CNN
F 1 "VDD" H 4200 2010 30  0000 C CNN
F 2 "" H 4200 1900 60  0000 C CNN
F 3 "" H 4200 1900 60  0000 C CNN
	1    4200 1900
	0    -1   -1   0   
$EndComp
$Comp
L VDD #PWR089
U 1 1 543003B6
P 4200 3600
F 0 "#PWR089" H 4200 3700 30  0001 C CNN
F 1 "VDD" H 4200 3710 30  0000 C CNN
F 2 "" H 4200 3600 60  0000 C CNN
F 3 "" H 4200 3600 60  0000 C CNN
	1    4200 3600
	0    -1   -1   0   
$EndComp
$Comp
L VDD #PWR090
U 1 1 54300739
P 4200 5300
F 0 "#PWR090" H 4200 5400 30  0001 C CNN
F 1 "VDD" H 4200 5410 30  0000 C CNN
F 2 "" H 4200 5300 60  0000 C CNN
F 3 "" H 4200 5300 60  0000 C CNN
	1    4200 5300
	0    -1   -1   0   
$EndComp
$Comp
L VDD #PWR091
U 1 1 5430074C
P 4600 3200
F 0 "#PWR091" H 4600 3300 30  0001 C CNN
F 1 "VDD" H 4600 3310 30  0000 C CNN
F 2 "" H 4600 3200 60  0000 C CNN
F 3 "" H 4600 3200 60  0000 C CNN
	1    4600 3200
	1    0    0    -1  
$EndComp
$Comp
L VDD #PWR092
U 1 1 5430075F
P 4600 4900
F 0 "#PWR092" H 4600 5000 30  0001 C CNN
F 1 "VDD" H 4600 5010 30  0000 C CNN
F 2 "" H 4600 4900 60  0000 C CNN
F 3 "" H 4600 4900 60  0000 C CNN
	1    4600 4900
	1    0    0    -1  
$EndComp
$Comp
L AGND #PWR093
U 1 1 5430076C
P 2700 2000
F 0 "#PWR093" H 2700 2000 40  0001 C CNN
F 1 "AGND" H 2700 1930 50  0000 C CNN
F 2 "" H 2700 2000 60  0000 C CNN
F 3 "" H 2700 2000 60  0000 C CNN
	1    2700 2000
	0    -1   -1   0   
$EndComp
$Comp
L AGND #PWR094
U 1 1 5430078E
P 4200 2200
F 0 "#PWR094" H 4200 2200 40  0001 C CNN
F 1 "AGND" H 4200 2130 50  0000 C CNN
F 2 "" H 4200 2200 60  0000 C CNN
F 3 "" H 4200 2200 60  0000 C CNN
	1    4200 2200
	0    1    1    0   
$EndComp
$Comp
L AGND #PWR095
U 1 1 543007A1
P 4200 3900
F 0 "#PWR095" H 4200 3900 40  0001 C CNN
F 1 "AGND" H 4200 3830 50  0000 C CNN
F 2 "" H 4200 3900 60  0000 C CNN
F 3 "" H 4200 3900 60  0000 C CNN
	1    4200 3900
	0    1    1    0   
$EndComp
$Comp
L AGND #PWR096
U 1 1 543007B4
P 4200 5600
F 0 "#PWR096" H 4200 5600 40  0001 C CNN
F 1 "AGND" H 4200 5530 50  0000 C CNN
F 2 "" H 4200 5600 60  0000 C CNN
F 3 "" H 4200 5600 60  0000 C CNN
	1    4200 5600
	0    1    1    0   
$EndComp
$Comp
L AGND #PWR097
U 1 1 54300820
P 4600 6000
F 0 "#PWR097" H 4600 6000 40  0001 C CNN
F 1 "AGND" H 4600 5930 50  0000 C CNN
F 2 "" H 4600 6000 60  0000 C CNN
F 3 "" H 4600 6000 60  0000 C CNN
	1    4600 6000
	1    0    0    -1  
$EndComp
$Comp
L AGND #PWR098
U 1 1 5430083B
P 4600 4300
F 0 "#PWR098" H 4600 4300 40  0001 C CNN
F 1 "AGND" H 4600 4230 50  0000 C CNN
F 2 "" H 4600 4300 60  0000 C CNN
F 3 "" H 4600 4300 60  0000 C CNN
	1    4600 4300
	1    0    0    -1  
$EndComp
$Comp
L AGND #PWR099
U 1 1 5430084E
P 4600 2600
F 0 "#PWR099" H 4600 2600 40  0001 C CNN
F 1 "AGND" H 4600 2530 50  0000 C CNN
F 2 "" H 4600 2600 60  0000 C CNN
F 3 "" H 4600 2600 60  0000 C CNN
	1    4600 2600
	1    0    0    -1  
$EndComp
$Comp
L C C201
U 1 1 54300A99
P 3600 2400
F 0 "C201" H 3600 2500 40  0000 L CNN
F 1 "100n" H 3606 2315 40  0000 L CNN
F 2 "Capacitors_SMD:C_0805" H 3638 2250 30  0001 C CNN
F 3 "" H 3600 2400 60  0000 C CNN
	1    3600 2400
	1    0    0    -1  
$EndComp
$Comp
L AGND #PWR0100
U 1 1 54300B1D
P 3600 2600
F 0 "#PWR0100" H 3600 2600 40  0001 C CNN
F 1 "AGND" H 3600 2530 50  0000 C CNN
F 2 "" H 3600 2600 60  0000 C CNN
F 3 "" H 3600 2600 60  0000 C CNN
	1    3600 2600
	1    0    0    -1  
$EndComp
$Comp
L VDD #PWR0101
U 1 1 54300B31
P 3600 2200
F 0 "#PWR0101" H 3600 2300 30  0001 C CNN
F 1 "VDD" H 3600 2310 30  0000 C CNN
F 2 "" H 3600 2200 60  0000 C CNN
F 3 "" H 3600 2200 60  0000 C CNN
	1    3600 2200
	1    0    0    -1  
$EndComp
$Comp
L C C202
U 1 1 54300B8C
P 3600 4100
F 0 "C202" H 3600 4200 40  0000 L CNN
F 1 "100n" H 3606 4015 40  0000 L CNN
F 2 "Capacitors_SMD:C_0805" H 3638 3950 30  0001 C CNN
F 3 "" H 3600 4100 60  0000 C CNN
	1    3600 4100
	1    0    0    -1  
$EndComp
$Comp
L AGND #PWR0102
U 1 1 54300B92
P 3600 4300
F 0 "#PWR0102" H 3600 4300 40  0001 C CNN
F 1 "AGND" H 3600 4230 50  0000 C CNN
F 2 "" H 3600 4300 60  0000 C CNN
F 3 "" H 3600 4300 60  0000 C CNN
	1    3600 4300
	1    0    0    -1  
$EndComp
$Comp
L VDD #PWR0103
U 1 1 54300B98
P 3600 3900
F 0 "#PWR0103" H 3600 4000 30  0001 C CNN
F 1 "VDD" H 3600 4010 30  0000 C CNN
F 2 "" H 3600 3900 60  0000 C CNN
F 3 "" H 3600 3900 60  0000 C CNN
	1    3600 3900
	1    0    0    -1  
$EndComp
$Comp
L C C203
U 1 1 54300BFD
P 3600 5800
F 0 "C203" H 3600 5900 40  0000 L CNN
F 1 "100n" H 3606 5715 40  0000 L CNN
F 2 "Capacitors_SMD:C_0805" H 3638 5650 30  0001 C CNN
F 3 "" H 3600 5800 60  0000 C CNN
	1    3600 5800
	1    0    0    -1  
$EndComp
$Comp
L AGND #PWR0104
U 1 1 54300C03
P 3600 6000
F 0 "#PWR0104" H 3600 6000 40  0001 C CNN
F 1 "AGND" H 3600 5930 50  0000 C CNN
F 2 "" H 3600 6000 60  0000 C CNN
F 3 "" H 3600 6000 60  0000 C CNN
	1    3600 6000
	1    0    0    -1  
$EndComp
$Comp
L VDD #PWR0105
U 1 1 54300C09
P 3600 5600
F 0 "#PWR0105" H 3600 5700 30  0001 C CNN
F 1 "VDD" H 3600 5710 30  0000 C CNN
F 2 "" H 3600 5600 60  0000 C CNN
F 3 "" H 3600 5600 60  0000 C CNN
	1    3600 5600
	1    0    0    -1  
$EndComp
Text HLabel 1750 2100 0    60   Input ~ 0
led1+
Text HLabel 1750 2200 0    60   Input ~ 0
led1-
Text HLabel 1750 2300 0    60   Input ~ 0
heizLed+
Text HLabel 1750 2400 0    60   Input ~ 0
heizLed-
$Comp
L CONN_01X09 P201
U 1 1 543010C9
P 2150 2000
F 0 "P201" H 2150 2500 50  0000 C CNN
F 1 "CONN_01X09" V 2250 2000 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x09" H 2150 2000 60  0001 C CNN
F 3 "" H 2150 2000 60  0000 C CNN
	1    2150 2000
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X09 P202
U 1 1 54301173
P 2500 2000
F 0 "P202" H 2500 2500 50  0000 C CNN
F 1 "CONN_01X09" V 2600 2000 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Angled_1x09" H 2500 2000 60  0001 C CNN
F 3 "" H 2500 2000 60  0000 C CNN
	1    2500 2000
	-1   0    0    -1  
$EndComp
Wire Wire Line
	1950 2100 1750 2100
Wire Wire Line
	1750 2200 1950 2200
Wire Wire Line
	1950 2300 1750 2300
Wire Wire Line
	1750 2400 1950 2400
$Comp
L LED D201
U 1 1 5430397B
P 1500 3400
F 0 "D201" H 1500 3500 50  0000 C CNN
F 1 "duoLed 5mm" H 1500 3300 50  0000 C CNN
F 2 "LEDs:LED-5MM" H 1500 3400 60  0001 C CNN
F 3 "" H 1500 3400 60  0000 C CNN
	1    1500 3400
	0    1    1    0   
$EndComp
$Comp
L LED D202
U 1 1 543039EA
P 2300 3400
F 0 "D202" H 2300 3500 50  0000 C CNN
F 1 "rot 5mm" H 2300 3300 50  0000 C CNN
F 2 "LEDs:LED-5MM" H 2300 3400 60  0001 C CNN
F 3 "" H 2300 3400 60  0000 C CNN
	1    2300 3400
	0    1    1    0   
$EndComp
Wire Wire Line
	2700 2100 3100 2100
Wire Wire Line
	3100 2100 3100 2700
Wire Wire Line
	3100 2700 1500 2700
Wire Wire Line
	1500 2700 1500 3200
Wire Wire Line
	2700 2200 3050 2200
Wire Wire Line
	3050 2200 3050 2650
Wire Wire Line
	3050 2650 1350 2650
Wire Wire Line
	1350 2650 1350 3750
Wire Wire Line
	1350 3750 1500 3750
Wire Wire Line
	1500 3750 1500 3600
Wire Wire Line
	2700 2300 3000 2300
Wire Wire Line
	3000 2300 3000 2800
Wire Wire Line
	3000 2800 2300 2800
Wire Wire Line
	2300 2800 2300 3200
Wire Wire Line
	2700 2400 2950 2400
Wire Wire Line
	2950 2400 2950 2750
Wire Wire Line
	2950 2750 2150 2750
Wire Wire Line
	2150 2750 2150 3750
Wire Wire Line
	2150 3750 2300 3750
Wire Wire Line
	2300 3750 2300 3600
Text Notes 750  4750 0    60   ~ 0
Status-LEDs:\n\nlinks: Duo-LED für alles-OK (grün), Kolben schläft\n(orange), und Fehler (rot). Die LED kann dafür vom\nAtmel umgepolt werden.\n\nrechts: einzelne, rote LED, die direkt mit der PWM\nder Heizung verknüpft ist und somit umso heller\nleuchtet, je mehr Leistung in den Lötkolben\nentlassen wird.
$Comp
L R_PACK4 RP203
U 1 1 5437B6E3
P 6100 3250
F 0 "RP203" H 6100 3700 40  0000 C CNN
F 1 "220" H 6100 3200 40  0000 C CNN
F 2 "Resistors_SMD:R_Cat16-4" H 6100 3250 60  0001 C CNN
F 3 "" H 6100 3250 60  0000 C CNN
	1    6100 3250
	1    0    0    1   
$EndComp
$Comp
L R_PACK4 RP204
U 1 1 5437B6E9
P 6100 3650
F 0 "RP204" H 6100 4100 40  0000 C CNN
F 1 "220" H 6100 3600 40  0000 C CNN
F 2 "Resistors_SMD:R_Cat16-4" H 6100 3650 60  0001 C CNN
F 3 "" H 6100 3650 60  0000 C CNN
	1    6100 3650
	1    0    0    1   
$EndComp
Wire Wire Line
	5900 3300 5600 3300
Wire Wire Line
	5600 3400 5900 3400
Wire Wire Line
	5900 3500 5600 3500
Wire Wire Line
	5600 3600 5900 3600
Wire Wire Line
	5600 3700 5900 3700
Wire Wire Line
	5600 3800 5900 3800
Wire Wire Line
	5600 3900 5900 3900
Wire Wire Line
	5600 4000 5900 4000
$Comp
L R_PACK4 RP205
U 1 1 5437B7A7
P 6100 4950
F 0 "RP205" H 6100 5400 40  0000 C CNN
F 1 "220" H 6100 4900 40  0000 C CNN
F 2 "Resistors_SMD:R_Cat16-4" H 6100 4950 60  0001 C CNN
F 3 "" H 6100 4950 60  0000 C CNN
	1    6100 4950
	1    0    0    1   
$EndComp
$Comp
L R_PACK4 RP206
U 1 1 5437B7AD
P 6100 5350
F 0 "RP206" H 6100 5800 40  0000 C CNN
F 1 "220" H 6100 5300 40  0000 C CNN
F 2 "Resistors_SMD:R_Cat16-4" H 6100 5350 60  0001 C CNN
F 3 "" H 6100 5350 60  0000 C CNN
	1    6100 5350
	1    0    0    1   
$EndComp
Wire Wire Line
	5900 5000 5600 5000
Wire Wire Line
	5600 5100 5900 5100
Wire Wire Line
	5900 5200 5600 5200
Wire Wire Line
	5600 5300 5900 5300
Wire Wire Line
	5600 5400 5900 5400
Wire Wire Line
	5600 5500 5900 5500
Wire Wire Line
	5600 5600 5900 5600
Wire Wire Line
	5600 5700 5900 5700
$Comp
L 7SEGMENTS AFF202
U 1 1 5437B7DD
P 7900 3700
F 0 "AFF202" H 7900 4250 60  0000 C CNN
F 1 "7SEGMENTS" H 7900 3250 60  0000 C CNN
F 2 "Sockets_DIP:DIP-10__300_ELL" H 7900 3700 60  0001 C CNN
F 3 "" H 7900 3700 60  0000 C CNN
	1    7900 3700
	1    0    0    -1  
$EndComp
$Comp
L 7SEGMENTS AFF203
U 1 1 5437B843
P 7900 5400
F 0 "AFF203" H 7900 5950 60  0000 C CNN
F 1 "7SEGMENTS" H 7900 4950 60  0000 C CNN
F 2 "Sockets_DIP:DIP-10__300_ELL" H 7900 5400 60  0001 C CNN
F 3 "" H 7900 5400 60  0000 C CNN
	1    7900 5400
	1    0    0    -1  
$EndComp
$Comp
L VDD #PWR0106
U 1 1 5437BB4D
P 8500 1550
F 0 "#PWR0106" H 8500 1650 30  0001 C CNN
F 1 "VDD" H 8500 1660 30  0000 C CNN
F 2 "" H 8500 1550 60  0000 C CNN
F 3 "" H 8500 1550 60  0000 C CNN
	1    8500 1550
	0    1    1    0   
$EndComp
$Comp
L VDD #PWR0107
U 1 1 5437BB6B
P 8500 1650
F 0 "#PWR0107" H 8500 1750 30  0001 C CNN
F 1 "VDD" H 8500 1760 30  0000 C CNN
F 2 "" H 8500 1650 60  0000 C CNN
F 3 "" H 8500 1650 60  0000 C CNN
	1    8500 1650
	0    1    1    0   
$EndComp
$Comp
L VDD #PWR0108
U 1 1 5437BB89
P 8500 3250
F 0 "#PWR0108" H 8500 3350 30  0001 C CNN
F 1 "VDD" H 8500 3360 30  0000 C CNN
F 2 "" H 8500 3250 60  0000 C CNN
F 3 "" H 8500 3250 60  0000 C CNN
	1    8500 3250
	0    1    1    0   
$EndComp
$Comp
L VDD #PWR0109
U 1 1 5437BBA7
P 8500 3350
F 0 "#PWR0109" H 8500 3450 30  0001 C CNN
F 1 "VDD" H 8500 3460 30  0000 C CNN
F 2 "" H 8500 3350 60  0000 C CNN
F 3 "" H 8500 3350 60  0000 C CNN
	1    8500 3350
	0    1    1    0   
$EndComp
$Comp
L VDD #PWR0110
U 1 1 5437BBC5
P 8500 4950
F 0 "#PWR0110" H 8500 5050 30  0001 C CNN
F 1 "VDD" H 8500 5060 30  0000 C CNN
F 2 "" H 8500 4950 60  0000 C CNN
F 3 "" H 8500 4950 60  0000 C CNN
	1    8500 4950
	0    1    1    0   
$EndComp
$Comp
L VDD #PWR0111
U 1 1 5437BBE3
P 8500 5050
F 0 "#PWR0111" H 8500 5150 30  0001 C CNN
F 1 "VDD" H 8500 5160 30  0000 C CNN
F 2 "" H 8500 5050 60  0000 C CNN
F 3 "" H 8500 5050 60  0000 C CNN
	1    8500 5050
	0    1    1    0   
$EndComp
$Comp
L CONN_01X01 P203
U 1 1 5437D78C
P 1400 5800
F 0 "P203" H 1400 5900 50  0000 C CNN
F 1 "CONN_01X01" V 1500 5800 50  0000 C CNN
F 2 "Connect:1pin" H 1400 5800 60  0001 C CNN
F 3 "" H 1400 5800 60  0000 C CNN
	1    1400 5800
	0    -1   -1   0   
$EndComp
$Comp
L CONN_01X01 P204
U 1 1 5437D871
P 2000 5800
F 0 "P204" H 2000 5900 50  0000 C CNN
F 1 "CONN_01X01" V 2100 5800 50  0000 C CNN
F 2 "Connect:1pin" H 2000 5800 60  0001 C CNN
F 3 "" H 2000 5800 60  0000 C CNN
	1    2000 5800
	0    -1   -1   0   
$EndComp
$Comp
L AGND #PWR0112
U 1 1 5437D8CD
P 2000 6000
F 0 "#PWR0112" H 2000 6000 40  0001 C CNN
F 1 "AGND" H 2000 5930 50  0000 C CNN
F 2 "" H 2000 6000 60  0000 C CNN
F 3 "" H 2000 6000 60  0000 C CNN
	1    2000 6000
	1    0    0    -1  
$EndComp
$Comp
L AGND #PWR0113
U 1 1 5437D902
P 1400 6000
F 0 "#PWR0113" H 1400 6000 40  0001 C CNN
F 1 "AGND" H 1400 5930 50  0000 C CNN
F 2 "" H 1400 6000 60  0000 C CNN
F 3 "" H 1400 6000 60  0000 C CNN
	1    1400 6000
	1    0    0    -1  
$EndComp
Wire Wire Line
	6300 1600 6800 1600
Wire Wire Line
	6800 1600 6800 2550
Wire Wire Line
	6800 2550 8500 2550
Wire Wire Line
	8500 2550 8500 2250
Wire Wire Line
	6300 1700 7000 1700
Wire Wire Line
	7000 1700 7000 1800
Wire Wire Line
	7000 1800 7300 1800
Wire Wire Line
	6300 1800 6950 1800
Wire Wire Line
	6950 1800 6950 1900
Wire Wire Line
	6950 1900 7300 1900
Wire Wire Line
	6300 1900 6900 1900
Wire Wire Line
	6900 1900 6900 2000
Wire Wire Line
	6900 2000 7300 2000
Wire Wire Line
	6300 2000 6850 2000
Wire Wire Line
	6850 2000 6850 2200
Wire Wire Line
	6850 2200 7300 2200
Wire Wire Line
	6300 2100 7300 2100
Wire Wire Line
	6300 2200 6750 2200
Wire Wire Line
	6750 2200 6750 1550
Wire Wire Line
	6750 1550 7300 1550
Wire Wire Line
	7300 1550 7300 1600
Wire Wire Line
	6300 2300 7050 2300
Wire Wire Line
	7050 2300 7050 1700
Wire Wire Line
	7050 1700 7300 1700
Wire Wire Line
	6300 3300 6800 3300
Wire Wire Line
	6800 3300 6800 4250
Wire Wire Line
	6800 4250 8500 4250
Wire Wire Line
	6300 3400 7000 3400
Wire Wire Line
	7000 3400 7000 3500
Wire Wire Line
	7000 3500 7300 3500
Wire Wire Line
	6300 3500 6950 3500
Wire Wire Line
	6950 3500 6950 3600
Wire Wire Line
	6950 3600 7300 3600
Wire Wire Line
	6300 3600 6900 3600
Wire Wire Line
	6900 3600 6900 3700
Wire Wire Line
	6900 3700 7300 3700
Wire Wire Line
	6300 3700 6850 3700
Wire Wire Line
	6850 3700 6850 3900
Wire Wire Line
	6850 3900 7300 3900
Wire Wire Line
	6300 3800 7300 3800
Wire Wire Line
	6300 3900 6750 3900
Wire Wire Line
	6750 3900 6750 3250
Wire Wire Line
	6750 3250 7300 3250
Wire Wire Line
	6300 4000 7050 4000
Wire Wire Line
	7050 4000 7050 3400
Wire Wire Line
	7050 3400 7300 3400
Wire Wire Line
	6300 5000 6800 5000
Wire Wire Line
	6800 5000 6800 5950
Wire Wire Line
	6800 5950 8500 5950
Wire Wire Line
	6300 5100 7000 5100
Wire Wire Line
	7000 5100 7000 5200
Wire Wire Line
	7000 5200 7300 5200
Wire Wire Line
	6300 5200 6950 5200
Wire Wire Line
	6950 5200 6950 5300
Wire Wire Line
	6950 5300 7300 5300
Wire Wire Line
	6300 5300 6900 5300
Wire Wire Line
	6900 5300 6900 5400
Wire Wire Line
	6900 5400 7300 5400
Wire Wire Line
	6300 5400 6850 5400
Wire Wire Line
	6850 5400 6850 5600
Wire Wire Line
	6850 5600 7300 5600
Wire Wire Line
	6300 5500 7300 5500
Wire Wire Line
	6300 5600 6750 5600
Wire Wire Line
	6750 5600 6750 4950
Wire Wire Line
	6750 4950 7300 4950
Wire Wire Line
	6300 5700 7050 5700
Wire Wire Line
	7050 5700 7050 5100
Wire Wire Line
	7050 5100 7300 5100
Wire Wire Line
	7300 3250 7300 3300
Wire Wire Line
	8500 4250 8500 3950
Wire Wire Line
	8500 5950 8500 5650
Wire Wire Line
	7300 4950 7300 5000
$EndSCHEMATC
