//
// Created by Youssef Baddi on 12/6/16.
//

#include "ns3/test.h"
#include "ns3/pim-sm-header.h"
#include "ns3/packet.h"
#include "ns3/ipv4-route.h"

namespace ns3
{
namespace pimsm
{

    class PimsmHelloTestCase : public TestCase {
    public:
        PimsmHelloTestCase();

        virtual void DoRun(void);
    };

    PimsmHelloTestCase::PimsmHelloTestCase()
            : TestCase("Check Hello pimsm messages") {
    }

    void
    PimsmHelloTestCase::DoRun(void) {
        PimsmHelloHeader pimsmHelloHeader(/* m_reserved */ 0, /* m_checksum */ 0);
        //pimsmHelloHeader.SetId (55);
        Ptr <Packet> p = Create<Packet>();
        p->AddHeader (pimsmHelloHeader);
    }

}
}