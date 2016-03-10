/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2007 INESC Porto
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * Author: Youssef BADDI  <baddi.youssef@gmail.com>
 */

#include "ns3/header.h"
#include "ns3/address-utils.h"
#include "ns3/packet.h"
#include "ns3/nstime.h"

#ifndef NS_3_DEV_MULTICAST_MODULE_PIM_SM_PACKET_H
#define NS_3_DEV_MULTICAST_MODULE_PIM_SM_PACKET_H

#endif //NS_3_DEV_MULTICAST_MODULE_PIM_SM_PACKET_H

namespace ns3 {
namespace pimsm {

	double EmfToSeconds (uint8_t emf);
	uint8_t SecondsToEmf (double seconds);

// 3.3.  Packet Format
//
//    The basic layout of any packet in OLSR is as follows (omitting IP and
//    UDP headers):
//    0                   1                   2                   3
//    0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
//   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//   |PIM Ver| Type  |   Reserved    |           Checksum            |
//   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

class PacketHeader: public Header {
public:
	// must be implemented to become a valid new header.
	static TypeId GetTypeId(void);
	virtual TypeId GetInstanceTypeId(void) const;
	virtual uint32_t GetSerializedSize(void) const;
	virtual void Serialize(Buffer::Iterator start) const;
	virtual uint32_t Deserialize(Buffer::Iterator start);
	virtual void Print(std::ostream &os) const;

	// allow protocol-specific access to the header data.
	void SetData(uint32_t data);
	uint32_t GetData(void) const;
private:
	uint32_t m_data;
};

		// 5.1.  Hello Message Format
//
//    The proposed format of a Hello message is as follows:
//
//    0                   1                   2                   3
//    0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
//   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//   |PIM Ver| Type  |   Reserved    |           Checksum            |
//   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//   |          OptionType           |         OptionLength          |
//   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//   |                          OptionValue                          |
//   |                              ...                              |
//   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//   |                               .                               |
//   |                               .                               |
//   |                               .                               |
//   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//   |          OptionType           |         OptionLength          |
//   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//   |                          OptionValue                          |
//   |                              ...                              |
//   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

		class HelloHeader : public Header
		{

			enum OptionType {
				Holdtime_TYPE =1,
			};

		private:
			OptionType o_optionType;

		public:
			static TypeId GetTypeId(void);
			virtual TypeId GetInstanceTypeId(void) const;
			virtual void Print(std::ostream &os) const;
			virtual uint32_t GetSerializedSize(void) const;
			virtual void Serialize(Buffer::Iterator start) const;
			virtual uint32_t Deserialize(Buffer::Iterator start);

		};

//    0                   1                   2                   3
//    0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
//   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//   |PIM Ver| Type  |   Reserved    |           Checksum            |
//   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

class MessageHeader: public Header {
public:

	enum MessageType {
		HELLO_MESSAGE = 1,
		Register_MESSAGE = 2,
		Register_Stop_MESSAGE = 3,
		Join_Prune_MESSAGE = 4,
		Bootstrap_MESSAGE = 5,
		Assert_MESSAGE = 6,
		Graft_MESSAGE = 7,
		Graft_Ack_MESSAGE = 8,
		Candidate_RP_Advertisement_MESSAGE = 9,
	};

	MessageHeader ();
	virtual ~MessageHeader ();

	void SetMessageType (MessageType messageType)
	{
		m_messageType = messageType;
	}
	MessageType GetMessageType () const
	{
		return m_messageType;
	}

	void SetVTime (Time time)
	{
		m_vTime = SecondsToEmf (time.GetSeconds ());
	}
	Time GetVTime () const
	{
		return Seconds (EmfToSeconds (m_vTime));
	}

	void SetOriginatorAddress (Ipv4Address originatorAddress)
	{
		m_originatorAddress = originatorAddress;
	}
	Ipv4Address GetOriginatorAddress () const
	{
		return m_originatorAddress;
	}

	void SetTimeToLive (uint8_t timeToLive)
	{
		m_timeToLive = timeToLive;
	}
	uint8_t GetTimeToLive () const
	{
		return m_timeToLive;
	}

	void SetHopCount (uint8_t hopCount)
	{
		m_hopCount = hopCount;
	}
	uint8_t GetHopCount () const
	{
		return m_hopCount;
	}

	void SetMessageSequenceNumber (uint16_t messageSequenceNumber)
	{
		m_messageSequenceNumber = messageSequenceNumber;
	}
	uint16_t GetMessageSequenceNumber () const
	{
		return m_messageSequenceNumber;
	}
private:
	MessageType m_messageType;
	uint8_t m_vTime;
	Ipv4Address m_originatorAddress;
	uint8_t m_timeToLive;
	uint8_t m_hopCount;
	uint16_t m_messageSequenceNumber;
	uint16_t m_messageSize;

public:
	static TypeId GetTypeId(void);
	virtual TypeId GetInstanceTypeId(void) const;
	virtual void Print(std::ostream &os) const;
	virtual uint32_t GetSerializedSize(void) const;
	virtual void Serialize(Buffer::Iterator start) const;
	virtual uint32_t Deserialize(Buffer::Iterator start);

private:
	struct
	{
		HelloHeader hello;
	} m_message; // union not allowed
};



}
}

