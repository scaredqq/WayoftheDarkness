#pragma once

constexpr int number_of_snowflakes = 20;
constexpr float single_frame = 1.F / 60;
constexpr float default_radius = 10.F;


float ease_in_and_out(float normalised_time)
{
    float t = normalised_time;
    return t < 0.5 ? 2 * t * t : 2 * t * (2 - t) - 1;
}

//we take unsigned and return float in order to work with SFML's window size which is unsigned
float generate_random(unsigned min, unsigned max)
{
    float real_min = static_cast<float>(min);
    float real_max = static_cast<float>(max);
    static std::random_device rd;
    static std::mt19937 generator(rd());
    std::uniform_real_distribution<float> distribution(real_min, real_max);
    return distribution(generator);
}

class Snowflake
{
public:
    explicit Snowflake(sf::Vector2f start_position) : position{ start_position }
    {
        snowflake.setPosition(position);
        begin = start_position.x;
    }

    void fall(sf::Vector2u window_size)
    {
        time += single_frame;
        if (time > duration)
        {
            begin += change;
            change = generate_random(1, 10);
            time = 0.F;
        }

        position.y = snowflake.getPosition().y;
        position.y += 1 / duration;
        if (position.y > window_size.y)
        {
            position.y = -10.F;
            begin = generate_random(0, window_size.x);
            change = generate_random(1, 10);
            time = 0;
            snowflake.setRadius(default_radius / duration);
        }

        position.x = shift_x();
        snowflake.setPosition(position);
    }
    void draw(sf::RenderWindow& window) { window.draw(snowflake); }
private:
    sf::Vector2f position;
    float begin;
    float change{ generate_random(1, 10) };
    float duration{ generate_random(1, 5) };
    float time{ 0 };
    sf::CircleShape snowflake{ default_radius / duration };

    float shift_x() const
    {
        return begin + change * ease_in_and_out(time / duration);
    }
};

