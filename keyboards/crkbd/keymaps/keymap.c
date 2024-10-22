#include QMK_KEYBOARD_H

//maybe add leader key? repeat key?
//qmk compile -kb crkbd -km 2haikus

enum custom_keycodes {
    KC_DTQS = SAFE_RANGE,
    KC_CMEX,
    KC_APQU,
    KC_SEMC,
    KC_PLAS,
    KC_MISL
};


uint16_t get_alt_repeat_key_keycode_user(uint16_t keycode, uint8_t mods) {
    bool shifted = (mods & MOD_MASK_SHIFT);  // Was Shift held?
    bool ctrled = (mods & MOD_MASK_CTRL);    //Was Ctrl held?
    bool ralted = (mods & MOD_MASK_ALT);    //Was RALT held?
    switch (keycode) {
        case KC_TAB:
            if (shifted) {        // If the last key was Shift + Tab,
                return KC_TAB;    // ... the reverse is Tab.
            } else {              // Otherwise, the last key was Tab,
                return S(KC_TAB); // ... and the reverse is Shift + Tab.
            }
        case KC_8:
            if (shifted) {        // (
                return S(KC_9);   // )
            } else if (ralted) {  // [
                return RALT(KC_9);// ]
            } else { 
                return KC_TRNS;
            }
        case KC_7:      
            if (ralted) {         // {
                return RALT(KC_0);// }    
            } else { 
                return KC_TRNS;
            }
        case KC_NUBS:             // <
            return S(KC_NUBS);    // >
        case KC_Z:
            if (ctrled) {
                return C(KC_Y);
            } else {
                return KC_TRNS;
            }
        case KC_Y:
            if (ctrled) {
                return C(KC_Z);
            } else {
                return KC_TRNS;
            }
        case KC_C: 
            if (ctrled) {
                return C(KC_V);
            } else { 
                return KC_TRNS;
            }
        case KC_X:
            if (ctrled) {
                return C(KC_V);
            } else { 
                return KC_TRNS;
            }
        case KC_F2: return S(KC_F2); //osu! random
    }
    return KC_TRNS;  // Defer to default definitions.
}                                                 

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case KC_DTQS: 
      if (record->event.pressed){
        if (get_mods() & MOD_BIT(KC_LSFT) || get_mods() & MOD_BIT(KC_RSFT)){
          register_code(KC_MINS);
        } else {
          register_code(KC_DOT);
        }
      } else {
        unregister_code(KC_MINS);
        unregister_code(KC_DOT);
      }
      return false;
    case KC_CMEX:
      if (record->event.pressed){
        if (get_mods() & MOD_BIT(KC_LSFT) || get_mods() & MOD_BIT(KC_RSFT)){
          register_code(KC_1);
        } else {
          register_code(KC_COMM);
        }
      } else {
        unregister_code(KC_1);
        unregister_code(KC_COMM);
      }
      return false;
    case KC_APQU:
      if (record->event.pressed){
        if (get_mods() & MOD_BIT(KC_LSFT) || get_mods() & MOD_BIT(KC_RSFT)){
          register_code(KC_2);
        } else {
          register_code(KC_NUHS);
        }
      } else {
        unregister_code(KC_2);
        unregister_code(KC_NUHS);
      }
      return false;
    case KC_SEMC:
      if (record->event.pressed){
        if (get_mods() & MOD_BIT(KC_LSFT) || get_mods() & MOD_BIT(KC_RSFT)){
          register_code(KC_COMM);
        } else {
          register_code16(S(KC_DOT));
        }
      } else {
        unregister_code16(S(KC_DOT));
        unregister_code(KC_COMM);
      }
      return false;
    case KC_PLAS:
      if (record->event.pressed){
        if (get_mods() & MOD_BIT(KC_LSFT) || get_mods() & MOD_BIT(KC_RSFT)){
          register_code(KC_NUHS);
        } else {
          register_code16(KC_MINS);
        }
      } else {
        unregister_code16(S(KC_NUHS));
        unregister_code(KC_MINS);
      }
      case KC_MISL:
      if (record->event.pressed){
        if (get_mods() & MOD_BIT(KC_LSFT) || get_mods() & MOD_BIT(KC_RSFT)){
          register_code(KC_7);
        } else {
          register_code16(KC_SLSH);
        }
      } else {
        unregister_code16(S(KC_7));
        unregister_code(KC_SLSH);
      }
      return false;
    default: 
      return true;
  }
}


