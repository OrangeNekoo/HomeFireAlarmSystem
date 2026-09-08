# SSD1306

Advance Information 

128 x 64 Dot Matrix 

OLED/PLED Segment/Common Driver with Controller 

## CONTENTS

1 GENERAL DESCRIPTION....6
2 FEATURES....6
3 ORDERING INFORMATION....6
4 BLOCK DIAGRAM....7
5 DIE PAD FLOOR PLAN....8
6 PIN ARRANGEMENT....11
6.1 SSD1306TR1 PIN ASSIGNMENT....11
7 PIN DESCRIPTION....13
8 FUNCTIONAL BLOCK DESCRIPTIONS....15
8.1 MCU INTERFACE SELECTION....15
8.1.1 MCU Parallel 6800-series Interface....15
8.1.2 MCU Parallel 8080-series Interface....16
8.1.3 MCU Serial Interface (4-wire SPI)....17
8.1.4 MCU Serial Interface (3-wire SPI)....18
8.1.5 MCU I²C Interface....19
8.2 COMMAND DECODER....22
8.3 OSCILLATOR CIRCUIT AND DISPLAY TIME GENERATOR....22
8.4 FR SYNCHRONIZATION....23
8.5 RESET CIRCUIT....23
8.6 SEGMENT DRIVERS / COMMON DRIVERS....24
8.7 GRAPHIC DISPLAY DATA RAM (GDDRAM)....25
8.8 SEG/COM DRIVING BLOCK....26
8.9 POWER ON AND OFF SEQUENCE....27
9 COMMAND TABLE....28
9.1 DATA READ / WRITE....33
10 COMMAND DESCRIPTIONS....34
10.1 FUNDAMENTAL COMMAND....34
10.1.1 Set Lower Column Start Address for Page Addressing Mode (00h~0Fh)....34
10.1.2 Set Higher Column Start Address for Page Addressing Mode (10h~1Fh)....34
10.1.3 Set Memory Addressing Mode (20h)....34
10.1.4 Set Column Address (21h)....35
10.1.5 Set Page Address (22h)....36
10.1.6 Set Display Start Line (40h~7Fh)....36
10.1.7 Set Contrast Control for BANK0 (81h)....36
10.1.8 Set Segment Re-map (A0h/A1h)....36
10.1.9 Entire Display ON (A4h/A5h)....37
10.1.10 Set Normal/Inverse Display (A6h/A7h)....37
10.1.11 Set Multiplex Ratio (A8h)....37
10.1.12 Set Display ON/OFF (AEh/AFh)....37
10.1.13 Set Page Start Address for Page Addressing Mode (B0h~B7h)....37
10.1.14 Set COM Output Scan Direction (C0h/C8h)....37
10.1.15 Set Display Offset (D3h)....37
10.1.16 Set Display Clock Divide Ratio/ Oscillator Frequency (D5h)....40
10.1.17 Set Pre-charge Period (D9h)....40
10.1.18 Set COM Pins Hardware Configuration (DAh)....40
10.1.19 Set VCOMH Deselect Level (DBh)....43 

10.1.20 NOP (E3h)....43
10.1.21 Status register Read....43
10.2 GRAPHIC ACCELERATION COMMAND....44
10.2.1 Horizontal Scroll Setup (26h/27h)....44
10.2.2 Continuous Vertical and Horizontal Scroll Setup (29h/2Ah)....45
10.2.3 Deactivate Scroll (2Eh)....46
10.2.4 Activate Scroll (2Fh)....46
10.2.5 Set Vertical Scroll Area(A3h)....46
11 MAXIMUM RATINGS....47
12 DC CHARACTERISTICS....48
13 AC CHARACTERISTICS....49
14 APPLICATION EXAMPLE....55
15 PACKAGE INFORMATION....56
15.1 SSD1306TR1 DETAIL DIMENSION....56
15.2 SSD1306Z DIE TRAY INFORMATION....58 

## TABLES

TABLE 5-1 : SSD1306Z BUMP DIE PAD COORDINATES....10
TABLE 6-1 : SSD1306TR1 PIN ASSIGNMENT TABLE....12
TABLE 7-1 : MCU BUS INTERFACE PIN SELECTION....14
TABLE 8-1 : MCU INTERFACE ASSIGNMENT UNDER DIFFERENT BUS INTERFACE MODE....15
TABLE 8-2 : CONTROL PINS OF 6800 INTERFACE....15
TABLE 8-3 : CONTROL PINS OF 8080 INTERFACE....17
TABLE 8-4 : CONTROL PINS OF 4-WIRE SERIAL INTERFACE....17
TABLE 8-5 : CONTROL PINS OF 3-WIRE SERIAL INTERFACE....18
TABLE 9-1 : COMMAND TABLE....28
TABLE 9-2 : READ COMMAND TABLE....33
TABLE 9-3 : ADDRESS INCREMENT TABLE (AUTOMATIC)....33
TABLE 10-1 : EXAMPLE OF SET DISPLAY OFFSET AND DISPLAY START LINE WITH NO REMAP....38
TABLE 10-2 : EXAMPLE OF SET DISPLAY OFFSET AND DISPLAY START LINE WITH REMAP....39
TABLE 10-3 : COM PINS HARDWARE CONFIGURATION....40
TABLE 11-1 : MAXIMUM RATINGS (VOLTAGE REFERENCED TO VSS)....47
TABLE 12-1 : DC CHARACTERISTICS....48
TABLE 13-1 : AC CHARACTERISTICS....49
TABLE 13-2 : 6800-SERIES MCU PARALLEL INTERFACE TIMING CHARACTERISTICS....50
TABLE 13-3 : 8080-SERIES MCU PARALLEL INTERFACE TIMING CHARACTERISTICS....51
TABLE 13-4 : 4-WIRE SERIAL INTERFACE TIMING CHARACTERISTICS....52
TABLE 13-5 : 3-WIRE SERIAL INTERFACE TIMING CHARACTERISTICS....53
TABLE 13-6 : I²C INTERFACE TIMING CHARACTERISTICS....54 

## FIGURES

FIGURE 4-1 SSD1306 BLOCK DIAGRAM .... 7
FIGURE 5-1 : SSD1306Z DIE DRAWING .... 8
FIGURE 5-2 : SSD1306Z ALIGNMENT MARK DIMENSIONS .... 9
FIGURE 6-1 : SSD1306TR1 PIN ASSIGNMENT .... 11
FIGURE 7-1 PIN DESCRIPTION .... 13
FIGURE 8-1 : DATA READ BACK PROCEDURE - INSERTION OF DUMMY READ .... 16
FIGURE 8-2 : EXAMPLE OF WRITE PROCEDURE IN 8080 PARALLEL INTERFACE MODE .... 16
FIGURE 8-3 : EXAMPLE OF READ PROCEDURE IN 8080 PARALLEL INTERFACE MODE .... 16
FIGURE 8-4 : DISPLAY DATA READ BACK PROCEDURE - INSERTION OF DUMMY READ .... 17
FIGURE 8-5 : WRITE PROCEDURE IN 4-WIRE SERIAL INTERFACE MODE .... 18
FIGURE 8-6 : WRITE PROCEDURE IN 3-WIRE SERIAL INTERFACE MODE .... 18
FIGURE 8-7 : I²C-BUS DATA FORMAT .... 20
FIGURE 8-8 : DEFINITION OF THE START AND STOP CONDITION .... 21
FIGURE 8-9 : DEFINITION OF THE ACKNOWLEDGEMENT CONDITION .... 21
FIGURE 8-10 : DEFINITION OF THE DATA TRANSFER CONDITION .... 21
FIGURE 8-11 : OSCILLATOR CIRCUIT AND DISPLAY TIME GENERATOR .... 22
FIGURE 8-12 : SEGMENT OUTPUT WAVEFORM IN THREE PHASES .... 24
FIGURE 8-13 : GDDRAM PAGES STRUCTURE OF SSD1306 .... 25
FIGURE 8-14 : ENLARGEMENT OF GDDRAM (NO ROW RE-MAPPING AND COLUMN-REMAPPING) .... 25
FIGURE 8-15 : IREF CURRENT SETTING BY RESISTOR VALUE .... 26
FIGURE 8-16 : THE POWER ON SEQUENCE .... 27
FIGURE 8-17 : THE POWER OFF SEQUENCE .... 27
FIGURE 10-1 : ADDRESS POINTER MOVEMENT OF PAGE ADDRESSING MODE .... 34
FIGURE 10-2 : EXAMPLE OF GDDRAM ACCESS POINTER SETTING IN PAGE ADDRESSING MODE (NO ROW AND COLUMN-REMAPPING) .... 34
FIGURE 10-3 : ADDRESS POINTER MOVEMENT OF HORIZONTAL ADDRESSING MODE .... 35
FIGURE 10-4 : ADDRESS POINTER MOVEMENT OF VERTICAL ADDRESSING MODE .... 35
FIGURE 10-5 : EXAMPLE OF COLUMN AND ROW ADDRESS POINTER MOVEMENT .... 36
FIGURE 10-6 : TRANSITION BETWEEN DIFFERENT MODES .... 37
FIGURE 10-7 : HORIZONTAL SCROLL EXAMPLE: SCROLL RIGHT BY 1 COLUMN.... 44
FIGURE 10-8 : HORIZONTAL SCROLL EXAMPLE: SCROLL LEFT BY 1 COLUMN.... 44
FIGURE 10-9 : HORIZONTAL SCROLLING SETUP EXAMPLE.... 44
FIGURE 10-10 : CONTINUOUS VERTICAL AND HORIZONTAL SCROLLING SETUP EXAMPLE.... 45
FIGURE 13-1 : 6800-SERIES MCU PARALLEL INTERFACE CHARACTERISTICS.... 50
FIGURE 13-2 : 8080-SERIES PARALLEL INTERFACE CHARACTERISTICS.... 51
FIGURE 13-3 : 4-WIRE SERIAL INTERFACE CHARACTERISTICS.... 52
FIGURE 13-4 : 3-WIRE SERIAL INTERFACE CHARACTERISTICS.... 53
FIGURE 13-5 : I²C INTERFACE TIMING CHARACTERISTICS.... 54
FIGURE 14-1 : APPLICATION EXAMPLE OF SSD1306Z .... 55
FIGURE 15-1 SSD1306TR1 DETAIL DIMENSION.... 56
FIGURE 15-2 : SSD1306Z DIE TRAY INFORMATION .... 58 

## 1 GENERAL DESCRIPTION

SSD1306 is a single-chip CMOS OLED/PLED driver with controller for organic / polymer light emitting diode dot-matrix graphic display system. It consists of 128 segments and 64commons. This IC is designed for Common Cathode type OLED panel. 

The SSD1306 embeds with contrast control, display RAM and oscillator, which reduces the number of external components and power consumption. It has 256-step brightness control. Data/Commands are sent from general MCU through the hardware selectable 6800/8000 series compatible Parallel Interface, I<sup>2</sup>C interface or Serial Peripheral Interface. It is suitable for many compact portable applications, such as mobile phone sub-display, MP3 player and calculator, etc. 

## 2 FEATURES

Resolution: 128 x 64 dot matrix panel 

• Power supply 

o V<sub>DD</sub> = 1.65V to 3.3V for IC logic 

o $\mathrm { v _ { C C } } = 7 \mathrm { v }$ to 15V for Panel driving 

• For matrix display 

o OLED driving output voltage, 15V maximum 

o Segment maximum source current: 100uA 

o Common maximum sink current: 15mA 

o 256 step contrast brightness current control 

• Embedded 128 x 64 bit SRAM display buffer 

• Pin selectable MCU Interfaces: 

o 8-bit 6800/8080-series parallel interface 

o 3 /4 wire Serial Peripheral Interface 

o I<sup>2</sup>C Interface 

• Screen saving continuous scrolling function in both horizontal and vertical direction 

• RAM write synchronization signal 

• Programmable Frame Rate and Multiplexing Ratio 

• Row Re-mapping and Column Re-mapping 

• On-Chip Oscillator 

• Chip layout for COG & COF 

• Wide range of operating temperature: ${ } _ { - 4 0 ^ { \circ } \mathrm { C } }$ to $8 5 \mathrm { { ^ \circ C } }$ 

## 3 ORDERING INFORMATION


Table 3-1: Ordering Information


<table><tr><td>Ordering Part Number</td><td>SEG</td><td>COM</td><td>Package Form</td><td>Reference</td><td>Remark</td></tr><tr><td>SSD1306Z</td><td>128</td><td>64</td><td>COG</td><td>8</td><td>○ Min SEG pad pitch : 47um○ Min COM pad pitch : 40um○ Die thickness: 300 +/- 25um</td></tr><tr><td>SSD1306TR1</td><td>104</td><td>48</td><td>TAB</td><td>11, 56</td><td>○ 35mm film, 4 sprocket hole, Folding TAB○ 8-bit 80 / 8-bit 68 / SPI / <eq>I^{2}C</eq> interface○ SEG, COM lead pitch 0.1mm x 0.997=0.0997mm○ Die thickness: 457 +/- 25um</td></tr></table>


Figure 4-1 SSD1306 Block Diagram


