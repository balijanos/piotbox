---------------------------------
-- pIOTbox GPIO management 
--
-- (c) 2017, Hi-Project Ltd.
-- hiproject.hu@gmail.com
---------------------------------

wiringPi = require "lua/wiringPi"

--------------------------------------------------------
-- returns model, revision and memory size
function rpiInfo()
	local model, rev, mem, maker, overVolted = wiringPi.piBoardId()
	local validModels = { 3, 4, 8, 9 }
	local mtype = ""
	if (model == wiringPi.PI_MODEL_B) then
		if (rev == wiringPi.PI_VERSION_2 ) then
		  mtype = " B2"
		else
		  mtype = " B1"
		end
	end
	return 
		wiringPi.PI_ModelNames[model+1]..mtype,
		wiringPi.PI_RevisionNames[rev+1],
		wiringPi.PI_MemorySize[mem+1]
end

local function findPin(pin)
	for _,p in pairs(GPIO_PORTS) do
		if p.bcm==pin then
			return p.gpio
		end
	end
	return nil
end

function wiringPi.pinMode(pin,mode)
	if findPin(pin) then
		wiringPi.mode(pin,mode)
	else
		 io.stderr:write("pIOTbox [pinMode] *GPIO ERROR invalid pin:"..tostring(pin))
	end
end

function wiringPi.pullUpDnControl(pin,pud)
	if findPin(pin) then
		wiringPi.pud(pin,pud)
	else
		 io.stderr:write("pIOTbox [pullUpDnControl] *GPIO ERROR invalid pin:"..tostring(pin))
	end
end

function wiringPi.digitalWrite(pin,value)
	if findPin(pin) then
		wiringPi.write(pin,value)
	else
		 io.stderr:write("pIOTbox [digitalWrite] *GPIO ERROR invalid pin:"..tostring(pin))
	end
end

