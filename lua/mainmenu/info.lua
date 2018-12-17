require "lua.config"
require "lua.gpio"
require "lua.events"
local display = require "lua.display"

-----------------------------------------------
function getIPAddress()
	pboxMode = M_WAIT
	local ipa = cmdLine("hostname -I") or "Network Error"
	ipa = ipa:trim():split(" ")
	display.info(ipa)
end 

-----------------------------------------------
require "lua.gpio"
function getFirmwareInfo()
	pboxMode = M_WAIT
	display.info{ "PiotBox v1.0", "", string.format("%s R%s (%dMb)",rpiInfo()), "" ,_VERSION}
end