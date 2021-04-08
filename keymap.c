/* Copyright 2015-2017 Jack Humbert
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "planck.h"
#include "action_layer.h"

extern keymap_config_t keymap_config;

enum planck_layers {
    _QWERTY,
    _LOWER,
    _RAISE,
    _ADJUST,
    _ARROW,
    _INTJ,
    _MODS,
    _APPS,
    _TODOIST,
    _EMOJI,
    _NAV,
    _MOD
};

enum planck_keycodes {
    QWERTY = SAFE_RANGE,
    STRING1,
    STRING2,
    DEL_EML,
    ARC_EML,
    // App shortcuts
    BRAVE,
    DISCORD,
    FINDER,
    INTELLIJ,
    MESSAGES,
    NOTION,
    POCKET,
    SIGNAL,
    SPOTIFY,
    TERMINAL,
    TODOIST,
    VIVALDI,
    // Todoist shortcuts
    T15MINS,
    T2HRS,
    T30MINS,
    T4HRS,
    T5MINS,
    T60MINS,
    TODAY,
    TOMORROW,
    WEEKEND,
    NEXTWEEK,
    P1,
    P2,
    P3,
    P4,
    RESPOND,
    // Emoji
    FACEPALM,
    HAPPY,
    MUSCLE,
    NO,
    SAD,
    THINKING,
    XFINGERS,
    YES
};

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)
#define ARROW MO(_ARROW)
#define MODS MO(_MODS)
#define EMOJI MO(_EMOJI)
#define NAV MO(_NAV)
#define MOD MO(_MOD)

#define ESCAPE LT(ARROW, KC_ESC)
#define INTJ LT(MO(_INTJ), KC_F4)
#define MODKEYS LT(MODS, KC_ENT)
#define TAB_ADJ LT(MO(_APPS), KC_TAB)
#define TODO MO(_TODOIST)
#define QUOTEMJI LT(EMOJI, KC_QUOT)
#define F_NAV LT(NAV, KC_F)
#define D_MOD LT(MOD, KC_D)

#define ADDTODO LGUI(LCTL(KC_A))

// IntelliJ Shortcuts
#define FNDFILE LSFT(LCTL(KC_N))
#define REFACTR LCTL(LALT(LSFT(KC_T)))
#define CLOSE LCTL(KC_F4)
#define HIDWINS LCTL(LSFT(KC_F12))
#define RUNTGTS LSFT(LALT(KC_F10))
#define RERUN LCTL(KC_F5)
#define EXECUTE LCTL(LSFT(KC_F10))
#define SYMBOL LSFT(LCTL(LALT(KC_N)))
#define DEBUG LCTL(LSFT(KC_F9))
#define END LCTL(KC_F2)
#define CREATE LALT(KC_INS)
#define FIND LCTL(LSFT(KC_F))
#define GO2TEST LCTL(LSFT(KC_T))
#define GIT LALT(KC_GRV)
#define MOREGIT LCTL(LALT(LSFT(KC_G)))
#define HIERARC LCTL(LALT(KC_H))
#define USAGES LALT(KC_F7)
#define MENU LALT(LSFT(KC_SCLN))
#define BACK LCTL(LALT(KC_LEFT))
#define FORWARD LCTL(LALT(KC_RGHT))
#define PREVMTD LALT(KC_UP)
#define NEXTMTD LALT(KC_DOWN)
#define FONT_DN LSFT(LCTL(LALT(KC_MINS)))
#define FONT_UP LSFT(LCTL(LALT(KC_EQL)))
#define FONTRES LSFT(LCTL(LALT(KC_SCLN)))
#define INFO LCTL(KC_F1)
#define OUTLINE LCTL(KC_F12)
#define PRVCHNG LCTL(LALT(LSFT(KC_UP)))
#define NXTCHNG LCTL(LALT(LSFT(KC_DOWN)))
#define EXT_VAR LCTL(LALT(KC_V))
#define ACEJUMP LCTL(LALT(KC_SCLN))
#define MTWLEFT LCTL(LSFT(KC_LEFT))
#define MTWDOWN LCTL(LSFT(KC_DOWN))
#define MTW_UP LCTL(LSFT(KC_UP))
#define MTWRGHT LCTL(LSFT(KC_RGHT))
#define MUTEBKPT LCTL(LALT(LSFT(KC_QUOT)))

// MacOS Shortcuts
#define ALFRED LALT(KC_SPACE)
#define ZOOMIN LGUI(KC_PLUS)
#define ZOOMOUT LGUI(KC_MINS)
#define BSP_WORD LALT(KC_BSPC)
#define DEL_WORD LALT(KC_DEL)

// MacOS Navigation Shortcuts
#define ALTBSPC LALT(KC_BSPC)
#define ALTLEFT LALT(KC_LEFT)
#define ALTRGHT LALT(KC_RGHT)
#define GUILEFT LGUI(KC_LEFT)
#define GUIRGHT LGUI(KC_RGHT)
#define ALT_1 LALT(KC_1)
#define ALT_2 LALT(KC_2)
#define ALT_3 LALT(KC_3)
#define ALT_4 LALT(KC_4)
#define ALT_5 LALT(KC_5)
#define ALT_6 LALT(KC_6)
#define ALT_7 LALT(KC_7)
#define ALT_8 LALT(KC_8)
#define ALT_9 LALT(KC_9)
#define ALT_0 LALT(KC_0)
#define CTL_1 LCTL(KC_1)
#define CTL_2 LCTL(KC_2)
#define CTL_3 LCTL(KC_3)
#define CTL_4 LCTL(KC_4)
#define CTL_5 LCTL(KC_5)
#define CTL_6 LCTL(KC_6)
#define CTL_7 LCTL(KC_7)
#define CTL_8 LCTL(KC_8)
#define CTL_9 LCTL(KC_9)
#define CTL_0 LCTL(KC_0)
#define GUI_1 LGUI(KC_1)
#define GUI_2 LGUI(KC_2)
#define GUI_3 LGUI(KC_3)
#define GUI_4 LGUI(KC_4)
#define GUI_5 LGUI(KC_5)
#define GUI_6 LGUI(KC_6)
#define GUI_7 LGUI(KC_7)
#define GUI_8 LGUI(KC_8)
#define GUI_9 LGUI(KC_9)
#define GUI_0 LGUI(KC_0)

// DIVVY Shortcuts
#define TOPLEFT LGUI(LSFT(LCTL(KC_R)))
#define TOPHALF LGUI(LSFT(LCTL(KC_T)))
#define TOPRGHT LGUI(LSFT(LCTL(KC_Y)))
#define LFTHALF LGUI(LSFT(LCTL(KC_F)))
#define FULLSCR LGUI(LSFT(LCTL(KC_G)))
#define RGTHALF LGUI(LSFT(LCTL(KC_H)))
#define BOTLEFT LGUI(LSFT(LCTL(KC_V)))
#define BOTHALF LGUI(LSFT(LCTL(KC_B)))
#define BOTRGHT LGUI(LSFT(LCTL(KC_N)))

// @formatter:off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,-----------------------------------------------------------------------------------------------------------------------.
 * |   Tab   |    Q    |    W    |    E    |    R    |    T    |    Y    |    U    |    I    |    O    |    P    |  Bksp   |
 * |---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------*---------|
 * |   Esc   |    A    |    S    | D / Mod | F / Nav |    G    |    H    |    J    |    K    |    L    |    ;    |" / Emoji|
 * |---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------|
 * |  Shift  |    Z    |    X    |    C    |    V    |    B    |    N    |    M    |    ,    |    .    |    /    |  Enter  |
 * |---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------|
 * |   IntJ  |  Ctrl   |   Alt   |   GUI   |  Lower  |  Space  |Mods/Entr|  Raise  | Alfred  |  Down   |   Up    | Todoist |
 * `-----------------------------------------------------------------------------------------------------------------------'
 */
