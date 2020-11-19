EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 3 3
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
L power:+3.3V #PWR027
U 1 1 5B6F41FE
P 6700 3250
F 0 "#PWR027" H 6700 3100 50  0001 C CNN
F 1 "+3.3V" H 6715 3423 50  0000 C CNN
F 2 "" H 6700 3250 50  0001 C CNN
F 3 "" H 6700 3250 50  0001 C CNN
	1    6700 3250
	-1   0    0    1   
$EndComp
$Comp
L power:+3.3V #PWR028
U 1 1 5B6F4242
P 6700 4900
F 0 "#PWR028" H 6700 4750 50  0001 C CNN
F 1 "+3.3V" H 6715 5073 50  0000 C CNN
F 2 "" H 6700 4900 50  0001 C CNN
F 3 "" H 6700 4900 50  0001 C CNN
	1    6700 4900
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR022
U 1 1 5B6F42B1
P 6150 4950
F 0 "#PWR022" H 6150 4700 50  0001 C CNN
F 1 "GND" H 6155 4777 50  0000 C CNN
F 2 "" H 6150 4950 50  0001 C CNN
F 3 "" H 6150 4950 50  0001 C CNN
	1    6150 4950
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR021
U 1 1 5B6F42FF
P 6150 3300
F 0 "#PWR021" H 6150 3050 50  0001 C CNN
F 1 "GND" H 6155 3127 50  0000 C CNN
F 2 "" H 6150 3300 50  0001 C CNN
F 3 "" H 6150 3300 50  0001 C CNN
	1    6150 3300
	1    0    0    -1  
$EndComp
Text GLabel 6900 4550 2    50   Input ~ 0
nrst_radio868
Text GLabel 6900 4450 2    50   Output ~ 0
busy_radio868
Text GLabel 6900 4350 2    50   BiDi ~ 0
dio2_radio868
Text GLabel 6900 4250 2    50   BiDi ~ 0
dio1_radio868
Text GLabel 6900 4150 2    50   Input ~ 0
txen_radio868
Text GLabel 6900 4050 2    50   Input ~ 0
rxen_radio868
Text GLabel 6900 2900 2    50   Input ~ 0
nrst_radio433
Text GLabel 6900 2800 2    50   Output ~ 0
busy_radio433
Text GLabel 6900 2700 2    50   BiDi ~ 0
dio2_radio433
Text GLabel 6900 2600 2    50   BiDi ~ 0
dio1_radio433
Text GLabel 6900 2500 2    50   Input ~ 0
txen_radio433
Text GLabel 6900 2400 2    50   Input ~ 0
rxen_radio433
Text GLabel 5500 2400 0    50   Input ~ 0
cs_radio433
Text GLabel 5500 2500 0    50   Input ~ 0
spi_sck
Text GLabel 5500 2700 0    50   Input ~ 0
spi_mosi
Text GLabel 5500 2600 0    50   Output ~ 0
spi_miso
Text GLabel 5500 4050 0    50   Input ~ 0
cs_radio868
Text GLabel 5500 4150 0    50   Input ~ 0
spi_sck
Text GLabel 5500 4350 0    50   Input ~ 0
spi_mosi
Text GLabel 5500 4250 0    50   Output ~ 0
spi_miso
Wire Wire Line
	5500 2850 4900 2850
$Comp
L power:GND #PWR019
U 1 1 5B6F4BDD
P 4700 3050
F 0 "#PWR019" H 4700 2800 50  0001 C CNN
F 1 "GND" H 4705 2877 50  0000 C CNN
F 2 "" H 4700 3050 50  0001 C CNN
F 3 "" H 4700 3050 50  0001 C CNN
	1    4700 3050
	1    0    0    -1  
$EndComp
Wire Wire Line
	5500 4500 4900 4500
$Comp
L Device:C C8
U 1 1 5B6F63A5
P 5850 1200
F 0 "C8" H 5965 1246 50  0000 L CNN
F 1 "1u" H 5965 1155 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 5888 1050 50  0001 C CNN
F 3 "~" H 5850 1200 50  0001 C CNN
	1    5850 1200
	1    0    0    -1  
$EndComp
$Comp
L Device:C C9
U 1 1 5B6F64ED
P 6300 1200
F 0 "C9" H 6415 1246 50  0000 L CNN
F 1 "1u" H 6415 1155 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 6338 1050 50  0001 C CNN
F 3 "~" H 6300 1200 50  0001 C CNN
	1    6300 1200
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR025
U 1 1 5B6F6541
P 6300 1050
F 0 "#PWR025" H 6300 900 50  0001 C CNN
F 1 "+3.3V" H 6315 1223 50  0000 C CNN
F 2 "" H 6300 1050 50  0001 C CNN
F 3 "" H 6300 1050 50  0001 C CNN
	1    6300 1050
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR023
U 1 1 5B6F6594
P 5850 1050
F 0 "#PWR023" H 5850 900 50  0001 C CNN
F 1 "+3.3V" H 5865 1223 50  0000 C CNN
F 2 "" H 5850 1050 50  0001 C CNN
F 3 "" H 5850 1050 50  0001 C CNN
	1    5850 1050
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR026
U 1 1 5B6F65F7
P 6300 1350
F 0 "#PWR026" H 6300 1100 50  0001 C CNN
F 1 "GND" H 6305 1177 50  0000 C CNN
F 2 "" H 6300 1350 50  0001 C CNN
F 3 "" H 6300 1350 50  0001 C CNN
	1    6300 1350
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR024
U 1 1 5B6F6656
P 5850 1350
F 0 "#PWR024" H 5850 1100 50  0001 C CNN
F 1 "GND" H 5855 1177 50  0000 C CNN
F 2 "" H 5850 1350 50  0001 C CNN
F 3 "" H 5850 1350 50  0001 C CNN
	1    5850 1350
	1    0    0    -1  
