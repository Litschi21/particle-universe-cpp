#include "main.h"

#include <SFML/Graphics.hpp>
#include <algorithm>
#include <cmath>
#include <random>
#include <vector>

Particle Particle::getRandParticle() {
  return Particle(largestID++, defaultSize, sf::Color::Cyan, randFloat(0.f, width_f),
                  randFloat(0.f, height_f), randInt(minStartingMass, maxStartingMass),
                  randFloat(minStartingSpeed, maxStartingSpeed),
                  randFloat(minStartingSpeed, maxStartingSpeed));
}

bool Particle::operator==(const Particle &p) const { return (p.id == this->id); }

float randFloat(const float min, const float max) {
  thread_local std::mt19937 rng{std::random_device{}()};
  std::uniform_real_distribution<float> dist{min, max};
  return dist(rng);
}

int randInt(const int min, const int max) {
  thread_local std::mt19937 rng{std::random_device{}()};
  std::uniform_int_distribution<int> dist{min, max};
  return dist(rng);
}

void removeParticle(const int id) {
  std::erase_if(particles, [id](Particle &p) { return id == p.id; });
}

bool scheduledForRemoval(const int id) {
  return std::find(toRemove.begin(), toRemove.end(), id) != toRemove.end();
}

void addRandParticle() { particles.emplace_back(Particle::getRandParticle()); }

int main() {
  sf::RenderWindow window(sf::VideoMode({width, height}), "Particle Universe");
  bool skip = false;

  for (int i{}; i < numParticles; ++i) {
    addRandParticle();
  }

  while (window.isOpen()) {
    while (const auto event = window.pollEvent()) {
      if (event->is<sf::Event::Closed>())
        window.close();
    }

    window.clear(sf::Color(15, 18, 28));

    while (particles.size() < numParticles)
      addRandParticle();
    for (auto &p : particles) {
      sf::CircleShape particle(p.size);
      particle.setFillColor(p.color);
      particle.setOrigin({p.size, p.size});
      particle.setPosition({p.x, p.y});
      window.draw(particle);

      if (p.size > maxSize) {
        for (auto &p2 : particles) {
          if (p2.id == p.id)
            continue;

          float dx = p2.x - p.x;
          float dy = p2.y - p.y;

          float distSquared = dx * dx + dy * dy;
          if (distSquared < 1.f)
            continue;

          float dist = std::sqrt(distSquared);
          float strength = explosionStrength / (distSquared + 100.f);

          p2.xVel += (dx / dist) * strength;
          p2.yVel += (dy / dist) * strength;
        }

        toRemove.emplace_back(p.id);
        continue;
      }

      if (scheduledForRemoval(p.id))
        continue;

      for (auto &p2 : particles) {
        if (p == p2 || scheduledForRemoval(p2.id) || p2.size > maxSize)
          continue;

        float dx = p2.x - p.x;
        float dy = p2.y - p.y;
        float distSquared = dx * dx + dy * dy;
        float radii = p.size + p2.size;
        if (distSquared < radii * radii) {
          merged.emplace_back(Particle(largestID++, p.size + p2.size, sf::Color::Cyan,
                                       (p.x * p.size + p2.x * p2.size) / (p.size + p2.size),
                                       (p.y * p.size + p2.y * p2.size) / (p.size + p2.size),
                                       p.mass + p2.mass,
                                       (p.xVel * p.size + p2.xVel * p2.size) / (p.size + p2.size),
                                       (p.yVel * p.size + p2.yVel * p2.size) / (p.size + p2.size)));

          toRemove.emplace_back(p.id);
          toRemove.emplace_back(p2.id);

          skip = true;
          break;
        }

        if (distSquared > 0.01f) {
          float force = p2.mass / distSquared;

          p.xVel += force * dx / std::sqrt(distSquared) * dt;
          p.yVel += force * dy / std::sqrt(distSquared) * dt;
        }
      }

      if (skip) {
        skip = false;
        continue;
      }

      p.x += p.xVel * dt;
      p.y += p.yVel * dt;

      if (p.x + p.size < 0 || p.x - p.size > width || p.y + p.size < 0 || p.y - p.size > height)
        toRemove.emplace_back(p.id);
    }

    for (auto &p : merged) {
      particles.emplace_back(p);
    }

    for (const int id : toRemove) {
      removeParticle(id);
    }

    merged = {};
    toRemove = {};
    window.display();
  }
}
