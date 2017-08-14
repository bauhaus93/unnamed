#include "Wrapper.h"

namespace unnamed::sdl {

Uint32 RenderCallback(Uint32 interval, void* param) {
    SDL_Event event;
    CallbackData* data = static_cast<CallbackData*>(param);

    memset(&event, 0, sizeof(SDL_Event));
    event.type = data->eventType;
    SDL_PushEvent(&event);

    return static_cast<Uint32>(data->handler.GetDelay());
}

Uint32 UpdateCallback(Uint32 interval, void* param) {
    SDL_Event event;
    CallbackData* data = static_cast<CallbackData*>(param);

    memset(&event, 0, sizeof(SDL_Event));
    event.type = data->eventType;
    SDL_PushEvent(&event);

    return static_cast<Uint32>(data->handler.GetDelay());
}

Wrapper::Wrapper(const std::string& windowTitle, const Size<int>& windowSize):
    window { nullptr },
    renderer { nullptr },
    dataRender { nullptr },
    dataUpdate { nullptr } {

    INFO("Initializing SDL2...");

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_TIMER) != 0) {
        throw SDLException("SDL_Init");
    }
    INFO("SDL initialized");

    SDL_version compiled;
    SDL_version linked;

    SDL_VERSION(&compiled);
    SDL_GetVersion(&linked);

    INFO(StringFormat("Compiled with SDL %d.%d.%d", compiled.major,
                                                    compiled.minor,
                                                    compiled.patch));


    INFO(StringFormat("Linked against SDL %d.%d.%d",    linked.major,
                                                        linked.minor,
                                                        linked.patch));

    if (compiled.major != linked.major ||
        compiled.minor != linked.minor ||
        compiled.patch != linked.patch) {
            WARN(StringFormat("SDL compiled/linked versions do not match: %d.%d.%d/%d.%d.%d",
                compiled.major,
                compiled.minor,
                compiled.patch,
                linked.major,
                linked.minor,
                linked.patch));
    }

    window = SDL_CreateWindow(  windowTitle.c_str(),
                                SDL_WINDOWPOS_UNDEFINED,
                                SDL_WINDOWPOS_UNDEFINED,
                                windowSize.x,
                                windowSize.y,
                                SDL_WINDOW_OPENGL);

    if (window == nullptr) {
        throw SDLException("SDL_CreateWindow");
    }
    INFO(StringFormat("Created window %dx%d", windowSize.x, windowSize.y));

    renderer = SDL_CreateRenderer(  window,
                                    -1,
                                    SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE);

    if (renderer == nullptr) {
        throw SDLException("SDL_CreateRenderer");
    }
    INFO("Created renderer");

    UseAlphaBlending();
}

Wrapper::~Wrapper() {

    StopTimers();

    if (renderer != nullptr) {
        SDL_DestroyRenderer(renderer);
        INFO("Destroyed renderer");
    }

    if (window != nullptr) {
        SDL_DestroyWindow(window);
        INFO("Destroyed window");
    }
    SDL_Quit();
    INFO("SDL quit");
}

void Wrapper::ClearScene() {
    SDL_RenderClear(renderer);
}

void Wrapper::ShowScene() {
    SDL_RenderPresent(renderer);
}

void Wrapper::ClearRenderTarget(){
    if (SDL_SetRenderTarget(renderer, nullptr) == -1)
        throw SDLException("SDL_SetRenderTarget");
}

void Wrapper::UseAlphaBlending() {
    if (SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND) < 0) {
        throw SDLException("SDL_SetRenderDrawBlendMode");
    }
}

void Wrapper::UseNoBlending() {
    if (SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE) < 0) {
        throw SDLException("SDL_SetRenderDrawBlendMode");
    }
}

void Wrapper::SetDrawColor(const Color& color) {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
}

void Wrapper::SetWindowTitle(const std::string& title){
	SDL_SetWindowTitle(window, title.c_str());
}

void Wrapper::DrawLine(const Point& start, const Point& stop, const Color& color) {
    if (lineRGBA(   renderer,
                    static_cast<int16_t>(start.x),
					static_cast<int16_t>(start.y),
					static_cast<int16_t>(stop.x),
					static_cast<int16_t>(stop.y),
                    color.r,
					color.g,
					color.b,
					color.a) < 0) {
        throw SDLException("lineRGBA");
    }
}

void Wrapper::DrawRect(const Rect& rect, const Color& color) {
    if (rectangleRGBA(  renderer,
						static_cast<int16_t>(rect.x),
						static_cast<int16_t>(rect.y),
						static_cast<int16_t>(rect.x + rect.w),
						static_cast<int16_t>(rect.y + rect.h),
                        color.r,
						color.g,
						color.b,
						color.a) < 0) {
        throw SDLException("rectangleRGBA");
    }
}

