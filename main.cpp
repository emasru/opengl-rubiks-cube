#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/System.hpp>

#ifdef __APPLE__
#include <OpenGL/glu.h>
#else
#include <GL/glu.h>
#include <GL/glut.h>
#endif

#include <glm/glm.hpp>

#include <stdio.h>
#include <string.h>

#include "cube.cpp"
#include <tuple>
#include <cmath>


class SFMLApplication {
  sf::ContextSettings context_settings;
  sf::Window window;

public:
  SFMLApplication() : context_settings(24),
                      window(sf::VideoMode(1920/2, 1080), "SFML Example", sf::Style::Default, context_settings) {
    window.setFramerateLimit(144);
    window.setVerticalSyncEnabled(true);

    //Various settings
    glClearColor(0.5, 0.5, 0.5, 0.0);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    //Setup projection matrix
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
    gluPerspective(45.0, 4.0 / 3.0, 0.1, 100.0);

    glMatrixMode(GL_MODELVIEW);
  }


  void start() {
    glm::vec3 camera(0.0, 0.0, 6.0);

    char *myargv[1];
    int myargc = 1;
    myargv[0] = strdup("fakeappname");
    glutInit(&myargc, myargv);

    RubiksCube rubiksCube;

    bool running = true;
    while (running) {
      //Handle events
      sf::Event event;
      while (window.pollEvent(event)) {
        if (event.type == sf::Event::KeyPressed) {
          if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            window.close();
            running = false;
          }
        }
        else if (event.type == sf::Event::Closed) {
          window.close();
          running = false;
        }
      }

      float t = glutGet(GLUT_ELAPSED_TIME) / 1000.0f;
      float angle = 0;
      angle += t/4;
      if (angle > 2 * M_PI) {
        angle -= 2 * M_PI; // Ensure angle stays within [0, 2*PI]
      }
      float radius = 6;

      //Draw
      //Real code starts here
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      glLoadIdentity();

      gluLookAt(radius * cos(angle), camera.y+3, radius * sin(angle), //Camera position in World Space
                camera.x, camera.y, 0.0,      //Camera looks towards this position
                0.0, 1.0, 0.0);               //Up

      rubiksCube.drawCube(t);

      window.display();
    }
  }
};

	int main() {
  SFMLApplication sfml_application;
  sfml_application.start();

  return 0;
}
