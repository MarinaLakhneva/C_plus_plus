#include "Collider.h"

namespace NArkanoid {

    float TBoxCollider::x() {
        return rect.getPosition().x;
    }

    float TBoxCollider::y() {
        return rect.getPosition().y;
    }

    float TBoxCollider::Left() {
        return x();
    }

    float TBoxCollider::Right() {
        return x() + rect.getSize().x;
    }

    float TBoxCollider::Top() {
        return y();
    }

    float TBoxCollider::Bottom() {
        return y() + rect.getSize().y;
    }

    float TCircleCollider::x() {
        return circle.getPosition().x;
    }

    float TCircleCollider::y() {
        return circle.getPosition().y;
    }

    float TCircleCollider::Left() {
        return x();
    }

    float TCircleCollider::Right() {
        return x() + 2.f * circle.getRadius();
    }

    float TCircleCollider::Top() {
        return y();
    }

    float TCircleCollider::Bottom() {
        return y() + 2.f * circle.getRadius();
    }
}

int NArkanoid::Collide(ICollider* a, ICollider* b) {
    bool intersect = (
        (b->Left() < a->Right()) && (a->Left() < b->Right()) &&
        (b->Top() < a->Bottom()) && (a->Top() < b->Bottom())
    );
    
    if (!intersect) {
        return 0;
    }
    float overlapLeft = std::abs(b->Right() - a->Left());
    float overlapRight = std::abs(a->Right() - b->Left());
    float overlapTop = std::abs(a->Bottom() - b->Top());
    float overlapBottom = std::abs(b->Bottom() - a->Top());

    float minOverlapX = std::min(overlapLeft, overlapRight);
    float minOverlapY = std::min(overlapTop, overlapBottom);

    if (minOverlapX < minOverlapY) {
        return 1;
    }
    return -1;
}