#include "AllegroSystem.h"
#include "AllegroKeyboard.h"
#include "AllegroScreen.h"

#include <allegro5/allegro.h>
#include <iostream>
#include <string>

AllegroSystem* AllegroSystem::mInstance = nullptr;
// Define the static variables
volatile long AllegroSystem::SpeedCounter = 0;
volatile long AllegroSystem::TimeTicks = 0;
volatile int AllegroSystem::Fps = 0;
volatile int AllegroSystem::AvgFps = 0;
volatile int AllegroSystem::LastFps = 0;

AllegroSystem::AllegroSystem() {
    if (!al_init()) {
        throw std::runtime_error("Failed to initialize Allegro.");
    }

    eventQueue = al_create_event_queue();
    if (!eventQueue) {
        throw std::runtime_error("Failed to create event queue.");
    }

    // Create and register a timer for logic updates (30 ticks/sec)
    timer = al_create_timer(1.0 / 30);
    if (!timer) {
        throw std::runtime_error("Failed to create timer.");
    }

    al_register_event_source(eventQueue, al_get_timer_event_source(timer));
    al_start_timer(timer);

    al_install_keyboard(); // Needed for AllegroKeyboard
    al_register_event_source(eventQueue, al_get_keyboard_event_source());

    lastTime = al_get_time();
}

AllegroSystem::~AllegroSystem() {
    if (timer) al_destroy_timer(timer);
    if (eventQueue) al_destroy_event_queue(eventQueue);
    delete mScreen;
    delete mKeyboard;
}

AllegroSystem* AllegroSystem::Instance() {
    if (!mInstance)
        mInstance = new AllegroSystem();
    return mInstance;
}

bool AllegroSystem::setupScreen(const ObjectSize& size, bool fullScreen, ColorDepth colorDepth) {
    try {
        mScreen = new AllegroScreen(size, fullScreen, colorDepth);
    } catch (const std::string& e) {
        std::cerr << "An exception occurred: " << e << std::endl;
        return false;
    }
    return true;
}

AllegroKeyboard* AllegroSystem::installKeyboard() {
    return (mKeyboard = new AllegroKeyboard());
}

void AllegroSystem::initializeTimers() {
    // Already handled via `al_create_timer` and `al_start_timer`
}

void AllegroSystem::pollEvents() {
    ALLEGRO_EVENT ev;
    while (al_get_next_event(eventQueue, &ev)) {
        if (ev.type == ALLEGRO_EVENT_TIMER) {
            SpeedCounter++;
            TimeTicks++;
        }
        if (mKeyboard) {
            // TODO: Optimize
            // mKeyboard->processEvent(ev);
            mKeyboard->update();
        }
    }
}

void AllegroSystem::waitForTicks() {
    // This can be left empty in Allegro 5 unless you want to throttle the frame rate.
}