[_QWERTY] = {
  { TAB_ADJ,     KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,      KC_I,     KC_O,     KC_P,  KC_BSPC},
  {  ESCAPE,     KC_A,     KC_S,    D_MOD,    F_NAV,     KC_G,     KC_H,     KC_J,      KC_K,     KC_L,  KC_SCLN, QUOTEMJI},
  { KC_LSFT,     KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,   KC_COMM,   KC_DOT,  KC_SLSH,   KC_ENT},
  {    INTJ,  KC_LCTL,  KC_LALT,  KC_LGUI,    LOWER,   KC_SPC,  MODKEYS,    RAISE,    ALFRED,  KC_DOWN,    KC_UP,     TODO}
},

/* Lower
 * ,-----------------------------------------------------------------------------------------------------------------------.
 * |    ~    |    !    |    @    |    #    |    $    |    %    |    ^    |    &    |    *    |    (    |    )    |  Bksp   |
 * |---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------|
 * |         |         |         |         |         |         |         |    _    |    +    |    {    |    }    |    |    |
 * |---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------|
 * |         |         |         |         |         |         |         |         |         |         |         |  Play   |
 * |---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------|
 * |         |         |         |         |         |         |         |         |PrevTrack|  Vol-   |  Vol+   |NextTrack|
 * `-----------------------------------------------------------------------------------------------------------------------'
 */
