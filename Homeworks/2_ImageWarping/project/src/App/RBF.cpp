#include "RBF.h"

#define maxn 10000000.0

RBF::RBF()
{

}

RBF::~RBF()
{

}

void RBF::set_r()
{
	int N = wraping_start_points.size();
	r.resize(N);
	double min = 0.0;
	for (int i = 0; i < N; i++)
	{
		min = maxn;
		for (int j = 0; j < N; j++)
		{
			if (j != i)
			{
				double disc = distance(wraping_start_points[i], wraping_start_points[j]);
				min = (min < disc) ? min : disc;
			}
		}
		r[i] = min;
	}
}

void RBF::set_H()
{
	int N = wraping_start_points.size();
	MatrixXd Ma(N, N);
	RBF_H = Ma;

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			double disc = distance(wraping_start_points[i], wraping_start_points[j]);
			RBF_H(i, j) = pow((disc * disc + r[j] * r[j]), 0.5);
		}
	}
}

void RBF::wraping(QImage& image)
{
	int N = wraping_start_points.size();
	QImage img(image);
	int width = image.width();
	int height = image.height();
	VectorXd Minus_x(N); VectorXd Minus_y(N);
	VectorXd a_x; VectorXd a_y; VectorXd g_d(N);

	MatrixXi a(width, height);
	a = MatrixXi::Zero(width, height);
	Hole = a;

	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			image.setPixel(i, j, qRgb(255, 255, 255));
		}
	}

	set_r();
	set_H();

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			Minus_x[i] = double(wraping_end_points[i].x()) - wraping_start_points[i].x();
			Minus_y[i] = double(wraping_end_points[i].y()) - wraping_start_points[i].y();
		}
	}

	a_x = RBF_H.colPivHouseholderQr().solve(Minus_x);
	a_y = RBF_H.colPivHouseholderQr().solve(Minus_y);

	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			QPoint P(i, j);
			for (int k = 0; k < N; k++)
			{
				double disc = distance(P, wraping_start_points[k]);
				g_d[k] = pow((disc * disc + r[k] * r[k]), 0.5);
			}
			double x_output = a_x.dot(g_d);
			double y_output = a_y.dot(g_d);

			int x0 = floor(x_output) + i;
			int y0 = floor(y_output) + j;

			if (InImage(x0, y0, width, height))
			{
				image.setPixel(x0, y0, img.pixel(i, j));
				Hole(x0, y0) = 1;
			}
			

		}
	}

	Fill(image);
}

void RBF::Fill(QImage& image)
{
	QImage img(image);
	int width = image.width();
	int height = image.height();
	QRgb color;

	for (int i = 1; i < width - 1; i++)
	{
		for (int j = 1; j < height - 1; j++)
		{
			color = image.pixel(i, j);
			if (Hole(i, j) == 0)
			{
				QRgb color1 = img.pixel(i - 1, j);
				QRgb color2 = img.pixel(i, j - 1);
				QRgb color3 = img.pixel(i, j + 1);
				QRgb color4 = img.pixel(i + 1, j);
				int mRed = (qRed(color1) + qRed(color2) + qRed(color3) + qRed(color4)) / 4;
				int mGreen = (qGreen(color1) + qGreen(color2) + qGreen(color3) + qGreen(color4)) / 4;
				int mBlue = (qBlue(color1) + qBlue(color2) + qBlue(color3) + qBlue(color4)) / 4;
				//int mRed = (qRed(color1)  + qRed(color4)) / 2;
				//int mGreen = (qGreen(color1)  + qGreen(color4)) / 2;
				//int mBlue = (qBlue(color1) +  qBlue(color4)) / 2;
				image.setPixel(i, j, qRgb(mRed, mGreen, mBlue));

			}
		}
	}
}