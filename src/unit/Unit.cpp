#include "Unit.h"

namespace unnamed::unit {

Unit::Unit(map::Tile* initialTile, std::shared_ptr<atlas::Element>& sprite_):
    currTile { initialTile },
    position { currTile->GetPos() },
    speed { 10 },
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
        if (currDest->ReachedDestination()) {
            DEBUG(StringFormat("Unit @ (%d/%d) reached it's destination",
                position.x,
                position.y));
            currDest = nullptr;
        }
        else {
            Size<double> offset = currDest->GetMoveOffset(GetPos());
            INFO(StringFormat("MoveOffset: (%.2f/%.2f)", offset.x, offset.y));
            Move(offset);
            UpdateTile();
        }
    }
}

void Unit::UpdateTile() {
    if (!PointInRectangle(position, currTile->GetRect())) {
        currTile = currTile->GetNeighbourByPoint(position);
        if (currTile == nullptr)
            throw exception::GameException("Unit::UpdateTile", "New unit tile is not neighbour of old tile");
    }
}

void Unit::SetPos(const Point& newPos) {
    position = newPos;
}

void Unit::Move(const Size<double>& normalizedOffset) {
    position.x += static_cast<int>(normalizedOffset.x * speed);
    position.y += static_cast<int>(normalizedOffset.y * speed);
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
