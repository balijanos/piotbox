---------------------------------
-- pIOTbox Lua 'mainmenu' 
--
-- (c) 2018, Hi-Project Ltd.
-- hiproject.hu@gmail.com
---------------------------------
-- setup menu functions

require "lua.mainmenu.power"
require "lua.mainmenu.setup"

-- Menu tree
	local setupMenu = {
		{ title = "IP Address", call = "getIPAddress" },
		{ title = "Storage", call = "getUSBStorage" },
		{ title = "Shutdown", 
			submenu = {
				{ title = "Shutdown Pi", call = "pwrShutdown" },
				{ title = "Reboot Pi", call = "pwrReboot" },
				{ title = "Restart pIOTbox", call = "pwrRestart" },
				{ title = "Quit pIOTbox", call = "pwrStop" },
			} 
		},	
	}
mainMenu = {
	-- MAIN
	title = "Main menu",
	submenu = {                                
		{ title = "Setup", submenu = setupMenu },
	}
}

pboxCurMenu = mainMenu