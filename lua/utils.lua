local MOUNT_DIR = "/mnt"

function getMountDir()
	return MOUNT_DIR
end 

-- executes shell command and gets the result
function cmdLine(cmd)
	local handle = io.popen(cmd .. " 2>&1")
	local output = handle:read("*a")
	handle:close()
	if (string.len(output)==0) then
		output = nil
	end
	return output
end

function string:split(sep)
   local sep, fields = sep or ":", {}
   local pattern = string.format("([^%s]+)", sep)
   self:gsub(pattern, function(c) fields[#fields+1] = c end)
   return fields
end

function string:trim()
   local from = self:match"^%s*()"
   return from > #self and "" or self:match(".*%S", from)
end
