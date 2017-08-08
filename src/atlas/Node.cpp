#include "Node.h"


Node::Node(const Rect& rect_):
    subTree { nullptr, nullptr, nullptr, nullptr },
    element { nullptr },
    rect { rect_ } {
    char msg[100];

    snprintf(msg, 100, "Creating atlas node (%d, %d, %d, %d)", rect.x, rect.y, rect.w, rect.h);
    INFO(msg);
}


int Node::ExpandTree(int depth) {
    Size subSize { rect.w / 2, rect.h / 2 };
    int subCount = 4;

    subTree[0] = std::make_unique<Node>(Rect{ rect.x, rect.y, subSize.x, subSize.y });
    subTree[1] = std::make_unique<Node>(Rect{ rect.x + subSize.x, rect.y, subSize.x, subSize.y });
    subTree[2] = std::make_unique<Node>(Rect{ rect.x, rect.y + subSize.y, subSize.x, subSize.y });
    subTree[3] = std::make_unique<Node>(Rect{ rect.x + subSize.x, rect.y + subSize.y, subSize.x, subSize.y });
    if (depth - 1 > 0) {
        for(int i = 0; i < 4; i++)
            subCount += subTree[i]->ExpandTree(depth - 1);
    }
    return subCount;
}

bool Node::HasElement() const {
    return element != nullptr;
}

bool Node::HasSubTree() const {
    return subTree[0] != nullptr;
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

void Node::DestroySubTree() {
    for (int i = 0; i < 4; i++) {
        subTree[i] = nullptr;
    }
}

AtlasElement& Node::AddElement(const Size& size, SDLSprite& atlasSprite) {

    if (!FitsInSubTree(size) || !HasSubTree()) {
        if (!HasElement() && FitsInMe(size) && IsSubTreeEmpty()) {
            element = std::make_unique<AtlasElement>(Rect{ rect.x, rect.y, size.x, size.y}, atlasSprite);
            DestroySubTree();
            char msg[200];
            snprintf(msg, 200, "New atlas element (%d, %d, %d, %d) in %d/%d", rect.x, rect.y, size.x, size.y, rect.w, rect.h);
            INFO(msg);
            return *element;
        }
    }
    else if (HasSubTree()) {
        for (int i = 0; i < 4; i++) {
            try {
                return subTree[i]->AddElement(size, atlasSprite);
            }
            catch (const SubTreeFullException& e) {
            }
        }
    }
    throw SubTreeFullException();
}
