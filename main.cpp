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

      //Draw
      //Real code starts here
      //
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      glLoadIdentity();

      gluLookAt(camera.x, camera.y, camera.z, //Camera position in World Space
                camera.x, camera.y, 0.0,      //Camera looks towards this position
                0.0, 1.0, 0.0);               //Up

      glColor3f(1.0f, 0.0f, 0.0f);      // Set the color to red

      glRotatef(t*5, 0.0f, 0.0f, 1.0f);
      
      glBegin(GL_QUADS);
      // Drawing a face facing the camera
      // Start at bottom left corner, moving clockwise
      // Anchor at bottom middle
      glVertex3f(-1.0f, 0.0f, 0.0f);
      glVertex3f(-1.0f, 1.0f, 0.0f);
      glVertex3f(1.0f, 1.0f, 0.0f);
      glVertex3f(1.0f, 0.0f, 0.0f);

      
      glEnd();

      //Swap buffer (show result)
      window.display();
    }
  }
};

	int main() {
  SFMLApplication sfml_application;
  sfml_application.start();

  return 0;
}
