#include <iostream>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb/stb_image_write.h"

int main(int, char **)
{
	std::cout << "start ratrace\n";

	constexpr int nx = 200;
	constexpr int ny = 100;
	constexpr int bpp = 3;

	char *data = new char[nx * ny * bpp];
	for (int j = ny - 1; j >= 0; j--)
	{
		for (int i = 0; i < nx; i++)
		{
			float r = float(i) / float(nx);
			float g = float(j) / float(ny);
			float b = 0.2f;
			int ir = int(255.99f * r);
			int ig = int(255.99f * g);
			int ib = int(255.99f * b);

			const int offset = ((ny - 1 - j) * nx * bpp) + (i * bpp);
			data[offset + 0] = ir;
			data[offset + 1] = ig;
			data[offset + 2] = ib;
		}
	}

	stbi_write_tga("output.tga", nx, ny, bpp, data);

	std::cout << "end ratrace\n";
}