[_LOWER] = {
  { KC_TILD,  KC_EXLM,    KC_AT,  KC_HASH,   KC_DLR,  KC_PERC,  KC_CIRC,  KC_AMPR,  KC_ASTR,  KC_LPRN,  KC_RPRN,  KC_BSPC},
  { _______,  _______,  _______,  _______,  _______,  _______,  _______,  KC_UNDS,  KC_PLUS,  KC_LCBR,  KC_RCBR,  KC_PIPE},
  { _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  KC_MPLY},
  { _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  KC_MPRV,  KC_VOLD,  KC_VOLU,  KC_MNXT}
},

/* Raise
 * ,-----------------------------------------------------------------------------------------------------------------------.
 * |    `    |    1    |    2    |    3    |    4    |    5    |    6    |    7    |    8    |    9    |    0    |         |
 * |---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------|
 * |         |   F1    |   F2    |   F3    |   F4    |   F5    |   F6    |    -    |    =    |    [    |    ]    |     \   |
 * |---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------|
 * |         |   F7    |   F8    |   F9    |   F10   |   F11   |   F12   |         |         |  Pg Up  |  Pg Dn  |         |
 * |---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------|
 * |         |         |         |         |         |         |         |         |         |         |         |         |
 * `-----------------------------------------------------------------------------------------------------------------------'
 */
[_RAISE] = {
  {  KC_GRV,     KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,  _______},
  { _______,    KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,  KC_MINS,   KC_EQL,  KC_LBRC,  KC_RBRC,  KC_BSLS},
  { _______,    KC_F7,    KC_F8,    KC_F9,   KC_F10,   KC_F11,   KC_F12,  _______,  _______,  KC_PGUP,  KC_PGDN,  _______},
  { _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______}
},

/* Adjust (Lower + Raise)
 * ,-----------------------------------------------------------------------------------------------------------------------.
   |         |  Reset  |         |         |         |         |         |   <^    |   ^^    |   ^>    |         |         |
 * |---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------|
 * |         |         |         |         |         |         |         |   <<    |FulScreen|   >>    |         |         |
 * |---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------|
 * |         |         |         |         |         |         |         |   <v    |   vv    |   v>    |         |         |
 * |---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------|
 * |         |         |         |         |         |         |         |         |         |         |         |         |
 * `-----------------------------------------------------------------------------------------------------------------------'
 */
