//
// Created by baddi on 28/02/16.
//
#include "ns3/header.h"
#include "ns3/address-utils.h"
#include "ns3/packet.h"

#ifndef NS_3_DEV_MULTICAST_MODULE_PIM_SM_PACKET_H
#define NS_3_DEV_MULTICAST_MODULE_PIM_SM_PACKET_H

#endif //NS_3_DEV_MULTICAST_MODULE_PIM_SM_PACKET_H

namespace ns3 {
namespace pimsm {

	class PIMSMHeader: public Header
	{
	public:
	    // must be implemented to become a valid new header.
	    static TypeId GetTypeId (void);
	    virtual TypeId GetInstanceTypeId (void) const;
	    virtual uint32_t GetSerializedSize (void) const;
	    virtual void Serialize (Buffer::Iterator start) const;
	    virtual uint32_t Deserialize (Buffer::Iterator start);
	    virtual void Print (std::ostream &os) const;

	    // allow protocol-specific access to the header data.
	    void SetData (uint32_t data);
	    uint32_t GetData (void) const;
	private:
	    uint32_t m_data;
	};

}
}

