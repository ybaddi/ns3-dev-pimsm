#include "pim-sm-packet.h"
#include "ns3/log.h"

namespace ns3
{

NS_LOG_COMPONENT_DEFINE ("PIMSMHeader");

namespace pimsm
{

PIMSMHeader::PIMSMHeader (MessageType t) :
  m_type (t), m_valid (true)
{
}

TypeId PIMSMHeader::GetTypeId(void)
{
	NS_LOG_INFO("creating the nodes");
	static TypeId tid = TypeId("ns3::pimsm::PIMSMHeader")
			.SetParent<Header>()
			.AddConstructor<PIMSMHeader>();
	return tid;
}

TypeId
PIMSMHeader::GetInstanceTypeId(void) const
{
	return GetTypeId();
}

uint32_t
PIMSMHeader::GetSerializedSize(void) const
{
	return 6;
}
void
PIMSMHeader::Serialize(Buffer::Iterator start) const
{
	// The 2 byte-constant
	start.WriteU8(0xfe);
	start.WriteU8(0xef);
	// the message type
	start.WriteU8 ((uint8_t) m_type);
	// The data.
	start.WriteHtonU32(m_data);
}

uint32_t
PIMSMHeader::Deserialize(Buffer::Iterator start)
{
	Buffer::Iterator i = start;
	uint8_t tmp;
	tmp = start.ReadU8();
	NS_ASSERT(tmp == 0xfe);
	tmp = start.ReadU8();
	NS_ASSERT(tmp == 0xef);
	m_data = start.ReadNtohU32();
	uint32_t dist = i.GetDistanceFrom (start);
	NS_ASSERT (dist == GetSerializedSize ());
	return dist; // the number of bytes consumed.
}

void PIMSMHeader::Print(std::ostream &os) const
{
	switch (m_type)
	    {
	    case PIMSMTYPE_PIMHELLO:
	      {
	        os << "RREQ";
	        break;
	      }
	    default:
	      os << "UNKNOWN_TYPE";
	    }
}

bool
PIMSMHeader::operator== (PIMSMHeader const & o) const
{
  return (m_type == o.m_type && m_valid == o.m_valid);
}

std::ostream &
operator<< (std::ostream & os, PIMSMHeader const & h)
{
  h.Print (os);
  return os;
}

//-----------------------------------------------------------------------------


void PIMSMHeader::SetData (uint32_t data){

	m_data = data;

}
}
}
