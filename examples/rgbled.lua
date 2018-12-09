-- pIOTbox (RGB led demo)
--
-- (c) 2017, Hi-Project Ltd.
--
---------------------------------
require "lua/global"
local display = require "lua/display"

PBOX_CALLBACK = "blinkLeds"

local LEDS = {14,15,18}
local OUT = wiringPi.OUTPUT
local LO = wiringPi.LOW
local HI = wiringPi.HIGH

local cycle = 1
local cled = 1
local DELAY = 100

function initialize()
	display.initDisplay()
	display.info("RGB LED Blinker")
	for i=1,#LEDS do
		wiringPi.pinMode(LEDS[i],OUT)
		wiringPi.digitalWrite(LEDS[i],LO)
	end
end

function finalize()
	for i=1,#LEDS do
		wiringPi.digitalWrite(LEDS[i],LO)
	end
	display.info("Stopped")
	os.execute("sleep 1")
	display.closeDisplay()
	return exitStatus			
end

function blinkLeds()
	cycle = cycle + 1
	if cycle>DELAY then
		cycle = 1
		wiringPi.digitalWrite(LEDS[cled],LO)
		cled = cled + 1
	end
	if cled>#LEDS then
		cled = 1
	end
	if cycle==1 then
		wiringPi.digitalWrite(LEDS[cled],HI)
	end
	return exitStatus
end

function buttonCallback(b,rtime)
	exitStatus = 0
end

function encoderCallback(enc,dif)
	DELAY = DELAY + dif
	if DELAY<4 then DELAY=4 elseif DELAY>200 then DELAY=200 end
end
