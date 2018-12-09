---------------------------------
-- pIOTbox (buttonState app)
--
-- (c) 2017, Hi-Project Ltd.
--
---------------------------------
require "lua/global"
local display = require "lua/display"

PBOX_CALLBACK = "readButtonState"

function readButtonState()
    local s = " "
	for i=0,5 do
		s = s .. getButtonState(i) .." "
	end
	display.info(s)
	return exitStatus
end

function initialize()
	display.initDisplay()
end

function finalize()
	display.closeDisplay()
	return exitStatus			
end

function buttonCallback(b,rtime)
	-- terminate if button5 and button6 pressed
	if getButtonState(BUTTON5)==B_DOWN and b==BUTTON6 then
		exitStatus = 0
	end
end
