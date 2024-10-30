/* Copyright 2023 @ Keychron (https://www.keychron.com)
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

#include QMK_KEYBOARD_H

enum layers {
    MAC_BASE,
    MAC_FN,
    WIN_BASE,
    WIN_FN,
    SHORTCUTS,
};

enum custom_macros { LOG_OUT = SAFE_RANGE, N_FD_BK, HOMEROW, HOMEROW_SCROLL };

// Left-hand home row mods
#define HOME_A LSFT_T(KC_A)
#define HOME_Q LCTL_T(KC_Q)
#define HOME_D LALT_T(KC_D)
#define HOME_F LGUI_T(KC_F)

// Right-hand home row mods
#define HOME_J RGUI_T(KC_J)
#define HOME_K LALT_T(KC_K)
#define HOME_P RCTL_T(KC_P)
#define HOME_SCLN RSFT_T(KC_SCLN)

// Macro Definitions
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        // for basic strings
        case N_FD_BK:
            if (record->event.pressed) {
                SEND_STRING("No feedback");
                return false;
            }

        // for more complex macros (want to add modifiers, etc.)
        case LOG_OUT:
            if (record->event.pressed) {
                register_code(KC_LGUI);
                register_code(KC_LCTL);
                register_code(KC_Q);
                unregister_code(KC_Q);
                unregister_code(KC_LCTL);
                unregister_code(KC_LGUI);
                return false;
            }

        case HOMEROW:
            if (record->event.pressed) {
                register_code(KC_LGUI);
                register_code(KC_LSFT);
                register_code(KC_SPC);
                unregister_code(KC_SPC);
                unregister_code(KC_LSFT);
                unregister_code(KC_LGUI);
                return false;
            }

        case HOMEROW_SCROLL:
            if (record->event.pressed) {
                register_code(KC_LGUI);
                register_code(KC_LSFT);
                register_code(KC_J);
                unregister_code(KC_J);
                unregister_code(KC_LSFT);
                unregister_code(KC_LGUI);
                return false;
            }
    }
    return true;
};

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [MAC_BASE] = LAYOUT_90_ansi(
        KC_MUTE,    KC_ESC,   KC_BRID,  KC_BRIU,  KC_MCTL,  KC_LPAD,  BL_DOWN,   BL_UP,    KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MUTE,  KC_VOLD,  KC_VOLU,  LOG_OUT,             KC_DEL,
        N_FD_BK,       KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,      KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,   KC_BSPC,            KC_PGUP,
        MC_2,       KC_TAB,   HOME_Q,     KC_W,     KC_E,     KC_R,     KC_T,      KC_Y,     KC_U,     KC_I,     KC_O,     HOME_P,     KC_LBRC,  KC_RBRC,  KC_BSLS,            KC_PGDN,
        MC_3,       KC_CAPS,  HOME_A,   KC_S,   HOME_D,   HOME_F,   KC_G,      KC_H,     HOME_J,   HOME_K,   KC_L,   HOME_SCLN,KC_QUOT,  KC_ENT,   KC_HOME,
        MC_4,       _______,  KC_Z,     KC_X,   KC_C,   KC_V,    KC_B,     MO(MAC_FN),     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  _______,  KC_UP,
        /* MC_4,       KC_LSFT,            KC_Z,     KC_X,   KC_C,   KC_V,    KC_B,     MO(MAC_FN),     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  KC_RSFT,  KC_UP, */
        MC_5,       _______,  _______,  MO(MAC_FN), LT(SHORTCUTS,KC_SPC),  KC_ESC,           KC_SPC,     HOMEROW,        HOMEROW_SCROLL,            KC_LEFT,  KC_DOWN,  KC_RGHT),
        /* MC_5,       KC_LCTL,  KC_LOPTN,           KC_LCMMD, KC_SPC,  KC_ESC,           KC_SPC,             KC_RCMMD,           KC_RCTL,            KC_LEFT,  KC_DOWN,  KC_RGHT), */

    [MAC_FN] = LAYOUT_90_ansi(
        BL_TOGG,    _______,  KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,     KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   _______,            _______,
        _______,    _______,  BT_HST1,  BT_HST2,  BT_HST3,  _______,  _______,   _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,
        _______,    BL_TOGG,  BL_STEP,  BL_UP,    _______,  _______,  _______,   _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,
        _______,    _______,  _______,  BL_DOWN,  _______,  _______,  _______,   KC_LEFT,  KC_DOWN,  KC_UP,  KC_RIGHT,   _______,    _______,            _______,            _______,
        KC_SNAP,    _______,            _______,  _______,  _______,  _______,   BAT_LVL,  BAT_LVL,  NK_TOGG,  _______,  _______,  _______,  _______,  _______,  _______,
        _______,    _______,  _______,            _______,  _______,  _______,             _______,            _______,            _______,            _______,  _______,  _______),

    [WIN_BASE] = LAYOUT_90_ansi(
        KC_MUTE,    KC_ESC,   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,     KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   KC_INS,             KC_DEL,
        MC_1,       KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,      KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,   KC_BSPC,            KC_PGUP,
        MC_2,       KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,      KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,  KC_BSLS,            KC_PGDN,
        MC_3,       KC_CAPS,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,      KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,            KC_ENT,             KC_HOME,
        MC_4,       KC_LSFT,            KC_Z,     KC_X,     KC_C,     KC_V,      KC_B,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  KC_RSFT,  KC_UP,
        MC_5,       KC_LCTL,  KC_LWIN,            KC_LALT,  KC_SPC,  MO(WIN_FN),           KC_SPC,             KC_RALT,            KC_RCTL,            KC_LEFT,  KC_DOWN,  KC_RGHT),

    [WIN_FN] = LAYOUT_90_ansi(
        BL_TOGG,    _______,  KC_BRID,  KC_BRIU,  KC_TASK,  KC_FILE,  BL_DOWN,   BL_UP,    KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MUTE,  KC_VOLD,   KC_VOLU,  _______,            _______,
        _______,    _______,  BT_HST1,  BT_HST2,  BT_HST3,  _______,  _______,   _______,  _______,  _______,  _______,  _______,  _______,   _______,  _______,            _______,
        _______,    BL_TOGG,  BL_STEP,  BL_UP,    _______,  _______,  _______,   _______,  _______,  _______,  _______,  _______,  _______,   _______,  _______,            _______,
        _______,    _______,  _______,  BL_DOWN,  _______,  _______,  _______,   _______,  _______,  _______,  _______,  _______,  _______,             _______,            _______,
        _______,    _______,            _______,  _______,  _______,  _______,   BAT_LVL,  BAT_LVL,  NK_TOGG,  _______,  _______,  _______,   _______,  _______,  _______,
        _______,    _______,  _______,            _______,  _______,  _______,             _______,            _______,            _______,             _______,  _______,  _______),

    [SHORTCUTS] = LAYOUT_90_ansi(
        _______,    _______,  _______,    _______,    _______,    _______,    _______,     _______,    _______,    _______,    _______,    _______,   _______,   _______,   _______,            _______,
        _______,    _______,  _______,  _______,  _______,  _______,  _______,   _______,  LALT(KC_7),  LALT(KC_8),  LALT(KC_9),  LALT(KC_0),  _______,  _______,  _______,            _______,
        _______,    LCTL(KC_TAB),  LGUI(KC_Q),  LGUI(KC_W),    _______,  LGUI(KC_R),  LGUI(KC_T),   _______,  LCTL(KC_U),  _______,  _______,  _______,  _______,  _______,  _______,            _______,
        _______,    _______,  LGUI(KC_A),  _______,  LCTL(KC_D),  LGUI(KC_F),  _______,   HYPR(KC_H),  LAG(KC_J),  _______,  _______,   _______,    _______,            _______,            _______,
        _______,    _______,            _______,  LGUI(KC_X),  LGUI(KC_C),  LGUI(KC_V),   _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
        _______,    _______,  _______,            _______,  _______,  _______,             _______,            _______,            _______,            _______,  _______,  _______),
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [MAC_BASE] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [MAC_FN]   = { ENCODER_CCW_CW(BL_DOWN, BL_STEP) },
    [WIN_BASE] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [WIN_FN]   = { ENCODER_CCW_CW(BL_DOWN, BL_UP) },
    [SHORTCUTS]   = { ENCODER_CCW_CW(BL_DOWN, BL_UP) }, 
};
#endif // ENCODER_MAP_ENABLE
