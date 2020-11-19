EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 2 3
Title "Daisy"
Date "2018-09-15"
Rev "v1.0"
Comp "www.2-0.dk"
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L Device:CP C?
U 1 1 5B66E084
P 2600 1400
AR Path="/5B48B53B/5B66E084" Ref="C?"  Part="1" 
AR Path="/5B66E084" Ref="C?"  Part="1" 
AR Path="/5B66D7A7/5B66E084" Ref="C1"  Part="1" 
F 0 "C1" H 2718 1446 50  0000 L CNN
F 1 "10u" H 2718 1355 50  0000 L CNN
F 2 "Capacitor_Tantalum_SMD:CP_EIA-3528-12_Kemet-T" H 2638 1250 50  0001 C CNN
F 3 "~" H 2600 1400 50  0001 C CNN
	1    2600 1400
	-1   0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5B66E0A4
P 2600 1550
AR Path="/5B48B53B/5B66E0A4" Ref="#PWR?"  Part="1" 
AR Path="/5B66E0A4" Ref="#PWR?"  Part="1" 
AR Path="/5B66D7A7/5B66E0A4" Ref="#PWR01"  Part="1" 
F 0 "#PWR01" H 2600 1300 50  0001 C CNN
F 1 "GND" H 2605 1377 50  0000 C CNN
F 2 "" H 2600 1550 50  0001 C CNN
F 3 "" H 2600 1550 50  0001 C CNN
	1    2600 1550
	1    0    0    -1  
$EndComp
Text GLabel 2450 1250 0    50   Input ~ 0
vusb
Connection ~ 2600 1250
Wire Wire Line
	2600 1250 2750 1250
Wire Wire Line
	2450 1250 2600 1250
Wire Wire Line
	2800 1350 2750 1350
Wire Wire Line
	2750 1350 2750 1250
Connection ~ 2750 1250
Wire Wire Line
	2750 1250 2800 1250
$Comp
L MCU_ST_STM32F0:STM32F072C8Tx U?
U 1 1 5B66E0BD
P 7700 3700
AR Path="/5B48B53E/5B66E0BD" Ref="U?"  Part="1" 
AR Path="/5B66E0BD" Ref="U?"  Part="1" 
AR Path="/5B66D7A7/5B66E0BD" Ref="U3"  Part="1" 
F 0 "U3" H 7700 3650 50  0000 C CNN
F 1 "STM32F072C8Tx" H 7700 3750 50  0000 C CNN
F 2 "Package_QFP:LQFP-48_7x7mm_P0.5mm" H 7100 2300 50  0001 R CNN
F 3 "http://www.st.com/st-web-ui/static/active/en/resource/technical/document/datasheet/DM00090510.pdf" H 7700 3700 50  0001 C CNN
	1    7700 3700
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5B66E0C4
P 3900 4600
AR Path="/5B48B53E/5B66E0C4" Ref="#PWR?"  Part="1" 
AR Path="/5B66E0C4" Ref="#PWR?"  Part="1" 
AR Path="/5B66D7A7/5B66E0C4" Ref="#PWR05"  Part="1" 
F 0 "#PWR05" H 3900 4350 50  0001 C CNN
F 1 "GND" H 3900 4450 50  0000 C CNN
F 2 "" H 3900 4600 50  0001 C CNN
F 3 "" H 3900 4600 50  0001 C CNN
	1    3900 4600
	1    0    0    -1  
$EndComp
Text GLabel 4800 3100 2    50   Output ~ 0
vusb
Text GLabel 5000 3700 2    50   BiDi ~ 0
usb_dm
Text GLabel 5000 3900 2    50   BiDi ~ 0
usb_dp
$Comp
L Device:R R?
U 1 1 5B66E0CD
P 5100 3300
AR Path="/5B48B53E/5B66E0CD" Ref="R?"  Part="1" 
AR Path="/5B66E0CD" Ref="R?"  Part="1" 
AR Path="/5B66D7A7/5B66E0CD" Ref="R1"  Part="1" 
F 0 "R1" V 5000 3300 50  0000 C CNN
F 1 "5k1" V 5100 3300 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 5030 3300 50  0001 C CNN
F 3 "~" H 5100 3300 50  0001 C CNN
	1    5100 3300
	0    1    1    0   
