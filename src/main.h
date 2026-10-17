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
  float acc = 0.f;

  static Particle getRandParticle();
  bool operator==(const Particle &p) const;
};

constexpr int width = 2560;
constexpr int height = 1440;
constexpr float width_f = static_cast<float>(width);
constexpr float height_f = static_cast<float>(height);

const double G = 6.6743 * std::pow(10, -11);
constexpr float dt = 0.016;
constexpr int numParticles = 100;

int largestID = 0;
bool skip = false;

std::vector<Particle> particles{};
std::vector<Particle> merged{};
std::vector<int> toRemove{};

float randFloat(float min, float max);
int randInt(int min, int max);
void removeParticle();
bool scheduledForRemoval(int id);
void addRandParticle();

#endif // MAIN_H
