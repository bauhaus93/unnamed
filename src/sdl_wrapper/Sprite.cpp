#include "Sprite.h"

namespace unnamed::sdl {

Sprite::Sprite(Wrapper& sdlWrapper_, const Size<int>& size):
    sdlWrapper { sdlWrapper_ },
    texture { nullptr } {

    texture = SDL_CreateTexture(    sdlWrapper.GetRenderer(),
                                    SDL_PIXELFORMAT_RGBA8888,
                                    SDL_TEXTUREACCESS_TARGET,
                                    size.x,
                                    size.y);
    if (texture == nullptr) {
        throw SDLException("SDL_CreateTexture");
    }
    if (SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND) < 0) {
        throw SDLException("SDL_SetTextureBlendMode");
    }

}

void Sprite::SetAsRenderTarget(){
	if (SDL_SetRenderTarget(sdlWrapper.GetRenderer(), texture) == -1)
		throw SDLException("SDL_SetRenderTarget");
}

void Sprite::Draw(const Rect& srcRect, const Rect& destRect) const {
    SDL_Rect src { srcRect.x, srcRect.y, srcRect.w, srcRect.h };
    SDL_Rect dest { destRect.x, destRect.y, destRect.w, destRect.h };

    if (SDL_RenderCopy(sdlWrapper.GetRenderer(), texture, &src, &dest) == -1)
		throw SDLException("SDL_RenderCopy");
}

void Sprite::MarkRed(const Rect& rect) {
    SetAsRenderTarget();
    sdlWrapper.DrawRect(rect, Color{ 0xFF, 0, 0, 0xFF });
    sdlWrapper.ClearRenderTarget();
}

}