$EndComp
$Comp
L Device:R R?
U 1 1 5B66E0D4
P 5100 3400
AR Path="/5B48B53E/5B66E0D4" Ref="R?"  Part="1" 
AR Path="/5B66E0D4" Ref="R?"  Part="1" 
AR Path="/5B66D7A7/5B66E0D4" Ref="R2"  Part="1" 
F 0 "R2" V 5200 3400 50  0000 C CNN
F 1 "5k1" V 5100 3400 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 5030 3400 50  0001 C CNN
F 3 "~" H 5100 3400 50  0001 C CNN
	1    5100 3400
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5B66E0DB
P 5250 3400
AR Path="/5B48B53E/5B66E0DB" Ref="#PWR?"  Part="1" 
AR Path="/5B66E0DB" Ref="#PWR?"  Part="1" 
AR Path="/5B66D7A7/5B66E0DB" Ref="#PWR010"  Part="1" 
F 0 "#PWR010" H 5250 3150 50  0001 C CNN
F 1 "GND" V 5255 3272 50  0000 R CNN
F 2 "" H 5250 3400 50  0001 C CNN
F 3 "" H 5250 3400 50  0001 C CNN
	1    5250 3400
	0    -1   -1   0   
$EndComp
Text GLabel 8300 4700 2    50   BiDi ~ 0
usb_dp
$Comp
L power:GND #PWR?
U 1 1 5B66E0E2
P 7800 5200
AR Path="/5B48B53E/5B66E0E2" Ref="#PWR?"  Part="1" 
AR Path="/5B66E0E2" Ref="#PWR?"  Part="1" 
AR Path="/5B66D7A7/5B66E0E2" Ref="#PWR015"  Part="1" 
F 0 "#PWR015" H 7800 4950 50  0001 C CNN
F 1 "GND" H 7805 5027 50  0000 C CNN
F 2 "" H 7800 5200 50  0001 C CNN
F 3 "" H 7800 5200 50  0001 C CNN
	1    7800 5200
	1    0    0    -1  
$EndComp
Wire Wire Line
	7500 5200 7600 5200
Connection ~ 7800 5200
Connection ~ 7600 5200
Wire Wire Line
	7600 5200 7700 5200
Connection ~ 7700 5200
Wire Wire Line
	7700 5200 7800 5200
$Comp
L power:+3V3 #PWR?
U 1 1 5B66E0EE
P 7700 2200
AR Path="/5B48B53E/5B66E0EE" Ref="#PWR?"  Part="1" 
AR Path="/5B66E0EE" Ref="#PWR?"  Part="1" 
AR Path="/5B66D7A7/5B66E0EE" Ref="#PWR014"  Part="1" 
F 0 "#PWR014" H 7700 2050 50  0001 C CNN
F 1 "+3V3" H 7715 2373 50  0000 C CNN
F 2 "" H 7700 2200 50  0001 C CNN
F 3 "" H 7700 2200 50  0001 C CNN
	1    7700 2200
	1    0    0    -1  
$EndComp
Wire Wire Line
	7500 2200 7600 2200
Connection ~ 7600 2200
Wire Wire Line
	7600 2200 7700 2200
Connection ~ 7700 2200
Wire Wire Line
	7700 2200 7800 2200
Connection ~ 7800 2200
Wire Wire Line
	7800 2200 7900 2200
$Comp
L Device:C C?
U 1 1 5B66E0FB
P 5600 1400
AR Path="/5B48B53E/5B66E0FB" Ref="C?"  Part="1" 
AR Path="/5B66E0FB" Ref="C?"  Part="1" 
AR Path="/5B66D7A7/5B66E0FB" Ref="C6"  Part="1" 
F 0 "C6" H 5450 1450 50  0000 C CNN
F 1 "100n" H 5400 1350 50  0000 C CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 5638 1250 50  0001 C CNN
F 3 "~" H 5600 1400 50  0001 C CNN
	1    5600 1400
	-1   0    0    -1  
$EndComp
$Comp
L Device:R R?
U 1 1 5B66E102
P 6000 1400
AR Path="/5B48B53E/5B66E102" Ref="R?"  Part="1" 
AR Path="/5B66E102" Ref="R?"  Part="1" 
AR Path="/5B66D7A7/5B66E102" Ref="R3"  Part="1" 
F 0 "R3" H 6100 1400 50  0000 C CNN
F 1 "100k" V 6000 1400 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 5930 1400 50  0001 C CNN
F 3 "~" H 6000 1400 50  0001 C CNN
	1    6000 1400
	1    0    0    -1  
