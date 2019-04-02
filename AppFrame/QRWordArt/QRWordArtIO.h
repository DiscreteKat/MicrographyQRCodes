#pragma once
#include "QRStringLine.h"
#include <iostream>

namespace QRWordArt
{
	namespace IO
	{
		void SaveWordArt(QRStringLines& data, const char* filename );
		QRStringLines LoadWordArt( const char* filename );
	}
}
