#include "cMessageManager_impl.h"
#include "iMessageInterface.h"
#include <iostream>

cMessageManager_impl::cMessageManager_impl()
{
}

cMessageManager_impl::~cMessageManager_impl()
{
}

bool cMessageManager_impl::Register(const std::string& interfaceName, iMessageInterface* interface)
{
	if (m_mapMessageInterfaces.find(interfaceName) != m_mapMessageInterfaces.end())
	{
		if (m_mapMessageInterfaces[interfaceName] == interface)
		{
			std::cout << "cMessageManager_impl - " 
					  << "Double registration fo the same class: " 
					  << interfaceName << " Ignored" << std::endl;
		}
		else
		{
			// This should not happen. resuse of a UID
			assert(false);
			std::cout << "cMessageManager_impl - " 
				<< "Invalid double registration fo different classes with the same name: "
				<< interfaceName << std::endl;
		}
		return false;
	}
	m_mapMessageInterfaces[interfaceName] = interface;
	return true;
}


bool cMessageManager_impl::SendMessage(const iMessage& message)
{
	auto reciever = message.Reciever();
	auto sender = message.Sender();

	// Do some validation
	if (m_mapMessageInterfaces.find(reciever) == m_mapMessageInterfaces.end())
	{
		std::cout << "cMessageManager_impl: " << " Unregistered reciever: " << reciever << std::endl;
		assert(false);
		return false;
	}
	if (m_mapMessageInterfaces.find(sender) == m_mapMessageInterfaces.end())
	{
		std::cout << "cMessageManager_impl: " << " Unregistered sender: " << sender << std::endl;
		assert(false);
		return false;
	}

	return m_mapMessageInterfaces[reciever]->RecieveMessage(message);
}

bool cMessageManager_impl::SendWithResponse(const iMessage& send, iMessage& ret)
{
	auto reciever = send.Reciever();
	auto sender = send.Sender();

	// Do some validation
	if (m_mapMessageInterfaces.find(reciever) == m_mapMessageInterfaces.end())
	{
		std::cout << "cMessageManager_impl: " << " Unregistered reciever: " << reciever << std::endl;
		assert(false);
		return false;
	}
	if (m_mapMessageInterfaces.find(sender) == m_mapMessageInterfaces.end())
	{
		std::cout << "cMessageManager_impl: " << " Unregistered sender: " << sender << std::endl;
		assert(false);
		return false;
	}

	return m_mapMessageInterfaces[reciever]->RecieveAndRespond(send, ret);
}

// Broadcast a message to anyone who is interested
bool cMessageManager_impl::Broadcast(const iMessage& message)
{
	// No reciever since it's a broadcast
	auto sender = message.Sender();

	// Do some validation
	if (m_mapMessageInterfaces.find(sender) == m_mapMessageInterfaces.end())
	{
		std::cout << "cMessageManager_impl: " << " Unregistered sender: " << sender << std::endl;
		assert(false);
		return false;
	}
	//TODO - Broadast to all listeners
	assert(false);			//TODO implement
	return false;
}