$EndComp
$Comp
L Device:C C?
U 1 1 5B66E109
P 4550 1400
AR Path="/5B48B53E/5B66E109" Ref="C?"  Part="1" 
AR Path="/5B66E109" Ref="C?"  Part="1" 
AR Path="/5B66D7A7/5B66E109" Ref="C3"  Part="1" 
F 0 "C3" H 4665 1446 50  0000 L CNN
F 1 "100n" H 4665 1355 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 4588 1250 50  0001 C CNN
F 3 "~" H 4550 1400 50  0001 C CNN
	1    4550 1400
	1    0    0    -1  
$EndComp
$Comp
L Device:C C?
U 1 1 5B66E110
P 4900 1400
AR Path="/5B48B53E/5B66E110" Ref="C?"  Part="1" 
AR Path="/5B66E110" Ref="C?"  Part="1" 
AR Path="/5B66D7A7/5B66E110" Ref="C4"  Part="1" 
F 0 "C4" H 5015 1446 50  0000 L CNN
F 1 "100n" H 5015 1355 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 4938 1250 50  0001 C CNN
F 3 "~" H 4900 1400 50  0001 C CNN
	1    4900 1400
	1    0    0    -1  
$EndComp
$Comp
L Device:C C?
U 1 1 5B66E117
P 5250 1400
AR Path="/5B48B53E/5B66E117" Ref="C?"  Part="1" 
AR Path="/5B66E117" Ref="C?"  Part="1" 
AR Path="/5B66D7A7/5B66E117" Ref="C5"  Part="1" 
F 0 "C5" H 5365 1446 50  0000 L CNN
F 1 "100n" H 5365 1355 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 5288 1250 50  0001 C CNN
F 3 "~" H 5250 1400 50  0001 C CNN
	1    5250 1400
	1    0    0    -1  
$EndComp
$Comp
L Device:C C?
U 1 1 5B66E11E
P 6350 1400
AR Path="/5B48B53E/5B66E11E" Ref="C?"  Part="1" 
AR Path="/5B66E11E" Ref="C?"  Part="1" 
AR Path="/5B66D7A7/5B66E11E" Ref="C7"  Part="1" 
F 0 "C7" H 6465 1446 50  0000 L CNN
F 1 "100n" H 6465 1355 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 6388 1250 50  0001 C CNN
F 3 "~" H 6350 1400 50  0001 C CNN
	1    6350 1400
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5B66E125
P 4550 1550
AR Path="/5B48B53E/5B66E125" Ref="#PWR?"  Part="1" 
AR Path="/5B66E125" Ref="#PWR?"  Part="1" 
AR Path="/5B66D7A7/5B66E125" Ref="#PWR08"  Part="1" 
F 0 "#PWR08" H 4550 1300 50  0001 C CNN
F 1 "GND" H 4555 1377 50  0000 C CNN
F 2 "" H 4550 1550 50  0001 C CNN
F 3 "" H 4550 1550 50  0001 C CNN
	1    4550 1550
	1    0    0    -1  
$EndComp
$Comp
L power:+3V3 #PWR?
U 1 1 5B66E12B
P 4550 1250
AR Path="/5B48B53E/5B66E12B" Ref="#PWR?"  Part="1" 
AR Path="/5B66E12B" Ref="#PWR?"  Part="1" 
AR Path="/5B66D7A7/5B66E12B" Ref="#PWR07"  Part="1" 
F 0 "#PWR07" H 4550 1100 50  0001 C CNN
F 1 "+3V3" H 4565 1423 50  0000 C CNN
F 2 "" H 4550 1250 50  0001 C CNN
F 3 "" H 4550 1250 50  0001 C CNN
	1    4550 1250
	1    0    0    -1  
$EndComp
Wire Wire Line
	4550 1550 4900 1550
Connection ~ 4900 1550
Wire Wire Line
	4900 1550 5250 1550
Connection ~ 5250 1550
Wire Wire Line
	5250 1550 5600 1550
Wire Wire Line
	4550 1250 4900 1250
Connection ~ 4900 1250
Wire Wire Line
	4900 1250 5250 1250
Connection ~ 5250 1250
Wire Wire Line
	5250 1250 5600 1250
Wire Wire Line
	5250 3300 5250 3400
Connection ~ 5250 3400
Connection ~ 4550 1250
Connection ~ 4550 1550
Wire Wire Line
	4800 3300 4950 3300
Wire Wire Line
	4800 3400 4950 3400
Wire Wire Line
	4800 3700 4850 3700
Wire Wire Line
	4800 3900 4850 3900
Wire Wire Line
	4800 3600 4850 3600
