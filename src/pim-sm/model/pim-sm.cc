/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */

#include "pim-sm.h"
#include "pim-sm-packet.h"
#include "ns3/address-utils.h"
#include "ns3/packet.h"
#include "ns3/core-module.h"
#include <iostream>

namespace ns3 {

NS_LOG_COMPONENT_DEFINE ("PIM-SM");

namespace pimsm {

void ProcessHello(void) {
	std::cout << "Starting simulation for  ...\n";
	Ptr<Packet> p ;
	PIMSMHeader pimsmHeader;
	pimsmHeader.SetData (10);
	// copy the header into the packet
	p->AddHeader (pimsmHeader);

}

}

}

