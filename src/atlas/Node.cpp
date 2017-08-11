#include "Node.h"

namespace unnamed::atlas {

Node::Node(const Rect& rect_):
    subTree { nullptr, nullptr, nullptr, nullptr },
    element { nullptr },
    rect { rect_ },
    subSpace { rect.w, rect.h } {

}


void Node::ExpandTree() {
    Size subSize { rect.w / 2, rect.h / 2 };

    if (subSize.x <= 0 || subSize.y <= 0)
        return;

    subTree[0] = std::make_unique<Node>(Rect{ rect.x, rect.y, subSize.x, subSize.y });
    subTree[1] = std::make_unique<Node>(Rect{ rect.x + subSize.x, rect.y, subSize.x, subSize.y });
    subTree[2] = std::make_unique<Node>(Rect{ rect.x, rect.y + subSize.y, subSize.x, subSize.y });
    subTree[3] = std::make_unique<Node>(Rect{ rect.x + subSize.x, rect.y + subSize.y, subSize.x, subSize.y });
    subSpace = subSize;

}

bool Node::HasElement() const {
    return element != nullptr;
}

bool Node::HasSubTree() const {
    return subTree[0] != nullptr;
}

bool Node::IsLeaf() const {
    return !HasElement() && !HasSubTree();
}

bool Node::FitsInMe(const Size& size) const {
    return size.x <= rect.w && size.y <= rect.h;
}

bool Node::FitsInSubTree(const Size& size) const {
    return size.x <= rect.w / 2 && size.y <= rect.h / 2;
}

bool Node::IsSubTreeEmpty() const {
    if (HasSubTree()) {
        bool empty = true;
        for (int i = 0; i < 4 && empty; i++) {
            empty &= subTree[i]->IsSubTreeEmpty();
        }
        return empty;
    }
    return !HasElement();
}

Size Node::GetSubSpace() const {
    return subSpace;
}

void Node::RecalculateSubSpace() {
    Size maxSize = subTree[0]->GetSubSpace();
    for(int i = 1; i < 4; i++) {
        Size currSize = subTree[i]->GetSubSpace();
        if (std::min(currSize.x, currSize.y) > std::min(maxSize.x, maxSize.y)) {
            maxSize = currSize;
        }
    }
    subSpace = maxSize;
}

AtlasElement& Node::AddElement(const Size& size, sdl::SDLSprite& atlasSprite) {
    DEBUG(StringFormat("Node for (%d, %d, %d, %d)", rect.x, rect.y, rect.w, rect.h));

    if (FitsInSubTree(size)) {
        if (!HasSubTree()) {
            ExpandTree();
            DEBUG("Expanded tree");
            AtlasElement& element = subTree[0]->AddElement(size, atlasSprite);
            RecalculateSubSpace();
            return element;
        }
        else {
            for(int i = 0; i < 4; i++) {
                Size maxSize = subTree[i]->GetSubSpace();
                DEBUG(StringFormat("MaxSubtreeSpace: %d/%d, index: %d, leaf? %d", maxSize.x, maxSize.y, i, subTree[i]->IsLeaf()));
                if (size.x <= maxSize.x && size.y <= maxSize.y) {
                    AtlasElement& element = subTree[i]->AddElement(size, atlasSprite);
                    RecalculateSubSpace();
                    return element;
                }
            }
        }
    }
    else if (FitsInMe(size) && IsLeaf()){
        element = std::make_unique<AtlasElement>(Rect{ rect.x, rect.y, size.x, size.y}, atlasSprite);
        DEBUG(StringFormat("New atlas element (%d, %d, %d, %d) in %d/%d",   rect.x,
                                                                            rect.y,
                                                                            size.x,
                                                                            size.y,
                                                                            rect.w,
                                                                            rect.h));
        subSpace = Size{ 0, 0 };
        return *element;
    }
    throw NoAtlasSpaceException(size);
}

}