Wire Wire Line
	4850 3600 4850 3700
Connection ~ 4850 3700
Wire Wire Line
	4850 3700 5000 3700
Wire Wire Line
	4800 3800 4850 3800
Wire Wire Line
	4850 3800 4850 3900
Connection ~ 4850 3900
Wire Wire Line
	4850 3900 5000 3900
NoConn ~ 4800 4200
$Comp
L power:GND #PWR?
U 1 1 5B66E163
P 6550 6050
AR Path="/5B48B53E/5B66E163" Ref="#PWR?"  Part="1" 
AR Path="/5B66E163" Ref="#PWR?"  Part="1" 
AR Path="/5B66D7A7/5B66E163" Ref="#PWR013"  Part="1" 
F 0 "#PWR013" H 6550 5800 50  0001 C CNN
F 1 "GND" V 6555 5922 50  0000 R CNN
F 2 "" H 6550 6050 50  0001 C CNN
F 3 "" H 6550 6050 50  0001 C CNN
	1    6550 6050
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5B66E169
P 8100 6050
AR Path="/5B48B53E/5B66E169" Ref="#PWR?"  Part="1" 
AR Path="/5B66E169" Ref="#PWR?"  Part="1" 
AR Path="/5B66D7A7/5B66E169" Ref="#PWR016"  Part="1" 
F 0 "#PWR016" H 8100 5800 50  0001 C CNN
F 1 "GND" V 8105 5922 50  0000 R CNN
F 2 "" H 8100 6050 50  0001 C CNN
F 3 "" H 8100 6050 50  0001 C CNN
	1    8100 6050
	0    1    1    0   
$EndComp
$Comp
L Device:R R?
U 1 1 5B66E16F
P 7100 6250
AR Path="/5B48B53E/5B66E16F" Ref="R?"  Part="1" 
AR Path="/5B66E16F" Ref="R?"  Part="1" 
AR Path="/5B66D7A7/5B66E16F" Ref="R6"  Part="1" 
F 0 "R6" V 7000 6250 50  0000 C CNN
F 1 "470" V 7100 6250 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 7030 6250 50  0001 C CNN
F 3 "~" H 7100 6250 50  0001 C CNN
	1    7100 6250
	0    1    1    0   
$EndComp
$Comp
L Device:R R?
U 1 1 5B66E176
P 7100 6050
AR Path="/5B48B53E/5B66E176" Ref="R?"  Part="1" 
AR Path="/5B66E176" Ref="R?"  Part="1" 
AR Path="/5B66D7A7/5B66E176" Ref="R5"  Part="1" 
F 0 "R5" V 7000 6050 50  0000 C CNN
F 1 "470" V 7100 6050 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 7030 6050 50  0001 C CNN
F 3 "~" H 7100 6050 50  0001 C CNN
	1    7100 6050
	0    1    1    0   
$EndComp
$Comp
L Device:R R?
U 1 1 5B66E17D
P 8650 6050
AR Path="/5B48B53E/5B66E17D" Ref="R?"  Part="1" 
AR Path="/5B66E17D" Ref="R?"  Part="1" 
AR Path="/5B66D7A7/5B66E17D" Ref="R8"  Part="1" 
F 0 "R8" V 8550 6050 50  0000 C CNN
F 1 "470" V 8650 6050 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 8580 6050 50  0001 C CNN
F 3 "~" H 8650 6050 50  0001 C CNN
	1    8650 6050
	0    1    1    0   
$EndComp
$Comp
L Device:R R?
U 1 1 5B66E184
P 8650 5850
AR Path="/5B48B53E/5B66E184" Ref="R?"  Part="1" 
AR Path="/5B66E184" Ref="R?"  Part="1" 
AR Path="/5B66D7A7/5B66E184" Ref="R7"  Part="1" 
F 0 "R7" V 8550 5850 50  0000 C CNN
F 1 "470" V 8650 5850 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 8580 5850 50  0001 C CNN
F 3 "~" H 8650 5850 50  0001 C CNN
	1    8650 5850
	0    1    1    0   