[_ADJUST] = {
  { _______,    RESET,  _______,  _______,  _______,  _______,  _______,  TOPLEFT,  TOPHALF,  TOPRGHT,  _______,  _______},
  { _______,  _______,  _______,  _______,  _______,  _______,  _______,  LFTHALF,  FULLSCR,  RGTHALF,  _______,  _______},
  { _______,  _______,  _______,  _______,  _______,  _______,  _______,  BOTLEFT,  BOTHALF,  BOTRGHT,  _______,  _______},
  { _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______}
},

/* App Shortcuts
 * ,-----------------------------------------------------------------------------------------------------------------------.
 * |         |         |         |         |         | Todoist |  iTerm  |         |IntelliJ |         | Pocket  |         |
 * |---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------|
 * |         |Messages | Signal  | Discord | Finder  |         |         |         |         |         |         |         |
 * |---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------|
 * |         |         |         |  Teams  | Vivaldi |  Brave  | Notion  | Spotify |         |         |         |         |
 * |---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------|
 * |         |         |         |         |         |         |         |         |         |         |         |         |
 * `-----------------------------------------------------------------------------------------------------------------------'
 */
[_APPS] = {
  { _______,  _______,  _______,  _______,  _______,  TODOIST, TERMINAL,  _______, INTELLIJ,  _______,   POCKET,  _______},
  { _______, MESSAGES,   SIGNAL,  DISCORD,   FINDER,  _______,  _______,  _______,  _______,  _______,  _______,  _______},
  { _______,  _______,  _______,  _______,  VIVALDI,    BRAVE,   NOTION,  SPOTIFY,  _______,  _______,  _______,  _______},
  { _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______}
},

/* Arrow (Hold Escape)
 * ,-----------------------------------------------------------------------------------------------------------------------.
 * |         |         |         |         |         |         |         |DeleteEml|   Up    |ArchveEml|         |         |
 * |---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------|
 * |         |DelWdLeft|Backspace| Delete  | DelWrd  |         |Left1Word|  Left   |  Down   |  Right  |Rght1Word|         |
 * |---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------|
 * |         |         |         |         |         |  Home   |   End   |Full Left|         |FullRight|         |         |
 * |---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------|
 * |         |         |         |         |         |         |         |         |         |Zoom Out | Zoom In |         |
 * `-----------------------------------------------------------------------------------------------------------------------'
 */

[_ARROW] = {
  { _______,  _______,  _______,  _______,  _______,  _______,  _______,  DEL_EML,    KC_UP,  ARC_EML,  _______,  _______ },
  { _______,  BSPCWRD,  KC_BSPC,   KC_DEL,  DELWORD,  _______,  ALTLEFT,  KC_LEFT,  KC_DOWN,  KC_RGHT,  ALTRGHT,  _______ },
  { _______,  _______,  _______,  _______,  _______,  KC_HOME,   KC_END,  GUILEFT,  _______,  GUIRGHT,  _______,  _______ },
  { _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,   ZOOMIN,  ZOOMOUT,  _______ }
},

/* IntelliJ (Fn)
 * ,-----------------------------------------------------------------------------------------------------------------------.
 * |         |  Close  |         |Stop Run |Refactor |GoTo Test|         | Usages  |PrevMethd| Outline |  Str1   |  Str2   |
 * |---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------|
 * |HidWndows|RunTargts| Symbol  |  Debug  |  Find   |   Git   |Hierarchy|Nav Back |NextMethd|NavForwrd|ResetFont|MuteBrkPt|
 * |---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------|
 * |         |  Rerun  |   Run   | Create  |ExtrctVar|More Git |  File   |  Menu   |  Font-  |  Font+  |  Info   |         |
 * |---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------|
 * |         |         |         |         |         |         |         |         |MovTWLeft|MovTWDown|MovTW Up |MovTWRght|
 * `-----------------------------------------------------------------------------------------------------------------------'
 */

