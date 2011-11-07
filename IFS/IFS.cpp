#include <cstdio>
#include <cstdlib>
#include <cassert>

#include "IFS.h"
#include "image.h"
#include "vector.h"
#include "matrix.h"

// -------------------------------------------------------------------
// -------------------------------------------------------------------

// Member Function of Rendering Fractal Graphics.
void IFS::fractalRendering(Image &img, unsigned int pointNum, unsigned int iterTimes, const char *outputFile) const
{
	// Image Initialization ~~
	int height = img.Height(), width = img.Width();
	assert (height > 0 && width > 0);
	
	Vec3f black(0.0f, 0.0f, 0.0f), white(255.0f, 255.0f, 255.0f);
	img.SetAllPixels(black);

	// To Generate Random float number between 0 and 1 ~~
	std::vector<Vec2f> initPoints;
	for (unsigned int i = 0; i < pointNum; ++i) {
		Vec2f randomPoint((float)(rand() % width), (float)(rand() % height));
		
		initPoints.push_back(randomPoint);
		// img.SetPixel((int)(randomPoint.x()), (int)(randomPoint.y()), white);
	}

	for (int i = 0; i < m_transProbality.size(); ++i) {
		printf("%f ", m_transProbality[i]);
	}

	printf("\n");

	// Starting to iterate~~
	for (unsigned int times = 0; times < iterTimes; ++times)
	{
		for (unsigned int j = 0; j < initPoints.size(); ++j)
		{
			// To determine to use which transform ~~
			double ran = (double)(rand()) / (double)(RAND_MAX), p = m_transProbality[0];
			unsigned int index = 0;
			while (p < ran) {
				p += m_transProbality[++index];
			}

			// printf("Random Number is: %f\n", ran);
			// printf("Index is: %d\n", index);

			// Affline Transformation ~~
			Matrix transMatrix = m_transMatrix[index];
			Vec2f t(initPoints[j].x() / (double)(width), initPoints[j].y() / (double)(height));
			transMatrix.Transform(t);
			initPoints[j].Set(t.x() * width, t.y() * height);
		}
	}

	// Draw Image ~~
	int x_min = UINT_MAX, x_max = INT_MIN, y_min = UINT_MAX, y_max = INT_MIN;
	for (int i = 0; i < initPoints.size(); ++i) {
		if (initPoints[i].x() < x_min) x_min = initPoints[i].x();
		if (initPoints[i].x() > x_max) x_max = initPoints[i].x();

		if (initPoints[i].y() < y_min) y_min = initPoints[i].y();
		if (initPoints[i].y() > y_max) y_max = initPoints[i].y();
	}
	
	if (x_min < 0) {
		for (int i = 0; i < initPoints.size(); ++i) {
			initPoints[i].Set(initPoints[i].x() - x_min, initPoints[i].y()); }

		x_max -= x_min;
	}

	if (y_min < 0) {
		for (int i = 0; i < initPoints.size(); ++i)
			initPoints[i].Set(initPoints[i].x(), initPoints[i].y() - y_min);

		y_max -= y_min;
	}

	if (x_max >= width || y_max >= height) {
		int d = (x_max > y_max) ? x_max : y_max;
		double f1 = (double)(width) / (double)(d), f2 = (double)(height) / (double)(d);

		for (int i = 0; i < initPoints.size(); ++i)
			initPoints[i].Set(initPoints[i].x() * (f1 - 0.01), initPoints[i].y() * (f2 - 0.01));
	}

	for (int i = 0; i < initPoints.size(); ++i) {
		img.SetPixel(initPoints[i].x(), initPoints[i].y(), white);
	}

	// To Save the finished image ~~
	// img.SaveTGA("D:\\IFS_Result.tga");
	img.SaveTGA(outputFile);
	return;
}


// Get IFS system information from the specified file.
void IFS::readFile(const char *filename)
{
	assert (filename != NULL);

	m_transMatrix.clear();
	m_transProbality.clear();

	FILE *f = fopen(filename, "r");
	if (f == NULL) {
		perror("Error opening file");
		return;
	}

	unsigned int number = 0;
	int isread = fscanf(f, "%d\n", &number);
	assert (isread > 0);

	m_n = number;
	
	for (unsigned int i = 0; i < m_n; ++i)
	{
		float prob = 0.0;
		fscanf(f, "%f", &prob);
		m_transProbality.push_back(prob);
		
		Matrix m;
		m.Read3x3(f);
		m_transMatrix.push_back(m);
	}

	return;
}


// Print IFS ~~
void IFS::printIFS() const
{
	printf("Number of Transform Kinds:\t%d\n", m_n);

	for (unsigned int i = 0; i < m_n; ++i)
	{
		printf("Transform Probality and Matrix of index %d:\n", i+1);
		printf("%g\n", m_transProbality[i]);
		m_transMatrix[i].Write();
		
		printf("\n");
	}
	
	return;
}