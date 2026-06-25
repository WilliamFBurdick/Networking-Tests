#include "networking.h"

enum class CustomMsgTypes : uint32_t
{
	Heartbeat,
	GeneralPoll
};

int main()
{
	networking::message<CustomMsgTypes> msg;
	msg.header.id = CustomMsgTypes::Heartbeat;

	int a = 1;
	bool b = true;
	float c = 3.14159f;

	struct
	{
		float x;
		float y;
	} d[5];

	msg << a << b << c << d;

	a = 99;
	b = false;
	c = 99.0f;

	msg >> d >> c >> b >> a;

	return 0;
}