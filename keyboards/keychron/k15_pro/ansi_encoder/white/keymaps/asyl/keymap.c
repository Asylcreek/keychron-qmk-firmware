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

enum layers { MAC_BASE, MAC_FN, WIN_BASE, WIN_FN, SHORTCUTS, SHIFTED, SYM, CMD, SHORTS };

enum custom_macros { LOG_OUT = SAFE_RANGE, N_FD_BK, HOMEROW, HOMEROW_SCROLL, AE_SERVICE };

// define combo names
enum combos {
    COMBO_LCTL,
    COMBO_LGUI,
    COMBO_LALT,
    COMBO_LSFT,
    // more here...

    COMBO_LENGTH // nifty trick to avoid manually specifying how many combos you have
};

uint16_t COMBO_LEN = COMBO_LENGTH; // nifty trick continued

const uint16_t PROGMEM TS_GUI[]     = {KC_T, KC_S, COMBO_END};
const uint16_t PROGMEM RT_OPT[]     = {KC_R, KC_T, COMBO_END};
const uint16_t PROGMEM RTS_SFT[]    = {KC_R, KC_T, KC_S, COMBO_END};
const uint16_t PROGMEM ENTSPC_CTL[] = {LT(SHIFTED, KC_ENT), LT(SHORTS, KC_SPC), COMBO_END};

combo_t key_combos[] = {
    COMBO(TS_GUI, KC_LGUI),     //
    COMBO(RT_OPT, KC_LALT),     //
    COMBO(RTS_SFT, KC_LSFT),    //
    COMBO(ENTSPC_CTL, KC_LCTL), //
};

// Left-hand home row mods
/* #define HOME_A LSFT_T(KC_A) */
/* #define HOME_B LCTL_T(KC_B) */
/* #define HOME_D LALT_T(KC_D) */
/* #define HOME_F LGUI_T(KC_F) */

