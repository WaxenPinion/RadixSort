#pragma once

#include <Windows.h>

class SetCP {

public:

	SetCP(int code)
		: m_prev_in{ GetConsoleCP() }
		, m_prev_out{ GetConsoleOutputCP() } {

		SetConsoleCP(code);
		SetConsoleOutputCP(code);

	};

	~SetCP() {
		SetConsoleCP(m_prev_in);
		SetConsoleOutputCP(m_prev_out);
	}

private:

	unsigned int m_prev_in;
	unsigned int m_prev_out;
};


int generateRandomInt(int min = INT_MIN, int max = INT_MAX);
