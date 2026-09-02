NXP Semiconductors 

## Chapter 3 Memory Map 

## 3.1 Introduction 

This chip contains various memories and memory-mapped peripherals that are placed in a 32-bit contiguous memory space, and this chapter describes the memory and peripheral locations within that memory space. 

For high-level chip memory map details, see the memory map file attached to this document. 

## 3.2 SRAM memory map 

The memory map file attached to this document provides a complete architectural address space definition for various sections that the RAM is partitioned into and across the S32K3xx product series. Based on the physical sizes of the memories and peripherals, the actual address regions used may be smaller. For details see chapter 'Memory and Memory Interfaces'. 

## 3.3 Access-related details of the memory types used in this chip 

The Cortex-M7 core can access these memories sequentially: 

- ITCM 

- DTCM 

- I-cache 

- D-cache 

ITCM and DTCM can be accessed via 32-bit AHBS interface by any master, e.g., different Cortex-M7 cores, eDMA, etc to bootload instructions in ITCM. EMAC is another master that can access DTCM. See 'Block diagram' in the 'Introduction' chapter for details on the transaction path. 

Access to SRAM beyond the RAM available on the chip terminates the bus cycle with an error followed by an appropriate response in the requesting bus master. 

## 3.4 TCM as system memory 

On multi–core device, all enabled core and non–core masters can use TCMs of the disabled core. In order to allow use of ITCM and DTCM of the disabled core as system memories the following steps must be executed by enabled core: 

1. Write 1 to MC_ME's PRTN2_COFB1_CLKEN[REQ62] field for Cortex-M7_0, PRTN2_COFB1_CLKEN[REQ63] field for Cortex-M7_1, PRTN2_COFB2_CLKEN[REQ64] field for Cortex-M7_2, and PRTN2_COFB2_CLKEN[REQ65] field for Cortex-M7_3. This enables the Cortex-M7 core's TCM controller clock. 

2. . Write 1 to DCM_GPR's DCMRWF4[CM7_0_CPUWAIT] field for Cortex-M7_0, DCMRWF4[CM7_1_CPUWAIT] field for Cortex-M7_1, DCMRWF4[CM7_2_CPUWAIT] field for Cortex-M7_2, and DCMRWF4[CM7_3_CPUWAIT] field for Cortex-M7_3. This configures the core operation in Wait mode. 

3. Write 1 to MC_ME's PRTN0_CORE0_PCONF[CCE] field for Cortex-M7_0, PRTN0_CORE1_PCONF[CCE] field for Cortex-M7 _1, PRTN0_CORE4_PCONF[CCE] field for Cortex-M7_2, and PRTN0_CORE3_PCONF[CCE] field for Cortex-M7_3. This enables the Cortex-M7 core's clock. 

Table 6. TCM modes of operation 

Description Control bit (Internal signal) Cortex-M7 and TCM mode 

Table continues on the next page... 

S32K3xx Reference Manual, Rev. 12, 2025-11-11 

Reference Manual 

34 / 5394 

NXP Semiconductors 

Memory Map 

Table 6. TCM modes of operation (continued) 

||PRTN2_COFBi_CLKEN[RE<br>Q62+n]1|DCMRWF4[CM7_n_CP<br>UWAIT]|PRTN0_COREn_PCON<br>F[CCE]|CM7_n<br>mode|CM7_n_T<br>CM<br>backdoor<br>enabled|
|---|---|---|---|---|---|
|Application<br>configurations|—|0|1|RUN|Yes|
||0|1|1|WAIT|Yes|
||1|1|1|WAIT|Yes|
||—|—|0|Disabled|No|



1. where i represent 1 for Cortex-M7_0/1 and 2 for Cortex-M7_2/3 

## 3.5 Considerations related to TCM's implementation 

You must first initialize TCM (ITCM and DTCM) and system RAMs by 64-bit writes before performing read accesses. The system RAM can be initialized using eDMA and core. The ITCM initialization can be performed only by core using either direct or back-door accesses. ITCM initialization via back-door can be done by using STM (Store Multiple) with even number of registers. STRD (Store Dual) instruction would not work. 

The DTCM can be initialized also by 32-bit writes performed either using core's direct and back-door accesses using eDMA. These writes are required to set up the initial ECC code words after chip power-on reset. 

Each Cortex-M7 core is equipped with a 32 KB ITCM and 64 KB DTCM with a zero wait-state access. In the lockstep operation, the checker core's TCM is added to the primary core. 

See table 'Memory ECC initialization summary' in chapter 'Memory and Memory Interfaces' for details on memory ECC initialization. 

## 3.6 Flash memory map 

For details, see the memory map file attached to this document. 

## 3.7 AIPS-Lite memory map 

You can access the peripheral memory map via a crossbar slave port. The next table shows the three regions associated with peripheral space. 

Table 7. Regions associated with peripheral space 

|Address of region|Region description|
|---|---|
|4000_0000h–401F_FFFFh|This 2048 KB region (AIPS_Lite_0) is partitioned into 128 spaces, each 16 KB<br>in size, having 32 on-platform and 96 off-platform spaces. AIPS_Lite generates<br>unique module enables for all the 32 on-platform spaces.|
|4020_0000h–403F_FFFFh|This 2048 KB region (AIPS_Lite_1) is partitioned into 128 spaces, each 16 KB<br>in size, having 32 on-platform and 96 off-platform spaces. AIPS_Lite generates<br>unique module enables for all the 32 on-platform spaces.|
|4040_0000h–405F_FFFFh|This 2048 KB region (AIPS_Lite_2) is partitioned into 128 spaces, each 16 KB<br>in size, having 32 on-platform and 96 off-platform spaces. AIPS_Lite generates<br>unique module enables for all the 32 on-platform spaces.|



Modules that are disabled via their clock gate control fields in the MC_CGM registers disable the associated AIPS_Lite slots. Access to any address within an unimplemented or disabled peripheral bridge slot results in a transfer error termination. 

S32K3xx Reference Manual, Rev. 12, 2025-11-11 

Reference Manual 

35 / 5394 

NXP Semiconductors 

Memory Map 

Multiple instances of same peripherals are connected to different bridges on the interconnect. For details, see the memory map file attached to this document. 

## 3.8 Serialization of memory operations 

In particular cases, you must complete the process of writing to a peripheral before the subsequent action occurs. Examples of such situations include: 

- Exiting an interrupt service routine 

- Changing a mode 

- Configuring a function 

In these situations, you must perform a read-after-write sequence to achieve the required serialization of memory operations. The following table provides this sequence. 

Table 8. Read-after-write sequence for serialization of memory operations 

|Step|Action|
|---|---|
|1|Write to the associated peripheral register.|
|2|Read the register to verify the write process.|
|3|Continue with the subsequent operations.|



## 3.9 PPB memory map 

PPB is a part of the defined Arm bus architecture and provides access to specific processor-local modules. You can access these modules only through the core, and not through other system masters. 

Table 9. PPB memory map 

|Starting hex address|Ending hex address|Size (KB)|Module|
|---|---|---|---|
|E000_0000|E000_0FFF|4|ITM|
|E000_1000|E000_1FFF||DWT|
|E000_2000|E000_2FFF||FPB|
|E000_3000|E000_DFFF|44|—|
|E000_E000|E000_EFFF|4|SCS|
|E000_F000|E003_FFFF|196|Reserved|
|E004_0000|E004_0FFF|4|TPIU|
|E004_1000|E004_1FFF||ETM|
|E004_2000|E004_2FFF||CTI|
|E004_3000|E004_3FFF||—|
|E004_4000|E004_4FFF|||
|E004_5000|E004_5FFF|||
|E004_6000|E007_FFFF|232||
|E008_0000|E008_0FFF|4|MCM|
|E008_1000|E008_1FFF||—|



Table continues on the next page... 

S32K3xx Reference Manual, Rev. 12, 2025-11-11 

Reference Manual 

36 / 5394 

NXP Semiconductors 

Memory Map 

Table 9. PPB memory map (continued) 

|Starting hex address|Ending hex address|Size (KB)|Module|
|---|---|---|---|
|E008_2000|E008_2FFF|||
|E008_3000|E00F_EFFF|496||
|E00F_F000|E00F_FFFF|4|Cortex-M7 PPB ROM table|
|3.10 Glossary<br>CTI<br>Cross trigger interface<br>DTCM<br>Data tightly coupled memory<br>D-cache<br>Data cache<br>DWT<br>Debug watchpoint and trace<br>ETM<br>Embedded trace macrocell<br>FPB<br>Flash patch and breakpoints<br>ITCM<br>Instruction tightly coupled memory<br>I-cache<br>Instruction cache<br>ITM<br>Instrumentation trace macrocells<br>PPB<br>Private peripheral bus<br>SCS<br>System control space<br>SRAM<br>Static random access memory<br>TPIU<br>Trace port interface unit||||



S32K3xx Reference Manual, Rev. 12, 2025-11-11 

Reference Manual 

37 / 5394 

NXP Semiconductors 

## Chapter 4 Signal Multiplexing 

## 4.1 Introduction 

The signal multiplexing enables the sharing of single pad for multiple functions. 

The signal multiplexing unit comprises control signals from SIUL2 and pad interface logic. The signal multiplexing unit consists of several individual sub-units, each handling the signal multiplexing of one pad. 

The "SIUL2 Multiplexed Signal Configuration Register (MSCR)" controls the module specific pad settings (pull-up etc.) and the signal present on the external pin. See SIUL2_MSCR for the description of control signals. The pad attributes may vary depending on the pad type. 

For the pad attributes of each pad type and their reset values per port, see the IOMUX file attached to this document. The pads specific to the packages and their multiplexing is also documented in the IOMUX file attached to this document. 

## ~~NOTE~~ 

The input functions for the protocols which are not to be used should be appropriated configured as 'disabled low'/'disabled high' with appropriate SIUL2.IMCR configurations corresponding for that function. 

## 4.2 Pad description 

Following figure shows the basic representation of a GPIO pad. 

**==> picture [257 x 199] intentionally omitted <==**

**----- Start of picture text -----**<br>
OBE<br>DO<br>Pad<br>SRC Output<br>driver<br>DSE<br>PUE<br>PUS<br>Pull logic<br>IND Input Low-pass<br>receiver filter<br>lBE<br>IFE<br>**----- End of picture text -----**<br>


Figure 12. GPIO pad representation 

Table 10. Pad Signal description 

|Signal name|Direction|Description|
|---|---|---|
|Pad|I/O|I/O to external world|
|DO|I|Data coming from the core into the pad|
|OBE|I|Enable output driver|



Table continues on the next page... 

S32K3xx Reference Manual, Rev. 12, 2025-11-11 

Reference Manual 

38 / 5394 

NXP Semiconductors 

Signal Multiplexing 

Table 10. Pad Signal description (continued) 

|Signal name|Direction|Description|
|---|---|---|
|PUE|I|0: Disable internal pullup or pulldown resistor 1: Enable internal pullup or<br>pulldown resistor|
|PUS|I|0: Enable internal pulldown resistor if pue is set 1: Enable internal pullup<br>resistor if pue is set|
|IBE|I|Enable input receiver|
|IND|O|Data coming out of the pad into the core|
|SRC|I|Slew Rate Control|
|PKE|I|Pad keeping enable|
|IFE|I|Input filter enable|
|DSE|I|Drive Strength enable|



Table 11. Input buffer enable 

|IBE|Pad|IND|Description|
|---|---|---|---|
|0|X|0|Input buffer disabled, ind gets low|
|1|0/1|0/1|Input buffer enabled, ind = pad|



Table 12. Output buffer enable 

|OBE|DO|Pad|Description|
|---|---|---|---|
|0|X|Z|Output buffer disabled, pad hi-Z (If not configured as input)|
|1|0/1|0/1|Output buffer enable, pad = do|



Table 13. Input filter enable 

|IFE|Description|
|---|---|
|1|Input filter enabled|
|0|Input filter disabled|



Table 14. Pull up/Pull down 

|PUE|PUS|Pad|Description|
|---|---|---|---|
|0|X|-|Weak pull disabled. Pad retains previous state|
|1|0|0|Weak pull down enabled|
|1|1|1|Weak pull up enabled|



## Table 15. Slew rate control 

|SRC|Description|
|---|---|
|0|Slew rate enabled|
|1|Slew rate disabled|



S32K3xx Reference Manual, Rev. 12, 2025-11-11 

Reference Manual 

39 / 5394 

NXP Semiconductors 

Signal Multiplexing 

Table 16. Drive strength enable 

|DSE|Description|
|---|---|
|1|Drive strength supported|
|0|Drive strength not supported|



Table 17. Pad keeping enable 

|PKE|Description|
|---|---|
|0|Pad keeping disabled|
|1|Pad keeping enabled|



## ~~NOTE~~ 

The default state of GPIO pins on a reset event is high-Z. The high-Z state might settle to active high or active low at chip depending on the supply, temperature and other factors. Hence, it is recommended to use external pulls to ensure safe inactive state in event of a reset. 

## 4.3 Functional description 

The signal multiplexing architectural implementation is as shown in the following figure. 

**==> picture [405 x 156] intentionally omitted <==**

**----- Start of picture text -----**<br>
IND IND IND<br>GPIO<br>Pad controls<br>DO Signal DO Functional<br>Padring multiplexing modules or<br>unit peripherals<br>OBE OBE<br>IBE IBE<br>Figure 13. Signal Multiplexing<br>**----- End of picture text -----**<br>


## 4.4 Signal Multiplexing sheet 

IO Signal Description Input Multiplexing sheet(s) attached to the Reference Manual contains information on pins/balls of this device. 

The 'IO Signal Table' and 'Input Muxing' tabs in the sheet correspond to the signal multiplexing information. The 'IO Signal Table' consists of all the pin muxing details and the 'Input Muxing' specifies the priority for the input muxing where an input path is driven by more than one pad. 

## 4.4.1 IO Signal Table 

Following is an example snippet of IO Signal Table. For selecting any functionality, the pad MSCR register (refer to SIUL2_MSCRn) needs to be configured accordingly. 

S32K3xx Reference Manual, Rev. 12, 2025-11-11 

Reference Manual 

40 / 5394 

NXP Semiconductors 

Signal Multiplexing 

||||||||||||||||||||||||||||||
|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|
|**Port**|**CR**|**SSS**|**Function**|**Module**|**Description**|**Direction**|**Pad Type**|**S32K344_257bga**|**S32K344_172hdqfp**|**I/O Power Domain**|**I/O Power Domain**<br>**Pad State During**<br>**Destructive Reset**|**Pad State After**<br>**Destructive Reset**|**Pad State During**<br>**Functional Reset**|**Pad State After**<br>**Functional Reset**|**Pad State After Selftest**|**Pad State After FCCU**<br>**Error**|**Pad State After FCCU**<br>**I/O Power Segment**|**MSCR**|||||||||||
|||||||||||||||||||**OBE[21]**|**IBE[19]**|**INV[17]**|**PKE[16]**|**SRC[14]**|**PUE[13]**|**PUS[11]**|**DSE[8]**|**IFE[6]**|**SMC[5]**|**SSS[2:0]**|
|PTA0|SIUL_MSCR00000_0000|SIUL_MSCR00000_0000|GPIO[0]|SIUL||I/O|GPIO-STANDARD|A13|137|VDD_HV_A|Hi-Z|Hi-Z|Hi-Z|Hi-Z|Hi-Z|Hi-Z||0|0|0|0|-|0|0|-|-|0|~~0~~00|
|PTA0||0000_0001|LPSPI4_PCS2|LPSPI4|Peripheral Chip Select 2|O|||||||||||||||||||||||
|PTA0||0000_0010|eMIOS_0_CH[17]_Y|eMIOS_0|eMIOS Channel|O|||||||||||||||||||||||
|PTA0||0000_0011|LCU0_OUT4|LCU0|LCU Output|O|||||||||||||||||||||||
|PTA0||0000_0100|FXIO_D2|FXIO|FlexIO Bi-directional Shift/timer I/O|O|||||||||||||||||||||||
|PTA0||0000_0101|eMIOS_1_CH[0]_X|eMIOS_1|eMIOS Channel|O|||||||||||||||||||||||
|PTA0||0000_0110|LPSPI0_PCS7|LPSPI0|Peripheral Chip Select 7|O|||||||||||||||||||||||
|PTA0||0000_0111|TRGMUX_OUT3|TRGMUX|Trigger Mux Output|O|||||||||||||||||||||||
|PTA0|-|-|ADC0_S8|ADC0|ADC Standard Input|I|||||||||||||||||||||||
|PTA0|-|-|CMP1_IN0|CMP1|Comparator Input Signal|I|||||||||||||||||||||||
|PTA0|SIUL_IMCR528|SIUL_IMCR528 0000_0001|0000_0001<br>EIRQ[0]|SIUL|External Interrupt|I|||||||||||||||||||||||
|PTA0|SIUL_IMCR577|SIUL_IMCR577 0000_0010|0000_0010<br>eMIOS_0_CH[17]_Y|eMIOS_0|eMIOS Channel|I|||||||||||||||||||||||
|PTA0|SIUL_IMCR592|SIUL_IMCR592 0000_0011|0000_0011<br>eMIOS_1_CH[0]_X|eMIOS_1|eMIOS Channel|I|||||||||||||||||||||||
|PTA0|SIUL_IMCR666|SIUL_IMCR666 0000_0010|0000_0010<br>FXIO_D2|FXIO|FlexIO Bi-directional Shift/timer I/O|I|||||||||||||||||||||||
|PTA0|SIUL_IMCR740|SIUL_IMCR740 0000_0001|0000_0001<br>LPSPI0_PCS7|LPSPI0|Peripheral Chip Select 7|I|||||||||||||||||||||||
|PTA0|SIUL_IMCR769|SIUL_IMCR769 0000_0001|0000_0001<br>LPSPI4_PCS2|LPSPI4|Peripheral Chip Select 2|I|||||||||||||||||||||||
|PTA0|SIUL_IMCR872|SIUL_IMCR872 0000_0001|0000_0001<br>LPUART0_CTS|LPUART0|Clear To Send (bar)|I|||||||||||||||||||||||
|Figure 14. IO signal table snippet|||||||||||||||||||||||||||||



Figure 14. IO signal table snippet 

The columns of the above figure are described below: 

- Port: This field in IO Signal Table specifies the PAD names of the device. 

- CR(Control Register): This field specifies the name of MSCR corresponding to the Port field. 'On this device, there are up to twelve port groups (PTA, PTB, PTC, PTD, PTE, PTF, PTG, PTH,PTI,PTJ and PTK) that are controlled by SIUL2_MSCRn registers. The below table shows the mapping of ports with respect to SIUL2_MSCRn registers. 

- Table 18. • Port/MSCR mapping 

|Port|SIUL2_MSCRn index|
|---|---|
|PortA[0-31]|MSCR0 - MSCR31|
|PortB[0-31]|MSCR32 - MSCR63|
|PortC[0-31]|MSCR64 - MSCR95|
|PortD[0-31]|MSCR96 - MSCR127|
|PortE[0-31]|MSCR128 - MSCR159|
|PortF[0-31]|MSCR160 - MSCR191|
|PortG[0-31]|MSCR192 - MSCR223|
|PortH[0-31]|MSCR224 - MSCR255|
|PortI[0-31]|MSCR256 - MSCR287|
|PortJ[0-31]|MSCR288 - MSCR319|
|PortK[0-3]|MSCR320 - MSCR323|



See SIUL2_MSCR/IMCR (See following Input Muxing section for details on IMCR) for description of MSCR/IMCR fields. 

- SSS: This field specifies the ALT mode of operation as per MSCR[Mux_mode]. Not all pins support all pin muxing slots. Unimplemented pin muxing slots are reserved. The corresponding pin is configured in the following pin muxing slot as follows: 

   - 0000: Alternative 0 (GPIO) 

   - 0001: Alternative 1 (chip-specific) 

   - 0010: Alternative 2 (chip-specific) 

   - 0011: Alternative 3 (chip-specific) 

   - 0100: Alternative 4 (chip-specific) 

   - 0101: Alternative 5 (chip-specific) 

   - 0110: Alternative 6 (chip-specific) 

   - 0111: Alternative 7 (chip-specific) 

S32K3xx Reference Manual, Rev. 12, 2025-11-11 

Reference Manual 

41 / 5394 

NXP Semiconductors 

Signal Multiplexing 

- 1000: Alternative 8 (chip-specific) 

- 1001: Alternative 9 (chip-specific) 

- 1010: Alternative 10 (chip-specific) 

- 1011: Alternative 11 (chip-specific) 

- 1100: Alternative 12 (chip-specific) 

- 1101: Alternative 13 (chip-specific) 

- 1110: Alternative 14 (chip-specific) 

- 1111: Alternative 15 (chip-specific) 

## ~~NOTE~~ 

The analog functionalities are specified with '-' in this field. 

- Function: This field specifies the functionality of the pad as per the corresponding ALT mode specified by SSS field. 

- Module: The Module field contains the module which is governing the pad for the ALT mode. 

- Description: This field mentions a short description of pad functionality. 

- Direction: This field specifies the direction (Input, Output or Input/Output) of the pad for the concerned functionality. 

- Pad Type: This field mentions the pad type of the corresponding pad. 

   - GPIO-Standard: 

      - ◦Switching up to 10 MHz 

      - ◦High drive-strength not supported. 

      - ◦Slew-rate control not supported. 

   - GPIO-Standard plus: 

      - ◦Switching up to 25 MHz 

      - ◦Supports high drive-strength. 

      - ◦Slew-rate control not supported. 

   - GPIO-Medium: 

      - ◦Switching up to 50 MHz 

      - ◦Supports high drive-strength. 

      - ◦Supports slew-rate control. 

   - GPIO-Fast: 

      - ◦Switching up to 120 MHz 

## ~~NOTE~~ 

For S32K328, S32K338, S32K348, S32K358, S32K356, S32K388, and S32K389 switching frequency up to 125 MHz. 

   - ◦Supports high drive-strength. 

   - ◦Supports slew-rate control. 

- The next columns specify the pin number in the supported packages for the device. 

- I/O Power Domain: This field refers to the power domain of associated pad (VDD_HV_A/VDD_HV_B). 

- Pad State during/after Reset: These fields represent the pad states during and post different device resets. 

S32K3xx Reference Manual, Rev. 12, 2025-11-11 

Reference Manual 

42 / 5394 

NXP Semiconductors 

Signal Multiplexing 

- MSCR: This field specifies the default MSCR value for corresponding pad. Refer SIUL2_MSCRn for description of MSCR fields. 

- The next two columns specify the reset value and the configurable bit fields of MSCR corresponding to pad. 

## 4.4.2 Input muxing table 

As the same function can be multiplexed to several pads by configuring their respective IMCRs, there is priority input muxing. In case of same input being driven from multiple pads, the one with highest priority (1 being the highest) will drive the input. Following is a snippet of Input Muxing Table. 

|4.4.2 Input muxing table<br>As the same function can be multiplexed to several pads by configuring their respective IMCRs, there is priority input muxing. In<br>case of same input being driven from multiple pads, the one with highest priority (1 being the highest) will drive the input. Following<br>is a snippet of Input Muxing Table.|4.4.2 Input muxing table<br>As the same function can be multiplexed to several pads by configuring their respective IMCRs, there is priority input muxing. In<br>case of same input being driven from multiple pads, the one with highest priority (1 being the highest) will drive the input. Following<br>is a snippet of Input Muxing Table.|4.4.2 Input muxing table<br>As the same function can be multiplexed to several pads by configuring their respective IMCRs, there is priority input muxing. In<br>case of same input being driven from multiple pads, the one with highest priority (1 being the highest) will drive the input. Following<br>is a snippet of Input Muxing Table.|4.4.2 Input muxing table<br>As the same function can be multiplexed to several pads by configuring their respective IMCRs, there is priority input muxing. In<br>case of same input being driven from multiple pads, the one with highest priority (1 being the highest) will drive the input. Following<br>is a snippet of Input Muxing Table.|4.4.2 Input muxing table<br>As the same function can be multiplexed to several pads by configuring their respective IMCRs, there is priority input muxing. In<br>case of same input being driven from multiple pads, the one with highest priority (1 being the highest) will drive the input. Following<br>is a snippet of Input Muxing Table.|4.4.2 Input muxing table<br>As the same function can be multiplexed to several pads by configuring their respective IMCRs, there is priority input muxing. In<br>case of same input being driven from multiple pads, the one with highest priority (1 being the highest) will drive the input. Following<br>is a snippet of Input Muxing Table.|4.4.2 Input muxing table<br>As the same function can be multiplexed to several pads by configuring their respective IMCRs, there is priority input muxing. In<br>case of same input being driven from multiple pads, the one with highest priority (1 being the highest) will drive the input. Following<br>is a snippet of Input Muxing Table.|4.4.2 Input muxing table<br>As the same function can be multiplexed to several pads by configuring their respective IMCRs, there is priority input muxing. In<br>case of same input being driven from multiple pads, the one with highest priority (1 being the highest) will drive the input. Following<br>is a snippet of Input Muxing Table.|4.4.2 Input muxing table<br>As the same function can be multiplexed to several pads by configuring their respective IMCRs, there is priority input muxing. In<br>case of same input being driven from multiple pads, the one with highest priority (1 being the highest) will drive the input. Following<br>is a snippet of Input Muxing Table.|
|---|---|---|---|---|---|---|---|---|
||||||||||
|**Destination Instance**|**Destination Function**|**CR Instance**|<br>**Input CR#**|**Input SSS **|**Source Instance**|**Source Signal**|**S32K344_257bga**|**S32K344_172hdqfp_D**|
|CAN0|CAN0_RX|SIUL|SIUL_IMCR512|0000_0000|-|disable low|||
|||||0000_0001|IO_PAD|PTC2|T4|50|
|||||0000_0010|IO_PAD|PTA6|M15|102|
|||||0000_0011|IO_PAD|PTB0|P16|95|
|||||0000_0100|IO_PAD|PTA28|N2|30|
|||||0000_0101|IO_PAD|PTF21|K14||
|Figure 15. Input muxing table snippet|||||||||



The columns of the figure are briefly described below: 

- Destination Instance: This field contains the instance name of the input path to where the signal will propagate from padring. 

- Destination Function: This field mentions the function name of the input path. 

- Input SSS: This field specifies the IMCR[Mux_mode] value corresponding to the pad specified in source signal column. 

- Source Instance: This field specifies the source pad type. A blank is mentioned for the default source when no pad is driving the input path. 

- Source Signal: This field mentions the pad name. A ‘disable low’/’disable high’ specifies the signal behavior when none of the pads are driving the input path. 

- The next columns specify the pin number in the supported packages for the device. 

## 4.4.3 MSCR/IMCR description/explanation 

## MSCR assignments 

The Implemented SIUL2 Multiplexed Single Configuration Register details is provided in the I/O Signal Description Table attached as excel. 

## Example: 

If user wants to configure PTB0 as CAN0RX and PTB1 as CAN0TX, then the following configuration can be used in SIUL2 registers: 

```
//.CAN0.RX.(PTB0):
SIUL2.IMCR0.B.SSS.=.0b011;.//.Select.CAN0-RX
SIUL2.MSCR32.B.IBE.=.1;....//.Enable.the.input.buffer
//.CAN0.TX.(PTB1):
SIUL2.MSCR33.B.SSS.=.0b101;.//.Select.CAN0-TX
SIUL2.MSCR33.B.OBE.=.1;.//.Enable.the.output.buffer
```

MSCR bit fields correspond to pin/pad basis, these are independent of muxing implemented on that specific pin/pad. As an example, pad PTA31 has SSS, SMC, DSE, PUS, PKE, INV, IBE and OBE are implemented with the reset value 0 and SRC is implemented with reset value 1. 

S32K3xx Reference Manual, Rev. 12, 2025-11-11 

Reference Manual 

43 / 5394 

NXP Semiconductors 

Signal Multiplexing 

In the 'IO Signal Table' tab of the IOMUX file attached, the MSCR register bits shows ‘0’, ‘1’, and ‘-’ for state of all bits associated with different ports. ‘0’ or ’1’ represents the reset state and ‘-’ represents the bit is not supported on the respective port. 

## ~~NOTE~~ 

The GPIOs 38 and 39 are used for direct connections and FXOSC. 

## 4.4.4 Pinout diagrams 

See IO Signal Description Input Multiplexing sheet(s) attached to the Reference Manual for pinout diagrams corresponding to available packages. 

## 4.5 Pin States 

The tables in the upcoming sections mention the state of pins of the device under various conditions/event like Functional Reset, Destructive Reset, Power Up condition, during Selftest Phase etc. The details of the Reset events can be found in the Reset overview Chapter. The Details of Selftest can be found in the STCU chapter. 

## ~~NOTE~~ 

For S32K358, S32K356, S32K348, S32K338, and S32K328: Pad states of PTE13 are defined when this is not configured as VRC_CTRL pin. 

## 4.5.1 Pin numbers 

See IOMUX sheet for the pin numbers of the functions mentioned in tables given in following sections. 

