---------------------------------
-- pIOTbox Menu 
--
-- (c) 2017, Hi-Project Ltd.
--
---------------------------------
local m = {}
require "lua.global"
local display = require "lua.display"

function m.show(xmenu,xcitm)
	display.clear()
	local n = 0
	local menu = xmenu or pboxCurMenu
	local citm = xcitm or pboxCurItem
	local color = 1
	display.title(menu.title or "",1,color)
	local y = display.height()/2 - #menu.submenu * DISPLAY_CHARHEIGHT + 4
	for i=1,#menu.submenu do
		color = 1
		y = y + DISPLAY_CHARHEIGHT+4
		if n==citm-1 then
		  display.bar(10,y-2,display.width()-20,DISPLAY_CHARHEIGHT+4,color)
		  color = 0
		end
		display.textOut(menu.submenu[i].title or "","C",y,1,color)
		n = n + 1
	end
	display.show()
end

function m.next(xmenu,xcitm)
	local menu = xmenu or pboxCurMenu.submenu
	local citm = xcitm or pboxCurItem
	if citm<#menu then
		if xcitm then
			xcitm = xcitm + 1
		else
			pboxCurItem = pboxCurItem + 1
		end
	end
	m.show()
end

function m.prev(xmenu,xcitm)
	local menu = xmenu or pboxCurMenu.submenu
	local citm = xcitm or pboxCurItem
	if citm>1 then
		if xcitm then
			xcitm = xcitm - 1
		else
			pboxCurItem = pboxCurItem - 1
		end
	end
	m.show()
end

function m.enter()
	local mi = pboxCurMenu.submenu[pboxCurItem]
	if mi.submenu and #mi.submenu>0 then
		table.insert(pboxMenuChain,{parent=pboxCurMenu,item=pboxCurItem})
		pboxCurMenu = pboxCurMenu.submenu[pboxCurItem]
		pboxCurItem = pboxCurMenu.lastMenu or 1
		m.show()
	elseif mi.call and type(_G[mi.call])=="function" then
		_G[mi.call]()
	end
end

function m.back()
	if #pboxMenuChain>0 then
		pboxCurMenu.lastMenu = pboxCurItem
		pboxCurMenu = pboxMenuChain[#pboxMenuChain].parent
		pboxCurItem = pboxMenuChain[#pboxMenuChain].item
		table.remove(pboxMenuChain,#pboxMenuChain)
		m.show()
	end
end

return m








