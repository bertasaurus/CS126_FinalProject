#include "filler_game_app.h"

using fillergame::FillerGameApp;

void prepareSettings(FillerGameApp::Settings* settings) {
  settings->setResizable(false);
}

CINDER_APP(FillerGameApp, ci::app::RendererGl, prepareSettings);