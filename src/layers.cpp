#include "layers.h"
#include "key_events.h"

static uint8_t DefaultLayer;
static uint32_t LayerState;

Layer_::Layer_ (void) {
    Serial.println ("[debug] Layer_ constructor called.");
    defaultLayer (0);
}

Key Layer_::lookup(byte row, byte col) {
    Key mappedKey;
    int8_t layer = 31;

    mappedKey.raw = Key_Trans.raw;

    do {
        if (Layer.isOn (layer))
            mappedKey.raw = pgm_read_word(&(keymaps[layer][row][col]));
        layer--;
    } while (mappedKey.raw != Key_Trans.raw && layer > DefaultLayer);

    // [debug] Layer_::lookup(row, col) = (flags, rawKey) @ layer
    Serial.print ("[debug] Layer_::lookup(");
    Serial.print (row, DEC);
    Serial.print (", ");
    Serial.print (col, DEC);
    Serial.print (") = (");
    Serial.print (mappedKey.flags, BIN);
    Serial.print (", ");
    Serial.print (mappedKey.rawKey, DEC);
    Serial.print (") @ ");
    Serial.println (layer, DEC);
    return mappedKey;
}

uint8_t Layer_::top (void) {
    Serial.print ("[debug]: Layer_::top() = ");
    for (int8_t i = 31; i >= 0; i--) {
      if (bitRead (LayerState, i)) {
           Serial.println(i, DEC);
            return i;
      }
    }
    Serial.println(0, DEC);
    return 0;
}

void Layer_::move (uint8_t layer) {
  Serial.print ("[debug] Layer_::move(");
  Serial.print (layer, DEC);
  Serial.println (")");

  LayerState = 0;
  on (layer);
}

void Layer_::on (uint8_t layer) {
    bitSet (LayerState, layer);
    Serial.print ("[debug] Layer_::on(");
    Serial.print (layer, DEC);
    Serial.print (") = ");
    Serial.println (LayerState, BIN);
}

void Layer_::off (uint8_t layer) {
    bitClear (LayerState, layer);
    Serial.print ("[debug] Layer_::off(");
    Serial.print (layer, DEC);
    Serial.print (") = ");
    Serial.println (LayerState, BIN);
}

boolean Layer_::isOn (uint8_t layer) {
  Serial.print ("[debug] Layer_::isOn(");
  Serial.print (layer, DEC);
  Serial.print (") = ");
  Serial.println (bitRead (LayerState, layer), DEC);

  return bitRead(LayerState, layer);
}

void Layer_::next (void) {
  Serial.println ("[debug]: Layer_::next()");
    on (top () + 1);
}

void Layer_::previous (void) {
  Serial.println ("[debug]: Layer_::previous()");
    off (top ());
}

void Layer_::defaultLayer (uint8_t layer) {
    move (layer);
    DefaultLayer = layer;
}

uint8_t Layer_::defaultLayer (void) {
    return DefaultLayer;
}

uint32_t Layer_::getLayerState (void) {
    return LayerState;
}

Layer_ Layer;
