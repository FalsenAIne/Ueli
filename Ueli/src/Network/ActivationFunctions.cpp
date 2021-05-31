#include "Network/ActivationFunctions.h"

namespace Ueli {
	namespace Network {

		float ReLU(float x)
		{
			if (x < 0.0f) return 0.0f;
			return x;
		}
	}

}