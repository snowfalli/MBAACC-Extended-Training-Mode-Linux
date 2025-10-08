#pragma once
#ifndef UNICODE
#define UNICODE
#endif
#define NDEBUG
#include <cstdint>
#include <ws2tcpip.h>
#include <winsock2.h>
#include <windows.h>
#include <vector>
#include <string>
#include <map>
#include <unordered_map>
#include <iostream>
#include <cwctype>
#include <algorithm>

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))
#define CLAMP(value, min_val, max_val) MAX(MIN((value), (max_val)), (min_val))

#pragma comment(lib, "ws2_32.lib")

typedef DWORD DADDRESS;

enum eMenu { MAIN = 2, BATTLE_SETTINGS = 6, ENEMY_SETTINGS = 7, VIEW_SCREEN = 12, COMMAND_LIST = 13, TRAINING_DISPLAY = 8 };
enum eEnemyStatus { STAND, JUMP, CROUCH, CPU, MANUAL, DUMMY };
enum eMagicCircuit { UNLIMITED = 3 };
enum eRecover {};
enum eEnemyOffOnRandom { OFF, ON, RANDOM };
enum eEnemyDefense { NOGUARD, ALLGUARD, STATUSGUARD, ALLSHIELD, STATUSSHIELD, DODGE };
enum eEnemyStance { STANDING = 0, STANDGUARDING = 17, CROUCHING = 13 };
enum ePresetSettings { DEFAULT, FUZZY, BLOCKSTRING, HEATOS, FUZZYMASH, FUZZYJUMP, CUSTOM };
enum eEnemyGuardLevelSettings { INF, ONEHUNDRED, SEVENTYFIVE, FIFTY, TWENTYFIVE, ZERO };
enum eSettingsPages { REVERSALS_PAGE = 1, STATS_PAGE, HIGHLIGHT_PAGE, POSITIONS_PAGE, CHARACTER_SPECIFICS, HITBOXES_PAGE, SAVE_STATE_PAGE, FRAME_TOOL, RNG_PAGE, UI_PAGE, SYSTEM_PAGE };
enum eHotkeyPages { GENERIC_HOTKEYS_PAGE = 1, FRAME_TOOL_HOTKEYS_PAGE, RNG_HOTKEYS_PAGE };
enum eReversalType { REVERSAL_OFF, REVERSAL_NORMAL, REVERSAL_RANDOM, REVERSAL_SHIELD, /*REVERSAL_SEQUENCE,*/ REVERSAL_REPEAT };
enum eFrameDataDisplay { FRAMEDISPLAY_NORMAL, FRAMEDISPLAY_ADVANCED };
enum eHighlightSettings { NO_HIGHLIGHT, RED_HIGHLIGHT, YELLOW_HIGHLIGHT, GREEN_HIGHLIGHT, BLUE_HIGHLIGHT, PURPLE_HIGHLIGHT, BLACK_HIGHLIGHT };
enum eRNGMode { RNG_OFF, RNG_SEED, RNG_RN };
enum eRNGRate { RNG_EVERY_FRAME, RNG_EVERY_RESET };
enum eHitboxStyle { HITBOX_DRAW_ALL, HITBOX_BLEND };
enum eBackground { BG_NORMAL, BG_WHITE, BG_GRAY, BG_BLACK, BG_RED, BG_GREEN, BG_BLUE, BG_PURPLE, BG_YELLOW };
enum eSlow { SLOW_THREE_FOURTHS = 3, SLOW_ONE_HALF = 2, SLOW_ONE_FOURTH = 1 };
enum eInputDisplay { INPUT_OFF, INPUT_LIST, INPUT_ARCADE, INPUT_BOTH };

const std::string GITHUB_LATEST = "https://api.github.com/repos/fangdreth/MBAACC-Extended-Training-Mode/releases/latest";
const std::string GITHUB_RELEASE = "https://github.com/fangdreth/MBAACC-Extended-Training-Mode/releases";
const std::string GITHUB_README = "https://github.com/fangdreth/MBAACC-Extended-Training-Mode/blob/main/README.md";
const std::string VERSION = "v2.0";