$EndComp
$Comp
L daisy:E22-EBYTE U4
U 1 1 5FAB2673
P 6200 2650
F 0 "U4" H 6200 3165 50  0000 C CNN
F 1 "E22-EBYTE" H 6200 3074 50  0000 C CNN
F 2 "daisy:E22-EBYTE" H 6250 2650 50  0001 C CNN
F 3 "" H 6250 2650 50  0001 C CNN
	1    6200 2650
	1    0    0    -1  
$EndComp
Wire Wire Line
	6500 3250 6600 3250
$Comp
L daisy:E22-EBYTE U5
U 1 1 5FAB59DA
P 6200 4300
F 0 "U5" H 6200 4815 50  0000 C CNN
F 1 "E22-EBYTE" H 6200 4724 50  0000 C CNN
F 2 "daisy:E22-EBYTE" H 6250 4300 50  0001 C CNN
F 3 "" H 6250 4300 50  0001 C CNN
	1    6200 4300
	1    0    0    -1  
$EndComp
Wire Wire Line
	6500 4900 6600 4900
Wire Wire Line
	5700 4900 5800 4900
Wire Wire Line
	5800 4900 5900 4900
Connection ~ 5800 4900
Wire Wire Line
	5900 4900 6000 4900
Connection ~ 5900 4900
Wire Wire Line
	6000 4900 6100 4900
Connection ~ 6000 4900
Wire Wire Line
	6100 4900 6150 4900
Connection ~ 6100 4900
Wire Wire Line
	6200 4900 6300 4900
Connection ~ 6200 4900
Wire Wire Line
	6300 4900 6400 4900
Connection ~ 6300 4900
Wire Wire Line
	6400 4900 6500 4900
Connection ~ 6400 4900
Connection ~ 6500 4900
Wire Wire Line
	5700 3250 5800 3250
Wire Wire Line
	5800 3250 5900 3250
Connection ~ 5800 3250
Wire Wire Line
	5900 3250 6000 3250
Connection ~ 5900 3250
Wire Wire Line
	6000 3250 6100 3250
Connection ~ 6000 3250
Wire Wire Line
	6100 3250 6150 3250
Connection ~ 6100 3250
Wire Wire Line
	6200 3250 6300 3250
Connection ~ 6200 3250
Wire Wire Line
	6300 3250 6400 3250
Connection ~ 6300 3250
Wire Wire Line
	6400 3250 6500 3250
Connection ~ 6400 3250
Connection ~ 6500 3250
$Comp
L Connector:Conn_Coaxial ANT1
U 1 1 5FAF1689
P 4700 2850
F 0 "ANT1" H 4628 3088 50  0000 C CNN
F 1 "SMA" H 4628 2997 50  0000 C CNN
F 2 "daisy:SMA_Molex_73251-2200_Horizontal" H 4700 2850 50  0001 C CNN
F 3 " ~" H 4700 2850 50  0001 C CNN
	1    4700 2850
	-1   0    0    -1  
$EndComp
$Comp
L Connector:Conn_Coaxial ANT2
U 1 1 5FAF663A
P 4700 4500
F 0 "ANT2" H 4628 4738 50  0000 C CNN
F 1 "SMA" H 4628 4647 50  0000 C CNN
F 2 "daisy:SMA_Molex_73251-2200_Horizontal" H 4700 4500 50  0001 C CNN
F 3 " ~" H 4700 4500 50  0001 C CNN
	1    4700 4500
	-1   0    0    -1  
$EndComp
$Comp
L power:GND #PWR020
U 1 1 5FAF702A
P 4700 4700
F 0 "#PWR020" H 4700 4450 50  0001 C CNN
F 1 "GND" H 4705 4527 50  0000 C CNN
F 2 "" H 4700 4700 50  0001 C CNN
F 3 "" H 4700 4700 50  0001 C CNN
	1    4700 4700
	1    0    0    -1  
$EndComp
Wire Wire Line
	6150 3250 6150 3300
Connection ~ 6150 3250
Wire Wire Line
	6150 3250 6200 3250
Wire Wire Line
	6150 4900 6150 4950
Connection ~ 6150 4900
Wire Wire Line
	6150 4900 6200 4900
$EndSCHEMATC
