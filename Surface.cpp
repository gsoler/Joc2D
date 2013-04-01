#include "Surface.h"
//#include <random>
#include <assert.h>

Surface::Surface(int height, int width)
{
	this->width = width;
	this->height = height;

	this->surface = vector<vector<double> >(height, vector<double>(width, 0));
}

Surface::~Surface(void)
{
}

double Surface::getZ(int y, int x) 
{
	assert(x >= 0 || x < width || y >= 0 || y < height);
	return surface[y][x];
}

double Surface::dRand(double min, double max) {
	double f = rand() / RAND_MAX;
	return min + f * (max - min);
}

void Surface::perlinNoise(int r, unsigned int seed)
{
	assert(r > 0);

	int n = width/r + 2;
	int m = height/r + 2;
	vector<vector<vec2> > grid(m, vector<vec2>(n));

	//using random
	//default_random_engine generator(seed);
	//uniform_real_distribution<double> distribution(-1.0, 1.0);

	for (int i = 0; i < m; ++i) {
		for (int j = 0; j < n; ++j) {
			//grid[i][j].x = distribution(generator);
			//grid[i][j].y = distribution(generator);
			grid[i][j].x = dRand(-1.0, 1.0);
			grid[i][j].y = dRand(-1.0, 1.0);
			normalizeVec2(grid[i][j]);
		}
	}

	for (int i = 0; i < height; ++i) {
		for (int j = 0; j < width; ++j) {
			int x0 = j/r;
			int x1 = x0 + 1;
			int y0 = i/r;
			int y1 = y0 + 1;

			double y = double(i)/double(r);
			double x = double(j)/double(r);
			
			vec2 v, u, s, t;
			s.x = x - double(x0); s.y = y - double(y0);
			u.x = x - double(x0); u.y = y - double(y1);
			t.x = x - double(x1); t.y = y - double(y0);
			v.x = x - double(x1); v.y = y - double(y1);
			
			double z00 = dotProdVec2(grid[y0][x0], s);
			double z10 = dotProdVec2(grid[y1][x0], u);
			double z01 = dotProdVec2(grid[y0][x1], t);
			double z11 = dotProdVec2(grid[y1][x1], v);

			double Sx = s.x*s.x * (3.0 - 2.0*s.x);
			double Sy = s.y*s.y * (3.0 - 2.0*s.y);

			double a = z00 + Sx*(z01-z00);
			double b = z10 + Sx*(z11-z10);

			surface[i][j] = a + Sy*(b-a);
		}
	}
}

void Surface::normalizeVec2(vec2& v) 
{
	double length = sqrt(v.x*v.x + v.y*v.y);

	v.x = v.x/length;
	v.y = v.y/length;
}

double Surface::dotProdVec2(const vec2& v, const vec2& u) 
{
	return v.x+u.y * v.y+u.y;
}