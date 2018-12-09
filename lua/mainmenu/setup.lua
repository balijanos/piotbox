---------------------------------
-- pIOTbox Setup menu routines 
--
-- (c) 2017, Hi-Project Ltd.
--
---------------------------------
require "lua.global"
local display = require "lua.display"
local menu = require "lua.menu"

local MOUNT_DIR = "/mnt"

-----------------------------------------------
function getIPAddress()
	pboxMode = M_WAIT
	local ipa = cmdLine("hostname -I") or "Network Error"
	display.info(ipa)
end 
-----------------------------------------------
local function mountDialog(mountp,usb)
	local mnt = cmdLine("mount | grep "..mountp)
	local menuCallBack = { 
		cbfunc="mountCallBack", 
		title="USB: "..usb,
		submenu={{title="Mount"}, {title="Eject"}}, 
		var={mountp=mountp,label=usb},
		idx=(cmdLine("mount | grep "..mountp)==nil and 1) or 2
	}
	menu.show(menuCallBack,menuCallBack.idx)
	pboxMode = M_CBCK
	pboxMenuCallBack = menuCallBack
end

function mountCallBack(opt,rot)
	-- selection changed?
	if rot then
		if opt<0 and pboxMenuCallBack.idx>1 then
			pboxMenuCallBack.idx = pboxMenuCallBack.idx - 1
		elseif opt>0 and pboxMenuCallBack.idx<#pboxMenuCallBack.submenu then
			pboxMenuCallBack.idx = pboxMenuCallBack.idx + 1
		end
		menu.show(pboxMenuCallBack,pboxMenuCallBack.idx)
	else
	-- selection was made
		local r = nil
		if opt==1 then
			r = cmdLine("mount "..pboxMenuCallBack.var.mountp.." "..MOUNT_DIR)
			display.info{ pboxMenuCallBack.var.label, "", (r~=nil and "Mount error") or "Mounted" }
		elseif opt==2 then
			r = cmdLine("umount "..pboxMenuCallBack.var.mountp)
			display.info{ pboxMenuCallBack.var.label, "", (r~=nil and "Eject error") or "Ejected"}
		else
			display.info{ "Cancelled", "", "Press any button..."}
		end
		pboxMode = M_WAIT
		pboxMenuCallBack = nil
	end
end

function getUSBStorage()
	pboxMode = M_WAIT
	local mountp = cmdLine("blkid | grep dev/sd | awk '{print $1}' | sed -e 's/://'")
	local usb = cmdLine("blkid | grep dev/sd | awk -F'\"' '{print $2}'")
	if (mountp==nil) then
		usb = "SD Card"
		display.info(usb)
	else
		mountp = mountp:sub(1, -2)
		if usb==nil then
			usb = "'NO LABEL'"
		end
		mountDialog(mountp,usb)
	end
end 