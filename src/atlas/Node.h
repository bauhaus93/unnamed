#pragma once

#include <memory>
#include <algorithm>

#include "common/Rect.h"
#include "common/Size.h"
#include "common/StringFormat.h"
#include "logger/StdLogger.h"
#include "Element.h"
#include "NoAtlasSpaceException.h"

namespace unnamed::atlas {

class Node {

    std::unique_ptr<Node>           subTree[4];
    std::shared_ptr<Element>        element;
    Rect                            rect;
    Size<int>                            subSpace;

public:
    explicit                    Node(const Rect& Rect_);
    void                        ExpandTree();
    bool                        HasElement() const;
    bool                        HasSubTree() const;
    bool                        IsLeaf() const;
    bool                        FitsInMe(const Size<int>& size) const;
    bool                        FitsInSubTree(const Size<int>& size) const;
    Size<int>                        GetSubSpace() const;
    void                        RecalculateSubSpace();
    bool                        IsSubTreeEmpty() const;
    std::shared_ptr<Element>    AddElement(const Size<int>& size, sdl::Sprite& atlasSprite);

};

}
