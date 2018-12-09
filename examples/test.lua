---------------------------------
-- pIOTbox (test app)
--
-- (c) 2017, Hi-Project Ltd.
--
---------------------------------
require "lua.global"

local display = require "lua.display"
local menu = require "lua.menu"
local testStage=0

-- 
-- user menu definition
-- 
print(mainMenu)
table.insert(mainMenu.submenu, 1, {title = "First program", call= "testApp" })
table.insert(mainMenu.submenu, 2, {title = "Second program", call= "testApp" })
table.insert(mainMenu.submenu, 3, {title = "Third program", call= "testApp" })

-- 
-- Test program initialization
-- 
function testApp()
	if testStage==0 then
		display.info{
			"press any button to",
			"continue TEST mode",
			"",
			"hold Button#5 then",
			"press Button#6 to",
			"exit from TEST mode"
		}
	else
		display.info("waiting for event...")
	end
	pboxMode = M_APP
end

--
-- Event handlers, called from iface.lua if mode==M_APP
-- 
function handleQuickButton(b)
	if getButtonState(BUTTON5)==B_DOWN and b==BUTTON6 then
		pboxMode = M_MENU
		menu.show()
		testStage=0
	elseif testStage==0 then
		testStage=1
		testApp()
	else
		display.info(string.format("BUTTON #%d click",b+1))
	end
end

function handleSlowButton(b)
	if getButtonState(BUTTON5)==B_DOWN and b==BUTTON6 then
		pboxMode = M_MENU
		menu.show()
		testStage=0
	elseif testStage==1 then
		display.info(string.format("BUTTON #%d slow press",b+1))
	end
end

function handleRotary(b,diff)
	if testStage==1 then
		display.info(string.format("ROTARY #%d  diff=%d",b+1,diff))
	end
end
