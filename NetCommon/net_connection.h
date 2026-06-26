#pragma once

#include "net_common.h"
#include "net_tsqueue.h"
#include "net_message.h"

namespace networking
{
	template<typename T>
	class connection : public std::enable_shared_from_this<connection<T>>
	{
	public:
		connection()
		{

		}

		virtual ~connection()
		{

		}
		
	public:
		bool ConnectToServer();
		bool Disconnect();
		bool IsConnected() const;

	public:
		bool Send(const message<T>& msg);

	protected:
		// Each connection has a unique socket to a remote.
		asio::ip::tcp::socket m_socket;
		
		// This context is shared with the whole asio instance.
		asio::io_context& m_asioContext;

		// Queue holds all message to be sent to the remote.
		tsqueue<message<T>> m_qMessagesOut;

		// Queue holds all messages that have been received from the remote.
		tsqueue<owned_message>& m_qMessagesIn;
	};
}