#include "MathService.h"

float MathService::radiansToDegrees(const float &angle) {
	return -(angle * 180) / M_PI;
}
