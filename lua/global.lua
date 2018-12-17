---------------------------------
-- pIOTbox Globals
--
-- (c) 2017, Hi-Project Ltd.
--
---------------------------------
KEEPRUNNING = 1

-- Buttons
BUTTON1 = 0
BUTTON2 = 1
BUTTON3 = 2
BUTTON4 = 3
BUTTON5 = 4
BUTTON6 = 5

B_ENTER = BUTTON6
B_OK = BUTTON5
B_CANCEL = BUTTON3
B_BACK = BUTTON4

B_UP = 1		-- button state released
B_DOWN = 0		-- button state pressed

-- Rotary encoders
ROTARY1 = 0
ROTARY2 = 1

-- Menu globals
M_MENU = 0
M_WAIT = 1	-- wait for any button
M_CBCK = 2	-- handled by callback function
M_QUIT = 3	-- power off menu
M_APP  = 4	-- handled by app functions

pboxMenuChain = {}	-- menu chain
pboxCurMenu = nil	-- Current menu
pboxCurItem = 1		-- Current menu item

-- Callback function. Usage example at setup.lua/mountDialog function
pboxMenuCallBack = nil
