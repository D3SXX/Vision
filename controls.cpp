#include "controls.h"

Controls::Controls() {
}

void Controls::updateVolumeFromScrollBar(int value){
    this->audioVolume = ((float)value)/100;
    emit volumeChanged();
}