// Right-hand home row mods
/* #define HOME_J RGUI_T(KC_J) */
/* #define HOME_K LALT_T(KC_K) */
/* #define HOME_J RCTL_T(KC_J) */
/* #define HOME_SCLN RSFT_T(KC_SCLN) */

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

        case AE_SERVICE:
            if (record->event.pressed) {
                register_code(KC_LOPT);
                register_code(KC_LSFT);
                register_code(KC_SCLN);
                unregister_code(KC_SCLN);
                unregister_code(KC_LSFT);
                unregister_code(KC_LOPT);
                return false;
            }
    }
    return true;
};

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [MAC_BASE] = LAYOUT_90_ansi(
        KC_MUTE,    KC_ESC,         KC_BRID,           KC_BRIU,  KC_MCTL,               KC_LPAD,  BL_DOWN,   BL_UP,     KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MUTE,  KC_VOLD,  KC_VOLU,  LOG_OUT,             KC_DEL,
        N_FD_BK,    KC_LOPT,          KC_1,              KC_2,     KC_3,                  KC_4,     KC_5,      KC_6,      KC_7,     KC_8,     KC_9,     KC_0,     KC_NO,    KC_NO,   KC_NO,            KC_PGUP,
        /* MC_2,       KC_TAB,         HOME_B,            KC_L,     KC_D,                  KC_W,     KC_Z,      KC_QUOTE,  KC_F,     KC_O,     KC_U,     HOME_J,     KC_SCLN,  KC_NO,   KC_NO,            KC_PGDN, */
        MC_2,       KC_TAB,         KC_B,            KC_L,     KC_D,                  KC_W,     KC_Z,      KC_QUOTE,  KC_F,     KC_O,     KC_U,     KC_J,     KC_SCLN,  KC_NO,   KC_NO,            KC_PGDN,
        MC_3,       TG(SHIFTED),   KC_N,              KC_R,     KC_T,                  KC_S,     KC_G,      KC_Y,      KC_H,     KC_A,     KC_E,     KC_I,     KC_COMM,  KC_NO,   KC_HOME,
        KC_LGUI,    KC_NO,  KC_Q,              KC_X,     KC_M,                  KC_C,     KC_V,      MO(MAC_FN),KC_K,     KC_P,     KC_DOT,   KC_MINS,  KC_SLSH,  KC_NO,  KC_UP,
        MC_5,       HOMEROW,  HOMEROW_SCROLL,    LT(CMD,KC_ESC),   LT(SHIFTED,KC_ENT),  KC_LSFT,  LT(SHORTS,KC_SPC),    LT(SYM,KC_BSPC),    KC_NO,                                                 KC_LEFT,  KC_DOWN,  KC_RGHT),

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

    [SHIFTED] = LAYOUT_90_ansi(
        KC_TRNS,    KC_TRNS,        KC_TRNS,  KC_TRNS,  KC_TRNS,   KC_TRNS,  KC_TRNS,   KC_TRNS,    KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,             KC_TRNS,
        KC_TRNS,    KC_TRNS,        S(KC_1),  S(KC_2),  S(KC_3),   S(KC_4),     S(KC_5),      S(KC_6),      S(KC_7),     S(KC_8),     S(KC_9),     S(KC_0),     KC_TRNS,    KC_TRNS,   KC_TRNS,            KC_TRNS,
        KC_TRNS,    S(KC_TAB),         S(KC_B),  S(KC_L),  S(KC_D),   S(KC_W),     S(KC_Z),      S(KC_MINS),   S(KC_F),     S(KC_O),     S(KC_U),     S(KC_J),     S(KC_SCLN),  KC_TRNS,   KC_TRNS,            KC_TRNS,
        KC_TRNS,    KC_TRNS,   S(KC_N),  S(KC_R),  S(KC_T),   S(KC_S),     S(KC_G),      S(KC_Y),      S(KC_H),     S(KC_A),     S(KC_E),     S(KC_I),     S(KC_SLSH),  KC_TRNS,   KC_TRNS,
        KC_TRNS,    KC_TRNS,        S(KC_Q),  S(KC_X),  S(KC_M),   S(KC_C),     S(KC_V),KC_TRNS,S(KC_K),    S(KC_P),     S(KC_DOT),   S(KC_QUOT),  S(KC_COMM),  KC_TRNS,  KC_TRNS,
        KC_TRNS,    KC_TRNS, KC_TRNS,    KC_TRNS,   S(KC_ENT),  KC_TRNS,  KC_TRNS,    KC_TRNS,     KC_TRNS,            KC_TRNS,  KC_TRNS,  KC_TRNS),

    [SYM] = LAYOUT_90_ansi(
        KC_TRNS,    KC_TRNS,  KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,     KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   KC_TRNS,            KC_TRNS,
        KC_TRNS,    KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,   KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,            KC_TRNS,
        KC_TRNS,    KC_TRNS,  KC_TRNS,  KC_TRNS,    KC_TRNS,  S(KC_GRAVE),  KC_TRNS,   KC_TRNS,  S(KC_LBRC),  S(KC_RBRC),  S(KC_EQL),  S(KC_BSLS),  KC_TRNS,  KC_TRNS,  KC_TRNS,            KC_TRNS,
        KC_TRNS,    KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_GRAVE,  KC_TRNS,   KC_TRNS,  KC_LBRC,  KC_RBRC,   KC_EQL,    KC_BSLS,   KC_TRNS,              KC_TRNS,            KC_TRNS,
        KC_TRNS,    KC_TRNS,            KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,   KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,
        KC_TRNS,    KC_TRNS,  KC_TRNS,            KC_TRNS,  KC_TRNS,  KC_TRNS,             KC_TRNS,            KC_TRNS,            KC_TRNS,            KC_TRNS,  KC_TRNS,  KC_TRNS),

    [CMD] = LAYOUT_90_ansi(
        KC_TRNS,    KC_TRNS,  KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,     KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,            KC_TRNS,
        KC_TRNS,    KC_TRNS,  G(KC_1),  G(KC_2),  G(KC_3),  G(KC_4),  G(KC_5),   G(KC_6),  G(KC_7),  G(KC_8),  G(KC_9),  G(KC_0),  G(KC_EQL),  KC_TRNS,  KC_TRNS,            KC_TRNS,
        KC_TRNS,    G(KC_TAB),  G(KC_B),  G(KC_L),    G(KC_D),  G(KC_W),  G(KC_Z),   HYPR(KC_H),  G(KC_F),  G(KC_O),  G(KC_U),  G(LOPT(KC_J)),  G(KC_MINS),  KC_TRNS,  KC_TRNS,            KC_TRNS,
        KC_TRNS,    C(KC_TAB),  G(KC_N),  G(KC_R),  G(KC_T),  G(KC_S),  G(S(KC_T)),   G(KC_Y),  G(KC_SPC),  G(KC_A),   G(KC_E),    G(S(KC_SPC)),   KC_TRNS,              KC_TRNS,            KC_TRNS,
        KC_TRNS,    KC_TRNS,  G(KC_Q),  G(KC_X),  G(KC_M),  G(KC_C),   G(KC_V),  KC_TRNS,  KC_LSFT,  G(KC_P),  G(KC_LEFT),  G(KC_RIGHT),  G(S(KC_J)),  KC_TRNS,  KC_TRNS,
        KC_TRNS,    KC_TRNS,  KC_TRNS,            KC_TRNS,  KC_TRNS,  KC_TRNS,             G(KC_ENT),            G(KC_BSPC),            KC_TRNS,            KC_TRNS,  KC_TRNS,  KC_TRNS),

    [SHORTS] = LAYOUT_90_ansi(
        KC_TRNS,    KC_TRNS,  KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,     KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,            KC_TRNS,
        KC_TRNS,    KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,   KC_TRNS,  A(KC_7),  A(KC_8),  A(KC_9),  A(KC_0),  KC_TRNS,  KC_TRNS,  KC_TRNS,            KC_TRNS,
        KC_TRNS,    A(KC_TAB),  A(S(KC_7)),  A(S(KC_U)),    A(S(KC_0)),  A(S(KC_8)),  A(S(KC_9)),   A(KC_LEFT),  A(KC_UP),  A(KC_DOWN),  A(KC_RIGHT),  A(KC_J),  AE_SERVICE,  KC_TRNS,  KC_TRNS,            KC_TRNS,
        KC_TRNS,    C(KC_TAB),  A(KC_7),  A(KC_U),  A(KC_0),  A(KC_8),  A(KC_9),   KC_LEFT,  KC_DOWN,  KC_UP,   KC_RIGHT,    A(KC_K),   KC_TRNS,              KC_TRNS,            KC_TRNS,
        KC_TRNS,    KC_TRNS,            KC_LSFT,  C(S(KC_C)),  KC_LALT,  A(KC_COMM),   A(KC_SLSH),  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,
        KC_TRNS,    KC_TRNS,  KC_TRNS,            A(KC_BSPC),  A(KC_ENT),  KC_TRNS,             KC_TRNS,            KC_TRNS,            KC_TRNS,            KC_TRNS,  KC_TRNS,  KC_TRNS),
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [MAC_BASE] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [MAC_FN]   = { ENCODER_CCW_CW(BL_DOWN, BL_STEP) },
    [WIN_BASE] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [WIN_FN]   = { ENCODER_CCW_CW(BL_DOWN, BL_UP) },
    [SHORTCUTS]   = { ENCODER_CCW_CW(BL_DOWN, BL_UP) },
    [SHIFTED]   = { ENCODER_CCW_CW(BL_DOWN, BL_UP) },
    [SYM]   = { ENCODER_CCW_CW(BL_DOWN, BL_UP) },
    [CMD]   = { ENCODER_CCW_CW(BL_DOWN, BL_UP) },
    [SHORTS]   = { ENCODER_CCW_CW(BL_DOWN, BL_UP) },
};
#endif // ENCODER_MAP_ENABLE