$EndComp
Text GLabel 7250 6050 2    50   Input ~ 0
led1_green
Text GLabel 8800 6050 2    50   Input ~ 0
led2_green
Text GLabel 7250 5850 2    50   Input ~ 0
led1_red
Text GLabel 8800 5850 2    50   Input ~ 0
led2_red
NoConn ~ 4800 4300
Text GLabel 4700 6150 2    50   Input ~ 0
usb_dp
Text GLabel 4700 5950 2    50   Input ~ 0
usb_dm
Text GLabel 4200 5550 1    50   Input ~ 0
vusb
$Comp
L power:GND #PWR?
U 1 1 5B66E19A
P 4200 6550
AR Path="/5B48B53E/5B66E19A" Ref="#PWR?"  Part="1" 
AR Path="/5B66E19A" Ref="#PWR?"  Part="1" 
AR Path="/5B66D7A7/5B66E19A" Ref="#PWR06"  Part="1" 
F 0 "#PWR06" H 4200 6300 50  0001 C CNN
F 1 "GND" H 4205 6377 50  0000 C CNN
F 2 "" H 4200 6550 50  0001 C CNN
F 3 "" H 4200 6550 50  0001 C CNN
	1    4200 6550
	1    0    0    -1  
$EndComp
Text GLabel 3700 6150 0    50   Input ~ 0
usb_dm
Text GLabel 3700 5950 0    50   Input ~ 0
usb_dp
$Comp
L Device:LED_RCGB D?
U 1 1 5B66E1A2
P 6750 6050
AR Path="/5B48B53E/5B66E1A2" Ref="D?"  Part="1" 
AR Path="/5B66E1A2" Ref="D?"  Part="1" 
AR Path="/5B66D7A7/5B66E1A2" Ref="D1"  Part="1" 
F 0 "D1" H 6750 6547 50  0000 C CNN
F 1 "LED_RCGB" H 6750 6456 50  0000 C CNN
F 2 "LED_THT:LED_D5.0mm-4" H 6750 6000 50  0001 C CNN
F 3 "~" H 6750 6000 50  0001 C CNN
	1    6750 6050
	1    0    0    -1  
$EndComp
$Comp
L Device:LED_RCGB D?
U 1 1 5B66E1A9
P 8300 6050
AR Path="/5B48B53E/5B66E1A9" Ref="D?"  Part="1" 
AR Path="/5B66E1A9" Ref="D?"  Part="1" 
AR Path="/5B66D7A7/5B66E1A9" Ref="D2"  Part="1" 
F 0 "D2" H 8300 6550 50  0000 C CNN
F 1 "LED_RCGB" H 8300 6450 50  0000 C CNN
F 2 "LED_THT:LED_D5.0mm-4" H 8300 6000 50  0001 C CNN
F 3 "~" H 8300 6000 50  0001 C CNN
	1    8300 6050
	1    0    0    -1  
$EndComp
$Comp
L Device:R R?
U 1 1 5B66E1B0
P 7100 5850
AR Path="/5B48B53E/5B66E1B0" Ref="R?"  Part="1" 
AR Path="/5B66E1B0" Ref="R?"  Part="1" 
AR Path="/5B66D7A7/5B66E1B0" Ref="R4"  Part="1" 
F 0 "R4" V 7000 5850 50  0000 C CNN
F 1 "470" V 7100 5850 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 7030 5850 50  0001 C CNN
F 3 "~" H 7100 5850 50  0001 C CNN
	1    7100 5850
	0    1    1    0   
$EndComp
Text GLabel 7250 6250 2    50   Input ~ 0
led1_blue
$Comp
L Device:R R?
U 1 1 5B66E1B8
P 8650 6250
AR Path="/5B48B53E/5B66E1B8" Ref="R?"  Part="1" 
AR Path="/5B66E1B8" Ref="R?"  Part="1" 
AR Path="/5B66D7A7/5B66E1B8" Ref="R9"  Part="1" 
F 0 "R9" V 8550 6250 50  0000 C CNN
F 1 "470" V 8650 6250 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 8580 6250 50  0001 C CNN
F 3 "~" H 8650 6250 50  0001 C CNN
	1    8650 6250
	0    1    1    0   
$EndComp
Text GLabel 8800 6250 2    50   Input ~ 0
led2_blue
$Comp
L power:GND #PWR?
U 1 1 5B66E1C0
P 6000 1550
AR Path="/5B48B53E/5B66E1C0" Ref="#PWR?"  Part="1" 
AR Path="/5B66E1C0" Ref="#PWR?"  Part="1" 
AR Path="/5B66D7A7/5B66E1C0" Ref="#PWR011"  Part="1" 
F 0 "#PWR011" H 6000 1300 50  0001 C CNN
F 1 "GND" H 6000 1400 50  0000 C CNN
F 2 "" H 6000 1550 50  0001 C CNN
F 3 "" H 6000 1550 50  0001 C CNN
	1    6000 1550
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5B66E1C6
P 6350 1550
AR Path="/5B48B53E/5B66E1C6" Ref="#PWR?"  Part="1" 
AR Path="/5B66E1C6" Ref="#PWR?"  Part="1" 
AR Path="/5B66D7A7/5B66E1C6" Ref="#PWR012"  Part="1" 
F 0 "#PWR012" H 6350 1300 50  0001 C CNN
F 1 "GND" H 6350 1400 50  0000 C CNN
F 2 "" H 6350 1550 50  0001 C CNN
F 3 "" H 6350 1550 50  0001 C CNN
	1    6350 1550
	1    0    0    -1  
