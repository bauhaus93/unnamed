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
    std::unique_ptr<Element>        element;
    Rect                            rect;
    Size                            subSpace;

public:
    explicit                    Node(const Rect& Rect_);
    void                        ExpandTree();
    bool                        HasElement() const;
    bool                        HasSubTree() const;
    bool                        IsLeaf() const;
    bool                        FitsInMe(const Size& size) const;
    bool                        FitsInSubTree(const Size& size) const;
    Size                        GetSubSpace() const;
    void                        RecalculateSubSpace();
    bool                        IsSubTreeEmpty() const;
    Element&                    AddElement(const Size& size, sdl::Sprite& atlasSprite);

};

}