const DWORD dwP1WillBlock = 0x1552AC;
const DWORD dwP2WillBlock = 0x1552AC + 0xAFC;
const DWORD dwRoundTime = 0x162A40; //0-inf
const DWORD dwMot = 0x1581CC;   // this one is mysterious.  I think it's an animation counter
const DWORD dwEnemyStatus = 0x37C1E8; //0:STAND 1:JUMP 2:CROUCH 3:CPU 4:MANUAL 5:DUMMY
const DWORD dwEnemyStatusCopy = 0x34D7F8;
const DWORD dwEnemyDefense = 0x37C1F0; //0:OFF 1:ALLGUARD 2:STATUSGUARD 3:ALLSHIELD 4:STATUSSHIELD 5:DODGE
const DWORD dwEnemyDefenseCorrected = 0x155DA8; // set this after setting dwEnemyDefense
const DWORD dwEnemyDefenseType = 0x37C1F4; //0:OFF 1:COMBO 2:RANDOM
const DWORD dwP1GuardAmount = 0x1551F4; //0-1174011904 aka 0.0f-8000.0f
const DWORD dwP2GuardAmount = 0x1551F4 + 0xAFC; //0-1174011904 aka 0.0f-8000.0f
const DWORD dwP1GuardQuality = 0x155208;
const DWORD dwP2GuardQuality = 0x155208 + 0xAFC;
const DWORD dwGuardSetting = 0x37C200; //0:100 1:75 2:50 3:25 4:0
const DWORD dwAirRecovery = 0x37C208;
const DWORD dwDownRecovery = 0x37C20C;
const DWORD dwThrowRecovery = 0x37C214;
const DWORD dwReduceRecovery = 0x37C218;
const DWORD dwP1ExGuard = 0x1551E0; //10:ExGuard
const DWORD dwP2ExGuard = 0x1551E0 + 0xAFC; //10:ExGuard
const DWORD dwP1Meter = 0x155210;   // abc.xy truncated Ex. 12345 = 123.4%
const DWORD dwP1Health = 0x1551EC;
const DWORD dwP1RedHealth = 0x1551F0;
const DWORD dwP2Meter = 0x155210 + 0xAFC;
const DWORD dwP2Health = 0x1551EC + 0xAFC;
const DWORD dwP2RedHealth = 0x1551F0 + 0xAFC;
const DWORD dwP1SionBullets = 0x1552F6; // counts shots used i.e. 0=13 in mag, 4=9 in mag, etc
const DWORD dwP2SionBullets = 0x1552F6 + 0xAFC; // counts shots used i.e. 0=13 in mag, 4=9 in mag, etc
const DWORD dwP1RoaVisibleCharge = 0x155302;    // 0-9
const DWORD dwP2RoaVisibleCharge = 0x155302 + 0xAFC;    // 0-9
const DWORD dwP1RoaHiddenCharge = 0x155300; // 0-9
const DWORD dwP2RoaHiddenCharge = 0x155300 + 0xAFC; // 0-9
const DWORD dwP1Y = 0x155248;
const DWORD dwP2Y = 0x155248 + 0xAFC;
const DWORD dwP1X = 0x155238;
const DWORD dwP2X = 0x155238 + 0xAFC;
const DWORD dwP3X = 0x155238 + 0xAFC * 2;
const DWORD dwP4X = 0x155238 + 0xAFC * 3;
const DWORD dwP1Exists = 0x155130;
const DWORD dwP2Exists = 0x155130 + 0xAFC;
const DWORD dwP3Exists = 0x155130 + 0xAFC * 2;
const DWORD dwP4Exists = 0x155130 + 0xAFC * 3;
const DWORD dwP2PatternSet = 0x155F38;
const DWORD dwP1PatternRead = 0x155140;
const DWORD dwP4PatternSet = 0x157234;
const DWORD dwP2PatternRead = dwP1PatternRead + 0xAFC;
const DWORD dwCSSFlag = 0x155130;
const DWORD dwP2CharNumber = 0x34D91C;
const DWORD dwP2CharMoon = 0x34D924;
const DWORD dwP1CharMoon = 0x34D900;
const DWORD dwP1CharNumber = 0x34D8F8;
const DWORD dwP1ButtonPress = 0x154654;
const DWORD dwP1APressed = 0x371399;
const DWORD dwP1BPressed = 0x37139A;
const DWORD dwP1F1Pressed = 0x37144C;
const DWORD dwP1F2Pressed = 0x37144D;
const DWORD dwP1DPressed = 0x37139C;
const DWORD dwP1DirectionInput = 0x371398;
const DWORD dwPausedFlag = 0x162A64;
const DWORD dwEnemyAction = 0x37C1EC;
const DWORD dwLifeRecover = 0x37C1F8;
const DWORD dwP1InputEvent = 0x15543C;
const DWORD dwP2InputEvent = dwP1InputEvent + 0xAFC;
const DWORD dwP1ShieldType = 0x1552A0;
const DWORD dwP2ShieldType = dwP1ShieldType + 0xAFC;
const DWORD dwP1HitstunRemaining = 0x1552DC;
const DWORD dwP2HitstunRemaining = 0x1552DC + 0xAFC;
const DWORD dwP1NotInCombo = 0x155194; //1:InCombo 0:NotInCombo
const DWORD dwP2NotInCombo = 0x155194 + 0xAFC; //1:InCombo 0:NotInCombo
const DWORD dwP1HitstopRemaining = 0x1552D4; //0:not in hitstop
const DWORD dwP2HitstopRemaining = 0x1552D4 + 0xAFC; //0:not in hitstop
const DWORD dwComboCount = 0x157E00; // there's another address that tracks this
const DWORD dwP2E = 0x3713C9;
const DWORD dwMagicCircuitSetting = 0x37C1FC;
const DWORD dwBasePointer = 0x34D7FC;
const DWORD dwBurstCooldown = 0x155DBE;
const DWORD dwP1ArmorTimer = 0x1552C8; // 0:no armor >0:armor
const DWORD dwP2ArmorTimer = 0x1552C8 + 0xAFC;
const DWORD dwP2RecievedHitstop = 0x155DD0;
const DWORD dwGameMode = 0x162A74; // 16:training
const DWORD dwDrawFPS = 0x154128; // 0:off 1:on
const DWORD dwFPS = 0x374A70;
const DWORD dwP1Color = 0x34D83C;
const DWORD dwP2Color = 0x34D868;
const DWORD dwP1Struct = 0x155130;
const DWORD dwP2Struct = dwP1Struct + 0xAFC;
const DWORD dwP1RyougiKnife = 0x1552E8; //0=knife 1=no knife
const DWORD dwP2RyougiKnife = 0x1552E8 + 0xAFC; //0=knife 1=no knife
const DWORD dwP1FMaidsHisuiLeadHearts = 0x1552FC; //0=full 5=empty
const DWORD dwP1FMaidsKohaLeadHearts = 0x1568F6; //0=full 5=empty
const DWORD dwP2FMaidsHisuiLeadHearts = 0x1552FC + 0xAFC; //0=full 5=empty
const DWORD dwP2FMaidsKohaLeadHearts = 0x1568F6 + 0xAFC; //0=full 5=empty
const DWORD dwP1Blocking = 0x1552AB;
const DWORD dwP2Blocking = dwP1Blocking + 0xAFC;
const DWORD dwGlobalExFlash = 0x162A48;
const DWORD dwP1ExFlash = 0x158908;
const DWORD dwP2ExFlash = 0x158C14;
const DWORD dwFrameTimer = 0x15D1CC;
const DWORD dwGameState = 0x14EEE8; //1=training
const DWORD dwP1ThrowInvuln = 0x1552B6; //0=no >0=invuln
const DWORD dwP2ThrowInvuln = 0x1552B6 + 0xAFC; //0=no >0=invuln
const DWORD dwAttackInfo = 0x1595B8;
const DWORD dwInputDisplay = 0x1585F8;

