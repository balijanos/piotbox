---------------------------------
-- pIOTbox hardware configuration
--
-- (c) 2017, Hi-Project Ltd.
--
---------------------------------

-- PIoTBox loop callback
PBOX_CALLBACK = "pboxCallBack"

-- button pins
PBOX_BUTTONS = { 13, 19, 4, 22, 17, 27 }
-- button callback
PBOX_BUTTON_CALLBACK = "buttonCallback"

-- encoders pins {CLK,DT,Sensitivity}
PBOX_ENCODERS = { 
	{sensitivity=3, clk=16, dt=20}, 
	{sensitivity=3, clk=26, dt=21} 
}
-- encoder callback
PBOX_ENCODER_CALLBACK = "encoderCallback"

-- analog using GPIO8,9,10,11 as SPI
PBOX_ADC = "MCP3002" -- two channel adc
PBOX_ANALOG_CALLBACK = "analogCallback"

-- display using GPIO2,3 as I2C
DISPLAY_TYPE = 6 -- OLED_SH1106_I2C_128x64 

-- pIOTbox free gpio ports
GPIO_PORTS = {
 {gpio="GPIO 0", bcm=0 },
 {gpio="GPIO 1", bcm=1 },
 {gpio="GPIO 5", bcm=5 },
 {gpio="GPIO 6", bcm=6 },
 {gpio="GPIO 7", bcm=7 },
 {gpio="GPIO 12", bcm=12 },
 {gpio="GPIO 14", bcm=14 },
 {gpio="GPIO 15", bcm=15 },
 {gpio="GPIO 18", bcm=18 },
 {gpio="GPIO 23", bcm=23 },
 {gpio="GPIO 24", bcm=24 },
 {gpio="GPIO 25", bcm=25 }
}