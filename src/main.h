#ifndef MAIN_H
#define MAIN_H

#include <SFML/Graphics.hpp>
#include <vector>

class Particle {
public:
  int id;
  float size;
  sf::Color color;
  float x;
  float y;

  int mass;
  float xVel = 0.f;
  float yVel = 0.f;

  static Particle getRandParticle();
  bool operator==(const Particle &p) const;
};

constexpr int width = 2560;
constexpr int height = 1440;
constexpr float width_f = static_cast<float>(width);
constexpr float height_f = static_cast<float>(height);

inline int largestID = 0;
constexpr int fps = 60;
constexpr float timescale = 13;
constexpr float dt = timescale / fps;
constexpr int maxSize = 200;
constexpr int numParticles = 100;
constexpr int minStartingMass = 10;
constexpr int maxStartingMass = 1'000;
constexpr float maxStartingSpeed = 2;
constexpr float minStartingSpeed = -2;
constexpr float explosionStrength = 5'000'000;

inline std::vector<Particle> particles{};
inline std::vector<Particle> merged{};
inline std::vector<int> toRemove{};

float randFloat(float min, float max);
int randInt(int min, int max);
void removeParticle(int id);
bool scheduledForRemoval(int id);
void addRandParticle();

#endif // MAIN_H
