#include "pim-sm-packet.h"
#include "ns3/log.h"

namespace ns3 {

NS_LOG_COMPONENT_DEFINE ("PIMSMHeader");

namespace pimsm {

TypeId PIMSMHeader::GetTypeId(void) {
	NS_LOG_INFO("creating the nodes");
	static TypeId tid =
			TypeId("PIMSMHeader").SetParent<Header>().AddConstructor<PIMSMHeader>();
	return tid;
}
TypeId PIMSMHeader::GetInstanceTypeId(void) const {
	return GetTypeId();
}

uint32_t PIMSMHeader::GetSerializedSize(void) const {
	return 6;
}
void PIMSMHeader::Serialize(Buffer::Iterator start) const {
	// The 2 byte-constant
	start.WriteU8(0xfe);
	start.WriteU8(0xef);
	// The data.
	start.WriteHtonU32(m_data);
}
uint32_t PIMSMHeader::Deserialize(Buffer::Iterator start) {
	uint8_t tmp;
	tmp = start.ReadU8();
	NS_ASSERT(tmp == 0xfe);
	tmp = start.ReadU8();
	NS_ASSERT(tmp == 0xef);
	m_data = start.ReadNtohU32();
	return 6; // the number of bytes consumed.
}

void PIMSMHeader::Print(std::ostream &os) const {
	os << "data=" << m_data;
}

void PIMSMHeader::SetData (uint32_t data){

	m_data = data;

}
}
}
