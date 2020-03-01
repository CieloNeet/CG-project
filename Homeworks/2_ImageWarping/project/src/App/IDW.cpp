#include "IDW.h"

IDW::IDW()
{
	u = 2;
}

IDW::~IDW()
{

}

int IDW::judge(int x, int y)
{
	for (size_t i = 0; i < IDW::wraping_start_points.size(); i++)
	{
		if ((x == IDW::wraping_start_points[i].x()) && (y == IDW::wraping_start_points[i].y()))
		{
			return i;
		}
	}
	return -1;
}

void IDW::wraping(QImage& image)
{
	QImage img(image);
	int width = image.width();
	int height = image.height();


	MatrixXi a(width, height);
	a = MatrixXi::Zero(width, height);
	Hole = a;
	
	double x_output , y_output ;

	int N = wraping_start_points.size();
	vector<double> sigma(N);

	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			image.setPixel(i, j, qRgb(255, 255, 255));
		}
	}


	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			//image.setPixel(i, j, qRgb(0, 0, 0));
			if (judge(i, j) != -1)
			{
				int k = judge(i, j);
				image.setPixel(wraping_end_points[k].x(),wraping_end_points[k].y(), img.pixel(i, j));
				//std::cout << 233 << std::endl;
			}
			else
			{
				double sigma_sum = 0.0;
				for (int m = 0; m < N; m++)
				{
					QPoint p_input(i, j);
					double disc = distance(p_input, wraping_start_points[m]);
					double sigma0 = 1.0 / pow(disc, u);
					sigma[m] = sigma0;
					sigma_sum += sigma0;
				}

				x_output = 0.0; y_output = 0.0;

				for (int m = 0; m < N; m++)
				{
					double omiga = sigma[m] / sigma_sum;
					double a1 = wraping_end_points[m].x(); double a2 = wraping_start_points[m].x();
					x_output = x_output + omiga * (a1 - a2);
					a1 = wraping_end_points[m].y(); a2 = wraping_start_points[m].y();
					y_output = y_output + omiga * (a1 - a2);
				}
				
				int x_p = floor(x_output) + i; int y_p = floor(y_output) + j;
				if (InImage(x_p, y_p, width, height))
				{
					image.setPixel(x_p, y_p, img.pixel(i, j));
					Hole(x_p, y_p) = 1;
				}
			}
		}
	}

	Fill(image);
	//Optional(image);


}

void IDW::Fill(QImage& image)
{
	QImage img(image);
	int width = image.width();
	int height = image.height();
	QRgb color;

	for (int i = 1; i < width-1; i++)
	{
		for (int j = 1; j < height-1; j++)
		{
			color = image.pixel(i, j);
			if (Hole(i,j)==0)
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

void IDW::Search(int i, int j)
{
	
}