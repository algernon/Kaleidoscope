#include "layers.h"
#include "key_events.h"

static uint8_t DefaultLayer;
static uint32_t LayerState;

Layer_::Layer_ (void) {
    defaultLayer (0);
}

Key Layer_::lookup(byte row, byte col) {
    Key mappedKey;
    int8_t layer = top ();

    do {
        mappedKey.raw = pgm_read_word(&(keymaps[layer][row][col]));
        layer--;
    } while (mappedKey.raw != Key_Trans.raw && layer > DefaultLayer);

    return mappedKey;
}

uint8_t Layer_::top (void) {
    for (uint8_t i = 31; i >= 0; i--) {
        if (bitRead (LayerState, i))
            return i;
    }
    return 0;
}

void Layer_::move (uint8_t layer) {
    LayerState = 0;
    on (layer);
}

void Layer_::on (uint8_t layer) {
    bitSet (LayerState, layer);
}

void Layer_::off (uint8_t layer) {
    bitClear (LayerState, layer);
}

boolean Layer_::isOn (uint8_t layer) {
    return bitRead(LayerState, layer);
}

void Layer_::next (void) {
    on (top () + 1);
}

void Layer_::previous (void) {
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
