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
  _DIVVY
};

enum planck_keycodes {
  QWERTY = SAFE_RANGE,
  BACKLIT,
  EXT_PLV,
  PW,
  DEL_EML,
  ARC_EML,
  BRAVE,
  CALENDR,
  INTELIJ,
  ITERM,
  MAIL,
  NOTION,
  OUTLOOK,
  SIGNAL,
  SPOTIFY,
  TEAMS,
  TODOIST,
  UNANET,
  VMWARE,
  RMVIEW
};

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)
#define ARROW MO(_ARROW)
#define MODS MO(_MODS)

#define ESCAPE LT(ARROW, KC_ESC)
#define INTJ LT(MO(_INTJ), KC_F4)
#define MODKEYS LT(MODS, KC_DEL)
#define DIVVY LT(MO(_DIVVY), KC_D)

#define ADDTODO LGUI(LCTL(KC_A))

// VDI Shortcuts
#define TERMNAL LCTL(KC_GRV)

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

// MacOS Shortcuts
#define CYCLSCR LSFT(LCTL(LGUI(KC_G)))
#define ALFRED LALT(KC_SPACE)

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
#define CTL_1 LCTL(LALT(KC_1))
#define CTL_2 LCTL(LALT(KC_2))
#define CTL_3 LCTL(LALT(KC_3))
#define CTL_4 LCTL(LALT(KC_4))
#define CTL_5 LCTL(LALT(KC_5))
#define CTL_6 LCTL(LALT(KC_6))
#define CTL_7 LCTL(LALT(KC_7))
#define CTL_8 LCTL(LALT(KC_8))
#define CTL_9 LCTL(LALT(KC_9))
#define CTL_0 LCTL(LALT(KC_0))
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

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,-----------------------------------------------------------------------------------.
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Esc  |   A  |   S  |D/Divy|   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  "   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | IntJ | Ctrl | Alt  | GUI  |Lower |Space | Mods |Raise |Alfred| Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_QWERTY] = {
  { KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,     KC_I,    KC_O,    KC_P, KC_BSPC},
  { ESCAPE,    KC_A,    KC_S,   DIVVY,    KC_F,    KC_G,    KC_H,    KC_J,     KC_K,    KC_L, KC_SCLN, KC_QUOT},
  {KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,  KC_COMM,  KC_DOT, KC_SLSH,  KC_ENT},
  {   INTJ, KC_LCTL, KC_LALT, KC_LGUI,   LOWER,  KC_SPC, MODKEYS,   RAISE,   ALFRED, KC_DOWN,   KC_UP, KC_RGHT}
},

/* Lower
 * ,-----------------------------------------------------------------------------------.
 * |   ~  |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Del  |      |      |      |      |      |      |   _  |   +  |   {  |   }  |  |   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      | Next | Vol- | Vol+ | Play |
 * `-----------------------------------------------------------------------------------'
 */
[_LOWER] = {
  {KC_TILD, KC_EXLM,   KC_AT, KC_HASH,  KC_DLR, KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSPC},
  { KC_DEL, _______, _______, _______, _______, _______, _______, KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE},
  {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_MPLY},
  {_______, _______, _______, _______, _______, _______, _______, _______, KC_MPRV, KC_VOLD, KC_VOLU, KC_MNXT}
},

/* Raise
 * ,-----------------------------------------------------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Del  |      |      |      |      |      |      |   -  |   =  |   [  |   ]  |  \   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |Pg Up |Pg Dn |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      | Next | Vol- | Vol+ | Play |
 * `-----------------------------------------------------------------------------------'
 */
[_RAISE] = {
  { KC_GRV,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0, KC_BSPC},
  { KC_DEL, _______, _______, _______, _______, _______, _______, KC_MINS,  KC_EQL, KC_LBRC, KC_RBRC, KC_BSLS},
  {_______, _______, _______, _______, _______, _______, _______, _______, _______, KC_PGUP, KC_PGDN, _______},
  {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______}
},

/* Adjust (Lower + Raise)
 * ,-----------------------------------------------------------------------------------.
 * |      | Reset|      |      |      |Tdoist|iTerm |      |Intelj|Outlok|      |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |Signal|Calndr|      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |Teams |VMWare|Brave |Notion|Sptify|      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_ADJUST] = {
  {_______,   RESET, _______, _______, _______, TODOIST,   ITERM, _______, INTELIJ, OUTLOOK, _______, _______},
  {_______, _______,  SIGNAL, CALENDR, _______, _______, _______, _______, _______, _______, _______, _______},
  {_______, _______, _______,   TEAMS,  VMWARE,   BRAVE,  NOTION, SPOTIFY, _______, _______, _______, _______},
  {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______}
},

/* Arrow (Hold Escape)
 * ,-----------------------------------------------------------------------------------.
 * |      |  F1  |  F2  |  F3  |  F4  |      |      |DelEml|  Up  |ArcEml|      |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |  F5  |  F6  |  F7  |  F8  |      |AltLft| Left | Down | Right|AltRgt|      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |  F9  |  F10 |  F11 |  F12 | Home |  End |      |      |      |      |RmView|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |W.Menu|      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */

[_ARROW] = {
  {_______,   KC_F1,   KC_F2,   KC_F3,   KC_F4, _______, _______, DEL_EML,   KC_UP, ARC_EML, _______, ALTBSPC },
  {_______,   KC_F5,   KC_F6,   KC_F7,   KC_F8, _______, ALTLEFT, KC_LEFT, KC_DOWN, KC_RGHT, ALTRGHT, _______ },
  {_______,   KC_F9,  KC_F10,  KC_F11,  KC_F12, KC_HOME,  KC_END, GUILEFT, _______, GUIRGHT, _______,  RMVIEW },
  {_______, _______, _______, _______, _______, _______,  KC_APP, _______, _______, _______, _______, _______ }
},

