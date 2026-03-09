#pragma once
#include "Projectile.hpp"
#include "Math.hpp"
#include "ImageManager.hpp"
#include "Animation.hpp"
#include <iostream>

class Program;

class Enemy {
    protected:
        float angle = 90;
        int cooldown = 60;
        int speed = 3;
        bool spawning = false;
        bool frame = false;
        int frameCooldown = 30;
        
    public:
        int health = 1;
        std::pair<float, float> position;
        HitBox hitBox;
        int score;

        inline static float direction = 0.5;
        inline static int directionChange = 100;
        inline static std::vector<std::pair<std::pair<float, float>, Enemy*>> enemies;

        Enemy() {}

        Enemy(float x, float y) {
            position.first = x;
            position.second = y;
            hitBox = HitBox(x, y, 30, 30);
        }

        virtual void draw() = 0;
        virtual void update(std::pair<float, float> pos, HitBox target) = 0;
        virtual void attack(HitBox target) = 0;

        void frameChange() {
            frameCooldown--;

             if (frameCooldown <= 0) {
                frame = !frame;
                frameCooldown = 30;
             }
        }

       static void ManageEnemies(HitBox target, Program* program);
};