// DLL Constants
const DWORD dwCameraX = 0x0055dec4;
const DWORD dwCameraY = 0x0055dec8;
const DWORD dwCameraZoom = 0x0054eb70;
const DWORD dwWindowWidth = 0x0054d048;
const DWORD dwWindowHeight = 0x0054d04c;
const DWORD dwP1AnimationPtr = dwP1Struct + 0x320;
const DWORD dwP2AnimationPtr = dwP2Struct + 0x320;

//FrameDisplay Constants

const int BAR_MEMORY_SIZE = 400; //Number of frames stored before overriding (FIFO). Only used in determining how far back you can scroll.
const int BAR_INTERVAL = 20; //Number of frames of only blanks before the bar stops and resets on the next non-blank frame
const int MAX_SAVES = 3;
const int SAVE_RESET_TIME = 60; //Frames of holding Save State Hotkey before clearing that save
const char TEXT_TIMER = 40; //How many frames Save State popup text stays on screen

const int SAVE_NUM_EFFECTS = 100;
const int SAVE_EFFECTS_SIZE = 0x33c;
const int SAVE_STOP_SITUATION_SIZE = 1632;
const int SAVE_ATTACK_DISPLAY_INFO_SIZE = 52;
const int SAVE_ATTACK_DISPLAY_INFO_2_SIZE = 1004;
const int SAVE_PLAYER_1_SIZE = 492;
const int SAVE_PLAYER_2_SIZE = 284;
const int SAVE_RNG_SIZE = 228;

const int ADJ_SAVE_EFFECTS_SIZE = SAVE_EFFECTS_SIZE / 4;
const int ADJ_SAVE_STOP_SITUATION_SIZE = SAVE_STOP_SITUATION_SIZE /4;
const int ADJ_SAVE_ATTACK_DISPLAY_INFO_SIZE = SAVE_ATTACK_DISPLAY_INFO_SIZE / 4;
const int ADJ_SAVE_ATTACK_DISPLAY_INFO_2_SIZE = SAVE_ATTACK_DISPLAY_INFO_2_SIZE / 4;
const int ADJ_SAVE_PLAYER_1_SIZE = SAVE_PLAYER_1_SIZE / 4;
const int ADJ_SAVE_PLAYER_2_SIZE = SAVE_PLAYER_2_SIZE / 4;
const int ADJ_SAVE_RNG_SIZE = SAVE_RNG_SIZE / 4;

const char REVERSE_INPUT_MAP[10] = { 0, 3, 2, 1, 6, 0, 4, 9, 8, 7 };
const char CH_MAP[3] = { ' ', 'H', 'L' };

// Foreground color -> \x1b[38;2;R;G;Bm
// Background color -> \x1b[48;2;R;G;Bm
const std::string FD_CLEAR = "\x1b[0m";
const std::string FD_UNDERLINE = "\x1b[4m";
const std::string FD_INACTIONABLE = "\x1b[38;2;255;255;255m\x1b[48;2;65;200;0m";
const std::string FD_JUMP = "\x1b[38;2;177;177;255m\x1b[48;2;241;224;132m";
const std::string FD_HITSTUN = "\x1b[38;2;255;255;255m\x1b[48;2;140;140;140m";
const std::string FD_BLOCKSTUN = "\x1b[38;2;255;255;255m\x1b[48;2;180;180;180m";
const std::string FD_ACTIONABLE = "\x1b[38;2;92;92;92m\x1b[48;2;0;0;0m";
const std::string FD_ADVANTAGE = "\x1b[38;2;255;255;255m\x1b[48;2;0;0;0m";
const std::string FD_NEUTRAL = "\x1b[38;2;255;255;255m\x1b[48;2;32;90;0m";
const std::string FD_THROW_ACTIVE = "\x1b[38;2;255;255;255m\x1b[48;2;192;0;128m";
const std::string FD_THROWN = "\x1b[38;2;255;255;255m\x1b[48;2;110;110;110m";
const std::string FD_CLASH = "\x1b[38;2;255;255;255m\x1b[48;2;225;184;0m";
const std::string FD_SHIELD = "\x1b[38;2;255;255;255m\x1b[48;2;145;194;255m";
const std::string FD_INACTIONABLE_INVULN = "\x1b[38;2;160;160;160m\x1b[48;2;255;255;255m";
const std::string FD_ACTIONABLE_INVULN = "\x1b[38;2;100;100;100m\x1b[48;2;255;255;255m";
const std::string FD_FREEZE = "\x1b[38;2;255;255;255m\x1b[48;2;60;60;60m";
const std::string FD_HITSTOP = "\x1b[38;2;255;255;255m\x1b[48;2;60;80;128m";
const std::string FD_ACTIVE = "\x1b[38;2;255;255;255m\x1b[48;2;255;0;0m";
const std::string FD_ASSIST_ACTIVE = "\x1b[38;2;255;255;255m\x1b[48;2;255;128;0m";
const std::string FD_BUTTON_PRESSED = "\x1b[38;2;255;255;255m\x1b[48;2;128;128;128m";
const std::string FD_A_PRESSED = "\x1b[38;2;255;143;169m\x1b[48;2;170;27;58m";
const std::string FD_B_PRESSED = "\x1b[38;2;255;255;137m\x1b[48;2;169;91;7m";
const std::string FD_C_PRESSED = "\x1b[38;2;143;255;195m\x1b[48;2;18;132;62m";
const std::string FD_D_PRESSED = "\x1b[38;2;137;255;255m\x1b[48;2;21;66;161m";
const std::string test = "hi";
const DADDRESS adMBAABase = 0x400000;

