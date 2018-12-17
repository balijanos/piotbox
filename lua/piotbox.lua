---------------------------------
-- pIOTbox Lua 'Interface' 
--
-- (c) 2018, Hi-Project Ltd.
-- hiproject.hu@gmail.com
---------------------------------
-- config
require "lua.config"
-- system
require "lua.gpio"
require "lua.events"
require "lua.utils"
---------------------------------
-- mainmenu
require "lua.mainmenu.entry"
---------------------------------
local display = require "lua.display"
local pboxMenu = require "lua.menu"
-- startup
function initialize()
	display.initDisplay()
	display.info{ "PiotBox v1.0", "", string.format("%s R%s (%dMb)",rpiInfo())}
	os.execute("sleep 2")
	pboxMenu.show()
end

function finalize()
	display.info("BYE")
	os.execute("sleep 1")
	display.closeDisplay()
	return exitStatus			
end

io.stdout:write(string.format("Running on %s R%s (%dMb)\n",rpiInfo()))
