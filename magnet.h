//https://www.sparkfun.com/datasheets/Sensors/Magneto/HMC5843.pdf
//The default (factory) HMC5843 7-bit slave address is 0x3C for write operations, or 0x3D for read operations

//REGISTERS
//00 Configuration Register A Read/Write
//01 Configuration Register B Read/Write
//02 Mode Register Read/Write
//03 Data Output X MSB Register Read
//04 Data Output X LSB Register Read
//05 Data Output Y MSB Register Read
//06 Data Output Y LSB Register Read
//07 Data Output Z MSB Register Read
//08 Data Output Z LSB Register Read
//09 Status Register Read
//10 Identification Register A Read
//11 Identification Register B Read
//12 Identification Register C Read

//If (address pointer = 09) then address pointer = 03
//Else if (address pointer >= 12) then address pointer = 0
//Else (address pointer) = (address pointer) + 1

//EG continuous mode
//0x3C 0x02 0x00

//0x3D, and clock out DXRA, DXRB, DYRA, DYRB, DZRA, DZRB located in registers 3 through 8. The HMC5843 will
//automatically re-point back to register 3 for the next 0x3D query, expected 100 milli-seconds or later.


// Register A

//CRA4 to CRA2 DO2 to DO0
//DATA_RATE
//0 0 0 0.5
//0 0 1 1
//0 1 0 2
//0 1 1 5
//1 0 0 10 (default)
//1 0 1 20
//1 1 0 50
//1 1 1 Not used

//CRA1 to CRA0 MS1 to MS0
//MS1 MS0 Mode
//0 0 Normal measurement configuration (default). In normal measurement
//configuration the device follows normal measurement flow. Pins BP and BN
//are left floating and high impedance.
//0 1 Positive bias configuration. In positive bias configuration, a positive current
//is forced across the resistive load on pins BP and BN.
//1 0 Negative bias configuration. In negative bias configuration, a negative
//current is forced across the resistive load on pins BP and BN.
//1 1 This configuration is not used.

// Register B
//CRB7 to CRB5 GN2 to GN0
//Gain Configuration Bits. These bits configure the gain for
//the device. The gain configuration is common for all
//channels.
//CRB4 to CRB0 0 This bit must be cleared for correct operation.

//0 0 0 ±0.7Ga 1620 0xF800–0x07FF
//(-2048–2047 )
//0 0 1 ±1.0Ga (default) 1300 0xF800–0x07FF
//(-2048–2047 )
//0 1 0 ±1.5Ga 970 0xF800–0x07FF
//(-2048–2047 )
//0 1 1 ±2.0Ga 780 0xF800–0x07FF
//(-2048–2047 )
//1 0 0 ±3.2Ga 530 0xF800–0x07FF
//(-2048–2047 )
//1 0 1 ±3.8Ga 460 0xF800–0x07FF
//(-2048–2047 )
//1 1 0 ±4.5Ga 390 0xF800–0x07FF
//(-2048–2047 )
//1 1 1
//±6.5Ga
//(Not Recommended) 280 0xF800–0x07FF
//(-2048–2047 )


// Mode Resgester
//MR7 MR6 MR5 MR4 MR3 MR2 MR1 MR0
//(0) (0) (0) (0) (0) (0) MD1 (1) MD0 (0)
//Table 14: Mode Register
//Location Name Description
//MR7 to
//MR2 0 These bits must be cleared for correct operation.
//MR1 to
//MR0
//MD1 to
//MD0
//Mode Select Bits. These bits select the operation mode of
//this device.

//MD1 MD0 Mode
//0 0
//Continuous-Conversion Mode. In continuous-conversion mode, the
//device continuously performs conversions an places the result in the
//data register. RDY goes high when new data is placed in all three
//registers. After a power-on or a write to the mode or configuration
//register, the first measurement set is available from all three data
//output registers after a period of 2/fDO and subsequent
//measurements are available at a frequency of fDO, where fDO is the
//frequency of data output.
//0 1
//Single-Conversion Mode. When single-conversion mode is selected,
//device performs a single measurement, sets RDY high and returned
//to sleep mode. Mode register returns to sleep mode bit values. The
//measurement remains in the data output register and RDY remains
//high until the data output register is read or another conversion is
//performed.
//1 0 Idle Mode. Device is placed in idle mode.
//1 1 Sleep Mode. Device is placed in sleep mode.


//Status Register
SR7 SR6 SR5 SR4 SR3 SR2 SR1 SR0
(0) (0) (0) (0) (0) REN (0) LOCK (0) RDY(0)
Table 20: Status Register
HMC5843
16 www.honeywell.com
Location Name Description
SR7 to
SR3 0 These bits must be cleared for correct operation.
SR2 REN
Regulator Enabled Bit. This bit is set when the internal
voltage regulator is enabled. This bit is cleared when the
internal regulator is disabled.
SR1 LOCK
Data output register lock. This bit is set when this some but
not all for of the six data output registers have been read.
When this bit is set, the six data output registers are locked
and any new data will not be placed in these register until
on of four conditions are met: one, all six have been read
or the mode changed, two, a POR is issued, three, the
mode is changed, or four, the measurement is changed.
SR0 RDY
Ready Bit. Set when data is written to all six data registers.
Cleared when device initiates a write to the data output
registers, when in off mode, and after one or more of the
data output registers are written to. When RDY bit is clear
it shall remain cleared for a minimum of 5 µs. DRDY pin
can be used as an alternative to the status register for
monitoring the device for conversion data.



