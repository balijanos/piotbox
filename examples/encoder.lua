---------------------------------
-- pIOTbox (encoder app)
--
-- (c) 2017, Hi-Project Ltd.
--
---------------------------------
require "lua/global"
local display = require "lua/display"

local encPos=50

local function showEncoderBar()
	display.clear()
	display.textOut(encPos.."","C",40,2,1)
	display.hBar(14,20,100,10,1,encPos)
	display.show()
end

function initialize()
	display.initDisplay()
	showEncoderBar()
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

function encoderCallback(enc,dif)
	encPos = encPos+dif
	if encPos<0 then encPos=0 end
	if encPos>100 then encPos=100 end	
	showEncoderBar()
end