## 4.5.2 Power up 

This table mentions the pin behavior on power up condition of the device. 

Table 19. Power up 

|Pin function|POWER UP until SW comes up1|
|---|---|
|RESET_B|LOW|
|JTAG_TMS,JTAG_TCK,JTAG_TDI,JTAG_TDOas JTAG|PULLED Values:<br>(TMS = HIGH, TCK = LOW, TDI =HIGH)<br>TDO: HIGH Z|
|ETM_TRACE|HIGH Z|
|FCCU_ERR|HIGH Z|
|CLKOUT_STANDBY|HIGH Z|
|GPIOs|HIGH Z|
|EXTAL|HIGH Z till extal is connected|
|XTAL|HIGH Z till xtal is connected|



1. The IO pad states are undefined until Supply rises sufficiently to enable the POR circuits. 

## 4.5.3 Destructive Reset 

This table mentions the Pin behavior when any Destructive Reset event is triggered. 

S32K3xx Reference Manual, Rev. 12, 2025-11-11 

Reference Manual 

44 / 5394 

NXP Semiconductors 

Signal Multiplexing 

Table 20. Destructive Reset 

|Pins|ON Destructive Reset until SW comes up|
|---|---|
|RESET_B|LOW|
|TMS,TCK,TDI,TDO as JTAG|PULLED Values:<br>(TMS = HIGH TCK = LOW, TDI =HIGH)<br>TDO: HIGH Z|
|ETM_TRACE (Only on 17trace Pins)|HIGH Z|
|FCCU_ERR|HIGH Z|
|CLKOUT_STANDBY|Clkout expose if CLKOUT_STANDBY is configured to<br>be Enabled<br>Else HIGH Z|
|GPIOs|HIGH Z|



## 4.5.4 Functional Reset including Functional entry sequence 

This table mentions the Pin behavior when any functional Reset event is triggered. Also, when the FCCU reaction is configured as Functional Reset , then also the same behavior is achieved. 

Table 21. Functional Reset including Functional entry sequence 

|Pins|Functional Reset Entry|Reset until SW comes up|
|---|---|---|
|RESET_B|LOW|LOW|
|TMS,TCK,TDI,TDO as JTAG|TMS,TCK,TDI: PULLED Values if<br>configured as JTAG<br>(TMS = HIGH TCK = LOW, TDI =HIGH)<br>HIGH Z if configured as GPIO<br>TDO: HIGH Z|PULLED Values<br>(TMS = HIGH TCK = LOW, TDI =HIGH)<br>TDO: HIGH Z|
|ETM_TRACE|Trace if<br>MDMAPCTL[DBGRSTSLOWPAD] or<br>MDMAPCTL[DBGRSTFASTPAD] is<br>configured to be Enabled<br>Else HIGH Z|Trace if<br>MDMAPCTL[DBGRSTSLOWPAD] or<br>MDMAPCTL[DBGRSTFASTPAD] is<br>configured to be Enabled<br>Else HIGH Z|
|FCCU_ERR|ERR from FCCU if<br>UTEST_MISC[FCCU_EOUT_DEDICAT<br>ED] is configured to be Enabled<br>Else HIGH Z|ERR from FCCU if<br>UTEST_MISC[FCCU_EOUT_DEDICAT<br>ED] is configured to be Enabled.<br>Else HIGH Z|
|CLKOUT_STANDBY|Clkout expose if<br>DCMRWP1[CLKOUT_STANDBY] is<br>configured to be Enabled<br>Else HIGH Z|Clkout expose if<br>DCMRWP1[CLKOUT_STANDBY] is<br>configured to be Enabled<br>Else HIGH Z|



Table continues on the next page... 

S32K3xx Reference Manual, Rev. 12, 2025-11-11 

Reference Manual 

45 / 5394 

NXP Semiconductors 

Signal Multiplexing 

Table 21. Functional Reset including Functional entry sequence (continued) 

|Pins|Functional Reset Entry|Reset until SW comes up|
|---|---|---|
|GPIOs|HIGH Z|HIGH Z|



## 4.5.5 SELFTEST(MC_RGM.ERCTRL[ERASSERT] configured as 1) 

Table 22. SELFTEST(MC_RGM.ERCTRL[ERASSERT] configured as 1) 

|Pins|Selftest|Reset until SW comes up|
|---|---|---|
|RESET_B|LOW if configured as Reset Pin<br>High Z if configured as GPIO|LOW if configured as Reset Pin<br>High Z if configured as GPIO|
|TMS,TCK,TDI,TDO as JTAG|PULLED Values if configured as JTAG<br>(TMS = HIGH, TCK = LOW, TDI = HIGH)<br>TDO: HIGH Z|PULLED Values<br>(TMS = HIGH, TCK = LOW, TDI = HIGH)<br>TDO: HIGH Z|
|ETM_TRACE|Trace if<br>MDMAPCTL[DBGRSTSLOWPAD] or<br>MDMAPCTL[DBGRSTFASTPAD] is<br>configured to be Enabled.<br>Else HIGH Z|Trace if<br>MDMAPCTL[DBGRSTSLOWPAD] or<br>MDMAPCTL[DBGRSTFASTPAD] is<br>configured to be Enabled.<br>Else HIGH Z|
|FCCU_ERR|FCCU Error State if<br>UTEST_MISC[FCCU_EOUT_DEDICAT<br>ED] is Enabled and<br>DCMRWD2[EOUT_STAT_DUR_STEST<br>] is Enabled<br>Else HIGH Z|FCCU Error State if<br>UTEST_MISC[FCCU_EOUT_DEDICAT<br>ED] is Enabled and<br>DCMRWD2[EOUT_STAT_DUR_STEST<br>] is Enabled<br>Else HIGH Z|
|CLKOUT_STANDBY|Clkout expose if<br>DCMRWP1[CLKOUT_STANDBY] is<br>configured to be Enabled<br>Else HIGH Z|Clkout expose if<br>DCMRWP1[CLKOUT_STANDBY] is<br>configured to be Enabled<br>Else HIGH Z|
|GPIOs|HIGH Z|HIGH Z|



## 4.5.6 SELFTEST (RGM_ERCTRL[ERASSERT]=0 and RGM_FRBE[ST_DONE] =0) 

Table 23. SELFTEST (RGM_ERCTRL[ERASSERT]=0 and RGM_FRBE[ST_DONE] =0) 

|Pins|Selftest|Reset after Selftest until SW comes up|
|---|---|---|
|RESET_B|Same state as before selftest|Same state as before selftest|
|TMS,TCK,TDI,TDO as JTAG|Same state as before selftest|PULLED Values<br>(TMS = HIGH, TCK = LOW, TDI = HIGH)<br>TDO: No change|
|ETM_TRACE|Same state as before selftest|Same state as before selftest|
|Table continues on the next page...|||



S32K3xx Reference Manual, Rev. 12, 2025-11-11 

Reference Manual 

46 / 5394 

NXP Semiconductors 

Signal Multiplexing 

Table 23. SELFTEST (RGM_ERCTRL[ERASSERT]=0 and RGM_FRBE[ST_DONE] =0) (continued) 

|Pins|Selftest|Reset after Selftest until SW comes up|
|---|---|---|
|FCCU_ERR|FCCU Error State if<br>UTEST_MISC[FCCU_EOUT_DEDICAT<br>ED] is Enabled and<br>DCMRWD2[EOUT_STAT_DUR_STEST<br>] is Enabled<br>Else No change|FCCU Error State if<br>UTEST_MISC[FCCU_EOUT_DEDICAT<br>ED] is Enabled and<br>DCMRWD2[EOUT_STAT_DUR_STEST<br>] is Enabled<br>Else No change|
|CLKOUT_STANDBY|Same state as before selftest|Same state as before selftest|
|GPIOs|Same state as before selftest|Same state as before selftest|



## 4.5.7 FCCU fault in RUN mode when the fault reaction is not Reset 

## ~~NOTE~~ 

For any GPIO PAD If SMC=1 then the pad would retain it's state during the fault mode else if SMC=0 then the pad would become high Z during the fault mode. 

Table 24. FCCU fault in RUN mode, fault reaction not Reset 

|Pins|ON FCCU Fault|
|---|---|
|RESET_B|If RESET_B is assigned as a dedicated PAD then no change in the state of the PAD else if RESET_B<br>is configured as GPIO then it would behave as per the SMC configuration.<br>• Case 1: If dcf_client_reset_pad_dedicated[reset pad dedicated] is configured as 1'b1, the pad<br>functions as per the reset state machine.<br>• Case 2: If dcf_client_reset_pad_dedicated[reset pad dedicated] is configured as 1'b0 and<br>SIUL2.MSCR5[SMC] is configured as 1'b1, the pad functions as per the configured protocol<br>status, the protocol being configured via SIUL2.MSCR5[SSS].<br>• Case 3: If dcf_client_reset_pad_dedicated[reset pad dedicated] is configured as 1'b0 and<br>SIUL2.MSCR5[SMC] is configured as 1'b0, the pin gets tristated (high-Z).|
|TMS, TCK, TDI, TDO<br>as JTAG|If the PAD is configured as a JTAG PAD then no change and the pad would continue performing the<br>operation else if it is a GPIO PAD then it would behave as per the SMC configuration.<br>• Case 1: If the pad is configured for JTAG mode and SMC bit of SIUL2's MSCR register of the<br>corresponding pin is configured as 1'b1, the pad functions as per the JTAGC state machine<br>or protocol.<br>• Case 2: If the pad is configured for non-JTAG mode and SMC bit of SIUL2's MSCR register of the<br>corresponding pin is configured as 1'b0, the pins get tristated (high-Z).|
|ETM_TRACE|If the PAD is configured as a dedicated PAD then no change and the pad would continue performing<br>the operation else if it is a GPIO PAD then it would behave as per the SMC configuration.<br>• Case 1: If the pad is configured for ETM_TRACE functionality and SMC bit of SIUL2's MSCR<br>register of the corresponding pin is configured as 1'b1, the pad functions as per the ETM trace<br>control logic.<br>• Case 2: If the pad is configured for non-ETM_TRACE mode and SMC bit of SIUL2's MSCR<br>register of the corresponding pin is configured as 1'b0, the pins get tristated (high-Z).|



Table continues on the next page... 

S32K3xx Reference Manual, Rev. 12, 2025-11-11 

Reference Manual 

47 / 5394 

NXP Semiconductors 

Signal Multiplexing 

Table 24. FCCU fault in RUN mode, fault reaction not Reset (continued) 

|Pins|ON FCCU Fault|
|---|---|
|FCCU_ERR|If the PAD is configured as a dedicated PAD by programming the<br>UTEST_MISC[FCCU_EOUT_DEDICATED] as well as Eout indication is enabled then it would be<br>indicating error state else if it is a GPIO PAD then it would behave as per the SMC configuration.<br>• Case 1: If dcf_client_utest_misc[FCCU_EOUT_DEDICATED] is configured as 1'b1, the<br>FCCU_ERR pins indicate the error state.<br>• Case 2: If dcf_client_utest_misc[FCCU_EOUT_DEDICATED] is configured as 1'b0 and SMC bit<br>of the SIUL2's corresponding MSCR register is configured as 1'b1, the pin retains its state.<br>• Case 3: If dcf_client_utest_misc[FCCU_EOUT_DEDICATED] is configured as 1'b0 and<br>SIUL2.MSCR5[SMC] is configured as 1'b0, the pin gets tristated (high-Z).|
|CLKOUT_STANDBY|If the PAD is configured as a dedicated PAD then no change and the pad would continue performing<br>the operation else if it is a GPIO PAD then it would behave as per the SMC configuration.<br>• Case 1: If the pad is configured for CLKOUT_STANDBY functionality and SMC bit of SIUL2's<br>MSCR register of the corresponding pin is configured as 1'b1, the pin continues functioning as the<br>CLKOUT_STANDBY pin.<br>• Case 2: If the SMC bit of SIUL2's MSCR register of the corresponding pin is configured as 1'b0,<br>the pin gets tristated (high-Z).|
|GPIOs|If the PAD is configured as a dedicated PAD then no change and the pad would continue performing<br>the operation else if it is a GPIO PAD then it would behave as per the SMC configuration.<br>• Case 1: If the SMC bit of SIUL2's MSCR register of the corresponding pin is configured as 1'b1,<br>the pin continues its operation.<br>• Case 2: If the SMC bit of SIUL2's MSCR register of the corresponding pin is configured as 1'b0,<br>the pins get tristated (high-Z).|



## 4.5.8 STANDBY ( DCMRWF1[STANDBY_IO_CONFIG] must be configured as 1) 

- Please refer to Padkeeping Section for steps to configure the various pad states during standby 

Table 25. STANDBY 

|Pins|Standby until SW comes up|
|---|---|
|RESET_B|Alive / HighZ /LOW/HIGH (Depends on Software configuration<br>before entering STANDBY)|
|TMS,TCK,TDI,TDO as JTAG|HighZ /LOW/HIGH (Depends on Software configuration before<br>entering STANDBY)|
|ETM_TRACE|HighZ /LOW/HIGH (Depends on Software configuration before<br>entering STANDBY)|
|FCUU_ERR|HighZ /LOW/HIGH (Depends on Software configuration before<br>entering STANDBY)|
|CLKOUT_STANDBY|Alive / HighZ /LOW/HIGH (Depends on Software configuration<br>before entering STANDBY)|
|GPIOs|HighZ /LOW/HIGH (Depends on Software configuration before<br>entering STANDBY)|



S32K3xx Reference Manual, Rev. 12, 2025-11-11 

Reference Manual 

48 / 5394 

NXP Semiconductors 

Signal Multiplexing 

## 4.6 Glossary 

|4.6 Glossary||
|---|---|
|DSE|Drive strength enable|
|EXTAL|External crystal input|
|GPIO|General purpose input/output|
|IBE|Input buffer enable|
|INV|Invert enable|
|JTAG_TMS|JTAG test mode select|
|JTAG_TCK|JTAG test clock input|
|JTAG_TDI|JTAG test data input|
|JTAG_TDO|JTAG test data output|
|OBE|Output buffer enable|
|PUS|Pullup and pulldown select|
|PKE|Pad keeping enable|
|SMC|Safe mode control|
|SRC|Slew rate control|
|SSS|Source signal select|
|XTAL|External crystal output|



S32K3xx Reference Manual, Rev. 12, 2025-11-11 

Reference Manual 

49 / 5394 

NXP Semiconductors 

## Chapter 5 Cortex-M7 Overview 

## 5.1 Introduction 

Cortex-M7 is a high-performance embedded processor intended for deeply embedded applications that require fast interrupt response features. The configuration of the processor is based on little-endian format, and you must compile the execution testbench tests in this format too. 

Table 26. Cortex-M7 instances 

|Instances|S32K388/<br>S32K389|S32K338|S32K358/<br>S32K356|S32K328/<br>S32K324/S32K322|S32K348/S32K344/S32K342/<br>S32K341/S32K314/S32K312/<br>S32K311/S32K310|
|---|---|---|---|---|---|
|CM7_0|Yes|Yes|Yes|Yes|Yes|
|CM7_1|Yes|Yes|No|Yes|No|
|CM7_2|Yes|Yes|Yes|No|No|
|CM7_3|Yes|No|No|No|No|



## 5.1.1 Features 

Cortex-M7 provides: 

- Low interrupt latency 

- Low-cost debug 

- Backwards compatibility with existing Cortex-M profile processors 

- In-order superscalar pipeline 

- Dual-issue support for load/load and load/store instruction pairs to multiple memory interfaces 

- An MPU that you could configure to protect regions of memory 

- An NVIC 

- A debug and trace unit (CoreSight components) 

- Floating-point arithmetic functionality, with support for single-precision arithmetic 

- The ability to perform speculative load from any normal type memory space through its AXIM bus, if D-cache is enabled 

- Several memory interfaces that include: 

   - Harvard architecture-based instruction and data caches, and an AXIM interface 

   - A dedicated low-latency AHBP interface 

   - A 64-bit AXI AMBA4 memory interface with a 16 KB instruction cache and a 16 KB data cache for efficient access to external resources. The instruction and data caches are ECC protected. 

   - A 32-bit AHBS for interfacing with slaves such as DMA 

   - 64-bit and 32-bit memory interfaces for the connection to local Tightly Coupled Memories called ITCM and DTCM. For details see Core configuration 

## 5.1.2 Related information 

For detailed information on: 

S32K3xx Reference Manual, Rev. 12, 2025-11-11 

Reference Manual 

50 / 5394 

NXP Semiconductors 

Cortex-M7 Overview 

- Cortex-M7 processor, see Arm Cortex-M7 Processor Technical Reference Manual. 

- Cortex-M7 peripherals and control, see Arm Cortex-M7 Devices Generic User Guide. 

- System memory map, see the memory map file attached to this document. 

## 5.1.3 Buses, interconnects, and interfaces 

This table discusses Cortex-M7 buses and their associated interconnects and interfaces. 

Table 27. Buses and associated information 

|Bus name|Description|
|---|---|
|AXIM|Using the XHB400 module, this bus is first translated to the AHB-Lite bus that interfaces<br>with the AXBS crossbar switch providing high-bandwidth access to on-chip memories and<br>peripherals.|
|AHBP|This bus connects to the AXBS crossbar switch providing high-bandwidth access to on-chip<br>peripherals.|
|PPB|This bus provides access to these modules:<br>• Arm modules such as NVIC,ETM,ITM,DWT, and ROM tables<br>• Miscellaneous Control Module (MCM)|



~~NOTE~~ 

S32K3xx AHBP bus is enabled after reset. Therefore, accesses of all cores to on-chip peripherals are performed exclusively through this bus. 

## 5.1.4 Core configuration 

This table describes Cortex-M7 parameter settings. 

Table 28. Core configuration 

|Parameter|Configuration1|
|---|---|
|FPU|Single precision|
|DSP extension instructions|• Single cycle 16/32-bitMAC<br>• Single cycle dual 16-bit MAC<br>• 8/16-bitSIMDarithmetic<br>• Hardware divide (2-12 cycles)|
|Armv8-M security extensions|Not implemented|
|I-cache|Implemented|
|D-cache|Implemented|
|Caches ECC|Implemented|
|On core MPU region|16|
|Number of IRQs|240|
|IRQ priority width configuration|4 (16 interrupt priority levels)|
|Debug (breakpoint/watchpoint)|Full comparator set: 4 DWT and 8FPBcomparators|



Table continues on the next page... 

S32K3xx Reference Manual, Rev. 12, 2025-11-11 

Reference Manual 

51 / 5394 

NXP Semiconductors 

Cortex-M7 Overview 

Table 28. Core configuration (continued) 

|Parameter|Configuration1|
|---|---|
|Internal trace support|ITM and DWT trace functionality implemented|
|ETM support|Instruction and data ETM interface implemented|
|CTI|Implemented|
|WIC support|Not implemented|
|Dual-redundant core (lock-step) CPU functionality|Not implemented2|
|RAR|All asynchronously reset|
|I-cache size|Implemented3|
|D-cache size|Implemented3|
|ITCM|• All chips except S32K388/S32K389: 32 KB for CM7_0/1,<br>64 KB for CM7_2<br>• S32K388/S32K389: 32 KB for all cores|
|DTCM0|• All chips except S32K388/S32K389: 32 KB for CM7_0/1,<br>64 KB for CM7_2<br>• S32K388/S32K389: 32 KB for all cores|
|DTCM1|• All chips except S32K388/S32K389: 32 KB for CM7_0/1,<br>64 KB for CM7_2<br>• S32K388/S32K389: 32 KB for all cores|



1. Armv7-M (Harvard architecture), six-stage superscalar plus branch prediction 

2. Two different Cortex-M7 cores are used physically in the S32K342, S32K344, S32K348, S32K358, S32K356, S32K388, and S32K389 chips (dual Cortex-M7 lock-step parts) 

3. See chapter 'Memory and Memory Interfaces' for details 

## 5.2 Speculative accesses 

The Arm Cortex M7 processor can issue speculative read accesses that may access any location within the complete memory address range. This behavior can be controlled, but not disabled. Corresponding effects must be considered for a proper operation of your system. 

Speculative accesses do not cause any processor faults. The processor is aware whether an access is speculative, and ignores any error response signaled by the system due to the speculative access. However, the system that is integrating the processor cannot distinguish speculative accesses from non-speculative accesses. 

Addresses used by speculative accesses are not validated against the memory map of the device, and may attempt to also access non-existing memory regions or hardware elements having side effects. For details about corresponding behavior of the Arm Cortex M7 processor see Related information. Important processing aspects are listed in section “Memory Model” within the Generic User Guide. 

Speculative accesses can result in improved performance when the related memory regions are properly characterized. It is imperative to properly setup the attributes within the Memory Protection Unit (MPU) to avoid any unwanted impact of a speculative access. Examples for possible, corresponding issues are usually the result of side effects unknown to the processor: 

- Speculative access to an uninitialized RAM memory location that causes a double bit error {the related fault processing by the FCCU is performed independently from the processor}. 

- Speculative access to a peripheral that causes an unwanted operation; for example, a FIFO read {the corresponding data may be removed from the FIFO without being processed}. 

S32K3xx Reference Manual, Rev. 12, 2025-11-11 

Reference Manual 

52 / 5394 

NXP Semiconductors 

Cortex-M7 Overview 

- Speculative access to a peripheral that is not clocked, powered down, or cannot respond {the access may not be terminated, resulting an access that is stalled, system blockage}. 

- Speculative access to an address range that causes an unexpected error being reported; for example, a read-while-write error of the embedded flash (indicated by setting MCRS[RWE]) during a flash erase or program operation {which may hide real errors}. 

Speculative accesses can be controlled by a proper assignment of memory regions within the MPU: 

- Speculative instruction fetches are never made to memory addresses in an Execute Never region. 

- Speculative data reads are never made to memory addresses marked as non-accessible in the MPU. 

- Speculative cache line-fills are never made to non-cacheable memory addresses. 

- Speculative data reads and speculative cache line-fills are never made to memory addresses in a region having a Device or Strongly-ordered attribute. 

- Speculative reads are never made on the AHBP interface. 

- Speculative writes are never made. 

Memory regions mapped to a TCM are always treated as Normal Memory (equivalent to the MPU attribute) and are therefore always subject to speculation. Related issues can be avoided by properly initializing any TCM memory before a corresponding access may occur and by ensuring that corresponding faults are not being processed before the appropriate management is in place. 

When no speculative accesses should be initiated to a memory region, it is recommended to set all of the following attributes within the MPU for this region: Device or Strongly-ordered, and Execute Never. These attributes are often also used for address ranges associated with peripherals. 

Unwanted processing of side effects caused by a speculative access can also be inhibited by disabling the related events while a speculative access may occur. As an example, the FCCU can be enabled after the ECC of the RAM memories has been initialized. As a second example, read accesses to a Flash block can be inhibited by configuring an MPU region while it is being erased. 

## 5.3 Debug facilities 

This chip has extensive debug capabilities such as run control and tracing. It includes the standard Arm debug port that supports the JTAG and SWD interfaces. 

## 5.4 Vector fetch behavior on Cortex-M7 

In Cortex-M7, the vector fetches are looked up into the I-Cache. if the vector table is located in a region of memory that is cacheable, any load or store to the vector must be treated as self-modifying code and cache maintenance instructions should be used to synchronize the updates to the data and instruction caches. The Cortex-M7 Device Generic User Guide chapter 'Cache maintenance design hints and tips' specifies a recommendation for synchronization of the D-Cache and I-Cache. 

If cache maintenance is to be avoided each time when the vector table gets updated, then the vector table must be allocated in the ITCM or DTCM, as those are non-cacheable regions. Alternatively, the I-Cache must be enabled after the vector table has been initialized. 

## 5.5 TCM retry 

TCM retry is disabled and software should disable the TCM retry bit at startup by programming the relevant core's CM7_ITCMCR[RETEN] and CM7_DTCMR[RETEN] fields to disable state. 

## 5.6 Glossary 

AHBP AHB-lite peripheral 

AHBS AHB-slave port 

S32K3xx Reference Manual, Rev. 12, 2025-11-11 

Reference Manual 

53 / 5394 

NXP Semiconductors 

Cortex-M7 Overview 

AXIM Advanced extensible interface master 

- DWT Data watchpoint and trace unit 

- ETM Embedded trace macrocell 

- FPU Floating point unit 

- FPB Flash patch and breakpoint 

- ITM Instrumentation trace macrocell 

- MAC Multiplier accumulator (refers to a multiplier accumulator unit as well as multiplier accumulator operation) 

- NVIC Nested vectored interrupt controller 

- RCCU Redundancy control checking unit 

- RAR Reset-all-registers 

- SIMD Single instruction multiple data 

S32K3xx Reference Manual, Rev. 12, 2025-11-11 

Reference Manual 

54 / 5394 

NXP Semiconductors 

## Chapter 6 Miscellaneous Control Module (MCM) 

## 6.1 Chip-specific MCM information 

## 6.1.1 MCM instances and configuration 

This chip supports up to four instances of MCM: 

- MCM_0 

- MCM_1 

- MCM_2 

- MCM_3 

## ~~NOTE~~ 

For S32K358, S32K356, S32K338, S32K388, and S32K389 the reset value for CM7_2 is: 

- LMEM_DESC_0: 8706_0000h 

- LMEM_DESC_1-2 : 8704_2000h 

Table 29. MCM instances 

|Instances|S32K388/<br>S32K389|S32K358/<br>S32K356/<br>S32K348/<br>S32K338/<br>S32K328|S32K322/S32K324/S32K344/S32K342|S32K312/S32K311/<br>S32K310/S32K314|
|---|---|---|---|---|
|MCM_0|Yes|Yes|Yes|Yes|
|MCM_1|Yes|Yes|Yes|No|
|MCM_2|Yes|Yes|No|No|
|MCM_3|Yes|No|No|No|



Table 30. Memories for all chips except S32K358/S32K356/S32K348/S32K338/S32K328/S32K388/S32K389 

|Memory|S32K311/S32K310/S32K312/S32K314<br>(Single core)|S32K322/S32K324 (Dual<br>core)|S32K342/S32K344<br>(Lockstep mode)|
|---|---|---|---|
|Icache|8 KB|8 KB (per core)|8 KB|
|Dcache|8 KB|8 KB (per core)|8 KB|
|ITCM|32 KB|32 KB (per core)|64 KB|
|DTCM|64 KB|64 KB (per core)|128 KB|



Table 31. Memories for S32K358/S32K356/S32K348/S32K338/S32K328/S32K388/S32K389 

