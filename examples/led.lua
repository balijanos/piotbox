-- pIOTbox (RGB led demo)
--
-- (c) 2017, Hi-Project Ltd.
--
---------------------------------

local LED = 14

function initialize()
	wiringPi.pinMode(LED,1)
	wiringPi.digitalWrite(LED,1)
end

function finalize()
	wiringPi.digitalWrite(LED,0)
	return exitStatus			
end

function buttonCallback(b,rtime)
	exitStatus = 0
end