![image](https://cdn-mineru.openxlab.org.cn/result/2026-09-08/61e8663c-ef74-4a31-bef6-08879770bc52/08ae4e85666977f6bea30b04ca3cf1f3741c7dbc4240f7d508c55adcfb2e3aa6.jpg)


Gold Bumps face up 

Pad 1 ▶000000000000000000 


Figure 5-1 : SSD1306Z Die Drawing


<table><tr><td>Die size</td><td>6.76mm x 0.86mm</td></tr><tr><td>Die thickness</td><td>300 +/- 25um</td></tr><tr><td>Min I/O pad pitch</td><td>60um</td></tr><tr><td>Min SEG pad pitch</td><td>47um</td></tr><tr><td>Min COM pad pitch</td><td>40um</td></tr><tr><td>Bump height</td><td>Nominal 15um</td></tr></table>

<table><tr><td>Bump size</td><td></td></tr><tr><td>Pad 1, 106, 124, 256</td><td>80um x 50um</td></tr><tr><td>Pad 2-18, 89-105, 107-123, 257-273</td><td>25ium x 80um</td></tr><tr><td>Pad 19-88</td><td>40um x 89um</td></tr><tr><td>Pad 125-255</td><td>31um x 59um</td></tr><tr><td>Pad 274-281 (TR pads)</td><td>30um x 50um</td></tr></table>

<table><tr><td>Alignment mark</td><td>Position</td><td>Size</td></tr><tr><td>+ shape</td><td>(-2973, 0)</td><td>75um x 75um</td></tr><tr><td>+ shape</td><td>(2973, 0)</td><td>75um x 75um</td></tr><tr><td>Circle</td><td>(2466.665, 7.575)</td><td>R37.5um, inner 18um</td></tr><tr><td>SSL Logo</td><td>(-2862.35, 144.82)</td><td>-</td></tr></table>


(For details dimension please see p.9 ) 



Note 



<sup>(1)</sup> Diagram showing the Gold bumps face up. 


<sup>(2)</sup> Coordinates are referenced to center of the chip. 

<sup>(3)</sup> Coordinate units and size of all alignment marks are in um. 

<sup>(4)</sup> All alignment keys do not contain gold 

![image](https://cdn-mineru.openxlab.org.cn/result/2026-09-08/61e8663c-ef74-4a31-bef6-08879770bc52/4c438fb1b6ea9b3142d1caff101ffb15d52c29d22ad7da1e5187bf4bc2487f2f.jpg)



0000000000000000000



Figure 5-2 : SSD1306Z alignment mark dimensions


![image](https://cdn-mineru.openxlab.org.cn/result/2026-09-08/61e8663c-ef74-4a31-bef6-08879770bc52/034062046635a5c842d9c55be8981f3520c22f87625fc59db88f5b066b89cc00.jpg)



*All units are in um


<table><tr><td>Pad no.</td><td>Pad Name</td><td>X-pos</td><td>Y-pos</td></tr><tr><td>1</td><td>NC</td><td>-3315</td><td>-377.5</td></tr><tr><td>2</td><td>VSS</td><td>-3084.77</td><td>-362.5</td></tr><tr><td>3</td><td>COM49</td><td>-3044.77</td><td>-362.5</td></tr><tr><td>4</td><td>COM50</td><td>-3004.77</td><td>-362.5</td></tr><tr><td>5</td><td>COM51</td><td>-2964.77</td><td>-362.5</td></tr><tr><td>6</td><td>COM52</td><td>-2924.77</td><td>-362.5</td></tr><tr><td>7</td><td>COM53</td><td>-2884.77</td><td>-362.5</td></tr><tr><td>8</td><td>COM54</td><td>-2844.77</td><td>-362.5</td></tr><tr><td>9</td><td>COM55</td><td>-2804.77</td><td>-362.5</td></tr><tr><td>10</td><td>COM56</td><td>-2764.77</td><td>-362.5</td></tr><tr><td>11</td><td>COM57</td><td>-2724.77</td><td>-362.5</td></tr><tr><td>12</td><td>COM58</td><td>-2684.77</td><td>-362.5</td></tr><tr><td>13</td><td>COM59</td><td>-2644.77</td><td>-362.5</td></tr><tr><td>14</td><td>COM60</td><td>-2604.77</td><td>-362.5</td></tr><tr><td>15</td><td>COM61</td><td>-2564.77</td><td>-362.5</td></tr><tr><td>16</td><td>COM62</td><td>-2524.77</td><td>-362.5</td></tr><tr><td>17</td><td>COM63</td><td>-2484.77</td><td>-362.5</td></tr><tr><td>18</td><td>VCOMH</td><td>-2444.77</td><td>-362.5</td></tr><tr><td>19</td><td>NC</td><td>-2334.965</td><td>-352.83</td></tr><tr><td>20</td><td>C2P</td><td>-2278.265</td><td>-352.83</td></tr><tr><td>21</td><td>C2P</td><td>-2218.265</td><td>-352.83</td></tr><tr><td>22</td><td>C2N</td><td>-2136.715</td><td>-352.83</td></tr><tr><td>23</td><td>C2N</td><td>-2055.465</td><td>-352.83</td></tr><tr><td>24</td><td>C1P</td><td>-1995.465</td><td>-352.83</td></tr><tr><td>25</td><td>C1P</td><td>-1904.115</td><td>-352.83</td></tr><tr><td>26</td><td>C1N</td><td>-1844.115</td><td>-352.83</td></tr><tr><td>27</td><td>C1N</td><td>-1762.865</td><td>-352.83</td></tr><tr><td>28</td><td>VBAT</td><td>-1679.31</td><td>-352.83</td></tr><tr><td>29</td><td>VBAT</td><td>-1619.31</td><td>-352.83</td></tr><tr><td>30</td><td>VBREF</td><td>-1537.51</td><td>-352.83</td></tr><tr><td>31</td><td>BGGND</td><td>-1477.51</td><td>-352.83</td></tr><tr><td>32</td><td>VCC</td><td>-1416.01</td><td>-352.83</td></tr><tr><td>33</td><td>VCC</td><td>-1356.01</td><td>-352.83</td></tr><tr><td>34</td><td>VCOMH</td><td>-1266.955</td><td>-352.83</td></tr><tr><td>35</td><td>VCOMH</td><td>-1206.955</td><td>-352.83</td></tr><tr><td>36</td><td>VLSS</td><td>-1125.155</td><td>-352.83</td></tr><tr><td>37</td><td>VLSS</td><td>-1043.355</td><td>-352.83</td></tr><tr><td>38</td><td>VLSS</td><td>-983.355</td><td>-352.83</td></tr><tr><td>39</td><td>VSS</td><td>-920</td><td>-352.83</td></tr><tr><td>40</td><td>VSS</td><td>-856</td><td>-352.83</td></tr><tr><td>41</td><td>VSS</td><td>-796</td><td>-352.83</td></tr><tr><td>42</td><td>VDD</td><td>-732.645</td><td>-352.83</td></tr><tr><td>43</td><td>VDD</td><td>-672.645</td><td>-352.83</td></tr><tr><td>44</td><td>BS0</td><td>-595.655</td><td>-352.83</td></tr><tr><td>45</td><td>VSS</td><td>-531.955</td><td>-352.83</td></tr><tr><td>46</td><td>BS1</td><td>-467.655</td><td>-352.83</td></tr><tr><td>47</td><td>VDD</td><td>-403.155</td><td>-352.83</td></tr><tr><td>48</td><td>VDD</td><td>-342.555</td><td>-352.83</td></tr><tr><td>49</td><td>BS2</td><td>-279.705</td><td>-352.83</td></tr><tr><td>50</td><td>VSS</td><td>-215.705</td><td>-352.83</td></tr><tr><td>51</td><td>FR</td><td>-151.955</td><td>-352.83</td></tr><tr><td>52</td><td>CL</td><td>-89.815</td><td>-352.83</td></tr><tr><td>53</td><td>VSS</td><td>-25.665</td><td>-352.83</td></tr><tr><td>54</td><td>CS#</td><td>38.635</td><td>-352.83</td></tr><tr><td>55</td><td>RES#</td><td>109.835</td><td>-352.83</td></tr><tr><td>56</td><td>D/C#</td><td>182.425</td><td>-352.83</td></tr><tr><td>57</td><td>VSS</td><td>246.125</td><td>-352.83</td></tr><tr><td>58</td><td>R/W#</td><td>310.425</td><td>-352.83</td></tr><tr><td>59</td><td>E</td><td>373.125</td><td>-352.83</td></tr><tr><td>60</td><td>VDD</td><td>457.175</td><td>-352.83</td></tr><tr><td>61</td><td>VDD</td><td>517.175</td><td>-352.83</td></tr><tr><td>62</td><td>D0</td><td>609.275</td><td>-352.83</td></tr><tr><td>63</td><td>D1</td><td>692.475</td><td>-352.83</td></tr><tr><td>64</td><td>D2</td><td>765.675</td><td>-352.83</td></tr><tr><td>65</td><td>D3</td><td>828.875</td><td>-352.83</td></tr><tr><td>66</td><td>VSS</td><td>890.325</td><td>-352.83</td></tr><tr><td>67</td><td>D4</td><td>951.275</td><td>-352.83</td></tr><tr><td>68</td><td>D5</td><td>1013.315</td><td>-352.83</td></tr><tr><td>69</td><td>D6</td><td>1075.355</td><td>-352.83</td></tr><tr><td>70</td><td>D7</td><td>1137.395</td><td>-352.83</td></tr><tr><td>71</td><td>VSS</td><td>1220.735</td><td>-352.83</td></tr><tr><td>72</td><td>VSS</td><td>1280.735</td><td>-352.83</td></tr><tr><td>73</td><td>CLS</td><td>1362.585</td><td>-352.83</td></tr><tr><td>74</td><td>VDD</td><td>1425.285</td><td>-352.83</td></tr><tr><td>75</td><td>VDD</td><td>1485.885</td><td>-352.83</td></tr><tr><td>76</td><td>VDD</td><td>1553.185</td><td>-352.83</td></tr><tr><td>77</td><td>VDD</td><td>1613.185</td><td>-352.83</td></tr><tr><td>78</td><td>IREF</td><td>1684.585</td><td>-352.83</td></tr><tr><td>79</td><td>IREF</td><td>1744.585</td><td>-352.83</td></tr><tr><td>80</td><td>VCOMH</td><td>1815.585</td><td>-352.83</td></tr></table>


Table 5-1 : SSD1306Z Bump Die Pad Coordinates


<table><tr><td>Pad no.</td><td>Pad Name</td><td>X-pos</td><td>Y-pos</td></tr><tr><td>81</td><td>VCOMH</td><td>1875.585</td><td>-352.83</td></tr><tr><td>82</td><td>VCC</td><td>1967.185</td><td>-352.83</td></tr><tr><td>83</td><td>VCC</td><td>2027.185</td><td>-352.83</td></tr><tr><td>84</td><td>VLSS</td><td>2109.185</td><td>-352.83</td></tr><tr><td>85</td><td>VLSS</td><td>2169.185</td><td>-352.83</td></tr><tr><td>86</td><td>VLSS</td><td>2254.185</td><td>-352.83</td></tr><tr><td>87</td><td>NC</td><td>2314.185</td><td>-352.83</td></tr><tr><td>88</td><td>NC</td><td>2374.185</td><td>-352.83</td></tr><tr><td>89</td><td>VSS</td><td>2444.77</td><td>-362.5</td></tr><tr><td>90</td><td>COM31</td><td>2484.77</td><td>-362.5</td></tr><tr><td>91</td><td>COM30</td><td>2524.77</td><td>-362.5</td></tr><tr><td>92</td><td>COM29</td><td>2564.77</td><td>-362.5</td></tr><tr><td>93</td><td>COM28</td><td>2604.77</td><td>-362.5</td></tr><tr><td>94</td><td>COM27</td><td>2644.77</td><td>-362.5</td></tr><tr><td>95</td><td>COM26</td><td>2684.77</td><td>-362.5</td></tr><tr><td>96</td><td>COM25</td><td>2724.77</td><td>-362.5</td></tr><tr><td>97</td><td>COM24</td><td>2764.77</td><td>-362.5</td></tr><tr><td>98</td><td>COM23</td><td>2804.77</td><td>-362.5</td></tr><tr><td>99</td><td>COM22</td><td>2844.77</td><td>-362.5</td></tr><tr><td>100</td><td>COM21</td><td>2884.77</td><td>-362.5</td></tr><tr><td>101</td><td>COM20</td><td>2924.77</td><td>-362.5</td></tr><tr><td>102</td><td>COM19</td><td>2964.77</td><td>-362.5</td></tr><tr><td>103</td><td>COM18</td><td>3004.77</td><td>-362.5</td></tr><tr><td>104</td><td>COM17</td><td>3044.77</td><td>-362.5</td></tr><tr><td>105</td><td>VSS</td><td>3084.77</td><td>-362.5</td></tr><tr><td>106</td><td>NC</td><td>3315</td><td>-377.5</td></tr><tr><td>107</td><td>COM16</td><td>3315</td><td>-325</td></tr><tr><td>108</td><td>COM15</td><td>3315</td><td>-285</td></tr><tr><td>109</td><td>COM14</td><td>3315</td><td>-245</td></tr><tr><td>110</td><td>COM13</td><td>3315</td><td>-205</td></tr><tr><td>111</td><td>COM12</td><td>3315</td><td>-165</td></tr><tr><td>112</td><td>COM11</td><td>3315</td><td>-125</td></tr><tr><td>113</td><td>COM10</td><td>3315</td><td>-85</td></tr><tr><td>114</td><td>COM9</td><td>3315</td><td>-45</td></tr><tr><td>115</td><td>COM8</td><td>3315</td><td>-5</td></tr><tr><td>116</td><td>COM7</td><td>3315</td><td>35</td></tr><tr><td>117</td><td>COM6</td><td>3315</td><td>75</td></tr><tr><td>118</td><td>COM5</td><td>3315</td><td>115</td></tr><tr><td>119</td><td>COM4</td><td>3315</td><td>155</td></tr><tr><td>120</td><td>COM3</td><td>3315</td><td>195</td></tr><tr><td>121</td><td>COM2</td><td>3315</td><td>235</td></tr><tr><td>122</td><td>COM1</td><td>3315</td><td>275</td></tr><tr><td>123</td><td>COM0</td><td>3315</td><td>315</td></tr><tr><td>124</td><td>NC</td><td>3315</td><td>367.5</td></tr><tr><td>125</td><td>NC</td><td>3055.5</td><td>356</td></tr><tr><td>126</td><td>SEG0</td><td>3009.5</td><td>356</td></tr><tr><td>127</td><td>SEG1</td><td>2962.5</td><td>356</td></tr><tr><td>128</td><td>SEG2</td><td>2915.5</td><td>356</td></tr><tr><td>129</td><td>SEG3</td><td>2868.5</td><td>356</td></tr><tr><td>130</td><td>SEG4</td><td>2821.5</td><td>356</td></tr><tr><td>131</td><td>SEG5</td><td>2774.5</td><td>356</td></tr><tr><td>132</td><td>SEG6</td><td>2727.5</td><td>356</td></tr><tr><td>133</td><td>SEG7</td><td>2680.5</td><td>356</td></tr><tr><td>134</td><td>SEG8</td><td>2633.5</td><td>356</td></tr><tr><td>135</td><td>SEG9</td><td>2586.5</td><td>356</td></tr><tr><td>136</td><td>SEG10</td><td>2539.5</td><td>356</td></tr><tr><td>137</td><td>SEG11</td><td>2492.5</td><td>356</td></tr><tr><td>138</td><td>SEG12</td><td>2445.5</td><td>356</td></tr><tr><td>139</td><td>SEG13</td><td>2398.5</td><td>356</td></tr><tr><td>140</td><td>SEG14</td><td>2351.5</td><td>356</td></tr><tr><td>141</td><td>SEG15</td><td>2304.5</td><td>356</td></tr><tr><td>142</td><td>SEG16</td><td>2257.5</td><td>356</td></tr><tr><td>143</td><td>SEG17</td><td>2210.5</td><td>356</td></tr><tr><td>144</td><td>SEG18</td><td>2163.5</td><td>356</td></tr><tr><td>145</td><td>SEG19</td><td>2116.5</td><td>356</td></tr><tr><td>146</td><td>SEG20</td><td>2069.5</td><td>356</td></tr><tr><td>147</td><td>SEG21</td><td>2022.5</td><td>356</td></tr><tr><td>148</td><td>SEG22</td><td>1975.5</td><td>356</td></tr><tr><td>149</td><td>SEG23</td><td>1928.5</td><td>356</td></tr><tr><td>150</td><td>SEG24</td><td>1881.5</td><td>356</td></tr><tr><td>151</td><td>SEG25</td><td>1834.5</td><td>356</td></tr><tr><td>152</td><td>SEG26</td><td>1787.5</td><td>356</td></tr><tr><td>153</td><td>SEG27</td><td>1740.5</td><td>356</td></tr><tr><td>154</td><td>SEG28</td><td>1693.5</td><td>356</td></tr><tr><td>155</td><td>SEG29</td><td>1646.5</td><td>356</td></tr><tr><td>156</td><td>SEG30</td><td>1599.5</td><td>356</td></tr><tr><td>157</td><td>SEG31</td><td>1552.5</td><td>356</td></tr><tr><td>158</td><td>SEG32</td><td>1505.5</td><td>356</td></tr><tr><td>159</td><td>SEG33</td><td>1458.5</td><td>356</td></tr><tr><td>160</td><td>SEG34</td><td>1411.5</td><td>356</td></tr></table>

<table><tr><td>Pad no.</td><td>Pad Name</td><td>X-pos</td><td>Y-pos</td></tr><tr><td>161</td><td>SEG35</td><td>1364.5</td><td>356</td></tr><tr><td>162</td><td>SEG36</td><td>1317.5</td><td>356</td></tr><tr><td>163</td><td>SEG37</td><td>1270.5</td><td>356</td></tr><tr><td>164</td><td>SEG38</td><td>1223.5</td><td>356</td></tr><tr><td>165</td><td>SEG39</td><td>1176.5</td><td>356</td></tr><tr><td>166</td><td>SEG40</td><td>1129.5</td><td>356</td></tr><tr><td>167</td><td>SEG41</td><td>1082.5</td><td>356</td></tr><tr><td>168</td><td>SEG42</td><td>1035.5</td><td>356</td></tr><tr><td>169</td><td>SEG43</td><td>988.5</td><td>356</td></tr><tr><td>170</td><td>SEG44</td><td>941.5</td><td>356</td></tr><tr><td>171</td><td>SEG45</td><td>894.5</td><td>356</td></tr><tr><td>172</td><td>SEG46</td><td>847.5</td><td>356</td></tr><tr><td>173</td><td>SEG47</td><td>800.5</td><td>356</td></tr><tr><td>174</td><td>SEG48</td><td>753.5</td><td>356</td></tr><tr><td>175</td><td>SEG49</td><td>706.5</td><td>356</td></tr><tr><td>176</td><td>SEG50</td><td>659.5</td><td>356</td></tr><tr><td>177</td><td>SEG51</td><td>612.5</td><td>356</td></tr><tr><td>178</td><td>SEG52</td><td>565.5</td><td>356</td></tr><tr><td>179</td><td>SEG53</td><td>518.5</td><td>356</td></tr><tr><td>180</td><td>SEG54</td><td>471.5</td><td>356</td></tr><tr><td>181</td><td>SEG55</td><td>424.5</td><td>356</td></tr><tr><td>182</td><td>SEG56</td><td>377.5</td><td>356</td></tr><tr><td>183</td><td>SEG57</td><td>330.5</td><td>356</td></tr><tr><td>184</td><td>SEG58</td><td>283.5</td><td>356</td></tr><tr><td>185</td><td>SEG59</td><td>236.5</td><td>356</td></tr><tr><td>186</td><td>SEG60</td><td>189.5</td><td>356</td></tr><tr><td>187</td><td>SEG61</td><td>142.5</td><td>356</td></tr><tr><td>188</td><td>SEG62</td><td>95.5</td><td>356</td></tr><tr><td>189</td><td>SEG63</td><td>48.5</td><td>356</td></tr><tr><td>190</td><td>SEG64</td><td>1.5</td><td>356</td></tr><tr><td>191</td><td>SEG65</td><td>-45.5</td><td>356</td></tr><tr><td>192</td><td>SEG66</td><td>-92.5</td><td>356</td></tr><tr><td>193</td><td>SEG67</td><td>-139.5</td><td>356</td></tr><tr><td>194</td><td>SEG68</td><td>-186.5</td><td>356</td></tr><tr><td>195</td><td>SEG69</td><td>-233.5</td><td>356</td></tr><tr><td>196</td><td>SEG70</td><td>-280.5</td><td>356</td></tr><tr><td>197</td><td>SEG71</td><td>-327.5</td><td>356</td></tr><tr><td>198</td><td>SEG72</td><td>-374.5</td><td>356</td></tr><tr><td>199</td><td>SEG73</td><td>-421.5</td><td>356</td></tr><tr><td>200</td><td>SEG74</td><td>-468.5</td><td>356</td></tr><tr><td>201</td><td>SEG75</td><td>-515.5</td><td>356</td></tr><tr><td>202</td><td>SEG76</td><td>-562.5</td><td>356</td></tr><tr><td>203</td><td>SEG77</td><td>-609.5</td><td>356</td></tr><tr><td>204</td><td>SEG78</td><td>-656.5</td><td>356</td></tr><tr><td>205</td><td>SEG79</td><td>-703.5</td><td>356</td></tr><tr><td>206</td><td>SEG80</td><td>-750.5</td><td>356</td></tr><tr><td>207</td><td>SEG81</td><td>-797.5</td><td>356</td></tr><tr><td>208</td><td>SEG82</td><td>-844.5</td><td>356</td></tr><tr><td>209</td><td>SEG83</td><td>-891.5</td><td>356</td></tr><tr><td>210</td><td>NC</td><td>-940</td><td>356</td></tr><tr><td>211</td><td>SEG84</td><td>-988.5</td><td>356</td></tr><tr><td>212</td><td>SEG85</td><td>-1035.5</td><td>356</td></tr><tr><td>213</td><td>SEG86</td><td>-1082.5</td><td>356</td></tr><tr><td>214</td><td>SEG87</td><td>-1129.5</td><td>356</td></tr><tr><td>215</td><td>SEG88</td><td>-1176.5</td><td>356</td></tr><tr><td>216</td><td>SEG89</td><td>-1223.5</td><td>356</td></tr><tr><td>217</td><td>SEG90</td><td>-1270.5</td><td>356</td></tr><tr><td>218</td><td>SEG91</td><td>-1317.5</td><td>356</td></tr><tr><td>219</td><td>SEG92</td><td>-1364.5</td><td>356</td></tr><tr><td>220</td><td>SEG93</td><td>-1411.5</td><td>356</td></tr><tr><td>221</td><td>SEG94</td><td>-1458.5</td><td>356</td></tr><tr><td>222</td><td>SEG95</td><td>-1505.5</td><td>356</td></tr><tr><td>223</td><td>SEG96</td><td>-1552.5</td><td>356</td></tr><tr><td>224</td><td>SEG97</td><td>-1599.5</td><td>356</td></tr><tr><td>225</td><td>SEG98</td><td>-1646.5</td><td>356</td></tr><tr><td>226</td><td>SEG99</td><td>-1693.5</td><td>356</td></tr><tr><td>227</td><td>SEG100</td><td>-1740.5</td><td>356</td></tr><tr><td>228</td><td>SEG101</td><td>-1787.5</td><td>356</td></tr><tr><td>229</td><td>SEG102</td><td>-1834.5</td><td>356</td></tr><tr><td>230</td><td>SEG103</td><td>-1881.5</td><td>356</td></tr><tr><td>231</td><td>SEG104</td><td>-1928.5</td><td>356</td></tr><tr><td>232</td><td>SEG105</td><td>-1975.5</td><td>356</td></tr><tr><td>233</td><td>SEG106</td><td>-2022.5</td><td>356</td></tr><tr><td>234</td><td>SEG107</td><td>-2069.5</td><td>356</td></tr><tr><td>235</td><td>SEG108</td><td>-2116.5</td><td>356</td></tr><tr><td>236</td><td>SEG109</td><td>-2163.5</td><td>356</td></tr><tr><td>237</td><td>SEG110</td><td>-2210.5</td><td>356</td></tr><tr><td>238</td><td>SEG111</td><td>-2257.5</td><td>356</td></tr><tr><td>239</td><td>SEG112</td><td>-2304.5</td><td>356</td></tr><tr><td>240</td><td>SEG113</td><td>-2351.5</td><td>356</td></tr></table>

<table><tr><td>Pad no.</td><td>Pad Name</td><td>X-pos</td><td>Y-pos</td></tr><tr><td>241</td><td>SEG114</td><td>-2398.5</td><td>356</td></tr><tr><td>242</td><td>SEG115</td><td>-2445.5</td><td>356</td></tr><tr><td>243</td><td>SEG116</td><td>-2492.5</td><td>356</td></tr><tr><td>244</td><td>SEG117</td><td>-2539.5</td><td>356</td></tr><tr><td>245</td><td>SEG118</td><td>-2586.5</td><td>356</td></tr><tr><td>246</td><td>SEG119</td><td>-2633.5</td><td>356</td></tr><tr><td>247</td><td>SEG120</td><td>-2680.5</td><td>356</td></tr><tr><td>248</td><td>SEG121</td><td>-2727.5</td><td>356</td></tr><tr><td>249</td><td>SEG122</td><td>-2774.5</td><td>356</td></tr><tr><td>250</td><td>SEG123</td><td>-2821.5</td><td>356</td></tr><tr><td>251</td><td>SEG124</td><td>-2868.5</td><td>356</td></tr><tr><td>252</td><td>SEG125</td><td>-2915.5</td><td>356</td></tr><tr><td>253</td><td>SEG126</td><td>-2962.5</td><td>356</td></tr><tr><td>254</td><td>SEG127</td><td>-3009.5</td><td>356</td></tr><tr><td>255</td><td>NC</td><td>-3056.5</td><td>356</td></tr><tr><td>256</td><td>NC</td><td>-3315</td><td>367.5</td></tr><tr><td>257</td><td>COM32</td><td>-3315</td><td>315</td></tr><tr><td>258</td><td>COM33</td><td>-3315</td><td>275</td></tr><tr><td>259</td><td>COM34</td><td>-3315</td><td>235</td></tr><tr><td>260</td><td>COM35</td><td>-3315</td><td>195</td></tr><tr><td>261</td><td>COM36</td><td>-3315</td><td>155</td></tr><tr><td>262</td><td>COM37</td><td>-3315</td><td>115</td></tr><tr><td>263</td><td>COM38</td><td>-3315</td><td>75</td></tr><tr><td>264</td><td>COM39</td><td>-3315</td><td>35</td></tr><tr><td>265</td><td>COM40</td><td>-3315</td><td>-5</td></tr><tr><td>266</td><td>COM41</td><td>-3315</td><td>-45</td></tr><tr><td>267</td><td>COM42</td><td>-3315</td><td>-85</td></tr><tr><td>268</td><td>COM43</td><td>-3315</td><td>-125</td></tr><tr><td>269</td><td>COM44</td><td>-3315</td><td>-165</td></tr><tr><td>270</td><td>COM45</td><td>-3315</td><td>-205</td></tr><tr><td>271</td><td>COM46</td><td>-3315</td><td>-245</td></tr><tr><td>272</td><td>COM47</td><td>-3315</td><td>-285</td></tr><tr><td>273</td><td>COM48</td><td>-3315</td><td>-325</td></tr><tr><td></td><td></td><td></td><td></td></tr><tr><td>Pad no.</td><td>Pad Name</td><td>X-pos</td><td>Y-pos</td></tr><tr><td>Pin#</td><td>Pin name</td><td>X-dir</td><td>Y-dir</td></tr><tr><td>274</td><td>TR0</td><td>2757.05</td><td>114.8</td></tr><tr><td>275</td><td>TR1</td><td>2697.05</td><td>114.8</td></tr><tr><td>276</td><td>TR2</td><td>2637.05</td><td>114.8</td></tr><tr><td>277</td><td>TR3</td><td>2577.05</td><td>114.8</td></tr><tr><td>278</td><td>VSS</td><td>2517.05</td><td>114.8</td></tr><tr><td>279</td><td>TR4</td><td>2457.05</td><td>114.8</td></tr><tr><td>280</td><td>TR5</td><td>2397.05</td><td>114.8</td></tr><tr><td>281</td><td>TR6</td><td>2337.05</td><td>114.8</td></tr></table>


Note: <sup>(1)</sup> COM sequence (Split) is under command setting: DAh, 12h


## 6 PIN ARRANGEMENT

## 6.1 SSD1306TR1 pin assignment


Figure 6-1 : SSD1306TR1 Pin Assignment


![image](https://cdn-mineru.openxlab.org.cn/result/2026-09-08/61e8663c-ef74-4a31-bef6-08879770bc52/3e753ec821cead92a33b129a31f37e4372e392cdbd45618aafb103783c1729e1.jpg)



Table 6-1 : SSD1306TR1 Pin Assignment Table


<table><tr><td>Pin no.</td><td>Pin Name</td><td>Pin no.</td><td>Pin Name</td><td>Pin no.</td><td>Pin Name</td></tr><tr><td>1</td><td>NC</td><td>81</td><td>SEG90</td><td>161</td><td>SEG10</td></tr><tr><td>2</td><td>VCC</td><td>82</td><td>SEG89</td><td>162</td><td>SEG9</td></tr><tr><td>3</td><td>VCOMH</td><td>83</td><td>SEG88</td><td>163</td><td>SEG8</td></tr><tr><td>4</td><td>IREF</td><td>84</td><td>SEG87</td><td>164</td><td>SEG7</td></tr><tr><td>5</td><td>D7</td><td>85</td><td>SEG86</td><td>165</td><td>SEG6</td></tr><tr><td>6</td><td>D6</td><td>86</td><td>SEG85</td><td>166</td><td>SEG5</td></tr><tr><td>7</td><td>D5</td><td>87</td><td>SEG84</td><td>167</td><td>SEG4</td></tr><tr><td>8</td><td>D4</td><td>88</td><td>SEG83</td><td>168</td><td>SEG3</td></tr><tr><td>9</td><td>D3</td><td>89</td><td>SEG82</td><td>169</td><td>SEG2</td></tr><tr><td>10</td><td>D2</td><td>90</td><td>SEG81</td><td>170</td><td>SEG1</td></tr><tr><td>11</td><td>D1</td><td>91</td><td>SEG80</td><td>171</td><td>SEG0</td></tr><tr><td>12</td><td>D0</td><td>92</td><td>SEG79</td><td>172</td><td>NC</td></tr><tr><td>13</td><td>E/RD#</td><td>93</td><td>SEG78</td><td>173</td><td>NC</td></tr><tr><td>14</td><td>R/W#</td><td>94</td><td>SEG77</td><td>174</td><td>NC</td></tr><tr><td>15</td><td>D/C#</td><td>95</td><td>SEG76</td><td>175</td><td>NC</td></tr><tr><td>16</td><td>RES#</td><td>96</td><td>SEG75</td><td>176</td><td>NC</td></tr><tr><td>17</td><td>CS#</td><td>97</td><td>SEG74</td><td>177</td><td>NC</td></tr><tr><td>18</td><td>NC</td><td>98</td><td>SEG73</td><td>178</td><td>NC</td></tr><tr><td>19</td><td>BS2</td><td>99</td><td>SEG72</td><td>179</td><td>NC</td></tr><tr><td>20</td><td>BS1</td><td>100</td><td>SEG71</td><td>180</td><td>NC</td></tr><tr><td>21</td><td>VDD</td><td>101</td><td>SEG70</td><td>181</td><td>NC</td></tr><tr><td>22</td><td>NC</td><td>102</td><td>SEG69</td><td>182</td><td>COM0</td></tr><tr><td>23</td><td>NC</td><td>103</td><td>SEG68</td><td>183</td><td>COM2</td></tr><tr><td>24</td><td>NC</td><td>104</td><td>SEG67</td><td>184</td><td>COM4</td></tr><tr><td>25</td><td>NC</td><td>105</td><td>SEG66</td><td>185</td><td>COM6</td></tr><tr><td>26</td><td>NC</td><td>106</td><td>SEG65</td><td>186</td><td>COM8</td></tr><tr><td>27</td><td>NC</td><td>107</td><td>SEG64</td><td>187</td><td>COM10</td></tr><tr><td>28</td><td>NC</td><td>108</td><td>SEG63</td><td>188</td><td>COM12</td></tr><tr><td>29</td><td>NC</td><td>109</td><td>SEG62</td><td>189</td><td>COM14</td></tr><tr><td>30</td><td>VSS</td><td>110</td><td>SEG61</td><td>190</td><td>COM16</td></tr><tr><td>31</td><td>NC</td><td>111</td><td>SEG60</td><td>191</td><td>COM18</td></tr><tr><td>32</td><td>NC</td><td>112</td><td>SEG59</td><td>192</td><td>COM20</td></tr><tr><td>33</td><td>NC</td><td>113</td><td>SEG58</td><td>193</td><td>COM22</td></tr><tr><td>34</td><td>COM47</td><td>114</td><td>SEG57</td><td>194</td><td>COM24</td></tr><tr><td>35</td><td>COM45</td><td>115</td><td>SEG56</td><td>195</td><td>COM26</td></tr><tr><td>36</td><td>COM43</td><td>116</td><td>SEG55</td><td>196</td><td>COM28</td></tr><tr><td>37</td><td>COM41</td><td>117</td><td>SEG54</td><td>197</td><td>COM30</td></tr><tr><td>38</td><td>COM39</td><td>118</td><td>SEG53</td><td>198</td><td>COM32</td></tr><tr><td>39</td><td>COM37</td><td>119</td><td>SEG52</td><td>199</td><td>COM34</td></tr><tr><td>40</td><td>COM35</td><td>120</td><td>SEG51</td><td>200</td><td>COM36</td></tr><tr><td>41</td><td>COM33</td><td>121</td><td>SEG50</td><td>201</td><td>COM38</td></tr><tr><td>42</td><td>COM31</td><td>122</td><td>SEG49</td><td>202</td><td>COM40</td></tr><tr><td>43</td><td>COM29</td><td>123</td><td>SEG48</td><td>203</td><td>COM42</td></tr><tr><td>44</td><td>COM27</td><td>124</td><td>SEG47</td><td>204</td><td>COM44</td></tr><tr><td>45</td><td>COM25</td><td>125</td><td>SEG46</td><td>205</td><td>COM46</td></tr><tr><td>46</td><td>COM23</td><td>126</td><td>SEG45</td><td>206</td><td>NC</td></tr><tr><td>47</td><td>COM21</td><td>127</td><td>SEG44</td><td>207</td><td>NC</td></tr><tr><td>48</td><td>COM19</td><td>128</td><td>SEG43</td><td></td><td></td></tr><tr><td>49</td><td>COM17</td><td>129</td><td>SEG42</td><td></td><td></td></tr><tr><td>50</td><td>COM15</td><td>130</td><td>SEG41</td><td></td><td></td></tr><tr><td>51</td><td>COM13</td><td>131</td><td>SEG40</td><td></td><td></td></tr><tr><td>52</td><td>COM11</td><td>132</td><td>SEG39</td><td></td><td></td></tr><tr><td>53</td><td>COM9</td><td>133</td><td>SEG38</td><td></td><td></td></tr><tr><td>54</td><td>COM7</td><td>134</td><td>SEG37</td><td></td><td></td></tr><tr><td>55</td><td>COM5</td><td>135</td><td>SEG36</td><td></td><td></td></tr><tr><td>56</td><td>COM3</td><td>136</td><td>SEG35</td><td></td><td></td></tr><tr><td>57</td><td>COM1</td><td>137</td><td>SEG34</td><td></td><td></td></tr><tr><td>58</td><td>NC</td><td>138</td><td>SEG33</td><td></td><td></td></tr><tr><td>59</td><td>NC</td><td>139</td><td>SEG32</td><td></td><td></td></tr><tr><td>60</td><td>NC</td><td>140</td><td>SEG31</td><td></td><td></td></tr><tr><td>61</td><td>NC</td><td>141</td><td>SEG30</td><td></td><td></td></tr><tr><td>62</td><td>NC</td><td>142</td><td>SEG29</td><td></td><td></td></tr><tr><td>63</td><td>NC</td><td>143</td><td>SEG28</td><td></td><td></td></tr><tr><td>64</td><td>NC</td><td>144</td><td>SEG27</td><td></td><td></td></tr><tr><td>65</td><td>NC</td><td>145</td><td>SEG26</td><td></td><td></td></tr><tr><td>66</td><td>NC</td><td>146</td><td>SEG25</td><td></td><td></td></tr><tr><td>67</td><td>NC</td><td>147</td><td>SEG24</td><td></td><td></td></tr><tr><td>68</td><td>SEG103</td><td>148</td><td>SEG23</td><td></td><td></td></tr><tr><td>69</td><td>SEG102</td><td>149</td><td>SEG22</td><td></td><td></td></tr><tr><td>70</td><td>SEG101</td><td>150</td><td>SEG21</td><td></td><td></td></tr><tr><td>71</td><td>SEG100</td><td>151</td><td>SEG20</td><td></td><td></td></tr><tr><td>72</td><td>SEG99</td><td>152</td><td>SEG19</td><td></td><td></td></tr><tr><td>73</td><td>SEG98</td><td>153</td><td>SEG18</td><td></td><td></td></tr><tr><td>74</td><td>SEG97</td><td>154</td><td>SEG17</td><td></td><td></td></tr><tr><td>75</td><td>SEG96</td><td>155</td><td>SEG16</td><td></td><td></td></tr><tr><td>76</td><td>SEG95</td><td>156</td><td>SEG15</td><td></td><td></td></tr><tr><td>77</td><td>SEG94</td><td>157</td><td>SEG14</td><td></td><td></td></tr><tr><td>78</td><td>SEG93</td><td>158</td><td>SEG13</td><td></td><td></td></tr><tr><td>79</td><td>SEG92</td><td>159</td><td>SEG12</td><td></td><td></td></tr><tr><td>80</td><td>SEG91</td><td>160</td><td>SEG11</td><td></td><td></td></tr></table>

## 7 PIN DESCRIPTION

Key: 

<table><tr><td>I = Input</td><td>NC = Not Connected</td></tr><tr><td>O = Output</td><td>Pull LOW= connect to Ground</td></tr><tr><td>I/O = Bi-directional (input/output)</td><td>Pull HIGH= connect to <eq>V_{DD}</eq></td></tr><tr><td>P = Power pin</td><td></td></tr></table>


Figure 7-1 Pin Description


<table><tr><td>Pin Name</td><td>Type</td><td>Description</td></tr><tr><td><eq>V_{DD}</eq></td><td>P</td><td>Power supply pin for core logic operation.</td></tr><tr><td><eq>V_{CC}</eq></td><td>P</td><td>Power supply for panel driving voltage. This is also the most positive power voltage supply pin.</td></tr><tr><td><eq>V_{SS}</eq></td><td>P</td><td>This is a ground pin.</td></tr><tr><td><eq>V_{LSS}</eq></td><td>P</td><td>This is an analog ground pin. It should be connected to <eq>V_{SS}</eq> externally.</td></tr><tr><td><eq>V_{COMH}</eq></td><td>O</td><td>The pin for COM signal deselected voltage level.A capacitor should be connected between this pin and <eq>V_{SS}</eq>.</td></tr><tr><td><eq>V_{BAT}</eq></td><td>P</td><td>Reserved pin. It should be connected to <eq>V_{DD}</eq>.</td></tr><tr><td>BGGND</td><td>P</td><td>Reserved pin. It should be connected to ground.</td></tr><tr><td>C1P/C1N C2P/C2N</td><td>I</td><td>Reserved pin. It should be kept NC.</td></tr><tr><td><eq>V_{BREF}</eq></td><td>P</td><td>Reserved pin. It should be kept NC.</td></tr><tr><td>BS[2:0]</td><td>I</td><td>MCU bus interface selection pins. Please refer to Table 7-1 for the details of setting.</td></tr><tr><td><eq>I_{REF}</eq></td><td>I</td><td>This is segment output current reference pin.A resistor should be connected between this pin and <eq>V_{SS}</eq> to maintain the <eq>I_{REF}</eq> current at 12.5 uA. Please refer to Figure 8-15 for the details of resistor value.</td></tr><tr><td>FR</td><td>O</td><td>This pin outputs RAM write synchronization signal. Proper timing between MCU data writing and frame display timing can be achieved to prevent tearing effect.It should be kept NC if it is not used. Please refer to Section 8.4 for details usage.</td></tr><tr><td>CL</td><td>I</td><td>This is external clock input pin.When internal clock is enabled (i.e. HIGH in CLS pin), this pin is not used and should be connected to <eq>V_{SS}</eq>. When internal clock is disabled (i.e. LOW in CLS pin), this pin is the external clock source input pin.</td></tr><tr><td>CLS</td><td>I</td><td>This is internal clock enable pin. When it is pulled HIGH (i.e. connect to <eq>V_{DD}</eq>), internal clock is enabled. When it is pulled LOW, the internal clock is disabled; an external clock source must be connected to the CL pin for normal operation.</td></tr><tr><td>RES#</td><td>I</td><td>This pin is reset signal input. When the pin is pulled LOW, initialization of the chip is executed. Keep this pin HIGH (i.e. connect to <eq>V_{DD}</eq>) during normal operation.</td></tr><tr><td>CS#</td><td>I</td><td>This pin is the chip select input. (active LOW).</td></tr><tr><td>D/C#</td><td>I</td><td>This is Data/Command control pin. When it is pulled HIGH (i.e. connect to <eq>V_{DD}</eq>), the data at D[7:0] is treated as data. When it is pulled LOW, the data at D[7:0] will be transferred to the command register.In <eq>I^{2}C</eq> mode, this pin acts as SA0 for slave address selection.When 3-wire serial interface is selected, this pin must be connected to <eq>V_{SS}</eq>.For detail relationship to MCU interface signals, please refer to the Timing Characteristics Diagrams: Figure 13-1 to Figure 13-5.</td></tr><tr><td>E (RD#)</td><td>I</td><td>When interfacing to a 6800-series microprocessor, this pin will be used as the Enable (E) signal. Read/write operation is initiated when this pin is pulled HIGH (i.e. connect to <eq>V_{DD}</eq>) and the chip is selected.When connecting to an 8080-series microprocessor, this pin receives the Read (RD#) signal. Read operation is initiated when this pin is pulled LOW and the chip is selected.When serial or <eq>I^{2}C</eq> interface is selected, this pin must be connected to <eq>V_{SS}</eq>.</td></tr><tr><td>R/W#(WR#)</td><td>I</td><td>This is read / write control input pin connecting to the MCU interface.When interfacing to a 6800-series microprocessor, this pin will be used as Read/Write (R/W#) selection input. Read mode will be carried out when this pin is pulled HIGH (i.e. connect to <eq>V_{DD}</eq>) and write mode when LOW.When 8080 interface mode is selected, this pin will be the Write (WR#) input. Data write operation is initiated when this pin is pulled LOW and the chip is selected.When serial or <eq>I^{2}C</eq> interface is selected, this pin must be connected to <eq>V_{SS}</eq>.</td></tr><tr><td>D[7:0]</td><td>IO</td><td>These are 8-bit bi-directional data bus to be connected to the microprocessor's data bus.When serial interface mode is selected, D0 will be the serial clock input: SCLK; D1 will be the serial data input: SDIN and D2 should be kept NC.When <eq>I^{2}C</eq> mode is selected, D2, D1 should be tied together and serve as <eq>SDA_{out}</eq>, <eq>SDA_{in}</eq> in application and D0 is the serial clock input, SCL.</td></tr><tr><td>TR0-TR6</td><td>-</td><td>Testing reserved pins. It should be kept NC.</td></tr><tr><td>SEG0 ~ SEG127</td><td>O</td><td>These pins provide Segment switch signals to OLED panel. These pins are <eq>V_{SS}</eq> state when display is OFF.</td></tr><tr><td>COM0 ~ COM63</td><td>O</td><td>These pins provide Common switch signals to OLED panel. They are in high impedance state when display is OFF.</td></tr><tr><td>NC</td><td>-</td><td>This is dummy pin. Do not group or short NC pins together.</td></tr></table>


Table 7-1 : MCU Bus Interface Pin Selection


<table><tr><td>SSD1306 Pin Name</td><td><eq>I^{2}C</eq> Interface</td><td>6800-parallel interface (8 bit)</td><td>8080-parallel interface (8 bit)</td><td>4-wire Serial interface</td><td>3-wire Serial interface</td></tr><tr><td>BS0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>1</td></tr><tr><td>BS1</td><td>1</td><td>0</td><td>1</td><td>0</td><td>0</td></tr><tr><td>BS2</td><td>0</td><td>1</td><td>1</td><td>0</td><td>0</td></tr></table>


Note 



<sup>(1)</sup> 0 is connected to $\mathrm { V _ { S S } }$ 



<sup>(2)</sup> 1 is connected to $\mathrm { \Delta V _ { D D } }$ 


## 8.1 MCU Interface selection

SSD1306 MCU interface consist of 8 data pins and 5 control pins. The pin assignment at different interface mode is summarized in Table 8-1. Different MCU mode can be set by hardware selection on BS[2:0] pins (please refer to Table 7-1 for BS[2:0] setting). 


Table 8-1 : MCU interface assignment under different bus interface mode


<table><tr><td rowspan="2">Pin NameBusInterface</td><td colspan="8">Data/Command Interface</td><td colspan="5">Control Signal</td></tr><tr><td>D7</td><td>D6</td><td>D5</td><td>D4</td><td>D3</td><td>D2</td><td>D1</td><td>D0</td><td>E</td><td>R/W#</td><td>CS#</td><td>D/C#</td><td>RES#</td></tr><tr><td>8-bit 8080</td><td colspan="8">D[7:0]</td><td>RD#</td><td>WR#</td><td>CS#</td><td>D/C#</td><td>RES#</td></tr><tr><td>8-bit 6800</td><td colspan="8">D[7:0]</td><td>E</td><td>R/W#</td><td>CS#</td><td>D/C#</td><td>RES#</td></tr><tr><td>3-wire SPI</td><td colspan="5">Tie LOW</td><td>NC</td><td>SDIN</td><td>SCLK</td><td colspan="2">Tie LOW</td><td>CS#</td><td>Tie LOW</td><td>RES#</td></tr><tr><td>4-wire SPI</td><td colspan="5">Tie LOW</td><td>NC</td><td>SDIN</td><td>SCLK</td><td colspan="2">Tie LOW</td><td>CS#</td><td>D/C#</td><td>RES#</td></tr><tr><td><eq>I^2C</eq></td><td colspan="5">Tie LOW</td><td><eq>SDA_{OUT}</eq></td><td><eq>SDA_{IN}</eq></td><td>SCL</td><td colspan="3">Tie LOW</td><td>SA0</td><td>RES#</td></tr></table>

## 8.1.1 MCU Parallel 6800-series Interface

The parallel interface consists of 8 bi-directional data pins (D[7:0]), R/W#, D/C#, E and CS#. 

A LOW in R/W# indicates WRITE operation and HIGH in R/W# indicates READ operation. A LOW in D/C# indicates COMMAND read/write and HIGH in D/C# indicates DATA read/write. The E input serves as data latch signal while CS# is LOW. Data is latched at the falling edge of E signal. 


Table 8-2 : Control pins of 6800 interface


<table><tr><td>Function</td><td>E</td><td>R/W#</td><td>CS#</td><td>D/C#</td></tr><tr><td>Write command</td><td>↓</td><td>L</td><td>L</td><td>L</td></tr><tr><td>Read status</td><td>↓</td><td>H</td><td>L</td><td>L</td></tr><tr><td>Write data</td><td>↓</td><td>L</td><td>L</td><td>H</td></tr><tr><td>Read data</td><td>↓</td><td>H</td><td>L</td><td>H</td></tr></table>

## Note

<sup>(1)</sup> ↓ stands for falling edge of signal 

H stands for HIGH in signal 

L stands for LOW in signal 

In order to match the operating frequency of display RAM with that of the microprocessor, some pipeline processing is internally performed which requires the insertion of a dummy read before the first actual display data read. This is shown in Figure 8-1. 


Figure 8-1 : Data read back procedure - insertion of dummy read


![image](https://cdn-mineru.openxlab.org.cn/result/2026-09-08/61e8663c-ef74-4a31-bef6-08879770bc52/f7cc90d1faad0524c19d1952beb4786437de070f85f9e955b97a0a8eea0fe013.jpg)


## 8.1.2 MCU Parallel 8080-series Interface

The parallel interface consists of 8 bi-directional data pins (D[7:0]), RD#, WR#, D/C# and CS#. 

A LOW in D/C# indicates COMMAND read/write and HIGH in D/C# indicates DATA read/write. A rising edge of RD# input serves as a data READ latch signal while CS# is kept LOW. A rising edge of WR# input serves as a data/command WRITE latch signal while CS# is kept LOW. 


Figure 8-2 : Example of Write procedure in 8080 parallel interface mode


![image](https://cdn-mineru.openxlab.org.cn/result/2026-09-08/61e8663c-ef74-4a31-bef6-08879770bc52/05823db9815e296da917995e31f95b3e8e1e0b5cafdc4c9a5d0e56662781512f.jpg)



Figure 8-3 : Example of Read procedure in 8080 parallel interface mode


![image](https://cdn-mineru.openxlab.org.cn/result/2026-09-08/61e8663c-ef74-4a31-bef6-08879770bc52/bd0a854827e283e07d30b1ccc33dfcedf1895237c119a74894a5c04b608a741b.jpg)



Table 8-3 : Control pins of 8080 interface


<table><tr><td>Function</td><td>RD#</td><td>WR#</td><td>CS#</td><td>D/C#</td></tr><tr><td>Write command</td><td>H</td><td>↑</td><td>L</td><td>L</td></tr><tr><td>Read status</td><td>↑</td><td>H</td><td>L</td><td>L</td></tr><tr><td>Write data</td><td>H</td><td>↑</td><td>L</td><td>H</td></tr><tr><td>Read data</td><td>↑</td><td>H</td><td>L</td><td>H</td></tr></table>

## Note

<sup>(1)</sup> ↑ stands for rising edge of signal 

<sup>(2)</sup> H stands for HIGH in signal 

<sup>(3)</sup> L stands for LOW in signal 

In order to match the operating frequency of display RAM with that of the microprocessor, some pipeline processing is internally performed which requires the insertion of a dummy read before the first actual display data read. This is shown in Figure 8-4. 


Figure 8-4 : Display data read back procedure - insertion of dummy read


![image](https://cdn-mineru.openxlab.org.cn/result/2026-09-08/61e8663c-ef74-4a31-bef6-08879770bc52/35b02c79c5b4dc9f16a58b7810b4d0081ed81a2c4d6874327a8af40f30ebb1d3.jpg)


## 8.1.3 MCU Serial Interface (4-wire SPI)

The 4-wire serial interface consists of serial clock: SCLK, serial data: SDIN, D/C#, CS#. In 4-wire SPI mode, D0 acts as SCLK, D1 acts as SDIN. For the unused data pins, D2 should be left open. The pins from D3 to D7, E and R/W# (WR#)# can be connected to an external ground. 


Table 8-4 : Control pins of 4-wire Serial interface


<table><tr><td>Function</td><td>E(RD#)</td><td>R/W#(WR#)</td><td>CS#</td><td>D/C#</td><td>D0</td></tr><tr><td>Write command</td><td>Tie LOW</td><td>Tie LOW</td><td>L</td><td>L</td><td>↑</td></tr><tr><td>Write data</td><td>Tie LOW</td><td>Tie LOW</td><td>L</td><td>H</td><td>↑</td></tr></table>

## Note

<sup>(1)</sup> H stands for HIGH in signal 

<sup>(2)</sup> L stands for LOW in signal 

SDIN is shifted into an 8-bit shift register on every rising edge of SCLK in the order of D7, D6, ... D0. D/C# is sampled on every eighth clock and the data byte in the shift register is written to the Graphic Display Data RAM (GDDRAM) or command register in the same clock. 

Under serial mode, only write operations are allowed. 


Figure 8-5 : Write procedure in 4-wire Serial interface mode


![image](https://cdn-mineru.openxlab.org.cn/result/2026-09-08/61e8663c-ef74-4a31-bef6-08879770bc52/1df8eada947eef981b41fbbf050737cf7ba04a42dbe5bba60f0902f7e594722b.jpg)


## 8.1.4 MCU Serial Interface (3-wire SPI)

The 3-wire serial interface consists of serial clock SCLK, serial data SDIN and CS#. In 3-wire SPI mode, D0 acts as SCLK, D1 acts as SDIN. For the unused data pins, D2 should be left open. The pins from D3 to D7, R/W# (WR#)#, E and D/C# can be connected to an external ground. 

The operation is similar to 4-wire serial interface while D/C# pin is not used. There are altogether 9-bits will be shifted into the shift register on every ninth clock in sequence: D/C# bit, D7 to D0 bit. The D/C# bit (first bit of the sequential data) will determine the following data byte in the shift register is written to the Display Data RAM (D/C# bit = 1) or the command register (D/C# bit = 0). Under serial mode, only write operations are allowed. 


Table 8-5 : Control pins of 3-wire Serial interface


<table><tr><td>Function</td><td>E(RD#)</td><td>R/W#(WR#)</td><td>CS#</td><td>D/C#</td><td>D0</td></tr><tr><td>Write command</td><td>Tie LOW</td><td>Tie LOW</td><td>L</td><td>Tie LOW</td><td>↑</td></tr><tr><td>Write data</td><td>Tie LOW</td><td>Tie LOW</td><td>L</td><td>Tie LOW</td><td>↑</td></tr></table>


Figure 8-6 : Write procedure in 3-wire Serial interface mode


![image](https://cdn-mineru.openxlab.org.cn/result/2026-09-08/61e8663c-ef74-4a31-bef6-08879770bc52/9cf5072b0672ae67a05436f5ae53e9631a83bb7114a0d4b9aacb13d8751a1559.jpg)


## 8.1.5 MCU $\mathbf { I } ^ { 2 } \mathbf { C }$ Interface

The $\mathrm { I } ^ { 2 } \mathrm { C }$ communication interface consists of slave address bit SA0, $\mathrm { I } ^ { 2 } \mathrm { C }$ -bus data signal SDA $\mathrm { ( S D A _ { O U T } / D _ { 2 } }$ for output and $\mathrm { S D A } _ { \mathrm { I N } } / \mathrm { D } _ { 1 }$ for input) and $\mathrm { I } ^ { 2 } \mathrm { C } .$ -bus clock signal SCL $\left( \mathrm { D } _ { 0 } \right)$ . Both the data and clock signals must be connected to pull-up resistors. RES# is used for the initialization of device. 

## a) Slave address bit (SA0)

SSD1306 has to recognize the slave address before transmitting or receiving any information by the I<sup>2</sup>C-bus. The device will respond to the slave address following by the slave address bit $( ^ { \circ } \mathrm { S A } 0 ^ { \circ } \ \mathrm { b i t } )$ and the read/write select bit $( ^ { \circ } \mathrm { { ^ R } / W \# ^ { \circ } \ b i t { } ) }$ with the following byte format, 

b<sub>7</sub> ${ \sf b } _ { 6 }$ b<sub>5</sub> ${ \sf b } _ { 4 }$ b<sub>3</sub> b<sub>2</sub> b<sub>1</sub> b<sub>0</sub> 

0 1 1 1 1 0 SA0 R/W# 

$\mathbf { \bar { s } } \mathbf { A } 0 ^ { \mathbf { \bar { \mathbf { \mathbf { \mathbf { \Lambda } } } } } }$ bit provides an extension bit for the slave address. Either $^ { \mathfrak { c } \mathfrak { c } } 0 1 1 1 1 0 0 ^ { \mathfrak { gg } } \mathrm { o r } ^ { \mathfrak { c } \mathfrak { c } } 0 1 1 1 1 0 1 ^ { \mathfrak { > } }$ , can be selected as the slave address of SSD1306. D/C# pin acts as $\operatorname { S A } 0$ for slave address selection. 

${ } ^ { \infty } \mathrm { R } / \mathrm { W } \# ^ { , }$ bit is used to determine the operation mode of the I<sup>2</sup>C-bus interface. $\mathrm { R } / \mathrm { W } \# { = } 1$ , it is in read mode. $\scriptstyle \mathrm { R } / \mathrm { W } \# = 0$ , it is in write mode. 

## b) I<sup>2</sup>C-bus data signal (SDA)

SDA acts as a communication channel between the transmitter and the receiver. The data and the acknowledgement are sent through the SDA. 

It should be noticed that the ITO track resistance and the pulled-up resistance at $ { \mathrm { { ^ { c c } S D A } } } ^ { \prime }$ pin becomes a voltage potential divider. As a result, the acknowledgement would not be possible to attain a valid logic 0 level in $\boldsymbol { ^ { \circ } \mathrm { S D A } ^ { \circ } }$ 

$\mathrm { \mathop { s c } { S D A _ { I N } } } ^ { \mathrm { * } } ,$ and ${ } ^ { \mathrm { \sc \mathrm { S D A _ { 0 U T } } } } { } ^ { \mathrm { 3 3 } }$ are tied together and serve as SDA. The $\mathrm { ^ { \circ } S D A _ { I N } } ^ { \mathrm { ^ { \circ } S } }$ pin must be connected to act as SDA. The $^ { \mathrm { \infty } } \mathrm { S D A _ { \mathrm { 0 U T } } } ^ { \mathrm { 3 3 } }$ pin may be disconnected. When ${ } ^ { \mathrm { \infty } } \mathrm { S D A _ { 0 U T } } ^ { \mathrm { \infty } } { } ^ { \mathrm { \infty } }$ pin is disconnected, the acknowledgement signal will be ignored in the $\mathrm { I } ^ { 2 } \mathrm { C } \mathrm { - } \mathsf { b u s } .$ 

## c) I<sup>2</sup>C-bus clock signal (SCL)

The transmission of information in the $\mathrm { \Delta } \Gamma ^ { 2 } \mathrm { C }$ -bus is following a clock signal, SCL. Each transmission of data bit is taken place during a single clock period of SCL. 

## 8.1.5.1 I<sup>2</sup>C-bus Write data

The I<sup>2</sup>C-bus interface gives access to write data and command into the device. Please refer to Figure 8-7 for the write mode of I<sup>2</sup>C-bus in chronological order. 


Figure 8-7 : I<sup>2</sup>C-bus data format


![image](https://cdn-mineru.openxlab.org.cn/result/2026-09-08/61e8663c-ef74-4a31-bef6-08879770bc52/8acb269f806e7137d89a59021bdbca87c0bf82029d8932d6f6324ee22004cb64.jpg)


## 8.1.5.2 Write mode for $\mathbf { I } ^ { 2 } \mathbf { C }$

1) The master device initiates the data communication by a start condition. The definition of the start condition is shown in Figure 8-8. The start condition is established by pulling the SDA from HIGH to LOW while the SCL stays HIGH. 

2) The slave address is following the start condition for recognition use. For the SSD1306, the slave address is either “b0111100” or “b0111101” by changing the SA0 to LOW or HIGH (D/C pin acts as SA0). 

3) The write mode is established by setting the R/W# bit to logic “0”. 

4) An acknowledgement signal will be generated after receiving one byte of data, including the slave address and the R/W# bit. Please refer to the Figure 8-9 for the graphical representation of the acknowledge signal. The acknowledge bit is defined as the SDA line is pulled down during the HIGH period of the acknowledgement related clock pulse. 

5) After the transmission of the slave address, either the control byte or the data byte may be sent across the SDA. A control byte mainly consists of Co and D/C# bits following by six “0” ‘s. 

a. If the Co bit is set as logic “0”, the transmission of the following information will contain data bytes only. 

b. The D/C# bit determines the next data byte is acted as a command or a data. If the D/C# bit is set to logic $^ { \circ }$ , it defines the following data byte as a command. If the D/C# bit is set to logic “1”, it defines the following data byte as a data which will be stored at the GDDRAM. The GDDRAM column address pointer will be increased by one automatically after each data write. 

6) Acknowledge bit will be generated after receiving each control byte or data byte. 

7) The write mode will be finished when a stop condition is applied. The stop condition is also defined in Figure 8-8. The stop condition is established by pulling the “SDA in” from LOW to HIGH while the “SCL” stays HIGH. 


Figure 8-8 : Definition of the Start and Stop Condition


![image](https://cdn-mineru.openxlab.org.cn/result/2026-09-08/61e8663c-ef74-4a31-bef6-08879770bc52/649c443ce6bb2f5c718fc37155ab8a00cbd96f79d1a7455d306cc2f80eef94f0.jpg)



Figure 8-9 : Definition of the acknowledgement condition


![image](https://cdn-mineru.openxlab.org.cn/result/2026-09-08/61e8663c-ef74-4a31-bef6-08879770bc52/d1473acab273c1764deeb4c2bea842765e19eb1155782300a18aa3fa87c132b1.jpg)


Please be noted that the transmission of the data bit has some limitations. 

1. The data bit, which is transmitted during each SCL pulse, must keep at a stable state within the “HIGH” period of the clock pulse. Please refer to the Figure 8-10 for graphical representations. Except in start or stop conditions, the data line can be switched only when the SCL is LOW. 

2. Both the data line (SDA) and the clock line (SCL) should be pulled up by external resistors. 


Figure 8-10 : Definition of the data transfer condition


![image](https://cdn-mineru.openxlab.org.cn/result/2026-09-08/61e8663c-ef74-4a31-bef6-08879770bc52/d84be1c2ae3630709e62754133bee5967716e888301620961932271c3ce05520.jpg)


## 8.2 Command Decoder

This module determines whether the input data is interpreted as data or command. Data is interpreted based upon the input of the D/C# pin 

If D/C# pin is HIGH, D[7:0] is interpreted as display data written to Graphic Display Data RAM (GDDRAM). If it is LOW, the input at D[7:0] is interpreted as a command. Then data input will be decoded and written to the corresponding command register. 

## 8.3 Oscillator Circuit and Display Time Generator


Figure 8-11 : Oscillator Circuit and Display Time Generator


![image](https://cdn-mineru.openxlab.org.cn/result/2026-09-08/61e8663c-ef74-4a31-bef6-08879770bc52/1624f793b1f0aae8bc57fea7090cbf7e5cdbc9aa82dfb33f5cf538ab27aafdf3.jpg)


This module is an on-chip LOW power RC oscillator circuitry. The operation clock (CLK) can be generated either from internal oscillator or external source CL pin. This selection is done by CLS pin. If CLS pin is pulled HIGH, internal oscillator is chosen and CL should be left open. Pulling CLS pin LOW disables internal oscillator and external clock must be connected to CL pins for proper operation. When the internal oscillator is selected, its output frequency Fosc can be changed by command D5h A[7:4]. 

The display clock (DCLK) for the Display Timing Generator is derived from CLK. The division factor “D” can be programmed from 1 to 16 by command D5h 

$$
\mathrm{DCLK} = \mathrm {F_ {OSC}} / \mathrm{D}
$$

The frame frequency of display is determined by the following formula. 

$$
\mathrm{F} _ {\mathrm{FRM}} = \frac {\mathrm{F} _ {\mathrm{osc}}}{\mathrm{D} \times \mathrm{K} \times \text {No.of Mux}}
$$

where 

● D stands for clock divide ratio. It is set by command D5h A[3:0]. The divide ratio has the range from 1 to 16. 

• K is the number of display clocks per row. The value is derived by 

K = Phase 1 period + Phase 2 period + BANK0 pulse width 

$= 2 + 2 + 5 0 = 5 4$ at power on reset 

(Please refer to Section 8.6 “Segment Drivers / Common Drivers” for the details of the “Phase”) 

• Number of multiplex ratio is set by command A8h. The power on reset value is 63 (i.e. 64MUX). 

• F<sub>OSC</sub> is the oscillator frequency. It can be changed by command D5h A[7:4]. The higher the register setting results in higher frequency. 

## 8.4 FR synchronization

FR synchronization signal can be used to prevent tearing effect. 

![image](https://cdn-mineru.openxlab.org.cn/result/2026-09-08/61e8663c-ef74-4a31-bef6-08879770bc52/157971bbb00c49466bdc088077186fdba11564f99df8e77f822af6774cd7bf5e.jpg)


The starting time to write a new image to OLED driver is depended on the MCU writing speed. If MCU can finish writing a frame image within one frame period, it is classified as fast write MCU. For MCU needs longer writing time to complete (more than one frame but within two frames), it is a slow write one. 

For fast write MCU: MCU should start to write new frame of ram data just after rising edge of FR pulse and should be finished well before the rising edge of the next FR pulse. 

For slow write MCU: MCU should start to write new frame ram data after the falling edge of the 1<sup>st</sup> FR pulse and must be finished before the rising edge of the 3<sup>rd</sup> FR pulse. 

## 8.5 Reset Circuit

When RES# input is LOW, the chip is initialized with the following status: 

1. Display is OFF 

2. 128 x 64 Display Mode 

3. Normal segment and display data column address and row address mapping (SEG0 mapped to address 00h and COM0 mapped to address 00h) 

4. Shift register data clear in serial interface 

5. Display start line is set at display RAM address 0 

6. Column address counter is set at 0 

7. Normal scan direction of the COM outputs 

8. Contrast control register is set at 7Fh 

9. Normal display mode (Equivalent to A4h command) 

## 8.6 Segment Drivers / Common Drivers

Segment drivers deliver 128 current sources to drive the OLED panel. The driving current can be adjusted from 0 to 100uA with 256 steps. Common drivers generate voltage-scanning pulses. 

The segment driving waveform is divided into three phases: 

1. In phase 1, the OLED pixel charges of previous image are discharged in order to prepare for next image content display. 

2. In phase 2, the OLED pixel is driven to the targeted voltage. The pixel is driven to attain the corresponding voltage level from $\mathrm { V } _ { \mathrm { S S } } .$ . The period of phase 2 can be programmed in length from 1 to 15 DCLKs. If the capacitance value of the pixel of OLED panel is larger, a longer period is required to charge up the capacitor to reach the desired voltage. 

3. In phase 3, the OLED driver switches to use current source to drive the OLED pixels and this is the current drive stage. 


Figure 8-12 : Segment Output Waveform in three phases


![image](https://cdn-mineru.openxlab.org.cn/result/2026-09-08/61e8663c-ef74-4a31-bef6-08879770bc52/4f2fbbd73176787cb2cfc7de057d713a9e555ff6dcf0b6635f05197c6f71125f.jpg)


After finishing phase 3, the driver IC will go back to phase 1 to display the next row image data. This threestep cycle is run continuously to refresh image display on OLED panel. 

In phase 3, if the length of current drive pulse width is set to 50, after finishing 50 DCLKs in current drive phase, the driver IC will go back to phase 1 for next row display. 

## 8.7 Graphic Display Data RAM (GDDRAM)

The GDDRAM is a bit mapped static RAM holding the bit pattern to be displayed. The size of the RAM is 128 x 64 bits and the RAM is divided into eight pages, from PAGE0 to PAGE7, which are used for monochrome 128x64 dot matrix display, as shown in Figure 8-13. 


Figure 8-13 : GDDRAM pages structure of SSD1306


<table><tr><td>PAGE0 (COM0-COM7)</td><td>Page 0</td><td>Row re-mapping</td></tr><tr><td>PAGE1 (COM8-COM15)</td><td>Page 1</td><td>PAGE0 (COM 63-COM56)</td></tr><tr><td>PAGE2 (COM16-COM23)</td><td>Page 2</td><td>PAGE1 (COM 55-COM48)</td></tr><tr><td>PAGE3 (COM24-COM31)</td><td>Page 3</td><td>PAGE2 (COM47-COM40)</td></tr><tr><td>PAGE4 (COM32-COM39)</td><td>Page 4</td><td>PAGE3 (COM39-COM32)</td></tr><tr><td>PAGE5 (COM40-COM47)</td><td>Page 5</td><td>PAGE4 (COM31-COM24)</td></tr><tr><td>PAGE6 (COM48-COM55)</td><td>Page 6</td><td>PAGE5 (COM23-COM16)</td></tr><tr><td>PAGE7 (COM56-COM63)</td><td>Page 7</td><td>PAGE6 (COM15-COM8)</td></tr><tr><td></td><td>SEG0</td><td>PAGE7 (COM 7-COM0)</td></tr><tr><td>Column re-mapping</td><td>SEG127</td><td>SEG0</td></tr></table>

When one data byte is written into GDDRAM, all the rows image data of the same page of the current column are filled (i.e. the whole column (8 bits) pointed by the column address pointer is filled.). Data bit D0 is written into the top row, while data bit D7 is written into bottom row as shown in Figure 8-14. 


Figure 8-14 : Enlargement of GDDRAM (No row re-mapping and column-remapping)


<table><tr><td colspan="2">PAGE2</td></tr><tr><td></td><td>SEG0</td></tr><tr><td></td><td>SEG1</td></tr><tr><td></td><td>SEG2</td></tr><tr><td></td><td>SEG3</td></tr><tr><td></td><td>SEG4</td></tr><tr><td></td><td>LSB D0</td></tr><tr><td></td><td>MSB D7</td></tr><tr><td></td><td>...</td></tr><tr><td></td><td>...</td></tr><tr><td></td><td>...</td></tr><tr><td></td><td>...</td></tr><tr><td></td><td>...</td></tr><tr><td></td><td>...</td></tr><tr><td></td><td>...</td></tr><tr><td></td><td>...</td></tr><tr><td></td><td>...</td></tr><tr><td></td><td>...</td></tr><tr><td></td><td>...</td></tr><tr><td></td><td>...</td></tr><tr><td></td><td>...</td></tr><tr><td></td><td>...</td></tr><tr><td></td><td>...</td></tr><tr><td></td><td>...</td></tr><tr><td></td><td>...</td></tr><tr><td></td><td>...</td></tr><tr><td></td><td>...</td></tr><tr><td></td><td>...</td></tr><tr><td></td><td>COM16</td></tr><tr><td>COM23</td><td>...</td></tr><tr><td>COM17</td><td>...</td></tr><tr><td>COM16</td><td>...</td></tr></table>

For mechanical flexibility, re-mapping on both Segment and Common outputs can be selected by software as shown in Figure 8-13. 

For vertical shifting of the display, an internal register storing the display start line can be set to control the portion of the RAM data to be mapped to the display (command D3h). 

## 8.8 SEG/COM Driving block

This block is used to derive the incoming power sources into the different levels of internal use voltage and current. 

$\mathrm { V _ { C C } }$ is the most positive voltage supply. 

$\mathrm { V _ { C O M H } }$ is the Common deselected level. It is internally regulated. 

$\mathrm { { V _ { L S S } } }$ is the ground path of the analog and panel current. 

$\mathrm { I _ { R E F } }$ is a reference current source for segment current drivers $\mathrm { I } _ { \mathrm { S E G } }$ . The relationship between reference current and segment current of a color is: 

$$
\mathrm{I} _ {\mathrm{SEG}} = \text { Contrast } / 2 5 6 \times \mathrm{I} _ {\mathrm{REF}} \times \text { scale   factor }
$$

in which 

the contrast (0~255) is set by Set Contrast command $8 1 \mathrm { h } ;$ and the scale factor is 8 by default. 

The magnitude of $\mathrm { I _ { R E F } }$ is controlled by the value of resistor, which is connected between $\mathrm { I _ { R E F } }$ pin and $\mathrm { V _ { S S } }$ as shown in Figure 8-15. It is recommended to set $\mathrm { I _ { R E F } }$ to $1 2 . 5 \pm 2 \mathrm { u A }$ so as to achieve $\mathrm { I } _ { \mathrm { S E G } } =$ 100uA at maximum contrast 255. 


Figure 8-15 : $\mathbf { I } _ { \mathbf { R E F } }$ Current Setting by Resistor Value


![image](https://cdn-mineru.openxlab.org.cn/result/2026-09-08/61e8663c-ef74-4a31-bef6-08879770bc52/68e74e57ddc43bc591009c02abf75d758718f8f17d0d005fd06c8c8e7ca1d91d.jpg)


Since the voltage at $\mathrm { I _ { R E F } }$ pin is $\mathrm { V } _ { \mathrm { C C } } - 2 . 5 \mathrm { V } _ { \mathrm { : } }$ , the value of resistor R1 can be found as below: 

$$
\mathrm {For I_ {REF} = 12.5uA, V_ {CC} = 12V:}
$$

$$
\begin{array}{r l} \mathrm{R1} & = (\text { Voltage   at   I } _ {\mathrm{REF}} - \mathrm{V} _ {\mathrm{SS}}) / \mathrm{I} _ {\mathrm{REF}} \\ & = (1 2 - 2. 5) / 1 2. 5 \mathrm{uA} \\ & = 7 6 0 \mathrm{K} \Omega \end{array}
$$

## 8.9 Power ON and OFF sequence

The following figures illustrate the recommended power ON and power OFF sequence of SSD1306 

Power ON sequence: 

1. Power ON $\mathrm { \Delta V _ { D D } }$ 

2. After V<sub>DD</sub> become stable, set RES# pin LOW (logic low) for at least 3us $\left( \mathrm { t } _ { 1 } \right) ^ { ( 4 ) }$ and then HIGH (logic high). 

3. After set RES# pin LOW (logic low), wait for at least 3us (t<sub>2</sub>). Then Power ON ${ \mathrm { V } } _ { \mathrm { C C } } . ^ { ( 1 ) }$ 

4. After $\mathrm { V _ { C C } }$ become stable, send command AFh for display ON. SEG/COM will be ON after 100ms $( \mathrm { t _ { A F } } )$ 


Figure 8-16 : The Power ON sequence


<table><tr><td></td><td>ON V_DD-</td><td>RES#</td><td>ON VCC</td><td>Send AFh command for Display ON</td></tr><tr><td>VDD</td><td></td><td></td><td></td><td></td></tr><tr><td>OFF</td><td></td><td></td><td></td><td></td></tr><tr><td>RES#</td><td></td><td></td><td></td><td></td></tr><tr><td>GND</td><td></td><td></td><td></td><td></td></tr><tr><td>VCC</td><td></td><td></td><td></td><td></td></tr><tr><td>OFF</td><td></td><td></td><td></td><td></td></tr><tr><td>SEG/COM</td><td></td><td></td><td></td><td></td></tr></table>

Power OFF sequence: 

1. Send command AEh for display OFF. 

2. Power OFF $\mathrm { V _ { C C } }$ (1), (2), (3) 

3. Power OFF $\mathrm { \Delta V _ { D D } }$ after $\mathrm { t _ { O F F } }$ . <sup>(5)</sup> (Typical $\mathrm { t _ { O F F } } { = } 1 0 0 \mathrm { m s } )$ 


Figure 8-17 : The Power OFF sequence


<table><tr><td colspan="2">Send command AEh for display OFF</td><td colspan="2">OFF VCC</td><td colspan="2">OFF VDD</td></tr><tr><td colspan="2">VCC</td><td colspan="2">OFF</td><td colspan="2">OFF</td></tr><tr><td colspan="2">OFF</td><td colspan="2">tOFF</td><td colspan="2"></td></tr><tr><td colspan="2">VDD</td><td colspan="2"></td><td colspan="2"></td></tr><tr><td colspan="2">OFF</td><td colspan="2"></td><td colspan="2"></td></tr></table>

## Note:

<sup>(1)</sup> Since an ESD protection circuit is connected between $\mathrm { \Delta V _ { D D } }$ and $\mathrm { V } _ { \mathrm { C C } } , \mathrm { V } _ { \mathrm { C C } }$ becomes lower than $\mathrm { \Delta V _ { D D } }$ whenever $\mathrm { \Delta V _ { D D } }$ is ON and $\mathrm { V _ { C C } }$ is OFF as shown in the dotted line of $\mathrm { V _ { C C } }$ in Figure 8-16 and Figure 8-17. 

(2) $\mathrm { V _ { C C } }$ should be kept float (i.e. disable) when it is OFF. 

<sup>(3)</sup> Power Pins $( \mathrm { V } _ { \mathrm { D D } } , \mathrm { V } _ { \mathrm { C C } } )$ can never be pulled to ground under any circumstance. 

<sup>(4)</sup> The register values are reset after t<sub>1</sub>. 

(5) $\mathrm { \Delta V _ { D D } }$ should not be Power OFF before $\mathrm { V _ { C C } }$ Power OFF. 


Table 9-1: Command Table



(D/C#=0, R/W#(WR#) = 0, E(RD#=1) unless specific setting is stated)


<table><tr><td colspan="12">1. Fundamental Command Table</td></tr><tr><td>D/C#</td><td>Hex</td><td>D7</td><td>D6</td><td>D5</td><td>D4</td><td>D3</td><td>D2</td><td>D1</td><td>D0</td><td>Command</td><td>Description</td></tr><tr><td>0</td><td>81</td><td>1</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>1</td><td>Set Contrast Control</td><td>Double byte command to select 1 out of 256 contrast steps. Contrast increases as the value increases.(RESET = 7Fh)</td></tr><tr><td>0</td><td>A[7:0]</td><td><eq>A_7</eq></td><td><eq>A_6</eq></td><td><eq>A_5</eq></td><td><eq>A_4</eq></td><td><eq>A_3</eq></td><td><eq>A_2</eq></td><td><eq>A_1</eq></td><td><eq>A_0</eq></td><td></td><td></td></tr><tr><td>0</td><td>A4/A5</td><td>1</td><td>0</td><td>1</td><td>0</td><td>0</td><td>1</td><td>0</td><td><eq>X_0</eq></td><td>Entire Display ON</td><td>A4h, <eq>X_0=0b</eq>: Resume to RAM content display (RESET)Output follows RAM contentA5h, <eq>X_0=1b</eq>: Entire display ONOutput ignores RAM content</td></tr><tr><td>0</td><td>A6/A7</td><td>1</td><td>0</td><td>1</td><td>0</td><td>0</td><td>1</td><td>1</td><td><eq>X_0</eq></td><td>Set Normal/Inverse Display</td><td>A6h, X[0]=0b: Normal display (RESET)0 in RAM: OFF in display panel1 in RAM: ON in display panelA7h, X[0]=1b: Inverse display0 in RAM: ON in display panel1 in RAM: OFF in display panel</td></tr><tr><td>0</td><td>AE AF</td><td>1</td><td>0</td><td>1</td><td>0</td><td>1</td><td>1</td><td>1</td><td><eq>X_0</eq></td><td>Set Display ON/OFF</td><td>AEh, X[0]=0b:Display OFF (sleep mode)(RESET)AFh X[0]=1b:Display ON in normal mode</td></tr></table>

<table><tr><td colspan="12">2. Scrolling Command Table</td></tr><tr><td>D/C#</td><td>Hex</td><td>D7</td><td>D6</td><td>D5</td><td>D4</td><td>D3</td><td>D2</td><td>D1</td><td>D0</td><td>Command</td><td>Description</td></tr><tr><td>0</td><td>26/27</td><td>0</td><td>0</td><td>1</td><td>0</td><td>0</td><td>1</td><td>1</td><td><eq>X_0</eq></td><td rowspan="8">Continuous Horizontal Scroll Setup</td><td rowspan="5">26h, X[0]=0, Right Horizontal Scroll 27h, X[0]=1, Left Horizontal Scroll (Horizontal scroll by 1 column) A[7:0] : Dummy byte (Set as 00h) B[2:0] : Define start page address</td></tr><tr><td>0</td><td>A[7:0]</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td></tr><tr><td>0</td><td>B[2:0]</td><td>*</td><td>*</td><td>*</td><td>*</td><td>*</td><td><eq>B_2</eq></td><td><eq>B_1</eq></td><td><eq>B_0</eq></td></tr><tr><td>0</td><td>C[2:0]</td><td>*</td><td>*</td><td>*</td><td>*</td><td>*</td><td><eq>C_2</eq></td><td><eq>C_1</eq></td><td><eq>C_0</eq></td></tr><tr><td>0</td><td>D[2:0]</td><td>*</td><td>*</td><td>*</td><td>*</td><td>*</td><td><eq>D_2</eq></td><td><eq>D_1</eq></td><td><eq>D_0</eq></td></tr><tr><td rowspan="2">0</td><td rowspan="2">E[7:0]</td><td rowspan="2">0</td><td rowspan="2">0</td><td rowspan="2">0</td><td rowspan="2">0</td><td rowspan="2">0</td><td rowspan="2">0</td><td rowspan="2">0</td><td rowspan="2">0</td><td>000b-PAGE0 011b-PAGE3 110b-PAGE6</td></tr><tr><td>001b-PAGE1 100b-PAGE4 111b-PAGE7</td></tr><tr><td>0</td><td>F[7:0]</td><td>1</td><td>1</td><td>1</td><td>1</td><td>1</td><td>1</td><td>1</td><td>1</td><td>010b-PAGE2 101b-PAGE5</td></tr><tr><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td>C[2:0] : Set time interval between each scroll step in terms of frame frequency</td></tr><tr><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td>000b-5 frames 100b-3 frames</td></tr><tr><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td>001b-64 frames 101b-4 frames</td></tr><tr><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td>010b-128 frames 110b-25 frame</td></tr><tr><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td>011b-256 frames 111b-2 frame</td></tr><tr><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td>D[2:0] : Define end page address</td></tr><tr><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td>000b-PAGE0 011b-PAGE3 110b-PAGE6</td></tr><tr><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td>001b-PAGE1 100b-PAGE4 111b-PAGE7</td></tr><tr><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td>010b-PAGE2 101b-PAGE5</td></tr><tr><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td>The value of D[2:0] must be larger or equal to B[2:0] E[7:0] : Dummy byte (Set as 00h) F[7:0] : Dummy byte (Set as FFh)</td></tr><tr><td>0</td><td>29/2A</td><td>0</td><td>0</td><td>1</td><td>0</td><td>1</td><td>0</td><td><eq>X_1</eq></td><td><eq>X_0</eq></td><td>Continuous</td><td rowspan="6">29h, <eq>X_1X_0=01b</eq>: Vertical and Right Horizontal Scroll 2Ah, <eq>X_1X_0=10b</eq>: Vertical and Left Horizontal Scroll (Horizontal scroll by 1 column) A[7:0]: Dummy byte B[2:0]: Define start page address</td></tr><tr><td>0</td><td>A[2:0]</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td rowspan="5">Vertical and Horizontal Scroll Setup</td></tr><tr><td>0</td><td>B[2:0]</td><td>*</td><td>*</td><td>*</td><td>*</td><td>*</td><td><eq>B_2</eq></td><td><eq>B_1</eq></td><td><eq>B_0</eq></td></tr><tr><td>0</td><td>C[2:0]</td><td>*</td><td>*</td><td>*</td><td>*</td><td>*</td><td><eq>C_2</eq></td><td><eq>C_1</eq></td><td><eq>C_0</eq></td></tr><tr><td>0</td><td>D[2:0]</td><td>*</td><td>*</td><td>*</td><td>*</td><td>*</td><td><eq>D_2</eq></td><td><eq>D_1</eq></td><td><eq>D_0</eq></td></tr><tr><td>0</td><td>E[5:0]</td><td>*</td><td>*</td><td><eq>E_5</eq></td><td><eq>E_4</eq></td><td><eq>E_3</eq></td><td><eq>E_2</eq></td><td><eq>E_1</eq></td><td><eq>E_0</eq></td></tr><tr><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td>000b-PAGE0 011b-PAGE3 110b-PAGE6</td></tr><tr><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td>001b-PAGE1 100b-PAGE4 111b-PAGE7</td></tr><tr><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td>010b-PAGE2 101b-PAGE5</td></tr><tr><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td>C[2:0]: Set time interval between each scroll step in terms of frame frequency</td></tr><tr><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td>000b-5 frames 100b-3 frames</td></tr><tr><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td>001b-64 frames 101b-4 frames</td></tr><tr><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td>010b-128 frames 110b-25 frame</td></tr><tr><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td>011b-256 frames 111b-2 frame</td></tr><tr><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td>D[2:0]: Define end page address</td></tr><tr><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td>000b-PAGE0 011b-PAGE3 110b-PAGE6</td></tr><tr><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td>001b-PAGE1 100b-PAGE4 111b-PAGE7</td></tr><tr><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td>010b-PAGE2 101n-PAGE5</td></tr><tr><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td>The value of D[2:0] must be larger or equal to B[2:0] E[5:0]: Vertical scrolling offset e.g. E[5:0]=01h refer to offset =1 row E[5:0]=3Fh refer to offset =63 rows Note(1) No continuous vertical scrolling is available.</td></tr><tr><td>0</td><td>2E</td><td>0</td><td>0</td><td>1</td><td>0</td><td>1</td><td>1</td><td>1</td><td>0</td><td>Deactivate scroll</td><td>Stop scrolling that is configured by command 26h/27h/29h/2Ah. Note(1) After sending 2Eh command to deactivate the scrolling action, the ram data needs to be rewritten.</td></tr><tr><td>0</td><td>2F</td><td>0</td><td>0</td><td>1</td><td>0</td><td>1</td><td>1</td><td>1</td><td>1</td><td>Activate scroll</td><td>Start scrolling that is configured by the scrolling setup commands :26h/27h/29h/2Ah with the following valid sequences: Valid command sequence 1: 26h ;2Fh. Valid command sequence 2: 27h ;2Fh. Valid command sequence 3: 29h ;2Fh. Valid command sequence 4: 2Ah ;2Fh. For example, if “26h; 2Ah; 2Fh.” commands are issued, the setting in the last scrolling setup command, i.e. 2Ah in this case, will be executed. In other words, setting in the last scrolling setup command overwrites the setting in the previous scrolling setup commands.</td></tr><tr><td>0</td><td>A3</td><td>1</td><td>0</td><td>1</td><td>0</td><td>0</td><td>0</td><td>1</td><td>1</td><td rowspan="3">Set Vertical Scroll Area</td><td rowspan="3">A[5:0] : Set No. of rows in top fixed area. The No. of rows in top fixed area is referenced to the top of the GDDRAM (i.e. row 0).[RESET = 0]B[6:0] : Set No. of rows in scroll area. This is the number of rows to be used for vertical scrolling. The scroll area starts in the first row below the top fixed area. [RESET = 64]Note(1) A[5:0]+B[6:0] &lt;= MUX ratio(2) B[6:0] &lt;= MUX ratio(3a) Vertical scrolling offset (E[5:0] in 29h/2Ah) &lt; B[6:0](3b) Set Display Start Line (X5X4X3X2X1X0 of 40h~7Fh) &lt; B[6:0](4) The last row of the scroll area shifts to the first row of the scroll area.(5) For 64d MUX display A[5:0] = 0, B[6:0]=64 : whole area scrolls A[5:0]= 0, B[6:0] &lt; 64 : top area scrolls A[5:0] + B[6:0] &lt; 64 : central area scrolls A[5:0] + B[6:0] = 64 : bottom area scrolls</td></tr><tr><td>0</td><td>A[5:0]</td><td>*</td><td>*</td><td>A5</td><td>A4</td><td>A3</td><td>A2</td><td>A1</td><td>A0</td></tr><tr><td>0</td><td>B[6:0]</td><td>*</td><td>B6</td><td>B5</td><td>B4</td><td>B3</td><td>B2</td><td>B1</td><td>B0</td></tr><tr><td colspan="12">3. Addressing Setting Command Table</td></tr><tr><td>D/C#</td><td>Hex</td><td>D7</td><td>D6</td><td>D5</td><td>D4</td><td>D3</td><td>D2</td><td>D1</td><td>D0</td><td>Command</td><td>Description</td></tr><tr><td>0</td><td>22</td><td>0</td><td>0</td><td>1</td><td>0</td><td>0</td><td>0</td><td>1</td><td>0</td><td rowspan="3">Set Page Address</td><td rowspan="3">Setup page start and end addressA[2:0] : Page start Address, range : 0-7d,(RESET = 0d)B[2:0] : Page end Address, range : 0-7d,(RESET = 7d)Note(1) This command is only for horizontal or verticaladdressing mode.</td></tr><tr><td>0</td><td>A[2:0]</td><td>*</td><td>*</td><td>*</td><td>*</td><td>*</td><td>A2</td><td>A1</td><td>A0</td></tr><tr><td>0</td><td>B[2:0]</td><td>*</td><td>*</td><td>*</td><td>*</td><td>*</td><td>B2</td><td>B1</td><td>B0</td></tr><tr><td>0</td><td>B0~B7</td><td>1</td><td>0</td><td>1</td><td>1</td><td>0</td><td>X2</td><td>X1</td><td>X0</td><td>Set Page StartAddress for PageAddressing Mode</td><td>Set GDDRAM Page Start Address(PAGE0~PAGE7) for Page Addressing Modeusing X[2:0].Note(1) This command is only for page addressing mode</td></tr></table>

<table><tr><td>D/C#</td><td>Hex</td><td>D7</td><td>D6</td><td>D5</td><td>D4</td><td>D3</td><td>D2</td><td>D1</td><td>D0</td><td>Command</td><td>Description</td></tr><tr><td>0</td><td>40~7F</td><td>0</td><td>1</td><td><eq>X_5</eq></td><td><eq>X_4</eq></td><td><eq>X_3</eq></td><td><eq>X_2</eq></td><td><eq>X_1</eq></td><td><eq>X_0</eq></td><td>Set Display Start Line</td><td>Set display RAM display start line register from 0-63 using <eq>X_5X_3X_2X_1X_0</eq>.Display start line register is reset to 000000b during RESET.</td></tr><tr><td>0</td><td>A0/A1</td><td>1</td><td>0</td><td>1</td><td>0</td><td>0</td><td>0</td><td>0</td><td><eq>X_0</eq></td><td>Set Segment Re-map</td><td>A0h, X[0]=0b: column address 0 is mapped to SEG0 (RESET)A1h, X[0]=1b: column address 127 is mapped to SEG0</td></tr><tr><td>00</td><td>A8A[5:0]</td><td>1*</td><td>0*</td><td>1<eq>A_5</eq></td><td>0<eq>A_4</eq></td><td>1<eq>A_3</eq></td><td>0<eq>A_2</eq></td><td>0<eq>A_1</eq></td><td>0<eq>A_0</eq></td><td>Set Multiplex Ratio</td><td>Set MUX ratio to N+1 MUXN=A[5:0] : from 16MUX to 64MUX, RESET=111111b (i.e. 63d, 64MUX)A[5:0] from 0 to 14 are invalid entry.</td></tr><tr><td>0</td><td>C0/C8</td><td>1</td><td>1</td><td>0</td><td>0</td><td><eq>X_3</eq></td><td>0</td><td>0</td><td>0</td><td>Set COM Output Scan Direction</td><td>C0h, X[3]=0b: normal mode (RESET) Scan from COM0 to COM[N -1]C8h, X[3]=1b: remapped mode. Scan from COM[N-1] to COM0Where N is the Multiplex ratio.</td></tr><tr><td>00</td><td>D3A[5:0]</td><td>1*</td><td>1*</td><td>0<eq>A_5</eq></td><td>1<eq>A_4</eq></td><td>0<eq>A_3</eq></td><td>0<eq>A_2</eq></td><td>1<eq>A_1</eq></td><td>1<eq>A_0</eq></td><td>Set Display Offset</td><td>Set vertical shift by COM from 0d~63dThe value is reset to 00h after RESET.</td></tr><tr><td>00</td><td>DAA[5:4]</td><td>10</td><td>10</td><td>0<eq>A_5</eq></td><td>1<eq>A_4</eq></td><td>10</td><td>00</td><td>11</td><td>00</td><td>Set COM Pins Hardware Configuration</td><td>A[4]=0b, Sequential COM pin configurationA[4]=1b(RESET), Alternative COM pin configurationA[5]=0b(RESET), Disable COM Left/Right remapA[5]=1b, Enable COM Left/Right remap</td></tr><tr><td colspan="12">5. Timing &amp; Driving Scheme Setting Command Table</td></tr><tr><td>D/C#</td><td>Hex</td><td>D7</td><td>D6</td><td>D5</td><td>D4</td><td>D3</td><td>D2</td><td>D1</td><td>D0</td><td>Command</td><td>Description</td></tr><tr><td>0</td><td>D5</td><td>1</td><td>1</td><td>0</td><td>1</td><td>0</td><td>1</td><td>0</td><td>1</td><td>Set Display Clock</td><td rowspan="2">A[3:0] : Define the divide ratio (D) of the display clocks (DCLK):Divide ratio= A[3:0] + 1, RESET is 0000b (divide ratio = 1)</td></tr><tr><td>0</td><td>A[7:0]</td><td><eq>A_7</eq></td><td><eq>A_6</eq></td><td><eq>A_5</eq></td><td><eq>A_4</eq></td><td><eq>A_3</eq></td><td><eq>A_2</eq></td><td><eq>A_1</eq></td><td><eq>A_0</eq></td><td>Divide Ratio/Oscillator Frequency</td></tr><tr><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td>A[7:4] : Set the Oscillator Frequency, <eq>F_{osc}</eq>. Oscillator Frequency increases with the value of A[7:4] and vice versa. RESET is 1000bRange:0000b~1111bFrequency increases as setting value increases.</td></tr><tr><td>0</td><td>D9</td><td>1</td><td>1</td><td>0</td><td>1</td><td>1</td><td>0</td><td>0</td><td>1</td><td>Set Pre-charge Period</td><td>A[3:0] : Phase 1 period of up to 15 DCLK clocks 0 is invalid entry (RESET=2h)</td></tr><tr><td>0</td><td>A[7:0]</td><td><eq>A_7</eq></td><td><eq>A_6</eq></td><td><eq>A_5</eq></td><td><eq>A_4</eq></td><td><eq>A_3</eq></td><td><eq>A_2</eq></td><td><eq>A_1</eq></td><td><eq>A_0</eq></td><td></td><td>A[7:4] : Phase 2 period of up to 15 DCLK clocks 0 is invalid entry (RESET=2h )</td></tr><tr><td>0</td><td>DB</td><td>1</td><td>1</td><td>0</td><td>1</td><td>1</td><td>0</td><td>1</td><td>1</td><td rowspan="2">Set <eq>V_{COMH}</eq> Deselect Level</td><td></td></tr><tr><td>0</td><td>A[6:4]</td><td>0</td><td><eq>A_6</eq></td><td><eq>A_5</eq></td><td><eq>A_4</eq></td><td>0</td><td>0</td><td>0</td><td>0</td><td>A[6:4] Hex code <eq>V_{COMH}</eq> deselect level</td></tr><tr><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td>000b 00h ~ 0.65 x <eq>V_{CC}</eq></td></tr><tr><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td>010b 20h ~ 0.77 x <eq>V_{CC}</eq> (RESET)</td></tr><tr><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td>011b 30h ~ 0.83 x <eq>V_{CC}</eq></td></tr><tr><td>0</td><td>E3</td><td>1</td><td>1</td><td>1</td><td>0</td><td>0</td><td>0</td><td>1</td><td>1</td><td>NOP</td><td>Command for no operation</td></tr></table>

(1) “*” stands for “Don’t care”. 

## Note


Table 9-2 : Read Command Table


<table><tr><td>Bit Pattern</td><td>Command</td><td>Description</td></tr><tr><td><eq>D_{7}D_{6}D_{5}D_{4}D_{3}D_{2}D_{1}D_{0}</eq></td><td>Status Register Read</td><td>D[7]: ReservedD[6]: “1” for display OFF / “0” for display OND[5]: ReservedD[4]: ReservedD[3]: ReservedD[2]: ReservedD[1]: ReservedD[0]: Reserved</td></tr></table>

Note 

<sup>(1)</sup> Patterns other than those given in the Command Table are prohibited to enter the chip as a command; as unexpected results can occur. 

## 9.1 Data Read / Write

To read data from the GDDRAM, select HIGH for both the R/W# (WR#) pin and the D/C# pin for 6800- series parallel mode and select LOW for the E (RD#) pin and HIGH for the D/C# pin for 8080-series parallel mode. No data read is provided in serial mode operation. 

In normal data read mode the GDDRAM column address pointer will be increased automatically by one after each data read. 

Also, a dummy read is required before the first data read. 

To write data to the GDDRAM, select LOW for the R/W# (WR#) pin and HIGH for the D/C# pin for both 6800-series parallel mode and 8080-series parallel mode. The serial interface mode is always in write mode. The GDDRAM column address pointer will be increased automatically by one after each data write. 


Table 9-3 : Address increment table (Automatic)


<table><tr><td>D/C#</td><td>R/W# (WR#)</td><td>Comment</td><td>Address Increment</td></tr><tr><td>0</td><td>0</td><td>Write Command</td><td>No</td></tr><tr><td>0</td><td>1</td><td>Read Status</td><td>No</td></tr><tr><td>1</td><td>0</td><td>Write Data</td><td>Yes</td></tr><tr><td>1</td><td>1</td><td>Read Data</td><td>Yes</td></tr></table>

## 10 COMMAND DESCRIPTIONS

## 10.1 Fundamental Command

## 10.1.1 Set Lower Column Start Address for Page Addressing Mode (00h~0Fh)

This command specifies the lower nibble of the 8-bit column start address for the display data RAM under Page Addressing Mode. The column address will be incremented by each data access. Please refer to Section Table 9-1 and Section 10.1.3 for details. 

## 10.1.2 Set Higher Column Start Address for Page Addressing Mode (10h~1Fh)

This command specifies the higher nibble of the 8-bit column start address for the display data RAM under Page Addressing Mode. The column address will be incremented by each data access. Please refer to Section Table 9-1 and Section 10.1.3 for details. 

## 10.1.3 Set Memory Addressing Mode (20h)

There are 3 different memory addressing mode in SSD1306: page addressing mode, horizontal addressing mode and vertical addressing mode. This command sets the way of memory addressing into one of the above three modes. In there, “COL” means the graphic display data RAM column. 

Page addressing mode (A[1:0]=10xb) 

In page addressing mode, after the display RAM is read/written, the column address pointer is increased automatically by 1. If the column address pointer reaches column end address, the column address pointer is reset to column start address and page address pointer is not changed. Users have to set the new page and column addresses in order to access the next page RAM content. The sequence of movement of the PAGE and column address point for page addressing mode is shown in Figure 10-1. 


Figure 10-1 : Address Pointer Movement of Page addressing mode


<table><tr><td></td><td>COL0</td><td>COL 1</td><td>......</td><td>COL 126</td><td>COL 127</td></tr><tr><td>PAGE0</td><td></td><td></td><td></td><td></td><td></td></tr><tr><td>PAGE1</td><td></td><td></td><td></td><td></td><td></td></tr><tr><td>:</td><td>:</td><td>:</td><td>:</td><td>:</td><td>:</td></tr><tr><td>PAGE6</td><td></td><td></td><td></td><td></td><td></td></tr><tr><td>PAGE7</td><td></td><td></td><td></td><td></td><td></td></tr></table>

In normal display data RAM read or write and page addressing mode, the following steps are required to define the starting RAM access pointer location: 

• Set the page start address of the target display location by command B0h to B7h. 

• Set the lower start column address of pointer by command 00h~0Fh. 

• Set the upper start column address of pointer by command 10h~1Fh. 

For example, if the page address is set to B2h, lower column address is 03h and upper column address is 10h, then that means the starting column is SEG3 of PAGE2. The RAM access pointer is located as shown in Figure 10-2. The input data byte will be written into RAM position of column 3. 


Figure 10-2 : Example of GDDRAM access pointer setting in Page Addressing Mode (No row and column remapping)


<table><tr><td>SEG0</td><td>SEG3 (Starting column)</td><td>RAM access pointer</td><td>Remapping)</td></tr><tr><td colspan="2">LSB D0</td><td rowspan="2" colspan="2">Each lattice represents one bit of image data</td></tr><tr><td colspan="2">MSB D7</td></tr><tr><td>COM16</td><td>COM17</td><td></td><td></td></tr><tr><td>:</td><td></td><td></td><td></td></tr><tr><td>:</td><td></td><td></td><td></td></tr><tr><td>:</td><td></td><td></td><td></td></tr><tr><td>:</td><td></td><td></td><td></td></tr><tr><td>COM23</td><td></td><td></td><td></td></tr></table>

## Horizontal addressing mode (A[1:0]=00b)

In horizontal addressing mode, after the display RAM is read/written, the column address pointer is increased automatically by 1. If the column address pointer reaches column end address, the column address pointer is reset to column start address and page address pointer is increased by 1. The sequence of movement of the page and column address point for horizontal addressing mode is shown in Figure 10-3. When both column and page address pointers reach the end address, the pointers are reset to column start address and page start address (Dotted line in Figure 10-3.) 


Figure 10-3 : Address Pointer Movement of Horizontal addressing mode


<table><tr><td></td><td>COL0</td><td>COL 1</td><td>......</td><td>COL 126</td><td>COL 127</td></tr><tr><td>PAGE0</td><td></td><td></td><td></td><td></td><td></td></tr><tr><td>PAGE1</td><td></td><td></td><td></td><td></td><td></td></tr><tr><td>:</td><td></td><td></td><td></td><td></td><td></td></tr><tr><td>PAGE6</td><td></td><td></td><td></td><td></td><td></td></tr><tr><td>PAGE7</td><td></td><td></td><td></td><td></td><td></td></tr></table>

Vertical addressing mode: (A[1:0]=01b) 

In vertical addressing mode, after the display RAM is read/written, the page address pointer is increased automatically by 1. If the page address pointer reaches the page end address, the page address pointer is reset to page start address and column address pointer is increased by 1. The sequence of movement of the page and column address point for vertical addressing mode is shown in Figure 10-4. When both column and page address pointers reach the end address, the pointers are reset to column start address and page start address (Dotted line in Figure 10-4.) 


Figure 10-4 : Address Pointer Movement of Vertical addressing mode


<table><tr><td></td><td>COL0</td><td>COL 1</td><td>......</td><td>COL 126</td><td>COL 127</td></tr><tr><td>PAGE0</td><td></td><td></td><td>......</td><td></td><td></td></tr><tr><td>PAGE1</td><td></td><td></td><td>......</td><td></td><td></td></tr><tr><td>:</td><td></td><td></td><td>...</td><td></td><td></td></tr><tr><td>PAGE6</td><td></td><td></td><td>......</td><td></td><td></td></tr><tr><td>PAGE7</td><td></td><td></td><td>......</td><td></td><td></td></tr></table>

In normal display data RAM read or write and horizontal / vertical addressing mode, the following steps are required to define the RAM access pointer location: 

• Set the column start and end address of the target display location by command 21h. 

• Set the page start and end address of the target display location by command 22h. 

Example is shown in Figure 10-5. 

## 10.1.4 Set Column Address (21h)

This triple byte command specifies column start address and end address of the display data RAM. This command also sets the column address pointer to column start address. This pointer is used to define the current read/write column address in graphic display data RAM. If horizontal address increment mode is enabled by command 20h, after finishing read/write one column data, it is incremented automatically to the next column address. Whenever the column address pointer finishes accessing the end column address, it is reset back to start column address and the row address is incremented to the next row. 

## 10.1.5 Set Page Address (22h)

This triple byte command specifies page start address and end address of the display data RAM. This command also sets the page address pointer to page start address. This pointer is used to define the current read/write page address in graphic display data RAM. If vertical address increment mode is enabled by command 20h, after finishing read/write one page data, it is incremented automatically to the next page address. Whenever the page address pointer finishes accessing the end page address, it is reset back to start page address. 

The figure below shows the way of column and page address pointer movement through the example: column start address is set to 2 and column end address is set to 125, page start address is set to 1 and page end address is set to 6; Horizontal address increment mode is enabled by command 20h. In this case, the graphic display data RAM column accessible range is from column 2 to column 125 and from page 1 to page 6 only. In addition, the column address pointer is set to 2 and page address pointer is set to 1. After finishing read/write one pixel of data, the column address is increased automatically by 1 to access the next RAM location for next read/write operation (solid line in Figure 10-5). Whenever the column address pointer finishes accessing the end column 125, it is reset back to column 2 and page address is automatically increased by 1 (solid line in Figure 10-5). While the end page 6 and end column 125 RAM location is accessed, the page address is reset back to 1 and the column address is reset back to 2 (dotted line in Figure 10-5). . 


Figure 10-5 : Example of Column and Row Address Pointer Movement


<table><tr><td></td><td>Col 0</td><td>Col 1</td><td>Col 2</td><td>......</td><td>......</td><td>Col 125</td><td>Col 126</td><td>Col 127</td></tr><tr><td>PAGE0</td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr><tr><td>PAGE1</td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr><tr><td>:</td><td></td><td></td><td></td><td>:</td><td></td><td></td><td></td><td></td></tr><tr><td>PAGE6</td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr><tr><td>PAGE7</td><td></td><td></td><td></td><td>:</td><td></td><td></td><td></td><td></td></tr></table>

## 10.1.6 Set Display Start Line (40h~7Fh)

This command sets the Display Start Line register to determine starting address of display RAM, by selecting a value from 0 to 63. With value equal to 0, RAM row 0 is mapped to COM0. With value equal to 1, RAM row 1 is mapped to COM0 and so on. 

Refer to Table 10-1 for more illustrations. 

## 10.1.7 Set Contrast Control for BANK0 (81h)

This command sets the Contrast Setting of the display. The chip has 256 contrast steps from 00h to FFh. The segment output current increases as the contrast step value increases. 

## 10.1.8 Set Segment Re-map (A0h/A1h)

This command changes the mapping between the display data column address and the segment driver. It allows flexibility in OLED module design. Please refer to Table 9-1. 

This command only affects subsequent data input. Data already stored in GDDRAM will have no changes. 

## 10.1.9 Entire Display ON (A4h/A5h)

A4h command enable display outputs according to the GDDRAM contents. 

If A5h command is issued, then by using A4h command, the display will resume to the GDDRAM contents. In other words, A4h command resumes the display from entire display “ON” stage. 

A5h command forces the entire display to be “ON”, regardless of the contents of the display data RAM. 

## 10.1.10 Set Normal/Inverse Display (A6h/A7h)

This command sets the display to be either normal or inverse. In normal display a RAM data of 1 indicates an “ON” pixel while in inverse display a RAM data of 0 indicates an “ON” pixel. 

## 10.1.11 Set Multiplex Ratio (A8h)

This command switches the default 63 multiplex mode to any multiplex ratio, ranging from 16 to 63. The output pads COM0~COM63 will be switched to the corresponding COM signal. 

## 10.1.12 Set Display ON/OFF (AEh/AFh)

These single byte commands are used to turn the OLED panel display ON or OFF. 

When the display is ON, the selected circuits by Set Master Configuration command will be turned ON. When the display is OFF, those circuits will be turned OFF and the segment and common output are in V<sub>SS</sub> state and high impedance state, respectively. These commands set the display to one of the two states: 

o AEh : Display OFF 

o AFh : Display ON 


Figure 10-6 :Transition between different modes


![image](https://cdn-mineru.openxlab.org.cn/result/2026-09-08/61e8663c-ef74-4a31-bef6-08879770bc52/92f815699a935cbb395ffea3f0c5b8b66b7b481db3cacdb3aa3548940ed86c87.jpg)


## 10.1.13 Set Page Start Address for Page Addressing Mode (B0h~B7h)

This command positions the page start address from 0 to 7 in GDDRAM under Page Addressing Mode. Please refer to Table 9-1 and Section 10.1.3 for details. 

## 10.1.14 Set COM Output Scan Direction (C0h/C8h)

This command sets the scan direction of the COM output, allowing layout flexibility in the OLED module design. Additionally, the display will show once this command is issued. For example, if this command is sent during normal display then the graphic display will be vertically flipped immediately. Please refer to Table 10-3 for details. 

## 10.1.15 Set Display Offset (D3h)

This is a double byte command. The second command specifies the mapping of the display start line to one of COM0~COM63 (assuming that COM0 is the display start line then the display start line register is equal to 0). 

For example, to move the COM16 towards the COM0 direction by 16 lines the 6-bit data in the second byte should be given as 010000b. To move in the opposite direction by 16 lines the 6-bit data should be given by 64 – 16, so the second byte would be 100000b. The following two tables (Table 10-1, Table 10-2) show the example of setting the command C0h/C8h and D3h. 


Table 10-1 : Example of Set Display Offset and Display Start Line with no Remap


<table><tr><td rowspan="5">Hardware pin name</td><td colspan="11">Output</td><td></td></tr><tr><td colspan="2">64</td><td colspan="2">64</td><td colspan="2">64</td><td colspan="2">56</td><td colspan="2">56</td><td>56</td><td>Set MUX ratio(A8h)</td></tr><tr><td colspan="2">Normal</td><td colspan="2">Normal</td><td colspan="2">Normal</td><td colspan="2">Normal</td><td colspan="2">Normal</td><td>Normal</td><td>COM Normal / Remapped (C0h / C8h)</td></tr><tr><td colspan="2">0</td><td colspan="2">8</td><td colspan="2">0</td><td colspan="2">0</td><td colspan="2">8</td><td>0</td><td>Display offset (D3h)</td></tr><tr><td colspan="2">0</td><td colspan="2">0</td><td colspan="2">8</td><td colspan="2">0</td><td colspan="2">0</td><td>8</td><td>Display start line (40h - 7Fh)</td></tr><tr><td>COM0</td><td>Row0</td><td>RAM0</td><td>Row8</td><td>RAM8</td><td>Row0</td><td>RAM8</td><td>Row0</td><td>RAM0</td><td>Row8</td><td>RAM8</td><td>Row0</td><td>RAM8</td></tr><tr><td>COM1</td><td>Row1</td><td>RAM1</td><td>Row9</td><td>RAM9</td><td>Row1</td><td>RAM9</td><td>Row1</td><td>RAM1</td><td>Row9</td><td>RAM9</td><td>Row1</td><td>RAM9</td></tr><tr><td>COM2</td><td>Row2</td><td>RAM2</td><td>Row10</td><td>RAM10</td><td>Row2</td><td>RAM10</td><td>Row2</td><td>RAM2</td><td>Row10</td><td>RAM10</td><td>Row2</td><td>RAM10</td></tr><tr><td>COM3</td><td>Row3</td><td>RAM3</td><td>Row11</td><td>RAM11</td><td>Row3</td><td>RAM11</td><td>Row3</td><td>RAM3</td><td>Row11</td><td>RAM11</td><td>Row3</td><td>RAM11</td></tr><tr><td>COM4</td><td>Row4</td><td>RAM4</td><td>Row12</td><td>RAM12</td><td>Row4</td><td>RAM12</td><td>Row4</td><td>RAM4</td><td>Row12</td><td>RAM12</td><td>Row4</td><td>RAM12</td></tr><tr><td>COM5</td><td>Row5</td><td>RAM5</td><td>Row13</td><td>RAM13</td><td>Row5</td><td>RAM13</td><td>Row5</td><td>RAM5</td><td>Row13</td><td>RAM13</td><td>Row5</td><td>RAM13</td></tr><tr><td>COM6</td><td>Row6</td><td>RAM6</td><td>Row14</td><td>RAM14</td><td>Row6</td><td>RAM14</td><td>Row6</td><td>RAM6</td><td>Row14</td><td>RAM14</td><td>Row6</td><td>RAM14</td></tr><tr><td>COM7</td><td>Row7</td><td>RAM7</td><td>Row15</td><td>RAM15</td><td>Row7</td><td>RAM15</td><td>Row7</td><td>RAM7</td><td>Row15</td><td>RAM15</td><td>Row7</td><td>RAM15</td></tr><tr><td>COM8</td><td>Row8</td><td>RAM8</td><td>Row16</td><td>RAM16</td><td>Row8</td><td>RAM16</td><td>Row8</td><td>RAM8</td><td>Row16</td><td>RAM16</td><td>Row8</td><td>RAM16</td></tr><tr><td>COM9</td><td>Row9</td><td>RAM9</td><td>Row17</td><td>RAM17</td><td>Row9</td><td>RAM17</td><td>Row9</td><td>RAM9</td><td>Row17</td><td>RAM17</td><td>Row9</td><td>RAM17</td></tr><tr><td>COM10</td><td>Row10</td><td>RAM10</td><td>Row18</td><td>RAM18</td><td>Row10</td><td>RAM18</td><td>Row10</td><td>RAM10</td><td>Row18</td><td>RAM18</td><td>Row10</td><td>RAM18</td></tr><tr><td>COM11</td><td>Row11</td><td>RAM11</td><td>Row19</td><td>RAM19</td><td>Row11</td><td>RAM19</td><td>Row11</td><td>RAM11</td><td>Row19</td><td>RAM19</td><td>Row11</td><td>RAM19</td></tr><tr><td>COM12</td><td>Row12</td><td>RAM12</td><td>Row20</td><td>RAM20</td><td>Row12</td><td>RAM20</td><td>Row12</td><td>RAM12</td><td>Row20</td><td>RAM20</td><td>Row12</td><td>RAM20</td></tr><tr><td>COM13</td><td>Row13</td><td>RAM13</td><td>Row21</td><td>RAM21</td><td>Row13</td><td>RAM21</td><td>Row13</td><td>RAM13</td><td>Row21</td><td>RAM21</td><td>Row13</td><td>RAM21</td></tr><tr><td>COM14</td><td>Row14</td><td>RAM14</td><td>Row22</td><td>RAM22</td><td>Row14</td><td>RAM22</td><td>Row14</td><td>RAM14</td><td>Row22</td><td>RAM22</td><td>Row14</td><td>RAM22</td></tr><tr><td>COM15</td><td>Row15</td><td>RAM15</td><td>Row23</td><td>RAM23</td><td>Row15</td><td>RAM23</td><td>Row15</td><td>RAM15</td><td>Row23</td><td>RAM23</td><td>Row15</td><td>RAM23</td></tr><tr><td>COM16</td><td>Row16</td><td>RAM16</td><td>Row24</td><td>RAM24</td><td>Row16</td><td>RAM24</td><td>Row16</td><td>RAM16</td><td>Row24</td><td>RAM24</td><td>Row16</td><td>RAM24</td></tr><tr><td>COM17</td><td>Row17</td><td>RAM17</td><td>Row25</td><td>RAM25</td><td>Row17</td><td>RAM25</td><td>Row17</td><td>RAM17</td><td>Row25</td><td>RAM25</td><td>Row17</td><td>RAM25</td></tr><tr><td>COM18</td><td>Row18</td><td>RAM18</td><td>Row26</td><td>RAM26</td><td>Row18</td><td>RAM26</td><td>Row18</td><td>RAM18</td><td>Row26</td><td>RAM26</td><td>Row18</td><td>RAM26</td></tr><tr><td>COM19</td><td>Row19</td><td>RAM19</td><td>Row27</td><td>RAM27</td><td>Row19</td><td>RAM27</td><td>Row19</td><td>RAM19</td><td>Row27</td><td>RAM27</td><td>Row19</td><td>RAM27</td></tr><tr><td>COM20</td><td>Row20</td><td>RAM20</td><td>Row28</td><td>RAM28</td><td>Row20</td><td>RAM28</td><td>Row20</td><td>RAM20</td><td>Row28</td><td>RAM28</td><td>Row20</td><td>RAM28</td></tr><tr><td>COM21</td><td>Row21</td><td>RAM21</td><td>Row29</td><td>RAM29</td><td>Row21</td><td>RAM29</td><td>Row21</td><td>RAM21</td><td>Row29</td><td>RAM29</td><td>Row21</td><td>RAM29</td></tr><tr><td>COM22</td><td>Row22</td><td>RAM22</td><td>Row30</td><td>RAM30</td><td>Row22</td><td>RAM30</td><td>Row22</td><td>RAM22</td><td>Row30</td><td>RAM30</td><td>Row22</td><td>RAM30</td></tr><tr><td>COM23</td><td>Row23</td><td>RAM23</td><td>Row31</td><td>RAM31</td><td>Row23</td><td>RAM31</td><td>Row23</td><td>RAM23</td><td>Row31</td><td>RAM31</td><td>Row23</td><td>RAM31</td></tr><tr><td>COM24</td><td>Row24</td><td>RAM24</td><td>Row32</td><td>RAM32</td><td>Row24</td><td>RAM32</td><td>Row24</td><td>RAM24</td><td>Row32</td><td>RAM32</td><td>Row24</td><td>RAM32</td></tr><tr><td>COM25</td><td>Row25</td><td>RAM25</td><td>Row33</td><td>RAM33</td><td>Row25</td><td>RAM33</td><td>Row25</td><td>RAM25</td><td>Row33</td><td>RAM33</td><td>Row25</td><td>RAM33</td></tr><tr><td>COM26</td><td>Row26</td><td>RAM26</td><td>Row34</td><td>RAM34</td><td>Row26</td><td>RAM34</td><td>Row26</td><td>RAM26</td><td>Row34</td><td>RAM34</td><td>Row26</td><td>RAM34</td></tr><tr><td>COM27</td><td>Row27</td><td>RAM27</td><td>Row35</td><td>RAM35</td><td>Row27</td><td>RAM35</td><td>Row27</td><td>RAM27</td><td>Row35</td><td>RAM35</td><td>Row27</td><td>RAM35</td></tr><tr><td>COM28</td><td>Row28</td><td>RAM28</td><td>Row36</td><td>RAM36</td><td>Row28</td><td>RAM36</td><td>Row28</td><td>RAM28</td><td>Row36</td><td>RAM36</td><td>Row28</td><td>RAM36</td></tr><tr><td>COM29</td><td>Row29</td><td>RAM29</td><td>Row37</td><td>RAM37</td><td>Row29</td><td>RAM37</td><td>Row29</td><td>RAM29</td><td>Row37</td><td>RAM37</td><td>Row29</td><td>RAM37</td></tr><tr><td>COM30</td><td>Row30</td><td>RAM30</td><td>Row38</td><td>RAM38</td><td>Row30</td><td>RAM38</td><td>Row30</td><td>RAM30</td><td>Row38</td><td>RAM38</td><td>Row30</td><td>RAM38</td></tr><tr><td>COM31</td><td>Row31</td><td>RAM31</td><td>Row39</td><td>RAM39</td><td>Row31</td><td>RAM39</td><td>Row31</td><td>RAM31</td><td>Row39</td><td>RAM39</td><td>Row31</td><td>RAM39</td></tr><tr><td>COM32</td><td>Row32</td><td>RAM32</td><td>Row40</td><td>RAM40</td><td>Row32</td><td>RAM40</td><td>Row32</td><td>RAM32</td><td>Row40</td><td>RAM40</td><td>Row32</td><td>RAM40</td></tr><tr><td>COM33</td><td>Row33</td><td>RAM33</td><td>Row41</td><td>RAM41</td><td>Row33</td><td>RAM41</td><td>Row33</td><td>RAM33</td><td>Row41</td><td>RAM41</td><td>Row33</td><td>RAM41</td></tr><tr><td>COM34</td><td>Row34</td><td>RAM34</td><td>Row42</td><td>RAM42</td><td>Row34</td><td>RAM42</td><td>Row34</td><td>RAM34</td><td>Row42</td><td>RAM42</td><td>Row34</td><td>RAM42</td></tr><tr><td>COM35</td><td>Row35</td><td>RAM35</td><td>Row43</td><td>RAM43</td><td>Row35</td><td>RAM43</td><td>Row35</td><td>RAM35</td><td>Row43</td><td>RAM43</td><td>Row35</td><td>RAM43</td></tr><tr><td>COM36</td><td>Row36</td><td>RAM36</td><td>Row44</td><td>RAM44</td><td>Row36</td><td>RAM44</td><td>Row36</td><td>RAM36</td><td>Row44</td><td>RAM44</td><td>Row36</td><td>RAM44</td></tr><tr><td>COM37</td><td>Row37</td><td>RAM37</td><td>Row45</td><td>RAM45</td><td>Row37</td><td>RAM45</td><td>Row37</td><td>RAM37</td><td>Row45</td><td>RAM45</td><td>Row37</td><td>RAM45</td></tr><tr><td>COM38</td><td>Row38</td><td>RAM38</td><td>Row46</td><td>RAM46</td><td>Row38</td><td>RAM46</td><td>Row38</td><td>RAM38</td><td>Row46</td><td>RAM46</td><td>Row38</td><td>RAM46</td></tr><tr><td>COM39</td><td>Row39</td><td>RAM39</td><td>Row47</td><td>RAM47</td><td>Row39</td><td>RAM47</td><td>Row39</td><td>RAM39</td><td>Row47</td><td>RAM47</td><td>Row39</td><td>RAM47</td></tr><tr><td>COM40</td><td>Row40</td><td>RAM40</td><td>Row48</td><td>RAM48</td><td>Row40</td><td>RAM48</td><td>Row40</td><td>RAM40</td><td>Row48</td><td>RAM48</td><td>Row40</td><td>RAM48</td></tr><tr><td>COM41</td><td>Row41</td><td>RAM41</td><td>Row49</td><td>RAM49</td><td>Row41</td><td>RAM49</td><td>Row41</td><td>RAM41</td><td>Row49</td><td>RAM49</td><td>Row41</td><td>RAM49</td></tr><tr><td>COM42</td><td>Row42</td><td>RAM42</td><td>Row50</td><td>RAM50</td><td>Row42</td><td>RAM50</td><td>Row42</td><td>RAM42</td><td>Row50</td><td>RAM50</td><td>Row42</td><td>RAM50</td></tr><tr><td>COM43</td><td>Row43</td><td>RAM43</td><td>Row51</td><td>RAM51</td><td>Row43</td><td>RAM51</td><td>Row43</td><td>RAM43</td><td>Row51</td><td>RAM51</td><td>Row43</td><td>RAM51</td></tr><tr><td>COM44</td><td>Row44</td><td>RAM44</td><td>Row52</td><td>RAM52</td><td>Row44</td><td>RAM52</td><td>Row44</td><td>RAM44</td><td>Row52</td><td>RAM52</td><td>Row44</td><td>RAM52</td></tr><tr><td>COM45</td><td>Row45</td><td>RAM45</td><td>Row53</td><td>RAM53</td><td>Row45</td><td>RAM53</td><td>Row45</td><td>RAM45</td><td>Row53</td><td>RAM53</td><td>Row45</td><td>RAM53</td></tr><tr><td>COM46</td><td>Row46</td><td>RAM46</td><td>Row54</td><td>RAM54</td><td>Row46</td><td>RAM54</td><td>Row46</td><td>RAM46</td><td>Row54</td><td>RAM54</td><td>Row46</td><td>RAM54</td></tr><tr><td>COM47</td><td>Row47</td><td>RAM47</td><td>Row55</td><td>RAM55</td><td>Row47</td><td>RAM55</td><td>Row47</td><td>RAM47</td><td>Row55</td><td>RAM55</td><td>Row47</td><td>RAM55</td></tr><tr><td>COM48</td><td>Row48</td><td>RAM48</td><td>Row56</td><td>RAM56</td><td>Row48</td><td>RAM56</td><td>Row48</td><td>RAM48</td><td>-</td><td>-</td><td>Row48</td><td>RAM56</td></tr><tr><td>COM49</td><td>Row49</td><td>RAM49</td><td>Row57</td><td>RAM57</td><td>Row49</td><td>RAM57</td><td>Row49</td><td>RAM49</td><td>-</td><td>-</td><td>Row49</td><td>RAM57</td></tr><tr><td>COM50</td><td>Row50</td><td>RAM50</td><td>Row58</td><td>RAM58</td><td>Row50</td><td>RAM58</td><td>Row50</td><td>RAM50</td><td>-</td><td>-</td><td>Row50</td><td>RAM58</td></tr><tr><td>COM51</td><td>Row51</td><td>RAM51</td><td>Row59</td><td>RAM59</td><td>Row51</td><td>RAM59</td><td>Row51</td><td>RAM51</td><td>-</td><td>-</td><td>Row51</td><td>RAM59</td></tr><tr><td>COM52</td><td>Row52</td><td>RAM52</td><td>Row60</td><td>RAM60</td><td>Row52</td><td>RAM60</td><td>Row52</td><td>RAM52</td><td>-</td><td>-</td><td>Row52</td><td>RAM60</td></tr><tr><td>COM53</td><td>Row53</td><td>RAM53</td><td>Row61</td><td>RAM61</td><td>Row53</td><td>RAM61</td><td>Row53</td><td>RAM53</td><td>-</td><td>-</td><td>Row53</td><td>RAM61</td></tr><tr><td>COM54</td><td>Row54</td><td>RAM54</td><td>Row62</td><td>RAM62</td><td>Row54</td><td>RAM62</td><td>Row54</td><td>RAM54</td><td>-</td><td>-</td><td>Row54</td><td>RAM62</td></tr><tr><td>COM55</td><td>Row55</td><td>RAM55</td><td>Row63</td><td>RAM63</td><td>Row55</td><td>RAM63</td><td>Row55</td><td>RAM55</td><td>-</td><td>-</td><td>Row55</td><td>RAM63</td></tr><tr><td>COM56</td><td>Row56</td><td>RAM56</td><td>Row0</td><td>RAM0</td><td>Row56</td><td>RAM0</td><td>-</td><td>-</td><td>Row0</td><td>RAM0</td><td>-</td><td>-</td></tr><tr><td>COM57</td><td>Row57</td><td>RAM57</td><td>Row1</td><td>RAM1</td><td>Row57</td><td>RAM1</td><td>-</td><td>-</td><td>Row1</td><td>RAM1</td><td>-</td><td>-</td></tr><tr><td>COM58</td><td>Row58</td><td>RAM58</td><td>Row2</td><td>RAM2</td><td>Row58</td><td>RAM2</td><td>-</td><td>-</td><td>Row2</td><td>RAM2</td><td>-</td><td>-</td></tr><tr><td>COM59</td><td>Row59</td><td>RAM59</td><td>Row3</td><td>RAM3</td><td>Row59</td><td>RAM3</td><td>-</td><td>-</td><td>Row3</td><td>RAM3</td><td>-</td><td>-</td></tr><tr><td>COM60</td><td>Row60</td><td>RAM60</td><td>Row4</td><td>RAM4</td><td>Row60</td><td>RAM4</td><td>-</td><td>-</td><td>Row4</td><td>RAM4</td><td>-</td><td>-</td></tr><tr><td>COM61</td><td>Row61</td><td>RAM61</td><td>Row5</td><td>RAM5</td><td>Row61</td><td>RAM5</td><td>-</td><td>-</td><td>Row5</td><td>RAM5</td><td>-</td><td>-</td></tr><tr><td>COM62</td><td>Row62</td><td>RAM62</td><td>Row6</td><td>RAM6</td><td>Row62</td><td>RAM6</td><td>-</td><td>-</td><td>Row6</td><td>RAM6</td><td>-</td><td>-</td></tr><tr><td>COM63</td><td>Row63</td><td>RAM63</td><td>Row7</td><td>RAM7</td><td>Row63</td><td>RAM7</td><td>-</td><td>-</td><td>Row7</td><td>RAM7</td><td>-</td><td>-</td></tr></table>

![image](https://cdn-mineru.openxlab.org.cn/result/2026-09-08/61e8663c-ef74-4a31-bef6-08879770bc52/c0e6614db0554803f0b10da69e2e8b982b4e3dc5c332684f3219d0f2d39cebc1.jpg)



Table 10-2 :Example of Set Display Offset and Display Start Line with Remap


<table><tr><td rowspan="5">Hardware pin name</td><td colspan="13">Output</td></tr><tr><td colspan="2">64</td><td colspan="2">64</td><td colspan="2">64</td><td colspan="2">48</td><td colspan="2">48</td><td colspan="2">48</td><td>48</td></tr><tr><td colspan="2">Remap</td><td colspan="2">Remap</td><td colspan="2">Remap</td><td colspan="2">Remap</td><td colspan="2">Remap</td><td colspan="2">Remap</td><td>Remap</td></tr><tr><td colspan="2">0</td><td colspan="2">8</td><td colspan="2">0</td><td colspan="2">0</td><td colspan="2">8</td><td colspan="2">0</td><td>8</td></tr><tr><td colspan="2">0</td><td colspan="2">0</td><td colspan="2">8</td><td colspan="2">0</td><td colspan="2">0</td><td colspan="2">8</td><td>16</td></tr><tr><td>COM0</td><td>Row63</td><td>RAM63</td><td>Row7</td><td>RAM7</td><td>Row63</td><td>RAM7</td><td>Row47</td><td>RAM47</td><td>-</td><td>-</td><td>Row47</td><td>RAM55</td><td>-</td></tr><tr><td>COM1</td><td>Row62</td><td>RAM62</td><td>Row6</td><td>RAM6</td><td>Row62</td><td>RAM6</td><td>Row46</td><td>RAM46</td><td>-</td><td>-</td><td>Row46</td><td>RAM54</td><td>-</td></tr><tr><td>COM2</td><td>Row61</td><td>RAM61</td><td>Row6</td><td>RAM6</td><td>Row61</td><td>RAM6</td><td>Row45</td><td>RAM45</td><td>-</td><td>-</td><td>Row45</td><td>RAM53</td><td>-</td></tr><tr><td>COM3</td><td>Row60</td><td>RAM60</td><td>Row4</td><td>RAM4</td><td>Row60</td><td>RAM4</td><td>Row44</td><td>RAM44</td><td>-</td><td>-</td><td>Row44</td><td>RAM52</td><td>-</td></tr><tr><td>COM4</td><td>Row59</td><td>RAM59</td><td>Row3</td><td>RAM3</td><td>Row59</td><td>RAM3</td><td>Row43</td><td>RAM43</td><td>-</td><td>-</td><td>Row43</td><td>RAM51</td><td>-</td></tr><tr><td>COM5</td><td>Row58</td><td>RAM58</td><td>Row2</td><td>RAM2</td><td>Row58</td><td>RAM2</td><td>Row42</td><td>RAM42</td><td>-</td><td>-</td><td>Row42</td><td>RAM50</td><td>-</td></tr><tr><td>COM6</td><td>Row57</td><td>RAM57</td><td>Row1</td><td>RAM1</td><td>Row57</td><td>RAM1</td><td>Row41</td><td>RAM41</td><td>-</td><td>-</td><td>Row41</td><td>RAM49</td><td>-</td></tr><tr><td>COM7</td><td>Row56</td><td>RAM56</td><td>Row0</td><td>RAM0</td><td>Row56</td><td>RAM0</td><td>Row40</td><td>RAM40</td><td>-</td><td>-</td><td>Row40</td><td>RAM48</td><td>-</td></tr><tr><td>COM8</td><td>Row55</td><td>RAM55</td><td>Row63</td><td>RAM63</td><td>Row65</td><td>RAM63</td><td>Row39</td><td>RAM59</td><td>Row47</td><td>RAM47</td><td>Row39</td><td>RAM47</td><td>Row47</td></tr><tr><td>COM9</td><td>Row54</td><td>RAM54</td><td>Row62</td><td>RAM62</td><td>Row54</td><td>RAM62</td><td>Row38</td><td>RAM38</td><td>Row46</td><td>RAM46</td><td>Row38</td><td>RAM46</td><td>Row46</td></tr><tr><td>COM10</td><td>Row53</td><td>RAM53</td><td>Row61</td><td>RAM61</td><td>Row53</td><td>RAM61</td><td>Row37</td><td>RAM37</td><td>Row45</td><td>RAM45</td><td>Row37</td><td>RAM45</td><td>Row45</td></tr><tr><td>COM11</td><td>Row52</td><td>RAM52</td><td>Row60</td><td>RAM60</td><td>Row52</td><td>RAM60</td><td>Row36</td><td>RAM36</td><td>Row44</td><td>RAM44</td><td>Row36</td><td>RAM44</td><td>Row44</td></tr><tr><td>COM12</td><td>Row51</td><td>RAM51</td><td>Row59</td><td>RAM59</td><td>Row51</td><td>RAM59</td><td>Row35</td><td>RAM35</td><td>Row43</td><td>RAM43</td><td>Row35</td><td>RAM43</td><td>Row43</td></tr><tr><td>COM13</td><td>Row50</td><td>RAM50</td><td>Row58</td><td>RAM58</td><td>Row50</td><td>RAM58</td><td>Row34</td><td>RAM34</td><td>Row42</td><td>RAM42</td><td>Row34</td><td>RAM42</td><td>Row42</td></tr><tr><td>COM14</td><td>Row49</td><td>RAM49</td><td>Row57</td><td>RAM57</td><td>Row49</td><td>RAM57</td><td>Row33</td><td>RAM33</td><td>Row41</td><td>RAM41</td><td>Row33</td><td>RAM41</td><td>Row41</td></tr><tr><td>COM15</td><td>Row48</td><td>RAM48</td><td>Row56</td><td>RAM56</td><td>Row48</td><td>RAM56</td><td>Row32</td><td>RAM32</td><td>Row40</td><td>RAM40</td><td>Row32</td><td>RAM40</td><td>Row40</td></tr><tr><td>COM16</td><td>Row47</td><td>RAM47</td><td>Row55</td><td>RAM55</td><td>Row47</td><td>RAM55</td><td>Row31</td><td>RAM31</td><td>Row39</td><td>RAM39</td><td>Row31</td><td>RAM39</td><td>Row39</td></tr><tr><td>COM17</td><td>Row46</td><td>RAM46</td><td>Row54</td><td>RAM54</td><td>Row46</td><td>RAM54</td><td>Row30</td><td>RAM30</td><td>Row38</td><td>RAM38</td><td>Row30</td><td>RAM38</td><td>Row38</td></tr><tr><td>COM18</td><td>Row45</td><td>RAM45</td><td>Row53</td><td>RAM53</td><td>Row45</td><td>RAM53</td><td>Row29</td><td>RAM29</td><td>Row37</td><td>RAM37</td><td>Row29</td><td>RAM37</td><td>Row37</td></tr><tr><td>COM19</td><td>Row44</td><td>RAM44</td><td>Row52</td><td>RAM52</td><td>Row44</td><td>RAM52</td><td>Row28</td><td>RAM28</td><td>Row36</td><td>RAM36</td><td>Row28</td><td>RAM36</td><td>Row36</td></tr><tr><td>COM20</td><td>Row43</td><td>RAM43</td><td>Row51</td><td>RAM51</td><td>Row43</td><td>RAM51</td><td>Row27</td><td>RAM27</td><td>Row35</td><td>RAM35</td><td>Row27</td><td>RAM35</td><td>Row35</td></tr><tr><td>COM21</td><td>Row42</td><td>RAM42</td><td>Row50</td><td>RAM50</td><td>Row42</td><td>RAM50</td><td>Row26</td><td>RAM26</td><td>Row34</td><td>RAM34</td><td>Row26</td><td>RAM34</td><td>Row34</td></tr><tr><td>COM22</td><td>Row41</td><td>RAM41</td><td>Row49</td><td>RAM49</td><td>Row41</td><td>RAM49</td><td>Row25</td><td>RAM25</td><td>Row33</td><td>RAM33</td><td>Row25</td><td>RAM33</td><td>Row33</td></tr><tr><td>COM23</td><td>Row40</td><td>RAM40</td><td>Row48</td><td>RAM48</td><td>Row40</td><td>RAM48</td><td>Row24</td><td>RAM24</td><td>Row32</td><td>RAM32</td><td>Row24</td><td>RAM32</td><td>Row32</td></tr><tr><td>COM24</td><td>Row39</td><td>RAM39</td><td>Row47</td><td>RAM47</td><td>Row39</td><td>RAM47</td><td>Row23</td><td>RAM23</td><td>Row31</td><td>RAM31</td><td>Row23</td><td>RAM31</td><td>Row31</td></tr><tr><td>COM25</td><td>Row38</td><td>RAM38</td><td>Row46</td><td>RAM46</td><td>Row38</td><td>RAM46</td><td>Row22</td><td>RAM22</td><td>Row30</td><td>RAM30</td><td>Row22</td><td>RAM30</td><td>Row30</td></tr><tr><td>COM26</td><td>Row37</td><td>RAM37</td><td>Row45</td><td>RAM45</td><td>Row37</td><td>RAM45</td><td>Row21</td><td>RAM21</td><td>Row29</td><td>RAM29</td><td>Row21</td><td>RAM29</td><td>Row29</td></tr><tr><td>COM27</td><td>Row36</td><td>RAM36</td><td>Row44</td><td>RAM44</td><td>Row36</td><td>RAM44</td><td>Row20</td><td>RAM20</td><td>Row28</td><td>RAM28</td><td>Row20</td><td>RAM28</td><td>Row28</td></tr><tr><td>COM28</td><td>Row35</td><td>RAM35</td><td>Row43</td><td>RAM43</td><td>Row35</td><td>RAM43</td><td>Row19</td><td>RAM19</td><td>Row27</td><td>RAM27</td><td>Row19</td><td>RAM27</td><td>Row27</td></tr><tr><td>COM29</td><td>Row34</td><td>RAM34</td><td>Row42</td><td>RAM42</td><td>Row34</td><td>RAM42</td><td>Row18</td><td>RAM18</td><td>Row26</td><td>RAM26</td><td>Row18</td><td>RAM26</td><td>Row26</td></tr><tr><td>COM30</td><td>Row33</td><td>RAM33</td><td>Row41</td><td>RAM41</td><td>Row33</td><td>RAM41</td><td>Row17</td><td>RAM17</td><td>Row25</td><td>RAM25</td><td>Row17</td><td>RAM25</td><td>Row25</td></tr><tr><td>COM31</td><td>Row32</td><td>RAM32</td><td>Row40</td><td>RAM40</td><td>Row32</td><td>RAM40</td><td>Row16</td><td>RAM16</td><td>Row24</td><td>RAM24</td><td>Row16</td><td>RAM24</td><td>Row24</td></tr><tr><td>COM32</td><td>Row31</td><td>RAM31</td><td>Row39</td><td>RAM39</td><td>Row31</td><td>RAM39</td><td>Row15</td><td>RAM15</td><td>Row23</td><td>RAM23</td><td>Row15</td><td>RAM23</td><td>Row23</td></tr><tr><td>COM33</td><td>Row30</td><td>RAM30</td><td>Row38</td><td>RAM38</td><td>Row30</td><td>RAM38</td><td>Row14</td><td>RAM14</td><td>Row22</td><td>RAM22</td><td>Row14</td><td>RAM22</td><td>Row22</td></tr><tr><td>COM34</td><td>Row29</td><td>RAM29</td><td>Row37</td><td>RAM37</td><td>Row29</td><td>RAM37</td><td>Row13</td><td>RAM13</td><td>Row21</td><td>RAM21</td><td>Row13</td><td>RAM21</td><td>Row21</td></tr><tr><td>COM35</td><td>Row28</td><td>RAM28</td><td>Row36</td><td>RAM36</td><td>Row28</td><td>RAM36</td><td>Row12</td><td>RAM12</td><td>Row20</td><td>RAM20</td><td>Row12</td><td>RAM20</td><td>Row20</td></tr><tr><td>COM36</td><td>Row27</td><td>RAM27</td><td>Row35</td><td>RAM35</td><td>Row27</td><td>RAM35</td><td>Row11</td><td>RAM11</td><td>Row19</td><td>RAM19</td><td>Row11</td><td>RAM19</td><td>Row19</td></tr><tr><td>COM37</td><td>Row26</td><td>RAM26</td><td>Row34</td><td>RAM34</td><td>Row26</td><td>RAM34</td><td>Row10</td><td>RAM10</td><td>Row18</td><td>RAM18</td><td>Row10</td><td>RAM18</td><td>Row18</td></tr><tr><td>COM38</td><td>Row25</td><td>RAM25</td><td>Row33</td><td>RAM33</td><td>Row25</td><td>RAM33</td><td>Row9</td><td>RAM9</td><td>Row17</td><td>RAM17</td><td>Row9</td><td>RAM17</td><td>Row17</td></tr><tr><td>COM39</td><td>Row24</td><td>RAM24</td><td>Row32</td><td>RAM32</td><td>Row24</td><td>RAM32</td><td>Row8</td><td>RAM8</td><td>Row16</td><td>RAM16</td><td>Row8</td><td>RAM16</td><td>Row16</td></tr><tr><td>COM40</td><td>Row23</td><td>RAM23</td><td>Row31</td><td>RAM31</td><td>Row23</td><td>RAM31</td><td>Row7</td><td>RAM7</td><td>Row15</td><td>RAM15</td><td>Row7</td><td>RAM15</td><td>Row15</td></tr><tr><td>COM41</td><td>Row22</td><td>RAM22</td><td>Row30</td><td>RAM30</td><td>Row22</td><td>RAM30</td><td>Row6</td><td>RAM6</td><td>Row14</td><td>RAM14</td><td>Row6</td><td>RAM14</td><td>Row14</td></tr><tr><td>COM42</td><td>Row21</td><td>RAM21</td><td>Row29</td><td>RAM29</td><td>Row21</td><td>RAM29</td><td>Row5</td><td>RAM5</td><td>Row13</td><td>RAM13</td><td>Row5</td><td>RAM13</td><td>Row13</td></tr><tr><td>COM43</td><td>Row20</td><td>RAM20</td><td>Row28</td><td>RAM28</td><td>Row20</td><td>RAM28</td><td>Row4</td><td>RAM4</td><td>Row12</td><td>RAM12</td><td>Row4</td><td>RAM12</td><td>Row12</td></tr><tr><td>COM44</td><td>Row19</td><td>RAM19</td><td>Row27</td><td>RAM27</td><td>Row19</td><td>RAM27</td><td>Row3</td><td>RAM3</td><td>Row11</td><td>RAM11</td><td>Row3</td><td>RAM11</td><td>Row11</td></tr><tr><td>COM45</td><td>Row18</td><td>RAM18</td><td>Row26</td><td>RAM26</td><td>Row18</td><td>RAM26</td><td>Row2</td><td>RAM2</td><td>Row10</td><td>RAM10</td><td>Row2</td><td>RAM10</td><td>Row10</td></tr><tr><td>COM46</td><td>Row17</td><td>RAM17</td><td>Row25</td><td>RAM25</td><td>Row17</td><td>RAM25</td><td>Row1</td><td>RAM1</td><td>Row9</td><td>RAM9</td><td>Row1</td><td>RAM9</td><td>Row9</td></tr><tr><td>COM47</td><td>Row16</td><td>RAM16</td><td>Row24</td><td>RAM24</td><td>Row16</td><td>RAM24</td><td>Row0</td><td>RAM0</td><td>Row8</td><td>RAM8</td><td>Row0</td><td>RAM8</td><td>Row8</td></tr><tr><td>COM48</td><td>Row15</td><td>RAM15</td><td>Row23</td><td>RAM23</td><td>Row15</td><td>RAM23</td><td>-</td><td>-</td><td>Row7</td><td>RAM7</td><td>-</td><td>-</td><td>Row7</td></tr><tr><td>COM49</td><td>Row14</td><td>RAM14</td><td>Row22</td><td>RAM22</td><td>Row14</td><td>RAM22</td><td>-</td><td>-</td><td>Row6</td><td>RAM6</td><td>-</td><td>-</td><td>Row6</td></tr><tr><td>COM50</td><td>Row13</td><td>RAM13</td><td>Row21</td><td>RAM21</td><td>Row13</td><td>RAM21</td><td>-</td><td>-</td><td>Row6</td><td>RAM6</td><td>-</td><td>-</td><td>Row6</td></tr><tr><td>COM51</td><td>Row12</td><td>RAM12</td><td>Row20</td><td>RAM20</td><td>Row12</td><td>RAM20</td><td>-</td><td>-</td><td>Row4</td><td>RAM4</td><td>-</td><td>-</td><td>Row4</td></tr><tr><td>COM52</td><td>Row11</td><td>RAM11</td><td>Row19</td><td>RAM19</td><td>Row11</td><td>RAM19</td><td>-</td><td>-</td><td>Row3</td><td>RAM3</td><td>-</td><td>-</td><td>Row3</td></tr><tr><td>COM53</td><td>Row10</td><td>RAM10</td><td>Row18</td><td>RAM18</td><td>Row10</td><td>RAM18</td><td>-</td><td>-</td><td>Row2</td><td>RAM2</td><td>-</td><td>-</td><td>Row2</td></tr><tr><td>COM54</td><td>Row9</td><td>RAM9</td><td>Row17</td><td>RAM17</td><td>Row9</td><td>RAM17</td><td>-</td><td>-</td><td>Row1</td><td>RAM1</td><td>-</td><td>-</td><td>Row1</td></tr><tr><td>COM55</td><td>Row8</td><td>RAM8</td><td>Row16</td><td>RAM16</td><td>Row8</td><td>RAM16</td><td>-</td><td>-</td><td>Row0</td><td>RAM0</td><td>-</td><td>-</td><td>Row0</td></tr><tr><td>COM56</td><td>Row7</td><td>RAM7</td><td>Row15</td><td>RAM15</td><td>Row7</td><td>RAM15</td><td>-</td><td>-</td><td>-</td><td>-</td><td>-</td><td>-</td><td>-</td></tr><tr><td>COM57</td><td>Row6</td><td>RAM6</td><td>Row14</td><td>RAM14</td><td>Row6</td><td>RAM14</td><td>-</td><td>-</td><td>-</td><td>-</td><td>-</td><td>-</td><td>-</td></tr><tr><td>COM58</td><td>Row5</td><td>RAM5</td><td>Row13</td><td>RAM13</td><td>Row5</td><td>RAM13</td><td>-</td><td>-</td><td>-</td><td>-</td><td>-</td><td>-</td><td>-</td></tr><tr><td>COM59</td><td>Row4</td><td>RAM4</td><td>Row12</td><td>RAM12</td><td>Row4</td><td>RAM12</td><td>-</td><td>-</td><td>-</td><td>-</td><td>-</td><td>-</td><td>-</td></tr><tr><td>COM60</td><td>Row3</td><td>RAM3</td><td>Row11</td><td>RAM11</td><td>Row3</td><td>RAM11</td><td>-</td><td>-</td><td>-</td><td>-</td><td>-</td><td>-</td><td>-</td></tr><tr><td>COM61</td><td>Row2</td><td>RAM2</td><td>Row10</td><td>RAM10</td><td>Row2</td><td>RAM10</td><td>-</td><td>-</td><td>-</td><td>-</td><td>-</td><td>-</td><td>-</td></tr><tr><td>COM62</td><td>Row1</td><td>RAM1</td><td>Row9</td><td>RAM9</td><td>Row1</td><td>RAM9</td><td>-</td><td>-</td><td>-</td><td>-</td><td>-</td><td>-</td><td>-</td></tr><tr><td>COM63</td><td>Row0</td><td>RAM0</td><td>Row8</td><td>RAM8</td><td>Row0</td><td>RAM8</td><td>-</td><td>-</td><td>-</td><td>-</td><td>-</td><td>-</td><td>-</td></tr></table>

![image](https://cdn-mineru.openxlab.org.cn/result/2026-09-08/61e8663c-ef74-4a31-bef6-08879770bc52/348c7625befdad46cc715f94b40a286bdb027fd2a82192bd7f3af451c159145d.jpg)


## 10.1.16 Set Display Clock Divide Ratio/ Oscillator Frequency (D5h)

This command consists of two functions: 

• Display Clock Divide Ratio (D)(A[3:0]) 

Set the divide ratio to generate DCLK (Display Clock) from CLK. The divide ratio is from 1 to 16, with reset value = 1. Please refer to section 8.3 for the details relationship of DCLK and CLK. 

• Oscillator Frequency (A[7:4]) 

Program the oscillator frequency Fosc that is the source of CLK if CLS pin is pulled high. The 4-bit value results in 16 different frequency settings available as shown below. The default setting is 1000b. 

## 10.1.17 Set Pre-charge Period (D9h)

This command is used to set the duration of the pre-charge period. The interval is counted in number of DCLK, where RESET equals 2 DCLKs. 

## 10.1.18 Set COM Pins Hardware Configuration (DAh)

This command sets the COM signals pin configuration to match the OLED panel hardware layout. The table below shows the COM pin configuration under different conditions (for MUX ratio =64): 


Table 10-3 : COM Pins Hardware Configuration


<table><tr><td>Conditions</td><td>COM pins Configurations</td></tr><tr><td>1 Sequential COM pin configuration (DAh A[4] =0)COM output Scan direction: from COM0 to COM63 (C0h)Disable COM Left/Right remap (DAh A[5] =0)</td><td></td></tr><tr><td>2 Sequential COM pin configuration (DAh A[4] =0)COM output Scan direction: from COM0 to COM63 (C0h)Enable COM Left/Right remap (DAh A[5] =1)Conditions</td><td>CO</td></tr><tr><td>3 Sequential COM pin configuration (DAh A[4] =0)COM output Scan direction: from COM63 to COM0 (C8h)Disable COM Left/Right remap (DAh A[5] =0)</td><td><img src="https://cdn-mineru.openxlab.org.cn/result/2026-09-08/61e8663c-ef74-4a31-bef6-08879770bc52/3c8363242f0cf539f291875f79a27c6ea15b7c434d48861671bbc562a6493761.jpg"/></td></tr><tr><td>4 Sequential COM pin configuration (DAh A[4] =0)COM output Scan direction: from COM63 to COM0 (C8h)Enable COM Left/Right remap (DAh A[5] =1)</td><td><img src="https://cdn-mineru.openxlab.org.cn/result/2026-09-08/61e8663c-ef74-4a31-bef6-08879770bc52/28dd9996ca6a79f8bcdc3c46748ae579352e1c9a8347938d4f0db5fb3fc6d68f.jpg"/></td></tr><tr><td>5 Alternative COM pin configuration (DAh A[4] =1)COM output Scan direction: from COM0 to COM63 (C0h)Disable COM Left/Right remap (DAh A[5] =0)Conditions</td><td><img src="https://cdn-mineru.openxlab.org.cn/result/2026-09-08/61e8663c-ef74-4a31-bef6-08879770bc52/b0710949ee754a9e713db7fa04240c765aae84f057a44a6bded77fdec4544513.jpg"/>COM pins Configurations</td></tr><tr><td>6 Alternative COM pin configuration (DAh A[4] =1)COM output Scan direction: from COM0 to COM63 (C0h)Enable COM Left/Right remap (DAh A[5] =1)</td><td><img src="https://cdn-mineru.openxlab.org.cn/result/2026-09-08/61e8663c-ef74-4a31-bef6-08879770bc52/af9dab991cd17209e68071b54bafeb174eaf904568fff64500307295ceae2015.jpg"/></td></tr><tr><td>7 Alternative COM pin configuration (DAh A[4] =1)COM output Scan direction: from COM63 to COM0(C8h)Disable COM Left/Right remap (DAh A[5] =0)</td><td><img src="https://cdn-mineru.openxlab.org.cn/result/2026-09-08/61e8663c-ef74-4a31-bef6-08879770bc52/538d939fa4fe6a7a52eeb24908a9ead056e317dcc4b09b2ad31d5705e7d70ecb.jpg"/></td></tr><tr><td>8 Alternative COM pin configuration (DAh A[4] =1)COM output Scan direction: from COM63 to COM0(C8h)Enable COM Left/Right remap (DAh A[5] =1)</td><td><img src="https://cdn-mineru.openxlab.org.cn/result/2026-09-08/61e8663c-ef74-4a31-bef6-08879770bc52/fd5367b206ca7be18c26a0d9af39a7a26ec892b7392aff746919783fa5ed687d.jpg"/></td></tr></table>

## 10.1.19 Set V<sub>COMH</sub> Deselect Level (DBh)

This command adjusts the $\mathrm { V _ { C O M H } }$ regulator output. 

## 10.1.20 NOP (E3h)

No Operation Command 

## 10.1.21 Status register Read

This command is issued by setting D/C# ON LOW during a data read (See Figure 13-1 to Figure 13-2 for parallel interface waveform). It allows the MCU to monitor the internal status of the chip. No status read is provided for serial mode. 

## 10.2 Graphic Acceleration Command

## 10.2.1 Horizontal Scroll Setup (26h/27h)

This command consists of consecutive bytes to set up the horizontal scroll parameters and determines the scrolling start page, end page and scrolling speed. 

Before issuing this command the horizontal scroll must be deactivated (2Eh). Otherwise, RAM content may be corrupted. 

The SSD1306 horizontal scroll is designed for 128 columns scrolling. The following two figures (Figure 10-7, Figure 10-8, Figure 10-9) show the examples of using the horizontal scroll: 


Figure 10-7 : Horizontal scroll example: Scroll RIGHT by 1 column


<table><tr><td>step\After one scroll</td><td>Original Setting</td></tr><tr><td>SEG127</td><td>SEG0</td></tr><tr><td>SEG0</td><td>SEG1</td></tr><tr><td>SEG1</td><td>SEG2</td></tr><tr><td>SEG2</td><td>SEG3</td></tr><tr><td>SEG3</td><td>SEG4</td></tr><tr><td>SEG4</td><td>SEG5</td></tr><tr><td>...</td><td>...</td></tr><tr><td>...</td><td>...</td></tr><tr><td>...</td><td>...</td></tr><tr><td>SEG121</td><td>SEG122</td></tr><tr><td>SEG122</td><td>SEG123</td></tr><tr><td>SEG123</td><td>SEG124</td></tr><tr><td>SEG124</td><td>SEG125</td></tr><tr><td>SEG125</td><td>SEG126</td></tr><tr><td>SEG126</td><td>SEG127</td></tr></table>


Figure 10-8 : Horizontal scroll example: Scroll LEFT by 1 column


<table><tr><td>After one scroll step</td><td>Original Setting</td></tr><tr><td>SEG1</td><td>SEG0</td></tr><tr><td>SEG2</td><td>SEG1</td></tr><tr><td>SEG3</td><td>SEG2</td></tr><tr><td>SEG4</td><td>SEG3</td></tr><tr><td>SEG5</td><td>SEG4</td></tr><tr><td>SEG6</td><td>SEG5</td></tr><tr><td>...</td><td>...</td></tr><tr><td>...</td><td>...</td></tr><tr><td>...</td><td>...</td></tr><tr><td>SEG123</td><td>SEG122</td></tr><tr><td>SEG124</td><td>SEG123</td></tr><tr><td>SEG125</td><td>SEG124</td></tr><tr><td>SEG126</td><td>SEG125</td></tr><tr><td>SEG127</td><td>SEG126</td></tr><tr><td>SEG0</td><td>SEG127</td></tr></table>


Figure 10-9 : Horizontal scrolling setup example


![image](https://cdn-mineru.openxlab.org.cn/result/2026-09-08/61e8663c-ef74-4a31-bef6-08879770bc52/aba8d05745202a27f694f581f444a4be5ade7f69efe5c17041a0b7a3827d8d91.jpg)


## 10.2.2 Continuous Vertical and Horizontal Scroll Setup (29h/2Ah)

This command consists of 6 consecutive bytes to set up the continuous vertical scroll parameters and determines the scrolling start page, end page, scrolling speed and vertical scrolling offset. 

The bytes B[2:0], C[2:0] and D[2:0] of command 29h/2Ah are for the setting of the continuous horizontal scrolling. The byte E[5:0] is for the setting of the continuous vertical scrolling offset. All these bytes together are for the setting of continuous diagonal (horizontal + vertical) scrolling. If the vertical scrolling offset byte E[5:0] is set to zero, then only horizontal scrolling is performed (like command 26/27h). 

Before issuing this command the scroll must be deactivated (2Eh). Otherwise, RAM content may be corrupted. The following figure (Figure 10-10 ) show the example of using the continuous vertical and horizontal scroll: 


Figure 10-10 : Continuous Vertical and Horizontal scrolling setup example


![image](https://cdn-mineru.openxlab.org.cn/result/2026-09-08/61e8663c-ef74-4a31-bef6-08879770bc52/e4f3177309688f0324f8213e9e76419d660aac9b0f9ec3150a844c79c1d9938e.jpg)


## 10.2.3 Deactivate Scroll (2Eh)

This command stops the motion of scrolling. After sending 2Eh command to deactivate the scrolling action, the ram data needs to be rewritten. 

## 10.2.4 Activate Scroll (2Fh)

This command starts the motion of scrolling and should only be issued after the scroll setup parameters have been defined by the scrolling setup commands :26h/27h/29h/2Ah . The setting in the last scrolling setup command overwrites the setting in the previous scrolling setup commands. 

The following actions are prohibited after the scrolling is activated 

RAM access (Data write or read) 

2. Changing the horizontal scroll setup parameters 

## 10.2.5 Set Vertical Scroll Area(A3h)

This command consists of 3 consecutive bytes to set up the vertical scroll area. For the continuous vertical scroll function (command 29/2Ah), the number of rows that in vertical scrolling can be set smaller or equal to the MUX ratio. 

## 11 MAXIMUM RATINGS


Table 11-1 : Maximum Ratings (Voltage Referenced to VSS)


<table><tr><td>Symbol</td><td>Parameter</td><td>Value</td><td>Unit</td></tr><tr><td><eq>V_{DD}</eq></td><td rowspan="2">Supply Voltage</td><td>-0.3 to +4</td><td>V</td></tr><tr><td><eq>V_{CC}</eq></td><td>0 to 16</td><td>V</td></tr><tr><td><eq>V_{SEG}</eq></td><td>SEG output voltage</td><td>0 to <eq>V_{CC}</eq></td><td>V</td></tr><tr><td><eq>V_{COM}</eq></td><td>COM output voltage</td><td>0 to 0.9*<eq>V_{CC}</eq></td><td>V</td></tr><tr><td><eq>V_{in}</eq></td><td>Input voltage</td><td><eq>V_{SS}-0.3</eq> to <eq>V_{DD}+0.3</eq></td><td>V</td></tr><tr><td><eq>T_A</eq></td><td>Operating Temperature</td><td>-40 to +85</td><td>°C</td></tr><tr><td><eq>T_{stg}</eq></td><td>Storage Temperature Range</td><td>-65 to +150</td><td>°C</td></tr></table>

Maximum ratings are those values beyond which damages to the device may occur. Functional operation should be restricted to th limits in the Electrical Characteristics tables or Pin Description section 

This device may be light sensitive. Caution should be taken to avoid exposure of this device to any light source during normal operation. This device is not radiation protected. 

## 12 DC CHARACTERISTICS

Condition (Unless otherwise specified): 

Voltage referenced to V<sub>SS</sub> 

V<sub>DD</sub> = 1.65 to 3.3V 

$$
\mathrm{T} _ {\mathrm{A}} = 2 5 ^ {\circ} \mathrm{C}
$$


Table 12-1 : DC Characteristics


<table><tr><td>Symbol</td><td>Parameter</td><td>Test Condition</td><td>Min</td><td>Typ</td><td>Max</td><td>Unit</td></tr><tr><td><eq>V_{CC}</eq></td><td>Operating Voltage</td><td>-</td><td>7</td><td>-</td><td>15</td><td>V</td></tr><tr><td><eq>V_{DD}</eq></td><td>Logic Supply Voltage</td><td>-</td><td>1.65</td><td>-</td><td>3.3</td><td>V</td></tr><tr><td><eq>V_{OH}</eq></td><td>High Logic Output Level</td><td><eq>I_{OUT} = 100uA, 3.3MHz</eq></td><td>0.9 x <eq>V_{DD}</eq></td><td>-</td><td>-</td><td>V</td></tr><tr><td><eq>V_{OL}</eq></td><td>Low Logic Output Level</td><td><eq>I_{OUT} = 100uA, 3.3MHz</eq></td><td>-</td><td>-</td><td>0.1 x <eq>V_{DD}</eq></td><td>V</td></tr><tr><td><eq>V_{IH}</eq></td><td>High Logic Input Level</td><td>-</td><td>0.8 x <eq>V_{DD}</eq></td><td>-</td><td>-</td><td>V</td></tr><tr><td><eq>V_{IL}</eq></td><td>Low Logic Input Level</td><td>-</td><td>-</td><td>-</td><td>0.2 x <eq>V_{DD}</eq></td><td>V</td></tr><tr><td><eq>I_{CC,SLEEP}</eq></td><td><eq>I_{CC,Sleep mode Current}</eq></td><td><eq>V_{DD} = 1.65V \sim 3.3V, V_{CC} = 7V \sim 15V</eq> Display OFF, No panel attached</td><td>-</td><td>-</td><td>10</td><td>uA</td></tr><tr><td><eq>I_{DD,SLEEP}</eq></td><td><eq>I_{DD,Sleep mode Current}</eq></td><td><eq>V_{DD} = 1.65V \sim 3.3V, V_{CC} = 7V \sim 15V</eq> Display OFF, No panel attached</td><td>-</td><td>-</td><td>10</td><td>uA</td></tr><tr><td><eq>I_{CC}</eq></td><td><eq>V_{CC Supply Current}</eq><eq>V_{DD} = 2.8V, V_{CC} = 12V,</eq><eq>I_{REF} = 12.5uA</eq>No loading, Display ON, All ON</td><td rowspan="2">Contrast = FFh</td><td>-</td><td>430</td><td>780</td><td>uA</td></tr><tr><td><eq>I_{DD}</eq></td><td><eq>V_{DD Supply Current}</eq><eq>V_{DD} = 2.8V, V_{CC} = 12V,</eq><eq>I_{REF} = 12.5uA</eq>No loading, Display ON, All ON</td><td>-</td><td>50</td><td>150</td><td>uA</td></tr><tr><td rowspan="3"><eq>I_{SEG}</eq></td><td rowspan="3">Segment Output Current<eq>V_{DD}=2.8V, V_{CC}=12V,</eq><eq>I_{REF}=12.5uA, Display ON.</eq></td><td>Contrast=FFh</td><td>-</td><td>100</td><td>-</td><td rowspan="3">uA</td></tr><tr><td>Contrast=AFh</td><td>-</td><td>69</td><td>-</td></tr><tr><td>Contrast=3Fh</td><td>-</td><td>25</td><td>-</td></tr><tr><td>Dev</td><td>Segment output current uniformity</td><td><eq>Dev = (I_{SEG} - I_{MID})/I_{MID}</eq><eq>I_{MID} = (I_{MAX} + I_{MIN})/2</eq><eq>I_{SEG}[0:131] = Segment current at contrast = FFh</eq></td><td>-3</td><td>-</td><td>+3</td><td>%</td></tr><tr><td>Adj. Dev</td><td>Adjacent pin output current uniformity (contrast = FF)</td><td>Adj Dev = (I[n]-I[n+1]) / (I[n]+I[n+1])</td><td>-2</td><td>-</td><td>+2</td><td>%</td></tr></table>

## 13 AC CHARACTERISTICS

## Conditions:

Voltage referenced to $\mathrm { V _ { S S } }$ 

$\mathrm { V _ { D D } } { = } 1 . 6 5$ to3.3V 

$$
\mathrm{T} _ {\mathrm{A}} = 2 5 ^ {\circ} \mathrm{C}
$$


Table 13-1 : AC Characteristics


<table><tr><td>Symbol</td><td>Parameter</td><td>Test Condition</td><td>Min</td><td>Typ</td><td>Max</td><td>Unit</td></tr><tr><td><eq>F_{OSC}^{(1)}</eq></td><td>Oscillation Frequency of Display Timing Generator</td><td><eq>V_{DD}=2.8V</eq></td><td>333</td><td>370</td><td>407</td><td>kHz</td></tr><tr><td><eq>F_{FRM}</eq></td><td>Frame Frequency for 64 MUX Mode</td><td>128x64 Graphic Display Mode, Display ON, Internal Oscillator Enabled</td><td>-</td><td><eq>F_{OSC} \times 1/(DxKx64)^{(2)}</eq></td><td>-</td><td>Hz</td></tr><tr><td>RES#</td><td>Reset low pulse width</td><td></td><td>3</td><td>-</td><td>-</td><td>us</td></tr></table>

## Note

<sup>(1)</sup> FOSC stands for the frequency value of the internal oscillator and the value is measured when command D5h $\mathrm { A } [ 7 { : } 4 ]$ is in default value. 

<sup>(2)</sup> D: divide ratio (default value = 1) 

K: number of display clocks (default value = 54) 

Please refer to Table 9-1 (Set Display Clock Divide Ratio/Oscillator Frequency, D5h) for detailed description 


Table 13-2 : 6800-Series MCU Parallel Interface Timing Characteristics



$( \mathrm { V _ { D D } - V _ { S S } = 1 }$ .65V to 3.3V, T<sub>A</sub> = 25°C)


<table><tr><td>Symbol</td><td>Parameter</td><td>Min</td><td>Typ</td><td>Max</td><td>Unit</td></tr><tr><td><eq>t_{cycle}</eq></td><td>Clock Cycle Time</td><td>300</td><td>-</td><td>-</td><td>ns</td></tr><tr><td><eq>t_{AS}</eq></td><td>Address Setup Time</td><td>0</td><td>-</td><td>-</td><td>ns</td></tr><tr><td><eq>t_{AH}</eq></td><td>Address Hold Time</td><td>0</td><td>-</td><td>-</td><td>ns</td></tr><tr><td><eq>t_{DSW}</eq></td><td>Write Data Setup Time</td><td>40</td><td>-</td><td>-</td><td>ns</td></tr><tr><td><eq>t_{DHW}</eq></td><td>Write Data Hold Time</td><td>7</td><td>-</td><td>-</td><td>ns</td></tr><tr><td><eq>t_{DHR}</eq></td><td>Read Data Hold Time</td><td>20</td><td>-</td><td>-</td><td>ns</td></tr><tr><td><eq>t_{OH}</eq></td><td>Output Disable Time</td><td>-</td><td>-</td><td>70</td><td>ns</td></tr><tr><td><eq>t_{ACC}</eq></td><td>Access Time</td><td>-</td><td>-</td><td>140</td><td>ns</td></tr><tr><td rowspan="2"><eq>PW_{CSL}</eq></td><td>Chip Select Low Pulse Width (read)</td><td>120</td><td rowspan="2">-</td><td rowspan="2">-</td><td rowspan="2">ns</td></tr><tr><td>Chip Select Low Pulse Width (write)</td><td>60</td></tr><tr><td rowspan="2"><eq>PW_{CSH}</eq></td><td>Chip Select High Pulse Width (read)</td><td>60</td><td rowspan="2">-</td><td rowspan="2">-</td><td rowspan="2">ns</td></tr><tr><td>Chip Select High Pulse Width (write)</td><td>60</td></tr><tr><td><eq>t_R</eq></td><td>Rise Time</td><td>-</td><td>-</td><td>40</td><td>ns</td></tr><tr><td><eq>t_F</eq></td><td>Fall Time</td><td>-</td><td>-</td><td>40</td><td>ns</td></tr></table>


Figure 13-1 : 6800-series MCU parallel interface characteristics


![image](https://cdn-mineru.openxlab.org.cn/result/2026-09-08/61e8663c-ef74-4a31-bef6-08879770bc52/7f07a2b6dfdaf454249ef301700ac6e8123f96ec95a28bd769d70dfbab3e97dd.jpg)



(V<sub>DD</sub> - V<sub>SS</sub> = 1.65V to 3.3V, T<sub>A</sub> = 25°C)



Table 13-3 : 8080-Series MCU Parallel Interface Timing Characteristics


<table><tr><td>Symbol</td><td>Parameter</td><td>Min</td><td>Typ</td><td>Max</td><td>Unit</td></tr><tr><td><eq>t_{cycle}</eq></td><td>Clock Cycle Time</td><td>300</td><td>-</td><td>-</td><td>ns</td></tr><tr><td><eq>t_{AS}</eq></td><td>Address Setup Time</td><td>10</td><td>-</td><td>-</td><td>ns</td></tr><tr><td><eq>t_{AH}</eq></td><td>Address Hold Time</td><td>0</td><td>-</td><td>-</td><td>ns</td></tr><tr><td><eq>t_{DSW}</eq></td><td>Write Data Setup Time</td><td>40</td><td>-</td><td>-</td><td>ns</td></tr><tr><td><eq>t_{DHW}</eq></td><td>Write Data Hold Time</td><td>7</td><td>-</td><td>-</td><td>ns</td></tr><tr><td><eq>t_{DHR}</eq></td><td>Read Data Hold Time</td><td>20</td><td>-</td><td>-</td><td>ns</td></tr><tr><td><eq>t_{OH}</eq></td><td>Output Disable Time</td><td>-</td><td>-</td><td>70</td><td>ns</td></tr><tr><td><eq>t_{ACC}</eq></td><td>Access Time</td><td>-</td><td>-</td><td>140</td><td>ns</td></tr><tr><td><eq>t_{PWLR}</eq></td><td>Read Low Time</td><td>120</td><td>-</td><td>-</td><td>ns</td></tr><tr><td><eq>t_{PWLW}</eq></td><td>Write Low Time</td><td>60</td><td>-</td><td>-</td><td>ns</td></tr><tr><td><eq>t_{PWHR}</eq></td><td>Read High Time</td><td>60</td><td>-</td><td>-</td><td>ns</td></tr><tr><td><eq>t_{PWHW}</eq></td><td>Write High Time</td><td>60</td><td>-</td><td>-</td><td>ns</td></tr><tr><td><eq>t_R</eq></td><td>Rise Time</td><td>-</td><td>-</td><td>40</td><td>ns</td></tr><tr><td><eq>t_F</eq></td><td>Fall Time</td><td>-</td><td>-</td><td>40</td><td>ns</td></tr><tr><td><eq>t_{CS}</eq></td><td>Chip select setup time</td><td>0</td><td>-</td><td>-</td><td>ns</td></tr><tr><td><eq>t_{CSH}</eq></td><td>Chip select hold time to read signal</td><td>0</td><td>-</td><td>-</td><td>ns</td></tr><tr><td><eq>t_{CSF}</eq></td><td>Chip select hold time</td><td>20</td><td>-</td><td>-</td><td>ns</td></tr></table>


Figure 13-2 : 8080-series parallel interface characteristics


![image](https://cdn-mineru.openxlab.org.cn/result/2026-09-08/61e8663c-ef74-4a31-bef6-08879770bc52/6aacd0947f40ff92b02339ab2a54faed1916b345be38b86be6e38779eef10983.jpg)


![image](https://cdn-mineru.openxlab.org.cn/result/2026-09-08/61e8663c-ef74-4a31-bef6-08879770bc52/847b6b7bc1ce45d507092a6e5890978e989ec9719d4a029e0b7928ada8795f63.jpg)



Table 13-4 : 4-wire Serial Interface Timing Characteristics



(V<sub>DD</sub> - V<sub>SS</sub> = 1.65V to 3.3V, T<sub>A</sub> = 25°C)


<table><tr><td>Symbol</td><td>Parameter</td><td>Min</td><td>Typ</td><td>Max</td><td>Unit</td></tr><tr><td><eq>t_{cycle}</eq></td><td>Clock Cycle Time</td><td>100</td><td>-</td><td>-</td><td>ns</td></tr><tr><td><eq>t_{AS}</eq></td><td>Address Setup Time</td><td>15</td><td>-</td><td>-</td><td>ns</td></tr><tr><td><eq>t_{AH}</eq></td><td>Address Hold Time</td><td>15</td><td>-</td><td>-</td><td>ns</td></tr><tr><td><eq>t_{CSS}</eq></td><td>Chip Select Setup Time</td><td>20</td><td>-</td><td>-</td><td>ns</td></tr><tr><td><eq>t_{CSH}</eq></td><td>Chip Select Hold Time</td><td>10</td><td>-</td><td>-</td><td>ns</td></tr><tr><td><eq>t_{DSW}</eq></td><td>Write Data Setup Time</td><td>15</td><td>-</td><td>-</td><td>ns</td></tr><tr><td><eq>t_{DHW}</eq></td><td>Write Data Hold Time</td><td>15</td><td>-</td><td>-</td><td>ns</td></tr><tr><td><eq>t_{CLKL}</eq></td><td>Clock Low Time</td><td>20</td><td>-</td><td>-</td><td>ns</td></tr><tr><td><eq>t_{CLKH}</eq></td><td>Clock High Time</td><td>20</td><td>-</td><td>-</td><td>ns</td></tr><tr><td><eq>t_R</eq></td><td>Rise Time</td><td>-</td><td>-</td><td>40</td><td>ns</td></tr><tr><td><eq>t_F</eq></td><td>Fall Time</td><td>-</td><td>-</td><td>40</td><td>ns</td></tr></table>


Figure 13-3 : 4-wire Serial interface characteristics


![image](https://cdn-mineru.openxlab.org.cn/result/2026-09-08/61e8663c-ef74-4a31-bef6-08879770bc52/eb4df96b2231f9c2f23a31db0fdfd1440a969fd6d99fa8d0aaefb005ad02e54b.jpg)


![image](https://cdn-mineru.openxlab.org.cn/result/2026-09-08/61e8663c-ef74-4a31-bef6-08879770bc52/052b4c3bda68da5a20d2d04bd7eb97ff82fb78d41a781b64408985b722775824.jpg)



Table 13-5 : 3-wire Serial Interface Timing Characteristics



(V<sub>DD</sub> - V<sub>SS</sub> = 1.65V to 3.3V, $\mathrm { T _ { A } } = 2 5 ^ { \circ } \mathrm { C } )$


<table><tr><td>Symbol</td><td>Parameter</td><td>Min</td><td>Typ</td><td>Max</td><td>Unit</td></tr><tr><td><eq>t_{cycle}</eq></td><td>Clock Cycle Time</td><td>100</td><td>-</td><td>-</td><td>ns</td></tr><tr><td><eq>t_{CSS}</eq></td><td>Chip Select Setup Time</td><td>20</td><td>-</td><td>-</td><td>ns</td></tr><tr><td><eq>t_{CSH}</eq></td><td>Chip Select Hold Time</td><td>10</td><td>-</td><td>-</td><td>ns</td></tr><tr><td><eq>t_{DSW}</eq></td><td>Write Data Setup Time</td><td>15</td><td>-</td><td>-</td><td>ns</td></tr><tr><td><eq>t_{DHW}</eq></td><td>Write Data Hold Time</td><td>15</td><td>-</td><td>-</td><td>ns</td></tr><tr><td><eq>t_{CLKL}</eq></td><td>Clock Low Time</td><td>20</td><td>-</td><td>-</td><td>ns</td></tr><tr><td><eq>t_{CLKH}</eq></td><td>Clock High Time</td><td>20</td><td>-</td><td>-</td><td>ns</td></tr><tr><td><eq>t_R</eq></td><td>Rise Time</td><td>-</td><td>-</td><td>40</td><td>ns</td></tr><tr><td><eq>t_F</eq></td><td>Fall Time</td><td>-</td><td>-</td><td>40</td><td>ns</td></tr></table>


Figure 13-4 : 3-wire Serial interface characteristics


![image](https://cdn-mineru.openxlab.org.cn/result/2026-09-08/61e8663c-ef74-4a31-bef6-08879770bc52/271d469c1a47b53de12afa1a619f5ae59f4534eb6dcb38064a474d9d6876ddd7.jpg)


## Conditions:

$$
\mathrm{V} _ {\mathrm{DD}} - \mathrm{V} _ {\mathrm{SS}} = \mathrm{V} _ {\mathrm{DD}} - \mathrm{V} _ {\mathrm{SS}} = 1. 6 5 \mathrm{V} \text {   to   } 3. 3 \mathrm{V}
$$

$$
\mathrm {T_ {A}} = 2 5 ^ {\circ} \mathrm{C}
$$


Table 13-6 $\mathbf { \Omega } ^ { \bullet } \mathbf { I } ^ { 2 } \mathbf { C }$ Interface Timing Characteristics


<table><tr><td>Symbol</td><td>Parameter</td><td>Min</td><td>Typ</td><td>Max</td><td>Unit</td></tr><tr><td><eq>t_{cycle}</eq></td><td>Clock Cycle Time</td><td>2.5</td><td>-</td><td>-</td><td>us</td></tr><tr><td><eq>t_{HSTART}</eq></td><td>Start condition Hold Time</td><td>0.6</td><td>-</td><td>-</td><td>us</td></tr><tr><td rowspan="2"><eq>t_{HD}</eq></td><td>Data Hold Time (for “SDA<eq>_{OUT}</eq>” pin)</td><td>0</td><td>-</td><td>-</td><td>ns</td></tr><tr><td>Data Hold Time (for “SDA<eq>_{IN}</eq>” pin)</td><td>300</td><td>-</td><td>-</td><td>ns</td></tr><tr><td><eq>t_{SD}</eq></td><td>Data Setup Time</td><td>100</td><td>-</td><td>-</td><td>ns</td></tr><tr><td><eq>t_{SSTART}</eq></td><td>Start condition Setup Time (Only relevant for a repeated Start condition)</td><td>0.6</td><td>-</td><td>-</td><td>us</td></tr><tr><td><eq>t_{SSTOP}</eq></td><td>Stop condition Setup Time</td><td>0.6</td><td>-</td><td>-</td><td>us</td></tr><tr><td><eq>t_R</eq></td><td>Rise Time for data and clock pin</td><td>-</td><td>-</td><td>300</td><td>ns</td></tr><tr><td><eq>t_F</eq></td><td>Fall Time for data and clock pin</td><td>-</td><td>-</td><td>300</td><td>ns</td></tr><tr><td><eq>t_{IDLE}</eq></td><td>Idle Time before a new transmission can start</td><td>1.3</td><td>-</td><td>-</td><td>us</td></tr></table>


Figure 13-5 : $\mathbf { I } ^ { 2 } \mathbf { C }$ interface Timing characteristics


![image](https://cdn-mineru.openxlab.org.cn/result/2026-09-08/61e8663c-ef74-4a31-bef6-08879770bc52/2a36d1761b2e7f046e4156c11ef7868debe358675e92b0ba3b4a9b129a47adef.jpg)



Figure 14-1 : Application Example of SSD1306Z


The configuration for 8080-parallel interface mode is shown in the following diagram: $(V_{DD}=2.8V, V_{CC}=12V, I_{REF}=12.5uA)$ DISPLAY PANEL
128 x 64

SSD1306Z

Pin connected to MCU interface: D[7:0], E, R/W#, D/C#, CS#, RES#
Pin internally connected to $V_{SS}$ : BS0, CL
Pin internally connected to $V_{DD}$ : CLS
C2P, C2N, C1P, C1N, $V_{BREF}$ , FB should be left open.

C1: 1.0uF (1)
C2: 2.2uF (1)
C3: 2.2uF (1)

Voltage at $I_{REF} = V_{CC} - 2.5V$ . For $V_{CC} = 12V$ , $I_{REF} = 12.5uA$ :
R1 = (Voltage at $I_{REF} - V_{SS}$ ) / $I_{REF}$ = (12-2.5) / 12.5u
=760KΩ

Note
(1) The capacitor value is recommended value. Select appropriate value against module application. 

## 15 PACKAGE INFORMATION

## 15.1 SSD1306TR1 Detail Dimension

## Figure 15-1 SSD1306TR1 Detail Dimension

![image](https://cdn-mineru.openxlab.org.cn/result/2026-09-08/61e8663c-ef74-4a31-bef6-08879770bc52/fe632f8d258b246cb98a0fd69062937899867f9ef6204dc0ae9885ce14e91609.jpg)


Specification: 1. GENERAL TOLERANCE:±0.05 mm 2.MATERIAL PI: 75 ± 8 um CU: $1 5 \pm 3$ um ADHESIVE: 12± 3um SR: 26 ± 14 um TOLERANCE± 0.200 mm FLEX COATING: Min10 um 3.Plating : Sn 0.20 ±0.05 um 4. TAPESITE: 4 SPH,19 mm 

![image](https://cdn-mineru.openxlab.org.cn/result/2026-09-08/61e8663c-ef74-4a31-bef6-08879770bc52/ddf21ac866299a2004df0fda380bf919b00a94f0c1d18edac53946efa9134559.jpg)


## 15.2 SSD1306Z Die Tray Information


Figure 15-2 : SSD1306Z die tray information


![image](https://cdn-mineru.openxlab.org.cn/result/2026-09-08/61e8663c-ef74-4a31-bef6-08879770bc52/32fc0fc0e254895d6a958dda90529940d581bdfcde06fc77fdc38f4592ccf793.jpg)


<table><tr><td colspan="2">SPEC</td></tr><tr><td></td><td>MM</td></tr><tr><td>(L1)</td><td>76.00±0.10</td></tr><tr><td>(L2)</td><td>68.10±0.10</td></tr><tr><td>(L3)</td><td>68.20±0.10</td></tr><tr><td>(T)</td><td>4.20±0.05</td></tr><tr><td>(SX)</td><td>8.95</td></tr><tr><td>(SY)</td><td>6.10</td></tr><tr><td>(S)</td><td>10.83</td></tr><tr><td>(X)</td><td>6.91±0.05</td></tr><tr><td>(Y)</td><td>1.00±0.05</td></tr><tr><td>(Z)</td><td>0.41±0.05</td></tr><tr><td>(Px)</td><td>8.30±0.05</td></tr><tr><td>(Py)</td><td>2.20±0.05</td></tr><tr><td>(Nx)</td><td>8</td></tr><tr><td>(Ny)</td><td>30</td></tr><tr><td>(N)</td><td>240</td></tr><tr><td>(P1)</td><td>1.60</td></tr><tr><td>(P2)</td><td>1.40</td></tr><tr><td>(P3)</td><td>0.65</td></tr></table>

Solomon Systech reserves the right to make changes without notice to any products herein. Solomon Systech makes no warranty, representation or guarantee regarding the suitability of its products for any particular purpose, nor does Solomon Systech assume an liability arising out of the application or use of any product or circuit, and specifically disclaims any, and all, liability, including without limitation consequential or incidental damages. “Typical” parameters can and do vary in different applications. All operating parameters, including “Typical” must be validated for each customer application by the customer’s technical experts. Solomon Systech does not convey any license under its patent rights nor the rights of others. Solomon Systech products are not designed, intended, or authorized for use as components in systems intended for surgical implant into the body, or other applications intended to support or sustain life, or for any other application in which the failure of the Solomon Systech product could create a situation where personal injury or death may occur. Should Buyer purchase or use Solomon Systech products for any such unintended or unauthorized application, Buyer shall indemnify and hold Solomon Systech and its offices, employees, subsidiaries, affiliates, and distributors harmless against all claims, costs, damages, and expenses, and reasonable attorney fees arising out of, directly or indirectly, any claim of personal injury or death associated with such unintended or unauthorized use, even if such claim alleges that Solomon Systech was negligent regarding the design or manufacture of th part. 

![image](https://cdn-mineru.openxlab.org.cn/result/2026-09-08/61e8663c-ef74-4a31-bef6-08879770bc52/7fb094aa3475209515e5e597cc4f03671fa714d250a6b390924f3371b97f7ee6.jpg)


All Solomon Systech Products complied with six (6) hazardous substances limitation requirement per European Union (EU) “Restriction ofHazardous Substance (RoHS) Directive (2002/95/EC)” and China standard “电子信息产品污染控制标识要求 (SJ/T11364-2006)” withcontrol Marking Symbol . Hazardous Substances test report is available upon requested.

http://www.solomon-systech.com 

# SSD1306

Application Note 

128 x 64 Dot Matrix 

OLED/PLED Segment/Common Driver with Controller 

This document contains information on a new product. Specifications and information herein are subject to change without notice. 

## TABLE OF CONTENTS

1 INTRODUCTION 3
2 CHARGE PUMP REGULATOR 3
2.1 Command Table for Charge Bump Setting 3
3 SOFTWARE CONFIGURATION 5 

## TABLE OF FIGURES

Figure 1 : Application Example of SSD1306Z with charge bump....4
Figure 2 : Software Initialization Flow Chart....5 

## 1 Introduction

This application note of SSD1306 is written to explain the charge pump regulator function of SSD1306. SSD1306 is a single-chip CMOS OLED/PLED driver with controller for organic / polymer light emitting diode dot-matrix graphic display system. It consists of 128 segments and 64 commons. This IC is designed for Common Cathode type OLED panel. 

For the detailed characteristics of the driver IC, please refer to SSD1306 datasheet. 

## 2 Charge Pump Regulator

The internal regulator circuit in SSD1306 accompanying only 2 external capacitors can generate a 7.5V voltage supply, ${ \mathsf { V } } _ { \mathsf { C C } } ,$ from a low voltage supply input, $\mathsf { V } _ { \mathsf { B A T } } .$ The $\mathsf { V } _ { \mathsf { C C } }$ is the voltage supply to the OLED driver block. This is a switching capacitor regulator circuit, designed for handheld applications. This regulator can be turned on/off by software command setting. 

• Power supply 

o $\mathsf { V } _ { \mathsf { D D } } = 1 . 6 5 \mathsf { V } \mathsf { t o } 3 . 3 \mathsf { V } , < \mathsf { V } _ { \mathsf { B A T } }$ for IC logic o $\mathsf { V } _ { \mathsf { B A T } } = 3 . 3 \mathsf { V } \mathsf { t o } 4 . 2 \mathsf { V }$ for charge pump regulator circuit 

• Pins description for related pins of the charge pump regulator 

$\mathsf { V } _ { \mathsf { B A T } } - \mathsf { P o w e r }$ supply for charge pump regulator circuit. 

<table><tr><td>Status</td><td><eq>V_{BAT}</eq></td><td><eq>V_{DD}</eq></td><td><eq>V_{CC}</eq></td></tr><tr><td>Enable charge pump</td><td>Connect to external <eq>V_{BAT}</eq> source</td><td>Connect to external <eq>V_{DD}</eq> source</td><td>A capacitor should be connected between this pin and <eq>V_{SS}</eq></td></tr><tr><td>Disable charge pump</td><td>Connect with <eq>V_{DD}</eq> pin</td><td>Connect to external <eq>V_{DD}</eq> source</td><td>Connect to external <eq>V_{CC}</eq> source</td></tr></table>

o C1P/C1N – Pin for charge pump capacitor; Connect to each other with a capacitor 

o C2P/C2N – Pin for charge pump capacitor; Connect to each other with a capacitor 

## 2.1 Command Table for Charge Bump Setting

<table><tr><td colspan="12">1. Charge Pump Command Table</td></tr><tr><td>D/C#</td><td>Hex</td><td>D7</td><td>D6</td><td>D5</td><td>D4</td><td>D3</td><td>D2</td><td>D1</td><td>D0</td><td>Command</td><td>Description</td></tr><tr><td>0</td><td>8D</td><td>1</td><td>0</td><td>0</td><td>0</td><td>1</td><td>1</td><td>0</td><td>1</td><td>Charge</td><td>A[2] = 0b, Disable charge</td></tr><tr><td>0</td><td>A[7:0]</td><td>*</td><td>*</td><td>0</td><td>1</td><td>0</td><td><eq>A_2</eq></td><td>0</td><td>0</td><td>Pump Setting</td><td>pump(RESET)A[2] = 1b, Enable charge pump during display onNote(1) The Charge Pump must be enabled by the following command: 8Dh ; Charge Pump Setting14h ; Enable Charge Pump AFh; Display ON</td></tr></table>


Figure 1 : Application Example of SSD1306Z with charge bump


The configuration for 8080-parallel interface mode is shown in the following diagram: $(V_{DD}=1.65V\sim3.3V,<V_{BAT}, V_{BAT}=3.3V\sim4.2V, I_{REF}=12.5uA)$ DISPLAY PANEL
104 x 16

SSD1306Z

Pin connected to MCU interface: D[7:0], E, R/W#, D/C#, CS#, RES#
Pin internally connected to Vss: BS0, CL
Pin internally connected to VDD: CLS
VBREF, FR should be left open.

C1, C4, C6, C7: 1.0uF (1)
C2, C3: 2.2uF (1)

Voltage at IREF = VCC - 2.5V. For VCC = 7.5V, IREF = 12.5uA:
R1 = (Voltage at IREF - VSS) / IREF
= (7.5-2.5) / 12.5u
=400KΩ

Note
(1) The capacitor value is recommended value. Select appropriate value against module application. 

## 3 Software Configuration

SSD1306 has internal command registers that are used to configure the operations of the driver IC. After reset, the registers should be set with appropriate values in order to function well. The registers can be accessed by MPU interface in either 6800, 8080, SPI type with D/C# pin pull low or using I<sup>2</sup>C interface. Below is an example of initialization flow of SSD1306. The values of registers depend on different condition and application. 


Figure 2 : Software Initialization Flow Chart


![image](https://cdn-mineru.openxlab.org.cn/result/2026-09-08/61e8663c-ef74-4a31-bef6-08879770bc52/3d520834fcc89dd877e5f59f61785de841942eb642bd3f771a196ee7015a5603.jpg)


Solomon Systech reserves the right to make changes without notice to any products herein. Solomon Systech makes no warranty, representation or guarantee regarding the suitability of its products for any particular purpose, nor does Solomon Systech assume any liability arising out of the application or use of any product or circuit, and specifically disclaims any, and all, liability, including without limitation consequential or incidental damages. “Typical” parameters can and do vary in different applications. All operating parameters, including “Typical” must be validated for each customer application by the customer’s technical experts. Solomon Systech does not convey any license under its patent rights nor the rights of others. Solomon Systech products are not designed, intended, or authorized for use as components in systems intended for surgical implant into the body, or other applications intended to support or sustain life, or for any other application in which the failure of the Solomon Systech product could create a situation where personal injury or death may occur. Should Buyer purchase or use Solomon Systech products for any such unintended or unauthorized application, Buyer shall indemnify and hold Solomon Systech and its offices, employees, subsidiaries, affiliates, and distributors harmless against all claims, costs, damages, and expenses, and reasonable attorney fees arising out of, directly or indirectly, any claim of personal injury or death associated with such unintended or unauthorized use, even if such claim alleges that Solomon Systech was negligent regarding the design or manufacture of the part. 

All Solomon Systech Products complied with six (6) hazardous substances limitation requirement per European Union (EU)“Restriction of Hazardous Substance (RoHS) Directive (2002/95/EC)” and China standard “电子信息产品污染控制标识要求(SJ/T11364-2006)” with control Marking Symbol . Hazardous Substances test report is available upon requested.

http://www.solomon-systech.com 