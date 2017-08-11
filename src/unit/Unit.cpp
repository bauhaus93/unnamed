#include "Unit.h"

namespace unnamed::unit {

Unit::Unit(map::Tile* initialTile, std::shared_ptr<atlas::Element>& sprite_):
    currTile { initialTile },
    position { currTile->GetPos() },
    sprite { sprite_ },
    currDest { nullptr } {

}

bool Unit::HasDestination() const {
    return currDest != nullptr;
}

void Unit::SetDestination(std::unique_ptr<map::Path> path) {
    DEBUG(StringFormat("Unit @ (%d/%d) has new destination: (%d/%d)"));
    currDest = std::move(path);
}

void Unit::WalkDestination() {
    if (currDest != nullptr ) {
        map::Tile* nextTile = currDest->GetNextTile();
        if (nextTile != nullptr) {
            currTile = nextTile;
            SetPos(currTile->GetPos());
        }
        else {
            DEBUG(StringFormat("Unit @ (%d/%d) reached it's desitnation",
                position.x,
                position.y));
            currDest = nullptr;
        }
    }
}

void Unit::SetPos(const Point& newPos) {
    position = newPos;
}

map::Tile* Unit::GetTile() const {
    return currTile;
}

Point Unit::GetPos() const {
    return position;
}

void Unit::Draw(const Point& camera, const Point& offset) {
    sprite->Draw(Point{ offset.x + position.x - camera.x, offset.y + position.y - camera.y });
}

}
