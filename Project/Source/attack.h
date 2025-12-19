#pragma once
#include "../Library/gameObject.h"

#include "effect2D.h"
#include <vector>

class Attack :public GameObject {
public:
	Attack();
	~Attack();
	void Update()override;
	void Draw()override;

    Vector2 Bezier2(float t);
    Vector2 CreateControlPoint(float range);

    struct Particle
    {
        float x, y;
        float vx, vy;
        float life;
        float size;
    };

    void SpawnParticle(std::vector<Particle>& particles, float cx, float cy);
private:
    Vector2 m_start;
    Vector2 m_end;
    Vector2 m_control;
    Vector2 m_pos;

    // à⁄ìÆä«óù
    int  m_frame;
    bool m_isMoving;

    static const int MOVE_TIME = 30;

    std::vector<Particle> particles;

    Effect2D* effect;
};