$EndComp
Text GLabel 7000 4800 0    50   Output ~ 0
led1_blue
Text GLabel 7000 4900 0    50   Output ~ 0
led1_green
Text GLabel 7000 5000 0    50   Output ~ 0
led1_red
Text GLabel 6000 1250 1    50   BiDi ~ 0
boot0
Text GLabel 6350 1250 1    50   BiDi ~ 0
nrst
Text GLabel 7000 2400 0    50   BiDi ~ 0
nrst
Text GLabel 7000 2600 0    50   BiDi ~ 0
boot0
Text GLabel 8300 4600 2    50   BiDi ~ 0
usb_dm
Text GLabel 8300 4500 2    50   Output ~ 0
led2_red
Text GLabel 8300 4400 2    50   Output ~ 0
led2_green
Text GLabel 8300 4300 2    50   Output ~ 0
led2_blue
NoConn ~ 7000 2800
NoConn ~ 7000 2900
NoConn ~ 7000 3800
NoConn ~ 7000 3900
NoConn ~ 7000 4300
NoConn ~ 7000 4400
NoConn ~ 8300 5000
$Comp
L power:GND #PWR?
U 1 1 5B672C1E
P 9450 3000
AR Path="/5B48B53E/5B672C1E" Ref="#PWR?"  Part="1" 
AR Path="/5B672C1E" Ref="#PWR?"  Part="1" 
AR Path="/5B66D7A7/5B672C1E" Ref="#PWR017"  Part="1" 
F 0 "#PWR017" H 9450 2750 50  0001 C CNN
F 1 "GND" V 9455 2872 50  0000 R CNN
F 2 "" H 9450 3000 50  0001 C CNN
F 3 "" H 9450 3000 50  0001 C CNN
	1    9450 3000
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5B672D82
P 9950 3000
AR Path="/5B48B53E/5B672D82" Ref="#PWR?"  Part="1" 
AR Path="/5B672D82" Ref="#PWR?"  Part="1" 
AR Path="/5B66D7A7/5B672D82" Ref="#PWR018"  Part="1" 
F 0 "#PWR018" H 9950 2750 50  0001 C CNN
F 1 "GND" V 9955 2872 50  0000 R CNN
F 2 "" H 9950 3000 50  0001 C CNN
F 3 "" H 9950 3000 50  0001 C CNN
	1    9950 3000
	0    -1   -1   0   
$EndComp
Text GLabel 9450 3100 0    50   Input ~ 0
uart_tx
Text GLabel 9450 3200 0    50   Output ~ 0
uart_rx
Text GLabel 9950 3100 2    50   BiDi ~ 0
swdio
Text GLabel 9950 3200 2    50   Output ~ 0
swclk
Text GLabel 8300 4800 2    50   BiDi ~ 0
swdio
Text GLabel 8300 4900 2    50   Input ~ 0
swclk
Text GLabel 7000 4100 0    50   Output ~ 0
uart_tx
Text GLabel 7000 4200 0    50   Input ~ 0
uart_rx
Text GLabel 7000 3100 0    50   BiDi ~ 0
dio1_radio868
Text GLabel 7000 3200 0    50   Input ~ 0
busy_radio868
Text GLabel 7000 3300 0    50   Output ~ 0
nrst_radio868
Text GLabel 8300 3800 2    50   Output ~ 0
cs_radio868
Text GLabel 8300 3500 2    50   Output ~ 0
rxen_radio868
Text GLabel 8300 3600 2    50   Output ~ 0
txen_radio868
Text GLabel 8300 3700 2    50   BiDi ~ 0
dio2_radio868
Text GLabel 8300 4000 2    50   Output ~ 0
spi_sck
Text GLabel 8300 4100 2    50   Input ~ 0
spi_miso
Text GLabel 8300 4200 2    50   Output ~ 0
spi_mosi
Text GLabel 8300 3900 2    50   Output ~ 0
cs_radio433
Text GLabel 7000 3500 0    50   BiDi ~ 0
dio1_radio433
Text GLabel 7000 3600 0    50   Input ~ 0
busy_radio433
Text GLabel 7000 3700 0    50   Output ~ 0
nrst_radio433
Text GLabel 7000 4600 0    50   BiDi ~ 0
dio2_radio433
Text GLabel 7000 4500 0    50   Output ~ 0
txen_radio433
Text GLabel 7000 4700 0    50   Output ~ 0
rxen_radio433
NoConn ~ 7000 4000
$Comp
L Connector_Generic:Conn_02x04_Odd_Even J2
U 1 1 5B9D2DE8
P 9650 3000
F 0 "J2" H 9700 3317 50  0000 C CNN
F 1 "Debug" H 9700 3226 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_2x04_P2.54mm_Vertical" H 9650 3000 50  0001 C CNN
F 3 "~" H 9650 3000 50  0001 C CNN
	1    9650 3000
	1    0    0    -1  