const DADDRESS adSaveCurrentCamZoom = 0x14EB70;
const DADDRESS adSaveDestinationCamZoom = 0x14EB74;
const DADDRESS adGameState = 0x14EEE8;
const DADDRESS adSaveDestinationCamX = 0x155124;
const DADDRESS adSaveDestinationCamY = 0x155128;

const DADDRESS adRNGArray = 0x16406C;
const DADDRESS adRNGIndex = 0x164068;

const DWORD dwPlayerStructSize = 0xAFC;
const DADDRESS adP1Base = 0x155130; //0x155130
const DADDRESS adP2Base = 0x155130 + 1 * dwPlayerStructSize; //0x155C2C
const DADDRESS adP3Base = 0x155130 + 2 * dwPlayerStructSize; //0x156728
const DADDRESS adP4Base = 0x155130 + 3 * dwPlayerStructSize; //0x157224

const DADDRESS adPattern = 0x10;
const DADDRESS adSave1Offset = 0x10;
const DADDRESS adState = 0x14;
const DADDRESS adHealth = 0xBC;
const DADDRESS adRedHealth = 0xC0;
const DADDRESS adGuardGauge = 0xC4;
const DADDRESS adGuardQuality = 0xD8;
const DADDRESS adMagicCircuit = 0xE0;
const DADDRESS adPlayerFrameCount = 0xF0;
const DADDRESS adXPosition = 0x108;
const DADDRESS adYPosition = 0x10C;
const DADDRESS adXSpeed = 0x11C;
const DADDRESS adYSpeed = 0x120;
const DADDRESS adXAcceleration = 0x124;
const DADDRESS adYAcceleration = 0x126;
const DADDRESS adMomentum = 0x138;
const DADDRESS adHitstop = 0x172;
const DADDRESS adThrowFlag = 0x176;
const DADDRESS adTagFlag = 0x178;
const DADDRESS adBlockstunFlag = 0x17B;
const DADDRESS adWillBlock = 0x17C;
const DADDRESS adEFStrikeInvuln = 0x185;
const DADDRESS adEFThrowInvuln = 0x186;
const DADDRESS adUntechTotal = 0x18E;
const DADDRESS adUntechCounter = 0x190;
const DADDRESS adHitstunRemaining = 0x1AC;
const DADDRESS adBlockHelper = 0x1EE;
const DADDRESS adCounterHit = 0x1FA;
const DADDRESS adSave2Offset = 0x200;
const DADDRESS adGravity = 0x2E4;
const DADDRESS adUntechPenalty = 0x2E8;
const DADDRESS adAirDirectionalInput = 0x2EA;
const DADDRESS adRawDirectionalInput = 0x2EB;
const DADDRESS adButtonInput = 0x2ED;
const DADDRESS adMacroInput = 0x2EE;
const DADDRESS adInputEvent = 0x30C;
const DADDRESS adOnRightFlag = 0x315;
const DADDRESS adAnimationDataPointer = 0x320;
const DADDRESS adAttackDataPointer = 0x324;
const DADDRESS adAnimationData_StateDataPointer = 0x38;
const DADDRESS adAnimationData_ConditionCount = 0x40;
const DADDRESS adAnimationData_BoxIndex = 0x42;
const DADDRESS adAnimationData_ConditionsPointer = 0x44;
const DADDRESS adStateData_Stance = 0xC;
const DADDRESS adStateData_Invuln = 0xD;
const DADDRESS adStateData_NormalCancel = 0xE;
const DADDRESS adStateData_SpecialCancel = 0xF;
const DADDRESS adStateData_Flagset2 = 0x18;
const DADDRESS adConditions_Condition1Pointer = 0x0;
const DADDRESS adConditions_Condition2Pointer = 0x4;
const DADDRESS adCondition_Type = 0x0;

const DADDRESS adP1TagFlag = 0x155130 + 0x178; //0x1552A8
const DADDRESS adP2TagFlag = 0x155130 + 0x178 + 1 * dwPlayerStructSize; //0x155DA4
const DADDRESS adP3TagFlag = 0x155130 + 0x178 + 2 * dwPlayerStructSize; //0x1568A0
const DADDRESS adP4TagFlag = 0x155130 + 0x178 + 3 * dwPlayerStructSize; //0x15739C

const DADDRESS adP1ControlledCharacter = 0x157DB8;
const DADDRESS adP1NextControlledCharacter = 0x157DBC;
const DADDRESS adSaveAttackDisplayInfo = 0x157DD8;
const DADDRESS adSaveAttackDisplayInfo2 = 0x157E10;
const DADDRESS adP1Inaction = 0x157FC0;
const DADDRESS adP2ControlledCharacter = 0x157FC4;
const DADDRESS adP2NextControlledCharacter = 0x157FC8;
const DADDRESS adP2Inaction = 0x1581CC;

const DADDRESS adSaveStopSituation = 0x158600;

const DADDRESS adP1Freeze = 0x158908;
const DADDRESS adP2Freeze = 0x158C14;
const DADDRESS adFrameCount = 0x15D1CC;

const DADDRESS adSaveCurrentCamX = 0x15DEC4;
const DADDRESS adSaveCurrentCamY = 0x15DEC8;

const DADDRESS adTrueFrameCount = 0x162A40;
const DADDRESS adGlobalFreeze = 0x162A48;

const DADDRESS adSaveRNG = 0x164068;

const DADDRESS adSaveCurrentCamXCopy = 0x164B14;
const DADDRESS adSaveCurrentCamYCopy = 0x164B18;

const DWORD dwEffectStructSize = 0x33C;
const DADDRESS adSaveEffects = 0x27BDE8;
const DADDRESS adEffectBase = 0x27BDE8;
const DADDRESS adEffectSource = 0x8;
const DADDRESS adEffectStatus = 0x9;

const DADDRESS adDummyState = 0x34D7F8;
const DADDRESS adP1FN1Input = 0x37144C;
const DADDRESS adP1FN2Input = 0x37144D;

//FrameBar Constants
const int DISPLAY_RANGE = 75;

