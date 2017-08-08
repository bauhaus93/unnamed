#pragma once

#include <memory>

#include "common/Rect.h"
#include "common/Size.h"
#include "logger/StdLogger.h"
#include "AtlasElement.h"
#include "SubTreeFullException.h"

class Node {

    std::unique_ptr<Node>           subTree[4];
    std::unique_ptr<AtlasElement>   element;
    Rect                            rect;

public:
                                Node(const Rect& Rect_);
    int                         ExpandTree(int depth);
    bool                        HasElement() const;
    bool                        HasSubTree() const;
    bool                        FitsInMe(const Size& size) const;
    bool                        FitsInSubTree(const Size& size) const;
    bool                        IsSubTreeEmpty() const;
    void                        DestroySubTree();
    AtlasElement&               AddElement(const Size& size, SDLSprite& atlasSprite);

};
