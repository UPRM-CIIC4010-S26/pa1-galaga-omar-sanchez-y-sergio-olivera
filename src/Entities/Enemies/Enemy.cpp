#pragma once
#include "Enemy.hpp"
#include "Program.hpp"
#include "Projectile.hpp"
#include "Math.hpp"
#include "ImageManager.hpp"
#include "Animation.hpp"
#include <iostream>

void Enemy::ManageEnemies(HitBox target, Program* program) {
    for (std::pair<std::pair<float, float>, Enemy*>& p : Enemy::enemies) {
        p.first.first += (p.first.first == 0) ? 0 : Enemy::direction;
        if (p.second) {
            p.second->update(p.first, target);

            for (Projectile& p2 : Projectile::projectiles) {
                if (p2.ID != 1 && HitBox::Collision(p.second->hitBox, p2.getHitBox())) {
                    p.second->health--;
                    p2.del = true;
                }
            }

            if (p.second->health <= 0) {
                Animation::animations.push_back(
                    Animation(p.second->position.first, p.second->position.second, 155, 0, 33, 33, 30, 30, 4, ImageManager::SpriteSheet)
                );
                program->AddScore(p.second->score);
                p.second = nullptr;
            }
        }
    }

    for (int i = 0; i < Enemy::enemies.size(); i++) {
        if ((Enemy::enemies[i].second && Enemy::enemies[i].second->position.first <= -30) ||
            (!Enemy::enemies[i].second && Enemy::enemies[i].first.first == 0 && Enemy::enemies[i].first.second == 0)) {
            Enemy::enemies.erase(Enemy::enemies.begin() + i);
            i--; // optional: adjust index after erase
        }
    }

    Enemy::directionChange++;

    if (Enemy::directionChange >= 200) {
        Enemy::directionChange = 0;
        Enemy::direction *= -1;
    }
}