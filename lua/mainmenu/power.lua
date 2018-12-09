---------------------------------
-- pIOTbox Power menu routines
--
-- (c) 2017, Hi-Project Ltd.
--
---------------------------------
require "lua.global"
local display = require "lua.display"

POWER_OFF_OPTION = KEEPRUNNING

function pwrShutdown()
	pboxMode=M_QUIT
	display.info("Press Button#5")
	POWER_OFF_OPTION = 91
end

function pwrReboot()
	pboxMode=M_QUIT
	display.info("Press Button#5")
	POWER_OFF_OPTION = 92
end

function pwrRestart()
	pboxMode=M_QUIT
	display.info("Press Button#5")
	POWER_OFF_OPTION = 93
end

function pwrStop()
	pboxMode=M_QUIT
	display.info("Press Button#5")
	POWER_OFF_OPTION = 94
end
