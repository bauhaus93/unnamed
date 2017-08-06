#include "Sprite.h"

Sprite::Sprite(SDLWrapper& sdlWrapper_, int sizeX, int sizeY):
    sdlWrapper { sdlWrapper_ },
    texture { nullptr } {

    texture = SDL_CreateTexture(    sdlWrapper.GetRenderer(),
                                    SDL_PIXELFORMAT_RGBA8888,
                                    SDL_TEXTUREACCESS_TARGET,
                                    sizeX,
                                    sizeY);
    if (texture == nullptr) {
        throw SDLException("SDL_CreateTexture");
    }
}

void Sprite::SetAsRenderTarget(){
	if (SDL_SetRenderTarget(sdlWrapper.GetRenderer(), texture) == -1)
		throw SDLException("SDL_SetRenderTarget");
}

void Sprite::Draw(const Rect& srcRect, const Rect& destRect) {
    SDL_Rect src { srcRect.x, srcRect.y, srcRect.w, srcRect.h };
    SDL_Rect dest { destRect.x, destRect.y, destRect.w, destRect.h };

    if (SDL_RenderCopy(sdlWrapper.GetRenderer(), texture, &src, &dest) == -1)
		throw SDLException("SDL_RenderCopy");
}
