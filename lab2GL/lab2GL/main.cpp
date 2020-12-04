#include<windows.h>
#include<GL/glu.h>
#include<GL/glut.h>
#include <cmath> 

// устанавливаем границы линий сканировани€
int LE[500], RE[500];

// эти переменные нужны дл€ того, чтобы
// сделать пользовательский выбор
int EdgeFlag = 0, FillFlag = 0;

// здесь мы ищем пересечени€ между двум€ точками
void Intersection(GLint x1, GLint y1, GLint x2, GLint y2)
{
    float x, M;
    int t;
    
    // засекаем пересечение
    if (y1 > y2)
    {
        // то мен€ем местами значени€ 
        // иксов
        t = x1;
        x1 = x2;
        x2 = t;

        // и игреков
        t = y1;
        y1 = y2;
        y2 = t;
    }
    // находим наклон линии,
    if ((y2 - y1) == 0)
        M = (x2 - x1);
    else
        M = (x2 - x1) / (y2 - y1);

    // засекаем точку на оси x,
    // чтобы скорректировать строки сканировани€
    // дл€ нашего полигона
    x = x1;
    for (int y = y1; y <= y2; y++)
    {
        // корректируем строки
        if (x < LE[y])
            LE[y] = x; // это границы линий сканировани€; их получаетс€ 500 и мы дл€ каждой линии корректируем
        if (x > RE[y])
            RE[y] = x;

        x = x + M;
    }
}

// устанавливаем точки, соедин€ем эти точки, дл€ того,
// чтобы были видны ребра нашего многоугольника
void Draw()
{
    int x, y, i;
    // кажда€ из точек имеет значение по координате x и y соответственно: 
    // здесь мы устанавливаем координаты вершин, да
    GLint P1[2] = { 125,250 }, P2[2] = { 250,125 }, P3[2] = { 375,250 }, P4[2] = { 250,375 };

    glClear(GL_COLOR_BUFFER_BIT);

    // здесь просто устанавливаем начальные значени€ линий сканировани€ , от 0 до 500 пикселов.
    for (i = 0; i < 500; i++)
    {
        LE[i] = 500;
        RE[i] = 0;
    }
    // если в UI, мы выбрали "With Edges", то точки соедин€тс€
    if (EdgeFlag == 1)
    {
        glBegin(GL_LINE_LOOP);
        glVertex2iv(P1);
        glVertex2iv(P2);
        glVertex2iv(P3);
        glVertex2iv(P4);
        glEnd();
    }

    // здесь находим пересечениие линий полигона
    // от самой левой вершины, к верхней, потом к противоположной правой и к нижней вершине
    Intersection(P1[0], P1[1], P2[0], P2[1]);
    Intersection(P2[0], P2[1], P3[0], P3[1]);
    Intersection(P3[0], P3[1], P4[0], P4[1]);
    Intersection(P4[0], P4[1], P1[0], P1[1]);

    // ну и закрашиваем необходимую нам область.
    if (FillFlag == 1)
    {
        for (y = 0; y < 500; y++)
        {
            // учитыва€ границы сканировани€, уже изменЄнные
            for (x = LE[y]; x < RE[y]; x++)
            {
                glBegin(GL_POINTS);
                glVertex2i(x, y);
                glEnd();
                glFlush();
            }
        }
    }

    glFlush();

    // зачтите пожалууйста )))
    // —ѕј—»Ѕќ :)
}
// UI
void Menu(int id)
{
    // имеют ќ„≈Ќ№ простой функционал
    // просто дл€ красоты сделал
    if (id == 1)
        EdgeFlag = 1;
    else if (id == 2)
        EdgeFlag = 0;
    else if (id == 3)
        exit(0);

    FillFlag = 1;
    glutPostRedisplay();
}

void MyInit()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 500, 0, 500);
    glMatrixMode(GL_MODELVIEW);

    glutCreateMenu(Menu);
    // ну вот в общем
    glutAddMenuEntry("With Edge", 1);
    glutAddMenuEntry("Without Edge", 2);
    glutAddMenuEntry("Exit", 3);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

int main(int argC, char* argV[])
{
    glutInit(&argC, argV);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutCreateWindow("Polygon Fill by Chernov Pavel");
    MyInit();
    glutDisplayFunc(Draw);
    glutMainLoop();
    return 0;
}
