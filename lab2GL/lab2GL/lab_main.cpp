/*
#include <stdlib.h> 
#include <windows.h> 
#include <iostream> 
#include <../include/GL/glut.h>
#include <cmath> 

using namespace std;


int points[100][100];

const int view_side_size = 40;
const int period = 120;

const int side_size = 700;

struct vec2_t {
	int x = 0, y = 0;
	vec2_t(int x, int y) : x(x), y(y) {}
	vec2_t() {}
	float len() {
		return sqrt(x * x + y * y);
	}

	int len_int() {
		return len();
	}
};

vec2_t operator-(vec2_t a, vec2_t b) {
	return vec2_t(a.x - b.x, a.y - b.y);
}

vec2_t to_inner_coords(int x, int y) {
	vec2_t out;
	out.x = x;
	out.y = y;
	out.x = round(((out.x - side_size / 2.0f) / side_size) * (view_side_size * 2.0f));
	out.y = round(((side_size / 2.0f - out.y) / side_size) * (view_side_size * 2.0f));

	return out;
}

vec2_t g[6];
int gi = 0;


// фиксируем нажатие мышью на рисунке
void mb(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON)
	{
		if (state == GLUT_UP && gi < 6) {
			vec2_t coords = to_inner_coords(x, y);

			g[gi++] = coords;
		}
	}
}

// создаем возможность создавать множество
// цветов
struct color_t
{
	double r, g, b, a;
	void setThis() const
	{
		const color_t& color = *this;
		glColor4d(color.r, color.g, color.b, color.a);
	}
};

const color_t orange = { 1, 0.5, 0.0, 1 };
const color_t red = { 1, 0, 1, 0 };
const color_t white = { 1, 1, 1, 0 };

// рисуем точку в том месте, где было зафиксировано нажатие
void DrawFatPixel(int x, int y, color_t color = red)
{
	color.setThis();
	// сама точка представляет собой маленький многоугольник
	glBegin(GL_POLYGON);
	glVertex2d(x - 0.5, y - 0.5);
	glVertex2d(x - 0.5, y + 0.5);
	glVertex2d(x + 0.5, y + 0.5);
	glVertex2d(x + 0.5, y - 0.5);
	glEnd();
}

void DrawCell() //прорисовка сетки координат 
{
	glLineWidth(1);
	glColor3f(0.0, 0.0, 0.0);//(1.0, 0.0, 1.0);

	for (double i = -view_side_size; i <= view_side_size; i += 1.5)
	{

		glBegin(GL_LINES);
		glVertex2f(i + 1.f, -view_side_size + .0f);
		glVertex2f(i + 1., view_side_size + .0f);

		glVertex2f(-view_side_size + .0f, i + 1.f);
		glVertex2f(view_side_size + .0f, i + 1.f);
		glEnd();

	}
}


// 
void DrawLineBrezenhem(int x0, int y0, int x1, int y1, int flag, color_t color = orange)  
{
	glColor3f(0.5, 1.0, 1.0);
	bool steep = false;
	if (std::abs(x0 - x1) < std::abs(y0 - y1))
	{
		std::swap(x0, y0);
		std::swap(x1, y1);
		steep = true;
	}
	if (x0 > x1)
	{
		std::swap(x0, x1);
		std::swap(y0, y1);
	}
	int dx = x1 - x0;
	int dy = y1 - y0;
	int derror2 = std::abs(dy) * 2;
	int error2 = 0;
	int y = y0;
	int i = 0;
	for (int x = x0; x <= x1; x++)
	{
		if (steep)
		{
			DrawFatPixel(y, x, color);
			points[y + 50][x + 50] |= flag;
		}
		else
		{
			DrawFatPixel(x, y, color);
			points[x + 50][y + 50] |= flag;
		}

		error2 += derror2;

		if (error2 > dx)
		{
			y += (y1 > y0 ? 1 : -1);
			error2 -= dx * 2;
		}
	}
}

int count_bits(int i) {
	int res = 0;
	while (i) {
		if (i & 1) res++;
		i = i >> 1;
	}
	return res;
}

void DrawPolygon(const int tick)
{
	for (int y = 0; y < 100 && y < tick; y++)
	{
		bool is_in = false;
		for (int x = 1; x < 100; x++)
		{
			if (points[x][y] && !(points[x][y] & points[x - 1][y]))
			{
				is_in = !is_in;
			}
			if (is_in) {
				DrawFatPixel(x-20, y-20, orange);
			}
		}
	}

	for (int y = 0; y < 100 && y < tick; y++)
	{
		for (int x = 99; x > 0; --x) {
			if (points[x][y]) break;
			DrawFatPixel(x - 50, y - 50, white);
		}
	}
}

void Display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	if (gi > 6) {
		static int tick = 0;
		tick++;
		DrawLineBrezenhem(g[0].x, g[0].y, g[1].x, g[1].y, 1 << 0);
		DrawLineBrezenhem(g[1].x, g[1].y, g[2].x, g[2].y, 1 << 1);
		DrawLineBrezenhem(g[2].x, g[2].y, g[3].x, g[3].y, 1 << 2);
		DrawLineBrezenhem(g[3].x, g[3].y, g[4].x, g[4].y, 1 << 3);
		DrawLineBrezenhem(g[4].x, g[4].y, g[5].x, g[5].y, 1 << 4);
		DrawLineBrezenhem(g[5].x, g[5].y, g[0].x, g[0].y - 1, 1 << 5);
		DrawPolygon(tick);
	}
	else {
		for (int i = 0; i < gi; ++i) {
			DrawFatPixel(g[i].x, g[i].y, orange);
		}
		if (gi == 6) gi++;
	}
	DrawCell();

	glFlush();
}

void timf(int value)
{
	glutPostRedisplay();
	glutTimerFunc(period, timf, 0);
}

void Initialize()
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-view_side_size, view_side_size, -view_side_size, view_side_size, -1.0, 1.0);
	for (int y = 0; y < 100; y++)
	{
		for (int x = 0; x < 100; x++)
		{
			points[x][y] = 0;
		}
	}
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(side_size, side_size);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Lab2_Chernov");
	Initialize();
	glutDisplayFunc(Display);
	glutMouseFunc(mb);
	glutTimerFunc(period, timf, 0);
	glutMainLoop();


	return 0;

}
*/