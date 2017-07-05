/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 */
#include "pimsm-header.h"
#include "ns3/address-utils.h"
#include "ns3/packet.h"
#include "ns3/log.h"

namespace ns3 {

    NS_LOG_COMPONENT_DEFINE ("PIMSMHeader");

    namespace pimsm {

        PIMSMHeader::PIMSMHeader(MessageType t) :
                m_type(t), m_valid(true) {
        }

        TypeId PIMSMHeader::GetTypeId(void) {
            NS_LOG_INFO("creating the nodes");
            static TypeId tid = TypeId("ns3::pimsm::PIMSMHeader")
                    .SetParent<Header>()
                    .AddConstructor<PIMSMHeader>();
            return tid;
        }

        TypeId
        PIMSMHeader::GetInstanceTypeId(void) const {
            return GetTypeId();
        }

        uint32_t
        PIMSMHeader::GetSerializedSize(void) const {
            return 6;
        }

        void
        PIMSMHeader::Serialize(Buffer::Iterator start) const {
            // The 2 byte-constant
            start.WriteU8(0xfe);
            start.WriteU8(0xef);
            // the message type
            start.WriteU8((uint8_t) m_type);
            // The data.
            start.Write (m_data.Begin (), m_data.End ());
        }

        uint32_t
        PIMSMHeader::Deserialize(Buffer::Iterator start) {
            Buffer::Iterator i = start;
            uint8_t tmp;
            tmp = start.ReadU8();
            NS_ASSERT(tmp == 0xfe);
            tmp = start.ReadU8();
            NS_ASSERT(tmp == 0xef);
            m_data = start.ReadNtohU32();
            uint32_t dist = i.GetDistanceFrom(start);
            NS_ASSERT(dist == GetSerializedSize());
            return dist; // the number of bytes consumed.
        }

        void PIMSMHeader::Print(std::ostream &os) const {
            switch (m_type) {
                case PIMSMTYPE_PIMHELLO: {
                    os << "RREQ";
                    break;
                }
                default:
                    os << "UNKNOWN_TYPE";
            }
        }

        bool
        PIMSMHeader::operator==(PIMSMHeader const &o) const {
            return (m_type == o.m_type && m_valid == o.m_valid);
        }

        std::ostream &
        operator<<(std::ostream &os, PIMSMHeader const &h) {
            h.Print(os);
            return os;
        }

//-----------------------------------------------------------------------------


        void PIMSMHeader::SetData(uint32_t data) {

            m_data = data;

        }



//-----------------------------------------------------------------------------
// Pimsm Hello
//-----------------------------------------------------------------------------

        PimsmHelloHeader::PimsmHelloHeader(uint8_t reserved, uint8_t checksum) :
                m_reserved(reserved), m_checksum(checksum)
        {
        }

        NS_OBJECT_ENSURE_REGISTERED (PimsmHelloHeader);

        TypeId
        PimsmHelloHeader::GetTypeId() {
            static TypeId tid = TypeId("ns3::pimsm::PimsmHelloHeader")
                    .SetParent<Header>()
                    .SetGroupName("Pimsm")
                    .AddConstructor<PimsmHelloHeader>();
            return tid;
        }

        TypeId
        PimsmHelloHeader::GetInstanceTypeId () const
        {
            return GetTypeId ();
        }

        uint32_t
        PimsmHelloHeader::GetSerializedSize () const
        {
            return 23;
        }

        void
        PimsmHelloHeader::Serialize (Buffer::Iterator i) const
        {

        }

        uint32_t
        PimsmHelloHeader::Deserialize (Buffer::Iterator start)
        {
            Buffer::Iterator i = start;

            m_reserved = i.ReadU8 ();
            m_checksum = i.ReadU8 ();

            return GetSerializedSize ();

        }

        void
        PimsmHelloHeader::Print (std::ostream &os) const
        {

        }

        std::ostream &
        operator<< (std::ostream & os, PimsmHelloHeader const & h)
        {
            h.Print (os);
            return os;
        }

    }
}
