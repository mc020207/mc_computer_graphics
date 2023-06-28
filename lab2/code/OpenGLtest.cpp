#include <iostream>
#include "Windows.h"
#include "math.h"
#include <iostream>
#include <gl/glut.h>  
using namespace std;
void Init()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.5f);
    //打开深度缓存并激活
    glDepthFunc(GL_LEQUAL);
    glEnable(GL_DEPTH_TEST);
    //打开阴影
    glShadeModel(GL_SMOOTH);
}
void InitLight()
{
    GLfloat light_position0[] = { 1.0, 0.0, 0.0, 0.0 };
	GLfloat light_position1[] = { -1.0, 1.0, 1.0, 0.0 };
	GLfloat light_diffuse1[] = { 1.0, 0.7, 0.7, 1.0 };
	GLfloat light_specular1[] = { 1.0, 1.0, 1.0, 1.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, light_position0);
	glLightfv(GL_LIGHT1, GL_POSITION, light_position1);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse1);
	glLightfv(GL_LIGHT1, GL_SPECULAR, light_specular1);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
    /*
     *   准备了双光源，
     *   光源0放置在X轴正半轴，距离是无穷远，放出白光，镜面反射也为白光
     *   光源1放置在X轴负半轴Y、Z正半轴的平分线上，距离无穷远，放出偏红光，镜面反射为白光
     */
}
void InitMaterial()
{
    float mat_ambient[] = { 1.0, 1.0, 1.0, 1.0 };
    float mat_diffuse[] = { 1, 1, 0, 1.0 };
    float mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    float mat_shininess[] = { 50.0 };

    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
    /*
     *   设置环境光为白光
     *   设置实体颜色为黄色（漫反射光为黄色）
     *   设置实体颜色为白光（漫反射光为白光）
     *   控制高亮颜色为白色，并设置镜面反射指数为50
     */
}
//定义光源的初始化函数
void Reshape(int w, int h)
{
    // 当窗口更改大小的时候实时调整画面
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-w / 2, w / 2, -h / 2, h / 2, -300, 300);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
void renderScene(void)
{
	static float i = 0;
	i += 0.1;
	if (i > 360) i = 0;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
    gluLookAt(1, 1, 1, 0, 0, 0, 0, 1, 0);
    // 从X、Y、Z正半轴的平分线方向上观察
	glPushMatrix();
	glTranslatef(0, 0, 0);
	glRotatef(i, 0 , 1, 0);
    // 转动中心是Y轴，进行旋转
	glutSolidTeapot(200);
	glPopMatrix();
	glutSwapBuffers();
}


int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(800, 600);
    glutCreateWindow("马成 20307130112");
    Init();
    InitMaterial();
    InitLight();
    glutDisplayFunc(renderScene);
    glutIdleFunc(renderScene);
    glutReshapeFunc(Reshape);
    glutMainLoop();
    return 0;
}