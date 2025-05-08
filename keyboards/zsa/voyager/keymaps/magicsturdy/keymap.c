// Copyright 2023 ZSA Technology Labs, Inc <@zsa>
// Copyright 2023 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

#include "voyager.h"
#include "layout.h"

enum layers {
  BASE,
  SYM,
  NAV,
};

enum custom_keycodes {
  RGB_SLD = SAFE_RANGE,
  // Macros invoked through the Magic key.
  M_ENT,
  M_MENT,
  M_ER,
  M_ES,
  M_UST,
  M_ON,
  M_ION,
  M_SP_BUT,
  M_EFORE,
  M_HICH,
};

// The "magic" key is the Alternate Repeat Key.
#define C_MAGIC QK_AREP

// Short aliases for home row mods and other tap-hold keys.
#define HRM_S LCTL_T(KC_S)
#define HRM_T LALT_T(KC_T)
#define HRM_R LSFT_T(KC_R)
#define HRM_D LGUI_T(KC_D)

#define HRM_N RGUI_T(KC_N)
#define HRM_E RSFT_T(KC_E)
#define HRM_A LALT_T(KC_A)
#define HRM_I RCTL_T(KC_I)

#define SPC_NAV LT(NAV, KC_SPACE)
#define BSPCSYM LT(SYM, KC_BSPC)

#define MAC_UND LGUI(KC_Z)
#define MAC_CUT LGUI(KC_X)
#define MAC_CPY LGUI(KC_C)
#define MAC_PST LGUI(KC_V)
// Screenshot to clipboard
#define MAC_SCR LGUI(LCTL(LSFT(KC_4)))

///////////////////////////////////////////////////////////////////////////////
// KEYMAP
///////////////////////////////////////////////////////////////////////////////
// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [BASE] = LAYOUT_LR(  // Base layer: Magic Sturdy.
    KC_GRV , XXXXXXX, XXXXXXX, KC_PLUS, KC_MINS, KC_EQL ,
    CW_TOGG, KC_V   , KC_M   , KC_L   , KC_C   , KC_P   ,
    KC_ESC , HRM_S  , HRM_T  , HRM_R  , HRM_D  , KC_Y   ,
    XXXXXXX, KC_X   , KC_K   , KC_J   , KC_G   , KC_W   ,
                                                 SPC_NAV, KC_ENT,

                      KC_LCBR, KC_RCBR, KC_LPRN, KC_RPRN, KC_LBRC, KC_RBRC,
                      KC_B   , C_MAGIC, KC_U   , KC_O   , KC_Q   , KC_BSLS,
                      KC_F   , HRM_N  , HRM_E  , HRM_A  , HRM_I  , KC_QUOT,
                      KC_Z   , KC_H   , KC_COMM, KC_DOT , KC_SLSH, KC_SCLN,
             KC_TAB , BSPCSYM
  ),

  [SYM] = LAYOUT_LR(  // Base layer: Magic Sturdy.
    _______, KC_F1  , KC_F2  , KC_F3  ,  KC_F4 , KC_F5  ,
    _______, KC_1   , KC_2   , KC_3   ,  KC_4  , KC_5   ,
    _______, KC_EXLM, KC_AT  , KC_HASH,  KC_DLR, KC_PERC,
    _______, _______, _______, _______, _______, _______,
                                                 _______, _______,

                      KC_F6  , KC_F7  , KC_F8  , KC_F9  , KC_F10 , KC_F11,
                      KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , KC_F12,
                      KC_CIRC, KC_AMPR, KC_ASTR, _______, _______, _______,
                      _______, _______, _______, _______, _______, _______,
             _______, _______
  ),

  [NAV] = LAYOUT_LR(  // Base layer: Magic Sturdy.
    _______, _______, _______, _______, MAC_SCR, _______,
    _______, _______, _______, _______, _______, _______,
    _______, KC_LCTL, KC_LOPT, KC_LSFT, KC_LCMD, _______,
    _______, MAC_UND, MAC_CUT, MAC_CPY, MAC_PST, _______,
                                                 _______, _______,

                      _______, _______, _______, _______, _______, _______,
                      KC_PGUP, KC_HOME, KC_UP  , KC_END , KC_VOLU, _______,
                      KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, KC_VOLD, _______,
                      _______, KC_MPRV, KC_MPLY, KC_MNXT, KC_MUTE, _______,
             _______, _______
  ),
};

///////////////////////////////////////////////////////////////////////////////
// TAPPING TERM PER KEY
///////////////////////////////////////////////////////////////////////////////
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case HRM_R:
            return TAPPING_TERM -20;
        case HRM_D:
            return TAPPING_TERM -20;
        case HRM_N:
            return TAPPING_TERM -20;
        case HRM_E:
            return TAPPING_TERM -20;
        case BSPCSYM:
            return TAPPING_TERM -20;
        default:
            return TAPPING_TERM;
    }
}

///////////////////////////////////////////////////////////////////////////////
// MAGIC KEY
///////////////////////////////////////////////////////////////////////////////
bool get_repeat_key_eligible_user(uint16_t keycode, keyrecord_t* record, uint8_t* remembered_mods) {
  switch (keycode) {
    case KC_A ... KC_Z:
      // Forget shift on repeat for letters
      if ((*remembered_mods & ~(MOD_MASK_SHIFT | MOD_BIT(KC_RALT))) == 0) {
          *remembered_mods &= ~MOD_MASK_SHIFT;
      }
      break;
  }

  return true;
}

