#include "SDLSprite.h"

SDLSprite::SDLSprite(SDLWrapper& sdlWrapper_, const Size& size):
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

void SDLSprite::SetAsRenderTarget(){
	if (SDL_SetRenderTarget(sdlWrapper.GetRenderer(), texture) == -1)
		throw SDLException("SDL_SetRenderTarget");
}

void SDLSprite::Draw(const Rect& srcRect, const Rect& destRect) const {
    SDL_Rect src { srcRect.x, srcRect.y, srcRect.w, srcRect.h };
    SDL_Rect dest { destRect.x, destRect.y, destRect.w, destRect.h };

    if (SDL_RenderCopy(sdlWrapper.GetRenderer(), texture, &src, &dest) == -1)
		throw SDLException("SDL_RenderCopy");
}

void SDLSprite::MarkRed(const Rect& rect) {
    SetAsRenderTarget();
    sdlWrapper.DrawRect(rect, Color{ 0xFF, 0, 0, 0xFF });
    sdlWrapper.ClearRenderTarget();
}
