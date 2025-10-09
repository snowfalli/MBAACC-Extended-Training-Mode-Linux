![alt text](https://github.com/snowfalli/MBAACC-Extended-Training-Mode-Linux/blob/main/Images/Extended%20Training%20Mode%20v2.0%20Corner.png?raw=true)

### Does not work with either GE-Proton, nor Proton, looking into the issue. Should work with wine.

#
![alt text](https://github.com/snowfalli/MBAACC-Extended-Training-Mode-Linux/blob/main/Images/Features.png?raw=true)

+ New "EXTENDED SETTINGS" menu
+ Reversals
	+ Four slots with five modes
		+ OFF: no reversals
		+ NORMAL: perform one of the selected reversals on block or hit
		+ RANDOM: 50% chance to perform one of the selected reversals on block or hit
		+ REPEAT: perform the selected reversals repeatedly
		+ SHIELD: perform one of the selected reversals after shielding
	+ Has support for nearly every action in the game
	+ Fixed 1f delay glitch
	+ Configurable delay can be added to the reversal to simulate fuzzy defense
+ EX Guard
+ Precise Meter and Health Controls
	+ Exact health and red health written to the screen
+ Guard Bar QoL
	+ Instantly regenerate instead of slowly refilling
	+ New INFINITE option
	+ Exact guard health and quality written to the screen
+ Position Controls
	+ Control both players and assist positions
	+ LOCK positions for custom reset positions
+ Burst After X Hits
+ More accurate meter built during a combo in Training Display
+ Option to reset the Reverse Penalty instantly after a combo or blockstring
+ Character Specific Resources
	+ Roa visible and hidden charges
	+ Sion bullets
	+ F-Maids heart meter
	+ Ryougi knife refill
	+ Normal, auto-refill, and infinite options
	+ Take Control of Assist Characters
	+ Control Kohaku as C-Maids through resets
+ Frame Data Display
	+ Displayed in the mod window or on the screen
	+ Startup, Total, and Advantage clearly displayed
	+ The display in the mod window can be configured to display significantly more detail
+ Save States
	+ Three separate save slots.
	+ Import and Export of save states supported
+ RNG
	+ Pick a custom seed or custom RNG value
	+ Can refresh the custom RNG every frame or every training mode reset depending on need
+ Character Highlights
	+ Highlight character Idle, Block, Hit, Armor, and Throw Protection
+ Character Hitboxes
	+ Different rendering styles for preference
	+ Color blind-friendly colors or the classic colors both supported
	+ Options to extend the origin for each character
	+ Option to draw the ground level
+ Hotkey Controls
+ Etcetera
	+ Helper text has been added to the new settings to explain their uses
	+ Replaced the stock FPS counter with one that is more accurate
	+ The background can be replaced with solid colors
	+ Shadows can be disabled
	+ The HUD can be disabled

#
![alt text](https://github.com/snowfalli/MBAACC-Extended-Training-Mode-Linux/blob/main/Images/Discord.png?raw=true)

We have a [Discord](https://discord.gg/6QUpZcThg7) where you can report bugs, get help, request features, or just discuss the mod.  If you do not want to join a discord, you can ping or message Fang___ instead.

#
![alt text](https://github.com/snowfalli/MBAACC-Extended-Training-Mode-Linux/blob/main/Images/Get.png?raw=true)

- [Download the latest .EXE and .DLL from this link.](https://github.com/fangdreth/MBAACC-Extended-Training-Mode/releases)  

- You'll need to run the exe through WINE

- Ensure both MBAACC and the training mod are run from the same wine prefix

- It is not necessary to put the executable in the same directory as MBAA.exe.

#
![alt text](https://github.com/snowfalli/MBAACC-Extended-Training-Mode-Linux/blob/main/Images/build.png?raw=true)

### On Windows
- Right now there isn't a CMAKE file, so if you want to build the mod yourself, get the [latest version of Visual Studio](https://visualstudio.microsoft.com/vs/), [DirectX SDK](https://www.microsoft.com/en-us/download/details.aspx?id=6812), and be sure to target x86.

### On Linux
- You'll need to use this horribly janky docker file
- git clone this repo and build the docker image [msvc-wine](https://github.com/mstorsjo/msvc-wine.git)
- the provided docker file should then work.. (i highly doubt this)
- Download the DirectX SDK and place the header files and .libs under Common/d3dx9
- Download [resource hacker](https://www.angusj.com/resourcehacker/) and place the .exe in the same directory as the Dockerfile
- Use MASM to compile the DLLAsmFuncs.asm into a .obj (or skip this and edit the docker file if you dont care about background colors)
- Run the docker file, then run  wine ResourceHacker.exe -script script.txt
- Should work from there hopefully..

#
![alt text](https://github.com/snowfalli/MBAACC-Extended-Training-Mode-Linux/blob/main/Images/faq.png?raw=true)

### Is it compatible with the Steam release?
At the moment, no.  You must use the latest version of the [community edition](https://play.meltyblood.club/).

### Is it compatible with Concerto?
Yes.  Concerto is just an external program for CCCaster, so it will work just fine.

### I found a bug, how do I report it?
You can join the Extended Training Mode Discord linked above, or send a message to Fang___

### "Looking for MBAA.exe..." when MBAA.exe is already open
Check Task Manager too see if you have a zombie MBAA.exe process running.  You may have to restart your computer to kill this program.

### "VCRUNTIME140.dll" was not found
You are missing a VC++ redistributable. Install vcrun2019 through winetricks on the prefix you use to run MBAACC

### Some of my settings change on their own
This is most likely because you are using the HITS UNTIL BURST option.  This setting requires MANUAL for the dummy and INFINITE for the meter, and turning HITS UNTIL BURST on automatically changes these.

### The hitboxes are being glitchy
More than likely this is because you opened the F4 menu at some point.  This is a known issue and can be easily fixed by switching in/out of fullscreen (alt+enter).

### Can I make my own version?
Yes.

#
![alt text](https://github.com/snowfalli/MBAACC-Extended-Training-Mode-Linux/blob/main/Images/changelog.png?raw=true)

+ Updated DirectX Hooks to work on Linux (Should work on windows as well?)

+ Uses DLL injection now in addition to the old external EXE

+ Frame data improved
  + Exact health, red health, guard bar, and guard quality values on-screen
  + Color Guide has been created to reference the meaning of the labels
  + Frame data is now written to the screen a la SF6

+ Reworked Save State controls
  + Press A on a save slot to delete it
  + Import and Export Save States
  + Save States support RNG
  + Hotkey controls
    + Save by pressing the hotkey, and delete by holding it
    + Change active Save Slot

+ Frame Step
  + Freeze the game and advance frame-by-frame

+ Hitboxes
  + Different styles of drawing and a color blind mode
  + Option to extend the characters' origin marker fullscreen
  + Option to highlight the ground

+ Color Overlay
  + Idle, Blocking, Hit, Armor, and Throw Protection
  + Red, Yellow, Green, Blue, Purple, and Black
  + Toggle on and off with a hotkey

+ More features to Enemy Reversals
  + Can be turned off without setting everything to NONE
  + Reversal out of shield
  + Reversal with a hotkey

+ Custom RNG Controls
  + Pick a custom Seed or a specific RNG value
  + Can reset every frame or just set it once when resetting training mode

+ Improved Input Display
  + Shows E presses
  + Arcade style similar to Strive

+ Customization
  + Configurable hotkeys for many of the training mode functions
  + Significantly more accurate FPS
  + Disable the HUD
  + Disable the background and replace it with a solid color.  Useful for chroma keying
  + Disable shadows

+ Training Display
  + Improved the accuracy of meter built during a combo

+ More character specific controls
  + FMaids Hearts
  + Ryougi Knife

+ Et cetera
  + Helper text has been added to everything in the Extended Settings menu
  + Fixed a few incorrect moves in Reversals
  + Improved inputs being dropped in the menu performance
  + Moved several menus around
  + Frame advantage is not shown with the FPS counter anymore
  + Removed random tripping

# License

tl;dr: You can copy and modify this project as much as you want.

Copyright (c) 2024 Fang

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files, to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