/* IntelliJ (Fn)
 * ,-----------------------------------------------------------------------------------.
 * |      | Close|      |  End |Refctr|OpenIn|      |Usages|Prev_M|Outlin|      |  PW  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |HidWin|RnTgts|Symbol|DbugIt|Search|  Git |Hierar| Prev |Next_M| Next |FntRes|      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |ReRun |Run It|Create|ExtVar|MorGit| File | Menu |Font- |Font+ | Info |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |TWLeft|TWDown|TW Up |TWRght|
 * `-----------------------------------------------------------------------------------'
 */
 
[_INTJ] = {
  {_______,   CLOSE, _______,     END, REFACTR, GO2TEST, _______,  USAGES, PREVMTD, OUTLINE, _______, PW },
  {HIDWINS, RUNTGTS,  SYMBOL,   DEBUG,    FIND,     GIT, HIERARC,    BACK, NEXTMTD, FORWARD, FONTRES, _______ },
  {_______,   RERUN, EXECUTE,  CREATE, EXT_VAR, MOREGIT, FNDFILE,    MENU, FONT_DN, FONT_UP,    INFO, _______ },
  {_______, _______, _______, _______, _______, _______, _______, _______, MTWLEFT, MTWDOWN,  MTW_UP, MTWRGHT }
},

/* Mods
 * ,-----------------------------------------------------------------------------------.
 * |CtAlF4|Alt+1 |Alt+2 |Alt+3 |Alt+4 |Alt+5 |Alt+6 |Alt+7 |Alt+8 |Alt+9 |Alt+0 |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |Ctrl+`|Ctrl+1|Ctrl+2|Ctrl+3|Ctrl+4|Ctrl+5|Ctrl+6|Ctrl+7|Ctrl+8|Ctrl+9|Ctrl+0|      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |Gui+1 |Gui+2 |Gui+3 |Gui+4 |Gui+5 |Gui+6 |Gui+7 |Gui+8 |Gui+9 |Gui+0 |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |FulScr|      |      |      |      |      |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */

[_MODS] = {
  {_______,   ALT_1,   ALT_2,   ALT_3,   ALT_4,   ALT_5,   ALT_6,   ALT_7,   ALT_8,   ALT_9,   ALT_0, _______ },
  {TERMNAL,   CTL_1,   CTL_2,   CTL_3,   CTL_4,   CTL_5,   CTL_6,   CTL_7,   CTL_8,   CTL_9,   CTL_0, _______ },
  {_______,   GUI_1,   GUI_2,   GUI_3,   GUI_4,   GUI_5,   GUI_6,   GUI_7,   GUI_8,   GUI_9,   GUI_0, _______ },
  {_______, _______, _______, _______, _______, ADDTODO, _______, _______, _______, _______, _______, _______ }
},

/* Divvy
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |  <^  |  ^^  |  ^>  |      |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |  <   |FulScr|   >  |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |  <v  |  vv  |  v>  |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_DIVVY] = {
{_______, _______, _______, _______, _______, _______, _______, TOPLEFT, TOPHALF, TOPRGHT, _______, _______},
{_______, _______, _______, _______, _______, _______, _______, LFTHALF, FULLSCR, RGTHALF, _______, _______},
{_______, _______, _______, _______, _______, _______, _______, BOTLEFT, BOTHALF, BOTRGHT, _______, _______},
{_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______}
}

};

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
    case PW:
      if (record->event.pressed) {
        SEND_STRING("PW_PLACEHOLDER");
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
    case CALENDR:
      if (record->event.pressed) {
        SEND_STRING(SS_LALT(SS_TAP(X_SPACE)));
        _delay_ms(200);
        SEND_STRING("calendar");
        SEND_STRING(SS_TAP(X_ENTER));
      }
      return false;
    case INTELIJ:
      if (record->event.pressed) {
        SEND_STRING(SS_LALT(SS_TAP(X_SPACE)));
        _delay_ms(200);
        SEND_STRING("intellij");
        SEND_STRING(SS_TAP(X_ENTER));
      }
      return false;
    case ITERM:
      if (record->event.pressed) {
        SEND_STRING(SS_LALT(SS_TAP(X_SPACE)));
        _delay_ms(200);
        SEND_STRING("iterm");
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
    case OUTLOOK:
      if (record->event.pressed) {
        SEND_STRING(SS_LALT(SS_TAP(X_SPACE)));
        _delay_ms(200);
        SEND_STRING("outlook");
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
    case TEAMS:
      if (record->event.pressed) {
        SEND_STRING(SS_LALT(SS_TAP(X_SPACE)));
        _delay_ms(200);
        SEND_STRING("teams");
        SEND_STRING(SS_TAP(X_ENTER));
      }
      return false;
    case TODOIST:
      if (record->event.pressed) {
        SEND_STRING(SS_LALT(SS_TAP(X_SPACE)));
        _delay_ms(200);
        SEND_STRING("firefox");
        SEND_STRING(SS_TAP(X_ENTER));
      }
      return false;
    case VMWARE:
      if (record->event.pressed) {
        SEND_STRING(SS_LALT(SS_TAP(X_SPACE)));
        _delay_ms(200);
        SEND_STRING("vmware");
        SEND_STRING(SS_TAP(X_ENTER));
      }
      return false;
    case RMVIEW:
      if (record->event.pressed) {
	SEND_STRING(SS_LALT("v"));
	_delay_ms(100);
	SEND_STRING("r");
      }
      return false;
  }
  return true;
}