const DADDRESS adNotInCombo = 0x64;
const DADDRESS adEffectOwner = 0x2F4;

// addresses for fonts
const DADDRESS adFont0 = 0x55D680;
const DADDRESS adFont1 = 0x55D260;
const DADDRESS adFont2 = 0x55DAA0;

// addresses for memory sharing
// let's include comments here so we know how big everything is
// to make it easier to add more.
const DADDRESS adShareBase = 0x381000;
const DADDRESS adSharedSaveSlot =					adShareBase + 0x0;	// 1 byte
const DADDRESS adSharedDoSave =						adShareBase + 0x1;	// 1 byte
const DADDRESS adSharedDoClearSave =					adShareBase + 0x2;	// 1 byte
const DADDRESS adSharedDisplayFreeze =				adShareBase + 0x3;	// 1 byte
const DADDRESS adSharedDisplayInputs =				adShareBase + 0x4;	// 1 byte
const DADDRESS adSharedScrolling =					adShareBase + 0x5;	// 2 bytes
const DADDRESS adSharedHoveringScroll =				adShareBase + 0x7;	// 1 byte
const DADDRESS adSharedFreezeOverride =				adShareBase + 0x8;	// 1 byte
const DADDRESS adSharedRNGMode =						adShareBase + 0x9;	// 1 byte
const DADDRESS adSharedRNGRate =						adShareBase + 0xA;	// 1 byte
const DADDRESS adSharedRNGCustomSeed =				adShareBase + 0xB;	// 4 bytes
const DADDRESS adSharedRNGCustomRN =					adShareBase + 0xF;	// 4 bytes
const DADDRESS adSharedHitboxStyle =					adShareBase + 0x14;	// 1 byte
const DADDRESS adSharedColorBlindMode =				adShareBase + 0x15;	// 1 byte
const DADDRESS adSharedDisplayHitboxes =				adShareBase + 0x16;	// 1 byte
const DADDRESS adSharedExtendOrigins =				adShareBase + 0x17; // 1 byte
const DADDRESS adSharedReversalKeyHeld =				adShareBase + 0x18; // 1 byte
const DADDRESS adSharedBackgroundStyle =				adShareBase + 0x19; // 1 byte
const DADDRESS adSharedDisableHUD =					adShareBase + 0x1A; // 1 byte
const DADDRESS adSharedDrawGround =					adShareBase + 0x1B; // 1 byte
const DADDRESS adSharedDisableShadow =				adShareBase + 0x1C; // 1 byte
const DADDRESS adSharedFastReversePenalty =			adShareBase + 0x1D; // 1 byte
const DADDRESS adSharedFrameDataDisplay =			adShareBase + 0x1E; // 1 byte
const DADDRESS adSharedSlowSpeed =					adShareBase + 0x1F; // 1 byte
const DADDRESS adSharedFrameBarY =					adShareBase + 0x20; // 4 bytes
const DADDRESS adSharedShowStats =					adShareBase + 0x24; // 1 byte
const DADDRESS adSharedP1InputDisplay =				adShareBase + 0x25; // 1 byte
const DADDRESS adSharedP2InputDisplay =				adShareBase + 0x26; // 1 byte
const DADDRESS adSharedHighlight =					adShareBase + 0x27; // 1 byte

const DADDRESS adSharedFreezeKey =					adShareBase + 0x30;	// 1 byte
const DADDRESS adSharedFrameStepKey =				adShareBase + 0x31;	// 1 byte
const DADDRESS adSharedHitboxesDisplayKey =			adShareBase + 0x32;	// 1 byte
const DADDRESS adSharedFrameDataDisplayKey =			adShareBase + 0x33;	// 1 byte
const DADDRESS adSharedHighlightsOnKey =				adShareBase + 0x34;	// 1 byte
const DADDRESS adSharedSaveStateKey =				adShareBase + 0x35;	// 1 byte
const DADDRESS adSharedPrevSaveSlotKey =				adShareBase + 0x36;	// 1 byte
const DADDRESS adSharedNextSaveSlotKey =				adShareBase + 0x37;	// 1 byte
const DADDRESS adSharedFrameBarScrollLeftKey =		adShareBase + 0x38;	// 1 byte
const DADDRESS adSharedFrameBarScrollRightKey =		adShareBase + 0x39;	// 1 byte
const DADDRESS adSharedRNGIncKey =					adShareBase + 0x3A; // 1 byte
const DADDRESS adSharedRNGDecKey =					adShareBase + 0x3B; // 1 byte
const DADDRESS adSharedReversalKey =					adShareBase + 0x3C; // 1 byte
const DADDRESS adSharedSlowKey =						adShareBase + 0x3D; // 1 byte

const DADDRESS adSharedIdleHighlight =				adShareBase + 0x50; // 4 bytes
const DADDRESS adSharedBlockingHighlight =			adShareBase + 0x54; // 4 bytes
const DADDRESS adSharedHitHighlight =				adShareBase + 0x58; // 4 bytes
const DADDRESS adSharedArmorHighlight =				adShareBase + 0x5C; // 4 bytes
const DADDRESS adSharedThrowProtectionHighlight =	adShareBase + 0x60; // 4 bytes

const DADDRESS adSharedMessageBuffer =				adShareBase + 0x100; // 32 bytes
const DADDRESS adSharedOnExtendedSettings =			adShareBase + 0x120; // 1 byte
const DADDRESS adSharedMainInfoText =				adShareBase + 0x121; // 64 bytes
const DADDRESS adSharedSubInfoText =					adShareBase + 0x161; // 64 bytes

// integer representations of raw float values
// not interested in messing with converting them when a table is good enough
const std::vector<int> vGuardLevelLookupTable =
{
    1174011904/*C 100*/, 1169915904/*C 75*/, 1165623296/*C 50*/, 1157234688/*C 25*/, 0/*C 0*/,
    1171963904/*F 100*/, 1168379904/*F 75*/, 1163575296/*F 50*/, 1155186688/*F 25*/, 0/*F 0*/,
    1176768512/*H 100*/, 1173755904/*H 75*/, 1168379904/*H 50*/, 1159991296/*H 25*/, 0/*H 0*/
};

