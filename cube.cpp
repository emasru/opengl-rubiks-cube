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

    // Applied when rotation is needed
    glm::vec3 anchorPoint;
    float angle;

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
        anchorPoint = glm::vec3(0.0f, 0.0f, 0.0f);
        angle = 0.0f;
    }

    RubiksPart(){}

    void rotateAround(glm::vec3 anchorPos, float a)
    {
        anchorPoint = anchorPos;
        angle = a;
    }

    void drawCube()
    {
        // Extract cube position
        GLfloat posX = std::get<0>(globalCubeCenterPos);
        GLfloat posY = std::get<1>(globalCubeCenterPos);
        GLfloat posZ = std::get<2>(globalCubeCenterPos);

        // Push the current matrix stack
        glPushMatrix();


        // Translate the cube so that the anchor point is at the origin
        glTranslatef(-anchorPoint.x, -anchorPoint.y, -anchorPoint.z);

        // Apply rotation around the origin (anchor point)
        glRotatef(angle, 1.0f, 0.0f, 0.0f);

        // Translate the cube back to its original position
        glTranslatef(anchorPoint.x, anchorPoint.y, anchorPoint.z);

        // Translate to the global position of the cube
        glTranslatef(posX, posY, posZ);

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

        // Back face (z = halfLength)
        glBegin(GL_QUADS);
        glColor3f(std::get<0>(backColor), std::get<1>(backColor), std::get<2>(backColor));
        glVertex3f(-halfLength, -halfLength, halfLength);
        glVertex3f(halfLength, -halfLength, halfLength);
        glVertex3f(halfLength, halfLength, halfLength);
        glVertex3f(-halfLength, halfLength, halfLength);
        glEnd();

        // Front face (z = -halfLength)
        glBegin(GL_QUADS);
        glColor3f(std::get<0>(frontColor), std::get<1>(frontColor), std::get<2>(frontColor));
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
        glPopMatrix();
    }
};


class RubiksCube
{
    public:
        RubiksPart rubiksCube[3][3][3];

        RubiksCube()
        {
            initializeCube();
        }

        void initializeCube()
        {
          std::tuple<GLfloat, GLfloat, GLfloat> rubiksWhite(1.0f, 1.0f, 1.0f);
          std::tuple<GLfloat, GLfloat, GLfloat> rubiksYellow(1.0f, 0.835f, 0.0f);
          std::tuple<GLfloat, GLfloat, GLfloat> rubiksRed(0.714f, 0.071f, 0.106f);
          std::tuple<GLfloat, GLfloat, GLfloat> rubiksBlue(0.0f, 0.275f, 0.678f);
          std::tuple<GLfloat, GLfloat, GLfloat> rubiksOrange(0.765f, 0.345f, 0.0f);
          std::tuple<GLfloat, GLfloat, GLfloat> rubiksGreen(0.0f, 0.608f, 0.282f);
          std::tuple<GLfloat, GLfloat, GLfloat> rubiksBlack(0.0f, 0.0f, 0.0f);


          // Indexing: bottom left front is the origin
          for (int x = 0; x < 3; x++)
          {
            for (int y = 0; y < 3; y++)
            {
              for (int z = 0; z < 3; z++)
              {
                std::tuple<GLfloat, GLfloat, GLfloat> bottomColor = rubiksBlack;
                std::tuple<GLfloat, GLfloat, GLfloat> topColor = rubiksBlack;
                std::tuple<GLfloat, GLfloat, GLfloat> frontColor = rubiksBlack;
                std::tuple<GLfloat, GLfloat, GLfloat> backColor = rubiksBlack;
                std::tuple<GLfloat, GLfloat, GLfloat> leftColor = rubiksBlack;
                std::tuple<GLfloat, GLfloat, GLfloat> rightColor = rubiksBlack;

                if (y == 0)
                {
                    bottomColor = rubiksWhite;
                }
                else if (y == 2)
                {
                    topColor = rubiksYellow;
                }

                if (x == 0)
                {
                    leftColor = rubiksOrange;
                }
                else if (x == 2)
                {
                    rightColor = rubiksRed;
                }

                if (z == 0)
                {
                    frontColor = rubiksGreen;
                }
                else if (z == 2)
                {
                    backColor = rubiksBlue;
                }

                GLfloat length = 0.5;
                std::tuple<GLfloat, GLfloat, GLfloat> orientation(0.0f, 1.0f, 0.0f);
                std::tuple<GLfloat, GLfloat, GLfloat> position(0.0f+(x * length), 0.0f+(y * length), 0.0f+(z * length));
                RubiksPart part(length, position, orientation, bottomColor, topColor, frontColor, rightColor, leftColor, backColor);
                rubiksCube[x][y][z] = part;
              }
            }
          }
        }

        void rotateLeftFace(float t)
        {
            glm::vec3 centerOfRotation(0.0f, -0.5f, -0.5f);
            //glm::vec3 centerOfRotation(0.0f, 0.0f, 0.0f);
            // Select with x = 0 gives all cubes on the left face
            for (int x = 0; x < 3; x++)
            {
                for (int y = 0; y < 3; y++)
                {
                    for (int z = 0; z < 3; z++)
                    {
                        if (x == 0)
                        {
                            rubiksCube[x][y][z].rotateAround(centerOfRotation, t*16);
                        }
                    }
                }
            }
        }

        void drawCube(float t)
        {
            rotateLeftFace(t);

            for (int x = 0; x < 3; x++)
            {
                for (int y = 0; y < 3; y++)
                {
                    for (int z = 0; z < 3; z++)
                    {
                        rubiksCube[x][y][z].drawCube();
                    }
                }
            }
        }


};
