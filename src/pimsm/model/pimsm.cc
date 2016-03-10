/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */

#include "pimsm.h"
#include "ns3/address-utils.h"
#include "ns3/packet.h"
#include "ns3/core-module.h"
#include "ns3/log.h"
#include <iostream>
#include "pimsm-header.h"
#include "ns3/ipv4-routing-protocol.h"
#include "ns3/ipv4-routing-table-entry.h"
#include "ns3/ipv4-route.h"

namespace ns3 {

    NS_LOG_COMPONENT_DEFINE ("pimsm");

    namespace pimsm {




        PIMSMProtocol::PIMSMProtocol()
                 {
            //m_uniformRandomVariable = CreateObject<UniformRandomVariable> ();

            //m_hnaRoutingTable = Create<Ipv4StaticRouting> ();
        }

        PIMSMProtocol::~PIMSMProtocol() {

        }

//        Ptr <Ipv4Route>
//        PIMSMProtocol::RouteOutput(Ptr <Packet> p, const Ipv4Header &header, Ptr <NetDevice> oif,
//                                     Socket::SocketErrno &sockerr) {
//            Ptr <Ipv4Route> rtentry;
//            return rtentry;
//        }
//
//        bool
//        PIMSMProtocol::RouteInput(Ptr<const Packet> p,
//                   const Ipv4Header &header,
//                   Ptr<const NetDevice> idev,
//                   UnicastForwardCallback ucb,
//                   MulticastForwardCallback mcb,
//                   LocalDeliverCallback lcb,
//                   ErrorCallback ecb) {
//            return true;
//        }
//
//        void
//        PIMSMProtocol::NotifyInterfaceUp (uint32_t i)
//        {}
//        void
//        PIMSMProtocol::NotifyInterfaceDown (uint32_t i)
//        {}
//        void
//        PIMSMProtocol::NotifyAddAddress (uint32_t interface, Ipv4InterfaceAddress address)
//        {}
//        void
//        PIMSMProtocol::NotifyRemoveAddress (uint32_t interface, Ipv4InterfaceAddress address)
//        {}
//
//        void
//        PIMSMProtocol::PrintRoutingTable (Ptr<OutputStreamWrapper> stream) const
//        {
//
//        }
//
//        void
//        PIMSMProtocol::SetIpv4 (Ptr<Ipv4> ipv4)
//        {
//
//        }

        void PIMSMProtocol::ProcessHello(void) {
            NS_LOG_FUNCTION(this);
            std::cout << "Starting simulation for  ...\n";
            Ptr <Packet> p = Create<Packet>();;
            PacketHeader pimsmHeader;
            pimsmHeader.SetData(10);
            // copy the header into the packet
            p->AddHeader(pimsmHeader);


        }

    }

}

