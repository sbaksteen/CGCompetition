#ifndef MATERIAL_H_
#define MATERIAL_H_

#include "triple.h"
#include "image.h"


enum TextureType {
	col, im
};

class Material
{
    public:
		
		Color color;
		Image *image;
		Image *normalMap = nullptr;
		TextureType type;
        double ka;          // ambient intensity
        double kd;          // diffuse intensity
        double ks;          // specular intensity
        double n;           // exponent for specular highlight size
		bool transparent = false;
		double eta = 1;

        Material() = default;

        Material(Color const &color, double ka, double kd, double ks, double n)
        :
			color(color),
            ka(ka),
            kd(kd),
            ks(ks),
            n(n)
        {
			type = col;
		}
		
		Material(Image* image, double ka, double kd, double ks, double n)
		:
			image(image),
			ka(ka),
			kd(kd),
			ks(ks),
			n(n)
		{
			type = im;
		}
		
		Color colorAt(double u, double v) {
			switch (type) {
				case col:
					return color;
				case im:
					return image->colorAt(u, v);
			}
		}

		Vector normalAt(double u, double v) {
			Color nc = normalMap->colorAt(u, v); // assumes normal map not null
			return 2*nc - 1;
		}

		void setNorm(Image* im) {
			normalMap = im;
		}

		bool hasNorm() {
			return normalMap != nullptr;
		}


		
			
};

#endif
