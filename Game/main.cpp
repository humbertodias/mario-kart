// #define ALLEGRO_MAIN
// #include "AllegroKeyboard.h"
// #include "AllegroSystem.h"
// #include "Game.h"
//
// #include <allegro5/allegro.h>
// #include <iostream>
//
// int main(int argc, char **argv) {
//   AllegroSystem *allegro = AllegroSystem::Instance();
//
//   // Set up screen with size and fullscreen mode
//   if (!allegro->setupScreen(ObjectSize(640, 480), false, DepthAuto)) {
//     std::cerr << "Error setting up screen." << std::endl;
//     return -1;
//   }
//
//   // Initialize the timers (30 FPS)
//   allegro->initializeTimers();
//
//   // Install keyboard
//   allegro->installKeyboard();
//
//   Game game;
//   int oldTime = 0;
//
//   // Main game loop
//   while (!game.quit()) {
//     // Poll for events (keyboard, timer, etc.)
//     allegro->pollEvents();
//
//     // If SpeedCounter is 0, wait for the next event
//     if (AllegroSystem::SpeedCounter == 0) {
//       al_rest(1.0 / 30.0); // Throttle to 30 FPS
//     }
//
//     // Process the game logic
//     while (AllegroSystem::SpeedCounter > 0) {
//       long oldSpeedCounter = AllegroSystem::SpeedCounter;
//
//       // Process input events
//       game.processInputEvents();
//
//       // Update the game state
//       game.update();
//
//       // Decrease the SpeedCounter after processing each frame
//       AllegroSystem::SpeedCounter--;
//
//       // Prevent running too many frames in one cycle
//       if (oldSpeedCounter <= AllegroSystem::SpeedCounter)
//         break;
//     }
//
//     // FPS calculations
//     AllegroSystem::Fps++;
//     if (AllegroSystem::TimeTicks - oldTime >= 30) {
//       AllegroSystem::LastFps = AllegroSystem::Fps;
//       AllegroSystem::Fps = 0;
//       oldTime = AllegroSystem::TimeTicks;
//     }
//
//     // Render the game
//     game.render();
//   }
//
//   return 0;
// }