[_INTJ] = {
  { _______,    CLOSE,  _______,      END,  REFACTR,  GO2TEST,  _______,   USAGES,  PREVMTD,  OUTLINE,  STRING1,  STRING2},
  { HIDWINS,  RUNTGTS,   SYMBOL,    DEBUG,     FIND,      GIT,  HIERARC,     BACK,  NEXTMTD,  FORWARD,  FONTRES, MUTEBKPT},
  { _______,    RERUN,  EXECUTE,   CREATE,  EXT_VAR,  MOREGIT,  FNDFILE,     MENU,  FONT_DN,  FONT_UP,     INFO,  _______},
  { _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  MTWLEFT,  MTWDOWN,   MTW_UP,  MTWRGHT}
},

/* Mods
 * ,-----------------------------------------------------------------------------------------------------------------------.
 * |         |  Alt+1  |  Alt+2  |  Alt+3  |  Alt+4  |  Alt+5  |  Alt+6  |  Alt+7  |  Alt+8  |  Alt+9  |  Alt+0  |         |
 * |---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------|
 * |         | Ctrl+1  | Ctrl+2  | Ctrl+3  | Ctrl+4  | Ctrl+5  | Ctrl+6  | Ctrl+7  | Ctrl+8  | Ctrl+9  | Ctrl+0  |         |
 * |---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------|
 * |         |  Gui+1  |  Gui+2  |  Gui+3  |  Gui+4  |  Gui+5  |  Gui+6  |  Gui+7  |  Gui+8  |  Gui+9  |  Gui+0  |         |
 * |---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------|
 * |         |         |         |         |         |Add To Do|         |         |         |         |         |         |
 * `-----------------------------------------------------------------------------------------------------------------------'
 */

[_MODS] = {
  { _______,    ALT_1,    ALT_2,    ALT_3,    ALT_4,    ALT_5,    ALT_6,    ALT_7,    ALT_8,    ALT_9,    ALT_0,  _______},
  { _______,    CTL_1,    CTL_2,    CTL_3,    CTL_4,    CTL_5,    CTL_6,    CTL_7,    CTL_8,    CTL_9,    CTL_0,  _______},
  { _______,    GUI_1,    GUI_2,    GUI_3,    GUI_4,    GUI_5,    GUI_6,    GUI_7,    GUI_8,    GUI_9,    GUI_0,  _______},
  { _______,  _______,  _______,  _______,  _______,  ADDTODO,  _______,  _______,  _______,  _______,  _______,  _______}
},

/* Todoist
 * ,-----------------------------------------------------------------------------------------------------------------------.
 * |         | @15mins | @2hours | @30mins | @4hours | @5mins  | @60mins |  Today  |Tomorrow | Weekend |Next Week|         |
 * |---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------|
 * |         |Priority1|Priority2|Priority3|Priority4|         |         |         |         |         |         |         |
 * |---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------|
 * |         |RespondTo|         |         |         |         |         |         |         |         |         |         |
 * |---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------|
 * |         |         |         |         |         |         |         |         |         |         |         |         |
 * `-----------------------------------------------------------------------------------------------------------------------'
 */

[_TODOIST] = {
  { _______,  T15MINS,    T2HRS,  T30MINS,    T4HRS,   T5MINS,  T60MINS,    TODAY, TOMORROW,  WEEKEND, NEXTWEEK,  _______},
  { _______,       P1,       P2,       P3,       P4,  _______,  _______,  _______,  _______,  _______,  _______,  _______},
  { _______,  RESPOND,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______},
  { _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______}
},

