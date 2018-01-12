//
// Created by baddi on 28/02/16.
//
#include <list>

#include "ns3/header.h"
#include "ns3/address-utils.h"
#include "ns3/packet.h"
#include "ns3/ipv4-address.h"

#ifndef NS_3_DEV_MULTICAST_MODULE_PIM_SM_PACKET_H
#define NS_3_DEV_MULTICAST_MODULE_PIM_SM_PACKET_H

#endif //NS_3_DEV_MULTICAST_MODULE_PIM_SM_PACKET_H

namespace ns3 {
namespace pimsm {

enum MessageType
{
  PIMSMTYPE_PIMHELLO  = 0,   //!< PIMSMTYPE_PIMHELLO
};


/**
* \ingroup aodv
* \brief   Route Request (RREQ) Message Format
* RFC 7761
  \verbatim
  0                   1                   2                   3
  0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
  |PIM Ver| Type  |   Reserved    |           Checksum            |
  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
  \endverbatim

  PIM Ver
         PIM Version number is 2.

   Type
         Types for specific PIM messages.  PIM Types are:

   Message Type                          Destination
   ---------------------------------------------------------------------
   0 = Hello                             Multicast to ALL-PIM-ROUTERS
   1 = Register                          Unicast to RP
   2 = Register-Stop                     Unicast to source of Register
                                            packet
   3 = Join/Prune                        Multicast to ALL-PIM-ROUTERS
   4 = Bootstrap                         Multicast to ALL-PIM-ROUTERS
   5 = Assert                            Multicast to ALL-PIM-ROUTERS
   6 = Graft (used in PIM-DM only)       Unicast to RPF'(S)
   7 = Graft-Ack (used in PIM-DM only)   Unicast to source of Graft
                                            packet
   8 = Candidate-RP-Advertisement        Unicast to Domain's BSR
*/


class PIMSMHeader: public Header {
public:
	PIMSMHeader (MessageType t = PIMSMTYPE_PIMHELLO);
	// must be implemented to become a valid new header.
	static TypeId GetTypeId(void);
	virtual TypeId GetInstanceTypeId(void) const;
	virtual uint32_t GetSerializedSize(void) const;
	virtual void Serialize(Buffer::Iterator start) const;
	virtual uint32_t Deserialize(Buffer::Iterator start);
	virtual void Print(std::ostream &os) const;

	// allow protocol-specific access to the header data.
	void SetData(uint32_t data);
	uint32_t GetData(void) const;

	/// Return type
	MessageType Get() const {
		return m_type;
	}
	/// Check that type if valid
	bool IsValid() const {
		return m_valid;
	}
	bool operator==(PIMSMHeader const & o) const;
private:
	MessageType m_type;
	bool m_valid;
	Buffer m_data;
};

std::ostream & operator<< (std::ostream & os, PIMSMHeader const & h);

/**
* \ingroup pimsm
* \brief   Hello Message Format
  \verbatim
   0                   1                   2                   3
   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |PIM Ver| Type  |   Reserved    |           Checksum            |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |          OptionType           |         OptionLength          |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |                          OptionValue                          |
   |                              ...                              |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |                               .                               |
   |                               .                               |
   |                               .                               |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |          OptionType           |         OptionLength          |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |                          OptionValue                          |
   |                              ...                              |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
  \endverbatim
*/
class PimsmHelloHeader : public PIMSMHeader
{
public:
	PimsmHelloHeader(uint8_t reserved = 0, uint8_t checksum = 0);

	// Header serialization/deserialization
	  static TypeId GetTypeId ();
	  TypeId GetInstanceTypeId () const;
	  uint32_t GetSerializedSize () const;
	  void Serialize (Buffer::Iterator start) const;
	  uint32_t Deserialize (Buffer::Iterator start);
	  void Print (std::ostream &os) const;

	  // Fields
private:
	  uint8_t        m_reserved;       ///< Not used
	  uint8_t        m_checksum;       ///< Checksum
};

std::ostream & operator<< (std::ostream & os, PimsmHelloHeader const &);

/**
* \ingroup pimsm
* \brief   Hello Message Format :  OptionType 1: Holdtime
  \verbatim
     0                   1                   2                   3
     0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
     +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
     |          Type = 1             |         Length = 2            |
     +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
     |          Holdtime             |
     +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
  \endverbatim
*/

class PimsmHelloHeaderHoldTimeHeader : public PimsmHelloHeader
{
public:
	PimsmHelloHeaderHoldTimeHeader();

	// Header serialization/deserialization
	static TypeId GetTypeId ();
	TypeId GetInstanceTypeId () const;
	uint32_t GetSerializedSize () const;
	void Serialize (Buffer::Iterator start) const;
	uint32_t Deserialize (Buffer::Iterator start);
	void Print (std::ostream &os) const;

