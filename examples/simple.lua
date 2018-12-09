---------------------------------
-- pIOTbox (simple app)
--
-- (c) 2017, Hi-Project Ltd.
--
---------------------------------
require "lua/global"
local display = require "lua/display"

function initialize()
	display.initDisplay()
	display.info("Press a button")
end

function finalize()
	display.info("Thank you")
	os.execute("sleep 1")
	display.closeDisplay()
	return exitStatus			
end

function buttonCallback(b,rtime)
	exitStatus = 0
end
