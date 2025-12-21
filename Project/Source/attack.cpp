#include "attack.h"

#include "boss.h"
#include "sound.h"

Attack::Attack()
{
    m_start = { 410, 400 };
    m_end = { 1180, 300 };

    m_pos = m_start;
    m_frame = 0;
    m_isMoving = false;

    effect = new Effect2D();
}

Attack::~Attack()
{
    delete effect;


}

void Attack::Update()
{
    static int prevAKey = 0;
    int nowAKey = CheckHitKey(KEY_INPUT_A);

    // Aキー押下で初期化＆開始
    if (nowAKey && !prevAKey)
    {
        m_frame = 0;
        m_isMoving = true;
        m_control = CreateControlPoint(300);
        FindGameObject<Sound>()->SetPlaySound(Sound::SOUND::ATTACK, 9000);
    }
    prevAKey = nowAKey;

    // 移動処理
    if (m_isMoving)
    {
        for (int i = 0; i < 4; i++)
        {
            SpawnParticle(particles, m_pos.x, m_pos.y);
        }

        float t = m_frame / (float)MOVE_TIME;
        if (t >= 1.0f)
        {
            t = 1.0f;
            m_isMoving = false;
            FindGameObject<Boss>()->Damage(2, 0.15f);

            effect->SetEffect(Effect2D::TYPE::TYPE_01, m_pos, 50);
            FindGameObject<Sound>()->SetPlaySound(Sound::SOUND::ATTACKPLASMA, 9000);
            
            FindGameObject<Sound>()->SetPlaySound(Sound::SOUND::ATTACKHIT_01, 9000);
            FindGameObject<Sound>()->SetPlaySound(Sound::SOUND::ATTACKHIT_02, 9000);
        }

        // イージング（任意）
        float easeT = t * t * (3 - 2 * t);

        m_pos = Bezier2(easeT);
        m_frame++;

        if (!m_isMoving)
            m_pos = m_start;
    }

    for (auto& p : particles)
    {
        p.x += p.vx;
        p.y += p.vy;
        p.life -= 1.0f;
        p.size *= 0.96f;
    }

    // 寿命切れ削除
    particles.erase(
        std::remove_if(particles.begin(), particles.end(),
            [](const Particle& p) { return p.life <= 0; }),
        particles.end());
}

void Attack::Draw()
{

    DrawCircle((int)m_pos.x, (int)m_pos.y, 10, GetColor(255, 0, 0), TRUE);


    SetDrawBlendMode(DX_BLENDMODE_ADD, 255);

    for (const auto& p : particles)
    {
        int alpha = (int)(p.life * 4);
        DrawCircleAA(
            p.x,
            p.y,
            p.size,
            16,
            GetColor(255, 255, 220),
            alpha);
    }

    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

    //effect->Draw();
}

Vector2 Attack::Bezier2(float t)
{
    float u = 1.0f - t;

    Vector2 p;
    p.x = u * u * m_start.x + 2 * u * t * m_control.x + t * t * m_end.x;
    p.y = u * u * m_start.y + 2 * u * t * m_control.y + t * t * m_end.y;
    return p;
}

Vector2 Attack::CreateControlPoint(float range)
{
    Vector2 mid = { (m_start.x + m_end.x) * 0.5f,
                 (m_start.y + m_end.y) * 0.5f };

    float dx = m_end.x - m_start.x;
    float dy = m_end.y - m_start.y;
    float len = sqrtf(dx * dx + dy * dy);
    dx /= len;
    dy /= len;

    float px = -dy;
    float py = dx;

    float offset = (float)(GetRand((int)range * 2) - range);

    Vector2 c;
    c.x = mid.x + px * offset;
    c.y = mid.y + py * offset;
    return c;
}

void Attack::SpawnParticle(std::vector<Particle>& particles, float cx, float cy)
{
    Particle p;

    float angle = GetRand(360) * DX_PI_F / 180.0f;
    float speed = GetRand(30) / 10.0f + 1.0f;

    p.x = cx;
    p.y = cy;
    p.vx = cosf(angle) * speed;
    p.vy = sinf(angle) * speed;
    p.life = 60.0f;
    p.size = GetRand(6) + 6;

    particles.push_back(p);
}