	// Fields
private:
	uint8_t m_type ;
	uint8_t m_length;
	uint8_t m_holdtime;
};

	std::ostream & operator<< (std::ostream & os, PimsmHelloHeaderHoldTimeHeader const &);

/**
* \ingroup pimsm
* \brief   Hello Message Format : OptionType 2: LAN Prune Delay
  \verbatim

      0                   1                   2                   3
      0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
     +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
     |          Type = 2             |          Length = 4           |
     +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
     |T|      Propagation_Delay      |      Override_Interval        |
     +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

  \endverbatim
*/

class PimsmHelloHeaderLANPruneDelayHeader : public PimsmHelloHeader
	{
	public:
		PimsmHelloHeaderLANPruneDelayHeader();

		// Header serialization/deserialization
		static TypeId GetTypeId ();
		TypeId GetInstanceTypeId () const;
		uint32_t GetSerializedSize () const;
		void Serialize (Buffer::Iterator start) const;
		uint32_t Deserialize (Buffer::Iterator start);
		void Print (std::ostream &os) const;

		// Fields
	private:
		uint8_t m_type ;
		uint8_t m_length;
		uint8_t propagation_Delay;
		uint8_t override_Interval;
	};

	std::ostream & operator<< (std::ostream & os, PimsmHelloHeaderLANPruneDelayHeader const &);

/**
* \ingroup pimsm
* \brief   Hello Message Format : OptionType 19: DR Priority
  \verbatim

	       0                   1                   2                   3
	       0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
	      +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
	      |          Type = 19            |          Length = 4           |
	      +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
	      |                         DR Priority                           |
	      +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

  \endverbatim
*/

	class PimsmHelloHeaderDRPriorityHeader : public PimsmHelloHeader
	{
	public:
		PimsmHelloHeaderDRPriorityHeader();

		// Header serialization/deserialization
		static TypeId GetTypeId ();
		TypeId GetInstanceTypeId () const;
		uint32_t GetSerializedSize () const;
		void Serialize (Buffer::Iterator start) const;
		uint32_t Deserialize (Buffer::Iterator start);
		void Print (std::ostream &os) const;

		// Fields
	private:
		uint8_t m_type ;
		uint8_t m_length;
		uint8_t DR_priority;
	};

	std::ostream & operator<< (std::ostream & os, PimsmHelloHeaderDRPriorityHeader const &);

/**
* \ingroup pimsm
* \brief   Hello Message Format : OptionType 20: Generation ID
  \verbatim

		        0                   1                   2                   3
		        0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
		       +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
		       |          Type = 20            |          Length = 4           |
		       +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
		       |                       Generation ID                           |
		       +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+


  \endverbatim
*/

class PimsmHelloHeaderGenerationIDHeader : public PimsmHelloHeader
	{
	public:
	PimsmHelloHeaderGenerationIDHeader();

		// Header serialization/deserialization
		static TypeId GetTypeId ();
		TypeId GetInstanceTypeId () const;
		uint32_t GetSerializedSize () const;
		void Serialize (Buffer::Iterator start) const;
		uint32_t Deserialize (Buffer::Iterator start);
		void Print (std::ostream &os) const;

		// Fields
	private:
		uint8_t m_type ;
		uint8_t m_length;
		uint16_t genration_ID;
	};

	std::ostream & operator<< (std::ostream & os, PimsmHelloHeaderGenerationIDHeader const &);

/**
* \ingroup pimsm
* \brief   Hello Message Format : OptionType 24: Address List
  \verbatim
			        0                   1                   2                   3
			        0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
			       +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
			       |          Type = 24            |      Length = <Variable>      |
			       +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
			       |         Secondary Address 1 (Encoded-Unicast format)          |
			       +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
			                                      ...
			       +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
			       |         Secondary Address N (Encoded-Unicast format)          |
			       +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

  \endverbatim
*/

class PimsmHelloHeaderAddressListHeader : public PimsmHelloHeader
	{
	public:
	PimsmHelloHeaderAddressListHeader();

		// Header serialization/deserialization
		static TypeId GetTypeId ();
		TypeId GetInstanceTypeId () const;
		uint32_t GetSerializedSize () const;
		void Serialize (Buffer::Iterator start) const;
		uint32_t Deserialize (Buffer::Iterator start);
		void Print (std::ostream &os) const;

		// Fields
	private:
		uint8_t m_type ;
		uint8_t m_length;
	    std::list<Ipv4Address> SecondaryAddress;
	};

	std::ostream & operator<< (std::ostream & os, PimsmHelloHeaderAddressListHeader const &);

}
}