const int MAX_REVERSAL_DELAY = 99;
const int MAX_HEALTH = 11400;
const int MAX_METER = 30000;
const int MAX_SETTINGS_PAGES = 11;
const int MAX_HOTKEY_PAGES = 3;
const int MAX_BULLETS = 13; //14:normal 15:infinite
const int MAX_CHARGE = 9;
const int MAX_HEARTS = 5; //6:normal 7:infinite
const int MIN_X = -65536;
const int MAX_X = 65536;
const int P1_DEFAULT_X = -16384;
const int P2_DEFAULT_X = 16384;
const int P3_DEFAULT_X = -29184;
const int P4_DEFAULT_X = 29184;
const int OFFSCREEN_LOCATION = 0x10000000;
const int ONSCREEN_LOCATION = 0x000000A0;
const int TOO_HIGH_TO_BURST = 10000;
const int MAX_BURST = 99;

const char pcSionBullets_13[13] = "SION BULLETS";
const char pcRoaVisibleCharge_19[19] = "ROA VISIBLE CHARGE";
const char pcRoaHiddenCharge_19[19] = "ROA HIDDEN CHARGE";
const char pcFMaidsHearts_15[15] = "F-MAIDS HEARTS";
const char pcRyougiKnife_13[13] = "RYOUGI KNIFE";
const char pcP1ControlledChar_19[19] = "P1 CONTROLLED CHAR";
const char pcP2ControlledChar_19[19] = "P2 CONTROLLED CHAR";
const char pcHitsUntilBurst_17[17] = "HITS UNTIL BURST";
const char pcNormal_7[7] = "NORMAL";
const char pcRepeat_7[7] = "REPEAT";
const char pcRandom_7[7] = "RANDOM";
const char pcShield_7[7] = "SHIELD";
const char pcInfinite_10[10] = "INFINITE";
const char pcOne_2[2] = "1";
const char pcMain_5[5] = "MAIN";
const char pcAssist_7[7] = "ASSIST";
const char pcHisui_6[6] = "HISUI";
const char pcKohaku_8[8] = "KOHAKU";

const char pcASlow_12[12] = "[A]->SLOWER";
const char pcP1XLoc_11[11] = "P1 X-LOC";
const char pcP2XLoc_11[11] = "P2 X-LOC";
const char pcAssistLoc_13[13] = "ASSIST X-LOC";
const char pcInvert_7[7] = "INVERT";
const char pcUnstable_11[11] = "(UNSTABLE)";

const char pcReversalSlot1_16[16] = "REVERSAL SLOT 1";
const char pcReversalSlot2_16[16] = "REVERSAL SLOT 2";
const char pcReversalSlot3_16[16] = "REVERSAL SLOT 3";
const char pcReversalSlot4_16[16] = "REVERSAL SLOT 4";
const char pcReversalType_14[14] = "REVERSAL TYPE";
const char pcPenaltyReset_14[14] = "PENALTY RESET";
const char pcInstant_8[8] = "INSTANT";
const char pcExGuard_9[9] = "EX GUARD";
const char pcReversalDelay_15[15] = "REVERSAL DELAY";
const char pcMeter_6[6] = "METER";
const char pcHealth_7[7] = "HEALTH";
const char pcGuardBar_10[10] = "GUARD BAR";
const char pcBlank_1[1] = "";
const char pcHotkeys_8[8] = "HOTKEYS";
const char pcCustomRNG_11[11] = "CUSTOM RNG";
const char pcSeed_5[5] = "SEED";
const char pcRate_5[5] = "RATE";
const char pcEveryFrame_13[13] = "EVERY FRAME";
const char pcEveryReset_13[13] = "EVERY RESET";
const char pcValue_6[6] = "VALUE";
const char pcBlank_32[32] = "";
const char pcBlank_64[64] = "";
const char pcPressA_32[32] = "PRESS A";
const char pcHoldA_32[32] = "HOLD A";
const char pcDisplayHitboxes_17[17] = "DISPLAY HITBOXES";
const char pcHitboxStyle_13[13] = "HITBOX STYLE";
const char pcColorBlindMode_17[17] = "COLOR BLIND MODE";
const char pcBlended_8[8] = "BLENDED";
const char pcLayered_8[8] = "LAYERED";
const char pcOriginStyle_13[13] = "ORIGIN STYLE";
const char pcStandard_9[9] = "STANDARD";
const char pcExtended_9[9] = "EXTENDED";
const char pcReversal_9[9] = "REVERSAL";
const char pcDrawOnScreen_15[15] = "DRAW ON SCREEN";
const char pcSlowMotion_12[12] = "SLOW MOTION";
const char pcThreeFourths_4[4] = "3/4";
const char pcOneHalf_4[4] = "1/2";
const char pcOneFourth_4[4] = "1/4";
const char pcList_5[5] = "LIST";
const char pcArcade_7[7] = "ARCADE";
const char pcBoth_5[5] = "BOTH";
const char pcP1InputDisplay_17[17] = "P1 INPUT DISPLAY";
const char pcP2InputDisplay_17[17] = "P2 INPUT DISPLAY";
const char pcShowStats_11[11] = "SHOW STATS";
const char pcAttackDisplay_15[15] = "ATTACK DISPLAY";

const char pcReversals_10[10] = "REVERSALS";
const char pcTraining_9[9] = "TRAINING";
const char pcPositions_10[10] = "POSITIONS";
const char pcSaveStates_12[12] = "SAVE STATES";
const char pcCharacter_10[10] = "CHARACTER";
const char pcHitboxes_9[9] = "HITBOXES";
const char pcHighlights_11[11] = "HIGHLIGHTS";
const char pcRNG_4[4] = "RNG";
const char pcSystem_8[8] = "SYSTEM";
const char pcUI_3[3] = "UI";
const char pcGeneralHotkeys_16[16] = "GENERAL HOTKEYS";
const char pcFrameDataHotkeys_19[19] = "FRAME DATA HOTKEYS";
const char pcRNGHotkeys_12[12] = "RNG HOTKEYS";
const char pcFrameDisplayY_16[16] = "FRAME DISPLAY Y";

