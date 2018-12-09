---------------------------------
-- pIOTbox C/C++ interface 
--
-- (c) 2018, Hi-Project Ltd.
-- hiproject.hu@gmail.com
-----------------------------------
require "lua.global"
local display = require "lua.display"
local pboxMenu = require "lua.menu"
-----------------------------------
pboxMode = M_MENU -- menu mode init
exitStatus = KEEPRUNNING
-----------------------------------
-- PIoTBox callback handler
function pboxCallBack()
	return exitStatus
end

-- Button callback handler (button)
function handleQuickButton(b)
end

function handleSlowButton(b)
end

-- Rotary callback handler (button, rotation)
function handleRotary(b,diff)
end

-- Analog callback handler (channel, value)
function analogCallback(c,v)
end


-- Button callback handler (buttonId, releaseTime)
function buttonCallback(b,rtime)
	if pboxMode==M_APP then
		if rtime>1500 then
			handleSlowButton(b)
		else
			handleQuickButton(b)
		end
	elseif pboxMode==M_MENU and b==B_ENTER then
		pboxMenu.enter()
	elseif pboxMode==M_MENU and b==B_BACK then
		pboxMenu.back()
	elseif pboxMode==M_QUIT and b==B_BACK then
		pboxMode = M_MENU
		pboxMenu.show()
	elseif pboxMode==M_QUIT and b==B_OK then
		exitStatus = POWER_OFF_OPTION
	elseif pboxMode==M_WAIT then
		pboxMode = M_MENU
		pboxMenu.show()
	elseif pboxMode==M_CBCK and b==B_ENTER then
		if pboxMenuCallBack and pboxMenuCallBack.cbfunc then
			_G[pboxMenuCallBack.cbfunc](pboxMenuCallBack.idx)	-- selected option
		end
	elseif pboxMode==M_CBCK and b==B_BACK then
		if pboxMenuCallBack and pboxMenuCallBack.cbfunc then
			_G[pboxMenuCallBack.cbfunc](-1)					-- selection cancelled
		end
	end
end

-- Encoder callback handler (encoderId, difference)
function encoderCallback(enc,dif)
	if pboxMode==M_APP then
		handleRotary(enc,dif)
	elseif pboxMode==M_MENU then
		if dif>0 then 
			pboxMenu.next()
		elseif dif<0 then 
			pboxMenu.prev()
		end
	elseif pboxMode==M_CBCK then	
		if pboxMenuCallBack and pboxMenuCallBack.cbfunc then
			_G[pboxMenuCallBack.cbfunc](dif,enc)					-- selection changed
		end
	end
end