void Wrapper::DrawFillRect(const Rect& rect, const Color& color) {
    if (boxRGBA(    renderer,
					static_cast<int16_t>(rect.x),
					static_cast<int16_t>(rect.y),
					static_cast<int16_t>(rect.x + rect.w),
					static_cast<int16_t>(rect.y + rect.h),
					color.r,
					color.g,
					color.b,
					color.a) < 0){
        throw SDLException("boxRGBA");
    }
}

void Wrapper::DrawRoundedFillRect(const Rect& rect, int radius, const Color& color) {
    if (roundedBoxRGBA(     renderer,
							static_cast<int16_t>(rect.x),
							static_cast<int16_t>(rect.y),
							static_cast<int16_t>(rect.x + rect.w),
							static_cast<int16_t>(rect.y + rect.h),
							static_cast<int16_t>(radius),
							color.r,
							color.g,
							color.b,
							color.a) < 0){
        throw SDLException("roundedBoxRGBA");
    }
}

void Wrapper::DrawPoint(const Point& point, const Color& color) {
    if (pixelRGBA(  renderer,
					static_cast<int16_t>(point.x),
					static_cast<int16_t>(point.y),
                    color.r,
					color.g,
					color.b,
					color.a) < 0) {
        throw SDLException("pixelRGBA");
    }
}

void Wrapper::DrawFilledCircle(const Point& origin, int radius, const Color& color) {
    if (filledCircleRGBA(   renderer,
							static_cast<int16_t>(origin.x),
							static_cast<int16_t>(origin.y),
							static_cast<int16_t>(radius),
                            color.r,
							color.g,
							color.b,
							color.a) < 0) {
        throw SDLException("filledCircleRGBA");
    }
}

void Wrapper::StartTimers(const freq::FrequencyHandler& fpsHandler, const freq::FrequencyHandler& upsHandler) {

    dataRender = std::make_unique<CallbackData>(-1, fpsHandler, 0);
    dataUpdate = std::make_unique<CallbackData>(-1, upsHandler, 0);

    dataUpdate->eventType = SDL_RegisterEvents(2);
    if (dataUpdate->eventType == (Uint32)-1) {
        throw SDLException("SDL_RegisterEvents");
    }

    dataRender->eventType = dataUpdate->eventType++;
    if (dataRender->eventType == (Uint32)-1) {
        throw SDLException("SDL_RegisterEvents");
    }

    dataUpdate->timerId = SDL_AddTimer(33, UpdateCallback, (void*)&*dataUpdate);
    if (dataUpdate->timerId == 0) {
        throw SDLException("SDL_AddTimer");
    }
    INFO("Started update timer");

    dataRender->timerId = SDL_AddTimer(50, RenderCallback, (void*)&*dataRender);
    if (dataRender->timerId == 0) {
        throw SDLException("SDL_AddTimer");
    }
    INFO("Started render timer");
}

void Wrapper::StopTimers() {
    if (dataRender->timerId != 0) {
        SDL_RemoveTimer(dataRender->timerId);
        dataRender->timerId = 0;
        INFO("Removed render timer");
    }

    if (dataUpdate->timerId != 0) {
        SDL_RemoveTimer(dataUpdate->timerId);
        dataUpdate->timerId = 0;
        INFO("Removed update timer");
    }
}

std::unique_ptr<event::Event> Wrapper::WaitEvent() {
    SDL_Event sdlEvent;
    std::unique_ptr<event::Event> event = nullptr;

    while (event == nullptr) {

        if (SDL_WaitEvent(&sdlEvent) == 0) {
            throw SDLException("SDL_WaitEvent");
        }
        if (sdlEvent.type == dataRender->eventType) {
            event = std::make_unique<event::Event>(event::EventType::RENDER);
        }
        else if (sdlEvent.type == dataUpdate->eventType) {
            event = std::make_unique<event::Event>(event::EventType::UPDATE);
        }
        else {
            switch (sdlEvent.type){
            case SDL_QUIT:
                event = std::make_unique<event::Event>(event::EventType::QUIT);
                break;
            case SDL_KEYDOWN:
                event::Key key;
                switch(sdlEvent.key.keysym.sym) {
                case SDLK_UP: key = event::Key::UP;          break;
                case SDLK_DOWN: key = event::Key::DOWN;      break;
                case SDLK_LEFT: key = event::Key::LEFT;      break;
                case SDLK_RIGHT: key = event::Key::RIGHT;    break;
                default: key = event::Key::UNKNOWN;          break;
                }
                event = std::make_unique<event::EventKeyDown>(key);
                break;
            }
        }
    }

    return event;
}

SDL_Renderer* Wrapper::GetRenderer() const {
    return renderer;
}



}
