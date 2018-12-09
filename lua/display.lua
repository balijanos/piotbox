---------------------------------
-- pIOTbox display driver
--
-- (c) 2017, Hi-Project Ltd.
--
---------------------------------
DISPLAY_CHARWIDTH = 6 -- in pixels
DISPLAY_CHARHEIGHT = 8 -- in pixels

local m={}
require "lua.global"
local display = require "display"
local displayOk = nil
 
function m.initDisplay()
	displayOk = (display.open(DISPLAY_TYPE)==0)
end

function m.closeDisplay()
	if displayOk then
		display.clear()
		display.display()
		display.close()
	end
end

function m.width()
	return display.width()
end

function m.height()
	return display.height()
end

function m.title(str,size,color)
	local x = display.width()/2-string.len(str)*DISPLAY_CHARWIDTH*size/2
	display.setCursor(x,0)
	display.setTextSize(size)
	display.setTextColor(color)
	display.printf(str or "")
	
	display.drawFastHLine(0,size*DISPLAY_CHARHEIGHT+1,display.width(),color)
end

function m.bar(x,y,w,h,c)
	display.fillRect(x,y,w,h,c)
end

function m.hBar(x,y,w,h,c,pos)
	display.drawRect(x,y,w,h,c)
	display.fillRect(x,y,pos,h,c)
end

function m.textOut(str,x,y,size,color)
	str = str or ""
	if type(x)=="string" then
		if string.upper(x)=="L" then
			x=0
		elseif string.upper(x)=="R" then
			x=display.width()-string.len(str)*DISPLAY_CHARWIDTH*size
		else
			x=display.width()/2-string.len(str)*DISPLAY_CHARWIDTH*size/2
		end
	end
	display.setCursor(x,y)
	display.setTextSize(size)
	display.setTextColor(color)
	display.printf(str)
end

function m.info(nfo)
	nfo = nfo or ""
	local function showLine(y,s)
		m.textOut(s,"C",y,1,1)
	end
	if displayOk then
		display.clear()
		display.drawRect(0,0,display.width(),display.height(),1)
		local str = nfo
		local y= display.height()/2-DISPLAY_CHARHEIGHT/2 + 4
		if type(nfo)=="table" then
			y= y-#nfo*(DISPLAY_CHARHEIGHT+2)/2
			for _,s in pairs(nfo) do
				showLine(y,s)
				y=y+DISPLAY_CHARHEIGHT+2
			end
		else
			showLine(y,str)
		end
		display.display()
	end
end

function m.clear()
	if displayOk then
		display.clear()
	end
end

function m.show()
	if displayOk then
		display.display()
	end
end

return m






