#include "pim-sm-header.h"

#include "ns3/log.h"

#define IPV4_ADDRESS_SIZE 4
#define OLSR_MSG_HEADER_SIZE 12
#define OLSR_PKT_HEADER_SIZE 4

namespace ns3 {

NS_LOG_COMPONENT_DEFINE ("PIMSMHeader");

namespace pimsm {




TypeId PacketHeader::GetTypeId(void) {
	NS_LOG_INFO("creating the nodes");
	static TypeId tid =
			TypeId("ns3::pimsm::PacketHeader")
			.SetParent<Header>()
			.SetGroupName ("Pimsm")
			.AddConstructor<PacketHeader>();
	return tid;
}
TypeId PacketHeader::GetInstanceTypeId(void) const {
	return GetTypeId();
}

uint32_t PacketHeader::GetSerializedSize(void) const {
	return 6;
}
void PacketHeader::Serialize(Buffer::Iterator start) const {
	// The 2 byte-constant
	start.WriteU8(0xfe);
	start.WriteU8(0xef);
	// The data.
	start.WriteHtonU32(m_data);
}
uint32_t PacketHeader::Deserialize(Buffer::Iterator start) {
	uint8_t tmp;
	tmp = start.ReadU8();
	NS_ASSERT(tmp == 0xfe);
	tmp = start.ReadU8();
	NS_ASSERT(tmp == 0xef);
	m_data = start.ReadNtohU32();
	return 6; // the number of bytes consumed.
}

void PacketHeader::Print(std::ostream &os) const {
	os << "data=" << m_data;
}

void PacketHeader::SetData (uint32_t data){

	m_data = data;

}


	// ---------------- PIMSM Message -------------------------------

	MessageHeader::MessageHeader ()
			: m_messageType (MessageHeader::MessageType (0))
	{
	}

	MessageHeader::~MessageHeader ()
	{
	}

	TypeId
	MessageHeader::GetTypeId (void)
	{
		static TypeId tid = TypeId ("ns3::olsr::MessageHeader")
				.SetParent<Header> ()
				.SetGroupName ("Pimsm")
				.AddConstructor<MessageHeader> ()
		;
		return tid;
	}
	TypeId
	MessageHeader::GetInstanceTypeId (void) const
	{
		return GetTypeId ();
	}

	uint32_t
	MessageHeader::GetSerializedSize (void) const
	{
		uint32_t size = OLSR_MSG_HEADER_SIZE;
		switch (m_messageType)
		{
			case HELLO_MESSAGE:
				//size += m_message.mid.GetSerializedSize ();
				break;
			case Register_MESSAGE:
				//NS_LOG_DEBUG ("Hello Message Size: " << size << " + " << m_message.hello.GetSerializedSize ());
				size += m_message.hello.GetSerializedSize ();
				break;
			case Register_Stop_MESSAGE:
				//size += m_message.tc.GetSerializedSize ();
				break;
			case Join_Prune_MESSAGE:
				//size += m_message.hna.GetSerializedSize ();
				break;
			default:
				NS_ASSERT (false);
		}
		return size;
	}

	void
	MessageHeader::Print (std::ostream &os) const
	{
		/// \todo
	}

	void
	MessageHeader::Serialize (Buffer::Iterator start) const
	{
		Buffer::Iterator i = start;
		i.WriteU8 (m_messageType);
		i.WriteU8 (m_vTime);
		i.WriteHtonU16 (GetSerializedSize ());
		i.WriteHtonU32 (m_originatorAddress.Get ());
		i.WriteU8 (m_timeToLive);
		i.WriteU8 (m_hopCount);
		i.WriteHtonU16 (m_messageSequenceNumber);

		switch (m_messageType)
		{
			case HELLO_MESSAGE:
				//m_message.mid.Serialize (i);
				break;
			case Register_MESSAGE:
				//m_message.hello.Serialize (i);
				break;
			case Register_Stop_MESSAGE:
				//m_message.tc.Serialize (i);
				break;
			case Join_Prune_MESSAGE:
				//m_message.hna.Serialize (i);
				break;
			default:
				NS_ASSERT (false);
		}

	}

	uint32_t
	MessageHeader::Deserialize (Buffer::Iterator start)
	{
		uint32_t size;
		Buffer::Iterator i = start;
		m_messageType  = (MessageType) i.ReadU8 ();
		NS_ASSERT (m_messageType >= HELLO_MESSAGE && m_messageType <= Join_Prune_MESSAGE);
		m_vTime  = i.ReadU8 ();
		m_messageSize  = i.ReadNtohU16 ();
		m_originatorAddress = Ipv4Address (i.ReadNtohU32 ());
		m_timeToLive  = i.ReadU8 ();
		m_hopCount  = i.ReadU8 ();
		m_messageSequenceNumber = i.ReadNtohU16 ();
		size = OLSR_MSG_HEADER_SIZE;
		switch (m_messageType)
		{
			case HELLO_MESSAGE:
				//size += m_message.mid.Deserialize (i, m_messageSize - OLSR_MSG_HEADER_SIZE);
				break;
			case Register_MESSAGE:
				//size += m_message.hello.Deserialize (i, m_messageSize - OLSR_MSG_HEADER_SIZE);
				break;
			case Register_Stop_MESSAGE:
				//size += m_message.tc.Deserialize (i, m_messageSize - OLSR_MSG_HEADER_SIZE);
				break;
			case Join_Prune_MESSAGE:
				//size += m_message.hna.Deserialize (i, m_messageSize - OLSR_MSG_HEADER_SIZE);
				break;
			default:
				NS_ASSERT (false);
		}
		return size;
	}


	// ---------------- HEllo PIMSM Message -------------------------------

	TypeId
	HelloHeader::GetTypeId (void)
	{
		static TypeId tid = TypeId ("ns3::pimsm::HelloHeader")
				.SetParent<Header> ()
				.SetGroupName ("Pimsm")
				.AddConstructor<MessageHeader> ()
		;
		return tid;
	}

	TypeId
	HelloHeader::GetInstanceTypeId (void) const
	{
		return GetTypeId ();
	}

	uint32_t
	HelloHeader::GetSerializedSize (void) const
	{
		uint32_t size = OLSR_MSG_HEADER_SIZE;
		return size;
	}

	void
	HelloHeader::Print (std::ostream &os) const
	{
		/// \todo
	}

	void
	HelloHeader::Serialize (Buffer::Iterator start) const
	{

	}

	uint32_t
	HelloHeader::Deserialize (Buffer::Iterator start) {
		uint32_t size = OLSR_MSG_HEADER_SIZE;
		return size;
	}
}
}