const std::vector<const char*> vHighlightNames = {	"OFF",
													"RED",
													"YELLOW",
													"GREEN",
													"BLUE",
													"PURPLE",
													"BLACK" };
const std::vector<const char*> vHighlightNamesWithFormatting = {	"OFF",
																	"~RED",
																	"`YELLOW",
																	"@GREEN",
																	"{BLUE",
																	"^PURPLE",
																	"*BLACK" };
const std::vector<const char*> vBackgroundNames = { "NORMAL",
													"WHITE",
													"GRAY",
													"BLACK",
													"RED",
													"GREEN",
													"BLUE",
													"PURPLE",
													"YELLOW"
};

const std::vector<const char*> vBackgroundNamesWithFormatting = { "NORMAL",
																	"WHITE",
																	"$GRAY",
																	"*BLACK",
																	"~RED",
																	"@GREEN",
																	"{BLUE",
																	"^PURPLE",
																	"`YELLOW"
};

const char pcEnemyReversal_15[15] = "ENEMY REVERSAL";

const char pcRecover_8[8] = "RECOVER";
const char pcRecover_11[11] = "NO RECOVER";

const char pcTrainingPreset_17[17] = "training preset.";
const char pcExtendedSettings_18[18] = "EXTENDED SETTINGS";

const char pcLatestVersion_19[19] = "LATEST VERSION";
const char pcOffline_8[8] = "OFFLINE";

const char pcFrameData_11[11] = "FRAME DATA";
const char pcSaveStateSlot_16[16] = "SAVE STATE SLOT";
const char pcSaveState_11[11] = "SAVE STATE";
const char pcDisplayFreeze_16[16] = "DISPLAY FREEZE";
const char pcDisplayInputs_15[15] = "DISPLAY INPUTS";
const char pcScrollDisplay_15[15] = "SCROLL DISPLAY";
const char pcColorGuide_12[12] = "COLOR GUIDE";
const char pcAdvanced_9[9] = "ADVANCED";
const char pcOff_4[4] = "OFF";
const char pcOn_3[3] = "ON";
const char pcNone_5[5] = "NONE";

const char pcClearAllSaves_16[16] = "CLEAR ALL SAVES";
const char pcImportSave_12[12] = "IMPORT SAVE";
const char pcExportSave_12[12] = "EXPORT SAVE";
const char pcLoadRNG_9[9] = "LOAD RNG";
const char pcNoData_8[8] = "NO DATA";
const char pcNoSlotSelected_17[17] = "NO SLOT SELECTED";
const char pcPressA_8[8] = "PRESS A";

const char pcIdle_5[5] = "IDLE";
const char pcBlock_6[6] = "BLOCK";
const char pcHit_4[4] = "HIT";
const char pcArmor_6[6] = "ARMOR";
const char pcThrowProtection_17[17] = "THROW PROTECTION";
const char pcRed_4[4] = "RED";
const char pcGreen_6[6] = "GREEN";
const char pcBlue_5[5] = "BLUE";
const char pcGray_5[5] = "GRAY";
const char pcWhite_6[6] = "WHITE";

const char pcHideHUD_9[9] = "HIDE HUD";
const char pcHideShadow_13[13] = "HIDE SHADOWS";
const char pcBackground_11[11] = "BACKGROUND";
const char pcDrawGround_12[12] = "DRAW GROUND";

const char pcFreeze_11[11] = "FREEZE KEY";
const char pcNextStep_14[14] = "NEXT STEP KEY";
const char pcHitboxes_13[13] = "HITBOXES KEY";
const char pcFrameDisplay_18[18] = "FRAME DISPLAY KEY";
const char pcHighlights_15[15] = "HIGHLIGHTS KEY";
const char pcSaveState_15[15] = "SAVE STATE KEY";
const char pcPrevSaveSlot_19[19] = "PREV SAVE SLOT KEY";
const char pcNextSaveSlot_19[19] = "NEXT SAVE SLOT KEY";
const char pcFrameBarLeft_15[15] = "FRAME BAR LEFT";
const char pcFrameBarRight_17[17] = "FRAME BAR RIGHT";
const char pcNextRNG_13[13] = "NEXT RNG KEY";
const char pcPrevRNG_13[13] = "PREV RNG KEY";

#define VK_KEY_UNSET 0x0;

#define VK_KEY_0 0x30
#define VK_KEY_1 0x31
#define VK_KEY_2 0x32
#define VK_KEY_3 0x33
#define VK_KEY_4 0x34
#define VK_KEY_5 0x35
#define VK_KEY_6 0x36
#define VK_KEY_7 0x37
#define VK_KEY_8 0x38
#define VK_KEY_9 0x39

#define VK_KEY_A 0x41
#define VK_KEY_B 0x42
#define VK_KEY_C 0x43
#define VK_KEY_D 0x44
#define VK_KEY_E 0x45
#define VK_KEY_F 0x46
#define VK_KEY_G 0x47
#define VK_KEY_H 0x48
#define VK_KEY_I 0x49
#define VK_KEY_J 0x4A
#define VK_KEY_K 0x4B
#define VK_KEY_L 0x4C
#define VK_KEY_M 0x4D
#define VK_KEY_N 0x4E
#define VK_KEY_O 0x4F
#define VK_KEY_P 0x50
#define VK_KEY_Q 0x51
#define VK_KEY_R 0x52
#define VK_KEY_S 0x53
#define VK_KEY_T 0x54
#define VK_KEY_U 0x55
#define VK_KEY_V 0x56
#define VK_KEY_W 0x57
#define VK_KEY_X 0x58
#define VK_KEY_Y 0x59
#define VK_KEY_Z 0x5A

