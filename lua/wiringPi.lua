-------------------------------------
-- wiringPi Lua interface v2.0
-- Copyright (C) 2016 Hi.Project Ltd.
-------------------------------------

local w = require "wiringPi"

w.INPUT = 0
w.OUTPUT = 1
w.PWM_OUTPUT = 2
w.GPIO_CLOCK = 3
w.SOFT_PWM_OUTPUT = 4
w.SOFT_TONE_OUTPUT = 5
w.PWM_TONE_OUTPUT = 6

w.LOW	= 0
w.HIGH = 1

w.PUD_OFF = 0
w.PUD_DOWN = 1
w.PUD_UP =2

w.PWM_MODE_MS = 0
w.PWM_MODE_BAL =1

w.INT_EDGE_SETUP = 0
w.INT_EDGE_FALLING = 1
w.INT_EDGE_RISING = 2
w.INT_EDGE_BOTH = 3

w.PI_MODEL_A = 0
w.PI_MODEL_B = 1
w.PI_MODEL_AP = 2
w.PI_MODEL_BP = 3
w.PI_MODEL_2 = 4
w.PI_ALPHA = 5
w.PI_MODEL_CM = 6
w.PI_MODEL_07 = 7
w.PI_MODEL_3 = 8
w.PI_MODEL_ZERO = 9

w.PI_VERSION_1 = 0
w.PI_VERSION_1_1 = 1
w.PI_VERSION_1_2 = 2
w.PI_VERSION_2 = 3

w.PI_MAKER_SONY = 0
w.PI_MAKER_EGOMAN = 1
w.PI_MAKER_MBEST = 2
w.PI_MAKER_UNKNOWN = 3

w.PI_ModelNames =
{
  "Model A",	--  0
  "Model B",	--  1
  "Model A+",	--  2
  "Model B+",	--  3
  "Pi 2",	--  4
  "Alpha",	--  5
  "CM",		--  6
  "Unknown07",	-- 07
  "Pi 3",	-- 08
  "Pi Zero",	-- 09
  "Unknown10",	-- 10
  "Unknown11",	-- 11
  "Unknown12",	-- 12
  "Unknown13",	-- 13
  "Unknown14",	-- 14
  "Unknown15",	-- 15
}

w.PI_RevisionNames =
{
  "00",
  "01",
  "02",
  "03",
  "04",
  "05",
  "06",
  "07",
  "08",
  "09",
  "10",
  "11",
  "12",
  "13",
  "14",
  "15",
} 

w.PI_MakerNames =
{
  "Sony",	--	 0
  "Egoman",	--	 1
  "Embest",	--	 2
  "Unknown",	--	 3
  "Embest",	--	 4
  "Unknown05",	--	 5
  "Unknown06",	--	 6
  "Unknown07",	--	 7
  "Unknown08",	--	 8
  "Unknown09",	--	 9
  "Unknown10",	--	10
  "Unknown11",	--	11
  "Unknown12",	--	12
  "Unknown13",	--	13
  "Unknown14",	--	14
  "Unknown15",	--	15
}

w.PI_MemorySize =
{
   256,		--	 0
   512,		--	 1
  1024,		--	 2
     0,		--	 3
     0,		--	 4
     0,		--	 5
     0,		--	 6
     0,		--	 7
}

w.Setup = w.setup
w.SetupGpio = w.setupGpio
w.SetupPhys = w.setupPhys
w.SetupSys = w.setupSys

w.pinMode = w.mode
w.pullUpDnControl = w.pud
w.digitalWrite = w.write
w.digitalRead = w.read

w.digitalWriteByte = w.writeByte
w.digitalReadByte = w.readByte
w.pwmSetMode = w.pwmmode
w.pwmSetRange = w.pwmrange
w.pwmSetClock = w.pwmclock 
w.piBoardRev = w.rev
w.wpiPinToGpio = w.pin2gpio
w.physPinToGpio = w.physpin2gpio

w.millis = w.millis
w.micros = w.micros
w.delay = w.delay
w.delayMicroseconds = w.microdelay

w.I2CSetup = w.i2csetup
w.I2CSetupInterface = w.i2csetupif
w.I2CRead = w.i2cread
w.I2CWrite = w.i2cwrite
w.I2CWriteReg8 = w.i2cwriter8
w.I2CWriteReg16 = w.i2cwriter16
w.I2CReadReg8 = w.i2creadr8
w.I2CReadReg16 = w.i2creadr16

w.shiftIn = w.shiftin
w.shiftOut = w.shiftout

w.softPwmCreate = w.pwm
w.softPwmWrite = w.freq

w.ISR = w.isr

w.piBoardId = w.piboardid
w.pinInfo = w.pininfo
w.physPinToGpio = w.phystogpio

return w