|Memory|Dual core CM7_0<br>and CM7_1|Single core<br>CM7_21|CM7_0 and CM7_1<br>(Lockstep mode|CM7_2 (Lockstep<br>mode)2|CM7_32|
|---|---|---|---|---|---|
|Icache|16 KB (per core)|16 KB|16 KB|16 KB|16 KB|



Table continues on the next page... 

S32K3xx Reference Manual, Rev. 12, 2025-11-11 

Reference Manual 

55 / 5394 

NXP Semiconductors 

Miscellaneous Control Module (MCM) 

Table 31. Memories for S32K358/S32K356/S32K348/S32K338/S32K328/S32K388/S32K389 (continued) 

|Memory|Dual core CM7_0<br>and CM7_1|Single core<br>CM7_21|CM7_0 and CM7_1<br>(Lockstep mode|CM7_2 (Lockstep<br>mode)2|CM7_32|
|---|---|---|---|---|---|
|Dcache|16 KB (per core)|16 KB|16 KB|16 KB|16 KB|
|ITCM|32 KB (per core)|64 KB|64 KB|32 KB|32 KB|
|DTCM|64 KB (per core)|128 KB|128 KB|64 KB|64 KB|



1. Available only in S32K358/S32K356 

2. Available only in S32K388/S32K389 

## 6.2 Overview 

MCM provides miscellaneous control functions and contains local memory descriptors for the Cortex-M7 core. For more information about core-related registers, see the Cortex-M7 core overview chapter. 

~~NOTE~~ 

The terminology in this chapter has been updated to align with Arm's AMBA AHB Protocol Specification, as shown 

in the table below. 

## Table 32. Updated terms 

|Updated term|Deprecated term|
|---|---|
|Manager|Master|
|Subordinate|Slave|



## 6.2.1 Features 

The MCM includes the following features: 

- Program-visible information on the platform configuration and revision 

- Floating Point Exception monitor and interrupt control 

- Local memory descriptors: 

   - ITCM 

   - D0TCM 

   - D1TCM 

   - I-cache 

   - D-cache 

## 6.3 Functional description 

## 6.3.1 Interrupts 

MCM generates an interrupt if any of the following are true: 

- FPU input denormal interrupt is enabled (FIDCE) and an input is denormalized (FIDC). 

- FPU inexact interrupt is enabled (FIXCE) and a number is inexact (FIXC). 

- FPU underflow interrupt is enabled (FUFCE) and an underflow occurs (FUFC). 

- FPU overflow interrupt is enabled (FOFCE) and an overflow occurs (FOFC). 

S32K3xx Reference Manual, Rev. 12, 2025-11-11 

Reference Manual 

56 / 5394 

NXP Semiconductors 

Miscellaneous Control Module (MCM) 

- FPU divide-by-zero interrupt is enabled (FDZCE) and a divide-by-zero occurs (FDZC). 

- FPU invalid operation interrupt is enabled (FIOCE) and an invalid operation occurs (FIOC). 

- Write abort interrupt is enabled (WABE) and a write abort occurs (CORTEX-M7 WABORTS INDICATOR). 

## Determining interrupt source 

To determine the exact source of the interrupt for Cortex-M7 core, qualify the interrupt status flags with the corresponding interrupt enable fields. 

- MCM_ISCR[31:16] && MCM_ISCR[15:0] 

- Search the result for asserted flags, which indicate the exact interrupt sources. 

## 6.4 Memory map and register descriptions 

The memory map and register descriptions below describe the registers using byte addresses. 

## ~~NOTE~~ 

The following actions result in bus errors: 

- Writing to read-only registers at 0x0. 

- Reading from or writing to an address from offset 480h and above. 

- Accessing any MCM register while in User mode. These registers are only accessible while in Supervisor mode. 

## 6.4.1 MCM register descriptions 

## 6.4.1.1 MCM memory map 

MCM_0_CM7 base address: E008_0000h 

MCM_1_CM7 base address: E008_0000h 

MCM_2_CM7 base address: E008_0000h 

MCM_3_CM7 base address: E008_0000h 

|Offset|Register|Width<br>(In bits)|Access|Reset value|
|---|---|---|---|---|
|0h|Chip-Defined Platform Revision (PLREV)|16|R|0000h|
|2h|Processor Core Type (PCT)|16|R|AC70h|
|Ch|Core Platform Control (CPCR)|32|RW|0000_0200h|
|10h|Interrupt Status and Control (ISCR)|32|RW|0000_0000h|
|30h|Process Identifier (PID)|8|RW|00h|
|400h|Local Memory Descriptor 0 (LMEM_DESC_0)|32|R|8606_0000h|
|404h - 408h|Local Memory Descriptor a (LMEM_DESC_1 - LMEM_DESC_2)|32|R|8604_2000h|
|40Ch|Local Memory Descriptor 3 (LMEM_DESC_3)|32|R|8526_4000h|
|410h|Local Memory Descriptor 4 (LMEM_DESC_4)|32|R|8544_6000h|



S32K3xx Reference Manual, Rev. 12, 2025-11-11 

Reference Manual 

57 / 5394 

NXP Semiconductors 

Miscellaneous Control Module (MCM) 

## 6.4.1.2 Chip-Defined Platform Revision (PLREV) 

## Offset 

|Register|Offset|
|---|---|
|PLREV|0h|



## Function 

Specifies a chip-defined platform revision number. A platform input signal defines the state of this register; it can only be read from the IPS programming model. Any attempted write is ignored. 

## Diagram 

**==> picture [504 x 72] intentionally omitted <==**

**----- Start of picture text -----**<br>
Bits 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0<br>R PLREV<br>W<br>Reset 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0<br>**----- End of picture text -----**<br>


## Fields 

|Field|Function|
|---|---|
|15-0<br>PLREV|Defines the software-visible revision number, specified by a platform input signal.|



## 6.4.1.3 Processor Core Type (PCT) 

## Offset 

|Register|Offset|
|---|---|
|PCT|2h|



## Function 

Specifies the architecture of the processor core within the platform on the chip. A module input signal defines the state of this register, which can only be read from the IPS programming model. Any attempted write is ignored. 

S32K3xx Reference Manual, Rev. 12, 2025-11-11 

Reference Manual 

58 / 5394 

NXP Semiconductors 

Miscellaneous Control Module (MCM) 

## Diagram 

**==> picture [504 x 72] intentionally omitted <==**

**----- Start of picture text -----**<br>
Bits 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0<br>R PCT<br>W<br>Reset 1 0 1 0 1 1 0 0 0 1 1 1 0 0 0 0<br>**----- End of picture text -----**<br>


## Fields 

|Field|Function|
|---|---|
|15-0<br>PCT|Core Complex Identifier<br>Identifies the core complex. This MCM design supports the Arm Cortex M7 core.<br>1010_1100_0111_0000b - Arm Cortex-M7|



## 6.4.1.4 Core Platform Control (CPCR) 

## Offset 

|Register|Offset|
|---|---|
|CPCR|Ch|



## Function 

Defines the arbitration and protection schemes for the two system RAM arrays. 

## Diagram 

**==> picture [505 x 153] intentionally omitted <==**

**----- Start of picture text -----**<br>
Bits 31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16<br>R CM7_A<br>Reserved  Reserved<br>W HB...<br>Reset 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0<br>Bits 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0<br>Reserv Reserv<br>R Reserved<br>ed  ed<br>Reserved<br>W<br>Reset 0 0 0 0 0 0 1 0 0 0 0 0 0 0 0 0<br>**----- End of picture text -----**<br>


Fields 

|Field|Function|
|---|---|
|31-28|Reserved|



Table continues on the next page... 

S32K3xx Reference Manual, Rev. 12, 2025-11-11 

Reference Manual 

59 / 5394 

NXP Semiconductors 

Miscellaneous Control Module (MCM) 

## Table continued from the previous page... 

|Field|Function|
|---|---|
|—||
|27<br>CM7_AHBSPRI|AHB Subordinate Priority<br>Indicates the access priority on the AHBS port of the Cortex-M7 core.<br>This setting has no effect unless enabled by AHBSCR[CTL]1of the Cortex-M7 core.<br>~~NOTE~~<br>0b - Uses a round-robin arbitration scheme<br>1b - AHB-subordinate access has priority over a core access|
|26-11<br>—|Reserved|
|10<br>—|Reserved|
|9<br>—|Reserved|
|8-0<br>—|Reserved|



1. For more information see Cortex-M7 documentation: Arm Cortex-M7 Processor Technical Reference Manual at www.arm.com. 

## 6.4.1.5 Interrupt Status and Control (ISCR) 

## Offset 

|Register|Offset|
|---|---|
|ISCR|10h|



## Function 

Defines the configuration and reports the status for a number of core-related interrupt exception conditions. It includes: 

- Enable and status fields associated with the core's floating-point exceptions 

- Bus errors associated with the core's cache write buffer 

The individual event indicators are first qualified with their exception enables, and then logically summed to form an interrupt request sent to the core's NVIC. 

Bits 15-8 are read-only indicator flags based on the processor's FPSCR register. Attempted writes to these fields are ignored. When these flags are 1, they retain this value until software clears the corresponding FPSCR field. For more information see Cortex-M7 documentation: Arm Cortex-M7 Processor Technical Reference Manual at www.arm.com. 

S32K3xx Reference Manual, Rev. 12, 2025-11-11 

Reference Manual 

60 / 5394 

NXP Semiconductors 

Miscellaneous Control Module (MCM) 

## Diagram 

|Bits<br>R<br>W<br>Reset<br>Bits<br>R<br>W<br>Reset|31|30<br>29<br>28|30<br>29<br>28|27<br>26<br>25<br>24|27<br>26<br>25<br>24|27<br>26<br>25<br>24|27<br>26<br>25<br>24|23<br>22<br>21|23<br>22<br>21|23<br>22<br>21|20|19<br>18<br>17<br>16|
|---|---|---|---|---|---|---|---|---|---|---|---|---|
||FIDCE|0|FIXCE|FUFC<br>E|FOFC<br>E|FDZC<br>E|FIOCE|0||WABE|0||
||||||||||||||
||0|0<br>0<br>0||0<br>0<br>0<br>0||||0<br>0<br>0|||0|0<br>0<br>0<br>0|
||||||||||||||
||15|14<br>13<br>12||11<br>10<br>9<br>8||||7<br>6<br>5|||4|3<br>2<br>1<br>0|
||FIDC|0|FIXC|FUFC|FOFC|FDZC|FIOC|0|WABS<br>O|WABS|0||
|||||||||||W1C|||
||0|0<br>0<br>0||0<br>0<br>0<br>0||||0<br>0<br>0|||0|0<br>0<br>0<br>0|



## Fields 

|Field|Function|
|---|---|
|31<br>FIDCE|FPU Input Denormal Interrupt Enable<br>0b - Disable<br>1b - Enable|
|30-29<br>—|Reserved|
|28<br>FIXCE|FPU Inexact Interrupt Enable<br>0b - Disable<br>1b - Enable|
|27<br>FUFCE|FPU Underflow Interrupt Enable<br>0b - Disable<br>1b - Enable|
|26<br>FOFCE|FPU Overflow Interrupt Enable<br>0b - Disable<br>1b - Enable|
|25<br>FDZCE|FPU Divide-by-Zero Interrupt Enable<br>0b - Disable<br>1b - Enable|
|24<br>FIOCE|FPU Invalid Operation Interrupt Enable<br>0b - Disable<br>1b - Enable|
|23-22|Reserved|



Table continues on the next page... 

S32K3xx Reference Manual, Rev. 12, 2025-11-11 

Reference Manual 

61 / 5394 

NXP Semiconductors 

Miscellaneous Control Module (MCM) 

## Table continued from the previous page... 

|Field|Function|
|---|---|
|—||
|21<br>WABE|TCM Write Abort Interrupt Enable<br>0b - Disable<br>1b - Enable|
|20-16<br>—|Reserved|
|15<br>FIDC|FPU Input Denormal Interrupt Status<br>Indicates that an input denormalized number has been detected in the processor's FPU. This field is a<br>copy of the core's FPSCR[IDC] field. When this field is 1, it retains this value until software clears the<br>FPSCR[IDC] field.<br>0b - No interrupt<br>1b - Interrupt occurred|
|14-13<br>—|Reserved|
|12<br>FIXC|FPU Inexact Interrupt Status<br>Indicates that an inexact number has been detected in the processor's FPU. This field is a copy of the<br>core's FPSCR[IXC] field. When this field is 1, it retains this value until software clears the FPSCR[IXC]<br>field.<br>0b - No interrupt<br>1b - Interrupt occurred|
|11<br>FUFC|FPU Underflow Interrupt Status<br>Indicates that an underflow has been detected in the processor's FPU. This field is a copy of the core's<br>FPSCR[UFC] field. When this field is 1, it retains this value until software clears the FPSCR[UFC] field.<br>0b - No interrupt<br>1b - Interrupt occurred|
|10<br>FOFC|FPU Overflow Interrupt Status<br>Indicates that an overflow has been detected in the processor's FPU. This field is a copy of the core's<br>FPSCR[OFC] field. When this field is 1, it retains this value until software clears the FPSCR[OFC] field.<br>0b - No interrupt<br>1b - Interrupt occurred|
|9<br>FDZC|FPU Divide-by-Zero Interrupt Status<br>Indicates that a divide-by-zero operation has been detected in the processor's FPU. This field is a<br>copy of the core's FPSCR[DZC] field. When this field is 1, it retains this value until software clears the<br>FPSCR[DZC] field.|



Table continues on the next page... 

S32K3xx Reference Manual, Rev. 12, 2025-11-11 

Reference Manual 

62 / 5394 

NXP Semiconductors 

Miscellaneous Control Module (MCM) 

## Table continued from the previous page... 

|Field|Function|
|---|---|
||0b - No interrupt<br>1b - Interrupt occurred|
|8<br>FIOC|FPU Invalid Operation Interrupt Status<br>Indicates that an illegal operation has been detected in the processor's FPU. This field is a copy of the<br>core's FPSCR[IOC] field. When this field is 1, it retains this value until software clears the FPSCR[IOC]<br>field.<br>0b - No interrupt<br>1b - Interrupt occurred|
|7<br>—|Reserved|
|6<br>WABSO|Write Abort on Subordinate Overrun<br>Indicates whether an abort overrun has occurred. The overrun conditions are reported only if WABE=1.<br>0b - No write abort overrun<br>1b - Write abort overrun occurred|
|5<br>WABS|Write Abort on Subordinate<br>Indicates when a write abort has occurred on the AHBS interface.<br>0b - No write abort occurred on AHBS interface<br>1b - Write abort occurred on AHBS interface|
|4-0<br>—|Reserved|



## 6.4.1.6 Process Identifier (PID) 

## Offset 

|Register|Offset|
|---|---|
|PID|30h|



## Function 

Contains the CPU process ID. 

S32K3xx Reference Manual, Rev. 12, 2025-11-11 

Reference Manual 

63 / 5394 

NXP Semiconductors 

Miscellaneous Control Module (MCM) 

## Diagram 

|Diagram|||
|---|---|---|
|Bits<br>R<br>W<br>Reset|7<br>6<br>5<br>4|3<br>2<br>1<br>0|
||PID||
||0<br>0<br>0<br>0|0<br>0<br>0<br>0|



## Fields 

|Field|Function|
|---|---|
|7-0<br>PID|Process Identifier<br>Identifies the CPU process.|



## 6.4.1.7 Local Memory Descriptor 0 (LMEM_DESC_0) 

## Offset 

|Register|Offset|
|---|---|
|LMEM_DESC_0|400h|



## Function 

~~NOTE~~ The DESC_a registers map to the LMEMs in this way: • DESC_0: ITCM • DESC_1: D0TCM • DESC_2: D1TCM • DESC_3: I-cache • DESC_4: D-cache 

~~NOTE~~ 

You can read and write to the reserved fields (instead of read as zero and write ignored). Writing to any of these fields has no functional impact. 

S32K3xx Reference Manual, Rev. 12, 2025-11-11 

Reference Manual 

64 / 5394 

NXP Semiconductors 

Miscellaneous Control Module (MCM) 

## Diagram 

|Bits<br>R<br>W<br>Reset<br>Bits<br>R<br>W<br>Reset|31<br>30<br>29|31<br>30<br>29|28|27<br>26<br>25<br>24|23<br>22<br>21<br>20|19<br>18<br>17<br>16|19<br>18<br>17<br>16|19<br>18<br>17<br>16|
|---|---|---|---|---|---|---|---|---|
||LMV|Reserved|LMSZ<br>H|LMSZ|WY|DPW||Reserv<br>ed|
||||||||||
||1<br>0<br>0||0|0<br>1<br>1<br>0|0<br>0<br>0<br>0|0<br>1<br>1<br>0|||
||||||||||
||15<br>14<br>13||12|11<br>10<br>9<br>8|7<br>6<br>5<br>4|3<br>2<br>1<br>0|||
||MT||Reserved|||Reserved|Reserved||
||||||||||
||0<br>0<br>0||0|0<br>0<br>0<br>0|0<br>0<br>0<br>0|0<br>0<br>0<br>0|||



## Fields 

|Field|Function|
|---|---|
|31<br>LMV|Local Memory Valid<br>Defines the validity (presence) of the local memory.<br>0b - LMEMn not present<br>1b - LMEMn present|
|30-29<br>—|Reserved|
|28<br>LMSZH|LMEM Size Hole<br>Used for local memories that are not fully populated (that is, local memories that include a memory "hole"<br>in the upper 25 % of the address range).<br>0b - LMEMn is a power-of-2 capacity<br>1b - LMEMn is not a power-of-2, with capacity of 0.75 × LMSZ|
|27-24<br>LMSZ|Local Memory Size<br>Indicates the local memory size.<br>0000b - 0 KB<br>0001b - 1 KB<br>0010b - 2 KB<br>0011b - 4 KB<br>0100b - 8 KB<br>0101b - 16 KB<br>0110b - 32 KB<br>0111b - 64 KB<br>1000b - 128 KB|



Table continues on the next page... 

S32K3xx Reference Manual, Rev. 12, 2025-11-11 

Reference Manual 

65 / 5394 

NXP Semiconductors 

Miscellaneous Control Module (MCM) 

## Table continued from the previous page... 

|Field|Function|
|---|---|
||1001b - 256 KB<br>1010b - 512 KB<br>1011b - 1024 KB<br>1100b - 2048 KB<br>1101b - 4096 KB<br>1110b - 8192 KB<br>1111b - 16384 KB|
|23-20<br>WY|Level 1 Cache Ways<br>Defines the level 1 cache ways.<br>0000b - No cache<br>0010b - 2-way set associative<br>0100b - 4-way set associative|
|19-17<br>DPW|Data Path Width<br>Defines the LMEMn data path width, which is the width of the local memory.<br>000b-001b - Reserved<br>010b - 32 bits<br>011b - 64 bits<br>100b-111b - Reserved|
|16<br>—|Reserved|
|15-13<br>MT|Memory Type<br>Defines the memory type.<br>000b - ITCM<br>001b - DTCM<br>010b - I-cache<br>011b - D-cache|
|12-4<br>—|Reserved|
|3-2<br>—|Reserved|
|1-0|Reserved|



Table continues on the next page... 

S32K3xx Reference Manual, Rev. 12, 2025-11-11 

Reference Manual 

66 / 5394 

NXP Semiconductors 

Miscellaneous Control Module (MCM) 

## Table continued from the previous page... 

|Field|Function|
|---|---|
|—||



## 6.4.1.8 Local Memory Descriptor a (LMEM_DESC_1 - LMEM_DESC_2) 

## Offset 

|Register|Offset|
|---|---|
|LMEM_DESC_1|404h|
|LMEM_DESC_2|408h|



## Function 

## ~~NOTE~~ 

The DESC_a registers map to the LMEMs in this way: 

- DESC_0: ITCM 

- DESC_1: D0TCM 

- DESC_2: D1TCM 

- DESC_3: I-cache 

- DESC_4: D-cache 

~~NOTE~~ 

You can read and write to the reserved fields (instead of read as zero and write ignored). Writing to any of these fields has no functional impact. 

## Diagram 

**==> picture [504 x 155] intentionally omitted <==**

**----- Start of picture text -----**<br>
Bits 31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16<br>LMSZ<br>R LMV  LMSZ  WY  DPW<br>H  Reserv<br>Reserved<br>ed<br>W<br>Reset 1 0 0 0 0 1 1 0 0 0 0 0 0 1 0 0<br>Bits 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0<br>R MT  Reserved<br>Reserved  Reserved<br>W<br>Reset 0 0 1 0 0 0 0 0 0 0 0 0 0 0 0 0<br>**----- End of picture text -----**<br>


S32K3xx Reference Manual, Rev. 12, 2025-11-11 

Reference Manual 

67 / 5394 

NXP Semiconductors 

Miscellaneous Control Module (MCM) 

## Fields 

|Field|Function|
|---|---|
|31<br>LMV|Local Memory Valid<br>Defines the validity (presence) of the local memory.<br>0b - LMEMn not present<br>1b - LMEMn present|
|30-29<br>—|Reserved|
|28<br>LMSZH|LMEM Size Hole<br>Used for local memories that are not fully populated (that is, local memories that include a memory "hole"<br>in the upper 25 % of the address range).<br>0b - LMEMn is a power-of-2 capacity<br>1b - LMEMn is not a power-of-2, with capacity of 0.75 × LMSZ|
|27-24<br>LMSZ|Local Memory Size<br>Indicates the local memory size.<br>0000b - 0 KB<br>0001b - 1 KB<br>0010b - 2 KB<br>0011b - 4 KB<br>0100b - 8 KB<br>0101b - 16 KB<br>0110b - 32 KB<br>0111b - 64 KB<br>1000b - 128 KB<br>1001b - 256 KB<br>1010b - 512 KB<br>1011b - 1024 KB<br>1100b - 2048 KB<br>1101b - 4096 KB<br>1110b - 8192 KB<br>1111b - 16384 KB|
|23-20<br>WY|Level 1 Cache Ways<br>Defines the level 1 cache ways.<br>0000b - No cache|



Table continues on the next page... 

S32K3xx Reference Manual, Rev. 12, 2025-11-11 

Reference Manual 

68 / 5394 

NXP Semiconductors 

Miscellaneous Control Module (MCM) 

## Table continued from the previous page... 

|Field|Function|
|---|---|
||0010b - 2-way set associative<br>0100b - 4-way set associative|
|19-17<br>DPW|Data Path Width<br>Defines the LMEMn data path width, which is the width of the local memory.<br>000b-001b - Reserved<br>010b - 32 bits<br>011b - 64 bits<br>100b-111b - Reserved|
|16<br>—|Reserved|
|15-13<br>MT|Memory Type<br>Defines the memory type.<br>000b - ITCM<br>001b - DTCM<br>010b - I-cache<br>011b - D-cache|
|12-4<br>—|Reserved|
|3-2<br>—|Reserved|
|1-0<br>—|Reserved|



## 6.4.1.9 Local Memory Descriptor 3 (LMEM_DESC_3) 

## Offset 

|Register|Offset|
|---|---|
|LMEM_DESC_3|40Ch|



S32K3xx Reference Manual, Rev. 12, 2025-11-11 

Reference Manual 

69 / 5394 

NXP Semiconductors 

Miscellaneous Control Module (MCM) 

## Function 

## ~~NOTE~~ 

The DESC_a registers map to the LMEMs in this way: 

- DESC_0: ITCM 

- DESC_1: D0TCM 

- DESC_2: D1TCM 

- DESC_3: I-cache 

- DESC_4: D-cache 

## ~~NOTE~~ 

You can read and write to the reserved fields (instead of read as zero and write ignored). Writing to any of these fields has no functional impact. 

## Diagram 

|Bits<br>R<br>W<br>Reset<br>Bits<br>R<br>W<br>Reset|31<br>30<br>29|31<br>30<br>29|28|27<br>26<br>25<br>24|23<br>22<br>21<br>20|19<br>18<br>17<br>16|19<br>18<br>17<br>16|19<br>18<br>17<br>16|
|---|---|---|---|---|---|---|---|---|
||LMV|Reserved|LMSZ<br>H|LMSZ|WY|DPW||Reserv<br>ed|
||||||||||
||1<br>0<br>0||0|0<br>1<br>0<br>1|0<br>0<br>1<br>0|0<br>1<br>1<br>0|||
||||||||||
||15<br>14<br>13||12|11<br>10<br>9<br>8|7<br>6<br>5<br>4|3<br>2<br>1<br>0|||
||MT||Reserved|||Reserved|Reserved||
||||||||||
||0<br>1<br>0||0|0<br>0<br>0<br>0|0<br>0<br>0<br>0|0<br>0<br>0<br>0|||



## Fields 

|Field|Function|
|---|---|
|31<br>LMV|Local Memory Valid<br>Defines the validity (presence) of the local memory.<br>0b - LMEMn not present<br>1b - LMEMn present|
|30-29<br>—|Reserved|
|28<br>LMSZH|LMEM Size Hole<br>Used for local memories that are not fully populated (that is, local memories that include a memory "hole"<br>in the upper 25 % of the address range).<br>0b - LMEMn is a power-of-2 capacity<br>1b - LMEMn is not a power-of-2, with capacity of 0.75 × LMSZ|



Table continues on the next page... 

S32K3xx Reference Manual, Rev. 12, 2025-11-11 

Reference Manual 

70 / 5394 

NXP Semiconductors 

Miscellaneous Control Module (MCM) 

## Table continued from the previous page... 

|Field|Function|
|---|---|
|27-24<br>LMSZ|Local Memory Size<br>Indicates the local memory size.<br>0000b - 0 KB<br>0001b - 1 KB<br>0010b - 2 KB<br>0011b - 4 KB<br>0100b - 8 KB<br>0101b - 16 KB<br>0110b - 32 KB<br>0111b - 64 KB<br>1000b - 128 KB<br>1001b - 256 KB<br>1010b - 512 KB<br>1011b - 1024 KB<br>1100b - 2048 KB<br>1101b - 4096 KB<br>1110b - 8192 KB<br>1111b - 16384 KB|
|23-20<br>WY|Level 1 Cache Ways<br>Defines the level 1 cache ways.<br>0000b - No cache<br>0010b - 2-way set associative<br>0100b - 4-way set associative|
|19-17<br>DPW|Data Path Width<br>Defines the LMEMn data path width, which is the width of the local memory.<br>000b-001b - Reserved<br>010b - 32 bits<br>011b - 64 bits<br>100b-111b - Reserved|
|16<br>—|Reserved|
|15-13|Memory Type|



Table continues on the next page... 

S32K3xx Reference Manual, Rev. 12, 2025-11-11 

Reference Manual 

71 / 5394 

NXP Semiconductors 

Miscellaneous Control Module (MCM) 

## Table continued from the previous page... 

|Field|Function|
|---|---|
|MT|Defines the memory type.<br>000b - ITCM<br>001b - DTCM<br>010b - I-cache<br>011b - D-cache|
|12-4<br>—|Reserved|
|3-2<br>—|Reserved|
|1-0<br>—|Reserved|



## 6.4.1.10 Local Memory Descriptor 4 (LMEM_DESC_4) 

## Offset 

|Register|Offset|
|---|---|
|LMEM_DESC_4|410h|



## Function 

## ~~NOTE~~ 

The DESC_a registers map to the LMEMs in this way: 

- DESC_0: ITCM 

- DESC_1: D0TCM 

- DESC_2: D1TCM 

- DESC_3: I-cache 

- DESC_4: D-cache 

## ~~NOTE~~ 

You can read and write to the reserved fields (instead of read as zero and write ignored). Writing to any of these fields has no functional impact. 

S32K3xx Reference Manual, Rev. 12, 2025-11-11 

Reference Manual 

72 / 5394 

NXP Semiconductors 

Miscellaneous Control Module (MCM) 

## Diagram 

|Bits<br>R<br>W<br>Reset<br>Bits<br>R<br>W<br>Reset|31<br>30<br>29|31<br>30<br>29|28|27<br>26<br>25<br>24|23<br>22<br>21<br>20|19<br>18<br>17<br>16|19<br>18<br>17<br>16|19<br>18<br>17<br>16|
|---|---|---|---|---|---|---|---|---|
||LMV|Reserved|LMSZ<br>H|LMSZ|WY|DPW||Reserv<br>ed|
||||||||||
||1<br>0<br>0||0|0<br>1<br>0<br>1|0<br>1<br>0<br>0|0<br>1<br>0<br>0|||
||||||||||
||15<br>14<br>13||12|11<br>10<br>9<br>8|7<br>6<br>5<br>4|3<br>2<br>1<br>0|||
||MT||Reserved|||Reserved|Reserved||
||||||||||
||0<br>1<br>1||0|0<br>0<br>0<br>0|0<br>0<br>0<br>0|0<br>0<br>0<br>0|||



## Fields 

|Field|Function|
|---|---|
|31<br>LMV|Local Memory Valid<br>Defines the validity (presence) of the local memory.<br>0b - LMEMn not present<br>1b - LMEMn present|
|30-29<br>—|Reserved|
|28<br>LMSZH|LMEM Size Hole<br>Used for local memories that are not fully populated (that is, local memories that include a memory "hole"<br>in the upper 25 % of the address range).<br>0b - LMEMn is a power-of-2 capacity<br>1b - LMEMn is not a power-of-2, with capacity of 0.75 × LMSZ|
|27-24<br>LMSZ|Local Memory Size<br>Indicates the local memory size.<br>0000b - 0 KB<br>0001b - 1 KB<br>0010b - 2 KB<br>0011b - 4 KB<br>0100b - 8 KB<br>0101b - 16 KB<br>0110b - 32 KB<br>0111b - 64 KB<br>1000b - 128 KB|



Table continues on the next page... 

S32K3xx Reference Manual, Rev. 12, 2025-11-11 

Reference Manual 

73 / 5394 

NXP Semiconductors 

Miscellaneous Control Module (MCM) 

## Table continued from the previous page... 

|Field|Function|
|---|---|
||1001b - 256 KB<br>1010b - 512 KB<br>1011b - 1024 KB<br>1100b - 2048 KB<br>1101b - 4096 KB<br>1110b - 8192 KB<br>1111b - 16384 KB|
|23-20<br>WY|Level 1 Cache Ways<br>Defines the level 1 cache ways.<br>0000b - No cache<br>0010b - 2-way set associative<br>0100b - 4-way set associative|
|19-17<br>DPW|Data Path Width<br>Defines the LMEMn data path width, which is the width of the local memory.<br>000b-001b - Reserved<br>010b - 32 bits<br>011b - 64 bits<br>100b-111b - Reserved|
|16<br>—|Reserved|
|15-13<br>MT|Memory Type<br>Defines the memory type.<br>000b - ITCM<br>001b - DTCM<br>010b - I-cache<br>011b - D-cache|
|12-4<br>—|Reserved|
|3-2<br>—|Reserved|
|1-0|Reserved|



Table continues on the next page... 

S32K3xx Reference Manual, Rev. 12, 2025-11-11 

Reference Manual 

74 / 5394 

NXP Semiconductors 

Miscellaneous Control Module (MCM) 

Table continued from the previous page... 

|Field|Function|
|---|---|
|—||



## 6.5 Glossary 

ITCM Instruction Tightly-Coupled Memory DTCM Data Tightly Coupled Memory I-cache Instruction Cache Memory D-cache Data Cache Memory 

S32K3xx Reference Manual, Rev. 12, 2025-11-11 

Reference Manual 

75 / 5394 

NXP Semiconductors 

## Chapter 7 Miscellaneous System Control Module (MSCM) 

## 7.1 Chip-specific MSCM information 

## 7.1.1 MSCM instance 

This chip has one instance of MSCM. 

~~NOTE~~ 

The XN_CTRL register is used to restrict execution from SRAM, including TCMs and their backdoors, which will be permanent until next device reset, while still allowing data R/W. 

XN_CTRL register is reserved for S32K344/S32K324/S32K314. 

## 7.1.2 Reporting of core-to-core interrupts 

For all the variants the core-to-core interrupts are reported to both INTM and MSCM for CM7_0 and CM7_1. But, for CM7_2 the core-to-core interrupts are reported to MSCM, instead of INTM. See the interrupt map file attached to this document for details. 

## 7.1.3 ENEDC register implementation 

In S32K310, S32K311, S32K312, S32K314, S32K322, S32K324, S32K341, S32K342, and S32K344 there are additional bit field as compared to what is mentioned in section 'MSCM memory map'. See following table for details. 

Table 33. Bitfield details 

|Bitfield name|Bitfield position|
|---|---|
|ENEDC[EN_WR_TCM]1|16|
|ENEDC[EN_ADD_TCM]1|17|



1. See section EN_WR_TCM and EN_ADD_TCM definition for details 

## 7.1.3.1 EN_WR_TCM and EN_ADD_TCM definition 

Register ENEDC has the following additional bitfields: 

Table 34. Bitfield definition 

|Bitfield position|Bitfield name|Bitfield description|
|---|---|---|
|16|EN_WR_TCM (Enable<br>Write Data Check TCM)|Enables or disables the write data check for TCM 64-bit path.<br>• 0b-Disabled<br>• 1b-Enabled|
|17|EN_ADD_TCM (Enable<br>Address Check TCM)|Enables or disables the address check for TCM 64-bit path.<br>• 0b-Disabled<br>• 1b-Enabled|



## 7.1.4 ENEDC and ENEDC1 register implementation for S32K358, S32K356, S32K348, S32K338, and S32K328 

In S32K358, S32K356, S32K348, S32K338, and S32K328 there are some differences in register[bit field] as compared to what is mentioned in section 'MSCM memory map'. See following table for details. 

S32K3xx Reference Manual, Rev. 12, 2025-11-11 

Reference Manual 

76 / 5394 

NXP Semiconductors 

Miscellaneous System Control Module (MSCM) 

## Table 35. Bitfield details 

|Register[Bitfield name]|Bitfield position|
|---|---|
|ENEDC[ADD_TCM_BACKDOOR]|17|
|ENEDC1[CM7_3_WDATA_CHK]1|12|
|ENEDC1[CM7_3_ADDR_CHK]1|13|
|ENEDC1[USDHC]|16|
|ENEDC1[CM7_3_AHBM]1|17|
|ENEDC1[CM7_3_AHBP]1|18|
|ENEDC1[MSTR_CHK_ACE_RESULT_CHK]1|19|
|ENEDC1[MSTR_CHK_ACE_FEED_CHK]1|20|
|ENEDC1[SLV_CHK_ACE_ADDR_CHK]1|21|
|ENEDC1[SLV_CHK_ACE_ACCEL_RESULT_M1_GSKT_WDATA_CHK]1|22|
|ENEDC1[SLV_CHK_ACE_ACCEL_RESULT_M1_GSKT_ADDR_CHK]1|23|
|ENEDC1[TCM_GSKT_ADDR_CHK]1|24|



1. This field is Reserved for S32K358, S32K356, S32K348, S32K338, and S32K328. 

## 7.1.4.1 ENEDC[ADD_TCM_BACKDOOR] and ENEDC1 [USDHC] definition 

In S32K358, S32K356, S32K348, S32K338, and S32K328 ENEDC register has the following additional bitfields: 

Table 36. Bitfield definition 

|Bitfield position|Bitfield name|Bitfield description|
|---|---|---|
|17|ADD_TCM_BACKDOOR (Write Data<br>Check For TCM Backdoor)|Enables or disables the address check<br>for the TCM backdoor path.<br>• 0b-Disabled<br>• 1b-Enabled|



In S32K358, S32K356, S32K348, S32K338, and S32K328 ENEDC1 register has the following additional bitfields: 

## Table 37. Bitfield definition 

|Bitfield position|Bitfield name|Bitfield description|
|---|---|---|
|16|USDHC (Enable Read Data<br>Check uSDHC)|Enables or disables the read data check<br>for the uSDHC path.<br>• 0b-Disabled<br>• 1b-Enabled|



## 7.2 Overview 

MSCM contains registers for: 

- CPU configuration 

- On-chip memory control 

- Interrupt router control 

S32K3xx Reference Manual, Rev. 12, 2025-11-11 

Reference Manual 

77 / 5394 

NXP Semiconductors 

Miscellaneous System Control Module (MSCM) 

- Message-based interrupt configuration 

- Virtual management 

## 7.2.1 Features 

- Software-accessible processor core configuration information 

- Support for interrupt router control 

- Support for message-based interrupt configuration 

## 7.3 Functional description 

MSCM provides information of the system cores and can identify the core that is running currently. 

## 7.3.1 MSI routing 

MSIs are interrupts that are indirectly broadcast to a target core by writing configuration bits in MSCM. These MSIs can be initiated by one core targeting another core in the system (known as core-to-core interrupts). These MSIs are initiated via writes to Interrupt Router CPn Interrupt Generation (IRCP0IGR0 - IRCP3IGR3) and managed through Interrupt Router CPn Interrupt Status (IRCP0ISR0 - IRCP3ISR3). The Cortex-M7 cores can support up to four outstanding core-to-core interrupts. 

**==> picture [434 x 142] intentionally omitted <==**

**----- Start of picture text -----**<br>
CPn Core-to-Core Int0 CPn Core-to-Core Int1<br>IRCP nlGR0 IRCP nlGR1<br>IRCP nlSR0 IRCP nlSR1<br>CPn Core-to-Core Int2 CPn Core-to-Core Int3<br>IRCP nlGR2 IRCP nlGR3<br>IRCP nlSR2 IRCP nlSR3<br>int_en int_en<br>cp1_int cp0_int cp1_int cp0_int<br>int_en int0_en<br>cp1_int cp0_int cp1_int cp0_int<br>**----- End of picture text -----**<br>


Figure 16. IRCPnIGRm/IRCPnISRm pairs for one core 

**==> picture [448 x 175] intentionally omitted <==**

**----- Start of picture text -----**<br>
CPn Core-to-Core Int0 CPn Core-to-Core Int1<br>IRCP nlGR0 IRCP nlGR1<br>IRCP nlSR0 IRCP nlSR1<br>CPn Core-to-Core Int2 CPn Core-to-Core Int3<br>IRCP nlGR2 IRCP nlGR3<br>IRCP nlSR2 IRCP nlSR3<br>CP0<br>CP1<br>Figure 17. IRCPnIGRm/IRCPnISRm pairs per core<br>int_en int_en<br>cp1_int cp0_int cp1_int cp0_int<br>int_en int0_en<br>cp1_int cp0_int cp1_int cp0_int<br>**----- End of picture text -----**<br>


S32K3xx Reference Manual, Rev. 12, 2025-11-11 

Reference Manual 

78 / 5394 

NXP Semiconductors 

Miscellaneous System Control Module (MSCM) 

## 7.3.1.1 Core-to-core MSIs 

The next figure depicts the sequence for initiating a core-to-core MSI, in which m represents the initiating core, n represents the target core, and x indicates the MSI number. CPm writes to IRCPnIGRx to initiate an MSI. The outstanding MSI that CPm initiates, targeting CPn, is reflected in the corresponding bit-mapped field in IRCPnISRx. 

**==> picture [435 x 172] intentionally omitted <==**

**----- Start of picture text -----**<br>
CPm writes to<br>wr 1<br>IRCP n IGR x IRCPnlGRx to generate<br>core-to-core<br>interrupt to CPn<br>CP m  masterID<br>IRCP n ISR x<br>Figure 18. Initiating a core-to-core MSI via IRCPnIGRx/IRCPnISRx<br>int_en<br>int<br>_<br>1<br>pc cp0_int<br>**----- End of picture text -----**<br>


## 7.3.2 Interrupt steering and semaphores 

## 7.3.2.1 Interrupt handling overview 

The interrupt handling mechanisms of the Cortex-M7 cores are very similar. These cores have an NVIC tightly coupled to the processor core. The real-time performance of the cores means the NVIC directly provides an appropriate interrupt vector, in the form of the starting instruction address for the interrupt service routine, to the core. These core architectural features directly translate into a faster ISR entry and exit capabilities, coupled with an improved runtime performance. See the Arm modules and Arm core technical reference manuals for details. 

In this architecture, a total of 240 IRQs are supported, where this parameter is defined by the realistic limits of the NVIC implementation, both in terms of silicon size and supported frequency of operation. These 240 IRQs are split into a total of four directed requests and 236 shared peripheral requests. Unless noted otherwise, let the directed requests be defined as IRQ[3:0] and the shared peripheral requests as IRQ[239:4]. See the interrupt map file attached to this document for details. 

## 7.3.2.2 MSCM interrupt router functional description 

As described in MSCM register descriptions, the interrupt routing registers enable the steering of requests to the processor cores. 

## 7.3.3 Clocking 

This module has no clocking considerations. 

## 7.4 External signals 

This module has no external signals. 

## 7.5 Initialization 

This module does not require initialization. 

## 7.6 Memory map and register definition 

S32K3xx Reference Manual, Rev. 12, 2025-11-11 

Reference Manual 

79 / 5394 

NXP Semiconductors 

Miscellaneous System Control Module (MSCM) 

## 7.6.1 Core configuration registers 

These read-only registers contain data that defines the core setup for this chip. You can access the registers using 32-bit read references; other access sizes terminate with an error. Attempted write accesses to the read-only core configuration registers also terminate with an error. 

The core configuration portion of the MSCM programming model map is organized based on the logical core number, and not on any type of physical port number. The following table shows how the configuration is partitioned. 

Table 38. MSCM core configuration partitioning 

|Offset address<br>range|Purpose|
|---|---|
|0h–018h|Defines the generic core x configuration information. Only the MSCM associated controllers can access<br>this region in either User or Privileged mode; reads by noncore bus controllers (including the debugger)<br>are treated as read as zero (RAZ) accesses. Write attempts are not permitted and terminate with a system<br>bus error.|
|020h–038h|Defines the configuration information for core 0 (CP0). Any bus controller can access this region in either User<br>or Privileged mode. Write attempts are not permitted and terminate with a system bus error.|
|040h–058h|Defines the configuration information for core 1 (CP1). A bus controller can access this region in either User<br>or Privileged mode. Write attempts are not permitted and terminate with a system bus error.|
|060h–078h|Defines the configuration information for core 2 (CP2). Any bus controller can access this region in either User<br>or Privileged mode. Write attempts are not permitted and terminate with a system bus error.|
|080h–098h|Defines the configuration information for core 3 (CP3). Any bus controller can access this region in either User<br>or Privileged mode. Write attempts are not permitted and terminate with a system bus error.|



~~NOTE~~ 

Attempted accesses to reserved locations are not permitted and terminate with a system bus error. 

## 7.6.2 Shared peripheral interrupt (SPI) routing 

The SPI router portion of MSCM provides a set of memory-mapped registers defining the interrupt routing for all the SPIs on this chip. 

## 7.6.3 MSCM register descriptions 

## 7.6.3.1 MSCM memory map 

MSCM base address: 4026_0000h 

|Offset|Register|Width<br>(In bits)|Access|Reset value|
|---|---|---|---|---|
|0h|Processor X Type (CPXTYPE)|32|R|See section|
|4h|Processor X Number (CPXNUM)|32|R|See section|
|8h|Processor X Revision (CPXREV)|32|R|See section|
|Ch|Processor X Configuration 0 (CPXCFG0)|32|R|0602_0604h|
|10h|Processor X Configuration 1 (CPXCFG1)|32|R|See section|



Table continues on the next page... 

S32K3xx Reference Manual, Rev. 12, 2025-11-11 

Reference Manual 

80 / 5394 

NXP Semiconductors 

Miscellaneous System Control Module (MSCM) 

## Table continued from the previous page... 

|Offset|Register|Width<br>(In bits)|Access|Reset value|
|---|---|---|---|---|
|14h|Processor X Configuration 2 (CPXCFG2)|32|R|See section|
|18h|Processor X Configuration 3 (CPXCFG3)|32|R|0000_000Bh|
|20h|Processor 0 Type (CP0TYPE)|32|R|434D_3730h|
|24h|Processor 0 Number (CP0NUM)|32|R|See section|
|28h|Processor 0 Count (CP0REV)|32|R|See section|
|2Ch|Processor 0 Configuration 0 (CP0CFG0)|32|R|0502_0504h|
|30h|Processor 0 Configuration 1 (CP0CFG1)|32|R|0000_0000h|
|34h|Processor 0 Configuration 2 (CP0CFG2)|32|R|See section|
|38h|Processor 0 Configuration 3 (CP0CFG3)|32|R|0000_000Bh|
|40h|Processor 1 Type (CP1TYPE)|32|R|434D_3731h|
|44h|Processor 1 Number (CP1NUM)|32|R|0000_0001h|
|48h|Processor 1 Count (CP1REV)|32|R|See section|
|4Ch|Processor 1 Configuration 0 (CP1CFG0)|32|R|0502_0504h|
|50h|Processor 1 Configuration 1 (CP1CFG1)|32|R|See section|
|54h|Processor 1 Configuration 2 (CP1CFG2)|32|R|See section|
|58h|Processor 1 Configuration 3 (CP1CFG3)|32|R|0000_000Bh|
|60h|Processor 2 Type (CP2TYPE)|32|R|434D_3732h|
|64h|Processor 2 Number (CP2NUM)|32|R|0000_0002h|
|68h|Processor 2 Count (CP2REV)|32|R|See section|
|6Ch|Processor 2 Configuration 0 (CP2CFG0)|32|R|0602_0604h|
|70h|Processor 2 Configuration 1 (CP2CFG1)|32|R|See section|
|74h|Processor 2 Configuration 2 (CP2CFG2)|32|R|See section|
|78h|Processor 2 Configuration 3 (CP2CFG3)|32|R|0000_000Bh|
|80h|Processor 3 Type (CP3TYPE)|32|R|434D_3733h|
|84h|Processor 3 Number (CP3NUM)|32|R|0000_0003h|
|88h|Processor 3 Count (CP3REV)|32|R|See section|
|8Ch|Processor 3 Configuration 0 (CP3CFG0)|32|R|0602_0604h|
|90h|Processor 3 Configuration 1 (CP3CFG1)|32|R|See section|
|94h|Processor 3 Configuration 2 (CP3CFG2)|32|R|See section|
|98h|Processor 3 Configuration 3 (CP3CFG3)|32|R|0000_000Bh|
|200h|Interrupt Router CP0 Interrupt Status (IRCP0ISR0)|32|RW|0000_0000h|



Table continues on the next page... 

S32K3xx Reference Manual, Rev. 12, 2025-11-11 

Reference Manual 

81 / 5394 

NXP Semiconductors 

Miscellaneous System Control Module (MSCM) 

## Table continued from the previous page... 

|Offset|Register|Width<br>(In bits)|Access|Reset value|
|---|---|---|---|---|
|204h|Interrupt Router CP0 Interrupt Generation (IRCP0IGR0)|32|RW|0000_0000h|
|208h|Interrupt Router CP0 Interrupt Status (IRCP0ISR1)|32|RW|0000_0000h|
|20Ch|Interrupt Router CP0 Interrupt Generation (IRCP0IGR1)|32|RW|0000_0000h|
|210h|Interrupt Router CP0 Interrupt Status (IRCP0ISR2)|32|RW|0000_0000h|
|214h|Interrupt Router CP0 Interrupt Generation (IRCP0IGR2)|32|RW|0000_0000h|
|218h|Interrupt Router CP0 Interrupt Status (IRCP0ISR3)|32|RW|0000_0000h|
|21Ch|Interrupt Router CP0 Interrupt Generation (IRCP0IGR3)|32|RW|0000_0000h|
|220h|Interrupt Router CP1 Interrupt Status (IRCP1ISR0)|32|RW|0000_0000h|
|224h|Interrupt Router CP1 Interrupt Generation (IRCP1IGR0)|32|RW|0000_0000h|
|228h|Interrupt Router CP1 Interrupt Status (IRCP1ISR1)|32|RW|0000_0000h|
|22Ch|Interrupt Router CP1 Interrupt Generation (IRCP1IGR1)|32|RW|0000_0000h|
|230h|Interrupt Router CP1 Interrupt Status (IRCP1ISR2)|32|RW|0000_0000h|
|234h|Interrupt Router CP1 Interrupt Generation (IRCP1IGR2)|32|RW|0000_0000h|
|238h|Interrupt Router CP1 Interrupt Status (IRCP1ISR3)|32|RW|0000_0000h|
|23Ch|Interrupt Router CP1 Interrupt Generation (IRCP1IGR3)|32|RW|0000_0000h|
|240h|Interrupt Router CP2 Interrupt Status (IRCP2ISR0)|32|RW|0000_0000h|
|244h|Interrupt Router CP2 Interrupt Generation (IRCP2IGR0)|32|RW|0000_0000h|
|248h|Interrupt Router CP2 Interrupt Status (IRCP2ISR1)|32|RW|0000_0000h|
|24Ch|Interrupt Router CP2 Interrupt Generation (IRCP2IGR1)|32|RW|0000_0000h|
|250h|Interrupt Router CP2 Interrupt Status (IRCP2ISR2)|32|RW|0000_0000h|
|254h|Interrupt Router CP2 Interrupt Generation (IRCP2IGR2)|32|RW|0000_0000h|
|258h|Interrupt Router CP2 Interrupt Status (IRCP2ISR3)|32|RW|0000_0000h|
|25Ch|Interrupt Router CP2 Interrupt Generation (IRCP2IGR3)|32|RW|0000_0000h|
|260h|Interrupt Router CP3 Interrupt Status (IRCP3ISR0)|32|RW|0000_0000h|
|264h|Interrupt Router CP3 Interrupt Generation (IRCP3IGR0)|32|RW|0000_0000h|
|268h|Interrupt Router CP3 Interrupt Status (IRCP3ISR1)|32|RW|0000_0000h|
|26Ch|Interrupt Router CP3 Interrupt Generation (IRCP3IGR1)|32|RW|0000_0000h|
|270h|Interrupt Router CP3 Interrupt Status (IRCP3ISR2)|32|RW|0000_0000h|
|274h|Interrupt Router CP3 Interrupt Generation (IRCP3IGR2)|32|RW|0000_0000h|
|278h|Interrupt Router CP3 Interrupt Status (IRCP3ISR3)|32|RW|0000_0000h|
|27Ch|Interrupt Router CP3 Interrupt Generation (IRCP3IGR3)|32|RW|0000_0000h|



Table continues on the next page... 

S32K3xx Reference Manual, Rev. 12, 2025-11-11 

Reference Manual 

82 / 5394 

NXP Semiconductors 

Miscellaneous System Control Module (MSCM) 

## Table continued from the previous page... 

|Offset|Register|Width<br>(In bits)|Access|Reset value|
|---|---|---|---|---|
|400h|Interrupt Router Configuration (IRCPCFG)|32|RW|0000_0000h|
|500h|Memory Execution Controls (XN_CTRL)|32|RW|4000_0000h|
|600h|Enable Interconnect Error Detection (ENEDC)|32|RW|0000_0000h|
|604h|Enable Interconnect Error Detection (ENEDC1)|32|RW|0000_0000h|
|700h|AHB Gasket Configuration (IAHBCFGREG)|32|RW|0000_0000h|
|880h - A5Eh|Interrupt Router Shared Peripheral Routing Control (IRSPRC0 -<br>IRSPRC239)|16|RW|000Fh|



## 7.6.3.2 Processor X Type (CPXTYPE) 

## Offset 

|Register|Offset|
|---|---|
|CPXTYPE|0h|



## Function 

Provides a CPU-specific response indicating the personality of the core making the access. The 32-bit response includes four ASCII characters defining the CPU type (Cortex-M7 cores) along with a byte defining the logical revision number and a byte defining the instance number of the core. 

A read from Cortex-M7 returns the appropriate processor information. Reads from any other bus controller return all 0s and attempted write accesses terminate with an error. 

Access: User or privileged read-only 

## Diagram 

**==> picture [504 x 148] intentionally omitted <==**

**----- Start of picture text -----**<br>
Bits 31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16<br>R PERSONALITY<br>W<br>Reset u u u u u u u u u u u u u u u u<br>Bits 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0<br>R PERSONALITY<br>W<br>Reset u u u u u u u u u u u u u u u u<br>**----- End of picture text -----**<br>


S32K3xx Reference Manual, Rev. 12, 2025-11-11 

Reference Manual 

83 / 5394 

NXP Semiconductors 

Miscellaneous System Control Module (MSCM) 

## Fields 

|Field|Function|Function|
|---|---|---|
|31-0<br>PERSONALITY|Personality of CPx<br>Defines the processor personality for CPx.||
||Processor|Personality|
||CPx = Cortex-M7_0|43_4D_37_30h|
||CPx = Cortex-M7_1|43_4D_37_31h|
||CPx = Cortex-M7_2|43_4D_37_32h|
||CPx = Cortex-M7_3|43_4D_37_33h|
||||



## 7.6.3.3 Processor X Number (CPXNUM) 

## Offset 

|Register|Offset|
|---|---|
|CPXNUM|4h|



## Function 

Provides a CPU-specific response indicating the logical processor number of the core making the access. 

A read from the Cortex-M7 cores returns the appropriate processor information. Reads from any other bus controller return all 0s and attempted write accesses terminate with an error. 

Access: User or privileged read-only 

## Diagram 

**==> picture [504 x 148] intentionally omitted <==**

**----- Start of picture text -----**<br>
Bits 31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16<br>R 0<br>W<br>Reset u u u u u u u u u u u u u u u u<br>Bits 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0<br>R 0 CPN<br>W<br>Reset u u u u u u u u u u u u u u u u<br>**----- End of picture text -----**<br>


S32K3xx Reference Manual, Rev. 12, 2025-11-11 

Reference Manual 

84 / 5394 

NXP Semiconductors 

Miscellaneous System Control Module (MSCM) 

## Fields 

|Field|Function|
|---|---|
|31-3<br>—|Reserved|
|2-0<br>CPN|Processor Number<br>Defines the logical processor number for CPx.<br>CPN in MSCM indicates only the on-platform cores and not the HSE_B core. CPN = 0<br>represents Cortex-M7_0 if it is a lockstep or dual core. In Lockstep mode, CPN = 1 does not<br>read fromProcessor X Number (CPXNUM).<br>~~NOTE~~<br>000b - Cortex-M7 core 0<br>001b - Cortex-M7 core 1<br>010b - Cortex-M7 core 2<br>011b - Cortex-M7 core 3|



## 7.6.3.4 Processor X Revision (CPXREV) 

## Offset 

|Register|Offset|
|---|---|
|CPXREV|8h|



## Function 

Provides a CPU-specific response indicating the logical revision number of the core. 

A read from the Cortex-M7 cores returns the appropriate processor information. Reads from any other bus controller return all 0s and attempted write accesses terminate with an error. 

Access: User or privileged read-only 

## Diagram 

**==> picture [504 x 148] intentionally omitted <==**

**----- Start of picture text -----**<br>
Bits 31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16<br>R 0<br>W<br>Reset 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0<br>Bits 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0<br>R 0 RYPZ<br>W<br>Reset 0 0 0 0 0 0 0 0 u u u u u u u u<br>**----- End of picture text -----**<br>


S32K3xx Reference Manual, Rev. 12, 2025-11-11 

Reference Manual 

85 / 5394 

NXP Semiconductors 

Miscellaneous System Control Module (MSCM) 

## Fields 

|Field|Function|
|---|---|
|31-8<br>—|Reserved|
|7-0<br>RYPZ|Processor Revision<br>Defines the processor revision for CPx.<br>For the Cortex-M7 cores in this chip, RYPZ = 12h corresponding to the r1p2 core release.|



## 7.6.3.5 Processor X Configuration 0 (CPXCFG0) 

## Offset 

|Register|Offset|
|---|---|
|CPXCFG0|Ch|



## Function 

Provides a CPU-specific response detailing configuration information. In this case, it is information on Level 1 (L1) cache, if present. 

A read from Cortex-M7 returns the appropriate processor information. Reads from any other bus controller return all 0s and attempted write accesses terminate with an error. 

Access: User or privileged read-only 

## Diagram 

**==> picture [504 x 149] intentionally omitted <==**

**----- Start of picture text -----**<br>
Bits 31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16<br>R ICSZ  ICWY<br>W<br>Reset 0 0 0 0 0 1 1 0 0 0 0 0 0 0 1 0<br>Bits 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0<br>R DCSZ  DCWY<br>W<br>Reset 0 0 0 0 0 1 1 0 0 0 0 0 0 1 0 0<br>**----- End of picture text -----**<br>


Fields 

|Field|Function|
|---|---|
|31-24<br>ICSZ|Level 1 Instruction Cache Size|



Table continues on the next page... 

S32K3xx Reference Manual, Rev. 12, 2025-11-11 

Reference Manual 

86 / 5394 

NXP Semiconductors 

Miscellaneous System Control Module (MSCM) 

## Table continued from the previous page... 

|Field|Function|
|---|---|
||Provides an encoded value of the instruction cache size. The capacity of the memory is derived using the<br>formula 2(8+SZ)and expressed as bytes. Here, ICSZ is a nonzero value and ICSZ = 0 indicates that the<br>memory is not present.<br>For information about cache sizes, see the "Miscellaneous Control Module (MCM)" chapter.|
|23-16<br>ICWY|L1 Instruction Cache Ways<br>Provides the number of cache ways for the instruction cache.<br>For the Cortex-M7 cores in this chip, ICWY = 2h (2-way set-associative).|
|15-8<br>DCSZ|L1 Data Cache Size<br>Provides an encoded value of the data cache size.<br>The capacity of the memory is derived using the formula 2(8+SZ)and expressed as bytes. Here, DCSZ is a<br>nonzero value and DCSZ = 0 indicates that the memory is not present.<br>For information about cache sizes, see the "Miscellaneous Control Module (MCM)" chapter.|
|7-0<br>DCWY|L1 Data Cache Ways<br>Provides the number of cache ways for the data cache.<br>For the Cortex-M7 cores in this chip, DCWY = 4h (4-way set-associative).|



## 7.6.3.6 Processor X Configuration 1 (CPXCFG1) 

## Offset 

|Register|Offset|
|---|---|
|CPXCFG1|10h|



## Function 

Provides a CPU-specific response detailing configuration information. In this case, it is information on Level 2 (L2) cache, if present. 

A read from the Cortex-M7 cores returns the appropriate processor information. Reads from any other bus controller return all 0s and attempted write accesses terminate with an error. 

Access: User or privileged read-only 

S32K3xx Reference Manual, Rev. 12, 2025-11-11 

Reference Manual 

87 / 5394 

NXP Semiconductors 

Miscellaneous System Control Module (MSCM) 

## Diagram 

|Bits<br>R<br>W<br>Reset<br>Bits<br>R<br>W<br>Reset|31<br>30<br>29<br>28|27<br>26<br>25<br>24|23<br>22<br>21<br>20|19<br>18<br>17<br>16|
|---|---|---|---|---|
||L2SZ||L2WY||
||||||
||u<br>u<br>u<br>u|u<br>u<br>u<br>u|u<br>u<br>u<br>u|u<br>u<br>u<br>u|
||||||
||15<br>14<br>13<br>12|11<br>10<br>9<br>8|7<br>6<br>5<br>4|3<br>2<br>1<br>0|
||0||||
||||||
||0<br>0<br>0<br>0|0<br>0<br>0<br>0|0<br>0<br>0<br>0|0<br>0<br>0<br>0|



## Fields 

|Field|Function|
|---|---|
|31-24<br>L2SZ|L2 Cache Size<br>Provides an encoded value of the L2 cache size. The capacity of the memory is derived using the formula<br>2(8+SZ)and expressed as bytes. Here, L2SZ is a nonzero value, and L2SZ = 0 indicates that the memory is<br>not present.<br>For the Cortex-M7 cores in this chip, L2SZ = 0h (not present).|
|23-16<br>L2WY|L2 Cache Ways<br>Provides the number of cache ways for the L2 cache.<br>For the Cortex-M7 cores in this chip, L2WY = 0h (not present).|
|15-0<br>—|Reserved|



## 7.6.3.7 Processor X Configuration 2 (CPXCFG2) 

## Offset 

|Register|Offset|
|---|---|
|CPXCFG2|14h|



## Function 

Provides a CPU-specific response detailing configuration information. In this case, it is information on tightly coupled local memories, if present. 

A read from the Cortex-M7 cores returns the appropriate processor information. Reads from any other bus controller return all 0s and attempted write accesses terminate with an error. 

Access: User or privileged read-only 

S32K3xx Reference Manual, Rev. 12, 2025-11-11 

Reference Manual 

88 / 5394 

NXP Semiconductors 

Miscellaneous System Control Module (MSCM) 

## Diagram 

|Bits<br>R<br>W<br>Reset<br>Bits<br>R<br>W<br>Reset|31<br>30<br>29<br>28|27<br>26<br>25<br>24|23<br>22<br>21<br>20|19<br>18<br>17<br>16|
|---|---|---|---|---|
||DTCMSZ||ITCMSZ||
||||||
||u<br>u<br>u<br>u|u<br>u<br>u<br>u|u<br>u<br>u<br>u|u<br>u<br>u<br>u|
||||||
||15<br>14<br>13<br>12|11<br>10<br>9<br>8|7<br>6<br>5<br>4|3<br>2<br>1<br>0|
||0||||
||||||
||0<br>0<br>0<br>0|0<br>0<br>0<br>0|0<br>0<br>0<br>0|0<br>0<br>0<br>0|



## Fields 

|Field|Function|
|---|---|
|31-24<br>DTCMSZ|Tightly Coupled Data Memory Size<br>Provides an encoded value of the tightly coupled local data memory size. The capacity of the memory is<br>derived using the formula 2(8+SZ)and expressed as bytes. Here, DTCMSZ is a nonzero value and DTCMSZ<br>= 0 indicates that the memory is not present.<br>For the Cortex-M7 cores in this chip:<br>• DTCMSZ = 08 in Decoupled mode (64 KB)<br>• DTCMSZ = 09 for Cortex-M7_0 in Lockstep mode (128 KB)|
|23-16<br>ITCMSZ|Instruction Tightly Coupled Memory Size<br>Provides an encoded value of the tightly coupled local instruction memory size. The capacity of the memory<br>is derived using the formula 2(8+SZ)and expressed as bytes. Here, ITCMSZ is a nonzero value, and ITCMSZ<br>= 0 indicates that the memory is not present.<br>For the Cortex-M7 cores in this chip:<br>• ITCMSZ = 07 in Decoupled mode (32 KB)<br>• ITCMSZ = 08 for Cortex-M7_0 in Lockstep mode (64 KB)|
|15-0<br>—|Reserved|



## 7.6.3.8 Processor X Configuration 3 (CPXCFG3) 

## Offset 

|Register|Offset|
|---|---|
|CPXCFG3|18h|



## Function 

Provides a CPU-specific response detailing configuration information. In this case, it is information on processor options. 

S32K3xx Reference Manual, Rev. 12, 2025-11-11 

Reference Manual 

89 / 5394 

NXP Semiconductors 

Miscellaneous System Control Module (MSCM) 

A privileged read from Cortex-M7 returns the appropriate processor information. Reads from any other bus controller return all 0s and attempted write accesses terminate with an error. 

Access: User or privileged read-only 

## Diagram 

|Bits<br>R<br>W<br>Reset<br>Bits<br>R<br>W<br>Reset|31<br>30<br>29<br>28|27<br>26<br>25<br>24|23<br>22<br>21<br>20|23<br>22<br>21<br>20|19<br>18<br>17<br>16|19<br>18<br>17<br>16|19<br>18<br>17<br>16|19<br>18<br>17<br>16|
|---|---|---|---|---|---|---|---|---|
||0||||||||
||||||||||
||0<br>0<br>0<br>0|0<br>0<br>0<br>0|0<br>0<br>0<br>0||0<br>0<br>0<br>0||||
||||||||||
||15<br>14<br>13<br>12|11<br>10<br>9<br>8|7<br>6<br>5<br>4||3<br>2<br>1<br>0||||
||0|||CPY|CMP|MMU|SIMD|FPU|
||||||||||
||0<br>0<br>0<br>0|0<br>0<br>0<br>0|0<br>0<br>0<br>0||1<br>0<br>1<br>1||||



Fields 

|Field|Function|
|---|---|
|31-5<br>—|Reserved|
|4<br>CPY|Cryptography<br>Indicates whether the cryptography extensions are supported in the core.<br>For the Cortex-M7 cores in this chip, CPY = 0h.<br>0b - Not supported<br>1b - Supported|
|3<br>CMP|Core Memory Protection Unit<br>Indicates whether the core memory protection hardware is included in this core.<br>For the Cortex-M7 cores in this chip, CMP = 1h.<br>0b - Not included<br>1b - Included|
|2<br>MMU|Memory Management Unit<br>Indicates whether virtual management capabilities are supported in this core.<br>For the Cortex-M7 cores in this chip, MMU = 0h.<br>0b - Not supported<br>1b - Supported|
|1<br>SIMD|SIMD/NEON Instruction Support|



Table continues on the next page... 

S32K3xx Reference Manual, Rev. 12, 2025-11-11 

Reference Manual 

90 / 5394 

NXP Semiconductors 

Miscellaneous System Control Module (MSCM) 

## Table continued from the previous page... 

|Field|Function|
|---|---|
||Indicates whether the instruction set extensions supporting SIMD and/or NEON capabilities are included in<br>the processor.<br>For the Cortex-M7 cores in this chip, SIMD = 1h.<br>0b - Not included<br>1b - Included|
|0<br>FPU|Floating Point Unit<br>Indicates whether hardware support for floating point capabilities is provided in the processor.<br>For the Cortex-M7 cores in this chip, FPU = 1h.<br>0b - Not provided<br>1b - Provided|



## 7.6.3.9 Processor 0 Type (CP0TYPE) 

## Offset 

|Register|Offset|
|---|---|
|CP0TYPE|20h|



## Function 

Defines the configuration information for processor 0 (CP0). It has the same field definitions and functionality as provided in Processor X Type (CPXTYPE). 

A read from any bus controller returns the appropriate processor information and attempted write accesses terminate with an error. 

Access: User or privileged read-only 

## Diagram 

**==> picture [504 x 148] intentionally omitted <==**

**----- Start of picture text -----**<br>
Bits 31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16<br>R PERSONALITY<br>W<br>Reset 0 1 0 0 0 0 1 1 0 1 0 0 1 1 0 1<br>Bits 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0<br>R PERSONALITY<br>W<br>Reset 0 0 1 1 0 1 1 1 0 0 1 1 0 0 0 0<br>**----- End of picture text -----**<br>


S32K3xx Reference Manual, Rev. 12, 2025-11-11 

Reference Manual 

91 / 5394 

NXP Semiconductors 

Miscellaneous System Control Module (MSCM) 

## Fields 

|Field|Function|
|---|---|
|31-0<br>PERSONALITY|Processor Personality<br>Defines the processor personality for CP0.<br>For Cortex-M7 core 0, personality = 43_4D_37_30h.|



## 7.6.3.10 Processor 0 Number (CP0NUM) 

## Offset 

|Register|Offset|
|---|---|
|CP0NUM|24h|



## Function 

Defines the configuration information for processor 0 (CP0). It has the same field definitions and functionality as provided in Processor X Number (CPXNUM). 

A privileged read from any bus controllers returns the appropriate processor information and attempted write accesses terminate with an error. 

Access: User or privileged read-only 

## Diagram 

**==> picture [504 x 148] intentionally omitted <==**

**----- Start of picture text -----**<br>
Bits 31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16<br>R 0<br>W<br>Reset 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0<br>Bits 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0<br>R 0 CPN<br>W<br>Reset 0 0 0 0 0 0 0 0 0 0 0 0 0 0 u u<br>**----- End of picture text -----**<br>


Fields 

|Field|Function|
|---|---|
|31-2<br>—|Reserved|
|1-0<br>CPN|Processor Number<br>Defines the logical processor number for CP0.<br>For processor Cortex-M7 core 0, processor number = 0.|



S32K3xx Reference Manual, Rev. 12, 2025-11-11 

Reference Manual 

92 / 5394 

NXP Semiconductors 

Miscellaneous System Control Module (MSCM) 

## 7.6.3.11 Processor 0 Count (CP0REV) 

## Offset 

|Register|Offset|
|---|---|
|CP0REV|28h|



## Function 

Defines the configuration information for processor 0 (CP0). It has the same field definitions and functionality as provided in Processor X Revision (CPXREV). 

A read from any bus controller returns the appropriate processor information and attempted write accesses terminate with an error. 

Access: User or privileged read-only 

## Diagram 

|Bits<br>R<br>W<br>Reset<br>Bits<br>R<br>W<br>Reset|31<br>30<br>29<br>28|27<br>26<br>25<br>24|23<br>22<br>21<br>20|19<br>18<br>17<br>16|
|---|---|---|---|---|
||0||||
||||||
||0<br>0<br>0<br>0|0<br>0<br>0<br>0|0<br>0<br>0<br>0|0<br>0<br>0<br>0|
||||||
||15<br>14<br>13<br>12|11<br>10<br>9<br>8|7<br>6<br>5<br>4|3<br>2<br>1<br>0|
||0||RYPZ||
||||||
||0<br>0<br>0<br>0|0<br>0<br>0<br>0|u<br>u<br>u<br>u|u<br>u<br>u<br>u|



## Fields 

|Field|Function|
|---|---|
|31-8<br>—|Reserved|
|7-0<br>RYPZ|Processor Revision<br>Defines the processor revision for CP0.<br>For the Cortex-M7 processor, RYPZ = 12h corresponding to the r1p2 core release.|



## 7.6.3.12 Processor 0 Configuration 0 (CP0CFG0) 

## Offset 

|Register|Offset|
|---|---|
|CP0CFG0|2Ch|



S32K3xx Reference Manual, Rev. 12, 2025-11-11 

Reference Manual 

93 / 5394 

NXP Semiconductors 

Miscellaneous System Control Module (MSCM) 

## Function 

Defines the configuration information for processor 0 (CP0). It has the same field definitions and functionality as provided in Processor X Configuration 0 (CPXCFG0). 

A read from any bus controller returns the appropriate processor information and attempted write accesses terminate with an error. 

Access: User or privileged read-only 

## Diagram 

|Bits<br>R<br>W<br>Reset<br>Bits<br>R<br>W<br>Reset|31<br>30<br>29<br>28|27<br>26<br>25<br>24|23<br>22<br>21<br>20|19<br>18<br>17<br>16|
|---|---|---|---|---|
||ICSZ||ICWY||
||||||
||0<br>0<br>0<br>0|0<br>1<br>0<br>1|0<br>0<br>0<br>0|0<br>0<br>1<br>0|
||||||
||15<br>14<br>13<br>12|11<br>10<br>9<br>8|7<br>6<br>5<br>4|3<br>2<br>1<br>0|
||DCSZ||DCWY||
||||||
||0<br>0<br>0<br>0|0<br>1<br>0<br>1|0<br>0<br>0<br>0|0<br>1<br>0<br>0|



## Fields 

|Field|Function|
|---|---|
|31-24<br>ICSZ|Level 1 Instruction Cache Size<br>Provides an encoded value of the instruction cache size. The capacity of the memory is derived using the<br>formula 2(8+SZ)and expressed as bytes. Here, ICSZ is a nonzero value, and ICSZ = 0 indicates that the<br>memory is not present.<br>For information about cache sizes, see the "Miscellaneous Control Module (MCM)" chapter.|
|23-16<br>ICWY|L1 Instruction Cache Ways<br>Provides the number of cache ways for the instruction cache.<br>For the Cortex-M7 cores in this chip, ICWY = 2h (2-way set-associative).|
|15-8<br>DCSZ|L1 Data Cache Size<br>Provides an encoded value of the data cache size.<br>The capacity of the memory is derived using the formula 2(8+SZ)and expressed as bytes. Here, DCSZ is a<br>nonzero value, and DCSZ = 0 indicates that the memory is not present.<br>For information about cache sizes, see the "Miscellaneous Control Module (MCM)" chapter.|
|7-0<br>DCWY|L1 Data Cache Ways<br>Provides the number of cache ways for the data cache.<br>For the Cortex-M7 cores in this chip, DCWY = 4h (4-way set-associative).|



S32K3xx Reference Manual, Rev. 12, 2025-11-11 

Reference Manual 

94 / 5394 

NXP Semiconductors 

Miscellaneous System Control Module (MSCM) 

## 7.6.3.13 Processor 0 Configuration 1 (CP0CFG1) 

## Offset 

|Register|Offset|
|---|---|
|CP0CFG1|30h|



## Function 

Defines the configuration information for processor 0 (CP0). It has the same field definitions and functionality as provided in Processor X Configuration 1 (CPXCFG1). 

A privileged read from any bus controller returns the appropriate processor information and attempted write accesses terminate with an error. 

Access: User or privileged read-only 

## Diagram 

|Bits<br>R<br>W<br>Reset<br>Bits<br>R<br>W<br>Reset|31<br>30<br>29<br>28|27<br>26<br>25<br>24|23<br>22<br>21<br>20|19<br>18<br>17<br>16|
|---|---|---|---|---|
||L2SZ||L2WY||
||||||
||0<br>0<br>0<br>0|0<br>0<br>0<br>0|0<br>0<br>0<br>0|0<br>0<br>0<br>0|
||||||
||15<br>14<br>13<br>12|11<br>10<br>9<br>8|7<br>6<br>5<br>4|3<br>2<br>1<br>0|
||0||||
||||||
||0<br>0<br>0<br>0|0<br>0<br>0<br>0|0<br>0<br>0<br>0|0<br>0<br>0<br>0|



## Fields 

|Field|Function|
|---|---|
|31-24<br>L2SZ|L2 Cache Size<br>Provides an encoded value of the L2 cache size.<br>The capacity of the memory is derived using the formula 2(8+SZ)and expressed as bytes. Here, L2SZ is a<br>nonzero value, and L2SZ = 0 indicates that the memory is not present.<br>For the Cortex-M7 cores in this chip, L2SZ = 0h (not present).|
|23-16<br>L2WY|L2 Cache Ways<br>Provides the number of cache ways for the L2 cache.<br>For the Cortex-M7 cores in this chip, L2WY = 0h (not present).|
|15-0<br>—|Reserved|



S32K3xx Reference Manual, Rev. 12, 2025-11-11 

Reference Manual 

95 / 5394 

NXP Semiconductors 

Miscellaneous System Control Module (MSCM) 

## 7.6.3.14 Processor 0 Configuration 2 (CP0CFG2) 

## Offset 

|Register|Offset|
|---|---|
|CP0CFG2|34h|



## Function 

Defines the configuration information for processor 0 (CP0). It has the same field definitions and functionality as provided in Processor X Configuration 2 (CPXCFG2). 

A privileged read from any bus controller returns the appropriate processor information and attempted write accesses terminate with an error. 

Access: User or privileged read-only 

## Diagram 

|Bits<br>R<br>W<br>Reset<br>Bits<br>R<br>W<br>Reset|31<br>30<br>29<br>28|27<br>26<br>25<br>24|23<br>22<br>21<br>20|19<br>18<br>17<br>16|
|---|---|---|---|---|
||DTCMSZ||ITCMSZ||
||||||
||u<br>u<br>u<br>u|u<br>u<br>u<br>u|u<br>u<br>u<br>u|u<br>u<br>u<br>u|
||||||
||15<br>14<br>13<br>12|11<br>10<br>9<br>8|7<br>6<br>5<br>4|3<br>2<br>1<br>0|
||0||||
||||||
||0<br>0<br>0<br>0|0<br>0<br>0<br>0|0<br>0<br>0<br>0|0<br>0<br>0<br>0|



## Fields 

|Field|Function|
|---|---|
|31-24<br>DTCMSZ|Tightly Coupled Data Memory Size<br>Provides an encoded value of the tightly coupled local data memory size.<br>The capacity of the memory is derived using the formula 2(8+SZ)and expressed as bytes. Here, TMLSZ is<br>a nonzero value, and TMLSZ = 0 indicates that the memory is not present.<br>For the Cortex-M7 cores in this chip:<br>• DTCMSZ = 8h in Decoupled mode (64 KB)<br>• DTCMSZ = 9h in Lockstep mode (128 KB)|
|23-16<br>ITCMSZ|Instruction Tightly Coupled Memory Size<br>Provides an encoded value of the tightly coupled local instruction memory size.<br>The capacity of the memory is derived using the formula 2(8+SZ)and expressed as bytes. Here, TMUSZ is<br>a nonzero value, and TMUSZ = 0 indicates that the memory is not present.|



Table continues on the next page... 

S32K3xx Reference Manual, Rev. 12, 2025-11-11 

Reference Manual 

96 / 5394 

NXP Semiconductors 

Miscellaneous System Control Module (MSCM) 

## Table continued from the previous page... 

|Field|Function|
|---|---|
||For the Cortex-M7 cores in this chip:<br>• ITCMSZ = 7h in Decoupled mode (32 KB)<br>• ITCMSZ = 8h in Lockstep mode (64 KB)|
|15-0<br>—|Reserved|



## 7.6.3.15 Processor 0 Configuration 3 (CP0CFG3) 

## Offset 

|Register|Offset|
|---|---|
|CP0CFG3|38h|



## Function 

Defines the configuration information for processor 0 (CP0). It has the same field definitions and functionality as provided in the CPXCFG3 register. 

A privileged read from any bus controller returns the appropriate processor information and attempted write accesses terminate with an error. 

Access: User or privileged read-only 

## Diagram 

**==> picture [504 x 148] intentionally omitted <==**

**----- Start of picture text -----**<br>
Bits 31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16<br>R 0<br>W<br>Reset 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0<br>Bits 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0<br>R 0 CPY  CMP  MMU  SIMD  FPU<br>W<br>Reset 0 0 0 0 0 0 0 0 0 0 0 0 1 0 1 1<br>**----- End of picture text -----**<br>


Fields 

|Field|Function|
|---|---|
|31-5<br>—|Reserved|
|Table continues on the next page...||



S32K3xx Reference Manual, Rev. 12, 2025-11-11 

Reference Manual 

97 / 5394 

NXP Semiconductors 

Miscellaneous System Control Module (MSCM) 

## Table continued from the previous page... 

|Field|Function|
|---|---|
|4<br>CPY|Cryptography<br>Indicates whether the cryptography extensions are supported in the core.<br>For the Cortex-M7 cores in this chip, CPY = 0h.<br>0b - Not supported<br>1b - Supported|
|3<br>CMP|Core Memory Protection Unit<br>Indicates whether the core memory protection hardware is included in this core.<br>For the Cortex-M7 cores in this chip, CMP = 1h.<br>0b - Not included<br>1b - Included|
|2<br>MMU|Memory Management Unit<br>Indicates whether virtual management capabilities are supported in this core.<br>For the Cortex-M7 cores in this chip, MMU = 0h.<br>0b - Not supported<br>1b - Supported|
|1<br>SIMD|SIMD/NEON Instruction Support<br>Indicates whether the instruction set extensions supporting SIMD and/or NEON capabilities are included in<br>the processor.<br>For the Cortex-M7 cores in this chip, SIMD = 1h.<br>0b - Not included<br>1b - Included|
|0<br>FPU|Floating Point Unit<br>Indicates whether hardware support for floating point capabilities is provided in the processor.<br>For the Cortex-M7 cores in this chip, FPU = 1h.<br>0b - Not provided<br>1b - Provided|



## 7.6.3.16 Processor 1 Type (CP1TYPE) 

## Offset 

|Register|Offset|
|---|---|
|CP1TYPE|40h|



S32K3xx Reference Manual, Rev. 12, 2025-11-11 

Reference Manual 

98 / 5394 

NXP Semiconductors 

Miscellaneous System Control Module (MSCM) 

## Function 

Defines the configuration information for processor 1 (CP1). It has the same field definitions and functionality as provided in Processor X Type (CPXTYPE). 

A read from any bus controller returns the appropriate processor information and attempted write accesses terminate with an error. 

Access: User or privileged read-only 

## Diagram 

|Bits<br>R<br>W<br>Reset<br>Bits<br>R<br>W<br>Reset|31<br>30<br>29<br>28|27<br>26<br>25<br>24|23<br>22<br>21<br>20|19<br>18<br>17<br>16|
|---|---|---|---|---|
||PERSONALITY||||
||||||
||0<br>1<br>0<br>0|0<br>0<br>1<br>1|0<br>1<br>0<br>0|1<br>1<br>0<br>1|
||||||
||15<br>14<br>13<br>12|11<br>10<br>9<br>8|7<br>6<br>5<br>4|3<br>2<br>1<br>0|
||PERSONALITY||||
||||||
||0<br>0<br>1<br>1|0<br>1<br>1<br>1|0<br>0<br>1<br>1|0<br>0<br>0<br>1|



## Fields 

|Field|Function|
|---|---|
|31-0<br>PERSONALITY|Personality Processor<br>Defines the processor personality for CP1.<br>CP1 = Cortex-M7 core 1 and processor personality = 43_4D_37_31h.|



## 7.6.3.17 Processor 1 Number (CP1NUM) 

## Offset 

|Register|Offset|
|---|---|
|CP1NUM|44h|



## Function 

Defines the configuration information for processor 1 (CP1). It has the same field definitions and functionality as provided in Processor X Number (CPXNUM). 

A read from any bus controller returns the appropriate processor information and attempted write accesses terminate with an error. 

Access: User or privileged read-only 

S32K3xx Reference Manual, Rev. 12, 2025-11-11 

Reference Manual 

99 / 5394 

NXP Semiconductors 

Miscellaneous System Control Module (MSCM) 

## Diagram 

|Bits<br>R<br>W<br>Reset<br>Bits<br>R<br>W<br>Reset|31<br>30<br>29<br>28|27<br>26<br>25<br>24|23<br>22<br>21<br>20|19<br>18<br>17<br>16|19<br>18<br>17<br>16|
|---|---|---|---|---|---|
||0|||||
|||||||
||0<br>0<br>0<br>0<br>0<br>0<br>0<br>0<br>0<br>0<br>0<br>0<br>0<br>0<br>0<br>0|||||
||15<br>14<br>13<br>12|11<br>10<br>9<br>8|7<br>6<br>5<br>4|3<br>2<br>1<br>0||
||0||||CPN|
|||||||
||0<br>0<br>0<br>0|0<br>0<br>0<br>0|0<br>0<br>0<br>0|0<br>0<br>0<br>1||



## Fields 

|Field|Function|
|---|---|
|31-2<br>—|Reserved|
|1-0<br>CPN|Processor Number<br>Defines the logical processor number for CP1.<br>For the Cortex-M7 core 1 processor, the processor number = 1. The processor personality is 0000_0001h.|



## 7.6.3.18 Processor 1 Count (CP1REV) 

## Offset 

|Register|Offset|
|---|---|
|CP1REV|48h|



## Function 

Defines the configuration information for processor 1 (CP1). It has the same field definitions and functionality as provided in Processor X Revision (CPXREV). 

A read from any bus controller returns the appropriate processor information and attempted write accesses terminate with an error. 

Access: User or privileged read-only 

S32K3xx Reference Manual, Rev. 12, 2025-11-11 

Reference Manual 

100 / 5394 

NXP Semiconductors 

Miscellaneous System Control Module (MSCM) 

## Diagram 

**==> picture [504 x 148] intentionally omitted <==**

**----- Start of picture text -----**<br>
Bits 31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16<br>R 0<br>W<br>Reset 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0<br>Bits 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0<br>R 0 RYPZ<br>W<br>Reset 0 0 0 0 0 0 0 0 u u u u u u u u<br>**----- End of picture text -----**<br>


## Fields 

|Field|Function|
|---|---|
|31-8<br>—|Reserved|
|7-0<br>RYPZ|Processor Revision<br>Defines the processor revision for CP1.<br>For the Cortex-M7 processor, RYPZ = 12h corresponding to the r1p2 core release.|



## 7.6.3.19 Processor 1 Configuration 0 (CP1CFG0) 

## Offset 

|Register|Offset|
|---|---|
|CP1CFG0|4Ch|



## Function 

Defines the configuration information for processor 1 (CP1). It has the same field definitions and functionality as provided in Processor X Configuration 0 (CPXCFG0). 

A privileged read from any bus controller returns the appropriate processor information and attempted write accesses terminate with an error. 

Access: User or privileged read-only 

S32K3xx Reference Manual, Rev. 12, 2025-11-11 

Reference Manual 

101 / 5394 

NXP Semiconductors 

Miscellaneous System Control Module (MSCM) 

## Diagram 

|Bits<br>R<br>W<br>Reset<br>Bits<br>R<br>W<br>Reset|31<br>30<br>29<br>28|27<br>26<br>25<br>24|23<br>22<br>21<br>20|19<br>18<br>17<br>16|
|---|---|---|---|---|
||ICSZ||ICWY||
||||||
||0<br>0<br>0<br>0|0<br>1<br>0<br>1|0<br>0<br>0<br>0|0<br>0<br>1<br>0|
||||||
||15<br>14<br>13<br>12|11<br>10<br>9<br>8|7<br>6<br>5<br>4|3<br>2<br>1<br>0|
||DCSZ||DCWY||
||||||
||0<br>0<br>0<br>0|0<br>1<br>0<br>1|0<br>0<br>0<br>0|0<br>1<br>0<br>0|



## Fields 

|Field|Function|
|---|---|
|31-24<br>ICSZ|Level 1 Instruction Cache Size<br>Provides an encoded value of the instruction cache size.<br>The capacity of the memory is derived using the formula 2(8+SZ)and expressed as bytes. Here, ICSZ is a<br>nonzero value, and ICSZ = 0 indicates that the memory is not present.<br>For information about cache sizes, see the "Miscellaneous Control Module (MCM)" chapter.|
|23-16<br>ICWY|Level 1 Instruction Cache Ways<br>Provides the number of cache ways for the instruction cache.<br>For the Cortex-M7 cores in this chip, ICWY = 2h (2-way set-associative).|
|15-8<br>DCSZ|L1 Data Cache Size<br>Provides an encoded value of the data cache size.<br>The capacity of the memory is derived using the formula 2(8+SZ)and expressed as bytes. Here, DCSZ is a<br>nonzero value, and DCSZ = 0 indicates that the memory is not present.<br>For information about cache sizes, see the "Miscellaneous Control Module (MCM)" chapter.|
|7-0<br>DCWY|L1 Data Cache Ways<br>Provides the number of cache ways for the data cache.<br>For the Cortex-M7 cores in this chip, DCWY = 4h (4-way set-associative).|



## 7.6.3.20 Processor 1 Configuration 1 (CP1CFG1) 

## Offset 

|Register|Offset|
|---|---|
|CP1CFG1|50h|



S32K3xx Reference Manual, Rev. 12, 2025-11-11 

Reference Manual 

102 / 5394 

NXP Semiconductors 

Miscellaneous System Control Module (MSCM) 

## Function 

Defines the configuration information for processor 1 (CP1). It has the same field definitions and functionality as provided in Processor X Configuration 1 (CPXCFG1). 

A privileged read from any bus controller returns the appropriate processor information and attempted write accesses terminate with an error. 

Access: User or privileged read-only 

## Diagram 

|Bits<br>R<br>W<br>Reset<br>Bits<br>R<br>W<br>Reset|31<br>30<br>29<br>28|27<br>26<br>25<br>24|23<br>22<br>21<br>20|19<br>18<br>17<br>16|
|---|---|---|---|---|
||L2SZ||L2WY||
||||||
||u<br>u<br>u<br>u|u<br>u<br>u<br>u|u<br>u<br>u<br>u|u<br>u<br>u<br>u|
||||||
||15<br>14<br>13<br>12|11<br>10<br>9<br>8|7<br>6<br>5<br>4|3<br>2<br>1<br>0|
||0||||
||||||
||0<br>0<br>0<br>0|0<br>0<br>0<br>0|0<br>0<br>0<br>0|0<br>0<br>0<br>0|



Fields 

|Field|Function|
|---|---|
|31-24<br>L2SZ|L2 Cache Size<br>Provides an encoded value of the L2 cache size.<br>The capacity of the memory is derived using the formula 2(8+SZ)and expressed as bytes. Here, L2SZ is a<br>nonzero value, and L2SZ = 0 indicates that the memory is not present.<br>For the Cortex-M7 cores in this chip, L2SZ = 0h (not present).|
|23-16<br>L2WY|L2 Cache Ways<br>Provides the number of cache ways for the L2 cache.<br>For the Cortex-M7 cores in this chip, L2WY = 0h (not present).|
|15-0<br>—|Reserved|



## 7.6.3.21 Processor 1 Configuration 2 (CP1CFG2) 

## Offset 

|Register|Offset|
|---|---|
|CP1CFG2|54h|



S32K3xx Reference Manual, Rev. 12, 2025-11-11 

Reference Manual 

103 / 5394 

NXP Semiconductors 

Miscellaneous System Control Module (MSCM) 

## Function 

Defines the configuration information for processor 1 (CP1). It has the same field definitions and functionality as provided in Processor X Configuration 2 (CPXCFG2). 

A privileged read from any bus controller returns the appropriate processor information and attempted write accesses terminate with an error. 

Access: User or privileged read-only 

## Diagram 

|Bits<br>R<br>W<br>Reset<br>Bits<br>R<br>W<br>Reset|31<br>30<br>29<br>28|27<br>26<br>25<br>24|23<br>22<br>21<br>20|19<br>18<br>17<br>16|
|---|---|---|---|---|
||DTCMSZ||ITCMSZ||
||||||
||u<br>u<br>u<br>u|u<br>u<br>u<br>u|u<br>u<br>u<br>u|u<br>u<br>u<br>u|
||||||
||15<br>14<br>13<br>12|11<br>10<br>9<br>8|7<br>6<br>5<br>4|3<br>2<br>1<br>0|
||0||||
||||||
||0<br>0<br>0<br>0|0<br>0<br>0<br>0|0<br>0<br>0<br>0|0<br>0<br>0<br>0|



## Fields 

|Field|Function|
|---|---|
|31-24<br>DTCMSZ|Tightly Coupled Data Memory Size<br>Provides an encoded value of the tightly coupled local data memory size.<br>The capacity of the memory is derived using the formula 2(8+SZ)and expressed as bytes. Here, TMLSZ is<br>a nonzero value, and TMLSZ = 0 indicates that the memory is not present.<br>For the Cortex-M7 cores in this chip, DTCMSZ = 8h in Decoupled mode (64 KB), and this value is not<br>applicable in Lockstep mode.|
|23-16<br>ITCMSZ|Instruction Tightly Coupled Memory Size<br>Provides an encoded value of the tightly coupled local instruction memory size. The capacity of the memory<br>is derived using the formula 2(8+SZ)and expressed as bytes. Here, TMUSZ is a nonzero value, and TMUSZ<br>= 0 indicates that the memory is not present.<br>For the Cortex-M7 cores in this chip, ITCMSZ = 7h in Decoupled mode (32 KB); this value is not applicable<br>in Lockstep mode.|
|15-0<br>—|Reserved|



S32K3xx Reference Manual, Rev. 12, 2025-11-11 

Reference Manual 

104 / 5394 

NXP Semiconductors 

Miscellaneous System Control Module (MSCM) 

## 7.6.3.22 Processor 1 Configuration 3 (CP1CFG3) 

## Offset 

|Register|Offset|
|---|---|
|CP1CFG3|58h|



## Function 

Defines the configuration information for processor 1 (CP1). It has the same field definitions and functionality as provided in the CPXCFG3 register. 

A privileged read from any bus controller returns the appropriate processor information and attempted write accesses terminate with an error. 

Access: User or privileged read-only 

## Diagram 

|Bits<br>R<br>W<br>Reset<br>Bits<br>R<br>W<br>Reset|31<br>30<br>29<br>28|27<br>26<br>25<br>24|23<br>22<br>21<br>20|23<br>22<br>21<br>20|19<br>18<br>17<br>16|19<br>18<br>17<br>16|19<br>18<br>17<br>16|19<br>18<br>17<br>16|
|---|---|---|---|---|---|---|---|---|
||0||||||||
||||||||||
||0<br>0<br>0<br>0|0<br>0<br>0<br>0|0<br>0<br>0<br>0||0<br>0<br>0<br>0||||
||||||||||
||15<br>14<br>13<br>12|11<br>10<br>9<br>8|7<br>6<br>5<br>4||3<br>2<br>1<br>0||||
||0|||CPY|CMP|MMU|SIMD|FPU|
||||||||||
||0<br>0<br>0<br>0|0<br>0<br>0<br>0|0<br>0<br>0<br>0||1<br>0<br>1<br>1||||



## Fields 

|Field|Function|
|---|---|
|31-5<br>—|Reserved|
|4<br>CPY|Cryptography<br>Indicates whether cryptography extensions are supported in the core.<br>For the Cortex-M7 cores in this chip, CPY = 0h.<br>0b - Not supported<br>1b - Supported|
|3<br>CMP|Core Memory Protection Unit<br>Indicates whether the core memory protection hardware is included in this core.<br>For the Cortex-M7 cores in this chip, CMP = 1h.|



Table continues on the next page... 

S32K3xx Reference Manual, Rev. 12, 2025-11-11 

Reference Manual 

105 / 5394 

NXP Semiconductors 

Miscellaneous System Control Module (MSCM) 

## Table continued from the previous page... 

|Field|Function|
|---|---|
||0b - Not included<br>1b - Included|
|2<br>MMU|Memory Management Unit<br>Indicates whether virtual management capabilities are supported in this core.<br>For the Cortex-M7 cores in this chip, MMU = 0h.<br>0b - Not supported<br>1b - Supported|
|1<br>SIMD|SIMD/NEON Instruction Support<br>Indicates whether the instruction set extensions supporting SIMD and/or NEON capabilities are included in<br>the processor.<br>For the Cortex-M7 cores in this chip, SIMD = 1h.<br>0b - Not included<br>1b - Included|
|0<br>FPU|Floating Point Unit<br>Indicates whether the processor includes hardware support for floating point capabilities.<br>For the Cortex-M7 cores in this chip, FPU = 1h.<br>0b - Not included<br>1b - Included|



## 7.6.3.23 Processor 2 Type (CP2TYPE) 

## Offset 

|Register|Offset|
|---|---|
|CP2TYPE|60h|



## Function 

Defines the configuration information for processor 2 (CP2). It has the same field definitions and functionality as provided in Processor X Type (CPXTYPE). 

A read from any bus controller returns the appropriate processor information and attempted write accesses terminate with an error. 

Access: User or privileged read-only 

S32K3xx Reference Manual, Rev. 12, 2025-11-11 

Reference Manual 

106 / 5394 

NXP Semiconductors 

Miscellaneous System Control Module (MSCM) 

## Diagram 

|Bits<br>R<br>W<br>Reset<br>Bits<br>R<br>W<br>Reset|31<br>30<br>29<br>28|27<br>26<br>25<br>24|23<br>22<br>21<br>20|19<br>18<br>17<br>16|
|---|---|---|---|---|
||PERSONALITY||||
||||||
||0<br>1<br>0<br>0<br>0<br>0<br>1<br>1<br>0<br>1<br>0<br>0<br>1<br>1<br>0<br>1||||
||15<br>14<br>13<br>12|11<br>10<br>9<br>8|7<br>6<br>5<br>4|3<br>2<br>1<br>0|
||PERSONALITY||||
||||||
||0<br>0<br>1<br>1|0<br>1<br>1<br>1|0<br>0<br>1<br>1|0<br>0<br>1<br>0|



## Fields 

|Field|Function|
|---|---|
|31-0<br>PERSONALITY|Processor Personality<br>Defines the processor personality for CP2.<br>CP2 = Cortex-M7 core 2 and processor personality = 43_4D_37_32h.|



## 7.6.3.24 Processor 2 Number (CP2NUM) 

## Offset 

|Register|Offset|
|---|---|
|CP2NUM|64h|



## Function 

Defines the configuration information for processor 2 (CP2). It has the same field definitions and functionality as provided in Processor X Number (CPXNUM). 

A read from any bus controller returns the appropriate processor information and attempted write accesses terminate with an error. 

Access: User or privileged read-only 

S32K3xx Reference Manual, Rev. 12, 2025-11-11 

Reference Manual 

107 / 5394 

NXP Semiconductors 

Miscellaneous System Control Module (MSCM) 

## Diagram 

|Bits<br>R<br>W<br>Reset<br>Bits<br>R<br>W<br>Reset|31<br>30<br>29<br>28|27<br>26<br>25<br>24|23<br>22<br>21<br>20|19<br>18<br>17<br>16|19<br>18<br>17<br>16|
|---|---|---|---|---|---|
||0|||||
|||||||
||0<br>0<br>0<br>0<br>0<br>0<br>0<br>0<br>0<br>0<br>0<br>0<br>0<br>0<br>0<br>0|||||
||15<br>14<br>13<br>12|11<br>10<br>9<br>8|7<br>6<br>5<br>4|3<br>2<br>1<br>0||
||0||||CPN|
|||||||
||0<br>0<br>0<br>0|0<br>0<br>0<br>0|0<br>0<br>0<br>0|0<br>0<br>1<br>0||



## Fields 

|Field|Function|
|---|---|
|31-2<br>—|Reserved|
|1-0<br>CPN|Processor Number<br>Defines the logical processor number for CP2.<br>For Cortex-M7 core 2, processor number = 2. The processor personality is 0000_0002h.|



## 7.6.3.25 Processor 2 Count (CP2REV) 

## Offset 

|Register|Offset|
|---|---|
|CP2REV|68h|



## Function 

Defines the configuration information for processor 2 (CP2). It has the same field definitions and functionality as provided in Processor X Revision (CPXREV). 

A read from any bus controller returns the appropriate processor information and attempted write accesses terminate with an error. 

Access: User or privileged read-only 

S32K3xx Reference Manual, Rev. 12, 2025-11-11 

Reference Manual 

108 / 5394 

NXP Semiconductors 

Miscellaneous System Control Module (MSCM) 

## Diagram 

**==> picture [504 x 148] intentionally omitted <==**

**----- Start of picture text -----**<br>
Bits 31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16<br>R 0<br>W<br>Reset 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0<br>Bits 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0<br>R 0 RYPZ<br>W<br>Reset 0 0 0 0 0 0 0 0 u u u u u u u u<br>**----- End of picture text -----**<br>


## Fields 

|Field|Function|
|---|---|
|31-8<br>—|Reserved|
|7-0<br>RYPZ|Processor Revision<br>Defines the processor revision for CP2.<br>For the Cortex-M7 processor, RYPZ = 12h corresponding to the r1p2 core release.|



## 7.6.3.26 Processor 2 Configuration 0 (CP2CFG0) 

## Offset 

|Register|Offset|
|---|---|
|CP2CFG0|6Ch|



## Function 

Defines the configuration information for processor 2 (CP2). It has the same field definitions and functionality as provided in Processor X Configuration 0 (CPXCFG0). 

A privileged read from any bus controller returns the appropriate processor information and attempted write accesses terminate with an error. 

Access: User or privileged read-only 

S32K3xx Reference Manual, Rev. 12, 2025-11-11 

Reference Manual 

109 / 5394 

NXP Semiconductors 

Miscellaneous System Control Module (MSCM) 

## Diagram 

|Bits<br>R<br>W<br>Reset<br>Bits<br>R<br>W<br>Reset|31<br>30<br>29<br>28|27<br>26<br>25<br>24|23<br>22<br>21<br>20|19<br>18<br>17<br>16|
|---|---|---|---|---|
||ICSZ||ICWY||
||||||
||0<br>0<br>0<br>0|0<br>1<br>1<br>0|0<br>0<br>0<br>0|0<br>0<br>1<br>0|
||||||
||15<br>14<br>13<br>12|11<br>10<br>9<br>8|7<br>6<br>5<br>4|3<br>2<br>1<br>0|
||DCSZ||DCWY||
||||||
||0<br>0<br>0<br>0|0<br>1<br>1<br>0|0<br>0<br>0<br>0|0<br>1<br>0<br>0|



## Fields 

|Field|Function|
|---|---|
|31-24<br>ICSZ|Level 1 Instruction Cache Size<br>Provides an encoded value of the instruction cache size.<br>The capacity of the memory is derived using the formula 2(8+SZ)and expressed as bytes. Here, ICSZ is a<br>nonzero value, and ICSZ = 0 indicates that the memory is not present.<br>For information about cache sizes, see the "Miscellaneous Control Module (MCM)" chapter.|
|23-16<br>ICWY|Level 1 Instruction Cache Ways<br>Provides the number of cache ways for the instruction cache.<br>For the Cortex-M7 cores in this chip, ICWY = 2h (2-way set-associative).|
|15-8<br>DCSZ|L1 Data Cache Size<br>Provides an encoded value of the data cache size.<br>The capacity of the memory is derived using the formula 2(8+SZ)and expressed as bytes. Here, DCSZ is a<br>nonzero value, and DCSZ = 0 indicates that the memory is not present.<br>For information about cache sizes, see the "Miscellaneous Control Module (MCM)" chapter.|
|7-0<br>DCWY|L1 Data Cache Ways<br>Provides the number of cache ways for the data cache.<br>For the Cortex-M7 cores in this chip, DCWY = 4h (4-way set-associative).|



## 7.6.3.27 Processor 2 Configuration 1 (CP2CFG1) 

## Offset 

|Register|Offset|
|---|---|
|CP2CFG1|70h|



S32K3xx Reference Manual, Rev. 12, 2025-11-11 

Reference Manual 

110 / 5394 

NXP Semiconductors 

Miscellaneous System Control Module (MSCM) 

## Function 

Defines the configuration information for processor 2 (CP2). It has the same field definitions and functionality as provided in Processor X Configuration 1 (CPXCFG1). 

A privileged read from any bus controller returns the appropriate processor information and attempted write accesses terminate with an error. 

Access: User or privileged read-only 

## Diagram 

|Bits<br>R<br>W<br>Reset<br>Bits<br>R<br>W<br>Reset|31<br>30<br>29<br>28|27<br>26<br>25<br>24|23<br>22<br>21<br>20|19<br>18<br>17<br>16|
|---|---|---|---|---|
||L2SZ||L2WY||
||||||
||u<br>u<br>u<br>u|u<br>u<br>u<br>u|u<br>u<br>u<br>u|u<br>u<br>u<br>u|
||||||
||15<br>14<br>13<br>12|11<br>10<br>9<br>8|7<br>6<br>5<br>4|3<br>2<br>1<br>0|
||0||||
||||||
||0<br>0<br>0<br>0|0<br>0<br>0<br>0|0<br>0<br>0<br>0|0<br>0<br>0<br>0|



Fields 

|Field|Function|
|---|---|
|31-24<br>L2SZ|L2 Cache Size<br>Provides an encoded value of the L2 cache size. The capacity of the memory is derived using the formula<br>2(8+SZ)and expressed as bytes. Here, L2SZ is a nonzero value, and L2SZ = 0 indicates that the memory is<br>not present.<br>For the Cortex-M7 cores in this chip, L2SZ = 0h (not present).|
|23-16<br>L2WY|L2 Cache Ways<br>Provides the number of cache ways for the L2 cache.<br>For the Cortex-M7 cores in this chip, L2WY = 0h (not present).|
|15-0<br>—|Reserved|



## 7.6.3.28 Processor 2 Configuration 2 (CP2CFG2) 

## Offset 

|Register|Offset|
|---|---|
|CP2CFG2|74h|



S32K3xx Reference Manual, Rev. 12, 2025-11-11 

Reference Manual 

111 / 5394 

NXP Semiconductors 

Miscellaneous System Control Module (MSCM) 

## Function 

Defines the configuration information for processor 2 (CP2). It has the same field definitions and functionality as provided in Processor X Configuration 2 (CPXCFG2). 

A privileged read from any bus controller returns the appropriate processor information and attempted write accesses terminate with an error. 

Access: User or privileged read-only 

## Diagram 

|Bits<br>R<br>W<br>Reset<br>Bits<br>R<br>W<br>Reset|31<br>30<br>29<br>28|27<br>26<br>25<br>24|23<br>22<br>21<br>20|19<br>18<br>17<br>16|
|---|---|---|---|---|
||DTCMSZ||ITCMSZ||
||||||
||u<br>u<br>u<br>u|u<br>u<br>u<br>u|u<br>u<br>u<br>u|u<br>u<br>u<br>u|
||||||
||15<br>14<br>13<br>12|11<br>10<br>9<br>8|7<br>6<br>5<br>4|3<br>2<br>1<br>0|
||0||||
||||||
||0<br>0<br>0<br>0|0<br>0<br>0<br>0|0<br>0<br>0<br>0|0<br>0<br>0<br>0|



## Fields 

|Field|Function|
|---|---|
|31-24<br>DTCMSZ|Tightly Coupled Data Memory Size<br>Provides an encoded value of the tightly coupled local data memory size.<br>The capacity of the memory is derived using the formula 2(8+SZ)and expressed as bytes. Here, TMLSZ is<br>a nonzero value, and TMLSZ = 0 indicates that the memory is not present.<br>For the Cortex-M7 cores in this chip, DTCMSZ = 8h in Decoupled mode (64 KB), and this value is not<br>applicable in Lockstep mode.|
|23-16<br>ITCMSZ|Instruction Tightly Coupled Memory Size<br>Provides an encoded value of the tightly coupled local instruction memory size. The capacity of the memory<br>is derived using the formula 2(8+SZ)and expressed as bytes. Here, TMUSZ is a nonzero value, and TMUSZ<br>= 0 indicates that the memory is not present.<br>For the Cortex-M7 cores in this chip, ITCMSZ = 7h in Decoupled mode (32 KB); this value is not applicable<br>in Lockstep mode.|
|15-0<br>—|Reserved|



S32K3xx Reference Manual, Rev. 12, 2025-11-11 

Reference Manual 

112 / 5394 

NXP Semiconductors 

Miscellaneous System Control Module (MSCM) 

## 7.6.3.29 Processor 2 Configuration 3 (CP2CFG3) 

## Offset 

|Register|Offset|
|---|---|
|CP2CFG3|78h|



## Function 

Defines the configuration information for processor 2 (CP2). It has the same field definitions and functionality as provided in the CPXCFG3 register. 

A privileged read from any bus controller returns the appropriate processor information and attempted write accesses terminate with an error. 

Access: User or privileged read-only 

## Diagram 

|Bits<br>R<br>W<br>Reset<br>Bits<br>R<br>W<br>Reset|31<br>30<br>29<br>28|27<br>26<br>25<br>24|23<br>22<br>21<br>20|23<br>22<br>21<br>20|19<br>18<br>17<br>16|19<br>18<br>17<br>16|19<br>18<br>17<br>16|19<br>18<br>17<br>16|
|---|---|---|---|---|---|---|---|---|
||0||||||||
||||||||||
||0<br>0<br>0<br>0|0<br>0<br>0<br>0|0<br>0<br>0<br>0||0<br>0<br>0<br>0||||
||||||||||
||15<br>14<br>13<br>12|11<br>10<br>9<br>8|7<br>6<br>5<br>4||3<br>2<br>1<br>0||||
||0|||CPY|CMP|MMU|SIMD|FPU|
||||||||||
||0<br>0<br>0<br>0|0<br>0<br>0<br>0|0<br>0<br>0<br>0||1<br>0<br>1<br>1||||



## Fields 

|Field|Function|
|---|---|
|31-5<br>—|Reserved|
|4<br>CPY|Cryptography<br>Indicates whether cryptography extensions are supported in the core.<br>For the Cortex-M7 cores in this chip, CPY = 0h.<br>0b - Not supported<br>1b - Supported|
|3<br>CMP|Core Memory Protection Unit<br>Indicates whether the core memory protection hardware is included in this core.<br>For the Cortex-M7 cores in this chip, CMP = 1h.|



Table continues on the next page... 

S32K3xx Reference Manual, Rev. 12, 2025-11-11 

Reference Manual 

113 / 5394 

NXP Semiconductors 

Miscellaneous System Control Module (MSCM) 

## Table continued from the previous page... 

|Field|Function|
|---|---|
||0b - Not included<br>1b - Included|
|2<br>MMU|Memory Management Unit<br>Indicates whether virtual management capabilities are supported in this core.<br>For the Cortex-M7 cores in this chip, MMU = 0h.<br>0b - Not supported<br>1b - Supported|
|1<br>SIMD|SIMD/NEON Instruction Support<br>Indicates whether the instruction set extensions supporting SIMD and/or NEON capabilities are included in<br>the processor.<br>For the Cortex-M7 cores in this chip, SIMD = 1h.<br>0b - Not included<br>1b - Included|
|0<br>FPU|Floating Point Unit<br>Indicates whether the processor includes hardware support for floating point capabilities.<br>For the Cortex-M7 cores in this chip, FPU = 1h.<br>0b - Not included<br>1b - Included|



## 7.6.3.30 Processor 3 Type (CP3TYPE) 

## Offset 

|Register|Offset|
|---|---|
|CP3TYPE|80h|



## Function 

Defines the configuration information for processor 3 (CP3). It has the same field definitions and functionality as provided in Processor X Type (CPXTYPE). 

A read from any bus controller returns the appropriate processor information and attempted write accesses terminate with an error. 

Access: User or privileged read-only 

S32K3xx Reference Manual, Rev. 12, 2025-11-11 

Reference Manual 

114 / 5394 

NXP Semiconductors 

Miscellaneous System Control Module (MSCM) 

## Diagram 

|Bits<br>R<br>W<br>Reset<br>Bits<br>R<br>W<br>Reset|31<br>30<br>29<br>28|27<br>26<br>25<br>24|23<br>22<br>21<br>20|19<br>18<br>17<br>16|
|---|---|---|---|---|
||PERSONALITY||||
||||||
||0<br>1<br>0<br>0<br>0<br>0<br>1<br>1<br>0<br>1<br>0<br>0<br>1<br>1<br>0<br>1||||
||15<br>14<br>13<br>12|11<br>10<br>9<br>8|7<br>6<br>5<br>4|3<br>2<br>1<br>0|
||PERSONALITY||||
||||||
||0<br>0<br>1<br>1|0<br>1<br>1<br>1|0<br>0<br>1<br>1|0<br>0<br>1<br>1|



## Fields 

|Field|Function|
|---|---|
|31-0<br>PERSONALITY|Processor Personality<br>Defines the processor personality for CP3.<br>CP3 = Cortex-M7 core 3 and processor personality = 43_4D_37_33h.|



## 7.6.3.31 Processor 3 Number (CP3NUM) 

## Offset 

|Register|Offset|
|---|---|
|CP3NUM|84h|



## Function 

Defines the configuration information for processor 3 (CP3). It has the same field definitions and functionality as provided in Processor X Number (CPXNUM). 

A read from any bus controller returns the appropriate processor information and attempted write accesses terminate with an error. 

Access: User or privileged read-only 

S32K3xx Reference Manual, Rev. 12, 2025-11-11 

Reference Manual 

115 / 5394 

NXP Semiconductors 

Miscellaneous System Control Module (MSCM) 

## Diagram 

|Bits<br>R<br>W<br>Reset<br>Bits<br>R<br>W<br>Reset|31<br>30<br>29<br>28|27<br>26<br>25<br>24|23<br>22<br>21<br>20|19<br>18<br>17<br>16|19<br>18<br>17<br>16|
|---|---|---|---|---|---|
||0|||||
|||||||
||0<br>0<br>0<br>0<br>0<br>0<br>0<br>0<br>0<br>0<br>0<br>0<br>0<br>0<br>0<br>0|||||
||15<br>14<br>13<br>12|11<br>10<br>9<br>8|7<br>6<br>5<br>4|3<br>2<br>1<br>0||
||0||||CPN|
|||||||
||0<br>0<br>0<br>0|0<br>0<br>0<br>0|0<br>0<br>0<br>0|0<br>0<br>1<br>1||



## Fields 

|Field|Function|
|---|---|
|31-2<br>—|Reserved|
|1-0<br>CPN|Processor Number<br>Defines the logical processor number for CP3.<br>For Cortex-M7 core 3, processor number = 3. The processor personality is 0000_0003h.|



## 7.6.3.32 Processor 3 Count (CP3REV) 

## Offset 

|Register|Offset|
|---|---|
|CP3REV|88h|



## Function 

Defines the configuration information for processor 3 (CP3). It has the same field definitions and functionality as provided in Processor X Revision (CPXREV). 

A read from any bus controller returns the appropriate processor information and attempted write accesses terminate with an error. 

Access: User or privileged read-only 

S32K3xx Reference Manual, Rev. 12, 2025-11-11 

Reference Manual 

116 / 5394 

NXP Semiconductors 

Miscellaneous System Control Module (MSCM) 

## Diagram 

|Bits<br>R<br>W<br>Reset<br>Bits<br>R<br>W<br>Reset|31<br>30<br>29<br>28|27<br>26<br>25<br>24|23<br>22<br>21<br>20|19<br>18<br>17<br>16|
|---|---|---|---|---|
||0||||
||||||
||0<br>0<br>0<br>0<br>0<br>0<br>0<br>0<br>0<br>0<br>0<br>0<br>0<br>0<br>0<br>0||||
||15<br>14<br>13<br>12|11<br>10<br>9<br>8|7<br>6<br>5<br>4|3<br>2<br>1<br>0|
||0||RYPZ||
||||||
||0<br>0<br>0<br>0|0<br>0<br>0<br>0|u<br>u<br>u<br>u|u<br>u<br>u<br>u|



## Fields 

|Field|Function|
|---|---|
|31-8<br>—|Reserved|
|7-0<br>RYPZ|Processor Revision<br>Defines the processor revision for CP3.<br>For the Cortex-M7 processor, RYPZ = 12h corresponding to the r1p2 core release.|



## 7.6.3.33 Processor 3 Configuration 0 (CP3CFG0) 

## Offset 

|Register|Offset|
|---|---|
|CP3CFG0|8Ch|



## Function 

Defines the configuration information for processor 3 (CP3). It has the same field definitions and functionality as provided in Processor X Configuration 0 (CPXCFG0). 

A privileged read from any bus controller returns the appropriate processor information and attempted write accesses terminate with an error. 

Access: User or privileged read-only 

S32K3xx Reference Manual, Rev. 12, 2025-11-11 

Reference Manual 

117 / 5394 

NXP Semiconductors 

Miscellaneous System Control Module (MSCM) 

## Diagram 

|Bits<br>R<br>W<br>Reset<br>Bits<br>R<br>W<br>Reset|31<br>30<br>29<br>28|27<br>26<br>25<br>24|23<br>22<br>21<br>20|19<br>18<br>17<br>16|
|---|---|---|---|---|
||ICSZ||ICWY||
||||||
||0<br>0<br>0<br>0|0<br>1<br>1<br>0|0<br>0<br>0<br>0|0<br>0<br>1<br>0|
||||||
||15<br>14<br>13<br>12|11<br>10<br>9<br>8|7<br>6<br>5<br>4|3<br>2<br>1<br>0|
||DCSZ||DCWY||
||||||
||0<br>0<br>0<br>0|0<br>1<br>1<br>0|0<br>0<br>0<br>0|0<br>1<br>0<br>0|



## Fields 

|Field|Function|
|---|---|
|31-24<br>ICSZ|Level 1 Instruction Cache Size<br>Provides an encoded value of the instruction cache size.<br>The capacity of the memory is derived using the formula 2(8+SZ)and expressed as bytes. Here, ICSZ is a<br>nonzero value, and ICSZ = 0 indicates that the memory is not present.<br>For information about cache sizes, see the "Miscellaneous Control Module (MCM)" chapter.|
|23-16<br>ICWY|Level 1 Instruction Cache Ways<br>Provides the number of cache ways for the instruction cache.<br>For the Cortex-M7 cores in this chip, ICWY = 2h (2-way set-associative).|
|15-8<br>DCSZ|L1 Data Cache Size<br>Provides an encoded value of the data cache size.<br>The capacity of the memory is derived using the formula 2(8+SZ)and expressed as bytes. Here, DCSZ is a<br>nonzero value, and DCSZ = 0 indicates that the memory is not present.<br>For information about cache sizes, see the "Miscellaneous Control Module (MCM)" chapter.|
|7-0<br>DCWY|L1 Data Cache Ways<br>Provides the number of cache ways for the data cache.<br>For the Cortex-M7 cores in this chip, DCWY = 4h (4-way set-associative).|



## 7.6.3.34 Processor 3 Configuration 1 (CP3CFG1) 

## Offset 

|Register|Offset|
|---|---|
|CP3CFG1|90h|



S32K3xx Reference Manual, Rev. 12, 2025-11-11 

Reference Manual 

118 / 5394 

NXP Semiconductors 

Miscellaneous System Control Module (MSCM) 

## Function 

Defines the configuration information for processor 3 (CP3). It has the same field definitions and functionality as provided in Processor X Configuration 1 (CPXCFG1). 

A privileged read from any bus controller returns the appropriate processor information and attempted write accesses terminate with an error. 

Access: User or privileged read-only 

## Diagram 

|Bits<br>R<br>W<br>Reset<br>Bits<br>R<br>W<br>Reset|31<br>30<br>29<br>28|27<br>26<br>25<br>24|23<br>22<br>21<br>20|19<br>18<br>17<br>16|
|---|---|---|---|---|
||L2SZ||L2WY||
||||||
||u<br>u<br>u<br>u|u<br>u<br>u<br>u|u<br>u<br>u<br>u|u<br>u<br>u<br>u|
||||||
||15<br>14<br>13<br>12|11<br>10<br>9<br>8|7<br>6<br>5<br>4|3<br>2<br>1<br>0|
||0||||
||||||
||0<br>0<br>0<br>0|0<br>0<br>0<br>0|0<br>0<br>0<br>0|0<br>0<br>0<br>0|



Fields 

|Field|Function|
|---|---|
|31-24<br>L2SZ|L2 Cache Size<br>Provides an encoded value of the L2 cache size. The capacity of the memory is derived using the formula<br>2(8+SZ)and expressed as bytes. Here, L2SZ is a nonzero value, and L2SZ = 0 indicates that the memory is<br>not present.<br>For the Cortex-M7 cores in this chip, L2SZ = 0h (not present).|
|23-16<br>L2WY|L2 Cache Ways<br>Provides the number of cache ways for the L2 cache.<br>For the Cortex-M7 cores in this chip, L2WY = 0h (not present).|
|15-0<br>—|Reserved|



## 7.6.3.35 Processor 3 Configuration 2 (CP3CFG2) 

## Offset 

|Register|Offset|
|---|---|
|CP3CFG2|94h|



S32K3xx Reference Manual, Rev. 12, 2025-11-11 

Reference Manual 

119 / 5394 

NXP Semiconductors 

Miscellaneous System Control Module (MSCM) 

## Function 

Defines the configuration information for processor 3 (CP3). It has the same field definitions and functionality as provided in Processor X Configuration 2 (CPXCFG2). 

A privileged read from any bus controller returns the appropriate processor information and attempted write accesses terminate with an error. 

Access: User or privileged read-only 

## Diagram 

|Bits<br>R<br>W<br>Reset<br>Bits<br>R<br>W<br>Reset|31<br>30<br>29<br>28|27<br>26<br>25<br>24|23<br>22<br>21<br>20|19<br>18<br>17<br>16|
|---|---|---|---|---|
||DTCMSZ||ITCMSZ||
||||||
||u<br>u<br>u<br>u|u<br>u<br>u<br>u|u<br>u<br>u<br>u|u<br>u<br>u<br>u|
||||||
||15<br>14<br>13<br>12|11<br>10<br>9<br>8|7<br>6<br>5<br>4|3<br>2<br>1<br>0|
||0||||
||||||
||0<br>0<br>0<br>0|0<br>0<br>0<br>0|0<br>0<br>0<br>0|0<br>0<br>0<br>0|



## Fields 

|Field|Function|
|---|---|
|31-24<br>DTCMSZ|Tightly Coupled Data Memory Size<br>Provides an encoded value of the tightly coupled local data memory size.<br>The capacity of the memory is derived using the formula 2(8+SZ)and expressed as bytes. Here, TMLSZ is<br>a nonzero value, and TMLSZ = 0 indicates that the memory is not present.<br>For the Cortex-M7 cores in this chip, DTCMSZ = 8h in Decoupled mode (64 KB), and this value is not<br>applicable in Lockstep mode.|
|23-16<br>ITCMSZ|Instruction Tightly Coupled Memory Size<br>Provides an encoded value of the tightly coupled local instruction memory size. The capacity of the memory<br>is derived using the formula 2(8+SZ)and expressed as bytes. Here, TMUSZ is a nonzero value, and TMUSZ<br>= 0 indicates that the memory is not present.<br>For the Cortex-M7 cores in this chip, ITCMSZ = 7h in Decoupled mode (32 KB); this value is not applicable<br>in Lockstep mode.|
|15-0<br>—|Reserved|



S32K3xx Reference Manual, Rev. 12, 2025-11-11 

Reference Manual 

120 / 5394 

NXP Semiconductors 

Miscellaneous System Control Module (MSCM) 

## 7.6.3.36 Processor 3 Configuration 3 (CP3CFG3) 

## Offset 

|Register|Offset|
|---|---|
|CP3CFG3|98h|



## Function 

Defines the configuration information for processor 3 (CP3). It has the same field definitions and functionality as provided in the CPXCFG3 register. 

A privileged read from any bus controller returns the appropriate processor information and attempted write accesses terminate with an error. 

Access: User or privileged read-only 

## Diagram 

|Bits<br>R<br>W<br>Reset<br>Bits<br>R<br>W<br>Reset|31<br>30<br>29<br>28|27<br>26<br>25<br>24|23<br>22<br>21<br>20|23<br>22<br>21<br>20|19<br>18<br>17<br>16|19<br>18<br>17<br>16|19<br>18<br>17<br>16|19<br>18<br>17<br>16|
|---|---|---|---|---|---|---|---|---|
||0||||||||
||||||||||
||0<br>0<br>0<br>0|0<br>0<br>0<br>0|0<br>0<br>0<br>0||0<br>0<br>0<br>0||||
||||||||||
||15<br>14<br>13<br>12|11<br>10<br>9<br>8|7<br>6<br>5<br>4||3<br>2<br>1<br>0||||
||0|||CPY|CMP|MMU|SIMD|FPU|
||||||||||
||0<br>0<br>0<br>0|0<br>0<br>0<br>0|0<br>0<br>0<br>0||1<br>0<br>1<br>1||||



## Fields 

|Field|Function|
|---|---|
|31-5<br>—|Reserved|
|4<br>CPY|Cryptography<br>Indicates whether cryptography extensions are supported in the core.<br>For the Cortex-M7 cores in this chip, CPY = 0h.<br>0b - Not supported<br>1b - Supported|
|3<br>CMP|Core Memory Protection Unit<br>Indicates whether the core memory protection hardware is included in this core.<br>For the Cortex-M7 cores in this chip, CMP = 1h.|



Table continues on the next page... 

S32K3xx Reference Manual, Rev. 12, 2025-11-11 

Reference Manual 

121 / 5394 

NXP Semiconductors 

Miscellaneous System Control Module (MSCM) 

## Table continued from the previous page... 

|Field|Function|
|---|---|
||0b - Not included<br>1b - Included|
|2<br>MMU|Memory Management Unit<br>Indicates whether virtual management capabilities are supported in this core.<br>For the Cortex-M7 cores in this chip, MMU = 0h.<br>0b - Not supported<br>1b - Supported|
|1<br>SIMD|SIMD/NEON Instruction Support<br>Indicates whether the instruction set extensions supporting SIMD and/or NEON capabilities are included in<br>the processor.<br>For the Cortex-M7 cores in this chip, SIMD = 1h.<br>0b - Not included<br>1b - Included|
|0<br>FPU|Floating Point Unit<br>Indicates whether the processor includes hardware support for floating point capabilities.<br>For the Cortex-M7 cores in this chip, FPU = 1h.<br>0b - Not included<br>1b - Included|



## 7.6.3.37 Interrupt Router CPn Interrupt Status (IRCP0ISR0 - IRCP3ISR3) 

## Offset 

For n = 0 to 3; m = 0 to 3: 

|Register|Offset|
|---|---|
|IRCPnISRm|200h + (n × 20h) + (m × 8h)|



## Function 

Provides an interrupt bit map, where each bit defines the state of a unique MSI based on the initiating core. An MSI interrupt clears in an interrupt service routine by writing 1 to the appropriate field in IRCPnISRm. 

In this discussion, CPm represents the initiating core and CPn represents the target core for a core-to-core interrupt. For more information on interrupt source mapping, see the interrupt map file attached to this document. 

## For read access: 

- Reads to IRCPnISRm are only accessible in Privileged mode using 32-bit (word) accesses. 

- Privileged 32-bit read accesses from noncore (and nondebugger) bus controllers are treated as RAZ. 

S32K3xx Reference Manual, Rev. 12, 2025-11-11 

Reference Manual 

122 / 5394 

NXP Semiconductors 

Miscellaneous System Control Module (MSCM) 

- Attempted accesses in User mode or the ones using a size other than 32 bits are not permitted. They terminate with an error. 

- When CPn requests to read IRCPnISRm, MSCM returns the entire content of IRCPnISRm. 

- When a trusted core, as the IRCPCFG register indicates, requests to read IRCPnISRm, MSCM returns the entire content of IRCPnISRm. 

- When the debugger requests to read IRCPnISRm, MSCM returns the entire content of IRCPnISRm. 

- When CPm requests to read IRCPnISRm, MSCM returns the value of the corresponding status, CPm_INT, while not exposing all the other pending interrupts that the cores initiated. 

- When CPm requests to read IRCPnISRm, MSCM returns the value of the corresponding status, CPm_INT, in bit position 0, reflecting how CPm set the MSI when it wrote to IRCPnIGRm. All the other fields on the returned read value are zero-filled. 

For write access: 

- Writes to IRCPnISRm are only accessible in Privileged mode using 32-bit (word) accesses. 

- Attempted accesses in User mode or the ones using a size other than 32 bits are not permitted. They terminate with an error. 

- Writes to IRCPnISRm follow the Write 1 to Clear (W1C) protocol, whereby writing 1 causes the corresponding field to become 0, and writing 0 is ignored. 

- The target core, CPn, has full access to write to all the fields of IRCPnISRm. 

- A trusted core, as the IRCPCFG register indicates, has full access to write to all the fields of IRCPnISRm. 

- When CPm is different from CPn, the W1C action by CPm only clears IRCPnISRm[CPm_INT]. 

- The CPm field must present W1C in bit position 0 to clear its corresponding interrupt. Write data bits 1-31 that CPm presents are ignored. 

- Privileged write accesses from the noncore (and nondebugger) bus controllers are treated as Writes Ignored (WI). 

- Privileged write accesses from the debugger are treated as WI. 

Access: Privileged mode only 

## Diagram 

**==> picture [504 x 155] intentionally omitted <==**

**----- Start of picture text -----**<br>
Bits 31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16<br>R 0<br>W<br>Reset 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0<br>Bits 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0<br>CP3_ CP2_ CP1_ CP0_<br>R 0<br>INT  INT  INT  INT<br>W W1C W1C W1C W1C<br>Reset 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0<br>**----- End of picture text -----**<br>


Fields 

|Field|Function|
|---|---|
|31-4|Reserved|



Table continues on the next page... 

S32K3xx Reference Manual, Rev. 12, 2025-11-11 

Reference Manual 

123 / 5394 

NXP Semiconductors 

Miscellaneous System Control Module (MSCM) 

Table continued from the previous page... 

|Field|Function|
|---|---|
|—||
|3<br>CP3_INT|CP3-to-CPn Interrupt<br>Generates a directed interrupt initiated by core 3 targeting core n, if the appropriate interrupt routing bit<br>is enabled. The interrupt is negated when the target core, a trusted core, or core 3 writes 1 to clear the<br>field.<br>0b - No interrupt is asserted to CPn<br>1b - Interrupt to CPn is asserted|
|2<br>CP2_INT|CP2-to-CPn Interrupt<br>Generates a directed interrupt initiated by core 2 targeting core n, if the appropriate interrupt routing bit<br>is enabled. The interrupt is negated when the target core, a trusted core, or core 2 writes 1 to clear the<br>field.<br>0b - No interrupt is asserted to CPn<br>1b - Interrupt to CPn is asserted|
|1<br>CP1_INT|CP1-to-CPn Interrupt<br>Generates a directed interrupt initiated by core 1 targeting core n, if the appropriate interrupt routing bit<br>is enabled. The interrupt is negated when the target core, a trusted core, or core 1 writes 1 to clear the<br>field.<br>0b - No interrupt is asserted to CPn<br>1b - Interrupt to CPn is asserted|
|0<br>CP0_INT|CP0-to-CPn Interrupt<br>Generates a directed interrupt initiated by core 0 targeting core n, if the appropriate interrupt routing bit<br>is enabled. The interrupt is negated when the target core, a trusted core, or core 0 writes 1 to clear the<br>field.<br>0b - No interrupt asserted to CPn<br>1b - Interrupt to CPn asserted|



## 7.6.3.38 Interrupt Router CPn Interrupt Generation (IRCP0IGR0 - IRCP3IGR3) 

## Offset 

For n = 0 to 3; m = 0 to 3: 

|Register|Offset|
|---|---|
|IRCPnIGRm|204h + (n × 20h) + (m × 8h)|



## Function 

Provides a mechanism for cores to initiate an MSI to another core in the system. 

Privileged, 32-bit accesses from the: 

S32K3xx Reference Manual, Rev. 12, 2025-11-11 

Reference Manual 

124 / 5394 

NXP Semiconductors 

Miscellaneous System Control Module (MSCM) 

- Cortex-M7 cores are treated as RAZ/W. 

- Debugger are treated as RAZ/WI. 

- Noncore (and nondebugger) bus controllers are treated as RAZ/WI. 

Access: Privileged mode only. Attempted accesses in User mode or the ones using a size other than 32 bits are not permitted and terminate with an error. 

## Diagram 

**==> picture [504 x 155] intentionally omitted <==**

**----- Start of picture text -----**<br>
Bits 31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16<br>R 0<br>W<br>Reset 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0<br>Bits 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0<br>R 0 0<br>INT_<br>W<br>EN<br>Reset 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0<br>**----- End of picture text -----**<br>


Fields 

|Field|Function|
|---|---|
|31-1<br>—|Reserved|
|0<br>INT_EN|Interrupt Enable<br>Initiates a core-to-core interrupt targeting CPn, if CPm writes to this field (where n indicates the logical<br>core number (0-1) and m represents the interrupt number (0-3)).|



## 7.6.3.39 Interrupt Router Configuration (IRCPCFG) 

## Offset 

|Register|Offset|
|---|---|
|IRCPCFG|400h|



## Function 

Provides a mechanism to designate specific cores in the system as trusted. These trusted cores are allowed to access and manage outstanding MSIs. 

Privileged, 32-bit accesses from the: 

- Cortex-M7 cores are treated as R/W. 

- Debugger are treated as R/WI. 

- Noncore (and nondebugger) bus controllers are treated as RAZ/WI. 

S32K3xx Reference Manual, Rev. 12, 2025-11-11 

Reference Manual 

125 / 5394 

NXP Semiconductors 

Miscellaneous System Control Module (MSCM) 

Attempted accesses in User mode or the ones using a size other than 32 bits are not permitted. They terminate with an error. Access: Privileged mode only 

## Diagram 

|Bits<br>R<br>W<br>Reset<br>Bits<br>R<br>W<br>Reset|31|30<br>29<br>28|27<br>26<br>25<br>24|23<br>22<br>21<br>20|19<br>18<br>17<br>16|19<br>18<br>17<br>16|19<br>18<br>17<br>16|19<br>18<br>17<br>16|
|---|---|---|---|---|---|---|---|---|
||LOCK|0|||||||
||||||||||
||0|0<br>0<br>0|0<br>0<br>0<br>0|0<br>0<br>0<br>0|0<br>0<br>0<br>0||||
||||||||||
||15|14<br>13<br>12|11<br>10<br>9<br>8|7<br>6<br>5<br>4|3<br>2<br>1<br>0||||
|||0|||CP3_<br>TR|CP2_<br>TR|CP1_<br>TR|CP0_<br>TR|
||||||||||
||0|0<br>0<br>0|0<br>0<br>0<br>0|0<br>0<br>0<br>0|0<br>0<br>0<br>0||||



## Fields 

|Field|Function|
|---|---|
|31<br>LOCK|Lock<br>Provides a locking mechanism that can be used to limit the ability to write to the register. After you write<br>1 to this field, it remains 1 until the next reset.<br>0b - Register can be written by any privileged write<br>1b - Register is locked (read-only) until the next reset|
|30-4<br>—|Reserved|
|3<br>CP3_TR|CP3 as Trusted Core<br>Indicates whether CP3 is a trusted core with access to read the full contents of IRCPnISRm.<br>0b - Not trusted<br>1b - Trusted|
|2<br>CP2_TR|CP2 as Trusted Core<br>Indicates whether CP2 is a trusted core with access to read the full contents of IRCPnISRm.<br>0b - Not trusted<br>1b - Trusted|
|1<br>CP1_TR|CP1 as Trusted Core<br>Indicates whether CP1 is a trusted core with access to read the full contents of IRCPnISRm.<br>0b - Not trusted<br>1b - Trusted|



Table continues on the next page... 

S32K3xx Reference Manual, Rev. 12, 2025-11-11 

Reference Manual 

126 / 5394 

NXP Semiconductors 

Miscellaneous System Control Module (MSCM) 

## Table continued from the previous page... 

|Field|Function|
|---|---|
|0<br>CP0_TR|CP0 as Trusted Core<br>Indicates whether CP0 is a trusted core with access to read the full contents of IRCPnISRm.<br>0b - Not trusted<br>1b - Trusted|



## 7.6.3.40 Memory Execution Controls (XN_CTRL) 

## Offset 

|Register|Offset|
|---|---|
|XN_CTRL|500h|



## Function 

Controls whether an instruction fetch, also known as a code fetch or executable fetch, is allowed for SRAM and TCM. 

**==> picture [506 x 254] intentionally omitted <==**

**----- Start of picture text -----**<br>
  NOTE<br>• This register does not inhibit HSE_B instruction accesses.<br>• Only PRAM0, PRAM1, and PRAM2 support code execution control.<br>Diagram<br>Bits 31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16<br>R 0 CM7_3 CM7_2 CM7_1 CM7_0 CM7_3 CM7_2 CM7_1 CM7_0<br>HLK  SLK<br>W _D... _D... _D... _D... _D... _D... _D... _D...<br>Reset 0 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0<br>Bits 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0<br>PRAM<br>R CM7_3 CM7_2 CM7_1 CM7_0 CM7_3 CM7_2 CM7_1 CM7_0 0 _3  PRAM PRAM PRAM<br>_I... _I... _I... _I... _D... _D... _D... _D... _2  _1  0<br>W<br>Reset 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0<br>Fields<br>**----- End of picture text -----**<br>


|Field|Function|
|---|---|
|31<br>HLK|Hard Lock<br>Enables hard lock.<br>This field locks the register to disable writes until the next hardware reset.|
|Table continues on the next page...||



S32K3xx Reference Manual, Rev. 12, 2025-11-11 

Reference Manual 

127 / 5394 

NXP Semiconductors 

Miscellaneous System Control Module (MSCM) 

## Table continued from the previous page... 

|Field|Function|
|---|---|
||0b - Disable<br>1b - Enable|
|30<br>SLK|Soft Lock<br>Enables soft lock.<br>This field locks the register to disable writes until this field becomes 0.<br>0b - Disable<br>1b - Enable|
|29-24<br>—|Reserved|
|23<br>CM7_3_DTCM|Transaction Control For Cortex-M7_3 DTCM<br>Does not select Cortex-M7_3 as target. All code fetch or executable fetch transactions to Cortex-M7_3<br>DTCM are not generated because Cortex-M7_3 DTCM is not selected (backdoor access).<br>0b - Transaction enabled<br>1b - Transaction disabled|
|22<br>CM7_2_DTCM|Transaction Control For Cortex-M7_2 DTCM<br>Does not select Cortex-M7_2 as target. All code fetch or executable fetch transactions to Cortex-M7_2<br>DTCM are not generated because Cortex-M7_2 DTCM is not selected (backdoor access).<br>0b - Transaction enabled<br>1b - Transaction disabled|
|21<br>CM7_1_DTCM|Transaction Control For Cortex-M7_1 DTCM<br>Does not select Cortex-M7_1 as target. All code fetch or executable fetch transactions to Cortex-M7_1<br>DTCM are not generated because Cortex-M7_1 DTCM is not selected (backdoor access).<br>0b - Transaction enabled<br>1b - Transaction disabled|
|20<br>CM7_0_DTCM|Transaction Control For Cortex-M7_0 DTCM<br>Does not select Cortex-M7_0 as target. All code fetch or executable fetch transactions to Cortex-M7_0<br>DTCM are not generated because Cortex-M7_0 DTCM is not selected (backdoor access).<br>0b - Transaction enabled<br>1b - Transaction disabled|
|19<br>CM7_3_DIS_D0<br>_D1TCM_EXEC|Disable D0 and D1 TCM Execution For Cortex-M7_3<br>Disables D0 and D1 TCM execution for Cortex-M7_3. It is provided to the core. If execution is disabled, it<br>is taken as illegal access by the core.|



Table continues on the next page... 

S32K3xx Reference Manual, Rev. 12, 2025-11-11 

Reference Manual 

128 / 5394 

NXP Semiconductors 

Miscellaneous System Control Module (MSCM) 

## Table continued from the previous page... 

|Field|Function|
|---|---|
||0b - Enable<br>1b - Disable|
|18<br>CM7_2_DIS_D0<br>_D1TCM_EXEC|Disable D0 and D1 TCM Execution For Cortex-M7_2<br>Disables D0 and D1 TCM execution for Cortex-M7_2. It is provided to the core. If execution is disabled, it<br>is taken as illegal access by the core.<br>0b - Enable<br>1b - Disable|
|17<br>CM7_1_DIS_D0<br>_D1TCM_EXEC|D0 and D1 TCM Execution For Cortex-M7_1<br>Disables D0 and D1 TCM execution for Cortex-M7_1. It is provided to the core. If execution is disabled, it<br>is taken as illegal access by the core.<br>0b - Enable<br>1b - Disable|
|16<br>CM7_0_DIS_D0<br>_D1TCM_EXEC|D0 And D1 TCM Execution For Cortex-M7_0<br>Disables D0 and D1 TCM execution for Cortex-M7_0. It is provided to the core. If execution is disabled, it<br>is taken as illegal access by the core.<br>0b - Enable<br>1b - Disable|
|15<br>CM7_3_ITCM|Transaction Control For Cortex-M7_3 ITCM<br>Does not select Cortex-M7_3 ITCM as target. All code fetch or executable fetch transactions to Cortex-<br>M7_3 ITCM are not generated because Cortex-M7_3 ITCM is not selected (backdoor access).<br>0b - Execution enabled<br>1b - Execution disabled|
|14<br>CM7_2_ITCM|Transaction Control For Cortex-M7_2 ITCM<br>Does not select Cortex-M7_2 ITCM as target. All code fetch or executable fetch transactions to Cortex-<br>M7_2 ITCM are not generated because Cortex-M7_2 ITCM is not selected (backdoor access).<br>0b - Execution enabled<br>1b - Execution disabled|
|13<br>CM7_1_ITCM|Transaction Control For Cortex-M7_1 ITCM<br>Does not select Cortex-M7_1 ITCM as target. All code fetch or executable fetch transactions to Cortex-<br>M7_1 ITCM are not generated because Cortex-M7_1 ITCM is not selected (backdoor access).<br>0b - Execution enabled<br>1b - Execution disabled|
|12|Transaction Control For Cortex-M7_0 ITCM|



Table continues on the next page... 

S32K3xx Reference Manual, Rev. 12, 2025-11-11 

Reference Manual 

129 / 5394 

NXP Semiconductors 

Miscellaneous System Control Module (MSCM) 

## Table continued from the previous page... 

|Field|Function|
|---|---|
|CM7_0_ITCM|Specifies the execution status.<br>This field does not select Cortex-M7_0 ITCM as target. All code fetch or executable fetch transactions to<br>Cortex-M7_0 ITCM are not generated because Cortex-M7_0 ITCM is not selected (backdoor access).<br>0b - Execution enabled<br>1b - Execution disabled|
|11<br>CM7_3_DIS_IT<br>CM_EXEC|ITCM Execution for Cortex-M7_3<br>Disables ITCM execution for Cortex-M7_3. It is provided to the core. If execution is disabled, it is<br>considered an illegal access by the core.<br>0b - Enable<br>1b - Disable|
|10<br>CM7_2_DIS_IT<br>CM_EXEC|ITCM Execution for Cortex-M7_2<br>Disables ITCM execution for Cortex-M7_2. It is provided to the core. If execution is disabled, it is<br>considered an illegal access by the core.<br>0b - Enable<br>1b - Disable|
|9<br>CM7_1_DIS_IT<br>CM_EXEC|ITCM Execution For Cortex-M7_1<br>Disables ITCM execution for Cortex-M7_1. It is provided to the core. If execution is disabled, it is<br>considered an illegal access by the core.<br>0b - Enable<br>1b - Disable|
|8<br>CM7_0_DIS_IT<br>CM_EXEC|ITCM Execution For Cortex-M7_0<br>Disables ITCM execution for Cortex-M7_0. It is provided to the core. If execution is disabled, it is<br>considered an illegal access by the core.<br>0b - Enable<br>1b - Disable|
|7-4<br>—|Reserved|
|3<br>PRAM_3|Transaction Control For PRAM 3<br>Does not select PRAM3 as target. All code fetch or executable fetch transactions to PRAM3 are not<br>generated because PRAM3 is not selected.<br>0b - Transaction enabled<br>1b - Transaction disabled|
|2|Transaction Control For PRAM 2|



Table continues on the next page... 

S32K3xx Reference Manual, Rev. 12, 2025-11-11 

Reference Manual 

130 / 5394 

NXP Semiconductors 

Miscellaneous System Control Module (MSCM) 

|Table continued from the previous page...|Table continued from the previous page...|
|---|---|
|Field|Function|
|PRAM_2|Does not select PRAM2 as target. All code fetch or executable fetch transactions to PRAM2 are not<br>generated because PRAM2 is not selected.<br>0b - Transaction enabled<br>1b - Transaction disabled|
|1<br>PRAM_1|Transaction Control For PRAM 1<br>Does not select PRAM1 as target. All code fetch or executable fetch transactions to PRAM1 are not<br>generated because PRAM1 is not selected.<br>0b - Transaction enabled<br>1b - Transaction disabled|
|0<br>PRAM0|Transaction Control For PRAM 0<br>Does not select PRAM0 as target. All code fetch or executable fetch transactions to PRAM0 are not<br>generated because PRAM0 is not selected.<br>0b - Transaction enabled<br>1b - Transaction disabled|



## 7.6.3.41 Enable Interconnect Error Detection (ENEDC) 

## Offset 

|Register|Offset|
|---|---|
|ENEDC|600h|



## Function 

Enables interconnect error detection. 

For more information, see the FCCU file attached to this document. 

Access: Privileged mode only 

## Diagram 

**==> picture [505 x 148] intentionally omitted <==**

**----- Start of picture text -----**<br>
Bits 31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16<br>R 0 0 0<br>ADD_ CM7_1 ADD_ CM7_0 ADD_ ADD_ ADD_ ADD_<br>AIPS2  AIPS1  AIPS0  QSPI<br>W CM7... _T... CM7... _T... AIP... AIP... AIP... QSPI<br>Reset 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0<br>Bits 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0<br>R ADD_ PRAM ADD_ PRAM PF1_P PF0_P PF0_P 0 CM7_1 CM7_1 0 CM7_0 CM7_0<br>ENET  HSE  EDMA<br>W PRA... 1  PRA... 0  0_... 1_... 0_... _A... _A... _A... _A...<br>Reset 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0<br>**----- End of picture text -----**<br>


S32K3xx Reference Manual, Rev. 12, 2025-11-11 

Reference Manual 

131 / 5394 

NXP Semiconductors 

Miscellaneous System Control Module (MSCM) 

## Fields 

|Field|Function|
|---|---|
|31-30<br>—|Reserved|
|29<br>ADD_CM7_1_T<br>CM|Address Check For Cortex-M7_1_TCM<br>Enables address check for the Cortex-M7_1_TCM backdoor path.<br>0b - Disable<br>1b - Enable|
|28<br>CM7_1_TCM|Write Data Check For Cortex-M7_1_TCM<br>Enables write data check for the Cortex-M7_1_TCM backdoor path.<br>0b - Disable<br>1b - Enable|
|27<br>ADD_CM7_0_T<br>CM|Address Check For Cortex-M7_0_TCM<br>Enables address check for the Cortex-M7_0_TCM backdoor path.<br>0b - Disable<br>1b - Enable|
|26<br>CM7_0_TCM|Write Data Check For Cortex-M7_0_TCM<br>Enables write data check for the Cortex-M7_0_TCM backdoor path.<br>0b - Disable<br>1b - Enable|
|25<br>ADD_AIPS2|Address Check For AIPS2<br>Enables address check for the AIPS2 path.<br>0b - Disable<br>1b - Enable|
|24<br>AIPS2|Write Data Check For AIPS2<br>Enables write data check for the AIPS2 path.<br>0b - Disable<br>1b - Enable|
|23<br>ADD_AIPS1|Address Check For AIPS1<br>Enables address check for the AIPS1 path.<br>0b - Disable<br>1b - Enable|
|22|Write Data Check For AIPS1|



Table continues on the next page... 

S32K3xx Reference Manual, Rev. 12, 2025-11-11 

Reference Manual 

132 / 5394 

NXP Semiconductors 

Miscellaneous System Control Module (MSCM) 

## Table continued from the previous page... 

|Field|Function|
|---|---|
|AIPS1|Enables write data check for the AIPS1 path.<br>0b - Disable<br>1b - Enable|
|21<br>ADD_AIPS0|Address Check For AIPS0<br>Enables address check for the AIPS0 path.<br>0b - Disable<br>1b - Enable|
|20<br>AIPS0|Write Data Check For AIPS0<br>Enables write data check for the AIPS0 path.<br>0b - Disable<br>1b - Enable|
|19<br>ADD_QSPI|Address Check For QuadSPI<br>Enables address check for the QuadSPI path.<br>0b - Disable<br>1b - Enable|
|18<br>QSPI|Write Data Check For QuadSPI<br>Enables write data check for the QuadSPI path.<br>0b - Disable<br>1b - Enable|
|17<br>—|Reserved|
|16<br>—|Reserved|
|15<br>ADD_PRAM1|Address Check For PRAM1<br>Enables address check for the PRAM1 path.<br>0b - Disable<br>1b - Enable|
|14<br>PRAM1|Write Data Check For PRAM1<br>Enables write data check for the PRAM1 path.<br>0b - Disable<br>1b - Enable|



Table continues on the next page... 

S32K3xx Reference Manual, Rev. 12, 2025-11-11 

Reference Manual 

133 / 5394 

NXP Semiconductors 

Miscellaneous System Control Module (MSCM) 

## Table continued from the previous page... 

|Field|Function|
|---|---|
|13<br>ADD_PRAM0|Address Check For PRAM0<br>Enables address check for the PRAM0 path.<br>0b - Disable<br>1b - Enable|
|12<br>PRAM0|Write Data Check For PRAM0<br>Enables write data check for the PRAM0 path.<br>0b - Disable<br>1b - Enable|
|11<br>PF1_P0_ACHK|Address Check for PF1 P0<br>Enables address check for flash memory controller 1 P0.<br>0b - Disable<br>1b - Enable|
|10<br>PF0_P1_ACHK|Address Check for PF0 P1<br>Enables address check for flash memory controller 0 P1.<br>0b - Disable<br>1b - Enable|
|9<br>PF0_P0_ACHK|Address Check for PF0 P0<br>Enables address check for flash controller 0 P0.<br>0b - Disable<br>1b - Enable|
|8<br>—|Reserved|
|7<br>CM7_1_AHBP|Read Data Check For Cortex-M7_1_AHBP<br>Enables read data check for the Cortex-M7_1_AHBP path.<br>0b - Disable<br>1b - Enable|
|6<br>CM7_1_AHBM|Read Data Check For Cortex-M7_1_AHBM<br>Enables read data check for the Cortex-M7_1_AHBM path.<br>0b - Disable<br>1b - Enable|
|5|Read Data Check For ENET|



Table continues on the next page... 

S32K3xx Reference Manual, Rev. 12, 2025-11-11 

Reference Manual 

134 / 5394 

NXP Semiconductors 

Miscellaneous System Control Module (MSCM) 

## Table continued from the previous page... 

|Field|Function|
|---|---|
|ENET|Enables read data check for the ENET path.<br>0b - Disable<br>1b - Enable|
|4<br>HSE|Read Data Check For HSE_B<br>Enables read data check for the HSE_B path.<br>0b - Disable<br>1b - Enable|
|3<br>—|Reserved|
|2<br>EDMA|Read Data Check For eDMA<br>Enables read data check for the eDMA path.<br>0b - Disable<br>1b - Enable|
|1<br>CM7_0_AHBP|Read Data Check For Cortex-M7_0_AHBP<br>Enables read data check for the Cortex-M7_0_AHBP path.<br>0b - Disable<br>1b - Enable|
|0<br>CM7_0_AHBM|Read Data Check For Cortex-M7_0_AHBM<br>Enables read data check for the Cortex-M7_0_AHBM path.<br>0b - Disable<br>1b - Enable|



## 7.6.3.42 Enable Interconnect Error Detection (ENEDC1) 

## Offset 

|Register|Offset|
|---|---|
|ENEDC1|604h|



## Function 

Enables interconnect error detection. 

For more information, see the FCCU file attached to this document. 

Access: Privileged mode only 

S32K3xx Reference Manual, Rev. 12, 2025-11-11 

Reference Manual 

135 / 5394 

NXP Semiconductors 

Miscellaneous System Control Module (MSCM) 

## Diagram 

|Bits<br>R<br>W<br>Reset<br>Bits<br>R<br>W<br>Reset|31<br>30<br>29<br>28|31<br>30<br>29<br>28|31<br>30<br>29<br>28|31<br>30<br>29<br>28|27|26|25<br>24|25<br>24|23<br>22<br>21<br>20|23<br>22<br>21<br>20|23<br>22<br>21<br>20|23<br>22<br>21<br>20|19<br>18|19<br>18|17|16|
|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|
||0|||PRAM<br>3_A...|PRAM<br>3_W...|0||TCM_<br>GSK...|SLV_C<br>HK...|SLV_C<br>HK...|SLV_C<br>HK...|MSTR<br>_CH...|MSTR<br>_CH...|CM7_3<br>_A...|CM7_3<br>_A...|0|
||||||||||||||||||
||0<br>0<br>0<br>0||||0|0|0<br>0||0<br>0<br>0<br>0||||0<br>0||0|0|
||||||||||||||||||
||15<br>14<br>13<br>12||||11|10|9<br>8||7<br>6<br>5<br>4||||3<br>2||1|0|
||ADD_<br>CM7...|CM7_2<br>_T...|CM7_3<br>_A...|CM7_3<br>_W...|ADD_<br>EN_...|EN_P<br>RAM2|0||MSTR<br>_CH...|EDMA<br>_S1|EDMA<br>_S0|PF1_P<br>1_...|CM7_2<br>_A...|CM7_2<br>_A...||0|
||||||||||||||||||
||0<br>0<br>0<br>0||||0|0|0<br>0||0<br>0<br>0<br>0||||0<br>0||0|0|



## Fields 

|Field|Function|
|---|---|
|31-29<br>—|Reserved|
|28<br>PRAM3_ACHK|Address Check for PRAM3<br>Enables address check for PRAM3.<br>0b - Disable<br>1b - Enable|
|27<br>PRAM3_WCHK|Write Data Check for PRAM3<br>Enables write data check for PRAM3.<br>0b - Disable<br>1b - Enable|
|26-25<br>—|Reserved|
|24<br>TCM_GSKT_A<br>DDR_CHK|TCM Gasket Address Check<br>Enables address check for TCM gasket.<br>0b - Disable<br>1b - Enable|
|23<br>SLV_CHK_ACE<br>_ACCEL_RESU<br>LT_M1_GSKT_<br>ADDR_CHK|Target Check Accelerator Result M1 Gasket Address Check<br>Enables gasket address check for target accelerator result.<br>0b - Disable<br>1b - Enable|
|22|Target Check Accelerator Result M1 Gasket Write Data Check|



Table continues on the next page... 

S32K3xx Reference Manual, Rev. 12, 2025-11-11 

Reference Manual 

136 / 5394 

NXP Semiconductors 

Miscellaneous System Control Module (MSCM) 

## Table continued from the previous page... 

|Field|Function|
|---|---|
|SLV_CHK_ACE<br>_ACCEL_RESU<br>LT_M1_GSKT_<br>WDATA_CHK|Enables gasket write data check for target accelerator result.<br>0b - Disable<br>1b - Enable|
|21<br>SLV_CHK_ACE<br>_ADDR_CHK|Target Check Accelerator Address<br>Enables target check for accelerator address.<br>0b - Disable<br>1b - Enable|
|20<br>MSTR_CHK_A<br>CE_FEED_CHK|Controller Check Accelerator Feed<br>Enables controller check for accelerator feed.<br>0b - Disable<br>1b - Enable|
|19<br>MSTR_CHK_A<br>CE_RESULT_C<br>HK|Controller Check Accelerator Result<br>Enables controller check for accelerator result.<br>0b - Disable<br>1b - Enable|
|18<br>CM7_3_AHBP|Enable Read Data Check Cortex-M7_3_AHBP<br>Enables the read data check for the Cortex-M7_3_AHBP path.<br>0b - Disable<br>1b - Enable|
|17<br>CM7_3_AHBM|Enable Read Data Check Cortex-M7_3_AHBM<br>Enables the read data check for the Cortex-M7_3_AHBM path.<br>0b - Disable<br>1b - Enable|
|16<br>—|Reserved|
|15<br>ADD_CM7_2_T<br>CM|Enable Address Check Cortex-M7_2_TCM<br>Enables the address data check for the Cortex-M7_2_TCM backdoor path.<br>0b - Disable<br>1b - Enable|
|14<br>CM7_2_TCM|Enable Write Data Check Cortex-M7_2_TCM<br>Enables write data check for the Cortex-M7_2_TCM backdoor path.|



Table continues on the next page... 

S32K3xx Reference Manual, Rev. 12, 2025-11-11 

Reference Manual 

137 / 5394 

NXP Semiconductors 

Miscellaneous System Control Module (MSCM) 

## Table continued from the previous page... 

|Field|Function|
|---|---|
||0b - Disable<br>1b - Enable|
|13<br>CM7_3_ADDR_<br>CHK|Enable Address Check Cortex-M7_3_TCM<br>Enables the address check for the Cortex-M7_3_TCM backdoor path.<br>0b - Disable<br>1b - Enable|
|12<br>CM7_3_WDAT<br>A_CHK|Enable Write Data Check Cortex-M7_3_TCM<br>Enables write data check for the Cortex-M7_3_TCM backdoor path.<br>0b - Disable<br>1b - Enable|
|11<br>ADD_EN_PRA<br>M2|Enable Address Check PRAM 2<br>Enables the address check for the PRAM 2 path.<br>0b - Disable<br>1b - Enable|
|10<br>EN_PRAM2|Enable Write Data Check PRAM 2<br>Enables the write data check for PRAM2.<br>0b - Disable<br>1b - Enable|
|9-8<br>—|Reserved|
|7<br>MSTR_CHECK<br>_ENET1|Controller Check ENET1<br>Enables the controller check for ENET1.<br>0b - Disable<br>1b - Enable|
|6<br>EDMA_S1|Enable Address Check eDMA S1<br>Enables the address check for the eDMA S1 path.<br>0b - Disable<br>1b - Enable|
|5<br>EDMA_S0|Enable Address Check eDMA S0<br>Enables address check for the eDMA S0 path.|
|Table continues on the next page...||



S32K3xx Reference Manual, Rev. 12, 2025-11-11 

Reference Manual 

138 / 5394 

NXP Semiconductors 

Miscellaneous System Control Module (MSCM) 

## Table continued from the previous page... 

|Field|Function|
|---|---|
||0b - Disable<br>1b - Enable|
|4<br>PF1_P1_ACHK|Enable Address Check PF1 P1<br>Enables address check for flash controller 1 P1.<br>0b - Disable<br>1b - Enable|
|3<br>CM7_2_AHBP|Enable Read Data Check Cortex-M7_2_AHBP<br>Enables read data check for the Cortex-M7_2_AHBP path.<br>0b - Disable<br>1b - Enable|
|2<br>CM7_2_AHBM|Enable Read Data Check Cortex-M7_2_AHBM<br>Enables read data check for the Cortex-M7_2_AHBM path.<br>0b - Disable<br>1b - Enable|
|1-0<br>—|Reserved|



## 7.6.3.43 AHB Gasket Configuration (IAHBCFGREG) 

## Offset 

|Register|Offset|
|---|---|
|IAHBCFGREG|700h|



## Function 

Controls the functional configuration of the AHB gaskets located on the platform. 

Access: Privileged mode only 

S32K3xx Reference Manual, Rev. 12, 2025-11-11 

Reference Manual 

139 / 5394 

NXP Semiconductors 

Miscellaneous System Control Module (MSCM) 

## Diagram 

|Bits<br>R<br>W<br>Reset<br>Bits<br>R<br>W<br>Reset|31<br>30<br>29<br>28|31<br>30<br>29<br>28|31<br>30<br>29<br>28|31<br>30<br>29<br>28|27<br>26<br>25<br>24|27<br>26<br>25<br>24|27<br>26<br>25<br>24|27<br>26<br>25<br>24|23<br>22<br>21<br>20|23<br>22<br>21<br>20|23<br>22<br>21<br>20|23<br>22<br>21<br>20|19<br>18<br>17<br>16|19<br>18<br>17<br>16|19<br>18<br>17<br>16|19<br>18<br>17<br>16|
|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|
||Reserved|||HSE_<br>CMX...|ACE_<br>GSK...|ACE_<br>ACC...|CM7_3<br>_A...|CM7_3<br>_A...|CM7_2<br>_A...|CM7_1<br>_A...|CM7_0<br>_A...|CM7_3<br>_A...|CM7_2<br>_A...|CM7_1<br>_A...|CM7_0<br>_A...|PRAM<br>2_D...|
||0<br>0<br>0<br>0||||0<br>0<br>0<br>0||||0<br>0<br>0<br>0||||0<br>0<br>0<br>0||||
||||||||||||||||||
||15<br>14<br>13<br>12||||11<br>10<br>9<br>8||||7<br>6<br>5<br>4||||3<br>2<br>1<br>0||||
||TCM_<br>PRA...|PRAM<br>1_D...|GMAC<br>1_D...|USDH<br>C_D...|AIPS0<br>_D...|AIPS2<br>_D...|AIPS1<br>_D...|CM7_2<br>_A...|CM7_1<br>_A...|CM7_0<br>_A...|QSPI_<br>DI...|TCM_<br>DIS...|HSE_<br>DIS...|DMA_<br>AXB...|DMA_<br>AXB...|EMAC<br>_DI...|
||0<br>0<br>0<br>0||||0<br>0<br>0<br>0||||0<br>0<br>0<br>0||||0<br>0<br>0<br>0||||



## Fields 

|Field|Function|
|---|---|
|31-29<br>—|Reserved|
|28<br>HSE_CMX_GS<br>KT_DAP_DISA<br>BLE_OPT_WR|HSE CMX Gasket Disable Write Optimization<br>Determines whether write burst optimizations in the HSE_B CMX gasket are enabled or disabled.<br>Enabling optimization allows performance improvements during burst writes. Disabling optimization is<br>required only if you expect an early write burst termination from a controller.<br>0b - Enable<br>1b - Disable|
|27<br>ACE_GSKT_DI<br>SABLE_OPT_W<br>R|ACE Gasket Disable Write Optimization<br>Determines whether write burst optimizations in the ACE gasket are enabled or disabled.<br>Enabling optimization allows performance improvements during burst writes. Disabling optimization is<br>required only if you expect an early write burst termination from a controller.<br>0b - Enable<br>1b - Disable|
|26<br>ACE_ACCEL_R<br>ESULT_M1_GS<br>KT_DISABLE_<br>OPT_WR|Ace Accelerator Disable Write Optimization<br>Determines whether write burst optimizations in the ace accelerator result M1 gasket are enabled<br>or disabled.<br>Enabling optimization allows performance improvements during burst writes. Disabling optimization is<br>required only if you expect an early write burst termination from a controller.<br>0b - Enable<br>1b - Disable|
|25<br>CM7_3_AHBS_<br>DIS_WR_OPT|Cortex-M7_3 AHBS Disable Write Optimization<br>Determines whether write burst optimizations in the Cortex-M7_3_AHBS gasket are enabled or disabled.|



Table continues on the next page... 

S32K3xx Reference Manual, Rev. 12, 2025-11-11 

Reference Manual 

140 / 5394 

NXP Semiconductors 

Miscellaneous System Control Module (MSCM) 

## Table continued from the previous page... 

|Field|Function|
|---|---|
||Enabling optimization allows performance improvements during burst writes. Disabling optimization is<br>required only if you expect an early write burst termination from a controller.<br>0b - Enable<br>1b - Disable|
|24<br>CM7_3_AHBP_<br>DIS_WR_OPT|Cortex-M7_3 AHBP Disable Write Optimization<br>Determines whether write burst optimizations in the Cortex-M7_3_AHBP gasket are enabled or disabled.<br>Enabling optimization allows performance improvements during burst writes. Disabling optimization is<br>required only if you expect an early write burst termination from a controller.<br>0b - Enable<br>1b - Disable|
|23<br>CM7_2_AHBP_<br>DIS_WR_OPT|Cortex-M7_2 AHBP Disable Write Optimization<br>Determines whether write burst optimizations in the Cortex-M7_2_AHBP gasket are enabled or disabled.<br>Enabling optimization allows performance improvements during burst writes. Disabling optimization is<br>required only if you expect an early write burst termination from a controller.<br>0b - Enable<br>1b - Disable|
|22<br>CM7_1_AHBP_<br>DIS_WR_OPT|Cortex-M7_1 AHBP Disable Write Optimization<br>Determines whether write burst optimizations in the Cortex-M7_1_AHBP gasket are enabled or disabled.<br>Enabling optimization allows performance improvements during burst writes. Disabling optimization is<br>required only if you expect an early write burst termination from a controller.<br>0b - Enable<br>1b - Disable|
|21<br>CM7_0_AHBP_<br>DIS_WR_OPT|Cortex-M7_0 AHBP Disable Write Optimization<br>Determines whether write burst optimizations in the Cortex-M7_0_AHBP gasket are enabled or disabled.<br>Enabling optimization allows performance improvements during burst writes. Disabling optimization is<br>required only if you expect an early write burst termination from a controller.<br>0b - Enable<br>1b - Disable|
|20<br>CM7_3_AHBM_<br>DIS_WR_OPT|Cortex-M7_3 AHBM Disable Write Optimization<br>Determines whether write burst optimizations in the Cortex-M7_3_AHBM gasket are enabled or disabled.<br>Enabling optimization allows performance improvements during burst writes. Disabling optimization is<br>required only if you expect an early write burst termination from a controller.<br>0b - Enable<br>1b - Disable|



Table continues on the next page... 

S32K3xx Reference Manual, Rev. 12, 2025-11-11 

Reference Manual 

141 / 5394 

NXP Semiconductors 

Miscellaneous System Control Module (MSCM) 

## Table continued from the previous page... 

|Field|Function|
|---|---|
|19<br>CM7_2_AHBM_<br>DIS_WR_OPT|Cortex-M7_2 AHBM Disable Write Optimization<br>Determines whether write burst optimizations in the Cortex-M7_2_AHBM gasket are enabled or disabled.<br>Enabling optimization allows performance improvements during burst writes. Disabling optimization is<br>required only if you expect an early write burst termination from a controller.<br>0b - Enable<br>1b - Disable|
|18<br>CM7_1_AHBM_<br>DIS_WR_OPT|Cortex-M7_1 AHBM Disable Write Optimization<br>Determines whether write burst optimizations in the Cortex-M7_1_AHBM gasket are enabled or disabled.<br>Enabling optimization allows performance improvements during burst writes. Disabling optimization is<br>required only if you expect an early write burst termination from a controller.<br>0b - Enable<br>1b - Disable|
|17<br>CM7_0_AHBM_<br>DIS_WR_OPT|Cortex-M7_0 AHBM Disable Write Optimization<br>Determines whether write burst optimizations in the Cortex-M7_0_AHBM gasket are enabled or disabled.<br>Enabling optimization allows performance improvements during burst writes. Disabling optimization is<br>required only if you expect an early write burst termination from a controller.<br>0b - Enable<br>1b - Disable|
|16<br>PRAM2_DIS_W<br>R_OPT|PRAM2 Disable Write Optimization<br>Determines whether write burst optimizations in the PRAM2 gasket are enabled or disabled.<br>Enabling optimization allows performance improvements during burst writes. Disabling optimization is<br>required only if you expect an early write burst termination from a controller.<br>0b - Enable<br>1b - Disable|
|15<br>TCM_PRAM_DI<br>S_WR_OPT|TCM PRAM Disable Write Optimization<br>Determines whether write burst optimizations in the TCM_PRAM gasket are enabled or disabled.<br>Enabling optimization allows performance improvements during burst writes. Disabling optimization is<br>required only if you expect an early write burst termination from a controller.<br>0b - Enable<br>1b - Disable|
|14<br>PRAM1_DIS_W<br>R_OPT|PRAM1 Disable Write Optimization<br>Determines whether write burst optimizations in the PRAM1 gasket are enabled or disabled.<br>Enabling optimization allows performance improvements during burst writes. Disabling optimization is<br>required only if you expect an early write burst termination from a controller.|



Table continues on the next page... 

S32K3xx Reference Manual, Rev. 12, 2025-11-11 

Reference Manual 

142 / 5394 

NXP Semiconductors 

Miscellaneous System Control Module (MSCM) 

## Table continued from the previous page... 

|Field|Function|
|---|---|
||0b - Enable<br>1b - Disable|
|13<br>GMAC1_DIS_W<br>R_OPT|GMAC1 Disable Write Optimization<br>Determines whether write burst optimizations in the GMAC1 gasket are enabled or disabled.<br>Enabling optimization allows performance improvements during burst writes. Disabling optimization is<br>required only if you expect an early write burst termination from a controller.<br>0b - Enable<br>1b - Disable|
|12<br>USDHC_DIS_W<br>R_OPT|uSDHC Disable Write Optimization<br>Determines whether write burst optimizations in the uSDHC gasket are enabled.<br>Enabling optimization allows performance improvements during burst writes. Disabling optimization is<br>required only if you expect an early write burst termination from a controller.<br>0b - Enable<br>1b - Disable|
|11<br>AIPS0_DIS_WR<br>_OPT|AIPS0 Disable Write Optimization<br>Determines whether write burst optimizations in the AIPS2 AHB gasket are enabled.<br>Enabling optimization allows performance improvements during burst writes. Disabling optimization is<br>required only if you expect an early write burst termination from a controller.<br>0b - Enable<br>1b - Disable|
|10<br>AIPS2_DIS_WR<br>_OPT|AIPS2 Disable Write Optimization<br>Determines whether write burst optimizations in the AIPS2 AHB gasket are enabled.<br>Enabling optimization allows performance improvements during burst writes. Disabling optimization is<br>required only if you expect an early write burst termination from a controller.<br>0b - Enable<br>1b - Disable|
|9<br>AIPS1_DIS_WR<br>_OPT|AIPS1 Disable Write Optimization<br>Determines whether write burst optimizations in the AIPS1 AHB gasket are enabled.<br>Enabling optimization allows performance improvements during burst writes. Disabling optimization is<br>required only if you expect an early write burst termination from a controller.<br>0b - Enable<br>1b - Disable|
|8|Cortex-M7_2 AHBS Disable Write Optimization|



Table continues on the next page... 

S32K3xx Reference Manual, Rev. 12, 2025-11-11 

Reference Manual 

143 / 5394 

NXP Semiconductors 

Miscellaneous System Control Module (MSCM) 

## Table continued from the previous page... 

|Field|Function|
|---|---|
|CM7_2_AHBS_<br>DIS_WR_OPT|Determines whether write burst optimizations in the Cortex-M7_2_AHBS gasket are enabled or disabled.<br>Enabling optimization allows performance improvements during burst writes. Disabling optimization is<br>required only if you expect an early write burst termination from a controller.<br>0b - Enable<br>1b - Disable|
|7<br>CM7_1_AHBS_<br>DIS_WR_OPT|Cortex-M7_1 AHBS Disable Write Optimization<br>Determines whether write burst optimizations in the Cortex-M7_1_AHBS gasket are enabled or disabled.<br>Enabling optimization allows performance improvements during burst writes. Disabling optimization is<br>required only if you expect an early write burst termination from a controller.<br>0b - Enable<br>1b - Disable|
|6<br>CM7_0_AHBS_<br>DIS_WR_OPT|Cortex-M7_0 AHBS Disable Write Optimization<br>Determines whether write burst optimizations in the Cortex-M7_0_AHBS gasket are enabled or disabled.<br>Enabling optimization allows performance improvements during burst writes. Disabling optimization is<br>required only if you expect an early write burst termination from a controller.<br>0b - Enable<br>1b - Disable|
|5<br>QSPI_DIS_WR_<br>OPT|QSPI Disable Write Optimization<br>Determines whether write burst optimizations in the QuadSPI AHB gasket are enabled.<br>Enabling optimization allows performance improvements during burst writes. Disabling optimization is<br>required only if you expect an early write burst termination from a controller.<br>0b - Enable<br>1b - Disable|
|4<br>TCM_DIS_WR_<br>OPT|TCM Disable Write Optimization<br>Determines whether write burst optimizations in the TCM AHB gasket are enabled.<br>Enabling optimization allows performance improvements during burst writes. Disabling optimization is<br>required only if you expect an early write burst termination from a controller.<br>0b - Enable<br>1b - Disable|
|3<br>HSE_DIS_WR_<br>OPT|HSE Disable Write Optimization<br>Determines whether write burst optimizations in the HSE_B AHB gasket are enabled.<br>Enabling optimization allows performance improvements during burst writes. Disabling optimization is<br>required only if you expect an early write burst termination from a controller.|



Table continues on the next page... 

S32K3xx Reference Manual, Rev. 12, 2025-11-11 

Reference Manual 

144 / 5394 

NXP Semiconductors 

Miscellaneous System Control Module (MSCM) 

## Table continued from the previous page... 

|Field|Function|
|---|---|
||0b - Enable<br>1b - Disable|
|2<br>DMA_AXBS_S1<br>_DIS_WR_OPT|DMA AXBS S1 Disable Write Optimization<br>Determines whether write burst optimizations in the DMA AXBS S1 AHB gasket are enabled.<br>Enabling optimization allows performance improvements during burst writes. Disabling optimization is<br>required only if you expect an early write burst termination from a controller.<br>0b - Enable<br>1b - Disable|
|1<br>DMA_AXBS_S0<br>_DIS_WR_OPT|DMA AXBS S0 Disable Write Optimization<br>Determines whether write burst optimizations in the DMA AXBS S0 AHB gasket are enabled.<br>Enabling optimization allows performance improvements during burst writes. Disabling optimization is<br>required only if you expect an early write burst termination from a controller.<br>0b - Enable<br>1b - Disable|
|0<br>EMAC_DIS_WR<br>_OPT|EMAC Disable Write Optimization<br>Determines whether write burst optimizations in the EMAC AHB gasket are enabled.<br>Enabling optimization allows performance improvements during burst writes. Disabling optimization is<br>required only if you expect an early write burst termination from a controller.<br>0b - Enable<br>1b - Disable|



7.6.3.44 Interrupt Router Shared Peripheral Routing Control (IRSPRC0 - IRSPRC239) 

## Offset 

For n = 0 to 239: 

|Register|Offset|
|---|---|
|IRSPRCn|880h + (n × 2h)|



## Function 

Provides an array of 16-bit registers, where each register defines the routing control for the corresponding interrupt request, starting from IRQ = 0 (first on-platform interrupt vector). See the interrupt map file attached to this document for details. 

For this chip, each interrupt request can be either routed to a subset or to all the cores using the bit-mapped fields in IRSPRCn. If all the CPxEn fields are cleared, the interrupt request is disabled. Each routing control halfword can be locked by writing 1 to the LOCK field. 

Privileged accesses from noncore (and nondebug) bus controllers are treated as RAZ/WI, and any attempted User mode reference terminates with an error. Attempted accesses using a size other than a 16-bit halfword also terminate with an error. 

S32K3xx Reference Manual, Rev. 12, 2025-11-11 

Reference Manual 

145 / 5394 

NXP Semiconductors 

Miscellaneous System Control Module (MSCM) 

If you write 1 to all the CPxEn bits, all the cores service the interrupt. You must ensure that no conflicts arise from this setup either via the interrupt handler or through programming core level interrupt routing (NVIC/GIC). 

Reads and writes to this register beyond IRSPRC207 lead to unpredictable results. 

Access: Privileged mode only 

## Diagram 

|Bits<br>R<br>W<br>Reset|15|14<br>13<br>12|11<br>10<br>9<br>8|7<br>6<br>5<br>4|3<br>2<br>1<br>0|3<br>2<br>1<br>0|3<br>2<br>1<br>0|3<br>2<br>1<br>0|
|---|---|---|---|---|---|---|---|---|
||LOCK|0|||M7_3|M7_2|M7_1|M7_0|
||||||||||
||0|0<br>0<br>0|0<br>0<br>0<br>0|0<br>0<br>0<br>0|1<br>1<br>1<br>1||||



## Fields 

|Field|Function|
|---|---|
|15<br>LOCK|Lock<br>Provides a mechanism to lock the routing of the corresponding interrupt request. After you write 1 to this<br>field, attempted writes to IRSPRCn are ignored until the next reset writes 0 to the field.<br>0b - Writes to IRSPRCn allowed<br>1b - Writes to IRSPRCn ignored|
|14-4<br>—|Reserved|
|3<br>M7_3|Enable Cortex-M7_3 Interrupt Steering<br>Enables the corresponding interrupt request to route to Cortex-M7_3.<br>0b - Routing disabled<br>1b - Routing enabled|
|2<br>M7_2|Enable Cortex-M7_2 Interrupt Steering<br>Enables the corresponding interrupt request to route to Cortex-M7_2.<br>0b - Routing disabled<br>1b - Routing enabled|
|1<br>M7_1|Enable Cortex-M7_1 Interrupt Steering<br>Enables the corresponding interrupt request to route to Cortex-M7_1.<br>0b - Routing disabled<br>1b - Routing enabled|
|0<br>M7_0|Enable Cortex-M7_0 Interrupt Steering<br>Enables the corresponding interrupt request to route to Cortex-M7_0.<br>0b - Routing disabled<br>1b - Routing enabled|



S32K3xx Reference Manual, Rev. 12, 2025-11-11 

Reference Manual 

146 / 5394 

NXP Semiconductors 

Miscellaneous System Control Module (MSCM) 

## 7.7 Glossary 

GIC Generic interrupt controller IRQs Interrupt requests ISR Interrupt service routine MSI Message signal interface NVIC Nested vector interrupt controller 

S32K3xx Reference Manual, Rev. 12, 2025-11-11 

Reference Manual 

147 / 5394 

