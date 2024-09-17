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
#include <tuple>

#include <GL/gl.h>
#include <tuple>

class RubiksPart
{
public:
    GLfloat cubeLength;
    std::tuple<GLfloat, GLfloat, GLfloat> globalCubeCenterPos;
    std::tuple<GLfloat, GLfloat, GLfloat> orientationVec; // Default is (0, 1, 0)
    std::tuple<GLfloat, GLfloat, GLfloat> bottomColor;
    std::tuple<GLfloat, GLfloat, GLfloat> topColor;
    std::tuple<GLfloat, GLfloat, GLfloat> frontColor;
    std::tuple<GLfloat, GLfloat, GLfloat> rightColor;
    std::tuple<GLfloat, GLfloat, GLfloat> leftColor;
    std::tuple<GLfloat, GLfloat, GLfloat> backColor;

    RubiksPart(GLfloat l,
               std::tuple<GLfloat, GLfloat, GLfloat> pos,
               std::tuple<GLfloat, GLfloat, GLfloat> orientation,
               std::tuple<GLfloat, GLfloat, GLfloat> bottomC,
               std::tuple<GLfloat, GLfloat, GLfloat> topC,
               std::tuple<GLfloat, GLfloat, GLfloat> frontC,
               std::tuple<GLfloat, GLfloat, GLfloat> rightC,
               std::tuple<GLfloat, GLfloat, GLfloat> leftC,
               std::tuple<GLfloat, GLfloat, GLfloat> backC)
        : cubeLength(l),
          globalCubeCenterPos(pos),
          orientationVec(orientation),
          bottomColor(bottomC),
          topColor(topC),
          frontColor(frontC),
          rightColor(rightC),
          leftColor(leftC),
          backColor(backC)
    {
    }

    void drawCube()
    {
        // Extract cube position
        GLfloat posX = std::get<0>(globalCubeCenterPos);
        GLfloat posY = std::get<1>(globalCubeCenterPos);
        GLfloat posZ = std::get<2>(globalCubeCenterPos);

        // Extract cube orientation (orientationVec)
        GLfloat orientX = std::get<0>(orientationVec);
        GLfloat orientY = std::get<1>(orientationVec);
        GLfloat orientZ = std::get<2>(orientationVec);

        // Push the current matrix stack
        //glPushMatrix();

        // Translate to the global position of the cube
        glTranslatef(posX, posY, posZ);

        // Compute the angle and axis for orientation
        // Assuming the default orientation is along (0, 1, 0), the Y-axis
        GLfloat defaultVec[] = {0.0f, 1.0f, 0.0f};  // Upward by default

        // Now calculate the angle and axis for rotation (if needed)
        // You can use cross product and dot product for this

        // Rotate cube based on orientationVec (simplified case; you'll need to compute a rotation matrix)
        // This assumes the orientationVec is a unit vector and glRotatef works well with it
        glRotatef(45.0f, orientX, orientY, orientZ); // Use the calculated angle and axis

        // Draw the cube's 6 faces
        GLfloat halfLength = cubeLength / 2.0f;

        // Top face (y = halfLength)
        glBegin(GL_QUADS);
        glColor3f(std::get<0>(topColor), std::get<1>(topColor), std::get<2>(topColor));
        glVertex3f(-halfLength, halfLength, -halfLength);
        glVertex3f(halfLength, halfLength, -halfLength);
        glVertex3f(halfLength, halfLength, halfLength);
        glVertex3f(-halfLength, halfLength, halfLength);
        glEnd();

        // Bottom face (y = -halfLength)
        glBegin(GL_QUADS);
        glColor3f(std::get<0>(bottomColor), std::get<1>(bottomColor), std::get<2>(bottomColor));
        glVertex3f(-halfLength, -halfLength, halfLength);
        glVertex3f(halfLength, -halfLength, halfLength);
        glVertex3f(halfLength, -halfLength, -halfLength);
        glVertex3f(-halfLength, -halfLength, -halfLength);
        glEnd();

        // Front face (z = halfLength)
        glBegin(GL_QUADS);
        glColor3f(std::get<0>(frontColor), std::get<1>(frontColor), std::get<2>(frontColor));
        glVertex3f(-halfLength, -halfLength, halfLength);
        glVertex3f(halfLength, -halfLength, halfLength);
        glVertex3f(halfLength, halfLength, halfLength);
        glVertex3f(-halfLength, halfLength, halfLength);
        glEnd();

        // Back face (z = -halfLength)
        glBegin(GL_QUADS);
        glColor3f(std::get<0>(backColor), std::get<1>(backColor), std::get<2>(backColor));
        glVertex3f(-halfLength, halfLength, -halfLength);
        glVertex3f(halfLength, halfLength, -halfLength);
        glVertex3f(halfLength, -halfLength, -halfLength);
        glVertex3f(-halfLength, -halfLength, -halfLength);
        glEnd();

        // Left face (x = -halfLength)
        glBegin(GL_QUADS);
        glColor3f(std::get<0>(leftColor), std::get<1>(leftColor), std::get<2>(leftColor));
        glVertex3f(-halfLength, -halfLength, -halfLength);
        glVertex3f(-halfLength, -halfLength, halfLength);
        glVertex3f(-halfLength, halfLength, halfLength);
        glVertex3f(-halfLength, halfLength, -halfLength);
        glEnd();

        // Right face (x = halfLength)
        glBegin(GL_QUADS);
        glColor3f(std::get<0>(rightColor), std::get<1>(rightColor), std::get<2>(rightColor));
        glVertex3f(halfLength, -halfLength, halfLength);
        glVertex3f(halfLength, -halfLength, -halfLength);
        glVertex3f(halfLength, halfLength, -halfLength);
        glVertex3f(halfLength, halfLength, halfLength);
        glEnd();

        // Pop the current matrix stack
        //glPopMatrix();
    }
};

