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

void Unit::SetDestination(map::Tile* destTile) {
    currDest = map::FindPath(GetTile(), destTile, speed);
    //TODO feedback if not reachable
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
            Move(offset);
            UpdateTile();
        }
    }
}

void Unit::UpdateTile() {
    if (!PointInRectangle(position, currTile->GetRect())) {
        map::Tile* newTile = currTile->GetNeighbourByPoint(position);
        if (newTile == nullptr) {
            ERROR(StringFormat("Could not retrieve new tile of unit by neighbour of current tile: unit pos: (%d, %d), old tile pos: (%d, %d)",
                GetPos().x,
                GetPos().y,
                currTile->GetPos().x,
                currTile->GetPos().y));
            currDest = nullptr;
        }
        else {
            currTile = newTile;
        }
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
    sprite->Draw(Point{ offset.x + position.x - TILE_SIZE / 2 - camera.x, offset.y + position.y - TILE_SIZE / 2 - camera.y });
}

}