uint16_t get_alt_repeat_key_keycode_user(uint16_t keycode, uint8_t mods) {
    switch (keycode) {
        case HRM_A: return KC_O;             // A -> O
        case KC_B: return M_EFORE;          // B -> EFORE
        case KC_C: return KC_Y;              // C -> Y
        case HRM_D: return KC_Y;             // D -> Y
        case HRM_E: return KC_U;             // E -> U

        case KC_G: return KC_Y;              // G -> Y

        case HRM_I: return M_ON;            // I -> ON
        case KC_J: return M_UST;            // J -> UST
        case KC_K: return KC_S;              // K -> S
        case KC_L: return KC_K;              // L -> K
        case KC_M: return M_ENT;            // M -> ENT
        case HRM_N: return M_ION;           // N -> ION
        case KC_O: return KC_A;              // O -> A
        case KC_P: return KC_Y;              // P -> Y

        case HRM_R: return KC_L;             // R -> L
        case HRM_S: return KC_K;             // S -> K
        case HRM_T: return M_MENT;          // T -> MENT
        case KC_U: return KC_E;              // U -> E
        case KC_V: return M_ER;             // V -> ER
        case KC_W: return M_HICH;           // W -> HICH
        case KC_X: return M_ES;             // X -> ES
        case KC_Y: return KC_P;              // Y -> P

        case KC_DOT:
            if (mods & MOD_MASK_SHIFT) {
                return KC_EQUAL;             // > -> =
            } else {
                return KC_BSLS;              // . -> \`
            }
        case KC_COMMA:
            if (mods & MOD_MASK_SHIFT) {
                return KC_EQUAL;             // < -> =
            } else {
                return M_SP_BUT;            // , -> ' but'
            }
        case KC_EQUAL: return KC_RABK;       // = -> >
        case KC_MINUS: return KC_RABK;       // - -> >

        case KC_1 ... KC_0: return KC_DOT;   // 1-0 -> .
    }

    return KC_N;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        int rep_count = get_repeat_key_count();
        if (rep_count < -1 && keycode != M_UST) {
            send_char('n');
            return false;
        }
        switch (keycode) {
            case M_ENT:
                SEND_STRING("ent");
                return false;
            case M_MENT:
                SEND_STRING("ment");
                return false;
            case M_ER:
                SEND_STRING("er");
                return false;
            case M_ES:
                SEND_STRING("es");
                return false;
            case M_UST:
                if (rep_count < -1) {
                    SEND_STRING("ment");
                } else {
                    SEND_STRING("ust");
                }
                return false;
            case M_ON:
                SEND_STRING("on");
                return false;
            case M_ION:
                SEND_STRING("ion");
                return false;
            case M_SP_BUT:
                SEND_STRING(" but");
                return false;
            case M_EFORE:
                SEND_STRING("efore");
                return false;
            case M_HICH:
                SEND_STRING("hich");
                return false;
        }
    }
    return true;
}

///////////////////////////////////////////////////////////////////////////////
// RGB
///////////////////////////////////////////////////////////////////////////////
extern rgb_config_t rgb_matrix_config;

void keyboard_post_init_user(void) {
  rgb_matrix_enable();
}

#define COLOUR1 {137, 255, 255}
#define COLOUR2 {137, 200, 255}
#define COLOUR3 {190, 150, 255}
#define COLOUR4 {245, 200, 255}
#define COLOUR5 {16, 255, 255}
#define COLOUR6 {21, 255, 255}
#define COLOUR7 {36, 255, 255}
#define COLOUR8 {53, 255, 255}

const uint8_t PROGMEM ledmap[][RGB_MATRIX_LED_COUNT][3] = {
    [0] = {
        COLOUR8, COLOUR7, COLOUR7, COLOUR6, COLOUR5, COLOUR4,
        COLOUR7, COLOUR7, COLOUR6, COLOUR5, COLOUR4, COLOUR3,
        COLOUR7, COLOUR6, COLOUR5, COLOUR4, COLOUR3, COLOUR2,
        COLOUR6, COLOUR5, COLOUR4, COLOUR3, COLOUR2, COLOUR1,
                                            COLOUR1, COLOUR1,

        COLOUR4, COLOUR5, COLOUR6, COLOUR7, COLOUR7, COLOUR8,
        COLOUR3, COLOUR4, COLOUR5, COLOUR6, COLOUR7, COLOUR7,
        COLOUR2, COLOUR3, COLOUR4, COLOUR5, COLOUR6, COLOUR7,
        COLOUR1, COLOUR2, COLOUR3, COLOUR4, COLOUR5, COLOUR6,
        COLOUR1, COLOUR1
    },
};

void set_layer_color(int layer) {
  for (int i = 0; i < RGB_MATRIX_LED_COUNT; i++) {
    HSV hsv = {
      .h = pgm_read_byte(&ledmap[layer][i][0]),
      .s = pgm_read_byte(&ledmap[layer][i][1]),
      .v = pgm_read_byte(&ledmap[layer][i][2]),
    };
    if (!hsv.h && !hsv.s && !hsv.v) {
        rgb_matrix_set_color( i, 0, 0, 0 );
    } else {
        RGB rgb = hsv_to_rgb( hsv );
        float f = (float)rgb_matrix_config.hsv.v / UINT8_MAX;
        rgb_matrix_set_color( i, f * rgb.r, f * rgb.g, f * rgb.b );
    }
  }
}

bool rgb_matrix_indicators_user(void) {
  if (keyboard_config.disable_layer_led) { return false; }
  switch (biton32(layer_state)) {
    case BASE:
    case SYM:
    case NAV:
      set_layer_color(0);
      break;
   default:
    if (rgb_matrix_get_flags() == LED_FLAG_NONE)
      rgb_matrix_set_color_all(0, 0, 0);
    break;
  }
  return true;
}
