#include <iostream>
#include <vector>
#include <map>
#include <memory>

#include "raylib.h"
#include "Platform.h"
#include "Obstacle.h"

class Character {
public:
    Character(std::filesystem::path path1, std::filesystem::path path2, std::filesystem::path path3,
              float speed, float x, float y, int currentFrame = 0, int framesCounter = 0,
              int framesSpeed = 8, int currentLine = 0, bool is_jumping = false);

    ~Character();

    bool update(bool input_jump, bool input_dash);

    void draw();

    void run();

    void die();

    void changeSpeed(float speed);

    bool isDead() const { return m_is_dead; }

    float getX() const { return m_position.x; }
    float getY() const { return m_position.y; }
    float getWidth() const { return m_frame_rec.width; }
    float getHeight() const { return m_frame_rec.height; }

    void setPosition(float x, float y) {
        m_position.x = x;
        m_position.y = y;
    }

    Rectangle getBounds() const;

    bool checkPlatformCollisions(const std::vector<std::unique_ptr<Platform> > &platforms,
                                 std::map<Platform *, std::unique_ptr<Obstacle> > &obstacles);

private:
    // Assets
    std::filesystem::path m_path_character;
    std::filesystem::path m_path_explosion;
    std::filesystem::path m_path_sound;
    Texture2D m_character;
    Texture2D m_explosion;
    Sound m_boom;

    // Character state
    Vector2 m_position;
    Rectangle m_frame_rec;
    int m_currentFrame;
    int m_framesCounter;
    int m_framesSpeed;
    int m_currentLine;
    bool m_is_dead = false;
    Vector2 m_death_position;

    // Physics & movement
    float m_vertical_velocity = 0.0f;
    float m_gravity = config::BASE_GRAVITY;
    float m_jump_force = config::BASE_JUMP_FORCE;
    float m_max_jump_height = 300.0f;
    bool m_is_jumping;
    bool m_prev_jump = false;
    int m_jumps_left;
    bool m_is_on_ground = false;

    // Dash mechanics
    bool m_is_dashing = false;
    float m_dash_duration = 0.0f;
    float m_dash_max_duration = 0.3f;
    float m_dash_cooldown = 0.0f;
    float m_dash_max_cooldown = 1.0f;
    float m_dash_distance = 30.0f;
    float m_dash_offset = 0.0f;
    float m_dash_return_speed = 60.0f;

    // Collision detection
    Image m_character_image;
    Color *m_pixel_data = nullptr;

    // Private methods
    void resetJump();

    bool checkCollisions(const Platform *platform, const Obstacle *obstacle);

    float GetCollisionDepth(Rectangle rec1, Rectangle rec2);

    bool checkPixelCollision(const Rectangle &bounds1, const Color *pixels1, int width1, int height1,
                             const Rectangle &bounds2, const Color *pixels2, int width2, int height2);
};