enum eKeyNames { KEY_FREEZE, KEY_FRAMESTEP, KEY_HITBOX, KEY_FRAMEDATA, KEY_HIGHLIGHT, KEY_SAVESTATE, KEY_PREVSAVE, KEY_NEXTSAVE, KEY_FRAMEBARLEFT, KEY_FRAMEBARRIGHT, KEY_RNGINC, KEY_RNGDEC, KEY_REVERSAL };

const uint8_t nDefaultFreezeKey = VK_KEY_UNSET;
const uint8_t nDefaultFrameStepKey = VK_KEY_UNSET;
const uint8_t nDefaultHitboxDisplayKey = VK_KEY_UNSET;
const uint8_t nDefaultFrameDataDisplayKey = VK_KEY_UNSET;
const uint8_t nDefaultHighlightsOnKey = VK_KEY_UNSET;
const uint8_t nDefaultSaveStateKey = VK_KEY_UNSET;
const uint8_t nDefaultPrevSaveSlotKey = VK_KEY_UNSET;
const uint8_t nDefaultNextSaveSlotKey = VK_KEY_UNSET;
const uint8_t nDefaultFrameBarScrollLeftKey = VK_KEY_UNSET;
const uint8_t nDefaultFrameBarScrollRightKey = VK_KEY_UNSET;
const uint8_t nDefaultRNGIncKey = VK_KEY_UNSET;
const uint8_t nDefaultRNGDecKey = VK_KEY_UNSET;
const uint8_t nDefaultReversalKey = VK_KEY_UNSET;
const uint8_t nDefaultSlowKey = VK_KEY_UNSET;

class KeyState
{
public:
	// please tell me if my use of classes here is overkill

	KeyState()
	{
		nKey = 0x00;
		nHeldKeyCounter = 0;
	}

	KeyState(int k)
	{
		nKey = k;
		nHeldKeyCounter = 0;
	}

	void setKey(int vKey_)
	{
		if (nKey != vKey_)
		{
			// reset the key state here to prevent it from firing
			// when it gets changed
			prevState = true;
			nKey = vKey_;
		}
	}

	bool isFocused()
	{
		return GetActiveWindow() == GetForegroundWindow();
	}

	bool keyHeld()
	{
		if (!isFocused()) {
			return false;
		}

		return nKey != 0x0 && GetAsyncKeyState(nKey) & 0x8000;
	}

	bool keyDown()
	{
		if (nKey == 0x0 || !isFocused()) {
			return false;
		}

		tempState = false;
		if (GetAsyncKeyState(nKey) & 0x8000)
			tempState = true;

		bool res = false;
		if (!prevState && tempState)
		{
			res = true;
		}

		prevState = tempState;

		return res;
	}
public:
	int nHeldKeyCounter;
private:
	uint8_t nKey;
	bool prevState = false;
	bool tempState = false;
};
//https://stackoverflow.com/questions/10737644/convert-const-char-to-wstring
std::wstring s2ws(const std::string& str)
{
	int size_needed = MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), NULL, 0);
	std::wstring wstrTo( size_needed, 0 );
	MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), &wstrTo[0], size_needed);
	return wstrTo;
}

static bool GetOpenSAVFileName(HANDLE hMBAAHandle, DWORD dwBaseAddress, std::wstring* pwsFileName)
{
	const uint8_t nOne = 1;
	const uint8_t nZero = 0;
	WriteProcessMemory(hMBAAHandle, (LPVOID)(dwBaseAddress + adSharedFreezeOverride), &nOne, 1, 0);

    LPWSTR pcFileName[MAX_PATH];

    OPENFILENAME ofn;
    ZeroMemory(pcFileName, sizeof(pcFileName));
    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = NULL;
    ofn.lpstrFilter = L"Save State\0*.sav\0";
    ofn.lpstrFile = (LPWSTR)pcFileName;
    ofn.nMaxFile = MAX_PATH;
    ofn.lpstrTitle = L"Open Save State";
    ofn.Flags = OFN_DONTADDTORECENT | OFN_FILEMUSTEXIST;

	bool bResult = GetOpenFileNameW((LPOPENFILENAMEW)&ofn);
	WriteProcessMemory(hMBAAHandle, (LPVOID)(dwBaseAddress + adSharedFreezeOverride), &nZero, 1, 0);
	if (bResult)
	{
		//*pwsFileName = std::wstring (ofn.lpstrFile);
		*pwsFileName = std::wstring (ofn.lpstrFile);
		return true;
	}
	return false;
}

static bool GetSaveSAVFileName(HANDLE hMBAAHandle, DWORD dwBaseAddress, std::wstring* pwsFileName)
{
	const uint8_t nOne = 1;
	const uint8_t nZero = 0;
	WriteProcessMemory(hMBAAHandle, (LPVOID)(dwBaseAddress + adSharedFreezeOverride), &nOne, 1, 0);

    LPWSTR pcFileName[MAX_PATH];

    OPENFILENAME ofn;
    ZeroMemory(pcFileName, sizeof(pcFileName));
    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = NULL;
    ofn.lpstrFilter = L"Save State\0*.sav\0";
    ofn.lpstrFile = (LPWSTR)pcFileName;
    ofn.nMaxFile = MAX_PATH;
    ofn.lpstrTitle = L"Create Save State";
    ofn.lpstrDefExt = L"sav";
    ofn.Flags = OFN_DONTADDTORECENT | OFN_OVERWRITEPROMPT;

	bool bResult = GetSaveFileNameW((LPOPENFILENAMEW)&ofn);
	WriteProcessMemory(hMBAAHandle, (LPVOID)(dwBaseAddress + adSharedFreezeOverride), &nZero, 1, 0);
    if (bResult)
	{
		*pwsFileName = std::wstring (ofn.lpstrFile);
		return true;
	}
	return false;
}