$EndComp
$Comp
L power:+3V3 #PWR?
U 1 1 5B9D2FB8
P 9950 2900
AR Path="/5B48B53B/5B9D2FB8" Ref="#PWR?"  Part="1" 
AR Path="/5B9D2FB8" Ref="#PWR?"  Part="1" 
AR Path="/5B66D7A7/5B9D2FB8" Ref="#PWR030"  Part="1" 
F 0 "#PWR030" H 9950 2750 50  0001 C CNN
F 1 "+3V3" V 9965 3028 50  0000 L CNN
F 2 "" H 9950 2900 50  0001 C CNN
F 3 "" H 9950 2900 50  0001 C CNN
	1    9950 2900
	0    1    1    0   
$EndComp
$Comp
L power:+3V3 #PWR?
U 1 1 5B9D3178
P 9450 2900
AR Path="/5B48B53B/5B9D3178" Ref="#PWR?"  Part="1" 
AR Path="/5B9D3178" Ref="#PWR?"  Part="1" 
AR Path="/5B66D7A7/5B9D3178" Ref="#PWR029"  Part="1" 
F 0 "#PWR029" H 9450 2750 50  0001 C CNN
F 1 "+3V3" V 9465 3028 50  0000 L CNN
F 2 "" H 9450 2900 50  0001 C CNN
F 3 "" H 9450 2900 50  0001 C CNN
	1    9450 2900
	0    -1   -1   0   
$EndComp
$Comp
L Power_Protection:SRV05-4 U2
U 1 1 5FA9C573
P 4200 6050
F 0 "U2" H 4200 6731 50  0000 C CNN
F 1 "SRV05-4" H 4200 6640 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-23-6" H 4900 5600 50  0001 C CNN
F 3 "http://www.onsemi.com/pub/Collateral/SRV05-4-D.PDF" H 4200 6050 50  0001 C CNN
	1    4200 6050
	1    0    0    -1  
$EndComp
$Comp
L Regulator_Linear:LP5907MFX-3.3 U1
U 1 1 5FAA6E98
P 3100 1350
F 0 "U1" H 3100 1717 50  0000 C CNN
F 1 "LP5907MFX-3.3" H 3100 1626 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-23-5" H 3100 1700 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/lp5907.pdf" H 3100 1850 50  0001 C CNN
	1    3100 1350
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5B66E09E
P 3100 1650
AR Path="/5B48B53B/5B66E09E" Ref="#PWR?"  Part="1" 
AR Path="/5B66E09E" Ref="#PWR?"  Part="1" 
AR Path="/5B66D7A7/5B66E09E" Ref="#PWR02"  Part="1" 
F 0 "#PWR02" H 3100 1400 50  0001 C CNN
F 1 "GND" H 3105 1477 50  0000 C CNN
F 2 "" H 3100 1650 50  0001 C CNN
F 3 "" H 3100 1650 50  0001 C CNN
	1    3100 1650
	1    0    0    -1  
$EndComp
$Comp
L Device:CP C?
U 1 1 5B66E08B
P 3600 1400
AR Path="/5B48B53B/5B66E08B" Ref="C?"  Part="1" 
AR Path="/5B66E08B" Ref="C?"  Part="1" 
AR Path="/5B66D7A7/5B66E08B" Ref="C2"  Part="1" 
F 0 "C2" H 3718 1446 50  0000 L CNN
F 1 "22u" H 3718 1355 50  0000 L CNN
F 2 "Capacitor_Tantalum_SMD:CP_EIA-3528-12_Kemet-T" H 3638 1250 50  0001 C CNN
F 3 "~" H 3600 1400 50  0001 C CNN
	1    3600 1400
	1    0    0    -1  