/* Emoji
 * ,-----------------------------------------------------------------------------------------------------------------------.
 * |         |         |         |         |         |Thinking |         |   Sad   |         |         |         |         |
 * |---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------|
 * |         |         |         |         |Face Palm|         |  Smile  |         |         |         |         |         |
 * |---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------|
 * |         |         |         |XedFngers|         |         |         | Muscle  |         |         |         |         |
 * |---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------|
 * |         |         |         |         |         |         |         |         |         |         |         |         |
 * `-----------------------------------------------------------------------------------------------------------------------'
 */

[_EMOJI] = {
  { _______,  _______,  _______,  _______,  _______, THINKING,      YES,      SAD,  _______,  _______,  _______,  _______},
  { _______,  _______,  _______,  _______, FACEPALM,  _______,    HAPPY,  _______,  _______,  _______,  _______, QUOTEMJI},
  { _______,  _______,  _______, XFINGERS,  _______,  _______,       NO,   MUSCLE,  _______,  _______,  _______,  _______},
  { _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______}
},

/* Navigation
 * ,-----------------------------------------------------------------------------------------------------------------------.
 * |         |         |         |         |         |         |         |         |   Up    |         |         |         |
 * |---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------|
 * |         |         |         |         |         |         |Alt+Left |  Left   |  Down   |  Right  |Alt+Right|         |
 * |---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------|
 * |         |         |         |         |         |         |         |GUI+Left |         |GUI+Right|         |         |
 * |---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------|
 * |         |         |         |         |         |         |         |         |         |         |         |         |
 * `-----------------------------------------------------------------------------------------------------------------------'
 */

[_NAV] = {
  { _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,    KC_UP,  _______,  _______,  _______},
  { _______,  _______,  _______,  _______,    F_NAV,  _______,  ALTLEFT,  KC_LEFT,  KC_DOWN,  KC_RGHT,  ALTRGHT,  _______},
  { _______,  _______,  _______,  _______,  _______,  _______,  _______,  GUILEFT,  _______,  GUIRGHT,  _______,  _______},
  { _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______}
},

/* Modification
 * ,-----------------------------------------------------------------------------------------------------------------------.
 * |         |         |         |         |         |         |         |         |   Up    |         |         |         |
 * |---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------|
 * |         |         |         |         |         |         |Alt+Left |Backspace|  Down   |Del Right|Alt+Right|         |
 * |---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------|
 * |         |         |         |         |         |         |         |GUI+Left |         |GUI+Right|         |         |
 * |---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------|
 * |         |         |         |         |         |         |         |         |         |         |         |         |
 * `-----------------------------------------------------------------------------------------------------------------------'
 */

[_MOD] = {
{ _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______},
{ _______,  _______,  _______,    D_MOD,  _______,  _______,  _______, BSP_WORD,  KC_BSPC,   KC_DEL, DEL_WORD,  _______},
{ _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______},
{ _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______}
}
};

// @formatter:on

