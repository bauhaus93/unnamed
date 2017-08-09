#pragma once

#include <memory>
#include <algorithm>

#include "common/Rect.h"
#include "common/Size.h"
#include "common/StringFormat.h"
#include "logger/StdLogger.h"
#include "AtlasElement.h"
#include "NoAtlasSpaceException.h"

class Node {

    std::unique_ptr<Node>           subTree[4];
    std::unique_ptr<AtlasElement>   element;
    Rect                            rect;

public:
    explicit                    Node(const Rect& Rect_);
    void                        ExpandTree();
    bool                        HasElement() const;
    bool                        HasSubTree() const;
    bool                        IsLeaf() const;
    bool                        FitsInMe(const Size& size) const;
    bool                        FitsInSubTree(const Size& size) const;
    Size                        MaxSubtreeSpace() const;
    bool                        IsSubTreeEmpty() const;
    AtlasElement&               AddElement(const Size& size, SDLSprite& atlasSprite);

};
