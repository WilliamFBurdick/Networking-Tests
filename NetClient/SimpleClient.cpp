#include "networking.h"

enum class CustomMsgTypes : uint32_t
{
	Heartbeat,
	GeneralPoll
};

class CustomClient : public networking::client_interface<CustomMsgTypes>
{
public:
	bool Heartbeat(float value)
	{
		networking::message<CustomMsgTypes> msg;
		msg.header.id = CustomMsgTypes::Heartbeat;
		msg << value;
		//Send(msg);
	}
};

int main()
{
	CustomClient c;
	c.Connect("website.com", 60000);
	c.Heartbeat(200.f);

	return 0;
}