$EndComp
$Comp
L power:+3V3 #PWR?
U 1 1 5B66E092
P 3800 1250
AR Path="/5B48B53B/5B66E092" Ref="#PWR?"  Part="1" 
AR Path="/5B66E092" Ref="#PWR?"  Part="1" 
AR Path="/5B66D7A7/5B66E092" Ref="#PWR04"  Part="1" 
F 0 "#PWR04" H 3800 1100 50  0001 C CNN
F 1 "+3V3" V 3815 1378 50  0000 L CNN
F 2 "" H 3800 1250 50  0001 C CNN
F 3 "" H 3800 1250 50  0001 C CNN
	1    3800 1250
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5B66E098
P 3600 1550
AR Path="/5B48B53B/5B66E098" Ref="#PWR?"  Part="1" 
AR Path="/5B66E098" Ref="#PWR?"  Part="1" 
AR Path="/5B66D7A7/5B66E098" Ref="#PWR03"  Part="1" 
F 0 "#PWR03" H 3600 1300 50  0001 C CNN
F 1 "GND" H 3605 1377 50  0000 C CNN
F 2 "" H 3600 1550 50  0001 C CNN
F 3 "" H 3600 1550 50  0001 C CNN
	1    3600 1550
	1    0    0    -1  
$EndComp
Connection ~ 3600 1250
Wire Wire Line
	3600 1250 3800 1250
Wire Wire Line
	3400 1250 3600 1250
$Comp
L Connector:USB_C_Receptacle_USB2.0 J1
U 1 1 5FAD3E63
P 4200 3700
F 0 "J1" H 4307 4567 50  0000 C CNN
F 1 "USB-C" H 4307 4476 50  0000 C CNN
F 2 "daisy:USB_C_Receptacle_HRO_TYPE-C-31-M-12" H 4350 3700 50  0001 C CNN
F 3 "https://www.usb.org/sites/default/files/documents/usb_type-c.zip" H 4350 3700 50  0001 C CNN
	1    4200 3700
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5FAE3BB0
P 4200 4600
AR Path="/5B48B53E/5FAE3BB0" Ref="#PWR?"  Part="1" 
AR Path="/5FAE3BB0" Ref="#PWR?"  Part="1" 
AR Path="/5B66D7A7/5FAE3BB0" Ref="#PWR09"  Part="1" 
F 0 "#PWR09" H 4200 4350 50  0001 C CNN
F 1 "GND" H 4200 4450 50  0000 C CNN
F 2 "" H 4200 4600 50  0001 C CNN
F 3 "" H 4200 4600 50  0001 C CNN
	1    4200 4600
	1    0    0    -1  
$EndComp
$Comp
L power:PWR_FLAG #FLG0101
U 1 1 5FB0007D
P 2850 2250
F 0 "#FLG0101" H 2850 2325 50  0001 C CNN
F 1 "PWR_FLAG" H 2850 2423 50  0000 C CNN
F 2 "" H 2850 2250 50  0001 C CNN
F 3 "~" H 2850 2250 50  0001 C CNN
	1    2850 2250
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5FB02165
P 2850 2250
AR Path="/5B48B53B/5FB02165" Ref="#PWR?"  Part="1" 
AR Path="/5FB02165" Ref="#PWR?"  Part="1" 
AR Path="/5B66D7A7/5FB02165" Ref="#PWR0101"  Part="1" 
F 0 "#PWR0101" H 2850 2000 50  0001 C CNN
F 1 "GND" H 2855 2077 50  0000 C CNN
F 2 "" H 2850 2250 50  0001 C CNN
F 3 "" H 2850 2250 50  0001 C CNN
	1    2850 2250
	1    0    0    -1  
$EndComp
$Comp
L power:PWR_FLAG #FLG0102
U 1 1 5FB02AFB
P 3400 2250
F 0 "#FLG0102" H 3400 2325 50  0001 C CNN
F 1 "PWR_FLAG" H 3400 2423 50  0000 C CNN
F 2 "" H 3400 2250 50  0001 C CNN
F 3 "~" H 3400 2250 50  0001 C CNN
	1    3400 2250
	1    0    0    -1  
$EndComp
Text GLabel 3400 2250 3    50   Output ~ 0
vusb
$EndSCHEMATC