/// windows and escape key maybe somewhere else and perhaps also do something about oled and swap hands. also quick tap term not working. fix
                                                                  // 0      1      2     3     4       5        6
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {  // default, nav, mouse, num, symbols, func, gaming
    [0] = LAYOUT_split_3x6_3( // BASE
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      KC_ESC,    KC_Q,    KC_L,    KC_R,    KC_B,  KC_APQU,                     KC_SEMC,  KC_W,    KC_U,    KC_D,   KC_Z, KC_PSCR,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_UP,    KC_S,    KC_H,    KC_N,    KC_T,   KC_F,                          KC_G,    KC_A,    KC_E,    KC_O,    KC_I,  KC_LEFT,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_DOWN, KC_X,     KC_M,     KC_C,    KC_V, KC_CMEX,                       KC_DTQS, KC_P,     KC_Y,    KC_K,     KC_J, KC_RIGHT,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                   QK_REP,KC_BSPC,LT(1,KC_TAB),         LT(3,KC_ENT), KC_SPC,QK_AREP 
                                 //`--------------------------'         `--------------------------'

  ),

    [1] = LAYOUT_split_3x6_3( // NAV 
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_MPLY, KC_MPRV, KC_MNXT,LGUI(KC_SPC), LCTL(KC_SPC),TG(5),                  XXXXXXX, KC_HOME,KC_PGDN, KC_PGUP,KC_END,XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      RCS(KC_T),LALT(KC_LEFT), LALT(KC_RGHT), RCS(KC_TAB), LCTL(KC_TAB), LCTL(KC_W),      XXXXXXX,KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       LGUI(KC_X), KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, LCTL(KC_NUBS),              XXXXXXX, KC_LSFT,  KC_LCTL, KC_LALT ,KC_LGUI, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          XXXXXXX, XXXXXXX,_______ ,    MO(4),  XXXXXXX, XXXXXXX
                                      //`--------------------------'  `--------------------------'
  ), 

    [2] = LAYOUT_split_3x6_3(  // MOUSE 
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                    XXXXXXX, KC_WH_L,KC_WH_D, KC_WH_U,  KC_WH_R, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R,XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, XXXXXXX,                      XXXXXXX, KC_LSFT,  KC_LCTL, KC_LALT ,KC_LGUI, XXXXXXX, 
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                         XXXXXXX, XXXXXXX, _______,     KC_BTN2, KC_BTN1, KC_BTN3
                                      //`--------------------------'  `--------------------------'
  ),
 
    [3] = LAYOUT_split_3x6_3(  // NUM 
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      KC_EQL, KC_NUBS, RALT(KC_7), RALT(KC_8), LSFT(KC_8), LSFT(KC_3),          XXXXXXX,  KC_7,    KC_8,    KC_9,  KC_LBRC, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      RALT(KC_RBRC), KC_PLAS, KC_MISL, LSFT(KC_0), RALT(KC_2), XXXXXXX,            KC_0,  KC_4,    KC_5,    KC_6,  KC_QUOT, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      LSFT(KC_RBRC), KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, XXXXXXX,             XXXXXXX,  KC_1,    KC_2,    KC_3,  KC_SCLN, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          XXXXXXX, XXXXXXX, MO(2),     _______, XXXXXXX,  XXXXXXX
                                      //`--------------------------'  `--------------------------'
  ), 
/*
 [4] = LAYOUT_split_3x6_3(  // SYMBOLS
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      KC_EQL,RALT(KC_7),RALT(KC_0),RALT(KC_8),RALT(KC_9),LSFT(KC_3),            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      RALT(KC_RBRC),KC_NUBS,LSFT(KC_NUBS),LSFT(KC_8),LSFT(KC_9),RALT(KC_2),     XXXXXXX, KC_LSFT, KC_LCTL, KC_LALT, KC_LGUI, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      LSFT(KC_RBRC), KC_MINS, KC_SLSH, LSFT(KC_NUHS), LSFT(KC_7), LSFT(KC_0),   XXXXXXX, KC_QUOT, KC_LBRC, KC_SCLN, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, _______, XXXXXXX
                                      //`--------------------------'  `--------------------------'
  ),
  */  

    [4] = LAYOUT_split_3x6_3(  // FUNCTION
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, RGB_MOD, XXXXXXX,                      XXXXXXX, KC_F7, KC_F8, KC_F9, KC_F10, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, KC_F4, KC_F5, KC_F6, KC_F11, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, XXXXXXX,                      XXXXXXX, KC_F1, KC_F2, KC_F3, KC_F12, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          XXXXXXX, XXXXXXX, XXXXXXX,    _______, XXXXXXX, XXXXXXX
                                      //`--------------------------'  `--------------------------'
  ),

  [5] = LAYOUT_split_3x6_3(  // GAMING
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      XXXXXXX, XXXXXXX, KC_E,   KC_W,     KC_E,   TG(5),                        XXXXXXX,  KC_U, KC_I, KC_O,  XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      LALT(KC_U), KC_LSFT,  KC_A,    KC_S,    KC_D,  KC_TAB,                      XXXXXXX,  KC_J, KC_K, KC_L,  XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_7,   KC_R,     XXXXXXX, KC_X,    KC_C,   XXXXXXX,                     XXXXXXX,  KC_1,    KC_2,    KC_3,  XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, KC_SPC , KC_ESC,     KC_ESC, KC_LALT, XXXXXXX
                                      //`--------------------------'  `--------------------------'
  )  
};


