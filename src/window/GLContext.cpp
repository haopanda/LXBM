#include "GLContext.h"

#define addSquare(a, b, c) if (b != -1) a += (b - c) * (b - c)
#define addOne(a, b, c) if (b && !c) a++
#define addDiff(a, b, c) if (b > c) a += b - c

int GLContext::chooseFBConfig(const FBConfig& desired, const std::vector<FBConfig>& alternatives)
{
	unsigned int missing, leastMissing = UINT_MAX;
	unsigned int colorDiff, leastColorDiff = UINT_MAX;
	unsigned int extraDiff, leastExtraDiff = UINT_MAX;

	int closet = -1;
	for (auto i = 0; i < alternatives.size(); ++i)
	{
		auto& current = alternatives.at(i);

		if (desired.stereo > 0 && current.stereo == 0)
			continue;

		if (desired.doubleBuffer != current.doubleBuffer)
			continue;

		{
			missing = 0;
			addOne(missing, desired.alphaBits, current.alphaBits);
			addOne(missing, desired.depthBits, current.depthBits);
			addOne(missing, desired.stencilBits, current.stencilBits);
			addOne(missing, desired.samples, current.samples);
			addDiff(missing, desired.auxBuffers, current.auxBuffers);
		}

		{
			colorDiff = 0;
			addSquare(colorDiff, desired.redBits, current.redBits);
			addSquare(colorDiff, desired.greenBits, current.greenBits);
			addSquare(colorDiff, desired.blueBits, current.blueBits);
		}

		{
			extraDiff = 0;
			addSquare(extraDiff, desired.alphaBits, current.alphaBits);
			addSquare(extraDiff, desired.depthBits, current.depthBits);
			addSquare(extraDiff, desired.stencilBits, current.stencilBits);
			addSquare(extraDiff, desired.accumRedBits, current.accumRedBits);
			addSquare(extraDiff, desired.accumGreenBits, current.accumGreenBits);
			addSquare(extraDiff, desired.accumBlueBits, current.accumBlueBits);
			addSquare(extraDiff, desired.accumAlphaBits, current.accumAlphaBits);
			addSquare(extraDiff, desired.samples, current.samples);
			addOne(extraDiff, desired.sRGB, current.sRGB);
		}

		if (missing < leastMissing)
			closet = i;
		else if (missing == leastMissing)
		{
			if ((colorDiff < leastColorDiff) ||
				(colorDiff == leastColorDiff && extraDiff < leastExtraDiff))
				closet = i;
		}

		if (closet == i)
		{
			leastMissing = missing;
			leastColorDiff = colorDiff;
			leastExtraDiff = extraDiff;
		}
	}

	return closet;
}

bool GLContext::stringInExtensionString(const char* string, const char* extensions)
{
	const char* start = extensions;

	for (;;)
	{
		const char* where;
		const char* terminator;

		where = strstr(start, string);
		if (!where)
			return false;

		terminator = where + strlen(string);
		if (where == start || *(where - 1) == ' ')
		{
			if (*terminator == ' ' || *terminator == '\0')
				break;
		}

		start = terminator;
	}

	return true;
}