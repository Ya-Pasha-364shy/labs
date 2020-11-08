#include <GL/glut.h>

void myDisplay(void);
void paintLine(void(*func)(int, int, int, int), int x1, int y1, int x2, int y2);

void drawBresenhamLine(int x1, int y1, int x2, int y2);
void drawDDALine(int x1, int y1, int x2, int y2);

// настраеваем окно вывода
int main(int argc, char** argv)
{
	// инициализируем окно
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	// устанавливаем размеры
	glutInitWindowSize(600, 400);
	// делаем вывод относительно
	// левого верхнего угла экрана
	glutInitWindowPosition(650, 50);
	glutCreateWindow("Lab1_Chernov");
	// цвет экрана
	glClearColor(1.0, 0.8, 0.8, .0);
	// устанавливаем единичную матрицу
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	// устанавливаем ортоганальную проекцию 
	// для изображений
	gluOrtho2D(0, 359, 0, 399);
	// запускаем алгоритмы здесь
	glutDisplayFunc(myDisplay);
	glutMainLoop();
}

void myDisplay()
{

	glClear(GL_COLOR_BUFFER_BIT);

	glBegin(GL_POINTS);
	// устанавливаем чёрный цвет
	glColor3f(0.0f, 0.0f, 0.0f);
	// запуск алгоритма Брезенхема
	// Чтобы изменить градус поворота линии относительно оси x, например,
	// необходимо изменить заменить значения x2, y2 на другие,
	// не превышающие значения разрешения установленного окна
	paintLine(drawBresenhamLine, 0, 100, 400, 350);
	
	// запуск алгоритма ЦДА
	// устанавливаем красный цвет
	glColor3f(1.0f, 0.2f, 0.0f);
	paintLine(drawDDALine, 0, 100, 500, 350);
	glEnd();

	glFlush();
}


void paintLine(void(*func)(int, int, int, int), int x1, int y1, int x2, int y2)
{
	func(x1, y1, x2, y2);
}


// алгоритм Брезенхема
void drawBresenhamLine(int x1, int y1, int x2, int y2)
{
	// объявляем начальные точки и разницы dx и dy,
	// для того, чтобы в алгоритме решать какой пиксель закрашивать
	int x, y, dx = x2 - x1, dy = y2 - y1;
	int d = (dy << 1) - dx, d1 = dy << 1, d2 = (dy - dx) << 1;
	x = x1, y = y1;
	// устанавливаем начальную и конечные точки вектора
	glVertex2i(x1, y1);
	glVertex2i(x2, y2);
	x2--;
	while (x < x2)
	{
		// делаем шаг вправо по оси x
		x++;
		// и выбираем какой пиксель закрасить 
		// (пойти дальше и закрасить правый пиксель или вверхний,
		// относительно конечной точки вектора)

		if (d < 0) d += d1;
		else
		{
			y++;
			d += d2;
		}
		glVertex2i(x, y);
	}
}

// алгоритм ЦДА
void drawDDALine(int x1, int y1, int x2, int y2)
{
	// устанавливаем начальную точку
	float x = x1, y = y1;
	// устанавливаем разницы
	int dx = x2 - x1, dy = y2 - y1;
	// выбираем значение steps,
	// для дальнейшего определения шага
	int steps = dx > dy ? dx - 1 : dy - 1;
	// устанавливаем начальные и конечные точки 
	glVertex2i(x1, y1);
	glVertex2i(x2, y2);
	// определяем шаг
	float d = (float)dy / steps;
	for (int i = 0; i < steps; i++)
	{
		// определяем закрашиваемый пиксель
		x++;
		y += d;
		glVertex2i(x, y);
	}
}