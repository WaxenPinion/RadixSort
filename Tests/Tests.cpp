#include "pch.h"
#include "CppUnitTest.h"

#include "ButtonLogic.hpp"
#include "Utils.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Tests
{
	TEST_CLASS(Tests)
	{
	public:
		sf::Http http{ "localhost", 8000 };
		
		TEST_METHOD(TestAdd100)
		{
			for (int i = 0; i < 100; ++i) {
				
			}
			sf::Http::Response response = sendPostRequest(http, "add/");
		}
	};
}
