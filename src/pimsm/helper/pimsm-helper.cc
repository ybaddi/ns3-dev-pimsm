/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */

#include "pimsm-helper.h"
#include "ns3/pimsm.h"
#include "ns3/olsr-routing-protocol.h"
#include "ns3/node-list.h"
#include "ns3/names.h"
#include "ns3/ptr.h"
#include "ns3/ipv4-list-routing.h"

namespace ns3 {


    PimsmHelper::PimsmHelper() {

    }


    PimsmHelper::~PimsmHelper() {

    }

    PimsmHelper* PimsmHelper::Copy (void) const{
        return new PimsmHelper (*this);
    }

    Ptr<Ipv4RoutingProtocol> PimsmHelper::Create (Ptr<Node> node) const{
        return NULL;
    }

    void PimsmHelper::AddMulticastRoute(Ptr< Node > 	n, Ipv4Address source, Ipv4Address group, Ptr <NetDevice> input,
                                        NetDeviceContainer output) {

    }

    void PimsmHelper::SetDefaultMulticastRoute(Ptr <Node> n, Ptr <NetDevice> nd) {

    }


}

