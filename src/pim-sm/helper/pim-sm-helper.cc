/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */

#include "pim-sm-helper.h"
#include "ns3/pim-sm.h"
#include "ns3/olsr-routing-protocol.h"
#include "ns3/node-list.h"
#include "ns3/names.h"
#include "ns3/ptr.h"
#include "ns3/ipv4-list-routing.h"

namespace ns3 {



    PimsmHelper::PimsmHelper ()
    {
        m_agentFactory.SetTypeId ("ns3::pimsm::PIMSMProtocol");
    }

    PimsmHelper::PimsmHelper (const PimsmHelper &o)
            : m_agentFactory (o.m_agentFactory)
    {
        m_interfaceExclusions = o.m_interfaceExclusions;
    }

    PimsmHelper::~PimsmHelper ()
    {

    }

    PimsmHelper*
    PimsmHelper::Copy (void) const
    {
        return new PimsmHelper (*this);
    }

    void
    PimsmHelper::ExcludeInterface (Ptr<Node> node, uint32_t interface)
    {

    }

    Ptr<Ipv4RoutingProtocol>
    PimsmHelper::Create (Ptr<Node> node) const {
        Ptr <pimsm::PIMSMProtocol> agent = m_agentFactory.Create<pimsm::PIMSMProtocol>();
        return agent;
    }

    void
    PimsmHelper::Set (std::string name, const AttributeValue &value)
    {
        m_agentFactory.Set (name, value);
    }

    int64_t
    PimsmHelper::AssignStreams (NodeContainer c, int64_t stream)
    {
        int64_t currentStream = stream;

        return (currentStream - stream);

    }

    }

