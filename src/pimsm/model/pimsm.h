/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
#ifndef PIM_SM_H
#define PIM_SM_H


#include "ns3/ipv4-routing-protocol.h"

#include "ns3/object.h"
#include "ns3/ipv4.h"
#include "ns3/ipv4-routing-protocol.h"
#include "ns3/ipv4-static-routing.h"

#include <set>
#include <vector>
#include <map>

namespace ns3 {

namespace pimsm {

///
/// \defgroup pimsm pimsm Multicast Routing Protocol
/// This section documents the API of the ns-3 pimsm module. For a generic
/// functional description, please refer to the ns-3 manual.


///
/// \ingroup pimsm
///
/// \brief OLSR routing protocol for IPv4
///

class PIMSMProtocol : public Ipv4MulticastRoute{
public:

	PIMSMProtocol ();
	virtual ~PIMSMProtocol ();
	void ProcessHello(void);

private:
	//std::set<uint32_t> m_interfaceExclusions;
	//Ptr<Ipv4StaticRouting> m_routingTableAssociation;

private:
	// From Ipv4RoutingProtocol
	/**virtual Ptr<Ipv4Route> RouteOutput (Ptr<Packet> p,
										const Ipv4Header &header,
										Ptr<NetDevice> oif,
										Socket::SocketErrno &sockerr);*/
	/**virtual bool RouteInput (Ptr<const Packet> p,
							 const Ipv4Header &header,
							 Ptr<const NetDevice> idev,
							 UnicastForwardCallback ucb,
							 MulticastForwardCallback mcb,
							 LocalDeliverCallback lcb,
							 ErrorCallback ecb);*/

	//virtual void NotifyInterfaceUp (uint32_t interface);
	//virtual void NotifyInterfaceDown (uint32_t interface);
	//virtual void NotifyAddAddress (uint32_t interface, Ipv4InterfaceAddress address);
	//virtual void NotifyRemoveAddress (uint32_t interface, Ipv4InterfaceAddress address);
	//virtual void SetIpv4 (Ptr<Ipv4> ipv4);
	//virtual void PrintRoutingTable (Ptr<OutputStreamWrapper> stream) const;

};

}

}

#endif /* PIM_SM_H */