uint32_t layer_state_set_user(uint32_t state) {
    return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

/*
void switch_to(char* app) {
    SEND_STRING(SS_LGUI(SS_TAP(X_SPACE)));
    _delay_ms(200);
    SEND_STRING(app);
    SEND_STRING(SS_TAP(X_ENTER));
}
*/

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case STRING1:
            if (record->event.pressed) {
                SEND_STRING("STRING1_PLACEHOLDER");
            }
            return false;
        case STRING2:
            if (record->event.pressed) {
                SEND_STRING("STRING2_PLACEHOLDER");
            }
            return false;
        case DEL_EML:
            if (record->event.pressed) {
                SEND_STRING("x#");
            }
            return false;
        case ARC_EML:
            if (record->event.pressed) {
                SEND_STRING("xE");
            }
            return false;
        case BRAVE:
            if (record->event.pressed) {
                SEND_STRING(SS_LALT(SS_TAP(X_SPACE)));
                _delay_ms(200);
                SEND_STRING("brave");
                SEND_STRING(SS_TAP(X_ENTER));
            }
            return false;
        case DISCORD:
            if (record->event.pressed) {
                SEND_STRING(SS_LALT(SS_TAP(X_SPACE)));
                _delay_ms(200);
                SEND_STRING("discord");
                SEND_STRING(SS_TAP(X_ENTER));
            }
            return false;
        case FINDER:
            if (record->event.pressed) {
                SEND_STRING(SS_LALT(SS_TAP(X_SPACE)));
                _delay_ms(200);
                SEND_STRING("finder");
                SEND_STRING(SS_TAP(X_ENTER));
            }
            return false;
        case INTELLIJ:
            if (record->event.pressed) {
                SEND_STRING(SS_LALT(SS_TAP(X_SPACE)));
                _delay_ms(200);
                SEND_STRING("intellij");
                SEND_STRING(SS_TAP(X_ENTER));
            }
            return false;
        case MESSAGES:
            if (record->event.pressed) {
                SEND_STRING(SS_LALT(SS_TAP(X_SPACE)));
                _delay_ms(200);
                SEND_STRING("messages");
                SEND_STRING(SS_TAP(X_ENTER));
            }
            return false;
        case NOTION:
            if (record->event.pressed) {
                SEND_STRING(SS_LALT(SS_TAP(X_SPACE)));
                _delay_ms(200);
                SEND_STRING("notion");
                SEND_STRING(SS_TAP(X_ENTER));
            }
            return false;
        case POCKET:
            if (record->event.pressed) {
                SEND_STRING(SS_LALT(SS_TAP(X_SPACE)));
                _delay_ms(200);
                SEND_STRING("pocket");
                SEND_STRING(SS_TAP(X_ENTER));
            }
            return false;
        case SIGNAL:
            if (record->event.pressed) {
                SEND_STRING(SS_LALT(SS_TAP(X_SPACE)));
                _delay_ms(200);
                SEND_STRING("signal");
                SEND_STRING(SS_TAP(X_ENTER));
            }
            return false;
        case SPOTIFY:
            if (record->event.pressed) {
                SEND_STRING(SS_LALT(SS_TAP(X_SPACE)));
                _delay_ms(200);
                SEND_STRING("spotify");
                SEND_STRING(SS_TAP(X_ENTER));
            }
            return false;
        case TERMINAL:
            if (record->event.pressed) {
                SEND_STRING(SS_LALT(SS_TAP(X_SPACE)));
                _delay_ms(200);
                SEND_STRING("terminal");
                SEND_STRING(SS_TAP(X_ENTER));
            }
            return false;
        case TODOIST:
            if (record->event.pressed) {
                SEND_STRING(SS_LALT(SS_TAP(X_SPACE)));
                _delay_ms(200);
                SEND_STRING("opera");
                SEND_STRING(SS_TAP(X_ENTER));
            }
            return false;
        case VIVALDI:
            if (record->event.pressed) {
                SEND_STRING(SS_LALT(SS_TAP(X_SPACE)));
                _delay_ms(200);
                SEND_STRING("vivaldi");
                SEND_STRING(SS_TAP(X_ENTER));
            }
            return false;
        case T15MINS:
            if (record->event.pressed) {
                SEND_STRING("@15mins");
                _delay_ms(100);
                SEND_STRING(SS_TAP(X_SPACE));
            }
            return false;
        case T2HRS:
            if (record->event.pressed) {
                SEND_STRING("@2hours");
                _delay_ms(100);
                SEND_STRING(SS_TAP(X_SPACE));
            }
            return false;
        case T30MINS:
            if (record->event.pressed) {
                SEND_STRING("@30mins");
                _delay_ms(100);
                SEND_STRING(SS_TAP(X_SPACE));
            }
            return false;
        case T4HRS:
            if (record->event.pressed) {
                SEND_STRING("@4hours");
                _delay_ms(100);
                SEND_STRING(SS_TAP(X_SPACE));
            }
            return false;
        case T5MINS:
            if (record->event.pressed) {
                SEND_STRING("@5mins");
                _delay_ms(100);
                SEND_STRING(SS_TAP(X_SPACE));
            }
            return false;
        case T60MINS:
            if (record->event.pressed) {
                SEND_STRING("@60mins");
                _delay_ms(100);
                SEND_STRING(SS_TAP(X_SPACE));
            }
            return false;
        case TODAY:
            if (record->event.pressed) {
                SEND_STRING("today");
                _delay_ms(100);
                SEND_STRING(SS_TAP(X_SPACE));
            }
            return false;
        case TOMORROW:
            if (record->event.pressed) {
                SEND_STRING("tomorrow");
                _delay_ms(100);
                SEND_STRING(SS_TAP(X_SPACE));
            }
            return false;
        case WEEKEND:
            if (record->event.pressed) {
                SEND_STRING("this weekend");
                _delay_ms(100);
                SEND_STRING(SS_TAP(X_SPACE));
            }
            return false;
        case NEXTWEEK:
            if (record->event.pressed) {
                SEND_STRING("next week");
                _delay_ms(100);
                SEND_STRING(SS_TAP(X_SPACE));
            }
            return false;
        case P1:
            if (record->event.pressed) {
                SEND_STRING("!!1");
                _delay_ms(100);
                SEND_STRING(SS_TAP(X_SPACE));
            }
            return false;
        case P2:
            if (record->event.pressed) {
                SEND_STRING("!!2");
                _delay_ms(100);
                SEND_STRING(SS_TAP(X_SPACE));
            }
            return false;
        case P3:
            if (record->event.pressed) {
                SEND_STRING("!!3");
                _delay_ms(100);
                SEND_STRING(SS_TAP(X_SPACE));
            }
            return false;
        case P4:
            if (record->event.pressed) {
                SEND_STRING("!!4");
                _delay_ms(100);
                SEND_STRING(SS_TAP(X_SPACE));
            }
            return false;
        case RESPOND:
            if (record->event.pressed) {
                SEND_STRING("@15mins");
                _delay_ms(100);
                SEND_STRING(SS_TAP(X_SPACE));
                SEND_STRING("@communication");
                _delay_ms(100);
                SEND_STRING(SS_TAP(X_SPACE));
                SEND_STRING("!!1");
                _delay_ms(100);
                SEND_STRING(SS_TAP(X_SPACE));
                SEND_STRING("today");
                _delay_ms(100);
                SEND_STRING(SS_TAP(X_SPACE));
                SEND_STRING("Respond to ");
            }
            return false;
        case FACEPALM:
            if (record->event.pressed) {
                SEND_STRING("::facepalm::");
                _delay_ms(100);
                SEND_STRING(" ");
            }
            return false;
        case HAPPY:
            if (record->event.pressed) {
                SEND_STRING("::happy::");
                _delay_ms(100);
                SEND_STRING(" ");
            }
            return false;
        case MUSCLE:
            if (record->event.pressed) {
                SEND_STRING("::muscle::");
                _delay_ms(100);
                SEND_STRING(" ");
            }
            return false;
        case NO:
            if (record->event.pressed) {
                SEND_STRING("::no::");
                _delay_ms(100);
                SEND_STRING(" ");
            }
            return false;
        case SAD:
            if (record->event.pressed) {
                SEND_STRING("::sad::");
                _delay_ms(100);
                SEND_STRING(" ");
            }
            return false;
        case THINKING:
            if (record->event.pressed) {
                SEND_STRING("::thinking::");
                _delay_ms(100);
                SEND_STRING(" ");
            }
            return false;
        case XFINGERS:
            if (record->event.pressed) {
                SEND_STRING("::xfing::");
                _delay_ms(100);
                SEND_STRING(" ");
            }
            return false;
        case YES:
            if (record->event.pressed) {
                SEND_STRING("::yes::");
                _delay_ms(100);
                SEND_STRING(" ");
            }
            return false;
    }
    return true;
}
